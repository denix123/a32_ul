// Copyright 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_SCHEDULER_SCHEDULER_STATE_MACHINE_H_
#define CC_SCHEDULER_SCHEDULER_STATE_MACHINE_H_

#include <string>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "cc/base/cc_export.h"
#include "cc/output/begin_frame_args.h"
#include "cc/scheduler/draw_result.h"
#include "cc/scheduler/scheduler_settings.h"

namespace base {
namespace debug {
class ConvertableToTraceForamt;
class TracedValue;
}
class Value;
}

namespace cc {

class CC_EXPORT SchedulerStateMachine {
 public:
  
  explicit SchedulerStateMachine(const SchedulerSettings& settings);

  enum OutputSurfaceState {
    OUTPUT_SURFACE_ACTIVE,
    OUTPUT_SURFACE_LOST,
    OUTPUT_SURFACE_CREATING,
    OUTPUT_SURFACE_WAITING_FOR_FIRST_COMMIT,
    OUTPUT_SURFACE_WAITING_FOR_FIRST_ACTIVATION,
  };
  static const char* OutputSurfaceStateToString(OutputSurfaceState state);

  
  
  
  
  enum BeginImplFrameState {
    BEGIN_IMPL_FRAME_STATE_IDLE,
    BEGIN_IMPL_FRAME_STATE_BEGIN_FRAME_STARTING,
    BEGIN_IMPL_FRAME_STATE_INSIDE_BEGIN_FRAME,
    BEGIN_IMPL_FRAME_STATE_INSIDE_DEADLINE,
  };
  static const char* BeginImplFrameStateToString(BeginImplFrameState state);

  enum CommitState {
    COMMIT_STATE_IDLE,
    COMMIT_STATE_BEGIN_MAIN_FRAME_SENT,
    COMMIT_STATE_BEGIN_MAIN_FRAME_STARTED,
    COMMIT_STATE_READY_TO_COMMIT,
    COMMIT_STATE_WAITING_FOR_ACTIVATION,
    COMMIT_STATE_WAITING_FOR_FIRST_DRAW,
  };
  static const char* CommitStateToString(CommitState state);

  enum ForcedRedrawOnTimeoutState {
    FORCED_REDRAW_STATE_IDLE,
    FORCED_REDRAW_STATE_WAITING_FOR_COMMIT,
    FORCED_REDRAW_STATE_WAITING_FOR_ACTIVATION,
    FORCED_REDRAW_STATE_WAITING_FOR_DRAW,
  };
  static const char* ForcedRedrawOnTimeoutStateToString(
      ForcedRedrawOnTimeoutState state);

  bool CommitPending() const {
    return commit_state_ == COMMIT_STATE_BEGIN_MAIN_FRAME_SENT ||
           commit_state_ == COMMIT_STATE_BEGIN_MAIN_FRAME_STARTED ||
           commit_state_ == COMMIT_STATE_READY_TO_COMMIT;
  }
  CommitState commit_state() const { return commit_state_; }

  bool RedrawPending() const { return needs_redraw_; }
  bool ManageTilesPending() const { return needs_manage_tiles_; }

  enum Action {
    ACTION_NONE,
    ACTION_ANIMATE,
    ACTION_SEND_BEGIN_MAIN_FRAME,
    ACTION_COMMIT,
    ACTION_UPDATE_VISIBLE_TILES,
    ACTION_ACTIVATE_SYNC_TREE,
    ACTION_DRAW_AND_SWAP_IF_POSSIBLE,
    ACTION_DRAW_AND_SWAP_FORCED,
    ACTION_DRAW_AND_SWAP_ABORT,
    ACTION_BEGIN_OUTPUT_SURFACE_CREATION,
    ACTION_MANAGE_TILES,
  };
  static const char* ActionToString(Action action);

  scoped_refptr<base::debug::ConvertableToTraceFormat> AsValue() const;
  void AsValueInto(base::debug::TracedValue* dict, base::TimeTicks now) const;

  Action NextAction() const;
  void UpdateState(Action action);

  
  
  bool BeginFrameNeeded() const;

  
  
  
  
  bool ShouldPollForAnticipatedDrawTriggers() const;

  
  
  
  void OnBeginImplFrame(const BeginFrameArgs& args);
  void OnBeginImplFrameDeadlinePending();
  void OnBeginImplFrameDeadline();
  void OnBeginImplFrameIdle();
  bool ShouldTriggerBeginImplFrameDeadlineEarly() const;
  BeginImplFrameState begin_impl_frame_state() const {
    return begin_impl_frame_state_;
  }

  
  
