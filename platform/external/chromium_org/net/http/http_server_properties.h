// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_HTTP_HTTP_SERVER_PROPERTIES_H_
#define NET_HTTP_HTTP_SERVER_PROPERTIES_H_

#include <map>
#include <string>
#include "base/basictypes.h"
#include "base/containers/mru_cache.h"
#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "net/base/host_port_pair.h"
#include "net/base/net_export.h"
#include "net/socket/next_proto.h"
#include "net/spdy/spdy_framer.h"  

namespace net {

enum AlternateProtocolExperiment {
  
  ALTERNATE_PROTOCOL_NOT_PART_OF_EXPERIMENT = 0,
  
  ALTERNATE_PROTOCOL_TRUNCATED_200_SERVERS,
  
  ALTERNATE_PROTOCOL_TRUNCATED_1000_SERVERS,
};

enum AlternateProtocolUsage {
  
  ALTERNATE_PROTOCOL_USAGE_NO_RACE = 0,
  
  ALTERNATE_PROTOCOL_USAGE_WON_RACE = 1,
  
  ALTERNATE_PROTOCOL_USAGE_LOST_RACE = 2,
  
  
  
  ALTERNATE_PROTOCOL_USAGE_MAPPING_MISSING = 3,
  
  ALTERNATE_PROTOCOL_USAGE_BROKEN = 4,
  
  ALTERNATE_PROTOCOL_USAGE_MAX,
};

NET_EXPORT void HistogramAlternateProtocolUsage(
    AlternateProtocolUsage usage,
    AlternateProtocolExperiment alternate_protocol_experiment);

enum BrokenAlternateProtocolLocation {
  BROKEN_ALTERNATE_PROTOCOL_LOCATION_HTTP_STREAM_FACTORY_IMPL_JOB = 0,
  BROKEN_ALTERNATE_PROTOCOL_LOCATION_QUIC_STREAM_FACTORY = 1,
  BROKEN_ALTERNATE_PROTOCOL_LOCATION_HTTP_STREAM_FACTORY_IMPL_JOB_ALT = 2,
  BROKEN_ALTERNATE_PROTOCOL_LOCATION_HTTP_STREAM_FACTORY_IMPL_JOB_MAIN = 3,
  BROKEN_ALTERNATE_PROTOCOL_LOCATION_MAX,
};

NET_EXPORT void HistogramBrokenAlternateProtocolLocation(
    BrokenAlternateProtocolLocation location);

enum AlternateProtocol {
  DEPRECATED_NPN_SPDY_2 = 0,
  ALTERNATE_PROTOCOL_MINIMUM_VALID_VERSION = DEPRECATED_NPN_SPDY_2,
  NPN_SPDY_MINIMUM_VERSION = DEPRECATED_NPN_SPDY_2,
  NPN_SPDY_3,
  NPN_SPDY_3_1,
  NPN_SPDY_4,  
  NPN_SPDY_MAXIMUM_VERSION = NPN_SPDY_4,
  QUIC,
  ALTERNATE_PROTOCOL_MAXIMUM_VALID_VERSION = QUIC,
  ALTERNATE_PROTOCOL_BROKEN,  
  UNINITIALIZED_ALTERNATE_PROTOCOL,
};

NET_EXPORT bool IsAlternateProtocolValid(AlternateProtocol protocol);

enum AlternateProtocolSize {
  NUM_VALID_ALTERNATE_PROTOCOLS =
    ALTERNATE_PROTOCOL_MAXIMUM_VALID_VERSION -
    ALTERNATE_PROTOCOL_MINIMUM_VALID_VERSION + 1,
};

NET_EXPORT const char* AlternateProtocolToString(AlternateProtocol protocol);
NET_EXPORT AlternateProtocol AlternateProtocolFromString(
    const std::string& str);
NET_EXPORT_PRIVATE AlternateProtocol AlternateProtocolFromNextProto(
    NextProto next_proto);

struct NET_EXPORT AlternateProtocolInfo {
  AlternateProtocolInfo(uint16 port,
                        AlternateProtocol protocol,
                        double probability)
      : port(port),
        protocol(protocol),
        probability(probability) {}

