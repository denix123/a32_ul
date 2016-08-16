// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PROFILES_PROFILE_DESTROYER_H_
#define CHROME_BROWSER_PROFILES_PROFILE_DESTROYER_H_

#include <set>

#include "base/memory/ref_counted.h"
#include "base/timer/timer.h"
#include "content/public/browser/render_process_host_observer.h"

class Profile;

namespace content {
class RenderProcessHost;
}

class ProfileDestroyer : public content::RenderProcessHostObserver {
 public:
  static void DestroyProfileWhenAppropriate(Profile* const profile);
  static void DestroyOffTheRecordProfileNow(Profile* const profile);

 private:
  typedef std::set<content::RenderProcessHost*> HostSet;
  typedef std::set<ProfileDestroyer*> DestroyerSet;

  friend class base::RefCounted<ProfileDestroyer>;

  ProfileDestroyer(Profile* const profile, HostSet* hosts);
  virtual ~ProfileDestroyer();

  
  virtual void RenderProcessHostDestroyed(
      content::RenderProcessHost* host) OVERRIDE;

  
  void DestroyProfile();

  
  
  static bool GetHostsForProfile(Profile* const profile, HostSet* hosts);

  
  static DestroyerSet* pending_destroyers_;

  
  base::Timer timer_;

  
  uint32 num_hosts_;

  
  
  Profile* profile_;

  base::WeakPtrFactory<ProfileDestroyer> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(ProfileDestroyer);
};

#endif  
