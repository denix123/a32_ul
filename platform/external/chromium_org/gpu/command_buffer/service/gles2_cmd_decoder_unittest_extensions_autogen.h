// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef GPU_COMMAND_BUFFER_SERVICE_GLES2_CMD_DECODER_UNITTEST_EXTENSIONS_AUTOGEN_H_
#define GPU_COMMAND_BUFFER_SERVICE_GLES2_CMD_DECODER_UNITTEST_EXTENSIONS_AUTOGEN_H_


TEST_P(GLES2DecoderTestWithCHROMIUMPathRendering, MatrixLoadfCHROMIUMImmediateValidArgs) {
  cmds::MatrixLoadfCHROMIUMImmediate& cmd = *GetImmediateAs<cmds::MatrixLoadfCHROMIUMImmediate>();
  SpecializedSetup<cmds::MatrixLoadfCHROMIUMImmediate, 0>(true);
  GLfloat temp[16] = { 0, };
  cmd.Init(GL_PATH_PROJECTION_CHROMIUM, &temp[0]);
  EXPECT_CALL(
      *gl_,
      MatrixLoadfEXT(GL_PATH_PROJECTION_CHROMIUM, reinterpret_cast<
          GLfloat*>(ImmediateDataAddress(&cmd))));
  EXPECT_EQ(error::kNoError,
            ExecuteImmediateCmd(cmd, sizeof(temp)));
  EXPECT_EQ(GL_NO_ERROR, GetGLError());
}

TEST_P(GLES2DecoderTestWithCHROMIUMPathRendering, MatrixLoadIdentityCHROMIUMValidArgs) {
  EXPECT_CALL(*gl_, MatrixLoadIdentityEXT(GL_PATH_PROJECTION_CHROMIUM));
  SpecializedSetup<cmds::MatrixLoadIdentityCHROMIUM, 0>(true);
  cmds::MatrixLoadIdentityCHROMIUM cmd;
  cmd.Init(GL_PATH_PROJECTION_CHROMIUM);
  EXPECT_EQ(error::kNoError, ExecuteCmd(cmd));
  EXPECT_EQ(GL_NO_ERROR, GetGLError());
}
#endif  

