// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_X_X11_UTIL_H_
#define UI_BASE_X_X11_UTIL_H_


#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/event_types.h"
#include "base/memory/ref_counted_memory.h"
#include "ui/base/ui_base_export.h"
#include "ui/events/event_constants.h"
#include "ui/events/keycodes/keyboard_codes.h"
#include "ui/gfx/point.h"
#include "ui/gfx/x/x11_types.h"

typedef unsigned long XSharedMemoryId;  
typedef unsigned long Cursor;
typedef struct _XcursorImage XcursorImage;
typedef union _XEvent XEvent;

namespace gfx {
class Canvas;
class Point;
class Rect;
}
class SkBitmap;

namespace ui {



UI_BASE_EXPORT bool IsXInput2Available();

enum SharedMemorySupport {
  SHARED_MEMORY_NONE,
  SHARED_MEMORY_PUTIMAGE,
  SHARED_MEMORY_PIXMAP
};
UI_BASE_EXPORT SharedMemorySupport QuerySharedMemorySupport(XDisplay* dpy);

UI_BASE_EXPORT bool QueryRenderSupport(XDisplay* dpy);

UI_BASE_EXPORT ::Cursor GetXCursor(int cursor_shape);

UI_BASE_EXPORT ::Cursor CreateReffedCustomXCursor(XcursorImage* image);

UI_BASE_EXPORT void RefCustomXCursor(::Cursor cursor);

UI_BASE_EXPORT void UnrefCustomXCursor(::Cursor cursor);

UI_BASE_EXPORT XcursorImage* SkBitmapToXcursorImage(const SkBitmap* bitmap,
                                                    const gfx::Point& hotspot);

UI_BASE_EXPORT int CoalescePendingMotionEvents(const XEvent* xev,
                                               XEvent* last_event);

UI_BASE_EXPORT void HideHostCursor();

UI_BASE_EXPORT ::Cursor CreateInvisibleCursor();

UI_BASE_EXPORT void SetUseOSWindowFrame(XID window, bool use_os_window_frame);


UI_BASE_EXPORT bool IsShapeExtensionAvailable();

UI_BASE_EXPORT XID GetX11RootWindow();

UI_BASE_EXPORT bool GetCurrentDesktop(int* desktop);

enum HideTitlebarWhenMaximized {
  SHOW_TITLEBAR_WHEN_MAXIMIZED = 0,
  HIDE_TITLEBAR_WHEN_MAXIMIZED = 1,
};
UI_BASE_EXPORT void SetHideTitlebarWhenMaximizedProperty(
    XID window,
    HideTitlebarWhenMaximized property);

UI_BASE_EXPORT void ClearX11DefaultRootWindow();

UI_BASE_EXPORT bool IsWindowVisible(XID window);

UI_BASE_EXPORT bool GetWindowRect(XID window, gfx::Rect* rect);

UI_BASE_EXPORT bool WindowContainsPoint(XID window, gfx::Point screen_loc);

UI_BASE_EXPORT bool PropertyExists(XID window,
                                   const std::string& property_name);

UI_BASE_EXPORT bool GetRawBytesOfProperty(
    XID window,
    XAtom property,
    scoped_refptr<base::RefCountedMemory>* out_data,
    size_t* out_data_items,
    XAtom* out_type);

UI_BASE_EXPORT bool GetIntProperty(XID window,
                                   const std::string& property_name,
                                   int* value);
UI_BASE_EXPORT bool GetXIDProperty(XID window,
                                   const std::string& property_name,
                                   XID* value);
UI_BASE_EXPORT bool GetIntArrayProperty(XID window,
                                        const std::string& property_name,
                                        std::vector<int>* value);
UI_BASE_EXPORT bool GetAtomArrayProperty(XID window,
                                         const std::string& property_name,
                                         std::vector<XAtom>* value);
UI_BASE_EXPORT bool GetStringProperty(XID window,
                                      const std::string& property_name,
                                      std::string* value);

UI_BASE_EXPORT bool SetIntProperty(XID window,
                                   const std::string& name,
                                   const std::string& type,
                                   int value);
UI_BASE_EXPORT bool SetIntArrayProperty(XID window,
                                        const std::string& name,
                                        const std::string& type,
                                        const std::vector<int>& value);
UI_BASE_EXPORT bool SetAtomProperty(XID window,
                                    const std::string& name,
                                    const std::string& type,
                                    XAtom value);
UI_BASE_EXPORT bool SetAtomArrayProperty(XID window,
                                         const std::string& name,
                                         const std::string& type,
                                         const std::vector<XAtom>& value);
UI_BASE_EXPORT bool SetStringProperty(XID window,
                                      XAtom property,
                                      XAtom type,
                                      const std::string& value);

UI_BASE_EXPORT XAtom GetAtom(const char* atom_name);

UI_BASE_EXPORT void SetWindowClassHint(XDisplay* display,
                                       XID window,
                                       const std::string& res_name,
                                       const std::string& res_class);

UI_BASE_EXPORT void SetWindowRole(XDisplay* display,
                                  XID window,
                                  const std::string& role);

UI_BASE_EXPORT bool GetCustomFramePrefDefault();

static const int kAllDesktops = -1;
bool GetWindowDesktop(XID window, int* desktop);

UI_BASE_EXPORT std::string GetX11ErrorString(XDisplay* display, int err);

class EnumerateWindowsDelegate {
 public:
  
  
  virtual bool ShouldStopIterating(XID xid) = 0;

