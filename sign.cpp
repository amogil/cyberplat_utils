#include <stdio.h>
#include "libipriv.h"

int eng=IPRIV_ENGINE_RSAREF;

int main(int argc, char *argv[]) {

	int rc;
	IPRIV_KEY key;
	char temp[1024];

	if (argc < 3) {
		printf("-1\n");
		printf("Wrong input parameters\n");
		return -1;
	}

	Crypt_Initialize();

	rc = Crypt_OpenSecretKeyFromFile(eng, argv[2], argv[3], &key);

	if (rc < 0) {
		if (rc == CRYPT_ERR_INVALID_KEY) {
			printf("%d\n", rc);
			printf("Ключ не может быть использован\n");
			return rc;
		}
		if (rc == CRYPT_ERR_FILE_NOT_FOUND) {
			printf("%d\n", rc);
			printf("Файл закрытого ключа не найден (%s)\n", argv[2]);
			return rc;
		}
		if (rc == CRYPT_ERR_INVALID_PASSWD) {
			printf("%d\n", rc);
			printf("Неверная кодовая фраза закрытого ключа\n");
			return rc;
		}
		printf("%d\n", rc);
		printf("Error code %d\n", rc);
		return rc;
	}

	rc = Crypt_Sign(argv[1], -1, temp, sizeof(temp), &key);
	printf("0\n");
	printf("%s", temp);
	Crypt_Done();

	return 0;
}