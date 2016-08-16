// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
#ifndef COMPONENTS_ENHANCED_BOOKMARKS_BOOKMARK_IMAGE_SERVICE_H_
#define COMPONENTS_ENHANCED_BOOKMARKS_BOOKMARK_IMAGE_SERVICE_H_

#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/singleton.h"
#include "components/bookmarks/browser/bookmark_model_observer.h"
#include "components/enhanced_bookmarks/image_store.h"
#include "components/keyed_service/core/keyed_service.h"
#include "net/url_request/url_request.h"
#include "url/gurl.h"

namespace base {
class SingleThreadTaskRunner;
}
class BookmarkNode;

namespace enhanced_bookmarks {

class EnhancedBookmarkModel;

class BookmarkImageService : public KeyedService,
                             public BookmarkModelObserver,
                             public base::NonThreadSafe {
 public:
  BookmarkImageService(const base::FilePath& path,
                       EnhancedBookmarkModel* enhanced_bookmark_model,
                       scoped_refptr<base::SequencedWorkerPool> pool);
  BookmarkImageService(scoped_ptr<ImageStore> store,
                       EnhancedBookmarkModel* enhanced_bookmark_model,
                       scoped_refptr<base::SequencedWorkerPool> pool);

  virtual ~BookmarkImageService();

  typedef base::Callback<void(const gfx::Image&, const GURL& url)> Callback;

  
  virtual void Shutdown() OVERRIDE;

  
  
  
  
  
  void SalientImageForUrl(const GURL& page_url, Callback callback);

  
  virtual void BookmarkNodeRemoved(BookmarkModel* model,
                                   const BookmarkNode* parent,
                                   int old_index,
                                   const BookmarkNode* node,
                                   const std::set<GURL>& removed_urls) OVERRIDE;
  virtual void BookmarkModelLoaded(BookmarkModel* model,
                                   bool ids_reassigned) OVERRIDE;
  virtual void BookmarkNodeMoved(BookmarkModel* model,
                                 const BookmarkNode* old_parent,
                                 int old_index,
                                 const BookmarkNode* new_parent,
                                 int new_index) OVERRIDE;
  virtual void BookmarkNodeAdded(BookmarkModel* model,
                                 const BookmarkNode* parent,
                                 int index) OVERRIDE;
  virtual void OnWillChangeBookmarkNode(BookmarkModel* model,
                                        const BookmarkNode* node) OVERRIDE;
  virtual void BookmarkNodeChanged(BookmarkModel* model,
                                   const BookmarkNode* node) OVERRIDE;
  virtual void BookmarkNodeFaviconChanged(BookmarkModel* model,
                                          const BookmarkNode* node) OVERRIDE;
  virtual void BookmarkNodeChildrenReordered(BookmarkModel* model,
                                             const BookmarkNode* node) OVERRIDE;
  virtual void BookmarkAllUserNodesRemoved(
      BookmarkModel* model,
      const std::set<GURL>& removed_urls) OVERRIDE;

 protected:
  
  bool IsPageUrlInProgress(const GURL& page_url);

  
  
  void ProcessNewImage(const GURL& page_url,
                       bool update_bookmarks,
                       const gfx::Image& image,
                       const GURL& image_url);

  
  
  
  
  virtual void RetrieveSalientImage(
      const GURL& page_url,
      const GURL& image_url,
      const std::string& referrer,
      net::URLRequest::ReferrerPolicy referrer_policy,
      bool update_bookmark) = 0;

  
  
  virtual void RetrieveSalientImageForPageUrl(const GURL& page_url);

  
  std::set<GURL> in_progress_page_urls_;

  
  EnhancedBookmarkModel* enhanced_bookmark_model_;

 private:
  
  
  void SalientImageForUrl(const GURL& page_url,
                          bool fetch_from_bookmark,
                          Callback stack_callback);

  
  void ProcessRequests(const GURL& page_url,
                       const gfx::Image& image,
                       const GURL& image_url);

  
  void StoreImage(const gfx::Image& image,
                  const GURL& image_url,
                  const GURL& page_url);

  
  
  void FetchCallback(const GURL& page_url,
                     Callback original_callback,
                     const gfx::Image& image,
                     const GURL& image_url);

  
  
  void RemoveImageForUrl(const GURL& url);

  
  void ChangeImageURL(const GURL& from, const GURL& to);

  
  void ClearAll();

  
  
  
  
  
  
  void RetrieveImageFromStore(const GURL& page_url,
                              BookmarkImageService::Callback callback);

  
  scoped_ptr<ImageStore> store_;

  
  std::map<const GURL, std::vector<Callback> > callbacks_;

  
  
  
  GURL previous_url_;

  
  scoped_refptr<base::SequencedWorkerPool> pool_;
  DISALLOW_COPY_AND_ASSIGN(BookmarkImageService);
};

}  

#endif  
