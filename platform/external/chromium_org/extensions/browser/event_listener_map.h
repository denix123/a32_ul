// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_EVENT_LISTENER_MAP_H_
#define EXTENSIONS_BROWSER_EVENT_LISTENER_MAP_H_

#include <map>
#include <set>
#include <string>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "extensions/common/event_filter.h"
#include "url/gurl.h"

namespace base {
class DictionaryValue;
}

namespace content {
class BrowserContext;
class RenderProcessHost;
}

class ListenerRemovalListener;

namespace extensions {
struct Event;

class EventListener {
 public:
  
  
  
  
  
  
  
  
  
  static scoped_ptr<EventListener> ForExtension(
      const std::string& event_name,
      const std::string& extension_id,
      content::RenderProcessHost* process,
      scoped_ptr<base::DictionaryValue> filter);
  static scoped_ptr<EventListener> ForURL(
      const std::string& event_name,
      const GURL& listener_url,
      content::RenderProcessHost* process,
      scoped_ptr<base::DictionaryValue> filter);

  ~EventListener();

  bool Equals(const EventListener* other) const;

  scoped_ptr<EventListener> Copy() const;

  
  bool IsLazy() const;

  
  void MakeLazy();

  
  
  content::BrowserContext* GetBrowserContext() const;

  const std::string& event_name() const { return event_name_; }
  const std::string& extension_id() const { return extension_id_; }
  const GURL& listener_url() const { return listener_url_; }
  content::RenderProcessHost* process() const { return process_; }
  base::DictionaryValue* filter() const { return filter_.get(); }
  EventFilter::MatcherID matcher_id() const { return matcher_id_; }
  void set_matcher_id(EventFilter::MatcherID id) { matcher_id_ = id; }

 private:
  EventListener(const std::string& event_name,
                const std::string& extension_id,
                const GURL& listener_url,
                content::RenderProcessHost* process,
                scoped_ptr<base::DictionaryValue> filter);

  const std::string event_name_;
  const std::string extension_id_;
  const GURL listener_url_;
  content::RenderProcessHost* process_;
  scoped_ptr<base::DictionaryValue> filter_;
  EventFilter::MatcherID matcher_id_;  

  DISALLOW_COPY_AND_ASSIGN(EventListener);
};

class EventListenerMap {
 public:
  typedef std::vector<linked_ptr<EventListener> > ListenerList;

  class Delegate {
   public:
    virtual ~Delegate() {}
    virtual void OnListenerAdded(const EventListener* listener) = 0;
    virtual void OnListenerRemoved(const EventListener* listener) = 0;
  };

  explicit EventListenerMap(Delegate* delegate);
  ~EventListenerMap();

  
  
  
  
  
  bool AddListener(scoped_ptr<EventListener> listener);

  
  
  bool RemoveListener(const EventListener* listener);

  
  std::set<const EventListener*> GetEventListeners(const Event& event);

  const ListenerList& GetEventListenersByName(const std::string& event_name) {
    return listeners_[event_name];
  }

  
  void RemoveListenersForProcess(const content::RenderProcessHost* process);

  
  bool HasListenerForEvent(const std::string& event_name);

  
  
  bool HasListenerForExtension(const std::string& extension_id,
                               const std::string& event_name);

  
  
  bool HasListener(const EventListener* listener);

  
  bool HasProcessListener(content::RenderProcessHost* process,
                          const std::string& extension_id);

  
  void RemoveLazyListenersForExtension(const std::string& extension_id);

  
  
  
  
  void LoadUnfilteredLazyListeners(const std::string& extension_id,
                                   const std::set<std::string>& event_names);

  
  
  
  void LoadFilteredLazyListeners(
      const std::string& extension_id,
      const base::DictionaryValue& filtered);

 private:
  
  typedef std::map<std::string, ListenerList> ListenerMap;

  void CleanupListener(EventListener* listener);
  bool IsFilteredEvent(const Event& event) const;
  scoped_ptr<EventMatcher> ParseEventMatcher(
      base::DictionaryValue* filter_dict);

  
  Delegate* delegate_;

  std::set<std::string> filtered_events_;
  ListenerMap listeners_;

  std::map<EventFilter::MatcherID, EventListener*> listeners_by_matcher_id_;

  EventFilter event_filter_;

  DISALLOW_COPY_AND_ASSIGN(EventListenerMap);
};

}  

#endif  
