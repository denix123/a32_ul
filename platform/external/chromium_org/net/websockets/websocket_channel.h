// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_WEBSOCKETS_WEBSOCKET_CHANNEL_H_
#define NET_WEBSOCKETS_WEBSOCKET_CHANNEL_H_

#include <queue>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/compiler_specific.h"  
#include "base/i18n/streaming_utf8_validator.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "net/base/net_export.h"
#include "net/websockets/websocket_event_interface.h"
#include "net/websockets/websocket_frame.h"
#include "net/websockets/websocket_stream.h"
#include "url/gurl.h"

namespace url {
class Origin;
}  

namespace net {

class BoundNetLog;
class IOBuffer;
class URLRequestContext;
struct WebSocketHandshakeRequestInfo;
struct WebSocketHandshakeResponseInfo;

class NET_EXPORT WebSocketChannel {
 public:
  
  
  typedef base::Callback<scoped_ptr<WebSocketStreamRequest>(
      const GURL&,
      const std::vector<std::string>&,
      const url::Origin&,
      URLRequestContext*,
      const BoundNetLog&,
      scoped_ptr<WebSocketStream::ConnectDelegate>)> WebSocketStreamCreator;

  
  
  
  WebSocketChannel(scoped_ptr<WebSocketEventInterface> event_interface,
                   URLRequestContext* url_request_context);
  virtual ~WebSocketChannel();

  
  void SendAddChannelRequest(
      const GURL& socket_url,
      const std::vector<std::string>& requested_protocols,
      const url::Origin& origin);

  
  
  
  
  
  
  
  
  
  
  
  void SendFrame(bool fin,
                 WebSocketFrameHeader::OpCode op_code,
                 const std::vector<char>& data);

  
  
  
  void SendFlowControl(int64 quota);

  
  
  
  
  
  
  
  
  
  void StartClosingHandshake(uint16 code, const std::string& reason);

  
  
  void SendAddChannelRequestForTesting(
      const GURL& socket_url,
      const std::vector<std::string>& requested_protocols,
      const url::Origin& origin,
      const WebSocketStreamCreator& creator);

  
  
  
  void SetClosingHandshakeTimeoutForTesting(base::TimeDelta delay);

  
  
  void OnStartOpeningHandshake(
      scoped_ptr<WebSocketHandshakeRequestInfo> request);

  
  
  void OnFinishOpeningHandshake(
      scoped_ptr<WebSocketHandshakeResponseInfo> response);

 private:
  class HandshakeNotificationSender;

  
  
  class PendingReceivedFrame {
   public:
    PendingReceivedFrame(bool final,
                         WebSocketFrameHeader::OpCode opcode,
                         const scoped_refptr<IOBuffer>& data,
                         size_t offset,
                         size_t size);
    ~PendingReceivedFrame();

    bool final() const { return final_; }
    WebSocketFrameHeader::OpCode opcode() const { return opcode_; }
    
    void ResetOpcode();
    const scoped_refptr<IOBuffer>& data() const { return data_; }
    size_t offset() const { return offset_; }
    size_t size() const { return size_; }
    
    void DidConsume(size_t bytes);

    
    
    

   private:
    bool final_;
    WebSocketFrameHeader::OpCode opcode_;
    scoped_refptr<IOBuffer> data_;
    
    
    size_t offset_;
    
    size_t size_;
  };

  
  
  
  typedef WebSocketEventInterface::ChannelState ChannelState;

  
  
  
  enum State {
    FRESHLY_CONSTRUCTED,
    CONNECTING,
    CONNECTED,
    SEND_CLOSED,  
    RECV_CLOSED,  
                  
                  
    CLOSE_WAIT,   
                  
    CLOSED,       
                  
  };

  
  
  
  
  
  
  class ConnectDelegate;

  
  void SendAddChannelRequestWithSuppliedCreator(
      const GURL& socket_url,
      const std::vector<std::string>& requested_protocols,
      const url::Origin& origin,
      const WebSocketStreamCreator& creator);

  
  
