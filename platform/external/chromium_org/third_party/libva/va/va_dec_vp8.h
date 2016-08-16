/*
 * Copyright (c) 2007-2012 Intel Corporation. All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
 * IN NO EVENT SHALL INTEL AND/OR ITS SUPPLIERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


#ifndef VA_DEC_VP8_H
#define VA_DEC_VP8_H

#ifdef __cplusplus
extern "C" {
#endif


typedef struct _VABoolCoderContextVPX
{
    
    unsigned char range;
    
    unsigned char value;

    unsigned char count;
} VABoolCoderContextVPX;

typedef struct  _VAPictureParameterBufferVP8
{
    
    unsigned int frame_width;
    
    unsigned int frame_height;

    
    VASurfaceID last_ref_frame;
    
    VASurfaceID golden_ref_frame;
    
    VASurfaceID alt_ref_frame;
    
    VASurfaceID out_of_loop_frame;

    union {
        struct {
	    
            unsigned int key_frame			: 1; 
	    
            unsigned int version			: 3;
	    
            unsigned int segmentation_enabled		: 1;
	    
            unsigned int update_mb_segmentation_map	: 1;
	    
            unsigned int update_segment_feature_data	: 1;
	    
            unsigned int filter_type			: 1; 
	    
            unsigned int sharpness_level		: 3; 
	    
            unsigned int loop_filter_adj_enable		: 1; 
	    
            unsigned int mode_ref_lf_delta_update	: 1; 
	    
            unsigned int sign_bias_golden		: 1; 
	    
            unsigned int sign_bias_alternate		: 1; 
	    
            unsigned int mb_no_coeff_skip		: 1; 
	    
            unsigned int loop_filter_disable		: 1; 
        } bits;
        unsigned int value;
    } pic_fields;

    unsigned char mb_segment_tree_probs[3];

    
    unsigned char loop_filter_level[4];
    
    char loop_filter_deltas_ref_frame[4];
    
    char loop_filter_deltas_mode[4];

    
    unsigned char prob_skip_false;
    
    unsigned char prob_intra;
    
    unsigned char prob_last;
    
    unsigned char prob_gf;

    unsigned char y_mode_probs[4]; 
    unsigned char uv_mode_probs[3];
    unsigned char mv_probs[2][19];

    VABoolCoderContextVPX bool_coder_ctx;

} VAPictureParameterBufferVP8;

typedef struct  _VASliceParameterBufferVP8
{
    unsigned int slice_data_size;
    unsigned int slice_data_offset;
    unsigned int slice_data_flag; 
    unsigned int macroblock_offset;

    unsigned char num_of_partitions;
    unsigned int partition_size[9];
} VASliceParameterBufferVP8;

typedef struct _VAProbabilityDataBufferVP8
{
    unsigned char dct_coeff_probs[4][8][3][11];
} VAProbabilityDataBufferVP8;

typedef struct _VAIQMatrixBufferVP8
{
    unsigned short quantization_index[4][6];
} VAIQMatrixBufferVP8;


#ifdef __cplusplus
}
#endif

#endif 
