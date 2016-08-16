// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PREFS_TRACKED_SEGREGATED_PREF_STORE_H_
#define CHROME_BROWSER_PREFS_TRACKED_SEGREGATED_PREF_STORE_H_

#include <set>
#include <string>

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "base/prefs/persistent_pref_store.h"

class SegregatedPrefStore : public PersistentPrefStore {
 public:
  
  
  
  
  
  
  
  
  SegregatedPrefStore(
      const scoped_refptr<PersistentPrefStore>& default_pref_store,
      const scoped_refptr<PersistentPrefStore>& selected_pref_store,
      const std::set<std::string>& selected_pref_names);

  
  virtual void AddObserver(Observer* observer) OVERRIDE;
  virtual void RemoveObserver(Observer* observer) OVERRIDE;
  virtual bool HasObservers() const OVERRIDE;
  virtual bool IsInitializationComplete() const OVERRIDE;
  virtual bool GetValue(const std::string& key,
                        const base::Value** result) const OVERRIDE;

  
  virtual void SetValue(const std::string& key, base::Value* value) OVERRIDE;
  virtual void RemoveValue(const std::string& key) OVERRIDE;

  
  virtual bool GetMutableValue(const std::string& key,
                               base::Value** result) OVERRIDE;
  virtual void ReportValueChanged(const std::string& key) OVERRIDE;
  virtual void SetValueSilently(const std::string& key,
                                base::Value* value) OVERRIDE;
  virtual bool ReadOnly() const OVERRIDE;
  virtual PrefReadError GetReadError() const OVERRIDE;
  virtual PrefReadError ReadPrefs() OVERRIDE;
  virtual void ReadPrefsAsync(ReadErrorDelegate* error_delegate) OVERRIDE;
  virtual void CommitPendingWrite() OVERRIDE;

 private:
  
  
  class AggregatingObserver : public PrefStore::Observer {
   public:
    explicit AggregatingObserver(SegregatedPrefStore* outer);

    
    virtual void OnPrefValueChanged(const std::string& key) OVERRIDE;
    virtual void OnInitializationCompleted(bool succeeded) OVERRIDE;

   private:
    SegregatedPrefStore* outer_;
    int failed_sub_initializations_;
    int successful_sub_initializations_;

    DISALLOW_COPY_AND_ASSIGN(AggregatingObserver);
  };

  virtual ~SegregatedPrefStore();

  
  
  PersistentPrefStore* StoreForKey(const std::string& key);
  const PersistentPrefStore* StoreForKey(const std::string& key) const;

  scoped_refptr<PersistentPrefStore> default_pref_store_;
  scoped_refptr<PersistentPrefStore> selected_pref_store_;
  std::set<std::string> selected_preference_names_;

  scoped_ptr<PersistentPrefStore::ReadErrorDelegate> read_error_delegate_;
  ObserverList<PrefStore::Observer, true> observers_;
  AggregatingObserver aggregating_observer_;

  DISALLOW_COPY_AND_ASSIGN(SegregatedPrefStore);
};

#endif  
