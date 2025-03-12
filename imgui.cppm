module;

#include <cstdint>
#include "imgui.h"
#include "imgui_internal.h"

export module ImGui;

export namespace ImGui {

	using ImGui::CreateContext;
	using ImGui::DestroyContext;
	using ImGui::GetCurrentContext;
	using ImGui::SetCurrentContext;
	using ImGui::GetIO;
	using ImGui::GetPlatformIO;
	using ImGui::GetStyle;
	using ImGui::NewFrame;
	using ImGui::EndFrame;
	using ImGui::Render;
	using ImGui::GetDrawData;

	using ImGui::ShowDemoWindow;
	using ImGui::ShowMetricsWindow;
	using ImGui::ShowDebugLogWindow;
	using ImGui::ShowIDStackToolWindow;
	using ImGui::ShowAboutWindow;
	using ImGui::ShowStyleEditor;
	using ImGui::ShowStyleSelector;
	using ImGui::ShowFontSelector;
	using ImGui::ShowUserGuide;
	using ImGui::GetVersion;

	using ImGui::StyleColorsDark;
	using ImGui::StyleColorsLight;
	using ImGui::StyleColorsClassic;

	using ImGui::Begin;
	using ImGui::End;

	using ImGui::BeginChild;
	using ImGui::EndChild;

	using ImGui::IsWindowAppearing;
	using ImGui::IsWindowCollapsed;
	using ImGui::IsWindowFocused;
	using ImGui::IsWindowHovered;
	using ImGui::GetWindowDrawList;
	using ImGui::GetWindowDpiScale;
	using ImGui::GetWindowPos;
	using ImGui::GetWindowSize;
	using ImGui::GetWindowWidth;
	using ImGui::GetWindowHeight;
	using ImGui::GetWindowViewport;

	using ImGui::SetNextWindowPos;
	using ImGui::SetNextWindowSize;
	using ImGui::SetNextWindowSizeConstraints;
	using ImGui::SetNextWindowContentSize;
	using ImGui::SetNextWindowCollapsed;
	using ImGui::SetNextWindowFocus;
	using ImGui::SetNextWindowScroll;
	using ImGui::SetNextWindowBgAlpha;
	using ImGui::SetNextWindowViewport;
	using ImGui::SetWindowPos;
	using ImGui::SetWindowSize;
	using ImGui::SetWindowCollapsed;
	using ImGui::SetWindowFocus;
	using ImGui::SetWindowFontScale;

	using ImGui::GetScrollX;
	using ImGui::GetScrollY;
	using ImGui::SetScrollX;
	using ImGui::SetScrollY;
	using ImGui::GetScrollMaxX;
	using ImGui::GetScrollMaxY;
	using ImGui::SetScrollHereX;
	using ImGui::SetScrollHereY;
	using ImGui::SetScrollFromPosX;
	using ImGui::SetScrollFromPosY;
	
	using ImGui::PushFont;
	using ImGui::PopFont;
	using ImGui::PushStyleColor;
	using ImGui::PopStyleColor;
	using ImGui::PushStyleVar;
	using ImGui::PushStyleVarX;
	using ImGui::PushStyleVarY;
	using ImGui::PopStyleVar;
	using ImGui::PushItemFlag;
	using ImGui::PopItemFlag;

	using ImGui::PushItemWidth;
	using ImGui::PopItemWidth;
	using ImGui::SetNextItemWidth;
	using ImGui::CalcItemWidth;
	using ImGui::PushTextWrapPos;
	using ImGui::PopTextWrapPos;

	using ImGui::GetFont;
	using ImGui::GetFontSize;
	using ImGui::GetFontTexUvWhitePixel;
	using ImGui::GetColorU32;
	using ImGui::GetStyleColorVec4;

	using ImGui::GetCursorScreenPos;
	using ImGui::SetCursorScreenPos;
	using ImGui::GetContentRegionAvail;
	using ImGui::GetCursorPos;
	using ImGui::GetCursorPosX;
	using ImGui::GetCursorPosY;
	using ImGui::SetCursorPos;
	using ImGui::SetCursorPosX;
	using ImGui::SetCursorPosY;
	using ImGui::GetCursorStartPos;
	
