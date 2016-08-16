// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CDM_KEY_SYSTEM_NAMES_H_
#define MEDIA_CDM_KEY_SYSTEM_NAMES_H_

#include <string>

#include "media/base/media_export.h"

namespace media {


MEDIA_EXPORT extern const char kClearKey[];

MEDIA_EXPORT extern const char kExternalClearKey[];

MEDIA_EXPORT inline bool IsClearKey(const std::string& key_system) {
  return key_system == kClearKey;
}

MEDIA_EXPORT bool IsExternalClearKey(const std::string& key_system);

}  

#endif  
