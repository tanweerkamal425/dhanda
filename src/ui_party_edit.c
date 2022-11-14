#include <dhanda/dhanda.h>
#include <dhanda/party.h>
#include <dhanda/ui.h>
#include <sys/types.h>
#include <regex.h>


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


	time(&new_party->cat);



	/*
	while(1) {
		printf("FIRST NAME :  ");
		get_string(new_party->fname, sizeof(new_party->fname));
		new_party->fname[0] = new_party->fname[0] - ('a' - 'A');

		if(is_valid(new_party->fname) == -1) {
			printf("Invalid first name");
			continue;
		} else {
			break;
		}
	}


	while(1) {
		printf("LAST NAME  :  ");
		get_string(new_party->lname, sizeof(new_party->lname));
		new_party->lname[0] = new_party->lname[0] - ('a' - 'A');

		if(is_valid(new_party(lname)) == -1) {
			printf("Invalid last name");
			continue;
		} else {
			break;
		}
	}

	while(1) {
		printf("PHONE      :  ");
		get_string(new_party->phone, sizeof(new_party->phone));
		if(strlen(p.phone) < 10) {
			printf("Invalid phone number");
			continue;
		} else {
			break;
		}
	}

	while(1) {
		printf("AMOUNT     :  ");
		char amount[10];
		get_string(amount, sizeof(amount));
	    long ret = strtol(amount, NULL, 10);

	    if(ret == 0) {
	    	printf("Invalid amount input");
	    	continue;
	    } else {
	    	new_party->amount = (int) ret;
	    	break;
	    }
	}
	*/
}
