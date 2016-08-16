// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_HISTORY_CORE_BROWSER_HISTORY_TYPES_H_
#define COMPONENTS_HISTORY_CORE_BROWSER_HISTORY_TYPES_H_

#include <deque>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/containers/stack_container.h"
#include "base/memory/ref_counted_memory.h"
#include "base/memory/scoped_vector.h"
#include "base/strings/string16.h"
#include "base/time/time.h"
#include "components/favicon_base/favicon_types.h"
#include "components/history/core/browser/url_row.h"
#include "components/history/core/common/thumbnail_score.h"
#include "ui/base/page_transition_types.h"
#include "ui/gfx/size.h"
#include "url/gurl.h"

class PageUsageData;

namespace content {
class WebContents;
}

namespace history {

class HistoryBackend;
class URLDatabase;

typedef std::vector<GURL> RedirectList;

typedef int64 FaviconBitmapID; 
typedef int64 SegmentID;  
typedef int64 IconMappingID; 

typedef content::WebContents* ContextID;

enum VisitSource {
  SOURCE_SYNCED = 0,         
  SOURCE_BROWSED = 1,        
  SOURCE_EXTENSION = 2,      
  SOURCE_FIREFOX_IMPORTED = 3,
  SOURCE_IE_IMPORTED = 4,
  SOURCE_SAFARI_IMPORTED = 5,
};

typedef int64 VisitID;
typedef std::map<VisitID, VisitSource> VisitSourceMap;


class VisitRow {
 public:
  VisitRow();
  VisitRow(URLID arg_url_id,
           base::Time arg_visit_time,
           VisitID arg_referring_visit,
           ui::PageTransition arg_transition,
           SegmentID arg_segment_id);
  ~VisitRow();

  
  VisitID visit_id;

  
  URLID url_id;

  base::Time visit_time;

  
  
  VisitID referring_visit;

  
  ui::PageTransition transition;

  
  
  SegmentID segment_id;

  
  
  
  
  base::TimeDelta visit_duration;

  
  bool operator<(const VisitRow& other) {
    return visit_time < other.visit_time;
  }

  
};

typedef std::vector<VisitRow> VisitVector;

typedef std::pair<base::Time, ui::PageTransition> VisitInfo;


struct PageVisit {
  URLID page_id;
  base::Time visit_time;
};


class QueryResults {
 public:
  typedef std::vector<URLResult*> URLResultVector;

  QueryResults();
  ~QueryResults();

  
  
  
  
  
  
  
  
  
  
  
  
  base::Time first_time_searched() const { return first_time_searched_; }
  void set_first_time_searched(base::Time t) { first_time_searched_ = t; }
  

  void set_reached_beginning(bool reached) { reached_beginning_ = reached; }
  bool reached_beginning() { return reached_beginning_; }

  size_t size() const { return results_.size(); }
  bool empty() const { return results_.empty(); }

  URLResult& back() { return *results_.back(); }
  const URLResult& back() const { return *results_.back(); }

  URLResult& operator[](size_t i) { return *results_[i]; }
  const URLResult& operator[](size_t i) const { return *results_[i]; }

  URLResultVector::const_iterator begin() const { return results_.begin(); }
  URLResultVector::const_iterator end() const { return results_.end(); }
  URLResultVector::const_reverse_iterator rbegin() const {
    return results_.rbegin();
  }
  URLResultVector::const_reverse_iterator rend() const {
    return results_.rend();
  }

  
  
  
  
  
  
  
  const size_t* MatchesForURL(const GURL& url, size_t* num_matches) const;

  
  
  void Swap(QueryResults* other);

  
  
  
  void AppendURLBySwapping(URLResult* result);

  
  void DeleteURL(const GURL& url);

  
  void DeleteRange(size_t begin, size_t end);

 private:
  
  
  
  
  typedef std::map<GURL, base::StackVector<size_t, 4> > URLToResultIndices;

  
  
  void AddURLUsageAtIndex(const GURL& url, size_t index);

  
  
  void AdjustResultMap(size_t begin, size_t end, ptrdiff_t delta);

  base::Time first_time_searched_;

  
  bool reached_beginning_;

  
  
  ScopedVector<URLResult> results_;

  
  URLToResultIndices url_to_results_;

  DISALLOW_COPY_AND_ASSIGN(QueryResults);
};


struct QueryOptions {
  QueryOptions();

  
  
  
  
  
  
  
  
  base::Time begin_time;
  base::Time end_time;

  
  void SetRecentDayRange(int days_ago);

  
  
  
  int max_count;

  enum DuplicateHandling {
    
    
    REMOVE_ALL_DUPLICATES,

    
    
    
    REMOVE_DUPLICATES_PER_DAY,

    
    KEEP_ALL_DUPLICATES
  };

  
  
  DuplicateHandling duplicate_policy;

  
  
