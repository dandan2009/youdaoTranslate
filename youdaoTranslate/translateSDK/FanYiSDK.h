//
//  FanYiSDK.h
//  FanYiSDK
//
//  Created by 白静 on 11/18/16.
//  Copyright © 2016 网易有道. All rights reserved.
//

#import <Foundation/Foundation.h>
@class YDTranslate;
@class YDTranslateRequest;
@class YDTranslateParameters;


#pragma mark - 在线查词
typedef void(^YDTranslateRequestHandler)(YDTranslateRequest *request,
                                         YDTranslate *translte,
                                         NSError *error) ;

@interface YDTranslateRequest : NSObject

@property (nonatomic, strong) YDTranslateParameters *translateParameters;
@property (nonatomic, strong) NSArray *supportLanguages;

+ (YDTranslateRequest *)request;

//查询
- (void)lookup:(NSString *) input WithCompletionHandler:(YDTranslateRequestHandler)handler;
//词库初始化，词库放工程中
- (BOOL) initOffline;
//词库初始化，指定词库目录
- (BOOL) initOfflineWithPath:(NSString *)path;
@end

@class CLLocation;

/**
 * The `YDTranslateParameters` class is used to attach targeting information to
 * `YDTranslateRequest` objects.
 */

@interface YDTranslateParameters : NSObject

typedef NS_ENUM(NSInteger, YDLanguageType) {
    YDLanguageTypeAuto = 0,
    YDLanguageTypeChinese, //中文
    YDLanguageTypeEnglish, //英文
    YDLanguageTypeJapanese, //日文
    YDLanguageTypeKorean, //韩文
    YDLanguageTypeFrench, //法文
    YDLanguageTypeRussian, //俄文
    YDLanguageTypePortuguese, //葡萄牙文
    YDLanguageTypeSpanish, //西班牙文
    YDLanguageTypeVietnamese, //越南文
    YDLanguageTypeChineseT, //中文繁体
    YDLanguageTypeGerman, //德文
    YDLanguageTypeArabic, //阿拉伯文
    YDLanguageTypeIndonesian //印尼文
};

/** @name Creating a Targeting Object */

/**
 * Creates and returns an empty YDTranslateParameters object.
 *
 * @return A newly initialized YDTranslateParameters object.
 */
+ (YDTranslateParameters *)targeting;

@property (nonatomic, copy) NSString *source;

@property (nonatomic, assign) YDLanguageType from;

@property (nonatomic, assign) YDLanguageType to;

@property (nonatomic, assign) BOOL offLine;

@end

@interface YDTranslate : NSObject

@property (retain,nonatomic)NSString *query;
@property (retain,nonatomic)NSString *usPhonetic;
@property (retain,nonatomic)NSString *ukPhonetic;
@property (retain,nonatomic)NSString *phonetic;

@property (retain,nonatomic)NSArray *translation;
@property (retain,nonatomic)NSArray *explains;
@property (retain,nonatomic)NSArray *webExplains;

@property (retain,nonatomic)NSString *from;
@property (retain,nonatomic)NSString *to;
@property (retain,nonatomic)NSString *l; //针对国内请求，服务器新增l字段（查询from和to）
@property (retain,nonatomic)NSDictionary *webdict;//针对海外请求，服务器新增webdict字段（词典海外web页面）
@property (retain,nonatomic)NSDictionary *dict;
@property (retain,nonatomic)NSString *tspeakurl;
@property (retain,nonatomic)NSString *speakurl;

@property (assign,atomic)int errorCodes;

- (void)openMore;
- (void)formData;

@end

@interface YDWebExplain : NSObject

@property (retain,nonatomic)NSArray *value;
@property (retain,nonatomic)NSString *key;

- (void)formData:(NSDictionary *) dict;
@end




#pragma mark - 离线查词
@class YDTranslate;
@class YDWordOfflineTranslate;

typedef void(^YDWordOfflineTranslateHandler)(YDWordOfflineTranslate *request,
                                             YDTranslate *translte,
                                             NSError *error) ;

@interface YDWordOfflineTranslate : NSObject


+ (YDWordOfflineTranslate *)request;

