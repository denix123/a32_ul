// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_SYSTEM_AUDIO_TRAY_AUDIO_DELEGATE_H_
#define ASH_SYSTEM_AUDIO_TRAY_AUDIO_DELEGATE_H_

namespace ash {
namespace system {

class ASH_EXPORT TrayAudioDelegate {
 public:

  enum { kNoAudioDeviceIcon = -1 };

  virtual ~TrayAudioDelegate() {}

  
  
  virtual void AdjustOutputVolumeToAudibleLevel() = 0;

  
  
  virtual int GetOutputDefaultVolumeMuteLevel() = 0;

  
  virtual int GetActiveOutputDeviceIconId() = 0;

  
  virtual int GetOutputVolumeLevel() = 0;

  
  virtual bool HasAlternativeSources() = 0;

  
  virtual bool IsOutputAudioMuted() = 0;

  
  virtual void SetOutputAudioIsMuted(bool is_muted) = 0;

  
  virtual void SetOutputVolumeLevel(int level) = 0;
};

}  
}  

#endif  
