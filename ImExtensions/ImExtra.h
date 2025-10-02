#include "imgui.h"
#include <string>

typedef int ImAutoMenuItemFlags;     // -> enum ImAutoMenuItemFlags_
enum ImAutoMenuItemFlags_
{
    ImAutoMenuItemFlags_None,		  // you have to call BeginMainMenuBar/EndMainMenuBar | BeginMenuBar/EndMenuBar
    ImAutoMenuItemFlags_MainMenuBar,
    ImAutoMenuItemFlags_WindowMenuBar
};

inline constexpr uint32_t ImColorU32(int R, int G, int B, int A) noexcept
{
    return (static_cast<ImU32>(A) << IM_COL32_A_SHIFT) |
        (static_cast<ImU32>(B) << IM_COL32_B_SHIFT) |
        (static_cast<ImU32>(G) << IM_COL32_G_SHIFT) |
        (static_cast<ImU32>(R) << IM_COL32_R_SHIFT);
}

namespace ImGui {

    IMGUI_API bool TextButton(const char* label, const ImVec2& size_arg = ImVec2(0, 0));

    IMGUI_API bool InputText(const char* label, std::string* str, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = nullptr, void* user_data = nullptr);
    IMGUI_API bool InputTextMultiline(const char* label, std::string* str, const ImVec2& size = ImVec2(0, 0), ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = nullptr, void* user_data = nullptr);
    IMGUI_API bool InputTextWithHint(const char* label, const char* hint, std::string* str, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = nullptr, void* user_data = nullptr);

    IMGUI_API bool SelectableButton(const char* label, const ImVec2& size, bool selected = false);

    IMGUI_API void ToolTip(const char* fmt, ...);

    IMGUI_API void ShiftCursorX(float offset);
    IMGUI_API void ShiftCursorY(float offset);
    IMGUI_API void ShiftCursor(ImVec2 offset);

    IMGUI_API bool AutoMenuItem(const char* path, const char* shortcut = NULL, bool selected = false, bool enabled = true, ImAutoMenuItemFlags flags = ImAutoMenuItemFlags_MainMenuBar);

    IMGUI_API void PushStyleCompact();
    IMGUI_API void PopStyleCompact();

    template<uint32_t N>
    IMGUI_API bool Combo(const char* label, const std::array<std::string_view, N>& arr, std::string_view current, void* selectedIndex)
    {
        bool res = false;
        if (ImGui::BeginCombo(label, current.data()))
        {
            for (int i = 0; i < arr.size(); i++)
            {
                bool isSelected = current == arr[i];
                if (ImGui::Selectable(arr[i].data(), isSelected))
                {
                    *(int*)selectedIndex = i;
                    res = true;
                }

                if (isSelected)
                    ImGui::SetItemDefaultFocus();
            }

            ImGui::EndCombo();
        }
        return res;
    }

