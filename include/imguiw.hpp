#include "imgui.h"
#include "rlImGui.h"

#include "raylibw.hpp"

namespace pkpy{

inline PyObject* py_var(VM* vm, ImVec2 im_vec){
    Vec2 vec(im_vec.x, im_vec.y);
    return py_var(vm, vec);
}

inline PyObject* py_var(VM* vm, ImVec4 im_vec){
    Vec4 vec(im_vec.x, im_vec.y, im_vec.z, im_vec.w);
    return py_var(vm, vec);
}

template<>
inline ImVec2 py_cast<ImVec2>(VM* vm, PyObject* obj){
    Vec2 vec = py_cast<Vec2>(vm, obj);
    return ImVec2(vec.x, vec.y);
}

template<>
inline ImVec4 py_cast<ImVec4>(VM* vm, PyObject* obj){
    Vec4 vec = py_cast<Vec4>(vm, obj);
    return ImVec4(vec.x, vec.y, vec.z, vec.w);
}

static void register_imgui_enums(VM* vm, PyObject* mod){
    vm->exec(
    "# ImDrawFlags_\n"
    "ImDrawFlags_None = 0\n"
    "ImDrawFlags_Closed = 1\n"
    "ImDrawFlags_RoundCornersTopLeft = 16\n"
    "ImDrawFlags_RoundCornersTopRight = 32\n"
    "ImDrawFlags_RoundCornersBottomLeft = 64\n"
    "ImDrawFlags_RoundCornersBottomRight = 128\n"
    "ImDrawFlags_RoundCornersNone = 256\n"
    "ImDrawFlags_RoundCornersTop = 48\n"
    "ImDrawFlags_RoundCornersBottom = 192\n"
    "ImDrawFlags_RoundCornersLeft = 80\n"
    "ImDrawFlags_RoundCornersRight = 160\n"
    "ImDrawFlags_RoundCornersAll = 240\n"
    "ImDrawFlags_RoundCornersDefault_ = 240\n"
    "ImDrawFlags_RoundCornersMask_ = 496\n"
    "\n"
    "# ImDrawListFlags_\n"
    "ImDrawListFlags_None = 0\n"
    "ImDrawListFlags_AntiAliasedLines = 1\n"
    "ImDrawListFlags_AntiAliasedLinesUseTex = 2\n"
    "ImDrawListFlags_AntiAliasedFill = 4\n"
    "ImDrawListFlags_AllowVtxOffset = 8\n"
    "\n"
    "# ImFontAtlasFlags_\n"
    "ImFontAtlasFlags_None = 0\n"
    "ImFontAtlasFlags_NoPowerOfTwoHeight = 1\n"
    "ImFontAtlasFlags_NoMouseCursors = 2\n"
    "ImFontAtlasFlags_NoBakedLines = 4\n"
    "\n"
    "# ImGuiActivateFlags_\n"
    "ImGuiActivateFlags_None = 0\n"
    "ImGuiActivateFlags_PreferInput = 1\n"
    "ImGuiActivateFlags_PreferTweak = 2\n"
    "ImGuiActivateFlags_TryToPreserveState = 4\n"
    "\n"
    "# ImGuiAxis\n"
    "ImGuiAxis_None = -1\n"
    "ImGuiAxis_X = 0\n"
    "ImGuiAxis_Y = 1\n"
    "\n"
    "# ImGuiBackendFlags_\n"
    "ImGuiBackendFlags_None = 0\n"
    "ImGuiBackendFlags_HasGamepad = 1\n"
    "ImGuiBackendFlags_HasMouseCursors = 2\n"
    "ImGuiBackendFlags_HasSetMousePos = 4\n"
    "ImGuiBackendFlags_RendererHasVtxOffset = 8\n"
    "\n"
    "# ImGuiButtonFlagsPrivate_\n"
    "ImGuiButtonFlags_PressedOnClick = 16\n"
    "ImGuiButtonFlags_PressedOnClickRelease = 32\n"
    "ImGuiButtonFlags_PressedOnClickReleaseAnywhere = 64\n"
    "ImGuiButtonFlags_PressedOnRelease = 128\n"
    "ImGuiButtonFlags_PressedOnDoubleClick = 256\n"
    "ImGuiButtonFlags_PressedOnDragDropHold = 512\n"
    "ImGuiButtonFlags_Repeat = 1024\n"
    "ImGuiButtonFlags_FlattenChildren = 2048\n"
    "ImGuiButtonFlags_AllowOverlap = 4096\n"
    "ImGuiButtonFlags_DontClosePopups = 8192\n"
    "ImGuiButtonFlags_AlignTextBaseLine = 32768\n"
    "ImGuiButtonFlags_NoKeyModifiers = 65536\n"
    "ImGuiButtonFlags_NoHoldingActiveId = 131072\n"
    "ImGuiButtonFlags_NoNavFocus = 262144\n"
    "ImGuiButtonFlags_NoHoveredOnFocus = 524288\n"
    "ImGuiButtonFlags_NoSetKeyOwner = 1048576\n"
    "ImGuiButtonFlags_NoTestKeyOwner = 2097152\n"
    "ImGuiButtonFlags_PressedOnMask_ = 1008\n"
    "ImGuiButtonFlags_PressedOnDefault_ = 32\n"
    "\n"
    "# ImGuiButtonFlags_\n"
    "ImGuiButtonFlags_None = 0\n"
    "ImGuiButtonFlags_MouseButtonLeft = 1\n"
    "ImGuiButtonFlags_MouseButtonRight = 2\n"
    "ImGuiButtonFlags_MouseButtonMiddle = 4\n"
    "ImGuiButtonFlags_MouseButtonMask_ = 7\n"
    "ImGuiButtonFlags_MouseButtonDefault_ = 1\n"
    "\n"
    "# ImGuiCol_\n"
    "ImGuiCol_Text = 0\n"
    "ImGuiCol_TextDisabled = 1\n"
    "ImGuiCol_WindowBg = 2\n"
    "ImGuiCol_ChildBg = 3\n"
    "ImGuiCol_PopupBg = 4\n"
    "ImGuiCol_Border = 5\n"
    "ImGuiCol_BorderShadow = 6\n"
    "ImGuiCol_FrameBg = 7\n"
    "ImGuiCol_FrameBgHovered = 8\n"
    "ImGuiCol_FrameBgActive = 9\n"
    "ImGuiCol_TitleBg = 10\n"
    "ImGuiCol_TitleBgActive = 11\n"
    "ImGuiCol_TitleBgCollapsed = 12\n"
    "ImGuiCol_MenuBarBg = 13\n"
    "ImGuiCol_ScrollbarBg = 14\n"
    "ImGuiCol_ScrollbarGrab = 15\n"
    "ImGuiCol_ScrollbarGrabHovered = 16\n"
    "ImGuiCol_ScrollbarGrabActive = 17\n"
    "ImGuiCol_CheckMark = 18\n"
    "ImGuiCol_SliderGrab = 19\n"
    "ImGuiCol_SliderGrabActive = 20\n"
    "ImGuiCol_Button = 21\n"
    "ImGuiCol_ButtonHovered = 22\n"
    "ImGuiCol_ButtonActive = 23\n"
    "ImGuiCol_Header = 24\n"
    "ImGuiCol_HeaderHovered = 25\n"
    "ImGuiCol_HeaderActive = 26\n"
    "ImGuiCol_Separator = 27\n"
    "ImGuiCol_SeparatorHovered = 28\n"
    "ImGuiCol_SeparatorActive = 29\n"
    "ImGuiCol_ResizeGrip = 30\n"
    "ImGuiCol_ResizeGripHovered = 31\n"
    "ImGuiCol_ResizeGripActive = 32\n"
    "ImGuiCol_Tab = 33\n"
    "ImGuiCol_TabHovered = 34\n"
    "ImGuiCol_TabActive = 35\n"
    "ImGuiCol_TabUnfocused = 36\n"
    "ImGuiCol_TabUnfocusedActive = 37\n"
    "ImGuiCol_PlotLines = 38\n"
    "ImGuiCol_PlotLinesHovered = 39\n"
    "ImGuiCol_PlotHistogram = 40\n"
    "ImGuiCol_PlotHistogramHovered = 41\n"
    "ImGuiCol_TableHeaderBg = 42\n"
    "ImGuiCol_TableBorderStrong = 43\n"
    "ImGuiCol_TableBorderLight = 44\n"
    "ImGuiCol_TableRowBg = 45\n"
    "ImGuiCol_TableRowBgAlt = 46\n"
    "ImGuiCol_TextSelectedBg = 47\n"
    "ImGuiCol_DragDropTarget = 48\n"
    "ImGuiCol_NavHighlight = 49\n"
    "ImGuiCol_NavWindowingHighlight = 50\n"
    "ImGuiCol_NavWindowingDimBg = 51\n"
    "ImGuiCol_ModalWindowDimBg = 52\n"
    "ImGuiCol_COUNT = 53\n"
    "\n"
    "# ImGuiColorEditFlags_\n"
    "ImGuiColorEditFlags_None = 0\n"
    "ImGuiColorEditFlags_NoAlpha = 2\n"
    "ImGuiColorEditFlags_NoPicker = 4\n"
    "ImGuiColorEditFlags_NoOptions = 8\n"
    "ImGuiColorEditFlags_NoSmallPreview = 16\n"
    "ImGuiColorEditFlags_NoInputs = 32\n"
    "ImGuiColorEditFlags_NoTooltip = 64\n"
    "ImGuiColorEditFlags_NoLabel = 128\n"
    "ImGuiColorEditFlags_NoSidePreview = 256\n"
    "ImGuiColorEditFlags_NoDragDrop = 512\n"
    "ImGuiColorEditFlags_NoBorder = 1024\n"
    "ImGuiColorEditFlags_AlphaBar = 65536\n"
    "ImGuiColorEditFlags_AlphaPreview = 131072\n"
    "ImGuiColorEditFlags_AlphaPreviewHalf = 262144\n"
    "ImGuiColorEditFlags_HDR = 524288\n"
    "ImGuiColorEditFlags_DisplayRGB = 1048576\n"
    "ImGuiColorEditFlags_DisplayHSV = 2097152\n"
    "ImGuiColorEditFlags_DisplayHex = 4194304\n"
    "ImGuiColorEditFlags_Uint8 = 8388608\n"
    "ImGuiColorEditFlags_Float = 16777216\n"
    "ImGuiColorEditFlags_PickerHueBar = 33554432\n"
    "ImGuiColorEditFlags_PickerHueWheel = 67108864\n"
    "ImGuiColorEditFlags_InputRGB = 134217728\n"
    "ImGuiColorEditFlags_InputHSV = 268435456\n"
    "ImGuiColorEditFlags_DefaultOptions_ = 177209344\n"
    "ImGuiColorEditFlags_DisplayMask_ = 7340032\n"
    "ImGuiColorEditFlags_DataTypeMask_ = 25165824\n"
    "ImGuiColorEditFlags_PickerMask_ = 100663296\n"
    "ImGuiColorEditFlags_InputMask_ = 402653184\n"
    "\n"
    "# ImGuiComboFlagsPrivate_\n"
    "ImGuiComboFlags_CustomPreview = 1048576\n"
    "\n"
    "# ImGuiComboFlags_\n"
    "ImGuiComboFlags_None = 0\n"
    "ImGuiComboFlags_PopupAlignLeft = 1\n"
    "ImGuiComboFlags_HeightSmall = 2\n"
    "ImGuiComboFlags_HeightRegular = 4\n"
    "ImGuiComboFlags_HeightLarge = 8\n"
    "ImGuiComboFlags_HeightLargest = 16\n"
    "ImGuiComboFlags_NoArrowButton = 32\n"
    "ImGuiComboFlags_NoPreview = 64\n"
    "ImGuiComboFlags_HeightMask_ = 30\n"
    "\n"
    "# ImGuiCond_\n"
    "ImGuiCond_None = 0\n"
    "ImGuiCond_Always = 1\n"
    "ImGuiCond_Once = 2\n"
    "ImGuiCond_FirstUseEver = 4\n"
    "ImGuiCond_Appearing = 8\n"
    "\n"
    "# ImGuiConfigFlags_\n"
    "ImGuiConfigFlags_None = 0\n"
    "ImGuiConfigFlags_NavEnableKeyboard = 1\n"
    "ImGuiConfigFlags_NavEnableGamepad = 2\n"
    "ImGuiConfigFlags_NavEnableSetMousePos = 4\n"
    "ImGuiConfigFlags_NavNoCaptureKeyboard = 8\n"
    "ImGuiConfigFlags_NoMouse = 16\n"
    "ImGuiConfigFlags_NoMouseCursorChange = 32\n"
    "ImGuiConfigFlags_IsSRGB = 1048576\n"
    "ImGuiConfigFlags_IsTouchScreen = 2097152\n"
    "\n"
    "# ImGuiContextHookType\n"
    "ImGuiContextHookType_NewFramePre = 0\n"
    "ImGuiContextHookType_NewFramePost = 1\n"
    "ImGuiContextHookType_EndFramePre = 2\n"
    "ImGuiContextHookType_EndFramePost = 3\n"
    "ImGuiContextHookType_RenderPre = 4\n"
    "ImGuiContextHookType_RenderPost = 5\n"
    "ImGuiContextHookType_Shutdown = 6\n"
    "ImGuiContextHookType_PendingRemoval_ = 7\n"
    "\n"
    "# ImGuiDataTypePrivate_\n"
    "ImGuiDataType_String = 11\n"
    "ImGuiDataType_Pointer = 12\n"
    "ImGuiDataType_ID = 13\n"
    "\n"
    "# ImGuiDataType_\n"
    "ImGuiDataType_S8 = 0\n"
    "ImGuiDataType_U8 = 1\n"
    "ImGuiDataType_S16 = 2\n"
    "ImGuiDataType_U16 = 3\n"
    "ImGuiDataType_S32 = 4\n"
    "ImGuiDataType_U32 = 5\n"
    "ImGuiDataType_S64 = 6\n"
    "ImGuiDataType_U64 = 7\n"
    "ImGuiDataType_Float = 8\n"
    "ImGuiDataType_Double = 9\n"
    "ImGuiDataType_COUNT = 10\n"
    "\n"
    "# ImGuiDebugLogFlags_\n"
    "ImGuiDebugLogFlags_None = 0\n"
    "ImGuiDebugLogFlags_EventActiveId = 1\n"
    "ImGuiDebugLogFlags_EventFocus = 2\n"
    "ImGuiDebugLogFlags_EventPopup = 4\n"
    "ImGuiDebugLogFlags_EventNav = 8\n"
    "ImGuiDebugLogFlags_EventClipper = 16\n"
    "ImGuiDebugLogFlags_EventSelection = 32\n"
    "ImGuiDebugLogFlags_EventIO = 64\n"
    "ImGuiDebugLogFlags_EventMask_ = 127\n"
    "ImGuiDebugLogFlags_OutputToTTY = 1024\n"
    "\n"
    "# ImGuiDir_\n"
    "ImGuiDir_None = -1\n"
    "ImGuiDir_Left = 0\n"
    "ImGuiDir_Right = 1\n"
    "ImGuiDir_Up = 2\n"
    "ImGuiDir_Down = 3\n"
    "ImGuiDir_COUNT = 4\n"
    "\n"
    "# ImGuiDragDropFlags_\n"
    "ImGuiDragDropFlags_None = 0\n"
    "ImGuiDragDropFlags_SourceNoPreviewTooltip = 1\n"
    "ImGuiDragDropFlags_SourceNoDisableHover = 2\n"
    "ImGuiDragDropFlags_SourceNoHoldToOpenOthers = 4\n"
    "ImGuiDragDropFlags_SourceAllowNullID = 8\n"
    "ImGuiDragDropFlags_SourceExtern = 16\n"
    "ImGuiDragDropFlags_SourceAutoExpirePayload = 32\n"
    "ImGuiDragDropFlags_AcceptBeforeDelivery = 1024\n"
    "ImGuiDragDropFlags_AcceptNoDrawDefaultRect = 2048\n"
    "ImGuiDragDropFlags_AcceptNoPreviewTooltip = 4096\n"
    "ImGuiDragDropFlags_AcceptPeekOnly = 3072\n"
    "\n"
    "# ImGuiFocusRequestFlags_\n"
    "ImGuiFocusRequestFlags_None = 0\n"
    "ImGuiFocusRequestFlags_RestoreFocusedChild = 1\n"
    "ImGuiFocusRequestFlags_UnlessBelowModal = 2\n"
    "\n"
    "# ImGuiFocusedFlags_\n"
    "ImGuiFocusedFlags_None = 0\n"
    "ImGuiFocusedFlags_ChildWindows = 1\n"
    "ImGuiFocusedFlags_RootWindow = 2\n"
    "ImGuiFocusedFlags_AnyWindow = 4\n"
    "ImGuiFocusedFlags_NoPopupHierarchy = 8\n"
    "ImGuiFocusedFlags_RootAndChildWindows = 3\n"
    "\n"
    "# ImGuiHoveredFlagsPrivate_\n"
    "ImGuiHoveredFlags_DelayMask_ = 245760\n"
    "ImGuiHoveredFlags_AllowedMaskForIsWindowHovered = 12463\n"
    "ImGuiHoveredFlags_AllowedMaskForIsItemHovered = 262048\n"
    "\n"
    "# ImGuiHoveredFlags_\n"
    "ImGuiHoveredFlags_None = 0\n"
    "ImGuiHoveredFlags_ChildWindows = 1\n"
    "ImGuiHoveredFlags_RootWindow = 2\n"
    "ImGuiHoveredFlags_AnyWindow = 4\n"
    "ImGuiHoveredFlags_NoPopupHierarchy = 8\n"
    "ImGuiHoveredFlags_AllowWhenBlockedByPopup = 32\n"
    "ImGuiHoveredFlags_AllowWhenBlockedByActiveItem = 128\n"
    "ImGuiHoveredFlags_AllowWhenOverlappedByItem = 256\n"
    "ImGuiHoveredFlags_AllowWhenOverlappedByWindow = 512\n"
    "ImGuiHoveredFlags_AllowWhenDisabled = 1024\n"
    "ImGuiHoveredFlags_NoNavOverride = 2048\n"
    "ImGuiHoveredFlags_AllowWhenOverlapped = 768\n"
    "ImGuiHoveredFlags_RectOnly = 928\n"
    "ImGuiHoveredFlags_RootAndChildWindows = 3\n"
    "ImGuiHoveredFlags_ForTooltip = 4096\n"
    "ImGuiHoveredFlags_Stationary = 8192\n"
    "ImGuiHoveredFlags_DelayNone = 16384\n"
    "ImGuiHoveredFlags_DelayShort = 32768\n"
    "ImGuiHoveredFlags_DelayNormal = 65536\n"
    "ImGuiHoveredFlags_NoSharedDelay = 131072\n"
    "\n"
    "# ImGuiInputEventType\n"
    "ImGuiInputEventType_None = 0\n"
    "ImGuiInputEventType_MousePos = 1\n"
    "ImGuiInputEventType_MouseWheel = 2\n"
    "ImGuiInputEventType_MouseButton = 3\n"
    "ImGuiInputEventType_Key = 4\n"
    "ImGuiInputEventType_Text = 5\n"
    "ImGuiInputEventType_Focus = 6\n"
    "ImGuiInputEventType_COUNT = 7\n"
    "\n"
    "# ImGuiInputFlags_\n"
    "ImGuiInputFlags_None = 0\n"
    "ImGuiInputFlags_Repeat = 1\n"
    "ImGuiInputFlags_RepeatRateDefault = 2\n"
    "ImGuiInputFlags_RepeatRateNavMove = 4\n"
    "ImGuiInputFlags_RepeatRateNavTweak = 8\n"
    "ImGuiInputFlags_RepeatRateMask_ = 14\n"
    "ImGuiInputFlags_CondHovered = 16\n"
    "ImGuiInputFlags_CondActive = 32\n"
    "ImGuiInputFlags_CondDefault_ = 48\n"
    "ImGuiInputFlags_CondMask_ = 48\n"
    "ImGuiInputFlags_LockThisFrame = 64\n"
    "ImGuiInputFlags_LockUntilRelease = 128\n"
    "ImGuiInputFlags_RouteFocused = 256\n"
    "ImGuiInputFlags_RouteGlobalLow = 512\n"
    "ImGuiInputFlags_RouteGlobal = 1024\n"
    "ImGuiInputFlags_RouteGlobalHigh = 2048\n"
    "ImGuiInputFlags_RouteMask_ = 3840\n"
    "ImGuiInputFlags_RouteAlways = 4096\n"
    "ImGuiInputFlags_RouteUnlessBgFocused = 8192\n"
    "ImGuiInputFlags_RouteExtraMask_ = 12288\n"
    "ImGuiInputFlags_SupportedByIsKeyPressed = 15\n"
    "ImGuiInputFlags_SupportedByShortcut = 16143\n"
    "ImGuiInputFlags_SupportedBySetKeyOwner = 192\n"
    "ImGuiInputFlags_SupportedBySetItemKeyOwner = 240\n"
    "\n"
    "# ImGuiInputSource\n"
    "ImGuiInputSource_None = 0\n"
    "ImGuiInputSource_Mouse = 1\n"
    "ImGuiInputSource_Keyboard = 2\n"
    "ImGuiInputSource_Gamepad = 3\n"
    "ImGuiInputSource_Clipboard = 4\n"
    "ImGuiInputSource_COUNT = 5\n"
    "\n"
    "# ImGuiInputTextFlagsPrivate_\n"
    "ImGuiInputTextFlags_Multiline = 67108864\n"
    "ImGuiInputTextFlags_NoMarkEdited = 134217728\n"
    "ImGuiInputTextFlags_MergedItem = 268435456\n"
    "\n"
    "# ImGuiInputTextFlags_\n"
    "ImGuiInputTextFlags_None = 0\n"
    "ImGuiInputTextFlags_CharsDecimal = 1\n"
    "ImGuiInputTextFlags_CharsHexadecimal = 2\n"
    "ImGuiInputTextFlags_CharsUppercase = 4\n"
    "ImGuiInputTextFlags_CharsNoBlank = 8\n"
    "ImGuiInputTextFlags_AutoSelectAll = 16\n"
    "ImGuiInputTextFlags_EnterReturnsTrue = 32\n"
    "ImGuiInputTextFlags_CallbackCompletion = 64\n"
    "ImGuiInputTextFlags_CallbackHistory = 128\n"
    "ImGuiInputTextFlags_CallbackAlways = 256\n"
    "ImGuiInputTextFlags_CallbackCharFilter = 512\n"
    "ImGuiInputTextFlags_AllowTabInput = 1024\n"
    "ImGuiInputTextFlags_CtrlEnterForNewLine = 2048\n"
    "ImGuiInputTextFlags_NoHorizontalScroll = 4096\n"
    "ImGuiInputTextFlags_AlwaysOverwrite = 8192\n"
    "ImGuiInputTextFlags_ReadOnly = 16384\n"
    "ImGuiInputTextFlags_Password = 32768\n"
    "ImGuiInputTextFlags_NoUndoRedo = 65536\n"
    "ImGuiInputTextFlags_CharsScientific = 131072\n"
    "ImGuiInputTextFlags_CallbackResize = 262144\n"
    "ImGuiInputTextFlags_CallbackEdit = 524288\n"
    "ImGuiInputTextFlags_EscapeClearsAll = 1048576\n"
    "\n"
    "# ImGuiItemFlags_\n"
    "ImGuiItemFlags_None = 0\n"
    "ImGuiItemFlags_NoTabStop = 1\n"
    "ImGuiItemFlags_ButtonRepeat = 2\n"
    "ImGuiItemFlags_Disabled = 4\n"
    "ImGuiItemFlags_NoNav = 8\n"
    "ImGuiItemFlags_NoNavDefaultFocus = 16\n"
    "ImGuiItemFlags_SelectableDontClosePopup = 32\n"
    "ImGuiItemFlags_MixedValue = 64\n"
    "ImGuiItemFlags_ReadOnly = 128\n"
    "ImGuiItemFlags_NoWindowHoverableCheck = 256\n"
    "ImGuiItemFlags_AllowOverlap = 512\n"
    "ImGuiItemFlags_Inputable = 1024\n"
    "\n"
    "# ImGuiItemStatusFlags_\n"
    "ImGuiItemStatusFlags_None = 0\n"
    "ImGuiItemStatusFlags_HoveredRect = 1\n"
    "ImGuiItemStatusFlags_HasDisplayRect = 2\n"
    "ImGuiItemStatusFlags_Edited = 4\n"
    "ImGuiItemStatusFlags_ToggledSelection = 8\n"
    "ImGuiItemStatusFlags_ToggledOpen = 16\n"
    "ImGuiItemStatusFlags_HasDeactivated = 32\n"
    "ImGuiItemStatusFlags_Deactivated = 64\n"
    "ImGuiItemStatusFlags_HoveredWindow = 128\n"
    "ImGuiItemStatusFlags_FocusedByTabbing = 256\n"
    "ImGuiItemStatusFlags_Visible = 512\n"
    "\n"
    "# ImGuiKey\n"
    "ImGuiKey_None = 0\n"
    "ImGuiKey_Tab = 512\n"
    "ImGuiKey_LeftArrow = 513\n"
    "ImGuiKey_RightArrow = 514\n"
    "ImGuiKey_UpArrow = 515\n"
    "ImGuiKey_DownArrow = 516\n"
    "ImGuiKey_PageUp = 517\n"
    "ImGuiKey_PageDown = 518\n"
    "ImGuiKey_Home = 519\n"
    "ImGuiKey_End = 520\n"
    "ImGuiKey_Insert = 521\n"
    "ImGuiKey_Delete = 522\n"
    "ImGuiKey_Backspace = 523\n"
    "ImGuiKey_Space = 524\n"
    "ImGuiKey_Enter = 525\n"
    "ImGuiKey_Escape = 526\n"
    "ImGuiKey_LeftCtrl = 527\n"
    "ImGuiKey_LeftShift = 528\n"
    "ImGuiKey_LeftAlt = 529\n"
    "ImGuiKey_LeftSuper = 530\n"
    "ImGuiKey_RightCtrl = 531\n"
    "ImGuiKey_RightShift = 532\n"
    "ImGuiKey_RightAlt = 533\n"
    "ImGuiKey_RightSuper = 534\n"
    "ImGuiKey_Menu = 535\n"
    "ImGuiKey_0 = 536\n"
    "ImGuiKey_1 = 537\n"
    "ImGuiKey_2 = 538\n"
    "ImGuiKey_3 = 539\n"
    "ImGuiKey_4 = 540\n"
    "ImGuiKey_5 = 541\n"
    "ImGuiKey_6 = 542\n"
    "ImGuiKey_7 = 543\n"
    "ImGuiKey_8 = 544\n"
    "ImGuiKey_9 = 545\n"
    "ImGuiKey_A = 546\n"
    "ImGuiKey_B = 547\n"
    "ImGuiKey_C = 548\n"
    "ImGuiKey_D = 549\n"
    "ImGuiKey_E = 550\n"
    "ImGuiKey_F = 551\n"
    "ImGuiKey_G = 552\n"
    "ImGuiKey_H = 553\n"
    "ImGuiKey_I = 554\n"
    "ImGuiKey_J = 555\n"
    "ImGuiKey_K = 556\n"
    "ImGuiKey_L = 557\n"
    "ImGuiKey_M = 558\n"
    "ImGuiKey_N = 559\n"
    "ImGuiKey_O = 560\n"
    "ImGuiKey_P = 561\n"
    "ImGuiKey_Q = 562\n"
    "ImGuiKey_R = 563\n"
    "ImGuiKey_S = 564\n"
    "ImGuiKey_T = 565\n"
    "ImGuiKey_U = 566\n"
    "ImGuiKey_V = 567\n"
    "ImGuiKey_W = 568\n"
    "ImGuiKey_X = 569\n"
    "ImGuiKey_Y = 570\n"
    "ImGuiKey_Z = 571\n"
    "ImGuiKey_F1 = 572\n"
    "ImGuiKey_F2 = 573\n"
    "ImGuiKey_F3 = 574\n"
    "ImGuiKey_F4 = 575\n"
    "ImGuiKey_F5 = 576\n"
    "ImGuiKey_F6 = 577\n"
    "ImGuiKey_F7 = 578\n"
    "ImGuiKey_F8 = 579\n"
    "ImGuiKey_F9 = 580\n"
    "ImGuiKey_F10 = 581\n"
    "ImGuiKey_F11 = 582\n"
    "ImGuiKey_F12 = 583\n"
    "ImGuiKey_Apostrophe = 584\n"
    "ImGuiKey_Comma = 585\n"
    "ImGuiKey_Minus = 586\n"
    "ImGuiKey_Period = 587\n"
    "ImGuiKey_Slash = 588\n"
    "ImGuiKey_Semicolon = 589\n"
    "ImGuiKey_Equal = 590\n"
    "ImGuiKey_LeftBracket = 591\n"
    "ImGuiKey_Backslash = 592\n"
    "ImGuiKey_RightBracket = 593\n"
    "ImGuiKey_GraveAccent = 594\n"
    "ImGuiKey_CapsLock = 595\n"
    "ImGuiKey_ScrollLock = 596\n"
    "ImGuiKey_NumLock = 597\n"
    "ImGuiKey_PrintScreen = 598\n"
    "ImGuiKey_Pause = 599\n"
    "ImGuiKey_Keypad0 = 600\n"
    "ImGuiKey_Keypad1 = 601\n"
    "ImGuiKey_Keypad2 = 602\n"
    "ImGuiKey_Keypad3 = 603\n"
    "ImGuiKey_Keypad4 = 604\n"
    "ImGuiKey_Keypad5 = 605\n"
    "ImGuiKey_Keypad6 = 606\n"
    "ImGuiKey_Keypad7 = 607\n"
    "ImGuiKey_Keypad8 = 608\n"
    "ImGuiKey_Keypad9 = 609\n"
    "ImGuiKey_KeypadDecimal = 610\n"
    "ImGuiKey_KeypadDivide = 611\n"
    "ImGuiKey_KeypadMultiply = 612\n"
    "ImGuiKey_KeypadSubtract = 613\n"
    "ImGuiKey_KeypadAdd = 614\n"
    "ImGuiKey_KeypadEnter = 615\n"
    "ImGuiKey_KeypadEqual = 616\n"
    "ImGuiKey_GamepadStart = 617\n"
    "ImGuiKey_GamepadBack = 618\n"
    "ImGuiKey_GamepadFaceLeft = 619\n"
    "ImGuiKey_GamepadFaceRight = 620\n"
    "ImGuiKey_GamepadFaceUp = 621\n"
    "ImGuiKey_GamepadFaceDown = 622\n"
    "ImGuiKey_GamepadDpadLeft = 623\n"
    "ImGuiKey_GamepadDpadRight = 624\n"
    "ImGuiKey_GamepadDpadUp = 625\n"
    "ImGuiKey_GamepadDpadDown = 626\n"
    "ImGuiKey_GamepadL1 = 627\n"
    "ImGuiKey_GamepadR1 = 628\n"
    "ImGuiKey_GamepadL2 = 629\n"
    "ImGuiKey_GamepadR2 = 630\n"
    "ImGuiKey_GamepadL3 = 631\n"
    "ImGuiKey_GamepadR3 = 632\n"
    "ImGuiKey_GamepadLStickLeft = 633\n"
    "ImGuiKey_GamepadLStickRight = 634\n"
    "ImGuiKey_GamepadLStickUp = 635\n"
    "ImGuiKey_GamepadLStickDown = 636\n"
    "ImGuiKey_GamepadRStickLeft = 637\n"
    "ImGuiKey_GamepadRStickRight = 638\n"
    "ImGuiKey_GamepadRStickUp = 639\n"
    "ImGuiKey_GamepadRStickDown = 640\n"
    "ImGuiKey_MouseLeft = 641\n"
    "ImGuiKey_MouseRight = 642\n"
    "ImGuiKey_MouseMiddle = 643\n"
    "ImGuiKey_MouseX1 = 644\n"
    "ImGuiKey_MouseX2 = 645\n"
    "ImGuiKey_MouseWheelX = 646\n"
    "ImGuiKey_MouseWheelY = 647\n"
    "ImGuiKey_ReservedForModCtrl = 648\n"
    "ImGuiKey_ReservedForModShift = 649\n"
    "ImGuiKey_ReservedForModAlt = 650\n"
    "ImGuiKey_ReservedForModSuper = 651\n"
    "ImGuiKey_COUNT = 652\n"
    "ImGuiMod_None = 0\n"
    "ImGuiMod_Ctrl = 4096\n"
    "ImGuiMod_Shift = 8192\n"
    "ImGuiMod_Alt = 16384\n"
    "ImGuiMod_Super = 32768\n"
    "ImGuiMod_Shortcut = 2048\n"
    "ImGuiMod_Mask_ = 63488\n"
    "ImGuiKey_NamedKey_BEGIN = 512\n"
    "ImGuiKey_NamedKey_END = 652\n"
    "ImGuiKey_NamedKey_COUNT = 140\n"
    "ImGuiKey_KeysData_SIZE = 652\n"
    "ImGuiKey_KeysData_OFFSET = 0\n"
    "\n"
    "# ImGuiLayoutType_\n"
    "ImGuiLayoutType_Horizontal = 0\n"
    "ImGuiLayoutType_Vertical = 1\n"
    "\n"
    "# ImGuiLocKey\n"
    "ImGuiLocKey_VersionStr = 0\n"
    "ImGuiLocKey_TableSizeOne = 1\n"
    "ImGuiLocKey_TableSizeAllFit = 2\n"
    "ImGuiLocKey_TableSizeAllDefault = 3\n"
    "ImGuiLocKey_TableResetOrder = 4\n"
    "ImGuiLocKey_WindowingMainMenuBar = 5\n"
    "ImGuiLocKey_WindowingPopup = 6\n"
    "ImGuiLocKey_WindowingUntitled = 7\n"
    "ImGuiLocKey_COUNT = 8\n"
    "\n"
    "# ImGuiLogType\n"
    "ImGuiLogType_None = 0\n"
    "ImGuiLogType_TTY = 1\n"
    "ImGuiLogType_File = 2\n"
    "ImGuiLogType_Buffer = 3\n"
    "ImGuiLogType_Clipboard = 4\n"
    "\n"
    "# ImGuiMouseButton_\n"
    "ImGuiMouseButton_Left = 0\n"
    "ImGuiMouseButton_Right = 1\n"
    "ImGuiMouseButton_Middle = 2\n"
    "ImGuiMouseButton_COUNT = 5\n"
    "\n"
    "# ImGuiMouseCursor_\n"
    "ImGuiMouseCursor_None = -1\n"
    "ImGuiMouseCursor_Arrow = 0\n"
    "ImGuiMouseCursor_TextInput = 1\n"
    "ImGuiMouseCursor_ResizeAll = 2\n"
    "ImGuiMouseCursor_ResizeNS = 3\n"
    "ImGuiMouseCursor_ResizeEW = 4\n"
    "ImGuiMouseCursor_ResizeNESW = 5\n"
    "ImGuiMouseCursor_ResizeNWSE = 6\n"
    "ImGuiMouseCursor_Hand = 7\n"
    "ImGuiMouseCursor_NotAllowed = 8\n"
    "ImGuiMouseCursor_COUNT = 9\n"
    "\n"
    "# ImGuiMouseSource\n"
    "ImGuiMouseSource_Mouse = 0\n"
    "ImGuiMouseSource_TouchScreen = 1\n"
    "ImGuiMouseSource_Pen = 2\n"
    "ImGuiMouseSource_COUNT = 3\n"
    "\n"
    "# ImGuiNavHighlightFlags_\n"
    "ImGuiNavHighlightFlags_None = 0\n"
    "ImGuiNavHighlightFlags_TypeDefault = 1\n"
    "ImGuiNavHighlightFlags_TypeThin = 2\n"
    "ImGuiNavHighlightFlags_AlwaysDraw = 4\n"
    "ImGuiNavHighlightFlags_NoRounding = 8\n"
    "\n"
    "# ImGuiNavInput\n"
    "ImGuiNavInput_Activate = 0\n"
    "ImGuiNavInput_Cancel = 1\n"
    "ImGuiNavInput_Input = 2\n"
    "ImGuiNavInput_Menu = 3\n"
    "ImGuiNavInput_DpadLeft = 4\n"
    "ImGuiNavInput_DpadRight = 5\n"
    "ImGuiNavInput_DpadUp = 6\n"
    "ImGuiNavInput_DpadDown = 7\n"
    "ImGuiNavInput_LStickLeft = 8\n"
    "ImGuiNavInput_LStickRight = 9\n"
    "ImGuiNavInput_LStickUp = 10\n"
    "ImGuiNavInput_LStickDown = 11\n"
    "ImGuiNavInput_FocusPrev = 12\n"
    "ImGuiNavInput_FocusNext = 13\n"
    "ImGuiNavInput_TweakSlow = 14\n"
    "ImGuiNavInput_TweakFast = 15\n"
    "ImGuiNavInput_COUNT = 16\n"
    "\n"
    "# ImGuiNavLayer\n"
    "ImGuiNavLayer_Main = 0\n"
    "ImGuiNavLayer_Menu = 1\n"
    "ImGuiNavLayer_COUNT = 2\n"
    "\n"
    "# ImGuiNavMoveFlags_\n"
    "ImGuiNavMoveFlags_None = 0\n"
    "ImGuiNavMoveFlags_LoopX = 1\n"
    "ImGuiNavMoveFlags_LoopY = 2\n"
    "ImGuiNavMoveFlags_WrapX = 4\n"
    "ImGuiNavMoveFlags_WrapY = 8\n"
    "ImGuiNavMoveFlags_WrapMask_ = 15\n"
    "ImGuiNavMoveFlags_AllowCurrentNavId = 16\n"
    "ImGuiNavMoveFlags_AlsoScoreVisibleSet = 32\n"
    "ImGuiNavMoveFlags_ScrollToEdgeY = 64\n"
    "ImGuiNavMoveFlags_Forwarded = 128\n"
    "ImGuiNavMoveFlags_DebugNoResult = 256\n"
    "ImGuiNavMoveFlags_FocusApi = 512\n"
    "ImGuiNavMoveFlags_IsTabbing = 1024\n"
    "ImGuiNavMoveFlags_IsPageMove = 2048\n"
    "ImGuiNavMoveFlags_Activate = 4096\n"
    "ImGuiNavMoveFlags_NoSelect = 8192\n"
    "ImGuiNavMoveFlags_NoSetNavHighlight = 16384\n"
    "\n"
    "# ImGuiNextItemDataFlags_\n"
    "ImGuiNextItemDataFlags_None = 0\n"
    "ImGuiNextItemDataFlags_HasWidth = 1\n"
    "ImGuiNextItemDataFlags_HasOpen = 2\n"
    "\n"
    "# ImGuiNextWindowDataFlags_\n"
    "ImGuiNextWindowDataFlags_None = 0\n"
    "ImGuiNextWindowDataFlags_HasPos = 1\n"
    "ImGuiNextWindowDataFlags_HasSize = 2\n"
    "ImGuiNextWindowDataFlags_HasContentSize = 4\n"
    "ImGuiNextWindowDataFlags_HasCollapsed = 8\n"
    "ImGuiNextWindowDataFlags_HasSizeConstraint = 16\n"
    "ImGuiNextWindowDataFlags_HasFocus = 32\n"
    "ImGuiNextWindowDataFlags_HasBgAlpha = 64\n"
    "ImGuiNextWindowDataFlags_HasScroll = 128\n"
    "\n"
    "# ImGuiOldColumnFlags_\n"
    "ImGuiOldColumnFlags_None = 0\n"
    "ImGuiOldColumnFlags_NoBorder = 1\n"
    "ImGuiOldColumnFlags_NoResize = 2\n"
    "ImGuiOldColumnFlags_NoPreserveWidths = 4\n"
    "ImGuiOldColumnFlags_NoForceWithinWindow = 8\n"
    "ImGuiOldColumnFlags_GrowParentContentsSize = 16\n"
    "\n"
    "# ImGuiPlotType\n"
    "ImGuiPlotType_Lines = 0\n"
    "ImGuiPlotType_Histogram = 1\n"
    "\n"
    "# ImGuiPopupFlags_\n"
    "ImGuiPopupFlags_None = 0\n"
    "ImGuiPopupFlags_MouseButtonLeft = 0\n"
    "ImGuiPopupFlags_MouseButtonRight = 1\n"
    "ImGuiPopupFlags_MouseButtonMiddle = 2\n"
    "ImGuiPopupFlags_MouseButtonMask_ = 31\n"
    "ImGuiPopupFlags_MouseButtonDefault_ = 1\n"
    "ImGuiPopupFlags_NoOpenOverExistingPopup = 32\n"
    "ImGuiPopupFlags_NoOpenOverItems = 64\n"
    "ImGuiPopupFlags_AnyPopupId = 128\n"
    "ImGuiPopupFlags_AnyPopupLevel = 256\n"
    "ImGuiPopupFlags_AnyPopup = 384\n"
    "\n"
    "# ImGuiPopupPositionPolicy\n"
    "ImGuiPopupPositionPolicy_Default = 0\n"
    "ImGuiPopupPositionPolicy_ComboBox = 1\n"
    "ImGuiPopupPositionPolicy_Tooltip = 2\n"
    "\n"
    "# ImGuiScrollFlags_\n"
    "ImGuiScrollFlags_None = 0\n"
    "ImGuiScrollFlags_KeepVisibleEdgeX = 1\n"
    "ImGuiScrollFlags_KeepVisibleEdgeY = 2\n"
    "ImGuiScrollFlags_KeepVisibleCenterX = 4\n"
    "ImGuiScrollFlags_KeepVisibleCenterY = 8\n"
    "ImGuiScrollFlags_AlwaysCenterX = 16\n"
    "ImGuiScrollFlags_AlwaysCenterY = 32\n"
    "ImGuiScrollFlags_NoScrollParent = 64\n"
    "ImGuiScrollFlags_MaskX_ = 21\n"
    "ImGuiScrollFlags_MaskY_ = 42\n"
    "\n"
    "# ImGuiSelectableFlagsPrivate_\n"
    "ImGuiSelectableFlags_NoHoldingActiveID = 1048576\n"
    "ImGuiSelectableFlags_SelectOnNav = 2097152\n"
    "ImGuiSelectableFlags_SelectOnClick = 4194304\n"
    "ImGuiSelectableFlags_SelectOnRelease = 8388608\n"
    "ImGuiSelectableFlags_SpanAvailWidth = 16777216\n"
    "ImGuiSelectableFlags_SetNavIdOnHover = 33554432\n"
    "ImGuiSelectableFlags_NoPadWithHalfSpacing = 67108864\n"
    "ImGuiSelectableFlags_NoSetKeyOwner = 134217728\n"
    "\n"
    "# ImGuiSelectableFlags_\n"
    "ImGuiSelectableFlags_None = 0\n"
    "ImGuiSelectableFlags_DontClosePopups = 1\n"
    "ImGuiSelectableFlags_SpanAllColumns = 2\n"
    "ImGuiSelectableFlags_AllowDoubleClick = 4\n"
    "ImGuiSelectableFlags_Disabled = 8\n"
    "ImGuiSelectableFlags_AllowOverlap = 16\n"
    "\n"
    "# ImGuiSeparatorFlags_\n"
    "ImGuiSeparatorFlags_None = 0\n"
    "ImGuiSeparatorFlags_Horizontal = 1\n"
    "ImGuiSeparatorFlags_Vertical = 2\n"
    "ImGuiSeparatorFlags_SpanAllColumns = 4\n"
    "\n"
    "# ImGuiSliderFlagsPrivate_\n"
    "ImGuiSliderFlags_Vertical = 1048576\n"
    "ImGuiSliderFlags_ReadOnly = 2097152\n"
    "\n"
    "# ImGuiSliderFlags_\n"
    "ImGuiSliderFlags_None = 0\n"
    "ImGuiSliderFlags_AlwaysClamp = 16\n"
    "ImGuiSliderFlags_Logarithmic = 32\n"
    "ImGuiSliderFlags_NoRoundToFormat = 64\n"
    "ImGuiSliderFlags_NoInput = 128\n"
    "\n"
    "# ImGuiSortDirection_\n"
    "ImGuiSortDirection_None = 0\n"
    "ImGuiSortDirection_Ascending = 1\n"
    "ImGuiSortDirection_Descending = 2\n"
    "\n"
    "# ImGuiStyleVar_\n"
    "ImGuiStyleVar_Alpha = 0\n"
    "ImGuiStyleVar_DisabledAlpha = 1\n"
    "ImGuiStyleVar_WindowPadding = 2\n"
    "ImGuiStyleVar_WindowRounding = 3\n"
    "ImGuiStyleVar_WindowBorderSize = 4\n"
    "ImGuiStyleVar_WindowMinSize = 5\n"
    "ImGuiStyleVar_WindowTitleAlign = 6\n"
    "ImGuiStyleVar_ChildRounding = 7\n"
    "ImGuiStyleVar_ChildBorderSize = 8\n"
    "ImGuiStyleVar_PopupRounding = 9\n"
    "ImGuiStyleVar_PopupBorderSize = 10\n"
    "ImGuiStyleVar_FramePadding = 11\n"
    "ImGuiStyleVar_FrameRounding = 12\n"
    "ImGuiStyleVar_FrameBorderSize = 13\n"
    "ImGuiStyleVar_ItemSpacing = 14\n"
    "ImGuiStyleVar_ItemInnerSpacing = 15\n"
    "ImGuiStyleVar_IndentSpacing = 16\n"
    "ImGuiStyleVar_CellPadding = 17\n"
    "ImGuiStyleVar_ScrollbarSize = 18\n"
    "ImGuiStyleVar_ScrollbarRounding = 19\n"
    "ImGuiStyleVar_GrabMinSize = 20\n"
    "ImGuiStyleVar_GrabRounding = 21\n"
    "ImGuiStyleVar_TabRounding = 22\n"
    "ImGuiStyleVar_ButtonTextAlign = 23\n"
    "ImGuiStyleVar_SelectableTextAlign = 24\n"
    "ImGuiStyleVar_SeparatorTextBorderSize = 25\n"
    "ImGuiStyleVar_SeparatorTextAlign = 26\n"
    "ImGuiStyleVar_SeparatorTextPadding = 27\n"
    "ImGuiStyleVar_COUNT = 28\n"
    "\n"
    "# ImGuiTabBarFlagsPrivate_\n"
    "ImGuiTabBarFlags_DockNode = 1048576\n"
    "ImGuiTabBarFlags_IsFocused = 2097152\n"
    "ImGuiTabBarFlags_SaveSettings = 4194304\n"
    "\n"
    "# ImGuiTabBarFlags_\n"
    "ImGuiTabBarFlags_None = 0\n"
    "ImGuiTabBarFlags_Reorderable = 1\n"
    "ImGuiTabBarFlags_AutoSelectNewTabs = 2\n"
    "ImGuiTabBarFlags_TabListPopupButton = 4\n"
    "ImGuiTabBarFlags_NoCloseWithMiddleMouseButton = 8\n"
    "ImGuiTabBarFlags_NoTabListScrollingButtons = 16\n"
    "ImGuiTabBarFlags_NoTooltip = 32\n"
    "ImGuiTabBarFlags_FittingPolicyResizeDown = 64\n"
    "ImGuiTabBarFlags_FittingPolicyScroll = 128\n"
    "ImGuiTabBarFlags_FittingPolicyMask_ = 192\n"
    "ImGuiTabBarFlags_FittingPolicyDefault_ = 64\n"
    "\n"
    "# ImGuiTabItemFlagsPrivate_\n"
    "ImGuiTabItemFlags_SectionMask_ = 192\n"
    "ImGuiTabItemFlags_NoCloseButton = 1048576\n"
    "ImGuiTabItemFlags_Button = 2097152\n"
    "\n"
    "# ImGuiTabItemFlags_\n"
    "ImGuiTabItemFlags_None = 0\n"
    "ImGuiTabItemFlags_UnsavedDocument = 1\n"
    "ImGuiTabItemFlags_SetSelected = 2\n"
    "ImGuiTabItemFlags_NoCloseWithMiddleMouseButton = 4\n"
    "ImGuiTabItemFlags_NoPushId = 8\n"
    "ImGuiTabItemFlags_NoTooltip = 16\n"
    "ImGuiTabItemFlags_NoReorder = 32\n"
    "ImGuiTabItemFlags_Leading = 64\n"
    "ImGuiTabItemFlags_Trailing = 128\n"
    "\n"
    "# ImGuiTableBgTarget_\n"
    "ImGuiTableBgTarget_None = 0\n"
    "ImGuiTableBgTarget_RowBg0 = 1\n"
    "ImGuiTableBgTarget_RowBg1 = 2\n"
    "ImGuiTableBgTarget_CellBg = 3\n"
    "\n"
    "# ImGuiTableColumnFlags_\n"
    "ImGuiTableColumnFlags_None = 0\n"
    "ImGuiTableColumnFlags_Disabled = 1\n"
    "ImGuiTableColumnFlags_DefaultHide = 2\n"
    "ImGuiTableColumnFlags_DefaultSort = 4\n"
    "ImGuiTableColumnFlags_WidthStretch = 8\n"
    "ImGuiTableColumnFlags_WidthFixed = 16\n"
    "ImGuiTableColumnFlags_NoResize = 32\n"
    "ImGuiTableColumnFlags_NoReorder = 64\n"
    "ImGuiTableColumnFlags_NoHide = 128\n"
    "ImGuiTableColumnFlags_NoClip = 256\n"
    "ImGuiTableColumnFlags_NoSort = 512\n"
    "ImGuiTableColumnFlags_NoSortAscending = 1024\n"
    "ImGuiTableColumnFlags_NoSortDescending = 2048\n"
    "ImGuiTableColumnFlags_NoHeaderLabel = 4096\n"
    "ImGuiTableColumnFlags_NoHeaderWidth = 8192\n"
    "ImGuiTableColumnFlags_PreferSortAscending = 16384\n"
    "ImGuiTableColumnFlags_PreferSortDescending = 32768\n"
    "ImGuiTableColumnFlags_IndentEnable = 65536\n"
    "ImGuiTableColumnFlags_IndentDisable = 131072\n"
    "ImGuiTableColumnFlags_IsEnabled = 16777216\n"
    "ImGuiTableColumnFlags_IsVisible = 33554432\n"
    "ImGuiTableColumnFlags_IsSorted = 67108864\n"
    "ImGuiTableColumnFlags_IsHovered = 134217728\n"
    "ImGuiTableColumnFlags_WidthMask_ = 24\n"
    "ImGuiTableColumnFlags_IndentMask_ = 196608\n"
    "ImGuiTableColumnFlags_StatusMask_ = 251658240\n"
    "\n"
    "# ImGuiTableFlags_\n"
    "ImGuiTableFlags_None = 0\n"
    "ImGuiTableFlags_Resizable = 1\n"
    "ImGuiTableFlags_Reorderable = 2\n"
    "ImGuiTableFlags_Hideable = 4\n"
    "ImGuiTableFlags_Sortable = 8\n"
    "ImGuiTableFlags_NoSavedSettings = 16\n"
    "ImGuiTableFlags_ContextMenuInBody = 32\n"
    "ImGuiTableFlags_RowBg = 64\n"
    "ImGuiTableFlags_BordersInnerH = 128\n"
    "ImGuiTableFlags_BordersOuterH = 256\n"
    "ImGuiTableFlags_BordersInnerV = 512\n"
    "ImGuiTableFlags_BordersOuterV = 1024\n"
    "ImGuiTableFlags_BordersH = 384\n"
    "ImGuiTableFlags_BordersV = 1536\n"
    "ImGuiTableFlags_BordersInner = 640\n"
    "ImGuiTableFlags_BordersOuter = 1280\n"
    "ImGuiTableFlags_Borders = 1920\n"
    "ImGuiTableFlags_NoBordersInBody = 2048\n"
    "ImGuiTableFlags_NoBordersInBodyUntilResize = 4096\n"
    "ImGuiTableFlags_SizingFixedFit = 8192\n"
    "ImGuiTableFlags_SizingFixedSame = 16384\n"
    "ImGuiTableFlags_SizingStretchProp = 24576\n"
    "ImGuiTableFlags_SizingStretchSame = 32768\n"
    "ImGuiTableFlags_NoHostExtendX = 65536\n"
    "ImGuiTableFlags_NoHostExtendY = 131072\n"
    "ImGuiTableFlags_NoKeepColumnsVisible = 262144\n"
    "ImGuiTableFlags_PreciseWidths = 524288\n"
    "ImGuiTableFlags_NoClip = 1048576\n"
    "ImGuiTableFlags_PadOuterX = 2097152\n"
    "ImGuiTableFlags_NoPadOuterX = 4194304\n"
    "ImGuiTableFlags_NoPadInnerX = 8388608\n"
    "ImGuiTableFlags_ScrollX = 16777216\n"
    "ImGuiTableFlags_ScrollY = 33554432\n"
    "ImGuiTableFlags_SortMulti = 67108864\n"
    "ImGuiTableFlags_SortTristate = 134217728\n"
    "ImGuiTableFlags_SizingMask_ = 57344\n"
    "\n"
    "# ImGuiTableRowFlags_\n"
    "ImGuiTableRowFlags_None = 0\n"
    "ImGuiTableRowFlags_Headers = 1\n"
    "\n"
    "# ImGuiTextFlags_\n"
    "ImGuiTextFlags_None = 0\n"
    "ImGuiTextFlags_NoWidthForLargeClippedText = 1\n"
    "\n"
    "# ImGuiTooltipFlags_\n"
    "ImGuiTooltipFlags_None = 0\n"
    "ImGuiTooltipFlags_OverridePrevious = 2\n"
    "\n"
    "# ImGuiTreeNodeFlagsPrivate_\n"
    "ImGuiTreeNodeFlags_ClipLabelForTrailingButton = 1048576\n"
    "ImGuiTreeNodeFlags_UpsideDownArrow = 2097152\n"
    "\n"
    "# ImGuiTreeNodeFlags_\n"
    "ImGuiTreeNodeFlags_None = 0\n"
    "ImGuiTreeNodeFlags_Selected = 1\n"
    "ImGuiTreeNodeFlags_Framed = 2\n"
    "ImGuiTreeNodeFlags_AllowOverlap = 4\n"
    "ImGuiTreeNodeFlags_NoTreePushOnOpen = 8\n"
    "ImGuiTreeNodeFlags_NoAutoOpenOnLog = 16\n"
    "ImGuiTreeNodeFlags_DefaultOpen = 32\n"
    "ImGuiTreeNodeFlags_OpenOnDoubleClick = 64\n"
    "ImGuiTreeNodeFlags_OpenOnArrow = 128\n"
    "ImGuiTreeNodeFlags_Leaf = 256\n"
    "ImGuiTreeNodeFlags_Bullet = 512\n"
    "ImGuiTreeNodeFlags_FramePadding = 1024\n"
    "ImGuiTreeNodeFlags_SpanAvailWidth = 2048\n"
    "ImGuiTreeNodeFlags_SpanFullWidth = 4096\n"
    "ImGuiTreeNodeFlags_NavLeftJumpsBackHere = 8192\n"
    "ImGuiTreeNodeFlags_CollapsingHeader = 26\n"
    "\n"
    "# ImGuiViewportFlags_\n"
    "ImGuiViewportFlags_None = 0\n"
    "ImGuiViewportFlags_IsPlatformWindow = 1\n"
    "ImGuiViewportFlags_IsPlatformMonitor = 2\n"
    "ImGuiViewportFlags_OwnedByApp = 4\n"
    "\n"
    "# ImGuiWindowFlags_\n"
    "ImGuiWindowFlags_None = 0\n"
    "ImGuiWindowFlags_NoTitleBar = 1\n"
    "ImGuiWindowFlags_NoResize = 2\n"
    "ImGuiWindowFlags_NoMove = 4\n"
    "ImGuiWindowFlags_NoScrollbar = 8\n"
    "ImGuiWindowFlags_NoScrollWithMouse = 16\n"
    "ImGuiWindowFlags_NoCollapse = 32\n"
    "ImGuiWindowFlags_AlwaysAutoResize = 64\n"
    "ImGuiWindowFlags_NoBackground = 128\n"
    "ImGuiWindowFlags_NoSavedSettings = 256\n"
    "ImGuiWindowFlags_NoMouseInputs = 512\n"
    "ImGuiWindowFlags_MenuBar = 1024\n"
    "ImGuiWindowFlags_HorizontalScrollbar = 2048\n"
    "ImGuiWindowFlags_NoFocusOnAppearing = 4096\n"
    "ImGuiWindowFlags_NoBringToFrontOnFocus = 8192\n"
    "ImGuiWindowFlags_AlwaysVerticalScrollbar = 16384\n"
    "ImGuiWindowFlags_AlwaysHorizontalScrollbar = 32768\n"
    "ImGuiWindowFlags_AlwaysUseWindowPadding = 65536\n"
    "ImGuiWindowFlags_NoNavInputs = 262144\n"
    "ImGuiWindowFlags_NoNavFocus = 524288\n"
    "ImGuiWindowFlags_UnsavedDocument = 1048576\n"
    "ImGuiWindowFlags_NoNav = 786432\n"
    "ImGuiWindowFlags_NoDecoration = 43\n"
    "ImGuiWindowFlags_NoInputs = 786944\n"
    "ImGuiWindowFlags_NavFlattened = 8388608\n"
    "ImGuiWindowFlags_ChildWindow = 16777216\n"
    "ImGuiWindowFlags_Tooltip = 33554432\n"
    "ImGuiWindowFlags_Popup = 67108864\n"
    "ImGuiWindowFlags_Modal = 134217728\n"
    "ImGuiWindowFlags_ChildMenu = 268435456\n"
    "\n"
    , "imgui.py", EXEC_MODE, mod);
}

template<typename T>
struct OpaquePointer{
    T* ptr;
    OpaquePointer(T* ptr): ptr(ptr){}
    T* _(){ return ptr; }
};

struct PyImGuiIO: OpaquePointer<ImGuiIO>{
    PY_CLASS(PyImGuiIO, imgui, _IO)

