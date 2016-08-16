// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_SPEECH_RECOGNITION_DISPATCHER_H_
#define CONTENT_RENDERER_SPEECH_RECOGNITION_DISPATCHER_H_

#include <map>

#include "base/basictypes.h"
#include "content/public/common/speech_recognition_result.h"
#include "content/public/renderer/render_view_observer.h"
#include "third_party/WebKit/public/platform/WebVector.h"
#include "third_party/WebKit/public/web/WebSpeechRecognitionHandle.h"
#include "third_party/WebKit/public/web/WebSpeechRecognizer.h"

namespace content {
class RenderViewImpl;
struct SpeechRecognitionError;
struct SpeechRecognitionResult;

class SpeechRecognitionDispatcher : public RenderViewObserver,
                                    public blink::WebSpeechRecognizer {
 public:
  explicit SpeechRecognitionDispatcher(RenderViewImpl* render_view);
  virtual ~SpeechRecognitionDispatcher();

  
  void AbortAllRecognitions();

 private:
  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

  
  virtual void start(const blink::WebSpeechRecognitionHandle&,
                     const blink::WebSpeechRecognitionParams&,
                     blink::WebSpeechRecognizerClient*) OVERRIDE;
  virtual void stop(const blink::WebSpeechRecognitionHandle&,
                    blink::WebSpeechRecognizerClient*) OVERRIDE;
  virtual void abort(const blink::WebSpeechRecognitionHandle&,
                     blink::WebSpeechRecognizerClient*) OVERRIDE;

  void OnRecognitionStarted(int request_id);
  void OnAudioStarted(int request_id);
  void OnSoundStarted(int request_id);
  void OnSoundEnded(int request_id);
  void OnAudioEnded(int request_id);
  void OnErrorOccurred(int request_id, const SpeechRecognitionError& error);
  void OnRecognitionEnded(int request_id);
  void OnResultsRetrieved(int request_id,
                          const SpeechRecognitionResults& result);

  int GetOrCreateIDForHandle(const blink::WebSpeechRecognitionHandle& handle);
  bool HandleExists(const blink::WebSpeechRecognitionHandle& handle);
  const blink::WebSpeechRecognitionHandle& GetHandleFromID(int handle_id);

  
  blink::WebSpeechRecognizerClient* recognizer_client_;

  typedef std::map<int, blink::WebSpeechRecognitionHandle> HandleMap;
  HandleMap handle_map_;
  int next_id_;

  DISALLOW_COPY_AND_ASSIGN(SpeechRecognitionDispatcher);
};

}  

#endif  