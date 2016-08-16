// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef NET_SPDY_SPDY_PROTOCOL_H_
#define NET_SPDY_SPDY_PROTOCOL_H_

#include <map>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string_piece.h"
#include "base/sys_byteorder.h"
#include "net/base/net_export.h"
#include "net/spdy/spdy_bitmasks.h"

namespace net {

enum SpdyMajorVersion {
  SPDY2 = 2,
  SPDY_MIN_VERSION = SPDY2,
  SPDY3 = 3,
  SPDY4 = 4,
  SPDY5 = 5,
  SPDY_MAX_VERSION = SPDY5
};

typedef uint32 SpdyStreamId;

const SpdyStreamId kSessionFlowControlStreamId = 0;

const int32 kSpdyStreamInitialWindowSize = 64 * 1024;  

const int32 kSpdyMaxControlFrameSize = (1 << 24) - 1;

const int32 kControlFrameSizeLimit = 1 << 14;

const int32 kSpdySessionInitialWindowSize = 64 * 1024;  

const int32 kSpdyMaximumWindowSize = 0x7FFFFFFF;  

const int32 kPaddingSizePerFrame = 256;

const char kV2Dictionary[] =
  "optionsgetheadpostputdeletetraceacceptaccept-charsetaccept-encodingaccept-"
  "languageauthorizationexpectfromhostif-modified-sinceif-matchif-none-matchi"
  "f-rangeif-unmodifiedsincemax-forwardsproxy-authorizationrangerefererteuser"
  "-agent10010120020120220320420520630030130230330430530630740040140240340440"
  "5406407408409410411412413414415416417500501502503504505accept-rangesageeta"
  "glocationproxy-authenticatepublicretry-afterservervarywarningwww-authentic"
  "ateallowcontent-basecontent-encodingcache-controlconnectiondatetrailertran"
  "sfer-encodingupgradeviawarningcontent-languagecontent-lengthcontent-locati"
  "oncontent-md5content-rangecontent-typeetagexpireslast-modifiedset-cookieMo"
  "ndayTuesdayWednesdayThursdayFridaySaturdaySundayJanFebMarAprMayJunJulAugSe"
  "pOctNovDecchunkedtext/htmlimage/pngimage/jpgimage/gifapplication/xmlapplic"
  "ation/xhtmltext/plainpublicmax-agecharset=iso-8859-1utf-8gzipdeflateHTTP/1"
  ".1statusversionurl";
const int kV2DictionarySize = arraysize(kV2Dictionary);

const char kV3Dictionary[] = {
  0x00, 0x00, 0x00, 0x07, 0x6f, 0x70, 0x74, 0x69,  
  0x6f, 0x6e, 0x73, 0x00, 0x00, 0x00, 0x04, 0x68,  
  0x65, 0x61, 0x64, 0x00, 0x00, 0x00, 0x04, 0x70,  
  0x6f, 0x73, 0x74, 0x00, 0x00, 0x00, 0x03, 0x70,  
  0x75, 0x74, 0x00, 0x00, 0x00, 0x06, 0x64, 0x65,  
  0x6c, 0x65, 0x74, 0x65, 0x00, 0x00, 0x00, 0x05,  
  0x74, 0x72, 0x61, 0x63, 0x65, 0x00, 0x00, 0x00,  
  0x06, 0x61, 0x63, 0x63, 0x65, 0x70, 0x74, 0x00,  
  0x00, 0x00, 0x0e, 0x61, 0x63, 0x63, 0x65, 0x70,  
  0x74, 0x2d, 0x63, 0x68, 0x61, 0x72, 0x73, 0x65,  
  0x74, 0x00, 0x00, 0x00, 0x0f, 0x61, 0x63, 0x63,  
  0x65, 0x70, 0x74, 0x2d, 0x65, 0x6e, 0x63, 0x6f,  
  0x64, 0x69, 0x6e, 0x67, 0x00, 0x00, 0x00, 0x0f,  
  0x61, 0x63, 0x63, 0x65, 0x70, 0x74, 0x2d, 0x6c,  
  0x61, 0x6e, 0x67, 0x75, 0x61, 0x67, 0x65, 0x00,  
  0x00, 0x00, 0x0d, 0x61, 0x63, 0x63, 0x65, 0x70,  
  0x74, 0x2d, 0x72, 0x61, 0x6e, 0x67, 0x65, 0x73,  
  0x00, 0x00, 0x00, 0x03, 0x61, 0x67, 0x65, 0x00,  
  0x00, 0x00, 0x05, 0x61, 0x6c, 0x6c, 0x6f, 0x77,  
  0x00, 0x00, 0x00, 0x0d, 0x61, 0x75, 0x74, 0x68,  
  0x6f, 0x72, 0x69, 0x7a, 0x61, 0x74, 0x69, 0x6f,  
  0x6e, 0x00, 0x00, 0x00, 0x0d, 0x63, 0x61, 0x63,  
  0x68, 0x65, 0x2d, 0x63, 0x6f, 0x6e, 0x74, 0x72,  
  0x6f, 0x6c, 0x00, 0x00, 0x00, 0x0a, 0x63, 0x6f,  
  0x6e, 0x6e, 0x65, 0x63, 0x74, 0x69, 0x6f, 0x6e,  
  0x00, 0x00, 0x00, 0x0c, 0x63, 0x6f, 0x6e, 0x74,  
  0x65, 0x6e, 0x74, 0x2d, 0x62, 0x61, 0x73, 0x65,  
  0x00, 0x00, 0x00, 0x10, 0x63, 0x6f, 0x6e, 0x74,  
  0x65, 0x6e, 0x74, 0x2d, 0x65, 0x6e, 0x63, 0x6f,  
  0x64, 0x69, 0x6e, 0x67, 0x00, 0x00, 0x00, 0x10,  
  0x63, 0x6f, 0x6e, 0x74, 0x65, 0x6e, 0x74, 0x2d,  
  0x6c, 0x61, 0x6e, 0x67, 0x75, 0x61, 0x67, 0x65,  
  0x00, 0x00, 0x00, 0x0e, 0x63, 0x6f, 0x6e, 0x74,  
  0x65, 0x6e, 0x74, 0x2d, 0x6c, 0x65, 0x6e, 0x67,  
  0x74, 0x68, 0x00, 0x00, 0x00, 0x10, 0x63, 0x6f,  
  0x6e, 0x74, 0x65, 0x6e, 0x74, 0x2d, 0x6c, 0x6f,  
  0x63, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x00, 0x00,  
  0x00, 0x0b, 0x63, 0x6f, 0x6e, 0x74, 0x65, 0x6e,  
  0x74, 0x2d, 0x6d, 0x64, 0x35, 0x00, 0x00, 0x00,  
  0x0d, 0x63, 0x6f, 0x6e, 0x74, 0x65, 0x6e, 0x74,  
  0x2d, 0x72, 0x61, 0x6e, 0x67, 0x65, 0x00, 0x00,  
  0x00, 0x0c, 0x63, 0x6f, 0x6e, 0x74, 0x65, 0x6e,  
  0x74, 0x2d, 0x74, 0x79, 0x70, 0x65, 0x00, 0x00,  
  0x00, 0x04, 0x64, 0x61, 0x74, 0x65, 0x00, 0x00,  
  0x00, 0x04, 0x65, 0x74, 0x61, 0x67, 0x00, 0x00,  
  0x00, 0x06, 0x65, 0x78, 0x70, 0x65, 0x63, 0x74,  
  0x00, 0x00, 0x00, 0x07, 0x65, 0x78, 0x70, 0x69,  
  0x72, 0x65, 0x73, 0x00, 0x00, 0x00, 0x04, 0x66,  
  0x72, 0x6f, 0x6d, 0x00, 0x00, 0x00, 0x04, 0x68,  
  0x6f, 0x73, 0x74, 0x00, 0x00, 0x00, 0x08, 0x69,  
  0x66, 0x2d, 0x6d, 0x61, 0x74, 0x63, 0x68, 0x00,  
  0x00, 0x00, 0x11, 0x69, 0x66, 0x2d, 0x6d, 0x6f,  
  0x64, 0x69, 0x66, 0x69, 0x65, 0x64, 0x2d, 0x73,  
  0x69, 0x6e, 0x63, 0x65, 0x00, 0x00, 0x00, 0x0d,  
  0x69, 0x66, 0x2d, 0x6e, 0x6f, 0x6e, 0x65, 0x2d,  
  0x6d, 0x61, 0x74, 0x63, 0x68, 0x00, 0x00, 0x00,  
  0x08, 0x69, 0x66, 0x2d, 0x72, 0x61, 0x6e, 0x67,  
  0x65, 0x00, 0x00, 0x00, 0x13, 0x69, 0x66, 0x2d,  
  0x75, 0x6e, 0x6d, 0x6f, 0x64, 0x69, 0x66, 0x69,  
  0x65, 0x64, 0x2d, 0x73, 0x69, 0x6e, 0x63, 0x65,  
  0x00, 0x00, 0x00, 0x0d, 0x6c, 0x61, 0x73, 0x74,  
  0x2d, 0x6d, 0x6f, 0x64, 0x69, 0x66, 0x69, 0x65,  
  0x64, 0x00, 0x00, 0x00, 0x08, 0x6c, 0x6f, 0x63,  
  0x61, 0x74, 0x69, 0x6f, 0x6e, 0x00, 0x00, 0x00,  
  0x0c, 0x6d, 0x61, 0x78, 0x2d, 0x66, 0x6f, 0x72,  
  0x77, 0x61, 0x72, 0x64, 0x73, 0x00, 0x00, 0x00,  
  0x06, 0x70, 0x72, 0x61, 0x67, 0x6d, 0x61, 0x00,  
  0x00, 0x00, 0x12, 0x70, 0x72, 0x6f, 0x78, 0x79,  
  0x2d, 0x61, 0x75, 0x74, 0x68, 0x65, 0x6e, 0x74,  
  0x69, 0x63, 0x61, 0x74, 0x65, 0x00, 0x00, 0x00,  
  0x13, 0x70, 0x72, 0x6f, 0x78, 0x79, 0x2d, 0x61,  
  0x75, 0x74, 0x68, 0x6f, 0x72, 0x69, 0x7a, 0x61,  
  0x74, 0x69, 0x6f, 0x6e, 0x00, 0x00, 0x00, 0x05,  
  0x72, 0x61, 0x6e, 0x67, 0x65, 0x00, 0x00, 0x00,  
  0x07, 0x72, 0x65, 0x66, 0x65, 0x72, 0x65, 0x72,  
  0x00, 0x00, 0x00, 0x0b, 0x72, 0x65, 0x74, 0x72,  
  0x79, 0x2d, 0x61, 0x66, 0x74, 0x65, 0x72, 0x00,  
  0x00, 0x00, 0x06, 0x73, 0x65, 0x72, 0x76, 0x65,  
  0x72, 0x00, 0x00, 0x00, 0x02, 0x74, 0x65, 0x00,  
  0x00, 0x00, 0x07, 0x74, 0x72, 0x61, 0x69, 0x6c,  
  0x65, 0x72, 0x00, 0x00, 0x00, 0x11, 0x74, 0x72,  
  0x61, 0x6e, 0x73, 0x66, 0x65, 0x72, 0x2d, 0x65,  
  0x6e, 0x63, 0x6f, 0x64, 0x69, 0x6e, 0x67, 0x00,  
  0x00, 0x00, 0x07, 0x75, 0x70, 0x67, 0x72, 0x61,  
  0x64, 0x65, 0x00, 0x00, 0x00, 0x0a, 0x75, 0x73,  
  0x65, 0x72, 0x2d, 0x61, 0x67, 0x65, 0x6e, 0x74,  
  0x00, 0x00, 0x00, 0x04, 0x76, 0x61, 0x72, 0x79,  
  0x00, 0x00, 0x00, 0x03, 0x76, 0x69, 0x61, 0x00,  
  0x00, 0x00, 0x07, 0x77, 0x61, 0x72, 0x6e, 0x69,  
  0x6e, 0x67, 0x00, 0x00, 0x00, 0x10, 0x77, 0x77,  
  0x77, 0x2d, 0x61, 0x75, 0x74, 0x68, 0x65, 0x6e,  
  0x74, 0x69, 0x63, 0x61, 0x74, 0x65, 0x00, 0x00,  
  0x00, 0x06, 0x6d, 0x65, 0x74, 0x68, 0x6f, 0x64,  
  0x00, 0x00, 0x00, 0x03, 0x67, 0x65, 0x74, 0x00,  
  0x00, 0x00, 0x06, 0x73, 0x74, 0x61, 0x74, 0x75,  
  0x73, 0x00, 0x00, 0x00, 0x06, 0x32, 0x30, 0x30,  
  0x20, 0x4f, 0x4b, 0x00, 0x00, 0x00, 0x07, 0x76,  
  0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x00, 0x00,  
  0x00, 0x08, 0x48, 0x54, 0x54, 0x50, 0x2f, 0x31,  
  0x2e, 0x31, 0x00, 0x00, 0x00, 0x03, 0x75, 0x72,  
  0x6c, 0x00, 0x00, 0x00, 0x06, 0x70, 0x75, 0x62,  
  0x6c, 0x69, 0x63, 0x00, 0x00, 0x00, 0x0a, 0x73,  
  0x65, 0x74, 0x2d, 0x63, 0x6f, 0x6f, 0x6b, 0x69,  
  0x65, 0x00, 0x00, 0x00, 0x0a, 0x6b, 0x65, 0x65,  
  0x70, 0x2d, 0x61, 0x6c, 0x69, 0x76, 0x65, 0x00,  
  0x00, 0x00, 0x06, 0x6f, 0x72, 0x69, 0x67, 0x69,  
  0x6e, 0x31, 0x30, 0x30, 0x31, 0x30, 0x31, 0x32,  
  0x30, 0x31, 0x32, 0x30, 0x32, 0x32, 0x30, 0x35,  
  0x32, 0x30, 0x36, 0x33, 0x30, 0x30, 0x33, 0x30,  
  0x32, 0x33, 0x30, 0x33, 0x33, 0x30, 0x34, 0x33,  
  0x30, 0x35, 0x33, 0x30, 0x36, 0x33, 0x30, 0x37,  
  0x34, 0x30, 0x32, 0x34, 0x30, 0x35, 0x34, 0x30,  
  0x36, 0x34, 0x30, 0x37, 0x34, 0x30, 0x38, 0x34,  
  0x30, 0x39, 0x34, 0x31, 0x30, 0x34, 0x31, 0x31,  
  0x34, 0x31, 0x32, 0x34, 0x31, 0x33, 0x34, 0x31,  
  0x34, 0x34, 0x31, 0x35, 0x34, 0x31, 0x36, 0x34,  
  0x31, 0x37, 0x35, 0x30, 0x32, 0x35, 0x30, 0x34,  
  0x35, 0x30, 0x35, 0x32, 0x30, 0x33, 0x20, 0x4e,  
  0x6f, 0x6e, 0x2d, 0x41, 0x75, 0x74, 0x68, 0x6f,  
  0x72, 0x69, 0x74, 0x61, 0x74, 0x69, 0x76, 0x65,  
  0x20, 0x49, 0x6e, 0x66, 0x6f, 0x72, 0x6d, 0x61,  
  0x74, 0x69, 0x6f, 0x6e, 0x32, 0x30, 0x34, 0x20,  
  0x4e, 0x6f, 0x20, 0x43, 0x6f, 0x6e, 0x74, 0x65,  
  0x6e, 0x74, 0x33, 0x30, 0x31, 0x20, 0x4d, 0x6f,  
  0x76, 0x65, 0x64, 0x20, 0x50, 0x65, 0x72, 0x6d,  
  0x61, 0x6e, 0x65, 0x6e, 0x74, 0x6c, 0x79, 0x34,  
  0x30, 0x30, 0x20, 0x42, 0x61, 0x64, 0x20, 0x52,  
  0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x34, 0x30,  
  0x31, 0x20, 0x55, 0x6e, 0x61, 0x75, 0x74, 0x68,  
  0x6f, 0x72, 0x69, 0x7a, 0x65, 0x64, 0x34, 0x30,  
  0x33, 0x20, 0x46, 0x6f, 0x72, 0x62, 0x69, 0x64,  
  0x64, 0x65, 0x6e, 0x34, 0x30, 0x34, 0x20, 0x4e,  
  0x6f, 0x74, 0x20, 0x46, 0x6f, 0x75, 0x6e, 0x64,  
  0x35, 0x30, 0x30, 0x20, 0x49, 0x6e, 0x74, 0x65,  
  0x72, 0x6e, 0x61, 0x6c, 0x20, 0x53, 0x65, 0x72,  
  0x76, 0x65, 0x72, 0x20, 0x45, 0x72, 0x72, 0x6f,  
  0x72, 0x35, 0x30, 0x31, 0x20, 0x4e, 0x6f, 0x74,  
  0x20, 0x49, 0x6d, 0x70, 0x6c, 0x65, 0x6d, 0x65,  
  0x6e, 0x74, 0x65, 0x64, 0x35, 0x30, 0x33, 0x20,  
  0x53, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x20,  
  0x55, 0x6e, 0x61, 0x76, 0x61, 0x69, 0x6c, 0x61,  
  0x62, 0x6c, 0x65, 0x4a, 0x61, 0x6e, 0x20, 0x46,  
  0x65, 0x62, 0x20, 0x4d, 0x61, 0x72, 0x20, 0x41,  
  0x70, 0x72, 0x20, 0x4d, 0x61, 0x79, 0x20, 0x4a,  
  0x75, 0x6e, 0x20, 0x4a, 0x75, 0x6c, 0x20, 0x41,  
  0x75, 0x67, 0x20, 0x53, 0x65, 0x70, 0x74, 0x20,  
  0x4f, 0x63, 0x74, 0x20, 0x4e, 0x6f, 0x76, 0x20,  
  0x44, 0x65, 0x63, 0x20, 0x30, 0x30, 0x3a, 0x30,  
  0x30, 0x3a, 0x30, 0x30, 0x20, 0x4d, 0x6f, 0x6e,  
  0x2c, 0x20, 0x54, 0x75, 0x65, 0x2c, 0x20, 0x57,  
  0x65, 0x64, 0x2c, 0x20, 0x54, 0x68, 0x75, 0x2c,  
  0x20, 0x46, 0x72, 0x69, 0x2c, 0x20, 0x53, 0x61,  
  0x74, 0x2c, 0x20, 0x53, 0x75, 0x6e, 0x2c, 0x20,  
  0x47, 0x4d, 0x54, 0x63, 0x68, 0x75, 0x6e, 0x6b,  
  0x65, 0x64, 0x2c, 0x74, 0x65, 0x78, 0x74, 0x2f,  
  0x68, 0x74, 0x6d, 0x6c, 0x2c, 0x69, 0x6d, 0x61,  
  0x67, 0x65, 0x2f, 0x70, 0x6e, 0x67, 0x2c, 0x69,  
  0x6d, 0x61, 0x67, 0x65, 0x2f, 0x6a, 0x70, 0x67,  
  0x2c, 0x69, 0x6d, 0x61, 0x67, 0x65, 0x2f, 0x67,  
  0x69, 0x66, 0x2c, 0x61, 0x70, 0x70, 0x6c, 0x69,  
  0x63, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x2f, 0x78,  
  0x6d, 0x6c, 0x2c, 0x61, 0x70, 0x70, 0x6c, 0x69,  
  0x63, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x2f, 0x78,  
  0x68, 0x74, 0x6d, 0x6c, 0x2b, 0x78, 0x6d, 0x6c,  
  0x2c, 0x74, 0x65, 0x78, 0x74, 0x2f, 0x70, 0x6c,  
  0x61, 0x69, 0x6e, 0x2c, 0x74, 0x65, 0x78, 0x74,  
  0x2f, 0x6a, 0x61, 0x76, 0x61, 0x73, 0x63, 0x72,  
  0x69, 0x70, 0x74, 0x2c, 0x70, 0x75, 0x62, 0x6c,  
  0x69, 0x63, 0x70, 0x72, 0x69, 0x76, 0x61, 0x74,  
  0x65, 0x6d, 0x61, 0x78, 0x2d, 0x61, 0x67, 0x65,  
  0x3d, 0x67, 0x7a, 0x69, 0x70, 0x2c, 0x64, 0x65,  
  0x66, 0x6c, 0x61, 0x74, 0x65, 0x2c, 0x73, 0x64,  
  0x63, 0x68, 0x63, 0x68, 0x61, 0x72, 0x73, 0x65,  
  0x74, 0x3d, 0x75, 0x74, 0x66, 0x2d, 0x38, 0x63,  
  0x68, 0x61, 0x72, 0x73, 0x65, 0x74, 0x3d, 0x69,  
  0x73, 0x6f, 0x2d, 0x38, 0x38, 0x35, 0x39, 0x2d,  
  0x31, 0x2c, 0x75, 0x74, 0x66, 0x2d, 0x2c, 0x2a,  
  0x2c, 0x65, 0x6e, 0x71, 0x3d, 0x30, 0x2e         
};
const int kV3DictionarySize = arraysize(kV3Dictionary);

const char kHttp2ConnectionHeaderPrefix[] = {
  0x50, 0x52, 0x49, 0x20, 0x2a, 0x20, 0x48, 0x54,  
  0x54, 0x50, 0x2f, 0x32, 0x2e, 0x30, 0x0d, 0x0a,  
  0x0d, 0x0a, 0x53, 0x4d, 0x0d, 0x0a, 0x0d, 0x0a   
};
const int kHttp2ConnectionHeaderPrefixSize =
    arraysize(kHttp2ConnectionHeaderPrefix);

const char kHttp2VersionString[] = "HTTP/1.1";

enum SpdyFrameType {
  DATA,
  SYN_STREAM,
  SYN_REPLY,
  RST_STREAM,
  SETTINGS,
  PING,
  GOAWAY,
  HEADERS,
  WINDOW_UPDATE,
  CREDENTIAL = 10,  
  PUSH_PROMISE,
  CONTINUATION,
  PRIORITY,
  
