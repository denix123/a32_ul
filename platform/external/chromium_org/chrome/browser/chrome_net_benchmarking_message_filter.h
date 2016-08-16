// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROME_NET_BENCHMARKING_MESSAGE_FILTER_H_
#define CHROME_BROWSER_CHROME_NET_BENCHMARKING_MESSAGE_FILTER_H_

#include "content/public/browser/browser_message_filter.h"

namespace net {
class URLRequestContextGetter;
}

class Profile;

class ChromeNetBenchmarkingMessageFilter
    : public content::BrowserMessageFilter {
 public:
  ChromeNetBenchmarkingMessageFilter(
      Profile* profile,
      net::URLRequestContextGetter* request_context);

  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

 private:
  virtual ~ChromeNetBenchmarkingMessageFilter();

  
  void OnCloseCurrentConnections();
  void OnClearCache(IPC::Message* reply_msg);
  void OnClearHostResolverCache(int* result);
  void OnSetCacheMode(bool enabled);
  void OnClearPredictorCache(int* result);

  
  bool CheckBenchmarkingEnabled() const;

  
  
  Profile* profile_;
  scoped_refptr<net::URLRequestContextGetter> request_context_;

  DISALLOW_COPY_AND_ASSIGN(ChromeNetBenchmarkingMessageFilter);
};

#endif  

