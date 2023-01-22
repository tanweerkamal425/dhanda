#include <dhanda/dhanda.h>
#include <dhanda/party.h>
#include <dhanda/ui.h>



void ui_party_delete(struct dhanda *app)
{
	Node *ptr;
	party *p;
	char choice;
	char line[8];

	debug_print("");


	sky();
	bold();
	centreprint("DHANDA > PARTY > DELETE");
	printf("\n\n");
	reset();


	ptr = app->party_list->head;
	while(!ptr){
		p = (party *) ptr->data;
	}

	confirmation();
	get_string(line, sizeof(line));
	char ch = line[0];
	if (ch == 'y' || ch == 'Y') {
		p->deletion_confirmed = 0;
	} else {
		p->deletion_confirmed = -1;
	}

}
