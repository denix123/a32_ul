// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_INPUT_METHOD_COMPONENT_EXTENSION_IME_MANAGER_IMPL_H_
#define CHROME_BROWSER_CHROMEOS_INPUT_METHOD_COMPONENT_EXTENSION_IME_MANAGER_IMPL_H_

#include <set>
#include <vector>

#include "base/bind.h"
#include "base/memory/weak_ptr.h"
#include "base/sequenced_task_runner.h"
#include "base/threading/thread_checker.h"
#include "base/values.h"
#include "chromeos/ime/component_extension_ime_manager.h"

class Profile;

namespace chromeos {

class ComponentExtensionIMEManagerImpl
    : public ComponentExtensionIMEManagerDelegate {
 public:
  ComponentExtensionIMEManagerImpl();
  virtual ~ComponentExtensionIMEManagerImpl();

  
  virtual std::vector<ComponentExtensionIME> ListIME() OVERRIDE;
  virtual void Load(Profile* profile,
                    const std::string& extension_id,
                    const std::string& manifest,
                    const base::FilePath& file_path) OVERRIDE;
  virtual void Unload(Profile* profile,
                      const std::string& extension_id,
                      const base::FilePath& file_path) OVERRIDE;

 private:
  
  
  static void ReadComponentExtensionsInfo(
      std::vector<ComponentExtensionIME>* out_imes);

  
  static scoped_ptr<base::DictionaryValue> GetManifest(
      const std::string& manifest_string);

  
  
  static bool ReadExtensionInfo(const base::DictionaryValue& manifest,
                                const std::string& extension_id,
                                ComponentExtensionIME* out);

  
  
  
  static bool ReadEngineComponent(
      const ComponentExtensionIME& component_extension,
      const base::DictionaryValue& dict,
      ComponentExtensionEngine* out);

  
  std::vector<ComponentExtensionIME> component_extension_list_;

  DISALLOW_COPY_AND_ASSIGN(ComponentExtensionIMEManagerImpl);
};

}  

#endif  

