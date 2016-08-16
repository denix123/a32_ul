// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_OPTIONS_CHROMEOS_CROS_LANGUAGE_OPTIONS_HANDLER_H_
#define CHROME_BROWSER_UI_WEBUI_OPTIONS_CHROMEOS_CROS_LANGUAGE_OPTIONS_HANDLER_H_

#include <string>

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "chrome/browser/ui/webui/options/language_options_handler.h"
#include "chromeos/ime/component_extension_ime_manager.h"
#include "chromeos/ime/input_method_descriptor.h"

namespace chromeos {
namespace options {

class CrosLanguageOptionsHandler
    : public ::options::LanguageOptionsHandlerCommon {
 public:
  CrosLanguageOptionsHandler();
  virtual ~CrosLanguageOptionsHandler();

  
  virtual void GetLocalizedValues(
      base::DictionaryValue* localized_strings) OVERRIDE;

  
  virtual void RegisterMessages() OVERRIDE;

  

  
  
  
  
  
  
  
  static base::ListValue* GetInputMethodList();

  
  
  
  
  static base::ListValue* ConvertInputMethodDescriptorsToIMEList(
      const input_method::InputMethodDescriptors& descriptors);

 private:
  
  virtual base::string16 GetProductName() OVERRIDE;
  virtual void SetApplicationLocale(const std::string& language_code) OVERRIDE;

  
  void RestartCallback(const base::ListValue* args);

  
  
  void InputMethodDisableCallback(const base::ListValue* args);

  
  
  void InputMethodEnableCallback(const base::ListValue* args);

  
  
  void InputMethodOptionsOpenCallback(const base::ListValue* args);

  
  
  void AddImeProvider(base::ListValue* list);

  DISALLOW_COPY_AND_ASSIGN(CrosLanguageOptionsHandler);
};

}  
}  

#endif  
