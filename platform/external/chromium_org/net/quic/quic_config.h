// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_QUIC_CONFIG_H_
#define NET_QUIC_QUIC_CONFIG_H_

#include <string>

#include "base/basictypes.h"
#include "net/quic/quic_protocol.h"
#include "net/quic/quic_time.h"

namespace net {

namespace test {
class QuicConfigPeer;
}  

class CryptoHandshakeMessage;

enum QuicConfigPresence {
  
  
  PRESENCE_OPTIONAL,
  
  
  PRESENCE_REQUIRED,
};

enum HelloType {
  CLIENT,
  SERVER,
};

class NET_EXPORT_PRIVATE QuicConfigValue {
 public:
  QuicConfigValue(QuicTag tag, QuicConfigPresence presence);
  virtual ~QuicConfigValue();

  
  virtual void ToHandshakeMessage(CryptoHandshakeMessage* out) const = 0;

  
  
  virtual QuicErrorCode ProcessPeerHello(
      const CryptoHandshakeMessage& peer_hello,
      HelloType hello_type,
      std::string* error_details) = 0;

 protected:
  const QuicTag tag_;
  const QuicConfigPresence presence_;
};

class NET_EXPORT_PRIVATE QuicNegotiableValue : public QuicConfigValue {
 public:
  QuicNegotiableValue(QuicTag tag, QuicConfigPresence presence);
  virtual ~QuicNegotiableValue();

  bool negotiated() const {
    return negotiated_;
  }

 protected:
  bool negotiated_;
};

class NET_EXPORT_PRIVATE QuicNegotiableUint32 : public QuicNegotiableValue {
 public:
  
  QuicNegotiableUint32(QuicTag name, QuicConfigPresence presence);
  virtual ~QuicNegotiableUint32();

  
  
  
  
  void set(uint32 max, uint32 default_value);

  
  
  uint32 GetUint32() const;

  
  
  virtual void ToHandshakeMessage(CryptoHandshakeMessage* out) const OVERRIDE;

  
  
  
  
  virtual QuicErrorCode ProcessPeerHello(
      const CryptoHandshakeMessage& peer_hello,
      HelloType hello_type,
      std::string* error_details) OVERRIDE;

 private:
  uint32 max_value_;
  uint32 default_value_;
  uint32 negotiated_value_;
};

class NET_EXPORT_PRIVATE QuicNegotiableTag : public QuicNegotiableValue {
 public:
  QuicNegotiableTag(QuicTag name, QuicConfigPresence presence);
  virtual ~QuicNegotiableTag();

  
  
  
  void set(const QuicTagVector& possible_values, QuicTag default_value);

  
  
  QuicTag GetTag() const;

  
  
  
  virtual void ToHandshakeMessage(CryptoHandshakeMessage* out) const OVERRIDE;

  
  
  
  virtual QuicErrorCode ProcessPeerHello(
      const CryptoHandshakeMessage& peer_hello,
      HelloType hello_type,
      std::string* error_details) OVERRIDE;

 private:
  
  
  
  QuicErrorCode ReadVector(const CryptoHandshakeMessage& msg,
                           const QuicTag** out,
                           size_t* out_length,
                           std::string* error_details) const;

  QuicTag negotiated_tag_;
  QuicTagVector possible_values_;
  QuicTag default_value_;
};

class NET_EXPORT_PRIVATE QuicFixedUint32 : public QuicConfigValue {
 public:
  QuicFixedUint32(QuicTag name, QuicConfigPresence presence);
  virtual ~QuicFixedUint32();

  bool HasSendValue() const;

  uint32 GetSendValue() const;

  void SetSendValue(uint32 value);

  bool HasReceivedValue() const;

  uint32 GetReceivedValue() const;

  void SetReceivedValue(uint32 value);

  
  virtual void ToHandshakeMessage(CryptoHandshakeMessage* out) const OVERRIDE;

  
  virtual QuicErrorCode ProcessPeerHello(
      const CryptoHandshakeMessage& peer_hello,
      HelloType hello_type,
      std::string* error_details) OVERRIDE;

 private:
  uint32 send_value_;
  bool has_send_value_;
  uint32 receive_value_;
  bool has_receive_value_;
};

class NET_EXPORT_PRIVATE QuicFixedTag : public QuicConfigValue {
 public:
  QuicFixedTag(QuicTag name, QuicConfigPresence presence);
  virtual ~QuicFixedTag();

  bool HasSendValue() const;

  QuicTag GetSendValue() const;

  void SetSendValue(QuicTag value);

  bool HasReceivedValue() const;

  QuicTag GetReceivedValue() const;

  void SetReceivedValue(QuicTag value);

  
  virtual void ToHandshakeMessage(CryptoHandshakeMessage* out) const OVERRIDE;

  
  virtual QuicErrorCode ProcessPeerHello(
      const CryptoHandshakeMessage& peer_hello,
      HelloType hello_type,
      std::string* error_details) OVERRIDE;

 private:
  QuicTag send_value_;
  bool has_send_value_;
  QuicTag receive_value_;
  bool has_receive_value_;
};

class NET_EXPORT_PRIVATE QuicFixedTagVector : public QuicConfigValue {
 public:
  QuicFixedTagVector(QuicTag name, QuicConfigPresence presence);
  virtual ~QuicFixedTagVector();

