/*
 *  Copyright (c) 2014 The WebM project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef VP9_ENCODER_VP9_SVC_LAYERCONTEXT_H_
#define VP9_ENCODER_VP9_SVC_LAYERCONTEXT_H_

#include "vpx/vpx_encoder.h"

#include "vp9/encoder/vp9_ratectrl.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  RATE_CONTROL rc;
  int target_bandwidth;
  int64_t starting_buffer_level;
  int64_t optimal_buffer_level;
  int64_t maximum_buffer_size;
  double framerate;
  int avg_frame_size;
  struct twopass_rc twopass;
  struct vpx_fixed_buf rc_twopass_stats_in;
  unsigned int current_video_frame_in_layer;
} LAYER_CONTEXT;

typedef struct {
  int spatial_layer_id;
  int temporal_layer_id;
  int number_spatial_layers;
  int number_temporal_layers;
  
  
  
  LAYER_CONTEXT layer_context[MAX(VPX_TS_MAX_LAYERS, VPX_SS_MAX_LAYERS)];
} SVC;

struct VP9_COMP;

void vp9_init_layer_context(struct VP9_COMP *const cpi);

void vp9_update_layer_context_change_config(struct VP9_COMP *const cpi,
                                            const int target_bandwidth);

void vp9_update_temporal_layer_framerate(struct VP9_COMP *const cpi);

void vp9_update_spatial_layer_framerate(struct VP9_COMP *const cpi,
                                        double framerate);

void vp9_restore_layer_context(struct VP9_COMP *const cpi);

void vp9_save_layer_context(struct VP9_COMP *const cpi);

void vp9_init_second_pass_spatial_svc(struct VP9_COMP *cpi);

void vp9_inc_frame_in_layer(SVC *svc);

#ifdef __cplusplus
}  
#endif

#endif  
