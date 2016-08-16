// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_COPRESENCE_COPRESENCE_TRANSLATIONS_H_
#define CHROME_BROWSER_EXTENSIONS_API_COPRESENCE_COPRESENCE_TRANSLATIONS_H_

#include <map>
#include <string>
#include <vector>

#include "base/macros.h"
#include "base/memory/linked_ptr.h"
#include "components/copresence/proto/enums.pb.h"

namespace copresence {
class ReportRequest;
}

namespace extensions {

namespace api {
namespace copresence {
struct Operation;
struct PublishOperation;
struct SubscribeOperation;
}
}

typedef std::map<std::string, std::string> SubscriptionToAppMap;

bool PrepareReportRequestProto(
    const std::vector<linked_ptr<api::copresence::Operation>>& operations,
    const std::string& app_id,
    SubscriptionToAppMap* apps_by_subscription_id,
    copresence::ReportRequest* request);

}  

#endif  
