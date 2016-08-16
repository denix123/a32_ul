// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_ANDROID_MEDIA_DECODER_JOB_H_
#define MEDIA_BASE_ANDROID_MEDIA_DECODER_JOB_H_

#include "base/callback.h"
#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "media/base/android/demuxer_stream_player_params.h"
#include "media/base/android/media_codec_bridge.h"
#include "ui/gl/android/scoped_java_surface.h"

namespace base {
class SingleThreadTaskRunner;
}

namespace media {

class MediaDrmBridge;

class MediaDecoderJob {
 public:
  struct Deleter {
    inline void operator()(MediaDecoderJob* ptr) const { ptr->Release(); }
  };

  
  
  
  
  
  typedef base::Callback<void(MediaCodecStatus, base::TimeDelta,
                              base::TimeDelta)> DecoderCallback;
  
  
  
  
  typedef base::Callback<void(base::TimeDelta, base::TimeDelta)>
      ReleaseOutputCompletionCallback;

  virtual ~MediaDecoderJob();

  
  void OnDataReceived(const DemuxerData& data);

  
  
  void Prefetch(const base::Closure& prefetch_cb);

  
  
  
  
  
  
  
  bool Decode(base::TimeTicks start_time_ticks,
              base::TimeDelta start_presentation_timestamp,
              const DecoderCallback& callback);

  
  
  
  
  
  
  
  
  void StopDecode();

  
  virtual void Flush();

  
  void BeginPrerolling(base::TimeDelta preroll_timestamp);

  
  virtual void ReleaseDecoderResources();

  
  virtual void SetDemuxerConfigs(const DemuxerConfigs& configs) = 0;

  
  bool OutputEOSReached() const;

  
  
  virtual bool HasStream() const = 0;

  void SetDrmBridge(MediaDrmBridge* drm_bridge);

  bool is_decoding() const { return !decode_cb_.is_null(); }

  bool is_content_encrypted() const { return is_content_encrypted_; }

  bool prerolling() const { return prerolling_; }

 protected:
  
  
  
  
  
  MediaDecoderJob(
      const scoped_refptr<base::SingleThreadTaskRunner>& decoder_task_runner,
      const base::Closure& request_data_cb,
      const base::Closure& config_changed_cb);

  
  
  virtual void ReleaseOutputBuffer(
      int output_buffer_index,
      size_t size,
      bool render_output,
      base::TimeDelta current_presentation_timestamp,
      const ReleaseOutputCompletionCallback& callback) = 0;

  
  
  virtual bool ComputeTimeToRender() const = 0;

  
  base::android::ScopedJavaLocalRef<jobject> GetMediaCrypto();

  
  void ReleaseMediaCodecBridge();

  MediaDrmBridge* drm_bridge() { return drm_bridge_; }

  void set_is_content_encrypted(bool is_content_encrypted) {
    is_content_encrypted_ = is_content_encrypted;
  }

  bool need_to_reconfig_decoder_job_;

  scoped_ptr<MediaCodecBridge> media_codec_bridge_;

 private:
  friend class MediaSourcePlayerTest;

  
  void Release();

  
  MediaCodecStatus QueueInputBuffer(const AccessUnit& unit);

  
  bool HasData() const;

  
  
  void RequestData(const base::Closure& done_cb);

  
  void DecodeCurrentAccessUnit(
      base::TimeTicks start_time_ticks,
      base::TimeDelta start_presentation_timestamp);

  
  
  
  
  
  
  
  
  
  
  
  void DecodeInternal(const AccessUnit& unit,
                      base::TimeTicks start_time_ticks,
                      base::TimeDelta start_presentation_timestamp,
                      bool needs_flush,
                      const DecoderCallback& callback);

  
  
  
  void OnDecodeCompleted(MediaCodecStatus status,
                         base::TimeDelta current_presentation_timestamp,
                         base::TimeDelta max_presentation_timestamp);

  
  const AccessUnit& CurrentAccessUnit() const;

  
  size_t CurrentReceivedDataChunkIndex() const;

  
  
  
  
  
  bool NoAccessUnitsRemainingInChunk(bool is_active_chunk) const;

  
  void RequestCurrentChunkIfEmpty();

  
  void InitializeReceivedData();

  
  void OnDecoderDrained();

  
  
  bool CreateMediaCodecBridge();

  
  
  
  virtual void CurrentDataConsumed(bool is_config_change) {}

  
  
  virtual bool CreateMediaCodecBridgeInternal() = 0;

  
  
  virtual bool AreDemuxerConfigsChanged(
      const DemuxerConfigs& configs) const = 0;

  
  
  virtual bool IsCodecReconfigureNeeded(const DemuxerConfigs& configs) const;

  
  
  virtual bool UpdateOutputFormat();

  
  size_t inactive_demuxer_data_index() const {
    return 1 - current_demuxer_data_index_;
  }

  
  scoped_refptr<base::SingleThreadTaskRunner> ui_task_runner_;

  
  scoped_refptr<base::SingleThreadTaskRunner> decoder_task_runner_;

  
  bool needs_flush_;

  
  
  bool input_eos_encountered_;

  
  bool output_eos_encountered_;

  
  
  
  
  bool skip_eos_enqueue_;

  
  
  
  
  base::TimeDelta preroll_timestamp_;

  
  
  
  
  
  bool prerolling_;

  
  base::Closure request_data_cb_;

  
  base::Closure config_changed_cb_;

  
  base::Closure data_received_cb_;

  
  DecoderCallback decode_cb_;

  
  
  
  
  
  
  DemuxerData received_data_[2];

  
  size_t current_demuxer_data_index_;

  
  size_t access_unit_index_[2];

  
  
  int input_buf_index_;

  
  bool is_content_encrypted_;

  
  
  bool stop_decode_pending_;

  
  
  
  bool destroy_pending_;

  
  bool is_requesting_demuxer_data_;

  
  bool is_incoming_data_invalid_;

  
  
  
  bool release_resources_pending_;

  
  MediaDrmBridge* drm_bridge_;

  
  
  bool drain_decoder_;

  
  
  AccessUnit eos_unit_;

  DISALLOW_IMPLICIT_CONSTRUCTORS(MediaDecoderJob);
};

}  

#endif  