	using ImGui::Separator;
	using ImGui::SameLine;
	using ImGui::NewLine;
	using ImGui::Spacing;
	using ImGui::Dummy;
	using ImGui::Indent;
	using ImGui::Unindent;
	using ImGui::BeginGroup;
	using ImGui::EndGroup;
	using ImGui::AlignTextToFramePadding;
	using ImGui::GetTextLineHeight;
	using ImGui::GetTextLineHeightWithSpacing;
	using ImGui::GetFrameHeight;
	using ImGui::GetFrameHeightWithSpacing;

	using ImGui::PushID;
	using ImGui::PopID;
	using ImGui::GetID;
	
	using ImGui::TextUnformatted;
	using ImGui::Text;
	using ImGui::TextV;
	using ImGui::TextColored;
	using ImGui::TextColoredV;
	using ImGui::TextDisabled;
	using ImGui::TextDisabledV;
	using ImGui::TextWrapped;
	using ImGui::TextWrappedV;
	using ImGui::LabelText;
	using ImGui::LabelTextV;
	using ImGui::BulletText;
	using ImGui::BulletTextV;
	using ImGui::SeparatorText;
	
	using ImGui::Button;
	using ImGui::SmallButton;
	using ImGui::InvisibleButton;
	using ImGui::ArrowButton;
	using ImGui::Checkbox;
	using ImGui::CheckboxFlags;
	using ImGui::RadioButton;
	using ImGui::ProgressBar;
	using ImGui::Bullet;
	using ImGui::TextLink;
	using ImGui::TextLinkOpenURL;
	
	using ImGui::Image;
	using ImGui::ImageButton;
	
	using ImGui::BeginCombo;
	using ImGui::EndCombo;
	using ImGui::Combo;

	using ImGui::DragFloat;
	using ImGui::DragFloat2;
	using ImGui::DragFloat3;
	using ImGui::DragFloat4;
	using ImGui::DragFloatRange2;
	using ImGui::DragInt;
	using ImGui::DragInt2;
	using ImGui::DragInt3;
	using ImGui::DragInt4;
	using ImGui::DragIntRange2;
	using ImGui::DragScalar;
	using ImGui::DragScalarN;
	
	using ImGui::SliderFloat;
	using ImGui::SliderFloat2;
	using ImGui::SliderFloat3;
	using ImGui::SliderFloat4;
	using ImGui::SliderAngle;
	using ImGui::SliderInt;
	using ImGui::SliderInt2;
	using ImGui::SliderInt3;
	using ImGui::SliderInt4;
	using ImGui::SliderScalar;
	using ImGui::SliderScalarN;
	using ImGui::VSliderFloat;
	using ImGui::VSliderInt;
	using ImGui::VSliderScalar;
	
	using ImGui::InputText;
	using ImGui::InputTextMultiline;
	using ImGui::InputTextWithHint;
	using ImGui::InputFloat;
	using ImGui::InputFloat2;
	using ImGui::InputFloat3;
	using ImGui::InputFloat4;
	using ImGui::InputInt;
	using ImGui::InputInt2;
	using ImGui::InputInt3;
	using ImGui::InputInt4;
	using ImGui::InputDouble;
	using ImGui::InputScalar;
	using ImGui::InputScalarN;
	
	using ImGui::ColorEdit3;
	using ImGui::ColorEdit4;
	using ImGui::ColorPicker3;
	using ImGui::ColorPicker4;
	using ImGui::ColorButton;
	using ImGui::SetColorEditOptions;
	
	using ImGui::TreeNode;
	using ImGui::TreeNodeV;
	using ImGui::TreeNodeEx;
	using ImGui::TreeNodeExV;
	using ImGui::TreePush;
	using ImGui::TreePop;
	using ImGui::GetTreeNodeToLabelSpacing;
	using ImGui::CollapsingHeader;
	using ImGui::SetNextItemOpen;
	using ImGui::SetNextItemStorageID;
	