    using OpaquePointer<ImGuiIO>::OpaquePointer;

    static void _register(VM* vm, PyObject* mod, PyObject* type){
        vm->bind_notimplemented_constructor<PyImGuiIO>(type);
                           
        PY_FIELD(PyImGuiIO, "ConfigFlags", _, ConfigFlags)           // int
        PY_FIELD(PyImGuiIO, "BackendFlags", _, BackendFlags)         // int
        PY_FIELD(PyImGuiIO, "DisplaySize", _, DisplaySize)           // struct ImVec2
        PY_FIELD(PyImGuiIO, "DeltaTime", _, DeltaTime)               // float
        PY_FIELD(PyImGuiIO, "IniSavingRate", _, IniSavingRate)       // float
        PY_FIELD(PyImGuiIO, "IniFilename", _, IniFilename)  // const char*
        PY_FIELD(PyImGuiIO, "LogFilename", _, LogFilename)  // const char*
        PY_READONLY_FIELD(PyImGuiIO, "UserData", _, UserData)        // void*
        PY_READONLY_FIELD(PyImGuiIO, "Fonts", _, Fonts)              // ImFontAtlas*
        PY_FIELD(PyImGuiIO, "FontGlobalScale", _, FontGlobalScale)   // float
        PY_FIELD(PyImGuiIO, "FontAllowUserScaling", _, FontAllowUserScaling)// bool
        PY_READONLY_FIELD(PyImGuiIO, "FontDefault", _, FontDefault)  // ImFont*
        PY_FIELD(PyImGuiIO, "DisplayFramebufferScale", _, DisplayFramebufferScale)// struct ImVec2
        PY_FIELD(PyImGuiIO, "MouseDrawCursor", _, MouseDrawCursor)   // bool
        PY_FIELD(PyImGuiIO, "ConfigMacOSXBehaviors", _, ConfigMacOSXBehaviors)// bool
        PY_FIELD(PyImGuiIO, "ConfigInputTrickleEventQueue", _, ConfigInputTrickleEventQueue)// bool
        PY_FIELD(PyImGuiIO, "ConfigInputTextCursorBlink", _, ConfigInputTextCursorBlink)// bool
        PY_FIELD(PyImGuiIO, "ConfigInputTextEnterKeepActive", _, ConfigInputTextEnterKeepActive)// bool
        PY_FIELD(PyImGuiIO, "ConfigDragClickToInputText", _, ConfigDragClickToInputText)// bool
        PY_FIELD(PyImGuiIO, "ConfigWindowsResizeFromEdges", _, ConfigWindowsResizeFromEdges)// bool
        PY_FIELD(PyImGuiIO, "ConfigWindowsMoveFromTitleBarOnly", _, ConfigWindowsMoveFromTitleBarOnly)// bool
        PY_FIELD(PyImGuiIO, "ConfigMemoryCompactTimer", _, ConfigMemoryCompactTimer)// float
        PY_FIELD(PyImGuiIO, "MouseDoubleClickTime", _, MouseDoubleClickTime)// float
        PY_FIELD(PyImGuiIO, "MouseDoubleClickMaxDist", _, MouseDoubleClickMaxDist)// float
        PY_FIELD(PyImGuiIO, "MouseDragThreshold", _, MouseDragThreshold)// float
        PY_FIELD(PyImGuiIO, "KeyRepeatDelay", _, KeyRepeatDelay)     // float
        PY_FIELD(PyImGuiIO, "KeyRepeatRate", _, KeyRepeatRate)       // float
        PY_FIELD(PyImGuiIO, "ConfigDebugBeginReturnValueOnce", _, ConfigDebugBeginReturnValueOnce)// bool
        PY_FIELD(PyImGuiIO, "ConfigDebugBeginReturnValueLoop", _, ConfigDebugBeginReturnValueLoop)// bool
        PY_FIELD(PyImGuiIO, "ConfigDebugIgnoreFocusLoss", _, ConfigDebugIgnoreFocusLoss)// bool
        PY_FIELD(PyImGuiIO, "ConfigDebugIniSettings", _, ConfigDebugIniSettings)// bool
        PY_READONLY_FIELD(PyImGuiIO, "BackendPlatformName", _, BackendPlatformName)// const char*
        PY_READONLY_FIELD(PyImGuiIO, "BackendRendererName", _, BackendRendererName)// const char*
        PY_READONLY_FIELD(PyImGuiIO, "BackendPlatformUserData", _, BackendPlatformUserData)// void*
        PY_READONLY_FIELD(PyImGuiIO, "BackendRendererUserData", _, BackendRendererUserData)// void*
        PY_READONLY_FIELD(PyImGuiIO, "BackendLanguageUserData", _, BackendLanguageUserData)// void*
        PY_READONLY_FIELD(PyImGuiIO, "ClipboardUserData", _, ClipboardUserData)// void*
        PY_FIELD(PyImGuiIO, "PlatformLocaleDecimalPoint", _, PlatformLocaleDecimalPoint)// ImWchar16
        PY_FIELD(PyImGuiIO, "WantCaptureMouse", _, WantCaptureMouse) // bool
        PY_FIELD(PyImGuiIO, "WantCaptureKeyboard", _, WantCaptureKeyboard)// bool
        PY_FIELD(PyImGuiIO, "WantTextInput", _, WantTextInput)       // bool
        PY_FIELD(PyImGuiIO, "WantSetMousePos", _, WantSetMousePos)   // bool
        PY_FIELD(PyImGuiIO, "WantSaveIniSettings", _, WantSaveIniSettings)// bool
        PY_FIELD(PyImGuiIO, "NavActive", _, NavActive)               // bool
        PY_FIELD(PyImGuiIO, "NavVisible", _, NavVisible)             // bool
        PY_FIELD(PyImGuiIO, "Framerate", _, Framerate)               // float
        PY_FIELD(PyImGuiIO, "MetricsRenderVertices", _, MetricsRenderVertices)// int
        PY_FIELD(PyImGuiIO, "MetricsRenderIndices", _, MetricsRenderIndices)// int
        PY_FIELD(PyImGuiIO, "MetricsRenderWindows", _, MetricsRenderWindows)// int
        PY_FIELD(PyImGuiIO, "MetricsActiveWindows", _, MetricsActiveWindows)// int
        PY_FIELD(PyImGuiIO, "MetricsActiveAllocations", _, MetricsActiveAllocations)// int
        PY_FIELD(PyImGuiIO, "MouseDelta", _, MouseDelta)             // struct ImVec2
        PY_READONLY_FIELD(PyImGuiIO, "Ctx", _, Ctx)                  // ImGuiContext*
        PY_FIELD(PyImGuiIO, "MousePos", _, MousePos)                 // struct ImVec2
        PY_FIELD(PyImGuiIO, "MouseWheel", _, MouseWheel)             // float
        PY_FIELD(PyImGuiIO, "MouseWheelH", _, MouseWheelH)           // float
        PY_FIELD(PyImGuiIO, "MouseSource", _, MouseSource)           // ImGuiMouseSource
        PY_FIELD(PyImGuiIO, "KeyCtrl", _, KeyCtrl)                   // bool
        PY_FIELD(PyImGuiIO, "KeyShift", _, KeyShift)                 // bool
        PY_FIELD(PyImGuiIO, "KeyAlt", _, KeyAlt)                     // bool
        PY_FIELD(PyImGuiIO, "KeySuper", _, KeySuper)                 // bool
        PY_FIELD(PyImGuiIO, "KeyMods", _, KeyMods)                   // int
        PY_FIELD(PyImGuiIO, "WantCaptureMouseUnlessPopupClose", _, WantCaptureMouseUnlessPopupClose)// bool
        PY_FIELD(PyImGuiIO, "MousePosPrev", _, MousePosPrev)         // struct ImVec2
        PY_FIELD(PyImGuiIO, "MouseWheelRequestAxisSwap", _, MouseWheelRequestAxisSwap)// bool
        PY_FIELD(PyImGuiIO, "PenPressure", _, PenPressure)           // float
        PY_FIELD(PyImGuiIO, "AppFocusLost", _, AppFocusLost)         // bool
        PY_FIELD(PyImGuiIO, "AppAcceptingEvents", _, AppAcceptingEvents)// bool
        PY_FIELD(PyImGuiIO, "BackendUsingLegacyKeyArrays", _, BackendUsingLegacyKeyArrays)// signed char
        PY_FIELD(PyImGuiIO, "BackendUsingLegacyNavInputArray", _, BackendUsingLegacyNavInputArray)// bool
        PY_FIELD(PyImGuiIO, "InputQueueSurrogate", _, InputQueueSurrogate)// unsigned short
    }
};


struct PyImGuiStyle: OpaquePointer<ImGuiStyle>{
    PY_CLASS(PyImGuiStyle, imgui, _Style)

