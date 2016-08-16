// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_ENHANCED_BOOKMARKS_BOOKMARK_SERVER_SEARCH_SERVICE_H_
#define COMPONENTS_ENHANCED_BOOKMARKS_BOOKMARK_SERVER_SEARCH_SERVICE_H_

#include <string>
#include <vector>

#include "components/bookmarks/browser/base_bookmark_model_observer.h"
#include "components/enhanced_bookmarks/bookmark_server_service.h"
#include "net/url_request/url_fetcher.h"

namespace enhanced_bookmarks {

class EnhancedBookmarkModel;

class BookmarkServerSearchService : public BookmarkServerService {
 public:
  BookmarkServerSearchService(
      scoped_refptr<net::URLRequestContextGetter> request_context_getter,
      ProfileOAuth2TokenService* token_service,
      SigninManagerBase* signin_manager,
      EnhancedBookmarkModel* bookmark_model);
  virtual ~BookmarkServerSearchService();

  
  
  
  void Search(const std::string& query);

  
  
  
  std::vector<const BookmarkNode*> ResultForQuery(const std::string& query);

 protected:

  virtual net::URLFetcher* CreateFetcher() OVERRIDE;

  virtual bool ProcessResponse(const std::string& response,
                               bool* should_notify) OVERRIDE;

  virtual void CleanAfterFailure() OVERRIDE;

  
  virtual void EnhancedBookmarkModelLoaded() OVERRIDE{};
  virtual void EnhancedBookmarkAdded(const BookmarkNode* node) OVERRIDE;
  virtual void EnhancedBookmarkRemoved(const BookmarkNode* node) OVERRIDE{};
  virtual void EnhancedBookmarkAllUserNodesRemoved() OVERRIDE;
  virtual void EnhancedBookmarkRemoteIdChanged(
      const BookmarkNode* node,
      const std::string& old_remote_id,
      const std::string& remote_id) OVERRIDE;

 private:
  
  std::map<std::string, std::vector<std::string> > searches_;
  std::string current_query_;
  DISALLOW_COPY_AND_ASSIGN(BookmarkServerSearchService);
};
}  

#endif  
