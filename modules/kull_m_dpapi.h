/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : http://creativecommons.org/licenses/by/3.0/fr/
*/
#pragma once
#include "globals.h"
#include "kull_m_crypto.h"
#include "kull_m_crypto_system.h"
#include "kull_m_string.h"

#define KIWI_DPAPI_ENTROPY_CAPI_KEY_EXPORTFLAGS	"Hj1diQ6kpUx7VC4m"
#define KIWI_DPAPI_ENTROPY_CNG_KEY_PROPERTIES	"6jnkd5J3ZdQDtrsu"
#define KIWI_DPAPI_ENTROPY_CNG_KEY_BLOB			"xT5rZW5qVVbrvpuA"

typedef struct _KULL_M_DWORD_TO_DWORD{
	PCWSTR	name;
	DWORD	id;
} KULL_M_DWORD_TO_DWORD, *PKULL_M_DWORD_TO_DWORD;

#pragma pack(push, 4) 
typedef struct _KULL_M_DPAPI_BLOB {
	DWORD	dwVersion;
	GUID	guidProvider;
	DWORD	dwMasterKeyVersion;
	GUID	guidMasterKey;
	DWORD	dwFlags;
	
	DWORD	dwDescriptionLen;
	PWSTR	szDescription;
	
	ALG_ID	algCrypt;
	DWORD	dwAlgCryptLen;
	
	DWORD	dwSaltLen;
	PBYTE	pbSalt;
	
	DWORD	dwHmacKeyLen;
	PBYTE	pbHmackKey;
	
	ALG_ID	algHash;
	DWORD	dwAlgHashLen;

	DWORD	dwHmac2KeyLen;
	PBYTE	pbHmack2Key;
	
	DWORD	dwDataLen;
	PBYTE	pbData;
	
	DWORD	dwSignLen;
	PBYTE	pbSign;
} KULL_M_DPAPI_BLOB, *PKULL_M_DPAPI_BLOB;


typedef struct _KULL_M_DPAPI_MASTERKEY {
	DWORD	dwVersion;
	BYTE	salt[16];
	DWORD	rounds;
	ALG_ID	algHash;
	ALG_ID	algCrypt;
	PBYTE	pbKey;
	DWORD	__dwKeyLen;
} KULL_M_DPAPI_MASTERKEY, *PKULL_M_DPAPI_MASTERKEY;

typedef struct _KULL_M_DPAPI_CREDHIST {
	DWORD	dwVersion;
	GUID	guid;
} KULL_M_DPAPI_CREDHIST, *PKULL_M_DPAPI_CREDHIST;

typedef struct _KULL_M_DPAPI_DOMAINKEY {
	DWORD	dwVersion;
	DWORD	dwSecretLen;
	DWORD	dwAccesscheckLen;
	GUID	guidMasterKey;
	PBYTE	pbSecret;
	PBYTE	pbAccesscheck;
} KULL_M_DPAPI_DOMAINKEY, *PKULL_M_DPAPI_DOMAINKEY;

typedef struct _KULL_M_DPAPI_MASTERKEYS {
	DWORD	dwVersion;
	DWORD	unk0;
	DWORD	unk1;
	WCHAR	szGuid[36];
	DWORD	unk2;
	DWORD	unk3;
	DWORD	dwFlags;
	DWORD64	dwMasterKeyLen;
	DWORD64 dwBackupKeyLen;
	DWORD64 dwCredHistLen;
	DWORD64	dwDomainKeyLen;
	PKULL_M_DPAPI_MASTERKEY	MasterKey;
	PKULL_M_DPAPI_MASTERKEY	BackupKey;
	PKULL_M_DPAPI_CREDHIST	CredHist;
	PKULL_M_DPAPI_DOMAINKEY	DomainKey;
} KULL_M_DPAPI_MASTERKEYS, *PKULL_M_DPAPI_MASTERKEYS;
#pragma pack(pop) 

void kull_m_dpapi_ptr_replace(PVOID ptr, DWORD64 size);
PKULL_M_DPAPI_BLOB kull_m_dpapi_blob_create(PVOID data/*, DWORD size*/);
void kull_m_dpapi_blob_delete(PKULL_M_DPAPI_BLOB blob);
void kull_m_dpapi_blob_descr(PKULL_M_DPAPI_BLOB blob);
PKULL_M_DPAPI_MASTERKEYS kull_m_dpapi_masterkeys_create(PVOID data/*, DWORD size*/);
void kull_m_dpapi_masterkeys_delete(PKULL_M_DPAPI_MASTERKEYS masterkeys);
void kull_m_dpapi_masterkeys_descr(PKULL_M_DPAPI_MASTERKEYS masterkeys);
PKULL_M_DPAPI_MASTERKEY kull_m_dpapi_masterkey_create(PVOID data, DWORD64 size);
void kull_m_dpapi_masterkey_delete(PKULL_M_DPAPI_MASTERKEY masterkey);
void kull_m_dpapi_masterkey_descr(PKULL_M_DPAPI_MASTERKEY masterkey);
PKULL_M_DPAPI_CREDHIST kull_m_dpapi_credhist_create(PVOID data, DWORD64 size);
void kull_m_dpapi_credhist_delete(PKULL_M_DPAPI_CREDHIST credhist);
void kull_m_dpapi_credhist_descr(PKULL_M_DPAPI_CREDHIST credhist);
PKULL_M_DPAPI_DOMAINKEY kull_m_dpapi_domainkey_create(PVOID data, DWORD64 size);
void kull_m_dpapi_domainkey_delete(PKULL_M_DPAPI_DOMAINKEY domainkey);
void kull_m_dpapi_domainkey_descr(PKULL_M_DPAPI_DOMAINKEY domainkey);

BOOL kull_m_dpapi_hmac_sha1_incorrect(LPCVOID key, DWORD keyLen, LPCVOID salt, DWORD saltLen, LPCVOID entropy, DWORD entropyLen, LPCVOID data, DWORD dataLen, LPVOID outKey);
BOOL kull_m_dpapi_sessionkey(LPCVOID masterkey, DWORD masterkeyLen, LPCVOID salt, DWORD saltLen, LPCVOID entropy, DWORD entropyLen, LPCVOID data, DWORD dataLen, ALG_ID hashAlg, LPVOID outKey, DWORD outKeyLen);
BOOL kull_m_dpapi_unprotect_blob(PKULL_M_DPAPI_BLOB blob, LPCVOID masterkey, DWORD masterkeyLen, LPCVOID entropy, DWORD entropyLen, LPCWSTR password, LPVOID *dataOut, DWORD *dataOutLen);

void kull_m_dpapi_displayPromptFlags(DWORD flags);
void kull_m_dpapi_displayProtectionFlags(DWORD flags);