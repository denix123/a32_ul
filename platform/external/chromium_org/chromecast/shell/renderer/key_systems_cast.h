// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMECAST_SHELL_RENDERER_KEY_SYSTEMS_CAST_H_
#define CHROMECAST_SHELL_RENDERER_KEY_SYSTEMS_CAST_H_

#include <vector>

#include "content/public/renderer/key_system_info.h"

namespace chromecast {
namespace shell {

void AddKeySystemWithCodecs(
    const std::string& key_system_name,
    std::vector<content::KeySystemInfo>* concrete_key_systems);

void AddChromecastKeySystems(
    std::vector<content::KeySystemInfo>* key_systems_info);

void AddChromecastPlatformKeySystems(
    std::vector<content::KeySystemInfo>* key_systems_info);

}  
}  

#endif  
