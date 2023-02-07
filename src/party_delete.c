#include <dhanda/dhanda.h>
#include <dhanda/party.h>
#include <unistd.h>




int party_delete(dhanda *app, party *party)	/*returns 1 for success*/
{											/*returns -1 for failure*/

	int ret;
	char sql[1024];
	char *err = NULL;

	sprintf(sql, "DELETE FROM parties WHERE id = '%d'", party->id);

	ret = sqlite3_exec(app->db, sql, NULL, NULL, &err);
	if (ret != SQLITE_OK) {
		fprintf(stderr, "sqlite3_exec error: %s\n", err);
		return -1;
	}

	app_success_set(app, "Party deleted successfully");
	return 0;
}
			
	
	
	
	
	
	
	
	
	
	
	