//查询
- (void)lookup:(NSString *) input WithCompletionHandler:(YDWordOfflineTranslateHandler)handler;
//词库初始化，词库放工程中
- (BOOL) initOffline;
//词库初始化，指定词库目录
- (BOOL) initOfflineWithPath:(NSString *)path;
@end


#pragma mark - 全局设置
@interface YDTranslateInstance : NSObject

+ (YDTranslateInstance*)sharedInstance;

@property (nonatomic, copy) NSString *appKey;
/**
 有道SDK的数据库存储路径，默认为document路径
 */
@property (nonatomic, copy) NSString *ydDBPath;
@property (nonatomic, assign) BOOL isHaiWai;
@property (nonatomic, assign) BOOL isTestMode;
@end



#pragma mark - 汉语词典
@class YDTranslate;
@class YDHanyucidianOfflineTranslate;

typedef void(^YDHanyucidianOfflineTranslateHandler)(YDHanyucidianOfflineTranslate *request,
                                                    NSArray *translte,
                                                    NSError *error) ;

@interface YDHanyucidianOfflineTranslate : NSObject


+ (YDHanyucidianOfflineTranslate *)request;

//查询
- (void)lookup:(NSString *)input WithCompletionHandler:(YDHanyucidianOfflineTranslateHandler)handler;
//词库初始化，指定词库目录
- (BOOL) initOfflineWithPath:(NSString *)path;

@end


@interface YDChDictMeans : NSObject

@property (retain,nonatomic)NSArray *examLines;
@property (retain,nonatomic)NSString *translate;

@end

@interface YDChDictTranslate : NSObject

@property (retain,nonatomic)NSString *query;
@property (retain,nonatomic)NSString *phonetic;

@property (retain,nonatomic)NSArray *translations;

@property (assign,atomic)int errorCodes;

- (void)openMore;
@end

@interface YDExamLine : NSObject

@property (nonatomic, assign)BOOL highlight;
@property (retain,nonatomic)NSString *text;

@end



#pragma mark - 离线句子翻译
@class YDTranslate;
@class YDSentenceOfflineTranslate;

typedef void(^YDSentenceOfflineTranslateHandler)(YDSentenceOfflineTranslate *request,
                                                 YDTranslate *translte,
                                                 NSError *error) ;

@interface YDSentenceOfflineTranslate : NSObject


+ (YDSentenceOfflineTranslate *)request;

//查询
- (void)lookup:(NSString *) input WithCompletionHandler:(YDSentenceOfflineTranslateHandler)handler;
//词库初始化，指定词库目录
- (BOOL) initOfflineSenWithPath:(NSString *)path;
@end

#pragma mark - 在线语音翻译
@class YDSpeechOnlineParam, YDSpeechResult, YDSpeechOnlineRequest;

typedef void(^YDSpeechOnlineRequestHandler)(YDSpeechOnlineRequest *request,YDSpeechResult *result, NSError *error) ;

@interface YDSpeechOnlineRequest : NSObject
@property (nonatomic, strong) YDSpeechOnlineParam *param;
+ (instancetype)request;
//查询
- (void)lookup:(NSString *)input WithCompletionHandler:(YDSpeechOnlineRequestHandler)handler;
@end

@interface YDSpeechResult : NSObject
/* 翻译结果发音地址，翻译成功一定存在 */
@property (nonatomic, copy) NSString *tSpeakUrl;
/* 翻译结果错误码，一定存在 */
@property (nonatomic, copy) NSString *errorCode;
/* 源语言文本，翻译成功一定存在 */
@property (nonatomic, copy) NSString *query;
/* 翻译结果，翻译成功一定存在 */
@property (nonatomic, strong) NSArray *translation;
/* 词典deeplink */
@property (nonatomic, strong) NSDictionary *dict;
/* 词典web deeplink */
@property (nonatomic, strong) NSDictionary *webdict;
/* 源语言发音地址，翻译成功一定存在 */
@property (nonatomic, copy) NSString *speakUrl;

+ (instancetype)initWithDict:(NSDictionary *)info;
@end

