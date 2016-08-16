// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SPEECH_TTS_CONTROLLER_IMPL_H_
#define CHROME_BROWSER_SPEECH_TTS_CONTROLLER_IMPL_H_

#include <queue>
#include <set>
#include <string>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "base/memory/singleton.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/speech/tts_controller.h"
#include "url/gurl.h"

namespace content {
class BrowserContext;
}

class TtsControllerImpl : public TtsController {
 public:
  
  static TtsControllerImpl* GetInstance();

  
  virtual bool IsSpeaking() OVERRIDE;
  virtual void SpeakOrEnqueue(Utterance* utterance) OVERRIDE;
  virtual void Stop() OVERRIDE;
  virtual void Pause() OVERRIDE;
  virtual void Resume() OVERRIDE;
  virtual void OnTtsEvent(int utterance_id,
                  TtsEventType event_type,
                  int char_index,
                  const std::string& error_message) OVERRIDE;
  virtual void GetVoices(content::BrowserContext* browser_context,
                         std::vector<VoiceData>* out_voices) OVERRIDE;
  virtual void VoicesChanged() OVERRIDE;
  virtual void AddVoicesChangedDelegate(
      VoicesChangedDelegate* delegate) OVERRIDE;
  virtual void RemoveVoicesChangedDelegate(
      VoicesChangedDelegate* delegate) OVERRIDE;
  virtual void SetTtsEngineDelegate(TtsEngineDelegate* delegate) OVERRIDE;
  virtual TtsEngineDelegate* GetTtsEngineDelegate() OVERRIDE;
  virtual void SetPlatformImpl(TtsPlatformImpl* platform_impl) OVERRIDE;
  virtual int QueueSize() OVERRIDE;

 protected:
  TtsControllerImpl();
  virtual ~TtsControllerImpl();

 private:
  
  TtsPlatformImpl* GetPlatformImpl();

  
  
  void SpeakNow(Utterance* utterance);

  
  
  void ClearUtteranceQueue(bool send_events);

  
  void FinishCurrentUtterance();

  
  void SpeakNextUtterance();

  
  
  int GetMatchingVoice(const Utterance* utterance,
                       std::vector<VoiceData>& voices);

  friend struct DefaultSingletonTraits<TtsControllerImpl>;

  
  Utterance* current_utterance_;

  
  bool paused_;

  
  std::queue<Utterance*> utterance_queue_;

  
  std::set<VoicesChangedDelegate*> voices_changed_delegates_;

  
  
  TtsPlatformImpl* platform_impl_;

  
  TtsEngineDelegate* tts_engine_delegate_;

  DISALLOW_COPY_AND_ASSIGN(TtsControllerImpl);
};

#endif  
