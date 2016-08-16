// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_STORAGE_STORAGE_API_H_
#define EXTENSIONS_BROWSER_API_STORAGE_STORAGE_API_H_

#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "extensions/browser/api/storage/settings_namespace.h"
#include "extensions/browser/api/storage/settings_observer.h"
#include "extensions/browser/extension_function.h"
#include "extensions/browser/value_store/value_store.h"

namespace extensions {

class SettingsFunction : public UIThreadExtensionFunction {
 protected:
  SettingsFunction();
  virtual ~SettingsFunction();

  
  virtual bool ShouldSkipQuotaLimiting() const OVERRIDE;
  virtual ResponseAction Run() OVERRIDE;

  
  
  virtual ResponseValue RunWithStorage(ValueStore* storage) = 0;

  
  
  
  
  
  
  ResponseValue UseReadResult(ValueStore::ReadResult result,
                              ValueStore* storage);

  
  
  
  
  
  
  
  ResponseValue UseWriteResult(ValueStore::WriteResult result,
                               ValueStore* storage);

 private:
  
  
  void AsyncRunWithStorage(ValueStore* storage);

  
  
  
  
  
  ResponseValue HandleError(const ValueStore::Error& error,
                            ValueStore* storage);

  
  
  settings_namespace::Namespace settings_namespace_;

  
  
  bool tried_restoring_storage_;

  
  scoped_refptr<SettingsObserverList> observers_;
};

class StorageStorageAreaGetFunction : public SettingsFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("storage.get", STORAGE_GET)

 protected:
  virtual ~StorageStorageAreaGetFunction() {}

  
  virtual ResponseValue RunWithStorage(ValueStore* storage) OVERRIDE;
};

class StorageStorageAreaSetFunction : public SettingsFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("storage.set", STORAGE_SET)

 protected:
  virtual ~StorageStorageAreaSetFunction() {}

  
  virtual ResponseValue RunWithStorage(ValueStore* storage) OVERRIDE;

  
  virtual void GetQuotaLimitHeuristics(
      QuotaLimitHeuristics* heuristics) const OVERRIDE;
};

class StorageStorageAreaRemoveFunction : public SettingsFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("storage.remove", STORAGE_REMOVE)

 protected:
  virtual ~StorageStorageAreaRemoveFunction() {}

  
  virtual ResponseValue RunWithStorage(ValueStore* storage) OVERRIDE;

  
  virtual void GetQuotaLimitHeuristics(
      QuotaLimitHeuristics* heuristics) const OVERRIDE;
};

class StorageStorageAreaClearFunction : public SettingsFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("storage.clear", STORAGE_CLEAR)

 protected:
  virtual ~StorageStorageAreaClearFunction() {}

  
  virtual ResponseValue RunWithStorage(ValueStore* storage) OVERRIDE;

  
  virtual void GetQuotaLimitHeuristics(
      QuotaLimitHeuristics* heuristics) const OVERRIDE;
};

class StorageStorageAreaGetBytesInUseFunction : public SettingsFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("storage.getBytesInUse", STORAGE_GETBYTESINUSE)

 protected:
  virtual ~StorageStorageAreaGetBytesInUseFunction() {}

  
  virtual ResponseValue RunWithStorage(ValueStore* storage) OVERRIDE;
};

}  

#endif  
