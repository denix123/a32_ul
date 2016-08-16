// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_AUDIO_VIDEO_METADATA_EXTRACTOR_H_
#define MEDIA_BASE_AUDIO_VIDEO_METADATA_EXTRACTOR_H_

#include <map>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "media/base/media_export.h"

struct AVDictionary;

namespace media {

class DataSource;

class MEDIA_EXPORT AudioVideoMetadataExtractor {
 public:
  typedef std::map<std::string, std::string> TagDictionary;

  struct StreamInfo {
    StreamInfo();
    ~StreamInfo();
    std::string type;
    TagDictionary tags;
  };

  typedef std::vector<StreamInfo> StreamInfoVector;

  AudioVideoMetadataExtractor();
  ~AudioVideoMetadataExtractor();

  
  
  bool Extract(DataSource* source, bool extract_attached_pics);

  
  double duration() const;

  
  int width() const;
  int height() const;

  
  int rotation() const;

  
  const std::string& album() const;
  const std::string& artist() const;
  const std::string& comment() const;
  const std::string& copyright() const;
  const std::string& date() const;
  int disc() const;
  const std::string& encoder() const;
  const std::string& encoded_by() const;
  const std::string& genre() const;
  const std::string& language() const;
  const std::string& title() const;
  int track() const;

  
  const StreamInfoVector& stream_infos() const;

  
  
  const std::vector<std::string>& attached_images_bytes() const;

 private:
  void ExtractDictionary(AVDictionary* metadata, TagDictionary* raw_tags);

  bool extracted_;

  int duration_;
  int width_;
  int height_;

  std::string album_;
  std::string artist_;
  std::string comment_;
  std::string copyright_;
  std::string date_;
  int disc_;
  std::string encoder_;
  std::string encoded_by_;
  std::string genre_;
  std::string language_;
  int rotation_;
  std::string title_;
  int track_;

  StreamInfoVector stream_infos_;

  std::vector<std::string> attached_images_bytes_;

  DISALLOW_COPY_AND_ASSIGN(AudioVideoMetadataExtractor);
};

}  

#endif  
