// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef APPS_SAVED_DEVICES_SERVICE_H_
#define APPS_SAVED_DEVICES_SERVICE_H_

#include <map>
#include <set>
#include <string>
#include <vector>

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/stl_util.h"
#include "base/strings/string16.h"
#include "base/threading/thread_checker.h"
#include "components/keyed_service/core/keyed_service.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "device/usb/usb_device.h"

class Profile;

namespace base {
class Value;
}

namespace extensions {
class Extension;
}

namespace apps {

struct SavedDeviceEntry {
  SavedDeviceEntry(uint16_t vendor_id,
                   uint16_t product_id,
                   const base::string16& serial_number);

  base::Value* ToValue() const;

  
  uint16_t vendor_id;

  
  uint16_t product_id;

  
  base::string16 serial_number;
};

class SavedDevicesService : public KeyedService,
                            public content::NotificationObserver {
 public:
  
  
  
  class SavedDevices : device::UsbDevice::Observer {
   public:
    bool IsRegistered(scoped_refptr<device::UsbDevice> device) const;
    void RegisterDevice(scoped_refptr<device::UsbDevice> device,
                         base::string16* serial_number);

   private:
    friend class SavedDevicesService;

    SavedDevices(Profile* profile, const std::string& extension_id);
    virtual ~SavedDevices();

    
    virtual void OnDisconnect(scoped_refptr<device::UsbDevice> device) OVERRIDE;

    Profile* profile_;
    const std::string extension_id_;

    // Devices with serial numbers are written to the prefs file.
    std::vector<SavedDeviceEntry> persistent_devices_;
    
    
    std::set<scoped_refptr<device::UsbDevice> > ephemeral_devices_;

    DISALLOW_COPY_AND_ASSIGN(SavedDevices);
  };

  explicit SavedDevicesService(Profile* profile);
  virtual ~SavedDevicesService();

  static SavedDevicesService* Get(Profile* profile);

  
  SavedDevices* GetOrInsert(const std::string& extension_id);

  std::vector<SavedDeviceEntry> GetAllDevices(
      const std::string& extension_id) const;

  
  void Clear(const std::string& extension_id);

 private:
  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  SavedDevices* Get(const std::string& extension_id) const;

  std::map<std::string, SavedDevices*> extension_id_to_saved_devices_;
  Profile* profile_;
  content::NotificationRegistrar registrar_;
  base::ThreadChecker thread_checker_;

  DISALLOW_COPY_AND_ASSIGN(SavedDevicesService);
};

}  

#endif  
