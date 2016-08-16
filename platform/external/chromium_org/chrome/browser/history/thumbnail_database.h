// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_HISTORY_THUMBNAIL_DATABASE_H_
#define CHROME_BROWSER_HISTORY_THUMBNAIL_DATABASE_H_

#include <vector>

#include "base/gtest_prod_util.h"
#include "base/memory/ref_counted.h"
#include "components/history/core/browser/history_types.h"
#include "sql/connection.h"
#include "sql/init_status.h"
#include "sql/meta_table.h"
#include "sql/statement.h"

namespace base {
class FilePath;
class RefCountedMemory;
class Time;
}

namespace history {

class HistoryClient;

class ThumbnailDatabase {
 public:
  explicit ThumbnailDatabase(HistoryClient* history_client);
  ~ThumbnailDatabase();

  
  
  sql::InitStatus Init(const base::FilePath& db_name);

  
  
  void ComputeDatabaseMetrics();

  
  void BeginTransaction();
  void CommitTransaction();
  int transaction_nesting() const {
    return db_.transaction_nesting();
  }
  void RollbackTransaction();

  
  
  void Vacuum();

  
  
  void TrimMemory(bool aggressively);

  

  
  
  
  
  
  
  bool GetFaviconBitmapIDSizes(
      favicon_base::FaviconID icon_id,
      std::vector<FaviconBitmapIDSize>* bitmap_id_sizes);

  
  
  bool GetFaviconBitmaps(favicon_base::FaviconID icon_id,
                         std::vector<FaviconBitmap>* favicon_bitmaps);

  
  
  bool GetFaviconBitmap(FaviconBitmapID bitmap_id,
                        base::Time* last_updated,
                        scoped_refptr<base::RefCountedMemory>* png_icon_data,
                        gfx::Size* pixel_size);

  
  
  
  
  
  
  
  
  FaviconBitmapID AddFaviconBitmap(
      favicon_base::FaviconID icon_id,
      const scoped_refptr<base::RefCountedMemory>& icon_data,
      base::Time time,
      const gfx::Size& pixel_size);

  
  
  
  bool SetFaviconBitmap(FaviconBitmapID bitmap_id,
                        scoped_refptr<base::RefCountedMemory> bitmap_data,
                        base::Time time);

  
  
  bool SetFaviconBitmapLastUpdateTime(FaviconBitmapID bitmap_id,
                                      base::Time time);

  
  
  bool DeleteFaviconBitmap(FaviconBitmapID bitmap_id);

  

  
  
  bool SetFaviconOutOfDate(favicon_base::FaviconID icon_id);

  
  
  
  
  
  
  
  favicon_base::FaviconID GetFaviconIDForFaviconURL(
      const GURL& icon_url,
      int required_icon_type,
      favicon_base::IconType* icon_type);

  
  bool GetFaviconHeader(favicon_base::FaviconID icon_id,
                        GURL* icon_url,
                        favicon_base::IconType* icon_type);

  
  
  favicon_base::FaviconID AddFavicon(const GURL& icon_url,
                                     favicon_base::IconType icon_type);

  
  
  favicon_base::FaviconID AddFavicon(
      const GURL& icon_url,
      favicon_base::IconType icon_type,
      const scoped_refptr<base::RefCountedMemory>& icon_data,
      base::Time time,
      const gfx::Size& pixel_size);

  
  bool DeleteFavicon(favicon_base::FaviconID id);

  
  
  
  
  
  

  
  
  
  
  
  
  
  bool GetIconMappingsForPageURL(const GURL& page_url,
                                 int required_icon_types,
                                 std::vector<IconMapping>* mapping_data);

  
  
  
  bool GetIconMappingsForPageURL(const GURL& page_url,
                                 std::vector<IconMapping>* mapping_data);

  
  
  IconMappingID AddIconMapping(const GURL& page_url,
                               favicon_base::FaviconID icon_id);

  
  
  
  bool UpdateIconMapping(IconMappingID mapping_id,
                         favicon_base::FaviconID icon_id);

  
  
  bool DeleteIconMappings(const GURL& page_url);

  
  
  bool DeleteIconMapping(IconMappingID mapping_id);

  
  bool HasMappingFor(favicon_base::FaviconID id);

  
  
  bool CloneIconMappings(const GURL& old_page_url, const GURL& new_page_url);

  
  
  class IconMappingEnumerator {
   public:
    IconMappingEnumerator();
    ~IconMappingEnumerator();

    
    bool GetNextIconMapping(IconMapping* icon_mapping);

   private:
    friend class ThumbnailDatabase;

    
    
    sql::Statement statement_;

    DISALLOW_COPY_AND_ASSIGN(IconMappingEnumerator);
  };

  
  bool InitIconMappingEnumerator(favicon_base::IconType type,
                                 IconMappingEnumerator* enumerator);

  
  
  
  bool RetainDataForPageUrls(const std::vector<GURL>& urls_to_keep);

 private:
  FRIEND_TEST_ALL_PREFIXES(ThumbnailDatabaseTest, RetainDataForPageUrls);
  FRIEND_TEST_ALL_PREFIXES(ThumbnailDatabaseTest, Version3);
  FRIEND_TEST_ALL_PREFIXES(ThumbnailDatabaseTest, Version4);
  FRIEND_TEST_ALL_PREFIXES(ThumbnailDatabaseTest, Version5);
  FRIEND_TEST_ALL_PREFIXES(ThumbnailDatabaseTest, Version6);
  FRIEND_TEST_ALL_PREFIXES(ThumbnailDatabaseTest, Version7);
  FRIEND_TEST_ALL_PREFIXES(ThumbnailDatabaseTest, WildSchema);

  
  
  
  
  sql::InitStatus OpenDatabase(sql::Connection* db,
                               const base::FilePath& db_name);

  
  
  
  sql::InitStatus InitImpl(const base::FilePath& db_name);

  
  sql::InitStatus CantUpgradeToVersion(int cur_version);

  
  bool UpgradeToVersion6();

  
  bool UpgradeToVersion7();

  
  bool IsFaviconDBStructureIncorrect();

  sql::Connection db_;
  sql::MetaTable meta_table_;

  HistoryClient* history_client_;
};

}  

#endif  
