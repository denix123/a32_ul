// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_HTTP_HTTP_SERVER_PROPERTIES_IMPL_H_
#define NET_HTTP_HTTP_SERVER_PROPERTIES_IMPL_H_

#include <map>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/containers/hash_tables.h"
#include "base/gtest_prod_util.h"
#include "base/threading/non_thread_safe.h"
#include "base/values.h"
#include "net/base/host_port_pair.h"
#include "net/base/net_export.h"
#include "net/http/http_server_properties.h"

namespace base {
class ListValue;
}

namespace net {

class NET_EXPORT HttpServerPropertiesImpl
    : public HttpServerProperties,
      NON_EXPORTED_BASE(public base::NonThreadSafe) {
 public:
  HttpServerPropertiesImpl();
  virtual ~HttpServerPropertiesImpl();

  
  
  void InitializeSpdyServers(std::vector<std::string>* spdy_servers,
                             bool support_spdy);

  void InitializeAlternateProtocolServers(
      AlternateProtocolMap* alternate_protocol_servers);

  void InitializeSpdySettingsServers(SpdySettingsMap* spdy_settings_map);

  void InitializeSupportsQuic(SupportsQuicMap* supports_quic_map);

  
  
  void GetSpdyServerList(base::ListValue* spdy_server_list,
                         size_t max_size) const;

  
  
  static std::string GetFlattenedSpdyServer(
      const net::HostPortPair& host_port_pair);

  
  
  
  static void ForceAlternateProtocol(const AlternateProtocolInfo& pair);
  static void DisableForcedAlternateProtocol();

  
  
  std::string GetCanonicalSuffix(const net::HostPortPair& server);

  
  
  

  
  virtual base::WeakPtr<HttpServerProperties> GetWeakPtr() OVERRIDE;

  
  virtual void Clear() OVERRIDE;

  
  virtual bool SupportsSpdy(const HostPortPair& server) OVERRIDE;

  
  virtual void SetSupportsSpdy(const HostPortPair& server,
                               bool support_spdy) OVERRIDE;

  
  virtual bool HasAlternateProtocol(const HostPortPair& server) OVERRIDE;

  
  
  virtual AlternateProtocolInfo GetAlternateProtocol(
      const HostPortPair& server) OVERRIDE;

  
  virtual void SetAlternateProtocol(
      const HostPortPair& server,
      uint16 alternate_port,
      AlternateProtocol alternate_protocol,
      double probability) OVERRIDE;

  
  virtual void SetBrokenAlternateProtocol(const HostPortPair& server) OVERRIDE;

  
  virtual bool WasAlternateProtocolRecentlyBroken(
      const HostPortPair& server) OVERRIDE;

  
  virtual void ConfirmAlternateProtocol(const HostPortPair& server) OVERRIDE;

  
  virtual void ClearAlternateProtocol(const HostPortPair& server) OVERRIDE;

  
  virtual const AlternateProtocolMap& alternate_protocol_map() const OVERRIDE;

  virtual void SetAlternateProtocolExperiment(
      AlternateProtocolExperiment experiment) OVERRIDE;

  virtual void SetAlternateProtocolProbabilityThreshold(
      double threshold) OVERRIDE;

  virtual AlternateProtocolExperiment GetAlternateProtocolExperiment()
      const OVERRIDE;

  
  
  virtual const SettingsMap& GetSpdySettings(
      const HostPortPair& host_port_pair) OVERRIDE;

  
  
  virtual bool SetSpdySetting(const HostPortPair& host_port_pair,
                              SpdySettingsIds id,
                              SpdySettingsFlags flags,
                              uint32 value) OVERRIDE;

  
  virtual void ClearSpdySettings(const HostPortPair& host_port_pair) OVERRIDE;

  
  virtual void ClearAllSpdySettings() OVERRIDE;

  
  virtual const SpdySettingsMap& spdy_settings_map() const OVERRIDE;

  
  virtual SupportsQuic GetSupportsQuic(
      const HostPortPair& host_port_pair) const OVERRIDE;

  virtual void SetSupportsQuic(const HostPortPair& host_port_pair,
                               bool used_quic,
                               const std::string& address) OVERRIDE;

  virtual const SupportsQuicMap& supports_quic_map() const OVERRIDE;

  
  virtual void SetServerNetworkStats(const HostPortPair& host_port_pair,
                                     NetworkStats stats) OVERRIDE;

  virtual const NetworkStats* GetServerNetworkStats(
      const HostPortPair& host_port_pair) const OVERRIDE;

 private:
  
  
  typedef base::MRUCache<std::string, bool> SpdyServerHostPortMap;
  typedef std::map<HostPortPair, NetworkStats> ServerNetworkStatsMap;
  typedef std::map<HostPortPair, HostPortPair> CanonicalHostMap;
  typedef std::vector<std::string> CanonicalSufficList;
  
  struct BrokenAlternateProtocolEntry {
    HostPortPair server;
    base::TimeTicks when;
  };
  typedef std::list<BrokenAlternateProtocolEntry>
      BrokenAlternateProtocolList;
  
  
  typedef std::map<HostPortPair, int> BrokenAlternateProtocolMap;

  
  CanonicalHostMap::const_iterator GetCanonicalHost(HostPortPair server) const;

  void RemoveCanonicalHost(const HostPortPair& server);
  void ExpireBrokenAlternateProtocolMappings();
  void ScheduleBrokenAlternateProtocolMappingsExpiration();

  SpdyServerHostPortMap spdy_servers_map_;

  AlternateProtocolMap alternate_protocol_map_;
  BrokenAlternateProtocolList broken_alternate_protocol_list_;
  BrokenAlternateProtocolMap broken_alternate_protocol_map_;
  AlternateProtocolExperiment alternate_protocol_experiment_;

  SpdySettingsMap spdy_settings_map_;
  SupportsQuicMap supports_quic_map_;
  ServerNetworkStatsMap server_network_stats_map_;
  
  
  
  CanonicalHostMap canonical_host_to_origin_map_;
  
  
  CanonicalSufficList canoncial_suffixes_;

  double alternate_protocol_probability_threshold_;

  base::WeakPtrFactory<HttpServerPropertiesImpl> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(HttpServerPropertiesImpl);
};

}  

#endif  
