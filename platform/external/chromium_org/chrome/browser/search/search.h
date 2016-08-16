// Copyright 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SEARCH_SEARCH_H_
#define CHROME_BROWSER_SEARCH_SEARCH_H_

#include <string>
#include <utility>
#include <vector>

#include "base/basictypes.h"
#include "base/strings/string16.h"
#include "chrome/browser/ui/search/search_model.h"

class GURL;
class Profile;
class TemplateURL;
class TemplateURLRef;

namespace content {
class BrowserContext;
class NavigationEntry;
class WebContents;
}

namespace user_prefs {
class PrefRegistrySyncable;
}

namespace chrome {

enum OptInState {
  
  INSTANT_EXTENDED_NOT_SET,
  
  INSTANT_EXTENDED_OPT_IN,
  
  INSTANT_EXTENDED_OPT_OUT,
  INSTANT_EXTENDED_OPT_IN_STATE_ENUM_COUNT,
};

enum DisplaySearchButtonConditions {
  DISPLAY_SEARCH_BUTTON_NEVER,
  DISPLAY_SEARCH_BUTTON_FOR_STR,         
  DISPLAY_SEARCH_BUTTON_FOR_STR_OR_IIP,  
  DISPLAY_SEARCH_BUTTON_ALWAYS,
  DISPLAY_SEARCH_BUTTON_NUM_VALUES,
};

enum OriginChipCondition {
  ORIGIN_CHIP_DISABLED = 0,
  ORIGIN_CHIP_ALWAYS,
  ORIGIN_CHIP_ON_SRP,
  ORIGIN_CHIP_NUM_VALUES,
};

extern const int kDisableStartMargin;

bool IsSuggestPrefEnabled(Profile* profile);

std::string InstantExtendedEnabledParam(bool for_search);

std::string ForceInstantResultsParam(bool for_prerender);

bool IsQueryExtractionEnabled();

base::string16 ExtractSearchTermsFromURL(Profile* profile, const GURL& url);

bool IsQueryExtractionAllowedForURL(Profile* profile, const GURL& url);

base::string16 GetSearchTermsFromNavigationEntry(
    const content::NavigationEntry* entry);

base::string16 GetSearchTerms(const content::WebContents* contents);

bool ShouldAssignURLToInstantRenderer(const GURL& url, Profile* profile);

bool IsRenderedInInstantProcess(const content::WebContents* contents,
                                Profile* profile);

bool ShouldUseProcessPerSiteForInstantURL(const GURL& url, Profile* profile);

bool IsNTPURL(const GURL& url, Profile* profile);

bool IsInstantNTP(const content::WebContents* contents);

bool NavEntryIsInstantNTP(const content::WebContents* contents,
                          const content::NavigationEntry* nav_entry);

GURL GetInstantURL(Profile* profile, bool force_instant_results);

std::vector<GURL> GetSearchURLs(Profile* profile);

GURL GetSearchResultPrefetchBaseURL(Profile* profile);

bool ShouldPrefetchSearchResults();

bool ShouldAllowPrefetchNonDefaultMatch();

bool ShouldPrerenderInstantUrlOnOmniboxFocus();

bool ShouldReuseInstantSearchBasePage();

GURL GetLocalInstantURL(Profile* profile);

DisplaySearchButtonConditions GetDisplaySearchButtonConditions();

bool ShouldDisplayOriginChip();

OriginChipCondition GetOriginChipCondition();

bool ShouldShowGoogleLocalNTP();

GURL GetEffectiveURLForInstant(const GURL& url, Profile* profile);

// |url| is rewritten to the value of --instant-new-tab-url.
bool HandleNewTabURLRewrite(GURL* url,
                            content::BrowserContext* browser_context);
bool HandleNewTabURLReverseRewrite(GURL* url,
                                   content::BrowserContext* browser_context);

void SetInstantSupportStateInNavigationEntry(InstantSupportState state,
                                             content::NavigationEntry* entry);

InstantSupportState GetInstantSupportStateFromNavigationEntry(
    const content::NavigationEntry& entry);

bool ShouldPrefetchSearchResultsOnSRP();


void EnableQueryExtractionForTesting();

GURL GetNewTabPageURL(Profile* profile);

bool ShouldUseAltInstantURL();

bool ShouldUseSearchPathForInstant();

}  

#endif  
