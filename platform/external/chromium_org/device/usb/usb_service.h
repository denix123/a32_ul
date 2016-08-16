// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_USB_USB_SERVICE_H_
#define DEVICE_USB_USB_SERVICE_H_

#include <vector>

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/threading/non_thread_safe.h"

namespace base {
class SingleThreadTaskRunner;
}

namespace device {

class UsbDevice;

class UsbService : public base::NonThreadSafe {
 public:
  
  
  
  
  static UsbService* GetInstance(
      scoped_refptr<base::SingleThreadTaskRunner> ui_task_runner);

  static void SetInstanceForTest(UsbService* instance);

  virtual scoped_refptr<UsbDevice> GetDeviceById(uint32 unique_id) = 0;

  
  
  
  virtual void GetDevices(std::vector<scoped_refptr<UsbDevice> >* devices) = 0;

 protected:
  friend struct base::DefaultDeleter<UsbService>;
  UsbService() {}
  virtual ~UsbService() {}
  DISALLOW_COPY_AND_ASSIGN(UsbService);
};

}  

#endif  
