#include<dhanda/dhanda.h>
#include<dhanda/party.h>

int party_update(dhanda *app, party *old_party, struct party *new_party)
{
	party temp;
	int matched = -1;

	debug_print("");

	fseek(app->party_fp, 0, SEEK_SET);
	//rewind(app->party_fp);
	while(fread(&temp, sizeof(party), 1, app->party_fp) > 0)
	{
		if(temp.id == old_party->id)
		{
			matched = 0;
			fseek(app->party_fp, -sizeof(party), SEEK_CUR);
			fwrite(new_party, sizeof(party), 1, app->party_fp);
			break;
		}
	}
		 
	if (matched == -1) {
		app_error_set(app, strerror(errno));
		return -1;
	}

	app_success_set(app, "Party updated successfully");
	
	return 0;
 }		 
