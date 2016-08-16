// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SIGNIN_FAKE_PROFILE_OAUTH2_TOKEN_SERVICE_BUILDER_H_
#define CHROME_BROWSER_SIGNIN_FAKE_PROFILE_OAUTH2_TOKEN_SERVICE_BUILDER_H_

class KeyedService;

namespace content {
class BrowserContext;
}

KeyedService* BuildFakeProfileOAuth2TokenService(
    content::BrowserContext* context);

KeyedService* BuildAutoIssuingFakeProfileOAuth2TokenService(
    content::BrowserContext* context);

#endif  
