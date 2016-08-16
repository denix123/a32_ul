// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_DOM_DISTILLER_CORE_DISTILLER_H_
#define COMPONENTS_DOM_DISTILLER_CORE_DISTILLER_H_

#include <map>
#include <string>

#include "base/callback.h"
#include "base/containers/hash_tables.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/memory/weak_ptr.h"
#include "components/dom_distiller/core/article_distillation_update.h"
#include "components/dom_distiller/core/distiller_page.h"
#include "components/dom_distiller/core/distiller_url_fetcher.h"
#include "components/dom_distiller/core/proto/distilled_article.pb.h"
#include "net/url_request/url_request_context_getter.h"
#include "url/gurl.h"

namespace dom_distiller {

class DistillerImpl;

class Distiller {
 public:
  typedef base::Callback<void(scoped_ptr<DistilledArticleProto>)>
      DistillationFinishedCallback;
  typedef base::Callback<void(const ArticleDistillationUpdate&)>
      DistillationUpdateCallback;

  virtual ~Distiller() {}

  
  
  
  
  
  
  virtual void DistillPage(const GURL& url,
                           scoped_ptr<DistillerPage> distiller_page,
                           const DistillationFinishedCallback& finished_cb,
                           const DistillationUpdateCallback& update_cb) = 0;
};

class DistillerFactory {
 public:
  virtual scoped_ptr<Distiller> CreateDistiller() = 0;
  virtual ~DistillerFactory() {}
};

class DistillerFactoryImpl : public DistillerFactory {
 public:
  DistillerFactoryImpl(
      scoped_ptr<DistillerURLFetcherFactory> distiller_url_fetcher_factory,
      const dom_distiller::proto::DomDistillerOptions& dom_distiller_options);
  virtual ~DistillerFactoryImpl();
  virtual scoped_ptr<Distiller> CreateDistiller() OVERRIDE;

 private:
  scoped_ptr<DistillerURLFetcherFactory> distiller_url_fetcher_factory_;
  dom_distiller::proto::DomDistillerOptions dom_distiller_options_;
};

class DistillerImpl : public Distiller {
 public:
  DistillerImpl(
      const DistillerURLFetcherFactory& distiller_url_fetcher_factory,
      const dom_distiller::proto::DomDistillerOptions& dom_distiller_options);
  virtual ~DistillerImpl();

  virtual void DistillPage(
      const GURL& url,
      scoped_ptr<DistillerPage> distiller_page,
      const DistillationFinishedCallback& finished_cb,
      const DistillationUpdateCallback& update_cb) OVERRIDE;

  void SetMaxNumPagesInArticle(size_t max_num_pages);

 private:
  
  
  
  

  
  struct DistilledPageData {
    DistilledPageData();
    virtual ~DistilledPageData();
    
    int page_num;
    ScopedVector<DistillerURLFetcher> image_fetchers_;
    scoped_refptr<base::RefCountedData<DistilledPageProto> >
        distilled_page_proto;

   private:
    DISALLOW_COPY_AND_ASSIGN(DistilledPageData);
  };

  void OnFetchImageDone(int page_num,
                        DistillerURLFetcher* url_fetcher,
                        const std::string& id,
                        const std::string& response);

  void OnPageDistillationFinished(
      int page_num,
      const GURL& page_url,
      scoped_ptr<proto::DomDistillerResult> distilled_page,
      bool distillation_successful);

  virtual void FetchImage(int page_num,
                          const std::string& image_id,
                          const std::string& item);

  
  void DistillNextPage();

  
  
  void AddToDistillationQueue(int page_num, const GURL& url);

  
  
  
  bool IsPageNumberInUse(int page_num) const;

  bool AreAllPagesFinished() const;

  
  
  size_t TotalPageCount() const;

  
  
  void RunDistillerCallbackIfDone();

  
  
  void AddPageIfDone(int page_num);

  DistilledPageData* GetPageAtIndex(size_t index) const;

  
  
  const ArticleDistillationUpdate CreateDistillationUpdate() const;

  const DistillerURLFetcherFactory& distiller_url_fetcher_factory_;
  scoped_ptr<DistillerPage> distiller_page_;

  dom_distiller::proto::DomDistillerOptions dom_distiller_options_;
  DistillationFinishedCallback finished_cb_;
  DistillationUpdateCallback update_cb_;

  
  
  
  ScopedVector<DistilledPageData> pages_;

  
  std::map<int, size_t> finished_pages_index_;

  
  
  
  base::hash_map<int, size_t> started_pages_index_;

  
  
  
  std::map<int, GURL> waiting_pages_;

  
  
  base::hash_set<std::string> seen_urls_;

  size_t max_pages_in_article_;

  bool destruction_allowed_;

  base::WeakPtrFactory<DistillerImpl> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(DistillerImpl);
};

}  

#endif  
