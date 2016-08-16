// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_DBUS_LORGNETTE_MANAGER_CLIENT_H_
#define CHROMEOS_DBUS_LORGNETTE_MANAGER_CLIENT_H_

#include <map>

#include "base/callback.h"
#include "base/files/file.h"
#include "base/memory/ref_counted_memory.h"
#include "chromeos/chromeos_export.h"
#include "chromeos/dbus/dbus_client.h"

namespace chromeos {

class CHROMEOS_EXPORT LorgnetteManagerClient : public DBusClient {
 public:
  
  typedef std::map<std::string, std::string> ScannerTableEntry;
  typedef std::map<std::string, ScannerTableEntry> ScannerTable;

  
  
  typedef base::Callback<void(
      bool succeeded, const ScannerTable&)> ListScannersCallback;

  
  
  typedef base::Callback<void(bool succeeded)> ScanImageCallback;

  
  struct ScanProperties {
    ScanProperties() : resolution_dpi(0) {}
    std::string mode;  
    int resolution_dpi;
  };

  virtual ~LorgnetteManagerClient();

  
  virtual void ListScanners(const ListScannersCallback& callback) = 0;

  
  
  virtual void ScanImage(std::string device_name,
                         base::PlatformFile file,
                         const ScanProperties& properties,
                         const ScanImageCallback& callback) = 0;

  
  
  static LorgnetteManagerClient* Create();

 protected:
  
  LorgnetteManagerClient();

 private:
  DISALLOW_COPY_AND_ASSIGN(LorgnetteManagerClient);
};

}  

#endif  
