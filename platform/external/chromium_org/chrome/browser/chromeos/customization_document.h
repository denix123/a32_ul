// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_CUSTOMIZATION_DOCUMENT_H_
#define CHROME_BROWSER_CHROMEOS_CUSTOMIZATION_DOCUMENT_H_

#include <string>
#include <vector>

#include "base/compiler_specific.h"
#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/singleton.h"
#include "base/memory/weak_ptr.h"
#include "base/values.h"
#include "net/url_request/url_fetcher_delegate.h"
#include "url/gurl.h"

class PrefRegistrySimple;
class Profile;

namespace base {
class DictionaryValue;
class FilePath;
}

namespace extensions {
class ExternalLoader;
}

namespace net {
class URLFetcher;
}

namespace user_prefs {
class PrefRegistrySyncable;
}

namespace chromeos {

class CustomizationWallpaperDownloader;
class ServicesCustomizationExternalLoader;

void InitStartupCustomizationDocumentForTesting(const std::string& manifest);

namespace system {
class StatisticsProvider;
}  

class CustomizationDocument {
 public:
  virtual ~CustomizationDocument();

  
  bool IsReady() const { return root_.get(); }

 protected:
  explicit CustomizationDocument(const std::string& accepted_version);

  virtual bool LoadManifestFromFile(const base::FilePath& manifest_path);
  virtual bool LoadManifestFromString(const std::string& manifest);

  std::string GetLocaleSpecificString(const std::string& locale,
                                      const std::string& dictionary_name,
                                      const std::string& entry_name) const;

  scoped_ptr<base::DictionaryValue> root_;

  
  
  std::string accepted_version_;

 private:
  DISALLOW_COPY_AND_ASSIGN(CustomizationDocument);
};

class StartupCustomizationDocument : public CustomizationDocument {
 public:
  static StartupCustomizationDocument* GetInstance();

  std::string GetEULAPage(const std::string& locale) const;

  
  
  
  
  const std::string& initial_locale() const { return initial_locale_; }

  
  const std::vector<std::string>& configured_locales() const;

  
  const std::string& initial_locale_default() const;
  const std::string& initial_timezone() const { return initial_timezone_; }
  const std::string& keyboard_layout() const { return keyboard_layout_; }

 private:
  FRIEND_TEST_ALL_PREFIXES(StartupCustomizationDocumentTest, Basic);
  FRIEND_TEST_ALL_PREFIXES(StartupCustomizationDocumentTest, VPD);
  FRIEND_TEST_ALL_PREFIXES(StartupCustomizationDocumentTest, BadManifest);
  FRIEND_TEST_ALL_PREFIXES(ServicesCustomizationDocumentTest, MultiLanguage);
  friend class OobeLocalizationTest;
  friend void InitStartupCustomizationDocumentForTesting(
      const std::string& manifest);
  friend struct DefaultSingletonTraits<StartupCustomizationDocument>;

  
  StartupCustomizationDocument();

  
  StartupCustomizationDocument(system::StatisticsProvider* provider,
                               const std::string& manifest);

  virtual ~StartupCustomizationDocument();

  void Init(system::StatisticsProvider* provider);

  
  void InitFromMachineStatistic(const char* attr, std::string* value);

  std::string initial_locale_;
  std::vector<std::string> configured_locales_;
  std::string initial_timezone_;
  std::string keyboard_layout_;

