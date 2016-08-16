// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_COMPONENT_UPDATER_TEST_URL_REQUEST_POST_INTERCEPTOR_H_
#define COMPONENTS_COMPONENT_UPDATER_TEST_URL_REQUEST_POST_INTERCEPTOR_H_

#include <stdint.h>
#include <map>
#include <queue>
#include <string>
#include <utility>
#include <vector>

#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/synchronization/lock.h"
#include "url/gurl.h"

namespace base {
class FilePath;
class SequencedTaskRunner;
}

namespace net {
class URLRequest;
}

namespace component_updater {

const uint8_t jebg_hash[] = {0x94, 0x16, 0x0b, 0x6d, 0x41, 0x75, 0xe9, 0xec,
                             0x8e, 0xd5, 0xfa, 0x54, 0xb0, 0xd2, 0xdd, 0xa5,
                             0x6e, 0x05, 0x6b, 0xe8, 0x73, 0x47, 0xf6, 0xc4,
                             0x11, 0x9f, 0xbc, 0xb3, 0x09, 0xb3, 0x5b, 0x40};
const uint8_t abag_hash[] = {0x01, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
                             0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
                             0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
                             0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x01};
const uint8_t ihfo_hash[] = {0x87, 0x5e, 0xa1, 0xa6, 0x9f, 0x85, 0xd1, 0x1e,
                             0x97, 0xd4, 0x4f, 0x55, 0xbf, 0xb4, 0x13, 0xa2,
                             0xe7, 0xc5, 0xc8, 0xf5, 0x60, 0x19, 0x78, 0x1b,
                             0x6d, 0xe9, 0x4c, 0xeb, 0x96, 0x05, 0x42, 0x17};

class URLRequestPostInterceptor {
 public:
  
  class RequestMatcher {
   public:
    virtual bool Match(const std::string& actual) const = 0;
    virtual ~RequestMatcher() {}
  };

  
  GURL GetUrl() const;

  
  
  
  
  
  
  
  bool ExpectRequest(class RequestMatcher* request_matcher);
  bool ExpectRequest(class RequestMatcher* request_matcher, int response_code);
  bool ExpectRequest(class RequestMatcher* request_matcher,
                     const base::FilePath& filepath);

  
  
  int GetHitCount() const;

  
  int GetCount() const;

  
  std::vector<std::string> GetRequests() const;

  
  std::string GetRequestsAsString() const;

  
  void Reset();

  class Delegate;

 private:
  friend class URLRequestPostInterceptorFactory;

  static const int kResponseCode200 = 200;

  struct ExpectationResponse {
    ExpectationResponse(int code, const std::string& body)
        : response_code(code), response_body(body) {}
    const int response_code;
    const std::string response_body;
  };
  typedef std::pair<const RequestMatcher*, ExpectationResponse> Expectation;

  URLRequestPostInterceptor(
      const GURL& url,
      const scoped_refptr<base::SequencedTaskRunner>& io_task_runner);
  ~URLRequestPostInterceptor();

  void ClearExpectations();

  const GURL url_;
  scoped_refptr<base::SequencedTaskRunner> io_task_runner_;

  mutable base::Lock interceptor_lock_;
  mutable int hit_count_;
  mutable std::vector<std::string> requests_;
  mutable std::queue<Expectation> expectations_;

  DISALLOW_COPY_AND_ASSIGN(URLRequestPostInterceptor);
};

class URLRequestPostInterceptorFactory {
 public:
  URLRequestPostInterceptorFactory(
      const std::string& scheme,
      const std::string& hostname,
      const scoped_refptr<base::SequencedTaskRunner>& io_task_runner);
  ~URLRequestPostInterceptorFactory();

  
  
  
  URLRequestPostInterceptor* CreateInterceptor(const base::FilePath& filepath);

 private:
  const std::string scheme_;
  const std::string hostname_;
  scoped_refptr<base::SequencedTaskRunner> io_task_runner_;

  
  
  
  URLRequestPostInterceptor::Delegate* delegate_;

  DISALLOW_COPY_AND_ASSIGN(URLRequestPostInterceptorFactory);
};

class InterceptorFactory : public URLRequestPostInterceptorFactory {
 public:
  explicit InterceptorFactory(
      const scoped_refptr<base::SequencedTaskRunner>& io_task_runner);
  ~InterceptorFactory();

  
  URLRequestPostInterceptor* CreateInterceptor();

  
  URLRequestPostInterceptor* CreateInterceptorForPath(const char* url_path);

 private:
  DISALLOW_COPY_AND_ASSIGN(InterceptorFactory);
};

class PartialMatch : public URLRequestPostInterceptor::RequestMatcher {
 public:
  explicit PartialMatch(const std::string& expected) : expected_(expected) {}
  virtual bool Match(const std::string& actual) const OVERRIDE;

 private:
  const std::string expected_;

  DISALLOW_COPY_AND_ASSIGN(PartialMatch);
};

}  

#endif  
