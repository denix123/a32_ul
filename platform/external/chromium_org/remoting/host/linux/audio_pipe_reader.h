// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_HOST_LINUX_AUDIO_PIPE_READER_H_
#define REMOTING_HOST_LINUX_AUDIO_PIPE_READER_H_

#include "base/files/file.h"
#include "base/files/file_path.h"
#include "base/files/file_path_watcher.h"
#include "base/memory/ref_counted.h"
#include "base/memory/ref_counted_memory.h"
#include "base/message_loop/message_loop.h"
#include "base/observer_list_threadsafe.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "remoting/proto/audio.pb.h"

namespace remoting {

struct AudioPipeReaderTraits;

class AudioPipeReader
    : public base::RefCountedThreadSafe<AudioPipeReader, AudioPipeReaderTraits>,
      public base::MessageLoopForIO::Watcher {
 public:
  
  
  static const AudioPacket_SamplingRate kSamplingRate =
      AudioPacket::SAMPLING_RATE_48000;
  static const AudioPacket_BytesPerSample kBytesPerSample =
      AudioPacket::BYTES_PER_SAMPLE_2;
  static const AudioPacket_Channels kChannels = AudioPacket::CHANNELS_STEREO;

  class StreamObserver {
   public:
    virtual void OnDataRead(scoped_refptr<base::RefCountedString> data) = 0;
  };

  
  static scoped_refptr<AudioPipeReader> Create(
      scoped_refptr<base::SingleThreadTaskRunner> task_runner,
      const base::FilePath& pipe_path);

  
  
  
  void AddObserver(StreamObserver* observer);
  void RemoveObserver(StreamObserver* observer);

  
  virtual void OnFileCanReadWithoutBlocking(int fd) OVERRIDE;
  virtual void OnFileCanWriteWithoutBlocking(int fd) OVERRIDE;

 private:
  friend class base::DeleteHelper<AudioPipeReader>;
  friend class base::RefCountedThreadSafe<AudioPipeReader>;
  friend struct AudioPipeReaderTraits;

  AudioPipeReader(scoped_refptr<base::SingleThreadTaskRunner> task_runner,
                  const base::FilePath& pipe_path);
  virtual ~AudioPipeReader();

  void StartOnAudioThread();
  void OnDirectoryChanged(const base::FilePath& path, bool error);
  void TryOpenPipe();
  void StartTimer();
  void DoCapture();
  void WaitForPipeReadable();

  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;
  base::FilePath pipe_path_;

  
  
  base::FilePathWatcher file_watcher_;

  base::File pipe_;
  base::RepeatingTimer<AudioPipeReader> timer_;
  scoped_refptr<ObserverListThreadSafe<StreamObserver> > observers_;

  
  base::TimeTicks started_time_;

  
  
  
  int64 last_capture_position_;

  
  std::string left_over_bytes_;

  base::MessageLoopForIO::FileDescriptorWatcher file_descriptor_watcher_;

  DISALLOW_COPY_AND_ASSIGN(AudioPipeReader);
};

struct AudioPipeReaderTraits {
  static void Destruct(const AudioPipeReader* audio_pipe_reader);
};

}  

#endif  
