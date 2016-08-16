// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_CRYPTO_SOURCE_ADDRESS_TOKEN_H_
#define NET_QUIC_CRYPTO_SOURCE_ADDRESS_TOKEN_H_

#include <string>

#include "base/basictypes.h"
#include "base/strings/string_piece.h"
#include "net/base/net_export.h"

namespace net {

class NET_EXPORT_PRIVATE CachedNetworkParameters {
 public:
  
  
  enum PreviousConnectionState {
    SLOW_START = 0,
    CONGESTION_AVOIDANCE = 1,
  };

  CachedNetworkParameters();
  ~CachedNetworkParameters();

  std::string serving_region() const {
    return serving_region_;
  }
  void set_serving_region(base::StringPiece serving_region) {
    serving_region_ = serving_region.as_string();
  }

  int32 bandwidth_estimate_bytes_per_second() const {
    return bandwidth_estimate_bytes_per_second_;
  }
  void set_bandwidth_estimate_bytes_per_second(
      int32 bandwidth_estimate_bytes_per_second) {
    bandwidth_estimate_bytes_per_second_ = bandwidth_estimate_bytes_per_second;
  }

  int32 max_bandwidth_estimate_bytes_per_second() const {
    return max_bandwidth_estimate_bytes_per_second_;
  }
  void set_max_bandwidth_estimate_bytes_per_second(
      int32 max_bandwidth_estimate_bytes_per_second) {
    max_bandwidth_estimate_bytes_per_second_ =
        max_bandwidth_estimate_bytes_per_second;
  }

  int64 max_bandwidth_timestamp_seconds() const {
    return max_bandwidth_timestamp_seconds_;
  }
  void set_max_bandwidth_timestamp_seconds(
      int64 max_bandwidth_timestamp_seconds) {
    max_bandwidth_timestamp_seconds_ = max_bandwidth_timestamp_seconds;
  }

  int32 min_rtt_ms() const {
    return min_rtt_ms_;
  }
  void set_min_rtt_ms(int32 min_rtt_ms) {
    min_rtt_ms_ = min_rtt_ms;
  }

  int32 previous_connection_state() const {
    return previous_connection_state_;
  }
  void set_previous_connection_state(int32 previous_connection_state) {
    previous_connection_state_ = previous_connection_state;
  }

 private:
  
  
  
  
  
  std::string serving_region_;
  
  
  int32 bandwidth_estimate_bytes_per_second_;
  
  int32 max_bandwidth_estimate_bytes_per_second_;
  
  
  int64 max_bandwidth_timestamp_seconds_;
  
  
  int32 min_rtt_ms_;
  
  int32 previous_connection_state_;
};

class NET_EXPORT_PRIVATE SourceAddressToken {
 public:
  SourceAddressToken();
  ~SourceAddressToken();

  std::string SerializeAsString() const;

  bool ParseFromArray(const char* plaintext, size_t plaintext_length);

  std::string ip() const {
    return ip_;
  }
  void set_ip(base::StringPiece ip) {
    ip_ = ip.as_string();
  }

  int64 timestamp() const {
    return timestamp_;
  }
  void set_timestamp(int64 timestamp) {
    timestamp_ = timestamp;
  }

  const CachedNetworkParameters& cached_network_parameters() const {
    return cached_network_parameters_;
  }
  void set_cached_network_parameters(
      const CachedNetworkParameters& cached_network_parameters) {
    cached_network_parameters_ = cached_network_parameters;
  }

 private:
  
  
  std::string ip_;
  
  
  int64 timestamp_;

  
  
  CachedNetworkParameters cached_network_parameters_;

  DISALLOW_COPY_AND_ASSIGN(SourceAddressToken);
};

}  

#endif  
