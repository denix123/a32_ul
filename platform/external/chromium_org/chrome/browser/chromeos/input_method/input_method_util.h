// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_INPUT_METHOD_INPUT_METHOD_UTIL_H_
#define CHROME_BROWSER_CHROMEOS_INPUT_METHOD_INPUT_METHOD_UTIL_H_

#include <cstddef>
#include <map>
#include <string>
#include <vector>

#include "base/containers/hash_tables.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "base/threading/thread_checker.h"
#include "chromeos/ime/input_method_descriptor.h"

namespace chromeos {
namespace input_method {

class InputMethodDelegate;

enum InputMethodType {
  kKeyboardLayoutsOnly,
  kAllInputMethods,
};

class InputMethodUtil {
 public:
  explicit InputMethodUtil(InputMethodDelegate* delegate);
  ~InputMethodUtil();

  // Converts a string sent from IBus IME engines, which is written in English,
  
  
  
  
  
  
  base::string16 TranslateString(const std::string& english_string) const;

  
  
  
  std::string GetLanguageCodeFromInputMethodId(
      const std::string& input_method_id) const;

  
  
  
  std::string GetInputMethodDisplayNameFromId(
      const std::string& input_method_id) const;

  base::string16 GetInputMethodShortName(
      const InputMethodDescriptor& input_method) const;
  base::string16 GetInputMethodMediumName(
      const InputMethodDescriptor& input_method) const;
  base::string16 GetInputMethodLongName(
      const InputMethodDescriptor& input_method) const;

  
  
  
  
  const InputMethodDescriptor* GetInputMethodDescriptorFromId(
      const std::string& input_method_id) const;

  
  
  
  
  
  
  
  bool GetInputMethodIdsFromLanguageCode(
      const std::string& language_code,
      InputMethodType type,
      std::vector<std::string>* out_input_method_ids) const;

  
  
  
  void GetFirstLoginInputMethodIds(
      const std::string& language_code,
      const InputMethodDescriptor& current_input_method,
      std::vector<std::string>* out_input_method_ids) const;

  
  
  void GetLanguageCodesFromInputMethodIds(
      const std::vector<std::string>& input_method_ids,
      std::vector<std::string>* out_language_codes) const;

  
  
  std::string GetLanguageDefaultInputMethodId(const std::string& language_code);

  
  
  
  
  
  bool MigrateInputMethods(std::vector<std::string>* input_method_ids);

  
  void UpdateHardwareLayoutCache();

  
  
  void SetHardwareKeyboardLayoutForTesting(const std::string& layout);

  
  
  const std::vector<std::string>& GetHardwareInputMethodIds();

  
  
  
  
  
  
  const std::vector<std::string>& GetHardwareLoginInputMethodIds();

  
  bool IsLoginKeyboard(const std::string& input_method_id) const;

  
  bool IsValidInputMethodId(const std::string& input_method_id) const;

  
  static bool IsKeyboardLayout(const std::string& input_method_id);

  
  void ResetInputMethods(const InputMethodDescriptors& imes);

  
  void AppendInputMethods(const InputMethodDescriptors& imes);

  
  void InitXkbInputMethodsForTesting();

  
  typedef std::map<
    std::string, InputMethodDescriptor> InputMethodIdToDescriptorMap;

  
  const InputMethodIdToDescriptorMap& GetIdToDesciptorMapForTesting();

  
  
  
  static InputMethodDescriptor GetFallbackInputMethodDescriptor();

 protected:
  
  bool GetInputMethodIdsFromLanguageCodeInternal(
      const std::multimap<std::string, std::string>& language_code_to_ids,
      const std::string& normalized_language_code,
      InputMethodType type,
      std::vector<std::string>* out_input_method_ids) const;

  
  
  
  
  
  
  
  
  
  
  std::string GetKeyboardLayoutName(const std::string& input_method_id) const;

 private:
  bool TranslateStringInternal(const std::string& english_string,
                               base::string16 *out_string) const;

  
  typedef std::multimap<std::string, std::string> LanguageCodeToIdsMap;

  LanguageCodeToIdsMap language_code_to_ids_;
  InputMethodIdToDescriptorMap id_to_descriptor_;
  std::map<std::string, std::string> xkb_layout_to_indicator_;

  typedef base::hash_map<std::string, int> HashType;
  HashType english_to_resource_id_;

  InputMethodDelegate* delegate_;

  base::ThreadChecker thread_checker_;
  std::vector<std::string> hardware_layouts_;
  std::vector<std::string> hardware_login_layouts_;
  std::vector<std::string> cached_hardware_layouts_;

  DISALLOW_COPY_AND_ASSIGN(InputMethodUtil);
};

}  
}  

#endif  
