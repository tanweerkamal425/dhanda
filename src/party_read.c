#include <dhanda/dhanda.h>
#include <dhanda/party.h>




int party_findbyid(dhanda *app, int id, party *result)
{
	int ret;
	int found = 0;

	debug_print("");
	
	fseek(app->party_fp, 0, SEEK_SET);
	while((ret = fread(result, sizeof(party), 1, app->party_fp)) > 0) {
		if (ret != 1) {
			app_error_set(app, strerror(errno));
			return -1;
		}
		if(id == result->id) {
			found = 1;
			break;
		}
	}
	if (ferror(app->party_fp)) {
		app_error_set(app, strerror(errno));
		found = -1;
	}

	app_success_set(app, "Party found");
	return found;
}


int party_search(dhanda *app, char *query, struct list *result)
{
	party temp;
	Node *node;
	int matched = 0;

	debug_print("");
	
	fseek(app->party_fp, 0, SEEK_SET); 
	while(fread(&temp, sizeof(temp), 1, app->party_fp) > 0) {
		if(strstr(temp.phone, query)) {
			matched = 1;
			node = list_new_node(result, (void *) &temp);
			assert(node != NULL);
			list_insert_end(result, node);
		}

		else if (strstr(temp.fname, query) || strstr(temp.lname, query)) {
			matched = 1;
			node = list_new_node(result, (void *) &temp);
			assert(node != NULL);
			list_insert_end(result, node);
		}
		
	}

	if(matched == 0) {
		app_error_set(app, "Party not found");
		return matched;
	}

	app_success_set(app, "Party searched successfully");

	return matched;
	
}
			

int party_get(dhanda *app, party_filter filter, struct list *result)
{
	List *list;
	party temp;
	int count = 0, offset;
	Node *node;

	debug_print("");
	
	/*offset = (filter.page - 1) * filter.items * sizeof(party);
	fseek(app->party_fp, offset * -1, SEEK_END);*/
	
	fseek(app->party_fp, 0, SEEK_SET);
	while(fread(&temp, sizeof(temp), 1, app->party_fp) > 0) {
		if(count >= filter.items)
			break;
			
		node = list_new_node(result, (void *) &temp);
		list_insert_end(result, node);
		count++;
		
		if(node == NULL) 
			break;
	}

	if(count >= filter.items) {
		app_error_set(app, strerror(errno));
		return count;
	}
	
	app_success_set(app, "Party found");

	return count;
}
		

		














	
	
	
