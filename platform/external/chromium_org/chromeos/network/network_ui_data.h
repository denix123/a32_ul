// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_NETWORK_NETWORK_UI_DATA_H_
#define CHROMEOS_NETWORK_NETWORK_UI_DATA_H_

#include <string>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "chromeos/chromeos_export.h"
#include "components/onc/onc_constants.h"

namespace base {
class DictionaryValue;
}

namespace chromeos {

class CHROMEOS_EXPORT NetworkUIData {
 public:
  NetworkUIData();
  NetworkUIData(const NetworkUIData& other);
  NetworkUIData& operator=(const NetworkUIData& other);
  explicit NetworkUIData(const base::DictionaryValue& dict);
  ~NetworkUIData();

  ::onc::ONCSource onc_source() const { return onc_source_; }

  const base::DictionaryValue* user_settings() const {
    return user_settings_.get();
  }
  void set_user_settings(scoped_ptr<base::DictionaryValue> dict);

  
  std::string GetONCSourceAsString() const;

  
  
  void FillDictionary(base::DictionaryValue* dict) const;

  
  
  static scoped_ptr<NetworkUIData> CreateFromONC(::onc::ONCSource onc_source);

  
  static const char kKeyONCSource[];

  
  static const char kKeyUserSettings[];

  
  static const char kONCSourceUserImport[];
  static const char kONCSourceDevicePolicy[];
  static const char kONCSourceUserPolicy[];

 private:
  ::onc::ONCSource onc_source_;
  scoped_ptr<base::DictionaryValue> user_settings_;
};

}  

#endif  
