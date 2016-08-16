/*
 *  Copyright (c) 2010 The WebM project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */


#ifndef VP9_ENCODER_VP9_SEGMENTATION_H_
#define VP9_ENCODER_VP9_SEGMENTATION_H_

#include "vp9/common/vp9_blockd.h"
#include "vp9/encoder/vp9_onyx_int.h"

#ifdef __cplusplus
extern "C" {
#endif

void vp9_enable_segmentation(struct segmentation *seg);
void vp9_disable_segmentation(struct segmentation *seg);

void vp9_disable_segfeature(struct segmentation *seg,
                            int segment_id,
                            SEG_LVL_FEATURES feature_id);
void vp9_clear_segdata(struct segmentation *seg,
                       int segment_id,
                       SEG_LVL_FEATURES feature_id);
void vp9_set_segmentation_map(VP9_COMP *cpi, unsigned char *segmentation_map);

void vp9_set_segment_data(struct segmentation *seg, signed char *feature_data,
                          unsigned char abs_delta);

void vp9_choose_segmap_coding_method(VP9_COMP *cpi);

void vp9_reset_segment_features(struct segmentation *seg);

#ifdef __cplusplus
}  
#endif

#endif  