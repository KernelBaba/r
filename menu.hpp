#pragma once
#include "../offsets.hpp"

extern void save_config();
extern void load_config();

namespace lo_menu {

    inline bool is_open = true;
    inline int selected_tab = 0;
    inline int item_selection = 0;

    const wchar_t* categories[] = {
        L"Aimbot",
        L"Anti Aim",
        L"Outlines",
        L"Visuals",
        L"World",
        L"Misc",
        L"Self",
        L"Config"
    };

    constexpr int category_count = 8;

    inline flinearcolor bg_box       = { 0.03f, 0.03f, 0.03f, 0.92f };
    inline flinearcolor turquoise    = { 0.0f, 0.85f, 0.85f, 1.0f };
    inline flinearcolor turq_dim     = { 0.0f, 0.55f, 0.55f, 1.0f };
    inline flinearcolor turq_glow    = { 0.0f, 0.85f, 0.85f, 0.25f };
    inline flinearcolor border_col   = { 0.0f, 0.45f, 0.45f, 0.7f };
    inline flinearcolor white        = { 1.0f, 1.0f, 1.0f, 1.0f };
    inline flinearcolor green_on     = { 0.1f, 1.0f, 0.1f, 1.0f };
    inline flinearcolor red_off      = { 1.0f, 0.0f, 0.0f, 1.0f };
    inline flinearcolor yellow_sel   = { 1.0f, 1.0f, 0.0f, 1.0f };

    constexpr float menu_x       = 40.0f;
    constexpr float menu_y       = 80.0f;
    constexpr float tab_w        = 105.0f;
    constexpr float tab_h        = 24.0f;
    constexpr float tab_gap      = 3.0f;
    constexpr float content_x    = menu_x + tab_w + 10.0f;
    constexpr float content_y    = menu_y;
    constexpr float content_w    = 200.0f;
    constexpr float row_h        = 20.0f;

    inline flinearcolor get_bool_color(bool val) {
        return val ? green_on : red_off;
    }

    inline void draw_filled_rect(ucanvas* canvas, fvector2d tl, fvector2d br, flinearcolor col) {
        for (float y = tl.y; y <= br.y; y += 1.0f) {
            canvas->k2_drawline({ tl.x, y }, { br.x, y }, 1.0f, col);
        }
    }

    inline void draw_rect_outline(ucanvas* canvas, fvector2d tl, fvector2d br, flinearcolor col) {
        canvas->k2_drawline(tl, { br.x, tl.y }, 1.0f, col);
        canvas->k2_drawline({ br.x, tl.y }, br, 1.0f, col);
        canvas->k2_drawline(br, { tl.x, br.y }, 1.0f, col);
        canvas->k2_drawline({ tl.x, br.y }, tl, 1.0f, col);
    }

    inline int get_max_items() {
        switch (selected_tab) {
        case 0: return 10;
        case 1: return 10;
        case 2: return 8;
        case 3: return 12;
        case 4: return 4;
        case 5: return 10;
        case 6: return 6;
        case 7: return 3;
        default: return 0;
        }
    }

