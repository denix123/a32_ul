// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
#ifndef CHROME_BROWSER_EXTENSIONS_API_IMAGE_WRITER_PRIVATE_REMOVABLE_STORAGE_PROVIDER_H_
#define CHROME_BROWSER_EXTENSIONS_API_IMAGE_WRITER_PRIVATE_REMOVABLE_STORAGE_PROVIDER_H_

#include "base/callback.h"
#include "chrome/common/extensions/api/image_writer_private.h"
#include "chrome/common/ref_counted_util.h"

namespace extensions {


typedef RefCountedVector<linked_ptr
  <api::image_writer_private::RemovableStorageDevice> > StorageDeviceList;

class RemovableStorageProvider {
 public:
  typedef base::Callback<void(scoped_refptr<StorageDeviceList>, bool)>
    DeviceListReadyCallback;

  
  static void GetAllDevices(DeviceListReadyCallback callback);

  
  
  
  static void SetDeviceListForTesting(
      scoped_refptr<StorageDeviceList> device_list);
  
  static void ClearDeviceListForTesting();

 private:
  
  static bool PopulateDeviceList(scoped_refptr<StorageDeviceList> device_list);
};

} 

#endif  
