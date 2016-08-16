/*
 *  Copyright (c) 2013 The WebM project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include <assert.h>
#include <stdio.h>

#include "./vpx_config.h"
#include "./vp9_rtcd.h"
#include "vp9/common/vp9_common.h"
#include "vpx/vpx_integer.h"
#include "vpx_ports/mem.h"
#include "vp9/common/vp9_convolve.h"
#include "vp9/common/mips/dspr2/vp9_common_dspr2.h"

#if HAVE_DSPR2
static void convolve_avg_vert_4_dspr2(const uint8_t *src,
                                      int32_t src_stride,
                                      uint8_t *dst,
                                      int32_t dst_stride,
                                      const int16_t *filter_y,
                                      int32_t w,
                                      int32_t h) {
  int32_t       x, y;
  const uint8_t *src_ptr;
  uint8_t       *dst_ptr;
  uint8_t       *cm = vp9_ff_cropTbl;
  uint32_t      vector4a = 64;
  uint32_t      load1, load2, load3, load4;
  uint32_t      p1, p2;
  uint32_t      n1, n2;
  uint32_t      scratch1, scratch2;
  uint32_t      store1, store2;
  int32_t       vector1b, vector2b, vector3b, vector4b;
  int32_t       Temp1, Temp2;

  vector1b = ((const int32_t *)filter_y)[0];
  vector2b = ((const int32_t *)filter_y)[1];
  vector3b = ((const int32_t *)filter_y)[2];
  vector4b = ((const int32_t *)filter_y)[3];

  src -= 3 * src_stride;

  for (y = h; y--;) {
    
    vp9_prefetch_store(dst + dst_stride);

    for (x = 0; x < w; x += 4) {
      src_ptr = src + x;
      dst_ptr = dst + x;

      __asm__ __volatile__ (
          "ulw              %[load1],     0(%[src_ptr])                   \n\t"
          "add              %[src_ptr],   %[src_ptr],     %[src_stride]   \n\t"
          "ulw              %[load2],     0(%[src_ptr])                   \n\t"
          "add              %[src_ptr],   %[src_ptr],     %[src_stride]   \n\t"
          "ulw              %[load3],     0(%[src_ptr])                   \n\t"
          "add              %[src_ptr],   %[src_ptr],     %[src_stride]   \n\t"
          "ulw              %[load4],     0(%[src_ptr])                   \n\t"

          "mtlo             %[vector4a],  $ac0                            \n\t"
          "mtlo             %[vector4a],  $ac1                            \n\t"
          "mtlo             %[vector4a],  $ac2                            \n\t"
          "mtlo             %[vector4a],  $ac3                            \n\t"
          "mthi             $zero,        $ac0                            \n\t"
          "mthi             $zero,        $ac1                            \n\t"
          "mthi             $zero,        $ac2                            \n\t"
          "mthi             $zero,        $ac3                            \n\t"

          "preceu.ph.qbr    %[scratch1],  %[load1]                        \n\t"
          "preceu.ph.qbr    %[p1],        %[load2]                        \n\t"
          "precrq.ph.w      %[n1],        %[p1],          %[scratch1]     \n\t" 
          "append           %[p1],        %[scratch1],    16              \n\t" 
          "preceu.ph.qbr    %[scratch2],  %[load3]                        \n\t"
          "preceu.ph.qbr    %[p2],        %[load4]                        \n\t"
          "precrq.ph.w      %[n2],        %[p2],          %[scratch2]     \n\t" 
          "append           %[p2],        %[scratch2],    16              \n\t" 

          "dpa.w.ph         $ac0,         %[p1],          %[vector1b]     \n\t"
          "dpa.w.ph         $ac0,         %[p2],          %[vector2b]     \n\t"
          "dpa.w.ph         $ac1,         %[n1],          %[vector1b]     \n\t"
          "dpa.w.ph         $ac1,         %[n2],          %[vector2b]     \n\t"

          "preceu.ph.qbl    %[scratch1],  %[load1]                        \n\t"
          "preceu.ph.qbl    %[p1],        %[load2]                        \n\t"
          "precrq.ph.w      %[n1],        %[p1],          %[scratch1]     \n\t" 
          "append           %[p1],        %[scratch1],    16              \n\t" 
          "preceu.ph.qbl    %[scratch2],  %[load3]                        \n\t"
          "preceu.ph.qbl    %[p2],        %[load4]                        \n\t"
          "precrq.ph.w      %[n2],        %[p2],          %[scratch2]     \n\t" 
          "append           %[p2],        %[scratch2],    16              \n\t" 

          "dpa.w.ph         $ac2,         %[p1],          %[vector1b]     \n\t"
          "dpa.w.ph         $ac2,         %[p2],          %[vector2b]     \n\t"
          "dpa.w.ph         $ac3,         %[n1],          %[vector1b]     \n\t"
          "dpa.w.ph         $ac3,         %[n2],          %[vector2b]     \n\t"

          "add              %[src_ptr],   %[src_ptr],     %[src_stride]   \n\t"
          "ulw              %[load1],     0(%[src_ptr])                   \n\t"
          "add              %[src_ptr],   %[src_ptr],     %[src_stride]   \n\t"
          "ulw              %[load2],     0(%[src_ptr])                   \n\t"
          "add              %[src_ptr],   %[src_ptr],     %[src_stride]   \n\t"
          "ulw              %[load3],     0(%[src_ptr])                   \n\t"
          "add              %[src_ptr],   %[src_ptr],     %[src_stride]   \n\t"
          "ulw              %[load4],     0(%[src_ptr])                   \n\t"

          "preceu.ph.qbr    %[scratch1],  %[load1]                        \n\t"
          "preceu.ph.qbr    %[p1],        %[load2]                        \n\t"
          "precrq.ph.w      %[n1],        %[p1],          %[scratch1]     \n\t" 
          "append           %[p1],        %[scratch1],    16              \n\t" 
          "preceu.ph.qbr    %[scratch2],  %[load3]                        \n\t"
          "preceu.ph.qbr    %[p2],        %[load4]                        \n\t"
          "precrq.ph.w      %[n2],        %[p2],          %[scratch2]     \n\t" 
          "append           %[p2],        %[scratch2],    16              \n\t" 

          "dpa.w.ph         $ac0,         %[p1],          %[vector3b]     \n\t"
          "dpa.w.ph         $ac0,         %[p2],          %[vector4b]     \n\t"
          "extp             %[Temp1],     $ac0,           31              \n\t"
          "dpa.w.ph         $ac1,         %[n1],          %[vector3b]     \n\t"
          "dpa.w.ph         $ac1,         %[n2],          %[vector4b]     \n\t"
          "extp             %[Temp2],     $ac1,           31              \n\t"

          "preceu.ph.qbl    %[scratch1],  %[load1]                        \n\t"
          "preceu.ph.qbl    %[p1],        %[load2]                        \n\t"
          "precrq.ph.w      %[n1],        %[p1],          %[scratch1]     \n\t" 
          "append           %[p1],        %[scratch1],    16              \n\t" 
          "lbu              %[scratch1],  0(%[dst_ptr])                   \n\t"
          "preceu.ph.qbl    %[scratch2],  %[load3]                        \n\t"
          "preceu.ph.qbl    %[p2],        %[load4]                        \n\t"
          "precrq.ph.w      %[n2],        %[p2],          %[scratch2]     \n\t" 
          "append           %[p2],        %[scratch2],    16              \n\t" 
          "lbu              %[scratch2],  1(%[dst_ptr])                   \n\t"

          "lbux             %[store1],    %[Temp1](%[cm])                 \n\t"
          "dpa.w.ph         $ac2,         %[p1],          %[vector3b]     \n\t"
          "dpa.w.ph         $ac2,         %[p2],          %[vector4b]     \n\t"
          "addqh_r.w        %[store1],    %[store1],      %[scratch1]     \n\t" 
          "extp             %[Temp1],     $ac2,           31              \n\t"

          "lbux             %[store2],    %[Temp2](%[cm])                 \n\t"
          "dpa.w.ph         $ac3,         %[n1],          %[vector3b]     \n\t"
          "dpa.w.ph         $ac3,         %[n2],          %[vector4b]     \n\t"
          "addqh_r.w        %[store2],    %[store2],      %[scratch2]     \n\t" 
          "extp             %[Temp2],     $ac3,           31              \n\t"
          "lbu              %[scratch1],  2(%[dst_ptr])                   \n\t"

          "sb               %[store1],    0(%[dst_ptr])                   \n\t"
          "sb               %[store2],    1(%[dst_ptr])                   \n\t"
          "lbu              %[scratch2],  3(%[dst_ptr])                   \n\t"

          "lbux             %[store1],    %[Temp1](%[cm])                 \n\t"
          "lbux             %[store2],    %[Temp2](%[cm])                 \n\t"
          "addqh_r.w        %[store1],    %[store1],      %[scratch1]     \n\t" 
          "addqh_r.w        %[store2],    %[store2],      %[scratch2]     \n\t" 

          "sb               %[store1],    2(%[dst_ptr])                   \n\t"
          "sb               %[store2],    3(%[dst_ptr])                   \n\t"

          : [load1] "=&r" (load1), [load2] "=&r" (load2),
            [load3] "=&r" (load3), [load4] "=&r" (load4),
            [p1] "=&r" (p1), [p2] "=&r" (p2), [n1] "=&r" (n1), [n2] "=&r" (n2),
            [scratch1] "=&r" (scratch1), [scratch2] "=&r" (scratch2),
            [Temp1] "=&r" (Temp1), [Temp2] "=&r" (Temp2),
            [store1] "=&r" (store1), [store2] "=&r" (store2),
            [src_ptr] "+r" (src_ptr)
          : [vector1b] "r" (vector1b), [vector2b] "r" (vector2b),
            [vector3b] "r" (vector3b), [vector4b] "r" (vector4b),
            [vector4a] "r" (vector4a),
            [src_stride] "r" (src_stride), [cm] "r" (cm), [dst_ptr] "r" (dst_ptr)
      );
    }

    
    src += src_stride;
    dst += dst_stride;
  }
}

static void convolve_avg_vert_64_dspr2(const uint8_t *src,
                                       int32_t src_stride,
                                       uint8_t *dst,
                                       int32_t dst_stride,
                                       const int16_t *filter_y,
                                       int32_t h) {
  int32_t       x, y;
  const uint8_t *src_ptr;
  uint8_t       *dst_ptr;
  uint8_t       *cm = vp9_ff_cropTbl;
  uint32_t      vector4a = 64;
  uint32_t      load1, load2, load3, load4;
  uint32_t      p1, p2;
  uint32_t      n1, n2;
  uint32_t      scratch1, scratch2;
  uint32_t      store1, store2;
  int32_t       vector1b, vector2b, vector3b, vector4b;
  int32_t       Temp1, Temp2;

  vector1b = ((const int32_t *)filter_y)[0];
  vector2b = ((const int32_t *)filter_y)[1];
  vector3b = ((const int32_t *)filter_y)[2];
  vector4b = ((const int32_t *)filter_y)[3];

  src -= 3 * src_stride;

  for (y = h; y--;) {
    
    vp9_prefetch_store(dst + dst_stride);
    vp9_prefetch_store(dst + dst_stride + 32);

    for (x = 0; x < 64; x += 4) {
      src_ptr = src + x;
      dst_ptr = dst + x;

      __asm__ __volatile__ (
          "ulw              %[load1],     0(%[src_ptr])                   \n\t"
          "add              %[src_ptr],   %[src_ptr],     %[src_stride]   \n\t"
          "ulw              %[load2],     0(%[src_ptr])                   \n\t"
          "add              %[src_ptr],   %[src_ptr],     %[src_stride]   \n\t"
          "ulw              %[load3],     0(%[src_ptr])                   \n\t"
          "add              %[src_ptr],   %[src_ptr],     %[src_stride]   \n\t"
          "ulw              %[load4],     0(%[src_ptr])                   \n\t"

          "mtlo             %[vector4a],  $ac0                            \n\t"
          "mtlo             %[vector4a],  $ac1                            \n\t"
          "mtlo             %[vector4a],  $ac2                            \n\t"
          "mtlo             %[vector4a],  $ac3                            \n\t"
          "mthi             $zero,        $ac0                            \n\t"
          "mthi             $zero,        $ac1                            \n\t"
          "mthi             $zero,        $ac2                            \n\t"
          "mthi             $zero,        $ac3                            \n\t"

          "preceu.ph.qbr    %[scratch1],  %[load1]                        \n\t"
          "preceu.ph.qbr    %[p1],        %[load2]                        \n\t"
          "precrq.ph.w      %[n1],        %[p1],          %[scratch1]     \n\t" 
          "append           %[p1],        %[scratch1],    16              \n\t" 
          "preceu.ph.qbr    %[scratch2],  %[load3]                        \n\t"
          "preceu.ph.qbr    %[p2],        %[load4]                        \n\t"
          "precrq.ph.w      %[n2],        %[p2],          %[scratch2]     \n\t" 
          "append           %[p2],        %[scratch2],    16              \n\t" 

          "dpa.w.ph         $ac0,         %[p1],          %[vector1b]     \n\t"
          "dpa.w.ph         $ac0,         %[p2],          %[vector2b]     \n\t"
          "dpa.w.ph         $ac1,         %[n1],          %[vector1b]     \n\t"
          "dpa.w.ph         $ac1,         %[n2],          %[vector2b]     \n\t"

          "preceu.ph.qbl    %[scratch1],  %[load1]                        \n\t"
          "preceu.ph.qbl    %[p1],        %[load2]                        \n\t"
          "precrq.ph.w      %[n1],        %[p1],          %[scratch1]     \n\t" 
          "append           %[p1],        %[scratch1],    16              \n\t" 
          "preceu.ph.qbl    %[scratch2],  %[load3]                        \n\t"
          "preceu.ph.qbl    %[p2],        %[load4]                        \n\t"
          "precrq.ph.w      %[n2],        %[p2],          %[scratch2]     \n\t" 
          "append           %[p2],        %[scratch2],    16              \n\t" 

          "dpa.w.ph         $ac2,         %[p1],          %[vector1b]     \n\t"
          "dpa.w.ph         $ac2,         %[p2],          %[vector2b]     \n\t"
          "dpa.w.ph         $ac3,         %[n1],          %[vector1b]     \n\t"
          "dpa.w.ph         $ac3,         %[n2],          %[vector2b]     \n\t"

          "add              %[src_ptr],   %[src_ptr],     %[src_stride]   \n\t"
          "ulw              %[load1],     0(%[src_ptr])                   \n\t"
          "add              %[src_ptr],   %[src_ptr],     %[src_stride]   \n\t"
          "ulw              %[load2],     0(%[src_ptr])                   \n\t"
          "add              %[src_ptr],   %[src_ptr],     %[src_stride]   \n\t"
          "ulw              %[load3],     0(%[src_ptr])                   \n\t"
          "add              %[src_ptr],   %[src_ptr],     %[src_stride]   \n\t"
          "ulw              %[load4],     0(%[src_ptr])                   \n\t"

          "preceu.ph.qbr    %[scratch1],  %[load1]                        \n\t"
          "preceu.ph.qbr    %[p1],        %[load2]                        \n\t"
          "precrq.ph.w      %[n1],        %[p1],          %[scratch1]     \n\t" 
          "append           %[p1],        %[scratch1],    16              \n\t" 
          "preceu.ph.qbr    %[scratch2],  %[load3]                        \n\t"
          "preceu.ph.qbr    %[p2],        %[load4]                        \n\t"
          "precrq.ph.w      %[n2],        %[p2],          %[scratch2]     \n\t" 
          "append           %[p2],        %[scratch2],    16              \n\t" 

          "dpa.w.ph         $ac0,         %[p1],          %[vector3b]     \n\t"
          "dpa.w.ph         $ac0,         %[p2],          %[vector4b]     \n\t"
          "extp             %[Temp1],     $ac0,           31              \n\t"
          "dpa.w.ph         $ac1,         %[n1],          %[vector3b]     \n\t"
          "dpa.w.ph         $ac1,         %[n2],          %[vector4b]     \n\t"
          "extp             %[Temp2],     $ac1,           31              \n\t"

          "preceu.ph.qbl    %[scratch1],  %[load1]                        \n\t"
          "preceu.ph.qbl    %[p1],        %[load2]                        \n\t"
          "precrq.ph.w      %[n1],        %[p1],          %[scratch1]     \n\t" 
          "append           %[p1],        %[scratch1],    16              \n\t" 
          "lbu              %[scratch1],  0(%[dst_ptr])                   \n\t"
          "preceu.ph.qbl    %[scratch2],  %[load3]                        \n\t"
          "preceu.ph.qbl    %[p2],        %[load4]                        \n\t"
          "precrq.ph.w      %[n2],        %[p2],          %[scratch2]     \n\t" 
          "append           %[p2],        %[scratch2],    16              \n\t" 
          "lbu              %[scratch2],  1(%[dst_ptr])                   \n\t"

          "lbux             %[store1],    %[Temp1](%[cm])                 \n\t"
          "dpa.w.ph         $ac2,         %[p1],          %[vector3b]     \n\t"
          "dpa.w.ph         $ac2,         %[p2],          %[vector4b]     \n\t"
          "addqh_r.w        %[store1],    %[store1],      %[scratch1]     \n\t" 
          "extp             %[Temp1],     $ac2,           31              \n\t"

          "lbux             %[store2],    %[Temp2](%[cm])                 \n\t"
          "dpa.w.ph         $ac3,         %[n1],          %[vector3b]     \n\t"
          "dpa.w.ph         $ac3,         %[n2],          %[vector4b]     \n\t"
          "addqh_r.w        %[store2],    %[store2],      %[scratch2]     \n\t" 
          "extp             %[Temp2],     $ac3,           31              \n\t"
          "lbu              %[scratch1],  2(%[dst_ptr])                   \n\t"

          "sb               %[store1],    0(%[dst_ptr])                   \n\t"
          "sb               %[store2],    1(%[dst_ptr])                   \n\t"
          "lbu              %[scratch2],  3(%[dst_ptr])                   \n\t"

          "lbux             %[store1],    %[Temp1](%[cm])                 \n\t"
          "lbux             %[store2],    %[Temp2](%[cm])                 \n\t"
          "addqh_r.w        %[store1],    %[store1],      %[scratch1]     \n\t" 
          "addqh_r.w        %[store2],    %[store2],      %[scratch2]     \n\t" 

          "sb               %[store1],    2(%[dst_ptr])                   \n\t"
          "sb               %[store2],    3(%[dst_ptr])                   \n\t"

          : [load1] "=&r" (load1), [load2] "=&r" (load2),
            [load3] "=&r" (load3), [load4] "=&r" (load4),
            [p1] "=&r" (p1), [p2] "=&r" (p2), [n1] "=&r" (n1), [n2] "=&r" (n2),
            [scratch1] "=&r" (scratch1), [scratch2] "=&r" (scratch2),
            [Temp1] "=&r" (Temp1), [Temp2] "=&r" (Temp2),
            [store1] "=&r" (store1), [store2] "=&r" (store2),
            [src_ptr] "+r" (src_ptr)
          : [vector1b] "r" (vector1b), [vector2b] "r" (vector2b),
            [vector3b] "r" (vector3b), [vector4b] "r" (vector4b),
            [vector4a] "r" (vector4a),
            [src_stride] "r" (src_stride), [cm] "r" (cm), [dst_ptr] "r" (dst_ptr)
      );
    }

    
    src += src_stride;
    dst += dst_stride;
  }
}

void vp9_convolve8_avg_vert_dspr2(const uint8_t *src, ptrdiff_t src_stride,
                                  uint8_t *dst, ptrdiff_t dst_stride,
                                  const int16_t *filter_x, int x_step_q4,
                                  const int16_t *filter_y, int y_step_q4,
                                  int w, int h) {
  if (((const int32_t *)filter_y)[1] == 0x800000) {
    vp9_convolve_avg(src, src_stride,
                     dst, dst_stride,
                     filter_x, x_step_q4,
                     filter_y, y_step_q4,
                     w, h);
  } else if (((const int32_t *)filter_y)[0] == 0) {
    vp9_convolve2_avg_vert_dspr2(src, src_stride,
                                 dst, dst_stride,
                                 filter_x, x_step_q4,
                                 filter_y, y_step_q4,
                                 w, h);
  } else {
    if (16 == y_step_q4) {
      uint32_t pos = 38;

      
      __asm__ __volatile__ (
        "wrdsp      %[pos],     1           \n\t"
        :
        : [pos] "r" (pos)
      );

      vp9_prefetch_store(dst);

      switch (w) {
        case 4:
        case 8:
        case 16:
        case 32:
          convolve_avg_vert_4_dspr2(src, src_stride,
                                    dst, dst_stride,
                                    filter_y, w, h);
          break;
        case 64:
          vp9_prefetch_store(dst + 32);
          convolve_avg_vert_64_dspr2(src, src_stride,
                                     dst, dst_stride,
                                     filter_y, h);
          break;
        default:
          vp9_convolve8_avg_vert_c(src, src_stride,
                                   dst, dst_stride,
                                   filter_x, x_step_q4,
                                   filter_y, y_step_q4,
                                   w, h);
          break;
      }
    } else {
      vp9_convolve8_avg_vert_c(src, src_stride,
                               dst, dst_stride,
                               filter_x, x_step_q4,
                               filter_y, y_step_q4,
                               w, h);
    }
  }
}

void vp9_convolve8_avg_dspr2(const uint8_t *src, ptrdiff_t src_stride,
                             uint8_t *dst, ptrdiff_t dst_stride,
                             const int16_t *filter_x, int x_step_q4,
                             const int16_t *filter_y, int y_step_q4,
                             int w, int h) {
  
  DECLARE_ALIGNED_ARRAY(32, uint8_t, temp, 64 * 135);
  int32_t intermediate_height = ((h * y_step_q4) >> 4) + 7;

  assert(w <= 64);
  assert(h <= 64);

  if (intermediate_height < h)
    intermediate_height = h;

  if (x_step_q4 != 16 || y_step_q4 != 16)
    return vp9_convolve8_avg_c(src, src_stride,
                               dst, dst_stride,
                               filter_x, x_step_q4,
                               filter_y, y_step_q4,
                               w, h);

  vp9_convolve8_horiz(src - (src_stride * 3), src_stride,
                      temp, 64,
                      filter_x, x_step_q4,
                      filter_y, y_step_q4,
                      w, intermediate_height);

  vp9_convolve8_avg_vert(temp + 64 * 3, 64,
                         dst, dst_stride,
                         filter_x, x_step_q4,
                         filter_y, y_step_q4,
                         w, h);
}

void vp9_convolve_avg_dspr2(const uint8_t *src, ptrdiff_t src_stride,
                            uint8_t *dst, ptrdiff_t dst_stride,
                            const int16_t *filter_x, int filter_x_stride,
                            const int16_t *filter_y, int filter_y_stride,
                            int w, int h) {
  int x, y;
  uint32_t tp1, tp2, tn1;
  uint32_t tp3, tp4, tn2;

  
  vp9_prefetch_load(src);
  vp9_prefetch_load(src + 32);
  vp9_prefetch_store(dst);

  switch (w) {
    case 4:
      
      for (y = h; y--; ) {
        vp9_prefetch_load(src + src_stride);
        vp9_prefetch_load(src + src_stride + 32);
        vp9_prefetch_store(dst + dst_stride);

        __asm__ __volatile__ (
            "ulw              %[tp1],         0(%[src])      \n\t"
            "ulw              %[tp2],         0(%[dst])      \n\t"
            "adduh_r.qb       %[tn1], %[tp2], %[tp1]         \n\t"  
            "sw               %[tn1],         0(%[dst])      \n\t"  

            : [tn1] "=&r" (tn1), [tp1] "=&r" (tp1),
              [tp2] "=&r" (tp2)
            : [src] "r" (src), [dst] "r" (dst)
        );

        src += src_stride;
        dst += dst_stride;
      }
      break;
    case 8:
      
      for (y = h; y--; ) {
        vp9_prefetch_load(src + src_stride);
        vp9_prefetch_load(src + src_stride + 32);
        vp9_prefetch_store(dst + dst_stride);

        __asm__ __volatile__ (
            "ulw              %[tp1],         0(%[src])      \n\t"
            "ulw              %[tp2],         0(%[dst])      \n\t"
            "ulw              %[tp3],         4(%[src])      \n\t"
            "ulw              %[tp4],         4(%[dst])      \n\t"
            "adduh_r.qb       %[tn1], %[tp2], %[tp1]         \n\t"  
            "sw               %[tn1],         0(%[dst])      \n\t"  
            "adduh_r.qb       %[tn2], %[tp3], %[tp4]         \n\t"  
            "sw               %[tn2],         4(%[dst])      \n\t"  

            : [tp1] "=&r" (tp1), [tp2] "=&r" (tp2),
              [tp3] "=&r" (tp3), [tp4] "=&r" (tp4),
              [tn1] "=&r" (tn1), [tn2] "=&r" (tn2)
            : [src] "r" (src), [dst] "r" (dst)
        );

        src += src_stride;
        dst += dst_stride;
      }
      break;
    case 16:
      
      for (y = h; y--; ) {
        vp9_prefetch_load(src + src_stride);
        vp9_prefetch_load(src + src_stride + 32);
        vp9_prefetch_store(dst + dst_stride);

        __asm__ __volatile__ (
            "ulw              %[tp1],         0(%[src])      \n\t"
            "ulw              %[tp2],         0(%[dst])      \n\t"
            "ulw              %[tp3],         4(%[src])      \n\t"
            "ulw              %[tp4],         4(%[dst])      \n\t"
            "adduh_r.qb       %[tn1], %[tp2], %[tp1]         \n\t"  
            "ulw              %[tp1],         8(%[src])      \n\t"
            "ulw              %[tp2],         8(%[dst])      \n\t"
            "sw               %[tn1],         0(%[dst])      \n\t"  
            "adduh_r.qb       %[tn2], %[tp3], %[tp4]         \n\t"  
            "sw               %[tn2],         4(%[dst])      \n\t"  
            "ulw              %[tp3],         12(%[src])     \n\t"
            "ulw              %[tp4],         12(%[dst])     \n\t"
            "adduh_r.qb       %[tn1], %[tp2], %[tp1]         \n\t"  
            "sw               %[tn1],         8(%[dst])      \n\t"  
            "adduh_r.qb       %[tn2], %[tp3], %[tp4]         \n\t"  
            "sw               %[tn2],         12(%[dst])     \n\t"  

            : [tp1] "=&r" (tp1), [tp2] "=&r" (tp2),
              [tp3] "=&r" (tp3), [tp4] "=&r" (tp4),
              [tn1] "=&r" (tn1), [tn2] "=&r" (tn2)
            : [src] "r" (src), [dst] "r" (dst)
        );

        src += src_stride;
        dst += dst_stride;
      }
      break;
    case 32:
      
      for (y = h; y--; ) {
        vp9_prefetch_load(src + src_stride);
        vp9_prefetch_load(src + src_stride + 32);
        vp9_prefetch_store(dst + dst_stride);

        __asm__ __volatile__ (
            "ulw              %[tp1],         0(%[src])      \n\t"
            "ulw              %[tp2],         0(%[dst])      \n\t"
            "ulw              %[tp3],         4(%[src])      \n\t"
            "ulw              %[tp4],         4(%[dst])      \n\t"
            "adduh_r.qb       %[tn1], %[tp2], %[tp1]         \n\t"  
            "ulw              %[tp1],         8(%[src])      \n\t"
            "ulw              %[tp2],         8(%[dst])      \n\t"
            "sw               %[tn1],         0(%[dst])      \n\t"  
            "adduh_r.qb       %[tn2], %[tp3], %[tp4]         \n\t"  
            "sw               %[tn2],         4(%[dst])      \n\t"  
            "ulw              %[tp3],         12(%[src])     \n\t"
            "ulw              %[tp4],         12(%[dst])     \n\t"
            "adduh_r.qb       %[tn1], %[tp2], %[tp1]         \n\t"  
            "ulw              %[tp1],         16(%[src])     \n\t"
            "ulw              %[tp2],         16(%[dst])     \n\t"
            "sw               %[tn1],         8(%[dst])      \n\t"  
            "adduh_r.qb       %[tn2], %[tp3], %[tp4]         \n\t"  
            "sw               %[tn2],         12(%[dst])     \n\t"  
            "ulw              %[tp3],         20(%[src])     \n\t"
            "ulw              %[tp4],         20(%[dst])     \n\t"
            "adduh_r.qb       %[tn1], %[tp2], %[tp1]         \n\t"  
            "ulw              %[tp1],         24(%[src])     \n\t"
            "ulw              %[tp2],         24(%[dst])     \n\t"
            "sw               %[tn1],         16(%[dst])     \n\t"  
            "adduh_r.qb       %[tn2], %[tp3], %[tp4]         \n\t"  
            "sw               %[tn2],         20(%[dst])     \n\t"  
            "ulw              %[tp3],         28(%[src])     \n\t"
            "ulw              %[tp4],         28(%[dst])     \n\t"
            "adduh_r.qb       %[tn1], %[tp2], %[tp1]         \n\t"  
            "sw               %[tn1],         24(%[dst])     \n\t"  
            "adduh_r.qb       %[tn2], %[tp3], %[tp4]         \n\t"  
            "sw               %[tn2],         28(%[dst])     \n\t"  

            : [tp1] "=&r" (tp1), [tp2] "=&r" (tp2),
              [tp3] "=&r" (tp3), [tp4] "=&r" (tp4),
              [tn1] "=&r" (tn1), [tn2] "=&r" (tn2)
            : [src] "r" (src), [dst] "r" (dst)
        );

        src += src_stride;
        dst += dst_stride;
      }
      break;
    case 64:
      vp9_prefetch_load(src + 64);
      vp9_prefetch_store(dst + 32);

      
      for (y = h; y--; ) {
        vp9_prefetch_load(src + src_stride);
        vp9_prefetch_load(src + src_stride + 32);
        vp9_prefetch_load(src + src_stride + 64);
        vp9_prefetch_store(dst + dst_stride);
        vp9_prefetch_store(dst + dst_stride + 32);

        __asm__ __volatile__ (
            "ulw              %[tp1],         0(%[src])      \n\t"
            "ulw              %[tp2],         0(%[dst])      \n\t"
            "ulw              %[tp3],         4(%[src])      \n\t"
            "ulw              %[tp4],         4(%[dst])      \n\t"
            "adduh_r.qb       %[tn1], %[tp2], %[tp1]         \n\t"  
            "ulw              %[tp1],         8(%[src])      \n\t"
            "ulw              %[tp2],         8(%[dst])      \n\t"
            "sw               %[tn1],         0(%[dst])      \n\t"  
            "adduh_r.qb       %[tn2], %[tp3], %[tp4]         \n\t"  
            "sw               %[tn2],         4(%[dst])      \n\t"  
            "ulw              %[tp3],         12(%[src])     \n\t"
            "ulw              %[tp4],         12(%[dst])     \n\t"
            "adduh_r.qb       %[tn1], %[tp2], %[tp1]         \n\t"  
            "ulw              %[tp1],         16(%[src])     \n\t"
            "ulw              %[tp2],         16(%[dst])     \n\t"
            "sw               %[tn1],         8(%[dst])      \n\t"  
            "adduh_r.qb       %[tn2], %[tp3], %[tp4]         \n\t"  
            "sw               %[tn2],         12(%[dst])     \n\t"  
            "ulw              %[tp3],         20(%[src])     \n\t"
            "ulw              %[tp4],         20(%[dst])     \n\t"
            "adduh_r.qb       %[tn1], %[tp2], %[tp1]         \n\t"  
            "ulw              %[tp1],         24(%[src])     \n\t"
            "ulw              %[tp2],         24(%[dst])     \n\t"
            "sw               %[tn1],         16(%[dst])     \n\t"  
            "adduh_r.qb       %[tn2], %[tp3], %[tp4]         \n\t"  
            "sw               %[tn2],         20(%[dst])     \n\t"  
            "ulw              %[tp3],         28(%[src])     \n\t"
            "ulw              %[tp4],         28(%[dst])     \n\t"
            "adduh_r.qb       %[tn1], %[tp2], %[tp1]         \n\t"  
            "ulw              %[tp1],         32(%[src])     \n\t"
            "ulw              %[tp2],         32(%[dst])     \n\t"
            "sw               %[tn1],         24(%[dst])     \n\t"  
            "adduh_r.qb       %[tn2], %[tp3], %[tp4]         \n\t"  
            "sw               %[tn2],         28(%[dst])     \n\t"  
            "ulw              %[tp3],         36(%[src])     \n\t"
            "ulw              %[tp4],         36(%[dst])     \n\t"
            "adduh_r.qb       %[tn1], %[tp2], %[tp1]         \n\t"  
            "ulw              %[tp1],         40(%[src])     \n\t"
            "ulw              %[tp2],         40(%[dst])     \n\t"
            "sw               %[tn1],         32(%[dst])     \n\t"  
            "adduh_r.qb       %[tn2], %[tp3], %[tp4]         \n\t"  
            "sw               %[tn2],         36(%[dst])     \n\t"  
            "ulw              %[tp3],         44(%[src])     \n\t"
            "ulw              %[tp4],         44(%[dst])     \n\t"
            "adduh_r.qb       %[tn1], %[tp2], %[tp1]         \n\t"  
            "ulw              %[tp1],         48(%[src])     \n\t"
            "ulw              %[tp2],         48(%[dst])     \n\t"
            "sw               %[tn1],         40(%[dst])     \n\t"  
            "adduh_r.qb       %[tn2], %[tp3], %[tp4]         \n\t"  
            "sw               %[tn2],         44(%[dst])     \n\t"  
            "ulw              %[tp3],         52(%[src])     \n\t"
            "ulw              %[tp4],         52(%[dst])     \n\t"
            "adduh_r.qb       %[tn1], %[tp2], %[tp1]         \n\t"  
            "ulw              %[tp1],         56(%[src])     \n\t"
            "ulw              %[tp2],         56(%[dst])     \n\t"
            "sw               %[tn1],         48(%[dst])     \n\t"  
            "adduh_r.qb       %[tn2], %[tp3], %[tp4]         \n\t"  
            "sw               %[tn2],         52(%[dst])     \n\t"  
            "ulw              %[tp3],         60(%[src])     \n\t"
            "ulw              %[tp4],         60(%[dst])     \n\t"
            "adduh_r.qb       %[tn1], %[tp2], %[tp1]         \n\t"  
            "sw               %[tn1],         56(%[dst])     \n\t"  
            "adduh_r.qb       %[tn2], %[tp3], %[tp4]         \n\t"  
            "sw               %[tn2],         60(%[dst])     \n\t"  

            : [tp1] "=&r" (tp1), [tp2] "=&r" (tp2),
              [tp3] "=&r" (tp3), [tp4] "=&r" (tp4),
              [tn1] "=&r" (tn1), [tn2] "=&r" (tn2)
            : [src] "r" (src), [dst] "r" (dst)
        );

        src += src_stride;
        dst += dst_stride;
      }
      break;
    default:
      for (y = h; y > 0; --y) {
        for (x = 0; x < w; ++x) {
          dst[x] = (dst[x] + src[x] + 1) >> 1;
        }

        src += src_stride;
        dst += dst_stride;
      }
      break;
  }
}
#endif