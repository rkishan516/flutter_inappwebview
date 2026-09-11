import 'package:flutter_inappwebview_internal_annotations/flutter_inappwebview_internal_annotations.dart';

import 'context_menu.dart';
import '../types/enum_method.dart';

part 'context_menu_settings.g.dart';

///Class that represents available settings used by [ContextMenu].
@ExchangeableObject(copyMethod: true)
class ContextMenuSettings_ {
  ///Whether all the default system context menu items should be hidden or not. The default value is `false`.
  bool hideDefaultSystemContextMenuItems;

  ///Names of the default system context menu items to keep even when
  ///[hideDefaultSystemContextMenuItems] is `true`, for example
  ///`{'cut', 'copy', 'paste', 'selectAll'}`. Lets you drop the browser chrome
  ///items while the native editing commands stay, keeping their localized
  ///labels, their enabled state and the platform clipboard.
  ///
  ///A name is the unlocalized English label of the item in lower camel case,
  ///as reported by WebView2 — the "Save as" item is `saveAs`. Names matching
  ///no default item are ignored.
  ///
  ///**NOTE**: only honored on the Windows platform at the moment.
  Set<String>? keptDefaultSystemContextMenuItems;

  ContextMenuSettings_({
    this.hideDefaultSystemContextMenuItems = false,
    this.keptDefaultSystemContextMenuItems,
  });
}

///Use [ContextMenuSettings] instead.
@Deprecated("Use ContextMenuSettings instead")
@ExchangeableObject(copyMethod: true)
class ContextMenuOptions_ {
  ///Whether all the default system context menu items should be hidden or not. The default value is `false`.
  bool hideDefaultSystemContextMenuItems;

  ContextMenuOptions_({this.hideDefaultSystemContextMenuItems = false});
}
