// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_RENDERER_HOST_CHROME_RENDER_WIDGET_HOST_VIEW_MAC_HISTORY_SWIPER_
#define CHROME_BROWSER_RENDERER_HOST_CHROME_RENDER_WIDGET_HOST_VIEW_MAC_HISTORY_SWIPER_

#import <Cocoa/Cocoa.h>

namespace blink {
class WebMouseWheelEvent;
}

@class HistorySwiper;
@protocol HistorySwiperDelegate
- (BOOL)shouldAllowHistorySwiping;
- (NSView*)viewThatWantsHistoryOverlay;
@end

namespace history_swiper {
enum NavigationDirection {
  kBackwards = 0,
  kForwards,
};
enum RecognitionState {
  
  
  
  
  
  kPending,
  
  
  
  kPotential,
  
  
  
  kTracking,
  
  
  kCompleted,
  
  
  kCancelled,
};
} 

@class HistoryOverlayController;
@interface HistorySwiper : NSObject {
 @private
  
  HistoryOverlayController* historyOverlay_;
  
  
  int currentGestureId_;
  
  NSPoint gestureStartPoint_;
  
  NSPoint gestureCurrentPoint_;
  
  
  BOOL inGesture_;
  
  BOOL receivingTouches_;
  
  
  int gestureStartPointValid_;
  
  int lastProcessedGestureId_;
  
  history_swiper::NavigationDirection historySwipeDirection_;
  
  BOOL historySwipeDirectionInverted_;

  
  
  BOOL beganEventUnconsumed_;
  history_swiper::RecognitionState recognitionState_;

  id<HistorySwiperDelegate> delegate_;

  
  
  NSSize mouseScrollDelta_;
}

- (BOOL)handleEvent:(NSEvent*)event;
- (void)rendererHandledWheelEvent:(const blink::WebMouseWheelEvent&)event
                         consumed:(BOOL)consumed;

- (void)touchesBeganWithEvent:(NSEvent*)event;
- (void)touchesMovedWithEvent:(NSEvent*)event;
- (void)touchesCancelledWithEvent:(NSEvent*)event;
- (void)touchesEndedWithEvent:(NSEvent*)event;
- (void)beginGestureWithEvent:(NSEvent*)event;
- (void)endGestureWithEvent:(NSEvent*)event;

- (BOOL)canRubberbandLeft:(NSView*)view;
- (BOOL)canRubberbandRight:(NSView*)view;

- (id)initWithDelegate:(id<HistorySwiperDelegate>)delegate;

@property (nonatomic, assign) id<HistorySwiperDelegate> delegate;

@end

@interface HistorySwiper (PrivateExposedForTesting)
+ (void)resetMagicMouseState;
@end

#endif 
