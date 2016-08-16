// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_OMNIBOX_OMNIBOX_UI_HANDLER_H_
#define CHROME_BROWSER_UI_WEBUI_OMNIBOX_OMNIBOX_UI_HANDLER_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "chrome/browser/autocomplete/autocomplete_controller_delegate.h"
#include "chrome/browser/ui/webui/mojo_web_ui_handler.h"
#include "chrome/browser/ui/webui/omnibox/omnibox.mojom.h"
#include "components/omnibox/autocomplete_input.h"
#include "components/omnibox/autocomplete_match.h"

class AutocompleteController;
class Profile;

class OmniboxUIHandler : public AutocompleteControllerDelegate,
                         public mojo::InterfaceImpl<OmniboxUIHandlerMojo>,
                         public MojoWebUIHandler {
 public:
  explicit OmniboxUIHandler(Profile* profile);
  virtual ~OmniboxUIHandler();

  
  virtual void OnResultChanged(bool default_match_changed) OVERRIDE;

  
  virtual void OnConnectionError() OVERRIDE {
    
  }

  
  virtual void StartOmniboxQuery(const mojo::String& input_string,
                                 int32_t cursor_position,
                                 bool prevent_inline_autocomplete,
                                 bool prefer_keyword,
                                 int32_t page_classification) OVERRIDE;

 private:
  
  
  
  bool LookupIsTypedHost(const base::string16& host, bool* is_typed_host) const;

  
  
  void ResetController();

  
  
  scoped_ptr<AutocompleteController> controller_;

  
  
  
  base::Time time_omnibox_started_;

  
  AutocompleteInput input_;

  
  Profile* profile_;

  DISALLOW_COPY_AND_ASSIGN(OmniboxUIHandler);
};

#endif  
