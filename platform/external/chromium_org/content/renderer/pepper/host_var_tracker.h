// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_PEPPER_HOST_VAR_TRACKER_H_
#define CONTENT_RENDERER_PEPPER_HOST_VAR_TRACKER_H_

#include <map>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/containers/hash_tables.h"
#include "base/gtest_prod_util.h"
#include "base/memory/linked_ptr.h"
#include "base/memory/ref_counted.h"
#include "content/common/content_export.h"
#include "ppapi/c/pp_instance.h"
#include "ppapi/shared_impl/host_resource.h"
#include "ppapi/shared_impl/resource_tracker.h"
#include "ppapi/shared_impl/var_tracker.h"
#include "v8/include/v8.h"

namespace ppapi {
class ArrayBufferVar;
class V8ObjectVar;
class Var;
}

namespace content {

class HostVarTracker : public ppapi::VarTracker {
 public:
  HostVarTracker();
  virtual ~HostVarTracker();

  
  
  
  void AddV8ObjectVar(ppapi::V8ObjectVar* object_var);
  void RemoveV8ObjectVar(ppapi::V8ObjectVar* object_var);
  
  PP_Var V8ObjectVarForV8Object(PP_Instance instance,
                                v8::Handle<v8::Object> object);
  
  
  CONTENT_EXPORT int GetLiveV8ObjectVarsForTest(PP_Instance instance);

  
  virtual PP_Var MakeResourcePPVarFromMessage(
      PP_Instance instance,
      const IPC::Message& creation_message,
      int pending_renderer_id,
      int pending_browser_id) OVERRIDE;
  virtual ppapi::ResourceVar* MakeResourceVar(PP_Resource pp_resource) OVERRIDE;
  virtual void DidDeleteInstance(PP_Instance pp_instance) OVERRIDE;

  virtual int TrackSharedMemoryHandle(PP_Instance instance,
                                      base::SharedMemoryHandle file,
                                      uint32 size_in_bytes) OVERRIDE;
  virtual bool StopTrackingSharedMemoryHandle(int id,
                                              PP_Instance instance,
                                              base::SharedMemoryHandle* handle,
                                              uint32* size_in_bytes) OVERRIDE;

 private:
  
  virtual ppapi::ArrayBufferVar* CreateArrayBuffer(uint32 size_in_bytes)
      OVERRIDE;
  virtual ppapi::ArrayBufferVar* CreateShmArrayBuffer(
      uint32 size_in_bytes,
      base::SharedMemoryHandle handle) OVERRIDE;

  
  
  void ForceReleaseV8Object(ppapi::V8ObjectVar* object_var);

  
  
  struct V8ObjectVarKey {
    explicit V8ObjectVarKey(ppapi::V8ObjectVar* object_var);
    V8ObjectVarKey(PP_Instance i, v8::Handle<v8::Object> object);
    ~V8ObjectVarKey();

    bool operator<(const V8ObjectVarKey& other) const;

    PP_Instance instance;
    int hash;
  };
  typedef std::multimap<V8ObjectVarKey, ppapi::V8ObjectVar*> ObjectMap;

  
  
  ObjectMap::iterator GetForV8Object(PP_Instance instance,
                                     v8::Handle<v8::Object> object);


  
  ObjectMap object_map_;

  
  struct SharedMemoryMapEntry {
    PP_Instance instance;
    base::SharedMemoryHandle handle;
    uint32 size_in_bytes;
  };
  typedef std::map<int, SharedMemoryMapEntry> SharedMemoryMap;
  SharedMemoryMap shared_memory_map_;
  uint32_t last_shared_memory_map_id_;

  DISALLOW_COPY_AND_ASSIGN(HostVarTracker);
};

}  

#endif  
