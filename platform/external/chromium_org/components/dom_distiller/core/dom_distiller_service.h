// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_DOM_DISTILLER_CORE_DOM_DISTILLER_SERVICE_H_
#define COMPONENTS_DOM_DISTILLER_CORE_DOM_DISTILLER_SERVICE_H_

#include <string>
#include <vector>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/memory/weak_ptr.h"
#include "components/dom_distiller/core/article_entry.h"
#include "components/dom_distiller/core/distilled_page_prefs.h"
#include "components/dom_distiller/core/distiller_page.h"

class GURL;

namespace syncer {
class SyncableService;
}

namespace dom_distiller {

class DistilledArticleProto;
class DistilledContentStore;
class DistillerFactory;
class DistillerPageFactory;
class DomDistillerObserver;
class DomDistillerStoreInterface;
class TaskTracker;
class ViewerHandle;
class ViewRequestDelegate;

class DomDistillerServiceInterface {
 public:
  typedef base::Callback<void(bool)> ArticleAvailableCallback;
  virtual ~DomDistillerServiceInterface() {}

  virtual syncer::SyncableService* GetSyncableService() const = 0;

  
  
  
  
  
  
  virtual const std::string AddToList(
      const GURL& url,
      scoped_ptr<DistillerPage> distiller_page,
      const ArticleAvailableCallback& article_cb) = 0;

  
  virtual bool HasEntry(const std::string& entry_id) = 0;

  
  
  
  virtual std::string GetUrlForEntry(const std::string& entry_id) = 0;

  
  virtual std::vector<ArticleEntry> GetEntries() const = 0;

  
  virtual scoped_ptr<ArticleEntry> RemoveEntry(const std::string& entry_id) = 0;

  
  
  
  
  
  
  
  
  virtual scoped_ptr<ViewerHandle> ViewEntry(
      ViewRequestDelegate* delegate,
      scoped_ptr<DistillerPage> distiller_page,
      const std::string& entry_id) = 0;

  
  
  
  
  virtual scoped_ptr<ViewerHandle> ViewUrl(
      ViewRequestDelegate* delegate,
      scoped_ptr<DistillerPage> distiller_page,
      const GURL& url) = 0;

  
  virtual scoped_ptr<DistillerPage> CreateDefaultDistillerPage(
      const gfx::Size& render_view_size) = 0;
  virtual scoped_ptr<DistillerPage> CreateDefaultDistillerPageWithHandle(
      scoped_ptr<SourcePageHandle> handle) = 0;

  virtual void AddObserver(DomDistillerObserver* observer) = 0;
  virtual void RemoveObserver(DomDistillerObserver* observer) = 0;

  
  
  virtual DistilledPagePrefs* GetDistilledPagePrefs() = 0;

 protected:
  DomDistillerServiceInterface() {}

 private:
  DISALLOW_COPY_AND_ASSIGN(DomDistillerServiceInterface);
};

class DomDistillerService : public DomDistillerServiceInterface {
 public:
  DomDistillerService(scoped_ptr<DomDistillerStoreInterface> store,
                      scoped_ptr<DistillerFactory> distiller_factory,
                      scoped_ptr<DistillerPageFactory> distiller_page_factory,
                      scoped_ptr<DistilledPagePrefs> distilled_page_prefs);
  virtual ~DomDistillerService();

  
  virtual syncer::SyncableService* GetSyncableService() const OVERRIDE;
  virtual const std::string AddToList(
      const GURL& url,
      scoped_ptr<DistillerPage> distiller_page,
      const ArticleAvailableCallback& article_cb) OVERRIDE;
  virtual bool HasEntry(const std::string& entry_id) OVERRIDE;
  virtual std::string GetUrlForEntry(const std::string& entry_id) OVERRIDE;
  virtual std::vector<ArticleEntry> GetEntries() const OVERRIDE;
  virtual scoped_ptr<ArticleEntry> RemoveEntry(
      const std::string& entry_id) OVERRIDE;
  virtual scoped_ptr<ViewerHandle> ViewEntry(
      ViewRequestDelegate* delegate,
      scoped_ptr<DistillerPage> distiller_page,
      const std::string& entry_id) OVERRIDE;
  virtual scoped_ptr<ViewerHandle> ViewUrl(
      ViewRequestDelegate* delegate,
      scoped_ptr<DistillerPage> distiller_page,
      const GURL& url) OVERRIDE;
  virtual scoped_ptr<DistillerPage> CreateDefaultDistillerPage(
      const gfx::Size& render_view_size) OVERRIDE;
  virtual scoped_ptr<DistillerPage> CreateDefaultDistillerPageWithHandle(
      scoped_ptr<SourcePageHandle> handle) OVERRIDE;
  virtual void AddObserver(DomDistillerObserver* observer) OVERRIDE;
  virtual void RemoveObserver(DomDistillerObserver* observer) OVERRIDE;
  virtual DistilledPagePrefs* GetDistilledPagePrefs() OVERRIDE;

 private:
  void CancelTask(TaskTracker* task);
  void AddDistilledPageToList(const ArticleEntry& entry,
                              const DistilledArticleProto* article_proto,
                              bool distillation_succeeded);

  TaskTracker* CreateTaskTracker(const ArticleEntry& entry);

  TaskTracker* GetTaskTrackerForEntry(const ArticleEntry& entry) const;

  
  
  
  TaskTracker* GetOrCreateTaskTrackerForUrl(const GURL& url);
  TaskTracker* GetOrCreateTaskTrackerForEntry(const ArticleEntry& entry);

  scoped_ptr<DomDistillerStoreInterface> store_;
  scoped_ptr<DistilledContentStore> content_store_;
  scoped_ptr<DistillerFactory> distiller_factory_;
  scoped_ptr<DistillerPageFactory> distiller_page_factory_;
  scoped_ptr<DistilledPagePrefs> distilled_page_prefs_;

  typedef ScopedVector<TaskTracker> TaskList;
  TaskList tasks_;

  DISALLOW_COPY_AND_ASSIGN(DomDistillerService);
};

}  

#endif  
