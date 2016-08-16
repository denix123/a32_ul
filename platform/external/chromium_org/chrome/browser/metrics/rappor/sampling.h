// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_METRICS_RAPPOR_SAMPLING_H_
#define CHROME_BROWSER_METRICS_RAPPOR_SAMPLING_H_

#include <string>

class GURL;

namespace rappor {

std::string GetDomainAndRegistrySampleFromGURL(const GURL& gurl);

void SampleDomainAndRegistryFromGURL(const std::string& metric,
                                     const GURL& gurl);

}  

#endif  