  bool HasSendValues() const;

  QuicTagVector GetSendValues() const;

  void SetSendValues(const QuicTagVector& values);

  bool HasReceivedValues() const;

  QuicTagVector GetReceivedValues() const;

  void SetReceivedValues(const QuicTagVector& values);

  
  
  virtual void ToHandshakeMessage(CryptoHandshakeMessage* out) const OVERRIDE;

  
  
  virtual QuicErrorCode ProcessPeerHello(
      const CryptoHandshakeMessage& peer_hello,
      HelloType hello_type,
      std::string* error_details) OVERRIDE;

 private:
  QuicTagVector send_values_;
  bool has_send_values_;
  QuicTagVector receive_values_;
  bool has_receive_values_;
};

class NET_EXPORT_PRIVATE QuicConfig {
 public:
  QuicConfig();
  ~QuicConfig();

  void set_congestion_feedback(const QuicTagVector& congestion_feedback,
                               QuicTag default_congestion_feedback);

  QuicTag congestion_feedback() const;

  void SetConnectionOptionsToSend(const QuicTagVector& connection_options);

  bool HasReceivedConnectionOptions() const;

  QuicTagVector ReceivedConnectionOptions() const;

  bool HasSendConnectionOptions() const;

  QuicTagVector SendConnectionOptions() const;

  void SetLossDetectionToSend(QuicTag loss_detection);

  bool HasReceivedLossDetection() const;

  QuicTag ReceivedLossDetection() const;

  void set_idle_connection_state_lifetime(
      QuicTime::Delta max_idle_connection_state_lifetime,
      QuicTime::Delta default_idle_conection_state_lifetime);

  QuicTime::Delta idle_connection_state_lifetime() const;

  QuicTime::Delta keepalive_timeout() const;

  void set_max_streams_per_connection(size_t max_streams,
                                      size_t default_streams);

  uint32 max_streams_per_connection() const;

  void set_max_time_before_crypto_handshake(
      QuicTime::Delta max_time_before_crypto_handshake);

  QuicTime::Delta max_time_before_crypto_handshake() const;

  
  void SetInitialCongestionWindowToSend(size_t initial_window);

  bool HasReceivedInitialCongestionWindow() const;

  uint32 ReceivedInitialCongestionWindow() const;

  
  void SetInitialRoundTripTimeUsToSend(size_t rtt_us);

  bool HasReceivedInitialRoundTripTimeUs() const;

  uint32 ReceivedInitialRoundTripTimeUs() const;

  bool HasInitialRoundTripTimeUsToSend() const;

  uint32 GetInitialRoundTripTimeUsToSend() const;

  
  
  
  void SetInitialFlowControlWindowToSend(uint32 window_bytes);

  uint32 GetInitialFlowControlWindowToSend() const;

  bool HasReceivedInitialFlowControlWindowBytes() const;

  uint32 ReceivedInitialFlowControlWindowBytes() const;

  
  void SetInitialStreamFlowControlWindowToSend(uint32 window_bytes);

  uint32 GetInitialStreamFlowControlWindowToSend() const;

  bool HasReceivedInitialStreamFlowControlWindowBytes() const;

  uint32 ReceivedInitialStreamFlowControlWindowBytes() const;

  
  void SetInitialSessionFlowControlWindowToSend(uint32 window_bytes);

  uint32 GetInitialSessionFlowControlWindowToSend() const;

  bool HasReceivedInitialSessionFlowControlWindowBytes() const;

  uint32 ReceivedInitialSessionFlowControlWindowBytes() const;

  
  void SetSocketReceiveBufferToSend(uint32 window_bytes);

  uint32 GetSocketReceiveBufferToSend() const;

  bool HasReceivedSocketReceiveBuffer() const;

  uint32 ReceivedSocketReceiveBuffer() const;

  bool negotiated();

  
  void SetDefaults();

  
  
  void ToHandshakeMessage(CryptoHandshakeMessage* out) const;

  
  
  QuicErrorCode ProcessPeerHello(const CryptoHandshakeMessage& peer_hello,
                                 HelloType hello_type,
                                 std::string* error_details);

 private:
  friend class test::QuicConfigPeer;

  
  QuicNegotiableTag congestion_feedback_;
  
  QuicFixedTagVector connection_options_;
  
  QuicFixedTag loss_detection_;
  
  QuicNegotiableUint32 idle_connection_state_lifetime_seconds_;
  
  QuicNegotiableUint32 keepalive_timeout_seconds_;
  
  QuicNegotiableUint32 max_streams_per_connection_;
  
  
  QuicTime::Delta max_time_before_crypto_handshake_;
  
  QuicFixedUint32 initial_congestion_window_;
  
  QuicFixedUint32 initial_round_trip_time_us_;

  
  
  QuicFixedUint32 initial_flow_control_window_bytes_;

  
  QuicFixedUint32 initial_stream_flow_control_window_bytes_;
  
  QuicFixedUint32 initial_session_flow_control_window_bytes_;

  
  QuicFixedUint32 socket_receive_buffer_;
};

}  

#endif  
