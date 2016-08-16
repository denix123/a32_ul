// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_USB_USB_DEVICE_H_
#define DEVICE_USB_USB_DEVICE_H_

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/observer_list.h"
#include "base/strings/string16.h"

namespace device {

class UsbDeviceHandle;
struct UsbConfigDescriptor;

class UsbDevice : public base::RefCountedThreadSafe<UsbDevice> {
 public:
  class Observer {
   public:
    virtual void OnDisconnect(scoped_refptr<UsbDevice> device) = 0;
  };

  
  uint16 vendor_id() const { return vendor_id_; }
  uint16 product_id() const { return product_id_; }
  uint32 unique_id() const { return unique_id_; }

#if defined(OS_CHROMEOS)
  
  
  
  
  virtual void RequestUsbAccess(
      int interface_id,
      const base::Callback<void(bool success)>& callback) = 0;
#endif  

  
  
  virtual scoped_refptr<UsbDeviceHandle> Open() = 0;

  
  
  
  
  virtual bool Close(scoped_refptr<UsbDeviceHandle> handle) = 0;

  
  
  virtual const UsbConfigDescriptor& GetConfiguration() = 0;

  
  
  virtual bool GetManufacturer(base::string16* manufacturer) = 0;

  
  
  virtual bool GetProduct(base::string16* product) = 0;

  
  
  virtual bool GetSerialNumber(base::string16* serial) = 0;

  void AddObserver(Observer* obs) { observer_list_.AddObserver(obs); }
  void RemoveObserver(Observer* obs) { observer_list_.RemoveObserver(obs); }

 protected:
  UsbDevice(uint16 vendor_id, uint16 product_id, uint32 unique_id);
  virtual ~UsbDevice();

  void NotifyDisconnect();

 private:
  friend class base::RefCountedThreadSafe<UsbDevice>;

  const uint16 vendor_id_;
  const uint16 product_id_;
  const uint32 unique_id_;

  ObserverList<Observer> observer_list_;

  DISALLOW_COPY_AND_ASSIGN(UsbDevice);
};

}  

#endif  