  BLOCKED,
  ALTSVC,
};

enum SpdyDataFlags {
  DATA_FLAG_NONE = 0x00,
  DATA_FLAG_FIN = 0x01,
  DATA_FLAG_END_SEGMENT = 0x02,
  DATA_FLAG_PADDED = 0x08,
  DATA_FLAG_COMPRESSED = 0x20,
};

enum SpdyControlFlags {
  CONTROL_FLAG_NONE = 0x00,
  CONTROL_FLAG_FIN = 0x01,
  CONTROL_FLAG_UNIDIRECTIONAL = 0x02,
};

enum SpdyPingFlags {
  PING_FLAG_ACK = 0x01,
};

enum SpdyHeadersFlags {
  HEADERS_FLAG_END_SEGMENT = 0x02,
  HEADERS_FLAG_END_HEADERS = 0x04,
  HEADERS_FLAG_PADDED = 0x08,
  HEADERS_FLAG_PRIORITY = 0x20,
};

enum SpdyPushPromiseFlags {
  PUSH_PROMISE_FLAG_END_PUSH_PROMISE = 0x04,
  PUSH_PROMISE_FLAG_PADDED = 0x08,
};

enum SpdySettingsControlFlags {
  SETTINGS_FLAG_CLEAR_PREVIOUSLY_PERSISTED_SETTINGS = 0x01,
};

enum Http2SettingsControlFlags {
  SETTINGS_FLAG_ACK = 0x01,
};

enum SpdySettingsFlags {
  SETTINGS_FLAG_NONE = 0x00,
  SETTINGS_FLAG_PLEASE_PERSIST = 0x01,
  SETTINGS_FLAG_PERSISTED = 0x02,
};

enum SpdySettingsIds {
  SETTINGS_UPLOAD_BANDWIDTH = 0x1,
  SETTINGS_DOWNLOAD_BANDWIDTH = 0x2,
  
