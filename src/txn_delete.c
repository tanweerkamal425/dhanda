#include <dhanda/dhanda.h>
#include <dhanda/party.h>
#include <dhanda/txn.h>
#include <unistd.h>

int txn_delete(struct dhanda *app, int pid)
{
	struct txn temp;
	int matched = -1;
	int trunc_size, count = 0;


	while (fread(&temp, sizeof(temp), 1, app->txn_fp) > 0) {
		count++;
	}

	fseek(app->txn_fp, 0, SEEK_SET);
	while (fread(&temp, sizeof(temp), 1, app->txn_fp) > 0) {
		if (temp.party_id == pid) {
			fseek(app->txn_fp, -sizeof(temp), SEEK_CUR);
			int ret = ftell(app->txn_fp);
			fseek(app->txn_fp, sizeof(temp), SEEK_CUR);
			while (fread(&temp, sizeof(temp), 1, app->txn_fp) > 0) {
				fseek(app->txn_fp, 2 * -sizeof(temp), SEEK_CUR);
				fwrite(&temp, sizeof(temp), 1, app->txn_fp);
				fseek(app->txn_fp, sizeof(temp), SEEK_CUR);
			}

			trunc_size = sizeof(temp) * count - sizeof(temp);
			if(ftruncate(fileno(app->txn_fp), trunc_size) != 0) {
				app_error_set(app, strerror(errno));
				count--;
				return -1;
			}

			fseek(app->txn_fp, ret, SEEK_SET);
		}
	}

	if (ftell(app->txn_fp) == 0) {
		return 0;
	} else {
		ftruncate(fileno(app->txn_fp), 0);
		return -1;
	}

	

}