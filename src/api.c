#ifndef TERMINAL_APP

#include <kore/kore.h>
#include <kore/http.h>

#include <dhanda/dhanda.h>
#include <dhanda/party.h>
#include <dhanda/txn.h>
#include <dhanda/api.h>
#include <dhanda/kore_util.h>

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

	struct kore_json_item *res_json;
	struct kore_buf buf;
	res_json = party_struct_to_korejson(&p);


	kore_buf_init(&buf, 512);
	kore_json_item_tobuf(res_json, &buf);

	http_response(req, 201, buf.data, buf.offset);




cleanup:
	kore_json_cleanup(&json);
	kore_json_item_free(res_json);

	return KORE_RESULT_OK;
}


int
api_party_get(struct http_request *req)
{
	int ret, page, items;
	struct list *result;
	party_filter filter = {};
	struct kore_json json = {};
	struct kore_buf buf;
	char *ptr;
	int err = 0;

	http_populate_get(req);

	ret = http_argument_get_uint32(req, "page", &page);
	if (!ret) page = 1;

	ret = http_argument_get_uint32(req, "items", &items);
	if (!ret) items = 50;

	filter.page = page;
	filter.items = items;

	result = list_create(sizeof(struct party));
	party_get(&app, filter, result);
	json.root = party_list_to_korejson(result);

	kore_buf_init(&buf, 512);
	kore_json_item_tobuf(json.root, &buf);

	http_response_header(req, "content-type", "application/json");
	http_response(req, 200, buf.data, buf.offset);

	return KORE_RESULT_OK;

}


int
api_party_show(struct http_request *req)
{
	struct kore_json json;
	struct kore_json_item *item;
	struct party result = {};
	int id;

	http_populate_get(req);

	kore_apputil_extract_route_ids(req->path, &id);
	
	if (party_findbyid(&app, id, &result) != 1) {
		http_response(req, 400, NULL, 0);
		return KORE_RESULT_ERROR;
	}


	struct kore_json_item *res_json;
	struct kore_buf buf;
	res_json = party_struct_to_korejson(&result);

	kore_buf_init(&buf, 512);
	kore_json_item_tobuf(res_json, &buf);

	http_response(req, 200, buf.data, buf.offset);


	return KORE_RESULT_OK;

}



int
api_party_update(struct http_request *req)
{
	struct kore_json json;
	struct kore_json_item *item;
	struct party result = {};
	struct party p = {};
	int id;


	kore_json_init(&json, req->http_body->data, req->http_body->length);

	if (!kore_json_parse(&json)) {
		http_response(req, 400, NULL, 0);
		goto cleanup;
	}

	kore_apputil_extract_route_ids(req->path, &id);
	if (party_findbyid(&app, id, &result) != 1) {
		http_response(req, 400, NULL, 0);
		return KORE_RESULT_ERROR;
	}

	p.id = id;
	item = kore_json_find_string(json.root, "first_name");
	strcpy(p.fname, item->data.string);
	item = kore_json_find_string(json.root, "last_name");
	strcpy(p.lname, item->data.string);
	item = kore_json_find_string(json.root, "phone");
	strcpy(p.phone, item->data.string);
	item = kore_json_find_integer(json.root, "amount");
	p.amount = (int) item->data.u64;

	p.cat = result.cat;
	time(&p.uat);
	party_update(&app, NULL, &p);


	struct kore_json_item *res_json;
	struct kore_buf buf;
	res_json = party_struct_to_korejson(&p);

	kore_buf_init(&buf, 512);
	kore_json_item_tobuf(res_json, &buf);

	http_response(req, 200, buf.data, buf.offset);

cleanup:
	kore_json_cleanup(&json);
	kore_json_item_free(res_json);

	return KORE_RESULT_OK;
}



