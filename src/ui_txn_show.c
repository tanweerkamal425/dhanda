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

	printf("\x1b[95m");
	printf("   ID NO      : %d               \n\n", t->id);
	printf("   AMOUNT     : %d               \n\n", t->amount);
	printf("   TYPE       : %d               \n\n", t->type);
	printf("   PARTY_ID   : %d               \n\n", t->party_id);
	printf("   DESC       : %s               \n", t->desc);
	printf("   CREATED AT : ");
	created_at(t->cat);
	printf("\n");
	reset();

}

