#include <kore/kore.h>
#include <kore/http.h>

int api_party_add(struct http_request *req);
int api_party_get(struct http_request *req);
int api_party_show(struct http_request *req);
int api_party_update(struct http_request *req);
int api_party_delete(struct http_request *req);
struct kore_json_item *party_struct_to_korejson(struct party *p);
struct kore_json_item *party_list_to_korejson(struct list *parties);


int api_txn_add(struct http_request *req);
int api_txn_get(struct http_request *req);
int api_txn_show(struct http_request *req);
struct kore_json_item *txn_struct_to_korejson(struct txn *t);
struct kore_json_item *txn_list_to_korejson(struct list *transactions);
struct kore_json_item *year_stat_list_to_korejson(struct list *year_stat);
struct kore_json_item *year_stat_struct_to_korejson(struct year_stat *year_stat);

int api_stat_get(struct http_request *req);
