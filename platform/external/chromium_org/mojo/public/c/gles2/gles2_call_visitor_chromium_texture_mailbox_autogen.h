// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


VISIT_GL_CALL(GenMailboxCHROMIUM, void, (GLbyte * mailbox), (mailbox))
VISIT_GL_CALL(ProduceTextureCHROMIUM,
              void,
              (GLenum target, const GLbyte* mailbox),
              (target, mailbox))
VISIT_GL_CALL(ProduceTextureDirectCHROMIUM,
              void,
              (GLuint texture, GLenum target, const GLbyte* mailbox),
              (texture, target, mailbox))
VISIT_GL_CALL(ConsumeTextureCHROMIUM,
              void,
              (GLenum target, const GLbyte* mailbox),
              (target, mailbox))
VISIT_GL_CALL(CreateAndConsumeTextureCHROMIUM,
              GLuint,
              (GLenum target, const GLbyte* mailbox),
              (target, mailbox))
