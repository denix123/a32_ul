// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_USERS_WALLPAPER_WALLPAPER_MANAGER_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_USERS_WALLPAPER_WALLPAPER_MANAGER_H_

#include <deque>
#include <string>
#include <vector>

#include "ash/desktop_background/desktop_background_controller.h"
#include "base/files/file_path.h"
#include "base/memory/ref_counted_memory.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/threading/sequenced_worker_pool.h"
#include "base/time/time.h"
#include "chrome/browser/chromeos/login/users/avatar/user_image_loader.h"
#include "chrome/browser/chromeos/settings/cros_settings.h"
#include "components/user_manager/user.h"
#include "components/user_manager/user_image/user_image.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "third_party/icu/source/i18n/unicode/timezone.h"
#include "ui/gfx/image/image_skia.h"

class PrefRegistrySimple;

namespace base {
class CommandLine;
class SequencedTaskRunner;
}

namespace user_manager {
class User;
class UserImage;
}

namespace chromeos {

struct WallpaperInfo {
  
  
  std::string location;
  ash::WallpaperLayout layout;
  user_manager::User::WallpaperType type;
  base::Time date;
  bool operator==(const WallpaperInfo& other) {
    return (location == other.location) && (layout == other.layout) &&
        (type == other.type);
  }
};

class MovableOnDestroyCallback;
typedef scoped_ptr<MovableOnDestroyCallback> MovableOnDestroyCallbackHolder;

class WallpaperManagerBrowserTest;

extern const char kWallpaperSequenceTokenName[];

extern const char kSmallWallpaperSuffix[];
extern const char kLargeWallpaperSuffix[];

extern const char kSmallWallpaperSubDir[];
extern const char kLargeWallpaperSubDir[];
extern const char kOriginalWallpaperSubDir[];
extern const char kThumbnailWallpaperSubDir[];

extern const int kSmallWallpaperMaxWidth;
extern const int kSmallWallpaperMaxHeight;
extern const int kLargeWallpaperMaxWidth;
extern const int kLargeWallpaperMaxHeight;

extern const int kWallpaperThumbnailWidth;
extern const int kWallpaperThumbnailHeight;

class WallpaperManager: public content::NotificationObserver {
 public:
  enum WallpaperResolution {
    WALLPAPER_RESOLUTION_LARGE,
    WALLPAPER_RESOLUTION_SMALL
  };

  
  class TestApi {
   public:
    explicit TestApi(WallpaperManager* wallpaper_manager);
    virtual ~TestApi();

    base::FilePath current_wallpaper_path();

    bool GetWallpaperFromCache(const std::string& user_id,
                               gfx::ImageSkia* image);

    void SetWallpaperCache(const std::string& user_id,
                           const gfx::ImageSkia& image);

    void ClearDisposableWallpaperCache();

   private:
    WallpaperManager* wallpaper_manager_;  

    DISALLOW_COPY_AND_ASSIGN(TestApi);
  };

  
  
  class CustomizedWallpaperRescaledFiles;

  class Observer {
   public:
    virtual ~Observer() {}
    virtual void OnWallpaperAnimationFinished(const std::string& user_id) = 0;
    virtual void OnUpdateWallpaperForTesting() {}
    virtual void OnPendingListEmptyForTesting() {}
  };

  
  
  
  
  
  
  
  
  
  class PendingWallpaper : public base::RefCountedThreadSafe<PendingWallpaper> {
   public:
    
    PendingWallpaper(const base::TimeDelta delay, const std::string& user_id);

    
    
    
    
    
    
    
    
    
    void ResetSetWallpaperImage(const gfx::ImageSkia& image,
                                const WallpaperInfo& info);
    void ResetLoadWallpaper(const WallpaperInfo& info);
    void ResetSetCustomWallpaper(const WallpaperInfo& info,
                                 const base::FilePath& wallpaper_path);
    void ResetSetDefaultWallpaper();

   private:
    friend class base::RefCountedThreadSafe<PendingWallpaper>;

    ~PendingWallpaper();

    
    void SetMode(const gfx::ImageSkia& image,
                 const WallpaperInfo& info,
                 const base::FilePath& wallpaper_path,
                 const bool is_default);

    
    void ProcessRequest();

    
    void OnWallpaperSet();

    std::string user_id_;
    WallpaperInfo info_;
    gfx::ImageSkia user_wallpaper_;
    base::FilePath wallpaper_path_;

    
    bool default_;

    
    
    MovableOnDestroyCallbackHolder on_finish_;
    base::OneShotTimer<WallpaperManager::PendingWallpaper> timer;

    
    base::Time started_load_at_;

    DISALLOW_COPY_AND_ASSIGN(PendingWallpaper);
  };

  WallpaperManager();
  virtual ~WallpaperManager();

  
  static WallpaperManager* Get();

  
  static void RegisterPrefs(PrefRegistrySimple* registry);

  
  
  
  static bool ResizeImage(const gfx::ImageSkia& image,
                          ash::WallpaperLayout layout,
                          int preferred_width,
                          int preferred_height,
                          scoped_refptr<base::RefCountedBytes>* output,
                          gfx::ImageSkia* output_skia);

  
  
  
  
