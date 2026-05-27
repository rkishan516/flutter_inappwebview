import 'package:flutter_inappwebview_internal_annotations/flutter_inappwebview_internal_annotations.dart';

part 'context_menu_item_target_kind.g.dart';

///Class representing the kind of target the user right-clicked on when the
///context menu was requested. Used by [ContextMenuItem.targetKinds] to
///conditionally show a menu item only for certain targets (e.g. a "Copy"
///item that should only appear when text is selected).
@ExchangeableEnum()
class ContextMenuItemTargetKind_ {
  // ignore: unused_field
  final int _value;
  const ContextMenuItemTargetKind_._internal(this._value);

  ///The user right-clicked on the page itself (no specific target).
  static const PAGE = ContextMenuItemTargetKind_._internal(0);

  ///The user right-clicked on an image element.
  static const IMAGE = ContextMenuItemTargetKind_._internal(1);

  ///The user right-clicked on a region containing selected text.
  static const SELECTED_TEXT = ContextMenuItemTargetKind_._internal(2);

  ///The user right-clicked on an audio element.
  static const AUDIO = ContextMenuItemTargetKind_._internal(3);

  ///The user right-clicked on a video element.
  static const VIDEO = ContextMenuItemTargetKind_._internal(4);

  ///The user right-clicked on a link (HTML::a with href).
  static const LINK = ContextMenuItemTargetKind_._internal(5);

  ///The user right-clicked on an editable element (input, textarea,
  ///contenteditable).
  static const EDITABLE = ContextMenuItemTargetKind_._internal(6);
}
