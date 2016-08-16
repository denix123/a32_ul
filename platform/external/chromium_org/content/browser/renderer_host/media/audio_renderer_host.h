// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef CONTENT_BROWSER_RENDERER_HOST_MEDIA_AUDIO_RENDERER_HOST_H_
#define CONTENT_BROWSER_RENDERER_HOST_MEDIA_AUDIO_RENDERER_HOST_H_

#include <map>

#include "base/atomic_ref_count.h"
#include "base/gtest_prod_util.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/process/process.h"
#include "base/sequenced_task_runner_helpers.h"
#include "content/common/content_export.h"
#include "content/public/browser/browser_message_filter.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/browser/render_view_host.h"
#include "media/audio/audio_io.h"
#include "media/audio/audio_logging.h"
#include "media/audio/audio_output_controller.h"
#include "media/audio/simple_sources.h"

namespace media {
class AudioManager;
class AudioParameters;
}

namespace content {

class AudioMirroringManager;
class MediaInternals;
class MediaStreamManager;
class ResourceContext;

class CONTENT_EXPORT AudioRendererHost : public BrowserMessageFilter {
 public:
  
  AudioRendererHost(int render_process_id,
                    media::AudioManager* audio_manager,
                    AudioMirroringManager* mirroring_manager,
                    MediaInternals* media_internals,
                    MediaStreamManager* media_stream_manager);

  
  void GetOutputControllers(
      int render_view_id,
      const RenderViewHost::GetAudioOutputControllersCallback& callback) const;

  
  virtual void OnChannelClosing() OVERRIDE;
  virtual void OnDestruct() const OVERRIDE;
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

  
  
  bool HasActiveAudio();

 private:
  friend class AudioRendererHostTest;
  friend class BrowserThread;
  friend class base::DeleteHelper<AudioRendererHost>;
  friend class MockAudioRendererHost;
  friend class TestAudioRendererHost;
  FRIEND_TEST_ALL_PREFIXES(AudioRendererHostTest, CreateMockStream);
  FRIEND_TEST_ALL_PREFIXES(AudioRendererHostTest, MockStreamDataConversation);

  class AudioEntry;
  typedef std::map<int, AudioEntry*> AudioEntryMap;

  virtual ~AudioRendererHost();

  

  

  
  
  
  
  
  
  
  void OnCreateStream(int stream_id,
                      int render_view_id,
                      int render_frame_id,
                      int session_id,
                      const media::AudioParameters& params);

  
  void OnPlayStream(int stream_id);

  
  void OnPauseStream(int stream_id);

  
  void OnCloseStream(int stream_id);

  
  void OnSetVolume(int stream_id, double volume);

  
  
  
  void DoCompleteCreation(int stream_id);

  
  void DoNotifyStreamStateChanged(int stream_id, bool is_playing);

  RenderViewHost::AudioOutputControllerList DoGetOutputControllers(
      int render_view_id) const;

  
  void SendErrorMessage(int stream_id);

  
  
  void DeleteEntry(scoped_ptr<AudioEntry> entry);

  
  void ReportErrorAndClose(int stream_id);

  
  
  AudioEntry* LookupById(int stream_id);

  
  const int render_process_id_;

  media::AudioManager* const audio_manager_;
  AudioMirroringManager* const mirroring_manager_;
  scoped_ptr<media::AudioLog> audio_log_;

  
  MediaStreamManager* media_stream_manager_;

  
  AudioEntryMap audio_entries_;

  
  base::AtomicRefCount num_playing_streams_;

  DISALLOW_COPY_AND_ASSIGN(AudioRendererHost);
};

}  

#endif  
