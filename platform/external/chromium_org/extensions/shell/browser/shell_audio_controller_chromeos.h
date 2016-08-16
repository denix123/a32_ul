// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_SHELL_BROWSER_SHELL_AUDIO_CONTROLLER_CHROMEOS_H_
#define EXTENSIONS_SHELL_BROWSER_SHELL_AUDIO_CONTROLLER_CHROMEOS_H_

#include "base/macros.h"
#include "chromeos/audio/audio_devices_pref_handler.h"
#include "chromeos/audio/cras_audio_handler.h"

namespace chromeos {
class AudioDevicesPrefHandler;
}

namespace extensions {

class ShellAudioController : public chromeos::CrasAudioHandler::AudioObserver {
 public:
  
  class PrefHandler : public chromeos::AudioDevicesPrefHandler {
   public:
    PrefHandler();

    
    virtual double GetOutputVolumeValue(
        const chromeos::AudioDevice* device) OVERRIDE;
    virtual double GetInputGainValue(
        const chromeos::AudioDevice* device) OVERRIDE;
    virtual void SetVolumeGainValue(const chromeos::AudioDevice& device,
                                    double value) OVERRIDE;
    virtual bool GetMuteValue(const chromeos::AudioDevice& device) OVERRIDE;
    virtual void SetMuteValue(const chromeos::AudioDevice& device,
                              bool mute_on) OVERRIDE;
    virtual bool GetAudioCaptureAllowedValue() OVERRIDE;
    virtual bool GetAudioOutputAllowedValue() OVERRIDE;
    virtual void AddAudioPrefObserver(
        chromeos::AudioPrefObserver* observer) OVERRIDE;
    virtual void RemoveAudioPrefObserver(
        chromeos::AudioPrefObserver* observer) OVERRIDE;

   protected:
    virtual ~PrefHandler();

   private:
    DISALLOW_COPY_AND_ASSIGN(PrefHandler);
  };

  ShellAudioController();
  virtual ~ShellAudioController();

  
  virtual void OnOutputVolumeChanged() OVERRIDE;
  virtual void OnOutputMuteChanged() OVERRIDE;
  virtual void OnInputGainChanged() OVERRIDE;
  virtual void OnInputMuteChanged() OVERRIDE;
  virtual void OnAudioNodesChanged() OVERRIDE;
  virtual void OnActiveOutputNodeChanged() OVERRIDE;
  virtual void OnActiveInputNodeChanged() OVERRIDE;

 private:
  
  
  void ActivateDevices();

  DISALLOW_COPY_AND_ASSIGN(ShellAudioController);
};

}  

#endif  
