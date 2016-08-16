// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_MEDIA_CAPTURE_AUDIO_MIRRORING_MANAGER_H_
#define CONTENT_BROWSER_MEDIA_CAPTURE_AUDIO_MIRRORING_MANAGER_H_

#include <set>
#include <utility>
#include <vector>

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/threading/thread_checker.h"
#include "content/common/content_export.h"
#include "media/audio/audio_source_diverter.h"

namespace media {
class AudioOutputStream;
}

namespace content {

class CONTENT_EXPORT AudioMirroringManager {
 public:
  
  typedef media::AudioSourceDiverter Diverter;

  
  
  typedef std::pair<int, int> SourceFrameRef;

  
  
  class MirroringDestination {
   public:
    
    
    
    
    
    typedef base::Callback<void(const std::set<SourceFrameRef>&)>
        MatchesCallback;
    virtual void QueryForMatches(
        const std::set<SourceFrameRef>& candidates,
        const MatchesCallback& results_callback) = 0;

    
    
    
    
    virtual media::AudioOutputStream* AddInput(
        const media::AudioParameters& params) = 0;

   protected:
    virtual ~MirroringDestination() {}
  };

  
  AudioMirroringManager();
  virtual ~AudioMirroringManager();

  
  static AudioMirroringManager* GetInstance();

  
  
  
  
  virtual void AddDiverter(int render_process_id, int render_frame_id,
                           Diverter* diverter);
  virtual void RemoveDiverter(Diverter* diverter);

  
  
  
  
  
  virtual void StartMirroring(MirroringDestination* destination);
  virtual void StopMirroring(MirroringDestination* destination);

 private:
  friend class AudioMirroringManagerTest;

  struct StreamRoutingState {
    
    SourceFrameRef source_render_frame;

    
    Diverter* diverter;

    
    
    MirroringDestination* destination;

    StreamRoutingState(const SourceFrameRef& source_frame,
                       Diverter* stream_diverter);
    ~StreamRoutingState();
  };

  typedef std::vector<StreamRoutingState> StreamRoutes;
  typedef std::vector<MirroringDestination*> Destinations;

  
  
  void InitiateQueriesToFindNewDestination(
      MirroringDestination* old_destination,
      const std::set<SourceFrameRef>& candidates);

  
  
  
  
  void UpdateRoutesToDestination(MirroringDestination* destination,
                                 bool add_only,
                                 const std::set<SourceFrameRef>& matches);

  
  
  static void ChangeRoute(StreamRoutingState* route,
                          MirroringDestination* new_destination);

  
  StreamRoutes routes_;

  
  Destinations sessions_;

  
  base::ThreadChecker thread_checker_;

  DISALLOW_COPY_AND_ASSIGN(AudioMirroringManager);
};

}  

#endif  
