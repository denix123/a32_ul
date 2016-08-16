// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BLINK_BUFFERED_DATA_SOURCE_H_
#define MEDIA_BLINK_BUFFERED_DATA_SOURCE_H_

#include <string>
#include <vector>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "base/synchronization/lock.h"
#include "media/base/data_source.h"
#include "media/base/media_export.h"
#include "media/base/ranges.h"
#include "media/blink/buffered_resource_loader.h"
#include "url/gurl.h"

namespace base {
class SingleThreadTaskRunner;
}

namespace media {
class MediaLog;

class MEDIA_EXPORT BufferedDataSourceHost {
 public:
  
  virtual void SetTotalBytes(int64 total_bytes) = 0;

  
  
  
  virtual void AddBufferedByteRange(int64 start, int64 end) = 0;

 protected:
  virtual ~BufferedDataSourceHost() {};
};

class MEDIA_EXPORT BufferedDataSource : public DataSource {
 public:
  
  
  
  
  
  
  
  enum Preload {
    NONE,
    METADATA,
    AUTO,
  };
  typedef base::Callback<void(bool)> DownloadingCB;

  
  
  
  BufferedDataSource(
      const GURL& url,
      BufferedResourceLoader::CORSMode cors_mode,
      const scoped_refptr<base::SingleThreadTaskRunner>& task_runner,
      blink::WebFrame* frame,
      MediaLog* media_log,
      BufferedDataSourceHost* host,
      const DownloadingCB& downloading_cb);
  virtual ~BufferedDataSource();

  
  
  
  typedef base::Callback<void(bool)> InitializeCB;
  void Initialize(const InitializeCB& init_cb);

  
  void SetPreload(Preload preload);

  
  
  
  
  bool HasSingleOrigin();

  
  bool DidPassCORSAccessCheck() const;

  
  
  
  
  
  void Abort();

  
  
  void MediaPlaybackRateChanged(float playback_rate);
  void MediaIsPlaying();
  void MediaIsPaused();

  
  bool assume_fully_buffered() { return !url_.SchemeIsHTTPOrHTTPS(); }

  
  
  virtual void Stop() OVERRIDE;

  virtual void Read(int64 position, int size, uint8* data,
                    const DataSource::ReadCB& read_cb) OVERRIDE;
  virtual bool GetSize(int64* size_out) OVERRIDE;
  virtual bool IsStreaming() OVERRIDE;
  virtual void SetBitrate(int bitrate) OVERRIDE;

 protected:
  
  
  
  virtual BufferedResourceLoader* CreateResourceLoader(
      int64 first_byte_position, int64 last_byte_position);

 private:
  friend class BufferedDataSourceTest;

  
  void ReadTask();

  
  
  void StopInternal_Locked();

  
  void StopLoader();

  
  void SetBitrateTask(int bitrate);

  
  
  void ReadInternal();

  
  void StartCallback(BufferedResourceLoader::Status status);

  
  
  void PartialReadStartCallback(BufferedResourceLoader::Status status);

  
  void ReadCallback(BufferedResourceLoader::Status status, int bytes_read);
  void LoadingStateChangedCallback(BufferedResourceLoader::LoadingState state);
  void ProgressCallback(int64 position);

  
  
  void UpdateDeferStrategy(bool paused);

  
  GURL url_;
  
  BufferedResourceLoader::CORSMode cors_mode_;

  
  
  
  int64 total_bytes_;

  
  
  bool streaming_;

  
  blink::WebFrame* frame_;

  
  scoped_ptr<BufferedResourceLoader> loader_;

  
  InitializeCB init_cb_;

  
  
  class ReadOperation;
  scoped_ptr<ReadOperation> read_op_;

  
  
  
  
  
  
  
  
  
  
  std::vector<uint8> intermediate_read_buffer_;

  
  const scoped_refptr<base::SingleThreadTaskRunner> render_task_runner_;

  
  base::Lock lock_;

  
  bool stop_signal_received_;

  
  
  bool media_has_played_;

  
  
  Preload preload_;

  
  int bitrate_;

  
  float playback_rate_;

  scoped_refptr<MediaLog> media_log_;

  
  BufferedDataSourceHost* host_;

  DownloadingCB downloading_cb_;

  
  base::WeakPtrFactory<BufferedDataSource> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(BufferedDataSource);
};

}  

#endif  
