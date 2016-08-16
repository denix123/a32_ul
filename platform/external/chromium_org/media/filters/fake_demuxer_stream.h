// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_FILTERS_FAKE_DEMUXER_STREAM_H_
#define MEDIA_FILTERS_FAKE_DEMUXER_STREAM_H_

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "media/base/audio_decoder_config.h"
#include "media/base/demuxer_stream.h"
#include "media/base/video_decoder_config.h"

namespace base {
class SingleThreadTaskRunner;
}  

namespace media {

class FakeDemuxerStream : public DemuxerStream {
 public:
  
  
  
  FakeDemuxerStream(int num_configs,
                    int num_buffers_in_one_config,
                    bool is_encrypted);
  virtual ~FakeDemuxerStream();

  
  virtual void Read(const ReadCB& read_cb) OVERRIDE;
  virtual AudioDecoderConfig audio_decoder_config() OVERRIDE;
  virtual VideoDecoderConfig video_decoder_config() OVERRIDE;
  virtual Type type() OVERRIDE;
  virtual bool SupportsConfigChanges() OVERRIDE;
  virtual VideoRotation video_rotation() OVERRIDE;

  void Initialize();

  int num_buffers_returned() const { return num_buffers_returned_; }

  
  
  void HoldNextRead();

  
  
  
  void HoldNextConfigChangeRead();

  
  void SatisfyRead();

  
  void SatisfyReadAndHoldNext();

  
  
  void Reset();

  
  
  void SeekToStart();

  
  void set_splice_timestamp(base::TimeDelta splice_timestamp) {
    splice_timestamp_ = splice_timestamp;
  }

 private:
  void UpdateVideoDecoderConfig();
  void DoRead();

  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;

  const int num_configs_;
  const int num_buffers_in_one_config_;
  const bool config_changes_;
  const bool is_encrypted_;

  int num_configs_left_;

  
  int num_buffers_left_in_current_config_;

  int num_buffers_returned_;

  base::TimeDelta current_timestamp_;
  base::TimeDelta duration_;
  base::TimeDelta splice_timestamp_;

  gfx::Size next_coded_size_;
  VideoDecoderConfig video_decoder_config_;

  ReadCB read_cb_;

  int next_read_num_;
  
  
  int read_to_hold_;

  DISALLOW_COPY_AND_ASSIGN(FakeDemuxerStream);
};

}  

#endif  
