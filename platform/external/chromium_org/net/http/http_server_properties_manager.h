// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_HTTP_HTTP_SERVER_PROPERTIES_MANAGER_H_
#define NET_HTTP_HTTP_SERVER_PROPERTIES_MANAGER_H_

#include <string>
#include <vector>
#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/prefs/pref_change_registrar.h"
#include "base/timer/timer.h"
#include "base/values.h"
#include "net/base/host_port_pair.h"
#include "net/http/http_server_properties.h"
#include "net/http/http_server_properties_impl.h"

class PrefService;

namespace base {
class SequencedTaskRunner;
}

namespace net {


class NET_EXPORT HttpServerPropertiesManager : public HttpServerProperties {
 public:
  
  
  
  HttpServerPropertiesManager(
      PrefService* pref_service,
      const char* pref_path,
      scoped_refptr<base::SequencedTaskRunner> network_task_runner);
  virtual ~HttpServerPropertiesManager();

  
  void InitializeOnNetworkThread();

  
  void ShutdownOnPrefThread();

  
  static void SetVersion(base::DictionaryValue* http_server_properties_dict,
                         int version_number);

  
  
  void Clear(const base::Closure& completion);

  
  
  

  
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
      double alternate_probability) OVERRIDE;

  
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

 protected:
  
  

  
  
  
  void ScheduleUpdateCacheOnPrefThread();

  
  
  virtual void StartCacheUpdateTimerOnPrefThread(base::TimeDelta delay);

  
  
  
  
  virtual void UpdateCacheFromPrefsOnPrefThread();

  
  
  void UpdateCacheFromPrefsOnNetworkThread(
      std::vector<std::string>* spdy_servers,
      SpdySettingsMap* spdy_settings_map,
      AlternateProtocolMap* alternate_protocol_map,
      AlternateProtocolExperiment alternate_protocol_experiment,
      SupportsQuicMap* supports_quic_map,
      bool detected_corrupted_prefs);

  
  
  
  void ScheduleUpdatePrefsOnNetworkThread();

  
  
  virtual void StartPrefsUpdateTimerOnNetworkThread(base::TimeDelta delay);

  
  
  
  
  void UpdatePrefsFromCacheOnNetworkThread();

  
  
  virtual void UpdatePrefsFromCacheOnNetworkThread(
      const base::Closure& completion);

  
  
  void UpdatePrefsOnPrefThread(base::ListValue* spdy_server_list,
                               SpdySettingsMap* spdy_settings_map,
                               AlternateProtocolMap* alternate_protocol_map,
                               SupportsQuicMap* supports_quic_map,
                               const base::Closure& completion);

 private:
  void OnHttpServerPropertiesChanged();

  
  
  

  const scoped_refptr<base::SequencedTaskRunner> pref_task_runner_;

  base::WeakPtr<HttpServerPropertiesManager> pref_weak_ptr_;

  
  scoped_ptr<base::OneShotTimer<HttpServerPropertiesManager> >
      pref_cache_update_timer_;

  
  PrefChangeRegistrar pref_change_registrar_;
  PrefService* pref_service_;  
  bool setting_prefs_;
  const char* path_;

  
  
  

  const scoped_refptr<base::SequencedTaskRunner> network_task_runner_;

  
  scoped_ptr<base::OneShotTimer<HttpServerPropertiesManager> >
      network_prefs_update_timer_;

  scoped_ptr<HttpServerPropertiesImpl> http_server_properties_impl_;

  
  scoped_ptr<base::WeakPtrFactory<HttpServerPropertiesManager> >
      pref_weak_ptr_factory_;

  
  scoped_ptr<base::WeakPtrFactory<HttpServerPropertiesManager> >
      network_weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(HttpServerPropertiesManager);
};

}  

#endif  