  SETTINGS_ROUND_TRIP_TIME = 0x3,
  
  SETTINGS_MAX_CONCURRENT_STREAMS = 0x4,
  
  SETTINGS_CURRENT_CWND = 0x5,
  
  SETTINGS_DOWNLOAD_RETRANS_RATE = 0x6,
  
  SETTINGS_INITIAL_WINDOW_SIZE = 0x7,
  
  SETTINGS_HEADER_TABLE_SIZE = 0x8,
  
  SETTINGS_ENABLE_PUSH = 0x9,
  
  SETTINGS_MAX_FRAME_SIZE = 0xa,
  
  SETTINGS_MAX_HEADER_LIST_SIZE = 0xb,
};

enum SpdyRstStreamStatus {
  RST_STREAM_INVALID = 0,
  RST_STREAM_PROTOCOL_ERROR = 1,
  RST_STREAM_INVALID_STREAM = 2,
  RST_STREAM_STREAM_CLOSED = 2,  
  RST_STREAM_REFUSED_STREAM = 3,
  RST_STREAM_UNSUPPORTED_VERSION = 4,
  RST_STREAM_CANCEL = 5,
  RST_STREAM_INTERNAL_ERROR = 6,
  RST_STREAM_FLOW_CONTROL_ERROR = 7,
  RST_STREAM_STREAM_IN_USE = 8,
  RST_STREAM_STREAM_ALREADY_CLOSED = 9,
  RST_STREAM_INVALID_CREDENTIALS = 10,
  
  
  
