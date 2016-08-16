// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_CAST_CHANNEL_CAST_FRAMER_H_
#define EXTENSIONS_BROWSER_API_CAST_CHANNEL_CAST_FRAMER_H_

#include "base/basictypes.h"
#include "extensions/common/api/cast_channel.h"
#include "net/base/io_buffer.h"

namespace extensions {
namespace core_api {
namespace cast_channel {
class CastMessage;

class MessageFramer {
 public:
  
  
  explicit MessageFramer(scoped_refptr<net::GrowableIOBuffer> input_buffer);
  ~MessageFramer();

  
  
  
  size_t BytesRequested();

  
  
  static bool Serialize(const CastMessage& message_proto,
                        std::string* message_data);

  
  
  
  
  
  
  
  
  
  
  
  scoped_ptr<CastMessage> Ingest(size_t num_bytes,
                                 size_t* message_length,
                                 ChannelError* error);

  
  
  struct MessageHeader {
    MessageHeader();
    
    void SetMessageSize(size_t message_size);
    
    void PrependToString(std::string* str);
    
    static void Deserialize(char* data, MessageHeader* header);
    
    static size_t header_size();
    
    
    static size_t max_message_size();
    std::string ToString();
    
    size_t message_size;
  };

 private:
  enum MessageElement { HEADER, BODY };

  
  void Reset();

  
  MessageElement current_element_;

  
  size_t message_bytes_received_;

  
  size_t body_size_;

  
  
  scoped_refptr<net::GrowableIOBuffer> input_buffer_;

  
  bool error_;

  DISALLOW_COPY_AND_ASSIGN(MessageFramer);
};
}  
}  
}  
#endif  
