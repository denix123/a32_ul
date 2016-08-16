// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef MEDIA_VIDEO_CAPTURE_WIN_VIDEO_CAPTURE_DEVICE_WIN_H_
#define MEDIA_VIDEO_CAPTURE_WIN_VIDEO_CAPTURE_DEVICE_WIN_H_

#define NO_DSHOW_STRSAFE
#include <dshow.h>

#include <map>
#include <string>

#include "base/threading/non_thread_safe.h"
#include "base/threading/thread.h"
#include "base/win/scoped_comptr.h"
#include "media/video/capture/video_capture_device.h"
#include "media/video/capture/video_capture_types.h"
#include "media/video/capture/win/capability_list_win.h"
#include "media/video/capture/win/sink_filter_win.h"
#include "media/video/capture/win/sink_input_pin_win.h"

namespace media {

class VideoCaptureDeviceWin
    : public base::NonThreadSafe,
      public VideoCaptureDevice,
      public SinkFilterObserver {
 public:
  
  
  
  class ScopedMediaType {
   public:
    ScopedMediaType() : media_type_(NULL) {}
    ~ScopedMediaType() { Free(); }

    AM_MEDIA_TYPE* operator->() { return media_type_; }
    AM_MEDIA_TYPE* get() { return media_type_; }
    void Free();
    AM_MEDIA_TYPE** Receive();

   private:
    void FreeMediaType(AM_MEDIA_TYPE* mt);
    void DeleteMediaType(AM_MEDIA_TYPE* mt);

    AM_MEDIA_TYPE* media_type_;
  };

  static HRESULT GetDeviceFilter(const std::string& device_id,
                                 const CLSID device_class_id,
                                 IBaseFilter** filter);
  static base::win::ScopedComPtr<IPin> GetPin(IBaseFilter* filter,
                                              PIN_DIRECTION pin_dir,
                                              REFGUID category,
                                              REFGUID major_type);
  static VideoPixelFormat TranslateMediaSubtypeToPixelFormat(
      const GUID& sub_type);

  explicit VideoCaptureDeviceWin(const Name& device_name);
  virtual ~VideoCaptureDeviceWin();
  
  bool Init();

  
  virtual void AllocateAndStart(
      const VideoCaptureParams& params,
      scoped_ptr<VideoCaptureDevice::Client> client) OVERRIDE;
  virtual void StopAndDeAllocate() OVERRIDE;

 private:
  enum InternalState {
    kIdle,  
    kCapturing,  
    kError  
            
  };

  
  virtual void FrameReceived(const uint8* buffer, int length);

  bool CreateCapabilityMap();
  void SetAntiFlickerInCaptureFilter();
  HRESULT InstantiateWDMFiltersAndPins();
  HRESULT AddWDMCrossbarFilterToGraphAndConnect();
  void SetErrorState(const std::string& reason);

  Name device_name_;
  InternalState state_;
  scoped_ptr<VideoCaptureDevice::Client> client_;

  base::win::ScopedComPtr<IBaseFilter> capture_filter_;
  base::win::ScopedComPtr<IGraphBuilder> graph_builder_;
  base::win::ScopedComPtr<IMediaControl> media_control_;
  base::win::ScopedComPtr<IPin> input_sink_pin_;
  base::win::ScopedComPtr<IPin> output_capture_pin_;
  
  base::win::ScopedComPtr<IBaseFilter> mjpg_filter_;
  base::win::ScopedComPtr<IPin> input_mjpg_pin_;
  base::win::ScopedComPtr<IPin> output_mjpg_pin_;
  
  
  base::win::ScopedComPtr<IBaseFilter> crossbar_filter_;
  base::win::ScopedComPtr<IPin> crossbar_video_output_pin_;
  base::win::ScopedComPtr<IPin> analog_video_input_pin_;

  scoped_refptr<SinkFilter> sink_filter_;

  
  CapabilityList capabilities_;
  VideoCaptureFormat capture_format_;

  DISALLOW_IMPLICIT_CONSTRUCTORS(VideoCaptureDeviceWin);
};

}  

#endif  
