// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_CHROMEOS_LOGIN_L10N_UTIL_H_
#define CHROME_BROWSER_UI_WEBUI_CHROMEOS_LOGIN_L10N_UTIL_H_

#include <string>
#include <vector>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"

namespace base {
class DictionaryValue;
class ListValue;
}

namespace chromeos {

extern const char kMostRelevantLanguagesDivider[];


scoped_ptr<base::ListValue> GetUILanguageList(
    const std::vector<std::string>* most_relevant_language_codes,
    const std::string& selected);

std::string FindMostRelevantLocale(
    const std::vector<std::string>& most_relevant_language_codes,
    const base::ListValue& available_locales,
    const std::string& fallback_locale);

scoped_ptr<base::ListValue> GetAcceptLanguageList();

scoped_ptr<base::ListValue> GetAndActivateLoginKeyboardLayouts(
    const std::string& locale,
    const std::string& selected);

typedef base::Callback<void(scoped_ptr<base::ListValue>)>
    GetKeyboardLayoutsForLocaleCallback;
void GetKeyboardLayoutsForLocale(
    const GetKeyboardLayoutsForLocaleCallback& callback,
    const std::string& locale);

scoped_ptr<base::DictionaryValue> GetCurrentKeyboardLayout();

}  

#endif  
