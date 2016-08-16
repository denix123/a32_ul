// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ANDROID_WEBVIEW_BROWSER_GLOBAL_TILE_MANAGER_H_
#define ANDROID_WEBVIEW_BROWSER_GLOBAL_TILE_MANAGER_H_

#include <list>
#include "base/basictypes.h"
#include "base/lazy_instance.h"
#include "base/sequence_checker.h"
#include "base/synchronization/lock.h"
#include "content/public/browser/android/synchronous_compositor.h"

namespace android_webview {

class GlobalTileManagerClient;

class GlobalTileManager {
 private:
  typedef std::list<GlobalTileManagerClient*> ListType;

 public:
  typedef ListType::iterator Key;
  static GlobalTileManager* GetInstance();

  void SetTileLimit(size_t num_tiles_limit);

  
  
  
  
  
  void RequestTiles(content::SynchronousCompositorMemoryPolicy new_policy,
                    Key key);

  Key PushBack(GlobalTileManagerClient* client);

  
  
  
  void DidUse(Key key);

  void Remove(Key key);

 private:
  friend struct base::DefaultLazyInstanceTraits<GlobalTileManager>;
  GlobalTileManager();
  ~GlobalTileManager();

  
  
  
  
  
  size_t Evict(size_t desired_num_tiles, Key key);

  
  
  bool IsConsistent() const;

  size_t num_tiles_limit_;

  size_t total_allocated_tiles_;
  ListType mru_list_;
  base::SequenceChecker sequence_checker_;

  DISALLOW_COPY_AND_ASSIGN(GlobalTileManager);
};

}  

#endif  
