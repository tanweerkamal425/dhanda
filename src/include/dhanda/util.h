#ifndef _DHANDA_UTIL_H_
#define _DHANDA_UTIL_H_

#include <dhanda/dhanda.h>

#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_YELLOW   "\x1b[33m"
#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_MAGENTA  "\x1b[35m"
#define ANSI_COLOR_CYAN     "\x1b[36m"
#define ANSI_COLOR_WHITE    "\x1b[37m"
#define ANSI_RESET          "\x1b[0m"

#define ANSI_BG_RED         "\x1b[41m"
#define ANSI_BG_GREEN       "\x1b[42m"
#define ANSI_BG_YELLOW      "\x1b[43m"

#define ANSI_BLINK          "\x1b[5m"
#define ANSI_BOLD           "\x1b[1m"

#define start_cmdline_color() printf(ANSI_BOLD ANSI_COLOR_CYAN);
#define end_cmdline_color()   printf(ANSI_RESET); fflush(stdout);

#if defined(DEBUG)
#define debug_print(fmt) fprintf(stderr, "%s:%s:%d: %s\n", __FILE__, __func__, __LINE__, fmt);
#else
#define debug_print(fmt)
#endif

int get_line(char line[], int size);
int get_string(char line[], int size);
void sky();
void red();
void yellow();
void yellow_fg();
void magenta_fg();
void blue_fg();
void reset ();
void grey();
void bold();
void warning();
void error();
void success();
void print_success(char *s);
void print_error(char *s);
void print_warning(char *s);
void confirmation();

void centreprint(char *s);

int validate_name(char *str);
int validate_phone(char *str);
int validate_amount(char *str);
int validate_amount_int(int x);
int validate_desc(char *str);
void input_valid_string(char *in, size_t size, int (*validator)(char *));
void input_amount(int *in, int (*validator)(char *));
void title_case(char *str);
void unispace_separate(char *str); 


void input_pid(dhanda *app, int *pid, int (*validator) (char *));
int validate_pid(char *str);
int validate_pid_int(int pid);
void input_txn_type(int *type, int (*validator) (char *));
int validate_type(char *str);
int validate_type_int(int type);
int check_func_call(void *ptr, int ncols, char **values, char **fields);
char *created_time(time_t t);
char *updated_time(time_t t);
int put_in_party_struct(void *ptr, int ncols, char **values, char **fields);
int put_in_txn_struct(void *ptr, int ncols, char **values, char **fields);
int put_in_txn_list(void *ptr, int ncols, char **values, char **fields);
time_t unix_time(char *timestr);




void created_at(time_t t);
void updated_at(time_t t);

#endif
