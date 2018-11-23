//
//  ViewController.m
//  youdaoTranslate
//
//  Created by dan on 2018/11/22.
//  Copyright © 2018年 shan. All rights reserved.
//

#import "ViewController.h"
#import "FanYiSDK.h"

@interface ViewController ()
@property(nonatomic,strong) YDTranslateRequest *translateRequest;
@property(nonatomic,assign) int i ;
@property(nonatomic,strong)NSString* lastindex;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    YDTranslateInstance *yd = [YDTranslateInstance sharedInstance];
    yd.appKey = @"";//你的appkey 也就是应用ID，注意修改bundleID
   
    
    NSString *txtPath = @"/Users/dan/Desktop/test.txt";
    
    NSError *error;
    NSString *resultString = [NSString stringWithContentsOfFile:txtPath encoding:NSUTF8StringEncoding error:&error];
    NSLog(@"%@", resultString);
    
    NSArray *strNarray = [resultString componentsSeparatedByString:@"\n"];
    
     self.translateRequest = [YDTranslateRequest request];
    
    YDTranslateParameters *parameters =
    [YDTranslateParameters targeting];
    parameters.source = @"demo";
    parameters.from = YDLanguageTypeEnglish;
    parameters.to = YDLanguageTypeChinese;
    self.translateRequest.translateParameters = parameters;
    
    

    NSMutableArray *array  =  [NSMutableArray array];
    for (NSUInteger index = 0; index < strNarray.count; index++) {
        NSString *subStr = strNarray[index] ;
        if (subStr.length==0) {
            continue;
        }
        else if([subStr hasPrefix:@"!["]){
            dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(5*index * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
                [self writefile:subStr];
            });
            continue;
        }
        [array insertObject:@(index) atIndex:0];
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(5*index * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            [self.translateRequest lookup:subStr WithCompletionHandler:^(YDTranslateRequest *request, YDTranslate *translte, NSError *error) {
                if (error) {
                    NSString *des = [error.userInfo objectForKey:NSLocalizedDescriptionKey];
                    NSLog(@"出错了1 ================> %ld%@", (long)error.code,des);
                    
                }
                else {
                    if (!translte.translation.count) {
                        NSLog(@"出错了2 ================> 没有结果");
                        return;
                    }
                    NSString *fanyi = translte.translation[0];
                    if(fanyi == nil){
                        NSLog(@"出错了3 ================> 结果为空");
                        return;
                    }
                    NSString *wreiteStr = [translte.query stringByAppendingString:@"\n"];
                    wreiteStr = [wreiteStr stringByAppendingString:fanyi];
                    [self writefile:wreiteStr];
    
                }
                
                NSLog(@"任务%lu结束",(unsigned long)index);
                NSNumber *ll = [array firstObject];
                if (index == [ll unsignedLongValue]) {
                    NSLog(@"全部任务结束");
                }
            }];
        });
    }
}

- (void)writefile:(NSString *)string{
    NSString *filePath = @"/Users/dan/Desktop/test1.txt";//[homePath stringByAppendingPathComponent:@"testfile.text"];
    
    NSFileManager *fileManager = [NSFileManager defaultManager];
    
    if(![fileManager fileExistsAtPath:filePath]){
        NSString *str = @"\n";
        [str writeToFile:filePath atomically:YES encoding:NSUTF8StringEncoding error:nil];
    }
    
    NSFileHandle *fileHandle = [NSFileHandle fileHandleForUpdatingAtPath:filePath];
    
    [fileHandle seekToEndOfFile];  //将节点跳到文件的末尾
    string = [string stringByAppendingString:@"\n\n"];
    NSData* stringData  = [string dataUsingEncoding:NSUTF8StringEncoding];
    
    [fileHandle writeData:stringData]; //追加写入数据
    
    [fileHandle closeFile];
}


@end