  static bool ResizeAndSaveWallpaper(const gfx::ImageSkia& image,
                                     const base::FilePath& path,
                                     ash::WallpaperLayout layout,
                                     int preferred_width,
                                     int preferred_height,
                                     gfx::ImageSkia* output_skia);

  
  static WallpaperResolution GetAppropriateResolution();

  
  
  static base::FilePath GetCustomWallpaperPath(const char* sub_dir,
                                               const std::string& user_id_hash,
                                               const std::string& file);

  void SetCommandLineForTesting(base::CommandLine* command_line);

  
  
  void Shutdown();

  
  void AddObservers();

  
  
  void EnsureLoggedInUserWallpaperLoaded();

  
  bool GetLoggedInUserWallpaperInfo(WallpaperInfo* info);

  
  
  
  void InitializeWallpaper();

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  void RemoveUserWallpaperInfo(const std::string& user_id);

  
  void SetCustomWallpaperOnSanitizedUsername(const std::string& user_id,
                                             const gfx::ImageSkia& image,
                                             bool update_wallpaper,
                                             bool cryptohome_success,
                                             const std::string& user_id_hash);

  
  
  
  void SetCustomWallpaper(const std::string& user_id,
                          const std::string& user_id_hash,
                          const std::string& file,
                          ash::WallpaperLayout layout,
                          user_manager::User::WallpaperType type,
                          const gfx::ImageSkia& image,
                          bool update_wallpaper);

  
  
  
  
  
  void SetDefaultWallpaperPath(
      const base::FilePath& customized_default_wallpaper_file_small,
      scoped_ptr<gfx::ImageSkia> small_wallpaper_image,
      const base::FilePath& customized_default_wallpaper_file_large,
      scoped_ptr<gfx::ImageSkia> large_wallpaper_image);

  
  void SetDefaultWallpaperNow(const std::string& user_id);

  
  void SetDefaultWallpaperDelayed(const std::string& user_id);

  
  
  void SetUserWallpaperInfo(const std::string& user_id,
                            const WallpaperInfo& info,
                            bool is_persistent);

  
  void SetUserWallpaperNow(const std::string& user_id);

  
  void SetUserWallpaperDelayed(const std::string& user_id);

  
  
  void SetWallpaperFromImageSkia(const std::string& user_id,
                                 const gfx::ImageSkia& image,
                                 ash::WallpaperLayout layout,
                                 bool update_wallpaper);

  
  
  void UpdateWallpaper(bool clear_cache);

  
  void AddObserver(Observer* observer);

  
  void RemoveObserver(Observer* observer);

  
  bool IsPolicyControlled(const std::string& user_id) const;

  
  
  void OnPolicySet(const std::string& policy, const std::string& user_id);

  
  void OnPolicyCleared(const std::string& policy, const std::string& user_id);

  
  
  void OnPolicyFetched(const std::string& policy,
                       const std::string& user_id,
                       scoped_ptr<std::string> data);

  
  
  
  void SetCustomizedDefaultWallpaper(const GURL& wallpaper_url,
                                     const base::FilePath& downloaded_file,
                                     const base::FilePath& resized_directory);

  
  size_t GetPendingListSizeForTesting() const;

 private:
  friend class TestApi;
  friend class PendingWallpaper;
  friend class WallpaperManagerBrowserTest;
  friend class WallpaperManagerBrowserTestDefaultWallpaper;
  friend class WallpaperManagerPolicyTest;

  typedef std::map<std::string, gfx::ImageSkia> CustomWallpaperMap;


  
  
  static void SaveCustomWallpaper(const std::string& user_id_hash,
                                  const base::FilePath& path,
                                  ash::WallpaperLayout layout,
                                  scoped_ptr<gfx::ImageSkia> image);

  
  
  static void MoveCustomWallpapersOnWorker(
      const std::string& user_id,
      const std::string& user_id_hash,
      base::WeakPtr<WallpaperManager> weak_ptr);

  
  
  
  static void GetCustomWallpaperInternal(
      const std::string& user_id,
      const WallpaperInfo& info,
      const base::FilePath& wallpaper_path,
      bool update_wallpaper,
      MovableOnDestroyCallbackHolder on_finish,
      base::WeakPtr<WallpaperManager> weak_ptr);

  
  static void ResizeCustomizedDefaultWallpaper(
      scoped_ptr<gfx::ImageSkia> image,
      const user_manager::UserImage::RawImage& raw_image,
      const CustomizedWallpaperRescaledFiles* rescaled_files,
      bool* success,
      gfx::ImageSkia* small_wallpaper_image,
      gfx::ImageSkia* large_wallpaper_image);

  
  
  void InitInitialUserWallpaper(const std::string& user_id, bool is_persistent);

  
  
  void SetPolicyControlledWallpaper(const std::string& user_id,
                                    const user_manager::UserImage& user_image);

  
  bool GetWallpaperFromCache(const std::string& user_id, gfx::ImageSkia* image);

  
  int loaded_wallpapers() const { return loaded_wallpapers_; }

  
  
  
  
  
  
  
  
  
  
