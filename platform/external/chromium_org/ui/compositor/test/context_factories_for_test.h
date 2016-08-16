// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

namespace ui {

class ContextFactory;

ui::ContextFactory* InitializeContextFactoryForTests(bool enable_pixel_output);
void TerminateContextFactoryForTests();

}  
