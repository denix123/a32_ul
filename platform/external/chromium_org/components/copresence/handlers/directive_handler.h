// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_COPRESENCE_HANDLERS_DIRECTIVE_HANDLER_H_
#define COMPONENTS_COPRESENCE_HANDLERS_DIRECTIVE_HANDLER_H_

#include <string>

#include "base/callback.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "components/copresence/handlers/audio/audio_directive_handler.h"
#include "components/copresence/mediums/audio/audio_recorder.h"

namespace copresence {

class Directive;

class DirectiveHandler {
 public:
  DirectiveHandler();
  virtual ~DirectiveHandler();

  
  
  
  
  virtual void Initialize(
      const AudioRecorder::DecodeSamplesCallback& decode_cb,
      const AudioDirectiveHandler::EncodeTokenCallback& encode_cb);

  
  virtual void AddDirective(const copresence::Directive& directive);
  
  virtual void RemoveDirectives(const std::string& op_id);

  const std::string& CurrentAudibleToken() const;
  const std::string& CurrentInaudibleToken() const;

 private:
  scoped_ptr<AudioDirectiveHandler> audio_handler_;

  DISALLOW_COPY_AND_ASSIGN(DirectiveHandler);
};

}  

#endif  
