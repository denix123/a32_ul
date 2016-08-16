// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MEDIA_WEBRTC_BROWSERTEST_BASE_H_
#define CHROME_BROWSER_MEDIA_WEBRTC_BROWSERTEST_BASE_H_

#include <string>

#include "chrome/test/base/in_process_browser_test.h"

namespace infobars {
class InfoBar;
}

namespace content {
class WebContents;
}

class WebRtcTestBase : public InProcessBrowserTest {
 public:
  
  static const char kAudioVideoCallConstraints[];
  static const char kAudioOnlyCallConstraints[];
  static const char kVideoOnlyCallConstraints[];
  static const char kAudioVideoCallConstraintsQVGA[];
  static const char kAudioVideoCallConstraints360p[];
  static const char kAudioVideoCallConstraintsVGA[];
  static const char kAudioVideoCallConstraints720p[];
  static const char kAudioVideoCallConstraints1080p[];

  static const char kFailedWithPermissionDeniedError[];
  static const char kFailedWithPermissionDismissedError[];

 protected:
  WebRtcTestBase();
  virtual ~WebRtcTestBase();

  
  
  void GetUserMediaAndAccept(content::WebContents* tab_contents) const;
  void GetUserMediaWithSpecificConstraintsAndAccept(
      content::WebContents* tab_contents,
      const std::string& constraints) const;
  void GetUserMediaAndDeny(content::WebContents* tab_contents);
  void GetUserMediaWithSpecificConstraintsAndDeny(
      content::WebContents* tab_contents,
      const std::string& constraints) const;
  void GetUserMediaAndDismiss(content::WebContents* tab_contents) const;
  void GetUserMedia(content::WebContents* tab_contents,
                    const std::string& constraints) const;

  
  
  content::WebContents* OpenPageAndGetUserMediaInNewTab(const GURL& url) const;

  
  
  content::WebContents* OpenPageAndGetUserMediaInNewTabWithConstraints(
      const GURL& url, const std::string& constraints) const;

  
  
  content::WebContents* OpenTestPageAndGetUserMediaInNewTab(
    const std::string& test_page) const;

  
  
  content::WebContents* OpenPageAndAcceptUserMedia(const GURL& url) const;

  
  void CloseLastLocalStream(content::WebContents* tab_contents) const;

  std::string ExecuteJavascript(const std::string& javascript,
                                content::WebContents* tab_contents) const;

  
  
  void SetupPeerconnectionWithLocalStream(content::WebContents* tab) const;

  
  
  
  
  void NegotiateCall(content::WebContents* from_tab,
                     content::WebContents* to_tab) const;

  
  void HangUp(content::WebContents* from_tab) const;

  
  
  
  void DetectErrorsInJavaScript();

  
  
  
  void StartDetectingVideo(content::WebContents* tab_contents,
                           const std::string& video_element) const;
  void WaitForVideoToPlay(content::WebContents* tab_contents) const;

  
  std::string GetStreamSize(content::WebContents* tab_contents,
                            const std::string& video_element) const;

  
  bool HasWebcamAvailableOnSystem(content::WebContents* tab_contents) const;

  
  bool OnWinXp() const;

  
  bool OnWin8() const;

 private:
  void CloseInfoBarInTab(content::WebContents* tab_contents,
                         infobars::InfoBar* infobar) const;

  std::string CreateLocalOffer(content::WebContents* from_tab) const;
  std::string CreateAnswer(std::string local_offer,
                           content::WebContents* to_tab) const;
  void ReceiveAnswer(std::string answer, content::WebContents* from_tab) const;
  void GatherAndSendIceCandidates(content::WebContents* from_tab,
                                  content::WebContents* to_tab) const;

  infobars::InfoBar* GetUserMediaAndWaitForInfoBar(
      content::WebContents* tab_contents,
      const std::string& constraints) const;

  bool detect_errors_in_javascript_;

  DISALLOW_COPY_AND_ASSIGN(WebRtcTestBase);
};

#endif  
