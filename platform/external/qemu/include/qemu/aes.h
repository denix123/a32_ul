#ifndef QEMU_AES_H
#define QEMU_AES_H

#define AES_MAXNR 14
#define AES_BLOCK_SIZE 16

struct aes_key_st {
    uint32_t rd_key[4 *(AES_MAXNR + 1)];
    int rounds;
};
typedef struct aes_key_st AES_KEY;

int AES_set_encrypt_key(const unsigned char *userKey, const int bits,
	AES_KEY *key);
int AES_set_decrypt_key(const unsigned char *userKey, const int bits,
	AES_KEY *key);

void AES_encrypt(const unsigned char *in, unsigned char *out,
	const AES_KEY *key);
void AES_decrypt(const unsigned char *in, unsigned char *out,
	const AES_KEY *key);
void AES_cbc_encrypt(const unsigned char *in, unsigned char *out,
		     const unsigned long length, const AES_KEY *key,
		     unsigned char *ivec, const int enc);


extern const uint32_t AES_Te0[256], AES_Te1[256], AES_Te2[256],
                      AES_Te3[256], AES_Te4[256];
extern const uint32_t AES_Td0[256], AES_Td1[256], AES_Td2[256],
                      AES_Td3[256], AES_Td4[256];

#endif