    inline void draw_menu(uobject* font, ucanvas* canvas) {
        if (!is_open || !canvas || !font) return;

        draw_filled_rect(canvas,
            { menu_x - 2, menu_y - 2 },
            { menu_x + tab_w + 2, menu_y + (category_count * (tab_h + tab_gap)) },
            { 0.0f, 0.0f, 0.0f, 0.85f });

        draw_rect_outline(canvas,
            { menu_x - 2, menu_y - 2 },
            { menu_x + tab_w + 2, menu_y + (category_count * (tab_h + tab_gap)) },
            border_col);

        canvas->k2_drawtext(font, crypt(L"KROUZZE").decrypt(),
            { menu_x + 4, menu_y - 20 }, { 1.3f, 1.3f }, turquoise,
            0.f, { 0,0,0,0 }, { 0,0 }, false, false, true, { 0,0,0,0.7f });

        for (int i = 0; i < category_count; i++) {
            float ty = menu_y + i * (tab_h + tab_gap);
            bool is_sel = (selected_tab == i);

            draw_filled_rect(canvas,
                { menu_x, ty },
                { menu_x + tab_w, ty + tab_h },
                is_sel ? turq_glow : bg_box);

            draw_rect_outline(canvas,
                { menu_x, ty },
                { menu_x + tab_w, ty + tab_h },
                is_sel ? turquoise : border_col);

            canvas->k2_drawtext(font, categories[i],
                { menu_x + 10, ty + 4 }, { 0.9f, 0.9f },
                is_sel ? turquoise : turq_dim,
                0.f, { 0,0,0,0 }, { 0,0 }, false, false, true, { 0,0,0,0.6f });
        }

        float content_bottom = content_y;
        float cx = content_x;

        switch (selected_tab) {
        case 0: {
            canvas->k2_drawtext(font, crypt(L"Aimbot").decrypt(),
                { cx, content_y - 20 }, { 1.1f, 1.1f }, turquoise,
                0.f, { 0,0,0,0 }, { 0,0 }, false, false, true, { 0,0,0,0.6f });

            auto draw_bool = [&](const wchar_t* label, bool val, int id) {
                float ry = content_y + id * row_h;
                canvas->k2_drawtext(font, label, { cx, ry }, { 0.85f, 0.85f },
                    (item_selection == id) ? yellow_sel : white,
                    0.f, { 0,0,0,0 }, { 0,0 }, false, false, true, { 0,0,0,0.5f });
                canvas->k2_drawtext(font, val ? crypt(L"[ON]").decrypt() : crypt(L"[OFF]").decrypt(),
                    { cx + 140, ry }, { 0.85f, 0.85f },
                    (item_selection == id) ? yellow_sel : get_bool_color(val),
                    0.f, { 0,0,0,0 }, { 0,0 }, false, false, true, { 0,0,0,0.5f });
                content_bottom = ry + row_h;
            };

            auto draw_float = [&](const wchar_t* label, float val, int id) {
                float ry = content_y + id * row_h;
                canvas->k2_drawtext(font, label, { cx, ry }, { 0.85f, 0.85f },
                    (item_selection == id) ? yellow_sel : white,
                    0.f, { 0,0,0,0 }, { 0,0 }, false, false, true, { 0,0,0,0.5f });
                wchar_t buf[32];
                swprintf_s(buf, L"%.2f", val);
                canvas->k2_drawtext(font, buf,
                    { cx + 140, ry }, { 0.85f, 0.85f },
                    (item_selection == id) ? yellow_sel : turquoise,
                    0.f, { 0,0,0,0 }, { 0,0 }, false, false, true, { 0,0,0,0.5f });
                content_bottom = ry + row_h;
            };

            draw_bool(crypt(L"Enabled").decrypt(),        globals::aimbot::a1mbot,      0);
            draw_bool(crypt(L"Visible Check").decrypt(),   globals::aimbot::v1sh_ch3ck,   1);
            draw_bool(crypt(L"Recoil Control").decrypt(),  globals::aimbot::reco1l_contr0l, 2);
            draw_bool(crypt(L"Spread Comp").decrypt(),     globals::aimbot::spread_comp,  3);
            draw_bool(crypt(L"Auto Shot").decrypt(),       globals::aimbot::autoshot,     4);
            draw_bool(crypt(L"Draw FOV").decrypt(),        globals::aimbot::draw_f0v,     5);
            draw_bool(crypt(L"Auto Scope").decrypt(),      globals::aimbot::auto_scope,   6);
            draw_float(crypt(L"Smooth").decrypt(),         globals::aimbot::a1m_sm00th,   7);
            draw_float(crypt(L"FOV").decrypt(),            globals::aimbot::a1m_f0v,      8);
            draw_float(crypt(L"Min Damage").decrypt(),     globals::aimbot::min_damage,   9);
            break;
        }
        case 1: {
            canvas->k2_drawtext(font, crypt(L"Anti Aim").decrypt(),
                { cx, content_y - 20 }, { 1.1f, 1.1f }, turquoise,
                0.f, { 0,0,0,0 }, { 0,0 }, false, false, true, { 0,0,0,0.6f });

            auto draw_bool = [&](const wchar_t* label, bool val, int id) {
                float ry = content_y + id * row_h;
                canvas->k2_drawtext(font, label, { cx, ry }, { 0.85f, 0.85f },
                    (item_selection == id) ? yellow_sel : white,
                    0.f, { 0,0,0,0 }, { 0,0 }, false, false, true, { 0,0,0,0.5f });
                canvas->k2_drawtext(font, val ? crypt(L"[ON]").decrypt() : crypt(L"[OFF]").decrypt(),
                    { cx + 140, ry }, { 0.85f, 0.85f },
                    (item_selection == id) ? yellow_sel : get_bool_color(val),
                    0.f, { 0,0,0,0 }, { 0,0 }, false, false, true, { 0,0,0,0.5f });
                content_bottom = ry + row_h;
            };

            auto draw_float = [&](const wchar_t* label, float val, int id) {
                float ry = content_y + id * row_h;
                canvas->k2_drawtext(font, label, { cx, ry }, { 0.85f, 0.85f },
                    (item_selection == id) ? yellow_sel : white,
                    0.f, { 0,0,0,0 }, { 0,0 }, false, false, true, { 0,0,0,0.5f });
                wchar_t buf[32];
                swprintf_s(buf, L"%.2f", val);
                canvas->k2_drawtext(font, buf,
                    { cx + 140, ry }, { 0.85f, 0.85f },
                    (item_selection == id) ? yellow_sel : turquoise,
                    0.f, { 0,0,0,0 }, { 0,0 }, false, false, true, { 0,0,0,0.5f });
                content_bottom = ry + row_h;
            };

            draw_bool(crypt(L"Enabled").decrypt(),           globals::misc::aa,              0);
            draw_bool(crypt(L"Spinner").decrypt(),            globals::misc::spinner,         1);
            draw_bool(crypt(L"Pitch").decrypt(),              globals::misc::pitch_enabled,   2);
            draw_bool(crypt(L"Jitter").decrypt(),             globals::misc::jitter_enabled,  3);
            draw_bool(crypt(L"Freestanding").decrypt(),       globals::misc::freestanding,    4);
            draw_bool(crypt(L"Manual AA").decrypt(),          globals::misc::manual_aa,       5);
            draw_bool(crypt(L"Desync").decrypt(),             globals::misc::aa_desync,       6);
            draw_float(crypt(L"Jitter Range").decrypt(),     globals::misc::jitter_range,    7);
            draw_float(crypt(L"Desync Range").decrypt(),     globals::misc::desync_range,    8);
            draw_float(crypt(L"Yaw Add").decrypt(),          globals::misc::yaw_add,         9);
            break;
        }
        case 2: {
            canvas->k2_drawtext(font, crypt(L"Outlines").decrypt(),
                { cx, content_y - 20 }, { 1.1f, 1.1f }, turquoise,
                0.f, { 0,0,0,0 }, { 0,0 }, false, false, true, { 0,0,0,0.6f });

            auto draw_bool = [&](const wchar_t* label, bool val, int id) {
                float ry = content_y + id * row_h;
                canvas->k2_drawtext(font, label, { cx, ry }, { 0.85f, 0.85f },
                    (item_selection == id) ? yellow_sel : white,
                    0.f, { 0,0,0,0 }, { 0,0 }, false, false, true, { 0,0,0,0.5f });
                canvas->k2_drawtext(font, val ? crypt(L"[ON]").decrypt() : crypt(L"[OFF]").decrypt(),
                    { cx + 140, ry }, { 0.85f, 0.85f },
                    (item_selection == id) ? yellow_sel : get_bool_color(val),
                    0.f, { 0,0,0,0 }, { 0,0 }, false, false, true, { 0,0,0,0.5f });
                content_bottom = ry + row_h;
            };

            auto draw_float = [&](const wchar_t* label, float val, int id) {
                float ry = content_y + id * row_h;
                canvas->k2_drawtext(font, label, { cx, ry }, { 0.85f, 0.85f },
                    (item_selection == id) ? yellow_sel : white,
                    0.f, { 0,0,0,0 }, { 0,0 }, false, false, true, { 0,0,0,0.5f });
                wchar_t buf[32];
                swprintf_s(buf, L"%.2f", val);
                canvas->k2_drawtext(font, buf,
                    { cx + 140, ry }, { 0.85f, 0.85f },
                    (item_selection == id) ? yellow_sel : turquoise,
                    0.f, { 0,0,0,0 }, { 0,0 }, false, false, true, { 0,0,0,0.5f });
                content_bottom = ry + row_h;
            };

            draw_bool(crypt(L"Outline Enabled").decrypt(),   globals::visuals::outline_enabled,    0);
            draw_bool(crypt(L"Visible Check").decrypt(),     globals::visuals::visiblecheck,       1);
            draw_bool(crypt(L"Dynamic Fresnel").decrypt(),   globals::visuals::dynamic_fresnel_outline, 2);
            draw_bool(crypt(L"Crystal Chams").decrypt(),     globals::visuals::crystal_chams_enabled,  3);
            draw_float(crypt(L"Visible Intensity").decrypt(), globals::visuals::intensityvisibleoutline, 4);
            draw_float(crypt(L"Invis Intensity").decrypt(),  globals::visuals::intensityinvisbleoutline, 5);
            draw_float(crypt(L"Glow Visible").decrypt(),     globals::visuals::GlowVisible,         6);
            draw_float(crypt(L"Glow Invisible").decrypt(),   globals::visuals::GlowInvisible,       7);
            break;
        }
        case 3: {
            canvas->k2_drawtext(font, crypt(L"Visuals").decrypt(),
                { cx, content_y - 20 }, { 1.1f, 1.1f }, turquoise,
                0.f, { 0,0,0,0 }, { 0,0 }, false, false, true, { 0,0,0,0.6f });

            auto draw_bool = [&](const wchar_t* label, bool val, int id) {
                float ry = content_y + id * row_h;
                canvas->k2_drawtext(font, label, { cx, ry }, { 0.85f, 0.85f },
                    (item_selection == id) ? yellow_sel : white,
                    0.f, { 0,0,0,0 }, { 0,0 }, false, false, true, { 0,0,0,0.5f });
                canvas->k2_drawtext(font, val ? crypt(L"[ON]").decrypt() : crypt(L"[OFF]").decrypt(),
                    { cx + 140, ry }, { 0.85f, 0.85f },
                    (item_selection == id) ? yellow_sel : get_bool_color(val),
                    0.f, { 0,0,0,0 }, { 0,0 }, false, false, true, { 0,0,0,0.5f });
                content_bottom = ry + row_h;
            };

            draw_bool(crypt(L"Head Box").decrypt(),         globals::visuals::headb0x,          0);
            draw_bool(crypt(L"Skeleton").decrypt(),          globals::visuals::sk3let0n,         1);
            draw_bool(crypt(L"Snapline").decrypt(),          globals::visuals::snapl1ne,         2);
            draw_bool(crypt(L"Health Bar").decrypt(),        globals::visuals::h3althbar,        3);
            draw_bool(crypt(L"Box 2D").decrypt(),            globals::visuals::box2d,            4);
            draw_bool(crypt(L"Box 3D").decrypt(),            globals::visuals::box3d,            5);
            draw_bool(crypt(L"Corner Box").decrypt(),        globals::visuals::cornerbox,        6);
            draw_bool(crypt(L"Agent Name").decrypt(),        globals::visuals::agent_name,       7);
            draw_bool(crypt(L"Weapon ESP").decrypt(),        globals::visuals::weaponesp,        8);
            draw_bool(crypt(L"Chinese Hat").decrypt(),       globals::visuals::chinese_hat,      9);
            draw_bool(crypt(L"Offscreen ESP").decrypt(),     globals::visuals::offscreen_esp,    10);
            draw_bool(crypt(L"Bullet Tracers").decrypt(),    globals::visuals::bullet_tracers,   11);
            break;
        }
        case 4: {
            canvas->k2_drawtext(font, crypt(L"World").decrypt(),
                { cx, content_y - 20 }, { 1.1f, 1.1f }, turquoise,
                0.f, { 0,0,0,0 }, { 0,0 }, false, false, true, { 0,0,0,0.6f });

            auto draw_bool = [&](const wchar_t* label, bool val, int id) {
                float ry = content_y + id * row_h;
                canvas->k2_drawtext(font, label, { cx, ry }, { 0.85f, 0.85f },
                    (item_selection == id) ? yellow_sel : white,
                    0.f, { 0,0,0,0 }, { 0,0 }, false, false, true, { 0,0,0,0.5f });
                canvas->k2_drawtext(font, val ? crypt(L"[ON]").decrypt() : crypt(L"[OFF]").decrypt(),
                    { cx + 140, ry }, { 0.85f, 0.85f },
                    (item_selection == id) ? yellow_sel : get_bool_color(val),
                    0.f, { 0,0,0,0 }, { 0,0 }, false, false, true, { 0,0,0,0.5f });
                content_bottom = ry + row_h;
            };

            draw_bool(crypt(L"Skybox").decrypt(),           globals::misc::skybox,           0);
            draw_bool(crypt(L"Skybox RGB").decrypt(),        globals::misc::skyboxrgb,        1);
            draw_bool(crypt(L"World ESP").decrypt(),         globals::misc::world_esp,        2);
            draw_bool(crypt(L"Gadgets").decrypt(),           globals::misc::gadgets,          3);
            break;
        }
        case 5: {
            canvas->k2_drawtext(font, crypt(L"Misc").decrypt(),
                { cx, content_y - 20 }, { 1.1f, 1.1f }, turquoise,
                0.f, { 0,0,0,0 }, { 0,0 }, false, false, true, { 0,0,0,0.6f });

            auto draw_bool = [&](const wchar_t* label, bool val, int id) {
                float ry = content_y + id * row_h;
                canvas->k2_drawtext(font, label, { cx, ry }, { 0.85f, 0.85f },
                    (item_selection == id) ? yellow_sel : white,
                    0.f, { 0,0,0,0 }, { 0,0 }, false, false, true, { 0,0,0,0.5f });
                canvas->k2_drawtext(font, val ? crypt(L"[ON]").decrypt() : crypt(L"[OFF]").decrypt(),
                    { cx + 140, ry }, { 0.85f, 0.85f },
                    (item_selection == id) ? yellow_sel : get_bool_color(val),
                    0.f, { 0,0,0,0 }, { 0,0 }, false, false, true, { 0,0,0,0.5f });
                content_bottom = ry + row_h;
            };

            draw_bool(crypt(L"Skin Changer").decrypt(),     globals::misc::sk1n_chang3r,    0);
            draw_bool(crypt(L"Hand Chams").decrypt(),        globals::misc::handchams,       1);
            draw_bool(crypt(L"Bunny Hop").decrypt(),         globals::misc::bunnyhop,        2);
            draw_bool(crypt(L"Fast Crouch").decrypt(),       globals::misc::fastcrouch,      3);
            draw_bool(crypt(L"Anti Flash").decrypt(),        globals::misc::antiflash,       4);
            draw_bool(crypt(L"Kill Sound").decrypt(),        globals::misc::killsound,       5);
            draw_bool(crypt(L"Kill Says").decrypt(),         globals::misc::killsays,        6);
            draw_bool(crypt(L"Chat Spammer").decrypt(),      globals::misc::chat_spammer,    7);
            draw_bool(crypt(L"TPerson").decrypt(),           globals::misc::tperson,         8);
            draw_bool(crypt(L"Disconnect").decrypt(),        globals::misc::disconnect_server, 9);
            break;
        }
        case 6: {
            canvas->k2_drawtext(font, crypt(L"Self").decrypt(),
                { cx, content_y - 20 }, { 1.1f, 1.1f }, turquoise,
                0.f, { 0,0,0,0 }, { 0,0 }, false, false, true, { 0,0,0,0.6f });

            auto draw_bool = [&](const wchar_t* label, bool val, int id) {
                float ry = content_y + id * row_h;
                canvas->k2_drawtext(font, label, { cx, ry }, { 0.85f, 0.85f },
                    (item_selection == id) ? yellow_sel : white,
                    0.f, { 0,0,0,0 }, { 0,0 }, false, false, true, { 0,0,0,0.5f });
                canvas->k2_drawtext(font, val ? crypt(L"[ON]").decrypt() : crypt(L"[OFF]").decrypt(),
                    { cx + 140, ry }, { 0.85f, 0.85f },
                    (item_selection == id) ? yellow_sel : get_bool_color(val),
                    0.f, { 0,0,0,0 }, { 0,0 }, false, false, true, { 0,0,0,0.5f });
                content_bottom = ry + row_h;
            };

            draw_bool(crypt(L"Self Chams").decrypt(),        globals::visuals::self_chams,          0);
            draw_bool(crypt(L"Self Galaxy").decrypt(),       globals::visuals::self_galaxy_enabled, 1);
            draw_bool(crypt(L"Wireframe").decrypt(),         globals::visuals::self_wireframe,      2);
            draw_bool(crypt(L"Self Chinese Hat").decrypt(),  globals::visuals::chinese_hat_self,    3);
            draw_bool(crypt(L"Hand Wireframe").decrypt(),    globals::visuals::wireframe_hands,     4);
            draw_bool(crypt(L"Weapon Wireframe").decrypt(),  globals::visuals::wireframe_weapon,    5);
            break;
        }
        case 7: {
            canvas->k2_drawtext(font, crypt(L"Config").decrypt(),
                { cx, content_y - 20 }, { 1.1f, 1.1f }, turquoise,
                0.f, { 0,0,0,0 }, { 0,0 }, false, false, true, { 0,0,0,0.6f });

            float ry0 = content_y + 0 * row_h;
            canvas->k2_drawtext(font, crypt(L"F5 - Save Config").decrypt(),
                { cx, ry0 }, { 0.85f, 0.85f },
                (item_selection == 0) ? yellow_sel : white,
                0.f, { 0,0,0,0 }, { 0,0 }, false, false, true, { 0,0,0,0.5f });

            float ry1 = content_y + 1 * row_h;
            canvas->k2_drawtext(font, crypt(L"F6 - Load Config").decrypt(),
                { cx, ry1 }, { 0.85f, 0.85f },
                (item_selection == 1) ? yellow_sel : white,
                0.f, { 0,0,0,0 }, { 0,0 }, false, false, true, { 0,0,0,0.5f });

            float ry2 = content_y + 2 * row_h;
            canvas->k2_drawtext(font, crypt(L"F7 - Reset Defaults").decrypt(),
                { cx, ry2 }, { 0.85f, 0.85f },
                (item_selection == 2) ? yellow_sel : white,
                0.f, { 0,0,0,0 }, { 0,0 }, false, false, true, { 0,0,0,0.5f });
            break;
        }
        }

        draw_rect_outline(canvas,
            { content_x - 2, content_y - 2 },
            { content_x + content_w + 2, content_bottom + 4 },
            border_col);
    }

