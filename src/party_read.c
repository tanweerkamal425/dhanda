#include <dhanda/dhanda.h>
#include <dhanda/party.h>




int party_findbyid(dhanda *app, int id, party *result) /*returns 1 if found*/
{														/*returns 0 if not found*/
	int ret;											/*return -1 for error*/
	int found = 0;
	char sql[1024];
	char *err = NULL;
	int is_found = 0;

	sprintf(sql, "SELECT * FROM parties WHERE id = %d", id);

	result->id = 0;
	ret = sqlite3_exec(app->db, sql, put_in_party_struct, (void *) result, &err);
	if (ret != SQLITE_OK) {
		fprintf(stderr, "sqlite_exec: %s\n", err);
		return -1;
	}

	if (result->id == 0) {
		app_error_set(app, "Party not found");
		return 0;
	}

	app_success_set(app, "Party found");
	return 1;
}


int party_search(dhanda *app, char *query, struct list *result)/*returns 1 if found*/
{															/*returns 0 if not found*/
															/*returns -1 for error*/
	int ret;
	char sql[1024];
	char *err = NULL;
	int is_found = 0;

	sprintf(sql, "SELECT * FROM parties WHERE phone LIKE '%%%s%%' OR first_name LIKE '%%%s%%'",
		query,
		query);

	ret = sqlite3_exec(app->db, sql, put_in_party_list, (void *) result, &err);
	if (ret != SQLITE_OK) {
		fprintf(stderr, "sqlite3_exec: %s\n", err);
		return -1;
	}

	if (result->head == NULL) {
		app_error_set(app, "Party not found");
		return -1;
	}

	app_success_set(app, "Party searched successfully");

	return 0;
	
}
			

int party_get(dhanda *app, party_filter filter, struct list *result)
{
	int ret;
	char *err = NULL;
	char sql[1024];

	sprintf(sql, "SELECT * FROM parties");

	ret = sqlite3_exec(app->db, sql, put_in_party_list, (void *) result, &err);
	if (ret != SQLITE_OK) {
		fprintf(stderr, "sqlite3_exec error: %s\n", err);
		return -1;
	}

	if (result->head == NULL) {
		app_error_set(app, "Party not found");
		return 0;
	}

	app_success_set(app, "Party found");
	return 1;
}

int put_in_party_struct(void *ptr, int ncols, char **values, char **fields)
{
	party *temp = (party *) ptr;
	
	temp->id = (int) strtol(values[0], NULL, 10);
	strcpy(temp->fname, values[1]);
	strcpy(temp->lname, values[2]);
	strcpy(temp->phone, values[3]);
	temp->amount = (int) strtol(values[4], NULL, 10);
	temp->cat = unix_time(values[5]);
	temp->uat = unix_time(values[6]);

	return SQLITE_OK;
		
}


int put_in_party_list(void *ptr, int ncols, char **values, char **fields)
{
	Node *node;
	party temp = {};

	temp.id = atoi(values[0]);
	strcpy(temp.fname, values[1]);
	strcpy(temp.lname, values[2]);
	strcpy(temp.phone, values[3]);
	temp.amount = atoi(values[4]);
	temp.cat = unix_time(values[5]);
	temp.uat = unix_time(values[6]);


	node = list_new_node((struct list *) ptr, (void *) &temp);
	list_insert_end((struct list *) ptr, node);

	return SQLITE_OK;
		
}