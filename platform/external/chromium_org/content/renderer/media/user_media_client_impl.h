// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_USER_MEDIA_CLIENT_IMPL_H_
#define CONTENT_RENDERER_MEDIA_USER_MEDIA_CLIENT_IMPL_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/non_thread_safe.h"
#include "content/common/content_export.h"
#include "content/public/renderer/render_frame_observer.h"
#include "content/renderer/media/media_stream_dispatcher_eventhandler.h"
#include "content/renderer/media/media_stream_source.h"
#include "third_party/WebKit/public/platform/WebMediaStream.h"
#include "third_party/WebKit/public/platform/WebMediaStreamSource.h"
#include "third_party/WebKit/public/platform/WebSourceInfo.h"
#include "third_party/WebKit/public/platform/WebVector.h"
#include "third_party/WebKit/public/web/WebMediaDevicesRequest.h"
#include "third_party/WebKit/public/web/WebUserMediaClient.h"
#include "third_party/WebKit/public/web/WebUserMediaRequest.h"
#include "third_party/libjingle/source/talk/app/webrtc/mediastreaminterface.h"

namespace content {
class PeerConnectionDependencyFactory;
class MediaStreamDispatcher;
class MediaStreamVideoSource;
class VideoCapturerDelegate;

class CONTENT_EXPORT UserMediaClientImpl
    : public RenderFrameObserver,
      NON_EXPORTED_BASE(public blink::WebUserMediaClient),
      public MediaStreamDispatcherEventHandler,
      NON_EXPORTED_BASE(public base::NonThreadSafe) {
 public:
  
  UserMediaClientImpl(
      RenderFrame* render_frame,
      PeerConnectionDependencyFactory* dependency_factory,
      scoped_ptr<MediaStreamDispatcher> media_stream_dispatcher);
  virtual ~UserMediaClientImpl();

  MediaStreamDispatcher* media_stream_dispatcher() const {
    return media_stream_dispatcher_.get();
  }

  
  virtual void requestUserMedia(
      const blink::WebUserMediaRequest& user_media_request);
  virtual void cancelUserMediaRequest(
      const blink::WebUserMediaRequest& user_media_request);
  virtual void requestMediaDevices(
      const blink::WebMediaDevicesRequest& media_devices_request) OVERRIDE;
  virtual void cancelMediaDevicesRequest(
      const blink::WebMediaDevicesRequest& media_devices_request) OVERRIDE;
  virtual void requestSources(
      const blink::WebMediaStreamTrackSourcesRequest& sources_request) OVERRIDE;

  
  virtual void OnStreamGenerated(
      int request_id,
      const std::string& label,
      const StreamDeviceInfoArray& audio_array,
      const StreamDeviceInfoArray& video_array) OVERRIDE;
  virtual void OnStreamGenerationFailed(
      int request_id,
      MediaStreamRequestResult result) OVERRIDE;
  virtual void OnDeviceStopped(const std::string& label,
                               const StreamDeviceInfo& device_info) OVERRIDE;
  virtual void OnDevicesEnumerated(
      int request_id,
      const StreamDeviceInfoArray& device_array) OVERRIDE;
  virtual void OnDeviceOpened(
      int request_id,
      const std::string& label,
      const StreamDeviceInfo& device_info) OVERRIDE;
  virtual void OnDeviceOpenFailed(int request_id) OVERRIDE;

  
  virtual void FrameWillClose() OVERRIDE;

 protected:
  
  void OnLocalSourceStopped(const blink::WebMediaStreamSource& source);

  
  
  
  virtual void GetUserMediaRequestSucceeded(
       const blink::WebMediaStream& stream,
       blink::WebUserMediaRequest* request_info);
  virtual void GetUserMediaRequestFailed(
      blink::WebUserMediaRequest* request_info,
      MediaStreamRequestResult result);
  virtual void GetUserMediaRequestTrackStartedFailed(
      blink::WebUserMediaRequest* request_info,
      MediaStreamRequestResult result,
      const blink::WebString& result_name);
  virtual void EnumerateDevicesSucceded(
      blink::WebMediaDevicesRequest* request,
      blink::WebVector<blink::WebMediaDeviceInfo>& devices);
  virtual void EnumerateSourcesSucceded(
      blink::WebMediaStreamTrackSourcesRequest* request,
      blink::WebVector<blink::WebSourceInfo>& sources);
  
  
  virtual MediaStreamVideoSource* CreateVideoSource(
      const StreamDeviceInfo& device,
      const MediaStreamSource::SourceStoppedCallback& stop_callback);

 private:
  
  
  class UserMediaRequestInfo
      : public base::SupportsWeakPtr<UserMediaRequestInfo> {
   public:
    typedef base::Callback<void(UserMediaRequestInfo* request_info,
                                MediaStreamRequestResult result,
                                const blink::WebString& result_name)>
      ResourcesReady;

    UserMediaRequestInfo(int request_id,
                         const blink::WebUserMediaRequest& request,
                         bool enable_automatic_output_device_selection);
    ~UserMediaRequestInfo();
    int request_id;
    
    
    bool generated;
    const bool enable_automatic_output_device_selection;
    blink::WebMediaStream web_stream;
    blink::WebUserMediaRequest request;

    void StartAudioTrack(const blink::WebMediaStreamTrack& track,
                         const blink::WebMediaConstraints& constraints);

    blink::WebMediaStreamTrack CreateAndStartVideoTrack(
        const blink::WebMediaStreamSource& source,
        const blink::WebMediaConstraints& constraints);

    
    
    void CallbackOnTracksStarted(const ResourcesReady& callback);

    bool IsSourceUsed(const blink::WebMediaStreamSource& source) const;
    void RemoveSource(const blink::WebMediaStreamSource& source);

    bool HasPendingSources() const;

   private:
    void OnTrackStarted(
        MediaStreamSource* source,
        MediaStreamRequestResult result,
        const blink::WebString& result_name);
    void CheckAllTracksStarted();

    ResourcesReady ready_callback_;
    MediaStreamRequestResult request_result_;
    blink::WebString request_result_name_;
    
    std::vector<blink::WebMediaStreamSource> sources_;
    std::vector<MediaStreamSource*> sources_waiting_for_callback_;
  };
  typedef ScopedVector<UserMediaRequestInfo> UserMediaRequests;

  typedef std::vector<blink::WebMediaStreamSource> LocalStreamSources;

  struct MediaDevicesRequestInfo;
  typedef ScopedVector<MediaDevicesRequestInfo> MediaDevicesRequests;

  
  
  void InitializeSourceObject(
      const StreamDeviceInfo& device,
      blink::WebMediaStreamSource::Type type,
      const blink::WebMediaConstraints& constraints,
      blink::WebMediaStreamSource* webkit_source);

  void CreateVideoTracks(
      const StreamDeviceInfoArray& devices,
      const blink::WebMediaConstraints& constraints,
      blink::WebVector<blink::WebMediaStreamTrack>* webkit_tracks,
      UserMediaRequestInfo* request);

  void CreateAudioTracks(
      const StreamDeviceInfoArray& devices,
      const blink::WebMediaConstraints& constraints,
      blink::WebVector<blink::WebMediaStreamTrack>* webkit_tracks,
      UserMediaRequestInfo* request);

  
  
  void OnCreateNativeTracksCompleted(
      UserMediaRequestInfo* request,
      MediaStreamRequestResult result,
      const blink::WebString& result_name);

  void OnStreamGeneratedForCancelledRequest(
      const StreamDeviceInfoArray& audio_array,
      const StreamDeviceInfoArray& video_array);

  void FinalizeEnumerateDevices(MediaDevicesRequestInfo* request);
  void FinalizeEnumerateSources(MediaDevicesRequestInfo* request);

  UserMediaRequestInfo* FindUserMediaRequestInfo(int request_id);
  UserMediaRequestInfo* FindUserMediaRequestInfo(
      const blink::WebUserMediaRequest& request);
  void DeleteUserMediaRequestInfo(UserMediaRequestInfo* request);
  void DeleteAllUserMediaRequests();

  MediaDevicesRequestInfo* FindMediaDevicesRequestInfo(int request_id);
  MediaDevicesRequestInfo* FindMediaDevicesRequestInfo(
      const blink::WebMediaDevicesRequest& request);
  void CancelAndDeleteMediaDevicesRequest(MediaDevicesRequestInfo* request);

  
  
  const blink::WebMediaStreamSource* FindLocalSource(
      const StreamDeviceInfo& device) const;

  void StopLocalSource(const blink::WebMediaStreamSource& source,
                       bool notify_dispatcher);

  
  
  
  
  PeerConnectionDependencyFactory* const dependency_factory_;

  
  
  const scoped_ptr<MediaStreamDispatcher> media_stream_dispatcher_;

  LocalStreamSources local_sources_;

  UserMediaRequests user_media_requests_;

  
  MediaDevicesRequests media_devices_requests_;

  
  
  base::WeakPtrFactory<UserMediaClientImpl> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(UserMediaClientImpl);
};

}  

#endif  
