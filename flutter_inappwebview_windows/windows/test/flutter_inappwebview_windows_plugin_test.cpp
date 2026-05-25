#include <gtest/gtest.h>
#include <windows.h>

#include <string>

#include "plugin_window_registry.h"

namespace flutter_inappwebview_plugin {
namespace test {

namespace {

const wchar_t* kTestWindowClass = L"PluginWindowRegistryTestWindow";

void EnsureTestWindowClass()
{
  WNDCLASS windowClass = {};
  windowClass.lpszClassName = kTestWindowClass;
  windowClass.lpfnWndProc = &DefWindowProc;
  windowClass.hInstance = GetModuleHandle(nullptr);
  RegisterClass(&windowClass);
}

HWND CreateTestWindow(HWND parent = nullptr)
{
  EnsureTestWindowClass();
  return CreateWindowEx(0, kTestWindowClass, L"", parent ? WS_CHILD : 0,
    0, 0, 10, 10, parent, nullptr, GetModuleHandle(nullptr), nullptr);
}

}  // namespace

TEST(PluginWindowRegistry, DestroyRegisteredWindowIsIdempotent) {
  PluginWindowRegistry registry;
  HWND window = CreateTestWindow();
  ASSERT_TRUE(IsWindow(window));

  registry.Register(window, "test");
  EXPECT_TRUE(registry.IsRegistered(window));

  registry.DestroyRegisteredWindow(window, "test destroy");
  EXPECT_FALSE(IsWindow(window));
  EXPECT_FALSE(registry.IsRegistered(window));

  registry.DestroyRegisteredWindow(window, "test destroy again");
  EXPECT_EQ(registry.size(), 0u);
}

TEST(PluginWindowRegistry, DetachesRegisteredChildWhenFlutterWindowCloses) {
  PluginWindowRegistry registry;
  HWND flutterWindow = CreateTestWindow();
  HWND childWindow = CreateTestWindow(flutterWindow);
  ASSERT_TRUE(IsWindow(flutterWindow));
  ASSERT_TRUE(IsWindow(childWindow));
  ASSERT_EQ(GetParent(childWindow), flutterWindow);

  registry.Register(childWindow, "child");
  registry.DetachWindowsForFlutterWindow(flutterWindow, WM_DESTROY);

  EXPECT_EQ(GetParent(childWindow), HWND_MESSAGE);
  EXPECT_TRUE(registry.IsRegistered(childWindow));

  registry.DestroyRegisteredWindow(childWindow, "test cleanup");
  DestroyWindow(flutterWindow);
}

}  // namespace test
}  // namespace flutter_inappwebview_plugin
