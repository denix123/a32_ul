// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_FEEDBACK_FEEDBACK_UPLOADER_FACTORY_H_
#define COMPONENTS_FEEDBACK_FEEDBACK_UPLOADER_FACTORY_H_

#include "components/keyed_service/content/browser_context_keyed_service_factory.h"

template<typename T> struct DefaultSingletonTraits;

namespace content {
class BrowserContext;
}

namespace feedback {

class FeedbackUploader;

class FeedbackUploaderFactory : public BrowserContextKeyedServiceFactory {
 public:
  
  static FeedbackUploaderFactory* GetInstance();

  
  static FeedbackUploader* GetForBrowserContext(
      content::BrowserContext* context);

 private:
  friend struct DefaultSingletonTraits<FeedbackUploaderFactory>;

  FeedbackUploaderFactory();
  virtual ~FeedbackUploaderFactory();

  
  virtual KeyedService* BuildServiceInstanceFor(
      content::BrowserContext* context) const OVERRIDE;
  virtual content::BrowserContext* GetBrowserContextToUse(
      content::BrowserContext* context) const OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(FeedbackUploaderFactory);
};

}  

#endif  
