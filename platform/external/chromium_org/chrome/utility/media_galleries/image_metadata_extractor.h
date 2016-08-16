// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_UTILITY_MEDIA_GALLERIES_IMAGE_METADATA_EXTRACTOR_H_
#define CHROME_UTILITY_MEDIA_GALLERIES_IMAGE_METADATA_EXTRACTOR_H_

#include <string>

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/memory/ref_counted.h"

namespace media {
class DataSource;
}

namespace net {
class DrainableIOBuffer;
}

namespace metadata {

class ImageMetadataExtractor {
 public:
  typedef base::Callback<void(bool)> DoneCallback;

  
  static bool InitializeLibrary();
  static bool InitializeLibraryForTesting();

  ImageMetadataExtractor();
  ~ImageMetadataExtractor();

  
  
  void Extract(media::DataSource* source, const DoneCallback& callback);

  
  
  int width() const;
  int height() const;

  
  int rotation() const;

  
  double x_resolution() const;
  double y_resolution() const;

  
  const std::string& date() const;

  const std::string& camera_make() const;
  const std::string& camera_model() const;
  double exposure_time_sec() const;
  bool flash_fired() const;
  double f_number() const;
  double focal_length_mm() const;
  int iso_equivalent() const;

 private:
  
  void FinishExtraction(const DoneCallback& callback,
                        const scoped_refptr<net::DrainableIOBuffer>& buffer);

  bool extracted_;

  int width_;
  int height_;

  int rotation_;

  double x_resolution_;
  double y_resolution_;

  std::string date_;

  std::string camera_make_;
  std::string camera_model_;
  double exposure_time_sec_;
  bool flash_fired_;
  double f_number_;
  double focal_length_mm_;
  int iso_equivalent_;

  DISALLOW_COPY_AND_ASSIGN(ImageMetadataExtractor);
};

}  

#endif  
