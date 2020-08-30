//
//  ViewController.m
//  OPENSSL_IOS
//
//  Created by Joon Kang on 2017-10-28.
//  Copyright © 2017 Joon Kang. All rights reserved.
//
#define MAX_LEN_BUFFER 1000

//#define REQUEST_NONE 0
//#define REQUEST_LOGIN 1

#include <string>
#include <cstring>
#include <vector>

using namespace std;

#import "ViewController.h"
//#include "base64.h"
#include "crypto.h"
#include "rsa_crypto.h"
//#include "crypto_example.h"
#include "request_protocol.h"
#include "response_protocol.h"

//#include <include/internal/evp_int.h>
//#include <rsa/rsa_locl.h>
//#include <bn/bn_lcl.h>

@interface ViewController () {
    
    CFReadStreamRef readStream;
    CFWriteStreamRef writeStream;
    
    NSInputStream *inputStream;
    NSOutputStream *outputStream;
    
    NSString *host;
    int port;
    
    vector<string> chatMessages;
}

@end

@implementation ViewController {
    Crypto *crypto;
    unsigned char *encryptedMessage;
    unsigned char *decryptedMessage;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    host = @"http://127.0.0.1";
    port = 7777;

    NSURL *url = [NSURL URLWithString:host];
    
    NSLog(@"Setting up connection to %@ : %i", [url absoluteString], port);
    
//    CFStreamCreatePairWithSocketToHost(kCFAllocatorDefault, (CFStringRef)[url host], port, &readStream, &writeStream);
    CFStreamCreatePairWithSocketToHost(kCFAllocatorDefault, (CFStringRef)CFBridgingRetain([url host]), port, &readStream, &writeStream);

    if(!CFWriteStreamOpen(writeStream)) {
        NSLog(@"Error, writeStream not open");
        
        return;
    }
    if(!CFReadStreamOpen(readStream)) {
        NSLog(@"Error, readStream not open");
        
        return;
    }
//    [self open];
    
    NSLog(@"Status of outputStream: %i", [outputStream streamStatus]);
    
    NSLog(@"Opening streams.");
    
    inputStream = (NSInputStream *)CFBridgingRelease(readStream);
    outputStream = (NSOutputStream *)CFBridgingRelease(writeStream);

    [inputStream setDelegate:self];
    [outputStream setDelegate:self];

    [inputStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    [outputStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];

    [inputStream open];
    [outputStream open];
    
    
    encryptedMessage = new unsigned char [MAX_LEN_BUFFER];
    decryptedMessage = new unsigned char [MAX_LEN_BUFFER];

    NSString *privateKeyPath = [[NSBundle mainBundle] pathForResource:@"private" ofType:@"pem"];
    NSString *privateKey = [NSString stringWithContentsOfFile:privateKeyPath encoding:NSUTF8StringEncoding error:NULL];
    NSLog(@"%@", privateKey);

    NSString *publicKeyPath = [[NSBundle mainBundle] pathForResource:@"public" ofType:@"pem"];
    NSString *publicKey = [NSString stringWithContentsOfFile:publicKeyPath encoding:NSUTF8StringEncoding error:NULL];
    NSLog(@"%@", publicKey);

    crypto = new RSACrypto([privateKey cStringUsingEncoding:NSUTF8StringEncoding], [publicKey cStringUsingEncoding:NSUTF8StringEncoding]);
 
    NSLog( @"Hello World from create \n" );
    NSThread* evtThread = [ [NSThread alloc] initWithTarget:self
                                                   selector:@selector(pollChatMessages)
                                                     object:nil ];
    
    [ evtThread start ];
}

- (void) pollChatMessages
{
    while (true) {
        char protocol[1000];
        RequestProtocolPollChatLog reqProt;
        
        char id[100];
        char password[100];
        
        reqProt.type = REQUEST_POLL_CHAT_LOG;
        reqProt.id = 0x12345678;
        reqProt.sessionID = 0x0123456789ABCDEF;
        
        int packetLen = reqProt.toPacket(protocol);
        reqProt.printCharArrayInHex(protocol, packetLen);
        
        unsigned char *encryptedMessage = new unsigned char [MAX_LEN_BUFFER];
        
//        NSLog(@"Encrypting.........................................................................................................");
        memset(encryptedMessage, 0, MAX_LEN_BUFFER);
        int encrypted_length = crypto->encrypt((unsigned char *)protocol, packetLen, encryptedMessage);
        
        NSLog(@"pollChatMessages(): ---------------------------------------------------------------------- Sending Response Poll Chat Log");

        [outputStream write:(uint8_t *)encryptedMessage maxLength:encrypted_length];
        
//        NSLog(@"encrypted_length = %d", encrypted_length);
        
        
        [NSThread sleepForTimeInterval:3.0f];
        
    }
}

- (void)stream:(NSStream *)stream handleEvent:(NSStreamEvent)event {
//    NSLog(@"Stream triggered.");

    switch(event) {
        case NSStreamEventHasSpaceAvailable: {
            if(stream == outputStream) {
//                NSLog(@"outputStream is ready.");
            }
            break;
        }
        case NSStreamEventHasBytesAvailable: {
            if(stream == inputStream) {
//                NSLog(@"inputStream is ready.");
                
                uint8_t buf[1024];
                unsigned int len = 0;
                
                len = [inputStream read:buf maxLength:1024];
                
                if(len > 0) {
//                    NSMutableData* data=[[NSMutableData alloc] initWithLength:0];
//
//                    [data appendBytes: (const void *)buf length:len];
//
//                    NSString *s = [[NSString alloc] initWithData:data encoding:NSASCIIStringEncoding];
                    ResponseProtocol::printCharArrayInHex((char *)buf, len);

                    ResponseProtocol *responseProtocol;
                    responseProtocol = ResponseProtocol::makeObjectFromPacket((char *)buf);
                    responseProtocol->fromPacket((char *)buf);
//                    responseProtocol->print();
                    if (responseProtocol->type == RESPONSE_POLL_CHAT_LOG) {
                        NSLog(@"stream(): -------------------------------------------------------------- responseProtocol->type == RESPONSE_POLL_CHAT_LOG");
                        
                        NSLog(@"Response Message from server = %s\n", ((ResponseProtocolPollChatLog *)responseProtocol)->messages.c_str());
                        
                        chatMessages.push_back(string(((ResponseProtocolPollChatLog *)responseProtocol)->messages.c_str()));
                        NSString *chatMessageInNSString = [NSString stringWithFormat:@"%@%s", _chatMessages.text, ((ResponseProtocolPollChatLog *)responseProtocol)->messages.c_str()];
                        
                        [_chatMessages setText:chatMessageInNSString];
                    }
                    else if (responseProtocol->type == RESPONSE_MESSAGE) {
                        NSLog(@"stream(): -------------------------------------------------------------- responseProtocol->type == RESPONSE_MESSAGE");
                    }

//                    [self readIn:s];
//
//                    [data release];
                }
            }
            break;
        }
        default: {
//            NSLog(@"Stream is sending an Event: %i", event);
            
            break;
        }
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)buttonPressed:(id)sender {
    char protocol[1000];
//    RequestProtocolPollChatLog reqProt;
    RequestProtocolMessage reqProt;

    char id[100];
    char password[100];
    
    NSString *message = _textField.text;
//    NSLog(@"message: %@", message);
    
    const char *messageInCharPtr = [message cStringUsingEncoding:NSUTF8StringEncoding];
    
    reqProt.type = REQUEST_MESSAGE;
    reqProt.id = 0x12345678;
    reqProt.sessionID = 0x0123456789ABCDEF;
    reqProt.message = string(messageInCharPtr);
    
//    for (int i = 0; i < strlen(messageInCharPtr); i++) {
//        protocol[i] = messageInCharPtr[i];
//    }
    
    int packetLen = reqProt.toPacket(protocol);
    reqProt.printCharArrayInHex(protocol, packetLen);
//    write(sockfd, protocol, packetLen);

//    NSLog(@"packet Byte Length: %d", packetLen);
    
    //--------------------------------------------------------------------------
    // the protcol is not encrypted yet
    // the entire protcol will be encrypted below using the gerneral/global
    // pemkey (this pemkey is copied manually to the other projects temporality;
    // iOS, Android, and server) and sent to the server
    //--------------------------------------------------------------------------

    unsigned char *encryptedMessage = new unsigned char [MAX_LEN_BUFFER];

//    NSLog(@"Encrypting.........................................................................................................");
    memset(encryptedMessage, 0, MAX_LEN_BUFFER);
    int encrypted_length = crypto->encrypt((unsigned char *)protocol, packetLen, encryptedMessage);
    
    [outputStream write:(uint8_t *)encryptedMessage maxLength:encrypted_length];

    message = _textField.text;
//    NSLog(@"message: %@", message);
    
//    NSLog(@"Encrypting.........................................................................................................");
    memset(encryptedMessage, 0, MAX_LEN_BUFFER);
    encrypted_length = crypto->encrypt((unsigned char *)messageInCharPtr, strlen(messageInCharPtr), encryptedMessage);
    [_encryptedTextField setText:[NSString stringWithCString:(char *)encryptedMessage
                                                    encoding:[NSString defaultCStringEncoding]]];

    
//    NSLog(@"Decrypting.........................................................................................................");
    memset(decryptedMessage, 0, MAX_LEN_BUFFER);
    int decrypted_length = crypto->decrypt((unsigned char *)encryptedMessage, encrypted_length, decryptedMessage);
//    NSLog(@"decryptedMessage: %s", decryptedMessage);
    [_decryptedTextField setText:[NSString stringWithCString:(char *)decryptedMessage
                                                    encoding:[NSString defaultCStringEncoding]]];
}

@end
