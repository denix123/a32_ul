// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef GPU_COMMAND_BUFFER_CLIENT_CMD_BUFFER_HELPER_H_
#define GPU_COMMAND_BUFFER_CLIENT_CMD_BUFFER_HELPER_H_

#include <string.h>
#include <time.h>

#include "base/time/time.h"
#include "gpu/command_buffer/common/cmd_buffer_common.h"
#include "gpu/command_buffer/common/command_buffer.h"
#include "gpu/command_buffer/common/constants.h"
#include "gpu/gpu_export.h"

namespace gpu {

#if !defined(OS_ANDROID)
#define CMD_HELPER_PERIODIC_FLUSH_CHECK
const int kCommandsPerFlushCheck = 100;
const int kPeriodicFlushDelayInMicroseconds =
    base::Time::kMicrosecondsPerSecond / (5 * 60);
#endif

const int kAutoFlushSmall = 16;  
const int kAutoFlushBig = 2;     

class GPU_EXPORT CommandBufferHelper {
 public:
  explicit CommandBufferHelper(CommandBuffer* command_buffer);
  virtual ~CommandBufferHelper();

  
  
  
  
  bool Initialize(int32 ring_buffer_size);

  
  
  void SetAutomaticFlushes(bool enabled);

  
  bool IsContextLost();

  
  
  
  void Flush();

  
  
  
  bool Finish();

  
  
  
  
  void WaitForAvailableEntries(int32 count);

  
  
  
  
  
  
  
  int32 InsertToken();

  
  
  
  bool HasTokenPassed(int32 token) const {
    if (token > token_)
      return true;  
    return last_token_read() >= token;
  }

  
  
  
  
  
  void WaitForToken(int32 token);

  
  
  void* GetSpace(int32 entries) {
#if defined(CMD_HELPER_PERIODIC_FLUSH_CHECK)
    
    
    
    
    ++commands_issued_;
    if (flush_automatically_ &&
        (commands_issued_ % kCommandsPerFlushCheck == 0)) {
      PeriodicFlushCheck();
    }
#endif

    
    if (entries > immediate_entry_count_) {
      WaitForAvailableEntries(entries);
      if (entries > immediate_entry_count_)
        return NULL;
    }

    DCHECK_LE(entries, immediate_entry_count_);

    
    CommandBufferEntry* space = &entries_[put_];
    put_ += entries;
    immediate_entry_count_ -= entries;

    DCHECK_LE(put_, total_entry_count_);
    return space;
  }

  template <typename T>
  void ForceNullCheck(T* data) {
#if defined(OS_WIN) && defined(ARCH_CPU_64_BITS)
    
    
    
    
    if (data)
      static_cast<volatile T*>(data)->header;
#endif
  }

  
  
  template <typename T>
  T* GetCmdSpace() {
    COMPILE_ASSERT(T::kArgFlags == cmd::kFixed, Cmd_kArgFlags_not_kFixed);
    int32 space_needed = ComputeNumEntries(sizeof(T));
    T* data = static_cast<T*>(GetSpace(space_needed));
    ForceNullCheck(data);
    return data;
  }

  
  template <typename T>
  T* GetImmediateCmdSpace(size_t data_space) {
    COMPILE_ASSERT(T::kArgFlags == cmd::kAtLeastN, Cmd_kArgFlags_not_kAtLeastN);
    int32 space_needed = ComputeNumEntries(sizeof(T) + data_space);
    T* data = static_cast<T*>(GetSpace(space_needed));
    ForceNullCheck(data);
    return data;
  }

  
  template <typename T>
  T* GetImmediateCmdSpaceTotalSize(size_t total_space) {
    COMPILE_ASSERT(T::kArgFlags == cmd::kAtLeastN, Cmd_kArgFlags_not_kAtLeastN);
    int32 space_needed = ComputeNumEntries(total_space);
    T* data = static_cast<T*>(GetSpace(space_needed));
    ForceNullCheck(data);
    return data;
  }

  int32 last_token_read() const {
    return command_buffer_->GetLastToken();
  }

