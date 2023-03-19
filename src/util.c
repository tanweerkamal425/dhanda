#include <dhanda/dhanda.h>
#include <dhanda/party.h>
#include <dhanda/txn.h>

int get_line(char line[], int size)
{
	int i;
	char ch;

	i = 0;
	do
	{
		ch = getchar();
		line[i] = ch;
		++i;
	} while (ch != EOF && ch != '\n' && i < size - 1);

	if (ch == EOF)
		line[--i] = '\0';
	else
		line[i] = '\0';

	return i;
}

int
get_string(char line[], int size)
{
	int len;

	len = get_line(line, size);
	line[len - 1] = '\0';

	return len - 1;
}

//COLORS FUNCTIONS
void sky()
{
	printf("\x1b[30;106m");
}
void red () {
  printf("\x1b[1;31m");
}
void yellow() {
  printf("\x1b[1;33m");
}
void grey(){
	printf("\x1b[30;47m");
}
void reset () {
  printf("\x1b[0m");
}
void bold(){
	printf("\x1b[1m");
}
void green(){
	printf("\x1b[30;42m");
}

void yellow_fg() {
	printf("\x1b[33m");
}

void magenta_fg() {
	printf("\x1b[95m");
}

void blue_fg() {
	printf("\x1b[94m");
}


void error() {
	printf("\x1b[37;41m");
	printf("ERROR:");
	reset();
	printf(" ");
}
void success() {
	printf("\x1b[37;42m");
	printf("SUCCESS:");
	reset();
	printf(" ");
}
void warning() {
	yellow();
	printf("WARNING:");
}

void confirmation() {
	red();
	printf("Do you want to delete [y/n]?: ");
}


//CENTRE PRINTING FUNCTION

void centreprint(char *s)
{

	int len = strlen(s);
	int x = 136;

	int sp = x - len;

	for (int i = 0; i < sp / 2; ++i)
	{

		printf(" ");
	}
	printf("%s", s);
	for (int i = 0; i < sp / 2; ++i)
	{
		printf(" ");
	}

}

void print_success(char *s)
{

	printf("\x1b[1;32m");
	printf("%s", s);
}

void print_error(char *s)
{
	printf("\x1b[1;31m");
	printf("%s", s);
}

void print_warning(char *s)
{
	printf("\x1b[1;93m");
	printf("%s", s);
}


void created_at(time_t t) 
{
	struct tm *tm;
	char timestr[100];


	tm = localtime(&t);

	strftime(timestr, sizeof(timestr), "%Y-%m-%d %T", tm);

	printf("%s\n", timestr);

}

char *created_time(time_t t)
{
	struct tm *tm;
	char *timestr = malloc(sizeof(char) * 128);

	tm = localtime(&t);

	strftime(timestr, 128, "%Y-%m-%d %T", tm);

	return timestr;
}

void updated_at(time_t t)
{
	struct tm *tm;
	char timestr[100];


	tm = localtime(&t);

	strftime(timestr, sizeof(timestr), "%Y-%m-%d %T", tm);

	printf("%s\n", timestr);

}


char *updated_time(time_t t)
{
	struct tm *tm;
	
	char *timestr = malloc(sizeof(char) * 128);

	tm = localtime(&t);

	strftime(timestr, 128, "%Y-%m-%d %T", tm);

	return timestr;
}


void input_valid_string(char *in, size_t size, int (*validator)(char *))
{
	while(1) {
		printf("> ");
		get_string(in, size);
		
		if(validator(in) == 0) break;
		
		printf("Invalid input\n");
	}
}


int validate_name(char *str)
{
	//regular expression
	char *pattern = "^[a-zA-Z ]{2,31}$";
	char buf[1024];
	int err;

	regex_t rgx;

	if ((err = regcomp(&rgx, pattern, REG_EXTENDED)) != 0) {
		// regerror(err, &rgx, buf, sizeof(buf));
		// printf("%s\n", buf);
		return -1;
	}

	if (regexec(&rgx, str, 0, NULL, 0) == REG_NOMATCH) {
		return -1;
	}

	return 0;
}


