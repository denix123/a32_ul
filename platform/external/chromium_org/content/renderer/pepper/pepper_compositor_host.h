// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_PEPPER_PEPPER_COMPOSITOR_H_
#define CONTENT_RENDERER_PEPPER_PEPPER_COMPOSITOR_H_

#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "ppapi/host/host_message_context.h"
#include "ppapi/host/resource_host.h"
#include "ppapi/shared_impl/compositor_layer_data.h"

namespace base {
class SharedMemory;
}  

namespace cc {
class Layer;
}  

namespace content {

class PepperPluginInstanceImpl;
class RendererPpapiHost;

class PepperCompositorHost : public ppapi::host::ResourceHost {
 public:
  PepperCompositorHost(RendererPpapiHost* host,
                       PP_Instance instance,
                       PP_Resource resource);
  
  
  
  
  bool BindToInstance(PepperPluginInstanceImpl* new_instance);

  const scoped_refptr<cc::Layer> layer() { return layer_; };

  void ViewInitiatedPaint();
  void ViewFlushedPaint();

 private:
  virtual ~PepperCompositorHost();

  void ImageReleased(int32_t id,
                     const scoped_ptr<base::SharedMemory>& shared_memory,
                     uint32_t sync_point,
                     bool is_lost);
  void ResourceReleased(int32_t id,
                        uint32_t sync_point,
                        bool is_lost);
  void SendCommitLayersReplyIfNecessary();
  void UpdateLayer(const scoped_refptr<cc::Layer>& layer,
                   const ppapi::CompositorLayerData* old_layer,
                   const ppapi::CompositorLayerData* new_layer,
                   scoped_ptr<base::SharedMemory> image_shm);

  
  virtual int32_t OnResourceMessageReceived(
      const IPC::Message& msg,
      ppapi::host::HostMessageContext* context) OVERRIDE;

  
  virtual bool IsCompositorHost() OVERRIDE;

  
  int32_t OnHostMsgCommitLayers(
      ppapi::host::HostMessageContext* context,
      const std::vector<ppapi::CompositorLayerData>& layers,
      bool reset);

  
  
  PepperPluginInstanceImpl* bound_instance_;

  
  scoped_refptr<cc::Layer> layer_;

  
  
  struct LayerData {
    LayerData(const scoped_refptr<cc::Layer>& cc,
              const ppapi::CompositorLayerData& pp);
    ~LayerData();

    scoped_refptr<cc::Layer> cc_layer;
    ppapi::CompositorLayerData pp_layer;
  };
  std::vector<LayerData> layers_;

  ppapi::host::ReplyMessageContext commit_layers_reply_context_;

  base::WeakPtrFactory<PepperCompositorHost> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(PepperCompositorHost);
};

}  

#endif  