  bool Equals(const AlternateProtocolInfo& other) const {
    return port == other.port &&
        protocol == other.protocol &&
        probability == other.probability;
  }

  std::string ToString() const;

  uint16 port;
  AlternateProtocol protocol;
  double probability;
};

struct NET_EXPORT SupportsQuic {
  SupportsQuic() : used_quic(false) {}
  SupportsQuic(bool used_quic, const std::string& address)
      : used_quic(used_quic),
        address(address) {}

  bool Equals(const SupportsQuic& other) const {
    return used_quic == other.used_quic && address == other.address;
  }

  bool used_quic;
  std::string address;
};

typedef base::MRUCache<
    HostPortPair, AlternateProtocolInfo> AlternateProtocolMap;
typedef base::MRUCache<HostPortPair, SettingsMap> SpdySettingsMap;
typedef std::map<HostPortPair, SupportsQuic> SupportsQuicMap;

extern const char kAlternateProtocolHeader[];

class NET_EXPORT HttpServerProperties {
 public:
  struct NetworkStats {
    base::TimeDelta srtt;
    uint64 bandwidth_estimate;
  };

  HttpServerProperties() {}
  virtual ~HttpServerProperties() {}

  
  virtual base::WeakPtr<HttpServerProperties> GetWeakPtr() = 0;

  
  virtual void Clear() = 0;

  
  virtual bool SupportsSpdy(const HostPortPair& server) = 0;

  
  
  virtual void SetSupportsSpdy(const HostPortPair& server,
                               bool support_spdy) = 0;

  
  virtual bool HasAlternateProtocol(const HostPortPair& server) = 0;

  
  
  virtual AlternateProtocolInfo GetAlternateProtocol(
      const HostPortPair& server) = 0;

  
  virtual void SetAlternateProtocol(const HostPortPair& server,
                                    uint16 alternate_port,
                                    AlternateProtocol alternate_protocol,
                                    double probability) = 0;

  
  virtual void SetBrokenAlternateProtocol(const HostPortPair& server) = 0;

  
  virtual bool WasAlternateProtocolRecentlyBroken(
      const HostPortPair& server) = 0;

  
  virtual void ConfirmAlternateProtocol(const HostPortPair& server) = 0;

  
  virtual void ClearAlternateProtocol(const HostPortPair& server) = 0;

  
  virtual const AlternateProtocolMap& alternate_protocol_map() const = 0;

  virtual void SetAlternateProtocolExperiment(
      AlternateProtocolExperiment experiment) = 0;

  
  
  
  
  
  virtual void SetAlternateProtocolProbabilityThreshold(
      double threshold) = 0;

  virtual AlternateProtocolExperiment GetAlternateProtocolExperiment()
      const = 0;

  
  
  virtual const SettingsMap& GetSpdySettings(
      const HostPortPair& host_port_pair) = 0;

  
  
  virtual bool SetSpdySetting(const HostPortPair& host_port_pair,
                              SpdySettingsIds id,
                              SpdySettingsFlags flags,
                              uint32 value) = 0;

  
  virtual void ClearSpdySettings(const HostPortPair& host_port_pair) = 0;

  
  virtual void ClearAllSpdySettings() = 0;

  
  virtual const SpdySettingsMap& spdy_settings_map() const = 0;

  
  virtual SupportsQuic GetSupportsQuic(
      const HostPortPair& host_port_pair) const = 0;

  virtual void SetSupportsQuic(const HostPortPair& host_port_pair,
                               bool used_quic,
                               const std::string& address) = 0;

  virtual const SupportsQuicMap& supports_quic_map() const = 0;

  virtual void SetServerNetworkStats(const HostPortPair& host_port_pair,
                                     NetworkStats stats) = 0;

  virtual const NetworkStats* GetServerNetworkStats(
      const HostPortPair& host_port_pair) const = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(HttpServerProperties);
};

}  

#endif  
