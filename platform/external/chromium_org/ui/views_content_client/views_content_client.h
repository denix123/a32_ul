// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_CONTENT_CLIENT_VIEWS_CONTENT_CLIENT_H_
#define UI_VIEWS_CONTENT_CLIENT_VIEWS_CONTENT_CLIENT_H_

#include "base/callback.h"
#include "base/macros.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/views_content_client/views_content_client_export.h"

namespace content {
class BrowserContext;
}

namespace sandbox {
struct SandboxInterfaceInfo;
}

namespace ui {

class VIEWS_CONTENT_CLIENT_EXPORT ViewsContentClient {
 public:
  typedef base::Callback<
      void(content::BrowserContext* browser_context,
           gfx::NativeWindow window_context)> Task;

#if defined(OS_WIN)
  ViewsContentClient(HINSTANCE instance,
                     sandbox::SandboxInterfaceInfo* sandbox_info);
#else
  ViewsContentClient(int argc, const char** argv);
#endif

  ~ViewsContentClient();

  
  int RunMain();

  
  
  void set_task(const Task& task) { task_ = task; }
  const Task& task() const { return task_; }

 private:
#if defined(OS_WIN)
  HINSTANCE instance_;
  sandbox::SandboxInterfaceInfo* sandbox_info_;
#else
  int argc_;
  const char** argv_;
#endif
  Task task_;

  DISALLOW_COPY_AND_ASSIGN(ViewsContentClient);
};

}  

#endif  