  void OnConnectSuccess(scoped_ptr<WebSocketStream> stream);

  
  
  void OnConnectFailure(const std::string& message);

  
  
  
  void OnSSLCertificateError(
      scoped_ptr<WebSocketEventInterface::SSLErrorCallbacks>
          ssl_error_callbacks,
      const SSLInfo& ssl_info,
      bool fatal);

  
  
  void ScheduleOpeningHandshakeNotification();

  
  void SetState(State new_state);

  
  bool InClosingState() const;

  
  ChannelState WriteFrames() WARN_UNUSED_RESULT;

  
  
  
  
  
  ChannelState OnWriteDone(bool synchronous, int result) WARN_UNUSED_RESULT;

  
  
  ChannelState ReadFrames() WARN_UNUSED_RESULT;

  
  
  
  
  ChannelState OnReadDone(bool synchronous, int result) WARN_UNUSED_RESULT;

  
  
  
  
  
  
  
  ChannelState HandleFrame(
      scoped_ptr<WebSocketFrame> frame) WARN_UNUSED_RESULT;

  
  
  ChannelState HandleFrameByState(
      const WebSocketFrameHeader::OpCode opcode,
      bool final,
      const scoped_refptr<IOBuffer>& data_buffer,
      size_t size) WARN_UNUSED_RESULT;

  
  
  
  ChannelState HandleDataFrame(WebSocketFrameHeader::OpCode opcode,
                               bool final,
                               const scoped_refptr<IOBuffer>& data_buffer,
                               size_t size) WARN_UNUSED_RESULT;

  
  
  
  
  
  ChannelState SendFrameFromIOBuffer(bool fin,
                                     WebSocketFrameHeader::OpCode op_code,
                                     const scoped_refptr<IOBuffer>& buffer,
                                     size_t size) WARN_UNUSED_RESULT;

  
  
  
  
  
  
  
  
  
  ChannelState FailChannel(const std::string& message,
                           uint16 code,
                           const std::string& reason) WARN_UNUSED_RESULT;

  
  
  
  
  ChannelState SendClose(uint16 code,
                         const std::string& reason) WARN_UNUSED_RESULT;

  
  
  
  
  
  
  bool ParseClose(const scoped_refptr<IOBuffer>& buffer,
                  size_t size,
                  uint16* code,
                  std::string* reason,
                  std::string* message);

  
  
  
  
  
  ChannelState DoDropChannel(bool was_clean,
                             uint16 code,
                             const std::string& reason);

  
  
  void CloseTimeout();

  
  GURL socket_url_;

  
  const scoped_ptr<WebSocketEventInterface> event_interface_;

  
  URLRequestContext* const url_request_context_;

  
  scoped_ptr<WebSocketStream> stream_;

  
  
  class SendBuffer;
  
  scoped_ptr<SendBuffer> data_being_sent_;
  
  
  scoped_ptr<SendBuffer> data_to_send_next_;

  
  ScopedVector<WebSocketFrame> read_frames_;

  
  
  std::queue<PendingReceivedFrame> pending_received_frames_;

  
  
  scoped_ptr<WebSocketStreamRequest> stream_request_;

  
  
  
  int send_quota_low_water_mark_;
  
  
  int send_quota_high_water_mark_;
  
  
  int current_send_quota_;
  
  
  int current_receive_quota_;

  
  base::OneShotTimer<WebSocketChannel> timer_;

  
  base::TimeDelta timeout_;

  
  
  
  uint16 received_close_code_;
  std::string received_close_reason_;

  
  
  State state_;

  
  scoped_ptr<HandshakeNotificationSender> notification_sender_;

  
  base::StreamingUtf8Validator outgoing_utf8_validator_;
  bool sending_text_message_;

  
  base::StreamingUtf8Validator incoming_utf8_validator_;
  bool receiving_text_message_;

  
  bool expecting_to_handle_continuation_;

  
  
  bool initial_frame_forwarded_;

  
  
  base::TimeTicks established_on_;

  DISALLOW_COPY_AND_ASSIGN(WebSocketChannel);
};

}  

#endif  
