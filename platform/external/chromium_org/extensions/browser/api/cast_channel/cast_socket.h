// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_CAST_CHANNEL_CAST_SOCKET_H_
#define EXTENSIONS_BROWSER_API_CAST_CHANNEL_CAST_SOCKET_H_

#include <queue>
#include <string>

#include "base/basictypes.h"
#include "base/cancelable_callback.h"
#include "base/gtest_prod_util.h"
#include "base/memory/ref_counted.h"
#include "base/threading/thread_checker.h"
#include "base/timer/timer.h"
#include "extensions/browser/api/api_resource.h"
#include "extensions/browser/api/api_resource_manager.h"
#include "extensions/common/api/cast_channel.h"
#include "extensions/common/api/cast_channel/logging.pb.h"
#include "net/base/completion_callback.h"
#include "net/base/io_buffer.h"
#include "net/base/ip_endpoint.h"
#include "net/base/net_log.h"

namespace net {
class AddressList;
class CertVerifier;
class SSLClientSocket;
class StreamSocket;
class TCPClientSocket;
class TransportSecurityState;
}

namespace extensions {
namespace core_api {
namespace cast_channel {

class CastMessage;
class Logger;
struct LastErrors;
class MessageFramer;

class CastSocket : public ApiResource {
 public:
  
  
  
  class Delegate {
   public:
    
    
    virtual void OnError(const CastSocket* socket,
                         ChannelError error_state,
                         const LastErrors& last_errors) = 0;
    
    virtual void OnMessage(const CastSocket* socket,
                           const MessageInfo& message) = 0;

   protected:
    virtual ~Delegate() {}
  };

  
  
  
  CastSocket(const std::string& owner_extension_id,
             const net::IPEndPoint& ip_endpoint,
             ChannelAuthType channel_auth,
             CastSocket::Delegate* delegate,
             net::NetLog* net_log,
             const base::TimeDelta& connect_timeout,
             const scoped_refptr<Logger>& logger);

  
  virtual ~CastSocket();

  
  const net::IPEndPoint& ip_endpoint() const { return ip_endpoint_; }

  
  ChannelAuthType channel_auth() const { return channel_auth_; }

  
  
  std::string CastUrl() const;

  
  int id() const { return channel_id_; }

  
  void set_id(int channel_id) { channel_id_ = channel_id; }

  
  virtual ReadyState ready_state() const;

  
  
  virtual ChannelError error_state() const;

  
  
  
  virtual void Connect(const net::CompletionCallback& callback);

  
  
  
  
  
  
  
  
  
  virtual void SendMessage(const MessageInfo& message,
                           const net::CompletionCallback& callback);

  
  
  
  
  virtual void Close(const net::CompletionCallback& callback);

 private:
  friend class ApiResourceManager<CastSocket>;
  friend class CastSocketTest;
  friend class TestCastSocket;

  static const char* service_name() { return "CastSocketManager"; }

  
  virtual scoped_ptr<net::TCPClientSocket> CreateTcpSocket();
  
  virtual scoped_ptr<net::SSLClientSocket> CreateSslSocket(
      scoped_ptr<net::StreamSocket> socket);
  
  
  
  virtual bool ExtractPeerCert(std::string* cert);
  
  
  
  virtual bool VerifyChallengeReply();

  
  
  void OnConnectTimeout();

  
  
  
  
  
  
  
  
  
  
  
  
  void DoConnectLoop(int result);
  
  
  
  int DoTcpConnect();
  int DoTcpConnectComplete(int result);
  int DoSslConnect();
  int DoSslConnectComplete(int result);
  int DoAuthChallengeSend();
  int DoAuthChallengeSendComplete(int result);
  void DoAuthChallengeSendWriteComplete(int result);
  int DoAuthChallengeReplyComplete(int result);
  

  
  
  
  
  void DoWriteLoop(int result);
  
  
  