 protected:
  virtual ~EnumerateWindowsDelegate() {}
};

UI_BASE_EXPORT bool EnumerateAllWindows(EnumerateWindowsDelegate* delegate,
                                        int max_depth);

UI_BASE_EXPORT void EnumerateTopLevelWindows(
    ui::EnumerateWindowsDelegate* delegate);

UI_BASE_EXPORT bool GetXWindowStack(XID window, std::vector<XID>* windows);

UI_BASE_EXPORT bool CopyAreaToCanvas(XID drawable,
                                     gfx::Rect source_bounds,
                                     gfx::Point dest_offset,
                                     gfx::Canvas* canvas);

enum WindowManagerName {
  WM_UNKNOWN,

  WM_AWESOME,
  WM_BLACKBOX,
  WM_COMPIZ,
  WM_ENLIGHTENMENT,
  WM_I3,
  WM_ICE_WM,
  WM_ION3,
  WM_KWIN,
  WM_MATCHBOX,
  WM_METACITY,
  WM_MUFFIN,
  WM_MUTTER,
  WM_NOTION,
  WM_OPENBOX,
  WM_QTILE,
  WM_RATPOISON,
  WM_STUMPWM,
  WM_XFWM4,
};
UI_BASE_EXPORT WindowManagerName GuessWindowManager();

UI_BASE_EXPORT std::string GuessWindowManagerName();

UI_BASE_EXPORT void SetDefaultX11ErrorHandlers();

UI_BASE_EXPORT bool IsX11WindowFullScreen(XID window);

UI_BASE_EXPORT bool WmSupportsHint(XAtom atom);

class UI_BASE_EXPORT XRefcountedMemory : public base::RefCountedMemory {
 public:
  XRefcountedMemory(unsigned char* x11_data, size_t length)
      : x11_data_(length ? x11_data : NULL), length_(length) {}

  
  virtual const unsigned char* front() const OVERRIDE;
  virtual size_t size() const OVERRIDE;

 private:
  virtual ~XRefcountedMemory();

  unsigned char* x11_data_;
  size_t length_;

  DISALLOW_COPY_AND_ASSIGN(XRefcountedMemory);
};

class UI_BASE_EXPORT XScopedString {
 public:
  explicit XScopedString(char* str) : string_(str) {}
  ~XScopedString();

  const char* string() const { return string_; }

 private:
  char* string_;

  DISALLOW_COPY_AND_ASSIGN(XScopedString);
};

class UI_BASE_EXPORT XScopedImage {
 public:
  explicit XScopedImage(XImage* image) : image_(image) {}
  ~XScopedImage();

  XImage* get() const { return image_; }

  XImage* operator->() const { return image_; }

  void reset(XImage* image);

 private:
  XImage* image_;

  DISALLOW_COPY_AND_ASSIGN(XScopedImage);
};

class UI_BASE_EXPORT XScopedCursor {
 public:
  
  XScopedCursor(::Cursor cursor, XDisplay* display);
  ~XScopedCursor();

  ::Cursor get() const;
  void reset(::Cursor cursor);

 private:
  ::Cursor cursor_;
  XDisplay* display_;

  DISALLOW_COPY_AND_ASSIGN(XScopedCursor);
};

namespace test {
UI_BASE_EXPORT void ResetXCursorCache();

UI_BASE_EXPORT const XcursorImage* GetCachedXcursorImage(::Cursor cursor);

}  

}  

#endif  
