// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GPU_COMMAND_BUFFER_COMMON_COMMAND_BUFFER_H_
#define GPU_COMMAND_BUFFER_COMMON_COMMAND_BUFFER_H_

#include "gpu/command_buffer/common/buffer.h"
#include "gpu/command_buffer/common/constants.h"
#include "gpu/gpu_export.h"

namespace base {
class SharedMemory;
}

namespace gpu {

class GPU_EXPORT CommandBuffer {
 public:
  struct State {
    State()
        : num_entries(0),
          get_offset(0),
          put_offset(0),
          token(-1),
          error(error::kNoError),
          context_lost_reason(error::kUnknown),
          generation(0) {
    }

    
    int32 num_entries;

    
    int32 get_offset;

    
    int32 put_offset;

    
    
    
    
    
    int32 token;

    
    error::Error error;

    
    error::ContextLostReason context_lost_reason;

    
    
    
    uint32 generation;
  };

  struct ConsoleMessage {
    
    int32 id;
    
    std::string message;
  };

  CommandBuffer() {
  }

  virtual ~CommandBuffer() {
  }

  
  
  static bool InRange(int32 start, int32 end, int32 value) {
    if (start <= end)
      return start <= value && value <= end;
    else
      return start <= value || value <= end;
  }

  
  virtual bool Initialize() = 0;

  
  virtual State GetLastState() = 0;

  
  
  
  
  
  virtual int32 GetLastToken() = 0;

  
  
  
  
  virtual void Flush(int32 put_offset) = 0;

  
  
  virtual void WaitForTokenInRange(int32 start, int32 end) = 0;

  
  
  virtual void WaitForGetOffsetInRange(int32 start, int32 end) = 0;

  
  
  virtual void SetGetBuffer(int32 transfer_buffer_id) = 0;

  
  
  virtual scoped_refptr<gpu::Buffer> CreateTransferBuffer(size_t size,
                                                          int32* id) = 0;

  
  virtual void DestroyTransferBuffer(int32 id) = 0;

#if !defined(NACL_WIN64)
  
  
  
  
  virtual error::Error GetLastError();
#endif

 private:
  DISALLOW_COPY_AND_ASSIGN(CommandBuffer);
};

}  

#endif  
