// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_INDEXED_DB_INDEXED_DB_CLASS_FACTORY_H_
#define CONTENT_BROWSER_INDEXED_DB_INDEXED_DB_CLASS_FACTORY_H_

#include "base/lazy_instance.h"
#include "base/memory/scoped_ptr.h"
#include "content/common/content_export.h"

namespace leveldb {
class Iterator;
}  

namespace content {

class LevelDBIteratorImpl;
class LevelDBDatabase;
class LevelDBTransaction;

class CONTENT_EXPORT IndexedDBClassFactory {
 public:
  typedef IndexedDBClassFactory* GetterCallback();

  static IndexedDBClassFactory* Get();

  static void SetIndexedDBClassFactoryGetter(GetterCallback* cb);

  virtual LevelDBIteratorImpl* CreateIteratorImpl(
      scoped_ptr<leveldb::Iterator> iterator);
  virtual LevelDBTransaction* CreateLevelDBTransaction(LevelDBDatabase* db);

 protected:
  IndexedDBClassFactory() {}
  virtual ~IndexedDBClassFactory() {}
  friend struct base::DefaultLazyInstanceTraits<IndexedDBClassFactory>;
};

}  

#endif  
