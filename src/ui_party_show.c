#include <dhanda/dhanda.h>
#include <dhanda/party.h>
#include <dhanda/ui.h>


void ui_party_show(struct dhanda *app)
{
	party *p;

	p = party_first_in_list(app);

	sky();
	bold();
	centreprint("DHANDA > PARTY > SHOW");
	printf("\n\n");
	reset();

	// grey();
	printf("\x1b[95m");
	printf("   ID NO      : %d               \n\n", p->id);

	printf("   FIRST NAME : %s               ", p->fname);
	printf("\n\n");
	printf("   LAST NAME  : %s               ", p->lname);
	printf("\n\n");

	printf("   PHONE NO   : %s               \n\n", p->phone);

	printf("   AMOUNT     : %d               \n\n", p->amount);
	
	printf("   CREATED AT : ");
	created_at(p->cat);

	printf("\n");

	printf("   UPDATED AT : ");
	updated_at(p->uat);

	reset();
	
}
