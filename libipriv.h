/*
   CopyRight (C) 1998-2005 CyberPlat.Com. All Rights Reserved.
   e-mail: support@cyberplat.com
*/


#ifndef __LIBIPRIV_H
#define __LIBIPRIV_H

// ���� ������
#define CRYPT_ERR_BAD_ARGS		-1	// ������ � ����������
#define CRYPT_ERR_OUT_OF_MEMORY		-2	// ������ ��������� ������
#define	CRYPT_ERR_INVALID_FORMAT	-3	// �������� ������ ���������
#define CRYPT_ERR_NO_DATA_FOUND		-4	// �������� �������� �� �� �����
#define CRYPT_ERR_INVALID_PACKET_FORMAT	-5	// ������ �� ���������� ��������� ���������
#define CRYPT_ERR_UNKNOWN_ALG		-6	// ����������� �������� ����������
#define CRYPT_ERR_INVALID_KEYLEN	-7	// ����� ����� �� ������������� ����� �������
#define CRYPT_ERR_INVALID_PASSWD	-8	// �������� ������� ����� ��������� �����
#define CRYPT_ERR_DOCTYPE		-9	// �������� ��� ���������
#define CRYPT_ERR_RADIX_DECODE		-10	// ������ ASCII ����������� ���������
#define CRYPT_ERR_RADIX_ENCODE		-11	// ������ ASCII ������������� ���������
#define CRYPT_ERR_INVALID_ENG		-12	// ����������� ��� ��������������
#define CRYPT_ERR_ENG_NOT_READY		-13	// �������������� �� ������
#define CRYPT_ERR_NOT_SUPPORT		-14	// ����� �� �������������� ���������������
#define CRYPT_ERR_FILE_NOT_FOUND	-15	// ���� �� ������
#define CRYPT_ERR_CANT_READ_FILE	-16	// ������ ������ �����
#define CRYPT_ERR_INVALID_KEY		-17	// ���� �� ����� ���� �����������
#define CRYPT_ERR_SEC_ENC		-18	// ������ ������������ �������
#define CRYPT_ERR_PUB_KEY_NOT_FOUND	-19	// �������� ���� � ����� �������� ������� �����������
#define CRYPT_ERR_VERIFY		-20	// ������� �� ������������� ����������� ���������
#define CRYPT_ERR_CREATE_FILE		-21	// ������ �������� �����
#define CRYPT_ERR_CANT_WRITE_FILE	-22	// ������ ������ � ����
#define CRYPT_ERR_INVALID_KEYCARD	-23	// �������� ������ �������� �����
#define CRYPT_ERR_GENKEY		-24	// ������ ��������� ������
#define CRYPT_ERR_PUB_ENC		-25	// ������ ����������
#define CRYPT_ERR_SEC_DEC		-26	// ������ ����������

// ���� �������������
#define IPRIV_ENGINE_RSAREF		0	// ���������� RSAREF
#define IPRIV_ENGINE_OPENSSL		1	// ���������� OpenSSL
#define IPRIV_ENGINE_PKCS11		2	// ��������� PKCS11 (������� ������ eToken)
#define IPRIV_ENGINE_WINCRYPT		3	// ��������� Microsoft Windows CryptoAPI

#define IPRIV_ENGINE_DEFAULT		IPRIV_ENGINE_RSAREF
#define IPRIV_DEFAULT_ENGINE		IPRIV_ENGINE_DEFAULT

// ������������ ���������� �������������� �������������
#define IPRIV_MAX_ENG_NUM		4

// ���� �������� � ��������������� (������������ ��� ������ Crypt_Ctrl)
#define IPRIV_ENGCMD_IS_READY			0	// in: none, retval: 1-ready, 0 - not ready
#define IPRIV_ENGCMD_GET_ERROR			1	// in: none, retval: errcode
#define IPRIV_ENGCMD_SET_PIN			2	// in: const char* null-terminated pin code, retval: 0-success
#define IPRIV_ENGCMD_SET_PKCS11_LIB		3	// in: static const char* null-terminated path to library, retval: 0-success
#define IPRIV_ENGCMD_GET_PKCS11_SLOTS_NUM	4	// in: none, retval - slots num or 0
#define IPRIV_ENGCMD_GET_PKCS11_SLOT_NAME	5	// in: int slot index, char* dst, int ndst, retval - string length
#define IPRIV_ENGCMD_SET_PKCS11_SLOT		6	// in: int slot index (from 0), retval - 0-success
#define IPRIV_ENGCMD_ENUM_PKCS11_KEYS		7	// in: IPRIV_KEY* array, int array max size, retval - keys num
#define IPRIV_ENGCMD_ENUM_PKCS11_PUBKEYS	8	// in: IPRIV_KEY* array, int array max size, retval - keys num

