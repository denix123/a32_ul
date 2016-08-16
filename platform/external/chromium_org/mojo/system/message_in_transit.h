// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SYSTEM_MESSAGE_IN_TRANSIT_H_
#define MOJO_SYSTEM_MESSAGE_IN_TRANSIT_H_

#include <stddef.h>
#include <stdint.h>

#include <vector>

#include "base/macros.h"
#include "base/memory/aligned_memory.h"
#include "base/memory/scoped_ptr.h"
#include "mojo/system/dispatcher.h"
#include "mojo/system/memory.h"
#include "mojo/system/system_impl_export.h"

namespace mojo {
namespace system {

class Channel;
class TransportData;

class MOJO_SYSTEM_IMPL_EXPORT MessageInTransit {
 public:
  typedef uint16_t Type;
  
  static const Type kTypeMessagePipeEndpoint = 0;
  
  static const Type kTypeMessagePipe = 1;
  
  static const Type kTypeChannel = 2;
  
  static const Type kTypeRawChannel = 3;

  typedef uint16_t Subtype;
  
  static const Subtype kSubtypeMessagePipeEndpointData = 0;
  
  
  
  static const Subtype kSubtypeChannelRunMessagePipeEndpoint = 0;
  static const Subtype kSubtypeChannelRemoveMessagePipeEndpoint = 1;
  static const Subtype kSubtypeChannelRemoveMessagePipeEndpointAck = 2;
  
  static const Subtype kSubtypeRawChannelPosixExtraPlatformHandles = 0;

  typedef uint32_t EndpointId;
  
  static const EndpointId kInvalidEndpointId = 0;

  
  
  static const size_t kMessageAlignment = 8;

  
 private:
  struct Header;

 public:
  
  class MOJO_SYSTEM_IMPL_EXPORT View {
   public:
    
    
    
    
    View(size_t message_size, const void* buffer);

    
    
    
    
    
    
    
    
    bool IsValid(size_t serialized_platform_handle_size,
                 const char** error_message) const;

    
    
    const void* main_buffer() const { return buffer_; }
    size_t main_buffer_size() const {
      return RoundUpMessageAlignment(sizeof(Header) + header()->num_bytes);
    }
    const void* transport_data_buffer() const {
      return (total_size() > main_buffer_size())
                 ? static_cast<const char*>(buffer_) + main_buffer_size()
                 : nullptr;
    }
    size_t transport_data_buffer_size() const {
      return total_size() - main_buffer_size();
    }
    size_t total_size() const { return header()->total_size; }
    uint32_t num_bytes() const { return header()->num_bytes; }
    const void* bytes() const {
      return static_cast<const char*>(buffer_) + sizeof(Header);
    }
    Type type() const { return header()->type; }
    Subtype subtype() const { return header()->subtype; }
    EndpointId source_id() const { return header()->source_id; }
    EndpointId destination_id() const { return header()->destination_id; }

   private:
    const Header* header() const { return static_cast<const Header*>(buffer_); }

    const void* const buffer_;

    
    
    
    DISALLOW_COPY_AND_ASSIGN(View);
  };

  
  MessageInTransit(Type type,
                   Subtype subtype,
                   uint32_t num_bytes,
                   const void* bytes);
  
  MessageInTransit(Type type,
                   Subtype subtype,
                   uint32_t num_bytes,
                   UserPointer<const void> bytes);
  
  explicit MessageInTransit(const View& message_view);

  ~MessageInTransit();

  
  
  
  
  
  
  
  static bool GetNextMessageSize(const void* buffer,
                                 size_t buffer_size,
                                 size_t* next_message_size);

  
  
  
  
  void SetDispatchers(scoped_ptr<DispatcherVector> dispatchers);

  
  
  void SetTransportData(scoped_ptr<TransportData> transport_data);

  
  
  
  
  void SerializeAndCloseDispatchers(Channel* channel);

  
  const void* main_buffer() const { return main_buffer_.get(); }
  size_t main_buffer_size() const { return main_buffer_size_; }

  
  const TransportData* transport_data() const { return transport_data_.get(); }
  TransportData* transport_data() { return transport_data_.get(); }

  
  size_t total_size() const { return header()->total_size; }

  
  uint32_t num_bytes() const { return header()->num_bytes; }

  
  const void* bytes() const { return main_buffer_.get() + sizeof(Header); }
  void* bytes() { return main_buffer_.get() + sizeof(Header); }

  Type type() const { return header()->type; }
  Subtype subtype() const { return header()->subtype; }
  EndpointId source_id() const { return header()->source_id; }
  EndpointId destination_id() const { return header()->destination_id; }

  void set_source_id(EndpointId source_id) { header()->source_id = source_id; }
  void set_destination_id(EndpointId destination_id) {
    header()->destination_id = destination_id;
  }

  
  
  
  DispatcherVector* dispatchers() { return dispatchers_.get(); }

  
  bool has_dispatchers() const {
    return dispatchers_ && !dispatchers_->empty();
  }

  
  static inline size_t RoundUpMessageAlignment(size_t n) {
    return (n + kMessageAlignment - 1) & ~(kMessageAlignment - 1);
  }

 private:
  
  struct PrivateStructForCompileAsserts;

  
  
  struct Header {
    
    
    
    
    
    uint32_t total_size;
    Type type;                  
    Subtype subtype;            
    EndpointId source_id;       
    EndpointId destination_id;  
    
    uint32_t num_bytes;
    uint32_t unused;
  };

  const Header* header() const {
    return reinterpret_cast<const Header*>(main_buffer_.get());
  }
  Header* header() { return reinterpret_cast<Header*>(main_buffer_.get()); }

  void ConstructorHelper(Type type, Subtype subtype, uint32_t num_bytes);
  void UpdateTotalSize();

  const size_t main_buffer_size_;
  const scoped_ptr<char, base::AlignedFreeDeleter> main_buffer_;  

  scoped_ptr<TransportData> transport_data_;  

  
  
  
  
  scoped_ptr<DispatcherVector> dispatchers_;

  DISALLOW_COPY_AND_ASSIGN(MessageInTransit);
};

}  
}  

#endif  
