// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_NETWORK_ONC_ONC_TRANSLATION_TABLES_H_
#define CHROMEOS_NETWORK_ONC_ONC_TRANSLATION_TABLES_H_

#include <string>
#include <vector>

#include "chromeos/chromeos_export.h"
#include "chromeos/network/onc/onc_signature.h"

namespace chromeos {
namespace onc {

struct FieldTranslationEntry {
  const char* onc_field_name;
  const char* shill_property_name;
};

struct StringTranslationEntry {
  const char* onc_value;
  const char* shill_value;
};

CHROMEOS_EXPORT extern const StringTranslationEntry kNetworkTypeTable[];
CHROMEOS_EXPORT extern const StringTranslationEntry kVPNTypeTable[];
CHROMEOS_EXPORT extern const StringTranslationEntry kWiFiSecurityTable[];
CHROMEOS_EXPORT extern const StringTranslationEntry kEAPOuterTable[];
CHROMEOS_EXPORT extern const StringTranslationEntry kEAP_PEAP_InnerTable[];
CHROMEOS_EXPORT extern const StringTranslationEntry kEAP_TTLS_InnerTable[];
CHROMEOS_EXPORT extern const StringTranslationEntry kActivationStateTable[];
CHROMEOS_EXPORT extern const StringTranslationEntry kRoamingStateTable[];

extern const FieldTranslationEntry kCellularDeviceTable[];

const FieldTranslationEntry* GetFieldTranslationTable(
    const OncValueSignature& onc_signature);

std::vector<std::string> GetPathToNestedShillDictionary(
    const OncValueSignature& onc_signature);

bool GetShillPropertyName(const std::string& onc_field_name,
                          const FieldTranslationEntry table[],
                          std::string* shill_property_name);

CHROMEOS_EXPORT bool TranslateStringToShill(
    const StringTranslationEntry table[],
    const std::string& onc_value,
    std::string* shill_value);

CHROMEOS_EXPORT bool TranslateStringToONC(const StringTranslationEntry table[],
                                          const std::string& shill_value,
                                          std::string* onc_value);

}  
}  

#endif  