  int DoWrite();
  int DoWriteComplete(int result);
  int DoWriteCallback();
  int DoWriteError(int result);
  

  
  
  
  
  void DoReadLoop(int result);
  
  
  
  int DoRead();
  int DoReadComplete(int result);
  int DoReadCallback();
  int DoReadError(int result);
  

  
  void DoConnectCallback(int result);
  
  void SendCastMessageInternal(const CastMessage& message,
                               const net::CompletionCallback& callback);
  void PostTaskToStartConnectLoop(int result);
  void PostTaskToStartReadLoop();
  void StartReadLoop();
  
  void CloseWithError();
  
  
  
  void CloseInternal();
  
  
  void RunPendingCallbacksOnClose();
  
  static bool Serialize(const CastMessage& message_proto,
                        std::string* message_data);

  virtual bool CalledOnValidThread() const;

  virtual base::Timer* GetTimer();

  void SetConnectState(proto::ConnectionState connect_state);
  void SetReadyState(ReadyState ready_state);
  void SetErrorState(ChannelError error_state);
  void SetReadState(proto::ReadState read_state);
  void SetWriteState(proto::WriteState write_state);

  base::ThreadChecker thread_checker_;

  
  int channel_id_;

  
  net::IPEndPoint ip_endpoint_;
  
  ChannelAuthType channel_auth_;
  
  Delegate* delegate_;

  
  scoped_refptr<net::GrowableIOBuffer> read_buffer_;
  scoped_ptr<MessageFramer> framer_;

  
  net::NetLog* net_log_;
  
  net::NetLog::Source net_log_source_;

  
  scoped_refptr<Logger> logger_;

  
  
  
  scoped_ptr<net::CertVerifier> cert_verifier_;
  scoped_ptr<net::TransportSecurityState> transport_security_state_;

  
  scoped_ptr<net::TCPClientSocket> tcp_socket_;
  
  scoped_ptr<net::SSLClientSocket> socket_;
  
  
  std::string peer_cert_;
  
  scoped_ptr<CastMessage> challenge_reply_;

  
  net::CompletionCallback connect_callback_;

  
  base::CancelableClosure connect_timeout_callback_;
  
  base::TimeDelta connect_timeout_;
  
  scoped_ptr<base::Timer> connect_timeout_timer_;
  
  
  bool is_canceled_;

  scoped_ptr<CastMessage> current_message_;

  
  proto::ConnectionState connect_state_;
  
  proto::WriteState write_state_;
  
  proto::ReadState read_state_;
  
  ChannelError error_state_;
  
  ReadyState ready_state_;

  
  
  base::CancelableClosure connect_loop_callback_;
  
  
  base::CancelableClosure send_auth_challenge_callback_;
  
  
  base::CancelableClosure read_loop_callback_;

  // Holds a message to be written to the socket. |callback| is invoked when the
  // message is fully written or an error occurrs.
  struct WriteRequest {
    explicit WriteRequest(const net::CompletionCallback& callback);
    ~WriteRequest();
    
    
    bool SetContent(const CastMessage& message_proto);

    net::CompletionCallback callback;
    std::string message_namespace;
    scoped_refptr<net::DrainableIOBuffer> io_buffer;
  };
  
  // being written.
  std::queue<WriteRequest> write_queue_;

  FRIEND_TEST_ALL_PREFIXES(CastSocketTest, TestFullSecureConnectionFlowAsync);
  FRIEND_TEST_ALL_PREFIXES(CastSocketTest, TestRead);
  FRIEND_TEST_ALL_PREFIXES(CastSocketTest, TestReadHeaderParseError);
  FRIEND_TEST_ALL_PREFIXES(CastSocketTest, TestReadMany);
  FRIEND_TEST_ALL_PREFIXES(CastSocketTest, TestWriteErrorLargeMessage);
  DISALLOW_COPY_AND_ASSIGN(CastSocket);
};
}  
}  
}  

#endif  
