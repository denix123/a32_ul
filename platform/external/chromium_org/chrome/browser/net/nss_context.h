// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_NET_NSS_CONTEXT_H_
#define CHROME_BROWSER_NET_NSS_CONTEXT_H_

#include <string>

#include "base/callback.h"
#include "base/compiler_specific.h"
#include "crypto/scoped_nss_types.h"

class Profile;

namespace net {
class NSSCertDatabase;
}

namespace content {
class ResourceContext;
}  

crypto::ScopedPK11Slot GetPublicNSSKeySlotForResourceContext(
    content::ResourceContext* context);

crypto::ScopedPK11Slot GetPrivateNSSKeySlotForResourceContext(
    content::ResourceContext* context,
    const base::Callback<void(crypto::ScopedPK11Slot)>& callback)
    WARN_UNUSED_RESULT;

net::NSSCertDatabase* GetNSSCertDatabaseForResourceContext(
    content::ResourceContext* context,
    const base::Callback<void(net::NSSCertDatabase*)>& callback)
    WARN_UNUSED_RESULT;

#if defined(OS_CHROMEOS)
void EnableNSSSystemKeySlotForResourceContext(
    content::ResourceContext* context);
#endif

void GetNSSCertDatabaseForProfile(
    Profile* profile,
    const base::Callback<void(net::NSSCertDatabase*)>& callback);

#endif  
