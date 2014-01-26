//
//  CSVKit.h
//  CSVKit
//
//  Copyright (c) 2011 Booyah, Inc.
//
//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included
//  in all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
//
//  Authors:
//  Jon Parise <jon@booyah.com>
//

//
//  Modifications Copyright (c) 2014 Kevin Zimmerman
//
//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included
//  in all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
//
//  Authors:
//  Kevin Zimmerman <kevin@kevinz.com>
//

#ifndef _CSVKIT_H_
#define _CSVKIT_H_

#import <Foundation/NSObject.h>

@class NSArray, NSData, NSDictionary, NSError, NSString, CSVParserContext;

extern NSString * const CSVErrorDomain;
extern NSString * const CSVLineNumberKey;
extern NSString * const CSVFieldNumberKey;

typedef void (^RowBlock)(NSArray *row, NSUInteger rowIndex, BOOL *stop);
typedef void (^FieldBlock)(id value, NSUInteger index, NSUInteger rowIndex, BOOL *stop);

typedef enum
{
    CSVQuoteStyleNone = 0,              // No special quote processing
    CSVQuoteStyleMinimal,               // Only quote fields with special characters
    CSVQuoteStyleAll,                   // Quote all fields
    CSVQuoteStyleNonNumeric,            // Quote non-numeric fields; unquoted fields are floats
} CSVQuoteStyle;

typedef struct
{
    unsigned char       delimiter;          // Field separator
    unsigned char       quoteChar;          // Quote character
    unsigned char       escapeChar;         // Escape character
    BOOL                doubleQuote;        // Is " represented by ""?
    BOOL                skipInitialSpace;   // Ignore spaces following delimiter?
    BOOL                strict;             // Raise exception on bad data?
    CSVQuoteStyle       quoteStyle;         // Quoting style
}  CSVDialect;

extern const CSVDialect CSVExcelDialect;    // Excel-generated CSV data
extern const CSVDialect CSVExcelTabDialect; // Excel-generated TAB-delimited data

@interface CSVParser : NSObject

@property (strong, nonatomic) CSVParserContext *context;

+ (id)parser;
+ (id)parserWithDialect:(const CSVDialect *)dialect;

- (id)init;
- (id)initWithDialect:(const CSVDialect *)dialect;

#pragma mark Field Parsing

- (BOOL)parseFieldsFromData:(NSData *)data block:(FieldBlock)block;
- (BOOL)parseFieldsFromData:(NSData *)data block:(FieldBlock)block error:(NSError **)error;

- (BOOL)parseFieldsFromString:(NSString *)string block:(FieldBlock)block;
- (BOOL)parseFieldsFromString:(NSString *)string block:(FieldBlock)block error:(NSError **)error;

- (BOOL)parseFieldsFromUTF8String:(const unsigned char *)string length:(NSUInteger)length block:(FieldBlock)block;
- (BOOL)parseFieldsFromUTF8String:(const unsigned char *)string length:(NSUInteger)length block:(FieldBlock)block error:(NSError **)error;

#pragma mark Row Parsing

- (BOOL)parseRowsFromData:(NSData *)data block:(RowBlock)block;
- (BOOL)parseRowsFromData:(NSData *)data block:(RowBlock)block error:(NSError **)error;

- (BOOL)parseRowsFromString:(NSString *)string block:(RowBlock)block;
- (BOOL)parseRowsFromString:(NSString *)string block:(RowBlock)block error:(NSError **)error;

- (BOOL)parseRowsFromUTF8String:(const unsigned char *)string length:(NSUInteger)length block:(RowBlock)block;
- (BOOL)parseRowsFromUTF8String:(const unsigned char *)string length:(NSUInteger)length block:(RowBlock)block error:(NSError **)error;

#pragma mark Convenience Methods

- (NSArray *)rowsFromData:(NSData *)data;
- (NSArray *)rowsFromData:(NSData *)data error:(NSError **)error;

- (NSArray *)rowsFromString:(NSString *)string;
- (NSArray *)rowsFromString:(NSString *)string error:(NSError **)error;

- (NSArray *)rowsFromUTF8String:(const unsigned char *)string length:(NSUInteger)length;
- (NSArray *)rowsFromUTF8String:(const unsigned char *)string length:(NSUInteger)length error:(NSError **)error;

@end

@interface CSVObjectParser : CSVParser
{
}

@property (nonatomic,retain) Class objectClass;
@property (nonatomic,retain) NSArray *propertyNames;

+ (id)parserWithDialect:(const CSVDialect *)dialect classClass:(Class)objectClass propertyNames:(NSArray *)propertyNames;
- (id)initWithDialect:(const CSVDialect *)dialect objectClass:(Class)objectClass propertyNames:(NSArray *)propertyNames;

#pragma mark Object Parsing

- (BOOL)parseObjectsFromData:(NSData *)data block:(void (^)(id object, BOOL *stop))block;
- (BOOL)parseObjectsFromData:(NSData *)data block:(void (^)(id object, BOOL *stop))block error:(NSError **)error;

- (BOOL)parseObjectsFromString:(NSString *)string block:(void (^)(id object, BOOL *stop))block;
- (BOOL)parseObjectsFromString:(NSString *)string block:(void (^)(id object, BOOL *stop))block error:(NSError **)error;

- (BOOL)parseObjectsFromUTF8String:(const unsigned char *)string length:(NSUInteger)length block:(void (^)(id object, BOOL *stop))block;
- (BOOL)parseObjectsFromUTF8String:(const unsigned char *)string length:(NSUInteger)length block:(void (^)(id object, BOOL *stop))block error:(NSError **)error;

#pragma mark Convenience Methods

- (NSArray *)objectsFromData:(NSData *)data;
- (NSArray *)objectsFromData:(NSData *)data error:(NSError **)error;

- (NSArray *)objectsFromString:(NSString *)string;
- (NSArray *)objectsFromString:(NSString *)string error:(NSError **)error;

- (NSArray *)objectsFromUTF8String:(const unsigned char *)string length:(NSUInteger)length;
- (NSArray *)objectsFromUTF8String:(const unsigned char *)string length:(NSUInteger)length error:(NSError **)error;

@end

#endif // _CSVKIT_H_ 
