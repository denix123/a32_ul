// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_URL_REQUEST_TEST_URL_REQUEST_INTERCEPTOR_H_
#define NET_URL_REQUEST_TEST_URL_REQUEST_INTERCEPTOR_H_

#include <string>

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"

class GURL;

namespace base {
class FilePath;
class TaskRunner;
}

namespace net {

class TestURLRequestInterceptor {
 public:
  
  
  
  
  
  
  
  TestURLRequestInterceptor(
      const std::string& scheme,
      const std::string& hostname,
      const scoped_refptr<base::TaskRunner>& network_task_runner,
      const scoped_refptr<base::TaskRunner>& worker_task_runner);
  virtual ~TestURLRequestInterceptor();

  
  
  
  void SetResponse(const GURL& url, const base::FilePath& path);

  
  
  void SetResponseIgnoreQuery(const GURL& url, const base::FilePath& path);

  
  int GetHitCount();

 private:
  class Delegate;

  const std::string scheme_;
  const std::string hostname_;

  scoped_refptr<base::TaskRunner> network_task_runner_;

  
  
  
  Delegate* delegate_;

  DISALLOW_COPY_AND_ASSIGN(TestURLRequestInterceptor);
};

class LocalHostTestURLRequestInterceptor : public TestURLRequestInterceptor {
 public:
  LocalHostTestURLRequestInterceptor(
      const scoped_refptr<base::TaskRunner>& network_task_runner,
      const scoped_refptr<base::TaskRunner>& worker_task_runner);

 private:
  DISALLOW_COPY_AND_ASSIGN(LocalHostTestURLRequestInterceptor);
};

}  

#endif  
