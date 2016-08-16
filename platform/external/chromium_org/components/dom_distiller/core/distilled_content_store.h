// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_DOM_DISTILLER_CORE_DOM_DISTILLER_CONTENT_STORE_H_
#define COMPONENTS_DOM_DISTILLER_CORE_DOM_DISTILLER_CONTENT_STORE_H_

#include <string>

#include "base/bind.h"
#include "base/containers/hash_tables.h"
#include "base/containers/mru_cache.h"
#include "components/dom_distiller/core/article_entry.h"
#include "components/dom_distiller/core/proto/distilled_article.pb.h"

namespace dom_distiller {

const int kDefaultMaxNumCachedEntries = 32;

class DistilledContentStore {
 public:
  typedef base::Callback<
      void(bool , scoped_ptr<DistilledArticleProto>)> LoadCallback;
  typedef base::Callback<void(bool )> SaveCallback;

  virtual void SaveContent(const ArticleEntry& entry,
                           const DistilledArticleProto& proto,
                           SaveCallback callback) = 0;
  virtual void LoadContent(const ArticleEntry& entry,
                           LoadCallback callback) = 0;

  DistilledContentStore() {};
  virtual ~DistilledContentStore() {};

 private:
  DISALLOW_COPY_AND_ASSIGN(DistilledContentStore);
};

class InMemoryContentStore : public DistilledContentStore {
 public:
  explicit InMemoryContentStore(const int max_num_entries);
  virtual ~InMemoryContentStore();

  
  virtual void SaveContent(const ArticleEntry& entry,
                           const DistilledArticleProto& proto,
                           SaveCallback callback) OVERRIDE;
  virtual void LoadContent(const ArticleEntry& entry,
                           LoadCallback callback) OVERRIDE;

  
  void InjectContent(const ArticleEntry& entry,
                     const DistilledArticleProto& proto);

 private:
  
  class CacheDeletor {
   public:
    explicit CacheDeletor(InMemoryContentStore* store);
    ~CacheDeletor();
    void operator()(const DistilledArticleProto& proto);

   private:
    InMemoryContentStore* store_;
  };

  void AddUrlToIdMapping(const ArticleEntry& entry,
                         const DistilledArticleProto& proto);

  void EraseUrlToIdMapping(const DistilledArticleProto& proto);

  typedef base::MRUCacheBase<std::string,
                             DistilledArticleProto,
                             InMemoryContentStore::CacheDeletor> ContentMap;
  typedef base::hash_map<std::string, std::string> UrlMap;

  ContentMap cache_;
  UrlMap url_to_id_;
};

}  

#endif  
