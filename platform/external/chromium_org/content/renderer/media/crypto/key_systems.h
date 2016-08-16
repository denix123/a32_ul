// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_CRYPTO_KEY_SYSTEMS_H_
#define CONTENT_RENDERER_MEDIA_CRYPTO_KEY_SYSTEMS_H_

#include <string>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "content/common/content_export.h"

namespace content {


std::string GetUnprefixedKeySystemName(const std::string& key_system);

std::string GetPrefixedKeySystemName(const std::string& key_system);

CONTENT_EXPORT bool IsConcreteSupportedKeySystem(const std::string& key_system);

CONTENT_EXPORT bool IsSupportedKeySystemWithMediaMimeType(
    const std::string& mime_type,
    const std::vector<std::string>& codecs,
    const std::string& key_system);

CONTENT_EXPORT std::string KeySystemNameForUMA(const std::string& key_system);

CONTENT_EXPORT bool CanUseAesDecryptor(const std::string& concrete_key_system);

#if defined(ENABLE_PEPPER_CDMS)
CONTENT_EXPORT std::string GetPepperType(
    const std::string& concrete_key_system);
#endif

#if defined(UNIT_TEST)
CONTENT_EXPORT void AddContainerMask(const std::string& container, uint32 mask);
CONTENT_EXPORT void AddCodecMask(const std::string& codec, uint32 mask);
#endif  

}  

#endif  
