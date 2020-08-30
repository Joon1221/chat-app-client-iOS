//#define USE_CONSTANT_KEY
#define USE_PEM_FILE_KEY

#define MAX_LEN_PEM_KEY 3000

#ifdef USE_PEM_FILE_KEY
    #define PRIVATE_PEM_KEY_FILENAME "private.pem"
    #define PUBLIC_PEM_KEY_FILENAME "public.pem"
#endif

#include <iostream>
#include <fstream>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <stdio.h>

using namespace std;

int public_encrypt(unsigned char * data,int data_len,unsigned char * key, unsigned char *encrypted);
int private_decrypt(unsigned char * enc_data,int data_len,unsigned char * key, unsigned char *decrypted);
int private_encrypt(unsigned char * data,int data_len,unsigned char * key, unsigned char *encrypted);
int public_decrypt(unsigned char * enc_data,int data_len,unsigned char * key, unsigned char *decrypted);

int padding = RSA_PKCS1_PADDING;

RSA * createRSA(unsigned char * key, int publicKey)
{
    RSA *rsa= NULL;
    BIO *keybio ;
    keybio = BIO_new_mem_buf(key, -1);
    if (keybio==NULL)
    {
        printf( "Failed to create key BIO");
        return 0;
    }
    if(publicKey)
    {
        rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa,NULL, NULL);
    }
    else
    {
        rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa,NULL, NULL);
    }
    if(rsa == NULL)
    {
        printf( "Failed to create RSA");
    }
    
    return rsa;
}

int public_encrypt(unsigned char * data,int data_len,unsigned char * key, unsigned char *encrypted)
{
    RSA * rsa = createRSA(key,1);
    int result = RSA_public_encrypt(data_len,data,encrypted,rsa,padding);
    return result;
}
int private_decrypt(unsigned char * enc_data,int data_len,unsigned char * key, unsigned char *decrypted)
{
    RSA * rsa = createRSA(key,0);
    int  result = RSA_private_decrypt(data_len,enc_data,decrypted,rsa,padding);
    return result;
}

int private_encrypt(unsigned char * data,int data_len,unsigned char * key, unsigned char *encrypted)
{
    RSA * rsa = createRSA(key,0);
    int result = RSA_private_encrypt(data_len,data,encrypted,rsa,padding);
    return result;
}
int public_decrypt(unsigned char * enc_data,int data_len,unsigned char * key, unsigned char *decrypted)
{
    RSA * rsa = createRSA(key,1);
    int  result = RSA_public_decrypt(data_len,enc_data,decrypted,rsa,padding);
    return result;
}

void printLastError(char *msg)
{
//    char * err = malloc(130);;
//    ERR_load_crypto_strings();
//    ERR_error_string(ERR_get_error(), err);
//    printf("%s ERROR: %s\n",msg, err);
//    free(err);
}

