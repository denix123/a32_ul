// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDERER_HOST_COMPOSITING_IOSURFACE_LAYER_MAC_H_
#define CONTENT_BROWSER_RENDERER_HOST_COMPOSITING_IOSURFACE_LAYER_MAC_H_

#import <Cocoa/Cocoa.h>

#include "base/mac/scoped_cftyperef.h"
#include "base/memory/ref_counted.h"
#include "base/timer/timer.h"
#include "ui/gfx/size.h"

@class IOSurfaceLayer;

namespace content {
class CompositingIOSurfaceMac;
class CompositingIOSurfaceContext;

class IOSurfaceLayerClient {
 public:
  
  
  
  virtual bool IOSurfaceLayerShouldAckImmediately() const = 0;

  
  
  virtual void IOSurfaceLayerDidDrawFrame() = 0;

  
  virtual void IOSurfaceLayerHitError() = 0;
};

class IOSurfaceLayerHelper {
 public:
  IOSurfaceLayerHelper(IOSurfaceLayerClient* client,
                                  IOSurfaceLayer* layer);
  ~IOSurfaceLayerHelper();

  
  void GotNewFrame();

  
  void SetNeedsDisplay();

  
  
  bool CanDraw();

  
  
  void DidDraw(bool success);

  
  
  void SetNeedsDisplayAndDisplayAndAck();

  
  
  void DisplayIfNeededAndAck();

  
  
  
  void BeginPumpingFrames();
  void EndPumpingFrames();

 private:
  
  
  
  void AckPendingFrame(bool success);

  void TimerFired();

  
  content::IOSurfaceLayerClient* const client_;

  
  IOSurfaceLayer* const layer_;

  
  
  
  bool needs_display_;

  
  bool has_pending_frame_;

  
  
  uint64 did_not_draw_counter_;

  
  bool is_pumping_frames_;

  
  
  
  
  base::DelayTimer<IOSurfaceLayerHelper> timer_;
};

}  

@interface IOSurfaceLayer : CAOpenGLLayer {
 @private
  scoped_refptr<content::CompositingIOSurfaceMac> iosurface_;
  scoped_refptr<content::CompositingIOSurfaceContext> context_;

  scoped_ptr<content::IOSurfaceLayerHelper> helper_;
}

- (id)initWithClient:(content::IOSurfaceLayerClient*)client
     withScaleFactor:(float)scale_factor;

- (bool)gotFrameWithIOSurface:(IOSurfaceID)io_surface_id
                withPixelSize:(gfx::Size)pixel_size
              withScaleFactor:(float)scale_factor;

- (void)poisonContextAndSharegroup;
- (bool)hasBeenPoisoned;

- (float)scaleFactor;

- (int)rendererID;

- (void)resetClient;

- (void)gotNewFrame;

- (void)setNeedsDisplayAndDisplayAndAck;

- (void)displayIfNeededAndAck;

- (void)beginPumpingFrames;
- (void)endPumpingFrames;
@end

#endif  
