// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SERVICES_CLIPBOARD_CLIPBOARD_STANDALONE_IMPL_H_
#define MOJO_SERVICES_CLIPBOARD_CLIPBOARD_STANDALONE_IMPL_H_

#include <base/memory/scoped_ptr.h>
#include <string>

#include "mojo/services/public/interfaces/clipboard/clipboard.mojom.h"

namespace mojo {

class ClipboardStandaloneImpl : public InterfaceImpl<mojo::Clipboard> {
 public:
  
  static const int kNumClipboards = 3;

  ClipboardStandaloneImpl();
  virtual ~ClipboardStandaloneImpl();

  
  virtual void GetSequenceNumber(Clipboard::Type clipboard_type,
                                 const mojo::Callback<void(uint64_t)>& callback)
      MOJO_OVERRIDE;
  virtual void GetAvailableMimeTypes(
      Clipboard::Type clipboard_types,
      const mojo::Callback<void(mojo::Array<mojo::String>)>& callback)
      MOJO_OVERRIDE;
  virtual void ReadMimeType(
      Clipboard::Type clipboard_type,
      const mojo::String& mime_type,
      const mojo::Callback<void(mojo::Array<uint8_t>)>& callback)
      MOJO_OVERRIDE;
  virtual void WriteClipboardData(Clipboard::Type clipboard_type,
                                  mojo::Array<MimeTypePairPtr> data)
      MOJO_OVERRIDE;

 private:
  uint64_t sequence_number_[kNumClipboards];

  
  class ClipboardData;

  
  scoped_ptr<ClipboardData> clipboard_state_[kNumClipboards];

  DISALLOW_COPY_AND_ASSIGN(ClipboardStandaloneImpl);
};

}  

#endif  
