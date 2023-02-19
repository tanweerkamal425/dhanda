#ifndef TERMINAL_APP

#include <kore/kore.h>
#include <kore/http.h>

#include <dhanda/dhanda.h>
#include <dhanda/party.h>
#include <dhanda/txn.h>
#include <dhanda/api.h>

#include <kore/seccomp.h>

KORE_SECCOMP_FILTER("app",
    KORE_SYSCALL_ALLOW(newfstatat), KORE_SYSCALL_ALLOW(fsync)
)


static dhanda app = {};

void
init_app(void)
{
	dhanda_init_app(&app);
}



int
api_party_add(struct http_request *req)
{
	struct kore_json json;
	struct kore_json_item *item;
	struct party p = {};

	kore_json_init(&json, req->http_body->data, req->http_body->length);

	if (!kore_json_parse(&json)) {
		http_response(req, 400, NULL, 0);
		goto cleanup;
	}

	item = kore_json_find_string(json.root, "first_name");
	strcpy(p.fname, item->data.string);

	item = kore_json_find_string(json.root, "last_name");
	strcpy(p.lname, item->data.string);

	item = kore_json_find_string(json.root, "phone");
	strcpy(p.phone, item->data.string);

	item = kore_json_find_integer(json.root, "amount");
	p.amount = (int) item->data.u64;

	time(&p.cat);
	time(&p.uat);

	party_add(&app, &p);

	struct kore_json res_json;
	struct kore_buf buf;
	party_struct_to_korejson(&p, &res_json);


	kore_buf_init(&buf, 512);
	kore_json_item_tobuf(res_json.root, &buf);

	http_response(req, 201, buf.data, buf.offset);




cleanup:
	kore_json_cleanup(&json);
	kore_json_item_free(res_json.root);

	return KORE_RESULT_OK;
}


int
api_txn_add(struct http_request *req)
{
	struct kore_json json;
	struct kore_json_item *item;
	struct txn t = {};

	kore_json_init(&json, req->http_body->data, req->http_body->length);

	if (!kore_json_parse(&json)) {
		http_response(req, 400, NULL, 0);
		goto cleanup;
	}

	item = kore_json_find_integer(json.root, "party_id");
	t.party_id = (int) item->data.u64;

	item = kore_json_find_integer(json.root, "amount");
	t.amount = (int) item->data.u64;

	item = kore_json_find_integer(json.root, "type");
	t.type = (int) item->data.u64;

	item = kore_json_find_string(json.root, "desc");
	strcpy(t.desc, item->data.string);

	time(&t.cat);

	txn_add(&app, &t);

	http_response(req, 200, "success", 0);


cleanup:
	kore_json_cleanup(&json);

	return KORE_RESULT_OK;
}


void party_struct_to_korejson(struct party *p, struct kore_json *json)
{
	struct kore_json_item *item;
	json->root = kore_json_create_object(NULL, NULL);

	item = kore_json_create_integer(json->root, "id", p->id);
	item = kore_json_create_string(json->root, "first_name", p->fname);
	item = kore_json_create_string(json->root, "last_name", p->lname);
	item = kore_json_create_string(json->root, "phone", p->phone);
	item = kore_json_create_integer(json->root, "amount", p->amount);
	item = kore_json_create_integer_u64(json->root, "cat", p->cat);
	item = kore_json_create_integer_u64(json->root, "uat", p->uat);


}

#endif