    using OpaquePointer<ImGuiStyle>::OpaquePointer;

    static void _register(VM* vm, PyObject* mod, PyObject* type){
        vm->bind_notimplemented_constructor<PyImGuiStyle>(type);
                           
        PY_FIELD(PyImGuiStyle, "Alpha", _, Alpha)                    // float
        PY_FIELD(PyImGuiStyle, "DisabledAlpha", _, DisabledAlpha)    // float
        PY_FIELD(PyImGuiStyle, "WindowPadding", _, WindowPadding)    // struct ImVec2
        PY_FIELD(PyImGuiStyle, "WindowRounding", _, WindowRounding)  // float
        PY_FIELD(PyImGuiStyle, "WindowBorderSize", _, WindowBorderSize)// float
        PY_FIELD(PyImGuiStyle, "WindowMinSize", _, WindowMinSize)    // struct ImVec2
        PY_FIELD(PyImGuiStyle, "WindowTitleAlign", _, WindowTitleAlign)// struct ImVec2
        PY_FIELD(PyImGuiStyle, "WindowMenuButtonPosition", _, WindowMenuButtonPosition)// int
        PY_FIELD(PyImGuiStyle, "ChildRounding", _, ChildRounding)    // float
        PY_FIELD(PyImGuiStyle, "ChildBorderSize", _, ChildBorderSize)// float
        PY_FIELD(PyImGuiStyle, "PopupRounding", _, PopupRounding)    // float
        PY_FIELD(PyImGuiStyle, "PopupBorderSize", _, PopupBorderSize)// float
        PY_FIELD(PyImGuiStyle, "FramePadding", _, FramePadding)      // struct ImVec2
        PY_FIELD(PyImGuiStyle, "FrameRounding", _, FrameRounding)    // float
        PY_FIELD(PyImGuiStyle, "FrameBorderSize", _, FrameBorderSize)// float
        PY_FIELD(PyImGuiStyle, "ItemSpacing", _, ItemSpacing)        // struct ImVec2
        PY_FIELD(PyImGuiStyle, "ItemInnerSpacing", _, ItemInnerSpacing)// struct ImVec2
        PY_FIELD(PyImGuiStyle, "CellPadding", _, CellPadding)        // struct ImVec2
        PY_FIELD(PyImGuiStyle, "TouchExtraPadding", _, TouchExtraPadding)// struct ImVec2
        PY_FIELD(PyImGuiStyle, "IndentSpacing", _, IndentSpacing)    // float
        PY_FIELD(PyImGuiStyle, "ColumnsMinSpacing", _, ColumnsMinSpacing)// float
        PY_FIELD(PyImGuiStyle, "ScrollbarSize", _, ScrollbarSize)    // float
        PY_FIELD(PyImGuiStyle, "ScrollbarRounding", _, ScrollbarRounding)// float
        PY_FIELD(PyImGuiStyle, "GrabMinSize", _, GrabMinSize)        // float
        PY_FIELD(PyImGuiStyle, "GrabRounding", _, GrabRounding)      // float
        PY_FIELD(PyImGuiStyle, "LogSliderDeadzone", _, LogSliderDeadzone)// float
        PY_FIELD(PyImGuiStyle, "TabRounding", _, TabRounding)        // float
        PY_FIELD(PyImGuiStyle, "TabBorderSize", _, TabBorderSize)    // float
        PY_FIELD(PyImGuiStyle, "TabMinWidthForCloseButton", _, TabMinWidthForCloseButton)// float
        PY_FIELD(PyImGuiStyle, "ColorButtonPosition", _, ColorButtonPosition)// int
        PY_FIELD(PyImGuiStyle, "ButtonTextAlign", _, ButtonTextAlign)// struct ImVec2
        PY_FIELD(PyImGuiStyle, "SelectableTextAlign", _, SelectableTextAlign)// struct ImVec2
        PY_FIELD(PyImGuiStyle, "SeparatorTextBorderSize", _, SeparatorTextBorderSize)// float
        PY_FIELD(PyImGuiStyle, "SeparatorTextAlign", _, SeparatorTextAlign)// struct ImVec2
        PY_FIELD(PyImGuiStyle, "SeparatorTextPadding", _, SeparatorTextPadding)// struct ImVec2
        PY_FIELD(PyImGuiStyle, "DisplayWindowPadding", _, DisplayWindowPadding)// struct ImVec2
        PY_FIELD(PyImGuiStyle, "DisplaySafeAreaPadding", _, DisplaySafeAreaPadding)// struct ImVec2
        PY_FIELD(PyImGuiStyle, "MouseCursorScale", _, MouseCursorScale)// float
        PY_FIELD(PyImGuiStyle, "AntiAliasedLines", _, AntiAliasedLines)// bool
        PY_FIELD(PyImGuiStyle, "AntiAliasedLinesUseTex", _, AntiAliasedLinesUseTex)// bool
        PY_FIELD(PyImGuiStyle, "AntiAliasedFill", _, AntiAliasedFill)// bool
        PY_FIELD(PyImGuiStyle, "CurveTessellationTol", _, CurveTessellationTol)// float
        PY_FIELD(PyImGuiStyle, "CircleTessellationMaxError", _, CircleTessellationMaxError)// float
        PY_FIELD(PyImGuiStyle, "HoverStationaryDelay", _, HoverStationaryDelay)// float
        PY_FIELD(PyImGuiStyle, "HoverDelayShort", _, HoverDelayShort)// float
        PY_FIELD(PyImGuiStyle, "HoverDelayNormal", _, HoverDelayNormal)// float
        PY_FIELD(PyImGuiStyle, "HoverFlagsForTooltipMouse", _, HoverFlagsForTooltipMouse)// int
        PY_FIELD(PyImGuiStyle, "HoverFlagsForTooltipNav", _, HoverFlagsForTooltipNav)// int
    }
};


void add_module_imgui(VM* vm){
    PyObject* imgui = vm->new_module("imgui");
    register_imgui_enums(vm, imgui);

    PyImGuiIO::register_class(vm, imgui);
    PyImGuiStyle::register_class(vm, imgui);

    //////////////// raylib ////////////////
    vm->bind(imgui, "rlImGuiSetup(darkTheme: bool)",
        "Sets up ImGui, loads fonts and themes.",
        [](VM* vm, ArgsView args){
            bool darkTheme = CAST(bool, args[0]);
            rlImGuiSetup(darkTheme);
            return vm->None;
        });

    vm->bind(imgui, "rlImGuiShutdown()",
        "Cleanup ImGui and unload font atlas.",
        [](VM* vm, ArgsView args){
            rlImGuiShutdown();
            return vm->None;
        });

    vm->bind(imgui, "rlImGuiReloadFonts()",
        [](VM* vm, ArgsView args){
            rlImGuiReloadFonts();
            return vm->None;
        });

    // image API
    vm->bind(imgui, "rlImGuiImage(image: Texture_p)",
        "Wraps `void rlImGuiImage(const Texture *image);`",
        [](VM* vm, ArgsView args){
            Texture* image = CAST(Texture*, args[0]);
            rlImGuiImage(image);
            return vm->None;
        });

    vm->bind(imgui, "rlImGuiImageSize(image: Texture_p, width: int, height: int)",
        "Wraps `void rlImGuiImageSize(const Texture *image, int width, int height);`",
        [](VM* vm, ArgsView args){
            Texture* image = CAST(Texture*, args[0]);
            int width = CAST(int, args[1]);
            int height = CAST(int, args[2]);
            rlImGuiImageSize(image, width, height);
            return vm->None;
        });

    vm->bind(imgui, "rlImGuiImageSizeV(image: Texture_p, size: vec2)",
        "Wraps `void rlImGuiImageSizeV(const Texture *image, Vector2 size);`",
        [](VM* vm, ArgsView args){
            Texture* image = CAST(Texture*, args[0]);
            Vector2 size = CAST(Vector2, args[1]);
            rlImGuiImageSizeV(image, size);
            return vm->None;
        });

    vm->bind(imgui, "rlImGuiImageRect(image: Texture_p, destWidth: int, destHeight: int, sourceRect: Rectangle)",
        "Wraps `void rlImGuiImageRect(const Texture* image, int destWidth, int destHeight, Rectangle sourceRect);`",
        [](VM* vm, ArgsView args){
            Texture* image = CAST(Texture*, args[0]);
            int destWidth = CAST(int, args[1]);
            int destHeight = CAST(int, args[2]);
            Rectangle sourceRect = CAST(Rectangle, args[3]);
            rlImGuiImageRect(image, destWidth, destHeight, sourceRect);
            return vm->None;
        });

    vm->bind(imgui, "rlImGuiImageRenderTexture(image: RenderTexture_p)",
        "Wraps `void rlImGuiImageRenderTexture(const RenderTexture* image);`",
        [](VM* vm, ArgsView args){
            RenderTexture* image = CAST(RenderTexture*, args[0]);
            rlImGuiImageRenderTexture(image);
            return vm->None;
        });

    vm->bind(imgui, "rlImGuiImageRenderTextureFit(image: RenderTexture_p, center: bool)",
        "Wraps `void rlImGuiImageRenderTextureFit(const RenderTexture* image, bool center);`",
        [](VM* vm, ArgsView args){
            RenderTexture* image = CAST(RenderTexture*, args[0]);
            bool center = CAST(bool, args[1]);
            rlImGuiImageRenderTextureFit(image, center);
            return vm->None;
        });

    vm->bind(imgui, "rlImGuiImageButton(name: str, image: Texture_p) -> bool",
        "Wraps `bool rlImGuiImageButton(const char* name, const Texture* image);`",
        [](VM* vm, ArgsView args){
            const char* name = CAST(const char*, args[0]);
            Texture* image = CAST(Texture*, args[1]);
            bool ret = rlImGuiImageButton(name, image);
            return VAR(ret);
        });

    vm->bind(imgui, "rlImGuiImageButtonSize(name: str, image: Texture_p, size: vec2) -> bool",
        "Wraps `bool rlImGuiImageButtonSize(const char* name, const Texture* image, struct ImVec2 size);`",
        [](VM* vm, ArgsView args){
            const char* name = CAST(CString, args[0]);
            Texture* image = CAST(Texture*, args[1]);
            ImVec2 size = CAST(ImVec2, args[2]);
            bool ret = rlImGuiImageButtonSize(name, image, size);
            return VAR(ret);
        });
    ////////////////////////////////////////

    // struct ImGuiContext;                // Dear ImGui context (opaque structure, unless including imgui_internal.h)
    // NOTE: context is an opaque pointer, so we treat it as void_p
    // vm->bind(imgui, "CreateContext() -> void_p",
    //     PK_VAR_LAMBDA(ImGui::CreateContext())
    //     );

    // vm->bind(imgui, "DestroyContext(ctx: void_p = None)",
    //     [](VM* vm, ArgsView args){
    //         void* ctx = CAST(void*, args[0]);
    //         ImGui::DestroyContext((ImGuiContext*)ctx);
    //         return vm->None;
    //     });

    // vm->bind(imgui, "GetCurrentContext() -> void_p",
    //     PK_VAR_LAMBDA(ImGui::GetCurrentContext())
    //     );

    // vm->bind(imgui, "SetCurrentContext(ctx: void_p)",
    //     [](VM* vm, ArgsView args){
    //         ImGui::SetCurrentContext((ImGuiContext*)CAST(void*, args[0]));
    //         return vm->None;
    //     });

    
    // Main
    vm->bind(imgui, "GetIO() -> _IO",
        "access the IO structure (mouse/keyboard/gamepad inputs, time, various configuration options/flags)",
        PK_LAMBDA(VAR_T(PyImGuiIO, &ImGui::GetIO()))
        );

    vm->bind(imgui, "GetStyle() -> _Style",
        "access the Style structure (colors, sizes). Always use PushStyleCol(), PushStyleVar() to modify style mid-frame!",
        PK_LAMBDA(VAR_T(PyImGuiStyle, &ImGui::GetStyle()))
        );

    vm->bind(imgui, "NewFrame()",
        "Wraps `void rlImGuiBegin();`",
        PK_ACTION(rlImGuiBegin())
        );

    vm->bind(imgui, "EndFrame()",
        "ends the Dear ImGui frame. automatically called by Render(). If you don't need to render data (skipping rendering) you may call EndFrame() without Render()... but you'll have wasted CPU already! If you don't need to render, better to not create any windows and not call NewFrame() at all!",
        PK_ACTION(ImGui::EndFrame())
        );

    vm->bind(imgui, "Render()",
        "Wraps `void rlImGuiEnd();`",
        PK_ACTION(rlImGuiEnd())
        );

    vm->bind(imgui, "GetDrawData() -> void_p",
        "valid after Render() and until the next call to NewFrame(). this is what you have to render.",
        PK_VAR_LAMBDA(ImGui::GetDrawData())
        );

    // Demo, Debug, Information
    vm->bind(imgui, "ShowDemoWindow(p_open: bool_p = None)",
        "create Demo window. demonstrate most ImGui features. call this to learn about the library! try to make it always available in your application!",
        [](VM* vm, ArgsView args){
            bool* p_open = CAST(bool*, args[0]);
            ImGui::ShowDemoWindow(p_open);
            return vm->None;
        });

    vm->bind(imgui, "ShowMetricsWindow(p_open: bool_p = None)",
        [](VM* vm, ArgsView args){
            bool* p_open = CAST(bool*, args[0]);
            ImGui::ShowMetricsWindow(p_open);
            return vm->None;
        });

    // ...

    vm->bind(imgui, "GetVersion() -> str",
        "get the compiled version string e.g. \"1.80 WIP\" (essentially the value for IMGUI_VERSION from the compiled version of imgui.cpp)",
        PK_VAR_LAMBDA(ImGui::GetVersion())
        );

    // Styles
    vm->bind(imgui, "StyleColorsDark()",
        "new, recommended style (default)",
        PK_ACTION(ImGui::StyleColorsDark())
        );

    vm->bind(imgui, "StyleColorsLight()",
        "best used with borders and a custom, thicker font",
        PK_ACTION(ImGui::StyleColorsLight())
        );

    vm->bind(imgui, "StyleColorsClassic()",
        "classic imgui style",
        PK_ACTION(ImGui::StyleColorsClassic())
        );

    // Windows
    vm->bind(imgui, "Begin(name: str, p_open: bool_p = None, flags=0) -> bool",
"- Begin() = push window to the stack and start appending to it. End() = pop window from the stack.\n"
"- Passing 'bool* p_open != NULL' shows a window-closing widget in the upper-right corner of the window,\n"
"   which clicking will set the boolean to false when clicked.\n"
"- You may append multiple times to the same window during the same frame by calling Begin()/End() pairs multiple times.\n"
"    Some information such as 'flags' or 'p_open' will only be considered by the first call to Begin().\n"
"- Begin() return false to indicate the window is collapsed or fully clipped, so you may early out and omit submitting\n"
"    anything to the window. Always call a matching End() for each Begin() call, regardless of its return value!\n"
"    [Important: due to legacy reason, this is inconsistent with most other functions such as BeginMenu/EndMenu,\n"
"    BeginPopup/EndPopup, etc. where the EndXXX call should only be called if the corresponding BeginXXX function\n"
"    returned true. Begin and BeginChild are the only odd ones out. Will be fixed in a future update.]\n"
"- Note that the bottom of window stack always contains a window called 'Debug'.\n",
        [](VM* vm, ArgsView args){
            const char* name = CAST(CString, args[0]);
            bool* p_open = CAST(bool*, args[1]);
            ImGuiWindowFlags flags = CAST(int, args[2]);
            bool open = ImGui::Begin(name, p_open, flags);
            return VAR(open);
        });

    vm->bind(imgui, "End()",
        PK_ACTION(ImGui::End())
        );

    // Child Windows
    vm->bind(imgui, "BeginChild(str_id: str, size: vec2 = None, border=False, flags=0)",
"- Use child windows to begin into a self-contained independent scrolling/clipping regions within a host window. Child windows can embed their own child.\n"
"- For each independent axis of 'size': ==0.0f: use remaining host window size / >0.0f: fixed size / <0.0f: use remaining window size minus abs(size) / Each axis can use a different mode, e.g. ImVec2(0,400).\n"
"- BeginChild() returns false to indicate the window is collapsed or fully clipped, so you may early out and omit submitting anything to the window.\n"
"    Always call a matching EndChild() for each BeginChild() call, regardless of its return value.\n"
"    [Important: due to legacy reason, this is inconsistent with most other functions such as BeginMenu/EndMenu,\n"
"    BeginPopup/EndPopup, etc. where the EndXXX call should only be called if the corresponding BeginXXX function\n"
"    returned true. Begin and BeginChild are the only odd ones out. Will be fixed in a future update.]\n",
        [](VM* vm, ArgsView args){
            const char* str_id = CAST(CString, args[0]);
            ImVec2 size = CAST_DEFAULT(ImVec2, args[1], ImVec2(0, 0));
            bool border = CAST(bool, args[2]);
            ImGuiWindowFlags flags = CAST(int, args[3]);
            bool open = ImGui::BeginChild(str_id, size, border, flags);
            return VAR(open);
        });

    vm->bind(imgui, "EndChild()",
        PK_ACTION(ImGui::EndChild())
        );

    // Windows Utilities
    // - 'current window' = the window we are appending into while inside a Begin()/End() block. 'next window' = next window we will Begin() into.
    vm->bind(imgui, "IsWindowAppearing() -> bool",
        PK_VAR_LAMBDA(ImGui::IsWindowAppearing())
        );

    vm->bind(imgui, "IsWindowCollapsed() -> bool",
        PK_VAR_LAMBDA(ImGui::IsWindowCollapsed())
        );

    vm->bind(imgui, "IsWindowFocused(flags=0) -> bool",
        "is current window focused? or its root/child, depending on flags. see flags for options.",
        [](VM* vm, ArgsView args){
            ImGuiFocusedFlags flags = CAST(int, args[0]);
            return VAR(ImGui::IsWindowFocused(flags));
        });

    vm->bind(imgui, "IsWindowHovered(flags=0) -> bool",
        "is current window hovered (and typically: not blocked by a popup/modal)? see flags for options. NB: If you are trying to check whether your mouse should be dispatched to imgui or to your app, you should use the 'io.WantCaptureMouse' boolean for that! Please read the FAQ!",
        [](VM* vm, ArgsView args){
            ImGuiHoveredFlags flags = CAST(int, args[0]);
            return VAR(ImGui::IsWindowHovered(flags));
        });

    vm->bind(imgui, "GetWindowDrawList() -> void_p",
        "get draw list associated to the current window, to append your own drawing primitives",
        PK_VAR_LAMBDA(ImGui::GetWindowDrawList())
        );

    vm->bind(imgui, "GetWindowPos() -> vec2",
        "get current window position in screen space (useful if you want to do your own drawing via the DrawList API)",
        PK_VAR_LAMBDA(ImGui::GetWindowPos())
        );

    vm->bind(imgui, "GetWindowSize() -> vec2",
        "get current window size",
        PK_VAR_LAMBDA(ImGui::GetWindowSize())
        );

    vm->bind(imgui, "GetWindowWidth() -> float",
        "get current window width (shortcut for GetWindowSize().x)",
        PK_VAR_LAMBDA(ImGui::GetWindowWidth())
        );

    vm->bind(imgui, "GetWindowHeight() -> float",
        "get current window height (shortcut for GetWindowSize().y)",
        PK_VAR_LAMBDA(ImGui::GetWindowHeight())
        );

    // Window manipulation
    // - Prefer using SetNextXXX functions (before Begin) rather that SetXXX functions (after Begin).
    // [SKIP: SetXXX functions]
    vm->bind(imgui, "SetNextWindowPos(pos: vec2, cond=0, pivot=None)",
        "set next window position. call before Begin(). use pivot=(0.5f,0.5f) to center on given point, etc.",
        [](VM* vm, ArgsView args){
            ImVec2 pos = CAST(ImVec2, args[0]);
            ImGuiCond cond = CAST(int, args[1]);
            ImVec2 pivot = CAST_DEFAULT(ImVec2, args[2], ImVec2(0, 0));
            ImGui::SetNextWindowPos(pos, cond, pivot);
            return vm->None;
        });

    vm->bind(imgui, "SetNextWindowSize(size: vec2, cond=0)",
        "set next window size. set axis to 0.0f to force an auto-fit on this axis. call before Begin()",
        [](VM* vm, ArgsView args){
            ImVec2 size = CAST(ImVec2, args[0]);
            ImGuiCond cond = CAST(int, args[1]);
            ImGui::SetNextWindowSize(size, cond);
            return vm->None;
        });

    vm->bind(imgui, "SetNextWindowSizeConstraints(size_min: vec2, size_max: vec2)",
        "set next window size limits. use -1,-1 on either X/Y axis to preserve the current size. Sizes will be rounded down. Use callback to apply non-trivial programmatic constraints.",
        [](VM* vm, ArgsView args){
            ImVec2 size_min = CAST(ImVec2, args[0]);
            ImVec2 size_max = CAST(ImVec2, args[1]);
            ImGui::SetNextWindowSizeConstraints(size_min, size_max);
            return vm->None;
        });

    vm->bind(imgui, "SetNextWindowContentSize(size: vec2)",
        "set next window content size (~ scrollable client area, which enforce the range of scrollbars). Not including window decorations (title bar, menu bar, etc.) nor WindowPadding. set an axis to 0.0f to leave it automatic. call before Begin()",
        [](VM* vm, ArgsView args){
            ImVec2 size = CAST(ImVec2, args[0]);
            ImGui::SetNextWindowContentSize(size);
            return vm->None;
        });

    vm->bind(imgui, "SetNextWindowCollapsed(collapsed: bool, cond=0)",
        "set next window collapsed state. call before Begin()",
        [](VM* vm, ArgsView args){
            bool collapsed = CAST(bool, args[0]);
            ImGuiCond cond = CAST(int, args[1]);
            ImGui::SetNextWindowCollapsed(collapsed, cond);
            return vm->None;
        });

    vm->bind(imgui, "SetNextWindowFocus()",
        "set next window to be focused / top-most. call before Begin()",
        [](VM* vm, ArgsView args){
            ImGui::SetNextWindowFocus();
            return vm->None;
        });

    vm->bind(imgui, "SetNextWindowScroll(scroll: vec2)",
        "set next window scrolling value (use < 0.0f to not affect a given axis).",
        [](VM* vm, ArgsView args){
            ImVec2 scroll = CAST(ImVec2, args[0]);
            ImGui::SetNextWindowScroll(scroll);
            return vm->None;
        });

    vm->bind(imgui, "SetNextWindowBgAlpha(alpha: float)",
        "set next window background alpha.",
        [](VM* vm, ArgsView args){
            float alpha = CAST_F(args[0]);
            ImGui::SetNextWindowBgAlpha(alpha);
            return vm->None;
        });

    // Content region
    // - Retrieve available space from a given point. GetContentRegionAvail() is frequently useful.
    // - Those functions are bound to be redesigned (they are confusing, incomplete and the Min/Max return values are in local window coordinates which increases confusion)
    vm->bind(imgui, "GetContentRegionAvail() -> vec2",
        "== GetContentRegionMax() - GetCursorPos()",
        PK_VAR_LAMBDA(ImGui::GetContentRegionAvail())
        );

    vm->bind(imgui, "GetContentRegionMax() -> vec2",
        "current content boundaries (typically window boundaries including scrolling, or current column boundaries), in windows coordinates",
        PK_VAR_LAMBDA(ImGui::GetContentRegionMax())
        );

    vm->bind(imgui, "GetWindowContentRegionMin() -> vec2",
        "content boundaries min (roughly (0,0)-Scroll), in window coordinates",
        PK_VAR_LAMBDA(ImGui::GetWindowContentRegionMin())
        );

    vm->bind(imgui, "GetWindowContentRegionMax() -> vec2",
        "content boundaries max (roughly (0,0)+Size-Scroll) where Size can be override with SetNextWindowContentSize(), in window coordinates",
        PK_VAR_LAMBDA(ImGui::GetWindowContentRegionMax())
        );

    // Window Scrolling
    // - Any change of Scroll will be applied at the beginning of next frame in the first call to Begin().
    // - You may instead use SetNextWindowScroll() prior to calling Begin() to avoid this delay, as an alternative to using SetScrollX()/SetScrollY().
    vm->bind(imgui, "GetScrollX()",
        "get scrolling amount [0 .. GetScrollMaxX()]",
        PK_VAR_LAMBDA(ImGui::GetScrollX())
        );

    vm->bind(imgui, "GetScrollY()",
        "get scrolling amount [0 .. GetScrollMaxY()]",
        PK_VAR_LAMBDA(ImGui::GetScrollY())
        );

    vm->bind(imgui, "SetScrollX(scroll_x: float)",
        "set scrolling amount [0 .. GetScrollMaxX()]",
        [](VM* vm, ArgsView args){
            float scroll_x = CAST_F(args[0]);
            ImGui::SetScrollX(scroll_x);
            return vm->None;
        });

    vm->bind(imgui, "SetScrollY(scroll_y: float)",
        "set scrolling amount [0 .. GetScrollMaxY()]",
        [](VM* vm, ArgsView args){
            float scroll_y = CAST_F(args[0]);
            ImGui::SetScrollY(scroll_y);
            return vm->None;
        });

    vm->bind(imgui, "GetScrollMaxX()",
        "get maximum scrolling amount ~~ ContentSize.x - WindowSize.x - DecorationsSize.x",
        PK_VAR_LAMBDA(ImGui::GetScrollMaxX())
        );

    vm->bind(imgui, "GetScrollMaxY()",
        "get maximum scrolling amount ~~ ContentSize.y - WindowSize.y - DecorationsSize.y",
        PK_VAR_LAMBDA(ImGui::GetScrollMaxY())
        );

    vm->bind(imgui, "SetScrollHereX(center_x_ratio=0.5)",
        "adjust scrolling amount to make current cursor position visible. center_x_ratio=0.0: left, 0.5: center, 1.0: right. When using to make a \"default/current item\" visible, consider using SetItemDefaultFocus() instead.",
        [](VM* vm, ArgsView args){
            float center_x_ratio = CAST_F(args[0]);
            ImGui::SetScrollHereX(center_x_ratio);
            return vm->None;
        });

    vm->bind(imgui, "SetScrollHereY(center_y_ratio=0.5)",
        "adjust scrolling amount to make current cursor position visible. center_y_ratio=0.0: top, 0.5: center, 1.0: bottom. When using to make a \"default/current item\" visible, consider using SetItemDefaultFocus() instead.",
        [](VM* vm, ArgsView args){
            float center_y_ratio = CAST_F(args[0]);
            ImGui::SetScrollHereY(center_y_ratio);
            return vm->None;
        });

    vm->bind(imgui, "SetScrollFromPosX(local_x: float, center_x_ratio=0.5)",
        "adjust scrolling amount to make given position visible. Generally GetCursorStartPos() + offset to compute a valid position.",
        [](VM* vm, ArgsView args){
            float local_x = CAST_F(args[0]);
            float center_x_ratio = CAST_F(args[1]);
            ImGui::SetScrollFromPosX(local_x, center_x_ratio);
            return vm->None;
        });

    vm->bind(imgui, "SetScrollFromPosY(local_y: float, center_y_ratio=0.5)",
        "adjust scrolling amount to make given position visible. Generally GetCursorStartPos() + offset to compute a valid position.",
        [](VM* vm, ArgsView args){
            float local_y = CAST_F(args[0]);
            float center_y_ratio = CAST_F(args[1]);
            ImGui::SetScrollFromPosY(local_y, center_y_ratio);
            return vm->None;
        });

    // Parameters stacks (shared)
    // vm->bind(imgui, "PushFont(font: ImFont)",
    //     "use None as a shortcut to push default font",
    //     [](VM* vm, ArgsView args){
    //         ImFont* font = CAST(PyImFont&, args[0]).ptr;
    //         ImGui::PushFont(font);
    //         return vm->None;
    //     });

    vm->bind(imgui, "PopFont()",
        PK_ACTION(ImGui::PopFont())
        );

    vm->bind(imgui, "PushStyleColor(idx: int, col: vec4)",
        "modify a style color. always use this if you modify the style after NewFrame().",
        [](VM* vm, ArgsView args){
            ImGuiCol idx = CAST(ImGuiCol, args[0]);
            ImVec4 col = CAST(ImVec4, args[1]);
            ImGui::PushStyleColor(idx, col);
            return vm->None;
        });

    vm->bind(imgui, "PopStyleColor(count=1)",
        [](VM* vm, ArgsView args){
            int count = CAST(int, args[0]);
            ImGui::PopStyleColor(count);
            return vm->None;
        });

    vm->bind(imgui, "PushStyleVar(idx: int, val: float)",
        "modify a style float variable. always use this if you modify the style after NewFrame().",
        [](VM* vm, ArgsView args){
            ImGuiStyleVar idx = CAST(ImGuiStyleVar, args[0]);
            float val = CAST_F(args[1]);
            ImGui::PushStyleVar(idx, val);
            return vm->None;
        });

    vm->bind(imgui, "PushStyleVar(idx: int, val: vec2)",
        "modify a style ImVec2 variable. always use this if you modify the style after NewFrame().",
        [](VM* vm, ArgsView args){
            ImGuiStyleVar idx = CAST(ImGuiStyleVar, args[0]);
            ImVec2 val = CAST(ImVec2, args[1]);
            ImGui::PushStyleVar(idx, val);
            return vm->None;
        });

    vm->bind(imgui, "PopStyleVar(count=1)",
        [](VM* vm, ArgsView args){
            int count = CAST(int, args[0]);
            ImGui::PopStyleVar(count);
            return vm->None;
        });

    vm->bind(imgui, "PushTabStop(tab_stop: bool)",
        "== tab stop enable. Allow focusing using TAB/Shift-TAB, enabled by default but you can disable it for certain widgets",
        [](VM* vm, ArgsView args){
            bool tab_stop = CAST(bool, args[0]);
            ImGui::PushTabStop(tab_stop);
            return vm->None;
        });

    vm->bind(imgui, "PopTabStop()",
        PK_ACTION(ImGui::PopTabStop())
        );

    vm->bind(imgui, "PushButtonRepeat(repeat: bool)",
        "in 'repeat' mode, Button*() functions return repeated true in a typematic manner (using io.KeyRepeatDelay/io.KeyRepeatRate setting). Note that you can call IsItemActive() after any Button() to tell if the button is held in the current frame.",
        [](VM* vm, ArgsView args){
            bool repeat = CAST(bool, args[0]);
            ImGui::PushButtonRepeat(repeat);
            return vm->None;
        });

    vm->bind(imgui, "PopButtonRepeat()",
        PK_ACTION(ImGui::PopButtonRepeat())
        );

    // Parameters stacks (current window)
    vm->bind(imgui, "PushItemWidth(item_width: float)",
        "push width of items for common large \"item+label\" widgets. >0.0f: width in pixels, <0.0f align xx pixels to the right of window (so -FLT_MIN always align width to the right side).",
        [](VM* vm, ArgsView args){
            float item_width = CAST_F(args[0]);
            ImGui::PushItemWidth(item_width);
            return vm->None;
        });

    vm->bind(imgui, "PopItemWidth()",
        PK_ACTION(ImGui::PopItemWidth())
        );

    vm->bind(imgui, "SetNextItemWidth(item_width: float)",
        "set width of the _next_ common large \"item+label\" widget. >0.0f: width in pixels, <0.0f align xx pixels to the right of window (so -FLT_MIN always align width to the right side)",
        [](VM* vm, ArgsView args){
            float item_width = CAST_F(args[0]);
            ImGui::SetNextItemWidth(item_width);
            return vm->None;
        });

    vm->bind(imgui, "CalcItemWidth() -> float",
        "width of item given pushed settings and current cursor position. NOT necessarily the width of last item unlike most 'Item' functions.",
        PK_VAR_LAMBDA(ImGui::CalcItemWidth())
        );

    vm->bind(imgui, "PushTextWrapPos(wrap_local_pos_x: float = 0.0)",
        "push word-wrapping position for Text*() commands. < 0.0f: no wrapping; 0.0f: wrap to end of window (or column); > 0.0f: wrap at 'wrap_pos_x' position in window local space",
        [](VM* vm, ArgsView args){
            float wrap_local_pos_x = CAST_F(args[0]);
            ImGui::PushTextWrapPos(wrap_local_pos_x);
            return vm->None;
        });

    vm->bind(imgui, "PopTextWrapPos()",
        PK_ACTION(ImGui::PopTextWrapPos())
        );

    // Style read access
    // - Use the ShowStyleEditor() function to interactively see/edit the colors.
    // vm->bind(imgui, "GetFont() -> ImFont",
    //     "get current font",
    //     [](VM* vm, ArgsView args){
    //         return VAR_T(PyImFont, ImGui::GetFont());
    //     });

    vm->bind(imgui, "GetFontSize() -> float",
        "get current font size (= height in pixels) of current font with current scale applied",
        PK_VAR_LAMBDA(ImGui::GetFontSize())
        );

    vm->bind(imgui, "GetFontTexUvWhitePixel() -> vec2",
        "get UV coordinate for a while pixel, useful to draw custom shapes via the ImDrawList API",
        PK_VAR_LAMBDA(ImGui::GetFontTexUvWhitePixel())
        );
    vm->bind(imgui, "GetStyleColorVec4(idx: int) -> vec4",
        "retrieve style color as stored in ImGuiStyle structure. use to feed back into PushStyleColor(), otherwise use GetColorU32() to get style color with style alpha baked in.",
        [](VM* vm, ArgsView args){
            ImGuiCol idx = CAST(ImGuiCol, args[0]);
            ImVec4 v = ImGui::GetStyleColorVec4(idx);
            return VAR(v);
        });

    // Cursor / Layout
    // - By "cursor" we mean the current output position.
    // - The typical widget behavior is to output themselves at the current cursor position, then move the cursor one line down.
    // - You can call SameLine() between widgets to undo the last carriage return and output at the right of the preceding widget.
    // - Attention! We currently have inconsistencies between window-local and absolute positions we will aim to fix with future API:
    //    Window-local coordinates:   SameLine(), GetCursorPos(), SetCursorPos(), GetCursorStartPos(), GetContentRegionMax(), GetWindowContentRegion*(), PushTextWrapPos()
    //    Absolute coordinate:        GetCursorScreenPos(), SetCursorScreenPos(), all ImDrawList:: functions.
    vm->bind(imgui, "Separator()",
        "separator, generally horizontal. inside a menu bar or in horizontal layout mode, this becomes a vertical separator.",
        PK_ACTION(ImGui::Separator())
        );

    vm->bind(imgui, "SameLine(offset_from_start_x=0.0, spacing=-1.0)",
        "call between widgets or groups to layout them horizontally. X position given in window coordinates.",
        [](VM* vm, ArgsView args){
            float offset_from_start_x = CAST_F(args[0]);
            float spacing = CAST_F(args[1]);
            ImGui::SameLine(offset_from_start_x, spacing);
            return vm->None;
        });

    vm->bind(imgui, "NewLine()",
        "undo a SameLine() or force a new line when in a horizontal-layout context.",
        PK_ACTION(ImGui::NewLine())
        );

    vm->bind(imgui, "Spacing()",
        "add vertical spacing.",
        PK_ACTION(ImGui::Spacing())
        );

    vm->bind(imgui, "Dummy(size: vec2)",
        "add a dummy item of given size. unlike InvisibleButton(), Dummy() won't take the mouse click or be navigable into.",
        [](VM* vm, ArgsView args){
            ImVec2 size = CAST(ImVec2, args[0]);
            ImGui::Dummy(size);
            return vm->None;
        });

    vm->bind(imgui, "Indent(indent_w=0.0)",
        "move content position toward the right, by indent_w, or style.IndentSpacing if indent_w <= 0",
        [](VM* vm, ArgsView args){
            float indent_w = CAST_F(args[0]);
            ImGui::Indent(indent_w);
            return vm->None;
        });

    vm->bind(imgui, "Unindent(indent_w=0.0)",
        "move content position back to the left, by indent_w, or style.IndentSpacing if indent_w <= 0",
        [](VM* vm, ArgsView args){
            float indent_w = CAST_F(args[0]);
            ImGui::Unindent(indent_w);
            return vm->None;
        });

    vm->bind(imgui, "BeginGroup()",
        "lock horizontal starting position",
        PK_ACTION(ImGui::BeginGroup())
        );

    vm->bind(imgui, "EndGroup()",
        "unlock horizontal starting position + capture the whole group bounding box into one \"item\" (so you can use IsItemHovered() or layout primitives such as SameLine() on whole group, etc.)",
        PK_ACTION(ImGui::EndGroup())
        );

    vm->bind(imgui, "GetCursorPos() -> vec2",
        "cursor position in window coordinates (relative to window position)",
        PK_VAR_LAMBDA(ImGui::GetCursorPos())
        );

    vm->bind(imgui, "GetCursorPosX() -> float",
        PK_VAR_LAMBDA(ImGui::GetCursorPosX())
        );

    vm->bind(imgui, "GetCursorPosY() -> float",
        PK_VAR_LAMBDA(ImGui::GetCursorPosY())
        );

    vm->bind(imgui, "SetCursorPos(local_pos: vec2)",
        "cursor position in window coordinates (relative to window position)",
        [](VM* vm, ArgsView args){
            ImVec2 local_pos = CAST(ImVec2, args[0]);
            ImGui::SetCursorPos(local_pos);
            return vm->None;
        });

    vm->bind(imgui, "SetCursorPosX(local_x: float)",
        [](VM* vm, ArgsView args){
            float local_x = CAST_F(args[0]);
            ImGui::SetCursorPosX(local_x);
            return vm->None;
        });

    vm->bind(imgui, "SetCursorPosY(local_y: float)",
        [](VM* vm, ArgsView args){
            float local_y = CAST_F(args[0]);
            ImGui::SetCursorPosY(local_y);
            return vm->None;
        });

    vm->bind(imgui, "GetCursorStartPos() -> vec2",
        "initial cursor position in window coordinates",
        PK_VAR_LAMBDA(ImGui::GetCursorStartPos())
        );

    vm->bind(imgui, "GetCursorScreenPos() -> vec2",
        "cursor position in absolute screen coordinates (0..io.DisplaySize) or natural OS coordinates when using multiple viewport. useful to work with ImDrawList API.",
        PK_VAR_LAMBDA(ImGui::GetCursorScreenPos())
        );

    vm->bind(imgui, "SetCursorScreenPos(pos: vec2)",
        "cursor position in absolute screen coordinates (0..io.DisplaySize) or natural OS coordinates when using multiple viewport. useful to work with ImDrawList API.",
        [](VM* vm, ArgsView args){
            ImVec2 pos = CAST(ImVec2, args[0]);
            ImGui::SetCursorScreenPos(pos);
            return vm->None;
        });

    vm->bind(imgui, "AlignTextToFramePadding()",
        "vertically align/lower upcoming text to FramePadding.y so that it will aligns to upcoming widgets (call if you have text on a line before regular widgets)",
        PK_ACTION(ImGui::AlignTextToFramePadding())
        );

    vm->bind(imgui, "GetTextLineHeight() -> float",
        "~ FontSize",
        PK_VAR_LAMBDA(ImGui::GetTextLineHeight())
        );

    vm->bind(imgui, "GetTextLineHeightWithSpacing() -> float",
        "~ FontSize + style.ItemSpacing.y (distance in pixels between 2 consecutive lines of text)",
        PK_VAR_LAMBDA(ImGui::GetTextLineHeightWithSpacing())
        );

    vm->bind(imgui, "GetFrameHeight() -> float",
        "~ FontSize + style.FramePadding.y * 2",
        PK_VAR_LAMBDA(ImGui::GetFrameHeight())
        );

    vm->bind(imgui, "GetFrameHeightWithSpacing() -> float",
        "~ FontSize + style.FramePadding.y * 2 + style.ItemSpacing.y (distance in pixels between 2 consecutive lines of framed widgets)",
        PK_VAR_LAMBDA(ImGui::GetFrameHeightWithSpacing())
        );
    
    // ID stack/scopes
    vm->bind(imgui, "PushID(x)",
        [](VM* vm, ArgsView args){
            if(is_non_tagged_type(args[0], vm->tp_str)){
                const char* str_id = _CAST(CString, args[0]);
                ImGui::PushID(str_id);
            }else if(is_int(args[0])){
                int int_id = _CAST(int, args[0]);
                ImGui::PushID(int_id);
            }else if(is_non_tagged_type(args[0], VoidP::_type(vm))){
                void* ptr_id = _CAST(VoidP&, args[0]).ptr;
                ImGui::PushID(ptr_id);
            }else{
                vm->TypeError("expected str, int or void_p");
            }
            return vm->None;
        });

    vm->bind_func<0>(imgui, "PopID", PK_ACTION(ImGui::PopID()));
    
    // Widgets: Text
    vm->bind(imgui, "Text(s: str)",
        [](VM* vm, ArgsView args){
            const char* text = CAST(CString, args[0]);
            ImGui::Text("%s", text);
            return vm->None;
        });

    vm->bind(imgui, "TextColored(col: vec4, s: str)",
        [](VM* vm, ArgsView args){
            ImVec4 col = CAST(ImVec4, args[0]);
            const char* text = CAST(CString, args[1]);
            ImGui::TextColored(col, "%s", text);
            return vm->None;
        });

    vm->bind(imgui, "TextDisabled(s: str)",
        [](VM* vm, ArgsView args){
            const char* text = CAST(CString, args[0]);
            ImGui::TextDisabled("%s", text);
            return vm->None;
        });

    vm->bind(imgui, "TextWrapped(s: str)",
        [](VM* vm, ArgsView args){
            const char* text = CAST(CString, args[0]);
            ImGui::TextWrapped("%s", text);
            return vm->None;
        });

    vm->bind(imgui, "LabelText(label: str, s: str)",
        [](VM* vm, ArgsView args){
            const char* label = CAST(CString, args[0]);
            const char* text = CAST(CString, args[1]);
            ImGui::LabelText(label, "%s", text);
            return vm->None;
        });

    vm->bind(imgui, "BulletText(s: str)",
        [](VM* vm, ArgsView args){
            const char* text = CAST(CString, args[0]);
            ImGui::BulletText("%s", text);
            return vm->None;
        });

    vm->bind(imgui, "SeparatorText(label: str)",
        [](VM* vm, ArgsView args){
            const char* label = CAST(CString, args[0]);
            ImGui::SeparatorText(label);
            return vm->None;
        });

    // Widgets: Main
    // - Most widgets return true when the value has been changed or when pressed/selected
    // - You may also use one of the many IsItemXXX functions (e.g. IsItemActive, IsItemHovered, etc.) to query widget state.
    vm->bind(imgui, "Button(label: str, size=None) -> bool",
        "button",
        [](VM* vm, ArgsView args){
            const char* label = CAST(CString, args[0]);
            ImVec2 size = CAST_DEFAULT(ImVec2, args[1], ImVec2(0, 0));
            bool ret = ImGui::Button(label, size);
            return VAR(ret);
        });

    vm->bind(imgui, "SmallButton(label: str) -> bool",
        "button with FramePadding=(0,0) to easily embed within text",
        [](VM* vm, ArgsView args){
            const char* label = CAST(CString, args[0]);
            bool ret = ImGui::SmallButton(label);
            return VAR(ret);
        });

    vm->bind(imgui, "InvisibleButton(str_id: str, size: vec2, flags=0) -> bool",
        "flexible button behavior without the visuals, frequently useful to build custom behaviors using the public api (along with IsItemActive, IsItemHovered, etc.)",
        [](VM* vm, ArgsView args){
            const char* str_id = CAST(CString, args[0]);
            ImVec2 size = CAST(ImVec2, args[1]);
            ImGuiButtonFlags flags = CAST(ImGuiButtonFlags, args[2]);
            bool ret = ImGui::InvisibleButton(str_id, size, flags);
            return VAR(ret);
        });

    vm->bind(imgui, "ArrowButton(str_id: str, dir: int) -> bool",
        "square button with an arrow shape",
        [](VM* vm, ArgsView args){
            const char* str_id = CAST(CString, args[0]);
            ImGuiDir dir = CAST(ImGuiDir, args[1]);
            bool ret = ImGui::ArrowButton(str_id, dir);
            return VAR(ret);
        });

    vm->bind(imgui, "Checkbox(label: str, v: bool_p) -> bool",
        [](VM* vm, ArgsView args){
            const char* label = CAST(CString, args[0]);
            bool* v = CAST(bool*, args[1]);
            bool ret = ImGui::Checkbox(label, v);
            return VAR(ret);
        });

    vm->bind(imgui, "CheckboxFlags(label: str, flags: int_p, flags_value: int) -> bool",
        [](VM* vm, ArgsView args){
            const char* label = CAST(CString, args[0]);
            int* flags = CAST(int*, args[1]);
            int flags_value = CAST(int, args[2]);
            bool ret = ImGui::CheckboxFlags(label, flags, flags_value);
            return VAR(ret);
        });

    vm->bind(imgui, "RadioButton(label: str, active: bool) -> bool",
        "use with e.g. if (RadioButton(\"one\", my_value==1)) { my_value = 1; }",
        [](VM* vm, ArgsView args){
            const char* label = CAST(CString, args[0]);
            bool active = CAST(bool, args[1]);
            bool ret = ImGui::RadioButton(label, active);
            return VAR(ret);
        });

    vm->bind(imgui, "ProgressBar(fraction: float, size: vec2=None, overlay: str=None)",
        [](VM* vm, ArgsView args){
            float fraction = CAST_F(args[0]);
            ImVec2 size = CAST_DEFAULT(ImVec2, args[1], ImVec2(-FLT_MIN, 0));
            const char* overlay = CAST_DEFAULT(CString, args[2], NULL);
            ImGui::ProgressBar(fraction, size, overlay);
            return vm->None;
        });

    vm->bind(imgui, "Bullet()",
        "draw a small circle + keep the cursor on the same line. advance cursor x position by GetTreeNodeToLabelSpacing(), same distance that TreeNode() uses",
        PK_ACTION(ImGui::Bullet())
        );

    // Widgets: Images
    // vm->bind(imgui, "Image(tex: Texture, size: vec2, uv0: vec2 = None, uv1: vec2 = None, tint_col: vec4 = None, border_col: vec4 = None)",
    //     "Read about ImTextureID here: https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples",
    //     [](VM* vm, ArgsView args){
    //         const Texture& tex = CAST(Texture&, args[0]);
    //         ImVec2 size = CAST(ImVec2, args[1]);
    //         ImVec2 uv0 = CAST_DEFAULT(ImVec2, args[2], ImVec2(0, 0));
    //         ImVec2 uv1 = CAST_DEFAULT(ImVec2, args[3], ImVec2(1, 1));
    //         ImVec4 tint_col = CAST_DEFAULT(ImVec4, args[4], ImVec4(1, 1, 1, 1));
    //         ImVec4 border_col = CAST_DEFAULT(ImVec4, args[5], ImVec4(0, 0, 0, 0));
    //         ImGui::Image(tex.imgui_id(), size, uv0, uv1, tint_col, border_col);
    //         return vm->None;
    //     });

    // vm->bind(imgui, "ImageButton(str_id: str, tex: Texture, size: vec2, uv0: vec2 = None, uv1: vec2 = None, bg_col: vec4 = None, tint_col: vec4 = None) -> bool",
    //     "Read about ImTextureID here: https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples",
    //     [](VM* vm, ArgsView args){
    //         const char* str_id = CAST(CString, args[0]);
    //         const Texture& tex = CAST(Texture&, args[1]);
    //         ImVec2 size = CAST(ImVec2, args[2]);
    //         ImVec2 uv0 = CAST_DEFAULT(ImVec2, args[3], ImVec2(0, 0));
    //         ImVec2 uv1 = CAST_DEFAULT(ImVec2, args[4], ImVec2(1, 1));
    //         ImVec4 bg_col = CAST_DEFAULT(ImVec4, args[5], ImVec4(0, 0, 0, 0));
    //         ImVec4 tint_col = CAST_DEFAULT(ImVec4, args[6], ImVec4(1, 1, 1, 1));
    //         bool ret = ImGui::ImageButton(str_id, tex.imgui_id(), size, uv0, uv1, bg_col, tint_col);
    //         return VAR(ret);
    //     });


    // Widgets: Combo Box (Dropdown)
    vm->bind(imgui, "BeginCombo(label: str, preview_value: str, flags=0) -> bool",
        "The BeginCombo()/EndCombo() api allows you to manage your contents and selection state however you want it, by creating e.g. Selectable() items.",
        [](VM* vm, ArgsView args){
            const char* label = CAST(CString, args[0]);
            const char* preview_value = CAST(CString, args[1]);
            ImGuiComboFlags flags = CAST(int, args[2]);
            return VAR(ImGui::BeginCombo(label, preview_value, flags));
        });

    vm->bind(imgui, "EndCombo()",
        "only call EndCombo() if BeginCombo() returns true!",
        PK_ACTION(ImGui::EndCombo()));

    vm->bind(imgui, "Combo(label: str, current_item: int_p, items: list[str], popup_max_height_in_items=-1)",
        "The old Combo() api are helpers over BeginCombo()/EndCombo() which are kept available for convenience purpose. This is analogous to how ListBox are created.",
        [](VM* vm, ArgsView args){
            const char* label = CAST(CString, args[0]);
            int* current_item = CAST(int*, args[1]);
            const List& items = CAST(List&, args[2]);
            std::vector<char> items_separated_by_zeros;
            for(PyObject* obj: items){
                for(char c: CAST(Str&, obj).sv()) items_separated_by_zeros.push_back(c);
                items_separated_by_zeros.push_back('\0');
            }
            items_separated_by_zeros.push_back('\0');
            int popup_max_height_in_items = CAST(int, args[3]);
            bool ret = ImGui::Combo(label, current_item, items_separated_by_zeros.data(), popup_max_height_in_items);
            return VAR(ret);
        });

    // Widgets: Drag Sliders
    // [SKIP]

    // Widgets: Regular Sliders
#define BIND_SLIDER_FLOAT(name)   \
vm->bind(imgui, #name "(label: str, v: float_p, v_min, v_max, format='%.3f', flags=0) -> bool",  \
    [](VM* vm, ArgsView args){  \
        const char* label = CAST(CString, args[0]); \
        float* v = CAST(float*, args[1]);   \
        float v_min = CAST_F(args[2]);  \
        float v_max = CAST_F(args[3]);  \
        const char* format = CAST(CString, args[4]);    \
        ImGuiSliderFlags flags = CAST(int, args[5]);    \
        bool ret = ImGui::name(label, v, v_min, v_max, format, flags);    \
        return VAR(ret);    \
    });

    BIND_SLIDER_FLOAT(SliderFloat)
    BIND_SLIDER_FLOAT(SliderFloat2)
    BIND_SLIDER_FLOAT(SliderFloat3)
    BIND_SLIDER_FLOAT(SliderFloat4)

#undef BIND_SLIDER_FLOAT

#define BIND_SLIDER_INT(name)   \
vm->bind(imgui, #name "(label: str, v: int_p, v_min, v_max, format='%d', flags=0) -> bool",  \
    [](VM* vm, ArgsView args){  \
        const char* label = CAST(CString, args[0]); \
        int* v = CAST(int*, args[1]);   \
        int v_min = CAST(int, args[2]);  \
        int v_max = CAST(int, args[3]);  \
        const char* format = CAST(CString, args[4]);    \
        ImGuiSliderFlags flags = CAST(int, args[5]);    \
        bool ret = ImGui::name(label, v, v_min, v_max, format, flags);    \
        return VAR(ret);    \
    });

    BIND_SLIDER_INT(SliderInt)
    BIND_SLIDER_INT(SliderInt2)
    BIND_SLIDER_INT(SliderInt3)
    BIND_SLIDER_INT(SliderInt4)

#undef BIND_SLIDER_INT

    // Widgets: Input with Keyboard
    vm->bind(imgui, "InputText(label: str, buf: char_p, buf_size: int, flags=0)",
        [](VM* vm, ArgsView args){
            const char* label = CAST(CString, args[0]);
            char* buf = CAST(char*, args[1]);
            size_t buf_size = CAST(size_t, args[2]);
            ImGuiInputTextFlags flags = CAST(int, args[3]);
            bool ret = ImGui::InputText(label, buf, buf_size, flags);
            return VAR(ret);
        });

    vm->bind(imgui, "InputTextMultiline(label: str, buf: char_p, buf_size: int, size: vec2 = None, flags=0)",
        [](VM* vm, ArgsView args){
            const char* label = CAST(CString, args[0]);
            char* buf = CAST(char*, args[1]);
            size_t buf_size = CAST(size_t, args[2]);
            ImVec2 size = CAST_DEFAULT(ImVec2, args[3], ImVec2(0, 0));
            ImGuiInputTextFlags flags = CAST(int, args[4]);
            bool ret = ImGui::InputTextMultiline(label, buf, buf_size, size, flags);
            return VAR(ret);
        });

    vm->bind(imgui, "InputTextWithHint(label: str, hint: str, buf: char_p, buf_size: int, flags=0)",
        [](VM* vm, ArgsView args){
            const char* label = CAST(CString, args[0]);
            const char* hint = CAST(CString, args[1]);
            char* buf = CAST(char*, args[2]);
            size_t buf_size = CAST(size_t, args[3]);
            ImGuiInputTextFlags flags = CAST(int, args[4]);
            bool ret = ImGui::InputTextWithHint(label, hint, buf, buf_size, flags);
            return VAR(ret);
        });

    vm->bind(imgui, "InputFloat(label: str, v: float_p, step=0.0, step_fast=0.0, format='%.3f', flags=0)",
        [](VM* vm, ArgsView args){
            const char* label = CAST(CString, args[0]);
            float* v = CAST(float*, args[1]);
            float step = CAST(float, args[2]);
            float step_fast = CAST(float, args[3]);
            const char* format = CAST(CString, args[4]);
            ImGuiInputTextFlags flags = CAST(int, args[5]);
            bool ret = ImGui::InputFloat(label, v, step, step_fast, format, flags);
            return VAR(ret);
        });

#define BIND_INPUT_FLOAT(name)  \
vm->bind(imgui, #name "(label: str, v: float_p, format='%.3f', flags=0) -> bool",  \
    [](VM* vm, ArgsView args){  \
        const char* label = CAST(CString, args[0]); \
        float* v = CAST(float*, args[1]);   \
        const char* format = CAST(CString, args[2]);    \
        ImGuiInputTextFlags flags = CAST(int, args[3]);    \
        bool ret = ImGui::name(label, v, format, flags);    \
        return VAR(ret);    \
    });
    BIND_INPUT_FLOAT(InputFloat2)
    BIND_INPUT_FLOAT(InputFloat3)
    BIND_INPUT_FLOAT(InputFloat4)

#undef BIND_INPUT_FLOAT

    vm->bind(imgui, "InputInt(label: str, v: int_p, step=1, step_fast=100, flags=0)",
        [](VM* vm, ArgsView args){
            const char* label = CAST(CString, args[0]);
            int* v = CAST(int*, args[1]);
            int step = CAST(int, args[2]);
            int step_fast = CAST(int, args[3]);
            ImGuiInputTextFlags flags = CAST(int, args[4]);
            bool ret = ImGui::InputInt(label, v, step, step_fast, flags);
            return VAR(ret);
        });

#define BIND_INPUT_INT(name)  \
vm->bind(imgui, #name "(label: str, v: int_p, flags=0) -> bool",  \
    [](VM* vm, ArgsView args){  \
        const char* label = CAST(CString, args[0]); \
        int* v = CAST(int*, args[1]);   \
        ImGuiInputTextFlags flags = CAST(int, args[2]);    \
        bool ret = ImGui::name(label, v, flags);    \
        return VAR(ret);    \
    });

    BIND_INPUT_INT(InputInt2)
    BIND_INPUT_INT(InputInt3)
    BIND_INPUT_INT(InputInt4)

#undef BIND_INPUT_INT

    // Widgets: Color Editor/Picker
    // ... (TODO)
    
    // Widgets: Trees
    vm->bind(imgui, "TreeNode(label: str, flags=0) -> bool",
        [](VM* vm, ArgsView args){
            const char* label = CAST(CString, args[0]);
            ImGuiTreeNodeFlags flags = CAST(int, args[1]);
            bool ret = ImGui::TreeNodeEx(label, flags);
            return VAR(ret);
        });

    vm->bind(imgui, "TreePush(str_id: str)",
        [](VM* vm, ArgsView args){
            const char* str_id = CAST(CString, args[0]);
            ImGui::TreePush(str_id);
            return vm->None;
        });

    vm->bind(imgui, "TreePop()",
        [](VM* vm, ArgsView args){
            ImGui::TreePop();
            return vm->None;
        });

    vm->bind(imgui, "SetNextItemOpen(is_open: bool, cond=0)",
        [](VM* vm, ArgsView args){
            bool is_open = CAST(bool, args[0]);
            ImGuiCond cond = CAST(int, args[1]);
            ImGui::SetNextItemOpen(is_open, cond);
            return vm->None;
        });

    // Widgets: Selectables
    // ... (TODO)

    // Widgets: List Boxes
    // ... (TODO)

    // Widgets: Data Plotting
    // ... (TODO)

    // Widgets: Value() Helpers
    // NOT NEEDED

    // Widgets: Menus
    // ... (TODO)

    // Tooltips
    vm->bind(imgui, "BeginTooltip() -> bool",
        "begin/append a tooltip window. to create full-featured tooltip (with any kind of items).",
        PK_VAR_LAMBDA(ImGui::BeginTooltip()));

    vm->bind(imgui, "EndTooltip()",
        "end/append tooltip window",
        PK_ACTION(ImGui::EndTooltip()));

    vm->bind(imgui, "SetTooltip(text: str)",
        "set a text-only tooltip, typically use with ImGui::IsItemHovered(). override any previous call to SetTooltip().",
        [](VM* vm, ArgsView args){
            const char* text = CAST(CString, args[0]);
            ImGui::SetTooltip("%s", text);
            return vm->None;
        });

    vm->bind(imgui, "BeginItemTooltip() -> bool",
        "begin/append a tooltip window. to create full-featured tooltip (with any kind of items).",
        PK_VAR_LAMBDA(ImGui::BeginTooltip()));

    vm->bind(imgui, "SetItemTooltip(text: str)",
        "set a text-only tooltip, typically use with ImGui::IsItemHovered(). override any previous call to SetTooltip().",
        [](VM* vm, ArgsView args){
            const char* text = CAST(CString, args[0]);
            ImGui::SetTooltip("%s", text);
            return vm->None;
        });

    // Popups, Modals
    // Popups: begin/end functions
    vm->bind(imgui, "BeginPopup(str_id: str, flags: int = 0) -> bool",
        "return true if the popup is open, and you can start outputting to it.",
        [](VM* vm, ArgsView args){
            const char* str_id = CAST(CString, args[0]);
            ImGuiWindowFlags flags = CAST_DEFAULT(ImGuiWindowFlags, args[1], ImGuiWindowFlags(0));
            bool ret = ImGui::BeginPopup(str_id, flags);
            return VAR(ret);
        });

    vm->bind(imgui, "BeginPopupModal(name: str, p_open=None, flags: int = 0) -> bool",
        "return true if the modal is open, and you can start outputting to it.",
        [](VM* vm, ArgsView args){
            const char* name = CAST(CString, args[0]);
            bool* p_open = CAST_DEFAULT(bool*, args[1], NULL);
            ImGuiWindowFlags flags = CAST_DEFAULT(ImGuiWindowFlags, args[2], ImGuiWindowFlags(0));
            bool ret = ImGui::BeginPopupModal(name, p_open, flags);
            return VAR(ret);
        });

    vm->bind(imgui, "EndPopup()",
        "only call EndPopup() if BeginPopupXXX() returns true!",
        [](VM* vm, ArgsView args){
            ImGui::EndPopup();
            return vm->None;
        });

    // Popups: open/close functions
    vm->bind(imgui, "OpenPopup(str_id: str, popup_flags: int = 0)",
        "call to mark popup as open (don't call every frame!).",
        [](VM* vm, ArgsView args){
            const char* str_id = CAST(CString, args[0]);
            ImGuiPopupFlags popup_flags = CAST(int, args[1]);
            ImGui::OpenPopup(str_id, popup_flags);
            return vm->None;
        });

    vm->bind(imgui, "OpenPopupOnItemClick(str_id: str = None, popup_flags: int = 1)",
        "helper to open popup when clicked on last item. Default to ImGuiPopupFlags_MouseButtonRight == 1. (note: actually triggers on the mouse _released_ event to be consistent with popup behaviors)",
        [](VM* vm, ArgsView args){
            const char* str_id = CAST_DEFAULT(CString, args[0], NULL);
            ImGuiPopupFlags popup_flags = CAST(int, args[1]);
            ImGui::OpenPopupOnItemClick(str_id, popup_flags);
            return vm->None;
        });

    vm->bind(imgui, "CloseCurrentPopup()",
        "manually close the popup we have begin-ed into.",
        PK_ACTION(ImGui::CloseCurrentPopup()));

    // Popups: open+begin combined functions helpers
    vm->bind(imgui, "BeginPopupContextItem(str_id: str = None, popup_flags: int = 1) -> bool",
        "open+begin popup when clicked on last item. Use str_id==None to associate the popup to previous item. If you want to use that on a non-interactive item such as Text() you need to pass in an explicit ID here. read comments in .cpp!",
        [](VM* vm, ArgsView args){
            const char* str_id = CAST_DEFAULT(CString, args[0], NULL);
            ImGuiPopupFlags popup_flags = CAST(int, args[1]);
            bool ret = ImGui::BeginPopupContextItem(str_id, popup_flags);
            return VAR(ret);
        });

    vm->bind(imgui, "BeginPopupContextWindow(str_id: str = None, popup_flags: int = 1) -> bool",
        "open+begin popup when clicked on current window.",
        [](VM* vm, ArgsView args){
            const char* str_id = CAST_DEFAULT(CString, args[0], NULL);
            ImGuiPopupFlags popup_flags = CAST(int, args[1]);
            bool ret = ImGui::BeginPopupContextWindow(str_id, popup_flags);
            return VAR(ret);
        });

    vm->bind(imgui, "BeginPopupContextVoid(str_id: str = None, popup_flags: int = 1) -> bool",
        "open+begin popup when clicked in void (where there are no windows).",
        [](VM* vm, ArgsView args){
            const char* str_id = CAST_DEFAULT(CString, args[0], NULL);
            ImGuiPopupFlags popup_flags = CAST(int, args[1]);
            bool ret = ImGui::BeginPopupContextVoid(str_id, popup_flags);
            return VAR(ret);
        });

    // Popups: query functions
    vm->bind(imgui, "IsPopupOpen(str_id: str, flags: int = 0) -> bool",
        "return true if the popup is open.",
        [](VM* vm, ArgsView args){
            const char* str_id = CAST(CString, args[0]);
            ImGuiPopupFlags flags = CAST(int, args[1]);
            bool ret = ImGui::IsPopupOpen(str_id, flags);
            return VAR(ret);
        });

    // Tables
    // ... (TODO)

    // Tab Bars, Tabs
    vm->bind(imgui, "BeginTabBar(str_id: str, flags: int = 0) -> bool",
        "create and append into a TabBar",
        [](VM* vm, ArgsView args){
            const char* str_id = CAST(CString, args[0]);
            ImGuiTabBarFlags flags = CAST(int, args[1]);
            bool ret = ImGui::BeginTabBar(str_id, flags);
            return VAR(ret);
        });

    vm->bind(imgui, "EndTabBar()",
        "only call EndTabBar() if BeginTabBar() returns true!",
        PK_ACTION(ImGui::EndTabBar()));

    vm->bind(imgui, "BeginTabItem(label: str, p_open=None, flags: int = 0) -> bool",
        "create a Tab. Returns true if the Tab is selected.",
        [](VM* vm, ArgsView args){
            const char* label = CAST(CString, args[0]);
            bool* p_open = CAST_DEFAULT(bool*, args[1], NULL);
            ImGuiTabItemFlags flags = CAST(int, args[2]);
            bool ret = ImGui::BeginTabItem(label, p_open, flags);
            return VAR(ret);
        });

    vm->bind(imgui, "EndTabItem()",
        "only call EndTabItem() if BeginTabItem() returns true!",
        PK_ACTION(ImGui::EndTabItem()));

    vm->bind(imgui, "TabItemButton(label: str, flags: int = 0) -> bool",
        "create a Tab behaving like a button. return true when clicked. cannot be selected in the tab bar.",
        [](VM* vm, ArgsView args){
            const char* label = CAST(CString, args[0]);
            ImGuiTabItemFlags flags = CAST(int, args[1]);
            bool ret = ImGui::TabItemButton(label, flags);
            return VAR(ret);
        });

    vm->bind(imgui, "SetTabItemClosed(tab_or_docked_window_label: str)",
        "notify TabBar or Docking system of a closed tab/window ahead (useful to reduce visual flicker on reorderable tab bars). For tab-bar: call after BeginTabBar() and before Tab submissions. Otherwise call with a window name.",
        [](VM* vm, ArgsView args){
            const char* tab_or_docked_window_label = CAST(CString, args[0]);
            ImGui::SetTabItemClosed(tab_or_docked_window_label);
            return vm->None;
        });


    // Logging/Capture
    // ... (TODO)

    // Drag and Drop
    // ... (TODO)

    // Disabling [BETA API]
    vm->bind(imgui, "BeginDisabled(disabled: bool = True)",
"- Disable all user interactions and dim items visuals (applying style.DisabledAlpha over current colors)\n"
"- Those can be nested but it cannot be used to enable an already disabled section (a single BeginDisabled(true) in the stack is enough to keep everything disabled)\n"
"- BeginDisabled(false) essentially does nothing useful but is provided to facilitate use of boolean expressions. If you can avoid calling BeginDisabled(False)/EndDisabled() best to avoid it.\n",
        [](VM* vm, ArgsView args){
            bool disabled = CAST(bool, args[0]);
            ImGui::BeginDisabled(disabled);
            return vm->None;
        });

    vm->bind(imgui, "EndDisabled()",
        PK_ACTION(ImGui::EndDisabled()));

    // Clipping
    vm->bind(imgui, "PushClipRect(clip_rect_min: vec2, clip_rect_max: vec2, intersect_with_current_clip_rect: bool)",
        [](VM* vm, ArgsView args){
            ImVec2 clip_rect_min = CAST(ImVec2, args[0]);
            ImVec2 clip_rect_max = CAST(ImVec2, args[1]);
            bool intersect_with_current_clip_rect = CAST(bool, args[2]);
            ImGui::PushClipRect(clip_rect_min, clip_rect_max, intersect_with_current_clip_rect);
            return vm->None;
        });

    vm->bind(imgui, "PopClipRect()",
        PK_ACTION(ImGui::PopClipRect()));

    // Focus, Activation
    vm->bind(imgui, "SetItemDefaultFocus()",
        "make last item the default focused item of a window.",
        PK_ACTION(ImGui::SetItemDefaultFocus()));

    vm->bind(imgui, "SetKeyboardFocusHere(offset: int = 0)",
        "focus keyboard on the next widget. Use positive 'offset' to access sub components of a multiple component widget. Use -1 to access previous widget.",
        [](VM* vm, ArgsView args){
            int offset = CAST(int, args[0]);
            ImGui::SetKeyboardFocusHere(offset);
            return vm->None;
        });
    
    // Item/Widgets Utilities and Query Functions
    // - Most of the functions are referring to the previous Item that has been submitted.
    // - See Demo Window under "Widgets->Querying Status" for an interactive visualization of most of those functions.
    vm->bind(imgui, "IsItemHovered(flags: int = 0) -> bool",
        "is the last item hovered? (and usable, aka not blocked by a popup, etc.). See ImGuiHoveredFlags for more options.",
        [](VM* vm, ArgsView args){
            ImGuiHoveredFlags flags = CAST(int, args[0]);
            bool ret = ImGui::IsItemHovered(flags);
            return VAR(ret);
        });

    vm->bind(imgui, "IsItemActive() -> bool",
        "is the last item active? (e.g. button being held, text field being edited. This will continuously return true while holding mouse button on an item. Items that don't interact will always return false)",
        PK_VAR_LAMBDA(ImGui::IsItemActive()));

    vm->bind(imgui, "IsItemFocused() -> bool",
        "is the last item focused for keyboard/gamepad navigation?",
        PK_VAR_LAMBDA(ImGui::IsItemFocused()));

    vm->bind(imgui, "IsItemClicked(mouse_button: int = 0) -> bool",
        "is the last item hovered and mouse clicked on? (**)  == IsMouseClicked(mouse_button) && IsItemHovered()Important. (**) this is NOT equivalent to the behavior of e.g. Button(). Read comments in function definition.",
        [](VM* vm, ArgsView args){
            ImGuiMouseButton mouse_button = CAST(int, args[0]);
            bool ret = ImGui::IsItemClicked(mouse_button);
            return VAR(ret);
        });

    vm->bind(imgui, "IsItemVisible() -> bool",
        "is the last item visible? (items may be out of sight because of clipping/scrolling)",
        PK_VAR_LAMBDA(ImGui::IsItemVisible()));

    vm->bind(imgui, "IsItemEdited() -> bool",
        "did the last item modify its underlying value this frame? or was pressed? This is generally the same as the \"bool\" return value of many widgets.",
        PK_VAR_LAMBDA(ImGui::IsItemEdited()));

    vm->bind(imgui, "IsItemActivated() -> bool",
        "was the last item just made active (item was previously inactive).",
        PK_VAR_LAMBDA(ImGui::IsItemActivated()));

    vm->bind(imgui, "IsItemDeactivated() -> bool",
        "was the last item just made inactive (item was previously active). Useful for Undo/Redo patterns with widgets that require continuous editing.",
        PK_VAR_LAMBDA(ImGui::IsItemDeactivated()));

    vm->bind(imgui, "IsItemDeactivatedAfterEdit() -> bool",
        "was the last item just made inactive and made a value change when it was active? (e.g. Slider/Drag moved). Useful for Undo/Redo patterns with widgets that require continuous editing. Note that you may get false positives (some widgets such as Combo()/ListBox()/Selectable() will return true even when clicking an already selected item).",
        PK_VAR_LAMBDA(ImGui::IsItemDeactivatedAfterEdit()));

    vm->bind(imgui, "IsItemToggledOpen() -> bool",
        "was the last item open state toggled? set by TreeNode().",
        PK_VAR_LAMBDA(ImGui::IsItemToggledOpen()));

    vm->bind(imgui, "IsAnyItemHovered() -> bool",
        "is any item hovered?",
        PK_VAR_LAMBDA(ImGui::IsAnyItemHovered()));

    vm->bind(imgui, "IsAnyItemActive() -> bool",
        "is any item active?",
        PK_VAR_LAMBDA(ImGui::IsAnyItemActive()));

    vm->bind(imgui, "IsAnyItemFocused() -> bool",
        "is any item focused?",
        PK_VAR_LAMBDA(ImGui::IsAnyItemFocused()));

    vm->bind(imgui, "GetItemRectMin() -> vec2",
        "get upper-left bounding rectangle of the last item (screen space)",
        PK_VAR_LAMBDA(ImGui::GetItemRectMin()));

    vm->bind(imgui, "GetItemRectMax() -> vec2",
        "get lower-right bounding rectangle of the last item (screen space)",
        PK_VAR_LAMBDA(ImGui::GetItemRectMax()));

    vm->bind(imgui, "GetItemRectSize() -> vec2",
        "get size of last item",
        PK_VAR_LAMBDA(ImGui::GetItemRectSize()));

    vm->bind(imgui, "SetItemAllowOverlap()",
        "allow last item to be overlapped by a subsequent item. sometimes useful with invisible buttons, selectables, etc. to catch unused area.",
        PK_ACTION(ImGui::SetItemAllowOverlap()));

    // Viewports
    vm->bind(imgui, "GetMainViewport() -> void_p",
        PK_VAR_LAMBDA(ImGui::GetMainViewport()));

    // Background/Foreground Draw Lists
    vm->bind(imgui, "GetBackgroundDrawList() -> void_p",
        "get background draw list for the current active window.",
        [](VM* vm, ArgsView args){
            ImDrawList* ret = ImGui::GetBackgroundDrawList();
            return VAR(ret);
        });

    vm->bind(imgui, "GetForegroundDrawList() -> void_p",
        "get foreground draw list for the current active window.",
        [](VM* vm, ArgsView args){
            ImDrawList* ret = ImGui::GetForegroundDrawList();
            return VAR(ret);
        });

    // Miscellaneous Utilities
    vm->bind(imgui, "IsRectVisible(size: vec2) -> bool",
        "test if rectangle (of given size, starting from cursor position) is visible / not clipped.",
        [](VM* vm, ArgsView args){
            ImVec2 size = CAST(ImVec2, args[0]);
            bool ret = ImGui::IsRectVisible(size);
            return VAR(ret);
        });

    vm->bind(imgui, "GetTime() -> float",
        "get global imgui time. incremented by io.DeltaTime every frame.",
        [](VM* vm, ArgsView args){
            double ret = ImGui::GetTime();
            return VAR(ret);
        });

    vm->bind(imgui, "GetFrameCount() -> int",
        "get global imgui frame count. incremented by 1 every frame.",
        [](VM* vm, ArgsView args){
            int ret = ImGui::GetFrameCount();
            return VAR(ret);
        });

    vm->bind(imgui, "GetDrawListSharedData() -> void_p",
        "you may use this when creating your own ImDrawList instances.",
        [](VM* vm, ArgsView args){
            ImDrawListSharedData* ret = ImGui::GetDrawListSharedData();
            return VAR(ret);
        });

    vm->bind(imgui, "GetStyleColorName(idx: int) -> str",
        "get a string corresponding to the enum value (for display, saving, etc.).",
        [](VM* vm, ArgsView args){
            ImGuiCol idx = CAST(ImGuiCol, args[0]);
            const char* ret = ImGui::GetStyleColorName(idx);
            return VAR(ret);
        });

    vm->bind(imgui, "SetStateStorage(storage: void_p)",
        "replace current window storage with our own (if you want to manipulate it yourself, typically clear subsection of it)",
        [](VM* vm, ArgsView args){
            ImGuiStorage* storage = CAST(ImGuiStorage*, args[0]);
            ImGui::SetStateStorage(storage);
            return vm->None;
        });

    vm->bind(imgui, "GetStateStorage() -> void_p",
        [](VM* vm, ArgsView args){
            ImGuiStorage* ret = ImGui::GetStateStorage();
            return VAR(ret);
        });

    vm->bind(imgui, "BeginChildFrame(id: int, size: vec2, flags: int = 0) -> bool",
        "helper to create a child window / scrolling region that looks like a normal widget frame",
        [](VM* vm, ArgsView args){
            ImGuiID id = CAST(ImGuiID, args[0]);
            ImVec2 size = CAST(ImVec2, args[1]);
            ImGuiWindowFlags flags = CAST_DEFAULT(ImGuiWindowFlags, args[2], ImGuiWindowFlags(0));
            bool ret = ImGui::BeginChildFrame(id, size, flags);
            return VAR(ret);
        });

    vm->bind(imgui, "EndChildFrame()",
        "always call EndChildFrame() regardless of BeginChildFrame() return values (which indicates a collapsed/clipped window)",
        [](VM* vm, ArgsView args){
            ImGui::EndChildFrame();
            return vm->None;
        });

    // Text Utilities
    vm->bind(imgui, "CalcTextSize(text: str, hide_text_after_double_hash=False, wrap_width=-1.0) -> vec2",
        "calculate text size. text can be multi-line. optionally ignore text after double-space (for e.g. for logging to file, etc.)",
        [](VM* vm, ArgsView args){
            const char* text = CAST(const char*, args[0]);
            bool hide_text_after_double_hash = CAST_DEFAULT(bool, args[1], false);
            float wrap_width = CAST_DEFAULT(float, args[2], -1.0f);
            ImVec2 ret = ImGui::CalcTextSize(text, nullptr, hide_text_after_double_hash, wrap_width);
            return VAR(ret);
        });

    // Color Utilities
    // ... (TODO)

    // Inputs Utilities: Keyboard/Mouse/Gamepad
    vm->bind(imgui, "IsKeyDown(key: int) -> bool",
        "is key being held.",
        [](VM* vm, ArgsView args){
            int key = CAST(int, args[0]);
            bool ret = ImGui::IsKeyDown((ImGuiKey)key);
            return VAR(ret);
        });

    vm->bind(imgui, "IsKeyPressed(key: int, repeat=True) -> bool",
        "was key pressed (went from !Down to Down)? if repeat=true, uses io.KeyRepeatDelay / KeyRepeatRate",
        [](VM* vm, ArgsView args){
            int key = CAST(int, args[0]);
            bool repeat = CAST_DEFAULT(bool, args[1], true);
            bool ret = ImGui::IsKeyPressed((ImGuiKey)key, repeat);
            return VAR(ret);
        });

    vm->bind(imgui, "IsKeyReleased(key: int) -> bool",
        "was key released (went from Down to !Down)?",
        [](VM* vm, ArgsView args){
            int key = CAST(int, args[0]);
            bool ret = ImGui::IsKeyReleased((ImGuiKey)key);
            return VAR(ret);
        });

    vm->bind(imgui, "GetKeyPressedAmount(key: int, repeat_delay: float, rate: float) -> int",
        "uses provided repeat rate/delay. return a count, most often 0 or 1 but might be >1 if RepeatRate is small enough that DeltaTime > RepeatRate",
        [](VM* vm, ArgsView args){
            int key = CAST(int, args[0]);
            float repeat_delay = CAST_F(args[1]);
            float rate = CAST_F(args[2]);
            int ret = ImGui::GetKeyPressedAmount((ImGuiKey)key, repeat_delay, rate);
            return VAR(ret);
        });

    vm->bind(imgui, "GetKeyName(key: int) -> str",
        "[DEBUG] returns English name of the key. Those names a provided for debugging purpose and are not meant to be saved persistently not compared.",
        [](VM* vm, ArgsView args){
            int key = CAST(int, args[0]);
            const char* ret = ImGui::GetKeyName((ImGuiKey)key);
            return VAR(ret);
        });

    vm->bind(imgui, "SetNextFrameWantCaptureKeyboard(want_capture_keyboard: bool)",
        "Override io.WantCaptureKeyboard flag next frame (said flag is left for your application to handle, typically when true it instructs your app to ignore inputs). e.g. force capture keyboard when your widget is being hovered. This is equivalent to setting \"io.WantCaptureKeyboard = want_capture_keyboard\"; after the next NewFrame() call.",
        [](VM* vm, ArgsView args){
            bool want_capture_keyboard = CAST(bool, args[0]);
            ImGui::SetNextFrameWantCaptureKeyboard(want_capture_keyboard);
            return vm->None;
        });

    // Inputs Utilities: Mouse specific
    vm->bind(imgui, "IsMouseDown(button: int) -> bool",
        "is mouse button held?",
        [](VM* vm, ArgsView args){
            int button = CAST(int, args[0]);
            bool ret = ImGui::IsMouseDown(button);
            return VAR(ret);
        });

    vm->bind(imgui, "IsMouseClicked(button: int, repeat=False) -> bool",
        "did mouse button clicked? (went from !Down to Down). Same as GetMouseClickedCount() == 1.",
        [](VM* vm, ArgsView args){
            int button = CAST(int, args[0]);
            bool repeat = CAST(bool, args[1]);
            bool ret = ImGui::IsMouseClicked(button, repeat);
            return VAR(ret);
        });

    vm->bind(imgui, "IsMouseReleased(button: int) -> bool",
        "did mouse button released? (went from Down to !Down)",
        [](VM* vm, ArgsView args){
            int button = CAST(int, args[0]);
            bool ret = ImGui::IsMouseReleased(button);
            return VAR(ret);
        });

    vm->bind(imgui, "IsMouseDoubleClicked(button: int) -> bool",
        "did mouse button double-clicked? Same as GetMouseClickedCount() == 2. (note that a double-click will also report IsMouseClicked() == true)",
        [](VM* vm, ArgsView args){
            int button = CAST(int, args[0]);
            bool ret = ImGui::IsMouseDoubleClicked(button);
            return VAR(ret);
        });

    vm->bind(imgui, "GetMouseClickedCount(button: int) -> int",
        "return the number of successive mouse-clicks at the time where a click happen (otherwise 0).",
        [](VM* vm, ArgsView args){
            int button = CAST(int, args[0]);
            int ret = ImGui::GetMouseClickedCount(button);
            return VAR(ret);
        });

    vm->bind(imgui, "IsMouseHoveringRect(r_min: vec2, r_max: vec2, clip=True) -> bool",
        "is mouse hovering given bounding rect (in screen space). clipped by current clipping settings, but disregarding of other consideration of focus/window ordering/popup-block.",
        [](VM* vm, ArgsView args){
            ImVec2 r_min = CAST(ImVec2, args[0]);
            ImVec2 r_max = CAST(ImVec2, args[1]);
            bool clip = CAST(bool, args[2]);
            bool ret = ImGui::IsMouseHoveringRect(r_min, r_max, clip);
            return VAR(ret);
        });

    vm->bind(imgui, "IsMousePosValid(mouse_pos: vec2 = None) -> bool",
        "by convention we use (-FLT_MAX,-FLT_MAX) to denote that there is no mouse available",
        [](VM* vm, ArgsView args){
            ImVec2 mouse_pos = CAST(ImVec2, args[0]);
            bool ret = ImGui::IsMousePosValid(&mouse_pos);
            return VAR(ret);
        });

    vm->bind(imgui, "IsAnyMouseDown() -> bool",
        "[WILL OBSOLETE] is any mouse button held? This was designed for backends, but prefer having backend maintain a mask of held mouse buttons, because upcoming input queue system will make this invalid.",
        [](VM* vm, ArgsView args){
            bool ret = ImGui::IsAnyMouseDown();
            return VAR(ret);
        });

    vm->bind(imgui, "GetMousePos() -> vec2",
        "shortcut to ImGui::GetIO().MousePos provided by user, to be consistent with other calls",
        [](VM* vm, ArgsView args){
            ImVec2 ret = ImGui::GetMousePos();
            return VAR(ret);
        });

    vm->bind(imgui, "GetMousePosOnOpeningCurrentPopup() -> vec2",
        "retrieve mouse position at the time of opening popup we have BeginPopup() into (helper to avoid user backing that value themselves)",
        [](VM* vm, ArgsView args){
            ImVec2 ret = ImGui::GetMousePosOnOpeningCurrentPopup();
            return VAR(ret);
        });

    vm->bind(imgui, "IsMouseDragging(button: int, lock_threshold=-1.0) -> bool",
        "is mouse dragging? (if lock_threshold < -1.0f, uses io.MouseDraggingThreshold)",
        [](VM* vm, ArgsView args){
            int button = CAST(int, args[0]);
            float lock_threshold = CAST_F(args[1]);
            bool ret = ImGui::IsMouseDragging(button, lock_threshold);
            return VAR(ret);
        });

    vm->bind(imgui, "GetMouseDragDelta(button: int=0, lock_threshold=-1.0) -> vec2",
        "return the delta from the initial clicking position while the mouse button is pressed or was just released. This is locked and return 0.0f until the mouse moves past a distance threshold at least once (if lock_threshold < -1.0f, uses io.MouseDraggingThreshold)",
        [](VM* vm, ArgsView args){
            int button = CAST(int, args[0]);
            float lock_threshold = CAST_F(args[1]);
            ImVec2 ret = ImGui::GetMouseDragDelta(button, lock_threshold);
            return VAR(ret);
        });

    vm->bind(imgui, "ResetMouseDragDelta(button: int=0) -> None",
        "reset the dragging state when the mouse has been dragging (0=left, 1=right, 2=middle)",
        [](VM* vm, ArgsView args){
            int button = CAST(int, args[0]);
            ImGui::ResetMouseDragDelta(button);
            return vm->None;
        });

    vm->bind(imgui, "GetMouseCursor() -> int",
        "get desired cursor type, reset in end frame. valid before Render(). if you use software rendering by setting io.MouseDrawCursor ImGui will render those for you",
        [](VM* vm, ArgsView args){
            ImGuiMouseCursor ret = ImGui::GetMouseCursor();
            return VAR(ret);
        });

    vm->bind(imgui, "SetMouseCursor(type: int) -> None",
        "set desired cursor type",
        [](VM* vm, ArgsView args){
            ImGuiMouseCursor type = CAST(ImGuiMouseCursor, args[0]);
            ImGui::SetMouseCursor(type);
            return vm->None;
        });

    vm->bind(imgui, "SetNextFrameWantCaptureMouse(want_capture_mouse: bool)",
        "set next window ala Begin() to be focused / hovered for input handling without navigation",
        [](VM* vm, ArgsView args){
            bool want_capture_mouse = CAST(bool, args[0]);
            ImGui::SetNextFrameWantCaptureMouse(want_capture_mouse);
            return vm->None;
        });
        
    // Clipboard Utilities
    vm->bind(imgui, "GetClipboardText() -> str",
        [](VM* vm, ArgsView args){
            const char* ret = ImGui::GetClipboardText();
            return VAR(ret);
        });

    vm->bind(imgui, "SetClipboardText(text: str) -> None",
        [](VM* vm, ArgsView args){
            const char* text = CAST(CString, args[0]);
            ImGui::SetClipboardText(text);
            return vm->None;
        });

    // Debug Utilities
    vm->bind(imgui, "DebugTextEncoding(text: str) -> None",
        [](VM* vm, ArgsView args){
            const char* text = CAST(CString, args[0]);
            ImGui::DebugTextEncoding(text);
            return vm->None;
        });
}

}