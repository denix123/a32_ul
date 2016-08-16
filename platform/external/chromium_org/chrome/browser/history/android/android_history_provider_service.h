// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_HISTORY_ANDROID_ANDROID_HISTORY_PROVIDER_SERVICE_H_
#define CHROME_BROWSER_HISTORY_ANDROID_ANDROID_HISTORY_PROVIDER_SERVICE_H_

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/task/cancelable_task_tracker.h"
#include "components/history/core/android/android_history_types.h"
#include "sql/statement.h"

class Profile;

class AndroidHistoryProviderService {
 public:
  explicit AndroidHistoryProviderService(Profile* profile);
  virtual ~AndroidHistoryProviderService();

  

  
  
  typedef base::Callback<void(history::AndroidStatement*)> QueryCallback;

  
  
  typedef base::Callback<void(int)> UpdateCallback;

  
  
  typedef base::Callback<void(int64)> InsertCallback;

  
  
  typedef base::Callback<void(int)> DeleteCallback;

  
  
  
  typedef base::Callback<void(int)> MoveStatementCallback;

  
  
  
  
  
  
  
  
  
  base::CancelableTaskTracker::TaskId QueryHistoryAndBookmarks(
      const std::vector<history::HistoryAndBookmarkRow::ColumnID>& projections,
      const std::string& selection,
      const std::vector<base::string16>& selection_args,
      const std::string& sort_order,
      const QueryCallback& callback,
      base::CancelableTaskTracker* tracker);

  
  
  
  
  
  
  base::CancelableTaskTracker::TaskId UpdateHistoryAndBookmarks(
      const history::HistoryAndBookmarkRow& row,
      const std::string& selection,
      const std::vector<base::string16>& selection_args,
      const UpdateCallback& callback,
      base::CancelableTaskTracker* tracker);

  
  
  
  
  
  
  
  base::CancelableTaskTracker::TaskId DeleteHistoryAndBookmarks(
      const std::string& selection,
      const std::vector<base::string16>& selection_args,
      const DeleteCallback& callback,
      base::CancelableTaskTracker* tracker);

  
  
  base::CancelableTaskTracker::TaskId InsertHistoryAndBookmark(
      const history::HistoryAndBookmarkRow& values,
      const InsertCallback& callback,
      base::CancelableTaskTracker* tracker);

  
  
  base::CancelableTaskTracker::TaskId DeleteHistory(
      const std::string& selection,
      const std::vector<base::string16>& selection_args,
      const DeleteCallback& callback,
      base::CancelableTaskTracker* tracker);

  
  
  
  
  base::CancelableTaskTracker::TaskId MoveStatement(
      history::AndroidStatement* statement,
      int current_pos,
      int destination,
      const MoveStatementCallback& callback,
      base::CancelableTaskTracker* tracker);

  
  
  void CloseStatement(history::AndroidStatement* statement);

  
  
  
  base::CancelableTaskTracker::TaskId InsertSearchTerm(
      const history::SearchRow& row,
      const InsertCallback& callback,
      base::CancelableTaskTracker* tracker);

  
  
  
  
  
  
  base::CancelableTaskTracker::TaskId UpdateSearchTerms(
      const history::SearchRow& row,
      const std::string& selection,
      const std::vector<base::string16>& selection_args,
      const UpdateCallback& callback,
      base::CancelableTaskTracker* tracker);

  
  
  
  
  
  
  
  base::CancelableTaskTracker::TaskId DeleteSearchTerms(
      const std::string& selection,
      const std::vector<base::string16>& selection_args,
      const DeleteCallback& callback,
      base::CancelableTaskTracker* tracker);

  
  
  
  
  
  
  
  base::CancelableTaskTracker::TaskId QuerySearchTerms(
      const std::vector<history::SearchRow::ColumnID>& projections,
      const std::string& selection,
      const std::vector<base::string16>& selection_args,
      const std::string& sort_order,
      const QueryCallback& callback,
      base::CancelableTaskTracker* tracker);

 private:
  Profile* profile_;

  DISALLOW_COPY_AND_ASSIGN(AndroidHistoryProviderService);
};

#endif  
