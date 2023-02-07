#include<dhanda/dhanda.h>
#include<dhanda/party.h>

int party_update(dhanda *app, party *old_party, struct party *new_party) /*returns 0 for success*/
{																		/*return -1 for error*/
	party temp;
	int matched = -1;

	int ret;
	char *err = NULL;
	char sql[1024];

	char *cat = created_time(new_party->cat);
    char *uat = updated_time(new_party->uat);

	sprintf(sql, "UPDATE parties SET "
				"first_name = '%s', last_name = '%s',"
				"phone = '%s', amount = %d,"
				"created_at = '%s', updated_at = '%s' WHERE id = %d",
														new_party->fname,
														new_party->lname,
														new_party->phone,
														new_party->amount,
														cat,
														uat,
														new_party->id);

	ret = sqlite3_exec(app->db, sql, NULL, NULL, &err);
	if (ret != SQLITE_OK) {
		fprintf(stderr, "sqlite3_exec error: %s\n", err);
		app_error_set(app, "Failed to updated party");
		return -1;
	}

	app_success_set(app, "Party updated successfully");
	
	return 0;
 }		 