  RST_STREAM_FRAME_TOO_LARGE = 11,
  RST_STREAM_FRAME_SIZE_ERROR = 11,
  RST_STREAM_SETTINGS_TIMEOUT = 12,
  RST_STREAM_CONNECT_ERROR = 13,
  RST_STREAM_ENHANCE_YOUR_CALM = 14,
  RST_STREAM_NUM_STATUS_CODES = 15
};

enum SpdyGoAwayStatus {
  GOAWAY_OK = 0,
  GOAWAY_NO_ERROR = GOAWAY_OK,
  GOAWAY_PROTOCOL_ERROR = 1,
  GOAWAY_INTERNAL_ERROR = 2,
  GOAWAY_FLOW_CONTROL_ERROR = 3,
  GOAWAY_SETTINGS_TIMEOUT = 4,
  GOAWAY_STREAM_CLOSED = 5,
  GOAWAY_FRAME_SIZE_ERROR = 6,
  GOAWAY_REFUSED_STREAM = 7,
  GOAWAY_CANCEL = 8,
  GOAWAY_COMPRESSION_ERROR = 9,
  GOAWAY_CONNECT_ERROR = 10,
  GOAWAY_ENHANCE_YOUR_CALM = 11,
  GOAWAY_INADEQUATE_SECURITY = 12
};

typedef uint8 SpdyPriority;

typedef std::map<std::string, std::string> SpdyNameValueBlock;

typedef uint64 SpdyPingId;

typedef std::string SpdyProtocolId;

class NET_EXPORT_PRIVATE SpdyConstants {
 public:
  
  
  static bool IsValidFrameType(SpdyMajorVersion version, int frame_type_field);

  
  
  
  
