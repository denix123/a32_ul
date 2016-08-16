// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_PEPPER_PPB_BUFFER_IMPL_H_
#define CONTENT_RENDERER_PEPPER_PPB_BUFFER_IMPL_H_

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/shared_memory.h"
#include "ppapi/shared_impl/resource.h"
#include "ppapi/thunk/ppb_buffer_api.h"

namespace content {

class PPB_Buffer_Impl : public ppapi::Resource,
                        public ppapi::thunk::PPB_Buffer_API {
 public:
  static PP_Resource Create(PP_Instance instance, uint32_t size);
  static scoped_refptr<PPB_Buffer_Impl> CreateResource(PP_Instance instance,
                                                       uint32_t size);

  virtual PPB_Buffer_Impl* AsPPB_Buffer_Impl();

  base::SharedMemory* shared_memory() const { return shared_memory_.get(); }
  uint32_t size() const { return size_; }

  
  virtual ppapi::thunk::PPB_Buffer_API* AsPPB_Buffer_API() OVERRIDE;

  
  virtual PP_Bool Describe(uint32_t* size_in_bytes) OVERRIDE;
  virtual PP_Bool IsMapped() OVERRIDE;
  virtual void* Map() OVERRIDE;
  virtual void Unmap() OVERRIDE;

  
  virtual int32_t GetSharedMemory(int* handle) OVERRIDE;

 private:
  virtual ~PPB_Buffer_Impl();

  explicit PPB_Buffer_Impl(PP_Instance instance);
  bool Init(uint32_t size);

  scoped_ptr<base::SharedMemory> shared_memory_;
  uint32_t size_;
  int map_count_;

  DISALLOW_COPY_AND_ASSIGN(PPB_Buffer_Impl);
};

class BufferAutoMapper {
 public:
  explicit BufferAutoMapper(ppapi::thunk::PPB_Buffer_API* api);
  ~BufferAutoMapper();

  
  void* data() { return data_; }
  uint32_t size() { return size_; }

 private:
  ppapi::thunk::PPB_Buffer_API* api_;

  bool needs_unmap_;

  void* data_;
  uint32_t size_;

  DISALLOW_COPY_AND_ASSIGN(BufferAutoMapper);
};

}  

#endif  