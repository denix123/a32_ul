// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef CONTENT_BROWSER_RENDERER_HOST_MEDIA_VIDEO_CAPTURE_MANAGER_H_
#define CONTENT_BROWSER_RENDERER_HOST_MEDIA_VIDEO_CAPTURE_MANAGER_H_

#include <map>
#include <set>
#include <string>

#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "base/message_loop/message_loop.h"
#include "base/process/process_handle.h"
#include "base/timer/elapsed_timer.h"
#include "content/browser/renderer_host/media/media_stream_provider.h"
#include "content/browser/renderer_host/media/video_capture_controller_event_handler.h"
#include "content/common/content_export.h"
#include "content/common/media/media_stream_options.h"
#include "media/video/capture/video_capture_device.h"
#include "media/video/capture/video_capture_device_factory.h"
#include "media/video/capture/video_capture_types.h"

namespace content {
class VideoCaptureController;
class VideoCaptureControllerEventHandler;

class CONTENT_EXPORT VideoCaptureManager : public MediaStreamProvider {
 public:
  
  typedef base::Callback<
      void(const base::WeakPtr<VideoCaptureController>&)> DoneCB;

  explicit VideoCaptureManager(
      scoped_ptr<media::VideoCaptureDeviceFactory> factory);

  
  virtual void Register(MediaStreamProviderListener* listener,
                        const scoped_refptr<base::SingleThreadTaskRunner>&
                            device_task_runner) OVERRIDE;

  virtual void Unregister() OVERRIDE;

  virtual void EnumerateDevices(MediaStreamType stream_type) OVERRIDE;

  virtual int Open(const StreamDeviceInfo& device) OVERRIDE;

  virtual void Close(int capture_session_id) OVERRIDE;

  
  
  
  
  
  
  
  
  
  
  
  
  void StartCaptureForClient(media::VideoCaptureSessionId session_id,
                             const media::VideoCaptureParams& capture_params,
                             base::ProcessHandle client_render_process,
                             VideoCaptureControllerID client_id,
                             VideoCaptureControllerEventHandler* client_handler,
                             const DoneCB& done_cb);

  
  
  
  
  void StopCaptureForClient(VideoCaptureController* controller,
                            VideoCaptureControllerID client_id,
                            VideoCaptureControllerEventHandler* client_handler,
                            bool aborted_due_to_error);

  
  
  
  void PauseCaptureForClient(
      VideoCaptureController* controller,
      VideoCaptureControllerID client_id,
      VideoCaptureControllerEventHandler* client_handler);

  
  
  
  
  
  
  
  void ResumeCaptureForClient(
      media::VideoCaptureSessionId session_id,
      const media::VideoCaptureParams& params,
      VideoCaptureController* controller,
      VideoCaptureControllerID client_id,
      VideoCaptureControllerEventHandler* client_handler);

  
  
  
  
  bool GetDeviceSupportedFormats(
      media::VideoCaptureSessionId capture_session_id,
      media::VideoCaptureFormats* supported_formats);

  
  
  
  bool GetDeviceFormatsInUse(media::VideoCaptureSessionId capture_session_id,
                             media::VideoCaptureFormats* formats_in_use);

  
  
  void SetDesktopCaptureWindowId(media::VideoCaptureSessionId session_id,
                                 gfx::NativeViewId window_id);

  
  media::VideoCaptureDeviceFactory* video_capture_device_factory() const {
    return video_capture_device_factory_.get();
  }

 private:
  virtual ~VideoCaptureManager();
  struct DeviceEntry;

  
  
  struct DeviceInfo {
    DeviceInfo();
    DeviceInfo(const media::VideoCaptureDevice::Name& name,
               const media::VideoCaptureFormats& supported_formats);
    ~DeviceInfo();

    media::VideoCaptureDevice::Name name;
    media::VideoCaptureFormats supported_formats;
  };
  typedef std::vector<DeviceInfo> DeviceInfos;

  
  
  
  void DestroyDeviceEntryIfNoClients(DeviceEntry* entry);

  
  void OnOpened(MediaStreamType type,
                media::VideoCaptureSessionId capture_session_id);
  void OnClosed(MediaStreamType type,
                media::VideoCaptureSessionId capture_session_id);
  void OnDevicesInfoEnumerated(MediaStreamType stream_type,
                               base::ElapsedTimer* timer,
                               const DeviceInfos& new_devices_info_cache);

  
  DeviceEntry* GetDeviceEntryForMediaStreamDevice(
      const MediaStreamDevice& device_info);

  
  
  DeviceEntry* GetOrCreateDeviceEntry(
      media::VideoCaptureSessionId capture_session_id);

  
  DeviceEntry* GetDeviceEntryForController(
      const VideoCaptureController* controller) const;

  bool IsOnDeviceThread() const;

  
  
  
  void ConsolidateDevicesInfoOnDeviceThread(
      base::Callback<void(const DeviceInfos&)> on_devices_enumerated_callback,
      MediaStreamType stream_type,
      const DeviceInfos& old_device_info_cache,
      scoped_ptr<media::VideoCaptureDevice::Names> names_snapshot);

  
  
  
  void DoStartDeviceOnDeviceThread(
      media::VideoCaptureSessionId session_id,
      DeviceEntry* entry,
      const media::VideoCaptureParams& params,
      scoped_ptr<media::VideoCaptureDevice::Client> client);

  
  
  void DoStopDeviceOnDeviceThread(DeviceEntry* entry);

  DeviceInfo* FindDeviceInfoById(const std::string& id,
                                 DeviceInfos& device_vector);

  void SetDesktopCaptureWindowIdOnDeviceThread(DeviceEntry* entry,
                                               gfx::NativeViewId window_id);

  void SaveDesktopCaptureWindowIdOnDeviceThread(
      media::VideoCaptureSessionId session_id,
      gfx::NativeViewId window_id);

  
  scoped_refptr<base::SingleThreadTaskRunner> device_task_runner_;

  
  MediaStreamProviderListener* listener_;
  media::VideoCaptureSessionId new_capture_session_id_;

  typedef std::map<media::VideoCaptureSessionId, MediaStreamDevice> SessionMap;
  
  
  
  
  SessionMap sessions_;

  
  
  
  
  
  
  
  
  
  struct DeviceEntry {
    DeviceEntry(MediaStreamType stream_type,
                const std::string& id,
                scoped_ptr<VideoCaptureController> controller);
    ~DeviceEntry();

    const MediaStreamType stream_type;
    const std::string id;

    
    scoped_ptr<VideoCaptureController> video_capture_controller;

    
    scoped_ptr<media::VideoCaptureDevice> video_capture_device;
  };
  typedef std::set<DeviceEntry*> DeviceEntries;
  DeviceEntries devices_;

  
  
  scoped_ptr<media::VideoCaptureDeviceFactory> video_capture_device_factory_;

  
  
  
  
  
  
  
  DeviceInfos devices_info_cache_;

  
  std::map<media::VideoCaptureSessionId, gfx::NativeViewId>
      notification_window_ids_;

  DISALLOW_COPY_AND_ASSIGN(VideoCaptureManager);
};

}  

#endif  
