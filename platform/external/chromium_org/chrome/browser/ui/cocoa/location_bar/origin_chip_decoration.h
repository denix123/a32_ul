// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_COCOA_LOCATION_BAR_ORIGIN_CHIP_DECORATION_H_
#define CHROME_BROWSER_UI_COCOA_LOCATION_BAR_ORIGIN_CHIP_DECORATION_H_

#import <Cocoa/Cocoa.h>

#include "base/mac/scoped_nsobject.h"
#include "chrome/browser/safe_browsing/ui_manager.h"
#include "chrome/browser/ui/cocoa/location_bar/button_decoration.h"
#include "chrome/browser/ui/location_bar/origin_chip_info.h"
#include "extensions/browser/extension_icon_image.h"

class LocationBarViewMac;
class LocationIconDecoration;

namespace content {
class WebContents;
}

class OriginChipDecoration : public ButtonDecoration,
                             public extensions::IconImage::Observer,
                             public SafeBrowsingUIManager::Observer {
 public:
  OriginChipDecoration(LocationBarViewMac* owner,
                       LocationIconDecoration* location_icon);
  virtual ~OriginChipDecoration();

  
  void Update();

  
  virtual bool PreventFocus(NSPoint location) const OVERRIDE;

  
  virtual CGFloat GetWidthForSpace(CGFloat width) OVERRIDE;
  virtual void DrawInFrame(NSRect frame, NSView* control_view) OVERRIDE;
  virtual NSString* GetToolTip() OVERRIDE;
  virtual bool OnMousePressed(NSRect frame, NSPoint location) OVERRIDE;
  virtual NSPoint GetBubblePointInFrame(NSRect frame) OVERRIDE;

  
  virtual void OnExtensionIconImageChanged(
      extensions::IconImage* image) OVERRIDE;

  
  virtual void OnSafeBrowsingHit(
      const SafeBrowsingUIManager::UnsafeResource& resource) OVERRIDE;
  virtual void OnSafeBrowsingMatch(
      const SafeBrowsingUIManager::UnsafeResource& resource) OVERRIDE;

 private:
  
  CGFloat GetChipWidth() const;

  
  base::scoped_nsobject<NSMutableDictionary> attributes_;

  
  
  base::scoped_nsobject<NSImage> extension_icon_;

  
  
  NSRect icon_rect_;

  
  OriginChipInfo info_;

  
  base::scoped_nsobject<NSString> label_;

  
  LocationIconDecoration* location_icon_;

  
  LocationBarViewMac* owner_;

  DISALLOW_COPY_AND_ASSIGN(OriginChipDecoration);
};

#endif  
