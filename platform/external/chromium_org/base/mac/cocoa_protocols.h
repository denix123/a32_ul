// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_COCOA_PROTOCOLS_MAC_H_
#define BASE_COCOA_PROTOCOLS_MAC_H_

#import <Cocoa/Cocoa.h>

#import "third_party/google_toolbox_for_mac/src/GTMDefines.h"


#define DEFINE_EMPTY_PROTOCOL(p) \
@protocol p \
@end

#if !defined(MAC_OS_X_VERSION_10_7) || \
    MAC_OS_X_VERSION_MAX_ALLOWED < MAC_OS_X_VERSION_10_7

DEFINE_EMPTY_PROTOCOL(NSDraggingDestination)
DEFINE_EMPTY_PROTOCOL(ICCameraDeviceDownloadDelegate)

#endif  

#undef DEFINE_EMPTY_PROTOCOL

#endif  