  static SpdyFrameType ParseFrameType(SpdyMajorVersion version,
                                      int frame_type_field);

  
  
  
  static int SerializeFrameType(SpdyMajorVersion version,
                                SpdyFrameType frame_type);

  
  
  static int DataFrameType(SpdyMajorVersion version);

  
  
  static bool IsValidSettingId(SpdyMajorVersion version, int setting_id_field);

  
  
  
  
  static SpdySettingsIds ParseSettingId(SpdyMajorVersion version,
                                        int setting_id_field);

  
  
  
  static int SerializeSettingId(SpdyMajorVersion version, SpdySettingsIds id);

  
  
  static bool IsValidRstStreamStatus(SpdyMajorVersion version,
                                     int rst_stream_status_field);

  
  
  
  
  
  static SpdyRstStreamStatus ParseRstStreamStatus(SpdyMajorVersion version,
                                                  int rst_stream_status_field);

  
  
  
  
  static int SerializeRstStreamStatus(SpdyMajorVersion version,
                                      SpdyRstStreamStatus rst_stream_status);

  
  
  static bool IsValidGoAwayStatus(SpdyMajorVersion version,
                                  int goaway_status_field);

  
  
  
  
  static SpdyGoAwayStatus ParseGoAwayStatus(SpdyMajorVersion version,
                                            int goaway_status_field);

  
  
  
  static int SerializeGoAwayStatus(SpdyMajorVersion version,
                                   SpdyGoAwayStatus status);

  
  
  
  static size_t GetDataFrameMinimumSize(SpdyMajorVersion version);

  
  static size_t GetControlFrameHeaderSize(SpdyMajorVersion version);

  static size_t GetPrefixLength(SpdyFrameType type, SpdyMajorVersion version);

  static size_t GetFrameMaximumSize(SpdyMajorVersion version);

  
  
