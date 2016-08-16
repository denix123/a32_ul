// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_FORMATS_MP2T_ES_PARSER_H_
#define MEDIA_FORMATS_MP2T_ES_PARSER_H_

#include <list>
#include <utility>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/time/time.h"
#include "media/base/media_export.h"
#include "media/base/stream_parser_buffer.h"

namespace media {

class OffsetByteQueue;
class StreamParserBuffer;

namespace mp2t {

class MEDIA_EXPORT EsParser {
 public:
  typedef base::Callback<void(scoped_refptr<StreamParserBuffer>)> EmitBufferCB;

  EsParser();
  virtual ~EsParser();

  
  
  bool Parse(const uint8* buf, int size,
             base::TimeDelta pts,
             DecodeTimestamp dts);

  
  virtual void Flush() = 0;

  
  void Reset();

 protected:
  struct TimingDesc {
    TimingDesc();
    TimingDesc(DecodeTimestamp dts, base::TimeDelta pts);

    DecodeTimestamp dts;
    base::TimeDelta pts;
  };

  
  
  virtual bool ParseFromEsQueue() = 0;

  
  virtual void ResetInternal() = 0;

  
  
  
  
  
  TimingDesc GetTimingDescriptor(int64 es_byte_count);

  
  scoped_ptr<media::OffsetByteQueue> es_queue_;

 private:
  
  
  
  
  
  
  
  
  
  
  
  std::list<std::pair<int64, TimingDesc> > timing_desc_list_;

  DISALLOW_COPY_AND_ASSIGN(EsParser);
};

}  
}  

#endif