// ���� ������
#define IPRIV_KEY_TYPE_RSA_SECRET	1
#define IPRIV_KEY_TYPE_RSA_PUBLIC	2

// ������������ ����� ���� ����������
#define MAX_USERID_LENGTH		20


#ifdef _WIN32
#define	IPRIVAPI	__stdcall
#else
#define	IPRIVAPI
#endif


// ��������� �����
typedef struct
{
	short eng;				// ��� ��������������
	short type;				// ��� �����
	unsigned long keyserial;		// �������� ����� �����
	char userid[24];			// ��� ���������� (������� MAX_USERID_LENGTH+1)
	void* key;				// ������������� ��� �������������� ������
}IPRIV_KEY;

/*
����� ����� ��������� IPRIV_KEY: 36 ����
�������� ��������� ��������� ������������ ������ � ������:
IPRIV_KEY::eng:		0
IPRIV_KEY::type:	2
IPRIV_KEY::keyserial:	4
IPRIV_KEY::userid:	8
IPRIV_KEY::key:		32
*/



// ************************
// ��������� ����������   *
// ************************

// �������� ������������� �������� �� ������� ������
#define CRYPT_IS_ERROR(RC)	(rc<0?1:0)
#define CRYPT_IS_SUCCESS(RC)	(rc>=0?1:0)