    template<uint32_t N>
    IMGUI_API bool ComboBox(const char* label, const std::array<std::string_view, N>& arr, std::string_view current, void* selectedIndex, ImVec2 size = { 70.0f, 16.0f})
    {
        bool res = false;

        auto& style = ImGui::GetStyle();
        float dpiScale = ImGui::GetWindowDpiScale();
        float scale = ImGui::GetIO().FontGlobalScale * dpiScale;

        size.x = size.x == 0.0f ? 70.0f : size.x;
        size.y = size.y == 0.0f ? 16.0f : size.y;

        ImVec2 buttonSize(
            size.x * scale + style.FramePadding.x * 2.0f,
            size.y * scale + style.FramePadding.y * 2.0f
        );

        float avl = ImGui::GetContentRegionAvail().x;
        int countInRow = (buttonSize.x > 0.0f) ? (int)(avl / buttonSize.x) : 1;
        if (countInRow < 1) countInRow = 1;

        ImGui::BeginGroup();

        if (label && strlen(label) >= 2 && label[0] != '#' && label[1] != '#')
        {
            ImGui::TextUnformatted(label);
            //ImGui::SameLine();
        }

        for (int i = 0; i < (int)(arr.size()); i++)
        {
            if (i % countInRow == 0)
            {
                float offset = (ImGui::GetContentRegionAvail().x - (buttonSize.x + 1.0f) * countInRow) * 0.5f;
                if (offset > 0.0f)
                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offset);
            }
            else
            {
                ImGui::SameLine(0.0f, 1.0f);
            }

            bool isSelected = (current == arr[i]);

            if (ImGui::SelectableButton(arr[i].data(), buttonSize, isSelected))
            {
                *(int*)selectedIndex = i;
                res = true;
            }

            if (isSelected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndGroup();

        return res;
    }

    struct ScopedButtonColor
    {
        ScopedButtonColor(const ScopedButtonColor&) = delete;
        ScopedButtonColor operator=(const ScopedButtonColor&) = delete;
        ScopedButtonColor(const ImVec4& baseColor)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, { baseColor.x, baseColor.y, baseColor.z, 0.8f });
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, { baseColor.x, baseColor.y, baseColor.z, 0.9f });
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { baseColor.x, baseColor.y, baseColor.z, 1.0f });
        }
        ~ScopedButtonColor() { ImGui::PopStyleColor(3); }
    };

    struct ScopedColor
    {
        ScopedColor(const ScopedColor&) = delete;
        ScopedColor operator=(const ScopedColor&) = delete;
        template<typename T>
        ScopedColor(ImGuiCol ColorId, T Color) { ImGui::PushStyleColor(ColorId, Color); }
        ~ScopedColor() { ImGui::PopStyleColor(); }
    };

    struct ScopedStyle
    {
        ScopedStyle(const ScopedStyle&) = delete;
        ScopedStyle operator=(const ScopedStyle&) = delete;
        template<typename T>
        ScopedStyle(ImGuiStyleVar styleVar, T value) { ImGui::PushStyleVar(styleVar, value); }
        ~ScopedStyle() { ImGui::PopStyleVar(); }
    };

    struct ScopedStyleCompact
    {
        ScopedStyleCompact(const ScopedStyleCompact&) = delete;
        ScopedStyleCompact operator=(const ScopedStyleCompact&) = delete;
        ScopedStyleCompact(float y)
        {
            ImGuiStyle& style = ImGui::GetStyle();
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, style.FramePadding.y * y));
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(style.ItemSpacing.x, style.ItemSpacing.y));
        }
        ~ScopedStyleCompact() { ImGui::PopStyleVar(2); }
    };

    struct ScopedFont
    {
        ScopedFont(const ScopedFont&) = delete;
        ScopedFont operator=(const ScopedFont&) = delete;
        ScopedFont(ImFont* font, float size = -1) { ImGui::PushFont(font, size * ImGui::GetWindowDpiScale()); }
        ScopedFont(int index, float size = -1) { ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[index], size * ImGui::GetWindowDpiScale()); }
        ~ScopedFont() { ImGui::PopFont(); }
    };

    struct ScopedDisabled
    {
        ScopedDisabled(const ScopedDisabled&) = delete;
        ScopedDisabled operator=(const ScopedDisabled&) = delete;
        ScopedDisabled(bool b) { ImGui::BeginDisabled(b); }
        ~ScopedDisabled() { ImGui::EndDisabled(); }
    };

    struct ScopedID
    {
        ScopedID(const ScopedID&) = delete;
        ScopedID operator=(const ScopedID&) = delete;
        template<typename T>
        ScopedID(T id) { ImGui::PushID(id); }
        ~ScopedID() { ImGui::PopID(); }
    };

    struct ScopedItemFlags
    {
        ScopedItemFlags(const ScopedItemFlags&) = delete;
        ScopedItemFlags operator=(const ScopedItemFlags&) = delete;
        ScopedItemFlags(const ImGuiItemFlags flags, const bool enable = true) { ImGui::PushItemFlag(flags, enable); }
        ~ScopedItemFlags() { ImGui::PopItemFlag(); }
    };

    struct ScopedItemWidth
    {
        ScopedItemWidth(const ScopedItemWidth&) = delete;
        ScopedItemWidth operator=(const ScopedItemWidth&) = delete;
        ScopedItemWidth(float value) { ImGui::PushItemWidth(value); }
        ~ScopedItemWidth() { ImGui::PopItemWidth(); }
    };

    struct ScopedFontSize
    {
        ScopedFontSize(const ScopedFontSize&) = delete;
        ScopedFontSize operator=(const ScopedFontSize&) = delete;
        ScopedFontSize(float size) { ImGui::PushFontSize(size); }
        ~ScopedFontSize() { ImGui::PopFontSize(); }
    };

    struct ScopedCompact
    {
        ScopedCompact(const ScopedCompact&) = delete;
        ScopedCompact operator=(const ScopedCompact&) = delete;
        ScopedCompact()
        {
            ImGuiStyle& style = ImGui::GetStyle();
            ImGui::PushStyleVarY(ImGuiStyleVar_FramePadding, (float)(int)(style.FramePadding.y * 0.60f));
            ImGui::PushStyleVarY(ImGuiStyleVar_ItemSpacing, (float)(int)(style.ItemSpacing.y * 0.60f));
        }
        ~ScopedCompact() { ImGui::PopStyleVar(2); }
    };

    struct ScopedColorStack
    {
        int count;

        ScopedColorStack(const ScopedColorStack&) = delete;
        ScopedColorStack operator=(const ScopedColorStack&) = delete;

        template <typename ColorType, typename... OtherColors>
        ScopedColorStack(ImGuiCol firstColorID, ColorType firstColor, OtherColors&& ... otherColorPairs)
            : count((sizeof... (otherColorPairs) / 2) + 1)
        {
            static_assert ((sizeof... (otherColorPairs) & 1u) == 0, "ScopedColorStack constructor expects a list of pairs of Color IDs and Colors as its arguments");
            PushColor(firstColorID, firstColor, std::forward<OtherColors>(otherColorPairs)...);
        }

        ~ScopedColorStack() { ImGui::PopStyleColor(count); }

    private:
        template <typename ColorType, typename... OtherColors>
        void PushColor(ImGuiCol ColorID, ColorType Color, OtherColors&& ... otherColorPairs)
        {
            if constexpr (sizeof... (otherColorPairs) == 0)
            {
                ImGui::PushStyleColor(ColorID, Color);
            }
            else
            {
                ImGui::PushStyleColor(ColorID, Color);
                PushColor(std::forward<OtherColors>(otherColorPairs)...);
            }
        }
    };

    struct ScopedStyleStack
    {
        int count;

        ScopedStyleStack(const ScopedStyleStack&) = delete;
        ScopedStyleStack operator=(const ScopedStyleStack&) = delete;

        template <typename ValueType, typename... OtherStylePairs>
        ScopedStyleStack(ImGuiStyleVar firstStyleVar, ValueType firstValue, OtherStylePairs&& ... otherStylePairs)
            : count((sizeof... (otherStylePairs) / 2) + 1)
        {
            static_assert ((sizeof... (otherStylePairs) & 1u) == 0, "ScopedStyleStack constructor expects a list of pairs of Color IDs and Colors as its arguments");

            PushStyle(firstStyleVar, firstValue, std::forward<OtherStylePairs>(otherStylePairs)...);
        }

        ~ScopedStyleStack() { ImGui::PopStyleVar(count); }

    private:
        template <typename ValueType, typename... OtherStylePairs>
        void PushStyle(ImGuiStyleVar styleVar, ValueType value, OtherStylePairs&& ... otherStylePairs)
        {
            if constexpr (sizeof... (otherStylePairs) == 0)
            {
                ImGui::PushStyleVar(styleVar, value);
            }
            else
            {
                ImGui::PushStyleVar(styleVar, value);
                PushStyle(std::forward<OtherStylePairs>(otherStylePairs)...);
            }
        }
    };
}

