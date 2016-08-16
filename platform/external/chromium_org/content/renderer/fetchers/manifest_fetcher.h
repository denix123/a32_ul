// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_FETCHERS_MANIFEST_FETCHER_H_
#define CONTENT_RENDERER_FETCHERS_MANIFEST_FETCHER_H_

#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "content/common/content_export.h"
#include "third_party/WebKit/public/platform/WebURLResponse.h"

class GURL;

namespace blink {
class WebFrame;
}

namespace content {

class ResourceFetcher;

class CONTENT_EXPORT ManifestFetcher {
 public:
  
  
  
  
  typedef base::Callback<void(const blink::WebURLResponse& response,
                              const std::string& data)> Callback;

  explicit ManifestFetcher(const GURL& url);
  virtual ~ManifestFetcher();

  void Start(blink::WebFrame* frame, const Callback& callback);
  void Cancel();

 private:
  void OnLoadComplete(const blink::WebURLResponse& response,
                      const std::string& data);

  bool completed_;
  Callback callback_;
  scoped_ptr<ResourceFetcher> fetcher_;

  DISALLOW_COPY_AND_ASSIGN(ManifestFetcher);
};

} 

#endif 
