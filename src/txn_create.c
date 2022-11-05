#include<dhanda/dhanda.h>
#include<dhanda/txn.h>

int txn_add(dhanda *app, txn *txn)
{
	struct txn temp;
	int init_posn, fin_posn, txn_id;
	debug_print("");

	fseek(app->txn_fp, 0, SEEK_END);
	init_posn = ftell(app->txn_fp);
	if (init_posn) {
		fseek(app->txn_fp, -sizeof(*txn), SEEK_END);
		fread(&temp, sizeof(*txn), 1, app->txn_fp);
		txn_id = temp.id;
		txn_id++;
	} else {
		txn_id = 1;
	}

	txn->id = txn_id;

	init_posn = ftell(app->txn_fp);
	fwrite(txn, sizeof(*txn), 1, app->txn_fp);
	fin_posn = ftell(app->txn_fp);




	if (init_posn < fin_posn)
		return 0;
	else {
		app_error_set(app, "Failed to create transaction");
		return -1;
	}
}
