// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_OMNIBOX_ANSWERS_CACHE_H_
#define COMPONENTS_OMNIBOX_ANSWERS_CACHE_H_

#include <list>

#include "base/basictypes.h"
#include "base/strings/string16.h"

struct AnswersQueryData {
  AnswersQueryData();
  AnswersQueryData(const base::string16& full_query_text,
                   const base::string16& query_type);
  base::string16 full_query_text;
  base::string16 query_type;
};

class AnswersCache {
 public:
  explicit AnswersCache(size_t max_entries);
  ~AnswersCache();

  
  
  AnswersQueryData GetTopAnswerEntry(const base::string16& query);

  
  void UpdateRecentAnswers(const base::string16& full_query_text,
                           const base::string16& query_type);

  
  bool empty() const { return cache_.empty(); }

 private:
  size_t max_entries_;
  typedef std::list<AnswersQueryData> Cache;
  Cache cache_;

  DISALLOW_COPY_AND_ASSIGN(AnswersCache);
};

#endif  
