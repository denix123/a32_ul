// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_MANAGEMENT_TEST_UTIL_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_MANAGEMENT_TEST_UTIL_H_

#include <string>

#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/values.h"
#include "chrome/browser/extensions/extension_management_constants.h"
#include "extensions/browser/pref_names.h"
#include "extensions/common/extension.h"

namespace extensions {

class ExtensionManagementPrefUpdaterBase {
 public:
  ExtensionManagementPrefUpdaterBase();
  virtual ~ExtensionManagementPrefUpdaterBase();

  
  void UnsetPerExtensionSettings(const ExtensionId& id);
  void ClearPerExtensionSettings(const ExtensionId& id);

  
  void SetBlacklistedByDefault(bool value);
  void ClearInstallationModesForIndividualExtensions();
  void SetIndividualExtensionInstallationAllowed(const ExtensionId& id,
                                                 bool allowed);
  void SetIndividualExtensionAutoInstalled(const ExtensionId& id,
                                           const std::string& update_url,
                                           bool forced);

  
  void UnsetInstallSources();
  void ClearInstallSources();
  void AddInstallSource(const std::string& install_source);
  void RemoveInstallSource(const std::string& install_source);

  
  void UnsetAllowedTypes();
  void ClearAllowedTypes();
  void AddAllowedType(const std::string& allowed_type);
  void RemoveAllowedType(const std::string& allowd_type);

  
  const base::DictionaryValue* GetPref();

 protected:
  
  
  
  void SetPref(base::DictionaryValue* pref);

  
  
  
  scoped_ptr<base::DictionaryValue> TakePref();

 private:
  
  void ClearList(const std::string& path);
  void AddStringToList(const std::string& path, const std::string& str);
  void RemoveStringFromList(const std::string& path, const std::string& str);

  scoped_ptr<base::DictionaryValue> pref_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionManagementPrefUpdaterBase);
};

template <class TestingPrefService>
class ExtensionManagementPrefUpdater
    : public ExtensionManagementPrefUpdaterBase {
 public:
  explicit ExtensionManagementPrefUpdater(TestingPrefService* service)
      : service_(service) {
    const base::Value* pref_value =
        service_->GetManagedPref(pref_names::kExtensionManagement);
    if (pref_value) {
      const base::DictionaryValue* dict_value = NULL;
      pref_value->GetAsDictionary(&dict_value);
      SetPref(dict_value->DeepCopy());
    } else {
      SetPref(new base::DictionaryValue);
    }
  }

  virtual ~ExtensionManagementPrefUpdater() {
    service_->SetManagedPref(pref_names::kExtensionManagement,
                             TakePref().release());
  }

 private:
  TestingPrefService* service_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionManagementPrefUpdater);
};

}  

#endif  
