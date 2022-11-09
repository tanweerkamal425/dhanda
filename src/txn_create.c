#include<dhanda/dhanda.h>
#include<dhanda/txn.h>

int txn_add(dhanda *app, txn *txn)
{
	struct txn temp;
	int init_posn, fin_posn, txn_id, ret;
	debug_print("");

	fseek(app->txn_fp, 0, SEEK_END);
	if (ftell(app->txn_fp)) {
		fseek(app->txn_fp, -sizeof(*txn), SEEK_END);
		ret = fread(&temp, sizeof(*txn), 1, app->txn_fp);
		if (ret != 1) {
			app_error_set(app, strerror(errno));
			return -1;
		}
		txn_id = temp.id;
		txn_id++;
	} else {
		txn_id = 1;
	}

	txn->id = txn_id;

	init_posn = ftell(app->txn_fp);
	ret = fwrite(txn, sizeof(*txn), 1, app->txn_fp);
	if (ret != 1) {
		app_error_set(app, strerror(errno));
		return -1;
	}

	app_success_set(app, "Transaction added successfully");
	return 0;
}
