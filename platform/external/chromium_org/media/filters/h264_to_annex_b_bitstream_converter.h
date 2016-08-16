// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_FILTERS_H264_TO_ANNEX_B_BITSTREAM_CONVERTER_H_
#define MEDIA_FILTERS_H264_TO_ANNEX_B_BITSTREAM_CONVERTER_H_

#include <vector>

#include "base/basictypes.h"
#include "media/base/media_export.h"

namespace media {

namespace mp4 {
struct AVCDecoderConfigurationRecord;
}

class MEDIA_EXPORT H264ToAnnexBBitstreamConverter {
 public:
  H264ToAnnexBBitstreamConverter();
  ~H264ToAnnexBBitstreamConverter();

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  bool ParseConfiguration(
      const uint8* configuration_record,
      int configuration_record_size,
      mp4::AVCDecoderConfigurationRecord* avc_config);

  
  
  uint32 GetConfigSize(
      const mp4::AVCDecoderConfigurationRecord& avc_config) const;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  uint32 CalculateNeededOutputBufferSize(
      const uint8* input,
      uint32 input_size,
      const mp4::AVCDecoderConfigurationRecord* avc_config) const;

  
  
  
  
  
  
  
  
  
  //     will be written to |output|.
  
  //     Pointer to buffer where the output should be written to.
  
  
  //     bytes written to output after successful call.
  
  
  
  
  
  bool ConvertAVCDecoderConfigToByteStream(
      const mp4::AVCDecoderConfigurationRecord& avc_config,
      uint8* output,
      uint32* output_size);

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  //     Pointer to buffer where the output should be written to.
  
  
  //     bytes written to output after successful call.
  
  
  
  
  
  bool ConvertNalUnitStreamToByteStream(
      const uint8* input,
      uint32 input_size,
      const mp4::AVCDecoderConfigurationRecord* avc_config,
      uint8* output,
      uint32* output_size);

 private:
  
  
  
  
  // written. On a successful write, |*out| is updated to point to the first
  // byte after the data that was written. |*out_size| is updated to reflect
  
  bool WriteParamSet(const std::vector<uint8>& param_set,
                     uint8** out,
                     uint32* out_size) const;

  
  bool configuration_processed_;
  
  bool first_nal_unit_in_access_unit_;
  
  uint8 nal_unit_length_field_width_;

  DISALLOW_COPY_AND_ASSIGN(H264ToAnnexBBitstreamConverter);
};

}  

#endif  
