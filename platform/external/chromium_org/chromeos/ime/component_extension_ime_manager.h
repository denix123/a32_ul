// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_IME_COMPONENT_EXTENSION_IME_MANAGER_H_
#define CHROMEOS_IME_COMPONENT_EXTENSION_IME_MANAGER_H_

#include <map>
#include <set>

#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "chromeos/chromeos_export.h"
#include "chromeos/ime/input_method_descriptor.h"

class Profile;

namespace chromeos {

struct CHROMEOS_EXPORT ComponentExtensionEngine {
  ComponentExtensionEngine();
  ~ComponentExtensionEngine();
  std::string engine_id;  
  std::string display_name;  
  std::vector<std::string> language_codes;  
  std::string description;  
  std::vector<std::string> layouts;  
  GURL options_page_url; 
  GURL input_view_url; 
};

struct CHROMEOS_EXPORT ComponentExtensionIME {
  ComponentExtensionIME();
  ~ComponentExtensionIME();
  std::string id;  
  std::string manifest;  
  std::string description;  
  GURL options_page_url; 
  base::FilePath path;
  std::vector<ComponentExtensionEngine> engines;
};

class CHROMEOS_EXPORT ComponentExtensionIMEManagerDelegate {
 public:
  ComponentExtensionIMEManagerDelegate();
  virtual ~ComponentExtensionIMEManagerDelegate();

  
  virtual std::vector<ComponentExtensionIME> ListIME() = 0;

  
  
  virtual void Load(Profile* profile,
                    const std::string& extension_id,
                    const std::string& manifest,
                    const base::FilePath& path) = 0;

  
  virtual void Unload(Profile* profile,
                      const std::string& extension_id,
                      const base::FilePath& path) = 0;
};

class CHROMEOS_EXPORT ComponentExtensionIMEManager {
 public:
  ComponentExtensionIMEManager();
  virtual ~ComponentExtensionIMEManager();

  
  
  
  void Initialize(scoped_ptr<ComponentExtensionIMEManagerDelegate> delegate);

  
  
  
  bool LoadComponentExtensionIME(Profile* profile,
                                 const std::string& input_method_id);

  
  
  
  bool UnloadComponentExtensionIME(Profile* profile,
                                   const std::string& input_method_id);

  
  
  bool IsWhitelisted(const std::string& input_method_id);

  
  bool IsWhitelistedExtension(const std::string& extension_id);

  
  input_method::InputMethodDescriptors GetAllIMEAsInputMethodDescriptor();

  
  input_method::InputMethodDescriptors GetXkbIMEAsInputMethodDescriptor();

 private:
  
  
  
  bool FindEngineEntry(const std::string& input_method_id,
                       ComponentExtensionIME* out_extension);

  bool IsInLoginLayoutWhitelist(const std::vector<std::string>& layouts);

  scoped_ptr<ComponentExtensionIMEManagerDelegate> delegate_;

  
  
  std::map<std::string, ComponentExtensionIME> component_extension_imes_;

  
  
  std::set<std::string> input_method_id_set_;

  std::set<std::string> login_layout_set_;

  DISALLOW_COPY_AND_ASSIGN(ComponentExtensionIMEManager);
};

}  

#endif  
