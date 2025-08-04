#include "ImExtra.h"
#include "imgui_internal.h"

#define MAX_AUTO_MENU_ITEM_TOKENS 16
#define MAX_AUTO_MENU_ITEM_TOKEN_LENGTH 64

static const ImGuiDataTypeInfo GDataTypeInfo[] =
{
    { sizeof(char),             "S8",   "%d",   "%d"    },  // ImGuiDataType_S8
    { sizeof(unsigned char),    "U8",   "%u",   "%u"    },
    { sizeof(short),            "S16",  "%d",   "%d"    },  // ImGuiDataType_S16
    { sizeof(unsigned short),   "U16",  "%u",   "%u"    },
    { sizeof(int),              "S32",  "%d",   "%d"    },  // ImGuiDataType_S32
    { sizeof(unsigned int),     "U32",  "%u",   "%u"    },
#ifdef _MSC_VER
    { sizeof(ImS64),            "S64",  "%I64d","%I64d" },  // ImGuiDataType_S64
    { sizeof(ImU64),            "U64",  "%I64u","%I64u" },
#else
    { sizeof(ImS64),            "S64",  "%lld", "%lld"  },  // ImGuiDataType_S64
    { sizeof(ImU64),            "U64",  "%llu", "%llu"  },
#endif
    { sizeof(float),            "float", "%.3f","%f"    },  // ImGuiDataType_Float (float are promoted to double in va_arg)
    { sizeof(double),           "double","%f",  "%lf"   },  // ImGuiDataType_Double
    { sizeof(bool),             "bool", "%d",   "%d"    },  // ImGuiDataType_Bool
    { 0,                        "char*","%s",   "%s"    },  // ImGuiDataType_String
};
IM_STATIC_ASSERT(IM_ARRAYSIZE(GDataTypeInfo) == ImGuiDataType_COUNT);

static const ImGuiDataTypeInfo* DataTypeGetInfo(ImGuiDataType data_type)
{
    IM_ASSERT(data_type >= 0 && data_type < ImGuiDataType_COUNT);
    return &GDataTypeInfo[data_type];
}

struct InputTextCallback_UserData
{
    std::string* Str;
    ImGuiInputTextCallback  ChainCallback;
    void* ChainCallbackUserData;
};

int InputTextCallback(ImGuiInputTextCallbackData* data)
{
    InputTextCallback_UserData* user_data = (InputTextCallback_UserData*)data->UserData;
    if (data->EventFlag == ImGuiInputTextFlags_CallbackResize)
    {
        // Resize string callback
        // If for some reason we refuse the new length (BufTextLen) and/or capacity (BufSize) we need to set them back to what we want.
        std::string* str = user_data->Str;
        IM_ASSERT(data->Buf == str->c_str());
        str->resize(data->BufTextLen);
        data->Buf = (char*)str->c_str();
    }
    else if (user_data->ChainCallback)
    {
        // Forward to user callback, if any
        data->UserData = user_data->ChainCallbackUserData;
        return user_data->ChainCallback(data);
    }
    return 0;
}

static bool SplitPath(const char* str, char delimiter, char outTokens[MAX_AUTO_MENU_ITEM_TOKENS][MAX_AUTO_MENU_ITEM_TOKEN_LENGTH], int& outCount)
{
    outCount = 0;
    int tokenLen = 0;

    if (!str)
        return false;

    while (*str && outCount < MAX_AUTO_MENU_ITEM_TOKENS)
    {
        if (*str == delimiter)
        {
            if (tokenLen > 0)
            {
                outTokens[outCount][tokenLen] = '\0';
                outCount++;
                tokenLen = 0;
            }
        }
        else if (tokenLen < MAX_AUTO_MENU_ITEM_TOKEN_LENGTH - 1)
        {
            outTokens[outCount][tokenLen++] = *str;
        }

        str++;
    }

    if (tokenLen > 0 && outCount < MAX_AUTO_MENU_ITEM_TOKENS)
    {
        outTokens[outCount][tokenLen] = '\0';
        outCount++;
    }

    return outCount > 0;
}

