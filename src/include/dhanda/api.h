#include <kore/kore.h>
#include <kore/http.h>

int api_party_add(struct http_request *req);
int api_party_get(struct http_request *req);
struct kore_json_item *party_struct_to_korejson(struct party *p);
struct kore_json_item *party_list_to_korejson(struct list *parties);


int api_txn_add(struct http_request *req);
int api_txn_get(struct http_request *req);
struct kore_json_item *txn_struct_to_korejson(struct txn *t);
struct kore_json_item *txn_list_to_korejson(struct list *transactions);