// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDERER_HOST_INPUT_MOTION_EVENT_ANDROID_H_
#define CONTENT_BROWSER_RENDERER_HOST_INPUT_MOTION_EVENT_ANDROID_H_

#include <jni.h>

#include "base/android/scoped_java_ref.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "content/common/content_export.h"
#include "ui/events/gesture_detection/motion_event.h"
#include "ui/gfx/geometry/point_f.h"

namespace content {

class CONTENT_EXPORT MotionEventAndroid : public ui::MotionEvent {
 public:
  
  
  MotionEventAndroid(float pix_to_dip,
                     JNIEnv* env,
                     jobject event,
                     jlong time_ms,
                     jint android_action,
                     jint pointer_count,
                     jint history_size,
                     jint action_index,
                     jfloat pos_x_0_pixels,
                     jfloat pos_y_0_pixels,
                     jfloat pos_x_1_pixels,
                     jfloat pos_y_1_pixels,
                     jint pointer_id_0,
                     jint pointer_id_1,
                     jfloat touch_major_0_pixels,
                     jfloat touch_major_1_pixels,
                     jfloat touch_minor_0_pixels,
                     jfloat touch_minor_1_pixels,
                     jfloat orientation_0_rad,
                     jfloat orientation_1_rad,
                     jfloat raw_pos_x_pixels,
                     jfloat raw_pos_y_pixels,
                     jint android_tool_type_0,
                     jint android_tool_type_1,
                     jint android_button_state,
                     jint meta_state);
  virtual ~MotionEventAndroid();

  
  virtual int GetId() const OVERRIDE;
  virtual Action GetAction() const OVERRIDE;
  virtual int GetActionIndex() const OVERRIDE;
  virtual size_t GetPointerCount() const OVERRIDE;
  virtual int GetPointerId(size_t pointer_index) const OVERRIDE;
  virtual float GetX(size_t pointer_index) const OVERRIDE;
  virtual float GetY(size_t pointer_index) const OVERRIDE;
  virtual float GetRawX(size_t pointer_index) const OVERRIDE;
  virtual float GetRawY(size_t pointer_index) const OVERRIDE;
  virtual float GetTouchMajor(size_t pointer_index) const OVERRIDE;
  virtual float GetTouchMinor(size_t pointer_index) const OVERRIDE;
  virtual float GetOrientation(size_t pointer_index) const OVERRIDE;
  virtual float GetPressure(size_t pointer_index) const OVERRIDE;
  virtual base::TimeTicks GetEventTime() const OVERRIDE;
  virtual size_t GetHistorySize() const OVERRIDE;
  virtual base::TimeTicks GetHistoricalEventTime(
      size_t historical_index) const OVERRIDE;
  virtual float GetHistoricalTouchMajor(size_t pointer_index,
                                        size_t historical_index) const OVERRIDE;
  virtual float GetHistoricalX(size_t pointer_index,
                               size_t historical_index) const OVERRIDE;
  virtual float GetHistoricalY(size_t pointer_index,
                               size_t historical_index) const OVERRIDE;
  virtual ToolType GetToolType(size_t pointer_index) const OVERRIDE;
  virtual int GetButtonState() const OVERRIDE;
  virtual int GetFlags() const OVERRIDE;
  virtual scoped_ptr<MotionEvent> Clone() const OVERRIDE;
  virtual scoped_ptr<MotionEvent> Cancel() const OVERRIDE;

  
  base::TimeTicks GetDownTime() const;

  static bool RegisterMotionEventAndroid(JNIEnv* env);

  static base::android::ScopedJavaLocalRef<jobject> Obtain(
      const MotionEventAndroid& event);
  static base::android::ScopedJavaLocalRef<jobject> Obtain(
      base::TimeTicks down_time,
      base::TimeTicks event_time,
      Action action,
      float x_pixels,
      float y_pixels);

 private:
  MotionEventAndroid();
  MotionEventAndroid(float pix_to_dip, JNIEnv* env, jobject event);
  MotionEventAndroid(const MotionEventAndroid&);
  MotionEventAndroid& operator=(const MotionEventAndroid&);

  float ToDips(float pixels) const;
  gfx::PointF ToDips(const gfx::PointF& pixels) const;

  
  
  
  enum { MAX_POINTERS_TO_CACHE = 2 };

  
  base::android::ScopedJavaGlobalRef<jobject> event_;

  base::TimeTicks cached_time_;
  Action cached_action_;
  size_t cached_pointer_count_;
  size_t cached_history_size_;
  int cached_action_index_;
  gfx::PointF cached_positions_[MAX_POINTERS_TO_CACHE];
  int cached_pointer_ids_[MAX_POINTERS_TO_CACHE];
  float cached_touch_majors_[MAX_POINTERS_TO_CACHE];
  float cached_touch_minors_[MAX_POINTERS_TO_CACHE];
  float cached_orientations_[MAX_POINTERS_TO_CACHE];
  gfx::Vector2dF cached_raw_position_offset_;
  ToolType cached_tool_types_[MAX_POINTERS_TO_CACHE];
  int cached_button_state_;
  int cached_flags_;

  
  
  const float pix_to_dip_;

  
  
  bool should_recycle_;
};

}  

#endif  
