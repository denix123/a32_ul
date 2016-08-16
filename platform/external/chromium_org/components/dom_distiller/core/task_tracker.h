// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_DOM_DISTILLER_CORE_TASK_TRACKER_H_
#define COMPONENTS_DOM_DISTILLER_CORE_TASK_TRACKER_H_

#include <string>
#include <vector>

#include "base/bind.h"
#include "base/callback.h"
#include "base/memory/weak_ptr.h"
#include "components/dom_distiller/core/article_distillation_update.h"
#include "components/dom_distiller/core/article_entry.h"
#include "components/dom_distiller/core/distiller.h"
#include "components/dom_distiller/core/proto/distilled_page.pb.h"

class GURL;

namespace dom_distiller {

class DistilledArticleProto;
class DistilledContentStore;

class ViewerHandle {
 public:
  typedef base::Callback<void()> CancelCallback;
  explicit ViewerHandle(CancelCallback callback);
  ~ViewerHandle();

 private:
  CancelCallback cancel_callback_;
  DISALLOW_COPY_AND_ASSIGN(ViewerHandle);
};

class ViewRequestDelegate {
 public:
  virtual ~ViewRequestDelegate() {}
  
  
  
  
  virtual void OnArticleReady(const DistilledArticleProto* article_proto) = 0;

  
  virtual void OnArticleUpdated(ArticleDistillationUpdate article_update) = 0;
};

class TaskTracker {
 public:
  typedef base::Callback<void(TaskTracker*)> CancelCallback;
  typedef base::Callback<
      void(const ArticleEntry&, const DistilledArticleProto*, bool)>
      SaveCallback;

  TaskTracker(const ArticleEntry& entry,
              CancelCallback callback,
              DistilledContentStore* content_store);
  ~TaskTracker();

  
  void StartDistiller(DistillerFactory* factory,
                      scoped_ptr<DistillerPage> distiller_page);
  void StartBlobFetcher();

  void AddSaveCallback(const SaveCallback& callback);

  void CancelSaveCallbacks();

  
  scoped_ptr<ViewerHandle> AddViewer(ViewRequestDelegate* delegate);

  const std::string& GetEntryId() const;
  bool HasEntryId(const std::string& entry_id) const;
  bool HasUrl(const GURL& url) const;

 private:
  void OnArticleDistillationUpdated(
      const ArticleDistillationUpdate& article_update);

  void OnDistillerFinished(scoped_ptr<DistilledArticleProto> distilled_article);
  void OnBlobFetched(bool success,
                     scoped_ptr<DistilledArticleProto> distilled_article);

  void RemoveViewer(ViewRequestDelegate* delegate);

  void DistilledArticleReady(
      scoped_ptr<DistilledArticleProto> distilled_article);

  
  void ScheduleSaveCallbacks(bool distillation_succeeded);

  
  void DoSaveCallbacks(bool distillation_succeeded);

  void AddDistilledContentToStore(const DistilledArticleProto& content);

  void NotifyViewersAndCallbacks();
  void NotifyViewer(ViewRequestDelegate* delegate);

  bool IsAnySourceRunning() const;
  void ContentSourceFinished();

  void CancelPendingSources();
  void MaybeCancel();

  CancelCallback cancel_callback_;

  DistilledContentStore* content_store_;

  std::vector<SaveCallback> save_callbacks_;
  
  
  std::vector<ViewRequestDelegate*> viewers_;

  scoped_ptr<Distiller> distiller_;
  bool blob_fetcher_running_;

  ArticleEntry entry_;
  scoped_ptr<DistilledArticleProto> distilled_article_;

  bool content_ready_;

  bool destruction_allowed_;

  
  
  base::WeakPtrFactory<TaskTracker> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(TaskTracker);
};

}  

#endif  
