#include <dhanda/kore_util.h>


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
