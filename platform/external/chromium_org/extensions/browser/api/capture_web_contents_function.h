// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_CAPTURE_WEB_CONTENTS_FUNCTION_H_
#define EXTENSIONS_BROWSER_API_CAPTURE_WEB_CONTENTS_FUNCTION_H_

#include "extensions/browser/extension_function.h"
#include "extensions/common/api/extension_types.h"

class SkBitmap;

namespace content {
class WebContents;
}

namespace extensions {

class CaptureWebContentsFunction : public AsyncExtensionFunction {
 public:
  CaptureWebContentsFunction() {}

 protected:
  virtual ~CaptureWebContentsFunction() {}

  
  virtual bool HasPermission() OVERRIDE;
  virtual bool RunAsync() OVERRIDE;

  virtual bool IsScreenshotEnabled() = 0;
  virtual content::WebContents* GetWebContentsForID(int context_id) = 0;

  enum FailureReason {
    FAILURE_REASON_UNKNOWN,
    FAILURE_REASON_ENCODING_FAILED,
    FAILURE_REASON_VIEW_INVISIBLE
  };
  virtual void OnCaptureFailure(FailureReason reason) = 0;

 private:
  typedef core_api::extension_types::ImageDetails ImageDetails;

  void CopyFromBackingStoreComplete(bool succeed, const SkBitmap& bitmap);
  void OnCaptureSuccess(const SkBitmap& bitmap);

  
  
  
  
  int context_id_;

  
  ImageDetails::Format image_format_;

  
  int image_quality_;

  DISALLOW_COPY_AND_ASSIGN(CaptureWebContentsFunction);
};

}  

#endif  
