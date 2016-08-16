// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STORAGE_BROWSER_QUOTA_SPECIAL_STORAGE_POLICY_H_
#define STORAGE_BROWSER_QUOTA_SPECIAL_STORAGE_POLICY_H_

#include <string>

#include "base/memory/ref_counted.h"
#include "base/observer_list.h"
#include "storage/browser/storage_browser_export.h"

class GURL;

namespace storage {

class STORAGE_EXPORT SpecialStoragePolicy
    : public base::RefCountedThreadSafe<SpecialStoragePolicy> {
 public:
  typedef int StoragePolicy;
  enum ChangeFlags {
    STORAGE_PROTECTED = 1 << 0,
    STORAGE_UNLIMITED = 1 << 1,
  };

  class STORAGE_EXPORT Observer {
   public:
    virtual void OnGranted(const GURL& origin, int change_flags) = 0;
    virtual void OnRevoked(const GURL& origin, int change_flags) = 0;
    virtual void OnCleared() = 0;

   protected:
    virtual ~Observer();
  };

  SpecialStoragePolicy();

  
  virtual bool IsStorageProtected(const GURL& origin) = 0;

  
  virtual bool IsStorageUnlimited(const GURL& origin) = 0;

  
  
  virtual bool CanQueryDiskSize(const GURL& origin) = 0;

  
  
  virtual bool IsFileHandler(const std::string& extension_id) = 0;

  
  virtual bool HasIsolatedStorage(const GURL& origin) = 0;

  
  
  virtual bool IsStorageSessionOnly(const GURL& origin) = 0;

  
  virtual bool HasSessionOnlyOrigins() = 0;

  
  
  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

 protected:
  friend class base::RefCountedThreadSafe<SpecialStoragePolicy>;
  virtual ~SpecialStoragePolicy();
  void NotifyGranted(const GURL& origin, int change_flags);
  void NotifyRevoked(const GURL& origin, int change_flags);
  void NotifyCleared();

  ObserverList<Observer> observers_;
};

}  

#endif  
