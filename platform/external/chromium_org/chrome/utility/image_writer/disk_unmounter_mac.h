// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_UTILITY_IMAGE_WRITER_DISK_UNMOUNTER_MAC_H_
#define CHROME_UTILITY_IMAGE_WRITER_DISK_UNMOUNTER_MAC_H_

#include <CoreFoundation/CoreFoundation.h>
#include <DiskArbitration/DiskArbitration.h>

#include "base/bind.h"
#include "base/callback.h"
#include "base/mac/foundation_util.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/thread.h"

namespace image_writer {

class ImageWriter;

class DiskUnmounterMac {
 public:
  DiskUnmounterMac();
  ~DiskUnmounterMac();

  
  
  
  void Unmount(const std::string& device_path,
               const base::Closure& success_continuation,
               const base::Closure& failure_continuation);

 private:
  
  static void DiskClaimed(DADiskRef disk,
                          DADissenterRef dissenter,
                          void* context);
  
  static DADissenterRef DiskClaimRevoked(DADiskRef disk, void* context);
  
  static void DiskUnmounted(DADiskRef disk,
                            DADissenterRef dissenter,
                            void* context);

  
  static scoped_ptr<base::MessagePump> CreateMessagePump();

  
  void UnmountOnWorker(const std::string& device_path);

  
  void Error();

  scoped_refptr<base::MessageLoopProxy> original_thread_;
  base::Closure success_continuation_;
  base::Closure failure_continuation_;

  base::ScopedCFTypeRef<DADiskRef> disk_;
  base::ScopedCFTypeRef<DASessionRef> session_;

  
  
  base::Thread cf_thread_;
};

}  

#endif  
