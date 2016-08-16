// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_BOOKMARKS_BOOKMARK_MODEL_FACTORY_H_
#define CHROME_BROWSER_BOOKMARKS_BOOKMARK_MODEL_FACTORY_H_

#include "base/macros.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"

template <typename T> struct DefaultSingletonTraits;

class BookmarkModel;
class Profile;

class BookmarkModelFactory : public BrowserContextKeyedServiceFactory {
 public:
  static BookmarkModel* GetForProfile(Profile* profile);

  static BookmarkModel* GetForProfileIfExists(Profile* profile);

  static BookmarkModelFactory* GetInstance();

 private:
  friend struct DefaultSingletonTraits<BookmarkModelFactory>;

  BookmarkModelFactory();
  virtual ~BookmarkModelFactory();

  
  virtual KeyedService* BuildServiceInstanceFor(
      content::BrowserContext* context) const OVERRIDE;
  virtual void RegisterProfilePrefs(
      user_prefs::PrefRegistrySyncable* registry) OVERRIDE;
  virtual content::BrowserContext* GetBrowserContextToUse(
      content::BrowserContext* context) const OVERRIDE;
  virtual bool ServiceIsNULLWhileTesting() const OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(BookmarkModelFactory);
};

#endif  
