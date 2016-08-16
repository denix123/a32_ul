// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_COMMON_GPU_MEDIA_VAAPI_VIDEO_ENCODE_ACCELERATOR_H_
#define CONTENT_COMMON_GPU_MEDIA_VAAPI_VIDEO_ENCODE_ACCELERATOR_H_

#include <list>
#include <queue>

#include "base/memory/linked_ptr.h"
#include "base/threading/thread.h"
#include "content/common/content_export.h"
#include "content/common/gpu/media/h264_dpb.h"
#include "content/common/gpu/media/va_surface.h"
#include "content/common/gpu/media/vaapi_wrapper.h"
#include "media/filters/h264_bitstream_buffer.h"
#include "media/video/video_encode_accelerator.h"

namespace content {

class CONTENT_EXPORT VaapiVideoEncodeAccelerator
    : public media::VideoEncodeAccelerator {
 public:
  explicit VaapiVideoEncodeAccelerator(Display* x_display);
  virtual ~VaapiVideoEncodeAccelerator();

  
  virtual std::vector<media::VideoEncodeAccelerator::SupportedProfile>
      GetSupportedProfiles() OVERRIDE;
  virtual bool Initialize(media::VideoFrame::Format format,
                          const gfx::Size& input_visible_size,
                          media::VideoCodecProfile output_profile,
                          uint32 initial_bitrate,
                          Client* client) OVERRIDE;
  virtual void Encode(const scoped_refptr<media::VideoFrame>& frame,
                      bool force_keyframe) OVERRIDE;
  virtual void UseOutputBitstreamBuffer(
      const media::BitstreamBuffer& buffer) OVERRIDE;
  virtual void RequestEncodingParametersChange(uint32 bitrate,
                                               uint32 framerate) OVERRIDE;
  virtual void Destroy() OVERRIDE;

 private:
  
  typedef std::list<scoped_refptr<VASurface> > RefPicList;

  
  
  
  
  
  
  struct EncodeJob {
    
    scoped_refptr<VASurface> input_surface;
    
    
    scoped_refptr<VASurface> recon_surface;
    
    VABufferID coded_buffer;
    
    
    
    RefPicList reference_surfaces;
    
    
    bool keyframe;

    EncodeJob();
    ~EncodeJob();
  };

  
  enum State {
    kUninitialized,
    kEncoding,
    kError,
  };

  
  struct InputFrameRef;
  
  struct BitstreamBufferRef;

  
  
  void InitializeTask();
  void EncodeTask(const scoped_refptr<media::VideoFrame>& frame,
                  bool force_keyframe);
  void UseOutputBitstreamBufferTask(scoped_ptr<BitstreamBufferRef> buffer_ref);
  void RequestEncodingParametersChangeTask(uint32 bitrate, uint32 framerate);
  void DestroyTask();

  
  
  void EncodeFrameTask();

  
  void UpdateSPS();
  void UpdatePPS();
  void UpdateRates(uint32 bitrate, uint32 framerate);

  
  
  void GeneratePackedSPS();
  void GeneratePackedPPS();

  
  
  
  bool PrepareNextJob();

  
  
  void BeginFrame(bool force_keyframe);

  
  
  void EndFrame();

  
  bool SubmitFrameParameters();
  
  bool SubmitHeadersIfNeeded();

  
  bool UploadFrame(const scoped_refptr<media::VideoFrame>& frame);

  
  
  bool ExecuteEncode();

  
  
  void RecycleVASurfaceID(VASurfaceID va_surface_id);

  
  
  
  void TryToReturnBitstreamBuffer();

  
  void NotifyError(Error error);

  
  void SetState(State state);

  
  
  scoped_ptr<VaapiWrapper> vaapi_wrapper_;

  
  media::VideoCodecProfile profile_;
  gfx::Size visible_size_;
  gfx::Size coded_size_;  
  
  unsigned int mb_width_;
  unsigned int mb_height_;

  
  unsigned int max_ref_idx_l0_size_;

  
  unsigned int qp_;

  
  unsigned int idr_period_;
  
  unsigned int i_period_;
  
  
  unsigned int ip_period_;

  
  size_t output_buffer_byte_size_;

  Display* x_display_;

  
  

  
  State state_;

  
  unsigned int frame_num_;
  
  unsigned int last_idr_frame_num_;

  
  unsigned int bitrate_;
  
  unsigned int framerate_;
  
  unsigned int cpb_size_;
  
  
  bool encoding_parameters_changed_;

  
  scoped_ptr<EncodeJob> current_encode_job_;

  
  
  
  media::H264SPS current_sps_;
  media::H264BitstreamBuffer packed_sps_;
  media::H264PPS current_pps_;
  media::H264BitstreamBuffer packed_pps_;

  
  H264Picture current_pic_;

  
  std::vector<VASurfaceID> available_va_surface_ids_;

  
  std::vector<VABufferID> available_va_buffer_ids_;

  
  RefPicList ref_pic_list0_;

  
  VASurface::ReleaseCB va_surface_release_cb_;

  
  std::queue<linked_ptr<InputFrameRef> > encoder_input_queue_;

  
  std::queue<linked_ptr<BitstreamBufferRef> > available_bitstream_buffers_;

  
  std::queue<linked_ptr<EncodeJob> > submitted_encode_jobs_;

  
  base::Thread encoder_thread_;
  scoped_refptr<base::MessageLoopProxy> encoder_thread_proxy_;

  const scoped_refptr<base::MessageLoopProxy> child_message_loop_proxy_;

  
  
  
  scoped_ptr<base::WeakPtrFactory<Client> > client_ptr_factory_;
  base::WeakPtr<Client> client_;

  
  
  
  
  base::WeakPtr<VaapiVideoEncodeAccelerator> weak_this_;
  base::WeakPtrFactory<VaapiVideoEncodeAccelerator> weak_this_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(VaapiVideoEncodeAccelerator);
};

}  

#endif  
