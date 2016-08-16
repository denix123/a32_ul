/*
 *  Copyright (c) 2010 The WebM project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include <math.h>
#include <limits.h>

#include "vp9/common/vp9_alloccommon.h"
#include "vp9/common/vp9_onyxc_int.h"
#include "vp9/common/vp9_quant_common.h"
#include "vp9/common/vp9_reconinter.h"
#include "vp9/common/vp9_systemdependent.h"
#include "vp9/encoder/vp9_extend.h"
#include "vp9/encoder/vp9_firstpass.h"
#include "vp9/encoder/vp9_mcomp.h"
#include "vp9/encoder/vp9_onyx_int.h"
#include "vp9/encoder/vp9_quantize.h"
#include "vp9/encoder/vp9_ratectrl.h"
#include "vp9/encoder/vp9_segmentation.h"
#include "vpx_mem/vpx_mem.h"
#include "vpx_ports/vpx_timer.h"
#include "vpx_scale/vpx_scale.h"

#define ALT_REF_MC_ENABLED 1    

static void temporal_filter_predictors_mb_c(MACROBLOCKD *xd,
                                            uint8_t *y_mb_ptr,
                                            uint8_t *u_mb_ptr,
                                            uint8_t *v_mb_ptr,
                                            int stride,
                                            int uv_block_size,
                                            int mv_row,
                                            int mv_col,
                                            uint8_t *pred,
                                            struct scale_factors *scale,
                                            int x, int y) {
  const int which_mv = 0;
  const MV mv = { mv_row, mv_col };
  const InterpKernel *const kernel =
    vp9_get_interp_kernel(xd->mi[0]->mbmi.interp_filter);

  enum mv_precision mv_precision_uv;
  int uv_stride;
  if (uv_block_size == 8) {
    uv_stride = (stride + 1) >> 1;
    mv_precision_uv = MV_PRECISION_Q4;
  } else {
    uv_stride = stride;
    mv_precision_uv = MV_PRECISION_Q3;
  }

  vp9_build_inter_predictor(y_mb_ptr, stride,
                            &pred[0], 16,
                            &mv,
                            scale,
                            16, 16,
                            which_mv,
                            kernel, MV_PRECISION_Q3, x, y);

  vp9_build_inter_predictor(u_mb_ptr, uv_stride,
                            &pred[256], uv_block_size,
                            &mv,
                            scale,
                            uv_block_size, uv_block_size,
                            which_mv,
                            kernel, mv_precision_uv, x, y);

  vp9_build_inter_predictor(v_mb_ptr, uv_stride,
                            &pred[512], uv_block_size,
                            &mv,
                            scale,
                            uv_block_size, uv_block_size,
                            which_mv,
                            kernel, mv_precision_uv, x, y);
}

void vp9_temporal_filter_apply_c(uint8_t *frame1,
                                 unsigned int stride,
                                 uint8_t *frame2,
                                 unsigned int block_size,
                                 int strength,
                                 int filter_weight,
                                 unsigned int *accumulator,
                                 uint16_t *count) {
  unsigned int i, j, k;
  int modifier;
  int byte = 0;

  for (i = 0, k = 0; i < block_size; i++) {
    for (j = 0; j < block_size; j++, k++) {
      int src_byte = frame1[byte];
      int pixel_value = *frame2++;

      modifier   = src_byte - pixel_value;
      
      
      
      modifier  *= modifier;
      modifier  *= 3;
      modifier  += 1 << (strength - 1);
      modifier >>= strength;

      if (modifier > 16)
        modifier = 16;

      modifier = 16 - modifier;
      modifier *= filter_weight;

      count[k] += modifier;
      accumulator[k] += modifier * pixel_value;

      byte++;
    }

    byte += stride - block_size;
  }
}

#if ALT_REF_MC_ENABLED

static int temporal_filter_find_matching_mb_c(VP9_COMP *cpi,
                                              uint8_t *arf_frame_buf,
                                              uint8_t *frame_ptr_buf,
                                              int stride) {
  MACROBLOCK *x = &cpi->mb;
  MACROBLOCKD* const xd = &x->e_mbd;
  int step_param;
  int sadpb = x->sadperbit16;
  int bestsme = INT_MAX;

  MV best_ref_mv1 = {0, 0};
  MV best_ref_mv1_full; 
  MV *ref_mv = &x->e_mbd.mi[0]->bmi[0].as_mv[0].as_mv;

  
  struct buf_2d src = x->plane[0].src;
  struct buf_2d pre = xd->plane[0].pre[0];

  best_ref_mv1_full.col = best_ref_mv1.col >> 3;
  best_ref_mv1_full.row = best_ref_mv1.row >> 3;

  
  x->plane[0].src.buf = arf_frame_buf;
  x->plane[0].src.stride = stride;
  xd->plane[0].pre[0].buf = frame_ptr_buf;
  xd->plane[0].pre[0].stride = stride;

  
  if (cpi->speed < 8)
    step_param = cpi->sf.reduce_first_step_size + ((cpi->speed > 5) ? 1 : 0);
  else
    step_param = cpi->sf.reduce_first_step_size + 2;
  step_param = MIN(step_param, (cpi->sf.max_step_search_steps - 2));

  
  
  vp9_hex_search(x, &best_ref_mv1_full, step_param, sadpb, 1,
                 &cpi->fn_ptr[BLOCK_16X16], 0, &best_ref_mv1, ref_mv);

  
  
  {
    int distortion;
    unsigned int sse;
    
    bestsme = cpi->find_fractional_mv_step(x, ref_mv,
                                           &best_ref_mv1,
                                           cpi->common.allow_high_precision_mv,
                                           x->errorperbit,
                                           &cpi->fn_ptr[BLOCK_16X16],
                                           0, cpi->sf.subpel_iters_per_step,
                                           NULL, NULL,
                                           &distortion, &sse);
  }

  
  x->plane[0].src = src;
  xd->plane[0].pre[0] = pre;

  return bestsme;
}
#endif

static void temporal_filter_iterate_c(VP9_COMP *cpi,
                                      int frame_count,
                                      int alt_ref_index,
                                      int strength,
                                      struct scale_factors *scale) {
  int byte;
  int frame;
  int mb_col, mb_row;
  unsigned int filter_weight;
  int mb_cols = cpi->common.mb_cols;
  int mb_rows = cpi->common.mb_rows;
  int mb_y_offset = 0;
  int mb_uv_offset = 0;
  DECLARE_ALIGNED_ARRAY(16, unsigned int, accumulator, 16 * 16 * 3);
  DECLARE_ALIGNED_ARRAY(16, uint16_t, count, 16 * 16 * 3);
  MACROBLOCKD *mbd = &cpi->mb.e_mbd;
  YV12_BUFFER_CONFIG *f = cpi->frames[alt_ref_index];
  uint8_t *dst1, *dst2;
  DECLARE_ALIGNED_ARRAY(16, uint8_t,  predictor, 16 * 16 * 3);
  const int mb_uv_height = 16 >> mbd->plane[1].subsampling_y;

  
  uint8_t* input_buffer[MAX_MB_PLANE];
  int i;

  
  assert(mbd->plane[1].subsampling_x == mbd->plane[1].subsampling_y);

  for (i = 0; i < MAX_MB_PLANE; i++)
    input_buffer[i] = mbd->plane[i].pre[0].buf;

  for (mb_row = 0; mb_row < mb_rows; mb_row++) {
#if ALT_REF_MC_ENABLED
    
    
    
    
    
    
    
    
    
    
    
    cpi->mb.mv_row_min = -((mb_row * 16) + (17 - 2 * VP9_INTERP_EXTEND));
    cpi->mb.mv_row_max = ((cpi->common.mb_rows - 1 - mb_row) * 16)
                         + (17 - 2 * VP9_INTERP_EXTEND);
#endif

    for (mb_col = 0; mb_col < mb_cols; mb_col++) {
      int i, j, k;
      int stride;

      vpx_memset(accumulator, 0, 16 * 16 * 3 * sizeof(accumulator[0]));
      vpx_memset(count, 0, 16 * 16 * 3 * sizeof(count[0]));

#if ALT_REF_MC_ENABLED
      cpi->mb.mv_col_min = -((mb_col * 16) + (17 - 2 * VP9_INTERP_EXTEND));
      cpi->mb.mv_col_max = ((cpi->common.mb_cols - 1 - mb_col) * 16)
                           + (17 - 2 * VP9_INTERP_EXTEND);
#endif

      for (frame = 0; frame < frame_count; frame++) {
        if (cpi->frames[frame] == NULL)
          continue;

        mbd->mi[0]->bmi[0].as_mv[0].as_mv.row = 0;
        mbd->mi[0]->bmi[0].as_mv[0].as_mv.col = 0;

        if (frame == alt_ref_index) {
          filter_weight = 2;
        } else {
          int err = 0;
#if ALT_REF_MC_ENABLED
#define THRESH_LOW   10000
#define THRESH_HIGH  20000

          
          err = temporal_filter_find_matching_mb_c
                (cpi,
                 cpi->frames[alt_ref_index]->y_buffer + mb_y_offset,
                 cpi->frames[frame]->y_buffer + mb_y_offset,
                 cpi->frames[frame]->y_stride);
#endif
          
          
          
          filter_weight = err < THRESH_LOW
                          ? 2 : err < THRESH_HIGH ? 1 : 0;
        }

        if (filter_weight != 0) {
          
          temporal_filter_predictors_mb_c
          (mbd,
           cpi->frames[frame]->y_buffer + mb_y_offset,
           cpi->frames[frame]->u_buffer + mb_uv_offset,
           cpi->frames[frame]->v_buffer + mb_uv_offset,
           cpi->frames[frame]->y_stride,
           mb_uv_height,
           mbd->mi[0]->bmi[0].as_mv[0].as_mv.row,
           mbd->mi[0]->bmi[0].as_mv[0].as_mv.col,
           predictor, scale,
           mb_col * 16, mb_row * 16);

          
          vp9_temporal_filter_apply(f->y_buffer + mb_y_offset, f->y_stride,
                                    predictor, 16, strength, filter_weight,
                                    accumulator, count);

          vp9_temporal_filter_apply(f->u_buffer + mb_uv_offset, f->uv_stride,
                                    predictor + 256, mb_uv_height, strength,
                                    filter_weight, accumulator + 256,
                                    count + 256);

          vp9_temporal_filter_apply(f->v_buffer + mb_uv_offset, f->uv_stride,
                                    predictor + 512, mb_uv_height, strength,
                                    filter_weight, accumulator + 512,
                                    count + 512);
        }
      }

      
      dst1 = cpi->alt_ref_buffer.y_buffer;
      stride = cpi->alt_ref_buffer.y_stride;
      byte = mb_y_offset;
      for (i = 0, k = 0; i < 16; i++) {
        for (j = 0; j < 16; j++, k++) {
          unsigned int pval = accumulator[k] + (count[k] >> 1);
          pval *= cpi->fixed_divide[count[k]];
          pval >>= 19;

          dst1[byte] = (uint8_t)pval;

          
          byte++;
        }

        byte += stride - 16;
      }

      dst1 = cpi->alt_ref_buffer.u_buffer;
      dst2 = cpi->alt_ref_buffer.v_buffer;
      stride = cpi->alt_ref_buffer.uv_stride;
      byte = mb_uv_offset;
      for (i = 0, k = 256; i < mb_uv_height; i++) {
        for (j = 0; j < mb_uv_height; j++, k++) {
          int m = k + 256;

          
          unsigned int pval = accumulator[k] + (count[k] >> 1);
          pval *= cpi->fixed_divide[count[k]];
          pval >>= 19;
          dst1[byte] = (uint8_t)pval;

          
          pval = accumulator[m] + (count[m] >> 1);
          pval *= cpi->fixed_divide[count[m]];
          pval >>= 19;
          dst2[byte] = (uint8_t)pval;

          
          byte++;
        }

        byte += stride - mb_uv_height;
      }

      mb_y_offset += 16;
      mb_uv_offset += mb_uv_height;
    }

    mb_y_offset += 16 * (f->y_stride - mb_cols);
    mb_uv_offset += mb_uv_height * (f->uv_stride - mb_cols);
  }

  
  for (i = 0; i < MAX_MB_PLANE; i++)
    mbd->plane[i].pre[0].buf = input_buffer[i];
}

void vp9_temporal_filter_prepare(VP9_COMP *cpi, int distance) {
  VP9_COMMON *const cm = &cpi->common;

  int frame = 0;

  int frames_to_blur_backward = 0;
  int frames_to_blur_forward = 0;
  int frames_to_blur = 0;
  int start_frame = 0;

  int strength = cpi->active_arnr_strength;
  int blur_type = cpi->oxcf.arnr_type;
  int max_frames = cpi->active_arnr_frames;

  const int num_frames_backward = distance;
  const int num_frames_forward = vp9_lookahead_depth(cpi->lookahead)
                               - (num_frames_backward + 1);
  struct scale_factors sf;

  switch (blur_type) {
    case 1:
      
      frames_to_blur_backward = num_frames_backward;

      if (frames_to_blur_backward >= max_frames)
        frames_to_blur_backward = max_frames - 1;

      frames_to_blur = frames_to_blur_backward + 1;
      break;

    case 2:
      
      frames_to_blur_forward = num_frames_forward;

      if (frames_to_blur_forward >= max_frames)
        frames_to_blur_forward = max_frames - 1;

      frames_to_blur = frames_to_blur_forward + 1;
      break;

    case 3:
    default:
      
      frames_to_blur_forward = num_frames_forward;
      frames_to_blur_backward = num_frames_backward;

      if (frames_to_blur_forward > frames_to_blur_backward)
        frames_to_blur_forward = frames_to_blur_backward;

      if (frames_to_blur_backward > frames_to_blur_forward)
        frames_to_blur_backward = frames_to_blur_forward;

      
      if (frames_to_blur_forward > (max_frames - 1) / 2)
        frames_to_blur_forward = ((max_frames - 1) / 2);

      if (frames_to_blur_backward > (max_frames / 2))
        frames_to_blur_backward = (max_frames / 2);

      frames_to_blur = frames_to_blur_backward + frames_to_blur_forward + 1;
      break;
  }

  start_frame = distance + frames_to_blur_forward;

#ifdef DEBUGFWG
  
  printf(
      "max:%d FBCK:%d FFWD:%d ftb:%d ftbbck:%d ftbfwd:%d sei:%d lasei:%d "
      "start:%d",
      max_frames, num_frames_backward, num_frames_forward, frames_to_blur,
      frames_to_blur_backward, frames_to_blur_forward, cpi->source_encode_index,
      cpi->last_alt_ref_sei, start_frame);
#endif

  
  vp9_setup_scale_factors_for_frame(&sf,
      get_frame_new_buffer(cm)->y_crop_width,
      get_frame_new_buffer(cm)->y_crop_height,
      cm->width, cm->height);

  
  vp9_zero(cpi->frames);
  for (frame = 0; frame < frames_to_blur; frame++) {
    int which_buffer = start_frame - frame;
    struct lookahead_entry *buf = vp9_lookahead_peek(cpi->lookahead,
                                                     which_buffer);
    cpi->frames[frames_to_blur - 1 - frame] = &buf->img;
  }

  temporal_filter_iterate_c(cpi, frames_to_blur, frames_to_blur_backward,
                            strength, &sf);
}

void vp9_configure_arnr_filter(VP9_COMP *cpi,
                               const unsigned int frames_to_arnr,
                               const int group_boost) {
  int half_gf_int;
  int frames_after_arf;
  int frames_bwd = cpi->oxcf.arnr_max_frames - 1;
  int frames_fwd = cpi->oxcf.arnr_max_frames - 1;
  int q;

  
  
  
  
  
  
  half_gf_int = cpi->rc.baseline_gf_interval >> 1;
  frames_after_arf = vp9_lookahead_depth(cpi->lookahead)
      - frames_to_arnr - 1;

  switch (cpi->oxcf.arnr_type) {
    case 1:  
      frames_fwd = 0;
      if (frames_bwd > half_gf_int)
        frames_bwd = half_gf_int;
      break;

    case 2:  
      if (frames_fwd > half_gf_int)
        frames_fwd = half_gf_int;
      if (frames_fwd > frames_after_arf)
        frames_fwd = frames_after_arf;
      frames_bwd = 0;
      break;

    case 3:  
    default:
      frames_fwd >>= 1;
      if (frames_fwd > frames_after_arf)
        frames_fwd = frames_after_arf;
      if (frames_fwd > half_gf_int)
        frames_fwd = half_gf_int;

      frames_bwd = frames_fwd;

      
      
      if (frames_bwd < half_gf_int)
        frames_bwd += (cpi->oxcf.arnr_max_frames + 1) & 0x1;
      break;
  }

  cpi->active_arnr_frames = frames_bwd + 1 + frames_fwd;

  
  if (cpi->common.current_video_frame > 1)
    q = ((int)vp9_convert_qindex_to_q(
        cpi->rc.avg_frame_qindex[INTER_FRAME]));
  else
    q = ((int)vp9_convert_qindex_to_q(
        cpi->rc.avg_frame_qindex[KEY_FRAME]));
  if (q > 16) {
    cpi->active_arnr_strength = cpi->oxcf.arnr_strength;
  } else {
    cpi->active_arnr_strength = cpi->oxcf.arnr_strength - ((16 - q) / 2);
    if (cpi->active_arnr_strength < 0)
      cpi->active_arnr_strength = 0;
  }

  
  if (cpi->active_arnr_frames > (group_boost / 150)) {
    cpi->active_arnr_frames = (group_boost / 150);
    cpi->active_arnr_frames += !(cpi->active_arnr_frames & 1);
  }
  if (cpi->active_arnr_strength > (group_boost / 300)) {
    cpi->active_arnr_strength = (group_boost / 300);
  }
}