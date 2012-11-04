#include <stdio.h>
#include "libipriv.h"

int eng = IPRIV_ENGINE_RSAREF;

int main(int argc, char *argv[]) {

	int rc;
	IPRIV_KEY key;
	char temp[1024];

	if (argc < 3) {
		printf("-1\nWrong input parameters\n");
		return -1;
	}

	Crypt_Initialize();

	rc = Crypt_OpenSecretKeyFromFile(eng, argv[2], argv[3], &key);

	if (rc < 0) {
		if (rc == CRYPT_ERR_INVALID_KEY) {
			printf("%d\nКлюч не может быть использован\n", rc);
			return rc;
		}
		if (rc == CRYPT_ERR_FILE_NOT_FOUND) {
			printf("%d\nФайл закрытого ключа не найден (%s)\n", rc, argv[2]);
			return rc;
		}
		if (rc == CRYPT_ERR_INVALID_PASSWD) {
			printf("%d\nНеверная кодовая фраза закрытого ключа\n", rc);
			return rc;
		}
		printf("%d\nError code %d\n", rc, rc);
		return rc;
	}

	rc = Crypt_Sign(argv[1], -1, temp, sizeof(temp), &key);
	printf("0\n%s", temp);
	Crypt_Done();

	return 0;
}