  void CacheUsersWallpapers();

  
  void CacheUserWallpaper(const std::string& user_id);

  
  
  void ClearDisposableWallpaperCache();

  
  void ClearObsoleteWallpaperPrefs();

  
  void DeleteUserWallpapers(const std::string& user_id,
                            const std::string& path_to_file);

  
  base::CommandLine* GetCommandLine();

  
  
  void InitializeRegisteredDeviceWallpaper();

  
  
  void LoadWallpaper(const std::string& user_id,
                     const WallpaperInfo& info,
                     bool update_wallpaper,
                     MovableOnDestroyCallbackHolder on_finish);

  
  
  void MoveCustomWallpapersSuccess(const std::string& user_id,
                                   const std::string& user_id_hash);

  
  
  
  
  void MoveLoggedInUserCustomWallpaper();

  
  
  bool GetUserWallpaperInfo(const std::string& user_id,
                            WallpaperInfo* info) const;

  
  
  
  void OnWallpaperDecoded(const std::string& user_id,
                          ash::WallpaperLayout layout,
                          bool update_wallpaper,
                          MovableOnDestroyCallbackHolder on_finish,
                          const user_manager::UserImage& user_image);

  
  void ScheduleSetUserWallpaper(const std::string& user_id, bool delayed);

  
  void DoSetDefaultWallpaper(
      const std::string& user_id,
      MovableOnDestroyCallbackHolder on_finish);

  
  
  void StartLoad(const std::string& user_id,
                 const WallpaperInfo& info,
                 bool update_wallpaper,
                 const base::FilePath& wallpaper_path,
                 MovableOnDestroyCallbackHolder on_finish);

  
  void SaveLastLoadTime(const base::TimeDelta elapsed);

  
  void NotifyAnimationFinished();

  
  
  PendingWallpaper* GetPendingWallpaper(const std::string& user_id,
                                        bool delayed);

  
  void RemovePendingWallpaperFromList(PendingWallpaper* pending);

  
  
  
  
  
  base::TimeDelta GetWallpaperLoadDelay() const;

  
  void SetCustomizedDefaultWallpaperAfterCheck(
      const GURL& wallpaper_url,
      const base::FilePath& downloaded_file,
      scoped_ptr<CustomizedWallpaperRescaledFiles> rescaled_files);

  
  void OnCustomizedDefaultWallpaperDecoded(
      const GURL& wallpaper_url,
      scoped_ptr<CustomizedWallpaperRescaledFiles> rescaled_files,
      const user_manager::UserImage& user_image);

  
  
  void OnCustomizedDefaultWallpaperResized(
      const GURL& wallpaper_url,
      scoped_ptr<CustomizedWallpaperRescaledFiles> rescaled_files,
      scoped_ptr<bool> success,
      scoped_ptr<gfx::ImageSkia> small_wallpaper_image,
      scoped_ptr<gfx::ImageSkia> large_wallpaper_image);

  
  
  void SetDefaultWallpaperPathsFromCommandLine(base::CommandLine* command_line);

  
  void OnDefaultWallpaperDecoded(const base::FilePath& path,
                                 const ash::WallpaperLayout layout,
                                 scoped_ptr<user_manager::UserImage>* result,
                                 MovableOnDestroyCallbackHolder on_finish,
                                 const user_manager::UserImage& user_image);

  
  void StartLoadAndSetDefaultWallpaper(
      const base::FilePath& path,
      const ash::WallpaperLayout layout,
      MovableOnDestroyCallbackHolder on_finish,
      scoped_ptr<user_manager::UserImage>* result_out);

  
  const char* GetCustomWallpaperSubdirForCurrentResolution();

  
  void CreateSolidDefaultWallpaper();

  
  int loaded_wallpapers_;

  
  base::SequencedWorkerPool::SequenceToken sequence_token_;

  
  scoped_refptr<base::SequencedTaskRunner> task_runner_;

  
  base::FilePath current_wallpaper_path_;

  
  scoped_refptr<UserImageLoader> wallpaper_loader_;

  
  WallpaperInfo current_user_wallpaper_info_;

  
  base::CommandLine* command_line_for_testing_;

  
  CustomWallpaperMap wallpaper_cache_;

  
  std::string last_selected_user_;

  bool should_cache_wallpaper_;

  scoped_ptr<CrosSettings::ObserverSubscription>
      show_user_name_on_signin_subscription_;

  content::NotificationRegistrar registrar_;

  ObserverList<Observer> observers_;

  

  
  base::Time last_load_finished_at_;

  
  std::deque<base::TimeDelta> last_load_times_;

  
  
  PendingWallpaper* pending_inactive_;

  
  
  
  typedef std::vector<scoped_refptr<PendingWallpaper> > PendingList;
  PendingList loading_;

  base::FilePath default_small_wallpaper_file_;
  base::FilePath default_large_wallpaper_file_;

  base::FilePath guest_small_wallpaper_file_;
  base::FilePath guest_large_wallpaper_file_;

  
  scoped_ptr<user_manager::UserImage> default_wallpaper_image_;

  base::WeakPtrFactory<WallpaperManager> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(WallpaperManager);
};

}  

#endif  
