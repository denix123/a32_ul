// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_PREFS_JSON_PREF_STORE_H_
#define BASE_PREFS_JSON_PREF_STORE_H_

#include <set>
#include <string>

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/compiler_specific.h"
#include "base/files/file_path.h"
#include "base/files/important_file_writer.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/message_loop/message_loop_proxy.h"
#include "base/observer_list.h"
#include "base/prefs/base_prefs_export.h"
#include "base/prefs/persistent_pref_store.h"
#include "base/threading/non_thread_safe.h"

class PrefFilter;

namespace base {
class DictionaryValue;
class FilePath;
class SequencedTaskRunner;
class SequencedWorkerPool;
class Value;
}

class BASE_PREFS_EXPORT JsonPrefStore
    : public PersistentPrefStore,
      public base::ImportantFileWriter::DataSerializer,
      public base::SupportsWeakPtr<JsonPrefStore>,
      public base::NonThreadSafe {
 public:
  struct ReadResult;

  
  
  static scoped_refptr<base::SequencedTaskRunner> GetTaskRunnerForFile(
      const base::FilePath& pref_filename,
      base::SequencedWorkerPool* worker_pool);

  
  JsonPrefStore(
      const base::FilePath& pref_filename,
      const scoped_refptr<base::SequencedTaskRunner>& sequenced_task_runner,
      scoped_ptr<PrefFilter> pref_filter);

  
  
  
  
  // desired prefs may have previously been written to. If |pref_filename|
  
  
  JsonPrefStore(
      const base::FilePath& pref_filename,
      const base::FilePath& pref_alternate_filename,
      const scoped_refptr<base::SequencedTaskRunner>& sequenced_task_runner,
      scoped_ptr<PrefFilter> pref_filter);

  
  virtual bool GetValue(const std::string& key,
                        const base::Value** result) const OVERRIDE;
  virtual void AddObserver(PrefStore::Observer* observer) OVERRIDE;
  virtual void RemoveObserver(PrefStore::Observer* observer) OVERRIDE;
  virtual bool HasObservers() const OVERRIDE;
  virtual bool IsInitializationComplete() const OVERRIDE;

  
  virtual bool GetMutableValue(const std::string& key,
                               base::Value** result) OVERRIDE;
  virtual void SetValue(const std::string& key, base::Value* value) OVERRIDE;
  virtual void SetValueSilently(const std::string& key,
                                base::Value* value) OVERRIDE;
  virtual void RemoveValue(const std::string& key) OVERRIDE;
  virtual bool ReadOnly() const OVERRIDE;
  virtual PrefReadError GetReadError() const OVERRIDE;
  
  
  
  virtual PrefReadError ReadPrefs() OVERRIDE;
  virtual void ReadPrefsAsync(ReadErrorDelegate* error_delegate) OVERRIDE;
  virtual void CommitPendingWrite() OVERRIDE;
  virtual void ReportValueChanged(const std::string& key) OVERRIDE;

  
  
  void RemoveValueSilently(const std::string& key);

  
  
  void RegisterOnNextSuccessfulWriteCallback(
      const base::Closure& on_next_successful_write);

 private:
  virtual ~JsonPrefStore();

  
  
  
  
  
  
  void OnFileRead(scoped_ptr<ReadResult> read_result);

  
  virtual bool SerializeData(std::string* output) OVERRIDE;

  
  
  
  
  
  
  
  void FinalizeFileRead(bool initialization_successful,
                        scoped_ptr<base::DictionaryValue> prefs,
                        bool schedule_write);

  const base::FilePath path_;
  const base::FilePath alternate_path_;
  const scoped_refptr<base::SequencedTaskRunner> sequenced_task_runner_;

  scoped_ptr<base::DictionaryValue> prefs_;

  bool read_only_;

  
  base::ImportantFileWriter writer_;

  scoped_ptr<PrefFilter> pref_filter_;
  ObserverList<PrefStore::Observer, true> observers_;

  scoped_ptr<ReadErrorDelegate> error_delegate_;

  bool initialized_;
  bool filtering_in_progress_;
  PrefReadError read_error_;

  std::set<std::string> keys_need_empty_value_;

  DISALLOW_COPY_AND_ASSIGN(JsonPrefStore);
};

#endif  