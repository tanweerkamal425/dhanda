#include <dhanda/dhanda.h>
#include <dhanda/party.h>
#include <dhanda/ui.h>
#include <sys/types.h>
#include <regex.h>






void ui_party_create(struct dhanda *app)
{

	party p;
	int len;
	long ret;
	char s[100];
	char *ptr;
	char amount[10];

	//regular expression
	char *pattern = "^([a-zA-Z]{2, 31})$";

	regex_t rgx;


	sky();
	bold();
	centreprint("DHANDA > PARTY > CREATE");
	printf("\n\n");
	reset();


	printf("   FIRST NAME :  ");
	input_valid_string(p.fname, sizeof(p.fname), validate_name);
	title_case(p.fname);

	printf("   LAST NAME  :  ");
	input_valid_string(p.lname, sizeof(p.lname), validate_name);
	title_case(p.lname);

	printf("   PHONE      :  ");
	input_valid_string(p.phone, sizeof(p.phone), validate_phone);

	printf("  AMOUNT     :  ");
	input_amount(&p.amount, validate_amount);

	printf("\n");


	time(&p.cat);
	time(&p.uat);

	
	reset();
	party_insert_in_list(app, &p);

	puts("");

}


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


void ui_party_edit(struct dhanda *app)
{
	long int phone, amount;
	char fname[64], lname[64];
	party *old_party, *new_party;
	int len;
	char *ptr;
	long int ret;

	old_party = party_first_in_list(app);
	new_party = party_second_in_list(app);

	debug_print("");

	sky();
	bold();
	centreprint("DHANDA > PARTY > EDIT");
	printf("\n\n");
	reset();

	printf("FIRST NAME :  %s\n\n", old_party->fname);
	printf("LAST NAME  :  %s\n\n", old_party->lname);
	printf("PHONE      :  %s\n\n", old_party->phone);
	printf("AMOUNT     :  %d\n\n", old_party->amount);
	puts("");


	printf("   FIRST NAME :  ");
	input_valid_string(new_party->fname, sizeof(new_party->fname), validate_name);
	title_case(new_party->fname);

	printf("   LAST NAME  :  ");
	input_valid_string(new_party->lname, sizeof(new_party->lname), validate_name);
	title_case(new_party->lname);

	printf("   PHONE      :  ");
	input_valid_string(new_party->phone, sizeof(new_party->phone), validate_phone);

	printf("   AMOUNT     :  ");
	input_amount(&new_party->amount, validate_amount);

	printf("\n");

	printf("Added in time function\n");
	time(&new_party->uat);

}


void ui_party_list(struct dhanda *app)
{
	Node *ptr;
	party *p;
	ptr = app->party_list->head;
	char cat[32];
	char uat[32];
	/*printf("\x1b[30;106m  \x1b[1m \x1b[3m DHANDA > PARTY > LIST                    \n\n");
	printf("\x1b[0m");*/
	sky();
	bold();
	centreprint("DHANDA > PARTY > LIST");
	printf("\n\n");
	reset();
	// grey();
	yellow_fg();

	printf("   %-13s %-20s %-20s %-15s %-12s %-20s %-20s\n\n\n", "ID", "FIRST NAME", "LAST NAME", "AMOUNT", "PHONE", "CREATED_AT", "UPDATED_AT");
	reset();

	while(ptr){
		p = (party *) ptr->data;

		strcpy(cat, created_time(p->cat));
		strcpy(uat, created_time(p->uat));
		printf("   %-13d %-20s %-20s %-15d %-12s %-20s %-20s\n\n", p->id, p->fname, p->lname, p->amount, p->phone, cat, uat);
		ptr = ptr->next;
	}
}


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