// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SEARCH_ENGINES_KEYWORD_WEB_DATA_SERVICE_H__
#define COMPONENTS_SEARCH_ENGINES_KEYWORD_WEB_DATA_SERVICE_H__

#include "base/memory/ref_counted.h"
#include "components/search_engines/keyword_table.h"
#include "components/search_engines/template_url_id.h"
#include "components/webdata/common/web_data_service_base.h"
#include "components/webdata/common/web_database.h"

namespace base {
class MessageLoopProxy;
}

class WDTypedResult;
class WebDatabaseService;
struct TemplateURLData;

struct WDKeywordsResult {
  WDKeywordsResult();
  ~WDKeywordsResult();

  KeywordTable::Keywords keywords;
  
  
  int64 default_search_provider_id;
  
  int builtin_keyword_version;
};

class WebDataServiceConsumer;

class KeywordWebDataService : public WebDataServiceBase {
 public:
  
  
  
  
  
  
  
  
  
  
  class BatchModeScoper {
   public:
    explicit BatchModeScoper(KeywordWebDataService* service);
    ~BatchModeScoper();

   private:
    KeywordWebDataService* service_;

    DISALLOW_COPY_AND_ASSIGN(BatchModeScoper);
  };

  KeywordWebDataService(scoped_refptr<WebDatabaseService> wdbs,
                        scoped_refptr<base::MessageLoopProxy> ui_thread,
                        const ProfileErrorCallback& callback);

  
  
  
  
  
  

  void AddKeyword(const TemplateURLData& data);
  void RemoveKeyword(TemplateURLID id);
  void UpdateKeyword(const TemplateURLData& data);

  
  
  Handle GetKeywords(WebDataServiceConsumer* consumer);

  
  void SetDefaultSearchProviderID(TemplateURLID id);

  
  void SetBuiltinKeywordVersion(int version);

 protected:
  virtual ~KeywordWebDataService();

 private:
  
  void AdjustBatchModeLevel(bool entering_batch_mode);

  
  
  
  
  
  WebDatabase::State PerformKeywordOperationsImpl(
      const KeywordTable::Operations& operations,
      WebDatabase* db);
  scoped_ptr<WDTypedResult> GetKeywordsImpl(WebDatabase* db);
  WebDatabase::State SetDefaultSearchProviderIDImpl(TemplateURLID id,
                                                    WebDatabase* db);
  WebDatabase::State SetBuiltinKeywordVersionImpl(int version, WebDatabase* db);

  size_t batch_mode_level_;
  KeywordTable::Operations queued_keyword_operations_;

  DISALLOW_COPY_AND_ASSIGN(KeywordWebDataService);
};

#endif  
