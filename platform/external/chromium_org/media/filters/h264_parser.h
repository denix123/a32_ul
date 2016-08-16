// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_FILTERS_H264_PARSER_H_
#define MEDIA_FILTERS_H264_PARSER_H_

#include <sys/types.h>

#include <map>
#include <vector>

#include "base/basictypes.h"
#include "media/base/media_export.h"
#include "media/base/ranges.h"
#include "media/filters/h264_bit_reader.h"

namespace media {

struct SubsampleEntry;

struct MEDIA_EXPORT H264NALU {
  H264NALU();

  enum Type {
    kUnspecified = 0,
    kNonIDRSlice = 1,
    kSliceDataA = 2,
    kSliceDataB = 3,
    kSliceDataC = 4,
    kIDRSlice = 5,
    kSEIMessage = 6,
    kSPS = 7,
    kPPS = 8,
    kAUD = 9,
    kEOSeq = 10,
    kEOStream = 11,
    kFiller = 12,
    kSPSExt = 13,
    kReserved14 = 14,
    kReserved15 = 15,
    kReserved16 = 16,
    kReserved17 = 17,
    kReserved18 = 18,
    kCodedSliceAux = 19,
    kCodedSliceExtension = 20,
  };

  
  
  const uint8* data;
  off_t size;  

  int nal_ref_idc;
  int nal_unit_type;
};

enum {
  kH264ScalingList4x4Length = 16,
  kH264ScalingList8x8Length = 64,
};

struct MEDIA_EXPORT H264SPS {
  H264SPS();

  enum H264ProfileIDC {
    kProfileIDCBaseline = 66,
    kProfileIDCConstrainedBaseline = kProfileIDCBaseline,
    kProfileIDCMain = 77,
    kProfileIDCHigh = 100,
  };

  enum AspectRatioIdc {
    kExtendedSar = 255,
  };

  enum {
    
    kBitRateScaleConstantTerm = 6,  
    kCPBSizeScaleConstantTerm = 4,  
    kDefaultInitialCPBRemovalDelayLength = 24,
    kDefaultDPBOutputDelayLength = 24,
    kDefaultTimeOffsetLength = 24,
  };

  int profile_idc;
  bool constraint_set0_flag;
  bool constraint_set1_flag;
  bool constraint_set2_flag;
  bool constraint_set3_flag;
  bool constraint_set4_flag;
  bool constraint_set5_flag;
  int level_idc;
  int seq_parameter_set_id;

  int chroma_format_idc;
  bool separate_colour_plane_flag;
  int bit_depth_luma_minus8;
  int bit_depth_chroma_minus8;
  bool qpprime_y_zero_transform_bypass_flag;

  bool seq_scaling_matrix_present_flag;
  int scaling_list4x4[6][kH264ScalingList4x4Length];
  int scaling_list8x8[6][kH264ScalingList8x8Length];

  int log2_max_frame_num_minus4;
  int pic_order_cnt_type;
  int log2_max_pic_order_cnt_lsb_minus4;
  bool delta_pic_order_always_zero_flag;
  int offset_for_non_ref_pic;
  int offset_for_top_to_bottom_field;
  int num_ref_frames_in_pic_order_cnt_cycle;
  int expected_delta_per_pic_order_cnt_cycle;  
  int offset_for_ref_frame[255];
  int max_num_ref_frames;
  bool gaps_in_frame_num_value_allowed_flag;
  int pic_width_in_mbs_minus1;
  int pic_height_in_map_units_minus1;
  bool frame_mbs_only_flag;
  bool mb_adaptive_frame_field_flag;
  bool direct_8x8_inference_flag;
  bool frame_cropping_flag;
  int frame_crop_left_offset;
  int frame_crop_right_offset;
  int frame_crop_top_offset;
  int frame_crop_bottom_offset;