#ifdef __cplusplus
extern "C" {
#endif


// ������������� ����������.
// ������ ����������� ������ ���� ��� ��� ������� ���������� (� �������� ������).
// ����������: 0 - ����� ��� ��� ������
int IPRIVAPI Crypt_Initialize(void);


// ������������ ������ � ����������������.
// ���������� ��� ��������� � ������������� �������� ����������������.
// ��������, ��������� ���-���� ��� ������� � ������������ ����� eToken.
// eng: �������, ��� ����������������
// cmd: �������, ��� �������
// ����������: ������� �� ���� �������
int Crypt_Ctrl(int eng,int cmd,...);
int IPRIVAPI Crypt_Ctrl_Null(int eng,int cmd);
int IPRIVAPI Crypt_Ctrl_String(int eng,int cmd,const char* arg);
int IPRIVAPI Crypt_Ctrl_Int(int eng,int cmd,int arg);
int IPRIVAPI Crypt_Ctrl_Ptr(int eng,int cmd,void* arg);

// ������������ �������� ����� � ������ (Crypt_GenKeyCard) ��� � ����� (Crypt_GenKeyCardToFile).
// dst: ��������, ����� ��� ������ ���� �������� �����
// ndst: �������, ������������ ����� ��������� ������
// path: �������, ���� � ����� ��� �������� �����
// userid: �������, ��� ����������
// keyserial: �������, �������� ����� �����
// ����������: ����� ���� �������� ��� ��� ������
int IPRIVAPI Crypt_GenKeyCard(char* dst,int ndst,const char* userid,unsigned long keyserial);
int IPRIVAPI Crypt_GenKeyCardToFile(const char* path,const char* userid,unsigned long keyserial);

// ������ �������� �����
// path: �������, ���� � ����� ��� �������� �����
// keyserial: ��������, �������� ����� �����
// userid: ��������, ��� ����������
// ����������: 0 - ����� ��� ��� ������
int IPRIVAPI Crypt_ReadKeyCardFromFile(const char* path,unsigned long* keyserial,char* userid);

// ��������� ���� ������ (��������/��������) �� ������ �������� �����.
// eng: �������, ��� ����������������
// src: �������, ����� � ����� �������� �����
// nsrc: �������, ����� ������, -1 - ��������� ���� (������ ���� ����-����������)
// keycardpath: �������, ���� � ����� � ��������� �����
// sec: ��������, �������� ����
// pub: ��������, �������� ����
// bits: �������, ����� ����� � �����
// ����������: 0 - ����� ��� ��� ������
int IPRIVAPI Crypt_GenKey(int eng,const char* src,int nsrc,IPRIV_KEY* sec,IPRIV_KEY* pub,int bits);
int IPRIVAPI Crypt_GenKeyFromFile(int eng,const char* keycardpath,IPRIV_KEY* sec,IPRIV_KEY* pub,int bits);
int IPRIVAPI Crypt_GenKey2(int eng,unsigned long keyserial,const char* userid,IPRIV_KEY* sec,IPRIV_KEY* pub,int bits);

// �������� ��������� ����� �� ������ � ������ (Crypt_OpenSecretKey), �� ����� (Crypt_OpenSecretKeyFromFile)
// ��� �� ����������� ��������� ���������������� (Crypt_OpenSecretKeyFromStore). Crypt_OpenSecretKey2 ������ ����
// �� ������ ��� ���������� (������ ���� ����� � base64).
// eng: �������, ��� ����������������
// src: �������, ����� � ����� ��������� �����
// nsrc: �������, ����� ������, -1 - ��������� ���� (������ ���� ����-����������)
// path: �������, ���� � ����� � �������� ������
// passwd: �������, ������� ����� ��� ����������� ��������� �����
// keyserial: �������, �������� ����� ��������� �����
// key: ��������, �������� ����
// ����������: 0 - ����� ��� ��� ������
int IPRIVAPI Crypt_OpenSecretKey(int eng,const char* src,int nsrc,const char* passwd,IPRIV_KEY* key);
int IPRIVAPI Crypt_OpenSecretKey2(int eng,const char* src,int nsrc,const char* passwd,IPRIV_KEY* key);
int IPRIVAPI Crypt_OpenSecretKeyFromFile(int eng,const char* path,const char* passwd,IPRIV_KEY* key);
int IPRIVAPI Crypt_OpenSecretKeyFromStore(int eng,unsigned long keyserial,IPRIV_KEY* key);

// �������� ��������� ����� �� ������ � ������ (Crypt_OpenPublicKey), �� ����� (Crypt_OpenPublicKeyFromFile)
// ��� �� ����������� ��������� ���������������� (Crypt_OpenPublicKeyFromStore). Crypt_OpenPublicKey2 ������ ����
// �� ������ ��� ���������� � ������� (������ ���� ����� � base64).
// eng: �������, ��� ����������������
// src: �������, ����� � ����� ��������� �����
// nsrc: �������, ����� ������, -1 - ��������� ���� (������ ���� ����-����������)
// path: �������, ���� � ����� � ��������� �������
// keyserial: �������, �������� ����� ��������� �����
// key: ��������, �������� ����
// cakey: �������, ����� ���� 0, �������� ���� ��� �������� ������� �����
// ����������: 0 - ����� ��� ��� ������
int IPRIVAPI Crypt_OpenPublicKey(int eng,const char* src,int nsrc,unsigned long keyserial,IPRIV_KEY* key,IPRIV_KEY* cakey);
int IPRIVAPI Crypt_OpenPublicKey2(int eng,const char* src,int nsrc,IPRIV_KEY* key);
int IPRIVAPI Crypt_OpenPublicKeyFromFile(int eng,const char* path,unsigned long keyserial,IPRIV_KEY* key,IPRIV_KEY* cakey);
int IPRIVAPI Crypt_OpenPublicKeyFromStore(int eng,unsigned long keyserial,IPRIV_KEY* key);

// ������� ��������� ����� (����� �� �������������� �����������������).
// dst: ��������, ����� ��� ������ ��������� �����
// ndst: �������, ������������ ����� ��������� ������
// path: �������, ���� � ����� ��� ��������� �����
// passwd: �������, ������� ����� ��� ���������� ��������� �����
// key: �������, �������� ����
// ����������: ����� ���� ����� ��� ��� ������
int IPRIVAPI Crypt_ExportSecretKey(char* dst,int ndst,const char* passwd,IPRIV_KEY* key);
int IPRIVAPI Crypt_ExportSecretKeyToFile(const char* path,const char* passwd,IPRIV_KEY* key);

// ������� ��������� �����.
// dst: ��������, ����� ��� ������ ��������� �����
// ndst: �������, ������������ ����� ��������� ������
// path: �������, ���� � ����� � ��������� �������
// key: �������, �������� ����
// cakey: �������, ����� ���� 0, �������� ���� ��� ������������ ������� ��������� �����
// ����������: ����� ���� ����� ��� ��� ������
int IPRIVAPI Crypt_ExportPublicKey(char* dst,int ndst,IPRIV_KEY* key,IPRIV_KEY* cakey);
int IPRIVAPI Crypt_ExportPublicKeyToFile(const char* path,IPRIV_KEY* key,IPRIV_KEY* cakey);

// ������ ��������� ����� �� ���������� ��������� ���������������� (����� �� ��������������).
// ��������, ������ ��������� ����� ���������� � ����������� ���� eToken.
// eng: �������, ��� ����������������
// src: �������, ����� � ����� ��������� �����
// nsrc: �������, ����� ������, -1 - ��������� ���� (������ ���� ����-����������)
// path: �������, ���� � ����� � �������� ������
// passwd: �������, ������� ����� ��� ����������� ��������� �����
// ����������: 0 - ����� ��� ��� ������
int IPRIVAPI Crypt_ImportSecretKey(int eng,const char* src,int nsrc,const char* passwd);
int IPRIVAPI Crypt_ImportSecretKeyFromFile(int eng,const char* path,const char* passwd);

// ������ ��������� ����� �� ���������� ��������� ���������������� (����� �� ��������������).
// ��������, ������ ��������� ����� ����� � ����������� ���� eToken.
// eng: �������, ��� ����������������
// src: �������, ����� � ����� ��������� �����
// nsrc: �������, ����� ������, -1 - ��������� ���� (������ ���� ����-����������)
// path: �������, ���� � ����� � ��������� �������
// keyserial: �������, �������� ����� ��������� �����
// cakey: �������, ����� ���� 0, �������� ���� ��� �������� ������� �����
// ����������: 0 - ����� ��� ��� ������
int IPRIVAPI Crypt_ImportPublicKey(int eng,const char* src,int nsrc,unsigned long keyserial,IPRIV_KEY* cakey);
int IPRIVAPI Crypt_ImportPublicKeyFromFile(int eng,const char* path,unsigned long keyserial,IPRIV_KEY* cakey);

// ������������ ������� ���������.
// src: �������, ����� � ����� ���������
// nsrc: ����� ���������, -1 - ��������� ���� (������ ���� ����-����������)
// dst: ��������, ����� ��� ������ ���� ������������ ���������
// ndst: �������, ������������ ����� ��������� ������
// key: �������, �������� ����
// ����������: ����� ���� ��������� ��� ��� ������
int IPRIVAPI Crypt_Sign(const char* src,int nsrc,char* dst,int ndst,IPRIV_KEY* key);

// �������� ������� ���������.
// src: �������, ����� � ����� ���������
// nsrc: ����� ���������, -1 - ��������� ���� (������ ���� ����-����������)
// pdst: ��������, ����� ���� 0, ����� ���������, � ������� ���������� ����� ������������� ��������� (�� �������)
// pndst: ��������, ����� ���� 0, ����� ����������, � ������� ���������� ����� ������������� ��������� (�� �������)
// key: �������, �������� ����
// ����������: 0 - ����� ��� ��� ������
int IPRIVAPI Crypt_Verify(const char* src,int nsrc,const char** pdst,int* pndst,IPRIV_KEY* key);

// ���������� �������� ������. ����� ��������� �� ������ ��������� ����� �����.
// src: �������, ����� � ����� ���������
// nsrc: ����� ���������, -1 - ��������� ���� (������ ���� ����-����������)
// dst: ��������, ����� ��� ������ �������������� ���������
// ndst: �������, ������������ ����� ��������� ������
// ����������: ����� �������������� ��������� ��� ��� ������
int IPRIVAPI Crypt_Encrypt(const char* src,int nsrc,char* dst,int ndst,IPRIV_KEY* key);

// ������������ �������� ������.
// src: �������, ����� � ������������� ����������
// nsrc: ����� �������������� ���������, -1 - ��������� ���� (������ ���� ����-����������)
// dst: ��������, ����� ��� ������ ���������
// ndst: �������, ������������ ����� ��������� ������
// ����������: ����� ��������� ��� ��� ������
int IPRIVAPI Crypt_Decrypt(const char* src,int nsrc,char* dst,int ndst,IPRIV_KEY* key);

// �������� �����.
// key: �������, �������� ��� �������� ����
// ����������: 0 - ����� ��� ��� ������
int IPRIVAPI Crypt_CloseKey(IPRIV_KEY* key);

// ��������������� ����������.
// ������ ����������� ������ ���� ��� ��� ���������� ���������� (� �������� ������).
// ����������: 0 - ����� ��� ��� ������
int IPRIVAPI Crypt_Done(void);



#ifdef __cplusplus
}
#endif

#endif