	using ImGui::Selectable;

	using ImGui::BeginMultiSelect;
	using ImGui::EndMultiSelect;
	using ImGui::SetNextItemSelectionUserData;
	using ImGui::IsItemToggledSelection;

	using ImGui::BeginListBox;
	using ImGui::EndListBox;
	using ImGui::ListBox;
	
	using ImGui::PlotLines;
	using ImGui::PlotHistogram;
	
	using ImGui::Value;
	
	using ImGui::BeginMenuBar;
	using ImGui::EndMenuBar;
	using ImGui::BeginMainMenuBar;
	using ImGui::EndMainMenuBar;
	using ImGui::BeginMenu;
	using ImGui::EndMenu;
	using ImGui::MenuItem;
	
	using ImGui::BeginTooltip;       
	using ImGui::EndTooltip;
	using ImGui::SetTooltip;
	using ImGui::SetTooltipV;

	using ImGui::BeginItemTooltip;
	using ImGui::SetItemTooltip;
	using ImGui::SetItemTooltipV;
	
	using ImGui::BeginPopup;
	using ImGui::BeginPopupModal;
	using ImGui::EndPopup;
	
	using ImGui::OpenPopup;
	using ImGui::OpenPopupOnItemClick;
	using ImGui::CloseCurrentPopup;
	
	using ImGui::BeginPopupContextItem;
	using ImGui::BeginPopupContextWindow;
	using ImGui::BeginPopupContextVoid;
	
	using ImGui::IsPopupOpen;
	
	using ImGui::BeginTable;
	using ImGui::EndTable;
	using ImGui::TableNextRow;
	using ImGui::TableNextColumn;
	using ImGui::TableSetColumnIndex;
	
	using ImGui::TableSetupColumn;
	using ImGui::TableSetupScrollFreeze;
	using ImGui::TableHeader;
	using ImGui::TableHeadersRow;      
	using ImGui::TableAngledHeadersRow;

	using ImGui::TableGetSortSpecs;
	using ImGui::TableGetColumnCount;  
	using ImGui::TableGetColumnIndex;  
	using ImGui::TableGetRowIndex;
	using ImGui::TableGetColumnName;
	using ImGui::TableGetColumnFlags;
	using ImGui::TableSetColumnEnabled;
	using ImGui::TableGetHoveredColumn;
	using ImGui::TableSetBgColor;

	using ImGui::Columns;
	using ImGui::NextColumn;
	using ImGui::GetColumnIndex;
	using ImGui::GetColumnWidth;
	using ImGui::SetColumnWidth;
	using ImGui::GetColumnOffset;
	using ImGui::SetColumnOffset;
	using ImGui::GetColumnsCount;

	using ImGui::BeginTabBar;
	using ImGui::EndTabBar;
	using ImGui::BeginTabItem;
	using ImGui::EndTabItem;
	using ImGui::TabItemButton;
	using ImGui::SetTabItemClosed;

	using ImGui::DockSpace;
	using ImGui::DockSpaceOverViewport;
	using ImGui::SetNextWindowDockID;
	using ImGui::SetNextWindowClass;
	using ImGui::GetWindowDockID;
	using ImGui::IsWindowDocked;

	using ImGui::LogToTTY;
	using ImGui::LogToFile;
	using ImGui::LogToClipboard;
	using ImGui::LogFinish;
	using ImGui::LogButtons;
	using ImGui::LogText;
	using ImGui::LogTextV;

	using ImGui::BeginDragDropSource;
	using ImGui::SetDragDropPayload;
	using ImGui::EndDragDropSource;
	using ImGui::BeginDragDropTarget;
	using ImGui::AcceptDragDropPayload;
	using ImGui::EndDragDropTarget;
	using ImGui::GetDragDropPayload;

	using ImGui::BeginDisabled;
	using ImGui::EndDisabled;

