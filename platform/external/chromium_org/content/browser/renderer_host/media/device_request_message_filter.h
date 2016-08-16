// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDERER_HOST_MEDIA_DEVICE_REQUEST_MESSAGE_FILTER_H_
#define CONTENT_BROWSER_RENDERER_HOST_MEDIA_DEVICE_REQUEST_MESSAGE_FILTER_H_

#include <map>
#include <string>

#include "base/synchronization/lock.h"
#include "content/browser/renderer_host/media/media_stream_requester.h"
#include "content/common/content_export.h"
#include "content/public/browser/browser_message_filter.h"

namespace content {

class MediaStreamManager;
class ResourceContext;

class CONTENT_EXPORT DeviceRequestMessageFilter : public BrowserMessageFilter,
                                                  public MediaStreamRequester {
 public:
  DeviceRequestMessageFilter(ResourceContext* resource_context,
                             MediaStreamManager* media_stream_manager,
                             int render_process_id);

  
  
  
  
  virtual void StreamGenerated(
      int render_frame_id, int page_request_id, const std::string& label,
      const StreamDeviceInfoArray& audio_devices,
      const StreamDeviceInfoArray& video_devices) OVERRIDE {}
  virtual void StreamGenerationFailed(
      int render_frame_id,
      int page_request_id,
      content::MediaStreamRequestResult result) OVERRIDE {}
  virtual void DeviceStopped(int render_frame_id,
                             const std::string& label,
                             const StreamDeviceInfo& device) OVERRIDE {}
  virtual void DeviceOpened(int render_frame_id,
                            int page_request_id,
                            const std::string& label,
                            const StreamDeviceInfo& video_device) OVERRIDE {}
  
  virtual void DevicesEnumerated(int render_frame_id,
                                 int page_request_id,
                                 const std::string& label,
                                 const StreamDeviceInfoArray& devices) OVERRIDE;

  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;
  virtual void OnChannelClosing() OVERRIDE;

 protected:
  virtual ~DeviceRequestMessageFilter();

 private:
  void OnGetSources(int request_id, const GURL& security_origin);

  
  ResourceContext* resource_context_;
  MediaStreamManager* media_stream_manager_;

  struct DeviceRequest;
  typedef std::vector<DeviceRequest> DeviceRequestList;
  
  DeviceRequestList requests_;

  int render_process_id_;

  DISALLOW_COPY_AND_ASSIGN(DeviceRequestMessageFilter);
};

}  

#endif  