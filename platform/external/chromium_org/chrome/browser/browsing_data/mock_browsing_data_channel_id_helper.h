// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_BROWSING_DATA_MOCK_BROWSING_DATA_CHANNEL_ID_HELPER_H_
#define CHROME_BROWSER_BROWSING_DATA_MOCK_BROWSING_DATA_CHANNEL_ID_HELPER_H_

#include <map>
#include <string>

#include "chrome/browser/browsing_data/browsing_data_channel_id_helper.h"

class MockBrowsingDataChannelIDHelper
    : public BrowsingDataChannelIDHelper {
 public:
  MockBrowsingDataChannelIDHelper();

  
  virtual void StartFetching(const FetchResultCallback& callback) OVERRIDE;
  virtual void DeleteChannelID(const std::string& server_id) OVERRIDE;

  
  void AddChannelIDSample(const std::string& server_id);

  
  void Notify();

  
  void Reset();

  
  
  bool AllDeleted();

 private:
  virtual ~MockBrowsingDataChannelIDHelper();

  FetchResultCallback callback_;

  net::ChannelIDStore::ChannelIDList channel_id_list_;

  
  std::map<const std::string, bool> channel_ids_;

  DISALLOW_COPY_AND_ASSIGN(MockBrowsingDataChannelIDHelper);
};

#endif  