  int32 get_offset() const {
    return command_buffer_->GetLastState().get_offset;
  }

  
  void Noop(uint32 skip_count) {
    cmd::Noop* cmd = GetImmediateCmdSpace<cmd::Noop>(
        (skip_count - 1) * sizeof(CommandBufferEntry));
    if (cmd) {
      cmd->Init(skip_count);
    }
  }

  void SetToken(uint32 token) {
    cmd::SetToken* cmd = GetCmdSpace<cmd::SetToken>();
    if (cmd) {
      cmd->Init(token);
    }
  }

  void SetBucketSize(uint32 bucket_id, uint32 size) {
    cmd::SetBucketSize* cmd = GetCmdSpace<cmd::SetBucketSize>();
    if (cmd) {
      cmd->Init(bucket_id, size);
    }
  }

  void SetBucketData(uint32 bucket_id,
                     uint32 offset,
                     uint32 size,
                     uint32 shared_memory_id,
                     uint32 shared_memory_offset) {
    cmd::SetBucketData* cmd = GetCmdSpace<cmd::SetBucketData>();
    if (cmd) {
      cmd->Init(bucket_id,
                offset,
                size,
                shared_memory_id,
                shared_memory_offset);
    }
  }

  void SetBucketDataImmediate(
      uint32 bucket_id, uint32 offset, const void* data, uint32 size) {
    cmd::SetBucketDataImmediate* cmd =
        GetImmediateCmdSpace<cmd::SetBucketDataImmediate>(size);
    if (cmd) {
      cmd->Init(bucket_id, offset, size);
      memcpy(ImmediateDataAddress(cmd), data, size);
    }
  }

  void GetBucketStart(uint32 bucket_id,
                      uint32 result_memory_id,
                      uint32 result_memory_offset,
                      uint32 data_memory_size,
                      uint32 data_memory_id,
                      uint32 data_memory_offset) {
    cmd::GetBucketStart* cmd = GetCmdSpace<cmd::GetBucketStart>();
    if (cmd) {
      cmd->Init(bucket_id,
                result_memory_id,
                result_memory_offset,
                data_memory_size,
                data_memory_id,
                data_memory_offset);
    }
  }

  void GetBucketData(uint32 bucket_id,
                     uint32 offset,
                     uint32 size,
                     uint32 shared_memory_id,
                     uint32 shared_memory_offset) {
    cmd::GetBucketData* cmd = GetCmdSpace<cmd::GetBucketData>();
    if (cmd) {
      cmd->Init(bucket_id,
                offset,
                size,
                shared_memory_id,
                shared_memory_offset);
    }
  }

  CommandBuffer* command_buffer() const {
    return command_buffer_;
  }

  scoped_refptr<Buffer> get_ring_buffer() const { return ring_buffer_; }

  uint32 flush_generation() const { return flush_generation_; }

  void FreeRingBuffer();

  bool HaveRingBuffer() const {
    return ring_buffer_id_ != -1;
  }

  bool usable () const {
    return usable_;
  }

  void ClearUsable() {
    usable_ = false;
    CalcImmediateEntries(0);
  }

 private:
  
  int32 AvailableEntries() {
    return (get_offset() - put_ - 1 + total_entry_count_) % total_entry_count_;
  }

  void CalcImmediateEntries(int waiting_count);
  bool AllocateRingBuffer();
  void FreeResources();

  
  
  bool WaitForGetOffsetInRange(int32 start, int32 end);

#if defined(CMD_HELPER_PERIODIC_FLUSH_CHECK)
  
  void PeriodicFlushCheck();
#endif

  CommandBuffer* command_buffer_;
  int32 ring_buffer_id_;
  int32 ring_buffer_size_;
  scoped_refptr<gpu::Buffer> ring_buffer_;
  CommandBufferEntry* entries_;
  int32 total_entry_count_;  
  int32 immediate_entry_count_;
  int32 token_;
  int32 put_;
  int32 last_put_sent_;

#if defined(CMD_HELPER_PERIODIC_FLUSH_CHECK)
  int commands_issued_;
#endif

  bool usable_;
  bool context_lost_;
  bool flush_automatically_;

  base::TimeTicks last_flush_time_;

  
  
  uint32 flush_generation_;

  friend class CommandBufferHelperTest;
  DISALLOW_COPY_AND_ASSIGN(CommandBufferHelper);
};

}  

#endif  