int main(){
    
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#ifdef USE_CONSTANT_KEY
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
    // generated from save_key_pair_files
//    char publicKey[]="-----BEGIN PUBLIC KEY-----\n"\
//    "MIIBCgKCAQEAvwYzOs6Jr/LauEtfuOvz7pAhU+fEXBnFCpY/L7DS7dLO/NgWRuJC\n"\
//    "wAc/qA/FfyMAmt7f6ZsTz/0okN9B7JJvN88St64MXU0LpUhhyU4OCkx/y4BVuDeA\n"\
//    "lommO19oFumJhp8oyjZNzKm/sSZop+iPx1SYKckemc+p/LIyu213DF4e9Mwfioeh\n"\
//    "MmHOJ2PmOre+XR61INsmMXzvb/TNWaSgoLwWD02s26kY0RnjPH22rVyztjzOgJMJ\n"\
//    "jC6t5910wRrQqncO1X7x57oVSYMMT0qfgbAxohOsWtDw1K2HB9rUGCEBoFfgBe5c\n"\
//    "ynItmkHaEo61mYBNRLy0/XjcV2pWQ08krwIDAQAB\n"\
//    "-----END PUBLIC KEY-----\n";
    
    // http://hayageek.com/rsa-encryption-decryption-openssl-c/
//    char publicKey[]="-----BEGIN PUBLIC KEY-----\n"\
//    "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAy8Dbv8prpJ/0kKhlGeJY\n"\
//    "ozo2t60EG8L0561g13R29LvMR5hyvGZlGJpmn65+A4xHXInJYiPuKzrKUnApeLZ+\n"\
//    "vw1HocOAZtWK0z3r26uA8kQYOKX9Qt/DbCdvsF9wF8gRK0ptx9M6R13NvBxvVQAp\n"\
//    "fc9jB9nTzphOgM4JiEYvlV8FLhg9yZovMYd6Wwf3aoXK891VQxTr/kQYoq1Yp+68\n"\
//    "i6T4nNq7NWC+UNVjQHxNQMQMzU6lWCX8zyg3yH88OAQkUXIXKfQ+NkvYQ1cxaMoV\n"\
//    "PpY72+eVthKzpMeyHkBn7ciumk5qgLTEJAfWZpe4f4eFZj/Rc8Y8Jj2IS5kVPjUy\n"\
//    "wQIDAQAB\n"\
//    "-----END PUBLIC KEY-----\n";
    
    //openssl rsa -in private.pem -outform PEM -pubout -out public.pem
//    char publicKey[]="-----BEGIN PUBLIC KEY-----\n"\
//    "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAkmMu/YGCzPauVoWzVskc\n"\
//    "9vn6fu/42Aq1mrqVt/A9eTKDYYhn9y1kOwssjeFc+YMA4fmwN2LxQuBmeAFrID1W\n"\
//    "nDQTc/LtPDxNsbKZIbFwgYryhsADkkxgvCHQpLbmBXGHL0ggOmTttLmnEpLI4I6t\n"\
//    "HAeVlmyttPniblqjQocLWrx399fg9vEwl+z+IRwdeflyVC8Q+bfk6YJB8UQEjvw/\n"\
//    "Tm6t7DiYXS/oswQToOsQrrTsQyalqIaQSp1a5S9P9OZuhz8iTeNsDhiomUlmbWGV\n"\
//    "fVkvCi0ILNuh+PjS86HScIp60pi/mMh0a4Z82RxXf9gnhnn3BWWblMoS6wWOrYMv\n"\
//    "MwIDAQAB\n"\
//    "-----END PUBLIC KEY-----\n";

    //http://phpseclib.sourceforge.net/rsa/examples.html
//    char publicKey[]="-----BEGIN PUBLIC KEY-----\n"\
//    "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQCqGKukO1De7zhZj6+H0qtjTkVxwTCpvKe4eCZ0\n"\
//    "FPqri0cb2JZfXJ/DgYSF6vUpwmJG8wVQZKjeGcjDOL5UlsuusFncCzWBQ7RKNUSesmQRMSGkVb1/\n"\
//    "3j+skZ6UtW+5u09lHNsj6tQ51s1SPrCBkedbNf0Tp0GbMJDyR4e9T04ZZwIDAQAB\n"\
//    "-----END PUBLIC KEY-----\n";
    
    //https://stackoverflow.com/questions/5927164/how-to-generate-rsa-private-key-using-openssl + openssl rsa -in private.pem -outform PEM -pubout -out public.pem
//    char publicKey[]="-----BEGIN PUBLIC KEY-----\n"\
//    "MIGdMA0GCSqGSIb3DQEBAQUAA4GLADCBhwKBgQDJqdWJO8fd9KJN06EkpMAAqJiV\n"\
//    "N0ZG6AGpXghLXjdkcg/UvpGtc8JWBVbY5WbTU0AhFnlo1YTHkjOPKSQJ1sF6oXfs\n"\
//    "i//0fUi9ndMLLjtJtj/ad/BVdxqiTEtUulST+ZCazuWCzyxOFHlb0G6dHK2q60wY\n"\
//    "2tk1G1RrP7qaO962RwIBAw==\n"\
//    "-----END PUBLIC KEY-----\n";

   
    char publicKey[]="-----BEGIN PUBLIC KEY-----\n"\
    "MIGdMA0GCSqGSIb3DQEBAQUAA4GLADCBhwKBgQDIvNx6gMvbz+aSRjl1lVEWVJCn\n"\
    "cShbEqoiWOORTsEgOWwhFhP7QtoVEBhNqO4besy0+wZS5JKkOt6GIMRM0R/KtJJA\n"\
    "1fcvARqzRY1oRtJxYIVlcmsRlmlrlp39eVA4YRjVVuHfR8/CZO1tveOytcdtW74e\n"\
    "bDgp1lBE2OGMEusX9wIBAw==\n"\
    "-----END PUBLIC KEY-----\n";
    
    // generated from save_key_pair_files
//    char privateKey[]="-----BEGIN RSA PRIVATE KEY-----\n"\
//    "MIIEowIBAAKCAQEAy8Dbv8prpJ/0kKhlGeJYozo2t60EG8L0561g13R29LvMR5hy\n"\
//    "MIIEowIBAAKCAQEAvwYzOs6Jr/LauEtfuOvz7pAhU+fEXBnFCpY/L7DS7dLO/NgW\n"\
//    "RuJCwAc/qA/FfyMAmt7f6ZsTz/0okN9B7JJvN88St64MXU0LpUhhyU4OCkx/y4BV\n"\
//    "uDeAlommO19oFumJhp8oyjZNzKm/sSZop+iPx1SYKckemc+p/LIyu213DF4e9Mwf\n"\
//    "ioehMmHOJ2PmOre+XR61INsmMXzvb/TNWaSgoLwWD02s26kY0RnjPH22rVyztjzO\n"\
//    "gJMJjC6t5910wRrQqncO1X7x57oVSYMMT0qfgbAxohOsWtDw1K2HB9rUGCEBoFfg\n"\
//    "Be5cynItmkHaEo61mYBNRLy0/XjcV2pWQ08krwIDAQABAoIBADvqae8sESvK9KeR\n"\
//    "nLiX6a8OLiXvMDvjKVakwbTntYE6+gl8jaA2H9GzdFf2em/iPrJU7c6MAa7fLPYj\n"\
//    "0L2vQIs0vB44zVAGdnylM2a8wNKiJANkgX6CiiatjiJZToDBR42eJmEmn0huhd2+\n"\
//    "ulzQKSjQc9nHZ32/EQZdrmPzdb++yihA5ZKf+fmD+RQdRYZqCS84dlj30pCNTfBI\n"\
//    "Hem77ZgBdTmC5JsingND6ILrPiiUKJAtnRSWpfyzYNKWxpxN49ZfKqD4j17lyj83\n"\
//    "f6cW3mepRwyNpS5fmm5tl6/ebx09vlFWiKIYx05TZUAgNz2Zs7I//obQVRmcmA2O\n"\
//    "ttagemECgYEA+SsxRs3qlHSTTJYs3mUpZxza2aVdxp4DmZkZS7XP1Ujy6DLctJ+b\n"\
//    "U+zk8A5rgl4BRm8tTNc52u95+iFhSpA/Q42cbtjc20+MrcOqZmr8GNHciuTHXRju\n"\
//    "1hqmwyfu/LBUAUVFZXngiGKV4PXKK116A8S2tDzIqJ26/aLAZPWQvEUCgYEAxELq\n"\
//    "oLNg3ZkE0ndIJYcnB3s5xnFM6LZlYNQkTw324FDflKR/VwHt34Ti9PzoGN0zqQBy\n"\
//    "BnD2BJOF22dX1ap//T5K2JM8A0XeSJ/6PMypuBJqNW/gcC9Xm7j64f6heuceGx4v\n"\
//    "/pljC8LwVJGrP78U+jaUFi55gREP/o+EYIYxXmMCgYASSoxsgTNGQKSLi76xeMWo\n"\
//    "TyL1tUEEEpd7EBUeTLN8GcXTK+Ct1cWmTI6l3LkhsdrwG7s8l9QkcU4IAalNuvcZ\n"\
//    "82xXas4Tv2w5WVLJ//KPs+A3xgGooOrvhrdVPjo6DIuuKDKm92J3QJ12DTURJ+SM\n"\
//    "IEW1R30He8S9V9Q91RUR7QKBgH9OZMGO+cNkcbNP+nWVYKTCsuxdLCU7wzD3CwJY\n"\
//    "rY4+B3l05sD6mGFH4qxFrQwL2GnExzIUbhDz3H1AYMJRUapkkMpBX0lENfboBrsP\n"\
//    "ivvCvjAhfPVoUCzL5blYoUiGyImQoFNHDe9gKOLChtHX0fSoGJD23ovxFG3sjFLM\n"\
//    "WRO/AoGBAOYDjJpFGMGTVCfrTWfx5dEO1GE+GCB1i9tL/q2QKKULff/kjhu5OJPM\n"\
//    "iWfNlrda3sJ7eVswFD4Ujc39utWnARdJrm4syTMgLHbLRJCuTMdUHxzI8Wy9PYDq\n"\
//    "KDu5G6KASKQcU5s1idvD8nG6JPqJ0q9G0FFihNXFtNX7tw5F2IqX\n"\
//    "-----END RSA PRIVATE KEY-----\n";
    
    // http://hayageek.com/rsa-encryption-decryption-openssl-c/
//    char privateKey[]="-----BEGIN RSA PRIVATE KEY-----\n"\
//    "MIIEowIBAAKCAQEAy8Dbv8prpJ/0kKhlGeJYozo2t60EG8L0561g13R29LvMR5hy\n"\
//    "vGZlGJpmn65+A4xHXInJYiPuKzrKUnApeLZ+vw1HocOAZtWK0z3r26uA8kQYOKX9\n"\
//    "Qt/DbCdvsF9wF8gRK0ptx9M6R13NvBxvVQApfc9jB9nTzphOgM4JiEYvlV8FLhg9\n"\
//    "yZovMYd6Wwf3aoXK891VQxTr/kQYoq1Yp+68i6T4nNq7NWC+UNVjQHxNQMQMzU6l\n"\
//    "WCX8zyg3yH88OAQkUXIXKfQ+NkvYQ1cxaMoVPpY72+eVthKzpMeyHkBn7ciumk5q\n"\
//    "gLTEJAfWZpe4f4eFZj/Rc8Y8Jj2IS5kVPjUywQIDAQABAoIBADhg1u1Mv1hAAlX8\n"\
//    "omz1Gn2f4AAW2aos2cM5UDCNw1SYmj+9SRIkaxjRsE/C4o9sw1oxrg1/z6kajV0e\n"\
//    "N/t008FdlVKHXAIYWF93JMoVvIpMmT8jft6AN/y3NMpivgt2inmmEJZYNioFJKZG\n"\
//    "X+/vKYvsVISZm2fw8NfnKvAQK55yu+GRWBZGOeS9K+LbYvOwcrjKhHz66m4bedKd\n"\
//    "gVAix6NE5iwmjNXktSQlJMCjbtdNXg/xo1/G4kG2p/MO1HLcKfe1N5FgBiXj3Qjl\n"\
//    "vgvjJZkh1as2KTgaPOBqZaP03738VnYg23ISyvfT/teArVGtxrmFP7939EvJFKpF\n"\
//    "1wTxuDkCgYEA7t0DR37zt+dEJy+5vm7zSmN97VenwQJFWMiulkHGa0yU3lLasxxu\n"\
//    "m0oUtndIjenIvSx6t3Y+agK2F3EPbb0AZ5wZ1p1IXs4vktgeQwSSBdqcM8LZFDvZ\n"\
//    "uPboQnJoRdIkd62XnP5ekIEIBAfOp8v2wFpSfE7nNH2u4CpAXNSF9HsCgYEA2l8D\n"\
//    "JrDE5m9Kkn+J4l+AdGfeBL1igPF3DnuPoV67BpgiaAgI4h25UJzXiDKKoa706S0D\n"\
//    "4XB74zOLX11MaGPMIdhlG+SgeQfNoC5lE4ZWXNyESJH1SVgRGT9nBC2vtL6bxCVV\n"\
//    "WBkTeC5D6c/QXcai6yw6OYyNNdp0uznKURe1xvMCgYBVYYcEjWqMuAvyferFGV+5\n"\
//    "nWqr5gM+yJMFM2bEqupD/HHSLoeiMm2O8KIKvwSeRYzNohKTdZ7FwgZYxr8fGMoG\n"\
//    "PxQ1VK9DxCvZL4tRpVaU5Rmknud9hg9DQG6xIbgIDR+f79sb8QjYWmcFGc1SyWOA\n"\
//    "SkjlykZ2yt4xnqi3BfiD9QKBgGqLgRYXmXp1QoVIBRaWUi55nzHg1XbkWZqPXvz1\n"\
//    "I3uMLv1jLjJlHk3euKqTPmC05HoApKwSHeA0/gOBmg404xyAYJTDcCidTg6hlF96\n"\
//    "ZBja3xApZuxqM62F6dV4FQqzFX0WWhWp5n301N33r0qR6FumMKJzmVJ1TA8tmzEF\n"\
//    "yINRAoGBAJqioYs8rK6eXzA8ywYLjqTLu/yQSLBn/4ta36K8DyCoLNlNxSuox+A5\n"\
//    "w6z2vEfRVQDq4Hm4vBzjdi3QfYLNkTiTqLcvgWZ+eX44ogXtdTDO7c+GeMKWz4XX\n"\
//    "uJSUVL5+CVjKLjZEJ6Qc2WZLl94xSwL71E41H4YciVnSCQxVc4Jw\n"\
//    "-----END RSA PRIVATE KEY-----\n";
  
   //generated by openssl genrsa -out private.pem 2048
//    char privateKey[]="-----BEGIN RSA PRIVATE KEY-----\n"\
//    "MIIEowIBAAKCAQEAkmMu/YGCzPauVoWzVskc9vn6fu/42Aq1mrqVt/A9eTKDYYhn\n"\
//    "9y1kOwssjeFc+YMA4fmwN2LxQuBmeAFrID1WnDQTc/LtPDxNsbKZIbFwgYryhsAD\n"\
//    "kkxgvCHQpLbmBXGHL0ggOmTttLmnEpLI4I6tHAeVlmyttPniblqjQocLWrx399fg\n"\
//    "9vEwl+z+IRwdeflyVC8Q+bfk6YJB8UQEjvw/Tm6t7DiYXS/oswQToOsQrrTsQyal\n"\
//    "qIaQSp1a5S9P9OZuhz8iTeNsDhiomUlmbWGVfVkvCi0ILNuh+PjS86HScIp60pi/\n"\
//    "mMh0a4Z82RxXf9gnhnn3BWWblMoS6wWOrYMvMwIDAQABAoIBABRx18E+EkeP+D9L\n"\
//    "QwXO5sWzmgGagFWkAUMP5hMfcWZ44JKBm4uRAlugruNN409RtZDZ73t8zRc7AfSm\n"\
//    "thB1oKAGQeVCu1FbVrqHqA1lm8Hr5v1c2eLX2fbMfjhS9wMxnODEoQOmzvAbsbLN\n"\
//    "X1LFenXctU6h9Qy+jZo9/GkxNSvByqiecYwL9jm4Nsm3n2De869AKmI/WBF7q1Ov\n"\
//    "WFvGALFWSGyZ1XlDiBTCW6FqojzoSD8r/Zw5q5C0A+BvGj7EZYHU/uogZiHqZiZc\n"\
//    "CTYE3y2fZYFZhaUUPqXGqlaJ8xFRHyvbYj8SbFwtFH1zVlAd4042BwsIKWslkSMP\n"\
//    "KbyMtrkCgYEAwjdZBVTmT3rqhpCh6aSpFKPvs5m4hFL9F8DGfekXWfBY3aRTll1Y\n"\
//    "WTiZMigOz3RG7Krnu7/YRTPAET1gq5RQ4ck3tNrdtRmXFFiVRSgoGpUjFWc7kMhS\n"\
//    "l5bHg0hzPaczOU91m9GSuMKLiZSbuxzdj7jKMnw6D7LvKoaXryZpFXUCgYEAwPS9\n"\
//    "HLsk939WFIAMT0j01gFcmkB78Thpc+8GLl/n2P7oUJPoMbYzF9/uvllxnmfdXdZi\n"\
//    "3CRjAbdcsrjsvuVAQ8PN9Vjc0RjoKt9WpEaJaO/qKSqXi9lkjHd336zaIDt6F3KQ\n"\
//    "aWFUAuiDcrw+DSUT8vOaa5fDoQvPGNEqBrE9FQcCgYEAlrr79P5aLI852yv+7WUk\n"\
//    "8Gb3Ds2b/d6mnLu5kVjJDb1SStpRIR7bBYu+ocWjEPCuZtmRNg6DW9n5E6guEZvv\n"\
//    "VfyjplJCxV3R+jFx0BWFYnQioWbYPNqr9whHWaVuAwhz4ePAZCk3lPsv7pwObR7O\n"\
//    "+c8x5hKxwSNfKQMCUCYgYk0CgYBiFYZ0LmVyMhZtwVGAlBNxHawW9SSL0CM6vYwk\n"\
//    "0remRJ2PKEBl1LpQLpLLy+fHoACVDL+gLBbv7md+qiYeO6bZS5VMXGmTGNgbwv/l\n"\
//    "7b03zIz5dB8pBc7o4GndF56ht9ouRRxHlSQBfnQjRLE+OVTUsSQUAUd+e+RAN0Ln\n"\
//    "t/zWzQKBgAnDTFZbTS7BLY0ohz6em3xsfYnjT2jkJUMxADxtL1Xto4GxOjhZm6GE\n"\
//    "yhVZ+EIlJWG50fJIKcZ2uXqcdvhMOg96AprxOjY2S/5lljKJIQRR1fkAf4MN4JdK\n"\
//    "7Se0R8Oh+k528uL1nbJpoXyf7YN8PWLA1lF6agOpkj7KIEotX7OM\n"\
//    "-----END RSA PRIVATE KEY-----\n";
    
    //http://phpseclib.sourceforge.net/rsa/examples.html
//    char privateKey[]="-----BEGIN RSA PRIVATE KEY-----\n"\
//    "MIICXAIBAAKBgQCqGKukO1De7zhZj6+H0qtjTkVxwTCpvKe4eCZ0FPqri0cb2JZfXJ/DgYSF6vUp\n"\
//    "wmJG8wVQZKjeGcjDOL5UlsuusFncCzWBQ7RKNUSesmQRMSGkVb1/3j+skZ6UtW+5u09lHNsj6tQ5\n"\
//    "1s1SPrCBkedbNf0Tp0GbMJDyR4e9T04ZZwIDAQABAoGAFijko56+qGyN8M0RVyaRAXz++xTqHBLh\n"\
//    "3tx4VgMtrQ+WEgCjhoTwo23KMBAuJGSYnRmoBZM3lMfTKevIkAidPExvYCdm5dYq3XToLkkLv5L2\n"\
//    "pIIVOFMDG+KESnAFV7l2c+cnzRMW0+b6f8mR1CJzZuxVLL6Q02fvLi55/mbSYxECQQDeAw6fiIQX\n"\
//    "GukBI4eMZZt4nscy2o12KyYner3VpoeE+Np2q+Z3pvAMd/aNzQ/W9WaI+NRfcxUJrmfPwIGm63il\n"\
//    "AkEAxCL5HQb2bQr4ByorcMWm/hEP2MZzROV73yF41hPsRC9m66KrheO9HPTJuo3/9s5p+sqGxOlF\n"\
//    "L0NDt4SkosjgGwJAFklyR1uZ/wPJjj611cdBcztlPdqoxssQGnh85BzCj/u3WqBpE2vjvyyvyI5k\n"\
//    "X6zk7S0ljKtt2jny2+00VsBerQJBAJGC1Mg5Oydo5NwD6BiROrPxGo2bpTbu/fhrT8ebHkTz2epl\n"\
//    "U9VQQSQzY1oZMVX8i1m5WUTLPz2yLJIBQVdXqhMCQBGoiuSoSjafUhV7i1cEGpb88h5NBYZzWXGZ\n"\
//    "37sJ5QsW+sJyoNde3xH8vdXhzU7eT82D6X/scw9RZz+/6rCJ4p0=\n"\
//    "-----END RSA PRIVATE KEY-----\n";

    //https://stackoverflow.com/questions/5927164/how-to-generate-rsa-private-key-using-openssl + copy and pasted from printed result
//    char privateKey[]="-----BEGIN RSA PRIVATE KEY-----\n"\
//    "MIICXAIBAAKBgQDJqdWJO8fd9KJN06EkpMAAqJiVN0ZG6AGpXghLXjdkcg/UvpGt\n"\
//    "c8JWBVbY5WbTU0AhFnlo1YTHkjOPKSQJ1sF6oXfsi//0fUi9ndMLLjtJtj/ad/BV\n"\
//    "dxqiTEtUulST+ZCazuWCzyxOFHlb0G6dHK2q60wY2tk1G1RrP7qaO962RwIBAwKB\n"\
//    "gQCGcTkGJ9qT+Gwz4mttwyqrGxBjei7Z8AEblAWHlCTtoV/jKbZzooGOrjnl7kSM\n"\
//    "4irAuaZF463aYXe0xhgGjyul51Z/jEaCDHRjg4+ybApshPzywNpnL1xryqoP7qt6\n"\
//    "B9c36pglNlC8JCQM84nww/RaPchQma3LnbIWfKkpN8KZywJBAOYPjiJADgcyXpLv\n"\
//    "8YzAPKRzNBYqUAA1A0h0hm1NsUDODerSurrFvx4z3s8P5j20O5tg3t9hLD87MX+C\n"\
//    "FOpYCmkCQQDgZp8XViNjZ8nFi43/a2pKUTpAfmqv2v1T17ZnBaus/7kELpBC7XTA\n"\
//    "D2mUD825CufzPsEU81dvjhgFOsd94sUvAkEAmV+0FtVer3bpt0qhCIAobaIiuXGK\n"\
//    "qs4CME2u84kg1d6z8eHR0dkqFCKUigqZfngnvOs/P5Ydf3zLqla4nDqxmwJBAJWZ\n"\
//    "v2TkF5eahoOyXqpHnDGLfCr+8cqR/jflJESucnNVJgLJtYHzoyq08Q1f3ntcmqIp\n"\
//    "1g33j5+0EAN8hP6XLh8CQAMn2wquWManjOqzYFCetInm/UUBEBhs53DYTMEm98/t\n"\
//    "VLAvLH6/pTm/ykuWp77O1BFjxmY0RdBxWM6MfUTry1A=\n"\
//    "-----END RSA PRIVATE KEY-----\n";
    
    char privateKey[]="-----BEGIN RSA PRIVATE KEY-----\n"\
    "MIICXAIBAAKBgQDIvNx6gMvbz+aSRjl1lVEWVJCncShbEqoiWOORTsEgOWwhFhP7\n"\
    "QtoVEBhNqO4besy0+wZS5JKkOt6GIMRM0R/KtJJA1fcvARqzRY1oRtJxYIVlcmsR\n"\
    "lmlrlp39eVA4YRjVVuHfR8/CZO1tveOytcdtW74ebDgp1lBE2OGMEusX9wIBAwKB\n"\
    "gQCF0z2nAIfn3+8MLtD5DjYO4wsaS3A8txwW5e0LidYVe51rZA1SLJFjYBAzxfQS\n"\
    "Ud3N/K7h7bcYJz8EFdgzNhUwnuT6+CrI0iq3ksGvYt5FpmeBoZRqQcBL7lwhOgsw\n"\
    "+iV5W09yP/BUexD44hWYmO23kLF+3JsJ+jW6h0TYNQXcOwJBAPD7LWIlvGrLTp8Z\n"\
    "KUvJAJL1bbUT86SYr8jlpYT4LMEe+pM2/WJGfB4cMPMYxrWhQcluqQSDUX/5tOW0\n"\
    "c7VxVFMCQQDVP5r/kUVbD1FKUbfmvAhT9LVK+H6PMEnoLiYdR0IowaS6s7aFoMeO\n"\
    "N8d3qocawZg5RTcczElfBfgoRdQN8PlNAkEAoKdzlsPS8dzfFLtw3TCrDKOeeLf3\n"\
    "wxB1MJkZA1Ad1hSnDM9TltmoFBLLTLsvI8DWhknGAwI2VVEjQ82iePY4NwJBAI4q\n"\
    "Z1ULg5IKNjGLz+8oBY1NzjH6/wogMUV0GWjaLBsrwyciea5rL7QlL6UcWhHWZXuD\n"\
    "ehMy25SupXAujV6gpjMCQD+m7iVJgCTuygODLzKi82tgxxiICbg3vTFiQ6dqtLyd\n"\
    "opDGVCNqQmLU1VudBii9MFk3LBrxzSfIaD35YZ2/UTo=\n"\
    "-----END RSA PRIVATE KEY-----\n";
#endif
    
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#ifdef USE_PEM_FILE_KEY
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
    char publicKey[MAX_LEN_PEM_KEY];
    char privateKey[MAX_LEN_PEM_KEY];
    
    ifstream privatePemKeyFile;
    privatePemKeyFile.open(PRIVATE_PEM_KEY_FILENAME);
    if (privatePemKeyFile.fail()) {
        cout << "error - failed to open: " << PRIVATE_PEM_KEY_FILENAME << endl;
        exit(1);
    }
    
    int i = 0;
    char ch = privatePemKeyFile.get();
    while (!privatePemKeyFile.eof()) {
        privateKey[i] = ch;
        
        ch = privatePemKeyFile.get();
        i++;
    }
    privatePemKeyFile.close();

    ifstream publicPemKeyFile;
    publicPemKeyFile.open(PUBLIC_PEM_KEY_FILENAME);
    if (publicPemKeyFile.fail()) {
        cout << "error - failed to open: " << PUBLIC_PEM_KEY_FILENAME << endl;
        exit(1);
    }

    i = 0;
    ch = publicPemKeyFile.get();
    while (!publicPemKeyFile.eof()) {
        publicKey[i] = ch;
        
        ch = publicPemKeyFile.get();
        i++;
    }
    publicPemKeyFile.close();
    
#endif

    //--------------------------------------------------------------------------
    // 201801041705: read pem files
    //--------------------------------------------------------------------------
    char plainText[2048/8] = "Hello this is Ravi.";
//    char plainText[2048/8] =
//    "0123456789abcdef"\
//    "0123456789abcdef"\
//    "0123456789abcdef"\
//    "0123456789abcdef"\
//    "0123456789abcdef"\
//    "0123456789abcdef"\
//    "0123456789abcdef"\
//    "0123456789abcdef"\
//    "0123456789abcdef"\
//    "0123456789abcdef"\
//    "0123456789abcdef"\
//    "0123456789abcdef"\
//    "0123456789abcdef"\
//    "0123456789abcdef"\
//    "01234"\
//    "0123456789ABCDEF";
//    // 245바이트를 넘어가면, 에러가 나므로 일단 그 이하의 규격을 정해놓고 한다.

    int plainTextLen = strlen(plainText);
    unsigned char *plainTextPointer = (unsigned char *)&plainText[0];
    
    unsigned char *publicKeyPointer = (unsigned char *)&publicKey[0];
    unsigned char *privateKeyPointer = (unsigned char *)&privateKey[0];
    
    unsigned char encrypted[4096]={};
    unsigned char *encryptedPointer = &encrypted[0];
    unsigned char decrypted[4096]={};
    unsigned char *decryptedPointer = &decrypted[0];

    int encrypted_length = public_encrypt(plainTextPointer, plainTextLen, publicKeyPointer, encryptedPointer);
    if(encrypted_length == -1)
    {
        printLastError("Public Encrypt failed ");
        exit(0);
    }
    printf("Encrypted length =%d\n", encrypted_length);
    printf("Encrypted bytes =\n", encrypted_length);
    for (int i = 0; i < encrypted_length; i++) {
        printf("%02x ", encrypted[i]);
        if ((i+1) % 16 == 0) {
            printf("\n");
        }
    }
    
    int decrypted_length = private_decrypt(encryptedPointer, encrypted_length, privateKeyPointer, decryptedPointer);
    if(decrypted_length == -1)
    {
        printLastError("Private Decrypt failed ");
        exit(0);
    }
    printf("Decrypted Text = %s\n",decrypted);
    printf("Decrypted Length = %d\n",decrypted_length);
    
    
    encrypted_length= private_encrypt(plainTextPointer, plainTextLen, privateKeyPointer, encryptedPointer);
    if(encrypted_length == -1)
    {
        printLastError("Private Encrypt failed");
        exit(0);
    }
    printf("Encrypted length = %d\n",encrypted_length);
    
    decrypted_length = public_decrypt(encryptedPointer, encrypted_length, publicKeyPointer, decryptedPointer);
    if(decrypted_length == -1)
    {
        printLastError("Public Decrypt failed");
        exit(0);
    }
    printf("Decrypted Text = %s\n",decrypted);
    printf("Decrypted Length = %d\n",decrypted_length);
    
    return 0;
}
