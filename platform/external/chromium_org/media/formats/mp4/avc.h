// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_FORMATS_MP4_AVC_H_
#define MEDIA_FORMATS_MP4_AVC_H_

#include <vector>

#include "base/basictypes.h"
#include "media/base/media_export.h"

namespace media {

struct SubsampleEntry;

namespace mp4 {

struct AVCDecoderConfigurationRecord;

class MEDIA_EXPORT AVC {
 public:
  static bool ConvertFrameToAnnexB(int length_size, std::vector<uint8>* buffer);

  
  
  
  
  
  static bool InsertParamSetsAnnexB(
      const AVCDecoderConfigurationRecord& avc_config,
      std::vector<uint8>* buffer,
      std::vector<SubsampleEntry>* subsamples);

  static bool ConvertConfigToAnnexB(
      const AVCDecoderConfigurationRecord& avc_config,
      std::vector<uint8>* buffer,
      std::vector<SubsampleEntry>* subsamples);

  
  
  
  
  
  
  
  static bool IsValidAnnexB(const std::vector<uint8>& buffer,
                            const std::vector<SubsampleEntry>& subsamples);
  static bool IsValidAnnexB(const uint8* buffer, size_t size,
                            const std::vector<SubsampleEntry>& subsamples);
};

}  
}  

#endif  
