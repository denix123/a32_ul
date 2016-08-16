// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_SYSTEM_AUDIO_AUDIO_OBSERVER_H_
#define ASH_SYSTEM_AUDIO_AUDIO_OBSERVER_H_

namespace ash {

class AudioObserver {
 public:
  virtual ~AudioObserver() {}

  
  virtual void OnOutputVolumeChanged() = 0;

  
  virtual void OnOutputMuteChanged() = 0;

  
  virtual void OnAudioNodesChanged() = 0;

  
  virtual void OnActiveOutputNodeChanged() = 0;

  
  virtual void OnActiveInputNodeChanged() = 0;
};

}  

#endif  