  bool MainThreadIsInHighLatencyMode() const;

  
  
  
  void DidEnterPollForAnticipatedDrawTriggers();
  void DidLeavePollForAnticipatedDrawTriggers();
  bool inside_poll_for_anticipated_draw_triggers() const {
    return inside_poll_for_anticipated_draw_triggers_;
  }

  
  void SetVisible(bool visible);

  
  
  void SetNeedsRedraw();
  bool needs_redraw() const { return needs_redraw_; }

  void SetNeedsAnimate();
  bool needs_animate() const { return needs_animate_; }

  
  
  void SetNeedsManageTiles();

  
  void SetMaxSwapsPending(int max);

  
  
  
  void DidSwapBuffers();

  
  
  void SetSwapUsedIncompleteTile(bool used_incomplete_tile);

  
  void DidSwapBuffersComplete();

  
  
  void SetImplLatencyTakesPriority(bool impl_latency_takes_priority);
  bool impl_latency_takes_priority() const {
    return impl_latency_takes_priority_;
  }

  
  void DidDrawIfPossibleCompleted(DrawResult result);

  
  
  
  void SetNeedsCommit();

  
  
  
  void NotifyReadyToCommit();

  
  
  
  void BeginMainFrameAborted(bool did_handle);

  
  void SetCanStart() { can_start_ = true; }

  void SetSkipNextBeginMainFrameToReduceLatency();

  
  
  
  void SetCanDraw(bool can);

  
  void NotifyBeginMainFrameStarted();

  
  void NotifyReadyToActivate();

  bool has_pending_tree() const { return has_pending_tree_; }
  bool active_tree_needs_first_draw() const {
    return active_tree_needs_first_draw_;
  }

  void DidManageTiles();
  void DidLoseOutputSurface();
  void DidCreateAndInitializeOutputSurface();
  bool HasInitializedOutputSurface() const;

  
  bool PendingDrawsShouldBeAborted() const;

  bool SupportsProactiveBeginFrame() const;

  void SetContinuousPainting(bool continuous_painting) {
    continuous_painting_ = continuous_painting;
  }

  bool CouldSendBeginMainFrame() const;

  
  
  std::string GetStatesForDebugging() const;

 protected:
  bool BeginFrameNeededToAnimateOrDraw() const;
  bool ProactiveBeginFrameWanted() const;

  
  bool PendingActivationsShouldBeForced() const;

  bool ShouldAnimate() const;
  bool ShouldBeginOutputSurfaceCreation() const;
  bool ShouldDrawForced() const;
  bool ShouldDraw() const;
  bool ShouldActivatePendingTree() const;
  bool ShouldUpdateVisibleTiles() const;
  bool ShouldSendBeginMainFrame() const;
  bool ShouldCommit() const;
  bool ShouldManageTiles() const;

  void AdvanceCurrentFrameNumber();
  bool HasSentBeginMainFrameThisFrame() const;
  bool HasUpdatedVisibleTilesThisFrame() const;
  bool HasRequestedSwapThisFrame() const;
  bool HasSwappedThisFrame() const;

  void UpdateStateOnCommit(bool commit_was_aborted);
  void UpdateStateOnActivation();
  void UpdateStateOnDraw(bool did_request_swap);
  void UpdateStateOnManageTiles();

  const SchedulerSettings settings_;

  OutputSurfaceState output_surface_state_;
  BeginImplFrameState begin_impl_frame_state_;
  CommitState commit_state_;
  ForcedRedrawOnTimeoutState forced_redraw_state_;

  BeginFrameArgs begin_impl_frame_args_;

  int commit_count_;
  int current_frame_number_;
  int last_frame_number_animate_performed_;
  int last_frame_number_swap_performed_;
  int last_frame_number_swap_requested_;
  int last_frame_number_begin_main_frame_sent_;
  int last_frame_number_update_visible_tiles_was_called_;

  
  
  
  
  int manage_tiles_funnel_;
  int consecutive_checkerboard_animations_;
  int max_pending_swaps_;
  int pending_swaps_;
  bool needs_redraw_;
  bool needs_animate_;
  bool needs_manage_tiles_;
  bool swap_used_incomplete_tile_;
  bool needs_commit_;
  bool inside_poll_for_anticipated_draw_triggers_;
  bool visible_;
  bool can_start_;
  bool can_draw_;
  bool has_pending_tree_;
  bool pending_tree_is_ready_for_activation_;
  bool active_tree_needs_first_draw_;
  bool did_create_and_initialize_first_output_surface_;
  bool impl_latency_takes_priority_;
  bool skip_next_begin_main_frame_to_reduce_latency_;
  bool skip_begin_main_frame_to_reduce_latency_;
  bool continuous_painting_;

 private:
  DISALLOW_COPY_AND_ASSIGN(SchedulerStateMachine);
};

}  

#endif  
