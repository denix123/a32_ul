// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_COMMON_MEDIA_STREAM_REQUEST_H_
#define CONTENT_PUBLIC_COMMON_MEDIA_STREAM_REQUEST_H_

#include <map>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/memory/scoped_ptr.h"
#include "content/common/content_export.h"
#include "ui/gfx/native_widget_types.h"
#include "url/gurl.h"

namespace content {

enum MediaStreamType {
  MEDIA_NO_SERVICE = 0,

  
  MEDIA_DEVICE_AUDIO_CAPTURE,
  MEDIA_DEVICE_VIDEO_CAPTURE,

  
  MEDIA_TAB_AUDIO_CAPTURE,
  MEDIA_TAB_VIDEO_CAPTURE,

  
  MEDIA_DESKTOP_VIDEO_CAPTURE,

  
  
  
  MEDIA_LOOPBACK_AUDIO_CAPTURE,

  
  
  
  MEDIA_DEVICE_AUDIO_OUTPUT,

  NUM_MEDIA_TYPES
};

enum MediaStreamRequestType {
  MEDIA_DEVICE_ACCESS = 0,
  MEDIA_GENERATE_STREAM,
  MEDIA_ENUMERATE_DEVICES,
  MEDIA_OPEN_DEVICE  
};

enum VideoFacingMode {
  MEDIA_VIDEO_FACING_NONE = 0,
  MEDIA_VIDEO_FACING_USER,
  MEDIA_VIDEO_FACING_ENVIRONMENT,
  MEDIA_VIDEO_FACING_LEFT,
  MEDIA_VIDEO_FACING_RIGHT,

  NUM_MEDIA_VIDEO_FACING_MODE
};

enum MediaStreamRequestResult {
  MEDIA_DEVICE_OK = 0,
  MEDIA_DEVICE_PERMISSION_DENIED = 1,
  MEDIA_DEVICE_PERMISSION_DISMISSED = 2,
  MEDIA_DEVICE_INVALID_STATE = 3,
  MEDIA_DEVICE_NO_HARDWARE = 4,
  MEDIA_DEVICE_INVALID_SECURITY_ORIGIN = 5,
  MEDIA_DEVICE_TAB_CAPTURE_FAILURE = 6,
  MEDIA_DEVICE_SCREEN_CAPTURE_FAILURE = 7,
  MEDIA_DEVICE_CAPTURE_FAILURE = 8,
  MEDIA_DEVICE_CONSTRAINT_NOT_SATISFIED = 9,
  MEDIA_DEVICE_TRACK_START_FAILURE = 10,
  MEDIA_DEVICE_NOT_SUPPORTED = 11,
  MEDIA_DEVICE_FAILED_DUE_TO_SHUTDOWN = 12,
  NUM_MEDIA_REQUEST_RESULTS
};

CONTENT_EXPORT bool IsAudioInputMediaType(MediaStreamType type);
CONTENT_EXPORT bool IsVideoMediaType(MediaStreamType type);

struct CONTENT_EXPORT MediaStreamDevice {
  MediaStreamDevice();

  MediaStreamDevice(
      MediaStreamType type,
      const std::string& id,
      const std::string& name);

  MediaStreamDevice(
      MediaStreamType type,
      const std::string& id,
      const std::string& name,
      int sample_rate,
      int channel_layout,
      int frames_per_buffer);

  ~MediaStreamDevice();

  bool IsEqual(const MediaStreamDevice& second) const;

  
  MediaStreamType type;

  
  std::string id;

  
  VideoFacingMode video_facing;

  
  
  std::string matched_output_device_id;

  
  std::string name;

  
  
  struct AudioDeviceParameters {
    AudioDeviceParameters()
        : sample_rate(), channel_layout(), frames_per_buffer(), effects() {
    }

    AudioDeviceParameters(int sample_rate, int channel_layout,
        int frames_per_buffer)
        : sample_rate(sample_rate),
          channel_layout(channel_layout),
          frames_per_buffer(frames_per_buffer),
          effects() {
    }

    
    int sample_rate;

    
    
    
    int channel_layout;

    
    
    
    
    int frames_per_buffer;

    
    int effects;
  };

  
  

  
  AudioDeviceParameters input;

  
  
  
  
  AudioDeviceParameters matched_output;
};

class CONTENT_EXPORT MediaStreamDevices
    : public std::vector<MediaStreamDevice> {
 public:
  MediaStreamDevices();
  MediaStreamDevices(size_t count, const MediaStreamDevice& value);

  
  
  const MediaStreamDevice* FindById(const std::string& device_id) const;
};

typedef std::map<MediaStreamType, MediaStreamDevices> MediaStreamDeviceMap;

struct CONTENT_EXPORT MediaStreamRequest {
  MediaStreamRequest(
      int render_process_id,
      int render_frame_id,
      int page_request_id,
      const GURL& security_origin,
      bool user_gesture,
      MediaStreamRequestType request_type,
      const std::string& requested_audio_device_id,
      const std::string& requested_video_device_id,
      MediaStreamType audio_type,
      MediaStreamType video_type);

  ~MediaStreamRequest();

  
  
  
  int render_process_id;

  
  
  
  int render_frame_id;

  
  
  int page_request_id;

  
  std::string tab_capture_device_id;

  
  GURL security_origin;

  
  bool user_gesture;

  
  
  
  
  MediaStreamRequestType request_type;

  
  std::string requested_audio_device_id;
  std::string requested_video_device_id;

  
  MediaStreamType audio_type;

  
  MediaStreamType video_type;
};

class MediaStreamUI {
 public:
  virtual ~MediaStreamUI() {}

  
  
  
  virtual gfx::NativeViewId OnStarted(const base::Closure& stop) = 0;
};

typedef base::Callback<void(
    const MediaStreamDevices& devices,
    content::MediaStreamRequestResult result,
    scoped_ptr<MediaStreamUI> ui)> MediaResponseCallback;

}  

#endif  
