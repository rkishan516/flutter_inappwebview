#include "plugin_window_registry.h"

#include <cstdint>
#include <sstream>

#include "utils/log.h"

namespace flutter_inappwebview_plugin
{
  namespace
  {
    std::string HwndToString(HWND hwnd)
    {
      std::ostringstream stream;
      stream << "0x" << std::hex
        << reinterpret_cast<uintptr_t>(hwnd);
      return stream.str();
    }

    BOOL CALLBACK CollectChildWindow(HWND hwnd, LPARAM lParam)
    {
      auto* windows = reinterpret_cast<std::vector<HWND>*>(lParam);
      windows->push_back(hwnd);
      return TRUE;
    }

    bool HasOwnerInChain(HWND hwnd, HWND owner)
    {
      for (HWND current = ::GetWindow(hwnd, GW_OWNER); current;
        current = ::GetWindow(current, GW_OWNER)) {
        if (current == owner) {
          return true;
        }
      }
      return false;
    }

    struct OwnedWindowSearch {
      HWND owner = nullptr;
      std::vector<HWND> windows;
    };

    BOOL CALLBACK CollectOwnedWindow(HWND hwnd, LPARAM lParam)
    {
      auto* search = reinterpret_cast<OwnedWindowSearch*>(lParam);
      if (HasOwnerInChain(hwnd, search->owner)) {
        search->windows.push_back(hwnd);
      }
      return TRUE;
    }

    const char* MessageName(UINT message)
    {
      switch (message) {
      case WM_CLOSE:
        return "WM_CLOSE";
      case WM_DESTROY:
        return "WM_DESTROY";
      case WM_NCDESTROY:
        return "WM_NCDESTROY";
      default:
        return "window message";
      }
    }
  }

  void PluginWindowRegistry::Register(HWND hwnd, std::string owner)
  {
    if (!hwnd || !::IsWindow(hwnd)) {
      return;
    }

    windows_[hwnd] = { std::move(owner), false };
    LogWindowAction("register", hwnd, ::GetParent(hwnd), windows_[hwnd].owner, "");
  }

  void PluginWindowRegistry::Unregister(HWND hwnd)
  {
    auto it = windows_.find(hwnd);
    if (it == windows_.end()) {
      return;
    }

    LogWindowAction("unregister", hwnd, ::IsWindow(hwnd) ? ::GetParent(hwnd) : nullptr,
      it->second.owner, "");
    windows_.erase(it);
  }

  void PluginWindowRegistry::DetachForDestroy(HWND hwnd, const std::string& reason)
  {
    if (!hwnd || !::IsWindow(hwnd)) {
      return;
    }

    DetachOwnedWindows(hwnd, reason);
    DetachChildWindows(hwnd, reason);
    DetachSingleWindow(hwnd, reason);
  }

  void PluginWindowRegistry::DestroyRegisteredWindow(HWND hwnd, const std::string& reason)
  {
    if (!hwnd || !::IsWindow(hwnd)) {
      Unregister(hwnd);
      return;
    }

    auto it = windows_.find(hwnd);
    if (it != windows_.end()) {
      if (it->second.destroying) {
        return;
      }
      it->second.destroying = true;
    }

    DetachForDestroy(hwnd, reason);

    if (::IsWindow(hwnd)) {
      LogWindowAction("destroy", hwnd, ::GetParent(hwnd),
        it != windows_.end() ? it->second.owner : "", reason);
      ::DestroyWindow(hwnd);
    }

    Unregister(hwnd);
  }

  void PluginWindowRegistry::DetachWindowsForFlutterWindow(HWND flutterWindow, UINT message)
  {
    if (!flutterWindow) {
      return;
    }

    const std::string reason = std::string("Flutter ") + MessageName(message);
    for (const auto hwnd : SnapshotRegisteredWindows()) {
      if (!::IsWindow(hwnd)) {
        Unregister(hwnd);
        continue;
      }
      if (IsRelatedToFlutterWindow(hwnd, flutterWindow)) {
        DetachForDestroy(hwnd, reason);
      }
    }
  }

  bool PluginWindowRegistry::IsRegistered(HWND hwnd) const
  {
    return windows_.find(hwnd) != windows_.end();
  }

  size_t PluginWindowRegistry::size() const
  {
    return windows_.size();
  }

  std::vector<HWND> PluginWindowRegistry::SnapshotRegisteredWindows() const
  {
    std::vector<HWND> windows;
    windows.reserve(windows_.size());
    for (const auto& entry : windows_) {
      windows.push_back(entry.first);
    }
    return windows;
  }

  bool PluginWindowRegistry::IsRelatedToFlutterWindow(HWND hwnd, HWND flutterWindow) const
  {
    if (hwnd == flutterWindow) {
      return true;
    }

    if (::GetAncestor(hwnd, GA_ROOT) == flutterWindow) {
      return true;
    }

    for (HWND parent = ::GetParent(hwnd); parent; parent = ::GetParent(parent)) {
      if (parent == flutterWindow) {
        return true;
      }
    }

    return HasOwnerInChain(hwnd, flutterWindow);
  }

  void PluginWindowRegistry::DetachSingleWindow(HWND hwnd, const std::string& reason)
  {
    if (!hwnd || !::IsWindow(hwnd)) {
      return;
    }

    const HWND parent = ::GetParent(hwnd);
    if (parent == HWND_MESSAGE) {
      return;
    }

    const auto it = windows_.find(hwnd);
    const std::string owner = it != windows_.end() ? it->second.owner : "";
    LogWindowAction("detach", hwnd, parent, owner, reason);
    ::SetParent(hwnd, HWND_MESSAGE);
  }

  void PluginWindowRegistry::DetachChildWindows(HWND hwnd, const std::string& reason)
  {
    std::vector<HWND> children;
    ::EnumChildWindows(hwnd, CollectChildWindow, reinterpret_cast<LPARAM>(&children));

    for (auto child : children) {
      DetachSingleWindow(child, reason);
    }
  }

  void PluginWindowRegistry::DetachOwnedWindows(HWND hwnd, const std::string& reason)
  {
    OwnedWindowSearch search;
    search.owner = hwnd;
    ::EnumWindows(CollectOwnedWindow, reinterpret_cast<LPARAM>(&search));

    for (auto ownedWindow : search.windows) {
      DetachForDestroy(ownedWindow, reason);
    }
  }

  void PluginWindowRegistry::LogWindowAction(const std::string& action, HWND hwnd,
    HWND parent, const std::string& owner, const std::string& reason) const
  {
    std::string message = "PluginWindowRegistry " + action +
      " hwnd=" + HwndToString(hwnd) +
      " parent=" + HwndToString(parent);
    if (!owner.empty()) {
      message += " owner=" + owner;
    }
    if (!reason.empty()) {
      message += " reason=" + reason;
    }
    debugLog(message);
  }
}
