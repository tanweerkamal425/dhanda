#include <dhanda/dhanda.h>
#include <dhanda/party.h>
#include <dhanda/txn.h>
#include <unistd.h>


void
txn_insert_in_list(dhanda *app, txn *t)
{
	Node *node;
	debug_print("");

	node = list_new_node(app->txn_list, t);
	if (node)
		list_insert_end(app->txn_list, node);
}

txn *
txn_first_in_list(dhanda *app)
{
	txn *t = NULL;
	Node *head;
	debug_print("");

	head = app->txn_list->head;
	if (head)
		t = (txn *) head->data;

	return t;
}

txn *
txn_second_in_list(dhanda *app)
{
	txn *t = NULL;
	Node *head;
	debug_print("");

	head = app->txn_list->head;
	if (head && head->next)
		t = (txn *) head->next->data;

	return t;
}



int txn_add(dhanda *app, txn *txn)
{
	char sql[1024];
	char *err = NULL;
	int ret;

	char *cat = created_time(txn->cat);

	sprintf(sql, "INSERT INTO transactions(amount, created_at, type, desc, party_id) VALUES(%d, '%s', %d, '%s', %d)", txn->amount, 
																															cat, 
																															txn->type, 
																															txn->desc, 
																															txn->party_id);
																
	ret = sqlite3_exec(app->db, sql, NULL, NULL, &err);
	if (ret != SQLITE_OK) {
		fprintf(stderr, "sqlite3_exec error: %s\n", err);
		app_error_set(app, "Failed to add transaction");
		return -1;
	}


	txn->id = sqlite3_last_insert_rowid(app->db);

	app_success_set(app, "Transaction added successfully");
	return 0;
}


int txn_delete(struct dhanda *app, int pid)
{
	int ret;
	char *err = NULL;
	char sql[1024];

	sprintf(sql, "DELETE FROM transactions WHERE party_id = %d", pid);

	ret = sqlite3_exec(app->db, sql, NULL, NULL, &err);
	if (ret != SQLITE_OK) {
		fprintf(stderr, "sqlite3_exec error: %s\n", err);
		app_error_set(app, "Failed to delete transaction");
		return -1;
	}

	app_success_set(app, "Transaction deleted successfully");
	return 0;
}


int txn_findbyid(dhanda *app, int id, txn *result)	/*returns 1 for success and -1 for failure*/
{
	int ret;
	char *err = NULL;
	char sql[1024];

	sprintf(sql, "SELECT * FROM transactions WHERE id = %d", id);
	ret = sqlite3_exec(app->db, sql, put_in_txn_struct, (void *) result, &err);
	if (ret != SQLITE_OK) {
		fprintf(stderr, "sqlite3_exec: %s\n", err);
		return -1;
	}

	return 1;
}


	
int txn_search(dhanda *app, char *query, struct list *result)/*returns 1 if found*/
{															/*returns 0 if not found*/
															/*returns -1 for error*/
	int ret;
	char *err = NULL;
	char sql[1024];

	int pid = atoi(query);

	sprintf(sql, "SELECT * FROM transactions WHERE party_id = %d", pid);

	ret = sqlite3_exec(app->db, sql, put_in_txn_list, (void *) result, &err);
	if (ret != SQLITE_OK) {
		fprintf(stderr, "sqlite3_exec: %s\n", err);
		return 0;

	}

	if (result->head == NULL) {
		app_error_set(app, "Transaction not found");
		return -1;
	}

	return 1;
}



int txn_findbytype(dhanda *app, int type, struct list *result)
{	
	int ret;
	char *err = NULL;
	char sql[1024];

	sprintf(sql, "SELECT * FROM transactions WHERE type = %d", type);

	ret = sqlite3_exec(app->db, sql, put_in_txn_list, (void *) result, &err);
	if (ret != SQLITE_OK) {
		fprintf(stderr, "sqlite3_exec error: %s\n", err);
		return 0;
	}

	if (result->head == NULL) {
		app_error_set(app, "Transaction not found");
		return -1;
	}

	app_success_set(app, "Transaction found");
	return 0;
}



int txn_get(dhanda *app, txn_filter filter, struct list *result)
{
	int ret;
	char *err = NULL;
	char sql[1024];

	sprintf(sql, "SELECT * FROM transactions");

	ret = sqlite3_exec(app->db, sql, put_in_txn_list, (void *) result, &err);
	if (ret != SQLITE_OK) {
		fprintf(stderr, "sqlite3_exec error: %s\n", err);
		return -1;
	}

	if (result->head == NULL) {
		app_error_set(app, "Transaction not found");
		return 0;
	}

	app_success_set(app, "Transaction found");
	return 1;
}


int put_in_txn_struct(void *ptr, int ncols, char **values, char **fields)
{
	txn *temp = (txn *) ptr;

	temp->id = (int) strtol(values[0], NULL, 10);
	temp->amount = (int) strtol(values[1], NULL, 10);
	temp->cat = unix_time(values[2]);
	temp->type = (int) strtol(values[3], NULL, 10);
	strcpy(temp->desc, values[4]);
	temp->party_id = (int) strtol(values[5], NULL, 10);

	return SQLITE_OK;
}

int put_in_txn_list(void *ptr, int ncols, char **values, char **fields)
{
	Node *node;
	txn temp = {};

	temp.id = (int) strtol(values[0], NULL, 10);
	temp.amount = (int) strtol(values[1], NULL, 10);
	temp.cat = unix_time(values[2]);
	temp.type = (int) strtol(values[3], NULL, 10);
	strcpy(temp.desc, values[4]);
	temp.party_id = (int) strtol(values[5], NULL, 10);

	node = list_new_node((struct list *) ptr, (void *) &temp);
	assert(node != NULL);
	list_insert_end((struct list *) ptr, node);

	return SQLITE_OK;
}