  bool vui_parameters_present_flag;
  int sar_width;    
  int sar_height;   
  bool bitstream_restriction_flag;
  int max_num_reorder_frames;
  int max_dec_frame_buffering;
  bool timing_info_present_flag;
  int num_units_in_tick;
  int time_scale;
  bool fixed_frame_rate_flag;

  
  bool nal_hrd_parameters_present_flag;
  int cpb_cnt_minus1;
  int bit_rate_scale;
  int cpb_size_scale;
  int bit_rate_value_minus1[32];
  int cpb_size_value_minus1[32];
  bool cbr_flag[32];
  int initial_cpb_removal_delay_length_minus_1;
  int cpb_removal_delay_length_minus1;
  int dpb_output_delay_length_minus1;
  int time_offset_length;

  bool low_delay_hrd_flag;

  int chroma_array_type;
};

struct MEDIA_EXPORT H264PPS {
  H264PPS();

  int pic_parameter_set_id;
  int seq_parameter_set_id;
  bool entropy_coding_mode_flag;
  bool bottom_field_pic_order_in_frame_present_flag;
  int num_slice_groups_minus1;
  
  int num_ref_idx_l0_default_active_minus1;
  int num_ref_idx_l1_default_active_minus1;
  bool weighted_pred_flag;
  int weighted_bipred_idc;
  int pic_init_qp_minus26;
  int pic_init_qs_minus26;
  int chroma_qp_index_offset;
  bool deblocking_filter_control_present_flag;
  bool constrained_intra_pred_flag;
  bool redundant_pic_cnt_present_flag;
  bool transform_8x8_mode_flag;

  bool pic_scaling_matrix_present_flag;
  int scaling_list4x4[6][kH264ScalingList4x4Length];
  int scaling_list8x8[6][kH264ScalingList8x8Length];

  int second_chroma_qp_index_offset;
};

struct MEDIA_EXPORT H264ModificationOfPicNum {
  int modification_of_pic_nums_idc;
  union {
    int abs_diff_pic_num_minus1;
    int long_term_pic_num;
  };
};

struct MEDIA_EXPORT H264WeightingFactors {
  bool luma_weight_flag;
  bool chroma_weight_flag;
  int luma_weight[32];
  int luma_offset[32];
  int chroma_weight[32][2];
  int chroma_offset[32][2];
};

struct MEDIA_EXPORT H264DecRefPicMarking {
  int memory_mgmnt_control_operation;
  int difference_of_pic_nums_minus1;
  int long_term_pic_num;
  int long_term_frame_idx;
  int max_long_term_frame_idx_plus1;
};

struct MEDIA_EXPORT H264SliceHeader {
  H264SliceHeader();

  enum {
    kRefListSize = 32,
    kRefListModSize = kRefListSize
  };

  enum Type {
    kPSlice = 0,
    kBSlice = 1,
    kISlice = 2,
    kSPSlice = 3,
    kSISlice = 4,
  };

  bool IsPSlice() const;
  bool IsBSlice() const;
  bool IsISlice() const;
  bool IsSPSlice() const;
  bool IsSISlice() const;

  bool idr_pic_flag;       
  int nal_ref_idc;         
  const uint8* nalu_data;  
  off_t nalu_size;         
  off_t header_bit_size;   

  int first_mb_in_slice;
  int slice_type;
  int pic_parameter_set_id;
  int colour_plane_id;  
  int frame_num;
  bool field_pic_flag;
  bool bottom_field_flag;
  int idr_pic_id;
  int pic_order_cnt_lsb;
  int delta_pic_order_cnt_bottom;
  int delta_pic_order_cnt[2];
  int redundant_pic_cnt;
  bool direct_spatial_mv_pred_flag;

  bool num_ref_idx_active_override_flag;
  int num_ref_idx_l0_active_minus1;
  int num_ref_idx_l1_active_minus1;
  bool ref_pic_list_modification_flag_l0;
  bool ref_pic_list_modification_flag_l1;
  H264ModificationOfPicNum ref_list_l0_modifications[kRefListModSize];
  H264ModificationOfPicNum ref_list_l1_modifications[kRefListModSize];

  int luma_log2_weight_denom;
  int chroma_log2_weight_denom;

  bool luma_weight_l0_flag;
  bool chroma_weight_l0_flag;
  H264WeightingFactors pred_weight_table_l0;

