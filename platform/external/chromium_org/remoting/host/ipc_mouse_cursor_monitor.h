// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_HOST_IPC_MOUSE_CURSOR_MONITOR_H_
#define REMOTING_HOST_IPC_MOUSE_CURSOR_MONITOR_H_

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "third_party/webrtc/modules/desktop_capture/desktop_frame.h"
#include "third_party/webrtc/modules/desktop_capture/mouse_cursor_monitor.h"

namespace remoting {

class DesktopSessionProxy;

class IpcMouseCursorMonitor : public webrtc::MouseCursorMonitor {
 public:
  explicit IpcMouseCursorMonitor(
      scoped_refptr<DesktopSessionProxy> desktop_session_proxy);
  virtual ~IpcMouseCursorMonitor();

  
  virtual void Init(Callback* callback, Mode mode) OVERRIDE;
  virtual void Capture() OVERRIDE;

  
  void OnMouseCursor(scoped_ptr<webrtc::MouseCursor> cursor);

 private:
  
  webrtc::MouseCursorMonitor::Callback* callback_;

  
  scoped_refptr<DesktopSessionProxy> desktop_session_proxy_;

  
  base::WeakPtrFactory<IpcMouseCursorMonitor> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(IpcMouseCursorMonitor);
};

}  

#endif  
