// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_BROWSING_DATA_BROWSING_DATA_CHANNEL_ID_HELPER_H_
#define CHROME_BROWSER_BROWSING_DATA_BROWSING_DATA_CHANNEL_ID_HELPER_H_

#include <map>
#include <string>

#include "base/callback.h"
#include "net/ssl/channel_id_store.h"

namespace net {
class URLRequestContextGetter;
}

class BrowsingDataChannelIDHelper
    : public base::RefCountedThreadSafe<BrowsingDataChannelIDHelper> {
 public:
  
  
  static BrowsingDataChannelIDHelper* Create(
      net::URLRequestContextGetter* request_context);

  typedef base::Callback<
      void(const net::ChannelIDStore::ChannelIDList&)>
      FetchResultCallback;

  
  
  
  virtual void StartFetching(const FetchResultCallback& callback) = 0;
  
  
  virtual void DeleteChannelID(const std::string& server_id) = 0;

 protected:
  friend class base::RefCountedThreadSafe<BrowsingDataChannelIDHelper>;
  virtual ~BrowsingDataChannelIDHelper() {}
};

class CannedBrowsingDataChannelIDHelper
    : public BrowsingDataChannelIDHelper {
 public:
  CannedBrowsingDataChannelIDHelper();

  
  
  void AddChannelID(
      const net::ChannelIDStore::ChannelID& channel_id);

  
  void Reset();

  
  bool empty() const;

  
  size_t GetChannelIDCount() const;

  
  virtual void StartFetching(const FetchResultCallback& callback) OVERRIDE;
  virtual void DeleteChannelID(const std::string& server_id) OVERRIDE;

 private:
  virtual ~CannedBrowsingDataChannelIDHelper();

  void FinishFetching();

  typedef std::map<std::string, net::ChannelIDStore::ChannelID>
      ChannelIDMap;
  ChannelIDMap channel_id_map_;

  FetchResultCallback completion_callback_;

  DISALLOW_COPY_AND_ASSIGN(CannedBrowsingDataChannelIDHelper);
};

#endif  
