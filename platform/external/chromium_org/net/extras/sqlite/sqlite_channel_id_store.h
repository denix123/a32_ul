// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_EXTRAS_SQLITE_SQLITE_CHANNEL_ID_STORE_H_
#define NET_EXTRAS_SQLITE_SQLITE_CHANNEL_ID_STORE_H_

#include <list>
#include <string>

#include "base/callback_forward.h"
#include "base/compiler_specific.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "net/ssl/default_channel_id_store.h"

namespace base {
class FilePath;
class SequencedTaskRunner;
}

class GURL;

namespace net {

class SQLiteChannelIDStore : public DefaultChannelIDStore::PersistentStore {
 public:
  
  
  SQLiteChannelIDStore(
      const base::FilePath& path,
      const scoped_refptr<base::SequencedTaskRunner>& background_task_runner);

  
  virtual void Load(const LoadedCallback& loaded_callback) OVERRIDE;
  virtual void AddChannelID(
      const DefaultChannelIDStore::ChannelID& channel_id) OVERRIDE;
  virtual void DeleteChannelID(
      const DefaultChannelIDStore::ChannelID& channel_id) OVERRIDE;
  virtual void SetForceKeepSessionState() OVERRIDE;

  
  void DeleteAllInList(const std::list<std::string>& server_identifiers);

 private:
  virtual ~SQLiteChannelIDStore();

  class Backend;

  scoped_refptr<Backend> backend_;

  DISALLOW_COPY_AND_ASSIGN(SQLiteChannelIDStore);
};

}  

#endif  
