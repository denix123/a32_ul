// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_FORMATS_MP2T_TS_SECTION_PES_H_
#define MEDIA_FORMATS_MP2T_TS_SECTION_PES_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "media/base/byte_queue.h"
#include "media/formats/mp2t/ts_section.h"

namespace media {
namespace mp2t {

class EsParser;
class TimestampUnroller;

class TsSectionPes : public TsSection {
 public:
  TsSectionPes(scoped_ptr<EsParser> es_parser,
               TimestampUnroller* timestamp_unroller);
  virtual ~TsSectionPes();

  
  virtual bool Parse(bool payload_unit_start_indicator,
                     const uint8* buf, int size) OVERRIDE;
  virtual void Flush() OVERRIDE;
  virtual void Reset() OVERRIDE;

 private:
  
  
  
  
  bool Emit(bool emit_for_unknown_size);

  
  bool ParseInternal(const uint8* raw_pes, int raw_pes_size);

  void ResetPesState();

  
  ByteQueue pes_byte_queue_;

  
  scoped_ptr<EsParser> es_parser_;

  
  bool wait_for_pusi_;

  
  TimestampUnroller* const timestamp_unroller_;

  DISALLOW_COPY_AND_ASSIGN(TsSectionPes);
};

}  
}  

#endif

