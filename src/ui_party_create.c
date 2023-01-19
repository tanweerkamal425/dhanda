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
	grey();


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

	
	reset();
	party_insert_in_list(app, &p);

	puts("");

}

	