@interface YDSpeechOnlineParam : NSObject
/* 源语言 */
@property (nonatomic, copy) NSString *from;
/* 目标语言 */
@property (nonatomic, copy) NSString *to;
/* 采样率 */
@property (nonatomic, copy) NSString *rate;
/* 声道数，仅支持单声道，请填写固定值1 */
@property (nonatomic, copy) NSString *channel;
/* 翻译结果发音 */
@property (nonatomic, copy) NSString *voice;
+ (instancetype)param;
@end

#pragma mark - 在线语音识别

@class YDSpeechRecognitionParam, YDSpeechRecognitionResult, YDSpeechRecognitionRequest;

typedef void(^YDSpeechRecognitionRequestHandler)(YDSpeechRecognitionRequest *request,YDSpeechRecognitionResult *result, NSError *error) ;

@interface YDSpeechRecognitionRequest : NSObject
@property (nonatomic, strong) YDSpeechRecognitionParam *param;
+ (instancetype)request;
//查询
- (void)lookup:(NSString *)input WithCompletionHandler:(YDSpeechRecognitionRequestHandler)handler;
@end

@interface YDSpeechRecognitionParam : NSObject
/* 源语言类型 */
@property (nonatomic, copy) NSString *langType;
/* 采样率 */
@property (nonatomic, copy) NSString *rate;
/* 声道数，仅支持单声道，请填写固定值1 */
@property (nonatomic, copy) NSString *channel;
/* 类别，固定值1 */
@property (nonatomic, copy) NSString *type;
+ (instancetype)param;
@end

@interface YDSpeechRecognitionResult : NSObject
/* 识别结果 */
@property (nonatomic, copy) NSArray *result;
/* 翻译结果错误码，一定存在 */
@property (nonatomic, copy) NSString *errorCode;

+ (instancetype)initWithDict:(NSDictionary *)info;
@end

#pragma mark - 在线图片翻译
@interface YDOCRTransResult : NSObject
/* 错误码 */
@property (nonatomic, copy) NSString *errorCode;
/* ocr所识别出来认为的图片中的语言 */
@property (nonatomic, copy) NSString *lanFrom;
/* 目标语言 */
@property (nonatomic, copy) NSString *lanTo;
/* 图片所对应的方向 */
@property (nonatomic, copy) NSString *orientation;
/* 图片翻译的具体内容 */
@property (nonatomic, strong) NSArray *resRegions;
/* 图片的倾斜角度 */
@property (nonatomic, copy) NSString *textAngle;
/* 原始数据 */
@property (nonatomic, strong) NSDictionary *info;

+ (instancetype)initWithDict:(NSDictionary *)info;
@end

@interface YDOCRTransRegion : NSObject
/* 区域范围，四个值：左上角的x值，左上角的y值，区域的的宽，区域的高，例如：134,0,1066,249 */
@property (nonatomic, copy) NSString *boundingBox;
/* 该区域的原文 */
@property (nonatomic, copy) NSString *context;
/* 行高 */
@property (nonatomic, copy) NSString *lineheight;
/* 行数（用于前端排版） */
@property (nonatomic, copy) NSString *linesCount;
/* 翻译结果 */
@property (nonatomic, copy) NSString *tranContent;
/* 行间距 */
@property (nonatomic, copy) NSString *linespace;

+ (instancetype)initWithDict:(NSDictionary *)info;
@end

@interface YDOCRTransParameter : NSObject
/* 文件上传类型，目前支持base64（1）和图片上传方式（2） */
@property (nonatomic, copy) NSString *type;
/* 源语言 */
@property (nonatomic, copy) NSString *from;
/* 目标语言 */
@property (nonatomic, copy) NSString *to;
+ (instancetype)param;
@end

@class YDOCRTransRequest, YDOCRTransParameter, YDOCRTransResult;

typedef void(^YDOCRTransRequestHandler)(YDOCRTransRequest *request,YDOCRTransResult *result, NSError *error) ;

@interface YDOCRTransRequest : NSObject
@property (nonatomic, strong) YDOCRTransParameter *param;
+ (instancetype)request;
//查询
- (void)lookup:(NSString *)input WithCompletionHandler:(YDOCRTransRequestHandler)handler;
@end
