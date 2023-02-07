#include <dhanda/dhanda.h>
#include <dhanda/party.h>
#include <dhanda/txn.h>
#include <unistd.h>

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