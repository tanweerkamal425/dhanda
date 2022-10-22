#include <dhanda/dhanda.h>
#include <dhanda/party.h>
#include <dhanda/ui.h>
#include <sys/types.h>
#include <regex.h>



/*void input_valid_string(char *in, size_t size, int (*validator)(char *))
{
	while(1) {
		printf("> ");
		get_string(in, size);
		
		if(validator(in) == 0) break;
		
		printf("Invalid input\n");
	}
}*/


void ui_party_create(struct dhanda *app)
{
	/*long int phone = 9748538411,
		amount = 10000;
	char fname[64] = "Safwan", lname[64] = "Haider";
	*/
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

	// input_valid_string(p.fname, sizeof(p.fname), validator);
	// e.g. Input first name
	// input_valid_string(p.fname, sizeof(p.fname), validate_name);
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

	





