// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_OMAHA_QUERY_PARAMS_CHROME_OMAHA_QUERY_PARAMS_DELEGATE_H_
#define CHROME_BROWSER_OMAHA_QUERY_PARAMS_CHROME_OMAHA_QUERY_PARAMS_DELEGATE_H_

#include "components/omaha_query_params/omaha_query_params_delegate.h"

class ChromeOmahaQueryParamsDelegate
    : public omaha_query_params::OmahaQueryParamsDelegate {
 public:
  ChromeOmahaQueryParamsDelegate();
  virtual ~ChromeOmahaQueryParamsDelegate();

  
  static ChromeOmahaQueryParamsDelegate* GetInstance();

  
  virtual std::string GetExtraParams() OVERRIDE;

  
  
  
  static const char* GetChannelString();

  
  
  static const char* GetLang();

 private:
  DISALLOW_COPY_AND_ASSIGN(ChromeOmahaQueryParamsDelegate);
};

#endif  