int
api_party_delete(struct http_request *req)
{
	struct party result = {};
	struct kore_json json;
	struct kore_json_item *item;
	int id;

	http_populate_get(req);

	kore_apputil_extract_route_ids(req->path, &id);
	
	if (party_findbyid(&app, id, &result) != 1) {
		http_response(req, 400, NULL, 0);
		return KORE_RESULT_ERROR;
	}

	txn_delete(&app, result.id);
	party_delete(&app, &result);

	// struct kore_json_item *res_json;
	// struct kore_buf buf;

	// res_json = party_struct_to_korejson(&result);

	// kore_buf_init(&buf, 512);
	// kore_json_item_tobuf(res_json, &buf);

	http_response(req, 200, NULL, 0);

	return KORE_RESULT_OK;
}


struct kore_json_item *
party_list_to_korejson(struct list *parties)
{
	Node *ptr;
	struct party *party_ptr;
	struct kore_json_item *root, *item, *array;

	root = kore_json_create_object(NULL, NULL);

	array = kore_json_create_array(root, "parties");

	ptr = parties->head;

	while (ptr) {
		party_ptr = (struct party *) ptr->data;
		item = party_struct_to_korejson(party_ptr);
		kore_json_item_attach(array, item);

		ptr = ptr->next;
	}

	return root;
	
}


struct kore_json_item *
party_struct_to_korejson(struct party *p)
{
	struct kore_json_item *result, *item;
	
	result = kore_json_create_object(NULL, NULL);

	item = kore_json_create_integer(result, "id", p->id);
	item = kore_json_create_string(result, "first_name", p->fname);
	item = kore_json_create_string(result, "last_name", p->lname);
	item = kore_json_create_string(result, "phone", p->phone);
	item = kore_json_create_integer(result, "amount", p->amount);
	item = kore_json_create_integer_u64(result, "cat", p->cat);
	item = kore_json_create_integer_u64(result, "uat", p->uat);

	return result;
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

	struct kore_json_item *res_json;
	struct kore_buf buf;
	res_json = txn_struct_to_korejson(&t);

	kore_buf_init(&buf, 512);
	kore_json_item_tobuf(res_json, &buf);

	http_response(req, 201, buf.data, buf.offset);


cleanup:
	kore_json_cleanup(&json);
	kore_json_item_free(json.root);

	return KORE_RESULT_OK;
}


int
api_txn_get(struct http_request *req)
{
	int ret, page, items;
	struct list *result;
	txn_filter filter = {};
	struct kore_json json = {};
	struct kore_buf buf;
	char *ptr;
	int err = 0;

	http_populate_get(req);

	ret = http_argument_get_uint32(req, "page", &page);
	if (!ret) page = 1;

	ret = http_argument_get_uint32(req, "items", &items);
	if (!ret) items = 50;

	filter.page = page;
	filter.items = items;

	result = list_create(sizeof(struct txn));
	txn_get(&app, filter, result);
	json.root = txn_list_to_korejson(result);

	kore_buf_init(&buf, 512);
	kore_json_item_tobuf(json.root, &buf);

	http_response_header(req, "content-type", "application/json");
	http_response(req, 200, buf.data, buf.offset);

	return KORE_RESULT_OK;
}


struct kore_json_item *
txn_list_to_korejson(struct list *transactions)
{
	Node *ptr;
	struct txn *txn_ptr;
	struct kore_json_item *root, *item, *array;

	root = kore_json_create_object(NULL, NULL);

	array = kore_json_create_array(root, "transactions");

	ptr = transactions->head;

	while (ptr) {
		txn_ptr = (struct txn *) ptr->data;
		item = txn_struct_to_korejson(txn_ptr);
		kore_json_item_attach(array, item);

		ptr = ptr->next;
	}

	return root;
}



struct kore_json_item *
txn_struct_to_korejson(struct txn *t)
{
	struct kore_json_item *result, *item;
	
	result = kore_json_create_object(NULL, NULL);

	item = kore_json_create_integer(result, "party_id", t->party_id);
	item = kore_json_create_integer(result, "amount", t->amount);
	item = kore_json_create_integer(result, "type", t->type);
	item = kore_json_create_string(result, "desc", t->desc);

	return result;
}

#endif

