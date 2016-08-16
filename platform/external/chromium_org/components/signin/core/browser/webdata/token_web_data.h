// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// information and MUST not be extracted, overwritten or modified except

#ifndef COMPONENTS_SIGNIN_CORE_BROWSER_WEBDATA_TOKEN_WEB_DATA_H__
#define COMPONENTS_SIGNIN_CORE_BROWSER_WEBDATA_TOKEN_WEB_DATA_H__

#include <map>
#include <string>
#include <vector>

#include "base/callback_forward.h"
#include "base/files/file_path.h"
#include "base/location.h"
#include "base/memory/ref_counted.h"
#include "components/webdata/common/web_data_results.h"
#include "components/webdata/common/web_data_service_base.h"
#include "components/webdata/common/web_data_service_consumer.h"
#include "components/webdata/common/web_database.h"

namespace base {
class MessageLoopProxy;
}

class TokenWebDataBackend;
class WebDatabaseService;
class WebDataServiceConsumer;


class TokenWebData : public WebDataServiceBase {
 public:
  TokenWebData(scoped_refptr<WebDatabaseService> wdbs,
               scoped_refptr<base::MessageLoopProxy> ui_thread,
               scoped_refptr<base::MessageLoopProxy> db_thread,
               const ProfileErrorCallback& callback);

  TokenWebData(scoped_refptr<base::MessageLoopProxy> ui_thread,
               scoped_refptr<base::MessageLoopProxy> db_thread);

  
  void SetTokenForService(const std::string& service,
                          const std::string& token);

  
  void RemoveAllTokens();

  
  void RemoveTokenForService(const std::string& service);

  
  virtual Handle GetAllTokens(WebDataServiceConsumer* consumer);

 protected:
  
  TokenWebData();

  virtual ~TokenWebData();

 private:
  scoped_refptr<TokenWebDataBackend> token_backend_;

  DISALLOW_COPY_AND_ASSIGN(TokenWebData);
};

#endif  
