#ifndef _DHANDA_PARTY_H_
#define _DHANDA_PARTY_H_

#include <dhanda/dhanda.h>

typedef struct party {
	int id;
	char fname[32];
	char lname[32];
	char phone[12];
	int amount;
	time_t cat;
	time_t uat;
	int deletion_confirmed;
} party;

typedef struct party_stat {
	int party_count;
} party_stat;

typedef struct party_filter {
	int page;
	int items;
	char *query;
	int has_query;
} party_filter;


int party_init(dhanda *app);
int party_add(dhanda *app, party *party);
int party_update(dhanda *app, party *old_party, struct party *new_party);
int party_delete(dhanda *app, party *party);
int party_findbyid(dhanda *app, int id, party *result);
int party_search(dhanda *app, char *query, struct list *result);
int party_get(dhanda *app, party_filter filter, struct list *result);
int put_in_party_list(void *ptr, int ncols, char **values, char **fields);
int put_in_party_struct(void *ptr, int ncols, char **values, char **fields);
int party_update_amount(struct dhanda *app, int pid, int val, int type);
int party_stat_get(dhanda *app, party_stat *stat);
int count_parties(void *ptr, int ncols, char **values, char **fields);

//int validate_phone(dhanda *app, char *str);

/* Handy functions for passing data from Data layer to UI layer, since
 * UI functions only takes one argument and are called using callback
 * there is no way to call a callback with different type/number of
 * argument at run time. */
void party_insert_in_list(dhanda *app, party *p);
party *party_first_in_list(dhanda *app);
party *party_second_in_list(dhanda *app);

#endif
