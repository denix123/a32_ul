// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_IME_EXTENSION_IME_UTIL_H_
#define CHROMEOS_IME_EXTENSION_IME_UTIL_H_

#include <string>

#include "base/auto_reset.h"
#include "chromeos/chromeos_export.h"

namespace chromeos {

namespace extension_ime_util {

#if defined(GOOGLE_CHROME_BUILD)
const char kXkbExtensionId[] = "jkghodnilhceideoidjikpgommlajknk";
const char kM17nExtensionId[] = "gjaehgfemfahhmlgpdfknkhdnemmolop";
const char kHangulExtensionId[] = "bdgdidmhaijohebebipajioienkglgfo";
const char kMozcExtensionId[] = "gjaehgfemfahhmlgpdfknkhdnemmolop";
const char kT13nExtensionId[] = "gjaehgfemfahhmlgpdfknkhdnemmolop";
const char kChinesePinyinExtensionId[] = "gjaehgfemfahhmlgpdfknkhdnemmolop";
const char kChineseZhuyinExtensionId[] = "gjaehgfemfahhmlgpdfknkhdnemmolop";
const char kChineseCangjieExtensionId[] = "gjaehgfemfahhmlgpdfknkhdnemmolop";
#else
const char kXkbExtensionId[] = "fgoepimhcoialccpbmpnnblemnepkkao";
const char kM17nExtensionId[] = "jhffeifommiaekmbkkjlpmilogcfdohp";
const char kHangulExtensionId[] = "bdgdidmhaijohebebipajioienkglgfo";
const char kMozcExtensionId[] = "bbaiamgfapehflhememkfglaehiobjnk";
const char kT13nExtensionId[] = "gjaehgfemfahhmlgpdfknkhdnemmolop";
const char kChinesePinyinExtensionId[] = "cpgalbafkoofkjmaeonnfijgpfennjjn";
const char kChineseZhuyinExtensionId[] = "ekbifjdfhkmdeeajnolmgdlmkllopefi";
const char kChineseCangjieExtensionId[] = "aeebooiibjahgpgmhkeocbeekccfknbj";
#endif

std::string CHROMEOS_EXPORT GetInputMethodID(const std::string& extension_id,
                                             const std::string& engine_id);

std::string CHROMEOS_EXPORT GetComponentInputMethodID(
    const std::string& extension_id,
    const std::string& engine_id);

std::string CHROMEOS_EXPORT GetExtensionIDFromInputMethodID(
    const std::string& input_method_id);

std::string CHROMEOS_EXPORT GetInputMethodIDByEngineID(
    const std::string& engine_id);

bool CHROMEOS_EXPORT IsExtensionIME(const std::string& input_method_id);

bool CHROMEOS_EXPORT IsComponentExtensionIME(
    const std::string& input_method_id);

bool CHROMEOS_EXPORT IsMemberOfExtension(const std::string& input_method_id,
                                         const std::string& extension_id);

bool CHROMEOS_EXPORT IsKeyboardLayoutExtension(
    const std::string& input_method_id);

std::string CHROMEOS_EXPORT
    GetComponentIDByInputMethodID(const std::string& input_method_id);

std::string CHROMEOS_EXPORT MaybeGetLegacyXkbId(
    const std::string& input_method_id);

}  

}  

#endif  
