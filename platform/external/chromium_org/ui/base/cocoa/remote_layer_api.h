// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_COCOA_REMOTE_LAYER_API_H_
#define UI_BASE_COCOA_REMOTE_LAYER_API_H_

#if defined(__OBJC__)
#import <Cocoa/Cocoa.h>
#endif  

#include "ui/base/ui_base_export.h"

extern "C" {
typedef uint32_t CGSConnectionID;
CGSConnectionID CGSMainConnectionID(void);
};

typedef uint32_t CAContextID;

#if defined(__OBJC__)

@interface CAContext : NSObject
+ (id)contextWithCGSConnection:(CAContextID)contextId
                       options:(NSDictionary*)optionsDict;
@property(readonly) CAContextID contextId;
@property(retain) CALayer *layer;
@end

@interface CALayerHost : CALayer
@property CAContextID contextId;
@end

#endif 

namespace ui {

bool UI_BASE_EXPORT RemoteLayerAPISupported();

}  

#endif  
