#include <kore/kore.h>
#include <kore/http.h>

int api_party_add(struct http_request *req);
int api_txn_add(struct http_request *req);
void party_struct_to_korejson(struct party *p, struct kore_json *json);