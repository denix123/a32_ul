// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GPU_COMMAND_BUFFER_SERVICE_COMMAND_BUFFER_SERVICE_H_
#define GPU_COMMAND_BUFFER_SERVICE_COMMAND_BUFFER_SERVICE_H_

#include "base/callback.h"
#include "base/memory/shared_memory.h"
#include "gpu/command_buffer/common/command_buffer.h"
#include "gpu/command_buffer/common/command_buffer_shared.h"

namespace gpu {

class TransferBufferManagerInterface;

class GPU_EXPORT CommandBufferServiceBase : public CommandBuffer {
 public:
  
  virtual void SetGetOffset(int32 get_offset) = 0;

  
  
  virtual scoped_refptr<gpu::Buffer> GetTransferBuffer(int32 id) = 0;

  
  virtual void SetToken(int32 token) = 0;

  
  virtual void SetParseError(error::Error) = 0;

  
  
  
  virtual void SetContextLostReason(error::ContextLostReason) = 0;
};

class GPU_EXPORT CommandBufferService : public CommandBufferServiceBase {
 public:
  typedef base::Callback<bool(int32)> GetBufferChangedCallback;
  explicit CommandBufferService(
      TransferBufferManagerInterface* transfer_buffer_manager);
  virtual ~CommandBufferService();

  
  virtual bool Initialize() OVERRIDE;
  virtual State GetLastState() OVERRIDE;
  virtual int32 GetLastToken() OVERRIDE;
  virtual void Flush(int32 put_offset) OVERRIDE;
  virtual void WaitForTokenInRange(int32 start, int32 end) OVERRIDE;
  virtual void WaitForGetOffsetInRange(int32 start, int32 end) OVERRIDE;
  virtual void SetGetBuffer(int32 transfer_buffer_id) OVERRIDE;
  virtual scoped_refptr<Buffer> CreateTransferBuffer(size_t size,
                                                     int32* id) OVERRIDE;
  virtual void DestroyTransferBuffer(int32 id) OVERRIDE;

  
  virtual void SetGetOffset(int32 get_offset) OVERRIDE;
  virtual scoped_refptr<Buffer> GetTransferBuffer(int32 id) OVERRIDE;
  virtual void SetToken(int32 token) OVERRIDE;
  virtual void SetParseError(error::Error error) OVERRIDE;
  virtual void SetContextLostReason(error::ContextLostReason) OVERRIDE;

  
  
  
  
  
  
  
  
  virtual void SetPutOffsetChangeCallback(const base::Closure& callback);
  
  virtual void SetGetBufferChangeCallback(
      const GetBufferChangedCallback& callback);
  virtual void SetParseErrorCallback(const base::Closure& callback);

  
  void SetSharedStateBuffer(scoped_ptr<BufferBacking> shared_state_buffer);

  
  void UpdateState();

  
  
  bool RegisterTransferBuffer(int32 id, scoped_ptr<BufferBacking> buffer);

 private:
  int32 ring_buffer_id_;
  scoped_refptr<Buffer> ring_buffer_;
  scoped_ptr<BufferBacking> shared_state_buffer_;
  CommandBufferSharedState* shared_state_;
  int32 num_entries_;
  int32 get_offset_;
  int32 put_offset_;
  base::Closure put_offset_change_callback_;
  GetBufferChangedCallback get_buffer_change_callback_;
  base::Closure parse_error_callback_;
  TransferBufferManagerInterface* transfer_buffer_manager_;
  int32 token_;
  uint32 generation_;
  error::Error error_;
  error::ContextLostReason context_lost_reason_;

  DISALLOW_COPY_AND_ASSIGN(CommandBufferService);
};

}  

#endif  
