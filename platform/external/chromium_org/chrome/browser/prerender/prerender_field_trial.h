// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PRERENDER_PRERENDER_FIELD_TRIAL_H_
#define CHROME_BROWSER_PRERENDER_PRERENDER_FIELD_TRIAL_H_

#include <string>

class Profile;

namespace base {
class CommandLine;
}

namespace prerender {

void ConfigurePrerender(const base::CommandLine& command_line);

bool IsOmniboxEnabled(Profile* profile);

bool ShouldMergeSessionStorageNamespaces();

bool IsLocalPredictorEnabled();

bool ShouldDisableLocalPredictorBasedOnSyncAndConfiguration(Profile* profile);

bool ShouldDisableLocalPredictorDueToPreferencesAndNetwork(Profile* profile);

bool IsLoggedInPredictorEnabled();

bool IsSideEffectFreeWhitelistEnabled();

bool IsLocalPredictorPrerenderLaunchEnabled();

bool IsLocalPredictorPrerenderAlwaysControlEnabled();

bool IsLocalPredictorPrerenderPrefetchEnabled();

bool ShouldQueryPrerenderService(Profile* profile);

bool ShouldQueryPrerenderServiceForCurrentURL();
bool ShouldQueryPrerenderServiceForCandidateURLs();

std::string GetPrerenderServiceURLPrefix();

int GetPrerenderServiceBehaviorID();

int GetPrerenderServiceFetchTimeoutMs();

int GetPrerenderPrefetchListTimeoutSeconds();

int GetLocalPredictorTTLSeconds();

int GetLocalPredictorPrerenderPriorityHalfLifeTimeSeconds();

int GetLocalPredictorMaxConcurrentPrerenders();

int GetLocalPredictorMaxLaunchPrerenders();

bool SkipLocalPredictorFragment();
bool SkipLocalPredictorHTTPS();
bool SkipLocalPredictorWhitelist();
bool SkipLocalPredictorServiceWhitelist();
bool SkipLocalPredictorLoggedIn();
bool SkipLocalPredictorDefaultNoPrerender();
bool SkipLocalPredictorLocalCandidates();
bool SkipLocalPredictorServiceCandidates();

bool IsPrerenderCookieStoreEnabled();

}  

#endif  
