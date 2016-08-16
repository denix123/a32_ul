// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_CLOUD_DEVICES_COMMON_CLOUD_DEVICE_DESCRIPTION_H_
#define COMPONENTS_CLOUD_DEVICES_COMMON_CLOUD_DEVICE_DESCRIPTION_H_

#include <string>

#include "base/callback.h"

namespace base {
class DictionaryValue;
class ListValue;
}

namespace cloud_devices {

class CloudDeviceDescription {
 public:
  CloudDeviceDescription();
  ~CloudDeviceDescription();

  void Reset();

  bool InitFromDictionary(scoped_ptr<base::DictionaryValue> root);
  bool InitFromString(const std::string& json);

  std::string ToString() const;

  const base::DictionaryValue& root() const { return *root_; }

  
  
  const base::DictionaryValue* GetItem(const std::string& path) const;

  
  
  base::DictionaryValue* CreateItem(const std::string& path);

  
  
  const base::ListValue* GetListItem(const std::string& path) const;

  
  
  base::ListValue* CreateListItem(const std::string& path);

 private:
  scoped_ptr<base::DictionaryValue> root_;

  DISALLOW_COPY_AND_ASSIGN(CloudDeviceDescription);
};

}  

#endif  
