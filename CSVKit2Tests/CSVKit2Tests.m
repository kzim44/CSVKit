//
//  CSVKit2Tests.m
//  CSVKit2Tests
//
//  Created by kevin on 1/25/14.
//  Copyright (c) 2014 Kevin Zimmerman. All rights reserved.
//

#import <XCTest/XCTest.h>

@interface CSVKit2Tests : XCTestCase

@end

@implementation CSVKit2Tests

- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testExample
{
    XCTFail(@"No implementation for \"%s\"", __PRETTY_FUNCTION__);
}

//- (void)testErrorDetails
//{
//    NSString *badString = [[NSString alloc] initWithBytes:"a,\0\0" length:4 encoding:NSASCIIStringEncoding];
//    
//    NSError *error = nil;
//    [[CSVParser parser] rowsFromString:badString error:&error];
//    
//    STAssertEqualObjects([error domain], CSVErrorDomain, nil);
//    
//    NSDictionary *details = [error userInfo];
//    STAssertEquals([[details objectForKey:CSVLineNumberKey] unsignedLongValue], 1UL, nil);
//    STAssertEquals([[details objectForKey:CSVFieldNumberKey] longValue], 1L, nil);
//    
//    [badString release];
//}
//
//#pragma mark Fields
//
//- (void)testFields
//{
//    NSMutableArray *array = [[NSMutableArray alloc] init];
//    __block BOOL sawSentinel = NO;
//    
//    NSError *error = nil;
//    [[CSVParser parser] parseFieldsFromString:@"a,b,c\n" block:^(id value, NSUInteger index, BOOL *stop) {
//        if (index == NSUIntegerMax)
//        {
//            sawSentinel = YES;
//        }
//        else if (value)
//        {
//            [array addObject:value];
//        }
//    } error:&error];
//    
//    STAssertNil(error, nil);
//    STAssertTrue(sawSentinel, nil);
//    STAssertEquals(array.count, (NSUInteger)3, nil);
//    
//    [array release];
//}
//
//#pragma mark Rows
//
//- (void)testRows
//{
//    NSArray *array = [[CSVParser parser] rowsFromString:@"one,two,three\n1,2,3"];
//    STAssertEquals(array.count, (NSUInteger)2, nil);
//    
//    NSArray *row = [array objectAtIndex:0];
//    STAssertEquals(row.count, (NSUInteger)3, nil);
//    STAssertEqualObjects([row objectAtIndex:0], @"one", nil);
//}
//
//#pragma mark Objects
//
//- (void)testObjects
//{
//    NSArray *array = [[CSVObjectParser parser] objectsFromString:@"one,two,three\n1,2,3"];
//    STAssertEquals(array.count, (NSUInteger)1, nil);
//    
//    NSDictionary *dict = [array objectAtIndex:0];
//    STAssertEquals(dict.count, (NSUInteger)3, nil);
//    STAssertEqualObjects([dict objectForKey:@"one"], @"1", nil);
//}
//

@end
