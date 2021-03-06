//
//  SJVideoPlayer.h
//  SJVideoPlayerProject
//
//  Created by 畅三江 on 2018/5/29.
//  Copyright © 2018年 畅三江. All rights reserved.
//

#import "SJBaseVideoPlayer.h"
#import "SJVideoPlayerSettings.h"
#import "SJVideoPlayerMoreSetting.h"
#import "SJVideoPlayerURLAsset+SJControlAdd.h"
#import "SJVideoPlayerMoreSettingSecondary.h"
#import "SJFilmEditingResultShareItem.h"
#import "SJLightweightTopItem.h"
#import "SJVideoPlayerFilmEditingCommonHeader.h"
#import "SJVideoPlayerFilmEditingConfig.h"
#import "SJControlLayerSwitcher.h"

NS_ASSUME_NONNULL_BEGIN
/// 这两个标识是默认控制层的标识. 可以像下面这样扩展您的标识, 将相应的控制层加入到switcher(切换器)中, 通过switcher进行切换.
/// SJControlLayerIdentifier YourControlLayerIdentifier;
/// 当然, 也可以直接将默认的标识控制层, 替换成您的控制层.

extern SJControlLayerIdentifier SJControlLayer_Edge;
extern SJControlLayerIdentifier SJControlLayer_FilmEditing;


@interface SJVideoPlayer : SJBaseVideoPlayer

/// 使用默认的控制层
+ (instancetype)player;

/// A lightweight player with simple functions.
/// 一个具有简单功能的播放器.
+ (instancetype)lightweightPlayer;

/// 使用默认的控制层
- (instancetype)init;

- (instancetype)_init;

/// v2.0.8
/// 新增: 控制层 切换器, 管理控制层的切换
@property (nonatomic, strong, readonly) SJControlLayerSwitcher *switcher;

/// This block invoked when clicked back btn, if videoPlayer.isFullscreen == NO.
/// 点击`返回`按钮的回调
@property (null_resettable, nonatomic, copy) void(^clickedBackEvent)(SJVideoPlayer *player);

/// Player will prompt the user when the network status changes, if disableNetworkStatusChangePrompt == NO;
/// 是否禁止网络状态变化时的提示, 默认是NO.
@property (nonatomic) BOOL disableNetworkStatusChangePrompt;

+ (NSString *)version;

@end


/// 配置`播放器图片或slider的颜色等`
@interface SJVideoPlayer (CommonSettings)
/// Configure the player, Note: This `block` is run on the child thread.
/// 配置播放器, 例如: 滚动条的颜色等... 注意: 这个`block`在子线程运行
///
/// SJVideoPlayer.update(^(SJVideoPlayerSettings * _Nonnull commonSettings) {
///     ..... setting player ......
///     commonSettings.placeholder = [UIImage imageNamed:@"placeholder"];
///     commonSettings.more_trackColor = [UIColor whiteColor];
///     commonSettings.progress_trackColor = [UIColor colorWithWhite:0.4 alpha:1];
///     commonSettings.progress_bufferColor = [UIColor whiteColor];
/// });
@property (class, nonatomic, copy, readonly) void(^update)(void(^block)(SJVideoPlayerSettings *commonSettings));
+ (void)resetSetting; // 重置配置, 恢复默认设置
@end


/// 配置`轻量级的控制层`
@interface SJVideoPlayer (SettingLightweightControlLayer)

/// 配置top控制层上的item
@property (nonatomic, copy, nullable) NSArray<SJLightweightTopItem *> *topControlItems;

/// 点击item执行的block
@property (nonatomic, copy, nullable) void(^clickedTopControlItemExeBlock)(SJVideoPlayer *player, SJLightweightTopItem *item);

@end


/// 配置`默认的控制层`
@interface SJVideoPlayer (SettingDefaultControlLayer)

/// Whether to generate a preview view. default is YES.
/// 是否自动生成预览视图, 默认是 YES
@property (nonatomic) BOOL generatePreviewImages;

/// clicked More button to display items.
/// 点击`更多(右上角的三个点)`按钮, 弹出来的选项.
@property (nonatomic, strong, nullable) NSArray<SJVideoPlayerMoreSetting *> *moreSettings;

@end


/// 配置`剪辑的控制层`
@interface SJVideoPlayer (FilmEditing)

/// The player will display the right control view if YES
/// If the format of the video is m3u8, it does not work
///
/// 是否开启剪辑功能
/// 默认是NO
/// 不支持剪辑m3u8(如果开启, 将会自动隐藏剪辑按钮)
@property (nonatomic) BOOL enableFilmEditing;

/// 剪辑功能配置
@property (nonatomic, strong, readonly) SJVideoPlayerFilmEditingConfig *filmEditingConfig;

- (void)dismissFilmEditingViewCompletion:(void(^__nullable)(SJVideoPlayer *player))completionBlock;
@end

NS_ASSUME_NONNULL_END
