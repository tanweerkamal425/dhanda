#include <dhanda/dhanda.h>
#include <dhanda/txn.h>

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

	sprintf(sql, "SELECT * FROM transactions WHERE phone = '%s'", query);

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
