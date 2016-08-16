// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef NET_BASE_SDCH_DICTIONARY_FETCHER_H_
#define NET_BASE_SDCH_DICTIONARY_FETCHER_H_

#include <queue>
#include <set>
#include <string>

#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/non_thread_safe.h"
#include "net/base/sdch_manager.h"
#include "net/url_request/url_fetcher_delegate.h"
#include "net/url_request/url_request.h"

namespace net {

class URLRequest;
class URLRequestThrottlerEntryInterface;

class NET_EXPORT SdchDictionaryFetcher
    : public SdchFetcher,
      public URLRequest::Delegate,
      public base::NonThreadSafe {
 public:
  
  
  SdchDictionaryFetcher(SdchFetcher::Delegate* consumer,
                        URLRequestContext* context);
  virtual ~SdchDictionaryFetcher();

  
  virtual void Schedule(const GURL& dictionary_url) OVERRIDE;
  virtual void Cancel() OVERRIDE;

  
  virtual void OnResponseStarted(URLRequest* request) OVERRIDE;
  virtual void OnReadCompleted(URLRequest* request, int bytes_read) OVERRIDE;

 private:
  enum State {
    STATE_NONE,
    STATE_IDLE,
    STATE_REQUEST_STARTED,
    STATE_REQUEST_READING,
    STATE_REQUEST_COMPLETE,
  };

  
  int DoLoop(int rv);
  int DoDispatchRequest(int rv);
  int DoRequestStarted(int rv);
  int DoRead(int rv);
  int DoCompleteRequest(int rv);

  State next_state_;
  bool in_loop_;

  SdchFetcher::Delegate* const consumer_;

  
  std::queue<GURL> fetch_queue_;

  
  
  scoped_ptr<URLRequest> current_request_;
  scoped_refptr<IOBuffer> buffer_;

  
  std::string dictionary_;

  
  
  
  
  
  
  
  
  
  
  
  
  
  std::set<GURL> attempted_load_;

  
  
  URLRequestContext* context_;

  base::WeakPtrFactory<SdchDictionaryFetcher> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(SdchDictionaryFetcher);
};

}  

#endif  
