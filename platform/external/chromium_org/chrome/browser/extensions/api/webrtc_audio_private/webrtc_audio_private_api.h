// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_WEBRTC_AUDIO_PRIVATE_WEBRTC_AUDIO_PRIVATE_API_H_
#define CHROME_BROWSER_EXTENSIONS_API_WEBRTC_AUDIO_PRIVATE_WEBRTC_AUDIO_PRIVATE_API_H_

#include "base/memory/ref_counted.h"
#include "base/system_monitor/system_monitor.h"
#include "chrome/browser/extensions/chrome_extension_function.h"
#include "chrome/common/extensions/api/webrtc_audio_private.h"
#include "content/public/browser/render_view_host.h"
#include "extensions/browser/browser_context_keyed_api_factory.h"
#include "media/audio/audio_device_name.h"
#include "url/gurl.h"

namespace content {
class ResourceContext;
}

namespace extensions {

class WebrtcAudioPrivateEventService
    : public BrowserContextKeyedAPI,
      public base::SystemMonitor::DevicesChangedObserver {
 public:
  explicit WebrtcAudioPrivateEventService(content::BrowserContext* context);
  virtual ~WebrtcAudioPrivateEventService();

  
  virtual void Shutdown() OVERRIDE;
  static BrowserContextKeyedAPIFactory<WebrtcAudioPrivateEventService>*
      GetFactoryInstance();
  static const char* service_name();

  
  virtual void OnDevicesChanged(
      base::SystemMonitor::DeviceType device_type) OVERRIDE;

 private:
  friend class BrowserContextKeyedAPIFactory<WebrtcAudioPrivateEventService>;

  void SignalEvent();

  content::BrowserContext* browser_context_;
};

class WebrtcAudioPrivateFunction : public ChromeAsyncExtensionFunction {
 protected:
  WebrtcAudioPrivateFunction();
  virtual ~WebrtcAudioPrivateFunction();

 protected:
  
  
  void GetOutputDeviceNames();

  
  virtual void OnOutputDeviceNames(
      scoped_ptr<media::AudioDeviceNames> device_names);

  
  
  
  
  
  
  
  bool GetControllerList(int tab_id);

  
  virtual void OnControllerList(
      const content::RenderViewHost::AudioOutputControllerList& list);

  
  
  
  
  
  
  
  void CalculateHMAC(const std::string& raw_id);

  
  virtual void OnHMACCalculated(const std::string& hmac);

  
  
  
  std::string CalculateHMACImpl(const std::string& raw_id);

  
  
  void InitResourceContext();

  
  
  content::ResourceContext* resource_context() const;

 private:
  content::ResourceContext* resource_context_;

  DISALLOW_COPY_AND_ASSIGN(WebrtcAudioPrivateFunction);
};

class WebrtcAudioPrivateGetSinksFunction : public WebrtcAudioPrivateFunction {
 protected:
  virtual ~WebrtcAudioPrivateGetSinksFunction() {}

 private:
  DECLARE_EXTENSION_FUNCTION("webrtcAudioPrivate.getSinks",
                             WEBRTC_AUDIO_PRIVATE_GET_SINKS);

  
  
  
  virtual bool RunAsync() OVERRIDE;
  void DoQuery();
  virtual void OnOutputDeviceNames(
      scoped_ptr<media::AudioDeviceNames> raw_ids) OVERRIDE;
  void DoneOnUIThread();
};

class WebrtcAudioPrivateGetActiveSinkFunction
    : public WebrtcAudioPrivateFunction {
 protected:
  virtual ~WebrtcAudioPrivateGetActiveSinkFunction() {}

 private:
  DECLARE_EXTENSION_FUNCTION("webrtcAudioPrivate.getActiveSink",
                             WEBRTC_AUDIO_PRIVATE_GET_ACTIVE_SINK);

  virtual bool RunAsync() OVERRIDE;
  virtual void OnControllerList(
      const content::RenderViewHost::AudioOutputControllerList&
      controllers) OVERRIDE;
  virtual void OnHMACCalculated(const std::string& hmac) OVERRIDE;
};

class WebrtcAudioPrivateSetActiveSinkFunction
    : public WebrtcAudioPrivateFunction {
 public:
  WebrtcAudioPrivateSetActiveSinkFunction();

 protected:
  virtual ~WebrtcAudioPrivateSetActiveSinkFunction();

 private:
  DECLARE_EXTENSION_FUNCTION("webrtcAudioPrivate.setActiveSink",
                             WEBRTC_AUDIO_PRIVATE_SET_ACTIVE_SINK);

  virtual bool RunAsync() OVERRIDE;
  virtual void OnControllerList(
      const content::RenderViewHost::AudioOutputControllerList&
      controllers) OVERRIDE;
  virtual void OnOutputDeviceNames(
      scoped_ptr<media::AudioDeviceNames> device_names) OVERRIDE;
  void SwitchDone();
  void DoneOnUIThread();

  int tab_id_;
  std::string sink_id_;

  
  content::RenderViewHost::AudioOutputControllerList controllers_;

  
  
  size_t num_remaining_sink_ids_;
};

class WebrtcAudioPrivateGetAssociatedSinkFunction
    : public WebrtcAudioPrivateFunction {
 public:
  WebrtcAudioPrivateGetAssociatedSinkFunction();

 protected:
  virtual ~WebrtcAudioPrivateGetAssociatedSinkFunction();

 private:
  DECLARE_EXTENSION_FUNCTION("webrtcAudioPrivate.getAssociatedSink",
                             WEBRTC_AUDIO_PRIVATE_GET_ASSOCIATED_SINK);

  virtual bool RunAsync() OVERRIDE;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  

  
  
  
  void GetDevicesOnDeviceThread();

  
  
  void GetRawSourceIDOnIOThread();

  
  void GetAssociatedSinkOnDeviceThread(const std::string& raw_source_id);

  
  virtual void OnHMACCalculated(const std::string& hmac) OVERRIDE;

  
  
  scoped_ptr<api::webrtc_audio_private::GetAssociatedSink::Params> params_;

  
  media::AudioDeviceNames source_devices_;
};

}  

#endif  