  static size_t GetSizeOfSizeField(SpdyMajorVersion version);

  
  static size_t GetSettingSize(SpdyMajorVersion version);

  static SpdyMajorVersion ParseMajorVersion(int version_number);

  static int SerializeMajorVersion(SpdyMajorVersion version);

  static std::string GetVersionString(SpdyMajorVersion version);
};

class SpdyFrame;
typedef SpdyFrame SpdySerializedFrame;

class SpdyFrameVisitor;

class NET_EXPORT_PRIVATE SpdyFrameIR {
 public:
  virtual ~SpdyFrameIR() {}

  virtual void Visit(SpdyFrameVisitor* visitor) const = 0;

 protected:
  SpdyFrameIR() {}

 private:
  DISALLOW_COPY_AND_ASSIGN(SpdyFrameIR);
};

class NET_EXPORT_PRIVATE SpdyFrameWithStreamIdIR : public SpdyFrameIR {
 public:
  virtual ~SpdyFrameWithStreamIdIR() {}
  SpdyStreamId stream_id() const { return stream_id_; }
  void set_stream_id(SpdyStreamId stream_id) {
    DCHECK_EQ(0u, stream_id & ~kStreamIdMask);
    stream_id_ = stream_id;
  }

 protected:
  explicit SpdyFrameWithStreamIdIR(SpdyStreamId stream_id) {
    set_stream_id(stream_id);
  }

 private:
  SpdyStreamId stream_id_;

  DISALLOW_COPY_AND_ASSIGN(SpdyFrameWithStreamIdIR);
};

class NET_EXPORT_PRIVATE SpdyFrameWithFinIR : public SpdyFrameWithStreamIdIR {
 public:
  virtual ~SpdyFrameWithFinIR() {}
  bool fin() const { return fin_; }
  void set_fin(bool fin) { fin_ = fin; }

 protected:
  explicit SpdyFrameWithFinIR(SpdyStreamId stream_id)
      : SpdyFrameWithStreamIdIR(stream_id),
        fin_(false) {}

 private:
  bool fin_;

  DISALLOW_COPY_AND_ASSIGN(SpdyFrameWithFinIR);
};

class NET_EXPORT_PRIVATE SpdyFrameWithNameValueBlockIR
    : public NON_EXPORTED_BASE(SpdyFrameWithFinIR) {
 public:
  const SpdyNameValueBlock& name_value_block() const {
    return name_value_block_;
  }
  void set_name_value_block(const SpdyNameValueBlock& name_value_block) {
    
    name_value_block_ = name_value_block;
  }
  void SetHeader(const base::StringPiece& name,
                 const base::StringPiece& value) {
    name_value_block_[name.as_string()] = value.as_string();
  }
  SpdyNameValueBlock* mutable_name_value_block() {
    return &name_value_block_;
  }

 protected:
  explicit SpdyFrameWithNameValueBlockIR(SpdyStreamId stream_id);
  virtual ~SpdyFrameWithNameValueBlockIR();

 private:
  SpdyNameValueBlock name_value_block_;

  DISALLOW_COPY_AND_ASSIGN(SpdyFrameWithNameValueBlockIR);
};

class NET_EXPORT_PRIVATE SpdyDataIR
    : public NON_EXPORTED_BASE(SpdyFrameWithFinIR) {
 public:
  
  SpdyDataIR(SpdyStreamId stream_id, const base::StringPiece& data);

  
  explicit SpdyDataIR(SpdyStreamId stream_id);

  virtual ~SpdyDataIR();

  base::StringPiece data() const { return data_; }

  bool padded() const { return padded_; }

  int padding_payload_len() const { return padding_payload_len_; }

  void set_padding_len(int padding_len) {
    DCHECK_GT(padding_len, 0);
    DCHECK_LE(padding_len, kPaddingSizePerFrame);
    padded_ = true;
    
    padding_payload_len_ = padding_len - 1;
  }

  
  void SetDataDeep(const base::StringPiece& data) {
    data_store_.reset(new std::string(data.data(), data.length()));
    data_ = *(data_store_.get());
  }

  
  void SetDataShallow(const base::StringPiece& data) {
    data_store_.reset();
    data_ = data;
  }

  virtual void Visit(SpdyFrameVisitor* visitor) const OVERRIDE;

 private:
  
  scoped_ptr<std::string> data_store_;
  base::StringPiece data_;

  bool padded_;
  
  int padding_payload_len_;

  DISALLOW_COPY_AND_ASSIGN(SpdyDataIR);
};

class NET_EXPORT_PRIVATE SpdySynStreamIR
    : public SpdyFrameWithNameValueBlockIR {
 public:
  explicit SpdySynStreamIR(SpdyStreamId stream_id)
      : SpdyFrameWithNameValueBlockIR(stream_id),
        associated_to_stream_id_(0),
        priority_(0),
        unidirectional_(false) {}
  SpdyStreamId associated_to_stream_id() const {
    return associated_to_stream_id_;
  }
  void set_associated_to_stream_id(SpdyStreamId stream_id) {
    associated_to_stream_id_ = stream_id;
  }
  SpdyPriority priority() const { return priority_; }
  void set_priority(SpdyPriority priority) { priority_ = priority; }
  bool unidirectional() const { return unidirectional_; }
  void set_unidirectional(bool unidirectional) {
    unidirectional_ = unidirectional;
  }

  virtual void Visit(SpdyFrameVisitor* visitor) const OVERRIDE;

 private:
  SpdyStreamId associated_to_stream_id_;
  SpdyPriority priority_;
  bool unidirectional_;

  DISALLOW_COPY_AND_ASSIGN(SpdySynStreamIR);
};

class NET_EXPORT_PRIVATE SpdySynReplyIR : public SpdyFrameWithNameValueBlockIR {
 public:
  explicit SpdySynReplyIR(SpdyStreamId stream_id)
      : SpdyFrameWithNameValueBlockIR(stream_id) {}

  virtual void Visit(SpdyFrameVisitor* visitor) const OVERRIDE;

