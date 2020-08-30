================================================================================
                                    READ ME
================================================================================
Project name: 
    - metrotalk

Sub Project name: 
    - OPENSSL_IOS

Objectives:
    - Create a simple chatting client that sends and receives messages from a server.

Staff:
    - Lead programmer   : Samil Chai.
    - Junior programmer : Joon Kang.
    - [ Copy right to Samil Chai ]

Current project: []
    Start date	  : 2017-09-07
    End date  	  : ongoing
    Partial dates :

Environment:
    - Ubuntu v16.04 64 bit Virtual Box with Macbook:
	- MacBook Pro (Retina, 15-inch, 2017):
	    - System type   : 64-bit operating system, x64-based processor.
	    - Processor     : 3.1 GHz Intel Core i7.
	    - Installed RAM : 16.00 GB.
	    - Graphics card : Intel HD Graphics 630 1536 MB.
    - Virtual Box assistant version:	
	- Version  : Version 5.2.0 r118431 (Qt5.6.3)
		     Copyright © 2017 Oracle Corporation and/or its affiliates. 
Techique used:
    - Openssl API.

Sources:
    - Crypto-Example-master
    

Project documents Google Drive folder:
    - Google docs : [ https://docs.google.com/document/d/
		      1C0Qt0hNM1cxr9trSKH0jCyKSU4PV6OtPhuhkz06r9ro/edit]. 

Project document headquarter:
    - Google docs : [ https://docs.google.com/document/d/
		      1C0Qt0hNM1cxr9trSKH0jCyKSU4PV6OtPhuhkz06r9ro/edit]. 

Setup:
    - Download Xcode 
        - Version 9.2 (9C40b)
    - Create openssl libraries (libssl.a and libcrypto.a)
        - go to the openssl library folder (this project is automatically set to use 
						openssl-1.1.0-stable-SNAP-20171109) 
            - if that file does not exist download one from below and put it inside          
	      research_rsa_lib
                - https://www.openssl.org/source/ 
                - we recommend openssl-1.1.0X or openssl-1.1.0-stable-SNAP-XXXXXXXX 
        - turn on Terminal (should be in “Applications/Utilities” folder)
        - type cd “location of the openssl library you just downloaded”
            - it should be something like cd /Users/joonkang/Documents/xcode/
	      research_rsa_lib/openssl-1.1.0-stable-SNAP-20171109
        - then type the following commands
	    - if using iOS device(creates iOS Library): 
                - export C_INCLUDE_PATH=$C_INCLUDE_PATH:`pwd`/include
	        - export CPLUS_INCLUDE_PATH=$CPLUS_INCLUDE_PATH:`pwd`/include
	        - export LIBRARY_PATH=$LIBRARY_PATH:`pwd`
	        - export CROSS_COMPILE=$(xcode-select -print-path)"/Toolchains/
		  XcodeDefault.xctoolchain/usr/bin/"
	        - export CROSS_TOP=$(xcode-select -print-path)"/Platforms/
		  iPhoneOS.platform/Developer"
	        - export CROSS_SDK="iPhoneOS"$(xcrun -sdk iphoneos --show-sdk-
		  version)".sdk"
	        - ./Configure ios64-cross no-shared no-deprecated
	        - make -j8
	    - if using iOS emulator on MacOS(creates MacOS Library):
                - ./config
                - make
                - make install
	- when above is executed correctly, it will create following libraries
	    - iOS:
		- libssl.a
		- libcrypto.a 
	    - MacOS:
		- libssl.a 
		- libssl.pc
		- libssl.dylib 
		- libssl.1.1.dylib 
		- libcrypto.a
		- libcrypto.pc
		- libcrypto.dylib
	  	- libcrypto.1.1.dylib  
	- create a folder called “lib_ios” if using iOS, and “lib_mac” if using MacOS,
	  into the openssl library
        - create a folder called “static” and a folder called “dynamic”
        - drag the .a and .pc libraries into the static folder
        - drag the .dylib and .1.1.dylib libraries into the dynamic folder

	- it should look like this
	    - openssl library
		- etc files
		- lib_mac (if using MacOS)
		    - dynamic
			- libcrypto.1.1.dylib
			- libcrypto.dylib
			- libssl.1.1.dylib
			- libssl.dylib
		    - static  
			- libcrypto.a
			- libcrypto.pc
			- libssl.a
			- libssl.pc
		- lib_ios (if using iOS)
		    - dynamic
		    - static  
    - Link library paths in Xcode
	- go to research_rsa_lib/OPENSSL_IOS and open OPENSSL_IOS.xcodeproj
	- near the top left click on OPENSSL_IOS (should have a blue icon next to it)
 	- click on “Build Settings” near the top
	- find “Other Linker Flags” option under “Linking” tab and add the following
	    -  “-L../openssl-1.1.0-stable-SNAP-20171109/lib_mac/static”
	    - change “openssl-1.1.0-stable-SNAP-20171109” to the your openssl library
	    - change “lib_mac” to “lib_ios” if using iOS
    - Link include paths in Xcode
	- in the same section as above find “Other C++ Flags” under “AppleLLVM 9.0 - 
	  Custom Compiler Flags” and add the following
	    - “-I../openssl-1.1.0-stable-SNAP-20171109/include”
	    - change “openssl-1.1.0-stable-SNAP-20171109” to the your openssl library

How to run:


Note: 
    - iOS emulator on MacOS will use MacBook cpu meaning the openssl libraries have to be 
      compatible with MacOS not iOS
   

================================================================================
Directory description:
================================================================================


