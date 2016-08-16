// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_GOOGLE_CORE_BROWSER_GOOGLE_UTIL_H__
#define COMPONENTS_GOOGLE_CORE_BROWSER_GOOGLE_UTIL_H__

#include <string>

#include "base/basictypes.h"

class GURL;

namespace google_util {

bool HasGoogleSearchQueryParam(const std::string& str);

const char kInstantExtendedAPIParam[] = "espv";

GURL LinkDoctorBaseURL();
void SetMockLinkDoctorBaseURLForTesting();

std::string GetGoogleLocale(const std::string& application_locale);

GURL AppendGoogleLocaleParam(const GURL& url,
                             const std::string& application_locale);

std::string GetGoogleCountryCode(GURL google_homepage_url);

GURL GetGoogleSearchURL(GURL google_homepage_url);

GURL CommandLineGoogleBaseURL();

bool StartsWithCommandLineGoogleBaseURL(const GURL& url);


enum SubdomainPermission {
  ALLOW_SUBDOMAIN,
  DISALLOW_SUBDOMAIN,
};

enum PortPermission {
  ALLOW_NON_STANDARD_PORTS,
  DISALLOW_NON_STANDARD_PORTS,
};

bool IsGoogleHostname(const std::string& host,
                      SubdomainPermission subdomain_permission);

bool IsGoogleDomainUrl(const GURL& url,
                       SubdomainPermission subdomain_permission,
                       PortPermission port_permission);

bool IsGoogleHomePageUrl(const GURL& url);

bool IsGoogleSearchUrl(const GURL& url);

bool IsYoutubeDomainUrl(const GURL& url,
                        SubdomainPermission subdomain_permission,
                        PortPermission port_permission);

}  

#endif  
