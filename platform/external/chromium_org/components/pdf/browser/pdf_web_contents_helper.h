// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PDF_BROWSER_PDF_WEB_CONTENTS_HELPER_H_
#define COMPONENTS_PDF_BROWSER_PDF_WEB_CONTENTS_HELPER_H_

#include <string>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/browser/web_contents_user_data.h"
#include "ipc/ipc_message.h"

namespace content {
class WebContents;
}

namespace pdf {

class OpenPDFInReaderPromptClient;
class PDFWebContentsHelperClient;

class PDFWebContentsHelper
    : public content::WebContentsObserver,
      public content::WebContentsUserData<PDFWebContentsHelper> {
 public:
  static void CreateForWebContentsWithClient(
      content::WebContents* contents,
      scoped_ptr<PDFWebContentsHelperClient> client);

  OpenPDFInReaderPromptClient* open_in_reader_prompt() const {
    return open_in_reader_prompt_.get();
  }

  void ShowOpenInReaderPrompt(scoped_ptr<OpenPDFInReaderPromptClient> prompt);

 private:
  PDFWebContentsHelper(content::WebContents* web_contents,
                       scoped_ptr<PDFWebContentsHelperClient> client);
  virtual ~PDFWebContentsHelper();

  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;
  virtual void DidNavigateMainFrame(
      const content::LoadCommittedDetails& details,
      const content::FrameNavigateParams& params) OVERRIDE;

  

  void UpdateLocationBar();
  void OnModalPromptForPasswordClosed(IPC::Message* reply_message,
                                      bool success,
                                      const base::string16& actual_value);

  
  void OnHasUnsupportedFeature();
  void OnSaveURLAs(const GURL& url, const content::Referrer& referrer);
  void OnUpdateContentRestrictions(int content_restrictions);
  void OnModalPromptForPassword(const std::string& prompt,
                                IPC::Message* reply_message);

  
  scoped_ptr<OpenPDFInReaderPromptClient> open_in_reader_prompt_;
  scoped_ptr<PDFWebContentsHelperClient> client_;

  DISALLOW_COPY_AND_ASSIGN(PDFWebContentsHelper);
};

}  

#endif  