int validate_phone(char *str) {
		//regular expression
		char *pattern = "^[1-9][0-9]{9}$";
		char buf[1024];
		int err;

		regex_t rgx;

		if ((err = regcomp(&rgx, pattern, REG_EXTENDED)) != 0) {
			// regerror(err, &rgx, buf, sizeof(buf));
			// printf("%s\n", buf);
			return -1;
		}

		if (regexec(&rgx, str, 0, NULL, 0) == REG_NOMATCH) {
			return -1;
		}

		return 0;
	}


	void input_amount(int *in, int (*validator)(char *)) {
		char amount[10];

		while(1) {
			printf("> ");
			get_string(amount, 10);
			
			if(validator(amount) == 0) {
				long ret = strtol(amount, NULL, 10);
				*in = (int) ret;
				break;
			}
		
			printf("Invalid input\n");
		}

	}

	int validate_amount(char *str) {
		//regular expression
		char *pattern = "^[0-9]{1,10}$";
		char buf[1024];
		int err;

		regex_t rgx;

		if ((err = regcomp(&rgx, pattern, REG_EXTENDED)) != 0) {
			 regerror(err, &rgx, buf, sizeof(buf));
			 printf("%s\n", buf);
			return -1;
		}

		if (regexec(&rgx, str, 0, NULL, 0) == REG_NOMATCH) {
			return -1;
		}

		return 0;
	}

	int validate_amount_int(int x)
	{
		if (x >= INT_MIN && x <= INT_MAX) {
			return 0;
		}

		return -1;
	}

	void title_case(char *str)
	{
		unispace_separate(str);
		str[0] = toupper(str[0]);
		for (int i = 1; str[i] != '\0'; ++i) {
			if (str[i] == ' ') {
				str[i + 1] = toupper(str[i + 1]);
			}
		}
	}

	void unispace_separate(char *str) 
	{
		int i = 0;

		char last = 'a';
		char res[strlen(str)];

		res[0] = '\0';

		while (str[i] == ' ') {
			i++;
		}

		while (str[i] != '\0') {
			char ch = str[i];
			if (ch != ' ') {
				strncat(res, &ch, 1);
			} else if(last != ' ') {
					strncat(res, &ch, 1);
			}

			last = ch;
			i++;
		}

		strcpy(str, res);

	}


	void input_pid(dhanda *app, int *pid, int (*validator) (char *))
	{
		char pd[10];
		struct party result = {};

		while(1) {
			printf("> ");
			get_string(pd, 10);
			
			if(validator(pd) == 0) {
				long ret = strtol(pd, NULL, 10);
				*pid = (int) ret;
				if(party_findbyid(app, *pid, &result) == 1)
					break;
				else
					printf("Party does not exist\n");
			}
		
			printf("Invalid input\n");
		}
	}

	int validate_pid(char *str) 
	{
		//regular expression
		char *pattern = "^[0-9]{1,10}$";
		char buf[1024];
		int err;

		regex_t rgx;

		if ((err = regcomp(&rgx, pattern, REG_EXTENDED)) != 0) {
			 regerror(err, &rgx, buf, sizeof(buf));
			 printf("%s\n", buf);
			return -1;
		}

		if (regexec(&rgx, str, 0, NULL, 0) == REG_NOMATCH) {
			return -1;
		}

		return 0;
	}


	int validate_pid_int(int pid) {
		if (pid < 0 || pid > INT_MAX) {
			return -1;
		}

		return 0;
	}

	void input_txn_type(int *type, int (*validator) (char *))
	{
		char t[10];

		while(1) {
			printf("> ");
			get_string(t, 10);
			
			if(validator(t) == 0) {
				long ret = strtol(t, NULL, 10);
				*type = (int) ret;
				break;
			}
		
			printf("Invalid input\n");
		}
	}

	int validate_type(char *str)
	{
		//regular expression
		char *pattern = "^[0-1]{1}$";
		char buf[1024];
		int err;

		regex_t rgx;

		if ((err = regcomp(&rgx, pattern, REG_EXTENDED)) != 0) {
			 regerror(err, &rgx, buf, sizeof(buf));
			 printf("%s\n", buf);
			 return -1;
		}

		if (regexec(&rgx, str, 0, NULL, 0) == REG_NOMATCH) {
			return -1;
		}	

		return 0;
	}


	int validate_type_int(int type) {
		if (type == 0 || type == 1) {
			return 0;
		}

		return -1;
	}


	int validate_desc(char *str)
	{
		char *pattern = "^[a-zA-Z ]{2,1024}$";
		char buf[1024];
		int err;

		regex_t rgx;

		if ((err = regcomp(&rgx, pattern, REG_EXTENDED)) != 0) {
			// regerror(err, &rgx, buf, sizeof(buf));
			// printf("%s\n", buf);
			return -1;
		}

		if (regexec(&rgx, str, 0, NULL, 0) == REG_NOMATCH) {
			return -1;
		}

		return 0;
	}


	int check_func_call(void *ptr, int ncols, char **values, char **fields)
	{
		*((int *) ptr) = 1;

		return SQLITE_OK;
	}


	time_t unix_time(char *timestr)
	{
		struct tm tm = {};

		strptime(timestr, "%Y-%m-%d %T", &tm);

		time_t t = mktime(&tm);
		
		return t;
	}


