#include<dhanda/dhanda.h>
#include<dhanda/party.h>

int party_add(dhanda *app, party *party)
{
	char sql[1024];
	char *err = NULL;
	int ret;

	char *cat = created_time(party->cat);
	char *uat = updated_time(party->uat);

	sprintf(sql, "INSERT INTO parties(first_name, last_name, phone, amount, created_at, updated_at) VALUES('%s','%s', '%s', '%d', '%s', '%s')", party->fname,
		party->lname,
		party->phone,
		party->amount,
		cat,
		uat);

	ret = sqlite3_exec(app->db, sql, NULL, NULL, &err);
	if (ret != SQLITE_OK) {
		fprintf(stderr, "sqlite3_exec error: %s\n", err);
		app_error_set(app, "Failed to add party");
		return -1;
	}

	party->id = sqlite3_last_insert_rowid(app->db);

	app_success_set(app, "Party added successfully");
	return 0;

}

