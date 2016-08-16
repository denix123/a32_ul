// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_FORMATS_WEBM_TRACKS_BUILDER_H_
#define MEDIA_FORMATS_WEBM_TRACKS_BUILDER_H_

#include <list>
#include <string>
#include <vector>

#include "base/basictypes.h"

namespace media {

class TracksBuilder {
 public:
  
  
  
  explicit TracksBuilder(bool allow_invalid_values);
  TracksBuilder();  
  ~TracksBuilder();

  
  
  
  
  
  void AddVideoTrack(int track_num,
                     uint64 track_uid,
                     const std::string& codec_id,
                     const std::string& name,
                     const std::string& language,
                     int default_duration,
                     int video_pixel_width,
                     int video_pixel_height);
  void AddAudioTrack(int track_num,
                     uint64 track_uid,
                     const std::string& codec_id,
                     const std::string& name,
                     const std::string& language,
                     int default_duration,
                     int audio_channels,
                     double audio_sampling_frequency);
  void AddTextTrack(int track_num,
                    uint64 track_uid,
                    const std::string& codec_id,
                    const std::string& name,
                    const std::string& language);

  std::vector<uint8> Finish();

 private:
  void AddTrackInternal(int track_num,
                        int track_type,
                        uint64 track_uid,
                        const std::string& codec_id,
                        const std::string& name,
                        const std::string& language,
                        int default_duration,
                        int video_pixel_width,
                        int video_pixel_height,
                        int audio_channels,
                        double audio_sampling_frequency);
  int GetTracksSize() const;
  int GetTracksPayloadSize() const;
  void WriteTracks(uint8* buffer, int buffer_size) const;

  class Track {
   public:
    Track(int track_num,
          int track_type,
          uint64 track_uid,
          const std::string& codec_id,
          const std::string& name,
          const std::string& language,
          int default_duration,
          int video_pixel_width,
          int video_pixel_height,
          int audio_channels,
          double audio_sampling_frequency,
          bool allow_invalid_values);

    int GetSize() const;
    void Write(uint8** buf, int* buf_size) const;
   private:
    int GetPayloadSize() const;
    int GetVideoPayloadSize() const;
    int GetAudioPayloadSize() const;

    int track_num_;
    int track_type_;
    int track_uid_;
    std::string codec_id_;
    std::string name_;
    std::string language_;
    int default_duration_;
    int video_pixel_width_;
    int video_pixel_height_;
    int audio_channels_;
    double audio_sampling_frequency_;
  };

  typedef std::list<Track> TrackList;
  TrackList tracks_;
  bool allow_invalid_values_;

  DISALLOW_COPY_AND_ASSIGN(TracksBuilder);
};

}  

#endif  
