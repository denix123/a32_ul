// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_NET_NET_ERROR_TAB_HELPER_H_
#define CHROME_BROWSER_NET_NET_ERROR_TAB_HELPER_H_

#include "base/basictypes.h"
#include "base/bind.h"
#include "base/compiler_specific.h"
#include "base/memory/weak_ptr.h"
#include "base/prefs/pref_member.h"
#include "chrome/browser/net/dns_probe_service.h"
#include "chrome/common/net/net_error_info.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/browser/web_contents_user_data.h"

namespace chrome_browser_net {

class NetErrorTabHelper
    : public content::WebContentsObserver,
      public content::WebContentsUserData<NetErrorTabHelper> {
 public:
  enum TestingState {
    TESTING_DEFAULT,
    TESTING_FORCE_DISABLED,
    TESTING_FORCE_ENABLED
  };

  typedef base::Callback<void(chrome_common_net::DnsProbeStatus)>
      DnsProbeStatusSnoopCallback;

  virtual ~NetErrorTabHelper();

  static void set_state_for_testing(TestingState testing_state);

  
  
  
  void set_dns_probe_status_snoop_callback_for_testing(
      const DnsProbeStatusSnoopCallback& dns_probe_status_snoop_callback) {
    dns_probe_status_snoop_callback_ = dns_probe_status_snoop_callback;
  }

  
  virtual void DidStartNavigationToPendingEntry(
      const GURL& url,
      content::NavigationController::ReloadType reload_type) OVERRIDE;

  virtual void DidStartProvisionalLoadForFrame(
      content::RenderFrameHost* render_frame_host,
      const GURL& validated_url,
      bool is_error_page,
      bool is_iframe_srcdoc) OVERRIDE;

  virtual void DidCommitProvisionalLoadForFrame(
      content::RenderFrameHost* render_frame_host,
      const GURL& url,
      ui::PageTransition transition_type) OVERRIDE;

  virtual void DidFailProvisionalLoad(
      content::RenderFrameHost* render_frame_host,
      const GURL& validated_url,
      int error_code,
      const base::string16& error_description) OVERRIDE;

 protected:
  
  
  explicit NetErrorTabHelper(content::WebContents* contents);
  virtual void StartDnsProbe();
  virtual void SendInfo();
  void OnDnsProbeFinished(chrome_common_net::DnsProbeStatus result);

  chrome_common_net::DnsProbeStatus dns_probe_status() const {
    return dns_probe_status_;
  }

 private:
  friend class content::WebContentsUserData<NetErrorTabHelper>;

  void OnMainFrameDnsError();

  void InitializePref(content::WebContents* contents);
  bool ProbesAllowed() const;

  
  bool is_error_page_;

  
  
  bool dns_error_active_;

  
  
  bool dns_error_page_committed_;

  
  
  
  chrome_common_net::DnsProbeStatus dns_probe_status_;

  
  DnsProbeStatusSnoopCallback dns_probe_status_snoop_callback_;

  
  
  BooleanPrefMember resolve_errors_with_web_service_;

  base::WeakPtrFactory<NetErrorTabHelper> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(NetErrorTabHelper);
};

}  

#endif  
