#include <dhanda/dhanda.h>
#include <dhanda/txn.h>
#include <dhanda/ui.h>

void ui_txn_list(struct dhanda *app)
{
	Node *temp;
	txn *t;
	char cat[32];

	sky();
	bold();
	centreprint("DHANDA > TRANSACTION > LIST");
	printf("\n\n");
	reset();

	blue_fg();
	printf("   %-10s %-10s %-15s %-20s %-20s\n\n\n", "ID", "PARTY_ID", "AMOUNT", "DEBIT/CREDIT(D/C)", "CREATED_AT");
	reset();

	temp = app->txn_list->head;
	while(temp != NULL)
	{	
		t = (txn *)temp->data;
		strcpy(cat, created_time(t->cat));
        printf("   %-10d %-10d %-15d %-20d %-20s\n\n",	t->id,
														t->party_id,
												       	t->amount,
												       	t->type,
												       	cat);

        temp = temp->next;
	}

}

