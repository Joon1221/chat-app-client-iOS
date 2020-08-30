#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <stdio.h>

#include "rsa_crypto.h"

RSA *createRSA(unsigned char *key, int publicKey)
{
//    cout << "createRSA(): key: "<< endl;
//    cout << key << endl;
    
    RSA *rsa = NULL;
    BIO *keybio;
    
    keybio = BIO_new_mem_buf(key, -1);
    
    if (keybio == NULL) {
        printf( "Failed to create key BIO");
        return 0;
    }
    
    if (publicKey) {
        rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL);
    }
    else {
        rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);
    }
    
    if (rsa == NULL) {
        printf( "Failed to create RSA");
    }
    
    return rsa;
}

RSACrypto::RSACrypto() : Crypto() {
    privateKey[0] = '\0';
    publicKey[0] = '\0';
    
    rsaPrivateKey = NULL;
    rsaPublicKey = NULL;
}

RSACrypto::RSACrypto(const char *privateKey, const char *publicKey) : Crypto() {
    strncpy((char *)this->privateKey, (char *)privateKey, MAX_LEN_KEY);
    strncpy((char *)this->publicKey, (char *)publicKey, MAX_LEN_KEY);
    
//    cout << "this: " << (long)this << endl;
//    cout << "RSACrypto::RSACrypto(,): this->privateKey: "<< endl;
//    cout << this->privateKey << endl;
//    cout << "RSACrypto::RSACrypto(,): this->publicKey: "<< endl;
//    cout << this->publicKey << endl;
    
    rsaPrivateKey = createRSA((unsigned char *)publicKey, 1);
    rsaPublicKey = createRSA((unsigned char *)privateKey, 0);
}

RSACrypto::~RSACrypto() {
    
};

int RSACrypto::encrypt(unsigned char *msg, int msgLen, unsigned char *encMsg) {
//    cout << "this: " << (long)this << endl;
//    cout << "RSACrypto::encrypt(): this->publicKey: "<< endl;
//    cout << this->publicKey << endl;
//    cout << "RSACrypto::encrypt(): this->publicKey: "<< endl;
    int result = RSA_public_encrypt(msgLen, msg, encMsg, rsaPrivateKey, RSA_PKCS1_PADDING);
    return result;
}

int RSACrypto::decrypt(unsigned char *encryptedMessage, int encryptedMessageLength, unsigned char *decryptedMessage) {
//    cout << "RSACrypto::decrypt(): this->publicKey: "<< endl;

    int result = RSA_private_decrypt(encryptedMessageLength, encryptedMessage, decryptedMessage, rsaPublicKey, RSA_PKCS1_PADDING);
    return result;
}
