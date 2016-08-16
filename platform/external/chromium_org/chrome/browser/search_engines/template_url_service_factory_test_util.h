// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SEARCH_ENGINES_TEMPLATE_URL_SERVICE_FACTORY_TEST_UTIL_H_
#define CHROME_BROWSER_SEARCH_ENGINES_TEMPLATE_URL_SERVICE_FACTORY_TEST_UTIL_H_

#include <string>

#include "base/basictypes.h"

class TemplateURLService;
class TestingProfile;

class TemplateURLServiceFactoryTestUtil {
 public:
  explicit TemplateURLServiceFactoryTestUtil(TestingProfile* profile);
  virtual ~TemplateURLServiceFactoryTestUtil();

  
  void VerifyLoad();

  
  
  
  void SetManagedDefaultSearchPreferences(
      bool enabled,
      const std::string& name,
      const std::string& keyword,
      const std::string& search_url,
      const std::string& suggest_url,
      const std::string& icon_url,
      const std::string& encodings,
      const std::string& alternate_url,
      const std::string& search_terms_replacement_key);

  
  
  void RemoveManagedDefaultSearchPreferences();

  
  TemplateURLService* model() const;

 private:
  TestingProfile* profile_;

  DISALLOW_COPY_AND_ASSIGN(TemplateURLServiceFactoryTestUtil);
};

#endif  