static bool CreateMenuLoop(
    char tokens[MAX_AUTO_MENU_ITEM_TOKENS][MAX_AUTO_MENU_ITEM_TOKEN_LENGTH], int tokenCount,
    const char* shortcut, bool selected, bool enabled
)
{
    for (int i = 0; i < tokenCount; i++)
    {
        const bool isLast = (i == tokenCount - 1);

        if (isLast)
        {
            return ImGui::MenuItem(tokens[i], shortcut, selected, enabled);
        }
        else
        {
            if (ImGui::BeginMenu(tokens[i]))
            {
                bool result = true;
                i++;

                while (i < tokenCount - 1)
                {
                    if (!ImGui::BeginMenu(tokens[i]))
                    {
                        result = false;
                        break;
                    }
                    i++;
                }

                if (result && i == tokenCount - 1)
                    result = ImGui::MenuItem(tokens[i], shortcut, selected, enabled);

                for (int j = i; j > 0; j--)
                    ImGui::EndMenu();

                return result;
            }
            else
            {
                return false;
            }
        }
    }

    return false;
}


bool ImGui::TextButton(const char* label, const ImVec2& size_arg)
{
    ImGuiButtonFlags flags = ImGuiButtonFlags_None;
    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1, 1));

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = CalcTextSize(label, NULL, true);

    ImVec2 pos = window->DC.CursorPos;
    if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
        pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
    ImVec2 size = CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

    const ImRect bb(pos, pos + size);
    ItemSize(size, style.FramePadding.y);

    if (!ItemAdd(bb, id))
    {
        ImGui::PopStyleVar();
        return false;
    }

    bool hovered, held;
    bool pressed = ButtonBehavior(bb, id, &hovered, &held, flags);

    if (ImGui::IsItemHovered())
        ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);

    // Render
    RenderNavCursor(bb, id);
    RenderFrame(bb.Min, bb.Max, 0x00000000, true, style.FrameRounding);

    if (g.LogEnabled)
        LogSetNextTextDecoration("[", "]");

    const ImVec4 col = GetStyleColorVec4((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Text);
    PushStyleColor(ImGuiCol_Text, col);
    RenderTextClipped(bb.Min + style.FramePadding, bb.Max - style.FramePadding, label, NULL, &label_size, style.ButtonTextAlign, &bb);
    PopStyleColor();

    ImGui::PopStyleVar();

    IMGUI_TEST_ENGINE_ITEM_INFO(id, label, g.LastItemData.StatusFlags);
    return pressed;
}

bool ImGui::InputText(const char* label, std::string* str, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
{
    IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
    flags |= ImGuiInputTextFlags_CallbackResize;

    InputTextCallback_UserData cb_user_data;
    cb_user_data.Str = str;
    cb_user_data.ChainCallback = callback;
    cb_user_data.ChainCallbackUserData = user_data;
    return InputText(label, (char*)str->c_str(), str->capacity() + 1, flags, InputTextCallback, &cb_user_data);
}

bool ImGui::InputTextMultiline(const char* label, std::string* str, const ImVec2& size, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
{
    IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
    flags |= ImGuiInputTextFlags_CallbackResize;

    InputTextCallback_UserData cb_user_data;
    cb_user_data.Str = str;
    cb_user_data.ChainCallback = callback;
    cb_user_data.ChainCallbackUserData = user_data;
    return InputTextMultiline(label, (char*)str->c_str(), str->capacity() + 1, size, flags, InputTextCallback, &cb_user_data);
}

bool ImGui::InputTextWithHint(const char* label, const char* hint, std::string* str, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
{
    IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
    flags |= ImGuiInputTextFlags_CallbackResize;

    InputTextCallback_UserData cb_user_data;
    cb_user_data.Str = str;
    cb_user_data.ChainCallback = callback;
    cb_user_data.ChainCallbackUserData = user_data;
    return InputTextWithHint(label, hint, (char*)str->c_str(), str->capacity() + 1, flags, InputTextCallback, &cb_user_data);
}

bool ImGui::SelectableButton(const char* label, const ImVec2& size, bool selected)
{
    auto& colors = ImGui::GetStyle().Colors;

    if (selected)
    {
        ImGui::PushStyleColor(ImGuiCol_Button, colors[ImGuiCol_ButtonActive]);
        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
    }

    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colors[ImGuiCol_ButtonActive] - ImVec4(0, 0, 0, 0.1f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, colors[ImGuiCol_ButtonActive]);

    if (ImGui::Button(label, size))
    {
        if (selected)
        {
            ImGui::PopStyleColor();
            ImGui::PopFont();
        }
        ImGui::PopStyleColor(2);

        return true;
    }

    if (selected)
    {
        ImGui::PopStyleColor();
        ImGui::PopFont();
    }
    ImGui::PopStyleColor(2);

    return false;
}

void ImGui::ToolTip(const char* fmt, ...)
{
    if (ImGui::IsItemHovered(ImGuiHoveredFlags_Stationary | ImGuiHoveredFlags_ForTooltip))
    {
        va_list args;
        va_start(args, fmt);
        SetTooltipV(fmt, args);
        va_end(args);
    }
}

void ImGui::ShiftCursorX(float offset)
{
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offset);
}

void ImGui::ShiftCursorY(float offset)
{
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + offset);
}

void ImGui::ShiftCursor(ImVec2 offset)
{
    const ImVec2 cursor = ImGui::GetCursorPos();
    ImGui::SetCursorPos(ImVec2(cursor.x, cursor.y) + offset);
}

bool ImGui::AutoMenuItem(const char* path, const char* shortcut, bool selected, bool enabled, ImAutoMenuItemFlags flags)
{
    if (path == nullptr || strcmp(path, "/") == 0)
        path = "None";

    char tokens[MAX_AUTO_MENU_ITEM_TOKENS][MAX_AUTO_MENU_ITEM_TOKEN_LENGTH];
    int tokenCount = 0;

    if (!SplitPath(path, '/', tokens, tokenCount))
        return false;

    bool win = false;

    switch (flags)
    {
    case ImAutoMenuItemFlags_None:
        win = CreateMenuLoop(tokens, tokenCount, shortcut, selected, enabled);
        break;
    case ImAutoMenuItemFlags_MainMenuBar:
        if (ImGui::BeginMainMenuBar())
        {
            win = CreateMenuLoop(tokens, tokenCount, shortcut, selected, enabled);
            ImGui::EndMainMenuBar();
        }
        break;
    case ImAutoMenuItemFlags_WindowMenuBar:
        if (ImGui::BeginMenuBar())
        {
            win = CreateMenuLoop(tokens, tokenCount, shortcut, selected, enabled);
            ImGui::EndMenuBar();
        }
        break;
    }

    return win;
}

void ImGui::PushStyleCompact()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImGui::PushStyleVarY(ImGuiStyleVar_FramePadding, (float)(int)(style.FramePadding.y * 0.60f));
    ImGui::PushStyleVarY(ImGuiStyleVar_ItemSpacing, (float)(int)(style.ItemSpacing.y * 0.60f));
}

