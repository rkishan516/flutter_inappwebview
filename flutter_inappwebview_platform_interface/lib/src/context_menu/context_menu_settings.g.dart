// GENERATED CODE - DO NOT MODIFY BY HAND

part of 'context_menu_settings.dart';

// **************************************************************************
// ExchangeableObjectGenerator
// **************************************************************************

///Class that represents available settings used by [ContextMenu].
class ContextMenuSettings {
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
  ContextMenuSettings({
    this.hideDefaultSystemContextMenuItems = false,
    this.keptDefaultSystemContextMenuItems,
  });

  ///Gets a possible [ContextMenuSettings] instance from a [Map] value.
  static ContextMenuSettings? fromMap(
    Map<String, dynamic>? map, {
    EnumMethod? enumMethod,
  }) {
    if (map == null) {
      return null;
    }
    final instance = ContextMenuSettings(
      keptDefaultSystemContextMenuItems:
          map['keptDefaultSystemContextMenuItems'] != null
          ? Set<String>.from(
              map['keptDefaultSystemContextMenuItems']!.cast<String>(),
            )
          : null,
    );
    if (map['hideDefaultSystemContextMenuItems'] != null) {
      instance.hideDefaultSystemContextMenuItems =
          map['hideDefaultSystemContextMenuItems'];
    }
    return instance;
  }

  ///Converts instance to a map.
  Map<String, dynamic> toMap({EnumMethod? enumMethod}) {
    return {
      "hideDefaultSystemContextMenuItems": hideDefaultSystemContextMenuItems,
      "keptDefaultSystemContextMenuItems": keptDefaultSystemContextMenuItems
          ?.toList(),
    };
  }

  ///Converts instance to a map.
  Map<String, dynamic> toJson() {
    return toMap();
  }

  ///Returns a copy of ContextMenuSettings.
  ContextMenuSettings copy() {
    return ContextMenuSettings.fromMap(toMap()) ?? ContextMenuSettings();
  }

  @override
  String toString() {
    return 'ContextMenuSettings{hideDefaultSystemContextMenuItems: $hideDefaultSystemContextMenuItems, keptDefaultSystemContextMenuItems: $keptDefaultSystemContextMenuItems}';
  }
}

///Use [ContextMenuSettings] instead.
@Deprecated('Use ContextMenuSettings instead')
class ContextMenuOptions {
  ///Whether all the default system context menu items should be hidden or not. The default value is `false`.
  bool hideDefaultSystemContextMenuItems;
  ContextMenuOptions({this.hideDefaultSystemContextMenuItems = false});

  ///Gets a possible [ContextMenuOptions] instance from a [Map] value.
  static ContextMenuOptions? fromMap(
    Map<String, dynamic>? map, {
    EnumMethod? enumMethod,
  }) {
    if (map == null) {
      return null;
    }
    final instance = ContextMenuOptions();
    if (map['hideDefaultSystemContextMenuItems'] != null) {
      instance.hideDefaultSystemContextMenuItems =
          map['hideDefaultSystemContextMenuItems'];
    }
    return instance;
  }

  ///Converts instance to a map.
  Map<String, dynamic> toMap({EnumMethod? enumMethod}) {
    return {
      "hideDefaultSystemContextMenuItems": hideDefaultSystemContextMenuItems,
    };
  }

  ///Converts instance to a map.
  Map<String, dynamic> toJson() {
    return toMap();
  }

  ///Returns a copy of ContextMenuOptions.
  ContextMenuOptions copy() {
    return ContextMenuOptions.fromMap(toMap()) ?? ContextMenuOptions();
  }

  @override
  String toString() {
    return 'ContextMenuOptions{hideDefaultSystemContextMenuItems: $hideDefaultSystemContextMenuItems}';
  }
}
