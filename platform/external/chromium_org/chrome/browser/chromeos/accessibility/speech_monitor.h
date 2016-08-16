// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_ACCESSIBILITY_SPEECH_MONITOR_H_
#define CHROME_BROWSER_CHROMEOS_ACCESSIBILITY_SPEECH_MONITOR_H_

#include <deque>

#include "base/memory/ref_counted.h"
#include "chrome/browser/speech/tts_platform.h"
#include "content/public/test/test_utils.h"

namespace chromeos {

class SpeechMonitor : public TtsPlatformImpl {
 public:
  SpeechMonitor();
  virtual ~SpeechMonitor();

  
  std::string GetNextUtterance();

  
  
  bool SkipChromeVoxEnabledMessage();

  
  virtual bool PlatformImplAvailable() OVERRIDE;
  virtual bool Speak(
      int utterance_id,
      const std::string& utterance,
      const std::string& lang,
      const VoiceData& voice,
      const UtteranceContinuousParameters& params) OVERRIDE;
  virtual bool StopSpeaking() OVERRIDE;
  virtual bool IsSpeaking() OVERRIDE;
  virtual void GetVoices(std::vector<VoiceData>* out_voices) OVERRIDE;
  virtual void Pause() OVERRIDE {}
  virtual void Resume() OVERRIDE {}
  virtual std::string error() OVERRIDE;
  virtual void clear_error() OVERRIDE {}
  virtual void set_error(const std::string& error) OVERRIDE {}
  virtual void WillSpeakUtteranceWithVoice(
      const Utterance* utterance, const VoiceData& voice_data) OVERRIDE;

 private:
  scoped_refptr<content::MessageLoopRunner> loop_runner_;
  std::deque<std::string> utterance_queue_;

  DISALLOW_COPY_AND_ASSIGN(SpeechMonitor);
};

}  

#endif  
