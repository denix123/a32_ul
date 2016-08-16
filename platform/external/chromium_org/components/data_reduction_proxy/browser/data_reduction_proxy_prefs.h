// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_DATA_REDUCTION_PROXY_BROWSER_DATA_REDUCTION_PROXY_PREFS_H_
#define COMPONENTS_DATA_REDUCTION_PROXY_BROWSER_DATA_REDUCTION_PROXY_PREFS_H_

#include "base/macros.h"

namespace user_prefs {
class PrefRegistrySyncable;
}

class PrefRegistrySimple;

namespace data_reduction_proxy {

void RegisterSyncableProfilePrefs(
    user_prefs::PrefRegistrySyncable* registry);

void RegisterSimpleProfilePrefs(PrefRegistrySimple* registry);

void RegisterPrefs(PrefRegistrySimple* registry);

}  

#endif  
