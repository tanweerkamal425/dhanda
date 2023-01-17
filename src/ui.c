#include <dhanda/dhanda.h>
#include <dhanda/ui.h>


void
ui_home(dhanda *app)
{
	int txn = app->txn_list->count,
		amount = 12399,
		party = app->party_list->count,
		debit = 144,
		credit = 12;

	sky();
	bold();
	centreprint("DHANDA");
	printf("\n\n");
	reset();
	printf("Total # txn     Total amount   Total # party    Total debit     Total credit");
	printf("\n");
	printf("___________     ____________   _____________    ___________     ____________");
	printf("\n\n");
	printf("%-15d %-15d %-15d %-15d %-15d ", txn, 
											amount, 
											party, 
											debit, 
											credit);
	printf("\n\n");
	puts("");


}


