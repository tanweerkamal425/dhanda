#ifndef TERMINAL_APP

#include <dhanda/kore_util.h>
#include <dhanda/dhanda.h>


int
kore_apputil_extract_route_ids(const char *path, ...)
{
	va_list arg;
	size_t *id;
	int ret, err;
	char *parts[16];
	char *route = kore_strdup(path);
	char *part;

	ret = 0;
	va_start(arg, path);
	kore_split_string(route, "/", parts, sizeof(parts) / sizeof(parts[0]));
	for (int i = 0; parts[i] != NULL; ++i) {
		part = parts[i];
		while (*part) {
			if (!isdigit(*part)) break;
			++part;
		}
		/* If part has left something then it's not a number, skip it */
		if (*part) continue;
		id = va_arg(arg, size_t *);
		*id = kore_strtonum64(parts[i], 0, &err);
		if (err == KORE_RESULT_ERROR) {
			ret = -1;
			break;
		}
	}

	va_end(arg);
	kore_free(route);

	return ret;
}


int
util_http_json_error_response(struct http_request *req, struct kore_json_item *item, const char *field, int (*validator)(char *))
{
	int ret;
	struct kore_json_item *err_item;
	struct kore_buf buf;
	char msg[1024];

	if (item) {
		if (item->type == KORE_JSON_TYPE_STRING) {
			ret = validator(item->data.string);
		} else if (item->type == KORE_JSON_TYPE_INTEGER) {
			ret = validator((int) item->data.u64);
		}

		if (ret == 0) {
			return 0;
		}
	}

	ret = -1;
	if (item == NULL) {
		sprintf(msg, "%s is required", field);
	} else {
		sprintf(msg, "%s is invalid", field);
	}

	err_item = kore_json_create_object(NULL, NULL);

	kore_json_create_string(err_item, "msg", msg);

	kore_buf_init(&buf, 128);
	kore_json_item_tobuf(err_item, &buf);

	http_response_header(req, "content-type", "application/json");
	http_response(req, 400, buf.data, buf.offset);

	kore_buf_cleanup(&buf);
	kore_json_item_free(err_item);

	return ret;
}

int
util_http_response_msg(struct http_request *req, char *str)
{
	int ret;
	char msg[1024];
	struct kore_json_item *err_item;
	struct kore_buf buf;


	sprintf(msg, "error: %s", str);

	err_item = kore_json_create_object(NULL, NULL);

	kore_json_create_string(err_item, "msg", msg);

	kore_buf_init(&buf, 128);
	kore_json_item_tobuf(err_item, &buf);

	http_response_header(req, "content-type", "application/json");
	http_response(req, 400, buf.data, buf.offset);

	kore_buf_cleanup(&buf);
	kore_json_item_free(err_item);

	return 0;

}


#endif