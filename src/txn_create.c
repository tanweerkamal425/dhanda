#include<dhanda/dhanda.h>
#include<dhanda/txn.h>

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
