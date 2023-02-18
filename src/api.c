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

	http_response(req, 200, "", 0);


cleanup:
	kore_json_cleanup(&json);

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

	http_response(req, 200, "", 0);


cleanup:
	kore_json_cleanup(&json);

	return KORE_RESULT_OK;
}

#endif

