#ifndef RSA_CRYPTO_H
#define RSA_CRYPTO_H

#define MAX_LEN_KEY 3000

#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include "crypto.h"

class RSACrypto : public Crypto {
private:
    unsigned char publicKey[MAX_LEN_KEY];
    unsigned char privateKey[MAX_LEN_KEY];
    
    RSA *rsaPrivateKey;
    RSA *rsaPublicKey;

public:
    RSACrypto();
    RSACrypto(const char *privateKey, const char *publiKey);
    virtual ~RSACrypto();
    
    // return the length of encrypted message
    virtual int encrypt(unsigned char *msg, int msgLen, unsigned char *encMsg);
    // return the length of decrypted message
    virtual int decrypt(unsigned char *encryptedMessage, int encryptedMessageLength, unsigned char *decryptedMessage);
};

#endif
