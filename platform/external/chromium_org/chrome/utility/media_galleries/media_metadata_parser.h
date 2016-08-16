// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_UTILITY_MEDIA_GALLERIES_MEDIA_METADATA_PARSER_H_
#define CHROME_UTILITY_MEDIA_GALLERIES_MEDIA_METADATA_PARSER_H_

#include <string>
#include <vector>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/common/extensions/api/media_galleries.h"
#include "chrome/common/media_galleries/metadata_types.h"

namespace base {
class Thread;
}

namespace media {
class DataSource;
}

namespace metadata {

class MediaMetadataParser {
 public:
  typedef extensions::api::media_galleries::MediaMetadata MediaMetadata;
  typedef base::Callback<
      void(const MediaMetadata& metadata,
           const std::vector<AttachedImage>& attached_images)>
  MetadataCallback;

  
  
  MediaMetadataParser(media::DataSource* source, const std::string& mime_type,
                      bool get_attached_images);

  ~MediaMetadataParser();

  
  void Start(const MetadataCallback& callback);

 private:
  
  media::DataSource* const source_;

  const std::string mime_type_;

  bool get_attached_images_;

  
  
  
  
  scoped_ptr<base::Thread> media_thread_;

  DISALLOW_COPY_AND_ASSIGN(MediaMetadataParser);
};

}  

#endif  
