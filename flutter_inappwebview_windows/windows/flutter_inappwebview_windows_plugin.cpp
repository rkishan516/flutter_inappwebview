#include "flutter_inappwebview_windows_plugin.h"

#include <flutter/plugin_registrar_windows.h>

#include "cookie_manager.h"
#include "headless_in_app_webview/headless_in_app_webview_manager.h"
#include "in_app_browser/in_app_browser_manager.h"
#include "in_app_webview/in_app_webview_manager.h"
#include "platform_util.h"
#include "webview_environment/webview_environment_manager.h"


#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "rpcrt4.lib")  // UuidCreate - Minimum supported OS Win 2000
#pragma comment(lib, "WindowsApp.lib")

namespace flutter_inappwebview_plugin
{
  // static
  void FlutterInappwebviewWindowsPlugin::RegisterWithRegistrar(
    flutter::PluginRegistrarWindows* registrar)
  {
    auto plugin = std::make_unique<FlutterInappwebviewWindowsPlugin>(registrar);
    registrar->AddPlugin(std::move(plugin));
  }

  FlutterInappwebviewWindowsPlugin::FlutterInappwebviewWindowsPlugin(flutter::PluginRegistrarWindows* registrar)
    : registrar(registrar)
  {
    windowRegistry = std::make_unique<PluginWindowRegistry>();
    webViewEnvironmentManager = std::make_unique<WebViewEnvironmentManager>(this);
    inAppWebViewManager = std::make_unique<InAppWebViewManager>(this);
    inAppBrowserManager = std::make_unique<InAppBrowserManager>(this);
    headlessInAppWebViewManager = std::make_unique<HeadlessInAppWebViewManager>(this);
    cookieManager = std::make_unique<CookieManager>(this);
    platformUtil = std::make_unique<PlatformUtil>(this);

    window_proc_id = registrar->RegisterTopLevelWindowProcDelegate(
      [this](HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
      {
        return HandleWindowProc(hWnd, message, wParam, lParam);
      });
  }

  FlutterInappwebviewWindowsPlugin::~FlutterInappwebviewWindowsPlugin()
  {
    if (registrar) {
      registrar->UnregisterTopLevelWindowProcDelegate(window_proc_id);
    }
    inAppWebViewManager = nullptr;
    inAppBrowserManager = nullptr;
    headlessInAppWebViewManager = nullptr;
    webViewEnvironmentManager = nullptr;
    cookieManager = nullptr;
    platformUtil = nullptr;
    windowRegistry = nullptr;
  }


  std::optional<LRESULT> FlutterInappwebviewWindowsPlugin::HandleWindowProc(
    HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam)
  {
    // When the Flutter view is being closed/destroyed, detach plugin-owned
    // HWNDs from it before the OS cascade-destroys them. Otherwise the
    // engine's WindowManager subclass can crash inside UpdatePopupPosition /
    // OnDestroyWindow on stale popup metadata (Sentry DESKTOP-NATIVE-3J).
    if ((message == WM_CLOSE || message == WM_DESTROY || message == WM_NCDESTROY) && windowRegistry) {
      windowRegistry->DetachWindowsForFlutterWindow(hWnd, message);
    }

    std::optional<LRESULT> result = std::nullopt;

    if (platformUtil) {
      result = platformUtil->HandleWindowProc(hWnd, message, wParam, lParam);
    }

    return result;
  }
}