 private:
  DISALLOW_COPY_AND_ASSIGN(SpdySynReplyIR);
};

class NET_EXPORT_PRIVATE SpdyRstStreamIR : public SpdyFrameWithStreamIdIR {
 public:
  SpdyRstStreamIR(SpdyStreamId stream_id, SpdyRstStreamStatus status,
                  base::StringPiece description);

  virtual ~SpdyRstStreamIR();

  SpdyRstStreamStatus status() const {
    return status_;
  }
  void set_status(SpdyRstStreamStatus status) {
    status_ = status;
  }

  base::StringPiece description() const { return description_; }

  void set_description(base::StringPiece description) {
    description_ = description;
  }

  virtual void Visit(SpdyFrameVisitor* visitor) const OVERRIDE;

 private:
  SpdyRstStreamStatus status_;
  base::StringPiece description_;

  DISALLOW_COPY_AND_ASSIGN(SpdyRstStreamIR);
};

class NET_EXPORT_PRIVATE SpdySettingsIR : public SpdyFrameIR {
 public:
  
  struct Value {
    Value() : persist_value(false),
              persisted(false),
              value(0) {}
    bool persist_value;
    bool persisted;
    int32 value;
  };
  typedef std::map<SpdySettingsIds, Value> ValueMap;

  SpdySettingsIR();

  virtual ~SpdySettingsIR();

  
  const ValueMap& values() const { return values_; }
  void AddSetting(SpdySettingsIds id,
                  bool persist_value,
                  bool persisted,
                  int32 value) {
    values_[id].persist_value = persist_value;
    values_[id].persisted = persisted;
    values_[id].value = value;
  }

  bool clear_settings() const { return clear_settings_; }
  void set_clear_settings(bool clear_settings) {
    clear_settings_ = clear_settings;
  }
  bool is_ack() const { return is_ack_; }
  void set_is_ack(bool is_ack) {
    is_ack_ = is_ack;
  }

  virtual void Visit(SpdyFrameVisitor* visitor) const OVERRIDE;

 private:
  ValueMap values_;
  bool clear_settings_;
  bool is_ack_;

  DISALLOW_COPY_AND_ASSIGN(SpdySettingsIR);
};

class NET_EXPORT_PRIVATE SpdyPingIR : public SpdyFrameIR {
 public:
  explicit SpdyPingIR(SpdyPingId id) : id_(id), is_ack_(false) {}
  SpdyPingId id() const { return id_; }

  
  bool is_ack() const { return is_ack_; }
  void set_is_ack(bool is_ack) { is_ack_ = is_ack; }

  virtual void Visit(SpdyFrameVisitor* visitor) const OVERRIDE;

 private:
  SpdyPingId id_;
  bool is_ack_;

  DISALLOW_COPY_AND_ASSIGN(SpdyPingIR);
};

class NET_EXPORT_PRIVATE SpdyGoAwayIR : public SpdyFrameIR {
 public:
  SpdyGoAwayIR(SpdyStreamId last_good_stream_id, SpdyGoAwayStatus status,
               const base::StringPiece& description);
  virtual ~SpdyGoAwayIR();
  SpdyStreamId last_good_stream_id() const { return last_good_stream_id_; }
  void set_last_good_stream_id(SpdyStreamId last_good_stream_id) {
    DCHECK_LE(0u, last_good_stream_id);
    DCHECK_EQ(0u, last_good_stream_id & ~kStreamIdMask);
    last_good_stream_id_ = last_good_stream_id;
  }
  SpdyGoAwayStatus status() const { return status_; }
  void set_status(SpdyGoAwayStatus status) {
    
    status_ = status;
  }

  const base::StringPiece& description() const;

  virtual void Visit(SpdyFrameVisitor* visitor) const OVERRIDE;

 private:
  SpdyStreamId last_good_stream_id_;
  SpdyGoAwayStatus status_;
  const base::StringPiece description_;

  DISALLOW_COPY_AND_ASSIGN(SpdyGoAwayIR);
};

class NET_EXPORT_PRIVATE SpdyHeadersIR : public SpdyFrameWithNameValueBlockIR {
 public:
  explicit SpdyHeadersIR(SpdyStreamId stream_id)
    : SpdyFrameWithNameValueBlockIR(stream_id),
      has_priority_(false),
      priority_(0) {}

  virtual void Visit(SpdyFrameVisitor* visitor) const OVERRIDE;

  bool has_priority() const { return has_priority_; }
  void set_has_priority(bool has_priority) { has_priority_ = has_priority; }
  uint32 priority() const { return priority_; }
  void set_priority(SpdyPriority priority) { priority_ = priority; }

 private:
  bool has_priority_;
  
  uint32 priority_;
  DISALLOW_COPY_AND_ASSIGN(SpdyHeadersIR);
};

class NET_EXPORT_PRIVATE SpdyWindowUpdateIR : public SpdyFrameWithStreamIdIR {
 public:
  SpdyWindowUpdateIR(SpdyStreamId stream_id, int32 delta)
      : SpdyFrameWithStreamIdIR(stream_id) {
    set_delta(delta);
  }
  int32 delta() const { return delta_; }
  void set_delta(int32 delta) {
    DCHECK_LT(0, delta);
    DCHECK_LE(delta, kSpdyMaximumWindowSize);
    delta_ = delta;
  }

  virtual void Visit(SpdyFrameVisitor* visitor) const OVERRIDE;

 private:
  int32 delta_;

