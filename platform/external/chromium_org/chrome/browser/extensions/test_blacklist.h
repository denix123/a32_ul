// Copyright 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_TEST_BLACKLIST_H_
#define CHROME_BROWSER_EXTENSIONS_TEST_BLACKLIST_H_

#include <map>
#include <string>

#include "base/basictypes.h"
#include "chrome/browser/extensions/blacklist.h"
#include "chrome/browser/extensions/blacklist_state_fetcher.h"

namespace extensions {

class FakeSafeBrowsingDatabaseManager;

class BlacklistStateFetcherMock : public BlacklistStateFetcher {
 public:
  BlacklistStateFetcherMock();

  virtual ~BlacklistStateFetcherMock();

  virtual void Request(const std::string& id,
                       const RequestCallback& callback) OVERRIDE;

  void SetState(const std::string& id, BlacklistState state);

  void Clear();

  int request_count() const { return request_count_; }

 private:
  std::map<std::string, BlacklistState> states_;
  int request_count_;
};


class TestBlacklist {
 public:
  
  
  explicit TestBlacklist();

  explicit TestBlacklist(Blacklist* blacklist);

  ~TestBlacklist();

  void Attach(Blacklist* blacklist);

  
  
  void Detach();

  Blacklist* blacklist() { return blacklist_; }

  
  
  void SetBlacklistState(const std::string& extension_id,
                         BlacklistState state,
                         bool notify);

  BlacklistState GetBlacklistState(const std::string& extension_id);

  void Clear(bool notify);

  void DisableSafeBrowsing();

  void EnableSafeBrowsing();

  void NotifyUpdate();

  const BlacklistStateFetcherMock* fetcher() { return &state_fetcher_mock_; }

 private:
  Blacklist* blacklist_;

  
  
  
  BlacklistStateFetcherMock state_fetcher_mock_;

  scoped_refptr<FakeSafeBrowsingDatabaseManager> blacklist_db_;

  Blacklist::ScopedDatabaseManagerForTest scoped_blacklist_db_;

  DISALLOW_COPY_AND_ASSIGN(TestBlacklist);
};

}  

#endif  