	using ImGui::PushClipRect;
	using ImGui::PopClipRect;
	
	using ImGui::SetItemDefaultFocus;
	using ImGui::SetKeyboardFocusHere;
	
	using ImGui::SetNavCursorVisible;
	
	using ImGui::SetNextItemAllowOverlap;

	using ImGui::IsItemHovered;
	using ImGui::IsItemActive;
	using ImGui::IsItemFocused;
	using ImGui::IsItemClicked;
	using ImGui::IsItemVisible;
	using ImGui::IsItemEdited;
	using ImGui::IsItemActivated;
	using ImGui::IsItemDeactivated;
	using ImGui::IsItemDeactivatedAfterEdit;
	using ImGui::IsItemToggledOpen;
	using ImGui::IsAnyItemHovered;
	using ImGui::IsAnyItemActive;
	using ImGui::IsAnyItemFocused;
	using ImGui::GetItemID;
	using ImGui::GetItemRectMin;
	using ImGui::GetItemRectMax;
	using ImGui::GetItemRectSize;

	using ImGui::GetMainViewport;

	using ImGui::GetBackgroundDrawList;
	using ImGui::GetForegroundDrawList;
	
	using ImGui::IsRectVisible;
	using ImGui::GetTime;
	using ImGui::GetFrameCount;
	using ImGui::GetDrawListSharedData;
	using ImGui::GetStyleColorName;
	using ImGui::SetStateStorage;
	using ImGui::GetStateStorage;
	
	using ImGui::CalcTextSize;
	
	using ImGui::ColorConvertU32ToFloat4;
	using ImGui::ColorConvertFloat4ToU32;
	using ImGui::ColorConvertRGBtoHSV;
	using ImGui::ColorConvertHSVtoRGB;
	
	using ImGui::IsKeyDown;
	using ImGui::IsKeyPressed;
	using ImGui::IsKeyReleased;
	using ImGui::IsKeyChordPressed;
	using ImGui::GetKeyPressedAmount;
	using ImGui::GetKeyName;
	using ImGui::SetNextFrameWantCaptureKeyboard;

	using ImGui::Shortcut;
	using ImGui::SetNextItemShortcut;
	
	using ImGui::SetItemKeyOwner;

	using ImGui::IsMouseDown;
	using ImGui::IsMouseClicked;
	using ImGui::IsMouseReleased;
	using ImGui::IsMouseDoubleClicked;
	using ImGui::GetMouseClickedCount;
	using ImGui::IsMouseHoveringRect;
	using ImGui::IsMousePosValid;
	using ImGui::IsAnyMouseDown;
	using ImGui::GetMousePos;
	using ImGui::GetMousePosOnOpeningCurrentPopup;
	using ImGui::IsMouseDragging;
	using ImGui::GetMouseDragDelta;
	using ImGui::ResetMouseDragDelta;
	using ImGui::GetMouseCursor;
	using ImGui::SetMouseCursor;
	using ImGui::SetNextFrameWantCaptureMouse;

	using ImGui::GetClipboardText;
	using ImGui::SetClipboardText;

	using ImGui::LoadIniSettingsFromDisk;
	using ImGui::LoadIniSettingsFromMemory;
	using ImGui::SaveIniSettingsToDisk;
	using ImGui::SaveIniSettingsToMemory;

	using ImGui::DebugTextEncoding;
	using ImGui::DebugFlashStyleColor;
	using ImGui::DebugStartItemPicker;
	using ImGui::DebugCheckVersionAndDataLayout;
	
#ifndef IMGUI_DISABLE_DEBUG_TOOLS
	using ImGui::DebugLog;
	using ImGui::DebugLogV;
#endif

	using ImGui::SetAllocatorFunctions;
	using ImGui::GetAllocatorFunctions;
	using ImGui::MemAlloc;
	using ImGui::MemFree;

	using ImGui::UpdatePlatformWindows;
	using ImGui::RenderPlatformWindowsDefault;
	using ImGui::DestroyPlatformWindows;
	using ImGui::FindViewportByID;
	using ImGui::FindViewportByPlatformHandle;
}

