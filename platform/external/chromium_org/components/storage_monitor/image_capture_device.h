// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_STORAGE_MONITOR_IMAGE_CAPTURE_DEVICE_H_
#define COMPONENTS_STORAGE_MONITOR_IMAGE_CAPTURE_DEVICE_H_

#import <Foundation/Foundation.h>
#import <ImageCaptureCore/ImageCaptureCore.h>

#include "base/files/file.h"
#include "base/files/file_path.h"
#include "base/mac/cocoa_protocols.h"
#include "base/mac/foundation_util.h"
#include "base/mac/scoped_nsobject.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "base/strings/string_util.h"
#include "base/strings/sys_string_conversions.h"
#include "base/synchronization/lock.h"

namespace storage_monitor {

class ImageCaptureDeviceListener {
 public:
  virtual ~ImageCaptureDeviceListener() {}

  
  
  
  
  
  virtual void ItemAdded(const std::string& name,
                         const base::File::Info& info) = 0;

  
  virtual void NoMoreItems() = 0;

  
  
  
  virtual void DownloadedFile(const std::string& name,
                              base::File::Error error) = 0;

  
  
  virtual void DeviceRemoved() = 0;
};

}  

@interface ImageCaptureDevice
    : NSObject<ICCameraDeviceDelegate, ICCameraDeviceDownloadDelegate> {
 @private
  base::scoped_nsobject<ICCameraDevice> camera_;
  base::WeakPtr<storage_monitor::ImageCaptureDeviceListener> listener_;
  bool closing_;
}

- (id)initWithCameraDevice:(ICCameraDevice*)cameraDevice;
- (void)setListener:
        (base::WeakPtr<storage_monitor::ImageCaptureDeviceListener>)listener;
- (void)open;
- (void)close;

- (void)eject;

- (void)downloadFile:(const std::string&)name
           localPath:(const base::FilePath&)localPath;

@end

#endif  
