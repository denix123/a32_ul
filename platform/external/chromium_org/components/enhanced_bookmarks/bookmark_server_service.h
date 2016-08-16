// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_ENHANCED_BOOKMARKS_BOOKMARK_SERVER_SERVICE_H_
#define COMPONENTS_ENHANCED_BOOKMARKS_BOOKMARK_SERVER_SERVICE_H_

#include <string>
#include <vector>

#include "components/enhanced_bookmarks/enhanced_bookmark_model_observer.h"
#include "google_apis/gaia/google_service_auth_error.h"
#include "google_apis/gaia/oauth2_token_service.h"
#include "net/url_request/url_fetcher.h"
#include "net/url_request/url_fetcher_delegate.h"
#include "net/url_request/url_request_context_getter.h"

class ProfileOAuth2TokenService;
class SigninManagerBase;
class BookmarkNode;

namespace enhanced_bookmarks {

class BookmarkServerService;
class EnhancedBookmarkModel;

class BookmarkServerServiceObserver {
 public:
  virtual void OnChange(BookmarkServerService* service) = 0;

 protected:
  virtual ~BookmarkServerServiceObserver() {}
};

class BookmarkServerService : protected net::URLFetcherDelegate,
                              private OAuth2TokenService::Consumer,
                              public EnhancedBookmarkModelObserver {
 public:
  BookmarkServerService(
      scoped_refptr<net::URLRequestContextGetter> request_context_getter,
      ProfileOAuth2TokenService* token_service,
      SigninManagerBase* signin_manager,
      EnhancedBookmarkModel* enhanced_bookmark_model);
  virtual ~BookmarkServerService();

  void AddObserver(BookmarkServerServiceObserver* observer);
  void RemoveObserver(BookmarkServerServiceObserver* observer);

 protected:
  
  
  virtual const BookmarkNode* BookmarkForRemoteId(
      const std::string& remote_id) const;
  const std::string RemoteIDForBookmark(const BookmarkNode* bookmark) const;

  
  void Notify();

  
  void TriggerTokenRequest(bool cancel_previous);

  
  virtual net::URLFetcher* CreateFetcher() = 0;

  
  
  
  
  virtual bool ProcessResponse(const std::string& response,
                               bool* should_notify) = 0;

  
  virtual void CleanAfterFailure() = 0;

  
  virtual void EnhancedBookmarkModelShuttingDown() OVERRIDE;

  SigninManagerBase* GetSigninManager();

  
  EnhancedBookmarkModel* model_;  

 private:
  FRIEND_TEST_ALL_PREFIXES(BookmarkServerServiceTest, Cluster);
  FRIEND_TEST_ALL_PREFIXES(BookmarkServerServiceTest,
                           ClearClusterMapOnRemoveAllBookmarks);

  
  virtual void OnURLFetchComplete(const net::URLFetcher* source) OVERRIDE;

  
  virtual void OnGetTokenSuccess(const OAuth2TokenService::Request* request,
                                 const std::string& access_token,
                                 const base::Time& expiration_time) OVERRIDE;
  virtual void OnGetTokenFailure(const OAuth2TokenService::Request* request,
                                 const GoogleServiceAuthError& error) OVERRIDE;

  
  ObserverList<BookmarkServerServiceObserver> observers_;
  
  ProfileOAuth2TokenService* token_service_;  
  
  scoped_ptr<OAuth2TokenService::Request> token_request_;
  
  SigninManagerBase* signin_manager_;  
  
  scoped_refptr<net::URLRequestContextGetter> request_context_getter_;
  
  scoped_ptr<net::URLFetcher> url_fetcher_;
  
  std::map<std::string, const BookmarkNode*> starsid_to_bookmark_;

  DISALLOW_COPY_AND_ASSIGN(BookmarkServerService);
};
}  

#endif  