// imgui_internal.h
export {

    using ::ImGuiContext;
}

// extra!
export {

    inline constexpr uint32_t ImColor32(int R, int G, int B, int A) noexcept
    {
        return (static_cast<ImU32>(A) << IM_COL32_A_SHIFT) |
            (static_cast<ImU32>(B) << IM_COL32_B_SHIFT) |
            (static_cast<ImU32>(G) << IM_COL32_G_SHIFT) |
            (static_cast<ImU32>(R) << IM_COL32_R_SHIFT);
    }
}

export {

	using ::ImGuiID;
	using ::ImS8;
	using ::ImU8;
	using ::ImS16;
	using ::ImU16;
	using ::ImS32;
	using ::ImU32;
	using ::ImS64;
	using ::ImU64;

	using ::ImDrawChannel;
	using ::ImDrawCmd;
	using ::ImDrawData;
	using ::ImDrawList;
	using ::ImDrawListSharedData;
	using ::ImDrawListSplitter;
	using ::ImDrawVert;
	using ::ImFont;
	using ::ImFontAtlas;
	using ::ImFontBuilderIO;
	using ::ImFontConfig;
	using ::ImFontGlyph;
	using ::ImFontGlyphRangesBuilder;
	using ::ImColor;
	using ::ImGuiContext;
	using ::ImGuiIO;
	using ::ImGuiInputTextCallbackData;
	using ::ImGuiKeyData;
	using ::ImGuiListClipper;
	using ::ImGuiMultiSelectIO;
	using ::ImGuiOnceUponAFrame;
	using ::ImGuiPayload;
	using ::ImGuiPlatformIO;
	using ::ImGuiPlatformImeData;
	using ::ImGuiPlatformMonitor;
	using ::ImGuiSelectionBasicStorage;
	using ::ImGuiSelectionExternalStorage;
	using ::ImGuiSelectionRequest;
	using ::ImGuiSizeCallbackData;
	using ::ImGuiStorage;
	using ::ImGuiStoragePair;
	using ::ImGuiStyle;
	using ::ImGuiTableSortSpecs;
	using ::ImGuiTableColumnSortSpecs;
	using ::ImGuiTextBuffer;
	using ::ImGuiTextFilter;
	using ::ImGuiViewport;
	using ::ImGuiWindowClass;

	using ::ImGuiDir;
	using ::ImGuiKey;
	using ::ImGuiMouseSource;
	using ::ImGuiSortDirection;

	using ::ImGuiCol;
	using ::ImGuiCond;
	using ::ImGuiDataType;
	using ::ImGuiMouseButton;
	using ::ImGuiMouseCursor;
	using ::ImGuiStyleVar;
	using ::ImGuiTableBgTarget;

	using ::ImDrawFlags;
	using ::ImDrawListFlags;
	using ::ImFontAtlasFlags;
	using ::ImGuiBackendFlags;
	using ::ImGuiButtonFlags;
	using ::ImGuiChildFlags;
	using ::ImGuiColorEditFlags;
	using ::ImGuiConfigFlags;
	using ::ImGuiComboFlags;
	using ::ImGuiDockNodeFlags;
	using ::ImGuiDragDropFlags;
	using ::ImGuiFocusedFlags;
	using ::ImGuiHoveredFlags;
	using ::ImGuiInputFlags;
	using ::ImGuiInputTextFlags;
	using ::ImGuiItemFlags;
	using ::ImGuiKeyChord;
	using ::ImGuiPopupFlags;
	using ::ImGuiMultiSelectFlags;
	using ::ImGuiSelectableFlags;
	using ::ImGuiSliderFlags;
	using ::ImGuiTabBarFlags;
	using ::ImGuiTabItemFlags;
	using ::ImGuiTableFlags;
	using ::ImGuiTableColumnFlags;
	using ::ImGuiTableRowFlags;
	using ::ImGuiTreeNodeFlags;
	using ::ImGuiViewportFlags;
	using ::ImGuiWindowFlags;

	using ::ImDrawIdx;

	using ::ImWchar32;
	using ::ImWchar16;

#ifdef IMGUI_USE_WCHAR32
	using ::ImWchar;
#else
	using ::ImWchar;
#endif

	using ::ImGuiSelectionUserData;
	using ::ImVec2;
	using ::ImVec4;

	using ::ImGuiWindowFlags_;
	using ::ImGuiChildFlags_;
	using ::ImGuiItemFlags_;
	using ::ImGuiInputTextFlags_;
	using ::ImGuiTreeNodeFlags_;
	using ::ImGuiPopupFlags_;
	using ::ImGuiSelectableFlags_;
	using ::ImGuiComboFlags_;
	using ::ImGuiTabBarFlags_;
	using ::ImGuiTabItemFlags_;
	using ::ImGuiFocusedFlags_;
	using ::ImGuiHoveredFlags_;
	using ::ImGuiDockNodeFlags_;
	using ::ImGuiDragDropFlags_;
	using ::ImGuiDataType_;
	using ::ImGuiDir;
	using ::ImGuiSortDirection;
	using ::ImGuiKey;
	using ::ImGuiInputFlags_;
	using ::ImGuiConfigFlags_;
	using ::ImGuiBackendFlags_;
	using ::ImGuiCol_;
	using ::ImGuiStyleVar_;
	using ::ImGuiButtonFlags_;
	using ::ImGuiColorEditFlags_;
	using ::ImGuiSliderFlags_;
	using ::ImGuiMouseButton_;
	using ::ImGuiMouseCursor_;
	using ::ImGuiMouseSource;
	using ::ImGuiCond_;
	using ::ImGuiTableFlags_;
	using ::ImGuiTableColumnFlags_;
	using ::ImGuiTableRowFlags_;
	using ::ImGuiTableBgTarget_;
	using ::ImGuiTableSortSpecs;
	using ::ImGuiTableColumnSortSpecs;

	using ::ImVector;
	using ::ImGuiStyle;
	using ::ImGuiKeyData;
	using ::ImGuiIO;
	using ::ImGuiInputTextCallbackData;
	using ::ImGuiSizeCallbackData;
	using ::ImGuiWindowClass;
	using ::ImGuiPayload;
	using ::ImGuiOnceUponAFrame;
	using ::ImGuiTextFilter;
	using ::ImGuiTextBuffer;
	using ::ImGuiStoragePair;
	using ::ImGuiStorage;
	using ::ImGuiListClipper;

	// Operators
	using ::operator+;
	using ::operator-;
	using ::operator*;
	using ::operator/;
	using ::operator==;
	using ::operator!=;
	using ::operator*=;
	using ::operator-=;
	using ::operator/=;

	using ::ImColor;
	using ::ImGuiMultiSelectFlags_;
	using ::ImGuiMultiSelectIO;
	using ::ImGuiSelectionRequestType;
	using ::ImGuiSelectionRequest;
	using ::ImGuiSelectionBasicStorage;
	using ::ImGuiSelectionExternalStorage;
	using ::ImDrawCallback;
	using ::ImDrawCmd;
	using ::ImDrawVert;
	using ::ImDrawCmdHeader;
	using ::ImDrawChannel;
	using ::ImDrawListSplitter;
	using ::ImDrawFlags_;
	using ::ImDrawListFlags_;
	using ::ImDrawList;
	using ::ImDrawData;
	using ::ImFontConfig;
	using ::ImFontGlyph;
	using ::ImFontGlyphRangesBuilder;
	using ::ImFontAtlasCustomRect;
	using ::ImFontAtlasFlags_;
	using ::ImFontAtlas;
	using ::ImFont;
	using ::ImGuiViewportFlags_;
	using ::ImGuiViewport;

	using ::ImGuiPlatformIO;
	using ::ImGuiPlatformMonitor;
	using ::ImGuiPlatformImeData;
	using ::ImGuiPlatformMonitor;
}