enum ImFieldDrageScalerEvent
{
    ImFieldDrageScalerEvent_None,
    ImFieldDrageScalerEvent_Edited,
    ImFieldDrageScalerEvent_ResetX,
    ImFieldDrageScalerEvent_ResetY,
    ImFieldDrageScalerEvent_ResetZ,
    ImFieldDrageScalerEvent_ResetW,
};

namespace ImField {

    IMGUI_API bool BeginBlock(const char* label, const char* icon = nullptr, ImVec4 iconColor = {});
    IMGUI_API bool BeginBlock(const char* label, bool* enabled, const char* icon = nullptr, ImVec4 iconColor = {});
    IMGUI_API void EndBlock();

    IMGUI_API void Field(const char* name, float offsetX = 8.0f);

    IMGUI_API bool DragFloat(const char* label, float* v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    IMGUI_API bool DragFloat2(const char* label, float v[2], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    IMGUI_API bool DragFloat3(const char* label, float v[3], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    IMGUI_API bool DragFloat4(const char* label, float v[4], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);

    IMGUI_API ImFieldDrageScalerEvent DragScalarN(const char* label, ImGuiDataType data_type, void* p_data, int components, float v_speed, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags);
    IMGUI_API ImFieldDrageScalerEvent DragColoredFloat(const char* label, float v[1], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    IMGUI_API ImFieldDrageScalerEvent DragColoredFloat2(const char* label, float v[2], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    IMGUI_API ImFieldDrageScalerEvent DragColoredFloat3(const char* label, float v[3], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);
    IMGUI_API ImFieldDrageScalerEvent DragColoredFloat4(const char* label, float v[4], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0);

    IMGUI_API bool DragInt(const char* label, int* v, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0);
    IMGUI_API bool DragInt2(const char* label, int v[2], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0);
    IMGUI_API bool DragInt3(const char* label, int v[3], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0);
    IMGUI_API bool DragInt4(const char* label, int v[4], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0);

    IMGUI_API bool DragUInt(const char* label, unsigned int* v, float v_speed = 1.0f, unsigned int v_min = 0, unsigned int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0);
    IMGUI_API bool DragUInt2(const char* label, unsigned int v[2], float v_speed = 1.0f, unsigned int v_min = 0, unsigned int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0);
    IMGUI_API bool DragUInt3(const char* label, unsigned int v[3], float v_speed = 1.0f, unsigned int v_min = 0, unsigned int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0);
    IMGUI_API bool DragUInt4(const char* label, unsigned int v[4], float v_speed = 1.0f, unsigned int v_min = 0, unsigned int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0);

    IMGUI_API bool InputText(const char* label, std::string* str, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = nullptr, void* user_data = nullptr);

    IMGUI_API bool InputText(const char* label, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
    IMGUI_API bool InputTextMultiline(const char* label, char* buf, size_t buf_size, const ImVec2& size = ImVec2(0, 0), ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
    IMGUI_API bool InputTextWithHint(const char* label, const char* hint, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);

    IMGUI_API bool InputScalar(const char* label, void* p_data, int flags);
    IMGUI_API bool InputInt(const char* label, int* v, int step = 1, int step_fast = 100, ImGuiInputTextFlags flags = 0);
    IMGUI_API bool InputUInt(const char* label, uint32_t* v, int step = 1, int step_fast = 100, ImGuiInputTextFlags flags = 0);

    IMGUI_API bool Button(const char* label, const char* buttonLabel, const ImVec2& size_arge = ImVec2(-1, 0));
    IMGUI_API bool ImageButton(const char* str_id, ImTextureRef tex_ref, const ImVec2& image_size, const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1), const ImVec4& bg_col = ImVec4(0, 0, 0, 0), const ImVec4& tint_col = ImVec4(1, 1, 1, 1));

    IMGUI_API void Text(const char* label, const char* fmt, ...);

    IMGUI_API bool Checkbox(const char* label, bool* v);

    IMGUI_API void TextUnformatted(const char* label, const char* text);

    IMGUI_API void TextLinkOpenURL(const char* label, const char* url);

    IMGUI_API bool ColorEdit3(const char* label, float col[3], ImGuiColorEditFlags flags = 0);
    IMGUI_API bool ColorEdit4(const char* label, float col[4], ImGuiColorEditFlags flags = 0);

    IMGUI_API void SeparatorText(const char* text);
    IMGUI_API void Separator();

    template<uint32_t N>
    IMGUI_API bool Combo(const char* label, const std::array<std::string_view, N>& arr, std::string_view current, void* selectedIndex)
    {
        bool res = false;
        Field(label);
        if (ImGui::BeginCombo(label, current.data()))
        {
            for (int i = 0; i < arr.size(); i++)
            {
                bool isSelected = current == arr[i];
                if (ImGui::Selectable(arr[i].data(), isSelected))
                {
                    *(int*)selectedIndex = i;
                    res = true;
                }

                if (isSelected)
                    ImGui::SetItemDefaultFocus();
            }

            ImGui::EndCombo();
        }
        return res;
    }

    template<uint32_t N>
    IMGUI_API bool ComboBox(const char* label, const std::array<std::string_view, N>& arr, std::string_view current, void* selectedIndex, ImVec2 size = { 70.0f, 16.0f })
    {
        Field(label);
        return ImGui::ComboBox("##label", arr, current, selectedIndex, size);
    }
}