  int EffectiveMaxCount() const;
  int64 EffectiveBeginTime() const;
  int64 EffectiveEndTime() const;
};


struct QueryURLResult {
  QueryURLResult();
  ~QueryURLResult();

  
  
  bool success;
  URLRow row;
  VisitVector visits;
};


struct VisibleVisitCountToHostResult {
  
  
  
  bool success;
  int count;
  base::Time first_visit;
};


struct MostVisitedURL {
  MostVisitedURL();
  MostVisitedURL(const GURL& url, const base::string16& title);
  MostVisitedURL(const GURL& url,
                 const base::string16& title,
                 const base::Time& last_forced_time);
  ~MostVisitedURL();

  GURL url;
  base::string16 title;

  
  
  
  base::Time last_forced_time;

  RedirectList redirects;

  bool operator==(const MostVisitedURL& other) {
    return url == other.url;
  }
};


struct FilteredURL {
  struct ExtendedInfo {
    ExtendedInfo();
    
    unsigned int total_visits;
    
    unsigned int visits;
    
    int64 duration_opened;
    
    base::Time last_visit_time;
  };

  FilteredURL();
  explicit FilteredURL(const PageUsageData& data);
  ~FilteredURL();

  GURL url;
  base::string16 title;
  double score;
  ExtendedInfo extended_info;
};


struct HistoryAddPageArgs {
  
  
  
  
  
  
  HistoryAddPageArgs();
  HistoryAddPageArgs(const GURL& url,
                     base::Time time,
                     ContextID context_id,
                     int32 page_id,
                     const GURL& referrer,
                     const history::RedirectList& redirects,
                     ui::PageTransition transition,
                     VisitSource source,
                     bool did_replace_entry);
  ~HistoryAddPageArgs();

  GURL url;
  base::Time time;

  ContextID context_id;
  int32 page_id;

  GURL referrer;
  history::RedirectList redirects;
  ui::PageTransition transition;
  VisitSource visit_source;
  bool did_replace_entry;
};


typedef std::vector<MostVisitedURL> MostVisitedURLList;
typedef std::vector<FilteredURL> FilteredURLList;

struct Images {
  Images();
  ~Images();

  scoped_refptr<base::RefCountedMemory> thumbnail;
  ThumbnailScore thumbnail_score;

  
  
};

struct MostVisitedURLWithRank {
  MostVisitedURL url;
  int rank;
};

typedef std::vector<MostVisitedURLWithRank> MostVisitedURLWithRankList;

struct TopSitesDelta {
  TopSitesDelta();
  ~TopSitesDelta();

  MostVisitedURLList deleted;
  MostVisitedURLWithRankList added;
  MostVisitedURLWithRankList moved;
};

typedef std::map<GURL, scoped_refptr<base::RefCountedBytes> > URLToThumbnailMap;

struct ThumbnailMigration {
  ThumbnailMigration();
  ~ThumbnailMigration();

  MostVisitedURLList most_visited;
  URLToThumbnailMap url_to_thumbnail_map;
};

typedef std::map<GURL, Images> URLToImagesMap;

class MostVisitedThumbnails
    : public base::RefCountedThreadSafe<MostVisitedThumbnails> {
 public:
  MostVisitedThumbnails();

  MostVisitedURLList most_visited;
  URLToImagesMap url_to_images_map;

 private:
  friend class base::RefCountedThreadSafe<MostVisitedThumbnails>;
  virtual ~MostVisitedThumbnails();

  DISALLOW_COPY_AND_ASSIGN(MostVisitedThumbnails);
};


struct IconMapping {
  IconMapping();
  ~IconMapping();

  
  IconMappingID mapping_id;

  
  GURL page_url;

  
  favicon_base::FaviconID icon_id;

  
  GURL icon_url;

  
  favicon_base::IconType icon_type;
};

struct FaviconBitmapIDSize {
  FaviconBitmapIDSize();
  ~FaviconBitmapIDSize();

  
  FaviconBitmapID bitmap_id;

  
  gfx::Size pixel_size;
};

struct FaviconBitmap {
  FaviconBitmap();
  ~FaviconBitmap();

  
  FaviconBitmapID bitmap_id;

  
  favicon_base::FaviconID icon_id;

  
  base::Time last_updated;

  
  scoped_refptr<base::RefCountedMemory> bitmap_data;

  
  gfx::Size pixel_size;
};

struct BriefVisitInfo {
  URLID url_id;
  base::Time time;
  ui::PageTransition transition;
};

class VisitDatabaseObserver {
 public:
  virtual ~VisitDatabaseObserver();
  virtual void OnAddVisit(const BriefVisitInfo& info) = 0;
};

struct ExpireHistoryArgs {
  ExpireHistoryArgs();
  ~ExpireHistoryArgs();

  
  
  void SetTimeRangeForOneDay(base::Time time);

  std::set<GURL> urls;
  base::Time begin_time;
  base::Time end_time;
};

}  

#endif  
