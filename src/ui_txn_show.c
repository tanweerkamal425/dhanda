#include <dhanda/dhanda.h>
#include <dhanda/txn.h>
#include <dhanda/ui.h>


void ui_txn_show(struct dhanda *app)
{
	Node *ptr;
	ptr = app->txn_list->head;
	txn *t;
	debug_print("");

	t = (txn *) ptr->data;

	sky();
	bold();
	centreprint("DHANDA > TRANSACTION > SHOW");
	printf("\n\n");
	reset();
	printf("%-10s %-10s %-10s %-10s %-15s", "ID", 
												  "AMOUNT", 
												  "TYPE",
												  "PARTY_ID",
												  "DESC");
	printf("\n\n");
	
	printf("%-10d %-10d %-10d %-10d %-15s\n\n", t->id, 
										  t->amount, 
										  t->type,
										  t->party_id, 
										  t->desc);

}

