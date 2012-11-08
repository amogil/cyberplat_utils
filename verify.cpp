#include <stdio.h>
#include <stdlib.h>
#include "libipriv.h"

int engine = IPRIV_ENGINE_RSAREF;

int main(int argc, char *argv[]) {

	int rc;
	IPRIV_KEY ca;
	IPRIV_KEY pub;
	char temp[1024];

	if (argc < 3) {
		printf("-1\nWrong input parameters\n");
		return -1;
	}

	Crypt_Initialize();

	rc = Crypt_OpenPublicKeyFromFile(engine, argv[2], 0, &ca, 0);

	if (rc < 0) {
		if (rc == CRYPT_ERR_INVALID_KEY) {
			printf("%d\nКлюч не может быть использован\n", rc);
			return rc;
		}
		if (rc == CRYPT_ERR_FILE_NOT_FOUND) {
			printf("%d\nФайл открытого ключа не найден (%s)\n", rc, argv[2]);
			return rc;
		}

		printf("%d\nError code %d\n", rc, rc);
		return rc;
	}

	rc = Crypt_OpenPublicKeyFromFile(engine, argv[3], atoi(argv[4]), &pub, &ca);

	if (rc < 0) {
		if (rc == CRYPT_ERR_ENG_NOT_READY) {
			printf("%d\nКриптосредство не готово\n", rc);
			return rc;
		}
		if (rc == CRYPT_ERR_FILE_NOT_FOUND) {
			printf("%d\nФайл не найден (%s)\n", rc, argv[3]);
			return rc;
		}
		printf("%d\nError code %d\n", rc, rc);
		return rc;
	}

	rc = Crypt_Verify(argv[1], -1, 0, 0, &pub);

	if (rc < 0) {
		if (rc == CRYPT_ERR_VERIFY) {
			printf("%d\nПодпись не соответствует содержимому документа\n", rc);
			return rc;
		}
		printf("%d\nError code %d\n", rc, rc);
		return rc;
	}

	printf("%d\n", rc);

	Crypt_Done();

	return rc;

}