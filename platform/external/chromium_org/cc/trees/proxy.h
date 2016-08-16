// Copyright 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_TREES_PROXY_H_
#define CC_TREES_PROXY_H_

#include <string>

#include "base/basictypes.h"
#include "base/logging.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/threading/platform_thread.h"
#include "base/time/time.h"
#include "base/values.h"
#include "cc/base/cc_export.h"

namespace base {
namespace debug {
class TracedValue;
}
class SingleThreadTaskRunner;
}

namespace gfx {
class Rect;
class Vector2d;
}

namespace cc {
class BlockingTaskRunner;
class LayerTreeDebugState;
class OutputSurface;
struct RendererCapabilities;

class CC_EXPORT Proxy {
 public:
  base::SingleThreadTaskRunner* MainThreadTaskRunner() const;
  bool HasImplThread() const;
  base::SingleThreadTaskRunner* ImplThreadTaskRunner() const;

  
  bool IsMainThread() const;
  bool IsImplThread() const;
  bool IsMainThreadBlocked() const;
#if DCHECK_IS_ON
  void SetMainThreadBlocked(bool is_main_thread_blocked);
  void SetCurrentThreadIsImplThread(bool is_impl_thread);
#endif

  virtual ~Proxy();

  virtual void FinishAllRendering() = 0;

  virtual bool IsStarted() const = 0;

  
  
  virtual void SetOutputSurface(scoped_ptr<OutputSurface> output_surface) = 0;

  
  
  virtual void SetLayerTreeHostClientReady() = 0;

  virtual void SetVisible(bool visible) = 0;

  virtual const RendererCapabilities& GetRendererCapabilities() const = 0;

  virtual void SetNeedsAnimate() = 0;
  virtual void SetNeedsUpdateLayers() = 0;
  virtual void SetNeedsCommit() = 0;
  virtual void SetNeedsRedraw(const gfx::Rect& damage_rect) = 0;
  virtual void SetNextCommitWaitsForActivation() = 0;

  virtual void NotifyInputThrottledUntilCommit() = 0;

  
  
  
  virtual void SetDeferCommits(bool defer_commits) = 0;

  virtual void MainThreadHasStoppedFlinging() = 0;

  virtual bool CommitRequested() const = 0;
  virtual bool BeginMainFrameRequested() const = 0;

  
  virtual void Start() = 0;
  virtual void Stop() = 0;   

  
  
  virtual void ForceSerializeOnSwapBuffers() = 0;

  
  virtual size_t MaxPartialTextureUpdates() const = 0;

  virtual bool SupportsImplScrolling() const = 0;

  virtual void AsValueInto(base::debug::TracedValue* value) const = 0;

  virtual void SetDebugState(const LayerTreeDebugState& debug_state) = 0;

  
  virtual bool MainFrameWillHappenForTesting() = 0;

  BlockingTaskRunner* blocking_main_thread_task_runner() const {
    return blocking_main_thread_task_runner_.get();
  }

 protected:
  Proxy(scoped_refptr<base::SingleThreadTaskRunner> main_task_runner,
        scoped_refptr<base::SingleThreadTaskRunner> impl_task_runner);
  friend class DebugScopedSetImplThread;
  friend class DebugScopedSetMainThread;
  friend class DebugScopedSetMainThreadBlocked;

 private:
  scoped_refptr<base::SingleThreadTaskRunner> main_task_runner_;
  scoped_refptr<base::SingleThreadTaskRunner> impl_task_runner_;
  scoped_ptr<BlockingTaskRunner> blocking_main_thread_task_runner_;

#if DCHECK_IS_ON
  const base::PlatformThreadId main_thread_id_;
  bool impl_thread_is_overridden_;
  bool is_main_thread_blocked_;
#endif

  DISALLOW_COPY_AND_ASSIGN(Proxy);
};

#if DCHECK_IS_ON
class DebugScopedSetMainThreadBlocked {
 public:
  explicit DebugScopedSetMainThreadBlocked(Proxy* proxy) : proxy_(proxy) {
    DCHECK(!proxy_->IsMainThreadBlocked());
    proxy_->SetMainThreadBlocked(true);
  }
  ~DebugScopedSetMainThreadBlocked() {
    DCHECK(proxy_->IsMainThreadBlocked());
    proxy_->SetMainThreadBlocked(false);
  }
 private:
  Proxy* proxy_;
  DISALLOW_COPY_AND_ASSIGN(DebugScopedSetMainThreadBlocked);
};
#else
class DebugScopedSetMainThreadBlocked {
 public:
  explicit DebugScopedSetMainThreadBlocked(Proxy* proxy) {}
  ~DebugScopedSetMainThreadBlocked() {}
 private:
  DISALLOW_COPY_AND_ASSIGN(DebugScopedSetMainThreadBlocked);
};
#endif

}  

#endif  
