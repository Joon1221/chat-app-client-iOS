//
//  ViewController.h
//  OPENSSL_IOS
//
//  Created by Joon Kang on 2017-10-28.
//  Copyright © 2017 Joon Kang. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController <NSStreamDelegate>

@property (weak, nonatomic) IBOutlet UITextField *textField;
@property (weak, nonatomic) IBOutlet UITextField *encryptedTextField;
@property (weak, nonatomic) IBOutlet UITextField *decryptedTextField;
@property (weak, nonatomic) IBOutlet UITextView *chatMessages;

- (void)stream:(NSStream *)stream handleEvent:(NSStreamEvent)event;

@end