void ImGui::PopStyleCompact()
{
    ImGui::PopStyleVar(2);
}

bool ImField::BeginBlock(const char* label, const char* icon, ImVec4 iconColor)
{
    const ImGuiTreeNodeFlags treeNodeFlags =
        ImGuiTreeNodeFlags_DefaultOpen |
        ImGuiTreeNodeFlags_Framed |
        ImGuiTreeNodeFlags_SpanAvailWidth |
        ImGuiTreeNodeFlags_AllowItemOverlap |
        ImGuiTreeNodeFlags_FramePadding |
        ImGuiTreeNodeFlags_CollapsingHeader;

    ImGui::ScopedColorStack sc(ImGuiCol_Header, ImVec4(0, 0, 0, 0), ImGuiCol_HeaderHovered, ImVec4(0, 0, 0, 0), ImGuiCol_HeaderActive, ImVec4(0, 0, 0, 0));
    ImGui::BeginChild(label, { 0, 0 }, ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_AlwaysUseWindowPadding);

    bool open = ImGui::TreeNodeEx(label, treeNodeFlags, "");

    if (icon && strlen(icon) != 0)
    {
        ImGui::ScopedColor sc(ImGuiCol_Text, iconColor);
        ImGui::SameLine();
        ImGui::Text(icon);
    }

    ImGui::SameLine();
    ImGui::Text(label);

    return open;
}

void ImField::EndBlock()
{
    ImGui::EndChild();
}

void ImField::Field(const char* name, float offsetX)
{
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::ShiftCursorX(offsetX * ImGui::GetIO().FontGlobalScale * ImGui::GetWindowDpiScale());
    ImGui::Text(name);
    ImGui::TableNextColumn();
    ImGui::SetNextItemWidth(-FLT_MIN);
}

bool ImField::DragFloat(const char* label, float* v, float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)     // If v_min >= v_max we have no bound
{
    Field(label);
    return ImGui::DragScalarN(label, ImGuiDataType_Float, v, 1, v_speed, &v_min, &v_max, format, flags);
}