    inline void toggle_selected() {
        switch (selected_tab) {
        case 0:
            switch (item_selection) {
            case 0: globals::aimbot::a1mbot = !globals::aimbot::a1mbot; break;
            case 1: globals::aimbot::v1sh_ch3ck = !globals::aimbot::v1sh_ch3ck; break;
            case 2: globals::aimbot::reco1l_contr0l = !globals::aimbot::reco1l_contr0l; break;
            case 3: globals::aimbot::spread_comp = !globals::aimbot::spread_comp; break;
            case 4: globals::aimbot::autoshot = !globals::aimbot::autoshot; break;
            case 5: globals::aimbot::draw_f0v = !globals::aimbot::draw_f0v; break;
            case 6: globals::aimbot::auto_scope = !globals::aimbot::auto_scope; break;
            case 7: globals::aimbot::a1m_sm00th += 0.5f; if (globals::aimbot::a1m_sm00th > 10.0f) globals::aimbot::a1m_sm00th = 1.0f; break;
            case 8: globals::aimbot::a1m_f0v += 5.0f; if (globals::aimbot::a1m_f0v > 500.0f) globals::aimbot::a1m_f0v = 10.0f; break;
            case 9: globals::aimbot::min_damage += 5.0f; if (globals::aimbot::min_damage > 150.0f) globals::aimbot::min_damage = 10.0f; break;
            }
            break;
        case 1:
            switch (item_selection) {
            case 0: globals::misc::aa = !globals::misc::aa; break;
            case 1: globals::misc::spinner = !globals::misc::spinner; break;
            case 2: globals::misc::pitch_enabled = !globals::misc::pitch_enabled; break;
            case 3: globals::misc::jitter_enabled = !globals::misc::jitter_enabled; break;
            case 4: globals::misc::freestanding = !globals::misc::freestanding; break;
            case 5: globals::misc::manual_aa = !globals::misc::manual_aa; break;
            case 6: globals::misc::aa_desync = !globals::misc::aa_desync; break;
            case 7: globals::misc::jitter_range += 10.0f; if (globals::misc::jitter_range > 180.0f) globals::misc::jitter_range = 0.0f; break;
            case 8: globals::misc::desync_range += 10.0f; if (globals::misc::desync_range > 180.0f) globals::misc::desync_range = 0.0f; break;
            case 9: globals::misc::yaw_add += 5.0f; if (globals::misc::yaw_add > 180.0f) globals::misc::yaw_add = -180.0f; break;
            }
            break;
        case 2:
            switch (item_selection) {
            case 0: globals::visuals::outline_enabled = !globals::visuals::outline_enabled; break;
            case 1: globals::visuals::visiblecheck = !globals::visuals::visiblecheck; break;
            case 2: globals::visuals::dynamic_fresnel_outline = !globals::visuals::dynamic_fresnel_outline; break;
            case 3: globals::visuals::crystal_chams_enabled = !globals::visuals::crystal_chams_enabled; break;
            case 4: globals::visuals::intensityvisibleoutline += 2.0f; if (globals::visuals::intensityvisibleoutline > 300.0f) globals::visuals::intensityvisibleoutline = 1.0f; break;
            case 5: globals::visuals::intensityinvisbleoutline += 2.0f; if (globals::visuals::intensityinvisbleoutline > 300.0f) globals::visuals::intensityinvisbleoutline = 1.0f; break;
            case 6: globals::visuals::GlowVisible += 10.0f; if (globals::visuals::GlowVisible > 500.0f) globals::visuals::GlowVisible = 10.0f; break;
            case 7: globals::visuals::GlowInvisible += 10.0f; if (globals::visuals::GlowInvisible > 500.0f) globals::visuals::GlowInvisible = 10.0f; break;
            }
            break;
        case 3:
            switch (item_selection) {
            case 0: globals::visuals::headb0x = !globals::visuals::headb0x; break;
            case 1: globals::visuals::sk3let0n = !globals::visuals::sk3let0n; break;
            case 2: globals::visuals::snapl1ne = !globals::visuals::snapl1ne; break;
            case 3: globals::visuals::h3althbar = !globals::visuals::h3althbar; break;
            case 4: globals::visuals::box2d = !globals::visuals::box2d; break;
            case 5: globals::visuals::box3d = !globals::visuals::box3d; break;
            case 6: globals::visuals::cornerbox = !globals::visuals::cornerbox; break;
            case 7: globals::visuals::agent_name = !globals::visuals::agent_name; break;
            case 8: globals::visuals::weaponesp = !globals::visuals::weaponesp; break;
            case 9: globals::visuals::chinese_hat = !globals::visuals::chinese_hat; break;
            case 10: globals::visuals::offscreen_esp = !globals::visuals::offscreen_esp; break;
            case 11: globals::visuals::bullet_tracers = !globals::visuals::bullet_tracers; break;
            }
            break;
        case 4:
            switch (item_selection) {
            case 0: globals::misc::skybox = !globals::misc::skybox; break;
            case 1: globals::misc::skyboxrgb = !globals::misc::skyboxrgb; break;
            case 2: globals::misc::world_esp = !globals::misc::world_esp; break;
            case 3: globals::misc::gadgets = !globals::misc::gadgets; break;
            }
            break;
        case 5:
            switch (item_selection) {
            case 0: globals::misc::sk1n_chang3r = !globals::misc::sk1n_chang3r; break;
            case 1: globals::misc::handchams = !globals::misc::handchams; break;
            case 2: globals::misc::bunnyhop = !globals::misc::bunnyhop; break;
            case 3: globals::misc::fastcrouch = !globals::misc::fastcrouch; break;
            case 4: globals::misc::antiflash = !globals::misc::antiflash; break;
            case 5: globals::misc::killsound = !globals::misc::killsound; break;
            case 6: globals::misc::killsays = !globals::misc::killsays; break;
            case 7: globals::misc::chat_spammer = !globals::misc::chat_spammer; break;
            case 8: globals::misc::tperson = !globals::misc::tperson; break;
            case 9: globals::misc::disconnect_server = !globals::misc::disconnect_server; break;
            }
            break;
        case 6:
            switch (item_selection) {
            case 0: globals::visuals::self_chams = !globals::visuals::self_chams; break;
            case 1: globals::visuals::self_galaxy_enabled = !globals::visuals::self_galaxy_enabled; break;
            case 2: globals::visuals::self_wireframe = !globals::visuals::self_wireframe; break;
            case 3: globals::visuals::chinese_hat_self = !globals::visuals::chinese_hat_self; break;
            case 4: globals::visuals::wireframe_hands = !globals::visuals::wireframe_hands; break;
            case 5: globals::visuals::wireframe_weapon = !globals::visuals::wireframe_weapon; break;
            }
            break;
        case 7:
            switch (item_selection) {
            case 0: save_config(); break;
            case 1: load_config(); break;
            case 2: break;
            }
            break;
        }
    }

    inline void handle_input() {
        if (!is_open) return;

        if (GetAsyncKeyState(VK_RIGHT) & 1) {
            if (selected_tab < category_count - 1) {
                selected_tab++;
                item_selection = 0;
            }
        }
        if (GetAsyncKeyState(VK_LEFT) & 1) {
            if (selected_tab > 0) {
                selected_tab--;
                item_selection = 0;
            }
        }
        if (GetAsyncKeyState(VK_DOWN) & 1) {
            if (item_selection < get_max_items() - 1) {
                item_selection++;
            }
        }
        if (GetAsyncKeyState(VK_UP) & 1) {
            if (item_selection > 0) {
                item_selection--;
            }
        }
        if (GetAsyncKeyState(VK_RETURN) & 1) {
            toggle_selected();
        }
    }
}