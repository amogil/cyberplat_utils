#include <stdio.h>
#include "libipriv.h"

int eng=IPRIV_ENGINE_RSAREF;

int main(int argc, char *argv[]) {

	int rc;
	IPRIV_KEY pub;
	IPRIV_KEY pub_verify;
	char temp[1024];

	if (argc < 3) {
		printf("-1\nWrong input parameters\n");
		return -1;
	}

	Crypt_Initialize();

	rc = Crypt_OpenPublicKeyFromFile(eng, argv[2], argv[3], &pub, 0);

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

	rc = Crypt_OpenPublicKeyFromFile(eng, argv[2], argv[3], &pub, &pub_verify);

	rc = Crypt_Verify(argv[1], -1, 0, 0, &pub_verify);

	printf("%d\n", rc);

	Crypt_Done();

	return 0;

}