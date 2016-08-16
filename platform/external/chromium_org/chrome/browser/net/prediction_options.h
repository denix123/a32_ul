// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_NET_PREDICTION_OPTIONS_H_
#define CHROME_BROWSER_NET_PREDICTION_OPTIONS_H_

namespace user_prefs {
class PrefRegistrySyncable;
}

class PrefService;
class ProfileIOData;

namespace chrome_browser_net {

enum NetworkPredictionOptions {
  NETWORK_PREDICTION_ALWAYS,
  NETWORK_PREDICTION_WIFI_ONLY,
  NETWORK_PREDICTION_NEVER,
  NETWORK_PREDICTION_DEFAULT = NETWORK_PREDICTION_WIFI_ONLY,
};

void RegisterPredictionOptionsProfilePrefs(
    user_prefs::PrefRegistrySyncable* registry);

void MigrateNetworkPredictionUserPrefs(PrefService* pref_service);


bool CanPrefetchAndPrerenderIO(ProfileIOData* profile_io_data);

bool CanPrefetchAndPrerenderUI(PrefService* prefs);


bool CanPreresolveAndPreconnectIO(ProfileIOData* profile_io_data);

bool CanPreresolveAndPreconnectUI(PrefService* prefs);

}  

#endif  