bool ImField::DragFloat2(const char* label, float v[2], float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
{
    Field(label);
    return ImGui::DragScalarN(label, ImGuiDataType_Float, v, 2, v_speed, &v_min, &v_max, format, flags);
}

bool ImField::DragFloat3(const char* label, float v[3], float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
{
    Field(label);
    return ImGui::DragScalarN(label, ImGuiDataType_Float, v, 3, v_speed, &v_min, &v_max, format, flags);
}

bool ImField::DragFloat4(const char* label, float v[4], float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
{
    Field(label);
    return ImGui::DragScalarN(label, ImGuiDataType_Float, v, 4, v_speed, &v_min, &v_max, format, flags);;
}

bool ImField::DragInt(const char* label, int* v, float v_speed, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)     // If v_min >= v_max we have no bound
{
    Field(label);
    return ImGui::DragScalarN(label, ImGuiDataType_S32, v, 1, v_speed, &v_min, &v_max, format, flags);
}

bool ImField::DragInt2(const char* label, int v[2], float v_speed, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
{
    ImGui::ScopedID id(label);

    Field(label);
    return ImGui::DragScalarN(label, ImGuiDataType_S32, v, 2, v_speed, &v_min, &v_max, format, flags);
}

bool ImField::DragInt3(const char* label, int v[3], float v_speed, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
{
    Field(label);
    return ImGui::DragScalarN(label, ImGuiDataType_S32, v, 3, v_speed, &v_min, &v_max, format, flags);
}

bool ImField::DragInt4(const char* label, int v[4], float v_speed, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
{
    Field(label);
    return ImGui::DragScalarN(label, ImGuiDataType_S32, v, 4, v_speed, &v_min, &v_max, format, flags);;
}

ImFieldDrageScalerEvent ImField::DragScalarN(const char* label, ImGuiDataType data_type, void* p_data, int components, float v_speed, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return ImFieldDrageScalerEvent_None;

    float scale = ImGui::GetIO().FontGlobalScale * ImGui::GetWindowDpiScale();

    ImVec4 colors[] = {
       
        ImVec4(1.0f, 0.2117647f, 0.3254902f, 1.0f),
        ImVec4(1.0f, 0.3f,       0.4f,       1.0f),
        ImVec4(0.8f, 0.1f,       0.2f,       1.0f),

        ImVec4(0.5411765f, 0.8588235f, 0.0f, 1.0f),
        ImVec4(0.65f,       1.0f,       0.3f, 1.0f),
        ImVec4(0.4f,        0.7f,       0.0f, 1.0f),

        ImVec4(0.1725490f, 0.5607843f, 1.0f, 1.0f),
        ImVec4(0.3f,        0.65f,      1.0f, 1.0f),
        ImVec4(0.1f,        0.45f,      0.9f, 1.0f),

        ImVec4(0.8f, 0.3f, 0.8f, 1.0f),
        ImVec4(0.9f, 0.3f, 0.9f, 1.0f),
        ImVec4(1.0f, 0.3f, 1.0f, 1.0f),
    };


    ImGuiContext& g = *GImGui;
    ImFieldDrageScalerEvent value = ImFieldDrageScalerEvent_None;

    ImGui::BeginGroup();
    ImGui::PushID(label);
    float bw = 6 * scale;
    ImGui::PushMultiItemsWidths(components, ImGui::CalcItemWidth() - bw * components);
    size_t type_size = GDataTypeInfo[data_type].Size;
    for (int i = 0; i < components; i++)
    {
        ImGui::PushStyleColor(ImGuiCol_Button, colors[i * 3 + 0]);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colors[i * 3 + 1]);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, colors[i * 3 + 2]);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 1);
        ImGui::PushID(i + components);
        if (i > 0) ImGui::SameLine(0, g.Style.ItemInnerSpacing.x);
        value = (ImFieldDrageScalerEvent)(ImGui::Button("", ImVec2(bw, 0)) ? i + 2 : value);
        ImGui::PopStyleVar(1);
        ImGui::PopID();
        ImGui::PopStyleColor(3);


        ImGui::PushID(i);
        ImGui::SameLine(0, 0);
        value = (ImFieldDrageScalerEvent)(ImGui::DragScalar("", data_type, p_data, v_speed, p_min, p_max, format, flags) ? 1 : value);
        ImGui::PopID();
        ImGui::PopItemWidth();
        p_data = (void*)((char*)p_data + type_size);


    }
    ImGui::PopID();

    const char* label_end = ImGui::FindRenderedTextEnd(label);
    if (label != label_end)
    {
        ImGui::SameLine(0, g.Style.ItemInnerSpacing.x);
        ImGui::TextEx(label, label_end);
    }

    ImGui::EndGroup();
    return value;
}

ImFieldDrageScalerEvent ImField::DragColoredFloat(const char* label, float v[1], float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
{
    Field(label);
    return DragScalarN(label, ImGuiDataType_Float, v, 1, v_speed, &v_min, &v_max, format, flags);
}

ImFieldDrageScalerEvent ImField::DragColoredFloat2(const char* label, float v[2], float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
{
    Field(label);
    return DragScalarN(label, ImGuiDataType_Float, v, 2, v_speed, &v_min, &v_max, format, flags);
}

ImFieldDrageScalerEvent ImField::DragColoredFloat3(const char* label, float v[3], float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
{
    Field(label);
    return DragScalarN(label, ImGuiDataType_Float, v, 3, v_speed, &v_min, &v_max, format, flags);
}

ImFieldDrageScalerEvent ImField::DragColoredFloat4(const char* label, float v[4], float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
{
    Field(label);
    return DragScalarN(label, ImGuiDataType_Float, v, 4, v_speed, &v_min, &v_max, format, flags);
}

bool ImField::InputText(const char* label, std::string* str, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
{
    Field(label);
    return ImGui::InputText(label, str, flags, callback, user_data);
}

bool ImField::InputText(const char* label, char* buf, size_t buf_size, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
{
    Field(label);
    return ImGui::InputText(label, buf, buf_size, flags, callback, user_data);
}

bool ImField::InputTextMultiline(const char* label, char* buf, size_t buf_size, const ImVec2& size, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
{
    Field(label);
    return ImGui::InputTextMultiline(label, buf, buf_size, size, flags, callback, user_data);
}

bool ImField::InputTextWithHint(const char* label, const char* hint, char* buf, size_t buf_size, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
{
    Field(label);
    return ImGui::InputTextWithHint(label, hint, buf, buf_size, flags, callback, user_data);
}

bool ImField::InputScalar(const char* label, void* p_data, int flags)
{
    ImGui::ScopedID id(label);
    Field(label);
    return ImGui::InputScalar(label, flags, p_data);
}

bool ImField::InputInt(const char* label, int* v, int step, int step_fast, ImGuiInputTextFlags flags)
{
    Field(label);
    return ImGui::InputInt(label, v, step, step_fast, flags);
}

bool ImField::InputUInt(const char* label, uint32_t* v, int step, int step_fast, ImGuiInputTextFlags flags)
{
    ImGui::ScopedID id(label);
    Field(label);

    const char* format = (flags & ImGuiInputTextFlags_CharsHexadecimal) ? "%08X" : "%d";
    return ImGui::InputScalar(label, ImGuiDataType_U32, (void*)v, (void*)(step > 0 ? &step : NULL), (void*)(step_fast > 0 ? &step_fast : NULL), format, flags);
}

bool ImField::Button(const char* label, const char* buttonLabel, const ImVec2& size_arge)
{
    Field(label);
    return ImGui::Button(buttonLabel, size_arge);
}

bool ImField::ImageButton(const char* str_id, ImTextureRef tex_ref, const ImVec2& image_size, const ImVec2& uv0, const ImVec2& uv1, const ImVec4& bg_col, const ImVec4& tint_col)
{
    ImGuiContext& g = *GImGui;
    ImGuiWindow* window = g.CurrentWindow;
    if (window->SkipItems)
        return false;

    ImField::Field(str_id);
    return ImGui::ImageButtonEx(window->GetID(str_id), tex_ref, image_size, uv0, uv1, bg_col, tint_col);
}

void ImField::Text(const char* label, const char* fmt, ...)
{
    Field(label);
    va_list args;
    va_start(args, fmt);
    ImGui::TextV(fmt, args);
    va_end(args);
}

bool ImField::Checkbox(const char* label, bool* v)
{
    ImGui::ScopedID sid(label);
    Field(label);
    return ImGui::Checkbox("##label", v);
}

void ImField::TextUnformatted(const char* label, const char* text)
{
    Field(label);
    ImGui::TextUnformatted(text);
}

void ImField::TextLinkOpenURL(const char* label, const char* url)
{
    Field(label);
    ImGui::TextLinkOpenURL(url, url);
}

bool ImField::ColorEdit3(const char* label, float col[3], ImGuiColorEditFlags flags)
{
    Field(label);
    return ImGui::ColorEdit3(label, col, flags);
}

bool ImField::ColorEdit4(const char* label, float col[4], ImGuiColorEditFlags flags)
{
    Field(label);
    return ImGui::ColorEdit4(label, col, flags);
}

void ImField::SeparatorText(const char* text)
{
    ImField::Field(text);
    ImGui::SeparatorText("");
}

void ImField::Separator()
{
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::Separator();
    ImGui::TableNextColumn();
    ImGui::Separator();
}
