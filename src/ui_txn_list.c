#include <dhanda/dhanda.h>
#include <dhanda/txn.h>
#include <dhanda/ui.h>

void ui_txn_list(struct dhanda *app)
{
	Node *temp;
	txn *t;
	debug_print("");

	sky();
	bold();
	centreprint("DHANDA > TRANSACTION > LIST");
	printf("\n\n");
	reset();
	printf("   ID         PARTY_ID            AMOUNT          DEBIT/CREDIT(D/C)\n");
	printf("\n\n");

	temp = app->txn_list->head;
	while(temp != NULL)
	{	
		t = (txn *)temp->data;
         	printf("   %-10d %-19d %-15d %-15d\n\n",
			       	t->id,
				t->party_id,
			       	t->amount,
			       	t->type);

		temp = temp->next;
	}

}