  DISALLOW_COPY_AND_ASSIGN(SpdyWindowUpdateIR);
};

class NET_EXPORT_PRIVATE SpdyBlockedIR
    : public NON_EXPORTED_BASE(SpdyFrameWithStreamIdIR) {
 public:
  explicit SpdyBlockedIR(SpdyStreamId stream_id)
      : SpdyFrameWithStreamIdIR(stream_id) {}

  virtual void Visit(SpdyFrameVisitor* visitor) const OVERRIDE;

 private:
  DISALLOW_COPY_AND_ASSIGN(SpdyBlockedIR);
};

class NET_EXPORT_PRIVATE SpdyPushPromiseIR
    : public SpdyFrameWithNameValueBlockIR {
 public:
  SpdyPushPromiseIR(SpdyStreamId stream_id, SpdyStreamId promised_stream_id)
      : SpdyFrameWithNameValueBlockIR(stream_id),
        promised_stream_id_(promised_stream_id) {}
  SpdyStreamId promised_stream_id() const { return promised_stream_id_; }
  void set_promised_stream_id(SpdyStreamId id) { promised_stream_id_ = id; }

  virtual void Visit(SpdyFrameVisitor* visitor) const OVERRIDE;

 private:
  SpdyStreamId promised_stream_id_;
  DISALLOW_COPY_AND_ASSIGN(SpdyPushPromiseIR);
};

class NET_EXPORT_PRIVATE SpdyContinuationIR
    : public SpdyFrameWithNameValueBlockIR {
 public:
  explicit SpdyContinuationIR(SpdyStreamId stream_id)
      : SpdyFrameWithNameValueBlockIR(stream_id),
        end_headers_(false) {}

  virtual void Visit(SpdyFrameVisitor* visitor) const OVERRIDE;

  bool end_headers() const { return end_headers_; }
  void set_end_headers(bool end_headers) {end_headers_ = end_headers;}

 private:
  bool end_headers_;
  DISALLOW_COPY_AND_ASSIGN(SpdyContinuationIR);
};

class NET_EXPORT_PRIVATE SpdyAltSvcIR : public SpdyFrameWithStreamIdIR {
 public:
  explicit SpdyAltSvcIR(SpdyStreamId stream_id);

  uint32 max_age() const { return max_age_; }
  uint16 port() const { return port_; }
  SpdyProtocolId protocol_id() const {
    return protocol_id_;
  }
  std::string host() const { return host_; }
  std::string origin() const { return origin_; }

  void set_max_age(uint32 max_age) { max_age_ = max_age; }
  void set_port(uint16 port) { port_ = port; }
  void set_protocol_id(SpdyProtocolId protocol_id) {
    protocol_id_ = protocol_id;
  }
  void set_host(std::string host) {
    host_ = host;
  }
  void set_origin(std::string origin) {
    origin_ = origin;
  }

  virtual void Visit(SpdyFrameVisitor* visitor) const OVERRIDE;

 private:
  uint32 max_age_;
  uint16 port_;
  SpdyProtocolId protocol_id_;
  std::string host_;
  std::string origin_;
  DISALLOW_COPY_AND_ASSIGN(SpdyAltSvcIR);
};

class NET_EXPORT_PRIVATE SpdyPriorityIR : public SpdyFrameWithStreamIdIR {
 public:
  explicit SpdyPriorityIR(SpdyStreamId stream_id);
  explicit SpdyPriorityIR(SpdyStreamId stream_id,
                          SpdyStreamId parent_stream_id,
                          uint8 weight,
                          bool exclusive);
  SpdyStreamId parent_stream_id() const { return parent_stream_id_; }
  void set_parent_stream_id(SpdyStreamId id) { parent_stream_id_ = id; }
  uint8 weight() const { return weight_; }
  void set_weight(uint8 weight) { weight_ = weight; }
  bool exclusive() const { return exclusive_; }
  void set_exclusive(bool exclusive) { exclusive_ = exclusive; }

  virtual void Visit(SpdyFrameVisitor* visitor) const OVERRIDE;

 private:
  SpdyStreamId parent_stream_id_;
  uint8 weight_;
  bool exclusive_;
  DISALLOW_COPY_AND_ASSIGN(SpdyPriorityIR);
};


class SpdyFrame {
 public:
  
  
  
  
  
  
  
  SpdyFrame(char* data, size_t size, bool owns_buffer)
      : frame_(data),
        size_(size),
        owns_buffer_(owns_buffer) {
    DCHECK(frame_);
  }

  ~SpdyFrame() {
    if (owns_buffer_) {
      delete [] frame_;
    }
    frame_ = NULL;
  }

  
  
  char* data() const { return frame_; }

  
  size_t size() const { return size_; }

 protected:
  char* frame_;

 private:
  size_t size_;
  bool owns_buffer_;
  DISALLOW_COPY_AND_ASSIGN(SpdyFrame);
};

class SpdyFrameVisitor {
 public:
  virtual void VisitSynStream(const SpdySynStreamIR& syn_stream) = 0;
  virtual void VisitSynReply(const SpdySynReplyIR& syn_reply) = 0;
  virtual void VisitRstStream(const SpdyRstStreamIR& rst_stream) = 0;
  virtual void VisitSettings(const SpdySettingsIR& settings) = 0;
  virtual void VisitPing(const SpdyPingIR& ping) = 0;
  virtual void VisitGoAway(const SpdyGoAwayIR& goaway) = 0;
  virtual void VisitHeaders(const SpdyHeadersIR& headers) = 0;
  virtual void VisitWindowUpdate(const SpdyWindowUpdateIR& window_update) = 0;
  virtual void VisitBlocked(const SpdyBlockedIR& blocked) = 0;
  virtual void VisitPushPromise(const SpdyPushPromiseIR& push_promise) = 0;
  virtual void VisitContinuation(const SpdyContinuationIR& continuation) = 0;
  virtual void VisitAltSvc(const SpdyAltSvcIR& altsvc) = 0;
  virtual void VisitPriority(const SpdyPriorityIR& priority) = 0;
  virtual void VisitData(const SpdyDataIR& data) = 0;

 protected:
  SpdyFrameVisitor() {}
  virtual ~SpdyFrameVisitor() {}

 private:
  DISALLOW_COPY_AND_ASSIGN(SpdyFrameVisitor);
};

}  

#endif  
