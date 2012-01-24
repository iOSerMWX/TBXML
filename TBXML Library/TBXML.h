// ================================================================================================
//  TBXML.h
//  Fast processing of XML files
//
// ================================================================================================
//  Created by Tom Bradley on 21/10/2009.
//  Version 1.5
//  
//  Copyright 2012 71Squared All rights reserved.
//  
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//  
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//  
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
// ================================================================================================

@class TBXML;

// ================================================================================================
//  Block Callbacks
// ================================================================================================
typedef void (^TBXMLSuccessBlock)(TBXML *);
typedef void (^TBXMLFailureBlock)(TBXML *, NSError *);


// ================================================================================================
//  Error Codes
// ================================================================================================
#define D_TBXML_DATA_NIL 100
#define D_TBXML_DATA_NIL_TEXT @"data is nil"

#define D_TBXML_DECODE_FAILURE 101
#define D_TBXML_DECODE_FAILURE_TEXT @"decode failure"

#define D_TBXML_MEMORY_ALLOC_FAILURE 102
#define D_TBXML_MEMORY_ALLOC_FAILURE_TEXT @"unable to allocate memory"

#define D_TBXML_ROOT_NOT_FOUND 103
#define D_TBXML_ROOT_NOT_FOUND_TEXT @"document root not found"

#define D_TBXML_FILE_NOT_FOUND_IN_BUNDLE 104
#define D_TBXML_FILE_NOT_FOUND_IN_BUNDLE_TEXT @"file not found in bundle"



// ================================================================================================
//  Defines
// ================================================================================================
#define D_TBXML_DOMAIN @"com.71squared.tbxml"

#define MAX_ELEMENTS 100
#define MAX_ATTRIBUTES 100

#define TBXML_ATTRIBUTE_NAME_START 0
#define TBXML_ATTRIBUTE_NAME_END 1
#define TBXML_ATTRIBUTE_VALUE_START 2
#define TBXML_ATTRIBUTE_VALUE_END 3
#define TBXML_ATTRIBUTE_CDATA_END 4

// ================================================================================================
//  Structures
// ================================================================================================
typedef struct _TBXMLAttribute {
	char * name;
	char * value;
	struct _TBXMLAttribute * next;
} TBXMLAttribute;

typedef struct _TBXMLElement {
	char * name;
	char * text;
	
	TBXMLAttribute * firstAttribute;
	
	struct _TBXMLElement * parentElement;
	
	struct _TBXMLElement * firstChild;
	struct _TBXMLElement * currentChild;
	
	struct _TBXMLElement * nextSibling;
	struct _TBXMLElement * previousSibling;
	
} TBXMLElement;

typedef struct _TBXMLElementBuffer {
	TBXMLElement * elements;
	struct _TBXMLElementBuffer * next;
	struct _TBXMLElementBuffer * previous;
} TBXMLElementBuffer;

typedef struct _TBXMLAttributeBuffer {
	TBXMLAttribute * attributes;
	struct _TBXMLAttributeBuffer * next;
	struct _TBXMLAttributeBuffer * previous;
} TBXMLAttributeBuffer;

// ================================================================================================
//  TBXML Public Interface
// ================================================================================================
@interface TBXML : NSObject {
	
@private
	TBXMLElement * rootXMLElement;
	
	TBXMLElementBuffer * currentElementBuffer;
	TBXMLAttributeBuffer * currentAttributeBuffer;
	
	long currentElement;
	long currentAttribute;
	
	char * bytes;
	long bytesLength;
}

@property (nonatomic, readonly) TBXMLElement * rootXMLElement;

+ (id)tbxmlWithXMLString:(NSString*)aXMLString __attribute__((deprecated));
+ (id)tbxmlWithXMLString:(NSString*)aXMLString error:(NSError **)error;
+ (id)tbxmlWithXMLData:(NSData*)aData __attribute__((deprecated));
+ (id)tbxmlWithXMLData:(NSData*)aData error:(NSError **)error;
+ (id)tbxmlWithXMLFile:(NSString*)aXMLFile __attribute__((deprecated));
+ (id)tbxmlWithXMLFile:(NSString*)aXMLFile error:(NSError **)error;
+ (id)tbxmlWithXMLFile:(NSString*)aXMLFile fileExtension:(NSString*)aFileExtension __attribute__((deprecated));
+ (id)tbxmlWithXMLFile:(NSString*)aXMLFile fileExtension:(NSString*)aFileExtension error:(NSError **)error;


- (id)initWithXMLString:(NSString*)aXMLString __attribute__((deprecated));
- (id)initWithXMLString:(NSString*)aXMLString error:(NSError **)error;
- (id)initWithXMLData:(NSData*)aData __attribute__((deprecated));
- (id)initWithXMLData:(NSData*)aData error:(NSError **)error;
- (id)initWithXMLFile:(NSString*)aXMLFile __attribute__((deprecated));
- (id)initWithXMLFile:(NSString*)aXMLFile error:(NSError **)error;
- (id)initWithXMLFile:(NSString*)aXMLFile fileExtension:(NSString*)aFileExtension __attribute__((deprecated));
- (id)initWithXMLFile:(NSString*)aXMLFile fileExtension:(NSString*)aFileExtension error:(NSError **)error;


- (NSError *) decodeData:(NSData*)data;

@end

// ================================================================================================
//  TBXML Static Functions Interface
// ================================================================================================

@interface TBXML (StaticFunctions)

+ (NSString*) elementName:(TBXMLElement*)aXMLElement;
+ (NSString*) textForElement:(TBXMLElement*)aXMLElement;
+ (NSString*) valueOfAttributeNamed:(NSString *)aName forElement:(TBXMLElement*)aXMLElement;

+ (NSString*) attributeName:(TBXMLAttribute*)aXMLAttribute;
+ (NSString*) attributeValue:(TBXMLAttribute*)aXMLAttribute;

+ (TBXMLElement*) nextSiblingNamed:(NSString*)aName searchFromElement:(TBXMLElement*)aXMLElement;
+ (TBXMLElement*) childElementNamed:(NSString*)aName parentElement:(TBXMLElement*)aParentXMLElement;

@end