// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_STORAGE_MONITOR_IMAGE_CAPTURE_DEVICE_MANAGER_H_
#define COMPONENTS_STORAGE_MONITOR_IMAGE_CAPTURE_DEVICE_MANAGER_H_

#import <Foundation/Foundation.h>
#include <string>

#include "base/mac/scoped_nsobject.h"
#include "components/storage_monitor/storage_monitor.h"

@protocol ICDeviceBrowserDelegate;
@class ImageCaptureDevice;
@class ImageCaptureDeviceManagerImpl;

namespace storage_monitor {

class ImageCaptureDeviceManager {
 public:
  ImageCaptureDeviceManager();
  ~ImageCaptureDeviceManager();

  
  
  
  static ImageCaptureDevice* deviceForUUID(const std::string& uuid);

  
  id<ICDeviceBrowserDelegate> device_browser();

  
  
  void SetNotifications(StorageMonitor::Receiver* notifications);

  
  
  void EjectDevice(const std::string& uuid,
                   base::Callback<void(StorageMonitor::EjectStatus)> callback);

 private:
  base::scoped_nsobject<ImageCaptureDeviceManagerImpl> device_browser_;
};

}  

#endif  
