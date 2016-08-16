// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef CC_BASE_SWITCHES_H_
#define CC_BASE_SWITCHES_H_

#include "cc/base/cc_export.h"


namespace cc {
namespace switches {

CC_EXPORT extern const char kDisableThreadedAnimation[];
CC_EXPORT extern const char kDisableCompositedAntialiasing[];
CC_EXPORT extern const char kDisableMainFrameBeforeDraw[];
CC_EXPORT extern const char kDisableMainFrameBeforeActivation[];
CC_EXPORT extern const char kEnableMainFrameBeforeActivation[];
CC_EXPORT extern const char kEnableTopControlsPositionCalculation[];
CC_EXPORT extern const char kJankInsteadOfCheckerboard[];
CC_EXPORT extern const char kTopControlsHeight[];
CC_EXPORT extern const char kTopControlsHideThreshold[];
CC_EXPORT extern const char kTopControlsShowThreshold[];
CC_EXPORT extern const char kSlowDownRasterScaleFactor[];
CC_EXPORT extern const char kCompositeToMailbox[];
CC_EXPORT extern const char kMaxTilesForInterestArea[];
CC_EXPORT extern const char kMaxUnusedResourceMemoryUsagePercentage[];
CC_EXPORT extern const char kEnablePinchVirtualViewport[];
CC_EXPORT extern const char kDisablePinchVirtualViewport[];
CC_EXPORT extern const char kStrictLayerPropertyChangeChecking[];

CC_EXPORT extern const char kUIDisablePartialSwap[];
CC_EXPORT extern const char kEnableGpuBenchmarking[];

CC_EXPORT extern const char kShowCompositedLayerBorders[];
CC_EXPORT extern const char kUIShowCompositedLayerBorders[];
CC_EXPORT extern const char kShowFPSCounter[];
CC_EXPORT extern const char kUIShowFPSCounter[];
CC_EXPORT extern const char kShowLayerAnimationBounds[];
CC_EXPORT extern const char kUIShowLayerAnimationBounds[];
CC_EXPORT extern const char kShowPropertyChangedRects[];
CC_EXPORT extern const char kUIShowPropertyChangedRects[];
CC_EXPORT extern const char kShowSurfaceDamageRects[];
CC_EXPORT extern const char kUIShowSurfaceDamageRects[];
CC_EXPORT extern const char kShowScreenSpaceRects[];
CC_EXPORT extern const char kUIShowScreenSpaceRects[];
CC_EXPORT extern const char kShowReplicaScreenSpaceRects[];
CC_EXPORT extern const char kUIShowReplicaScreenSpaceRects[];
CC_EXPORT extern const char kShowOccludingRects[];
CC_EXPORT extern const char kUIShowOccludingRects[];
CC_EXPORT extern const char kShowNonOccludingRects[];
CC_EXPORT extern const char kUIShowNonOccludingRects[];

CC_EXPORT extern const char kCCLayerTreeTestNoTimeout[];
CC_EXPORT extern const char kCCRebaselinePixeltests[];

}  
}  

#endif  