  DISALLOW_COPY_AND_ASSIGN(StartupCustomizationDocument);
};

class ServicesCustomizationDocument : public CustomizationDocument,
                                      private net::URLFetcherDelegate {
 public:
  static ServicesCustomizationDocument* GetInstance();

  
  static void RegisterPrefs(PrefRegistrySimple* registry);
  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

  static const char kManifestUrl[];

  
  
  static bool WasOOBECustomizationApplied();

  
  void EnsureCustomizationApplied();

  
  base::Closure EnsureCustomizationAppliedClosure();

  
  void StartFetching();

  
  
  bool ApplyOOBECustomization();

  
  
  bool GetDefaultWallpaperUrl(GURL* out_url) const;

  
  bool GetDefaultApps(std::vector<std::string>* ids) const;

  
  
  extensions::ExternalLoader* CreateExternalLoader(Profile* profile);

  
  std::string GetOemAppsFolderName(const std::string& locale) const;

  
  
  static void InitializeForTesting();

  
  static void ShutdownForTesting();

  
  
  
  static base::FilePath GetCustomizedWallpaperCacheDir();
  static base::FilePath GetCustomizedWallpaperDownloadedFileName();

  CustomizationWallpaperDownloader* wallpaper_downloader_for_testing() {
    return wallpaper_downloader_.get();
  }

 private:
  friend struct DefaultSingletonTraits<ServicesCustomizationDocument>;
  FRIEND_TEST_ALL_PREFIXES(CustomizationWallpaperDownloaderBrowserTest,
                           OEMWallpaperIsPresent);
  FRIEND_TEST_ALL_PREFIXES(CustomizationWallpaperDownloaderBrowserTest,
                           OEMWallpaperRetryFetch);

  typedef std::vector<base::WeakPtr<ServicesCustomizationExternalLoader> >
      ExternalLoaders;

  
  class ApplyingTask;

  
  ServicesCustomizationDocument();

  
  explicit ServicesCustomizationDocument(const std::string& manifest);

  virtual ~ServicesCustomizationDocument();

  
  static void SetApplied(bool val);

  
  virtual bool LoadManifestFromString(const std::string& manifest) OVERRIDE;

  
  virtual void OnURLFetchComplete(const net::URLFetcher* source) OVERRIDE;

  
  void StartFileFetch();

  
  void DoStartFileFetch();

  
  static void ReadFileInBackground(
      base::WeakPtr<ServicesCustomizationDocument> self,
      const base::FilePath& file);

  
  void OnManifesteRead(const std::string& manifest);

  
  void OnManifestLoaded();

  
  static scoped_ptr<base::DictionaryValue> GetDefaultAppsInProviderFormat(
      const base::DictionaryValue& root);

  
  void UpdateCachedManifest(Profile* profile);

  
  void OnCustomizationNotFound();

  
  void SetOemFolderName(Profile* profile, const base::DictionaryValue& root);

  
  std::string GetOemAppsFolderNameImpl(
      const std::string& locale,
      const base::DictionaryValue& root) const;

  
  void StartOEMWallpaperDownload(const GURL& wallpaper_url,
                                 scoped_ptr<ApplyingTask> applying);

  
  
  
  void CheckAndApplyWallpaper();

  
  void OnCheckedWallpaperCacheExists(scoped_ptr<bool> exists,
                                     scoped_ptr<ApplyingTask> applying);

  
  void ApplyWallpaper(bool default_wallpaper_file_exists,
                      scoped_ptr<ApplyingTask> applying);

  
  
  
  void OnOEMWallpaperDownloaded(scoped_ptr<ApplyingTask> applying,
                                bool success,
                                const GURL& wallpaper_url);

  
  void ApplyingTaskStarted();

  
  void ApplyingTaskFinished(bool success);

  
  GURL url_;

  
  scoped_ptr<net::URLFetcher> url_fetcher_;

  
  int num_retries_;

  
  bool fetch_started_;

  
  base::TimeDelta network_delay_;

  
  ExternalLoaders external_loaders_;

  scoped_ptr<CustomizationWallpaperDownloader> wallpaper_downloader_;

  
  
  
  size_t apply_tasks_started_;
  size_t apply_tasks_finished_;

  
  
  
  size_t apply_tasks_success_;

  
  base::WeakPtrFactory<ServicesCustomizationDocument> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(ServicesCustomizationDocument);
};

}  

#endif  