  bool luma_weight_l1_flag;
  bool chroma_weight_l1_flag;
  H264WeightingFactors pred_weight_table_l1;

  bool no_output_of_prior_pics_flag;
  bool long_term_reference_flag;

  bool adaptive_ref_pic_marking_mode_flag;
  H264DecRefPicMarking ref_pic_marking[kRefListSize];

  int cabac_init_idc;
  int slice_qp_delta;
  bool sp_for_switch_flag;
  int slice_qs_delta;
  int disable_deblocking_filter_idc;
  int slice_alpha_c0_offset_div2;
  int slice_beta_offset_div2;
};

struct H264SEIRecoveryPoint {
  int recovery_frame_cnt;
  bool exact_match_flag;
  bool broken_link_flag;
  int changing_slice_group_idc;
};

struct MEDIA_EXPORT H264SEIMessage {
  H264SEIMessage();

  enum Type {
    kSEIRecoveryPoint = 6,
  };

  int type;
  int payload_size;
  union {
    
    
    H264SEIRecoveryPoint recovery_point;
  };
};

class MEDIA_EXPORT H264Parser {
 public:
  enum Result {
    kOk,
    kInvalidStream,      
    kUnsupportedStream,  
    kEOStream,           
  };

  
  
  
  
  
  
  
  
  
  
  
  static bool FindStartCode(const uint8* data, off_t data_size,
                            off_t* offset, off_t* start_code_size);

  H264Parser();
  ~H264Parser();

  void Reset();
  
  
  
  
  void SetStream(const uint8* stream, off_t stream_size);
  void SetEncryptedStream(const uint8* stream, off_t stream_size,
                          const std::vector<SubsampleEntry>& subsamples);

  
  
  
  
  
  
  Result AdvanceToNextNALU(H264NALU* nalu);

  
  

  
  
  
  
  
  
  
  
  
  
  
  Result ParseSPS(int* sps_id);
  Result ParsePPS(int* pps_id);

  
  
  const H264SPS* GetSPS(int sps_id);
  const H264PPS* GetPPS(int pps_id);

  
  
  
  

  
  
  Result ParseSliceHeader(const H264NALU& nalu, H264SliceHeader* shdr);

  
  
  Result ParseSEI(H264SEIMessage* sei_msg);

 private:
  
  
  
  
  
  
  
  bool LocateNALU(off_t* nalu_size, off_t* start_code_size);

  
  
  
  bool FindStartCodeInClearRanges(const uint8* data, off_t data_size,
                                  off_t* offset, off_t* start_code_size);

  
  
  Result ReadUE(int* val);

  
  Result ReadSE(int* val);

  
  Result ParseScalingList(int size, int* scaling_list, bool* use_default);
  Result ParseSPSScalingLists(H264SPS* sps);
  Result ParsePPSScalingLists(const H264SPS& sps, H264PPS* pps);

  
  Result ParseVUIParameters(H264SPS* sps);
  
  Result ParseAndIgnoreHRDParameters(bool* hrd_parameters_present);

  
  Result ParseRefPicListModifications(H264SliceHeader* shdr);
  Result ParseRefPicListModification(int num_ref_idx_active_minus1,
                                     H264ModificationOfPicNum* ref_list_mods);

  
  Result ParsePredWeightTable(const H264SPS& sps, H264SliceHeader* shdr);

  
  Result ParseWeightingFactors(int num_ref_idx_active_minus1,
                               int chroma_array_type,
                               int luma_log2_weight_denom,
                               int chroma_log2_weight_denom,
                               H264WeightingFactors* w_facts);

  
  Result ParseDecRefPicMarking(H264SliceHeader* shdr);

  
  const uint8* stream_;

  
  off_t bytes_left_;

  H264BitReader br_;

  
  typedef std::map<int, H264SPS*> SPSById;
  typedef std::map<int, H264PPS*> PPSById;
  SPSById active_SPSes_;
  PPSById active_PPSes_;

  
  
  Ranges<const uint8*> encrypted_ranges_;

  DISALLOW_COPY_AND_ASSIGN(H264Parser);
};

}  

#endif  
