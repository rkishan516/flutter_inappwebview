#ifndef FLUTTER_INAPPWEBVIEW_PLUGIN_PLUGIN_WINDOW_REGISTRY_H_
#define FLUTTER_INAPPWEBVIEW_PLUGIN_PLUGIN_WINDOW_REGISTRY_H_

#include <Windows.h>

#include <map>
#include <string>
#include <vector>

namespace flutter_inappwebview_plugin
{
  class PluginWindowRegistry {
  public:
    void Register(HWND hwnd, std::string owner);
    void Unregister(HWND hwnd);

    void DetachForDestroy(HWND hwnd, const std::string& reason);
    void DestroyRegisteredWindow(HWND hwnd, const std::string& reason);
    void DetachWindowsForFlutterWindow(HWND flutterWindow, UINT message);

    bool IsRegistered(HWND hwnd) const;
    size_t size() const;

  private:
    struct Entry {
      std::string owner;
      bool destroying = false;
    };

    std::map<HWND, Entry> windows_;

    std::vector<HWND> SnapshotRegisteredWindows() const;
    bool IsRelatedToFlutterWindow(HWND hwnd, HWND flutterWindow) const;
    void DetachSingleWindow(HWND hwnd, const std::string& reason);
    void DetachChildWindows(HWND hwnd, const std::string& reason);
    void DetachOwnedWindows(HWND hwnd, const std::string& reason);
    void LogWindowAction(const std::string& action, HWND hwnd, HWND parent,
      const std::string& owner, const std::string& reason) const;
  };
}

#endif // FLUTTER_INAPPWEBVIEW_PLUGIN_PLUGIN_WINDOW_REGISTRY_H_
