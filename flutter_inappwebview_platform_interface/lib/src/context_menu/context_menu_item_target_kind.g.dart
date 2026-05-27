// GENERATED CODE - DO NOT MODIFY BY HAND

part of 'context_menu_item_target_kind.dart';

// **************************************************************************
// ExchangeableEnumGenerator
// **************************************************************************

///Class representing the kind of target the user right-clicked on when the
///context menu was requested. Used by [ContextMenuItem.targetKinds] to
///conditionally show a menu item only for certain targets (e.g. a "Copy"
///item that should only appear when text is selected).
class ContextMenuItemTargetKind {
  final int _value;
  final int? _nativeValue;
  const ContextMenuItemTargetKind._internal(this._value, this._nativeValue);
  // ignore: unused_element
  factory ContextMenuItemTargetKind._internalMultiPlatform(
    int value,
    Function nativeValue,
  ) => ContextMenuItemTargetKind._internal(value, nativeValue());

  ///The user right-clicked on an audio element.
  static const AUDIO = ContextMenuItemTargetKind._internal(3, 3);

  ///The user right-clicked on an editable element (input, textarea,
  ///contenteditable).
  static const EDITABLE = ContextMenuItemTargetKind._internal(6, 6);

  ///The user right-clicked on an image element.
  static const IMAGE = ContextMenuItemTargetKind._internal(1, 1);

  ///The user right-clicked on a link (HTML::a with href).
  static const LINK = ContextMenuItemTargetKind._internal(5, 5);

  ///The user right-clicked on the page itself (no specific target).
  static const PAGE = ContextMenuItemTargetKind._internal(0, 0);

  ///The user right-clicked on a region containing selected text.
  static const SELECTED_TEXT = ContextMenuItemTargetKind._internal(2, 2);

  ///The user right-clicked on a video element.
  static const VIDEO = ContextMenuItemTargetKind._internal(4, 4);

  ///Set of all values of [ContextMenuItemTargetKind].
  static final Set<ContextMenuItemTargetKind> values = [
    ContextMenuItemTargetKind.AUDIO,
    ContextMenuItemTargetKind.EDITABLE,
    ContextMenuItemTargetKind.IMAGE,
    ContextMenuItemTargetKind.LINK,
    ContextMenuItemTargetKind.PAGE,
    ContextMenuItemTargetKind.SELECTED_TEXT,
    ContextMenuItemTargetKind.VIDEO,
  ].toSet();

  ///Gets a possible [ContextMenuItemTargetKind] instance from [int] value.
  static ContextMenuItemTargetKind? fromValue(int? value) {
    if (value != null) {
      try {
        return ContextMenuItemTargetKind.values.firstWhere(
          (element) => element.toValue() == value,
        );
      } catch (e) {
        return null;
      }
    }
    return null;
  }

  ///Gets a possible [ContextMenuItemTargetKind] instance from a native value.
  static ContextMenuItemTargetKind? fromNativeValue(int? value) {
    if (value != null) {
      try {
        return ContextMenuItemTargetKind.values.firstWhere(
          (element) => element.toNativeValue() == value,
        );
      } catch (e) {
        return null;
      }
    }
    return null;
  }

  /// Gets a possible [ContextMenuItemTargetKind] instance value with name [name].
  ///
  /// Goes through [ContextMenuItemTargetKind.values] looking for a value with
  /// name [name], as reported by [ContextMenuItemTargetKind.name].
  /// Returns the first value with the given name, otherwise `null`.
  static ContextMenuItemTargetKind? byName(String? name) {
    if (name != null) {
      try {
        return ContextMenuItemTargetKind.values.firstWhere(
          (element) => element.name() == name,
        );
      } catch (e) {
        return null;
      }
    }
    return null;
  }

  /// Creates a map from the names of [ContextMenuItemTargetKind] values to the values.
  ///
  /// The collection that this method is called on is expected to have
  /// values with distinct names, like the `values` list of an enum class.
  /// Only one value for each name can occur in the created map,
  /// so if two or more values have the same name (either being the
  /// same value, or being values of different enum type), at most one of
  /// them will be represented in the returned map.
  static Map<String, ContextMenuItemTargetKind> asNameMap() =>
      <String, ContextMenuItemTargetKind>{
        for (final value in ContextMenuItemTargetKind.values)
          value.name(): value,
      };

  ///Gets [int] value.
  int toValue() => _value;

  ///Gets [int] native value if supported by the current platform, otherwise `null`.
  int? toNativeValue() => _nativeValue;

  ///Gets the name of the value.
  String name() {
    switch (_value) {
      case 3:
        return 'AUDIO';
      case 6:
        return 'EDITABLE';
      case 1:
        return 'IMAGE';
      case 5:
        return 'LINK';
      case 0:
        return 'PAGE';
      case 2:
        return 'SELECTED_TEXT';
      case 4:
        return 'VIDEO';
    }
    return _value.toString();
  }

  @override
  int get hashCode => _value.hashCode;

  @override
  bool operator ==(value) => value == _value;

  ///Checks if the value is supported by the [defaultTargetPlatform].
  bool isSupported() {
    return _nativeValue != null;
  }

  @override
  String toString() {
    return name();
  }
}
