#ifndef CRYPTO_H
#define CRYPTO_H

class Crypto {
public:
    Crypto() {}
    virtual ~Crypto() {}
    
    // return the length of encrypted message
    virtual int encrypt(unsigned char *msg, int msgLen, unsigned char *encMsg) = 0;
    // return the length of decrypted message
    virtual int decrypt(unsigned char *encryptedMessage, int encryptedMessageLength, unsigned char *decryptedMessage) = 0;
};

#endif
