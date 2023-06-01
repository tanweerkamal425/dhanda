#include <dhanda/dhanda.h>
#include <dhanda/txn.h>
#include <dhanda/ui.h>


void ui_txn_create(struct dhanda *app)
{
	txn t;
	char line[256], ch;
	int len;
	char pid[10];
	debug_print("");

	sky();
	bold();
	centreprint("DHANDA > TRANSACTION > CREATE");
	printf("\n\n");
	reset();

	printf("   PARTY ID : ");
	input_pid(app, &t.party_id, validate_pid);

	printf("\n");

	printf("   AMOUNT   : ");
	input_amount(&t.amount, validate_amount);

	printf("\n");

	printf("[O FOR CRED, 1 FOR DEBT]\n");
	printf("   TYPE     : ");
	input_txn_type(&t.type, validate_type);


	printf("\n");

	printf("   DESC     : ");
	get_string(t.desc, 256);
	printf("\n");

	time(&t.cat);

	txn_insert_in_list(app, &t);
	puts("");
}



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
