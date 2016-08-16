// Copyright 2009 Google Inc.
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//     http://www.apache.org/licenses/LICENSE-2.0
// distributed under the License is distributed on an "AS IS" BASIS,
// See the License for the specific language governing permissions and
// limitations under the License.


#ifndef THIRD_PARTY_ANDROID_OPENGL_ETC1_ETC1_H_
#define THIRD_PARTY_ANDROID_OPENGL_ETC1_ETC1_H_


unsigned int etc1_get_encoded_data_size(unsigned int width, unsigned int height);


bool etc1_encode_image(const unsigned char* pIn, unsigned int width, unsigned int height,
         unsigned int pixelSize, unsigned int stride, unsigned char* pOut, unsigned int outWidth,
         unsigned int outHeight);

// pOut - pointer to the image data. Will be written such that

bool etc1_decode_image(const unsigned char* pIn, unsigned char* pOut,
        unsigned int width, unsigned int height,
        unsigned int pixelSize, unsigned int stride);


#define ETC_PKM_HEADER_SIZE 16


void etc1_pkm_format_header(unsigned char* pHeader, unsigned int width, unsigned int height);


bool etc1_pkm_is_valid(const unsigned char* pHeader);


unsigned int etc1_pkm_get_width(const unsigned char* pHeader);


unsigned int etc1_pkm_get_height(const unsigned char* pHeader);

#endif 
