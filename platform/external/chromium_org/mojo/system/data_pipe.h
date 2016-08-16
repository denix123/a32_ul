// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SYSTEM_DATA_PIPE_H_
#define MOJO_SYSTEM_DATA_PIPE_H_

#include <stdint.h>

#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/synchronization/lock.h"
#include "mojo/public/c/system/data_pipe.h"
#include "mojo/public/c/system/types.h"
#include "mojo/system/handle_signals_state.h"
#include "mojo/system/memory.h"
#include "mojo/system/system_impl_export.h"

namespace mojo {
namespace system {

class Waiter;
class WaiterList;

class MOJO_SYSTEM_IMPL_EXPORT DataPipe
    : public base::RefCountedThreadSafe<DataPipe> {
 public:
  
  
  
  static const MojoCreateDataPipeOptions kDefaultCreateOptions;

  
  
  
  // |MojoCreateDataPipeOptions| and will be entirely overwritten on success (it
  // may be partly overwritten on failure).
  static MojoResult ValidateCreateOptions(
      UserPointer<const MojoCreateDataPipeOptions> in_options,
      MojoCreateDataPipeOptions* out_options);

  
  
  void ProducerCancelAllWaiters();
  void ProducerClose();
  MojoResult ProducerWriteData(UserPointer<const void> elements,
                               UserPointer<uint32_t> num_bytes,
                               bool all_or_none);
  MojoResult ProducerBeginWriteData(UserPointer<void*> buffer,
                                    UserPointer<uint32_t> buffer_num_bytes,
                                    bool all_or_none);
  MojoResult ProducerEndWriteData(uint32_t num_bytes_written);
  HandleSignalsState ProducerGetHandleSignalsState();
  MojoResult ProducerAddWaiter(Waiter* waiter,
                               MojoHandleSignals signals,
                               uint32_t context,
                               HandleSignalsState* signals_state);
  void ProducerRemoveWaiter(Waiter* waiter, HandleSignalsState* signals_state);
  bool ProducerIsBusy() const;

  
  
  void ConsumerCancelAllWaiters();
  void ConsumerClose();
  
  
  MojoResult ConsumerReadData(UserPointer<void> elements,
                              UserPointer<uint32_t> num_bytes,
                              bool all_or_none);
  MojoResult ConsumerDiscardData(UserPointer<uint32_t> num_bytes,
                                 bool all_or_none);
  MojoResult ConsumerQueryData(UserPointer<uint32_t> num_bytes);
  MojoResult ConsumerBeginReadData(UserPointer<const void*> buffer,
                                   UserPointer<uint32_t> buffer_num_bytes,
                                   bool all_or_none);
  MojoResult ConsumerEndReadData(uint32_t num_bytes_read);
  HandleSignalsState ConsumerGetHandleSignalsState();
  MojoResult ConsumerAddWaiter(Waiter* waiter,
                               MojoHandleSignals signals,
                               uint32_t context,
                               HandleSignalsState* signals_state);
  void ConsumerRemoveWaiter(Waiter* waiter, HandleSignalsState* signals_state);
  bool ConsumerIsBusy() const;

 protected:
  DataPipe(bool has_local_producer,
           bool has_local_consumer,
           const MojoCreateDataPipeOptions& validated_options);

  friend class base::RefCountedThreadSafe<DataPipe>;
  virtual ~DataPipe();

  virtual void ProducerCloseImplNoLock() = 0;
  
  virtual MojoResult ProducerWriteDataImplNoLock(
      UserPointer<const void> elements,
      UserPointer<uint32_t> num_bytes,
      uint32_t max_num_bytes_to_write,
      uint32_t min_num_bytes_to_write) = 0;
  virtual MojoResult ProducerBeginWriteDataImplNoLock(
      UserPointer<void*> buffer,
      UserPointer<uint32_t> buffer_num_bytes,
      uint32_t min_num_bytes_to_write) = 0;
  virtual MojoResult ProducerEndWriteDataImplNoLock(
      uint32_t num_bytes_written) = 0;
  
  virtual HandleSignalsState ProducerGetHandleSignalsStateImplNoLock()
      const = 0;

  virtual void ConsumerCloseImplNoLock() = 0;
  
  virtual MojoResult ConsumerReadDataImplNoLock(
      UserPointer<void> elements,
      UserPointer<uint32_t> num_bytes,
      uint32_t max_num_bytes_to_read,
      uint32_t min_num_bytes_to_read) = 0;
  virtual MojoResult ConsumerDiscardDataImplNoLock(
      UserPointer<uint32_t> num_bytes,
      uint32_t max_num_bytes_to_discard,
      uint32_t min_num_bytes_to_discard) = 0;
  
  virtual MojoResult ConsumerQueryDataImplNoLock(
      UserPointer<uint32_t> num_bytes) = 0;
  virtual MojoResult ConsumerBeginReadDataImplNoLock(
      UserPointer<const void*> buffer,
      UserPointer<uint32_t> buffer_num_bytes,
      uint32_t min_num_bytes_to_read) = 0;
  virtual MojoResult ConsumerEndReadDataImplNoLock(uint32_t num_bytes_read) = 0;
  
  virtual HandleSignalsState ConsumerGetHandleSignalsStateImplNoLock()
      const = 0;

  
  bool may_discard() const { return may_discard_; }
  size_t element_num_bytes() const { return element_num_bytes_; }
  size_t capacity_num_bytes() const { return capacity_num_bytes_; }

  
  bool producer_open_no_lock() const {
    lock_.AssertAcquired();
    return producer_open_;
  }
  bool consumer_open_no_lock() const {
    lock_.AssertAcquired();
    return consumer_open_;
  }
  uint32_t producer_two_phase_max_num_bytes_written_no_lock() const {
    lock_.AssertAcquired();
    return producer_two_phase_max_num_bytes_written_;
  }
  uint32_t consumer_two_phase_max_num_bytes_read_no_lock() const {
    lock_.AssertAcquired();
    return consumer_two_phase_max_num_bytes_read_;
  }
  void set_producer_two_phase_max_num_bytes_written_no_lock(
      uint32_t num_bytes) {
    lock_.AssertAcquired();
    producer_two_phase_max_num_bytes_written_ = num_bytes;
  }
  void set_consumer_two_phase_max_num_bytes_read_no_lock(uint32_t num_bytes) {
    lock_.AssertAcquired();
    consumer_two_phase_max_num_bytes_read_ = num_bytes;
  }
  bool producer_in_two_phase_write_no_lock() const {
    lock_.AssertAcquired();
    return producer_two_phase_max_num_bytes_written_ > 0;
  }
  bool consumer_in_two_phase_read_no_lock() const {
    lock_.AssertAcquired();
    return consumer_two_phase_max_num_bytes_read_ > 0;
  }

 private:
  void AwakeProducerWaitersForStateChangeNoLock(
      const HandleSignalsState& new_producer_state);
  void AwakeConsumerWaitersForStateChangeNoLock(
      const HandleSignalsState& new_consumer_state);

  bool has_local_producer_no_lock() const {
    lock_.AssertAcquired();
    return !!producer_waiter_list_;
  }
  bool has_local_consumer_no_lock() const {
    lock_.AssertAcquired();
    return !!consumer_waiter_list_;
  }

  const bool may_discard_;
  const size_t element_num_bytes_;
  const size_t capacity_num_bytes_;

  mutable base::Lock lock_;  
  
  bool producer_open_;
  bool consumer_open_;
  
  scoped_ptr<WaiterList> producer_waiter_list_;
  scoped_ptr<WaiterList> consumer_waiter_list_;
  
  uint32_t producer_two_phase_max_num_bytes_written_;
  uint32_t consumer_two_phase_max_num_bytes_read_;

  DISALLOW_COPY_AND_ASSIGN(DataPipe);
};

}  
}  

#endif  
