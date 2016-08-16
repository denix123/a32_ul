// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_RENDERER_KEY_SYSTEM_INFO_H_
#define CONTENT_PUBLIC_RENDERER_KEY_SYSTEM_INFO_H_

#include <map>
#include <string>

#include "base/basictypes.h"
#include "base/containers/hash_tables.h"
#include "content/common/content_export.h"
#include "content/public/common/eme_codec.h"


namespace content {

struct CONTENT_EXPORT KeySystemInfo {
  explicit KeySystemInfo(const std::string& key_system);
  ~KeySystemInfo();

  std::string key_system;

  
  SupportedCodecs supported_codecs;

  
  
  
  std::string parent_key_system;

  
  bool use_aes_decryptor;
#if defined(ENABLE_PEPPER_CDMS)
  std::string pepper_type;
#endif
};

}  

#endif  
