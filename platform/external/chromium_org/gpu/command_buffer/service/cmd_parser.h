// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef GPU_COMMAND_BUFFER_SERVICE_CMD_PARSER_H_
#define GPU_COMMAND_BUFFER_SERVICE_CMD_PARSER_H_

#include "gpu/command_buffer/common/constants.h"
#include "gpu/command_buffer/common/cmd_buffer_common.h"
#include "gpu/gpu_export.h"

namespace gpu {

class AsyncAPIInterface;

class GPU_EXPORT CommandParser {
 public:
  static const int kParseCommandsSlice = 20;

  explicit CommandParser(AsyncAPIInterface* handler);

  
  void SetBuffer(
      void* shm_address,
      size_t shm_size,
      ptrdiff_t offset,
      size_t size);

  
  
  CommandBufferOffset get() const { return get_; }

  
  
  bool set_get(CommandBufferOffset get) {
    if (get >= 0 && get < entry_count_) {
      get_ = get;
      return true;
    }
    return false;
  }

  
  
  void set_put(CommandBufferOffset put) { put_ = put; }

  
  
  CommandBufferOffset put() const { return put_; }

  
  bool IsEmpty() const { return put_ == get_; }

  
  
  error::Error ProcessCommands(int num_commands);

  
  error::Error ProcessAllCommands();

 private:
  CommandBufferOffset get_;
  CommandBufferOffset put_;
  CommandBufferEntry* buffer_;
  int32 entry_count_;
  AsyncAPIInterface* handler_;
};

class GPU_EXPORT AsyncAPIInterface {
 public:
  AsyncAPIInterface() {}
  virtual ~AsyncAPIInterface() {}

  
  
  
  
  
  
  
  
  virtual error::Error DoCommand(
      unsigned int command,
      unsigned int arg_count,
      const void* cmd_data) = 0;

  
  
  
  
  
  
  virtual error::Error DoCommands(unsigned int num_commands,
                                  const void* buffer,
                                  int num_entries,
                                  int* entries_processed);

  
  virtual const char* GetCommandName(unsigned int command_id) const = 0;
};

}  

#endif  
