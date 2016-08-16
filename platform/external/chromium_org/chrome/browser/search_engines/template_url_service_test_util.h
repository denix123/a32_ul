// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SEARCH_ENGINES_TEMPLATE_URL_SERVICE_TEST_UTIL_H_
#define CHROME_BROWSER_SEARCH_ENGINES_TEMPLATE_URL_SERVICE_TEST_UTIL_H_

#include <string>

#include "base/basictypes.h"
#include "base/files/scoped_temp_dir.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "components/search_engines/template_url_service_observer.h"

class GURL;
class KeywordWebDataService;
class TemplateURLService;
class TestingProfile;
class TestingSearchTermsData;

class TemplateURLServiceTestUtil : public TemplateURLServiceObserver {
 public:
  TemplateURLServiceTestUtil();
  virtual ~TemplateURLServiceTestUtil();

  
  virtual void OnTemplateURLServiceChanged() OVERRIDE;

  
  int GetObserverCount();

  
  void ResetObserverCount();

  
  void VerifyLoad();

  
  
  
  void ChangeModelToLoadState();

  
  void ClearModel();

  
  void ResetModel(bool verify_load);

  
  
  base::string16 GetAndClearSearchTerm();

  
  void SetGoogleBaseURL(const GURL& base_url);

  
  
  
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

  KeywordWebDataService* web_data_service() { return web_data_service_.get(); }
  TemplateURLService* model() { return model_.get(); }
  TestingProfile* profile() { return profile_.get(); }

 private:
  scoped_ptr<TestingProfile> profile_;
  base::ScopedTempDir temp_dir_;
  int changed_count_;
  base::string16 search_term_;
  scoped_refptr<KeywordWebDataService> web_data_service_;
  TestingSearchTermsData* search_terms_data_;
  scoped_ptr<TemplateURLService> model_;

  DISALLOW_COPY_AND_ASSIGN(TemplateURLServiceTestUtil);
};

#endif  
