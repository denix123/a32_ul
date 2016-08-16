// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BLINK_ACTIVE_LOADER_H_
#define MEDIA_BLINK_ACTIVE_LOADER_H_

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "media/base/media_export.h"

namespace blink {
class WebURLLoader;
}

namespace media {

class MEDIA_EXPORT ActiveLoader {
 public:
  
  
  explicit ActiveLoader(scoped_ptr<blink::WebURLLoader> loader);
  ~ActiveLoader();

  
  void SetDeferred(bool deferred);
  bool deferred() { return deferred_; }

 private:
  friend class BufferedDataSourceTest;

  scoped_ptr<blink::WebURLLoader> loader_;
  bool deferred_;

  DISALLOW_IMPLICIT_CONSTRUCTORS(ActiveLoader);
};

}  

#endif  
