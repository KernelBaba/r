#include "hooks.hpp"
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <thread>
#include <random>
#include <ctime>
#include <mutex>
#include <windows.h>
#include <wininet.h>
#include <string>
#include <thread>
#include <chrono>
#include <map>
#include <sstream>
#include <iomanip>
#include <thread>
#include <wininet.h>
#pragma comment(lib, "wininet.lib")

#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "advapi32.lib")
#include <wininet.h>
#include <vector>
#include <string>
#pragma comment(lib, "wininet.lib")
#include <fstream>
#include <windows.h>
#include <shlobj.h>   
#include <string>
#include <stdexcept>
#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")


uworld* world;
uobject* class_private;
ashooterplayerstate* plste;
uskeletalmeshcomponent* mashe;
ashootercharacter* chara;


#include <windows.h>
#include <shlobj.h>
#include <string>
#include <fstream>
#include <vector>
#include <filesystem>
#include <sstream>
#include <algorithm>

namespace fs = std::filesystem;

std::string get_config_file_path() {
    return "C:\\Vacsen\\config.cfg";
}

void save_config() {
    std::string config_path = get_config_file_path();
    if (config_path.empty()) return;

    CreateDirectoryA("C:\\Vacsen", NULL);

    std::ofstream file(config_path, std::ios::binary);
    if (!file.is_open()) return;

    // Encrypted write functions
    auto write_bool = [&](int id, bool value) {
        file << id << "=" << (value ? "1" : "0") << "\n";
        };
    auto write_float = [&](int id, float value) {
        std::ostringstream oss;
        oss.imbue(std::locale::classic());
        oss << std::fixed << std::setprecision(6) << value;
        file << id << "=" << oss.str() << "\n";
        };
    auto write_int = [&](int id, int value) {
        file << id << "=" << value << "\n";
        };
    auto write_color = [&](int id, const flinearcolor& c) {
        file << id << "=" << c.r << "," << c.g << "," << c.b << "," << c.a << "\n";
        };
    auto write_string = [&](int id, const std::string& value) {
        file << id << "=" << value << "\n";
        };

    // Tab identifier
// Tab identifier
    file << "0=1\n"; // Config version/tab map

    // Aimbot (IDs 100-199)
    write_bool(100, globals::aimbot::a1mbot);
    write_bool(101, globals::aimbot::v1sh_ch3ck);
    write_bool(102, globals::aimbot::reco1l_contr0l);
    write_bool(103, globals::aimbot::spread_comp);
    write_bool(104, globals::aimbot::autoshot);
    write_bool(105, globals::aimbot::enable_360_fov);
    write_bool(106, globals::aimbot::spreadempty_comp);
    write_bool(107, globals::aimbot::pvc);
    write_bool(112, globals::aimbot::draw_f0v);
    write_bool(113, globals::aimbot::auto_scope);
    write_bool(114, globals::aimbot::aim_assist);
    write_bool(121, globals::aimbot::vsr); // NEW: Advanced Resolver
    write_float(108, globals::aimbot::a1m_sm00th);
    write_float(109, globals::aimbot::a1m_f0v);
    write_float(115, globals::aimbot::spread_comp_delay);
    write_float(116, globals::aimbot::autoshoot_delay);
    write_float(117, globals::aimbot::min_damage);
    write_float(118, globals::aimbot::max_aim_distance);
    write_int(110, globals::aimbot::a1m_b0ne);
    write_int(111, globals::aimbot::a1m_k3y);
    write_int(119, globals::aimbot::target_selection);
    write_int(120, globals::aimbot::auto_fire_mode);

    // Triggerbot (IDs 200-299)
    write_bool(200, globals::tr1g::onne);
    write_bool(201, globals::tr1g::v1sh_ch3ck);
    write_float(202, globals::tr1g::tr1g_f0v);

    // Anti-Aim (IDs 300-399)
    write_bool(300, globals::misc::aa);
    write_bool(301, globals::misc::spinner);
    write_bool(302, globals::misc::rpl);
    write_bool(308, globals::misc::fakeduck);
    write_bool(309, globals::misc::jitter_move);
    write_bool(310, globals::misc::pitch_enabled);
    write_bool(311, globals::misc::jitter_on_back);
    write_bool(312, globals::misc::jitter_enabled);
    write_bool(313, globals::misc::manual_aa);
    write_bool(314, globals::misc::freestanding);
    write_bool(315, globals::misc::atomic_aa);
    write_bool(316, globals::misc::prediction_breaker);
    write_bool(322, globals::misc::aa_spin); // NEW: AA spin
    write_bool(323, globals::misc::aa_jitter); // NEW: AA jitter
    write_bool(324, globals::misc::aa_threeway); // NEW: AA threeway
    write_bool(325, globals::misc::aa_desync); // NEW: AA desync
    write_int(303, globals::misc::aa_mode);
    write_int(317, globals::misc::atomic_mode);
    write_float(304, globals::misc::spinvalue);
    write_float(305, globals::misc::jitter_range);
    write_float(306, globals::misc::desync_range);
    write_float(307, globals::misc::fake_lag_ticks);
    write_float(318, globals::misc::pitch_value);
    write_float(319, globals::misc::yaw_add);
    write_float(320, globals::misc::atomic_speed);
    write_float(321, globals::misc::breaker_intensity);

    // Visuals (IDs 400-499)
    write_bool(400, globals::visuals::outline_enabled);
    write_bool(429, globals::visuals::self_galaxy_enabled);
    write_bool(430, globals::visuals::self_wireframe);
    write_bool(431, globals::visuals::chinese_hat_self);
    write_bool(432, globals::visuals::visible_check_ch);
    write_bool(433, globals::visuals::dynamic_fresnel_outline);
    write_bool(434, globals::visuals::galaxy_gun);
    write_bool(435, globals::visuals::dormant);
    write_bool(436, globals::visuals::agent_name);
    write_bool(437, globals::visuals::weaponesp);
    write_bool(438, globals::visuals::HealthText);
    write_bool(439, globals::visuals::chamsvsbd);
    write_bool(440, globals::visuals::bullet_tracers);
    write_bool(461, globals::visuals::crystal_chams_enabled); // NEW: Crystal Outline Self/Hand
    write_bool(401, globals::visuals::visiblecheck);
    write_bool(402, globals::visuals::box3d);
    write_bool(403, globals::visuals::box2d);
    write_bool(404, globals::visuals::cornerbox);
    write_bool(405, globals::visuals::dstc);
    write_bool(406, globals::visuals::snapl1ne);
    write_bool(407, globals::visuals::sk3let0n);
    write_bool(408, globals::visuals::agenticon);
    write_bool(409, globals::visuals::h3althbar);
    write_bool(410, globals::visuals::chinese_hat);
    write_bool(411, globals::visuals::headb0x);
    write_bool(412, globals::visuals::chamsvsb);
    write_bool(413, globals::visuals::chams);
    write_bool(414, globals::visuals::rainbow_chams);
    write_bool(415, globals::visuals::self_chams);
    write_bool(416, globals::visuals::wireframe_hands);
    write_bool(417, globals::visuals::wireframe_weapon);
    write_bool(418, globals::visuals::outline);
    write_float(419, globals::visuals::chams_intensity);
    write_float(420, globals::visuals::glow_intensity);
    write_float(421, globals::visuals::intensityvisibleoutline);
    write_float(422, globals::visuals::GlowVisible);
    write_float(423, globals::visuals::intensityinvisbleoutline);
    write_float(424, globals::visuals::GlowInvisible);
    write_float(441, globals::visuals::Self_CenterEdgeR);
    write_float(442, globals::visuals::Self_CenterEdgeG);
    write_float(443, globals::visuals::Self_CenterEdgeB);
    write_float(444, globals::visuals::Self_InnerEdgeR);
    write_float(445, globals::visuals::Self_InnerEdgeG);
    write_float(446, globals::visuals::Self_InnerEdgeB);
    write_float(447, globals::visuals::Self_OuterEdgeR);
    write_float(448, globals::visuals::Self_OuterEdgeG);
    write_float(449, globals::visuals::Self_OuterEdgeB);
    write_float(450, globals::visuals::InnerEdgeThickness);
    write_float(451, globals::visuals::OuterEdgeThickness);
    write_float(452, globals::visuals::RimPower);
    write_float(453, globals::visuals::RimMultiply);
    write_float(454, globals::visuals::RimFresnel);
    write_float(455, globals::visuals::OcclusionState);
    write_float(456, globals::visuals::OcclusionBehindWall);
    write_float(462, globals::visuals::outlineintensityvisibleoutline); // NEW: Outline intensity visible
    write_float(463, globals::visuals::outlineintensityinvisbleoutline); // NEW: Outline intensity invisible
    write_int(425, globals::visuals::outlinetype);
    write_int(426, globals::visuals::visible_color_preset);
    write_int(427, globals::visuals::invisible_color_preset);
    write_int(428, globals::visuals::usepresetedoutlines);
    write_int(457, globals::visuals::self_galaxy_preset);
    write_int(458, globals::visuals::dynamic_fresnel_preset);
    write_int(459, globals::visuals::visiblepreset);
    write_int(460, globals::visuals::invisiblepreset);
    write_int(464, globals::visuals::crystal_chams_preset); // NEW: Crystal chams preset

    // World/Skybox (IDs 500-599)
    write_bool(500, globals::misc::skybox);
    write_bool(501, globals::misc::skyboxrgb);
    write_bool(502, globals::misc::gdg);
    write_bool(503, globals::misc::spktimer);
    write_bool(504, globals::misc::cpp);
    write_bool(505, globals::misc::world_esp);
    write_bool(506, globals::misc::gadgets);
    write_int(507, globals::misc::skybox_preset_index);

    // Misc (IDs 600-699)
    write_bool(600, globals::misc::playerchamsself);
    write_bool(601, globals::misc::sk1n_chang3r);
    write_bool(602, globals::misc::customgun);
    write_bool(603, globals::misc::rmsdw);
    write_bool(604, globals::misc::BigGun3p);
    write_bool(605, globals::misc::BigSelf);
    write_bool(606, globals::misc::finisher);
    write_bool(607, globals::misc::onlylastkill);
    write_bool(608, globals::misc::killsound);
    write_bool(609, globals::misc::killsays);
    write_bool(610, globals::misc::chat_spammer);
    write_bool(611, globals::misc::aspect_ratio_enabled);
    write_bool(612, globals::misc::tperson);
    write_bool(613, globals::misc::FovChangor);
    write_bool(614, globals::misc::handchams);
    write_bool(615, globals::misc::bunnyhop);
    write_bool(616, globals::misc::fastcrouch);
    write_bool(617, globals::misc::antiflash);
    write_bool(618, globals::misc::disconnect_server);
    write_bool(633, globals::misc::hand_outline);
    write_bool(634, globals::misc::handchamsd2);
    write_bool(635, globals::misc::handchams2);
    write_bool(636, globals::misc::ath);
    write_bool(637, globals::misc::hitsound);
    write_bool(638, globals::misc::rdy); // NEW: Gun Materials
    write_bool(639, globals::misc::nld);
    write_bool(640, globals::misc::ht23); // NEW: Hit Priority
    write_int(641, globals::misc::killsound_selection);

    write_float(619, globals::misc::Fovchangerfloat);
    write_float(620, globals::misc::PlayerDistance);
    write_float(621, globals::misc::aspect_ratio_value);
    write_float(622, globals::misc::arm_width);
    write_float(623, globals::misc::arm_height);
    write_float(624, globals::misc::arm_length);
    write_float(625, globals::misc::weapon_width);
    write_float(626, globals::misc::weapon_height);
    write_float(627, globals::misc::weapon_length);
    write_float(628, globals::misc::ui_scale);
    write_float(642, globals::misc::handchams_intensity);
    write_float(643, globals::misc::weapon_z);
    write_float(644, globals::misc::arm_width_inspect);
    write_float(645, globals::misc::arm_height_inspect);
    write_float(646, globals::misc::arm_length_inspect);
    write_float(647, globals::misc::weapon_width_inspect);
    write_float(648, globals::misc::weapon_height_inspect);
    write_float(649, globals::misc::weapon_length_inspect);
    write_float(650, globals::misc::weapon_x_inspect);
    write_float(651, globals::misc::weapon_y_inspect);
    write_float(652, globals::misc::weapon_z_inspect);
    write_float(653, globals::misc::rifle_x_inspect);
    write_float(654, globals::misc::rifle_y_inspect);
    write_float(655, globals::misc::knife_width);
    write_float(656, globals::misc::knife_height);
    write_float(657, globals::misc::knife_length);
    write_float(658, globals::misc::knife_x);
    write_float(659, globals::misc::knife_y);
    write_float(660, globals::misc::knife_z);

    write_int(629, globals::misc::kky);
    write_int(630, globals::misc::chams_material_index);
    write_int(631, globals::misc::enemy_chams_material_index);
    write_int(661, globals::misc::handchams_material_index1);

    write_string(632, globals::misc::chat_message);

    write_bool(673, globals::misc::freecam_enabled);
    write_float(674, globals::misc::freecam_speed);
    write_int(675, globals::misc::freecam_key);
    write_bool(676, globals::misc::ViewModelChanger);

    // Colors (IDs 700-799)
    write_color(700, globals::misc::Horizon);
    write_color(701, globals::misc::Overall);
    write_color(702, globals::misc::Zenith);
    write_color(703, globals::misc::Cloud);
    write_color(704, globals::misc::SkySunColor);
    write_color(705, globals::misc::handchams_color);
    write_color(706, globals::visuals::chams_color);

    // Buddy (IDs 800-899)
    write_bool(800, globals::buddy::enabled);
    write_int(801, globals::buddy::index);

    // Insta Lock (IDs 900-999)
    write_bool(900, globals::il::enable);
    write_int(901, globals::il::lock_agent);

    file.close();
}

void load_config() {
    std::string config_path = get_config_file_path();
    if (config_path.empty()) return;

    std::ifstream file(config_path);
    if (!file.is_open()) return;

    std::string line;

    auto parse_bool = [](const std::string& v) { return v == "1"; };
    auto parse_float = [](const std::string& v) {
        std::istringstream iss(v);
        iss.imbue(std::locale::classic());
        float result = 0.0f;
        iss >> result;
        return result;
        };
    auto parse_int = [](const std::string& v) { return std::stoi(v); };
    auto parse_color = [](const std::string& v, flinearcolor& c) {
        std::stringstream ss(v);
        std::string item;
        float rgba[4];
        for (int i = 0; i < 4 && std::getline(ss, item, ','); ++i)
            rgba[i] = std::stof(item);
        c = { rgba[0], rgba[1], rgba[2], rgba[3] };
        };
    auto parse_string = [](const std::string& v) { return v; };

    while (std::getline(file, line)) {
        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
        if (line.empty()) continue;

        size_t delim = line.find('=');
        if (delim == std::string::npos) continue;

        std::string key_str = line.substr(0, delim);
        std::string val = line.substr(delim + 1);

        try {
            int key = std::stoi(key_str);

            switch (key) {
                // Aimbot
            case 100: globals::aimbot::a1mbot = parse_bool(val); break;
            case 101: globals::aimbot::v1sh_ch3ck = parse_bool(val); break;
            case 102: globals::aimbot::reco1l_contr0l = parse_bool(val); break;
            case 103: globals::aimbot::spread_comp = parse_bool(val); break;
            case 104: globals::aimbot::autoshot = parse_bool(val); break;
            case 105: globals::aimbot::enable_360_fov = parse_bool(val); break;
            case 106: globals::aimbot::spreadempty_comp = parse_bool(val); break;
            case 107: globals::aimbot::pvc = parse_bool(val); break;
            case 112: globals::aimbot::draw_f0v = parse_bool(val); break;
            case 113: globals::aimbot::auto_scope = parse_bool(val); break;
            case 114: globals::aimbot::aim_assist = parse_bool(val); break;
            case 121: globals::aimbot::vsr = parse_bool(val); break; // NEW: Advanced Resolver
            case 108: globals::aimbot::a1m_sm00th = parse_float(val); break;
            case 109: globals::aimbot::a1m_f0v = parse_float(val); break;
            case 115: globals::aimbot::spread_comp_delay = parse_float(val); break;
            case 116: globals::aimbot::autoshoot_delay = parse_float(val); break;
            case 117: globals::aimbot::min_damage = parse_float(val); break;
            case 118: globals::aimbot::max_aim_distance = parse_float(val); break;
            case 110: globals::aimbot::a1m_b0ne = parse_int(val); break;
            case 111: globals::aimbot::a1m_k3y = parse_int(val); break;
            case 119: globals::aimbot::target_selection = parse_int(val); break;
            case 120: globals::aimbot::auto_fire_mode = parse_int(val); break;

                // Triggerbot
            case 200: globals::tr1g::onne = parse_bool(val); break;
            case 201: globals::tr1g::v1sh_ch3ck = parse_bool(val); break;
            case 202: globals::tr1g::tr1g_f0v = parse_float(val); break;

                // Anti-Aim
            case 300: globals::misc::aa = parse_bool(val); break;
            case 301: globals::misc::spinner = parse_bool(val); break;
            case 302: globals::misc::rpl = parse_bool(val); break;
            case 308: globals::misc::fakeduck = parse_bool(val); break;
            case 309: globals::misc::jitter_move = parse_bool(val); break;
            case 310: globals::misc::pitch_enabled = parse_bool(val); break;
            case 311: globals::misc::jitter_on_back = parse_bool(val); break;
            case 312: globals::misc::jitter_enabled = parse_bool(val); break;
            case 313: globals::misc::manual_aa = parse_bool(val); break;
            case 314: globals::misc::freestanding = parse_bool(val); break;
            case 315: globals::misc::atomic_aa = parse_bool(val); break;
            case 316: globals::misc::prediction_breaker = parse_bool(val); break;
            case 322: globals::misc::aa_spin = parse_bool(val); break; // NEW: AA spin
            case 323: globals::misc::aa_jitter = parse_bool(val); break; // NEW: AA jitter
            case 324: globals::misc::aa_threeway = parse_bool(val); break; // NEW: AA threeway
            case 325: globals::misc::aa_desync = parse_bool(val); break; // NEW: AA desync
            case 303: globals::misc::aa_mode = parse_int(val); break;
            case 317: globals::misc::atomic_mode = parse_int(val); break;
            case 304: globals::misc::spinvalue = parse_float(val); break;
            case 305: globals::misc::jitter_range = parse_float(val); break;
            case 306: globals::misc::desync_range = parse_float(val); break;
            case 307: globals::misc::fake_lag_ticks = parse_float(val); break;
            case 318: globals::misc::pitch_value = parse_float(val); break;
            case 319: globals::misc::yaw_add = parse_float(val); break;
            case 320: globals::misc::atomic_speed = parse_float(val); break;
            case 321: globals::misc::breaker_intensity = parse_float(val); break;

                // Visuals
            case 400: globals::visuals::outline_enabled = parse_bool(val); break;
            case 429: globals::visuals::self_galaxy_enabled = parse_bool(val); break;
            case 430: globals::visuals::self_wireframe = parse_bool(val); break;
            case 431: globals::visuals::chinese_hat_self = parse_bool(val); break;
            case 432: globals::visuals::visible_check_ch = parse_bool(val); break;
            case 433: globals::visuals::dynamic_fresnel_outline = parse_bool(val); break;
            case 434: globals::visuals::galaxy_gun = parse_bool(val); break;
            case 435: globals::visuals::dormant = parse_bool(val); break;
            case 436: globals::visuals::agent_name = parse_bool(val); break;
            case 437: globals::visuals::weaponesp = parse_bool(val); break;
            case 438: globals::visuals::HealthText = parse_bool(val); break;
            case 439: globals::visuals::chamsvsbd = parse_bool(val); break;
            case 440: globals::visuals::bullet_tracers = parse_bool(val); break;
            case 461: globals::visuals::crystal_chams_enabled = parse_bool(val); break; // NEW: Crystal Outline Self/Hand
            case 401: globals::visuals::visiblecheck = parse_bool(val); break;
            case 402: globals::visuals::box3d = parse_bool(val); break;
            case 403: globals::visuals::box2d = parse_bool(val); break;
            case 404: globals::visuals::cornerbox = parse_bool(val); break;
            case 405: globals::visuals::dstc = parse_bool(val); break;
            case 406: globals::visuals::snapl1ne = parse_bool(val); break;
            case 407: globals::visuals::sk3let0n = parse_bool(val); break;
            case 408: globals::visuals::agenticon = parse_bool(val); break;
            case 409: globals::visuals::h3althbar = parse_bool(val); break;
            case 410: globals::visuals::chinese_hat = parse_bool(val); break;
            case 411: globals::visuals::headb0x = parse_bool(val); break;
            case 412: globals::visuals::chamsvsb = parse_bool(val); break;
            case 413: globals::visuals::chams = parse_bool(val); break;
            case 414: globals::visuals::rainbow_chams = parse_bool(val); break;
            case 415: globals::visuals::self_chams = parse_bool(val); break;
            case 416: globals::visuals::wireframe_hands = parse_bool(val); break;
            case 417: globals::visuals::wireframe_weapon = parse_bool(val); break;
            case 418: globals::visuals::outline = parse_bool(val); break;
            case 419: globals::visuals::chams_intensity = parse_float(val); break;
            case 420: globals::visuals::glow_intensity = parse_float(val); break;
            case 421: globals::visuals::intensityvisibleoutline = parse_float(val); break;
            case 422: globals::visuals::GlowVisible = parse_float(val); break;
            case 423: globals::visuals::intensityinvisbleoutline = parse_float(val); break;
            case 424: globals::visuals::GlowInvisible = parse_float(val); break;
            case 441: globals::visuals::Self_CenterEdgeR = parse_float(val); break;
            case 442: globals::visuals::Self_CenterEdgeG = parse_float(val); break;
            case 443: globals::visuals::Self_CenterEdgeB = parse_float(val); break;
            case 444: globals::visuals::Self_InnerEdgeR = parse_float(val); break;
            case 445: globals::visuals::Self_InnerEdgeG = parse_float(val); break;
            case 446: globals::visuals::Self_InnerEdgeB = parse_float(val); break;
            case 447: globals::visuals::Self_OuterEdgeR = parse_float(val); break;
            case 448: globals::visuals::Self_OuterEdgeG = parse_float(val); break;
            case 449: globals::visuals::Self_OuterEdgeB = parse_float(val); break;
            case 450: globals::visuals::InnerEdgeThickness = parse_float(val); break;
            case 451: globals::visuals::OuterEdgeThickness = parse_float(val); break;
            case 452: globals::visuals::RimPower = parse_float(val); break;
            case 453: globals::visuals::RimMultiply = parse_float(val); break;
            case 454: globals::visuals::RimFresnel = parse_float(val); break;
            case 455: globals::visuals::OcclusionState = parse_float(val); break;
            case 456: globals::visuals::OcclusionBehindWall = parse_float(val); break;
            case 462: globals::visuals::outlineintensityvisibleoutline = parse_float(val); break; // NEW: Outline intensity visible
            case 463: globals::visuals::outlineintensityinvisbleoutline = parse_float(val); break; // NEW: Outline intensity invisible
            case 425: globals::visuals::outlinetype = parse_int(val); break;
            case 426: globals::visuals::visible_color_preset = parse_int(val); break;
            case 427: globals::visuals::invisible_color_preset = parse_int(val); break;
            case 428: globals::visuals::usepresetedoutlines = parse_int(val); break;
            case 457: globals::visuals::self_galaxy_preset = parse_int(val); break;
            case 458: globals::visuals::dynamic_fresnel_preset = parse_int(val); break;
            case 459: globals::visuals::visiblepreset = parse_int(val); break;
            case 460: globals::visuals::invisiblepreset = parse_int(val); break;
            case 464: globals::visuals::crystal_chams_preset = parse_int(val); break; // NEW: Crystal chams preset

                // World/Skybox
            case 500: globals::misc::skybox = parse_bool(val); break;
            case 501: globals::misc::skyboxrgb = parse_bool(val); break;
            case 502: globals::misc::gdg = parse_bool(val); break;
            case 503: globals::misc::spktimer = parse_bool(val); break;
            case 504: globals::misc::cpp = parse_bool(val); break;
            case 505: globals::misc::world_esp = parse_bool(val); break;
            case 506: globals::misc::gadgets = parse_bool(val); break;
            case 507: globals::misc::skybox_preset_index = parse_int(val); break;

                // Misc
            case 600: globals::misc::playerchamsself = parse_bool(val); break;
            case 601: globals::misc::sk1n_chang3r = parse_bool(val); break;
            case 602: globals::misc::customgun = parse_bool(val); break;
            case 603: globals::misc::rmsdw = parse_bool(val); break;
            case 604: globals::misc::BigGun3p = parse_bool(val); break;
            case 605: globals::misc::BigSelf = parse_bool(val); break;
            case 606: globals::misc::finisher = parse_bool(val); break;
            case 607: globals::misc::onlylastkill = parse_bool(val); break;
            case 608: globals::misc::killsound = parse_bool(val); break;
            case 609: globals::misc::killsays = parse_bool(val); break;
            case 610: globals::misc::chat_spammer = parse_bool(val); break;
            case 611: globals::misc::aspect_ratio_enabled = parse_bool(val); break;
            case 612: globals::misc::tperson = parse_bool(val); break;
            case 613: globals::misc::FovChangor = parse_bool(val); break;
            case 614: globals::misc::handchams = parse_bool(val); break;
            case 615: globals::misc::bunnyhop = parse_bool(val); break;
            case 616: globals::misc::fastcrouch = parse_bool(val); break;
            case 617: globals::misc::antiflash = parse_bool(val); break;
            case 618: globals::misc::disconnect_server = parse_bool(val); break;
            case 633: globals::misc::hand_outline = parse_bool(val); break;
            case 634: globals::misc::handchamsd2 = parse_bool(val); break;
            case 635: globals::misc::handchams2 = parse_bool(val); break;
            case 636: globals::misc::ath = parse_bool(val); break;
            case 637: globals::misc::hitsound = parse_bool(val); break;
            case 638: globals::misc::rdy = parse_bool(val); break; // NEW: Gun Materials
            case 639: globals::misc::nld = parse_bool(val); break;
            case 640: globals::misc::ht23 = parse_bool(val); break; // NEW: Hit Priority
            case 641: globals::misc::killsound_selection = parse_int(val); break;

            case 619: globals::misc::Fovchangerfloat = parse_float(val); break;
            case 620: globals::misc::PlayerDistance = parse_float(val); break;
            case 621: globals::misc::aspect_ratio_value = parse_float(val); break;
            case 622: globals::misc::arm_width = parse_float(val); break;
            case 623: globals::misc::arm_height = parse_float(val); break;
            case 624: globals::misc::arm_length = parse_float(val); break;
            case 625: globals::misc::weapon_width = parse_float(val); break;
            case 626: globals::misc::weapon_height = parse_float(val); break;
            case 627: globals::misc::weapon_length = parse_float(val); break;
            case 628: globals::misc::ui_scale = parse_float(val); break;
            case 642: globals::misc::handchams_intensity = parse_float(val); break;
            case 643: globals::misc::weapon_z = parse_float(val); break;
            case 644: globals::misc::arm_width_inspect = parse_float(val); break;
            case 645: globals::misc::arm_height_inspect = parse_float(val); break;
            case 646: globals::misc::arm_length_inspect = parse_float(val); break;
            case 647: globals::misc::weapon_width_inspect = parse_float(val); break;
            case 648: globals::misc::weapon_height_inspect = parse_float(val); break;
            case 649: globals::misc::weapon_length_inspect = parse_float(val); break;
            case 650: globals::misc::weapon_x_inspect = parse_float(val); break;
            case 651: globals::misc::weapon_y_inspect = parse_float(val); break;
            case 652: globals::misc::weapon_z_inspect = parse_float(val); break;
            case 653: globals::misc::rifle_x_inspect = parse_float(val); break;
            case 654: globals::misc::rifle_y_inspect = parse_float(val); break;
            case 655: globals::misc::knife_width = parse_float(val); break;
            case 656: globals::misc::knife_height = parse_float(val); break;
            case 657: globals::misc::knife_length = parse_float(val); break;
            case 658: globals::misc::knife_x = parse_float(val); break;
            case 659: globals::misc::knife_y = parse_float(val); break;
            case 660: globals::misc::knife_z = parse_float(val); break;

            case 629: globals::misc::kky = parse_int(val); break;
            case 630: globals::misc::chams_material_index = parse_int(val); break;
            case 631: globals::misc::enemy_chams_material_index = parse_int(val); break;
            case 661: globals::misc::handchams_material_index1 = parse_int(val); break;

            case 632: globals::misc::chat_message = parse_string(val); break;

            case 673: globals::misc::freecam_enabled = parse_bool(val); break;
            case 674: globals::misc::freecam_speed = parse_float(val); break;
            case 675: globals::misc::freecam_key = parse_int(val); break;
            case 676: globals::misc::ViewModelChanger = parse_bool(val); break;

                // Colors
            case 700: parse_color(val, globals::misc::Horizon); break;
            case 701: parse_color(val, globals::misc::Overall); break;
            case 702: parse_color(val, globals::misc::Zenith); break;
            case 703: parse_color(val, globals::misc::Cloud); break;
            case 704: parse_color(val, globals::misc::SkySunColor); break;
            case 705: parse_color(val, globals::misc::handchams_color); break;
            case 706: parse_color(val, globals::visuals::chams_color); break;

                // Buddy
            case 800: globals::buddy::enabled = parse_bool(val); break;
            case 801: globals::buddy::index = parse_int(val); break;

                // Insta Lock
            case 900: globals::il::enable = parse_bool(val); break;
            case 901: globals::il::lock_agent = parse_int(val); break;
            }
        }
        catch (...) {
            // Hata durumunda sessizce devam et
        }
    }
    file.close();
}
namespace AntiAimFireHook
{
    static void* OriginalGetFiringLocation = nullptr;

    static void __fastcall HookedGetFiringLocation(ashootercharacter* actor, fvector* loc, fvector* rot, bool apply_recoil)
    {
        reinterpret_cast<void(__fastcall*)(ashootercharacter*, fvector*, fvector*, bool)>(OriginalGetFiringLocation)(actor, loc, rot, apply_recoil);

        if (globals::misc::spinner && globals::misc::aaEnabled && actor->is_alive()) {
            rot->y = globals::misc::fakeYaw;
        }
    }

    static void InitializeHook()
    {
        static bool hook_initialized = false;
        if (!hook_initialized) {
            uint64_t target_addr = memory::module_base + 0x3BF2000;
            OriginalGetFiringLocation = (void*)target_addr;


            memory::write<uint64_t>(target_addr, (uint64_t)&HookedGetFiringLocation);

            hook_initialized = true;
        }   
    }
}

void MainLoopFunction()
{

    static bool hook_initialized = false;
    if (!hook_initialized) {
        AntiAimFireHook::InitializeHook();
        hook_initialized = true;
    }


}

static std::mutex materials_mutex;
static bool materials_initialized = false;
static uobject* hand_materials[51] = { nullptr };
static uobject* hand_wfs[8] = { nullptr };
static uobject* gun_materials[51] = { nullptr };
static uobject* gun_wfs[8] = { nullptr };
static uobject* epl_wfs[17] = { nullptr };
static uobject* a_mts[50] = { nullptr };
static uskeletalmeshcomponent* c_ctm[72] = { nullptr };
static uskeletalmeshcomponent* c1_ctm[60] = { nullptr };
static uskeletalmeshcomponent* h_ctm[32] = { nullptr };
static uskeletalmeshcomponent* e_ctm[32] = { nullptr };
//static uskeletalmeshcomponent* g_ctm[1] = { nullptr };
static uobject* r_ctm[13] = { nullptr };
static uanimationasset* va_ctm[1] = { nullptr };

struct WeaponCosmetics {
    int16_t lmk_selection = 0;
    int16_t cm3_selection = 0;
    int16_t cm33_selection = 0;
    int16_t cm55_selection = 0;
    int16_t skin_selection = 0;
};

struct SkinData {
    const wchar_t* SkinName;
    const wchar_t* skin;
    const wchar_t* chroma;
    int level;
};


static const std::vector<SkinData> vandalSkins = {
    {L"Phaseguard Vandal", L"Default__AK_Commando_PrimaryAsset_C", L"Default__Commando_v1_PrimaryAsset_C", 4},
    {L"Divergence V4ndal", L"Default__AK_Anomaly_PrimaryAsset_C", L"Default__Anomaly_v1_PrimaryAsset_C", 4},
    {L"CYRAX Vandal", L"Default__AK_Syndra_PrimaryAsset_C", L"Default__Syndra_v1_PrimaryAsset_C", 4},
    {L"Primordium Vandal", L"Default__AK_Hellfire_PrimaryAsset_C", L"Default__Hellfire_v2_PrimaryAsset_C", 4},
    {L"Singularity Vandal", L"Default__AK_Edge2_PrimaryAsset_C", L"Default__AK_Edge2_v1_PrimaryAsset_C", 4},
    {L"Aemondir Vandal", L"Default__AK_Legion_PrimaryAsset_C", L"Default__AK_Legion_Lv3_PrimaryAsset_C", 4},
    {L"Evori Dreamwings Vandal", L"Default__AK_StarPower_PrimaryAsset_C", L"Default__StarPower_v3_PrimaryAsset_C", 4},
    {L"Prelude to Chaos Vandal", L"Default__AK_DemonStone_PrimaryAsset_C", L"Default__AK_DemonStone_Lv4_PrimaryAsset_C", 4},
    {L"Reaver Vandal", L"Default__AK_Soulstealer_PrimaryAsset_C", L"Default__AK_Soulstealer_White_PrimaryAsset_C", 4},
    {L"XERØFANG Vandal ", L"Default__AK_Hypedragon_PrimaryAsset_C", L"Default__AK_Hypedragon_v1_PrimaryAsset_C", 4},
    {L"Kuronami Vandal", L"Default__AK_Ninja_PrimaryAsset_C", L"Default__AK_Ninja_v1_PrimaryAsset_C", 4},
    {L"Imperium Vandal", L"Default__AK_Dynasty_PrimaryAsset_C", L"Default__AK_Dynasty_Standard_PrimaryAsset_C", 4},
    {L"Champions 2023 Vandal", L"Default__AK_Champions2023_PrimaryAsset_C", L"Default__AK_Champions2023_Standard_PrimaryAsset_C", 4},
    {L"Magepunk Vandal", L"Default__AK_Magepunk3_PrimaryAsset_C", L"Default__AK_Magepunk3_Standard_PrimaryAsset_C", 4},
    {L"Gaia's Vengeance Vandal", L"Default__AK_Ashen_PrimaryAsset_C", L"Default__AK_Ashen_v2_PrimaryAsset_C", 4},
    {L"RGX 11z Pro Vandal", L"Default__AK_Afterglow_PrimaryAsset_C", L"Default__AK_Afterglow_Blue_PrimaryAsset_C", 5},
    {L"Champions 2021 Vandal", L"Default__AK_Champions_PrimaryAsset_C", L"Default__AK_Champions_Lv4_PrimaryAsset_C", 4},
    {L"Elderflame Vandal", L"Default__AK_Dragon_PrimaryAsset_C", L"Default__AK_Dragon_Blue_PrimaryAsset_C", 4},
    {L"Ion Vandal", L"Default__AK_Oblivion2_PrimaryAsset_C", L"Default__AK_Oblivion2_v1_PrimaryAsset_C", 4},
    {L"ChronoVoid Vandal", L"Default__AK_Daedalus_PrimaryAsset_C", L"Default__AK_Daedalus_v2_PrimaryAsset_C", 4},
    {L"Araxys Vandal", L"Default__AK_Antares_PrimaryAsset_C", L"Default__AK_Antares_Lv4_PrimaryAsset_C", 4},
    {L"Origin Vandal", L"Default__AK_Circle_PrimaryAsset_C", L"Default__AK_Circle_Lv4_PrimaryAsset_C",4},
    {L"Sentinels of Light Vandal", L"Default__AK_SOL_PrimaryAsset_C", L"Default__AK_SOL_Lv4_PrimaryAsset_C", 4},
    {L"Glitchpop Vandal", L"Default__AK_Cyberpunk2_PrimaryAsset_C", L"Default__AK_Cyberpunk2_Red_PrimaryAsset_C", 4},
    {L"Prime Vandal", L"Default__AssaultRifle_AK_HypeBeast_PrimaryAsset_C", L"Default__AssaultRifle_AK_HypeBeast_Blue_PrimaryAsset_C", 4},
    {L"Oni Vandal", L"Default__AK_Oni2_PrimaryAsset_C", L"Default__AK_Oni2_Lv4_PrimaryAsset_C", 4},
    {L"Overdrive Vandal", L"Default__AK_Motorbike_PrimaryAsset_C", L"Default__Motorbike_v2_PrimaryAsset_C", 4},
    {L"EX.O Vandal", L"Default__AK_Hologram_PrimaryAsset_C", L"Default__Hologram_v3_PrimaryAsset_C", 4},
    {L"Valiant Hero Vandal", L"Default__AK_MonkeyKing_PrimaryAsset_C", L"Default__MonkeyKing_v1_PrimaryAsset_C", 4},
    {L"Cryostasis Vandal", L"Default__AK_Permafrost_PrimaryAsset_C", L"Default__Permafrost_v1_PrimaryAsset_C", 4},
    {L"Forsaken Vandal", L"Default__AK_Fallen_PrimaryAsset_C", L"Default__Fallen_v2_PrimaryAsset_C", 4},

};
static const std::vector<SkinData> phantomSkins = {

{L"Bolt Phantom", L"Default__Carbine_Bolt_PrimaryAsset_C", L"Default__Carbine_Bolt_v1_PrimaryAsset_C", 4},
{L"Nocturnum Phantom", L"Default__Carbine_Coven_PrimaryAsset_C", L"Default__Carbine_Coven_V1_PrimaryAsset_C", 4},
{L"Champions 2024 Phantom", L"Default__Carbine_Champions2024_PrimaryAsset_C", L"Default__Carbine_Champions2024_Lv4_PrimaryAsset_C", 4},
{L"Mystbloom Phantom", L"Default__Carbine_Spirit_PrimaryAsset_C", L"Default__Carbine_Spirit_v2_PrimaryAsset_C", 4},
{L"Sovereign Phantom", L"Default__Carbine_Sovereign2_PrimaryAsset_C", L"Default__Carbine_Sovereign2_v1_PrimaryAsset_C", 4},
{L"Singularity Phantom", L"Default__AssaultRifle_ACR_Edge_PrimaryAsset_C", L"Default__AssaultRifle_ACR_Edge_Lv4_PrimaryAsset_C", 4},
{L"Spectrum Phantom", L"Default__Carbine_Atlas_PrimaryAsset_C", L"Default__Carbine_Atlas_v1_PrimaryAsset_C", 4},
{L"Reaver Phantom", L"Default__Carbine_Soulstealer2_PrimaryAsset_C", L"Default__Carbine_Soulstealer2_v1_PrimaryAsset_C", 4},
{L"RGX 11z Pro Phantom", L"Default__Carbine_Afterglow2_PrimaryAsset_C", L"Default__Carbine_Afterglow2_v2_PrimaryAsset_C", 4},
{L"Glitchpop Phantom", L"Default__Carbine_Cyberpunk2_PrimaryAsset_C", L"Default__Carbine_Cyberpunk2_Lv4_PrimaryAsset_C", 4},
{L"Ruination Phantom", L"Default__Carbine_King_PrimaryAsset_C", L"Default__Carbine_King_Lv4_PrimaryAsset_C", 4},
{L"ChronoVoid Phantom", L"Default__Carbine_Daedalus_PrimaryAsset_C", L"Default__Carbine_Daedalus_Lv4_PrimaryAsset_C", 4},
{L"Recon Phantom", L"Default__Carbine_SpecOps_PrimaryAsset_C", L"Default__Carbine_SpecOps_Lv4_PrimaryAsset_C", 4},
{L"BlastX Phantom", L"Default__Carbine_URF_PrimaryAsset_C", L"Default__Carbine_URF_Lv4_PrimaryAsset_C", 4},
{L"Protocol 781-A Phantom", L"Default__Carbine_Protocol_PrimaryAsset_C", L"Default__Carbine_Protocol_Lv4_PrimaryAsset_C", 4},
{L"Oni Phantom", L"Default__AssaultRifle_ACR_Oni_PrimaryAsset_C", L"Default__AssaultRifle_ACR_Oni_Black_PrimaryAsset_C", 4},
{L"Nebula Phantom", L"Default__Carbine_Cosmos_PrimaryAsset_C", L"Default__Carbine_Cosmos_Lv1_PrimaryAsset_C", 4},
{L"Celestial Phantom", L"Default__Carbine_Lunar_PrimaryAsset_C", L"Default__Carbine_Lunar_Lv1_PrimaryAsset_C", 4},

};
//
//
static const std::vector<SkinData> operatorSkins = {
{L"Divergence Operator", L"Default__BoltSniper_Anomaly_PrimaryAsset_C", L"Default__BoltSniper_Anomaly_v1_PrimaryAsset_C", 4},
{L"Mystbloom Operator", L"Default__BoltSniper_Spirit_PrimaryAsset_C", L"Default__BoltSniper_Spirit_v2_PrimaryAsset_C", 4},
{L"Ion Operator", L"Default__BoltSniper_Oblivion_PrimaryAsset_C", L"Default__BoltSniper_OblivionLv4_PrimaryAsset_C", 4},
{L"RGX 11z Pro Operator", L"Default__BoltSniper_Afterglow2_PrimaryAsset_C", L"Default__BoltSniper_Afterglow2_Lv5_PrimaryAsset_C", 4},
{L"Origin Operator", L"Default__BoltSniper_Circle_PrimaryAsset_C", L"Default__BoltSniper_Circle_Lv4_PrimaryAsset_C", 4},
{L"Prelude to Chaos Operator", L"Default__BoltSniper_DemonStone_PrimaryAsset_C", L"Default__BoltSniper_DemonStone_Lv4_PrimaryAsset_C", 4},
{L"Forsaken Operator", L"Default__BoltSniper_Fallen_PrimaryAsset_C", L"Default__BoltSniper_Fallen_Lv4_PrimaryAsset_C", 4},
{L"Glitchpop Operator", L"Default__BoltSniper_Cyberpunk2_PrimaryAsset_C", L"Default__BoltSniper_Cyberpunk2_Lv4_PrimaryAsset_C", 4},
{L"Radiant Entertainment System Operator", L"Default__BoltSniper_Arcade_PrimaryAsset_C", L"Default__BoltSniper_Arcade_Lv4_PrimaryAsset_C", 4},
{L"Elderflame Operator", L"Default__BoltSniper_Dragon_PrimaryAsset_C", L"Default__BoltSniper_Dragon_Dark_PrimaryAsset_C", 4},
{L"Sentinels of Light Operator", L"Default__BoltSniper_SOL_PrimaryAsset_C", L"Default__BoltSniper_SOL_Lv4_PrimaryAsset_C", 4},
{L"Reaver Operator", L"Default__BoltSniper_Soulstealer_PrimaryAsset_C", L"Default__BoltSniper_Soulstealer_Black_PrimaryAsset_C", 4},
{L"Tethered Realms Operator", L"Default__BoltSniper_SovWorld_PrimaryAsset_C", L"Default__BoltSniper_SovWorld_Lv1_PrimaryAsset_C", 4},
{L"Araxys Operator", L"Default__BoltSniper_Antares_PrimaryAsset_C", L"Default__BoltSniper_Antares_Lv4_PrimaryAsset_C", 4},
{L"Gravitational Uranium Neuroblaster Operator", L"Default__BoltSniper_Raygun_PrimaryAsset_C", L"Default__BoltSniper_Raygun_Lv2_PrimaryAsset_C", 4},
{L"Magepunk Operator", L"Default__BoltSniper_Magepunk2_v1_PrimaryAsset_C", L"Default__BoltSniper_Magepunk2_Lv4_PrimaryAsset_C", 4},

};

static const std::vector<SkinData> bulldogSkins = {
{L"Phaseguard Bulldog", L"Default__Burst_Commando_PrimaryAsset_C", L"Default__Commando_v1_PrimaryAsset_C", 4},
{L"Nocturnum Bulldog", L"Default__Burst_Coven_PrimaryAsset_C", L"Default__Burst_Coven_v1_PrimaryAsset_C", 4},
{L"Glitchpop Bulldog", L"Default__AssaultRifle_Burst_Cyberpunk_PrimaryAsset_C", L"Default__AssaultRifle_Burst_Cyberpunk_Lv4_PrimaryAsset_C", 4},
{L"Spectrum Bulldog", L"Default__Burst_Atlas_PrimaryAsset_C", L"Default__Burst_Atlas_v2_PrimaryAsset_C", 4},
{L"Radiant Entertainment System Bulldog", L"Default__Burst_Arcade_v2_PrimaryAsset_C", L"Default__Burst_Arcade_Lv4_PrimaryAsset_C", 4},
};
//
static const std::vector<SkinData> frenzySkins = {

{L"Sovereign Frenzy", L"Default__AutoPistol_Sovereign2_PrimaryAsset_C", L"Default__AutoPistol_Sovereign2_v1_PrimaryAsset_C", 4},
{L"Elderflame Frenzy", L"Default__AutomaticPistol_Dragon_PrimaryAsset_C", L"Default__AutomaticPistol_Dragon_Blue_PrimaryAsset_C", 4},
{L"Glitchpop Frenzy", L"Default__AutomaticPistol_Cyberpunk_PrimaryAsset_C", L"Default__AutomaticPistol_Cyberpunk_Blue_PrimaryAsset_C", 4},
{L"BlastX Frenzy", L"Default__AutoPistol_URF_PrimaryAsset_C", L"Default__AutoPistol_URF_Standard_PrimaryAsset_C", 4},
{L"Prime//2.0 Frenzy", L"Default__AutomaticPistol_HypeBeast2_PrimaryAsset_C", L"Default__AutomaticPistol_HypeBeast2_PrimaryAsset_C", 4},
{L"Ion Frenzy", L"Default__AutoPistol_Oblivion2_PrimaryAsset_C", L"Default__AutoPistol_Oblivion2_Lv4_PrimaryAsset_C", 4},
{L"Oni Frenzy", L"Default__AutoPistol_Oni2_PrimaryAsset_C", L"Default__AutoPistol_Oni2_PrimaryAsset_C", 4},
{L"Origin Frenzy", L"Default__AutoPistol_Circle_PrimaryAsset_C", L"Default__AutoPistol_Circle_Lv4_PrimaryAsset_C", 4},
{L"RGX 11z Pro Frenzy", L"Default__AutoPistol_Afterglow_PrimaryAsset_C", L"Default__AutoPistol_Afterglow_Lv4_PrimaryAsset_C", 4},

};

static const std::vector<SkinData> guardianSkins = {

{L"Prime Guardian", L"Default__DMR_HypeBeast_PrimaryAsset_C", L"Default__DMR_HypeBeast_Lv4_PrimaryAsset_C", 4},
{L"Reaver Guardian", L"Default__DMR_SoulStealer_PrimaryAsset_C", L"Default__DMR_SoulStealer_Lv4_PrimaryAsset_C", 4},
{L"Ruination Guardian", L"Default__DMR_King_PrimaryAsset_C", L"Default__DMR_King_Lv4_PrimaryAsset_C", 4},
{L"Sovereign Guardian", L"Default__DMR_Sovereign_PrimaryAsset_C", L"Default__DMR_Sovereign_Lv4_PrimaryAsset_C", 4},
{L"RGX 11z Pro Guardian", L"Default__DMR_Afterglow_PrimaryAsset_C", L"Default__DMR_Afterglow_Lv4_PrimaryAsset_C", 4},
{L"Oni Guardian", L"Default__DMR_Oni_PrimaryAsset_C", L"Default__DMR_Oni_Lv4_PrimaryAsset_C", 4},

};
//
static const std::vector<SkinData> sheriffSkins = {

{L"Doombringer Sheriff", L"Default__Revolver_Cyberknight_PrimaryAsset_C", L"Default__Revolver_Cyberknight_v1_PrimaryAsset_C", 4},
{L"Neo Frontier Sheriff", L"Default__Revolver_Gunslinger_PrimaryAsset_C", L"Default__Revolver_Gunslinger_v1_PrimaryAsset_C", 4},
{L"RGX 11z Pro Sheriff", L"Default__Revolver_Afterglow3_PrimaryAsset_C", L"Default__Revolver_Afterglow3_v2_PrimaryAsset_C", 4},
{L"Mystbloom Sheriff", L"Default__Revolver_Spirit_PrimaryAsset_C", L"Default__Revolver_Spirit_v2_PrimaryAsset_C", 4},
{L"Kuronami Sheriff", L"Default__Revolver_Ninja_PrimaryAsset_C", L"Default__Revolver_Ninja_v1_PrimaryAsset_C", 4},
{L"Reaver Sheriff", L"Default__RevolverPistol_Soulstealer_PrimaryAsset_C", L"Default__RevolverPistol_Soulstealer_White_PrimaryAsset_C", 4},
{L"Singularity Sheriff", L"Default__RevolverPistol_Edge_PrimaryAsset_C", L"Default__RevolverPistol_Edge_Lv4_PrimaryAsset_C", 4},
{L"Protocol 781-A Sheriff", L"Default__Revolver_Protocol_PrimaryAsset_C", L"Default__Revolver_Protocol_Lv4_PrimaryAsset_C", 4},
{L"Sentinels of Light Sheriff", L"Default__Revolver_SOL_PrimaryAsset_C", L"Default__Revolver_SOL_Lv4_PrimaryAsset_C", 4},
{L"ChronoVoid Sheriff", L"Default__Revolver_Daedalus_PrimaryAsset_C", L"Default__Revolver_Daedalus_Lv4_PrimaryAsset_C", 4},
{L"Magepunk Sheriff", L"Default__Revolver_Magepunk2_PrimaryAsset_C", L"Default__Revolver_Magepunk2_Lv4_PrimaryAsset_C", 4},
{L"Nebula Sheriff", L"Default__Revolver_Cosmos_PrimaryAsset_C", L"Default__Revolver_Cosmos_Lv1_PrimaryAsset_C", 4},
{L"Arcane Sheriff", L"Default__Revolver_XP1_PrimaryAsset_C", L"Default__Revolver_XP1_Lv2_PrimaryAsset_C", 4},
{L"Schema Sheriff", L"Default__Revolver_Schema_PrimaryAsset_C", L"Default__Revolver_Schema_Lv1_PrimaryAsset_C", 4},
{L"Crimsonbeast Sheriff", L"Default__Revolver_Mythic_PrimaryAsset_C", L"Default__Revolver_Mythic_Lv2_PrimaryAsset_C", 4},
{L"Signature Sheriff", L"Default__Revolver_MidnightAerosol_PrimaryAsset_C", L"Default__Revolver_MidnightAerosol_PrimaryAsset_C", 4},
{L"Abyssal Sheriff", L"Default__Revolver_DeepSea_PrimaryAsset_C", L"Default__Revolver_DeepSea_Lv1_PrimaryAsset_C", 4},
{L"Ion Sheriff", L"Default__RevolverPistol_Oblivion_PrimaryAsset_C", L"Default__RevolverPistol_OblivionLv4_PrimaryAsset_C", 4},

};
static const std::vector<SkinData> ghostSkins = {
{L"Phaseguard Ghost", L"Default__Luger_Commando_PrimaryAsset_C", L"Default__Commando_v1_PrimaryAsset_C", 4},
{L"Reaver Ghost", L"Default__Luger_Soulstealer2_PrimaryAsset_C", L"Default__Luger_Soulstealer2_v1_PrimaryAsset_C", 4},
{L"XERØFANG Ghost", L"Default__Luger_Hypedragon_PrimaryAsset_C", L"Default__Luger_Hypedragon_v1_PrimaryAsset_C", 4},
{L"Sovereign Ghost", L"Default__LugerPistol_Sovereign_PrimaryAsset_C", L"Default__LugerPistol_Sovereign_Purple_PrimaryAsset_C", 4},
{L"Ruination Ghost", L"Default__Luger_King_PrimaryAsset_C", L"Default__Luger_King_Lv4_PrimaryAsset_C", 4},
{L"Magepunk Ghost", L"Default__Luger_Magepunk_PrimaryAsset_C", L"Default__Luger_Magepunk_Lv4_PrimaryAsset_C", 4},
{L"Gaia's Vengeance Ghost", L"Default__LugerPistol_Ashen_PrimaryAsset_C", L"Default__LugerPistol_Ashen_Lv4_PrimaryAsset_C", 4},

};
//
static const std::vector<SkinData> spectreSkins = {
{L"Kuronami Spectre", L"Default__MP5_Ninja_PrimaryAsset_C", L"Default__MP5_Ninja_v1_PrimaryAsset_C", 4},
{L"Ruination Spectre", L"Default__MP5_King_PrimaryAsset_C", L"Default__MP5_King_Lv4_PrimaryAsset_C", 4},
{L"Protocol 781-A Spectre", L"Default__MP5_Protocol_PrimaryAsset_C", L"Default__MP5_Protocol_Lv4_PrimaryAsset_C", 4},
{L"Reaver Spectre", L"Default__MP5_Soulstealer2_PrimaryAsset_C", L"Default__MP5_Soulstealer2_Lv4_PrimaryAsset_C", 4},
{L"Radiant Crisis 001 Spectre", L"Default__MP5_Comicbook_PrimaryAsset_C", L"Default__MP5_Comicbook_Lv3_PrimaryAsset_C", 4},
};
//
static const std::vector<SkinData> classicSkins = {
{L"VCT x SEN Classic", L"Default__BasePistol_VCTCaps24_SEN_PrimaryAsset_C", L"Default__BasePistol_VCTCaps24_SEN_V1_PrimaryAsset_C", 4},
{L"VCT x G2 Classic", L"Default__BasePistol_VCTCaps24_G2_PrimaryAsset_C", L"Default__BasePistol_VCTCaps24_G2_Lv3_PrimaryAsset_C", 4},
{L"VCT x BBL Classic", L"Default__BasePistol_VCTCaps24_BBL_PrimaryAsset_C", L"Default__BasePistol_VCTCaps24_BBL_Lv3_PrimaryAsset_C", 4},
{L"Spectrum Classic", L"Default__BasePistol_Atlas_PrimaryAsset_C", L"Default__BasePistol_Atlas_v1_PrimaryAsset_C", 4},
{L"Prime Classic", L"Default__BasePistol_HypeBeast_PrimaryAsset_C", L"Default__BasePistol_HypeBeast_Blue_PrimaryAsset_C", 4},
{L"RGX 11z Pro Classic", L"Default__BasePistol_Afterglow2_PrimaryAsset_C", L"Default__BasePistol_Afterglow2_Lv4_PrimaryAsset_C", 4},
{L"Forsaken Classic", L"Default__BasePistol_Fallen_PrimaryAsset_C", L"Default__BasePistol_Fallen_Lv3_PrimaryAsset_C", 4},
{L"Glitchpop Classic", L"Default__BasePistol_Cyberpunk2_PrimaryAsset_C", L"Default__BasePistol_Cyberpunk2_Lv4_PrimaryAsset_C", 4},
};
//
static const std::vector<SkinData> marshalSkins = {
{L"Nocturnum Marshal", L"Default__LeverSniper_Coven_PrimaryAsset_C", L"Default__LeverSniper_Coven_V1_PrimaryAsset_C", 4},
{L"Kuronami Marshal", L"Default__LeverSniper_Ninja_PrimaryAsset_C", L"Default__LeverSniper_Ninja_v1_PrimaryAsset_C", 4},
{L"Sovereign Marshal", L"Default__LeverSniperRifle_Sovereign_PrimaryAsset_C", L"Default__LeverSniperRifle_Sovereign_Purple_PrimaryAsset_C", 4},
};
//
//static const std::vector<SkinData> judgeSkins = {
//	{L"Default__AutomaticShotgun_Soulstealer_PrimaryAsset_C", L"Default__AutomaticShotgun_Soulstealer_Lv2_PrimaryAsset_C", 4},
//	{L"Default__AutomaticShotgun_Dragon_PrimaryAsset_C", L"Default__AutomaticShotgun_Dragon_Lv4_PrimaryAsset_C", 4},
//	{L"Default__AutomaticShotgun_Ninja_PrimaryAsset_C", L"Default__AutomaticShotgun_Ninja_v2_PrimaryAsset_C", 4},
//	{L"Default__AutomaticShotgun_Sovereign_PrimaryAsset_C", L"Default__AutomaticShotgun_Sovereign_Lv4_PrimaryAsset_C", 4},
//	{L"Default__AutomaticShotgun_Oni_PrimaryAsset_C", L"Default__AutomaticShotgun_Oni_Lv4_PrimaryAsset_C", 4},
//};
//
//static const std::vector<SkinData> ariesSkins = {
//	{L"Default__LMG_SOL_PrimaryAsset_C", L"Default__LMG_SOL_Lv4_PrimaryAsset_C", 4},
//	{L"Default__LMG_Dragon_PrimaryAsset_C", L"Default__LMG_Dragon_Lv4_PrimaryAsset_C", 4},
//	{L"Default__LMG_Ninja_PrimaryAsset_C", L"Default__LMG_Ninja_v2_PrimaryAsset_C", 4},
//	{L"Default__LMG_Soulstealer_PrimaryAsset_C", L"Default__LMG_Soulstealer_Lv4_PrimaryAsset_C", 4},
//	{L"Default__LMG_Oni_PrimaryAsset_C", L"Default__LMG_Oni_Lv4_PrimaryAsset_C", 4},
//};
//	
//static const std::vector<SkinData> odinSkins = {
//	{L"Default__HMG_Soulstealer_PrimaryAsset_C", L"Default__HMG_Soulstealer_Lv2_PrimaryAsset_C", 4},
//	{L"Default__HMG_Dragon_PrimaryAsset_C", L"Default__HMG_Dragon_Lv4_PrimaryAsset_C", 4},
//	{L"Default__HMG_Ninja_PrimaryAsset_C", L"Default__HMG_Ninja_v2_PrimaryAsset_C", 4},
//	{L"Default__HMG_Sovereign_PrimaryAsset_C", L"Default__HMG_Sovereign_Lv4_PrimaryAsset_C", 4},
//	{L"Default__HMG_Oni_PrimaryAsset_C", L"Default__HMG_Oni_Lv4_PrimaryAsset_C", 4},
//};
//
//static const std::vector<SkinData> buckySkins = {
//	{L"Default__PumpShotgun_Soulstealer_PrimaryAsset_C", L"Default__PumpShotgun_Soulstealer_Lv2_PrimaryAsset_C", 4},
//	{L"Default__PumpShotgun_Dragon_PrimaryAsset_C", L"Default__PumpShotgun_Dragon_Lv4_PrimaryAsset_C", 4},
//	{L"Default__PumpShotgun_Ninja_PrimaryAsset_C", L"Default__PumpShotgun_Ninja_v2_PrimaryAsset_C", 4},
//	{L"Default__PumpShotgun_Sovereign_PrimaryAsset_C", L"Default__PumpShotgun_Sovereign_Lv4_PrimaryAsset_C", 4},
//	{L"Default__PumpShotgun_Oni_PrimaryAsset_C", L"Default__PumpShotgun_Oni_Lv4_PrimaryAsset_C", 4},
//};
//
//static const std::vector<SkinData> shortySkins = {
//	{L"Default__SawedOffShotgun_Soulstealer_PrimaryAsset_C", L"Default__SawedOffShotgun_Soulstealer_Lv2_PrimaryAsset_C", 4},
//	{L"Default__SawedOffShotgun_Dragon_PrimaryAsset_C", L"Default__SawedOffShotgun_Dragon_Lv4_PrimaryAsset_C", 4},
//	{L"Default__SawedOffShotgun_Ninja_PrimaryAsset_C", L"Default__SawedOffShotgun_Ninja_v2_PrimaryAsset_C", 4},
//	{L"Default__SawedOffShotgun_Sovereign_PrimaryAsset_C", L"Default__SawedOffShotgun_Sovereign_Lv4_PrimaryAsset_C", 4},
//	{L"Default__SawedOffShotgun_Oni_PrimaryAsset_C", L"Default__SawedOffShotgun_Oni_Lv4_PrimaryAsset_C", 4},
//};
//
//static const std::vector<SkinData> stingerSkins = {
//	{L"Default__Vector_Soulstealer_PrimaryAsset_C", L"Default__Vector_Soulstealer_Lv2_PrimaryAsset_C", 4},
//	{L"Default__Vector_Dragon_PrimaryAsset_C", L"Default__Vector_Dragon_Lv4_PrimaryAsset_C", 4},
//	{L"Default__Vector_Ninja_PrimaryAsset_C", L"Default__Vector_Ninja_v2_PrimaryAsset_C", 4},
//	{L"Default__Vector_Sovereign_PrimaryAsset_C", L"Default__Vector_Sovereign_Lv4_PrimaryAsset_C", 4},
//	{L"Default__Vector_Oni_PrimaryAsset_C", L"Default__Vector_Oni_Lv4_PrimaryAsset_C", 4},
//};
//
static const std::vector<SkinData> knifeskins = {
{L"Phaseguard Splitter", L"Default__Melee_Commando_PrimaryAsset_C", L"Default__Melee_Commando_v1_PrimaryAsset_C", 2},
{L"Beta Remastered", L"Default__Melee_Warring_PrimaryAsset_C", L"Default__Melee_Warring_v1_PrimaryAsset_C", 2},
{L"Divergence St4ff", L"Default__Melee_Anomaly_PrimaryAsset_C", L"Default__Melee_Anomaly_v1_PrimaryAsset_C", 2},
{L"Helix Daggers", L"Default__Melee_Snake_PrimaryAsset_C", L"Default__Melee_Snake_v2_PrimaryAsset_C", 2},
{L"Blades of Primordia", L"Default__Melee_Hellfire_PrimaryAsset_C", L"Default__Melee_Hellfire_v2_PrimaryAsset_C", 2},
{L"Bolt Knife", L"Default__Melee_Bolt_PrimaryAsset_C", L"Default__Melee_Bolt_v1_PrimaryAsset_C", 2},
{L"CYRAX Fanblade", L"Default__Melee_Syndra_PrimaryAsset_C", L"Default__Melee_Syndra_v1_PrimaryAsset_C", 2},
{L"VCT 2025 Karambit", L"Default__Melee_VCT25Season_PrimaryAsset_C", L"Default__Melee_VCT25Season_v1_PrimaryAsset_C", 2},
{L"EX.O Edge", L"Default__Melee_Hologram_PrimaryAsset_C", L"Default__Melee_Hologram_v3_PrimaryAsset_C", 2},
{L"Doombringer Battleaxe", L"Default__Melee_Cyberknight_PrimaryAsset_C", L"Default__Melee_Cyberknight_v1_PrimaryAsset_C", 2},
{L"Neo Frontier Axe", L"Default__Melee_Gunslinger_PrimaryAsset_C", L"Default__Gunslinger_Syndra_v1_PrimaryAsset_C", 2},
{L"Evori's Spellcaster", L"Default__Melee_StarPower_PrimaryAsset_C", L"Default__Melee_StarPower_v1_PrimaryAsset_C", 2},
{L"Singularity Butterfly Knife", L"Default__Melee_Edge2_PrimaryAsset_C", L"Default__Melee_Edge2_v1_PrimaryAsset_C", 2},
{L"Nocturnum Scythe", L"Default__Melee_Coven_PrimaryAsset_C", L"Default__Melee_Coven_v1_PrimaryAsset_C", 2},
{L"Champions 2024 Blade", L"Default__Melee_Champions2024_PrimaryAsset_C", L"Default__Melee_Champions2024_Lv3_PrimaryAsset_C", 2},
{L"RGX 11z Pro Karambit", L"Default__Melee_Afterglow3_PrimaryAsset_C", L"Default__Melee_Afterglow3_v2_PrimaryAsset_C", 2},
{L"Mystbloom Kunai", L"Default__Melee_Spirit_PrimaryAsset_C", L"Default__Melee_Spirit_v2_PrimaryAsset_C", 2},
{L"Eternal Sovereign", L"Default__Melee_Sovereign2_PrimaryAsset_C", L"Default__Melee_Sovereign2_v1_PrimaryAsset_C", 2},
{L"Waveform", L"Default__Melee_Atlas_PrimaryAsset_C", L"Default__Melee_Atlas_v1_PrimaryAsset_C", 2},
{L"XERØFANG Knife", L"Default__Melee_Hypedragon_PrimaryAsset_C", L"Default__Melee_Hypedragon_v2_PrimaryAsset_C", 2},
{L"Kuronami no Yaiba", L"Default__Melee_Ninja_PrimaryAsset_C", L"Default__Melee_Ninja_V1_PrimaryAsset_C", 2},
{L"Champions 2023 Kunai", L"Default__Melee_Champions2023_PrimaryAsset_C", L"Default__Melee_Champions2023_PrimaryAsset_C", 2},
{L"Magepunk Sparkswitch", L"Default__Melee_Magepunk3_PrimaryAsset_C", L"Default__Melee_Magepunk3_PrimaryAsset_C", 2},
{L"VCT LOCK//IN Misericórdia", L"Default__Melee_Esportsinvitational_PrimaryAsset_C", L"Default__Melee_Esportsinvitational_Standard_PrimaryAsset_C", 2},
{L"Champions 2021 Karambit", L"Default__Melee_Champions_PrimaryAsset_C", L"Default__Melee_Champions_Lv2_PrimaryAsset_C", 2},
{L"Reaver Karambit", L"Default__Melee_Soulstealer2_PrimaryAsset_C", L"Default__Melee_Soulstealer2_v1_PrimaryAsset_C", 2},
{L"Black.Market Butterfly Knife", L"Default__Melee_Infantry2_Lv2_PrimaryAsset_C", L"Default__Melee_Infantry2_PrimaryAsset_C", 2},
{L"RGX 11z Pro Firefly", L"Default__Melee_Afterglow2_PrimaryAsset_C", L"Default__Melee_Afterglow2_v2_PrimaryAsset_C", 2},
{L"Xenohunter Knife", L"Default__Melee_Alien_PrimaryAsset_C", L"Default__Melee_Alien_Lv2_PrimaryAsset_C", 2},
{L"Prime//2.0 Karambit", L"Default__Melee_HypeBeast2_PrimaryAsset_C", L"Default__Melee_HypeBeast2_Lv2_PrimaryAsset_C", 2},
{L"Reaver Knife", L"Default__Melee_Soulstealer_PrimaryAsset_C", L"Default__Melee_Soulstealer_Lv2_PrimaryAsset_C", 2},
{L"Radiant Crisis 001 Baseball Bat", L"Default__Melee_Comicbook_PrimaryAsset_C", L"Default__Melee_Comicbook_Lv2_PrimaryAsset_C", 2},
//{L"NOT FOUND", L"Default__Melee_Dragon_PrimaryAsset_C", L"Default__Melee_Dragon_Lv2_PrimaryAsset_C", 2},
{L"Araxys Bio Harvester", L"Default__Melee_Antares_v2_PrimaryAsset_C", L"Default__Melee_Antares_Lv2_PrimaryAsset_C", 2},
{L"Soulstrife Scythe", L"Default__Melee_Haunted_PrimaryAsset_C", L"Default__Melee_Haunted_Lv2_PrimaryAsset_C", 2},
{L"Crimsonbeast Hammer", L"Default__Melee_Mythic_PrimaryAsset_C", L"Default__Melee_Mythic_Lv2_PrimaryAsset_C", 2},
{L"Magepunk Shock Gauntlet", L"Default__Melee_Magepunk2_PrimaryAsset_C", L"Default__Melee_Magepunk2_Lv2_PrimaryAsset_C", 2},
//{L"NOT FOUND", L"Default__Melee_Oni_PrimaryAsset_C", L"Default__Melee_Oni_Lv2_PrimaryAsset_C", 2},
{L"Onimaru Kunitsuna", L"Default__Melee_Oni2_PrimaryAsset_C", L"Default__Melee_Oni2_Lv2_PrimaryAsset_C", 2},
{L"Forsaken Ritual Blade", L"Default__Melee_Fallen_Lv2_PrimaryAsset_C", L"Default__Melee_Fallen_PrimaryAsset_C", 2},
{L"Blade of Chaos", L"Default__Melee_DemonStone_PrimaryAsset_C", L"Default__Melee_DemonStone_v2_PrimaryAsset_C", 2},
};

static const std::vector<SkinData> outlawskins = {
    {L"NIGGA",L"Default__DS_Gun_Afterglow3_PrimaryAsset_C", L"Default__DS_Gun_Afterglow3_v2_PrimaryAsset_C", 2},
};

static const std::vector<SkinData> chamspions_sheriff = {
    {L"NIGGA",L"Default__AK_Champions_PrimaryAsset_C", L"Default__AK_Champions_Lv4_PrimaryAsset_C", 2},
};
static int vandalSkinOption = 0;
static int sheriffSkinOption = 0;
static int guardianSkinOption = 0;
static int frenzySkinOption = 0;
static int bulldogSkinOption = 0;
static int operatorSkinOption = 0;
static int phantomSkinOption = 0;
static int ghostSkinOption = 0;
static int spectreSkinOption = 0;
static int classicSkinOption = 0;
static int marshalSkinOption = 0;
static int knifeSkinOption = 0;
static int outlawSkinOption = 0;
static int selectedSkinIndex = 0; // default to first
//
uworld* UWorldSave;

std::unordered_map<uobject*, WeaponCosmetics> weapon_cosmetics;

#define DefusePercentageMax 6.984602
#define CurrentDefuseSectionMax 2

#define MAX_TRACERS 100
#define TRACER_LIFETIME 7.0f
#define MAX_COLORS 20

struct Tracer {
    fvector worldStart;
    fvector worldEnd;
    float timeCreated;
    flinearcolor color;
    bool hasHit;
    float distance;
    bool isValid;
};

Tracer tracers[MAX_TRACERS];
int currentTracerIndex = 0;
int currentColorIndex = 0;
flinearcolor colorPalette[MAX_COLORS];
float lastTracerTime = 0.0f;
bool colorPaletteInitialized = false;

void initializeColorPalette() {
    const float baseIntensity = 0.5f;
    const float saturationRange = 0.3f;

    for (int i = 0; i < MAX_COLORS; i++) {
        float hue = static_cast<float>(rand()) / RAND_MAX;
        float saturation = (static_cast<float>(rand()) / RAND_MAX) * saturationRange + (1.0f - saturationRange);

        float chroma = saturation * baseIntensity;
        float huePrime = hue * 6.0f;
        float x = chroma * (1.0f - std::abs(fmodf(huePrime, 2.0f) - 1.0f));
        float r1, g1, b1;

        if (huePrime < 1.0f) { r1 = chroma; g1 = x; b1 = 0; }
        else if (huePrime < 2.0f) { r1 = x; g1 = chroma; b1 = 0; }
        else if (huePrime < 3.0f) { r1 = 0; g1 = chroma; b1 = x; }
        else if (huePrime < 4.0f) { r1 = 0; g1 = x; b1 = chroma; }
        else if (huePrime < 5.0f) { r1 = x; g1 = 0; b1 = chroma; }
        else { r1 = chroma; g1 = 0; b1 = x; }

        float m = baseIntensity - chroma;
        colorPalette[i] = flinearcolor(r1 + m, g1 + m, b1 + m, 1.0f);
    }
}

static float  Gloww = 5.0f;
static flinearcolor ChamsColorw{ 1.0f, 0.5f, 0.0f, 0.9f };

namespace G
{
    currentequippable* MyWeapon = nullptr;
    currentequippable* LastWeapon = nullptr;
}

static uobject* rage_icon = nullptr;
static uobject* legit_icon = nullptr;
static uobject* visuals_icon = nullptr;
static uobject* settings_icon = nullptr;
static uobject* config_icon = nullptr;
static uobject* local_icon = nullptr;

flinearcolor BOSSRAINBOMAW(float time)
{

    const float PI = 3.14159265359f;
    float R = 0.5f + 0.5f * sin(time);
    float G = 0.5f + 0.5f * sin(time + 2.0f * PI / 3.0f);
    float B = 0.5f + 0.5f * sin(time + 4.0f * PI / 3.0f);
    return flinearcolor(R, G, B, 1.0f);
}
#include <chrono>
#include <deque>
#include <unordered_map>

#include "offsets.hpp"

//#include <windows.h>
//#include <shlobj.h>
//#include <string>
//#include <fstream>
//#include <vector>
//#include <filesystem>
//#include <iostream>
//
//namespace fs = std::filesystem;
//
//std::string get_documents_path() {
//    char documents_path[MAX_PATH];
//    if (SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, documents_path) == S_OK) {
//        return std::string(documents_path);
//    }
//    return crypt("").decrypt();
//}
//
//std::string get_config_directory() {
//    std::string config_dir = get_documents_path() + crypt("\\configs").decrypt();
//    fs::create_directories(config_dir);
//    return config_dir;
//}
//
//std::string get_config_file_path(const std::string& config_name) {
//    return get_config_directory() + crypt("\\").decrypt() + config_name + crypt(".json").decrypt();
//}
//
//std::vector<std::string> list_configs() {
//    std::vector<std::string> config_files;
//    std::string config_dir = get_config_directory();
//
//    for (const auto& entry : fs::directory_iterator(config_dir)) {
//        if (entry.is_regular_file() && entry.path().extension() == crypt(".json").decrypt()) {
//            config_files.push_back(entry.path().stem().string());
//        }
//    }
//    return config_files;
//}
//
//void create_config(const std::string& config_name) {
//    std::string config_path = get_config_file_path(config_name);
//    std::ofstream file(config_path);
//    if (file.is_open()) {
//        file << crypt("{}").decrypt();
//        file.close();
//    }
//}
//
//void save_config(const std::string& config_name) {
//    std::string config_path = get_config_file_path(config_name);
//    std::ofstream file(config_path);
//    if (!file.is_open()) return;
//
//    file << "[Visuals]\n";
//    file << "b0x=" << globals::visuals::b0x << "\n";
//    file << "b0x_type=" << globals::visuals::b0x_type << "\n";
//    file << "box2d=" << globals::visuals::box2d << "\n";
//    file << "box=" << globals::visuals::box << "\n";
//    file << "headb0x=" << globals::visuals::headb0x << "\n";
//    file << "sk3let0n=" << globals::visuals::sk3let0n << "\n";
//    file << "snapl1ne=" << globals::visuals::snapl1ne << "\n";
//    file << "h3althbar=" << globals::visuals::h3althbar << "\n";
//    file << "b00ms=" << globals::visuals::b00ms << "\n";
//    file << "b11ms=" << globals::visuals::b11ms << "\n";
//    file << "dstc=" << globals::visuals::dstc << "\n";
//    file << "dormant=" << globals::visuals::dormant << "\n";
//    file << "visiblecheck=" << globals::visuals::visiblecheck << "\n";
//
//    file << "[Aimbot]\n";
//    file << "a1mbot=" << globals::aimbot::a1mbot << "\n";
//    file << "v1sh_ch3ck=" << globals::aimbot::v1sh_ch3ck << "\n";
//    file << "recoilcrosshair=" << globals::aimbot::recoilcrosshair << "\n";
//    file << "reco1l_contr0l=" << globals::aimbot::reco1l_contr0l << "\n";
//    file << "draw_f0v=" << globals::aimbot::draw_f0v << "\n";
//    file << "a1m_sm00th=" << globals::aimbot::a1m_sm00th << "\n";
//    file << "a1m_f0v=" << globals::aimbot::a1m_f0v << "\n";
//    file << "a1m_b0ne=" << globals::aimbot::a1m_b0ne << "\n";
//    file << "a1m_k3y=" << globals::aimbot::a1m_k3y << "\n";
//    file << "tr1g_f0v=" << globals::tr1g::tr1g_f0v << "\n";
//    file << "tr1g_k3y=" << globals::tr1g::tr1g_k3y << "\n";
//
//    file << "[Misc]\n";
//    file << "sk1n_chang3r=" << globals::misc::sk1n_chang3r << "\n";
//
//    file.close();
//}
//
//void load_config(const std::string& config_name) {
//    std::string config_path = get_config_file_path(config_name);
//    std::ifstream file(config_path);
//    if (!file.is_open()) return;
//
//    std::string line;
//    std::string current_section;
//
//    while (std::getline(file, line)) {
//        if (line.empty() || line[0] == ';' || line[0] == '#') continue;
//        if (line[0] == '[') {
//            current_section = line.substr(1, line.size() - 2);
//        }
//        else {
//            size_t delimiter_pos = line.find('=');
//            if (delimiter_pos == std::string::npos) continue;
//
//            std::string key = line.substr(0, delimiter_pos);
//            std::string value = line.substr(delimiter_pos + 1);
//
//            if (current_section == crypt("Visuals").decrypt()) {
//                if (key == crypt("b0x").decrypt()) globals::visuals::b0x = std::stoi(value);
//                else if (key == crypt("b0x_type").decrypt()) globals::visuals::b0x_type = std::stoi(value);
//                else if (key == crypt("box2d").decrypt()) globals::visuals::box2d = std::stoi(value);
//                else if (key == crypt("box3d").decrypt()) globals::visuals::box3d = std::stoi(value);
//                else if (key == crypt("box").decrypt()) globals::visuals::box = std::stoi(value);
//                else if (key == crypt("headb0x").decrypt()) globals::visuals::headb0x = std::stoi(value);
//                else if (key == crypt("sk3let0n").decrypt()) globals::visuals::sk3let0n = std::stoi(value);
//                else if (key == crypt("snapl1ne").decrypt()) globals::visuals::snapl1ne = std::stoi(value);
//                else if (key == crypt("h3althbar").decrypt()) globals::visuals::h3althbar = std::stoi(value);
//                else if (key == crypt("b00ms").decrypt()) globals::visuals::b00ms = std::stoi(value);
//                else if (key == crypt("b11ms").decrypt()) globals::visuals::b11ms = std::stoi(value);
//                else if (key == crypt("dstc").decrypt()) globals::visuals::dstc = std::stoi(value);
//                else if (key == crypt("dormant").decrypt()) globals::visuals::dormant = std::stoi(value);
//                else if (key == crypt("visiblecheck").decrypt()) globals::visuals::visiblecheck = std::stoi(value);
//            }
//            else if (current_section == crypt("Aimbot").decrypt()) {
//                if (key == crypt("a1mbot").decrypt()) globals::aimbot::a1mbot = std::stoi(value);
//                else if (key == crypt("v1sh_ch3ck").decrypt()) globals::aimbot::v1sh_ch3ck = std::stoi(value);
//                else if (key == crypt("recoilcrosshair").decrypt()) globals::aimbot::recoilcrosshair = std::stoi(value);
//                else if (key == crypt("reco1l_contr0l").decrypt()) globals::aimbot::reco1l_contr0l = std::stoi(value);
//                else if (key == crypt("draw_f0v").decrypt()) globals::aimbot::draw_f0v = std::stoi(value);
//                else if (key == crypt("a1m_sm00th").decrypt()) globals::aimbot::a1m_sm00th = std::stof(value);
//                else if (key == crypt("a1m_f0v").decrypt()) globals::aimbot::a1m_f0v = std::stof(value);
//                else if (key == crypt("a1m_b0ne").decrypt()) globals::aimbot::a1m_b0ne = std::stoi(value);
//                else if (key == crypt("a1m_k3y").decrypt()) globals::aimbot::a1m_k3y = std::stoi(value);
//                else if (key == crypt("tr1g_f0v").decrypt()) globals::tr1g::tr1g_f0v = std::stof(value);
//                else if (key == crypt("tr1g_k3y").decrypt()) globals::tr1g::tr1g_k3y = std::stoi(value);
//            }
//            else if (current_section == crypt("Misc").decrypt()) {
//                if (key == crypt("sk1n_chang3r").decrypt()) globals::misc::sk1n_chang3r = std::stoi(value);
//            }
//        }
//    }
//    file.close();
//}
//
//void delete_config(const std::string& config_name) {
//    std::string config_path = get_config_file_path(config_name);
//    if (fs::exists(config_path)) {
//        fs::remove(config_path);
//    }
//}

static flinearcolor vlsclr = { 1.0f, 1.0f, 1.0f, 1.0f };

uintptr_t camera_engine;
bool should_hook_gay;

int screen_width = GetSystemMetrics(SM_CXSCREEN);
int screen_height = GetSystemMetrics(SM_CYSCREEN);

bool InGame = 0;

float spin_value;

static auto OldAimAngles = fvector();
float GetDeltaTime() {
    static uint64_t lastTime = GetTickCount64();
    uint64_t currentTime = GetTickCount64();

    float delta = (currentTime - lastTime) / 1000.0f; // ms → saniye
    lastTime = currentTime;
    return delta;
}
struct DamageInfo {
    float damage;
    fvector position;
    float time;
    bool isHeadshot;

    DamageInfo(float d, const fvector& pos, float t, bool hs)
        : damage(d), position(pos), time(t), isHeadshot(hs) {
    }
};




// Helper fonksiyonlar
bool download_kill_sound1() {
    HINTERNET hInternet = InternetOpenA("KillSound1", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hInternet) return false;

    HINTERNET hUrl = InternetOpenUrlA(hInternet, "h", NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hUrl) {
        InternetCloseHandle(hInternet);
        return false;
    }

    std::vector<uint8_t> buffer;
    char temp[4096];
    DWORD bytesRead;

    while (InternetReadFile(hUrl, temp, sizeof(temp), &bytesRead) && bytesRead > 0) {
        buffer.insert(buffer.end(), temp, temp + bytesRead);
    }

    InternetCloseHandle(hUrl);
    InternetCloseHandle(hInternet);

    if (buffer.empty()) return false;

    HANDLE hFile = CreateFileW(L"C:\\Sound\\kill_sound1.wav", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) return false;

    DWORD bytesWritten;
    BOOL result = WriteFile(hFile, buffer.data(), buffer.size(), &bytesWritten, NULL);
    CloseHandle(hFile);

    return result && bytesWritten == buffer.size();
}

bool download_kill_sound2() {
    HINTERNET hInternet = InternetOpenA("KillSound2", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hInternet) return false;

    HINTERNET hUrl = InternetOpenUrlA(hInternet, "", NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hUrl) {
        InternetCloseHandle(hInternet);
        return false;
    }

    std::vector<uint8_t> buffer;
    char temp[4096];
    DWORD bytesRead;

    while (InternetReadFile(hUrl, temp, sizeof(temp), &bytesRead) && bytesRead > 0) {
        buffer.insert(buffer.end(), temp, temp + bytesRead);
    }

    InternetCloseHandle(hUrl);
    InternetCloseHandle(hInternet);

    if (buffer.empty()) return false;

    HANDLE hFile = CreateFileW(L"C:\\Sound\\kill_sound2.wav", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) return false;

    DWORD bytesWritten;
    BOOL result = WriteFile(hFile, buffer.data(), buffer.size(), &bytesWritten, NULL);
    CloseHandle(hFile);

    return result && bytesWritten == buffer.size();
}

bool download_kill_sound3() {
    HINTERNET hInternet = InternetOpenA("KillSound3", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hInternet) return false;

    HINTERNET hUrl = InternetOpenUrlA(hInternet, "", NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hUrl) {
        InternetCloseHandle(hInternet);
        return false;
    }

    std::vector<uint8_t> buffer;
    char temp[4096];
    DWORD bytesRead;

    while (InternetReadFile(hUrl, temp, sizeof(temp), &bytesRead) && bytesRead > 0) {
        buffer.insert(buffer.end(), temp, temp + bytesRead);
    }

    InternetCloseHandle(hUrl);
    InternetCloseHandle(hInternet);

    if (buffer.empty()) return false;

    HANDLE hFile = CreateFileW(L"C:\\Sound\\kill_sound3.wav", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) return false;

    DWORD bytesWritten;
    BOOL result = WriteFile(hFile, buffer.data(), buffer.size(), &bytesWritten, NULL);
    CloseHandle(hFile);

    return result && bytesWritten == buffer.size();
}

bool kill_sound1_exists() {
    DWORD attrs = GetFileAttributesW(L"C:\\Sound\\kill_sound1.wav");
    return (attrs != INVALID_FILE_ATTRIBUTES && !(attrs & FILE_ATTRIBUTE_DIRECTORY));
}

bool kill_sound2_exists() {
    DWORD attrs = GetFileAttributesW(L"C:\\Sound\\kill_sound2.wav");
    return (attrs != INVALID_FILE_ATTRIBUTES && !(attrs & FILE_ATTRIBUTE_DIRECTORY));
}

bool kill_sound3_exists() {
    DWORD attrs = GetFileAttributesW(L"C:\\Sound\\kill_sound3.wav");
    return (attrs != INVALID_FILE_ATTRIBUTES && !(attrs & FILE_ATTRIBUTE_DIRECTORY));
}

//void BlockGameInput(bool block) {
//    auto controller = blueprints::get_local_controller(nullptr); // blueprints:: ekle
//    auto character = get_local_character();
//
//    if (controller && character) {
//        if (block) {
//            character->DisableInput(controller);
//        }
//        else {
//            character->EnableInput(controller);
//        }
//    }
//}




// HOOK KURMA



//void meshp1_material_chams(acknowledgedpawn* pawn, ashootercharacter* shooter_character)
//{
//    // Load cosmos material
//    static uobject* cosmosMaterial = uobject::StaticLoadObject(crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/CosmosShader/_old/ScreenspaceProjection_MI.ScreenspaceProjection_MI"));
//
//    static fname fresnelColorName = string::string_to_name(L"Fresnel_Color");
//    static fname edgeHighlightColorName = string::string_to_name(L"Edge Highlight Color");
//    static fname emissiveColorName = string::string_to_name(L"Emissive Color");
//    static fname emissiveIntensityName = string::string_to_name(L"Emissive Intensity");
//
//    // Read component pointers
//    UPrimitiveComponent* mesh1p = memory::read<UPrimitiveComponent*>(uintptr_t(pawn) + offsets::mesh1p);
//    UPrimitiveComponent* meshOverlay = memory::read<UPrimitiveComponent*>(uintptr_t(pawn) + offsets::mesh1p_overlay);
//
//    if (!mesh1p && !meshOverlay) return;
//
//    static float rainbowTimeZHandChams = 0.f;
//    ashootercharacter* actor;
//
//    uskeletalmeshcomponent* mesh22 = actor->get_mesh();
//
//    // Glow / parlaklık çarpanı
//    float Glow1 = 1.0f;
//
//    float handcolorR = 0.0f;
//    float handcolorG = 0.5f;
//    float handcolorB = 1.0f;
//
//    // Rainbow modu için otomatik değerler
//    bool handChamsRGB = true;
//
//    flinearcolor colorToApply;
//    if (handChamsRGB) {
//        rainbowTimeZHandChams += 0.002f;
//        colorToApply = BOSSRAINBOMAW(rainbowTimeZHandChams);
//    }
//    else {
//        colorToApply = flinearcolor{
//            handcolorR,
//            handcolorG,
//            handcolorB
//        };
//    }
//
//    colorToApply = flinearcolor{
//        colorToApply.r * Glow1,
//        colorToApply.g * Glow1,
//        colorToApply.b * Glow1,
//        1.0f
//    };
//
//    auto applyChams = [&](UPrimitiveComponent* mesh) {
//        if (!mesh) return;
//
//        int numMaterials = mesh->get_num_materials();
//        for (int i = 0; i < numMaterials; i++) {
//            // Cosmos material'ını kullan
//            uobject* dynMat = mesh->create_and_set_material_instance_dynamic_from_material(i, cosmosMaterial);
//            if (!dynMat) continue;
//
//            auto mid = dynMat->cast<UMaterialInstanceDynamic>();
//            if (!mid) continue;
//
//            // Cosmos material parametrelerini ayarla
//            mid->set_vector_parameter_value1(fresnelColorName, colorToApply);
//            mid->set_vector_parameter_value2(edgeHighlightColorName, colorToApply);
//            mid->set_vector_parameter_value2(emissiveColorName, colorToApply);
//
//            // Scalar parametreler
//            mid->set_scalar_parameter_value(emissiveIntensityName, 3.0f * Glow1);
//        }
//
//        
//        if (globals::visuals::chams)
//        {
//            reinterpret_cast<uskeletalmeshcomponent* (__fastcall*)(uskeletalmeshcomponent*, int, bool)>(
//                memory::module_base + offsets::set_ares_outline_mode
//                )(mesh22, 4, true);
//
//            flinearcolor finalColor;
//            if (globals::visuals::rainbow_chams)
//            {
//                float t = GetTickCount64() * 0.002f;
//                finalColor = flinearcolor(
//                    (sinf(t + 0.5f) * 0.5f + 0.5f) * globals::visuals::chams_intensity,
//                    (sinf(t + 2.0f) * 0.5f + 0.5f) * globals::visuals::chams_intensity,
//                    (sinf(t + 4.0f) * 0.5f + 0.5f) * globals::visuals::chams_intensity,
//                    1.0f
//                );
//            }
//            else
//            {
//                auto col = globals::visuals::chams_color;
//                float intensity = globals::visuals::chams_intensity;
//                finalColor = flinearcolor(
//                    col.r * intensity,
//                    col.g * intensity,
//                    col.b * intensity,
//                    1.0f
//                );
//            }
//
//            ares_outline::setoutlinemode(world, finalColor, finalColor);
//
//            uintptr_t fresnel = *(uintptr_t*)((uintptr_t)mesh + offsets::fresnelcomponent);
//            if (fresnel)
//            {
//                *(float*)(fresnel + 0x10) = 1000.0f * globals::visuals::chams_intensity;
//                *(float*)(fresnel + 0x14) = 10.0f * globals::visuals::chams_intensity;
//            }
//
//            uintptr_t fresnel3 = *(uintptr_t*)((uintptr_t)mesh + offsets::fr3scomp);
//            if (fresnel3)
//            {
//                *(float*)(fresnel3 + 0x10) = 1000.0f * globals::visuals::chams_intensity;
//                *(float*)(fresnel3 + 0x14) = 10.0f * globals::visuals::chams_intensity;
//            }
//        }
//        };
//
//    applyChams(mesh1p);
//    applyChams(meshOverlay);
//}

using DamageTracker = std::unordered_map<ashootercharacter*, std::vector<DamageInfo>>;
DamageTracker damageTracker;

std::unordered_map<ashootercharacter*, float> lastHealthMap;

//#define Mesh1P 0xC60
//#define SkeletalMesh 0x598
//
//void ApplySkin(uobject* Mesh, uskeletalmeshcomponent* weapon)
//{
//    uintptr_t pMesh1P = memory::read<uintptr_t>(reinterpret_cast<uintptr_t>(weapon) + Mesh1P);
//
//    if (pMesh1P) {
//        memory::write<uintptr_t>(pMesh1P + SkeletalMesh, reinterpret_cast<uintptr_t>(Mesh));
//    }
//}
//
//ashootercharacter* characteru;
//
//void damn_fuck() {
//
//    uobject* skin_data_asset = uobject::find_object<uobject*>(crypt(L"Default__HMG_Alien_PrimaryAsset_C"));
//    uobject* chroma_data_asset = uobject::find_object<uobject*>(crypt(L"Default__HMG_Alien_Lv2_PrimaryAsset_C"));
//
//    uinventory* inventory = characteru->get_inventory();
//    currentequippable* equippable = inventory->get_current_equippable();
//
//    if (skin_data_asset && chroma_data_asset) {
//        content_library::clear_weapon_components(equippable);
//        content_library::apply_skin(equippable, skin_data_asset, chroma_data_asset, 2, nullptr, -1);
//    }
//}

//void Custom_Skin(uobject* WorldObject) {
//
//    umaterial_instance* MiniMapmatInst;
//    umaterial_instance* sectionMaterial;
//    UKismetRenderingLibrary* param;
//
//    UPrimitiveComponent* BoxMeshComponent = GetBoxExtent();
//    if (!BoxMeshComponent) return;
//
//    bool isValid;
//    int32_t texWidth, texHeight;
//    const char* Path =crypt("C:/picture.png";
//    UTexture2D* TextureParam = par->ImportFileAsTexture2D(WorldObject, Path);
//    MiniMapmatInst = static_cast<umaterial_instance*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Engine/EngineResources/DefaultTexture.DefaultTexture").decrypt()));
//    sectionMaterial = BoxMeshComponent->CreateAndSetMaterialInstanceDynamicFromMaterial(0, MiniMapmatInst);
//    a->set_vector_parameter_value(string::string_to_name(L"Fresnel Enemy Tint"), { 0, dmncolor.r * Glow1, dmncolor.g * Glow1, dmncolor.b * Glow1 });
//    sectionMaterial->SetTextureParameterValue(kismentsystemlibrary::Conv_StringToName("Diffuse"), TextureParam);
//
//}

//#define Mesh1P 0xC60
//#define SkeletalMesh 0x598
//#define OverrideMaterials 0x548
//
//void ApplySkin(uobject* Mesh, uobject* Material, uskeletalmeshcomponent* weapon)
//{
//    if (Mesh && Material && weapon) {
//        uintptr_t pMesh1P = memory::read<uintptr_t>(reinterpret_cast<uintptr_t>(weapon) + Mesh1P);
//
//        if (pMesh1P) {
//            memory::write<uintptr_t>(pMesh1P + SkeletalMesh, reinterpret_cast<uintptr_t>(Mesh));
//            memory::write<uintptr_t>(pMesh1P + 0x20, reinterpret_cast<uintptr_t>(Material));
//            memory::write<uintptr_t>(pMesh1P + OverrideMaterials, pMesh1P + 0x20);
//            memory::write<uint32_t>(pMesh1P + OverrideMaterials + 8, 1);
//        }
//    }
//}

//void ApplySkin(uskeletalmeshcomponent* Mesh, uobject* Material, uskeletalmeshcomponent* weapon)
//{
//    if (!Mesh || !Material || !weapon)
//        return;
//
//    uintptr_t* pMesh1P = reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(weapon) + Mesh1P);
//    if (!pMesh1P || !*pMesh1P)
//        return;
//
//    *reinterpret_cast<uskeletalmeshcomponent**>(*pMesh1P + SkeletalMesh) = Mesh;
//
//    *reinterpret_cast<uobject**>(*pMesh1P + 0x20) = Material;
//
//    *reinterpret_cast<uintptr_t*>(*pMesh1P + OverrideMaterials) = *pMesh1P + 0x20;
//
//    *reinterpret_cast<uint32_t*>(*pMesh1P + OverrideMaterials + 8) = 1;
//}

// 
//#include <Windows.h>
//#include <TlHelp32.h>
//#include <iostream>
//#include <vector>
//#include <memory>
//#include <string>
//
//void Log(const std::string& message) {
//    std::cout <<crypt("[VGCThreadInterceptor]crypt(" << message << std::endl;
//}
//
//// Enable debug privileges
//BOOL EnableDebugPrivilege() {
//    HANDLE hToken;
//    LUID luid;
//    TOKEN_PRIVILEGES tkp;
//
//    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
//        Log("OpenProcessToken failed:crypt(" + std::to_string(GetLastError()));
//        return FALSE;
//    }
//
//    if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid)) {
//        Log("LookupPrivilegeValue failed:crypt(" + std::to_string(GetLastError()));
//        CloseHandle(hToken);
//        return FALSE;
//    }
//
//    tkp.PrivilegeCount = 1;
//    tkp.Privileges[0].Luid = luid;
//    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
//
//    if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(tkp), NULL, NULL)) {
//        Log("AdjustTokenPrivileges failed:crypt(" + std::to_string(GetLastError()));
//        CloseHandle(hToken);
//        return FALSE;
//    }
//
//    CloseHandle(hToken);
//    return TRUE;
//}
//
//// Function to find and modify VGC-related threads
//void NopVgcThreadInstructions(DWORD processId) {
//    // Take a snapshot of all threads in the system
//    HANDLE hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
//    if (hThreadSnap == INVALID_HANDLE_VALUE) {
//        Log("Failed to create thread snapshot");
//        return;
//    }
//
//    THREADENTRY32 te32;
//    te32.dwSize = sizeof(THREADENTRY32);
//
//    if (!Thread32First(hThreadSnap, &te32)) {
//        Log("Failed to get first thread");
//        CloseHandle(hThreadSnap);
//        return;
//    }
//
//    // Iterate over all threads to find VGC-related threads
//    do {
//        if (te32.th32OwnerProcessID == processId) {
//            // Check if this thread is related to the VGC process
//            // You can replace this check with the actual logic to identify VGC threads
//            if (std::to_string(te32.th32ThreadID).find("VGC") != std::string::npos) { // Placeholder condition
//                HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, te32.th32ThreadID);
//                if (hThread) {
//                    CONTEXT threadContext;
//                    threadContext.ContextFlags = CONTEXT_FULL;
//                    if (GetThreadContext(hThread, &threadContext)) {
//                        // Check if the process is 64-bit or 32-bit and modify accordingly
//                        LPVOID targetAddress = NULL;
//                        if (sizeof(void*) == 8) { // 64-bit process
//                            targetAddress = reinterpret_cast<LPVOID>(threadContext.Rip); // Use Rip for 64-bit
//                        }
//
//                        BYTE nopInstruction[] = { 0x90, 0x90, 0x90 }; // NOP instruction (0x90)
//                        SIZE_T bytesWritten;
//
//                        // Replace critical instructions with NOPs at the target address
//                        BOOL result = WriteProcessMemory(GetCurrentProcess(), targetAddress, nopInstruction, sizeof(nopInstruction), &bytesWritten);
//                        if (result) {
//                            Log("NOP-ed instructions at threadcrypt(" + std::to_string(te32.th32ThreadID));
//                        }
//                        else {
//                            Log("Failed to write NOPs to memory:crypt(" + std::to_string(GetLastError()));
//                        }
//                    }
//                    else {
//                        Log("Failed to get thread context:crypt(" + std::to_string(GetLastError()));
//                    }
//
//                    CloseHandle(hThread);
//                }
//                else {
//                    Log("Failed to open thread:crypt(" + std::to_string(GetLastError()));
//                }
//            }
//        }
//    } while (Thread32Next(hThreadSnap, &te32));
//
//    CloseHandle(hThreadSnap);
//}
//
//// DLL entry point to initialize the process manipulation
//DWORD WINAPI InitializeVgcInterceptor(LPVOID lpParameter) {
//    if (!EnableDebugPrivilege()) {
//        Log("Failed to enable debug privileges.");
//        return 1;
//    }
//
//    DWORD currentProcessId = GetCurrentProcessId();
//    Log("Intercepting VGC threads in process ID:crypt(" + std::to_string(currentProcessId));
//
//    // Call the function to modify the VGC threads' instructions
//    NopVgcThreadInstructions(currentProcessId);
//
//    return 0;
//}

namespace hooks
{
    static int TargetX = 0;
    static int TargetY = 0;
    float ESPThickness = 1;
    bool enemiesarround = true;
    int enemyID = 0;
    int enemyIDvis = 0;
    int CloseRangeDistanceID = 0;
    float CloseRangeDistance = 50.f;

    /* ashootercharacter* OldMyShooter;*/

    aplayercontroller* controllers;
    aplayercontroller12* controllersss;
    pregame_view_controller* precontroller;

    acknowledgedpawn* pawn;

    ashootercharacter* character;

    void Recoil_Control() {
        Sleep(3);
        mouse.mouse_event(TargetX, 5, 0);
    }

    flinearcolor get_color(bool condition) {
        return condition ? flinearcolor{ 0.1f, 1.0f, 0.1f, 1 } : flinearcolor{ 1.0f, 0.0f, 0.0f, 1 };
    }

    static float  FOVChangorSprite = 5.0f;
    static float  Glow = 5.0f;
    static flinearcolor ChamsColor{ 1.0f, 0.5f, 0.0f, 0.9f };
    static flinearcolor wlcr{ 1.0f, 1.0f, 1.0f, 1.0f };
    static float  Glow1 = 20.0f;
    static flinearcolor dmncolor{ 1.0f, 0.5f, 0.0f, 0.9f };
    static flinearcolor vlnclr = { 1.0f, 1.0f, 1.0f, 1.0f };

    float rainbowTime = 0;  // Le temps qui augmentera pour générer un arc-en-ciel dynamique

    //flinearcolor Invisible = flinearcolor(0.0f, 0.0f, 0.0f, 0.0f);  // Invisible est une couleur de base (transparent ou noir)

    flinearcolor GetRainbowColor(float t)
    {
        const float PI = 3.14159265359f;
        float r = 0.5f + 0.5f * sinf(t);
        float g = 0.5f + 0.5f * sinf(t + 2.0f * PI / 3.0f);
        float b = 0.5f + 0.5f * sinf(t + 4.0f * PI / 3.0f);
        return flinearcolor(r, g, b, 1.0f);
    }

    fvector2d posss = { ((float)GetSystemMetrics(SM_CXSCREEN) / 2) - 500, ((float)GetSystemMetrics(SM_CYSCREEN) / 2) - 475 };

    auto calculate_box_dimensions = [](fvector2d head_long_out, fvector2d base_out) -> std::pair<float, float> {
        float box_height = abs(head_long_out.y - base_out.y);
        float box_width = box_height * 0.55f;
        return { box_width, box_height };
        };

    auto get_target_bone_matrix = [](uskeletalmeshcomponent* mesh, int bone) -> fvector {
        switch (bone) {
        case 0: return mesh->get_bone_location(8); break;
        case 1: return mesh->get_bone_location(6); break;
        case 2: return mesh->get_bone_location(4); break;
        default: return fvector();
        }
        };

    void draw_head(ucanvas* canvas, uobject* font, const wchar_t* text, flinearcolor color, fvector2d pos) {
        canvas->k2_drawtext(font, text, pos, { 1.50f, 1.50f }, color, 0.f, { 0, 0, 0, 0.30f }, { 0, 0 }, true, true, true, { 0, 0, 0, 0.90 });
    }

    float DegreeToRadian(float degrees) {
        return degrees * (3.1415926535897932f / 180);
    }

    void draw_head2(ucanvas* canvas, uobject* font, const wchar_t* text, flinearcolor color, fvector2d pos) {
        flinearcolor white_color = flinearcolor(1.0f, 1.0f, 1.0f, 1.0f); // Blanc (totalement opaque)

        // Définir la couleur de l'ombre : une version grise avec une opacité réduite (50 %)
        flinearcolor shadow_color = flinearcolor(0.5f, 0.5f, 0.5f, 0.5f); // Gris semi-transparent

        // Définir le décalage de l'ombre pour le texte (légèrement décalé en x et y)
        fvector2d shadow_offset = fvector2d{ 2.0f, 2.0f };

        // Draw the shadow first (slightly offset from the original position)
        canvas->k2_drawtext(font, text, pos + shadow_offset, { 1.0f, 1.0f }, shadow_color, 0.f, { 0, 0, 0, 0.30f }, { 0, 0 }, true, true, true, { 0, 0, 0, 0.90 });

        // Draw the main text with the purple color (overlaid on top of the shadow)
        canvas->k2_drawtext(font, text, pos, { 1.0f, 1.0f }, white_color, 0.f, { 0, 0, 0, 0.30f }, { 0, 0 }, true, true, true, { 0, 0, 0, 0.90 });
    }


    //void DrawWatermark(ucanvas* canvas, uobject* font) {
    //    // Ekranın sol üst köşesi
    //    fvector2d pos = { 60.0f, 60.0f };
    //    fvector2d scale = { 1.3f, 1.3f };

    //    // Koyu mavi renk
    //    flinearcolor darkBlue = { 0.0f, 0.0f, 0.5f, 1.0f };

    //    // Watermark çizimi
    //    canvas->k2_drawtext(
    //        font,
    //        fstring(L"Vip Products Version 1.0.2"),
    //        pos,
    //        scale,
    //        darkBlue,
    //        0.0f,                  // kerning
    //        { 0,0,0,0 },            // shadow color
    //        { 0,0 },                // shadow offset
    //        false,                  // centreX
    //        false,                  // centreY
    //        true,                   // outline
    //        { 0,0,0,1.0f }          // outline color siyah
    //    );
    //}


    fvector GetBoneMatrix(void* Mesh, int Idx) {
        FMatrix Matrix;
        reinterpret_cast<FMatrix* (__fastcall*)(void*, FMatrix*, int)>((uintptr_t)memory::module_base + offsets::bone_matrix)(Mesh, &Matrix, Idx); // E8 ?? ?? ?? ?? 48 8B 47 30 F3 0F 10 45 ??
        return  { Matrix.WPlane.X, Matrix.WPlane.Y, Matrix.WPlane.Z };
    }


    bool bOutline = 1;

    void draw_text45(ucanvas* canvas, uobject* font, const wchar_t* text, flinearcolor color, fvector2d pos) {
        canvas->k2_drawtext(font, text, pos, { 1.00f, 1.00f }, color, 0.f, { 0, 0, 0, 0.30f }, { 0, 0 }, true, true, true, { 0, 0, 0, 0.45 });
    }

    void draw_textO(ucanvas* canvas, uobject* font, const wchar_t* text, flinearcolor color, fvector2d pos) {
        canvas->k2_drawtext(font, text, pos, { 0.80f, 0.80f }, color, 0.f, { 0, 0, 0, 0.30f }, { 0, 0 }, true, true, true, { 0, 0, 0, 0.45 });
    }

    static void draw_text_rgb_string(ucanvas* canvas, uobject* font, fstring text, float x, float y, flinearcolor color, bool CenterX = 0)
    {
        canvas->k2_drawtext(font, text, { x, y }, { 1.1, 1.1 }, color, 0.f, { 0, 0, 0, 1 }, { 0, 0 }, CenterX, 0, bOutline, { 0, 0, 0, 1 });
    }
    int current_selection = 3;
    const int max_selection = 26;
    bool key_pressed = false;
    static bool open_canvas = true;

    currentequippable* myweapon;
    currentequippable* lastweapon;

    static flinearcolor maincolor{ 1.0f,1.0f,1.0f,1.0f };
    float bowv4l = 1;

    void draw_triangle(ucanvas* canvas, int current_selection, float x, float y, float size, flinearcolor color) {
        static float time = 0.0f;

        float animationSpeed = 0.05f;
        float maxMovementRange = 4.0f;

        float animatedX = x + (sin(time) * maxMovementRange);

        time += animationSpeed;

        if (time > 6.2832f) {
            time -= 6.2832f;
        }

        fvector2d point1, point2, point3;

        switch (current_selection) {
        case 3:
            point1 = { animatedX, y };
            point2 = { animatedX + size, y + size / 2 };
            point3 = { animatedX, y + size };
            break;
        case 4:
            point1 = { animatedX, y };
            point2 = { animatedX + size / 2, y + size };
            point3 = { animatedX + size, y };
            break;
        case 5:
            point1 = { animatedX + size, y };
            point2 = { animatedX, y + size / 2 };
            point3 = { animatedX + size, y + size };
            break;
        case 6:
            point1 = { animatedX, y + size };
            point2 = { animatedX + size / 2, y };
            point3 = { animatedX + size, y + size };
            break;
        default:
            point1 = { animatedX, y };
            point2 = { animatedX + size, y + size / 2 };
            point3 = { animatedX, y + size };
            break;
        }

        canvas->k2_drawline(point1, point2, 2.0f, color);
        canvas->k2_drawline(point2, point3, 2.0f, color);
        canvas->k2_drawline(point3, point1, 2.0f, color);
    }

    boolean in_rect(double centerX, double centerY, double radius, double x, double y) {
        return x >= centerX - radius && x <= centerX + radius &&
            y >= centerY - radius && y <= centerY + radius;
    }


    static flinearcolor Name_Color{ 1.f,1.f,1.f,1.f };
    float RainbowTime = 0.0f;
    const float RainbowSpeed = 1.0f;
    const float PI = 3.14159265359f;

    void draw_text(ucanvas* canvas, uobject* font, const wchar_t* text, flinearcolor color, fvector2d pos) {
        canvas->k2_drawtext(font, text, pos, { 1.00f, 1.00f }, color, 0.f, { 0, 0, 0, 0.30f }, { 0, 0 }, true, true, true, { 0, 0, 0, 0.45 });
    }

    void draw_text15(ucanvas* canvas, uobject* font, const wchar_t* text, flinearcolor color, fvector2d pos) {
        canvas->k2_drawtext(font, text, pos, { 0.4f, 0.4f }, color, 0.f, { 0, 0, 0, 0.30f }, { 0, 0 }, true, true, true, { 0, 0, 0, 0.45 });
    }

    void draw_texttt(ucanvas* canvas, uobject* font, const wchar_t* text, flinearcolor color, fvector2d pos) {
        canvas->k2_drawtext(font, text, pos, { 1.35f, 1.35f }, color, 0.f, { 0, 0, 0, 0.30f }, { 0, 0 }, true, true, true, { 0, 0, 0, 0.45 });
    }

    void draw_text_chk(ucanvas* canvas, uobject* font, const wchar_t* text, flinearcolor color, fvector2d pos) {
        // Disable horizontal centering and ensure proper alignment
        canvas->k2_drawtext(
            font,
            text,
            pos,
            { 1.00f, 1.00f }, // Text scale for clarity
            color,
            0.f,              // No kerning
            { 0, 0, 0, 0.30f }, // Subtle shadow for depth
            { 1.0f, 1.0f },     // Small shadow offset for clarity
            false,             // Disable horizontal centering
            true,              // Enable vertical centering for consistent placement
            true,              // Enable outline for contrast
            { 0, 0, 0, 0.45f } // Subtle outline for better visibility
        );
    }

    void draw_text4(ucanvas* canvas, uobject* font, const wchar_t* text, flinearcolor color, fvector2d pos) {
        canvas->k2_drawtext(
            font,
            text,
            pos,
            { 1.15f, 1.15f }, // Optimal scale for clarity
            color,
            0.f,
            { 0, 0, 0, 0.50f }, // Darker shadow for better edge definition
            { 1.2f, 1.2f },     // Slightly larger shadow offset for smoother appearance
            true,
            true,
            true,
            { 0, 0, 0, 0.60f }  // Stronger background shadow for enhanced contrast
        );
    }

    void draw_text77(ucanvas* canvas, uobject* font, const fstring& text, flinearcolor color, fvector2d pos) {
        canvas->k2_drawtext(font, text, pos, { 1.00f, 1.00f }, color, 0.f, { 0, 0, 0, 0.30f }, { 0, 0 }, true, true, true, { 0, 0, 0, 0.45f });
    }

    /*void draw_text(ucanvas* canvas, uobject* font, const wchar_t* text, flinearcolor color, fvector2d pos) {
        canvas->k2_drawtext(font, text, pos, { 1.00f, 1.00f }, color, 0.f, { 0, 0, 0, 0.30f }, { 0, 0 }, true, true, true, { 0, 0, 0, 0.45 });
    }*/

    static float radius = 4.0f;
    float LineamountCross = 35.0f;
    float LineamountCircle = 25.0f;
    float LineamountFov = 35.0f;

    void draw_section_header(ucanvas* canvas, uobject* font, const wchar_t* label,
        flinearcolor color, fvector2d pos) {
        const float header_width = 260.0f;
        const float header_height = 25.0f;

        canvas->k2_drawline(pos, { pos.x + header_width, pos.y }, 2.0f, color);
        draw_text(canvas, font, label, color, { pos.x, pos.y - header_height });
    }

    void draw_text_centered(ucanvas* canvas, uobject* font, const wchar_t* text,
        flinearcolor color, fvector2d pos) {
        float text_width = wcslen(text) * 8.0f;
        float text_height = 16.0f;

        draw_text(canvas, font, text, color,
            { pos.x - text_width / 2, pos.y - text_height / 2 });
    }


    void draw_line(ucanvas* canvas, const fvector2d& start, const fvector2d& end, const flinearcolor& color) {
        if (!canvas) return;

        canvas->k2_drawline(
            fvector2d{ start.x, start.y },
            fvector2d{ end.x, end.y },
            1.0f,
            color
        );
    }

    namespace Input
    {
        bool mouseDown[5];
        bool mouseDownAlready[256];

        bool keysDown[256];
        bool keysDownAlready[256];

        bool IsAnyMouseDown()
        {
            if (mouseDown[0]) return true;
            if (mouseDown[1]) return true;
            if (mouseDown[2]) return true;
            if (mouseDown[3]) return true;
            if (mouseDown[4]) return true;

            return false;
        }

        bool IsMouseClicked(int button, int element_id, bool repeat)
        {
            if (mouseDown[button])
            {
                if (!mouseDownAlready[element_id])
                {
                    mouseDownAlready[element_id] = true;
                    return true;
                }
                if (repeat)
                    return true;
            }
            else
            {
                mouseDownAlready[element_id] = false;
            }
            return false;
        }
        bool IsKeyPressed(int key, bool repeat)
        {
            if (keysDown[key])
            {
                if (!keysDownAlready[key])
                {
                    keysDownAlready[key] = true;
                    return true;
                }
                if (repeat)
                    return true;
            }
            else
            {
                keysDownAlready[key] = false;
            }
            return false;
        }

        void Handle()
        {
            if (GetAsyncKeyState(0x01))
                mouseDown[0] = true;
            else
                mouseDown[0] = false;
        }
    }



    wchar_t* s2wc(const char* c)
    {
        const size_t cSize = strlen(c) + 1;
        wchar_t* wc = new wchar_t[cSize];
        mbstowcs(wc, c, cSize);

        return wc;
    }

    struct DrawList
    {
        int type = -1; //1 = FilledRect, 2 = TextLeft, 3 = TextCenter, 4 = Draw_Line
        fvector2d pos;
        fvector2d size;
        flinearcolor color;
        const wchar_t* name;
        bool outline;

        fvector2d from;
        fvector2d to;
        int thickness;
    };
    DrawList drawlist[128];

    void drawFilledRect(fvector2d pos, float w, float h, flinearcolor color)
    {
        for (int i = 0; i < 128; i++)
        {
            if (drawlist[i].type == -1)
            {
                drawlist[i].type = 1;
                drawlist[i].pos = pos;
                drawlist[i].size = fvector2d{ w, h };
                drawlist[i].color = color;
                return;
            }
        }
    }
    void TextLeft(const wchar_t* name, fvector2d pos, flinearcolor color, bool outline)
    {
        for (int i = 0; i < 128; i++)
        {
            if (drawlist[i].type == -1)
            {
                drawlist[i].type = 2;
                drawlist[i].name = name;
                drawlist[i].pos = pos;
                drawlist[i].outline = outline;
                drawlist[i].color = color;
                return;
            }
        }
    }
    void TextCenter(const wchar_t* name, fvector2d pos, flinearcolor color, bool outline)
    {
        for (int i = 0; i < 128; i++)
        {
            if (drawlist[i].type == -1)
            {
                drawlist[i].type = 3;
                drawlist[i].name = name;
                drawlist[i].pos = pos;
                drawlist[i].outline = outline;
                drawlist[i].color = color;
                return;
            }
        }
    }
    void Draw_Line(ucanvas* cvs, fvector2d from, fvector2d to, int thickness, flinearcolor color)
    {
        cvs->k2_drawline(fvector2d{ from.x, from.y }, fvector2d{ to.x, to.y }, thickness, color);
    }

    int active_hotkey = -1;
    bool already_pressed = false;
    std::string VirtualKeyCodeToString(UCHAR virtualKey)
    {
        UINT scanCode = MapVirtualKey(virtualKey, MAPVK_VK_TO_VSC);
        if (virtualKey == VK_LBUTTON)
        {
            return (crypt("MOUSE0").decrypt());
        }
        if (virtualKey == VK_RBUTTON)
        {
            return (crypt("MOUSE1").decrypt());
        }
        if (virtualKey == VK_MBUTTON)
        {
            return (crypt("MBUTTON").decrypt());
        }
        if (virtualKey == VK_XBUTTON1)
        {
            return (crypt("XBUTTON1").decrypt());
        }
        if (virtualKey == VK_XBUTTON2)
        {
            return (crypt("XBUTTON2").decrypt());
        }


        CHAR szName[128];
        int result = 0;
        switch (virtualKey)
        {
        case VK_LEFT: case VK_UP: case VK_RIGHT: case VK_DOWN:
        case VK_RCONTROL: case VK_RMENU:
        case VK_LWIN: case VK_RWIN: case VK_APPS:
        case VK_PRIOR: case VK_NEXT:
        case VK_END: case VK_HOME:
        case VK_INSERT: case VK_DELETE:
        case VK_DIVIDE:
        case VK_NUMLOCK:
            scanCode |= KF_EXTENDED;
        default:
            result = GetKeyNameTextA(scanCode << 16, szName, 128);
        }

        return szName;
    }

    bool hover_element = false;
    fvector2d menu_pos = fvector2d{ 0, 0 };
    float offset_x = 0.0f;
    float offset_y = 0.0f;

    fvector2d first_element_pos = fvector2d{ 0, 0 };

    fvector2d last_element_pos = fvector2d{ 0, 0 };
    fvector2d last_element_size = fvector2d{ 0, 0 };

    int current_element = -1;
    fvector2d current_element_pos = fvector2d{ 0, 0 };
    fvector2d current_element_size = fvector2d{ 0, 0 };
    int elements_count = 0;
    flinearcolor Button_Idle{ 0.76f, 0.16f, 0.18f, 1.0f }; // New red (#C1282E)
    flinearcolor Button_Hovered{ 0.86f, 0.26f, 0.28f, 1.0f };
    bool sameLine = false;

    bool pushY = false;
    float pushYvalue = 0.0f;

    fvector2d CursorPos()
    {
        POINT cursorPos;
        GetCursorPos(&cursorPos);
        return fvector2d{ (float)cursorPos.x, (float)cursorPos.y };
    }

    bool MouseInZone(fvector2d pos, fvector2d size)
    {
        fvector2d cursor_pos = CursorPos();

        if (cursor_pos.x > pos.x && cursor_pos.y > pos.y)
            if (cursor_pos.x < pos.x + size.x && cursor_pos.y < pos.y + size.y)
                return true;

        return false;
    }

    void Hotkey(const char* name, fvector2d size, int* key)
    {
        elements_count++;

        static float menu_x = 100.0f;
        static float menu_y = 100.0f;
        const float menu_width = 900.0f;
        const float menu_height = 500.0f;
        const float tab_height = 40.0f;

        // Adjust padding and initial position based on the menu layout
        fvector2d padding = fvector2d{ 20, 15 };
        fvector2d pos = fvector2d{ menu_x + padding.x + offset_x, menu_y + tab_height + padding.y + offset_y };

        if (sameLine)
        {
            pos.x = last_element_pos.x + last_element_size.x + padding.x;
            pos.y = last_element_pos.y + (last_element_size.y / 2) - size.y / 2;
        }

        if (pushY)
        {
            pos.y = pushYvalue;
            pushY = false;
            pushYvalue = 0.0f;
            offset_y = pos.y - menu_y - tab_height;
        }

        // Ensure the position stays within the menu boundaries
        if (pos.x + size.x > menu_x + menu_width - padding.x)
        {
            pos.x = menu_x + padding.x;
            offset_y += size.y + padding.y;
        }

        // DEBUG: Visualize the hotkey position
        drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, flinearcolor{ 1.0f, 0.0f, 0.0f, 0.5f });

        bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, size);

        // Draw background
        if (isHovered)
        {
            drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, Button_Hovered);
            hover_element = true;
        }
        else
        {
            drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, Button_Idle);
        }

        if (!sameLine)
            offset_y += size.y + padding.y;

        fvector2d textPos = fvector2d{ pos.x + size.x / 2, pos.y + size.y / 2 };

        if (active_hotkey == elements_count)
        {
            // Showcrypt("Press Key" when selecting a key
            TextCenter(crypt(L"Press Key").decrypt(), textPos, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);

            if (!Input::IsAnyMouseDown())
            {
                already_pressed = false;
            }

            if (!already_pressed)
            {
                for (int code = 0; code < 255; code++)
                {
                    if (GetAsyncKeyState(code))
                    {
                        if (code == VK_ESCAPE)
                        {
                            *key = 0;
                            active_hotkey = -1;
                        }
                        else
                        {
                            *key = code;
                            active_hotkey = -1;
                        }
                    }
                }
            }
        }
        else
        {
            if (*key != 0)
            {
                TextCenter(s2wc(VirtualKeyCodeToString(*key).c_str()), textPos, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);
            }
            else
            {
                TextCenter(crypt(L"Keybind").decrypt(), textPos, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);
            }

            if (isHovered && Input::IsMouseClicked(0, elements_count, false))
            {
                already_pressed = true;
                active_hotkey = elements_count;

                // Queue Fix
                for (int code = 0; code < 255; code++)
                    if (GetAsyncKeyState(code)) {}
            }
        }

        sameLine = false;
        last_element_pos = pos;
        last_element_size = size;
        if (first_element_pos.x == 0.0f)
            first_element_pos = pos;
    }
    struct Color {
        float r, g, b, a;
    };

    flinearcolor HSVtoRGB(float h, float s, float v) {
        float r, g, b;

        int i = static_cast<int>(h * 6);
        float f = h * 6 - i;
        float p = v * (1 - s);
        float q = v * (1 - f * s);
        float t = v * (1 - (1 - f) * s);

        switch (i % 6) {
        case 0: r = v; g = t; b = p; break;
        case 1: r = q; g = v; b = p; break;
        case 2: r = p; g = v; b = t; break;
        case 3: r = p; g = q; b = v; break;
        case 4: r = t; g = p; b = v; break;
        case 5: r = v; g = p; b = q; break;
        default: r = g = b = 0.0f;
        }

        return flinearcolor{ r, g, b, 1.0f };
    }

    namespace input
    {
        bool mouseDown[5];
        bool mouseDownAlready[256];

        bool keysDown[256];
        bool keysDownAlready[256];

        bool is_any_mouse_down()
        {
            if (mouseDown[0]) return true;
            if (mouseDown[1]) return true;
            if (mouseDown[2]) return true;
            if (mouseDown[3]) return true;
            if (mouseDown[4]) return true;

            return false;
        }

        bool is_mouse_clicked(int button, int element_id, bool repeat)
        {
            if (mouseDown[button])
            {
                if (!mouseDownAlready[element_id])
                {
                    mouseDownAlready[element_id] = true;
                    return true;
                }
                if (repeat)
                    return true;
            }
            else
            {
                mouseDownAlready[element_id] = false;
            }
            return false;
        }
        bool is_key_pressed(int key, bool repeat)
        {
            if (keysDown[key])
            {
                if (!keysDownAlready[key])
                {
                    keysDownAlready[key] = true;
                    return true;
                }
                if (repeat)
                    return true;
            }
            else
            {
                keysDownAlready[key] = false;
            }
            return false;
        }

        void handle()
        {
            if (GetAsyncKeyState(0x01))
                mouseDown[0] = true;
            else
                mouseDown[0] = false;
        }
    }


    //namespace menu
    //{
    //    flinearcolor RGBtoFLC(float r, float g, float b)
    //    {
    //        return { r / 255, g / 255, b / 255, 1 };
    //    }

    //    void TextCenter(const wchar_t* name, fvector2d pos, flinearcolor color, bool outline)
    //    {
    //        for (int i = 0; i < 128; i++)
    //        {
    //            if (drawlist[i].type == -1)
    //            {
    //                drawlist[i].type = 3;
    //                drawlist[i].name = name;
    //                drawlist[i].pos = pos;
    //                drawlist[i].outline = outline;
    //                drawlist[i].color = color;
    //                return;
    //            }
    //        }
    //    }

    //    flinearcolor HSVtoRGB(float h, float s, float v) {
    //        float r, g, b;

    //        int i = static_cast<int>(h * 6);
    //        float f = h * 6 - i;
    //        float p = v * (1 - s);
    //        float q = v * (1 - f * s);
    //        float t = v * (1 - (1 - f) * s);

    //        switch (i % 6) {
    //        case 0: r = v; g = t; b = p; break;
    //        case 1: r = q; g = v; b = p; break;
    //        case 2: r = p; g = v; b = t; break;
    //        case 3: r = p; g = q; b = v; break;
    //        case 4: r = t; g = p; b = v; break;
    //        case 5: r = v; g = p; b = q; break;
    //        default: r = g = b = 0.0f;
    //        }

    //        return flinearcolor{ r, g, b, 1.0f };

    //    }
    //    namespace Colors
    //    {
    //        // Modern dark theme with blue/purple accent
    //        flinearcolor Text{ 0.95f, 0.95f, 0.98f, 1.0f }; // Almost white
    //        flinearcolor Text_Shadow{ 0.95f, 0.95f, 0.98f, 1.0f };
    //        flinearcolor Text_Outline{ 1.0f, 1.0f, 1.0f, 1.0f };
    //        flinearcolor Text_Active{ 0.6f, 0.6f, 1.0f, 0.8f }; // Light blue accent

    //        flinearcolor Button_Idle{ 0.13f, 0.15f, 0.22f, 1.0f }; // Dark blue
    //        flinearcolor Button_Hovered{ 0.22f, 0.25f, 0.38f, 1.0f }; // Lighter blue
    //        flinearcolor Button_Active{ 0.45f, 0.18f, 0.65f, 1.0f }; // Purple accent

    //        flinearcolor Checkbox_Idle{ 0.18f, 0.20f, 0.28f, 1.0f };
    //        flinearcolor Checkbox_Hovered{ 0.30f, 0.32f, 0.45f, 1.0f };
    //        flinearcolor Checkbox_Enabled{ 0.45f, 0.18f, 0.65f, 1.0f }; // Purple accent

    //        flinearcolor Combobox_Idle{ 0.13f, 0.15f, 0.22f, 1.0f };
    //        flinearcolor Combobox_Hovered{ 0.22f, 0.25f, 0.38f, 1.0f };
    //        flinearcolor Combobox_Elements{ 0.45f, 0.18f, 0.65f, 0.5f };

    //        flinearcolor Slider_Idle{ 0.13f, 0.15f, 0.22f, 1.0f };
    //        flinearcolor Slider_Hovered{ 0.22f, 0.25f, 0.38f, 1.0f };
    //        flinearcolor Slider_Progress{ 0.45f, 0.18f, 0.65f, 1.0f };
    //        flinearcolor Slider_Button{ 0.6f, 0.6f, 1.0f, 1.0f };

    //        flinearcolor ColorPicker_Background{ 0.10f, 0.10f, 0.15f, 0.95f };
    //        flinearcolor Outline{ 1.0f, 1.0f, 1.0f, 1.0f }; // White outline
    //    }

    //    namespace PostRenderer
    //    {
    //        struct DrawList
    //        {
    //            int type = -1; //1 = FilledRect, 2 = TextLeft, 3 = TextCenter, 4 = Draw_Line
    //            fvector2d pos;
    //            fvector2d size;
    //            flinearcolor color;
    //            const wchar_t* name;
    //            bool outline;

    //            fvector2d from;
    //            fvector2d to;
    //            int thickness;
    //        };
    //        DrawList drawlist[128];



    //        void drawFilledRect(fvector2d pos, float w, float h, flinearcolor color)
    //        {
    //            for (int i = 0; i < 128; i++)
    //            {
    //                if (drawlist[i].type == -1)
    //                {
    //                    drawlist[i].type = 1;
    //                    drawlist[i].pos = pos;
    //                    drawlist[i].size = fvector2d{ w, h };
    //                    drawlist[i].color = color;
    //                    return;
    //                }
    //            }
    //        }
    //        void TextLeft(const wchar_t* name, fvector2d pos, flinearcolor color, bool outline)
    //        {
    //            for (int i = 0; i < 128; i++)
    //            {
    //                if (drawlist[i].type == -1)
    //                {
    //                    drawlist[i].type = 2;
    //                    drawlist[i].name = name;
    //                    drawlist[i].pos = pos;
    //                    drawlist[i].outline = outline;
    //                    drawlist[i].color = color;
    //                    return;
    //                }
    //            }
    //        }
    //        void TextCenter(const wchar_t* name, fvector2d pos, flinearcolor color, bool outline)
    //        {
    //            for (int i = 0; i < 128; i++)
    //            {
    //                if (drawlist[i].type == -1)
    //                {
    //                    drawlist[i].type = 3;
    //                    drawlist[i].name = name;
    //                    drawlist[i].pos = pos;
    //                    drawlist[i].outline = outline;
    //                    drawlist[i].color = color;
    //                    return;
    //                }
    //            }
    //        }
    //        void Draw_Line(fvector2d from, fvector2d to, int thickness, flinearcolor color)
    //        {
    //            for (int i = 0; i < 128; i++)
    //            {
    //                if (drawlist[i].type == -1)
    //                {
    //                    drawlist[i].type = 4;
    //                    drawlist[i].from = from;
    //                    drawlist[i].to = to;
    //                    drawlist[i].thickness = thickness;
    //                    drawlist[i].color = color;
    //                    return;
    //                }
    //            }
    //        }
    //    }

    //    ucanvas* canvas;


    //    bool hover_element = false;
    //    fvector2d menu_pos = fvector2d{ 0, 0 };
    //    float offset_x = 0.0f;
    //    float offset_y = 0.0f;

    //    fvector2d first_element_pos = fvector2d{ 0, 0 };

    //    fvector2d last_element_pos = fvector2d{ 0, 0 };
    //    fvector2d last_element_size = fvector2d{ 0, 0 };

    //    int current_element = -1;
    //    fvector2d current_element_pos = fvector2d{ 0, 0 };
    //    fvector2d current_element_size = fvector2d{ 0, 0 };
    //    int elements_count = 0;

    //    bool sameLine = false;

    //    bool pushY = false;
    //    float pushYvalue = 0.0f;

    //    void SetupCanvas(ucanvas* _canvas)
    //    {
    //        canvas = _canvas;
    //    }

    //    void Draw_Line(fvector2d from, fvector2d to, int thickness, flinearcolor color)
    //    {
    //        canvas->k2_drawline(fvector2d{ from.x, from.y }, fvector2d{ to.x, to.y }, thickness, color);
    //    }
    //    void drawFilledRect(fvector2d initial_pos, float w, float h, flinearcolor color)
    //    {
    //        for (float i = 0.0f; i < h; i += 1.0f)
    //            canvas->k2_drawline(fvector2d{ initial_pos.x, initial_pos.y + i }, fvector2d{ initial_pos.x + w, initial_pos.y + i }, 1.0f, color);
    //    }
    //    void DrawGradientLine(fvector2d screenpos_a, fvector2d screenpos_b, flinearcolor color_a, flinearcolor color_c, flinearcolor color_b, float thickness, int num_segments)
    //    {
    //        for (int i = 0; i < num_segments; i++)
    //        {
    //            float t1 = static_cast<float>(i) / num_segments;
    //            float t2 = static_cast<float>(i + 1) / num_segments;

    //            fvector2d start = screenpos_a + (screenpos_b - screenpos_a) * t1;
    //            fvector2d end = screenpos_a + (screenpos_b - screenpos_a) * t2;

    //            float t_mid = (t1 + t2) / 2.0f;

    //            flinearcolor color;

    //            if (t_mid <= 0.5f)
    //            {
    //                float u = 2.0f * t_mid;  // Maps t_mid [0, 0.5] to u [0, 1]
    //                color.r = color_a.r * (1.0f - u) + color_c.r * u;
    //                color.g = color_a.g * (1.0f - u) + color_c.g * u;
    //                color.b = color_a.b * (1.0f - u) + color_c.b * u;
    //                color.a = color_a.a * (1.0f - u) + color_c.a * u;
    //            }
    //            else
    //            {
    //                float v = 2.0f * (t_mid - 0.5f);  // Maps t_mid [0.5, 1] to v [0, 1]
    //                color.r = color_c.r * (1.0f - v) + color_b.r * v;
    //                color.g = color_c.g * (1.0f - v) + color_b.g * v;
    //                color.b = color_c.b * (1.0f - v) + color_b.b * v;
    //                color.a = color_c.a * (1.0f - v) + color_b.a * v;
    //            }

    //            canvas->k2_drawline(start, end, thickness, color);
    //        }
    //    }

    //    // DrawGradientLine(startPos, endPos, red, green, blue, 2.0f, 20);
    //    void drawGradientFilledRect(fvector2d initial_pos, float w, float h, flinearcolor color_a, flinearcolor color_c, flinearcolor color_b, int num_segments)
    //    {
    //        for (float i = 0.0f; i < h; i += 1.0f)
    //            DrawGradientLine(fvector2d{ initial_pos.x, initial_pos.y + i }, fvector2d{ initial_pos.x + w, initial_pos.y + i }, color_a, color_c, color_b, 1.0f, num_segments);
    //    }

    //    void drawGradientFilledRectVertical(fvector2d initial_pos, float w, float h, flinearcolor color_a, flinearcolor color_c, flinearcolor color_b, int num_segments)
    //    {
    //        for (float i = 0.0f; i < w; i += 1.0f)
    //            DrawGradientLine(fvector2d{ initial_pos.x + i, initial_pos.y }, fvector2d{ initial_pos.x + i, initial_pos.y + h }, color_a, color_c, color_b, 1.0f, num_segments);
    //    }


    //    void draw_filled_rect(ucanvas* canvas, float x, float y, float width, float height, flinearcolor color) {
    //        for (float i = 0; i < height; i++) {
    //            canvas->k2_drawline(
    //                { x, y + i },
    //                { x + width, y + i },
    //                1.0f,
    //                color
    //            );
    //        }
    //    }

    //    void draw_rect(ucanvas* canvas, float x, float y, float width, float height, flinearcolor color) {
    //        canvas->k2_drawline({ x, y }, { x + width, y }, 1.0f, color);
    //        canvas->k2_drawline({ x + width, y }, { x + width, y + height }, 1.0f, color);
    //        canvas->k2_drawline({ x + width, y + height }, { x, y + height }, 1.0f, color);
    //        canvas->k2_drawline({ x, y + height }, { x, y }, 1.0f, color);
    //    }

    //    fvector2d CursorPos()
    //    {
    //        POINT cursorPos;
    //        GetCursorPos(&cursorPos);
    //        return fvector2d{ (float)cursorPos.x, (float)cursorPos.y };
    //    }
    //    bool MouseInZone(fvector2d pos, fvector2d size)
    //    {
    //        fvector2d cursor_pos = CursorPos();

    //        if (cursor_pos.x > pos.x && cursor_pos.y > pos.y)
    //            if (cursor_pos.x < pos.x + size.x && cursor_pos.y < pos.y + size.y)
    //                return true;

    //        return false;
    //    }

     /*   void Draw_Cursor(bool menu_opened)
        {
            if (menu_opened)
            {
                fvector2d cursorPos = CursorPos();
                drawFilledRect(fvector2d(cursorPos.x - 5, cursorPos.y - 5), 10, 10, flinearcolor(255, 255, 255, 255));
            }
        }*/

        //    /*void SameLine()
        //    {
        //        sameLine = true;
        //    }*/
        //    void PushNextElementY(float y, bool from_last_element = true)
        //    {
        //        pushY = true;
        //        if (from_last_element)
        //            pushYvalue = last_element_pos.y + last_element_size.y + y;
        //        else
        //            pushYvalue = y;
        //    }
        //    void NextColumn(float x)
        //    {
        //        offset_x = x;
        //        PushNextElementY(first_element_pos.y, false);
        //    }
        //    void ClearFirstPos()
        //    {
        //        first_element_pos = fvector2d{ 0, 0 };
        //    }

        //    void GetColor(flinearcolor* color, float* r, float* g, float* b, float* a)
        //    {
        //        *r = color->r;
        //        *g = color->g;
        //        *b = color->b;
        //        *a = color->a;
        //    }
        //    UINT32 GetColorUINT(int r, int g, int b, int a)
        //    {
        //        UINT32 result = (BYTE(a) << 24) + (BYTE(r) << 16) + (BYTE(g) << 8) + BYTE(b);
        //        return result;
        //    }
        //    void DrawFilledCircle(fvector2d pos, float r, flinearcolor color)
        //    {
        //        float smooth = 0.07f;

        //        double PI = 3.14159265359;
        //        int size = (int)(2.0f * PI / smooth) + 1;

        //        float angle = 0.0f;
        //        int i = 0;

        //        for (; angle < 2 * PI; angle += smooth, i++)
        //        {
        //            Draw_Line(fvector2d{ pos.x, pos.y }, fvector2d{ pos.x + cosf(angle) * r, pos.y + sinf(angle) * r }, 1.0f, color);
        //        }
        //    }
        //    void DrawCircle(fvector2d pos, int radius, int numSides, flinearcolor Color)
        //    {
        //        float PI = 3.1415927f;

        //        float Step = PI * 2.0 / numSides;
        //        int Count = 0;
        //        fvector2d V[128];
        //        for (float a = 0; a < PI * 2.0; a += Step) {
        //            float X1 = radius * cos(a) + pos.x;
        //            float Y1 = radius * sin(a) + pos.y;
        //            float X2 = radius * cos(a + Step) + pos.x;
        //            float Y2 = radius * sin(a + Step) + pos.y;
        //            V[Count].x = X1;
        //            V[Count].y = Y1;
        //            V[Count + 1].x = X2;
        //            V[Count + 1].y = Y2;
        //            //Draw_Line(fvector2d{ pos.x, pos.y }, fvector2d{ X2, Y2 }, 1.0f, Color); // Points from Centre to ends of circle
        //            Draw_Line(fvector2d{ V[Count].x, V[Count].y }, fvector2d{ X2, Y2 }, 1.0f, Color);// Circle Around
        //        }
        //    }

        //    fvector2d dragPos;
        //    bool Window(ucanvas* canvas, uobject* font, fstring title, fstring domain, fvector2d* pos, fvector2d size, bool isOpen)
        //    {
        //        elements_count = 0;

        //        if (!isOpen)
        //            return false;

        //        bool isHovered = MouseInZone(fvector2d{ pos->x, pos->y }, size);

        //        //Drop last element
        //        if (current_element != -1 && !GetAsyncKeyState(0x1))
        //        {
        //            current_element = -1;
        //        }

        //        // Removed drag functionality to keep menu fixed in position

        //        offset_x = 0.0f; offset_y = 0.0f;
        //        menu_pos = fvector2d{ pos->x, pos->y };
        //        first_element_pos = fvector2d{ 0, 0 };
        //        current_element_pos = fvector2d{ 0, 0 };
        //        current_element_size = fvector2d{ 0, 0 };

        //        // Ana menü arka planı - sadece temel arka plan
        //        drawFilledRect(fvector2d(pos->x, pos->y), size.x, size.y, RGBtoFLC(0.06f, 0.06f, 0.06f));

        //        menu::offset_x = 20;
        //        menu::offset_y = 20;

        //        return true;
        //    }

        //    bool ButtonTab(ucanvas* canvas, uobject* font, const wchar_t* name, fvector2d size, bool active)
        //    {
        //        elements_count++;

        //        fvector2d padding = fvector2d{ 0, 0 };
        //        fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
        //        if (sameLine)
        //        {
        //            pos.x = last_element_pos.x + last_element_size.x + offset_x;
        //            pos.y = last_element_pos.y;
        //        }
        //        if (pushY)
        //        {
        //            pos.y = pushYvalue;
        //            pushY = false;
        //            pushYvalue = 0.0f;
        //            offset_y = pos.y - menu_pos.y;
        //        }
        //        bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, size);

        //        if (!sameLine)
        //            offset_y += size.y + padding.y;

        //        fvector2d textPos = fvector2d{ pos.x + size.x / 2, pos.y + size.y / 2 };

        //        //Bg
        //        if (active)
        //        {
        //            drawFilledRect(fvector2d(pos.x, pos.y), size.x, size.y, RGBtoFLC(6, 6, 6));
        //            drawFilledRect(fvector2d(pos.x + 1, pos.y + 1), size.x - 2, size.y - 2, RGBtoFLC(2, 2, 2));

        //            drawFilledRect(fvector2d(pos.x + size.x - 3, pos.y + 7), 2, 21, RGBtoFLC(0, 145, 255));
        //            draw_text77(canvas, font, name, RGBtoFLC(0, 145, 255), { pos.x + 10, pos.y + 15 });

        //            canvas->k2_drawtext(font, name, textPos, fvector2d(0.98, 0.98), RGBtoFLC(0, 145, 255), 0.0f, RGBtoFLC(0, 0, 0), fvector2d(0, 0), true, true, false, RGBtoFLC(0, 0, 0));
        //        }
        //        else if (isHovered)
        //        {
        //            canvas->k2_drawtext(font, name, textPos, fvector2d(0.98, 0.98), RGBtoFLC(120, 120, 120), 0.0f, RGBtoFLC(0, 0, 0), fvector2d(0, 0), true, true, false, RGBtoFLC(0, 0, 0));
        //            hover_element = true;
        //        }
        //        else
        //        {
        //            canvas->k2_drawtext(font, name, textPos, fvector2d(0.98, 0.98), RGBtoFLC(60, 60, 60), 0.0f, RGBtoFLC(0, 0, 0), fvector2d(0, 0), true, true, false, RGBtoFLC(0, 0, 0));
        //        }

        //        sameLine = false;
        //        last_element_pos = pos;
        //        last_element_size = size;
        //        if (first_element_pos.x == 0.0f)
        //            first_element_pos = pos;

        //        if (isHovered && input::is_mouse_clicked(0, elements_count, false))
        //            return true;

        //        return false;
        //    }

        //    void SectionWrapper(ucanvas* canvas, uobject* font, fstring name, fvector2d size)
        //    {
        //        fvector2d padding = fvector2d{ 0, 0 };
        //        fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
        //        if (sameLine)
        //        {
        //            pos.x = menu_pos.x + padding.x + offset_x;
        //            pos.y = menu_pos.y + padding.y + offset_y;
        //        }

        //        drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, RGBtoFLC(6, 6, 6));
        //        drawFilledRect(fvector2d{ pos.x + 1, pos.y + 1 }, size.x - 2, size.y - 2, RGBtoFLC(2, 2, 2));

        //        canvas->k2_drawtext(font, name, fvector2d(pos.x + 10, pos.y + 15), fvector2d(1.1, 1.1), RGBtoFLC(0, 145, 255), 0.0f, RGBtoFLC(0, 0, 0), fvector2d(0, 0), false, true, false, RGBtoFLC(0, 0, 0));

        //        menu::offset_y += 27;

        //        sameLine = false;
        //    }

        //    static float cursor_x = 0;
        //    static float cursor_y = 0;
        //    static float same_line_offset = 0;

        //    void SetCursorPos(float x, float y) {
        //        cursor_x = x;
        //        cursor_y = y;
        //        same_line_offset = 0;
        //    }

        //    void NewLine(float spacing = 15.0f) {
        //        cursor_y += spacing;
        //        same_line_offset = 0;
        //    }

        //    void SameLine(float offset = 0.0f) {
        //        if (offset != 0.0f) {
        //            cursor_x += offset;
        //        }
        //        else {
        //            cursor_x += same_line_offset;
        //        }
        //        same_line_offset = 0;
        //    }

        //    void Checkbox(uobject* font, const wchar_t* name, bool* value, float relative_x, float relative_y)
        //    {
        //        elements_count++;

        //        // --- Yapılandırma ---
        //        float box_size = 12.0f;                     // Kare kutucuğun kenar uzunluğu
        //        float padding_x = 10.0f;
        //        float padding_y = 8.0f;
        //        float text_offset_y = 2.0f;                 // Metni dikeyde hizalamak için ofset
        //        float box_horizontal_offset = 300.0f;       // Metin ile kutucuk arasındaki sabit yatay mesafe (orijinal koddan korundu)

        //        // Renkler (Örn: RGBtoFLC, FLinearColor üreten bir fonksiyondur)
        //        flinearcolor color_border = RGBtoFLC(14, 14, 14);     // Koyu Kenarlık (Dış Çerçeve)
        //        flinearcolor color_unchecked = RGBtoFLC(40, 40, 40);  // Boş olduğundaki iç dolgu rengi
        //        flinearcolor color_checked = RGBtoFLC(0, 145, 255);   // Mavi Vurgu Rengi (Dolu olduğunda)
        //        flinearcolor color_text = RGBtoFLC(255, 255, 255);    // Beyaz Metin

        //        // --- Konum Hesaplamaları (Orijinal düzen mantığı korundu) ---
        //        fvector2d pos = fvector2d{ relative_x, relative_y };

        //        if (sameLine)
        //        {
        //            pos.x = last_element_pos.x + last_element_size.x + padding_x;
        //            pos.y = last_element_pos.y;
        //        }
        //        if (pushY)
        //        {
        //            pos.y = pushYvalue;
        //            pushY = false;
        //            pushYvalue = 0.0f;
        //        }

        //        // Çizim ve Etkileşim Alanı Konumları
        //        fvector2d box_pos = fvector2d{ pos.x + box_horizontal_offset, pos.y };
        //        fvector2d text_pos = fvector2d{ pos.x, pos.y - text_offset_y };

        //        // Etkileşim kontrolü (Kutucuk alanında fare var mı?)
        //        bool isHovered = MouseInZone(box_pos, fvector2d{ box_size, box_size });

        //        // --- Çizim ---

        //        // 1. Metni Çiz
        //        canvas->k2_drawtext(font, name, text_pos, fvector2d(1.0f, 1.0f), color_text, 0.0f, flinearcolor(), fvector2d(0, 0), false, false, false, flinearcolor());

        //        // 2. Kutucuk Çerçevesini Çiz (Koyu renkli 12x12 kare)
        //        // Bu, tüm durumlarda kenarlık görevi görecektir.
        //        drawFilledRect(box_pos, box_size, box_size, color_border);

        //        // 3. İç Dolguyu Çiz
        //        float inner_size = box_size - 2.0f; // 10x10 iç kare
        //        fvector2d inner_pos = fvector2d{ box_pos.x + 1.0f, box_pos.y + 1.0f }; // 1px içeriden başla

        //        if (*value)
        //        {
        //            // KUTUCUK DOLU: Mavi renkle içini doldur
        //            drawFilledRect(inner_pos, inner_size, inner_size, color_checked);
        //        }
        //        else
        //        {
        //            // KUTUCUK BOŞ: Kenarlık renginden biraz daha açık bir gri ile içini doldur.
        //            // Bu, dıştaki koyu çerçeve ile birlikte 'boş' veya 'kontürlü' bir görünüm oluşturur.
        //            drawFilledRect(inner_pos, inner_size, inner_size, color_unchecked);
        //        }

        //        // --- Etkileşim ---
        //        if (isHovered && input::is_mouse_clicked(0, elements_count, false))
        //            *value = !*value;

        //        // --- Düzen Güncelleme ---
        //        if (!sameLine)
        //            offset_y = pos.y + box_size + padding_y - menu_pos.y; // Yeni yüksekliği kullan

        //        sameLine = false;
        //        last_element_pos = pos;
        //        // last_element_size, bir sonraki SameLine öğesinin konumlandırılması için gereklidir.
        //        last_element_size = fvector2d{ box_horizontal_offset + box_size, box_size };
        //        if (first_element_pos.x == 0.0f)
        //            first_element_pos = pos;
        //    }


        //    bool checkbox_enabled[256];

        //    // Yeni versiyon: dışardan y pozisyonu alabiliyoruz
        //    void Combobox(uobject* font, const wchar_t* name, fvector2d size, int* value, float y_offset, const wchar_t* arg, ...)
        //    {
        //        elements_count++;

        //        fvector2d padding = fvector2d{ 14, 30 };
        //        fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };

        //        // Eğer dışardan y_offset verilmişse onu uygula ve pushY / offset_y mantığını devre dışı bırak
        //        if (y_offset >= 0.0f)
        //        {
        //            pos.y = menu_pos.y + y_offset;
        //            pushY = false;      // Combobox kendi kaydırmasını yapmasın
        //            offset_y = pos.y - menu_pos.y; // offset_y’yi y_offset’e göre ayarla
        //        }
        //        else
        //        {
        //            // Normal combobox mantığı
        //            if (pushY)
        //            {
        //                pos.y = pushYvalue;
        //                pushY = false;
        //                pushYvalue = 150.0f;
        //                offset_y = pos.y - menu_pos.y;
        //            }
        //        }

        //        if (sameLine)
        //        {
        //            pos.x = last_element_pos.x + last_element_size.x + padding.x;
        //            pos.y = last_element_pos.y;
        //        }

        //        bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, size);

        //        //Bg
        //        if (isHovered || checkbox_enabled[elements_count])
        //        {
        //            drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, RGBtoFLC(10, 10, 10));
        //            drawFilledRect(fvector2d{ pos.x + 1, pos.y + 1 }, size.x - 2, size.y - 2, RGBtoFLC(3, 3, 3));

        //            hover_element = true;
        //        }
        //        else
        //        {
        //            drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, RGBtoFLC(10, 10, 10));
        //            drawFilledRect(fvector2d{ pos.x + 1, pos.y + 1 }, size.x - 2, size.y - 2, RGBtoFLC(2, 2, 2));
        //        }

        //        if (!sameLine)
        //            offset_y += size.y + padding.y;

        //        //Text (clean, no shadow/outline)
        //        fvector2d textPos = fvector2d{ pos.x - 2.0f, pos.y - size.y + 2.0f };
        //        canvas->k2_drawtext(font, name, textPos, fvector2d(1.0f, 1.0f), RGBtoFLC(255, 255, 255), 0.0f, flinearcolor(), fvector2d(0, 0), false, false, false, flinearcolor());

        //        canvas->k2_drawtext(font, s2wc("+"), fvector2d{ pos.x + size.x - 17, pos.y + size.y / 2 }, fvector2d(1.0f, 1.0f), RGBtoFLC(255, 255, 255), 0.0f, flinearcolor(), fvector2d(0, 0), false, true, false, flinearcolor());

        //        //Elements
        //        bool isHovered2 = false;
        //        fvector2d element_pos = pos;
        //        int num = 0;

        //        if (checkbox_enabled[elements_count])
        //        {
        //            current_element_size.x = element_pos.x - 5.0f;
        //            current_element_size.y = element_pos.y - 5.0f;
        //        }
        //        va_list arguments;
        //        for (va_start(arguments, arg); arg != NULL; arg = va_arg(arguments, const wchar_t*))
        //        {
        //            //Selected Element (clean text)
        //            if (num == *value)
        //            {
        //                fvector2d _textPos = fvector2d{ pos.x + 5, pos.y + size.y / 2 };
        //                canvas->k2_drawtext(font, arg, _textPos, fvector2d(1.0f, 1.0f), RGBtoFLC(255, 255, 255), 0.0f, flinearcolor(), fvector2d(0, 0), false, true, false, flinearcolor());
        //            }

        //            if (checkbox_enabled[elements_count])
        //            {
        //                element_pos.y += 25.0f;

        //                isHovered2 = MouseInZone(fvector2d{ element_pos.x, element_pos.y }, fvector2d{ size.x, 25.0f });
        //                if (isHovered2)
        //                {
        //                    hover_element = true;
        //                    PostRenderer::drawFilledRect(fvector2d{ element_pos.x, element_pos.y }, size.x, 25.0f, RGBtoFLC(4, 4, 4));

        //                    //Click
        //                    if (input::is_mouse_clicked(0, elements_count, false))
        //                    {
        //                        *value = num;
        //                        checkbox_enabled[elements_count] = false;
        //                    }
        //                }
        //                else
        //                {
        //                    PostRenderer::drawFilledRect(fvector2d{ element_pos.x, element_pos.y }, size.x, 25.0f, RGBtoFLC(3, 3, 3));
        //                }

        //                // Element list text (clean white)
        //                PostRenderer::TextLeft(arg, fvector2d{ element_pos.x + 10.0f, element_pos.y + 5.0f }, RGBtoFLC(255, 255, 255), true);
        //            }
        //            num++;
        //        }
        //        va_end(arguments);
        //        if (checkbox_enabled[elements_count])
        //        {
        //            current_element_size.x = element_pos.x + 5.0f;
        //            current_element_size.y = element_pos.y + 5.0f;
        //        }

        //        sameLine = false;
        //        last_element_pos = pos;
        //        last_element_size = size;
        //        if (first_element_pos.x == 0.0f)
        //            first_element_pos = pos;

        //        if (isHovered && input::is_mouse_clicked(0, elements_count, false))
        //        {
        //            checkbox_enabled[elements_count] = !checkbox_enabled[elements_count];
        //        }
        //        if (!isHovered && !isHovered2 && input::is_mouse_clicked(0, elements_count, false))
        //        {
        //            checkbox_enabled[elements_count] = false;
        //        }
        //    }


        //    void SliderFloat(uobject* font, const wchar_t* name, float* value, float min, float max, float relative_x, float relative_y, const char* format = "%.0f")
        //    {
        //        elements_count++;
        //        fvector2d size = fvector2d{ 335, 22.5 };
        //        fvector2d slider_size = fvector2d{ 335, 12.5 };
        //        fvector2d adjust_zone = fvector2d{ 0, 20 };
        //        fvector2d padding = fvector2d{ 10, 5 };
        //        fvector2d pos = fvector2d{ relative_x, relative_y };
        //        if (sameLine)
        //        {
        //            pos.x = last_element_pos.x + last_element_size.x + padding.x;
        //            pos.y = last_element_pos.y;
        //        }
        //        if (pushY)
        //        {
        //            pos.y = pushYvalue;
        //            pushY = false;
        //            pushYvalue = 0.0f;
        //        }
        //        bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y + slider_size.y + padding.y - adjust_zone.y }, fvector2d{ slider_size.x, slider_size.y + adjust_zone.y * 1.5f });

        //        if (!sameLine)
        //            offset_y = pos.y + size.y + padding.y - menu_pos.y;

        //        //Bg - Sade arka plan
        //        if (isHovered || current_element == elements_count)
        //        {
        //            //Drag
        //            if (input::is_mouse_clicked(0, elements_count, true))
        //            {
        //                current_element = elements_count;

        //                fvector2d cursorPos = CursorPos();
        //                *value = ((cursorPos.x - pos.x) * ((max - min) / slider_size.x)) + min;
        //                if (*value < min) *value = min;
        //                if (*value > max) *value = max;
        //            }

        //            // Hover durumunda daha açık arka plan
        //            drawFilledRect(fvector2d{ pos.x, pos.y + slider_size.y + padding.y }, slider_size.x, slider_size.y, RGBtoFLC(20, 20, 20));
        //            drawFilledRect(fvector2d{ pos.x + 1, pos.y + slider_size.y + padding.y + 1 }, slider_size.x - 2, slider_size.y - 2, RGBtoFLC(15, 15, 15));

        //            hover_element = true;
        //        }
        //        else
        //        {
        //            // Normal durumda daha koyu arka plan
        //            drawFilledRect(fvector2d{ pos.x, pos.y + slider_size.y + padding.y }, slider_size.x, slider_size.y, RGBtoFLC(15, 15, 15));
        //            drawFilledRect(fvector2d{ pos.x + 1, pos.y + slider_size.y + padding.y + 1 }, slider_size.x - 2, slider_size.y - 2, RGBtoFLC(10, 10, 10));
        //        }

        //        //Text - Daha sade
        //        fvector2d textPos = fvector2d{ pos.x, pos.y - 2.0f };
        //        canvas->k2_drawtext(font, name, textPos, fvector2d(0.9f, 0.9f), RGBtoFLC(220, 220, 220), 0.0f, flinearcolor(), fvector2d(0, 0), false, false, false, flinearcolor());

        //        //Value - Daha ince ve sade
        //        float oneP = slider_size.x / (max - min);
        //        drawFilledRect(fvector2d{ pos.x + 1, pos.y + slider_size.y + padding.y + 1 }, oneP * (*value - min) - 1, slider_size.y - 2, RGBtoFLC(0, 120, 200));
        //        drawFilledRect(fvector2d{ pos.x + oneP * (*value - min) - 1, pos.y + slider_size.y + padding.y + 1 - 2 }, 3, 16, RGBtoFLC(0, 150, 255));

        //        char buffer[32];
        //        sprintf_s(buffer, format, *value);
        //        canvas->k2_drawtext(font, s2wc(buffer), fvector2d(pos.x + slider_size.x - 8.0f, pos.y - 2.0f), fvector2d(1.0f, 1.0f), RGBtoFLC(255, 255, 255), 0.0f, flinearcolor(), fvector2d(0, 0), true, false, false, flinearcolor());

        //        sameLine = false;
        //        last_element_pos = pos;
        //        last_element_size = size;
        //        if (first_element_pos.x == 0.0f)
        //            first_element_pos = pos;
        //    }



        //    int active_hotkey = -1;
        //    bool already_pressed = false;
        //    std::string VirtualKeyCodeToString(UCHAR virtualKey)
        //    {
        //        UINT scanCode = MapVirtualKey(virtualKey, MAPVK_VK_TO_VSC);
        //        if (virtualKey == VK_LBUTTON)
        //        {
        //            return ("MOUSE0");
        //        }
        //        if (virtualKey == VK_RBUTTON)
        //        {
        //            return ("MOUSE1");
        //        }
        //        if (virtualKey == VK_MBUTTON)
        //        {
        //            return ("MBUTTON");
        //        }
        //        if (virtualKey == VK_XBUTTON1)
        //        {
        //            return ("XBUTTON1");
        //        }
        //        if (virtualKey == VK_XBUTTON2)
        //        {
        //            return ("XBUTTON2");
        //        }


        //        CHAR szName[128];
        //        int result = 0;
        //        switch (virtualKey)
        //        {
        //        case VK_LEFT: case VK_UP: case VK_RIGHT: case VK_DOWN:
        //        case VK_RCONTROL: case VK_RMENU:
        //        case VK_LWIN: case VK_RWIN: case VK_APPS:
        //        case VK_PRIOR: case VK_NEXT:
        //        case VK_END: case VK_HOME:
        //        case VK_INSERT: case VK_DELETE:
        //        case VK_DIVIDE:
        //        case VK_NUMLOCK:
        //            scanCode |= KF_EXTENDED;
        //        default:
        //            result = GetKeyNameTextA(scanCode << 16, szName, 128);
        //        }

        //        return szName;
        //    }
        //    void Hotkey(uobject* font, const char* name, fvector2d size, int* key, float relative_x, float relative_y)
        //    {
        //        elements_count++;
        //        fvector2d padding = fvector2d{ 80, 4 };
        //        fvector2d pos = fvector2d{ relative_x, relative_y };
        //        if (sameLine)
        //        {
        //            pos.x = last_element_pos.x + last_element_size.x + padding.x;
        //            pos.y = last_element_pos.y - padding.y;
        //        }
        //        if (pushY)
        //        {
        //            pos.y = pushYvalue;
        //            pushY = false;
        //            pushYvalue = 0.0f;
        //        }
        //        bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, size);

        //        drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, RGBtoFLC(10, 10, 10));
        //        drawFilledRect(fvector2d{ pos.x + 1, pos.y + 1 }, size.x - 2, size.y - 2, RGBtoFLC(2, 2, 2));

        //        if (!sameLine)
        //            offset_y = pos.y + size.y + padding.y - menu_pos.y;

        //        if (active_hotkey == elements_count)
        //        {
        //            //Text
        //            fvector2d textPos = fvector2d{ pos.x + size.x / 2, pos.y + size.y / 2 };
        //            canvas->k2_drawtext(font, L"...", textPos, fvector2d(0.96, 0.94), RGBtoFLC(60, 60, 60), 0.0f, Colors::Text_Shadow, fvector2d(0, 0), true, true, true, Colors::Text_Outline);

        //            if (!input::is_any_mouse_down())
        //            {
        //                already_pressed = false;
        //            }

        //            if (!already_pressed)
        //            {
        //                for (int code = 0; code < 255; code++)
        //                {
        //                    if (GetAsyncKeyState(code))
        //                    {
        //                        *key = code;
        //                        active_hotkey = -1;
        //                    }
        //                }
        //            }
        //        }
        //        else
        //        {
        //            //Text
        //            fvector2d textPos = fvector2d{ pos.x + size.x / 2, pos.y + size.y / 2 };
        //            canvas->k2_drawtext(font, s2wc(VirtualKeyCodeToString(*key).c_str()), textPos, fvector2d(0.99, 0.99), RGBtoFLC(60, 60, 60), 0.0f, Colors::Text_Shadow, fvector2d(0, 0), true, true, true, Colors::Text_Outline);


        //            if (isHovered)
        //            {
        //                if (input::is_mouse_clicked(0, elements_count, false))
        //                {
        //                    already_pressed = true;
        //                    active_hotkey = elements_count;

        //                    //Queue Fix
        //                    for (int code = 0; code < 255; code++)
        //                        if (GetAsyncKeyState(code)) {}
        //                }
        //            }
        //            else
        //            {
        //                if (input::is_mouse_clicked(0, elements_count, false))
        //                {
        //                    active_hotkey = -1;
        //                }
        //            }
        //        }

        //        sameLine = false;
        //        last_element_pos = pos;
        //        last_element_size = size;
        //        if (first_element_pos.x == 0.0f)
        //            first_element_pos = pos;
        //    }

        //    bool draw_color_picker(ucanvas* canvas, uobject* font, const wchar_t* label, flinearcolor& color, fvector2d pos, fvector2d mouse_pos, bool mouse_clicked) {
        //        const float hue_slider_width = 100.0f;
        //        const float hue_slider_height = 7.0f;
        //        const float sb_picker_size = 75.0f;
        //        const float alpha_slider_width = hue_slider_width;
        //        const float alpha_slider_height = 7.0f;
        //        const float preview_box_size = 15.0f;
        //        const float spacing = 5.0f;

        //        static bool hue_dragging = false;
        //        static bool sb_dragging = false;
        //        static bool alpha_dragging = false;

        //        static float hue = 0.0f;
        //        static float saturation = 1.0f;
        //        static float brightness = 1.0f;

        //        float thickness = 2.0f; // grosor del texto
        //        float width_scale = 1.0f; // escala de anchura
        //        float height_scale = 0.8f; // escala de altura
        //        float text_scale = 1.1f; // escala del tamaÃ±o de la fuente

        //        bool value_changed = false;

        //        for (int i = 0; i < hue_slider_width; i++) {
        //            float h = (float)i / hue_slider_width;
        //            flinearcolor color_at_hue = HSVtoRGB(h, 1.0f, 1.0f);
        //            draw_filled_rect(canvas, pos.x + i, pos.y, 1.0f, hue_slider_height, color_at_hue); // raya arriba
        //        }
        //        draw_rect(canvas, pos.x, pos.y, hue_slider_width, hue_slider_height, RGBtoFLC(5, 5, 5));

        //        if (mouse_clicked && mouse_pos.x >= pos.x && mouse_pos.x <= pos.x + hue_slider_width &&
        //            mouse_pos.y >= pos.y && mouse_pos.y <= pos.y + hue_slider_height) {
        //            hue_dragging = true;
        //        }
        //        if (hue_dragging) {
        //            if (mouse_clicked) {
        //                hue = (mouse_pos.x - pos.x) / hue_slider_width;
        //                hue = std::clamp(hue, 0.0f, 1.0f);
        //                value_changed = true;
        //            }
        //            else {
        //                hue_dragging = false;
        //            }
        //        }

        //        fvector2d sb_pos = { pos.x, pos.y + hue_slider_height + spacing };

        //        for (int y = 0; y < sb_picker_size; y++) {
        //            for (int x = 0; x < sb_picker_size; x++) {
        //                float s = (float)x / sb_picker_size;
        //                float b = 1.0f - (float)y / sb_picker_size;
        //                flinearcolor sb_color = HSVtoRGB(hue, s, b);
        //                draw_filled_rect(canvas, sb_pos.x + x, sb_pos.y + y, 1.0f, 1.0f, sb_color);
        //            }
        //        }
        //        draw_rect(canvas, sb_pos.x, sb_pos.y, sb_picker_size, sb_picker_size, RGBtoFLC(5, 5, 5));

        //        if (mouse_clicked && mouse_pos.x >= sb_pos.x && mouse_pos.x <= sb_pos.x + sb_picker_size &&
        //            mouse_pos.y >= sb_pos.y && mouse_pos.y <= sb_pos.y + sb_picker_size) {
        //            sb_dragging = true;
        //        }
        //        if (sb_dragging) {
        //            if (mouse_clicked) {
        //                saturation = (mouse_pos.x - sb_pos.x) / sb_picker_size;
        //                brightness = 1.0f - (mouse_pos.y - sb_pos.y) / sb_picker_size;
        //                saturation = std::clamp(saturation, 0.0f, 1.0f);
        //                brightness = std::clamp(brightness, 0.0f, 1.0f);
        //                value_changed = true;
        //            }
        //            else {
        //                sb_dragging = false;
        //            }
        //        }

        //        fvector2d alpha_pos = { pos.x, sb_pos.y + sb_picker_size + spacing };

        //        for (int i = 0; i < alpha_slider_width; i++) {
        //            float alpha = (float)i / alpha_slider_width;
        //            flinearcolor alpha_color = HSVtoRGB(hue, saturation, brightness);
        //            alpha_color.a = alpha;
        //            draw_filled_rect(canvas, alpha_pos.x + i, alpha_pos.y, 1.0f, alpha_slider_height, alpha_color);
        //        }
        //        draw_rect(canvas, alpha_pos.x, alpha_pos.y, alpha_slider_width, alpha_slider_height, RGBtoFLC(5, 5, 5));

        //        if (mouse_clicked && mouse_pos.x >= alpha_pos.x && mouse_pos.x <= alpha_pos.x + alpha_slider_width &&
        //            mouse_pos.y >= alpha_pos.y && mouse_pos.y <= alpha_pos.y + alpha_slider_height) {
        //            alpha_dragging = true;
        //        }
        //        if (alpha_dragging) {
        //            if (mouse_clicked) {
        //                color.a = (mouse_pos.x - alpha_pos.x) / alpha_slider_width;
        //                color.a = std::clamp(color.a, 0.0f, 1.0f);
        //                value_changed = true;
        //            }
        //            else {
        //                alpha_dragging = false;
        //            }
        //        }

        //        flinearcolor final_color = HSVtoRGB(hue, saturation, brightness);
        //        color.r = final_color.r;
        //        color.g = final_color.g;
        //        color.b = final_color.b;

        //        fvector2d preview_pos = { pos.x + hue_slider_width + spacing, pos.y };
        //        draw_filled_rect(canvas, preview_pos.x, preview_pos.y, preview_box_size, preview_box_size, { color.r, color.g, color.b, color.a });
        //        draw_rect(canvas, preview_pos.x, preview_pos.y, preview_box_size, preview_box_size, RGBtoFLC(5, 5, 5));

        //        return value_changed;
        //    }
        //    bool draw_color_picker1(ucanvas* canvas, uobject* font, const wchar_t* label, flinearcolor& color, fvector2d pos, fvector2d mouse_pos, bool mouse_clicked) {
        //        const float picker_width = 100.0f;
        //        const float slider_height = 8.0f;
        //        const float sb_square_size = 80.0f;
        //        const float spacing = 4.0f;

        //        static bool hue_dragging = false;
        //        static bool sb_dragging = false;
        //        static bool saturation_dragging = false;
        //        static bool brightness_dragging = false;
        //        static bool alpha_dragging = false;

        //        static float hue = 0.0f;
        //        static float saturation = 1.0f;
        //        static float brightness = 1.0f;

        //        bool value_changed = false;

        //        const float picker_height = sb_square_size + (slider_height * 4) + (5 * spacing);
        //        draw_filled_rect(canvas, pos.x - 5.0f, pos.y - 5.0f, picker_width + 10.0f, picker_height + 10.0f, { 0.08f, 0.08f, 0.08f, 1.0f });
        //        draw_rect(canvas, pos.x - 5.0f, pos.y - 5.0f, picker_width + 10.0f, picker_height + 10.0f, { 0.2f, 0.2f, 0.2f, 1.0f });

        //        fvector2d sb_square_pos = { pos.x, pos.y };
        //        for (int y = 0; y < sb_square_size; y++) {
        //            for (int x = 0; x < sb_square_size; x++) {
        //                float s = (float)x / sb_square_size;
        //                float b = 1.0f - (float)y / sb_square_size;
        //                flinearcolor sb_color = HSVtoRGB(hue, s, b);
        //                draw_filled_rect(canvas, sb_square_pos.x + x, sb_square_pos.y + y, 1.0f, 1.0f, sb_color);
        //            }
        //        }
        //        draw_rect(canvas, sb_square_pos.x, sb_square_pos.y, sb_square_size, sb_square_size, { 0.5f, 0.5f, 0.5f, 1.0f });

        //        if (mouse_clicked && mouse_pos.x >= sb_square_pos.x && mouse_pos.x <= sb_square_pos.x + sb_square_size &&
        //            mouse_pos.y >= sb_square_pos.y && mouse_pos.y <= sb_square_pos.y + sb_square_size) {
        //            sb_dragging = true;
        //        }
        //        if (sb_dragging) {
        //            if (mouse_clicked) {
        //                saturation = (mouse_pos.x - sb_square_pos.x) / sb_square_size;
        //                brightness = 1.0f - (mouse_pos.y - sb_square_pos.y) / sb_square_size;
        //                saturation = std::clamp(saturation, 0.0f, 1.0f);
        //                brightness = std::clamp(brightness, 0.0f, 1.0f);
        //                value_changed = true;
        //            }
        //            else {
        //                sb_dragging = false;
        //            }
        //        }

        //        fvector2d hue_pos = { pos.x, sb_square_pos.y + sb_square_size + spacing };
        //        for (int i = 0; i < picker_width; i++) {
        //            float h = (float)i / picker_width;
        //            flinearcolor hue_color = HSVtoRGB(h, 1.0f, 1.0f);
        //            draw_filled_rect(canvas, hue_pos.x + i, hue_pos.y, 1.0f, slider_height, hue_color);
        //        }
        //        draw_rect(canvas, hue_pos.x, hue_pos.y, picker_width, slider_height, { 0.5f, 0.5f, 0.5f, 1.0f });

        //        if (mouse_clicked && mouse_pos.x >= hue_pos.x && mouse_pos.x <= hue_pos.x + picker_width &&
        //            mouse_pos.y >= hue_pos.y && mouse_pos.y <= hue_pos.y + slider_height) {
        //            hue_dragging = true;
        //        }
        //        if (hue_dragging) {
        //            if (mouse_clicked) {
        //                hue = (mouse_pos.x - hue_pos.x) / picker_width;
        //                hue = std::clamp(hue, 0.0f, 1.0f);
        //                value_changed = true;
        //            }
        //            else {
        //                hue_dragging = false;
        //            }
        //        }

        //        fvector2d saturation_pos = { hue_pos.x, hue_pos.y + slider_height + spacing };
        //        for (int i = 0; i < picker_width; i++) {
        //            float s = (float)i / picker_width;
        //            flinearcolor saturation_color = HSVtoRGB(hue, s, brightness);
        //            draw_filled_rect(canvas, saturation_pos.x + i, saturation_pos.y, 1.0f, slider_height, saturation_color);
        //        }
        //        draw_rect(canvas, saturation_pos.x, saturation_pos.y, picker_width, slider_height, { 0.5f, 0.5f, 0.5f, 1.0f });

        //        if (mouse_clicked && mouse_pos.x >= saturation_pos.x && mouse_pos.x <= saturation_pos.x + picker_width &&
        //            mouse_pos.y >= saturation_pos.y && mouse_pos.y <= saturation_pos.y + slider_height) {
        //            saturation_dragging = true;
        //        }
        //        if (saturation_dragging) {
        //            if (mouse_clicked) {
        //                saturation = (mouse_pos.x - saturation_pos.x) / picker_width;
        //                saturation = std::clamp(saturation, 0.0f, 1.0f);
        //                value_changed = true;
        //            }
        //            else {
        //                saturation_dragging = false;
        //            }
        //        }

        //        fvector2d brightness_pos = { saturation_pos.x, saturation_pos.y + slider_height + spacing };
        //        for (int i = 0; i < picker_width; i++) {
        //            float b = (float)i / picker_width;
        //            flinearcolor brightness_color = HSVtoRGB(hue, saturation, b);
        //            draw_filled_rect(canvas, brightness_pos.x + i, brightness_pos.y, 1.0f, slider_height, brightness_color);
        //        }
        //        draw_rect(canvas, brightness_pos.x, brightness_pos.y, picker_width, slider_height, { 0.5f, 0.5f, 0.5f, 1.0f });

        //        if (mouse_clicked && mouse_pos.x >= brightness_pos.x && mouse_pos.x <= brightness_pos.x + picker_width &&
        //            mouse_pos.y >= brightness_pos.y && mouse_pos.y <= brightness_pos.y + slider_height) {
        //            brightness_dragging = true;
        //        }
        //        if (brightness_dragging) {
        //            if (mouse_clicked) {
        //                brightness = (mouse_pos.x - brightness_pos.x) / picker_width;
        //                brightness = std::clamp(brightness, 0.0f, 1.0f);
        //                value_changed = true;
        //            }
        //            else {
        //                brightness_dragging = false;
        //            }
        //        }

        //        fvector2d alpha_pos = { brightness_pos.x, brightness_pos.y + slider_height + spacing };
        //        for (int i = 0; i < picker_width; i++) {
        //            float alpha = (float)i / picker_width;
        //            flinearcolor alpha_color = HSVtoRGB(hue, saturation, brightness);
        //            alpha_color.a = alpha;
        //            draw_filled_rect(canvas, alpha_pos.x + i, alpha_pos.y, 1.0f, slider_height, alpha_color);
        //        }
        //        draw_rect(canvas, alpha_pos.x, alpha_pos.y, picker_width, slider_height, { 0.5f, 0.5f, 0.5f, 1.0f });

        //        if (mouse_clicked && mouse_pos.x >= alpha_pos.x && mouse_pos.x <= alpha_pos.x + picker_width &&
        //            mouse_pos.y >= alpha_pos.y && mouse_pos.y <= alpha_pos.y + slider_height) {
        //            alpha_dragging = true;
        //        }
        //        if (alpha_dragging) {
        //            if (mouse_clicked) {
        //                color.a = (mouse_pos.x - alpha_pos.x) / picker_width;
        //                color.a = std::clamp(color.a, 0.0f, 1.0f);
        //                value_changed = true;
        //            }
        //            else {
        //                alpha_dragging = false;
        //            }
        //        }

        //        flinearcolor final_color = HSVtoRGB(hue, saturation, brightness);
        //        color.r = final_color.r;
        //        color.g = final_color.g;
        //        color.b = final_color.b;

        //        return value_changed;
        //    }

        //    void draw_line(ucanvas* canvas, const fvector2d& start, const fvector2d& end, const flinearcolor& color) {
        //        if (!canvas) return;

        //        canvas->k2_drawline(
        //            fvector2d{ start.x, start.y },
        //            fvector2d{ end.x, end.y },
        //            1.0f,
        //            color
        //        );
        //    }

        //    void draw_glow_effect33(ucanvas* canvas, float x, float y, float width, float height, float glow_size, flinearcolor glow_color = { 0.04f, 0.04f, 0.04f, 1.0f }) {
        //        for (float i = glow_size; i > 0; --i) {
        //            float alpha = glow_color.a * (i / glow_size);
        //            flinearcolor fade_color = flinearcolor(glow_color.r, glow_color.g, glow_color.b, alpha);

        //            draw_filled_rect(canvas, x - i, y - i, width + (2 * i), height + (2 * i), fade_color);
        //        }
        //    }

        //    bool draw_color_picker_menu(ucanvas* canvas, uobject* font, const wchar_t* label, flinearcolor& color, fvector2d pos, fvector2d mouse_pos, bool mouse_clicked) {
        //        static bool picker_open = false;
        //        static fvector2d picker_pos = pos;
        //        const float box_width = 30.0f;
        //        const float box_height = 10.5f;
        //        const float outline_thickness = 1.0f;

        //        auto min = [](float a, float b) { return (a < b) ? a : b; };
        //        auto max = [](float a, float b) { return (a > b) ? a : b; };

        //        if (picker_open && mouse_clicked &&
        //            (mouse_pos.x < picker_pos.x - 500.0f || mouse_pos.x > picker_pos.x + box_width + 500.0f ||
        //                mouse_pos.y < picker_pos.y - 500.0f || mouse_pos.y > picker_pos.y + box_height + 500.0f)) {
        //            picker_open = false;
        //        }

        //        draw_glow_effect33(canvas, pos.x, pos.y, box_width, box_height, 2.0f, RGBtoFLC(6, 6, 6));
        //        draw_filled_rect(canvas, pos.x, pos.y, box_width, box_height, color);

        //        if (mouse_clicked &&
        //            mouse_pos.x >= pos.x && mouse_pos.x <= pos.x + box_width &&
        //            mouse_pos.y >= pos.y && mouse_pos.y <= pos.y + box_height) {
        //            picker_open = !picker_open;
        //            picker_pos = { pos.x, pos.y + box_height + 10.0f };
        //        }

        //        if (picker_open) {
        //            return draw_color_picker1(canvas, font, label, color, picker_pos, mouse_pos, mouse_clicked);
        //        }

        //        return false;
        //    }

        //    bool draw_color_picker_menu1(ucanvas* canvas, uobject* font, const wchar_t* label, flinearcolor& color, fvector2d pos, fvector2d mouse_pos, bool mouse_clicked) {
        //        static bool picker_open = false;
        //        static fvector2d picker_pos = pos;
        //        const float box_width = 30.0f;
        //        const float box_height = 10.5f;
        //        const float outline_thickness = 1.0f;

        //        auto min = [](float a, float b) { return (a < b) ? a : b; };
        //        auto max = [](float a, float b) { return (a > b) ? a : b; };

        //        if (picker_open && mouse_clicked &&
        //            (mouse_pos.x < picker_pos.x - 500.0f || mouse_pos.x > picker_pos.x + box_width + 500.0f ||
        //                mouse_pos.y < picker_pos.y - 500.0f || mouse_pos.y > picker_pos.y + box_height + 500.0f)) {
        //            picker_open = false;
        //        }

        //        draw_glow_effect33(canvas, pos.x, pos.y, box_width, box_height, 2.0f, RGBtoFLC(6, 6, 6));
        //        draw_filled_rect(canvas, pos.x, pos.y, box_width, box_height, color);

        //        if (mouse_clicked &&
        //            mouse_pos.x >= pos.x && mouse_pos.x <= pos.x + box_width &&
        //            mouse_pos.y >= pos.y && mouse_pos.y <= pos.y + box_height) {
        //            picker_open = !picker_open;
        //            picker_pos = { pos.x, pos.y + box_height + 10.0f };
        //        }

        //        if (picker_open) {
        //            return draw_color_picker1(canvas, font, label, color, picker_pos, mouse_pos, mouse_clicked);
        //        }

        //        return false;
        //    }

        //    // END
        //    void Text(const wchar_t* text, bool center = false, bool outline = false)
        //    {
        //        elements_count++;

        //        float size = 24;
        //        fvector2d padding = fvector2d{ 1,3 };
        //        fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
        //        if (sameLine)
        //        {
        //            pos.x = last_element_pos.x + last_element_size.x + padding.x;
        //            pos.y = last_element_pos.y;
        //        }
        //        if (pushY)
        //        {
        //            pos.y = pushYvalue;
        //            pushY = false;
        //            pushYvalue = 0.0f;
        //            offset_y = pos.y - menu_pos.y;
        //        }

        //        if (!sameLine)
        //            offset_y += size + padding.y;

        //        //Text
        //        fvector2d textPos = fvector2d{ pos.x + 5.0f, pos.y };
        //        if (center)
        //            TextCenter(text, textPos, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, outline);
        //        else
        //            TextLeft(text, textPos, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, outline);

        //        sameLine = false;
        //        last_element_pos = pos;
        //        //last_element_size = size;
        //        if (first_element_pos.x == 0.0f)
        //            first_element_pos = pos;
        //    }
        //    bool Button(const wchar_t* name, fvector2d size)
        //    {
        //        elements_count++;

        //        fvector2d padding = fvector2d{ 15, 6 };
        //        fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
        //        if (sameLine)
        //        {
        //            pos.x = last_element_pos.x + last_element_size.x + padding.x;
        //            pos.y = last_element_pos.y;
        //        }
        //        if (pushY)
        //        {
        //            pos.y = pushYvalue;
        //            pushY = false;
        //            pushYvalue = 0.0f;
        //            offset_y = pos.y - menu_pos.y;
        //        }
        //        bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, size);

        //        //Bg
        //        if (isHovered)
        //        {
        //            drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, Colors::Button_Hovered);
        //            hover_element = true;
        //        }
        //        else
        //        {
        //            drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, Colors::Button_Idle);
        //        }

        //        if (!sameLine)
        //            offset_y += size.y + padding.y;

        //        //Text
        //        fvector2d textPos = fvector2d{ pos.x + size.x / 2, pos.y + size.y / 2 };
        //        //if (!TextOverlapedFromActiveElement(textPos))
        //        TextCenter(name, textPos, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);


        //        sameLine = false;
        //        last_element_pos = pos;
        //        last_element_size = size;
        //        if (first_element_pos.x == 0.0f)
        //            first_element_pos = pos;

        //        if (isHovered && input::is_mouse_clicked(0, elements_count, false))
        //            return true;

        //        return false;
        //    }
        //    void SliderInt(uobject* font, const wchar_t* name, int* value, int min, int max)
        //    {
        //        elements_count++;
        //        fvector2d size = fvector2d{ 335, 22.5 };
        //        fvector2d slider_size = fvector2d{ 335, 12.5 };
        //        fvector2d adjust_zone = fvector2d{ 0, 20 };
        //        fvector2d padding = fvector2d{ 10, 5 };
        //        fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };

        //        if (sameLine)
        //        {
        //            pos.x = last_element_pos.x + last_element_size.x + padding.x;
        //            pos.y = last_element_pos.y;
        //        }
        //        if (pushY)
        //        {
        //            pos.y = pushYvalue;
        //            pushY = false;
        //            pushYvalue = 0.0f;
        //            offset_y = pos.y - menu_pos.y;
        //        }

        //        bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y + slider_size.y + padding.y - adjust_zone.y }, fvector2d{ slider_size.x, slider_size.y + adjust_zone.y * 1.5f });

        //        if (!sameLine)
        //            offset_y += size.y + padding.y;

        //        if (isHovered || current_element == elements_count)
        //        {
        //            if (input::is_mouse_clicked(0, elements_count, true))
        //            {
        //                current_element = elements_count;

        //                fvector2d cursorPos = CursorPos();
        //                int newVal = ((cursorPos.x - pos.x) * ((max - min) / slider_size.x)) + min;
        //                *value = std::clamp(newVal, min, max);
        //            }

        //            drawFilledRect(fvector2d{ pos.x, pos.y + slider_size.y + padding.y }, slider_size.x, slider_size.y, RGBtoFLC(10, 10, 10));
        //            drawFilledRect(fvector2d{ pos.x + 1, pos.y + slider_size.y + padding.y + 1 }, slider_size.x - 2, slider_size.y - 2, RGBtoFLC(6, 6, 6));
        //            hover_element = true;
        //        }
        //        else
        //        {
        //            drawFilledRect(fvector2d{ pos.x, pos.y + slider_size.y + padding.y }, slider_size.x, slider_size.y, RGBtoFLC(10, 10, 10));
        //            drawFilledRect(fvector2d{ pos.x + 1, pos.y + slider_size.y + padding.y + 1 }, slider_size.x - 2, slider_size.y - 2, RGBtoFLC(5, 5, 5));
        //        }

        //        fvector2d textPos = fvector2d{ pos.x, pos.y - 2.0f };
        //        canvas->k2_drawtext(font, name, textPos, fvector2d(0.98, 0.98), RGBtoFLC(255, 255, 255), 0.0f, Colors::Text_Shadow, fvector2d(0, 0), false, false, true, Colors::Text_Outline);

        //        float oneP = slider_size.x / (float)(max - min);
        //        drawFilledRect(fvector2d{ pos.x + 1, pos.y + slider_size.y + padding.y + 1 }, oneP * (*value - min) - 2, slider_size.y - 2, RGBtoFLC(0, 145, 255));
        //        drawFilledRect(fvector2d{ pos.x + oneP * (*value - min), pos.y + slider_size.y + padding.y + 1 - 3 }, 17, 18, RGBtoFLC(7, 7, 7));

        //        char buffer[32];
        //        sprintf_s(buffer, "%d", *value);
        //        canvas->k2_drawtext(font, s2wc(buffer), fvector2d(pos.x + slider_size.x - 8.0f, pos.y - 2.0f), fvector2d(0.98, 0.98), RGBtoFLC(255, 255, 255), 0.0f, Colors::Text_Shadow, fvector2d(0, 0), true, false, true, Colors::Text_Outline);

        //        sameLine = false;
        //        last_element_pos = pos;
        //        last_element_size = size;
        //        if (first_element_pos.x == 0.0f)
        //            first_element_pos = pos;
        //    }

        //    int active_picker = -1;
        //    flinearcolor saved_color;
        //    bool ColorPixel(fvector2d pos, fvector2d size, flinearcolor* original, flinearcolor color)
        //    {
        //        PostRenderer::drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, color);

        //        //Выбранный цвет
        //        if (original->r == color.r && original->g == color.g && original->b == color.b)
        //        {
        //            PostRenderer::Draw_Line(fvector2d{ pos.x, pos.y }, fvector2d{ pos.x + size.x - 1, pos.y }, 1.0f, flinearcolor{ 0.0f, 0.0f, 0.0f, 1.0f });
        //            PostRenderer::Draw_Line(fvector2d{ pos.x, pos.y + size.y - 1 }, fvector2d{ pos.x + size.x - 1, pos.y + size.y - 1 }, 1.0f, flinearcolor{ 0.0f, 0.0f, 0.0f, 1.0f });
        //            PostRenderer::Draw_Line(fvector2d{ pos.x, pos.y }, fvector2d{ pos.x, pos.y + size.y - 1 }, 1.0f, flinearcolor{ 0.0f, 0.0f, 0.0f, 1.0f });
        //            PostRenderer::Draw_Line(fvector2d{ pos.x + size.x - 1, pos.y }, fvector2d{ pos.x + size.x - 1, pos.y + size.y - 1 }, 1.0f, flinearcolor{ 0.0f, 0.0f, 0.0f, 1.0f });
        //        }

        //        //Смена цвета
        //        bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, size);
        //        if (isHovered)
        //        {
        //            if (input::is_mouse_clicked(0, elements_count, false))
        //                *original = color;
        //        }

        //        return true;
        //    }
        //    void ColorPicker(const wchar_t* name, flinearcolor* color)
        //    {
        //        elements_count++;

        //        float size = 25;
        //        float xsize = 5;
        //        fvector2d padding = fvector2d{ 15, 10 };
        //        fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
        //        if (sameLine)
        //        {
        //            pos.x = last_element_pos.x + last_element_size.x + padding.x;
        //            pos.y = last_element_pos.y;
        //        }
        //        if (pushY)
        //        {
        //            pos.y = pushYvalue;
        //            pushY = false;
        //            pushYvalue = 0.0f;
        //            offset_y = pos.y - menu_pos.y;
        //        }
        //        bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, fvector2d{ size, size });

        //        if (!sameLine)
        //            offset_y += size + padding.y;

        //        if (active_picker == elements_count)
        //        {
        //            hover_element = true;

        //            float sizePickerX = 250;
        //            float sizePickerY = 250;
        //            bool isHoveredPicker = MouseInZone(fvector2d{ pos.x, pos.y }, fvector2d{ sizePickerX, sizePickerY - 60 });

        //            //Background
        //            PostRenderer::drawFilledRect(fvector2d{ pos.x, pos.y }, sizePickerX, sizePickerY - 65, Colors::ColorPicker_Background);

        //            fvector2d pixelSize = fvector2d{ sizePickerX / 12, sizePickerY / 12 };

        //            //0
        //            {
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 174 / 255.f, 235 / 255.f, 253 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 136 / 255.f, 225 / 255.f, 251 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 108 / 255.f, 213 / 255.f, 250 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 89 / 255.f, 175 / 255.f, 213 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 76 / 255.f, 151 / 255.f, 177 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 60 / 255.f, 118 / 255.f, 140 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 43 / 255.f, 85 / 255.f, 100 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 32 / 255.f, 62 / 255.f, 74 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 255 / 255.f, 255 / 255.f, 255 / 255.f, 1.0f });
        //            }
        //            //1
        //            {
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 175 / 255.f, 205 / 255.f, 252 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 132 / 255.f, 179 / 255.f, 252 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 90 / 255.f, 152 / 255.f, 250 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 55 / 255.f, 120 / 255.f, 250 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 49 / 255.f, 105 / 255.f, 209 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 38 / 255.f, 83 / 255.f, 165 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 28 / 255.f, 61 / 255.f, 120 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 20 / 255.f, 43 / 255.f, 86 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 247 / 255.f, 247 / 255.f, 247 / 255.f, 1.0f });
        //            }
        //            //2
        //            {
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 153 / 255.f, 139 / 255.f, 250 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 101 / 255.f, 79 / 255.f, 249 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 64 / 255.f, 50 / 255.f, 230 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 54 / 255.f, 38 / 255.f, 175 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 39 / 255.f, 31 / 255.f, 144 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 32 / 255.f, 25 / 255.f, 116 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 21 / 255.f, 18 / 255.f, 82 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 16 / 255.f, 13 / 255.f, 61 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 228 / 255.f, 228 / 255.f, 228 / 255.f, 1.0f });
        //            }
        //            //3
        //            {
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 194 / 255.f, 144 / 255.f, 251 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 165 / 255.f, 87 / 255.f, 249 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 142 / 255.f, 57 / 255.f, 239 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 116 / 255.f, 45 / 255.f, 184 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 92 / 255.f, 37 / 255.f, 154 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 73 / 255.f, 29 / 255.f, 121 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 53 / 255.f, 21 / 255.f, 88 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 37 / 255.f, 15 / 255.f, 63 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 203 / 255.f, 203 / 255.f, 203 / 255.f, 1.0f });
        //            }
        //            //4
        //            {
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 224 / 255.f, 162 / 255.f, 197 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 210 / 255.f, 112 / 255.f, 166 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 199 / 255.f, 62 / 255.f, 135 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 159 / 255.f, 49 / 255.f, 105 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 132 / 255.f, 41 / 255.f, 89 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 104 / 255.f, 32 / 255.f, 71 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 75 / 255.f, 24 / 255.f, 51 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 54 / 255.f, 14 / 255.f, 36 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 175 / 255.f, 175 / 255.f, 175 / 255.f, 1.0f });
        //            }
        //            //5
        //            {
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 235 / 255.f, 175 / 255.f, 176 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 227 / 255.f, 133 / 255.f, 135 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 219 / 255.f, 87 / 255.f, 88 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 215 / 255.f, 50 / 255.f, 36 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 187 / 255.f, 25 / 255.f, 7 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 149 / 255.f, 20 / 255.f, 6 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 107 / 255.f, 14 / 255.f, 4 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 77 / 255.f, 9 / 255.f, 3 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 144 / 255.f, 144 / 255.f, 144 / 255.f, 1.0f });
        //            }
        //            //6
        //            {
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 241 / 255.f, 187 / 255.f, 171 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 234 / 255.f, 151 / 255.f, 126 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 229 / 255.f, 115 / 255.f, 76 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 227 / 255.f, 82 / 255.f, 24 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 190 / 255.f, 61 / 255.f, 15 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 150 / 255.f, 48 / 255.f, 12 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 107 / 255.f, 34 / 255.f, 8 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 79 / 255.f, 25 / 255.f, 6 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 113 / 255.f, 113 / 255.f, 113 / 255.f, 1.0f });
        //            }
        //            //7
        //            {
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 245 / 255.f, 207 / 255.f, 169 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 240 / 255.f, 183 / 255.f, 122 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 236 / 255.f, 159 / 255.f, 74 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 234 / 255.f, 146 / 255.f, 37 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 193 / 255.f, 111 / 255.f, 28 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 152 / 255.f, 89 / 255.f, 22 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 110 / 255.f, 64 / 255.f, 16 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 80 / 255.f, 47 / 255.f, 12 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 82 / 255.f, 82 / 255.f, 82 / 255.f, 1.0f });
        //            }
        //            //8
        //            {
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 247 / 255.f, 218 / 255.f, 170 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 244 / 255.f, 200 / 255.f, 124 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 241 / 255.f, 182 / 255.f, 77 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 239 / 255.f, 174 / 255.f, 44 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 196 / 255.f, 137 / 255.f, 34 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 154 / 255.f, 108 / 255.f, 27 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 111 / 255.f, 77 / 255.f, 19 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 80 / 255.f, 56 / 255.f, 14 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 54 / 255.f, 54 / 255.f, 54 / 255.f, 1.0f });
        //            }
        //            //9
        //            {
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 254 / 255.f, 243 / 255.f, 187 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 253 / 255.f, 237 / 255.f, 153 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 253 / 255.f, 231 / 255.f, 117 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 254 / 255.f, 232 / 255.f, 85 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 242 / 255.f, 212 / 255.f, 53 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 192 / 255.f, 169 / 255.f, 42 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 138 / 255.f, 120 / 255.f, 30 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 101 / 255.f, 87 / 255.f, 22 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 29 / 255.f, 29 / 255.f, 29 / 255.f, 1.0f });
        //            }
        //            //10
        //            {
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 247 / 255.f, 243 / 255.f, 185 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 243 / 255.f, 239 / 255.f, 148 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 239 / 255.f, 232 / 255.f, 111 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 235 / 255.f, 229 / 255.f, 76 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 208 / 255.f, 200 / 255.f, 55 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 164 / 255.f, 157 / 255.f, 43 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 118 / 255.f, 114 / 255.f, 31 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 86 / 255.f, 82 / 255.f, 21 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 9 / 255.f, 9 / 255.f, 9 / 255.f, 1.0f });
        //            }
        //            //11
        //            {
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 218 / 255.f, 232 / 255.f, 182 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 198 / 255.f, 221 / 255.f, 143 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 181 / 255.f, 210 / 255.f, 103 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 154 / 255.f, 186 / 255.f, 76 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 130 / 255.f, 155 / 255.f, 64 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 102 / 255.f, 121 / 255.f, 50 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 74 / 255.f, 88 / 255.f, 36 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 54 / 255.f, 64 / 255.f, 26 / 255.f, 1.0f });
        //                ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 0 / 255.f, 0 / 255.f, 0 / 255.f, 1.0f });
        //            }



        //            if (isHoveredPicker)
        //            {
        //                if (input::is_mouse_clicked(0, elements_count, false))
        //                {

        //                }
        //            }
        //            else
        //            {
        //                if (input::is_mouse_clicked(0, elements_count, false))
        //                {
        //                    active_picker = -1;
        //                    //hover_element = false;
        //                }
        //            }
        //        }
        //        else
        //        {
        //            //Bg
        //            if (isHovered)
        //            {
        //                drawFilledRect(fvector2d{ pos.x, pos.y }, size, size, Colors::Checkbox_Hovered);
        //                hover_element = true;
        //            }
        //            else
        //            {
        //                drawFilledRect(fvector2d{ pos.x, pos.y }, size, size, Colors::Checkbox_Idle);
        //            }

        //            //Color
        //            drawFilledRect(fvector2d{ pos.x + 4, pos.y + 4 }, size - 8, size - 8, *color);

        //            //Text
        //            fvector2d textPos = fvector2d{ pos.x + size + 5.0f, pos.y - xsize + 6.0f };
        //            TextLeft(name, textPos, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);

        //            if (isHovered && input::is_mouse_clicked(0, elements_count, false))
        //            {
        //                saved_color = *color;
        //                active_picker = elements_count;
        //            }
        //        }


        //        sameLine = false;
        //        last_element_pos = pos;
        //        //last_element_size = size;
        //        if (first_element_pos.x == 0.0f)
        //            first_element_pos = pos;
        //    }


        //    void Render(uobject* font)
        //    {
        //        for (int i = 0; i < 128; i++)
        //        {
        //            if (PostRenderer::drawlist[i].type != -1)
        //            {
        //                
        //                if (PostRenderer::drawlist[i].type == 1)
        //                {
        //                    menu::drawFilledRect(PostRenderer::drawlist[i].pos, PostRenderer::drawlist[i].size.x, PostRenderer::drawlist[i].size.y, PostRenderer::drawlist[i].color);
        //                }
        //                
        //                else if (PostRenderer::drawlist[i].type == 2)
        //                {
        //                    canvas->k2_drawtext(font, (const wchar_t*)PostRenderer::drawlist[i].name, PostRenderer::drawlist[i].pos, fvector2d(0.98, 0.98), PostRenderer::drawlist[i].color, 0.0f, Colors::Text_Shadow, fvector2d(0, 0), false, false, PostRenderer::drawlist[i].outline, Colors::Text_Outline);
        //                }
        //                
        //                else if (PostRenderer::drawlist[i].type == 3)
        //                {
        //                    menu::TextCenter((const wchar_t*)PostRenderer::drawlist[i].name, PostRenderer::drawlist[i].pos, PostRenderer::drawlist[i].color, PostRenderer::drawlist[i].outline);
        //                }
        //                
        //                else if (PostRenderer::drawlist[i].type == 4)
        //                {
        //                    Draw_Line(PostRenderer::drawlist[i].from, PostRenderer::drawlist[i].to, PostRenderer::drawlist[i].thickness, PostRenderer::drawlist[i].color);
        //                }

        //                PostRenderer::drawlist[i].type = -1;
        //            }
        //        }
        //    }
        //}

static flinearcolor watermark_bg_color = { 0.02f, 0.03f, 0.05f, 0.95f };

// sns our watermark accent
//static flinearcolor watermark_accent_color = { 0.0f, 0.71f, 0.94f, 1.0f }; // #00B4F0 - matches your blue accent

// sysinfo watermark accent
static flinearcolor watermark_accent_color = { 0.55f, 0.25f, 0.95f, 1.0f }; // VacsenSoftware purple

static utexture2d* watermark_icon = nullptr;

namespace menu
{

    flinearcolor RGBtoFLC(float r, float g, float b)
    {
        return { r / 255, g / 255, b / 255, 1 };
    }

    tarray<uint8_t> create_buffer_from_data(const uint8_t* data, size_t size)
    {
        tarray<uint8_t> buffer;
        for (size_t i = 0; i < size; i++) {
            buffer.add(data[i]);
        }
        return buffer;
    }

 
    static int current_fps = 0;
    static int current_ping = 0;
    static int frame_count = 0;
    static float fps_timer = 0.0f;
    static float ping_update_timer = 0.0f;
    static float delta_time = 0.0f;
    static std::chrono::steady_clock::time_point last_frame_time = std::chrono::steady_clock::now();

    void DrawWatermark(ucanvas* canvas, uobject* font) {
        if (!canvas || !font) return;

        fvector2d pos = { globals::misc::watermark_pos_x, globals::misc::watermark_pos_y };
        fvector2d scale = { globals::misc::watermark_scale, globals::misc::watermark_scale };

        const wchar_t* rgb_brand = L"";
        float time = (float)GetTickCount64() / 100.0f;
        float blink = (sinf(time) + 1.0f) * 0.5f;
        float global_hue = fmodf(time / 36.0f, 1.0f);
        flinearcolor base = HSVtoRGB(global_hue, 1.0f, blink);
        for (int ci = 0; ci < (int)wcslen(rgb_brand); ci++) {
            wchar_t single[2] = { rgb_brand[ci], L'\0' };
            canvas->k2_drawtext(font, single, fvector2d{ pos.x + ci * 14.0f, pos.y }, scale, base, 0.0f, RGBtoFLC(0, 0, 0), fvector2d(0, 0), false, true, false, RGBtoFLC(0, 0, 0));
        }
    }
    //void DrawWatermark(ucanvas* canvas, uobject* font) {

    //    fvector2d pos = { 60.0f, 60.0f };
    //    fvector2d scale = { 1.3f, 1.3f };

    //   
    //    flinearcolor rainbowColors[] = {
    //        {0.78f, 0.08f, 0.52f, 1.0f},  // Koyu pembe
    //        {0.86f, 0.07f, 0.23f, 1.0f},  // Kırmızı
    //        {0.95f, 0.34f, 0.13f, 1.0f},  // Turuncu
    //        {0.99f, 0.73f, 0.00f, 1.0f},  // Altın sarısı
    //        {0.55f, 0.71f, 0.00f, 1.0f},  // Yeşil
    //        {0.00f, 0.62f, 0.85f, 1.0f},  // Mavi
    //        {0.29f, 0.00f, 0.51f, 1.0f}   // Mor
    //    };

    //    
    //    const wchar_t* text = L"sentinalhvh.club";
    //    int textLength = wcslen(text);

    //    for (int i = 0; i < textLength; i++) {
    //        fvector2d charPos = { pos.x + (i * 15.0f), pos.y };

    //      
    //        int colorIndex = i % 7;
    //        flinearcolor charColor = rainbowColors[colorIndex];

    //        // Tek karakter için string oluştur
    //        wchar_t singleChar[2] = { text[i], L'\0' };
    //        fstring charText = fstring(singleChar);

    //        canvas->k2_drawtext(
    //            font,
    //            charText,
    //            charPos,
    //            scale,
    //            charColor,
    //            0.0f,
    //            { 0,0,0,0 },
    //            { 0,0 },
    //            false,
    //            false,
    //            true,
    //            { 0,0,0,1.0f }
    //        );
    //    }
    //}

    //void DrawWatermark(ucanvas* canvas, uobject* font) {
    //    if (!canvas || !font) return;

    //    const float watermark_width = 320.0f;
    //    const float watermark_height = 60.0f;
    //    const float margin = 10.0f;

    // 
    //    fvector2d watermark_pos = { 1590.0f, 10.0f }; 

    //  
    //    SYSTEMTIME system_time;
    //    GetLocalTime(&system_time);
    //    wchar_t time_buffer[64];
    //    swprintf(time_buffer, 64, L"%02d:%02d:%02d",
    //        system_time.wHour, system_time.wMinute, system_time.wSecond);

    //  
    //    wchar_t date_buffer[32];
    //    const wchar_t* months[12] = { L"Jan", L"Feb", L"Mar", L"Apr", L"May", L"Jun",
    //                                 L"Jul", L"Aug", L"Sep", L"Oct", L"Nov", L"Dec" };
    //    swprintf(date_buffer, 32, L"%s %d", months[system_time.wMonth - 1], system_time.wDay);

    //    // Get local player ping using the real method
    //    int real_ping = 0;
    //    if (character) {
    //        uintptr_t player_state_ptr = memory::read<uintptr_t>((uintptr_t)character + offsets::player_state);
    //        if (player_state_ptr) {
    //            real_ping = memory::read<uint16_t>(player_state_ptr + offsets::get_ping);
    //        }
    //    }

    //    // Use real performance data
    //    int real_fps = current_fps;
    //    int real_tick = 64;

    //    // === WATERMARK BACKGROUND ===
    //    // Main background with subtle gradient
    //    drawFilledRect(watermark_pos, watermark_width, watermark_height, RGBtoFLC(2.666, 3.332, 4.165));
    //    drawFilledRect(fvector2d{ watermark_pos.x + 1, watermark_pos.y + 1 },
    //        watermark_width - 2, watermark_height - 2, RGBtoFLC(1.25, 1.416, 1.749));

    //    // Accent bar on left
    //    drawFilledRect(fvector2d{ watermark_pos.x, watermark_pos.y }, 3.0f, watermark_height, watermark_accent_color);

    //    // Separator lines
    //    drawFilledRect(fvector2d{ watermark_pos.x, watermark_pos.y + watermark_height - 1 },
    //        watermark_width, 1, RGBtoFLC(3.499, 4.498, 5.831));

    //    // === CONTENT LAYOUT ===
    //    const float icon_size = 40.0f;
    //    const float text_left_margin = 85.0f;
    //    const float icon_left_margin = watermark_width - icon_size - 15.0f;

    //    canvas->k2_drawtext(
    //        font,
    //        L"POWERED BY SYSINFO",
    //        fvector2d{ watermark_pos.x + text_left_margin, watermark_pos.y + 12 },
    //        fvector2d(1.1f, 1.0f),
    //        RGBtoFLC(255, 255, 255),
    //        0.0f,
    //        RGBtoFLC(0, 0, 0),
    //        fvector2d(0, 0),
    //        false,
    //        true,
    //        false,
    //        RGBtoFLC(0, 0, 0)
    //    );

    //    // Real date
    //    canvas->k2_drawtext(
    //        font,
    //        date_buffer,
    //        fvector2d{ watermark_pos.x + text_left_margin + 125, watermark_pos.y + 14 },
    //        fvector2d(0.85f, 0.75f),
    //        RGBtoFLC(100, 100, 100),
    //        0.0f,
    //        RGBtoFLC(0, 0, 0),
    //        fvector2d(0, 0),
    //        false,
    //        true,
    //        false,
    //        RGBtoFLC(0, 0, 0)
    //    );

    //    // Real system info line
    //    wchar_t info_buffer[128];
    //    swprintf(info_buffer, 128, L"%d FPS | %d MS | %d TICK", real_fps, real_ping, real_tick);

    //    canvas->k2_drawtext(
    //        font,
    //        info_buffer,
    //        fvector2d{ watermark_pos.x + text_left_margin, watermark_pos.y + 35 },
    //        fvector2d(0.8f, 0.75f),
    //        RGBtoFLC(180, 180, 180),
    //        0.0f,
    //        RGBtoFLC(0, 0, 0),
    //        fvector2d(0, 0),
    //        false,
    //        true,
    //        false,
    //        RGBtoFLC(0, 0, 0)
    //    );

    //    // Current time
    //    canvas->k2_drawtext(
    //        font,
    //        time_buffer,
    //        fvector2d{ watermark_pos.x + text_left_margin + 125, watermark_pos.y + 35 },
    //        fvector2d(0.8f, 0.75f),
    //        watermark_accent_color,
    //        0.0f,
    //        RGBtoFLC(0, 0, 0),
    //        fvector2d(0, 0),
    //        false,
    //        true,
    //        false,
    //        RGBtoFLC(0, 0, 0)
    //    );

    //    drawFilledRect(fvector2d{ watermark_pos.x + icon_left_margin, watermark_pos.y + 15 },
    //        icon_size - 10, icon_size - 10, watermark_accent_color);
    //}


    void Spacing11(float amount) {
        offset_y += amount;
    }

    void TextCenter(const wchar_t* name, fvector2d pos, flinearcolor color, bool outline)
    {
        for (int i = 0; i < 128; i++)
        {
            if (drawlist[i].type == -1)
            {
                drawlist[i].type = 3;
                drawlist[i].name = name;
                drawlist[i].pos = pos;
                drawlist[i].outline = outline;
                drawlist[i].color = color;
                return;
            }
        }
    }

    flinearcolor HSVtoRGB(float h, float s, float v) {
        float r, g, b;

        int i = static_cast<int>(h * 6);
        float f = h * 6 - i;
        float p = v * (1 - s);
        float q = v * (1 - f * s);
        float t = v * (1 - (1 - f) * s);

        switch (i % 6) {
        case 0: r = v; g = t; b = p; break;
        case 1: r = q; g = v; b = p; break;
        case 2: r = p; g = v; b = t; break;
        case 3: r = p; g = q; b = v; break;
        case 4: r = t; g = p; b = v; break;
        case 5: r = v; g = p; b = q; break;
        default: r = g = b = 0.0f;
        }

        return flinearcolor{ r, g, b, 1.0f };

    }

    // sns our colors

    //std::string& handle_input(ucanvas* canvas, uobject* font, fvector2d input_pos, float width, fvector2d mouse_pos, bool mouse_clicked, std::string& current_value) {
    //    static bool input_active = false;
    //    static bool key_pressed[256] = {};
    //    static auto last_backspace_time = std::chrono::steady_clock::now();

    //    const float input_width = width;
    //    const float input_height = 35.0f;

    //    // KOCAMAN TIKLAMA ALANI
    //    bool is_hovered = (mouse_pos.x >= input_pos.x - 30 && mouse_pos.x <= input_pos.x + input_width + 30 &&
    //        mouse_pos.y >= input_pos.y - 20 && mouse_pos.y <= input_pos.y + input_height + 20);

    //    // DAHA BÜYÜK VE BELİRGİN BOX
    //    drawFilledRect(fvector2d{ input_pos.x, input_pos.y }, input_width, input_height, RGBtoFLC(25, 30, 40));

    //    // BELİRGİN BORDER - drawFilledRect ile yap
    //    if (input_active) {
    //        // Aktifken KALIN MAVİ BORDER (4 pixel)
    //        drawFilledRect(fvector2d{ input_pos.x, input_pos.y }, input_width, 4, RGBtoFLC(0, 150, 255)); // ÜST
    //        drawFilledRect(fvector2d{ input_pos.x, input_pos.y + input_height - 4 }, input_width, 4, RGBtoFLC(0, 150, 255)); // ALT
    //        drawFilledRect(fvector2d{ input_pos.x, input_pos.y }, 4, input_height, RGBtoFLC(0, 150, 255)); // SOL
    //        drawFilledRect(fvector2d{ input_pos.x + input_width - 4, input_pos.y }, 4, input_height, RGBtoFLC(0, 150, 255)); // SAĞ
    //    }
    //    else {
    //        // Normalde GRI BORDER (3 pixel)
    //        drawFilledRect(fvector2d{ input_pos.x, input_pos.y }, input_width, 3, RGBtoFLC(80, 90, 110)); // ÜST
    //        drawFilledRect(fvector2d{ input_pos.x, input_pos.y + input_height - 3 }, input_width, 3, RGBtoFLC(80, 90, 110)); // ALT
    //        drawFilledRect(fvector2d{ input_pos.x, input_pos.y }, 3, input_height, RGBtoFLC(80, 90, 110)); // SOL
    //        drawFilledRect(fvector2d{ input_pos.x + input_width - 3, input_pos.y }, 3, input_height, RGBtoFLC(80, 90, 110)); // SAĞ

    //        // HOVER EFEKTİ
    //        if (is_hovered) {
    //            drawFilledRect(fvector2d{ input_pos.x, input_pos.y }, input_width, 3, RGBtoFLC(100, 120, 140));
    //            drawFilledRect(fvector2d{ input_pos.x, input_pos.y + input_height - 3 }, input_width, 3, RGBtoFLC(100, 120, 140));
    //            drawFilledRect(fvector2d{ input_pos.x, input_pos.y }, 3, input_height, RGBtoFLC(100, 120, 140));
    //            drawFilledRect(fvector2d{ input_pos.x + input_width - 3, input_pos.y }, 3, input_height, RGBtoFLC(100, 120, 140));
    //        }
    //    }

    //    // YAZIYI SOLA HİZALA ve DAHA BÜYÜK YAP
    //    std::string display_text = current_value.empty() ? "Write message..." : current_value;
    //    std::wstring wdisplay_text = std::wstring(display_text.begin(), display_text.end());

    //    fvector2d textPos = fvector2d{ input_pos.x + 15, input_pos.y + input_height / 2 - 12 };

    //    if (current_value.empty()) {
    //        canvas->k2_drawtext(font, wdisplay_text.c_str(), textPos, fvector2d(0.9f, 0.9f), RGBtoFLC(120, 130, 150), 0.0f,
    //            RGBtoFLC(0, 0, 0), fvector2d(0, 0), false, true, false, RGBtoFLC(0, 0, 0));
    //    }
    //    else {
    //        canvas->k2_drawtext(font, wdisplay_text.c_str(), textPos, fvector2d(0.9f, 0.9f), RGBtoFLC(220, 220, 220), 0.0f,
    //            RGBtoFLC(0, 0, 0), fvector2d(0, 0), false, true, false, RGBtoFLC(0, 0, 0));
    //    }

    //    // TIKLAMA MANTIĞI - ÇOK DAHA KOLAY
    //    if (mouse_clicked) {
    //        if (is_hovered) {
    //            input_active = true;
    //        }
    //        else {
    //            input_active = false;
    //        }
    //    }

    //    // INPUT HANDLING (aynı)
    //    if (input_active) {
    //        auto now = std::chrono::steady_clock::now();
    //        auto backspace_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_backspace_time);

    //        bool backspace_held = (GetAsyncKeyState(VK_BACK) & 0x8000);

    //        if (backspace_held && backspace_elapsed.count() > 50) {
    //            if (!current_value.empty()) {
    //                current_value.pop_back();
    //            }
    //            last_backspace_time = now;
    //        }

    //        for (int vk = 0; vk < 256; ++vk) {
    //            bool down = GetAsyncKeyState(vk) & 0x8000;

    //            if (down && !key_pressed[vk]) {
    //                key_pressed[vk] = true;
    //                last_backspace_time = now;

    //                if (vk == VK_BACK && !current_value.empty()) {
    //                    current_value.pop_back();
    //                }
    //                else if (vk == VK_RETURN || vk == VK_ESCAPE) {
    //                    input_active = false;
    //                }
    //                else if (current_value.size() < 100) {
    //                    BYTE keyboard_state[256];
    //                    GetKeyboardState(keyboard_state);

    //                    WCHAR unicode_chars[4] = {};
    //                    int result = ToUnicode(vk, MapVirtualKey(vk, MAPVK_VK_TO_VSC), keyboard_state, unicode_chars, 4, 0);

    //                    if (result > 0) {
    //                        char mb_char[8] = {};
    //                        WideCharToMultiByte(CP_UTF8, 0, unicode_chars, result, mb_char, sizeof(mb_char), nullptr, nullptr);
    //                        current_value += mb_char;
    //                    }
    //                    else if (vk == VK_SPACE) {
    //                        current_value += ' ';
    //                    }
    //                }
    //            }
    //            else if (!down) {
    //                key_pressed[vk] = false;
    //            }
    //        }
    //    }

    //    return current_value;
    //}

    // sysinfo colors

    std::string& handle_input(ucanvas* canvas, uobject* font, fvector2d input_pos, float width, fvector2d mouse_pos, bool mouse_clicked, std::string& current_value) {
        static bool input_active = false;
        static bool key_pressed[256] = {};
        static auto last_backspace_time = std::chrono::steady_clock::now();

        const float input_width = width;
        const float input_height = 35.0f;

        // KOCAMAN TIKLAMA ALANI
        bool is_hovered = (mouse_pos.x >= input_pos.x - 30 && mouse_pos.x <= input_pos.x + input_width + 30 &&
            mouse_pos.y >= input_pos.y - 20 && mouse_pos.y <= input_pos.y + input_height + 20);

        // DAHA BÜYÜK VE BELİRGİN BOX
        drawFilledRect(fvector2d{ input_pos.x, input_pos.y }, input_width, input_height, RGBtoFLC(25, 30, 40));

        // BELİRGİN BORDER - drawFilledRect ile yap
        if (input_active) {
            // Aktifken KALIN MOR BORDER (4 pixel)
            drawFilledRect(fvector2d{ input_pos.x, input_pos.y }, input_width, 4, RGBtoFLC(100, 180, 255)); // ÜST
            drawFilledRect(fvector2d{ input_pos.x, input_pos.y + input_height - 4 }, input_width, 4, RGBtoFLC(100, 180, 255)); // ALT
            drawFilledRect(fvector2d{ input_pos.x, input_pos.y }, 4, input_height, RGBtoFLC(100, 180, 255)); // SOL
            drawFilledRect(fvector2d{ input_pos.x + input_width - 4, input_pos.y }, 4, input_height, RGBtoFLC(100, 180, 255)); // SAĞ
        }
        else {
            // Normalde GRI BORDER (3 pixel)
            drawFilledRect(fvector2d{ input_pos.x, input_pos.y }, input_width, 3, RGBtoFLC(80, 90, 110)); // ÜST
            drawFilledRect(fvector2d{ input_pos.x, input_pos.y + input_height - 3 }, input_width, 3, RGBtoFLC(80, 90, 110)); // ALT
            drawFilledRect(fvector2d{ input_pos.x, input_pos.y }, 3, input_height, RGBtoFLC(80, 90, 110)); // SOL
            drawFilledRect(fvector2d{ input_pos.x + input_width - 3, input_pos.y }, 3, input_height, RGBtoFLC(80, 90, 110)); // SAĞ

            // HOVER EFEKTİ
            if (is_hovered) {
                drawFilledRect(fvector2d{ input_pos.x, input_pos.y }, input_width, 3, RGBtoFLC(100, 120, 140));
                drawFilledRect(fvector2d{ input_pos.x, input_pos.y + input_height - 3 }, input_width, 3, RGBtoFLC(100, 120, 140));
                drawFilledRect(fvector2d{ input_pos.x, input_pos.y }, 3, input_height, RGBtoFLC(100, 120, 140));
                drawFilledRect(fvector2d{ input_pos.x + input_width - 3, input_pos.y }, 3, input_height, RGBtoFLC(100, 120, 140));
            }
        }

        // YAZIYI SOLA HİZALA ve DAHA BÜYÜK YAP
        std::string display_text = current_value.empty() ? "Write message..." : current_value;
        std::wstring wdisplay_text = std::wstring(display_text.begin(), display_text.end());

        fvector2d textPos = fvector2d{ input_pos.x + 15, input_pos.y + input_height / 2 - 12 };

        if (current_value.empty()) {
            canvas->k2_drawtext(font, wdisplay_text.c_str(), textPos, fvector2d(0.9f, 0.9f), RGBtoFLC(120, 130, 150), 0.0f,
                RGBtoFLC(0, 0, 0), fvector2d(0, 0), false, true, false, RGBtoFLC(0, 0, 0));
        }
        else {
            canvas->k2_drawtext(font, wdisplay_text.c_str(), textPos, fvector2d(0.9f, 0.9f), RGBtoFLC(220, 220, 220), 0.0f,
                RGBtoFLC(0, 0, 0), fvector2d(0, 0), false, true, false, RGBtoFLC(0, 0, 0));
        }

        // TIKLAMA MANTIĞI - ÇOK DAHA KOLAY
        if (mouse_clicked) {
            if (is_hovered) {
                input_active = true;
            }
            else {
                input_active = false;
            }
        }

        // INPUT HANDLING
        if (input_active) {
            auto now = std::chrono::steady_clock::now();
            auto backspace_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_backspace_time);

            bool backspace_held = (GetAsyncKeyState(VK_BACK) & 0x8000);

            if (backspace_held && backspace_elapsed.count() > 50) {
                if (!current_value.empty()) {
                    current_value.pop_back();
                }
                last_backspace_time = now;
            }

            for (int vk = 0; vk < 256; ++vk) {
                bool down = GetAsyncKeyState(vk) & 0x8000;

                if (down && !key_pressed[vk]) {
                    key_pressed[vk] = true;
                    last_backspace_time = now;

                    if (vk == VK_BACK && !current_value.empty()) {
                        current_value.pop_back();
                    }
                    else if (vk == VK_RETURN || vk == VK_ESCAPE) {
                        input_active = false;
                    }
                    else if (current_value.size() < 100) {
                        BYTE keyboard_state[256];
                        GetKeyboardState(keyboard_state);

                        WCHAR unicode_chars[4] = {};
                        int result = ToUnicode(vk, MapVirtualKey(vk, MAPVK_VK_TO_VSC), keyboard_state, unicode_chars, 4, 0);

                        if (result > 0) {
                            char mb_char[8] = {};
                            WideCharToMultiByte(CP_UTF8, 0, unicode_chars, result, mb_char, sizeof(mb_char), nullptr, nullptr);
                            current_value += mb_char;
                        }
                        else if (vk == VK_SPACE) {
                            current_value += ' ';
                        }
                    }
                }
                else if (!down) {
                    key_pressed[vk] = false;
                }
            }
        }

        return current_value;
    }


    // sns our colors
    //namespace Colors
    //{
    //    // Modern dark theme with blue/purple accent
    //    flinearcolor Text{ 0.95f, 0.95f, 0.98f, 1.0f }; // Almost white
    //    flinearcolor Text_Shadow{ 0.95f, 0.95f, 0.98f, 1.0f };
    //    flinearcolor Text_Outline{ 1.0f, 1.0f, 1.0f, 1.0f };
    //    flinearcolor Text_Active{ 0.6f, 0.6f, 1.0f, 0.8f }; // Light blue accent

    //    flinearcolor Button_Idle{ 0.13f, 0.15f, 0.22f, 1.0f }; // Dark blue
    //    flinearcolor Button_Hovered{ 0.22f, 0.25f, 0.38f, 1.0f }; // Lighter blue
    //    flinearcolor Button_Active{ 0.45f, 0.18f, 0.65f, 1.0f }; // Purple accent

    //    flinearcolor Checkbox_Idle{ 0.18f, 0.20f, 0.28f, 1.0f };
    //    flinearcolor Checkbox_Hovered{ 0.30f, 0.32f, 0.45f, 1.0f };
    //    flinearcolor Checkbox_Enabled{ 0.45f, 0.18f, 0.65f, 1.0f }; // Purple accent

    //    flinearcolor Combobox_Idle{ 0.13f, 0.15f, 0.22f, 1.0f };
    //    flinearcolor Combobox_Hovered{ 0.22f, 0.25f, 0.38f, 1.0f };
    //    flinearcolor Combobox_Elements{ 0.45f, 0.18f, 0.65f, 0.5f };

    //    flinearcolor Slider_Idle{ 0.13f, 0.15f, 0.22f, 1.0f };
    //    flinearcolor Slider_Hovered{ 0.22f, 0.25f, 0.38f, 1.0f };
    //    flinearcolor Slider_Progress{ 0.45f, 0.18f, 0.65f, 1.0f };
    //    flinearcolor Slider_Button{ 0.6f, 0.6f, 1.0f, 1.0f };

    //    flinearcolor ColorPicker_Background{ 0.10f, 0.10f, 0.15f, 0.95f };
    //    flinearcolor Outline{ 1.0f, 1.0f, 1.0f, 1.0f }; // White outline
    //}

    // sysinfo colors
    namespace Colors
    {
        // Modern dark theme with purple accent
        flinearcolor Text{ 0.95f, 0.95f, 0.98f, 1.0f }; // Almost white
        flinearcolor Text_Shadow{ 0.95f, 0.95f, 0.98f, 1.0f };
        flinearcolor Text_Outline{ 1.0f, 1.0f, 1.0f, 1.0f };
        flinearcolor Text_Active{ 0.615f, 0.294f, 0.929f, 0.8f }; // Purple accent

        flinearcolor Button_Idle{ 0.13f, 0.15f, 0.22f, 1.0f }; // Dark base
        flinearcolor Button_Hovered{ 0.22f, 0.25f, 0.38f, 1.0f }; // Hover shade
        flinearcolor Button_Active{ 0.615f, 0.294f, 0.929f, 1.0f }; // Purple accent

        flinearcolor Checkbox_Idle{ 0.18f, 0.20f, 0.28f, 1.0f };
        flinearcolor Checkbox_Hovered{ 0.30f, 0.32f, 0.45f, 1.0f };
        flinearcolor Checkbox_Enabled{ 0.615f, 0.294f, 0.929f, 1.0f }; // Purple accent

        flinearcolor Combobox_Idle{ 0.13f, 0.15f, 0.22f, 1.0f };
        flinearcolor Combobox_Hovered{ 0.22f, 0.25f, 0.38f, 1.0f };
        flinearcolor Combobox_Elements{ 0.615f, 0.294f, 0.929f, 0.5f }; // Purple accent (semi-transparent)

        flinearcolor Slider_Idle{ 0.13f, 0.15f, 0.22f, 1.0f };
        flinearcolor Slider_Hovered{ 0.22f, 0.25f, 0.38f, 1.0f };
        flinearcolor Slider_Progress{ 0.615f, 0.294f, 0.929f, 1.0f }; // Purple accent
        flinearcolor Slider_Button{ 0.615f, 0.294f, 0.929f, 1.0f }; // Purple accent

        flinearcolor ColorPicker_Background{ 0.10f, 0.10f, 0.15f, 0.95f };
        flinearcolor Outline{ 1.0f, 1.0f, 1.0f, 1.0f }; // White outline
    }


    // sns our colors

    //bool draw_button(
    //    ucanvas* canvas,
    //    uobject* font,
    //    const wchar_t* label,
    //    fvector2d pos,
    //    float width,
    //    float height,
    //    flinearcolor normal_color,
    //    flinearcolor hover_color,
    //    flinearcolor text_color,
    //    fvector2d mouse_pos,
    //    bool mouse_clicked
    //) {
    //    static std::chrono::steady_clock::time_point last_click_time = std::chrono::steady_clock::now();
    //    bool is_hovered = (mouse_pos.x >= pos.x && mouse_pos.x <= pos.x + width &&
    //        mouse_pos.y >= pos.y && mouse_pos.y <= pos.y + height);

    //    // Draw button background - matching menu theme
    //    drawFilledRect(fvector2d{ pos.x, pos.y }, width, height, RGBtoFLC(2.666, 3.332, 4.165));

    //    if (is_hovered) {
    //        // Hover state - slightly brighter
    //        drawFilledRect(fvector2d{ pos.x + 1, pos.y + 1 }, width - 2, height - 2, RGBtoFLC(1.4, 1.6, 1.9));
    //    }
    //    else {
    //        // Normal state - matches window inner background
    //        drawFilledRect(fvector2d{ pos.x + 1, pos.y + 1 }, width - 2, height - 2, RGBtoFLC(1.25, 1.416, 1.749));
    //    }

    //    // Draw sharp, clearly visible borders
    //    drawFilledRect(fvector2d{ pos.x, pos.y }, 1, height, RGBtoFLC(3.999, 5.098, 6.631)); // Left border - brighter
    //    drawFilledRect(fvector2d{ pos.x + width - 1, pos.y }, 1, height, RGBtoFLC(0.299, 0.399, 0.531)); // Right border - darker
    //    drawFilledRect(fvector2d{ pos.x, pos.y }, width, 1, RGBtoFLC(3.999, 5.098, 6.631)); // Top border - brighter
    //    drawFilledRect(fvector2d{ pos.x, pos.y + height - 1 }, width, 1, RGBtoFLC(0.299, 0.399, 0.531)); // Bottom border - darker

    //    // Draw perfectly centered text (adjusted slightly higher)
    //    fvector2d textPos = fvector2d{ pos.x + width / 2, pos.y + height / 2 - 2 };
    //    canvas->k2_drawtext(font, label, textPos, fvector2d(0.94, 0.93), RGBtoFLC(255, 255, 255), 0.0f,
    //        Colors::Text_Shadow, fvector2d(0, 0), true, true, false, Colors::Text_Outline);

    //    // Click handling with 500ms cooldown
    //    auto current_time = std::chrono::steady_clock::now();
    //    auto time_since_last_click = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_click_time);

    //    if (mouse_clicked && is_hovered && time_since_last_click.count() >= 500) {
    //        last_click_time = current_time;
    //        return true;
    //    }

    //    return false;
    //}

    // sysinfo colors

    bool draw_button(
        ucanvas* canvas,
        uobject* font,
        const wchar_t* label,
        fvector2d pos,
        float width,
        float height,
        flinearcolor normal_color,
        flinearcolor hover_color,
        flinearcolor text_color,
        fvector2d mouse_pos,
        bool mouse_clicked
    ) {
        static std::chrono::steady_clock::time_point last_click_time = std::chrono::steady_clock::now();
        bool is_hovered = (mouse_pos.x >= pos.x && mouse_pos.x <= pos.x + width &&
            mouse_pos.y >= pos.y && mouse_pos.y <= pos.y + height);

        // Draw button background - matching menu theme
        drawFilledRect(fvector2d{ pos.x, pos.y }, width, height, RGBtoFLC(2, 2, 2));

        if (is_hovered) {
            drawFilledRect(fvector2d{ pos.x + 1, pos.y + 1 }, width - 2, height - 2, RGBtoFLC(2, 2, 2));
        }
        else {
            drawFilledRect(fvector2d{ pos.x + 1, pos.y + 1 }, width - 2, height - 2, RGBtoFLC(1, 1, 1));
        }

        // Draw sharp, clearly visible borders with purple accent
        drawFilledRect(fvector2d{ pos.x, pos.y }, 1, height, RGBtoFLC(100, 180, 255)); // Left border - purple
        drawFilledRect(fvector2d{ pos.x + width - 1, pos.y }, 1, height, RGBtoFLC(100, 180, 255)); // Right border - purple
        drawFilledRect(fvector2d{ pos.x, pos.y }, width, 1, RGBtoFLC(100, 180, 255)); // Top border - purple
        drawFilledRect(fvector2d{ pos.x, pos.y + height - 1 }, width, 1, RGBtoFLC(100, 180, 255)); // Bottom border - purple

        // Draw perfectly centered text (adjusted slightly higher)
        fvector2d textPos = fvector2d{ pos.x + width / 2, pos.y + height / 2 - 2 };
        canvas->k2_drawtext(font, label, textPos, fvector2d(0.94, 0.93), RGBtoFLC(255, 255, 255), 0.0f,
            Colors::Text_Shadow, fvector2d(0, 0), true, true, false, Colors::Text_Outline);

        // Click handling with 500ms cooldown
        auto current_time = std::chrono::steady_clock::now();
        auto time_since_last_click = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_click_time);

        if (mouse_clicked && is_hovered && time_since_last_click.count() >= 500) {
            last_click_time = current_time;
            return true;
        }

        return false;
    }


    namespace PostRenderer
    {
        struct DrawList
        {
            int type = -1; //1 = FilledRect, 2 = TextLeft, 3 = TextCenter, 4 = Draw_Line
            fvector2d pos;
            fvector2d size;
            flinearcolor color;
            const wchar_t* name;
            bool outline;

            fvector2d from;
            fvector2d to;
            int thickness;
        };
        DrawList drawlist[128];

        void drawFilledRect(fvector2d pos, float w, float h, flinearcolor color)
        {
            for (int i = 0; i < 128; i++)
            {
                if (drawlist[i].type == -1)
                {
                    drawlist[i].type = 1;
                    drawlist[i].pos = pos;
                    drawlist[i].size = fvector2d{ w, h };
                    drawlist[i].color = color;
                    return;
                }
            }
        }
        void TextLeft(const wchar_t* name, fvector2d pos, flinearcolor color, bool outline)
        {
            for (int i = 0; i < 128; i++)
            {
                if (drawlist[i].type == -1)
                {
                    drawlist[i].type = 2;
                    drawlist[i].name = name;
                    drawlist[i].pos = pos;
                    drawlist[i].outline = outline;
                    drawlist[i].color = color;
                    return;
                }
            }
        }
        void TextCenter(const wchar_t* name, fvector2d pos, flinearcolor color, bool outline)
        {
            for (int i = 0; i < 128; i++)
            {
                if (drawlist[i].type == -1)
                {
                    drawlist[i].type = 3;
                    drawlist[i].name = name;
                    drawlist[i].pos = pos;
                    drawlist[i].outline = outline;
                    drawlist[i].color = color;
                    return;
                }
            }
        }
        void Draw_Line(fvector2d from, fvector2d to, int thickness, flinearcolor color)
        {
            for (int i = 0; i < 128; i++)
            {
                if (drawlist[i].type == -1)
                {
                    drawlist[i].type = 4;
                    drawlist[i].from = from;
                    drawlist[i].to = to;
                    drawlist[i].thickness = thickness;
                    drawlist[i].color = color;
                    return;
                }
            }
        }
    }

    ucanvas* canvas;


    bool hover_element = false;
    fvector2d menu_pos = fvector2d{ 0, 0 };
    float offset_x = 0.0f;
    float offset_y = 0.0f;

    fvector2d first_element_pos = fvector2d{ 0, 0 };

    fvector2d last_element_pos = fvector2d{ 0, 0 };
    fvector2d last_element_size = fvector2d{ 0, 0 };

    int current_element = -1;
    fvector2d current_element_pos = fvector2d{ 0, 0 };
    fvector2d current_element_size = fvector2d{ 0, 0 };
    int elements_count = 0;

    bool sameLine = false;

    bool pushY = false;
    float pushYvalue = 0.0f;

    void SetupCanvas(ucanvas* _canvas)
    {
        canvas = _canvas;
    }

    void Draw_Line(fvector2d from, fvector2d to, int thickness, flinearcolor color)
    {
        canvas->k2_drawline(fvector2d{ from.x, from.y }, fvector2d{ to.x, to.y }, thickness, color);
    }
    void drawFilledRect(fvector2d initial_pos, float w, float h, flinearcolor color)
    {
        for (float i = 0.0f; i < h; i += 1.0f)
            canvas->k2_drawline(fvector2d{ initial_pos.x, initial_pos.y + i }, fvector2d{ initial_pos.x + w, initial_pos.y + i }, 1.0f, color);
    }
    void DrawGradientLine(fvector2d screenpos_a, fvector2d screenpos_b, flinearcolor color_a, flinearcolor color_c, flinearcolor color_b, float thickness, int num_segments)
    {
        for (int i = 0; i < num_segments; i++)
        {
            float t1 = static_cast<float>(i) / num_segments;
            float t2 = static_cast<float>(i + 1) / num_segments;

            fvector2d start = screenpos_a + (screenpos_b - screenpos_a) * t1;
            fvector2d end = screenpos_a + (screenpos_b - screenpos_a) * t2;

            float t_mid = (t1 + t2) / 2.0f;

            flinearcolor color;

            if (t_mid <= 0.5f)
            {
                float u = 2.0f * t_mid;  // Maps t_mid [0, 0.5] to u [0, 1]
                color.r = color_a.r * (1.0f - u) + color_c.r * u;
                color.g = color_a.g * (1.0f - u) + color_c.g * u;
                color.b = color_a.b * (1.0f - u) + color_c.b * u;
                color.a = color_a.a * (1.0f - u) + color_c.a * u;
            }
            else
            {
                float v = 2.0f * (t_mid - 0.5f);  // Maps t_mid [0.5, 1] to v [0, 1]
                color.r = color_c.r * (1.0f - v) + color_b.r * v;
                color.g = color_c.g * (1.0f - v) + color_b.g * v;
                color.b = color_c.b * (1.0f - v) + color_b.b * v;
                color.a = color_c.a * (1.0f - v) + color_b.a * v;
            }

            canvas->k2_drawline(start, end, thickness, color);
        }
    }

    // DrawGradientLine(startPos, endPos, red, green, blue, 2.0f, 20);
    void drawGradientFilledRect(fvector2d initial_pos, float w, float h, flinearcolor color_a, flinearcolor color_c, flinearcolor color_b, int num_segments)
    {
        for (float i = 0.0f; i < h; i += 1.0f)
            DrawGradientLine(fvector2d{ initial_pos.x, initial_pos.y + i }, fvector2d{ initial_pos.x + w, initial_pos.y + i }, color_a, color_c, color_b, 1.0f, num_segments);
    }

    void drawGradientFilledRectVertical(fvector2d initial_pos, float w, float h, flinearcolor color_a, flinearcolor color_c, flinearcolor color_b, int num_segments)
    {
        for (float i = 0.0f; i < w; i += 1.0f)
            DrawGradientLine(fvector2d{ initial_pos.x + i, initial_pos.y }, fvector2d{ initial_pos.x + i, initial_pos.y + h }, color_a, color_c, color_b, 1.0f, num_segments);
    }


    void draw_filled_rect(ucanvas* canvas, float x, float y, float width, float height, flinearcolor color) {
        for (float i = 0; i < height; i++) {
            canvas->k2_drawline(
                { x, y + i },
                { x + width, y + i },
                1.0f,
                color
            );
        }
    }

    void draw_rect(ucanvas* canvas, float x, float y, float width, float height, flinearcolor color) {
        canvas->k2_drawline({ x, y }, { x + width, y }, 1.0f, color);
        canvas->k2_drawline({ x + width, y }, { x + width, y + height }, 1.0f, color);
        canvas->k2_drawline({ x + width, y + height }, { x, y + height }, 1.0f, color);
        canvas->k2_drawline({ x, y + height }, { x, y }, 1.0f, color);
    }

    fvector2d CursorPos()
    {
        POINT cursorPos;
        GetCursorPos(&cursorPos);
        return fvector2d{ (float)cursorPos.x, (float)cursorPos.y };
    }
    bool MouseInZone(fvector2d pos, fvector2d size)
    {
        fvector2d cursor_pos = CursorPos();

        if (cursor_pos.x > pos.x && cursor_pos.y > pos.y)
            if (cursor_pos.x < pos.x + size.x && cursor_pos.y < pos.y + size.y)
                return true;

        return false;
    }

    void Draw_Cursor(bool menu_opened)
    {
        if (menu_opened)
        {
            fvector2d cp = CursorPos();
            flinearcolor red = RGBtoFLC(255, 0, 0);
            flinearcolor darkRed = RGBtoFLC(180, 0, 0);
            float cx = cp.x;
            float cy = cp.y;

            for (int i = 0; i < 18; i++) {
                float y = cy + i;
                float right;
                if (i <= 14)
                    right = cx + 1.0f + i * 0.75f;
                else
                    right = cx + 3.0f;

                canvas->k2_drawline(fvector2d(cx, y), fvector2d(right, y), 1.0f, red);
            }

            canvas->k2_drawline(fvector2d(cx, cy), fvector2d(cx + 12, cy + 11), 1.0f, darkRed);
            canvas->k2_drawline(fvector2d(cx + 12, cy + 11), fvector2d(cx + 5, cy + 11), 1.0f, darkRed);
            canvas->k2_drawline(fvector2d(cx + 5, cy + 11), fvector2d(cx + 3, cy + 16), 1.0f, darkRed);
            canvas->k2_drawline(fvector2d(cx + 3, cy + 16), fvector2d(cx, cy + 16), 1.0f, darkRed);
            canvas->k2_drawline(fvector2d(cx, cy + 16), fvector2d(cx, cy), 1.0f, darkRed);
        }
    }

    /*void SameLine()
    {
        sameLine = true;
    }*/
    void PushNextElementY(float y, bool from_last_element = true)
    {
        pushY = true;
        if (from_last_element)
            pushYvalue = last_element_pos.y + last_element_size.y + y;
        else
            pushYvalue = y;
    }
    void NextColumn(float x)
    {
        offset_x = x;
        PushNextElementY(first_element_pos.y, false);
    }
    void ClearFirstPos()
    {
        first_element_pos = fvector2d{ 0, 0 };
    }

    void GetColor(flinearcolor* color, float* r, float* g, float* b, float* a)
    {
        *r = color->r;
        *g = color->g;
        *b = color->b;
        *a = color->a;
    }
    UINT32 GetColorUINT(int r, int g, int b, int a)
    {
        UINT32 result = (BYTE(a) << 24) + (BYTE(r) << 16) + (BYTE(g) << 8) + BYTE(b);
        return result;
    }
    void DrawFilledCircle(fvector2d pos, float r, flinearcolor color)
    {
        float smooth = 0.07f;

        double PI = 3.14159265359;
        int size = (int)(2.0f * PI / smooth) + 1;

        float angle = 0.0f;
        int i = 0;

        for (; angle < 2 * PI; angle += smooth, i++)
        {
            Draw_Line(fvector2d{ pos.x, pos.y }, fvector2d{ pos.x + cosf(angle) * r, pos.y + sinf(angle) * r }, 1.0f, color);
        }
    }
    void DrawCircle(fvector2d pos, int radius, int numSides, flinearcolor Color)
    {
        float PI = 3.1415927f;

        float Step = PI * 2.0 / numSides;
        int Count = 0;
        fvector2d V[128];
        for (float a = 0; a < PI * 2.0; a += Step) {
            float X1 = radius * cos(a) + pos.x;
            float Y1 = radius * sin(a) + pos.y;
            float X2 = radius * cos(a + Step) + pos.x;
            float Y2 = radius * sin(a + Step) + pos.y;
            V[Count].x = X1;
            V[Count].y = Y1;
            V[Count + 1].x = X2;
            V[Count + 1].y = Y2;
            //Draw_Line(fvector2d{ pos.x, pos.y }, fvector2d{ X2, Y2 }, 1.0f, Color); // Points from Centre to ends of circle
            Draw_Line(fvector2d{ V[Count].x, V[Count].y }, fvector2d{ X2, Y2 }, 1.0f, Color);// Circle Around
        }
    }

    fvector2d dragPos;
    // sns our colors
    //bool Window(ucanvas* canvas, uobject* font, fstring title, fvector2d* pos, fvector2d size, bool isOpen, fstring date = L"", fstring username = L"")
    //{
    //    elements_count = 0;

    //    if (!isOpen)
    //        return false;

    //    bool isHovered = MouseInZone(fvector2d{ pos->x, pos->y }, size);

    //    if (current_element != -1 && !GetAsyncKeyState(0x1))
    //        current_element = -1;

    //    offset_x = 1.0f; offset_y = 47.0f;
    //    menu_pos = fvector2d{ pos->x, pos->y };
    //    first_element_pos = fvector2d{ 0, 0 };
    //    current_element_pos = fvector2d{ 0, 0 };
    //    current_element_size = fvector2d{ 0, 0 };

    //    // === Get Real System Username ===
    //    wchar_t usernameBuffer[256];
    //    DWORD usernameSize = sizeof(usernameBuffer) / sizeof(usernameBuffer[0]);

    //    // Check if username is empty by comparing with empty string using custom function
    //    bool useDefaultUsername = true;
    //    const wchar_t* usernamePtr = username.c_str();
    //    if (usernamePtr && usernamePtr[0] != L'\0') {
    //        useDefaultUsername = false;
    //    }

    //    if (useDefaultUsername && GetUserNameW(usernameBuffer, &usernameSize)) {
    //        username = fstring(usernameBuffer);
    //    }
    //    else if (useDefaultUsername) {
    //        username = L"user"; // Fallback
    //    }

    //    // === Get Real Current Date ===
    //    wchar_t dateBuffer[32];
    //    bool useDefaultDate = true;
    //    const wchar_t* datePtr = date.c_str();
    //    if (datePtr && datePtr[0] != L'\0') {
    //        useDefaultDate = false;
    //    }

    //    if (useDefaultDate) {
    //        SYSTEMTIME systemTime;
    //        GetLocalTime(&systemTime);

    //        const wchar_t* months[12] = { L"Jan", L"Feb", L"Mar", L"Apr", L"May", L"Jun",
    //                                     L"Jul", L"Aug", L"Sep", L"Oct", L"Nov", L"Dec" };

    //        swprintf(dateBuffer, 32, L"%s %d %d", months[systemTime.wMonth - 1], systemTime.wDay, systemTime.wYear);
    //        date = fstring(dateBuffer);
    //    }

    //    // === Window Background ===
    //    drawFilledRect(fvector2d(pos->x, pos->y), size.x, size.y, RGBtoFLC(2.666, 3.332, 4.165));
    //    drawFilledRect(fvector2d(pos->x + 1, pos->y + 1), size.x - 2, size.y - 2, RGBtoFLC(1.25, 1.416, 1.749));

    //    // === Separators ===
    //    drawFilledRect(fvector2d(pos->x + 1, pos->y + 1 + 45), size.x - 2, 1, RGBtoFLC(3.499, 4.498, 5.831));
    //    drawFilledRect(fvector2d(pos->x + 1, pos->y + 1 + 45 + 37), size.x - 2, 1, RGBtoFLC(3.499, 4.498, 5.831));

    //    // REMOVED: Bottom horizontal separator
    //    // drawFilledRect(fvector2d(pos->x + 1, pos->y + size.y - 1), size.x - 2, 1, RGBtoFLC(3.499, 4.498, 5.831));

    //    // Vertical separator - adjusted to go to the very bottom since bottom separator is removed
    //    float verticalSeparatorStartY = pos->y + 1 + 45 + 37 + 1;
    //    float verticalSeparatorEndY = pos->y + size.y - 1;
    //    float verticalSeparatorHeight = verticalSeparatorEndY - verticalSeparatorStartY;
    //    drawFilledRect(fvector2d(pos->x + 1 + 315.9, verticalSeparatorStartY), 1, verticalSeparatorHeight, RGBtoFLC(3.499, 4.498, 5.831));

    //    drawFilledRect(fvector2d(pos->x + 16, pos->y + (45 / 2) - 3), 6, 6, RGBtoFLC(0, 180, 240));

    //    drawFilledRect(fvector2d(pos->x + (size.x - 55), pos->y + 11), 38, 25, RGBtoFLC(2.666, 3.332, 4.165));
    //    drawFilledRect(fvector2d(pos->x + (size.x - 55) + 1, pos->y + 11 + 1), 38 - 2, 25 - 2, RGBtoFLC(1.25, 1.416, 1.749));

    //    // === Title ===
    //    canvas->k2_drawtext(
    //        font,
    //        title,
    //        fvector2d(pos->x + 1 + 32, pos->y + 1 + 22),
    //        fvector2d(1.2, 1),
    //        RGBtoFLC(255, 255, 255),
    //        0.0f,
    //        RGBtoFLC(0, 0, 0),
    //        fvector2d(0, 0),
    //        false,
    //        true,
    //        false,
    //        RGBtoFLC(0, 0, 0)
    //    );

    //    canvas->k2_drawtext(
    //        font,
    //        date,
    //        fvector2d(pos->x + 1 + 32 + 62, pos->y + 1 + 22 + 2),
    //        fvector2d(0.9, 0.8),
    //        RGBtoFLC(70, 70, 70),
    //        0.0f,
    //        RGBtoFLC(0, 0, 0),
    //        fvector2d(0, 0),
    //        false,
    //        true,
    //        false,
    //        RGBtoFLC(0, 0, 0)
    //    );

    //    canvas->k2_drawtext(
    //        font,
    //        L"Welcome back, ",
    //        fvector2d(pos->x + size.x - 211 - 10, pos->y + 1 + 22 + 2),
    //        fvector2d(0.9, 0.8),
    //        RGBtoFLC(140, 140, 140),
    //        0.0f,
    //        RGBtoFLC(0, 0, 0),
    //        fvector2d(0, 0),
    //        false,
    //        true,
    //        false,
    //        RGBtoFLC(0, 0, 0)
    //    );

    //    canvas->k2_drawtext(
    //        font,
    //        username,
    //        fvector2d(pos->x + size.x - 127, pos->y + 1 + 22 + 2),
    //        fvector2d(0.9, 0.8),
    //        RGBtoFLC(0, 180, 240),
    //        0.0f,
    //        RGBtoFLC(0, 0, 0),
    //        fvector2d(0, 0),
    //        false,
    //        true,
    //        false,
    //        RGBtoFLC(0, 0, 0)
    //    );

    //    canvas->k2_drawtext(
    //        font,
    //        L"BETA",
    //        fvector2d(pos->x + (size.x - 55) + 1 + 18, pos->y + 11 + 1 + 11.5),
    //        fvector2d(0.85, 0.75),
    //        RGBtoFLC(90, 90, 90),
    //        0.0f,
    //        RGBtoFLC(0, 0, 0),
    //        fvector2d(0, 0),
    //        true,
    //        true,
    //        false,
    //        RGBtoFLC(0, 0, 0)
    //    );

    //    return true;
    //}

    // sysinfo colors

    bool Window(ucanvas* canvas, uobject* font, fstring title, fvector2d* pos, fvector2d size, bool isOpen, fstring date = L"", fstring username = L"")
    {
        elements_count = 0;

        if (!isOpen)
            return false;

        bool isHovered = MouseInZone(fvector2d{ pos->x, pos->y }, size);

        if (current_element != -1 && !GetAsyncKeyState(0x1))
            current_element = -1;

        offset_x = 1.0f; offset_y = 47.0f;
        menu_pos = fvector2d{ pos->x, pos->y };
        first_element_pos = fvector2d{ 0, 0 };
        current_element_pos = fvector2d{ 0, 0 };
        current_element_size = fvector2d{ 0, 0 };

        // === Get Real System Username ===
        wchar_t usernameBuffer[256];
        DWORD usernameSize = sizeof(usernameBuffer) / sizeof(usernameBuffer[0]);

        bool useDefaultUsername = true;
        const wchar_t* usernamePtr = username.c_str();
        if (usernamePtr && usernamePtr[0] != L'\0') {
            useDefaultUsername = false;
        }

        if (useDefaultUsername && GetUserNameW(usernameBuffer, &usernameSize)) {
            username = fstring(usernameBuffer);
        }
        else if (useDefaultUsername) {
            username = L"user"; // Fallback
        }

        // === Get Real Current Date ===
        wchar_t dateBuffer[32];
        bool useDefaultDate = true;
        const wchar_t* datePtr = date.c_str();
        if (datePtr && datePtr[0] != L'\0') {
            useDefaultDate = false;
        }

        if (useDefaultDate) {
            SYSTEMTIME systemTime;
            GetLocalTime(&systemTime);

            const wchar_t* months[12] = { L"Jan", L"Feb", L"Mar", L"Apr", L"May", L"Jun",
                                         L"Jul", L"Aug", L"Sep", L"Oct", L"Nov", L"Dec" };

            swprintf(dateBuffer, 32, L"%s %d %d", months[systemTime.wMonth - 1], systemTime.wDay, systemTime.wYear);
            date = fstring(dateBuffer);
        }

        // === Window Background ===
        drawFilledRect(fvector2d(pos->x, pos->y), size.x, size.y, RGBtoFLC(0, 0, 0)); // black border
        drawFilledRect(fvector2d(pos->x + 1, pos->y + 1), size.x - 2, size.y - 2, RGBtoFLC(0, 0, 0)); // simsiyah icerik

        // === Separators ===
        // Title bar bottom line
        drawFilledRect(fvector2d(pos->x + 1, pos->y + 1 + 45), size.x - 2, 1, RGBtoFLC(3, 3, 3));

        drawFilledRect(fvector2d(pos->x + 16, pos->y + (45 / 2) - 3), 6, 6, RGBtoFLC(100, 180, 255)); // accent square

        canvas->k2_drawtext(font, L"Vacsen", fvector2d(pos->x + 30, pos->y + 12), fvector2d(1.1, 1.0), RGBtoFLC(80, 160, 255), 0.0f, RGBtoFLC(0, 0, 0), fvector2d(0, 0), false, false, false, RGBtoFLC(0, 0, 0));

        return true;
    }


    // ICONS

    //bool ButtonTab(ucanvas* canvas, uobject* font, const wchar_t* name, fvector2d size, bool active)
    //{
    //    elements_count++;

    //    fvector2d padding = fvector2d{ 0, 0 };
    //    fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
    //    if (sameLine)
    //    {
    //        pos.x = last_element_pos.x + last_element_size.x + offset_x;
    //        pos.y = last_element_pos.y;
    //    }
    //    if (pushY)
    //    {
    //        pos.y = pushYvalue;
    //        pushY = false;
    //        pushYvalue = 0.0f;
    //        offset_y = pos.y - menu_pos.y;
    //    }
    //    bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, size);

    //    if (!sameLine)
    //        offset_y += size.y + padding.y;

    //    fvector2d textPos = fvector2d{ pos.x + (size.x / 2) - 10, pos.y + (size.y / 2) - 10 };

    //    drawFilledRect(fvector2d(pos.x, pos.y), size.x, size.y, RGBtoFLC(2.083, 2.499, 2.999));
    //    drawGradientFilledRectVertical(fvector2d(pos.x + 1, pos.y + 1), size.x - 2, size.y - 2, RGBtoFLC(1.000, 1.166, 1.333), RGBtoFLC(1.333, 1.583, 1.833), RGBtoFLC(1.666, 1.916, 2.249), 10);

    //    //Bg
    //    if (active)
    //    {
    //        drawFilledRect(fvector2d(pos.x, pos.y + size.y - 1), size.x, 1, RGBtoFLC(0, 180, 240));
    //        if (name == L"R") {
    //            canvas->k2_drawtexture(rage_icon, textPos, fvector2d(20, 20),
    //                fvector2d(0.0f, 0.0f),
    //                fvector2d(1.0f, 1.0f),
    //                RGBtoFLC(0, 180, 240), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
    //        }
    //        else if (name == L"L") {
    //            canvas->k2_drawtexture(legit_icon, textPos, fvector2d(20, 20),
    //                fvector2d(0.0f, 0.0f),
    //                fvector2d(1.0f, 1.0f),
    //                RGBtoFLC(0, 180, 240), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
    //        }
    //        else if (name == L"V") {
    //            canvas->k2_drawtexture(visuals_icon, textPos, fvector2d(20, 20),
    //                fvector2d(0.0f, 0.0f),
    //                fvector2d(1.0f, 1.0f),
    //                RGBtoFLC(0, 180, 240), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
    //        }
    //        else if (name == L"S") {
    //            canvas->k2_drawtexture(settings_icon, textPos, fvector2d(20, 20),
    //                fvector2d(0.0f, 0.0f),
    //                fvector2d(1.0f, 1.0f),
    //                RGBtoFLC(0, 180, 240), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
    //        }
    //        else if (name == L"C") {
    //            canvas->k2_drawtexture(config_icon, textPos, fvector2d(20, 20),
    //                fvector2d(0.0f, 0.0f),
    //                fvector2d(1.0f, 1.0f),
    //                RGBtoFLC(0, 180, 240), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
    //        }
    //        else if (name == L"M") {
    //            canvas->k2_drawtexture(local_icon, textPos, fvector2d(20, 20),
    //                fvector2d(0.0f, 0.0f),
    //                fvector2d(1.0f, 1.0f),
    //                RGBtoFLC(0, 180, 240), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
    //        }
    //    }
    //    else if (isHovered)
    //    {
    //        hover_element = true;
    //        if (name == L"R") {
    //            canvas->k2_drawtexture(rage_icon, textPos, fvector2d(20, 20),
    //                fvector2d(0.0f, 0.0f),
    //                fvector2d(1.0f, 1.0f),
    //                RGBtoFLC(120, 120, 120), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
    //        }
    //        else if (name == L"L") {
    //            canvas->k2_drawtexture(legit_icon, textPos, fvector2d(20, 20),
    //                fvector2d(0.0f, 0.0f),
    //                fvector2d(1.0f, 1.0f),
    //                RGBtoFLC(120, 120, 120), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
    //        }
    //        else if (name == L"V") {
    //            canvas->k2_drawtexture(visuals_icon, textPos, fvector2d(20, 20),
    //                fvector2d(0.0f, 0.0f),
    //                fvector2d(1.0f, 1.0f),
    //                RGBtoFLC(120, 120, 120), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
    //        }
    //        else if (name == L"S") {
    //            canvas->k2_drawtexture(settings_icon, textPos, fvector2d(20, 20),
    //                fvector2d(0.0f, 0.0f),
    //                fvector2d(1.0f, 1.0f),
    //                RGBtoFLC(120, 120, 120), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
    //        }
    //        else if (name == L"C") {
    //            canvas->k2_drawtexture(config_icon, textPos, fvector2d(20, 20),
    //                fvector2d(0.0f, 0.0f),
    //                fvector2d(1.0f, 1.0f),
    //                RGBtoFLC(120, 120, 120), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
    //        }
    //        else if (name == L"M") {
    //            canvas->k2_drawtexture(local_icon, textPos, fvector2d(20, 20),
    //                fvector2d(0.0f, 0.0f),
    //                fvector2d(1.0f, 1.0f),
    //                RGBtoFLC(120, 120, 120), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
    //        }
    //    }
    //    else
    //    {
    //        if (name == L"R") {
    //            canvas->k2_drawtexture(rage_icon, textPos, fvector2d(20, 20),
    //                fvector2d(0.0f, 0.0f),
    //                fvector2d(1.0f, 1.0f),
    //                RGBtoFLC(70, 70, 70), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
    //        }
    //        else if (name == L"L") {
    //            canvas->k2_drawtexture(legit_icon, textPos, fvector2d(20, 20),
    //                fvector2d(0.0f, 0.0f),
    //                fvector2d(1.0f, 1.0f),
    //                RGBtoFLC(70, 70, 70), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
    //        }
    //        else if (name == L"V") {
    //            canvas->k2_drawtexture(visuals_icon, textPos, fvector2d(20, 20),
    //                fvector2d(0.0f, 0.0f),
    //                fvector2d(1.0f, 1.0f),
    //                RGBtoFLC(70, 70, 70), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
    //        }
    //        else if (name == L"S") {
    //            canvas->k2_drawtexture(settings_icon, textPos, fvector2d(20, 20),
    //                fvector2d(0.0f, 0.0f),
    //                fvector2d(1.0f, 1.0f),
    //                RGBtoFLC(70, 70, 70), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
    //        }
    //        else if (name == L"C") {
    //            canvas->k2_drawtexture(config_icon, textPos, fvector2d(20, 20),
    //                fvector2d(0.0f, 0.0f),
    //                fvector2d(1.0f, 1.0f),
    //                RGBtoFLC(70, 70, 70), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
    //        }
    //        else if (name == L"M") {
    //            canvas->k2_drawtexture(local_icon, textPos, fvector2d(20, 20),
    //                fvector2d(0.0f, 0.0f),
    //                fvector2d(1.0f, 1.0f),
    //                RGBtoFLC(70, 70, 70), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
    //        }
    //    }

    //    sameLine = false;
    //    last_element_pos = pos;
    //    last_element_size = size;
    //    if (first_element_pos.x == 0.0f)
    //        first_element_pos = pos;

    //    if (isHovered && input::is_mouse_clicked(0, elements_count, false))
    //        return true;

    //    return false;
    //}

    // TEXT

// sns our colors

//bool ButtonTab(ucanvas* canvas, uobject* font, const wchar_t* name, fvector2d size, bool active)
//{
//    elements_count++;
//
//    fvector2d padding = fvector2d{ 0, 0 };
//    fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
//    if (sameLine)
//    {
//        pos.x = last_element_pos.x + last_element_size.x + offset_x;
//        pos.y = last_element_pos.y;
//    }
//    if (pushY)
//    {
//        pos.y = pushYvalue;
//        pushY = false;
//        pushYvalue = 0.0f;
//        offset_y = pos.y - menu_pos.y;
//    }
//    bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, size);
//
//    if (!sameLine)
//        offset_y += size.y + padding.y;
//
//    // for icon
//    // textPos = fvector2d{ pos.x + (size.x / 2) - 10, pos.y + (size.y / 2) - 10 };
//    fvector2d textPos = fvector2d{ pos.x + (size.x / 2), pos.y + (size.y / 2) };
//
//    drawFilledRect(fvector2d(pos.x, pos.y), size.x, size.y, RGBtoFLC(2.083, 2.499, 2.999));
//    drawGradientFilledRectVertical(fvector2d(pos.x + 1, pos.y + 1), size.x - 2, size.y - 2, RGBtoFLC(1.000, 1.166, 1.333), RGBtoFLC(1.333, 1.583, 1.833), RGBtoFLC(1.666, 1.916, 2.249), 10);
//
//    //Bg
//    if (active)
//    {
//        drawFilledRect(fvector2d(pos.x, pos.y + size.y - 1), size.x, 1, RGBtoFLC(0, 180, 240));
//        if (name == L"R") {
//            canvas->k2_drawtexture(rage_icon, textPos, fvector2d(20, 20),
//                fvector2d(0.0f, 0.0f),
//                fvector2d(1.0f, 1.0f),
//                RGBtoFLC(0, 180, 240), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
//        }
//        else if (name == L"L") {
//            canvas->k2_drawtexture(legit_icon, textPos, fvector2d(20, 20),
//                fvector2d(0.0f, 0.0f),
//                fvector2d(1.0f, 1.0f),
//                RGBtoFLC(0, 180, 240), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
//        }
//        else if (name == L"V") {
//            canvas->k2_drawtexture(visuals_icon, textPos, fvector2d(20, 20),
//                fvector2d(0.0f, 0.0f),
//                fvector2d(1.0f, 1.0f),
//                RGBtoFLC(0, 180, 240), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
//        }
//        else if (name == L"S") {
//            canvas->k2_drawtexture(settings_icon, textPos, fvector2d(20, 20),
//                fvector2d(0.0f, 0.0f),
//                fvector2d(1.0f, 1.0f),
//                RGBtoFLC(0, 180, 240), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
//        }
//        else if (name == L"C") {
//            canvas->k2_drawtexture(config_icon, textPos, fvector2d(20, 20),
//                fvector2d(0.0f, 0.0f),
//                fvector2d(1.0f, 1.0f),
//                RGBtoFLC(0, 180, 240), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
//        }
//        else if (name == L"M") {
//            canvas->k2_drawtexture(local_icon, textPos, fvector2d(20, 20),
//                fvector2d(0.0f, 0.0f),
//                fvector2d(1.0f, 1.0f),
//                RGBtoFLC(0, 180, 240), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
//        }
//        else {
//            canvas->k2_drawtext(
//                font,
//                name,
//                textPos,
//                fvector2d(1.1, 1.0),
//                RGBtoFLC(0, 180, 240),
//                0.0f,
//                RGBtoFLC(0, 0, 0),
//                fvector2d(0, 0),
//                true,
//                true,
//                false,
//                RGBtoFLC(0, 0, 0)
//            );
//        }
//    }
//    else if (isHovered)
//    {
//        hover_element = true;
//        if (name == L"R") {
//            canvas->k2_drawtexture(rage_icon, textPos, fvector2d(20, 20),
//                fvector2d(0.0f, 0.0f),
//                fvector2d(1.0f, 1.0f),
//                RGBtoFLC(120, 120, 120), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
//        }
//        else if (name == L"L") {
//            canvas->k2_drawtexture(legit_icon, textPos, fvector2d(20, 20),
//                fvector2d(0.0f, 0.0f),
//                fvector2d(1.0f, 1.0f),
//                RGBtoFLC(120, 120, 120), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
//        }
//        else if (name == L"V") {
//            canvas->k2_drawtexture(visuals_icon, textPos, fvector2d(20, 20),
//                fvector2d(0.0f, 0.0f),
//                fvector2d(1.0f, 1.0f),
//                RGBtoFLC(120, 120, 120), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
//        }
//        else if (name == L"S") {
//            canvas->k2_drawtexture(settings_icon, textPos, fvector2d(20, 20),
//                fvector2d(0.0f, 0.0f),
//                fvector2d(1.0f, 1.0f),
//                RGBtoFLC(120, 120, 120), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
//        }
//        else if (name == L"C") {
//            canvas->k2_drawtexture(config_icon, textPos, fvector2d(20, 20),
//                fvector2d(0.0f, 0.0f),
//                fvector2d(1.0f, 1.0f),
//                RGBtoFLC(120, 120, 120), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
//        }
//        else if (name == L"M") {
//            canvas->k2_drawtexture(local_icon, textPos, fvector2d(20, 20),
//                fvector2d(0.0f, 0.0f),
//                fvector2d(1.0f, 1.0f),
//                RGBtoFLC(120, 120, 120), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
//        }
//        else {
//            canvas->k2_drawtext(
//                font,
//                name,
//                textPos,
//                fvector2d(1.1, 1.0),
//                RGBtoFLC(120, 120, 120),
//                0.0f,
//                RGBtoFLC(0, 0, 0),
//                fvector2d(0, 0),
//                true,
//                true,
//                false,
//                RGBtoFLC(0, 0, 0)
//            );
//        }
//    }
//    else
//    {
//        if (name == L"R") {
//            canvas->k2_drawtexture(rage_icon, textPos, fvector2d(20, 20),
//                fvector2d(0.0f, 0.0f),
//                fvector2d(1.0f, 1.0f),
//                RGBtoFLC(70, 70, 70), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
//        }
//        else if (name == L"L") {
//            canvas->k2_drawtexture(legit_icon, textPos, fvector2d(20, 20),
//                fvector2d(0.0f, 0.0f),
//                fvector2d(1.0f, 1.0f),
//                RGBtoFLC(70, 70, 70), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
//        }
//        else if (name == L"V") {
//            canvas->k2_drawtexture(visuals_icon, textPos, fvector2d(20, 20),
//                fvector2d(0.0f, 0.0f),
//                fvector2d(1.0f, 1.0f),
//                RGBtoFLC(70, 70, 70), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
//        }
//        else if (name == L"S") {
//            canvas->k2_drawtexture(settings_icon, textPos, fvector2d(20, 20),
//                fvector2d(0.0f, 0.0f),
//                fvector2d(1.0f, 1.0f),
//                RGBtoFLC(70, 70, 70), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
//        }
//        else if (name == L"C") {
//            canvas->k2_drawtexture(config_icon, textPos, fvector2d(20, 20),
//                fvector2d(0.0f, 0.0f),
//                fvector2d(1.0f, 1.0f),
//                RGBtoFLC(70, 70, 70), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
//        }
//        else if (name == L"M") {
//            canvas->k2_drawtexture(local_icon, textPos, fvector2d(20, 20),
//                fvector2d(0.0f, 0.0f),
//                fvector2d(1.0f, 1.0f),
//                RGBtoFLC(70, 70, 70), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
//        }
//        else {
//            canvas->k2_drawtext(
//                font,
//                name,
//                textPos,
//                fvector2d(1.1, 1.0),
//                RGBtoFLC(70, 70, 70),
//                0.0f,
//                RGBtoFLC(0, 0, 0),
//                fvector2d(0, 0),
//                true,
//                true,
//                false,
//                RGBtoFLC(0, 0, 0)
//            );
//        }
//    }
//
//    sameLine = false;
//    last_element_pos = pos;
//    last_element_size = size;
//    if (first_element_pos.x == 0.0f)
//        first_element_pos = pos;
//
//    if (isHovered && input::is_mouse_clicked(0, elements_count, false))
//        return true;
//
//    return false;
//}

// sysinfo colors

    bool ButtonTab(ucanvas* canvas, uobject* font, const wchar_t* name, fvector2d size, bool active)
    {
        elements_count++;

        fvector2d padding = fvector2d{ 0, 0 };
        fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
        if (sameLine)
        {
            pos.x = last_element_pos.x + last_element_size.x + offset_x;
            pos.y = last_element_pos.y;
        }
        if (pushY)
        {
            pos.y = pushYvalue;
            pushY = false;
            pushYvalue = 0.0f;
            offset_y = pos.y - menu_pos.y;
        }
        bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, size);

        if (!sameLine)
            offset_y += size.y + padding.y;

        fvector2d textPos = fvector2d{ pos.x + (size.x / 2), pos.y + (size.y / 2) };

        drawFilledRect(fvector2d(pos.x, pos.y), size.x, size.y, RGBtoFLC(2, 2, 2)); // mor border
        drawGradientFilledRectVertical(fvector2d(pos.x + 1, pos.y + 1), size.x - 2, size.y - 2, RGBtoFLC(1, 1, 1), RGBtoFLC(2, 1.3, 3.5), RGBtoFLC(1, 1, 1), 10); // mor gradient

        //Bg
        if (active)
        {
            drawFilledRect(fvector2d(pos.x, pos.y + size.y - 1), size.x, 1, RGBtoFLC(100, 180, 255)); // accent underline (purple)
            if (name == L"R") {
                canvas->k2_drawtexture(rage_icon, textPos, fvector2d(20, 20),
                    fvector2d(0.0f, 0.0f),
                    fvector2d(1.0f, 1.0f),
                    RGBtoFLC(100, 180, 255), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f)); // purple accent
            }
            else if (name == L"L") {
                canvas->k2_drawtexture(legit_icon, textPos, fvector2d(20, 20),
                    fvector2d(0.0f, 0.0f),
                    fvector2d(1.0f, 1.0f),
                    RGBtoFLC(100, 180, 255), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
            }
            else if (name == L"V") {
                canvas->k2_drawtexture(visuals_icon, textPos, fvector2d(20, 20),
                    fvector2d(0.0f, 0.0f),
                    fvector2d(1.0f, 1.0f),
                    RGBtoFLC(100, 180, 255), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
            }
            else if (name == L"S") {
                canvas->k2_drawtexture(settings_icon, textPos, fvector2d(20, 20),
                    fvector2d(0.0f, 0.0f),
                    fvector2d(1.0f, 1.0f),
                    RGBtoFLC(100, 180, 255), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
            }
            else if (name == L"C") {
                canvas->k2_drawtexture(config_icon, textPos, fvector2d(20, 20),
                    fvector2d(0.0f, 0.0f),
                    fvector2d(1.0f, 1.0f),
                    RGBtoFLC(100, 180, 255), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
            }
            else if (name == L"M") {
                canvas->k2_drawtexture(local_icon, textPos, fvector2d(20, 20),
                    fvector2d(0.0f, 0.0f),
                    fvector2d(1.0f, 1.0f),
                    RGBtoFLC(100, 180, 255), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
            }
            else {
                canvas->k2_drawtext(
                    font,
                    name,
                    textPos,
                    fvector2d(1.1, 1.0),
                    RGBtoFLC(100, 180, 255), // purple accent
                    0.0f,
                    RGBtoFLC(0, 0, 0),
                    fvector2d(0, 0),
                    true,
                    true,
                    false,
                    RGBtoFLC(0, 0, 0)
                );
            }
        }
        else if (isHovered)
        {
            hover_element = true;
            if (name == L"R") {
                canvas->k2_drawtexture(rage_icon, textPos, fvector2d(20, 20),
                    fvector2d(0.0f, 0.0f),
                    fvector2d(1.0f, 1.0f),
                    RGBtoFLC(120, 120, 120), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
            }
            else if (name == L"L") {
                canvas->k2_drawtexture(legit_icon, textPos, fvector2d(20, 20),
                    fvector2d(0.0f, 0.0f),
                    fvector2d(1.0f, 1.0f),
                    RGBtoFLC(120, 120, 120), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
            }
            else if (name == L"V") {
                canvas->k2_drawtexture(visuals_icon, textPos, fvector2d(20, 20),
                    fvector2d(0.0f, 0.0f),
                    fvector2d(1.0f, 1.0f),
                    RGBtoFLC(120, 120, 120), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
            }
            else if (name == L"S") {
                canvas->k2_drawtexture(settings_icon, textPos, fvector2d(20, 20),
                    fvector2d(0.0f, 0.0f),
                    fvector2d(1.0f, 1.0f),
                    RGBtoFLC(120, 120, 120), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
            }
            else if (name == L"C") {
                canvas->k2_drawtexture(config_icon, textPos, fvector2d(20, 20),
                    fvector2d(0.0f, 0.0f),
                    fvector2d(1.0f, 1.0f),
                    RGBtoFLC(120, 120, 120), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
            }
            else if (name == L"M") {
                canvas->k2_drawtexture(local_icon, textPos, fvector2d(20, 20),
                    fvector2d(0.0f, 0.0f),
                    fvector2d(1.0f, 1.0f),
                    RGBtoFLC(120, 120, 120), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
            }
            else {
                canvas->k2_drawtext(
                    font,
                    name,
                    textPos,
                    fvector2d(1.1, 1.0),
                    RGBtoFLC(120, 120, 120),
                    0.0f,
                    RGBtoFLC(0, 0, 0),
                    fvector2d(0, 0),
                    true,
                    true,
                    false,
                    RGBtoFLC(0, 0, 0)
                );
            }
        }
        else
        {
            if (name == L"R") {
                canvas->k2_drawtexture(rage_icon, textPos, fvector2d(20, 20),
                    fvector2d(0.0f, 0.0f),
                    fvector2d(1.0f, 1.0f),
                    RGBtoFLC(70, 70, 70), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
            }
            else if (name == L"L") {
                canvas->k2_drawtexture(legit_icon, textPos, fvector2d(20, 20),
                    fvector2d(0.0f, 0.0f),
                    fvector2d(1.0f, 1.0f),
                    RGBtoFLC(70, 70, 70), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
            }
            else if (name == L"V") {
                canvas->k2_drawtexture(visuals_icon, textPos, fvector2d(20, 20),
                    fvector2d(0.0f, 0.0f),
                    fvector2d(1.0f, 1.0f),
                    RGBtoFLC(70, 70, 70), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
            }
            else if (name == L"S") {
                canvas->k2_drawtexture(settings_icon, textPos, fvector2d(20, 20),
                    fvector2d(0.0f, 0.0f),
                    fvector2d(1.0f, 1.0f),
                    RGBtoFLC(70, 70, 70), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
            }
            else if (name == L"C") {
                canvas->k2_drawtexture(config_icon, textPos, fvector2d(20, 20),
                    fvector2d(0.0f, 0.0f),
                    fvector2d(1.0f, 1.0f),
                    RGBtoFLC(70, 70, 70), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
            }
            else if (name == L"M") {
                canvas->k2_drawtexture(local_icon, textPos, fvector2d(20, 20),
                    fvector2d(0.0f, 0.0f),
                    fvector2d(1.0f, 1.0f),
                    RGBtoFLC(70, 70, 70), e_blend_mode::translucent, 0.0f, fvector2d(0.5f, 0.5f));
            }
            else {
                canvas->k2_drawtext(
                    font,
                    name,
                    textPos,
                    fvector2d(1.1, 1.0),
                    RGBtoFLC(70, 70, 70),
                    0.0f,
                    RGBtoFLC(0, 0, 0),
                    fvector2d(0, 0),
                    true,
                    true,
                    false,
                    RGBtoFLC(0, 0, 0)
                );
            }
        }

        sameLine = false;
        last_element_pos = pos;
        last_element_size = size;
        if (first_element_pos.x == 0.0f)
            first_element_pos = pos;

        if (isHovered && input::is_mouse_clicked(0, elements_count, false))
            return true;

        return false;
    }

    // sns our colors
    //void SectionWrapper(ucanvas* canvas, uobject* font, fstring name, fvector2d size)
    //{
    //    fvector2d padding = fvector2d{ 0, 0 };
    //    fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };

    //    if (sameLine)
    //    {
    //        pos.x = menu_pos.x + padding.x + offset_x;
    //        pos.y = menu_pos.y + padding.y + offset_y;
    //    }

    //    // === Background ===
    //    drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, RGBtoFLC(0.833, 1.000, 1.250)); // main bg
    //    drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, 32, RGBtoFLC(1.749, 2.083, 2.416));    // header bg
    //    drawFilledRect(fvector2d{ pos.x, pos.y }, 0.5f, 32, RGBtoFLC(0, 180, 240));              // accent left bar
    //    drawFilledRect(fvector2d{ pos.x, pos.y + size.y - 1 }, size.x, 1, RGBtoFLC(3.499, 4.498, 5.831)); // bottom line

    //    // === Section Title Text ===
    //    fvector2d textPos = fvector2d{ pos.x + 16, pos.y + (32 / 2) }; // padding inside header
    //    canvas->k2_drawtext(
    //        font,
    //        name,
    //        textPos,
    //        fvector2d(1.0f, 0.97f),                 // scale
    //        RGBtoFLC(205, 205, 205),                 // text color (light gray/white)
    //        0.0f,
    //        RGBtoFLC(0, 0, 0),
    //        fvector2d(0, 0),
    //        false, true, false,
    //        RGBtoFLC(0, 0, 0)
    //    );

    //    // === Update offsets for next elements ===
    //    menu::offset_y += 32 + 7;
    //    sameLine = false;
    //}

    // sysinfo colors

    void SectionWrapper(ucanvas* canvas, uobject* font, fstring name, fvector2d size)
    {
        fvector2d padding = fvector2d{ 0, 0 };
        fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };

        if (sameLine)
        {
            pos.x = menu_pos.x + padding.x + offset_x;
            pos.y = menu_pos.y + padding.y + offset_y;
        }

        // === Background ===
        drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, RGBtoFLC(0, 0, 0)); // section bg
        drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, 32, RGBtoFLC(0, 0, 0));          // header bg
        drawFilledRect(fvector2d{ pos.x, pos.y }, 0.5f, 32, RGBtoFLC(100, 180, 255));        // accent left bar
        drawFilledRect(fvector2d{ pos.x, pos.y + size.y - 1 }, size.x, 1, RGBtoFLC(15, 15, 15)); // bottom line

        // === Section Title Text ===
        fvector2d textPos = fvector2d{ pos.x + 16, pos.y + (32 / 2) }; // padding inside header
        canvas->k2_drawtext(
            font,
            name,
            textPos,
            fvector2d(1.0f, 0.97f),                 // scale
            RGBtoFLC(205, 205, 205),                 // text color (light gray/white)
            0.0f,
            RGBtoFLC(0, 0, 0),
            fvector2d(0, 0),
            false, true, false,
            RGBtoFLC(0, 0, 0)
        );

        // === Update offsets for next elements ===
        menu::offset_y += 32 + 7;
        sameLine = false;
    }

    static float cursor_x = 0;
    static float cursor_y = 0;
    static float same_line_offset = 0;

    void SetCursorPos(float x, float y) {
        cursor_x = x;
        cursor_y = y;
        same_line_offset = 0;
    }

    void NewLine(float spacing = 15.0f) {
        cursor_y += spacing;
        same_line_offset = 0;
    }

    void SameLine()
    {
        sameLine = true;
    }

    // sns our colors
    // 
    //void Checkbox(uobject* font, const wchar_t* name, bool* value)
    //{
    //    elements_count++;

    //    float sizex = 16.5f;
    //    fvector2d padding = fvector2d{ 14,10 };
    //    fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };

    //    if (sameLine)
    //    {
    //        pos.x = last_element_pos.x + last_element_size.x + padding.x;
    //        pos.y = last_element_pos.y;
    //    }
    //    if (pushY)
    //    {
    //        pos.y = pushYvalue;
    //        pushY = false;
    //        pushYvalue = 0.0f;
    //        offset_y = pos.y - menu_pos.y;
    //    }

    //    // Checkbox zone
    //    bool isHovered = MouseInZone(fvector2d{ pos.x + 269, pos.y }, fvector2d{ sizex, sizex });

    //    // Draw label text slightly right of checkbox
    //    fvector2d textPos = fvector2d{ pos.x, pos.y + (sizex / 4) };

    //    if (!sameLine)
    //        offset_y += sizex + padding.y;

    //    // Checkbox drawing
    //    if (*value)
    //    {
    //        canvas->k2_drawtext(font, name, textPos, fvector2d(1.05, 0.99),
    //            RGBtoFLC(215, 215, 215), 0.0f, RGBtoFLC(0, 0, 0),
    //            fvector2d(0, 0), false, false, false, RGBtoFLC(0, 0, 0));

    //        // Outer border
    //        drawFilledRect(fvector2d{ pos.x + 269, pos.y }, sizex, sizex, RGBtoFLC(0, 180, 240));
    //        // Inner background
    //        drawFilledRect(fvector2d{ pos.x + 269 + 1, pos.y + 1 }, sizex - 2, sizex - 2, RGBtoFLC(1.25, 1.416, 1.749));
    //        // Check fill
    //        drawFilledRect(fvector2d{ pos.x + 269 + 3, pos.y + 3 }, sizex - 6, sizex - 6, RGBtoFLC(0, 180, 240));
    //    }
    //    else
    //    {
    //        canvas->k2_drawtext(font, name, textPos, fvector2d(1.05, 0.99),
    //            RGBtoFLC(120, 120, 120), 0.0f, RGBtoFLC(0, 0, 0),
    //            fvector2d(0, 0), false, false, false, RGBtoFLC(0, 0, 0));

    //        // Outer border
    //        drawFilledRect(fvector2d{ pos.x + 269, pos.y }, sizex, sizex, RGBtoFLC(3.499, 4.498, 5.831));
    //        // Inner background
    //        drawFilledRect(fvector2d{ pos.x + 269 + 1, pos.y + 1 }, sizex - 2, sizex - 2, RGBtoFLC(1.25, 1.416, 1.749));
    //    }

    //    sameLine = false;
    //    last_element_pos = pos;
    //    if (first_element_pos.x == 0.0f)
    //        first_element_pos = pos;

    //    if (isHovered && input::is_mouse_clicked(0, elements_count, false))
    //        *value = !*value;
    //}

    //bool checkbox_enabled[256];
    //void Combobox(uobject* font, fvector2d size, int* value, const wchar_t* arg, ...)
    //{
    //    elements_count++;

    //    fvector2d padding = fvector2d{ 14, 14 };
    //    fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };

    //    if (sameLine)
    //    {
    //        pos.x = last_element_pos.x + last_element_size.x + padding.x;
    //        pos.y = last_element_pos.y;
    //    }
    //    if (pushY)
    //    {
    //        pos.y = pushYvalue;
    //        pushY = false;
    //        pushYvalue = 20.0f;
    //        offset_y = pos.y - menu_pos.y;
    //    }

    //    bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, size);

    //    // FIRST: Draw dropdown items if open (this puts them behind the main combobox but above other elements)
    //    if (checkbox_enabled[elements_count])
    //    {
    //        fvector2d element_pos = pos;
    //        int num = 0;
    //        flinearcolor dropdown_bg = RGBtoFLC(5.166, 5.416, 5.666);
    //        flinearcolor dropdown_bg_hover = RGBtoFLC(6.166, 6.416, 6.666);

    //        va_list arguments;
    //        va_start(arguments, arg);
    //        for (const wchar_t* current_arg = arg; current_arg != NULL; current_arg = va_arg(arguments, const wchar_t*))
    //        {
    //            element_pos.y += 25.0f;
    //            bool isHovered2 = MouseInZone(fvector2d{ element_pos.x, element_pos.y }, fvector2d{ size.x, 25.0f });

    //            // Draw dropdown item with proper positioning and borders
    //            if (isHovered2)
    //            {
    //                hover_element = true;
    //                // Draw background with border
    //                drawFilledRect(element_pos, size.x, 25.0f, dropdown_bg_hover);
    //                // Draw inner fill
    //                drawFilledRect(fvector2d{ element_pos.x + 1, element_pos.y + 1 }, size.x - 2, 23.0f,
    //                    RGBtoFLC(3.166, 3.416, 3.666));

    //                if (input::is_mouse_clicked(0, elements_count, false))
    //                {
    //                    *value = num;
    //                    checkbox_enabled[elements_count] = false;
    //                }
    //            }
    //            else
    //            {
    //                // Draw background with border
    //                drawFilledRect(element_pos, size.x, 25.0f, dropdown_bg);
    //                // Draw inner fill
    //                drawFilledRect(fvector2d{ element_pos.x + 1, element_pos.y + 1 }, size.x - 2, 23.0f,
    //                    RGBtoFLC(2.166, 2.416, 2.666));
    //            }

    //            canvas->k2_drawtext(font, current_arg, fvector2d{ element_pos.x + (size.x / 2), element_pos.y + (size.y / 2) },
    //                fvector2d(1.0f, 0.9f), RGBtoFLC(230, 230, 230),
    //                0.0f, flinearcolor(), fvector2d(0, 0), true, true, false, flinearcolor());

    //            num++;
    //        }
    //        va_end(arguments);
    //    }

    //    // SECOND: Draw main combobox background with border (this stays on top of dropdown items)
    //    drawFilledRect(pos, size.x, size.y, RGBtoFLC(3.499, 4.498, 5.831));

    //    // --- BACKGROUND (horizontal gradient) ---
    //    if (isHovered || checkbox_enabled[elements_count])
    //    {
    //        // Inner fill
    //        drawFilledRect(fvector2d{ pos.x + 1, pos.y + 1 }, size.x - 2, size.y - 2, RGBtoFLC(2.166, 2.416, 2.666));

    //        hover_element = true;
    //    }
    //    else
    //    {
    //        drawFilledRect(fvector2d{ pos.x + 1, pos.y + 1 }, size.x - 2, size.y - 2, RGBtoFLC(1.166, 1.416, 1.666));
    //    }

    //    if (!sameLine)
    //        offset_y += size.y + padding.y;

    //    // THIRD: Draw selected item text and arrow (on top of everything)
    //    va_list arguments2;
    //    va_start(arguments2, arg);
    //    int num2 = 0;
    //    for (const wchar_t* current_arg = arg; current_arg != NULL; current_arg = va_arg(arguments2, const wchar_t*))
    //    {
    //        // Draw selected item text
    //        if (num2 == *value)
    //        {
    //            fvector2d _textPos = fvector2d{ pos.x + size.x / 2, pos.y + size.y / 2 };
    //            canvas->k2_drawtext(font, current_arg, _textPos,
    //                fvector2d(1.0f, 0.9f), RGBtoFLC(220, 220, 220),
    //                0.0f, flinearcolor(), fvector2d(0, 0), true, true, false, flinearcolor());
    //            break;
    //        }
    //        num2++;
    //    }
    //    va_end(arguments2);

    //    // Dropdown arrow
    //    canvas->k2_drawtext(font, s2wc("v"), fvector2d{ pos.x + size.x - 25, pos.y + (size.y / 2) - 2.0f },
    //        fvector2d(1.6f, 0.8f), RGBtoFLC(90, 90, 90),
    //        0.0f, flinearcolor(), fvector2d(0, 0), false, true, false, flinearcolor());

    //    // --- OPEN/CLOSE LOGIC ---
    //    if (isHovered && input::is_mouse_clicked(0, elements_count, false))
    //        checkbox_enabled[elements_count] = !checkbox_enabled[elements_count];

    //    if (!isHovered && input::is_mouse_clicked(0, elements_count, false))
    //        checkbox_enabled[elements_count] = false;

    //    sameLine = false;
    //    last_element_pos = pos;
    //    last_element_size = size;
    //    if (first_element_pos.x == 0.0f)
    //        first_element_pos = pos;
    //}

    //void SliderFloat(uobject* font, float* value, float min, float max, const char* label, const char* format = "%.0f")
    //{
    //    elements_count++;
    //    fvector2d size = fvector2d{ 286, 22 };
    //    fvector2d slider_size = fvector2d{ 286, 11 };
    //    fvector2d adjust_zone = fvector2d{ 0, 20 };
    //    fvector2d padding = fvector2d{ 14, 14 };
    //    fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
    //    if (sameLine)
    //    {
    //        pos.x = last_element_pos.x + last_element_size.x + padding.x;
    //        pos.y = last_element_pos.y;
    //    }
    //    if (pushY)
    //    {
    //        pos.y = pushYvalue;
    //        pushY = false;
    //        pushYvalue = 0.0f;
    //        offset_y = pos.y - menu_pos.y;
    //    }

    //    // ADD THIS - Move just the slider bar down by 10 pixels
    //    float slider_offset_y = 10.0f;

    //    bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y + slider_size.y + padding.y - adjust_zone.y + slider_offset_y }, fvector2d{ slider_size.x, slider_size.y + adjust_zone.y * 1.5f });

    //    if (!sameLine)
    //        offset_y += size.y + padding.y;

    //    // UPDATED: Draw the label text with larger size and positioned lower (closer to slider)
    //    canvas->k2_drawtext(font, s2wc(label), fvector2d(pos.x, pos.y + 8.0f), fvector2d(0.95, 0.88), RGBtoFLC(170, 170, 170), 0.0f, RGBtoFLC(0, 0, 0), fvector2d(0, 0), false, false, false, RGBtoFLC(0, 0, 0));

    //    //Bg - ADD slider_offset_y TO ALL SLIDER DRAWING POSITIONS
    //    if (isHovered || current_element == elements_count)
    //    {
    //        //Drag
    //        if (input::is_mouse_clicked(0, elements_count, true))
    //        {
    //            current_element = elements_count;

    //            fvector2d cursorPos = CursorPos();
    //            *value = ((cursorPos.x - pos.x) * ((max - min) / slider_size.x)) + min;
    //            if (*value < min) *value = min;
    //            if (*value > max) *value = max;
    //        }

    //        drawFilledRect(fvector2d{ pos.x, pos.y + slider_size.y + padding.y + slider_offset_y }, slider_size.x, slider_size.y, RGBtoFLC(2.666, 3.332, 4.165));
    //        drawFilledRect(fvector2d{ pos.x + 1, pos.y + slider_size.y + padding.y + 1 + slider_offset_y }, slider_size.x - 2, slider_size.y - 2, RGBtoFLC(2.999, 3.249, 3.666));

    //        hover_element = true;
    //    }
    //    else
    //    {
    //        drawFilledRect(fvector2d{ pos.x, pos.y + slider_size.y + padding.y + slider_offset_y }, slider_size.x, slider_size.y, RGBtoFLC(2.666, 3.332, 4.165));
    //        drawFilledRect(fvector2d{ pos.x + 1, pos.y + slider_size.y + padding.y + 1 + slider_offset_y }, slider_size.x - 2, slider_size.y - 2, RGBtoFLC(1.999, 2.249, 2.666));
    //    }

    //    //Value - ADD slider_offset_y HERE TOO
    //    float oneP = slider_size.x / (max - min);
    //    drawFilledRect(fvector2d{ pos.x + 1, pos.y + slider_size.y + padding.y + 1 + slider_offset_y }, oneP * (*value - min) - 2, slider_size.y - 2, RGBtoFLC(0, 180, 240));

    //    // Keep the value box and text at original position
    //    drawFilledRect(fvector2d{ pos.x + slider_size.x - 28 - (56 / 2), pos.y - 4.0f }, 56, 29, RGBtoFLC(2.666, 3.332, 4.165));
    //    drawFilledRect(fvector2d{ pos.x + slider_size.x - 28 - (56 / 2) + 1 , pos.y - 4.0f + 1 }, 56 - 2, 29 - 2, RGBtoFLC(1.999, 2.249, 2.666));

    //    char buffer[32];
    //    sprintf_s(buffer, format, *value);
    //    canvas->k2_drawtext(font, s2wc(buffer), fvector2d(pos.x + slider_size.x - 28, pos.y - 4.0f + (29 / 2) - 7.5f), fvector2d(1.1, 0.98), RGBtoFLC(78, 78, 78), 0.0f, RGBtoFLC(0, 0, 0), fvector2d(0, 0), true, false, false, RGBtoFLC(0, 0, 0));

    //    sameLine = false;
    //    last_element_pos = pos;
    //    last_element_size = size;
    //    if (first_element_pos.x == 0.0f)
    //        first_element_pos = pos;
    //}

    // sysinfo colors

    void Checkbox(uobject* font, const wchar_t* name, bool* value)
    {
        elements_count++;

        float sizex = 12.0f;
        fvector2d padding = fvector2d{ 14,10 };
        fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };

        if (sameLine)
        {
            pos.x = last_element_pos.x + last_element_size.x + padding.x;
            pos.y = last_element_pos.y;
        }
        if (pushY)
        {
            pos.y = pushYvalue;
            pushY = false;
            pushYvalue = 0.0f;
            offset_y = pos.y - menu_pos.y;
        }

        bool isHovered = MouseInZone(fvector2d{ pos.x + 170, pos.y }, fvector2d{ sizex, sizex });

        fvector2d textPos = fvector2d{ pos.x, pos.y + (sizex / 4) };

        if (!sameLine)
            offset_y += sizex + padding.y;

        if (*value)
        {
            canvas->k2_drawtext(font, name, textPos, fvector2d(0.85, 0.80),
                RGBtoFLC(80, 160, 255), 0.0f, RGBtoFLC(0, 0, 0),
                fvector2d(0, 0), false, false, false, RGBtoFLC(5, 10, 20));

            // Outer border (accent)
            drawFilledRect(fvector2d{ pos.x + 170, pos.y }, sizex, sizex, RGBtoFLC(100, 180, 255));
            // Inner background
            drawFilledRect(fvector2d{ pos.x + 170 + 1, pos.y + 1 }, sizex - 2, sizex - 2, RGBtoFLC(5, 15, 30));
            // Checkmark tick
            canvas->k2_drawtext(font, L"\u2713", fvector2d{ pos.x + 170 + 1, pos.y - 1 }, fvector2d(0.75, 0.75),
                RGBtoFLC(120, 200, 255), 0.0f, RGBtoFLC(0, 0, 0),
                fvector2d(0, 0), false, true, false, RGBtoFLC(0, 0, 0));
        }
        else
        {
            canvas->k2_drawtext(font, name, textPos, fvector2d(0.85, 0.80),
                RGBtoFLC(160, 160, 160), 0.0f, RGBtoFLC(0, 0, 0),
                fvector2d(0, 0), false, false, false, RGBtoFLC(0, 0, 0));

            drawFilledRect(fvector2d{ pos.x + 170, pos.y }, sizex, sizex, RGBtoFLC(3, 3, 3));
            drawFilledRect(fvector2d{ pos.x + 170 + 1, pos.y + 1 }, sizex - 2, sizex - 2, RGBtoFLC(1.5, 1.5, 1.5));
        }

        sameLine = false;
        last_element_pos = pos;
        if (first_element_pos.x == 0.0f)
            first_element_pos = pos;

        if (isHovered && input::is_mouse_clicked(0, elements_count, false))
            *value = !*value;
    }

    bool checkbox_enabled[256];
    void Combobox(uobject* font, fvector2d size, int* value, const wchar_t* arg, ...)
    {
        elements_count++;

        fvector2d padding = fvector2d{ 14, 14 };
        fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };

        if (sameLine)
        {
            pos.x = last_element_pos.x + last_element_size.x + padding.x;
            pos.y = last_element_pos.y;
        }
        if (pushY)
        {
            pos.y = pushYvalue;
            pushY = false;
            pushYvalue = 20.0f;
            offset_y = pos.y - menu_pos.y;
        }

        bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, size);

        // FIRST: Draw dropdown items if open (this puts them behind the main combobox but above other elements)
        if (checkbox_enabled[elements_count])
        {
            fvector2d element_pos = pos;
            int num = 0;
            flinearcolor dropdown_bg = RGBtoFLC(5.166, 5.416, 5.666);
            flinearcolor dropdown_bg_hover = RGBtoFLC(6.166, 6.416, 6.666);

            va_list arguments;
            va_start(arguments, arg);
            for (const wchar_t* current_arg = arg; current_arg != NULL; current_arg = va_arg(arguments, const wchar_t*))
            {
                element_pos.y += 25.0f;
                bool isHovered2 = MouseInZone(fvector2d{ element_pos.x, element_pos.y }, fvector2d{ size.x, 25.0f });

                // Draw dropdown item with proper positioning and borders
                if (isHovered2)
                {
                    hover_element = true;
                    // Draw background with border
                    drawFilledRect(element_pos, size.x, 25.0f, dropdown_bg_hover);
                    // Draw inner fill
                    drawFilledRect(fvector2d{ element_pos.x + 1, element_pos.y + 1 }, size.x - 2, 23.0f,
                        RGBtoFLC(3.166, 3.416, 3.666));

                    if (input::is_mouse_clicked(0, elements_count, false))
                    {
                        *value = num;
                        checkbox_enabled[elements_count] = false;
                    }
                }
                else
                {
                    // Draw background with border
                    drawFilledRect(element_pos, size.x, 25.0f, dropdown_bg);
                    // Draw inner fill
                    drawFilledRect(fvector2d{ element_pos.x + 1, element_pos.y + 1 }, size.x - 2, 23.0f,
                        RGBtoFLC(2, 2, 2));
                }

                canvas->k2_drawtext(font, current_arg, fvector2d{ element_pos.x + (size.x / 2), element_pos.y + (size.y / 2) },
                    fvector2d(1.0f, 0.9f), RGBtoFLC(230, 230, 230),
                    0.0f, flinearcolor(), fvector2d(0, 0), true, true, false, flinearcolor());

                num++;
            }
            va_end(arguments);
        }

        // SECOND: Draw main combobox background with border (this stays on top of dropdown items)
        drawFilledRect(pos, size.x, size.y, RGBtoFLC(3, 3, 3));

        // --- BACKGROUND (horizontal gradient) ---
        if (isHovered || checkbox_enabled[elements_count])
        {
            // Inner fill
            drawFilledRect(fvector2d{ pos.x + 1, pos.y + 1 }, size.x - 2, size.y - 2, RGBtoFLC(2, 2, 2));

            hover_element = true;
        }
        else
        {
            drawFilledRect(fvector2d{ pos.x + 1, pos.y + 1 }, size.x - 2, size.y - 2, RGBtoFLC(1, 1, 1));
        }

        if (!sameLine)
            offset_y += size.y + padding.y;

        // THIRD: Draw selected item text and arrow (on top of everything)
        va_list arguments2;
        va_start(arguments2, arg);
        int num2 = 0;
        for (const wchar_t* current_arg = arg; current_arg != NULL; current_arg = va_arg(arguments2, const wchar_t*))
        {
            // Draw selected item text
            if (num2 == *value)
            {
                fvector2d _textPos = fvector2d{ pos.x + size.x / 2, pos.y + size.y / 2 };
                canvas->k2_drawtext(font, current_arg, _textPos,
                    fvector2d(1.0f, 0.9f), RGBtoFLC(220, 220, 220),
                    0.0f, flinearcolor(), fvector2d(0, 0), true, true, false, flinearcolor());
                break;
            }
            num2++;
        }
        va_end(arguments2);

        // Dropdown arrow
        canvas->k2_drawtext(font, s2wc("v"), fvector2d{ pos.x + size.x - 25, pos.y + (size.y / 2) - 2.0f },
            fvector2d(1.6f, 0.8f), RGBtoFLC(90, 90, 90),
            0.0f, flinearcolor(), fvector2d(0, 0), false, true, false, flinearcolor());

        // --- OPEN/CLOSE LOGIC ---
        if (isHovered && input::is_mouse_clicked(0, elements_count, false))
            checkbox_enabled[elements_count] = !checkbox_enabled[elements_count];

        if (!isHovered && input::is_mouse_clicked(0, elements_count, false))
            checkbox_enabled[elements_count] = false;

        sameLine = false;
        last_element_pos = pos;
        last_element_size = size;
        if (first_element_pos.x == 0.0f)
            first_element_pos = pos;
    }

    void SliderFloat(uobject* font, float* value, float min, float max, const char* label, const char* format = "%.0f")
    {
        elements_count++;
        fvector2d size = fvector2d{ 240, 22 };
        fvector2d slider_size = fvector2d{ 240, 8 };
        fvector2d adjust_zone = fvector2d{ 0, 16 };
        fvector2d padding = fvector2d{ 14, 14 };
        fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
        if (sameLine)
        {
            pos.x = last_element_pos.x + last_element_size.x + padding.x;
            pos.y = last_element_pos.y;
        }
        if (pushY)
        {
            pos.y = pushYvalue;
            pushY = false;
            pushYvalue = 0.0f;
            offset_y = pos.y - menu_pos.y;
        }

        float slider_offset_y = 10.0f;

        bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y + slider_size.y + padding.y - adjust_zone.y + slider_offset_y }, fvector2d{ slider_size.x, slider_size.y + adjust_zone.y * 1.5f });

        if (!sameLine)
            offset_y += size.y + padding.y;

        canvas->k2_drawtext(font, s2wc(label), fvector2d(pos.x, pos.y + 8.0f), fvector2d(0.95, 0.88), RGBtoFLC(170, 170, 170), 0.0f, RGBtoFLC(0, 0, 0), fvector2d(0, 0), false, false, false, RGBtoFLC(0, 0, 0));

        if (isHovered || current_element == elements_count)
        {
            if (input::is_mouse_clicked(0, elements_count, true))
            {
                current_element = elements_count;

                fvector2d cursorPos = CursorPos();
                *value = ((cursorPos.x - pos.x) * ((max - min) / slider_size.x)) + min;
                if (*value < min) *value = min;
                if (*value > max) *value = max;
            }

            drawFilledRect(fvector2d{ pos.x, pos.y + slider_size.y + padding.y + slider_offset_y }, slider_size.x, slider_size.y, RGBtoFLC(2, 2, 2));
            drawFilledRect(fvector2d{ pos.x + 1, pos.y + slider_size.y + padding.y + 1 + slider_offset_y }, slider_size.x - 2, slider_size.y - 2, RGBtoFLC(4, 2.5, 6.5));

            hover_element = true;
        }
        else
        {
            drawFilledRect(fvector2d{ pos.x, pos.y + slider_size.y + padding.y + slider_offset_y }, slider_size.x, slider_size.y, RGBtoFLC(2, 2, 2));
            drawFilledRect(fvector2d{ pos.x + 1, pos.y + slider_size.y + padding.y + 1 + slider_offset_y }, slider_size.x - 2, slider_size.y - 2, RGBtoFLC(2.5, 1.5, 4));
        }

        // Value bar (accent color)
        float oneP = slider_size.x / (max - min);
        drawFilledRect(fvector2d{ pos.x + 1, pos.y + slider_size.y + padding.y + 1 + slider_offset_y }, oneP * (*value - min) - 2, slider_size.y - 2, RGBtoFLC(100, 180, 255));

        drawFilledRect(fvector2d{ pos.x + slider_size.x - 22 - (44 / 2), pos.y - 2.0f }, 44, 24, RGBtoFLC(2, 2, 2));
        drawFilledRect(fvector2d{ pos.x + slider_size.x - 22 - (44 / 2) + 1 , pos.y - 2.0f + 1 }, 44 - 2, 24 - 2, RGBtoFLC(2.5, 1.5, 4));

        char buffer[32];
        sprintf_s(buffer, format, *value);
        canvas->k2_drawtext(font, s2wc(buffer), fvector2d(pos.x + slider_size.x - 22, pos.y - 2.0f + (24 / 2) - 7.5f), fvector2d(1.1, 0.98), RGBtoFLC(78, 78, 78), 0.0f, RGBtoFLC(0, 0, 0), fvector2d(0, 0), true, false, false, RGBtoFLC(0, 0, 0));

        sameLine = false;
        last_element_pos = pos;
        last_element_size = size;
        if (first_element_pos.x == 0.0f)
            first_element_pos = pos;
    }


    int active_hotkey = -1;
    bool already_pressed = false;
    std::string VirtualKeyCodeToString(UCHAR virtualKey)
    {
        UINT scanCode = MapVirtualKey(virtualKey, MAPVK_VK_TO_VSC);
        if (virtualKey == VK_LBUTTON)
        {
            return ("MOUSE0");
        }
        if (virtualKey == VK_RBUTTON)
        {
            return ("MOUSE1");
        }
        if (virtualKey == VK_MBUTTON)
        {
            return ("MBUTTON");
        }
        if (virtualKey == VK_XBUTTON1)
        {
            return ("XBUTTON1");
        }
        if (virtualKey == VK_XBUTTON2)
        {
            return ("XBUTTON2");
        }


        CHAR szName[128];
        int result = 0;
        switch (virtualKey)
        {
        case VK_LEFT: case VK_UP: case VK_RIGHT: case VK_DOWN:
        case VK_RCONTROL: case VK_RMENU:
        case VK_LWIN: case VK_RWIN: case VK_APPS:
        case VK_PRIOR: case VK_NEXT:
        case VK_END: case VK_HOME:
        case VK_INSERT: case VK_DELETE:
        case VK_DIVIDE:
        case VK_NUMLOCK:
            scanCode |= KF_EXTENDED;
        default:
            result = GetKeyNameTextA(scanCode << 16, szName, 128);
        }

        return szName;
    }
    void Hotkey(uobject* font, const char* name, fvector2d size, int* key)
    {
        elements_count++;
        fvector2d padding = fvector2d{ 14, 14 };
        fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };

        if (sameLine)
        {
            pos.x = last_element_pos.x + last_element_size.x + padding.x;
            pos.y = last_element_pos.y;
        }
        if (pushY)
        {
            pos.y = pushYvalue;
            pushY = false;
            pushYvalue = 0.0f;
            offset_y = pos.y - menu_pos.y;
        }

        bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, fvector2d{ 44, 24 });

        drawFilledRect(fvector2d{ pos.x, pos.y }, 44, 24, RGBtoFLC(50, 50, 50));
        drawFilledRect(fvector2d{ pos.x + 1, pos.y + 1 }, 44 - 2, 24 - 2, RGBtoFLC(60, 60, 60));

        if (!sameLine)
            offset_y += 24 + padding.y;

        fvector2d textPos = fvector2d{ pos.x + 22, pos.y + 12.0f };

        if (active_hotkey == elements_count)
        {
            canvas->k2_drawtext(font, L"...", textPos, fvector2d(0.85, 0.85),
                RGBtoFLC(78, 78, 78), 0.0f, RGBtoFLC(0, 0, 0),
                fvector2d(0, 0), true, true, false, RGBtoFLC(0, 0, 0));

            if (!Input::IsAnyMouseDown())
            {
                already_pressed = false;
            }

            if (!already_pressed)
            {
                for (int code = 0; code < 255; code++)
                {
                    if (GetAsyncKeyState(code))
                    {
                        *key = code;
                        active_hotkey = -1;
                    }
                }
            }
        }
        else
        {
            canvas->k2_drawtext(font, s2wc(VirtualKeyCodeToString(*key).c_str()), textPos,
                fvector2d(0.85, 0.85), RGBtoFLC(78, 78, 78), 0.0f, RGBtoFLC(0, 0, 0),
                fvector2d(0, 0), true, true, false, RGBtoFLC(0, 0, 0));

            if (isHovered)
            {
                if (input::is_mouse_clicked(0, elements_count, false))
                {
                    already_pressed = true;
                    active_hotkey = elements_count;

                    //Queue Fix
                    for (int code = 0; code < 255; code++)
                        if (GetAsyncKeyState(code)) {}
                }
            }
            else
            {
                if (input::is_mouse_clicked(0, elements_count, false))
                {
                    active_hotkey = -1;
                }
            }
        }

        sameLine = false;
        last_element_pos = pos;
        last_element_size = fvector2d{ 44, 24 };
        if (first_element_pos.x == 0.0f)
            first_element_pos = pos;
    }

    bool multi_combobox_enabled[256];
    std::vector<bool> multi_combobox_values[256];

    void MultiCombobox(uobject* font, fvector2d size, const wchar_t* name, const wchar_t* arg, ...)
    {
        elements_count++;

        fvector2d padding = fvector2d{ 14, 14 };
        fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };

        if (sameLine)
        {
            pos.x = last_element_pos.x + last_element_size.x + padding.x;
            pos.y = last_element_pos.y;
        }
        if (pushY)
        {
            pos.y = pushYvalue;
            pushY = false;
            pushYvalue = 0.0f;
            offset_y = pos.y - menu_pos.y;
        }

        bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, size);

        // Draw main combobox background with border
        drawFilledRect(pos, size.x, size.y, RGBtoFLC(3, 3, 3));

        // --- BACKGROUND (same as combobox) ---
        if (isHovered || multi_combobox_enabled[elements_count])
        {
            // Inner fill
            drawFilledRect(fvector2d{ pos.x + 1, pos.y + 1 }, size.x - 2, size.y - 2, RGBtoFLC(2, 2, 2));
            hover_element = true;
        }
        else
        {
            drawFilledRect(fvector2d{ pos.x + 1, pos.y + 1 }, size.x - 2, size.y - 2, RGBtoFLC(1, 1, 1));
        }

        if (!sameLine)
            offset_y += size.y + padding.y;

        // Dropdown arrow
        canvas->k2_drawtext(font, s2wc("v"), fvector2d{ pos.x + size.x - 25, pos.y + (size.y / 2) - 2.0f },
            fvector2d(1.6f, 0.8f), RGBtoFLC(90, 90, 90),
            0.0f, flinearcolor(), fvector2d(0, 0), false, true, false, flinearcolor());

        // Initialize values if first time
        if (multi_combobox_values[elements_count].empty())
        {
            va_list args;
            va_start(args, arg);
            for (const wchar_t* current = arg; current != NULL; current = va_arg(args, const wchar_t*))
            {
                multi_combobox_values[elements_count].push_back(false);
            }
            va_end(args);
        }

        // Count selected items for display
        int selectedCount = 0;
        std::wstring displayText = L"";

        va_list arguments;
        va_start(arguments, arg);
        int num = 0;
        for (const wchar_t* current = arg; current != NULL; current = va_arg(arguments, const wchar_t*))
        {
            if (multi_combobox_values[elements_count][num])
            {
                selectedCount++;
                if (displayText.empty())
                    displayText = current;
                else if (selectedCount == 2)
                    displayText = L"Multiple...";
            }
            num++;
        }
        va_end(arguments);

        if (selectedCount == 0)
            displayText = name;

        // Draw selected items text (CENTERED like combobox)
        fvector2d textPos = fvector2d{ pos.x + size.x / 2, pos.y + size.y / 2 };
        canvas->k2_drawtext(font, displayText.c_str(), textPos,
            fvector2d(1.0f, 0.9f), RGBtoFLC(220, 220, 220),
            0.0f, flinearcolor(), fvector2d(0, 0), true, true, false, flinearcolor());

        // Draw dropdown items
        if (multi_combobox_enabled[elements_count])
        {
            fvector2d element_pos = fvector2d{ pos.x, pos.y + size.y };
            int itemIndex = 0;

            // Store the original background color for dropdown items (same as combobox)
            flinearcolor dropdown_bg = RGBtoFLC(5.166, 5.416, 5.666);
            flinearcolor dropdown_bg_hover = RGBtoFLC(6.166, 6.416, 6.666);

            va_list items;
            va_start(items, arg);
            for (const wchar_t* current = arg; current != NULL; current = va_arg(items, const wchar_t*))
            {
                bool isHoveredItem = MouseInZone(fvector2d{ element_pos.x, element_pos.y }, fvector2d{ size.x, 25.0f });

                // Draw dropdown item with proper positioning and borders (same as combobox)
                if (isHoveredItem)
                {
                    hover_element = true;
                    // Draw background with border
                    drawFilledRect(element_pos, size.x, 25.0f, dropdown_bg_hover);
                    // Draw inner fill
                    drawFilledRect(fvector2d{ element_pos.x + 1, element_pos.y + 1 }, size.x - 2, 23.0f,
                        RGBtoFLC(3.166, 3.416, 3.666));

                    if (input::is_mouse_clicked(0, elements_count, false))
                    {
                        multi_combobox_values[elements_count][itemIndex] = !multi_combobox_values[elements_count][itemIndex];
                    }
                }
                else
                {
                    // Draw background with border
                    drawFilledRect(element_pos, size.x, 25.0f, dropdown_bg);
                    // Draw inner fill
                    drawFilledRect(fvector2d{ element_pos.x + 1, element_pos.y + 1 }, size.x - 2, 23.0f,
                        RGBtoFLC(2, 2, 2));
                }

                // Checkmark if selected
                if (multi_combobox_values[elements_count][itemIndex])
                {
                    canvas->k2_drawtext(font, current, fvector2d{ element_pos.x + (size.x / 2), element_pos.y + (25.0f / 2) },
                        fvector2d(1.0f, 0.9f), RGBtoFLC(0, 180, 240),
                        0.0f, flinearcolor(), fvector2d(0, 0), true, true, false, flinearcolor());
                }
                else {
                    canvas->k2_drawtext(font, current, fvector2d{ element_pos.x + (size.x / 2), element_pos.y + (25.0f / 2) },
                        fvector2d(1.0f, 0.9f), RGBtoFLC(230, 230, 230),
                        0.0f, flinearcolor(), fvector2d(0, 0), true, true, false, flinearcolor());
                }

                element_pos.y += 25.0f;
                itemIndex++;
            }
            va_end(items);
        }

        // --- OPEN/CLOSE LOGIC (same as combobox) ---
        if (isHovered && input::is_mouse_clicked(0, elements_count, false))
            multi_combobox_enabled[elements_count] = !multi_combobox_enabled[elements_count];

        if (!isHovered && input::is_mouse_clicked(0, elements_count, false))
            multi_combobox_enabled[elements_count] = false;

        sameLine = false;
        last_element_pos = pos;
        last_element_size = size;
        if (first_element_pos.x == 0.0f)
            first_element_pos = pos;
    }

    // Helper function to get multi-combobox value
    bool GetMultiComboboxValue(int element_id, int index)
    {
        if (multi_combobox_values[element_id].size() > index)
            return multi_combobox_values[element_id][index];
        return false;
    }

    bool draw_color_picker(ucanvas* canvas, uobject* font, const wchar_t* label, flinearcolor& color, fvector2d pos, fvector2d mouse_pos, bool mouse_clicked) {
        const float hue_slider_width = 100.0f;
        const float hue_slider_height = 7.0f;
        const float sb_picker_size = 75.0f;
        const float alpha_slider_width = hue_slider_width;
        const float alpha_slider_height = 7.0f;
        const float preview_box_size = 15.0f;
        const float spacing = 5.0f;

        static bool hue_dragging = false;
        static bool sb_dragging = false;
        static bool alpha_dragging = false;

        static float hue = 0.0f;
        static float saturation = 1.0f;
        static float brightness = 1.0f;

        float thickness = 2.0f; // grosor del texto
        float width_scale = 1.0f; // escala de anchura
        float height_scale = 0.8f; // escala de altura
        float text_scale = 1.1f; // escala del tamaÃ±o de la fuente

        bool value_changed = false;

        for (int i = 0; i < hue_slider_width; i++) {
            float h = (float)i / hue_slider_width;
            flinearcolor color_at_hue = HSVtoRGB(h, 1.0f, 1.0f);
            draw_filled_rect(canvas, pos.x + i, pos.y, 1.0f, hue_slider_height, color_at_hue); // raya arriba
        }
        draw_rect(canvas, pos.x, pos.y, hue_slider_width, hue_slider_height, RGBtoFLC(5, 5, 5));

        if (mouse_clicked && mouse_pos.x >= pos.x && mouse_pos.x <= pos.x + hue_slider_width &&
            mouse_pos.y >= pos.y && mouse_pos.y <= pos.y + hue_slider_height) {
            hue_dragging = true;
        }
        if (hue_dragging) {
            if (mouse_clicked) {
                hue = (mouse_pos.x - pos.x) / hue_slider_width;
                hue = std::clamp(hue, 0.0f, 1.0f);
                value_changed = true;
            }
            else {
                hue_dragging = false;
            }
        }

        fvector2d sb_pos = { pos.x, pos.y + hue_slider_height + spacing };

        for (int y = 0; y < sb_picker_size; y++) {
            for (int x = 0; x < sb_picker_size; x++) {
                float s = (float)x / sb_picker_size;
                float b = 1.0f - (float)y / sb_picker_size;
                flinearcolor sb_color = HSVtoRGB(hue, s, b);
                draw_filled_rect(canvas, sb_pos.x + x, sb_pos.y + y, 1.0f, 1.0f, sb_color);
            }
        }
        draw_rect(canvas, sb_pos.x, sb_pos.y, sb_picker_size, sb_picker_size, RGBtoFLC(5, 5, 5));

        if (mouse_clicked && mouse_pos.x >= sb_pos.x && mouse_pos.x <= sb_pos.x + sb_picker_size &&
            mouse_pos.y >= sb_pos.y && mouse_pos.y <= sb_pos.y + sb_picker_size) {
            sb_dragging = true;
        }
        if (sb_dragging) {
            if (mouse_clicked) {
                saturation = (mouse_pos.x - sb_pos.x) / sb_picker_size;
                brightness = 1.0f - (mouse_pos.y - sb_pos.y) / sb_picker_size;
                saturation = std::clamp(saturation, 0.0f, 1.0f);
                brightness = std::clamp(brightness, 0.0f, 1.0f);
                value_changed = true;
            }
            else {
                sb_dragging = false;
            }
        }

        fvector2d alpha_pos = { pos.x, sb_pos.y + sb_picker_size + spacing };

        for (int i = 0; i < alpha_slider_width; i++) {
            float alpha = (float)i / alpha_slider_width;
            flinearcolor alpha_color = HSVtoRGB(hue, saturation, brightness);
            alpha_color.a = alpha;
            draw_filled_rect(canvas, alpha_pos.x + i, alpha_pos.y, 1.0f, alpha_slider_height, alpha_color);
        }
        draw_rect(canvas, alpha_pos.x, alpha_pos.y, alpha_slider_width, alpha_slider_height, RGBtoFLC(5, 5, 5));

        if (mouse_clicked && mouse_pos.x >= alpha_pos.x && mouse_pos.x <= alpha_pos.x + alpha_slider_width &&
            mouse_pos.y >= alpha_pos.y && mouse_pos.y <= alpha_pos.y + alpha_slider_height) {
            alpha_dragging = true;
        }
        if (alpha_dragging) {
            if (mouse_clicked) {
                color.a = (mouse_pos.x - alpha_pos.x) / alpha_slider_width;
                color.a = std::clamp(color.a, 0.0f, 1.0f);
                value_changed = true;
            }
            else {
                alpha_dragging = false;
            }
        }

        flinearcolor final_color = HSVtoRGB(hue, saturation, brightness);
        color.r = final_color.r;
        color.g = final_color.g;
        color.b = final_color.b;

        fvector2d preview_pos = { pos.x + hue_slider_width + spacing, pos.y };
        draw_filled_rect(canvas, preview_pos.x, preview_pos.y, preview_box_size, preview_box_size, { color.r, color.g, color.b, color.a });
        draw_rect(canvas, preview_pos.x, preview_pos.y, preview_box_size, preview_box_size, RGBtoFLC(5, 5, 5));

        return value_changed;
    }
    bool draw_color_picker1(ucanvas* canvas, uobject* font, const wchar_t* label, flinearcolor& color, fvector2d pos, fvector2d mouse_pos, bool mouse_clicked) {
        const float picker_width = 100.0f;
        const float slider_height = 8.0f;
        const float sb_square_size = 80.0f;
        const float spacing = 4.0f;

        static bool hue_dragging = false;
        static bool sb_dragging = false;
        static bool saturation_dragging = false;
        static bool brightness_dragging = false;
        static bool alpha_dragging = false;

        static float hue = 0.0f;
        static float saturation = 1.0f;
        static float brightness = 1.0f;

        bool value_changed = false;

        const float picker_height = sb_square_size + (slider_height * 4) + (5 * spacing);
        draw_filled_rect(canvas, pos.x - 5.0f, pos.y - 5.0f, picker_width + 10.0f, picker_height + 10.0f, { 0.08f, 0.08f, 0.08f, 1.0f });
        draw_rect(canvas, pos.x - 5.0f, pos.y - 5.0f, picker_width + 10.0f, picker_height + 10.0f, { 0.2f, 0.2f, 0.2f, 1.0f });

        fvector2d sb_square_pos = { pos.x, pos.y };
        for (int y = 0; y < sb_square_size; y++) {
            for (int x = 0; x < sb_square_size; x++) {
                float s = (float)x / sb_square_size;
                float b = 1.0f - (float)y / sb_square_size;
                flinearcolor sb_color = HSVtoRGB(hue, s, b);
                draw_filled_rect(canvas, sb_square_pos.x + x, sb_square_pos.y + y, 1.0f, 1.0f, sb_color);
            }
        }
        draw_rect(canvas, sb_square_pos.x, sb_square_pos.y, sb_square_size, sb_square_size, { 0.5f, 0.5f, 0.5f, 1.0f });

        if (mouse_clicked && mouse_pos.x >= sb_square_pos.x && mouse_pos.x <= sb_square_pos.x + sb_square_size &&
            mouse_pos.y >= sb_square_pos.y && mouse_pos.y <= sb_square_pos.y + sb_square_size) {
            sb_dragging = true;
        }
        if (sb_dragging) {
            if (mouse_clicked) {
                saturation = (mouse_pos.x - sb_square_pos.x) / sb_square_size;
                brightness = 1.0f - (mouse_pos.y - sb_square_pos.y) / sb_square_size;
                saturation = std::clamp(saturation, 0.0f, 1.0f);
                brightness = std::clamp(brightness, 0.0f, 1.0f);
                value_changed = true;
            }
            else {
                sb_dragging = false;
            }
        }

        fvector2d hue_pos = { pos.x, sb_square_pos.y + sb_square_size + spacing };
        for (int i = 0; i < picker_width; i++) {
            float h = (float)i / picker_width;
            flinearcolor hue_color = HSVtoRGB(h, 1.0f, 1.0f);
            draw_filled_rect(canvas, hue_pos.x + i, hue_pos.y, 1.0f, slider_height, hue_color);
        }
        draw_rect(canvas, hue_pos.x, hue_pos.y, picker_width, slider_height, { 0.5f, 0.5f, 0.5f, 1.0f });

        if (mouse_clicked && mouse_pos.x >= hue_pos.x && mouse_pos.x <= hue_pos.x + picker_width &&
            mouse_pos.y >= hue_pos.y && mouse_pos.y <= hue_pos.y + slider_height) {
            hue_dragging = true;
        }
        if (hue_dragging) {
            if (mouse_clicked) {
                hue = (mouse_pos.x - hue_pos.x) / picker_width;
                hue = std::clamp(hue, 0.0f, 1.0f);
                value_changed = true;
            }
            else {
                hue_dragging = false;
            }
        }

        fvector2d saturation_pos = { hue_pos.x, hue_pos.y + slider_height + spacing };
        for (int i = 0; i < picker_width; i++) {
            float s = (float)i / picker_width;
            flinearcolor saturation_color = HSVtoRGB(hue, s, brightness);
            draw_filled_rect(canvas, saturation_pos.x + i, saturation_pos.y, 1.0f, slider_height, saturation_color);
        }
        draw_rect(canvas, saturation_pos.x, saturation_pos.y, picker_width, slider_height, { 0.5f, 0.5f, 0.5f, 1.0f });

        if (mouse_clicked && mouse_pos.x >= saturation_pos.x && mouse_pos.x <= saturation_pos.x + picker_width &&
            mouse_pos.y >= saturation_pos.y && mouse_pos.y <= saturation_pos.y + slider_height) {
            saturation_dragging = true;
        }
        if (saturation_dragging) {
            if (mouse_clicked) {
                saturation = (mouse_pos.x - saturation_pos.x) / picker_width;
                saturation = std::clamp(saturation, 0.0f, 1.0f);
                value_changed = true;
            }
            else {
                saturation_dragging = false;
            }
        }

        fvector2d brightness_pos = { saturation_pos.x, saturation_pos.y + slider_height + spacing };
        for (int i = 0; i < picker_width; i++) {
            float b = (float)i / picker_width;
            flinearcolor brightness_color = HSVtoRGB(hue, saturation, b);
            draw_filled_rect(canvas, brightness_pos.x + i, brightness_pos.y, 1.0f, slider_height, brightness_color);
        }
        draw_rect(canvas, brightness_pos.x, brightness_pos.y, picker_width, slider_height, { 0.5f, 0.5f, 0.5f, 1.0f });

        if (mouse_clicked && mouse_pos.x >= brightness_pos.x && mouse_pos.x <= brightness_pos.x + picker_width &&
            mouse_pos.y >= brightness_pos.y && mouse_pos.y <= brightness_pos.y + slider_height) {
            brightness_dragging = true;
        }
        if (brightness_dragging) {
            if (mouse_clicked) {
                brightness = (mouse_pos.x - brightness_pos.x) / picker_width;
                brightness = std::clamp(brightness, 0.0f, 1.0f);
                value_changed = true;
            }
            else {
                brightness_dragging = false;
            }
        }

        fvector2d alpha_pos = { brightness_pos.x, brightness_pos.y + slider_height + spacing };
        for (int i = 0; i < picker_width; i++) {
            float alpha = (float)i / picker_width;
            flinearcolor alpha_color = HSVtoRGB(hue, saturation, brightness);
            alpha_color.a = alpha;
            draw_filled_rect(canvas, alpha_pos.x + i, alpha_pos.y, 1.0f, slider_height, alpha_color);
        }
        draw_rect(canvas, alpha_pos.x, alpha_pos.y, picker_width, slider_height, { 0.5f, 0.5f, 0.5f, 1.0f });

        if (mouse_clicked && mouse_pos.x >= alpha_pos.x && mouse_pos.x <= alpha_pos.x + picker_width &&
            mouse_pos.y >= alpha_pos.y && mouse_pos.y <= alpha_pos.y + slider_height) {
            alpha_dragging = true;
        }
        if (alpha_dragging) {
            if (mouse_clicked) {
                color.a = (mouse_pos.x - alpha_pos.x) / picker_width;
                color.a = std::clamp(color.a, 0.0f, 1.0f);
                value_changed = true;
            }
            else {
                alpha_dragging = false;
            }
        }

        flinearcolor final_color = HSVtoRGB(hue, saturation, brightness);
        color.r = final_color.r;
        color.g = final_color.g;
        color.b = final_color.b;

        return value_changed;
    }

    void draw_line(ucanvas* canvas, const fvector2d& start, const fvector2d& end, const flinearcolor& color) {
        if (!canvas) return;

        canvas->k2_drawline(
            fvector2d{ start.x, start.y },
            fvector2d{ end.x, end.y },
            1.0f,
            color
        );
    }

    void draw_glow_effect33(ucanvas* canvas, float x, float y, float width, float height, float glow_size, flinearcolor glow_color = { 0.04f, 0.04f, 0.04f, 1.0f }) {
        for (float i = glow_size; i > 0; --i) {
            float alpha = glow_color.a * (i / glow_size);
            flinearcolor fade_color = flinearcolor(glow_color.r, glow_color.g, glow_color.b, alpha);

            draw_filled_rect(canvas, x - i, y - i, width + (2 * i), height + (2 * i), fade_color);
        }
    }

    bool draw_color_picker_menu(ucanvas* canvas, uobject* font, const wchar_t* label, flinearcolor& color, fvector2d pos, fvector2d mouse_pos, bool mouse_clicked) {
        static bool picker_open = false;
        static fvector2d picker_pos = pos;
        const float box_width = 30.0f;
        const float box_height = 10.5f;
        const float outline_thickness = 1.0f;

        auto min = [](float a, float b) { return (a < b) ? a : b; };
        auto max = [](float a, float b) { return (a > b) ? a : b; };

        if (picker_open && mouse_clicked &&
            (mouse_pos.x < picker_pos.x - 500.0f || mouse_pos.x > picker_pos.x + box_width + 500.0f ||
                mouse_pos.y < picker_pos.y - 500.0f || mouse_pos.y > picker_pos.y + box_height + 500.0f)) {
            picker_open = false;
        }

        draw_glow_effect33(canvas, pos.x, pos.y, box_width, box_height, 2.0f, RGBtoFLC(6, 6, 6));
        draw_filled_rect(canvas, pos.x, pos.y, box_width, box_height, color);

        if (mouse_clicked &&
            mouse_pos.x >= pos.x && mouse_pos.x <= pos.x + box_width &&
            mouse_pos.y >= pos.y && mouse_pos.y <= pos.y + box_height) {
            picker_open = !picker_open;
            picker_pos = { pos.x, pos.y + box_height + 10.0f };
        }

        if (picker_open) {
            return draw_color_picker1(canvas, font, label, color, picker_pos, mouse_pos, mouse_clicked);
        }

        return false;
    }

    bool draw_color_picker_menu1(ucanvas* canvas, uobject* font, const wchar_t* label, flinearcolor& color, fvector2d pos, fvector2d mouse_pos, bool mouse_clicked) {
        static bool picker_open = false;
        static fvector2d picker_pos = pos;
        const float box_width = 30.0f;
        const float box_height = 10.5f;
        const float outline_thickness = 1.0f;

        auto min = [](float a, float b) { return (a < b) ? a : b; };
        auto max = [](float a, float b) { return (a > b) ? a : b; };

        if (picker_open && mouse_clicked &&
            (mouse_pos.x < picker_pos.x - 500.0f || mouse_pos.x > picker_pos.x + box_width + 500.0f ||
                mouse_pos.y < picker_pos.y - 500.0f || mouse_pos.y > picker_pos.y + box_height + 500.0f)) {
            picker_open = false;
        }

        draw_glow_effect33(canvas, pos.x, pos.y, box_width, box_height, 2.0f, RGBtoFLC(6, 6, 6));
        draw_filled_rect(canvas, pos.x, pos.y, box_width, box_height, color);

        if (mouse_clicked &&
            mouse_pos.x >= pos.x && mouse_pos.x <= pos.x + box_width &&
            mouse_pos.y >= pos.y && mouse_pos.y <= pos.y + box_height) {
            picker_open = !picker_open;
            picker_pos = { pos.x, pos.y + box_height + 10.0f };
        }

        if (picker_open) {
            return draw_color_picker1(canvas, font, label, color, picker_pos, mouse_pos, mouse_clicked);
        }

        return false;
    }

    // END
    void Text(const wchar_t* text, bool center = false, bool outline = false)
    {
        elements_count++;

        float size = 24;
        fvector2d padding = fvector2d{ 1,3 };
        fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
        if (sameLine)
        {
            pos.x = last_element_pos.x + last_element_size.x + padding.x;
            pos.y = last_element_pos.y;
        }
        if (pushY)
        {
            pos.y = pushYvalue;
            pushY = false;
            pushYvalue = 0.0f;
            offset_y = pos.y - menu_pos.y;
        }

        if (!sameLine)
            offset_y += size + padding.y;

        //Text
        fvector2d textPos = fvector2d{ pos.x + 5.0f, pos.y };
        if (center)
            TextCenter(text, textPos, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, outline);
        else
            TextLeft(text, textPos, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, outline);

        sameLine = false;
        last_element_pos = pos;
        //last_element_size = size;
        if (first_element_pos.x == 0.0f)
            first_element_pos = pos;
    }
    bool Button(const wchar_t* name, fvector2d size)
    {
        elements_count++;

        fvector2d padding = fvector2d{ 15, 6 };
        fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
        if (sameLine)
        {
            pos.x = last_element_pos.x + last_element_size.x + padding.x;
            pos.y = last_element_pos.y;
        }
        if (pushY)
        {
            pos.y = pushYvalue;
            pushY = false;
            pushYvalue = 0.0f;
            offset_y = pos.y - menu_pos.y;
        }
        bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, size);

        //Bg
        if (isHovered)
        {
            drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, Colors::Button_Hovered);
            hover_element = true;
        }
        else
        {
            drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, Colors::Button_Idle);
        }

        if (!sameLine)
            offset_y += size.y + padding.y;

        //Text
        fvector2d textPos = fvector2d{ pos.x + size.x / 2, pos.y + size.y / 2 };
        //if (!TextOverlapedFromActiveElement(textPos))
        TextCenter(name, textPos, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);


        sameLine = false;
        last_element_pos = pos;
        last_element_size = size;
        if (first_element_pos.x == 0.0f)
            first_element_pos = pos;

        if (isHovered && input::is_mouse_clicked(0, elements_count, false))
            return true;

        return false;
    }
    void SliderInt(uobject* font, const wchar_t* name, int* value, int min, int max)
    {
        elements_count++;
        fvector2d size = fvector2d{ 335, 22.5 };
        fvector2d slider_size = fvector2d{ 335, 12.5 };
        fvector2d adjust_zone = fvector2d{ 0, 20 };
        fvector2d padding = fvector2d{ 10, 5 };
        fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };

        if (sameLine)
        {
            pos.x = last_element_pos.x + last_element_size.x + padding.x;
            pos.y = last_element_pos.y;
        }
        if (pushY)
        {
            pos.y = pushYvalue;
            pushY = false;
            pushYvalue = 0.0f;
            offset_y = pos.y - menu_pos.y;
        }

        bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y + slider_size.y + padding.y - adjust_zone.y }, fvector2d{ slider_size.x, slider_size.y + adjust_zone.y * 1.5f });

        if (!sameLine)
            offset_y += size.y + padding.y;

        if (isHovered || current_element == elements_count)
        {
            if (input::is_mouse_clicked(0, elements_count, true))
            {
                current_element = elements_count;

                fvector2d cursorPos = CursorPos();
                int newVal = ((cursorPos.x - pos.x) * ((max - min) / slider_size.x)) + min;
                *value = std::clamp(newVal, min, max);
            }

            drawFilledRect(fvector2d{ pos.x, pos.y + slider_size.y + padding.y }, slider_size.x, slider_size.y, RGBtoFLC(10, 10, 10));
            drawFilledRect(fvector2d{ pos.x + 1, pos.y + slider_size.y + padding.y + 1 }, slider_size.x - 2, slider_size.y - 2, RGBtoFLC(6, 6, 6));
            hover_element = true;
        }
        else
        {
            drawFilledRect(fvector2d{ pos.x, pos.y + slider_size.y + padding.y }, slider_size.x, slider_size.y, RGBtoFLC(10, 10, 10));
            drawFilledRect(fvector2d{ pos.x + 1, pos.y + slider_size.y + padding.y + 1 }, slider_size.x - 2, slider_size.y - 2, RGBtoFLC(5, 5, 5));
        }

        fvector2d textPos = fvector2d{ pos.x, pos.y - 2.0f };
        canvas->k2_drawtext(font, name, textPos, fvector2d(0.98, 0.98), RGBtoFLC(255, 255, 255), 0.0f, Colors::Text_Shadow, fvector2d(0, 0), false, false, true, Colors::Text_Outline);

        float oneP = slider_size.x / (float)(max - min);
        drawFilledRect(fvector2d{ pos.x + 1, pos.y + slider_size.y + padding.y + 1 }, oneP * (*value - min) - 2, slider_size.y - 2, RGBtoFLC(0, 145, 255));
        drawFilledRect(fvector2d{ pos.x + oneP * (*value - min), pos.y + slider_size.y + padding.y + 1 - 3 }, 17, 18, RGBtoFLC(7, 7, 7));

        char buffer[32];
        sprintf_s(buffer, "%d", *value);
        canvas->k2_drawtext(font, s2wc(buffer), fvector2d(pos.x + slider_size.x - 8.0f, pos.y - 2.0f), fvector2d(0.98, 0.98), RGBtoFLC(255, 255, 255), 0.0f, Colors::Text_Shadow, fvector2d(0, 0), true, false, true, Colors::Text_Outline);

        sameLine = false;
        last_element_pos = pos;
        last_element_size = size;
        if (first_element_pos.x == 0.0f)
            first_element_pos = pos;
    }

    int active_picker = -1;
    flinearcolor saved_color;
    bool ColorPixel(fvector2d pos, fvector2d size, flinearcolor* original, flinearcolor color)
    {
        PostRenderer::drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, color);

        //Выбранный цвет
        if (original->r == color.r && original->g == color.g && original->b == color.b)
        {
            PostRenderer::Draw_Line(fvector2d{ pos.x, pos.y }, fvector2d{ pos.x + size.x - 1, pos.y }, 1.0f, flinearcolor{ 0.0f, 0.0f, 0.0f, 1.0f });
            PostRenderer::Draw_Line(fvector2d{ pos.x, pos.y + size.y - 1 }, fvector2d{ pos.x + size.x - 1, pos.y + size.y - 1 }, 1.0f, flinearcolor{ 0.0f, 0.0f, 0.0f, 1.0f });
            PostRenderer::Draw_Line(fvector2d{ pos.x, pos.y }, fvector2d{ pos.x, pos.y + size.y - 1 }, 1.0f, flinearcolor{ 0.0f, 0.0f, 0.0f, 1.0f });
            PostRenderer::Draw_Line(fvector2d{ pos.x + size.x - 1, pos.y }, fvector2d{ pos.x + size.x - 1, pos.y + size.y - 1 }, 1.0f, flinearcolor{ 0.0f, 0.0f, 0.0f, 1.0f });
        }

        //Смена цвета
        bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, size);
        if (isHovered)
        {
            if (input::is_mouse_clicked(0, elements_count, false))
                *original = color;
        }

        return true;
    }
    void ColorPicker(const wchar_t* name, flinearcolor* color)
    {
        elements_count++;

        float size = 25;
        float xsize = 5;
        fvector2d padding = fvector2d{ 15, 10 };
        fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
        if (sameLine)
        {
            pos.x = last_element_pos.x + last_element_size.x + padding.x;
            pos.y = last_element_pos.y;
        }
        if (pushY)
        {
            pos.y = pushYvalue;
            pushY = false;
            pushYvalue = 0.0f;
            offset_y = pos.y - menu_pos.y;
        }
        bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, fvector2d{ size, size });

        if (!sameLine)
            offset_y += size + padding.y;

        if (active_picker == elements_count)
        {
            hover_element = true;

            float sizePickerX = 250;
            float sizePickerY = 250;
            bool isHoveredPicker = MouseInZone(fvector2d{ pos.x, pos.y }, fvector2d{ sizePickerX, sizePickerY - 60 });

            //Background
            PostRenderer::drawFilledRect(fvector2d{ pos.x, pos.y }, sizePickerX, sizePickerY - 65, Colors::ColorPicker_Background);

            fvector2d pixelSize = fvector2d{ sizePickerX / 12, sizePickerY / 12 };

            //0
            {
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 174 / 255.f, 235 / 255.f, 253 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 136 / 255.f, 225 / 255.f, 251 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 108 / 255.f, 213 / 255.f, 250 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 89 / 255.f, 175 / 255.f, 213 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 76 / 255.f, 151 / 255.f, 177 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 60 / 255.f, 118 / 255.f, 140 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 43 / 255.f, 85 / 255.f, 100 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 32 / 255.f, 62 / 255.f, 74 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 255 / 255.f, 255 / 255.f, 255 / 255.f, 1.0f });
            }
            //1
            {
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 175 / 255.f, 205 / 255.f, 252 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 132 / 255.f, 179 / 255.f, 252 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 90 / 255.f, 152 / 255.f, 250 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 55 / 255.f, 120 / 255.f, 250 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 49 / 255.f, 105 / 255.f, 209 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 38 / 255.f, 83 / 255.f, 165 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 28 / 255.f, 61 / 255.f, 120 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 20 / 255.f, 43 / 255.f, 86 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 247 / 255.f, 247 / 255.f, 247 / 255.f, 1.0f });
            }
            //2
            {
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 153 / 255.f, 139 / 255.f, 250 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 101 / 255.f, 79 / 255.f, 249 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 64 / 255.f, 50 / 255.f, 230 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 54 / 255.f, 38 / 255.f, 175 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 39 / 255.f, 31 / 255.f, 144 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 32 / 255.f, 25 / 255.f, 116 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 21 / 255.f, 18 / 255.f, 82 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 16 / 255.f, 13 / 255.f, 61 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 228 / 255.f, 228 / 255.f, 228 / 255.f, 1.0f });
            }
            //3
            {
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 194 / 255.f, 144 / 255.f, 251 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 165 / 255.f, 87 / 255.f, 249 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 142 / 255.f, 57 / 255.f, 239 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 116 / 255.f, 45 / 255.f, 184 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 92 / 255.f, 37 / 255.f, 154 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 73 / 255.f, 29 / 255.f, 121 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 53 / 255.f, 21 / 255.f, 88 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 37 / 255.f, 15 / 255.f, 63 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 203 / 255.f, 203 / 255.f, 203 / 255.f, 1.0f });
            }
            //4
            {
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 224 / 255.f, 162 / 255.f, 197 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 210 / 255.f, 112 / 255.f, 166 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 199 / 255.f, 62 / 255.f, 135 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 159 / 255.f, 49 / 255.f, 105 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 132 / 255.f, 41 / 255.f, 89 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 104 / 255.f, 32 / 255.f, 71 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 75 / 255.f, 24 / 255.f, 51 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 54 / 255.f, 14 / 255.f, 36 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 175 / 255.f, 175 / 255.f, 175 / 255.f, 1.0f });
            }
            //5
            {
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 235 / 255.f, 175 / 255.f, 176 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 227 / 255.f, 133 / 255.f, 135 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 219 / 255.f, 87 / 255.f, 88 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 215 / 255.f, 50 / 255.f, 36 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 187 / 255.f, 25 / 255.f, 7 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 149 / 255.f, 20 / 255.f, 6 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 107 / 255.f, 14 / 255.f, 4 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 77 / 255.f, 9 / 255.f, 3 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 144 / 255.f, 144 / 255.f, 144 / 255.f, 1.0f });
            }
            //6
            {
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 241 / 255.f, 187 / 255.f, 171 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 234 / 255.f, 151 / 255.f, 126 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 229 / 255.f, 115 / 255.f, 76 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 227 / 255.f, 82 / 255.f, 24 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 190 / 255.f, 61 / 255.f, 15 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 150 / 255.f, 48 / 255.f, 12 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 107 / 255.f, 34 / 255.f, 8 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 79 / 255.f, 25 / 255.f, 6 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 113 / 255.f, 113 / 255.f, 113 / 255.f, 1.0f });
            }
            //7
            {
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 245 / 255.f, 207 / 255.f, 169 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 240 / 255.f, 183 / 255.f, 122 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 236 / 255.f, 159 / 255.f, 74 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 234 / 255.f, 146 / 255.f, 37 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 193 / 255.f, 111 / 255.f, 28 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 152 / 255.f, 89 / 255.f, 22 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 110 / 255.f, 64 / 255.f, 16 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 80 / 255.f, 47 / 255.f, 12 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 82 / 255.f, 82 / 255.f, 82 / 255.f, 1.0f });
            }
            //8
            {
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 247 / 255.f, 218 / 255.f, 170 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 244 / 255.f, 200 / 255.f, 124 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 241 / 255.f, 182 / 255.f, 77 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 239 / 255.f, 174 / 255.f, 44 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 196 / 255.f, 137 / 255.f, 34 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 154 / 255.f, 108 / 255.f, 27 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 111 / 255.f, 77 / 255.f, 19 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 80 / 255.f, 56 / 255.f, 14 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 54 / 255.f, 54 / 255.f, 54 / 255.f, 1.0f });
            }
            //9
            {
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 254 / 255.f, 243 / 255.f, 187 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 253 / 255.f, 237 / 255.f, 153 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 253 / 255.f, 231 / 255.f, 117 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 254 / 255.f, 232 / 255.f, 85 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 242 / 255.f, 212 / 255.f, 53 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 192 / 255.f, 169 / 255.f, 42 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 138 / 255.f, 120 / 255.f, 30 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 101 / 255.f, 87 / 255.f, 22 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 29 / 255.f, 29 / 255.f, 29 / 255.f, 1.0f });
            }
            //10
            {
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 247 / 255.f, 243 / 255.f, 185 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 243 / 255.f, 239 / 255.f, 148 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 239 / 255.f, 232 / 255.f, 111 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 235 / 255.f, 229 / 255.f, 76 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 208 / 255.f, 200 / 255.f, 55 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 164 / 255.f, 157 / 255.f, 43 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 118 / 255.f, 114 / 255.f, 31 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 86 / 255.f, 82 / 255.f, 21 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 9 / 255.f, 9 / 255.f, 9 / 255.f, 1.0f });
            }
            //11
            {
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 218 / 255.f, 232 / 255.f, 182 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 198 / 255.f, 221 / 255.f, 143 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 181 / 255.f, 210 / 255.f, 103 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 154 / 255.f, 186 / 255.f, 76 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 130 / 255.f, 155 / 255.f, 64 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 102 / 255.f, 121 / 255.f, 50 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 74 / 255.f, 88 / 255.f, 36 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 54 / 255.f, 64 / 255.f, 26 / 255.f, 1.0f });
                ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 0 / 255.f, 0 / 255.f, 0 / 255.f, 1.0f });
            }



            if (isHoveredPicker)
            {
                if (input::is_mouse_clicked(0, elements_count, false))
                {

                }
            }
            else
            {
                if (input::is_mouse_clicked(0, elements_count, false))
                {
                    active_picker = -1;
                    //hover_element = false;
                }
            }
        }
        else
        {
            //Bg
            if (isHovered)
            {
                drawFilledRect(fvector2d{ pos.x, pos.y }, size, size, Colors::Checkbox_Hovered);
                hover_element = true;
            }
            else
            {
                drawFilledRect(fvector2d{ pos.x, pos.y }, size, size, Colors::Checkbox_Idle);
            }

            //Color
            drawFilledRect(fvector2d{ pos.x + 4, pos.y + 4 }, size - 8, size - 8, *color);

            //Text
            fvector2d textPos = fvector2d{ pos.x + size + 5.0f, pos.y - xsize + 6.0f };
            TextLeft(name, textPos, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);

            if (isHovered && input::is_mouse_clicked(0, elements_count, false))
            {
                saved_color = *color;
                active_picker = elements_count;
            }
        }


        sameLine = false;
        last_element_pos = pos;
        //last_element_size = size;
        if (first_element_pos.x == 0.0f)
            first_element_pos = pos;
    }


    void Render(uobject* font)
    {
        for (int i = 0; i < 128; i++)
        {
            if (PostRenderer::drawlist[i].type != -1)
            {
                //Filled Rect
                if (PostRenderer::drawlist[i].type == 1)
                {
                    menu::drawFilledRect(PostRenderer::drawlist[i].pos, PostRenderer::drawlist[i].size.x, PostRenderer::drawlist[i].size.y, PostRenderer::drawlist[i].color);
                }
                //TextLeft
                else if (PostRenderer::drawlist[i].type == 2)
                {
                    canvas->k2_drawtext(font, (const wchar_t*)PostRenderer::drawlist[i].name, PostRenderer::drawlist[i].pos, fvector2d(0.98, 0.98), PostRenderer::drawlist[i].color, 0.0f, Colors::Text_Shadow, fvector2d(0, 0), false, false, PostRenderer::drawlist[i].outline, Colors::Text_Outline);
                }
                //TextCenter
                else if (PostRenderer::drawlist[i].type == 3)
                {
                    menu::TextCenter((const wchar_t*)PostRenderer::drawlist[i].name, PostRenderer::drawlist[i].pos, PostRenderer::drawlist[i].color, PostRenderer::drawlist[i].outline);
                }
                //Draw_Line
                else if (PostRenderer::drawlist[i].type == 4)
                {
                    Draw_Line(PostRenderer::drawlist[i].from, PostRenderer::drawlist[i].to, PostRenderer::drawlist[i].thickness, PostRenderer::drawlist[i].color);
                }

                PostRenderer::drawlist[i].type = -1;
            }
        }
    }
}

static int keybind = 0;
static int boxstyle = 0;
static bool test = false;
static bool test2 = false;
static float number = 0.0f;

namespace burat {

    float LineamountFov = 50.0f;
    static flinearcolor fovcolor = { 255.0f, 255.0f, 255.0f, 1.0f };
    fvector2d pos = { -10, -10 }; // Moved slightly more to top-left

    // Texture loading flags and pointers
    static bool textures_loaded = false;

    static void text_wrapper_ooo(ucanvas* canvas, uobject* font, fvector2d position, flinearcolor c, bool center, fstring text) noexcept
    {
        canvas->k2_drawtext(font, text, position, fvector2d(1.1f, 1.1f), c, 0.f, flinearcolor(), position, center, center, false, flinearcolor(0.f, 0.f, 0.f, 1.f));
    }

    void hk_draw_canvas(uobject* font, bool open_canvas, ucanvas* canvas) {
        if (!canvas || !open_canvas) return;

        /*static uint64_t last_texture_load_time = 0;
        static bool textures_loading_in_progress = false;

        uint64_t current_time12 = GetTickCount64();
        if ((!textures_loaded || (current_time12 - last_texture_load_time) > 2000) && !textures_loading_in_progress) {
            textures_loading_in_progress = true;

            if (!rage_icon) {
                tarray<uint8_t> rage_buffer = menu::create_buffer_from_data(RAGE_ICON_DATA, sizeof(RAGE_ICON_DATA));
                rage_icon = system::import_buffer_as_texture2d(world, rage_buffer);
            }

            if (!legit_icon) {
                tarray<uint8_t> legit_buffer = menu::create_buffer_from_data(LEGIT_ICON_DATA, sizeof(LEGIT_ICON_DATA));
                legit_icon = system::import_buffer_as_texture2d(world, legit_buffer);
            }

            if (!visuals_icon) {
                tarray<uint8_t> visuals_buffer = menu::create_buffer_from_data(VISUALS_ICON_DATA, sizeof(VISUALS_ICON_DATA));
                visuals_icon = system::import_buffer_as_texture2d(world, visuals_buffer);
            }

            if (!settings_icon) {
                tarray<uint8_t> settings_buffer = menu::create_buffer_from_data(SETTINGS_ICON_DATA, sizeof(SETTINGS_ICON_DATA));
                settings_icon = system::import_buffer_as_texture2d(world, settings_buffer);
            }

            if (!config_icon) {
                tarray<uint8_t> config_buffer = menu::create_buffer_from_data(CONFIG_ICON_DATA, sizeof(CONFIG_ICON_DATA));
                config_icon = system::import_buffer_as_texture2d(world, config_buffer);
            }

            if (!local_icon) {
                tarray<uint8_t> local_buffer = menu::create_buffer_from_data(LOCAL_ICON_DATA, sizeof(LOCAL_ICON_DATA));
                local_icon = system::import_buffer_as_texture2d(world, local_buffer);
            }

            textures_loaded = true;
            last_texture_load_time = current_time12;
            textures_loading_in_progress = false;
        }*/

        menu::SetupCanvas(canvas);
        input::handle();

        // sns our accent

       // flinearcolor accent_color = { 0.16f, 0.38f, 0.85f, 1.0f };

        // sysinfo accent

        flinearcolor accent_color = { 0.39f, 0.71f, 1.0f, 1.0f };


        flinearcolor bg_color = { 0.02f, 0.02f, 0.02f, 0.97f };
        flinearcolor dark_accent = { 0.04f, 0.04f, 0.04f, 1.0f };
        flinearcolor text_color = { 0.95f, 0.95f, 0.95f, 1.0f };
        flinearcolor highlight = { 0.39f, 0.71f, 1.0f, 1.0f };
        flinearcolor secondary = { 0.3f, 0.3f, 0.3f, 1.0f };

        static float menu_x = (GetSystemMetrics(SM_CXSCREEN) - 550) / 2.0f;
        static float menu_y = (GetSystemMetrics(SM_CYSCREEN) - 650) / 2.0f;
        static bool is_dragging = false;
        static fvector2d drag_offset = { 0,0 };

        float current_time = 0.0f;
        float pulse_effect = (sinf(current_time * 2.0f) * 0.5f + 0.5f) * 0.3f + 0.7f;

        static bool prev_mouse_clicked = false;
        POINT mouse_point;
        GetCursorPos(&mouse_point);
        ScreenToClient(GetActiveWindow(), &mouse_point);
        fvector2d mouse_pos = { (float)mouse_point.x, (float)mouse_point.y };
        bool mouse_clicked = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;

        if (mouse_clicked && !prev_mouse_clicked) {
            if (                mouse_pos.x >= menu_x && mouse_pos.x <= menu_x + 550 &&
                mouse_pos.y >= menu_y && mouse_pos.y <= menu_y + 45) {
                is_dragging = true;
                drag_offset = { mouse_pos.x - menu_x, mouse_pos.y - menu_y };
            }
        }

        if (is_dragging) {
            if (mouse_clicked) {
                menu_x = mouse_pos.x - drag_offset.x;
                menu_y = mouse_pos.y - drag_offset.y;
            }
            else {
                is_dragging = false;
            }
        }

        fvector2d pos = { menu_x, menu_y };

        if (menu::Window(canvas, font, L"VACSEN", &pos, fvector2d{ 550, 650 }, open_canvas)) {
            static int tab = 1;

            // === Vertical sidebar tabs (wide buttons) ===
            {
                const wchar_t* categories[] = { L"Aimbot", L"AntiAim", L"Outlines", L"Visuals", L"World", L"Misc", L"Self", L"Config" };
                const int cat_count = 8;
                float cat_btn_h = 38.0f;
                float cat_btn_w = 85.0f;
                float cat_start_y = pos.y + 46.0f + 6.0f;
                float cat_x = pos.x + 4.0f;

                for (int ci = 0; ci < cat_count; ci++) {
                    float btn_y = cat_start_y + ci * (cat_btn_h + 2.0f);
                    bool is_active = (tab == ci + 1);
                    bool is_hovered = menu::MouseInZone(fvector2d{ cat_x, btn_y }, fvector2d{ cat_btn_w, cat_btn_h });

                    if (is_active) {
                        menu::drawFilledRect(fvector2d{ cat_x, btn_y }, cat_btn_w, cat_btn_h, menu::RGBtoFLC(255, 255, 255));
                        canvas->k2_drawtext(font, categories[ci], fvector2d{ cat_x + cat_btn_w / 2, btn_y + cat_btn_h / 2 },
                            fvector2d(0.85, 0.8), menu::RGBtoFLC(0, 0, 0), 0.0f, menu::RGBtoFLC(0, 0, 0), fvector2d(0, 0), true, true, false, menu::RGBtoFLC(0, 0, 0));
                    }
                    else if (is_hovered) {
                        menu::drawFilledRect(fvector2d{ cat_x, btn_y }, cat_btn_w, cat_btn_h, menu::RGBtoFLC(20, 20, 20));
                        canvas->k2_drawtext(font, categories[ci], fvector2d{ cat_x + cat_btn_w / 2, btn_y + cat_btn_h / 2 },
                            fvector2d(0.85, 0.8), menu::RGBtoFLC(180, 180, 180), 0.0f, menu::RGBtoFLC(0, 0, 0), fvector2d(0, 0), true, true, false, menu::RGBtoFLC(0, 0, 0));
                    }
                    else {
                        menu::drawFilledRect(fvector2d{ cat_x, btn_y }, cat_btn_w, cat_btn_h, menu::RGBtoFLC(0, 0, 0));
                        canvas->k2_drawtext(font, categories[ci], fvector2d{ cat_x + cat_btn_w / 2, btn_y + cat_btn_h / 2 },
                            fvector2d(0.85, 0.8), menu::RGBtoFLC(60, 60, 60), 0.0f, menu::RGBtoFLC(0, 0, 0), fvector2d(0, 0), true, true, false, menu::RGBtoFLC(0, 0, 0));
                    }

                    if (is_hovered && mouse_clicked && !prev_mouse_clicked) {
                        tab = ci + 1;
                    }
                }

                // Vertical separator between sidebar and content
                float sep_x = cat_x + cat_btn_w + 2.0f;
                float sep_start_y = cat_start_y;
                float sep_end_y = cat_start_y + cat_count * (cat_btn_h + 2.0f);
                menu::drawFilledRect(fvector2d{ sep_x, sep_start_y }, 1, sep_end_y - sep_start_y, menu::RGBtoFLC(30, 30, 30));
            }

            prev_mouse_clicked = mouse_clicked;

                // Content area starts after sidebar
                menu::offset_x = 98;
                menu::offset_y = 46 + 1;
                if (tab == 1) {
                    float aimbot_section_height = 600 - (menu::offset_y + 10);
                    menu::SectionWrapper(canvas, font, L"AIMBOT", fvector2d(200, aimbot_section_height));
                    menu::offset_y -= 10;

                    menu::Checkbox(font, L"Enable Aim", &globals::aimbot::a1mbot);
                    menu::Checkbox(font, L"Show target fov", &globals::aimbot::draw_f0v);
                    menu::Checkbox(font, L"Recoil Control", &globals::aimbot::reco1l_contr0l);
                    menu::Checkbox(font, L"NoSpread ", &globals::aimbot::spread_comp);
                    menu::Checkbox(font, L"Automatic Fire", &globals::aimbot::autoshot);
                    menu::Checkbox(font, L"360 FOV", &globals::aimbot::enable_360_fov);
                    menu::Checkbox(font, L"No Spread Delay", &globals::aimbot::spreadempty_comp);
                    menu::Checkbox(font, L"Prediction", &globals::aimbot::pvc);                   
                    menu::Checkbox(font, L"Visibility Check", &globals::aimbot::v1sh_ch3ck);
                    //menu::Checkbox(font, L"Wall Penetrate", &globals::aimbot::wall_penetrate);
                    menu::offset_y += 2;
                    menu::Hotkey(font, "Aim key", fvector2d(63, 16.5), &globals::aimbot::a1m_k3y);

                    menu::offset_y += 5;

                    float advanced_section_height = 600 - (menu::offset_y + 10);
                    menu::SectionWrapper(canvas, font, L"CONFIGURATION", fvector2d(200, advanced_section_height));
                    menu::offset_y -= 10;

                    menu::SliderFloat(font, &globals::aimbot::a1m_sm00th, 1.0f, 100.0f, "smooth", "%.1f");
                    menu::offset_y += 20;

                    if (!globals::aimbot::enable_360_fov && globals::aimbot::a1m_f0v > 2000.0f) {
                        globals::aimbot::a1m_f0v = 2000.0f;
                    }

                    float show_fov = globals::aimbot::enable_360_fov ? 2000.0f : globals::aimbot::a1m_f0v;
                    menu::SliderFloat(font, &show_fov, 1.0f, 2000.0f, "fov", "%.0f");

                    if (!globals::aimbot::enable_360_fov) {
                        globals::aimbot::a1m_f0v = show_fov;
                    }

                    menu::offset_y += 25;

                    static bool silent_aim = false;
                    static bool clssts = false;
                    static bool target_team = false;
                    static bool target_knife = true;
                    static int hitbox_selection = 0;

                    menu::Checkbox(font, L"Silent Aim", &silent_aim);
                    menu::Checkbox(font, L"Closest Enemy Target", &clssts);
                    menu::Checkbox(font, L"Hitbox Selector", &target_team);

                    menu::Combobox(font, fvector2d(201, 24), &hitbox_selection, L"head", L"neck", L"chest", L"random", NULL);

                    menu::offset_x = 310;
                    menu::offset_y = 45 + 1;

                    float settings_height = 600 - (menu::offset_y + 10);
                    menu::SectionWrapper(canvas, font, L"TARGET SELECTION", fvector2d(200, settings_height));
                    menu::offset_y -= 10;

                    static int target_selection = 0;

                    int combobox_index2 = menu::elements_count + 1;
                    menu::Combobox(font, fvector2d(201, 24), &globals::aimbot::target_selection,
                        L"Distance closest",
                        L"Crosshair closest",
                        L"Combined (Distance + Crosshair)");

                    if (menu::checkbox_enabled[combobox_index2]) {
                        menu::offset_y += 40;
                    }
                    menu::Checkbox(font, L"Hitsound", &test2);
                    menu::Checkbox(font, L"Thru Smoke", &globals::misc::rpl);
                    menu::Checkbox(font, L"Spans Check", &test2);
                    menu::Checkbox(font, L"Target Selector", &test);
                    menu::offset_y += 18;
                    int combobox_index = menu::elements_count + 1;
                    menu::Combobox(font, fvector2d(201, 24), &globals::aimbot::auto_fire_mode,
                        L"Manual Mode",
                        L"Automatic Mode",
                        NULL);
                    menu::offset_y += 20;
                    menu::SliderFloat(font, &globals::aimbot::spread_comp_delay, 0.0f, 500.0f, "Default its 100", "%.1f");
                    menu::offset_y += 20;
                    menu::SliderFloat(font, &globals::aimbot::autoshoot_delay, 0.0f, 100.0f, "Default its 20", "%.1f");

                    menu::offset_y += 40;
                    float other_height = 600 - (menu::offset_y + 10);
                    menu::SectionWrapper(canvas, font, L"OTHER", fvector2d(200, other_height));
                    menu::offset_y -= 10;

                    menu::Checkbox(font, L"Hit Priority", &globals::misc::ht23);
                    menu::Checkbox(font, L"Automatic Scope", &globals::aimbot::auto_scope);
                    menu::Checkbox(font, L"Aim assist", &globals::aimbot::aim_assist);
                    menu::offset_y += 15;
                    menu::SliderFloat(font, &globals::aimbot::min_damage, 0.0f, 100.0f, "Minimum Damage", "%.0f");

                    //// YENİ: Wall Penetrate Min Damage Slider
                    //menu::offset_y += 15;
                    //menu::SliderFloat(font, &globals::aimbot::auto_wall_min_damage, 0.0f, 100.0f, "Wall Penetrate Min Damage", "%.0f");

                    menu::offset_y += 15;
                    menu::SliderFloat(font, &globals::aimbot::max_aim_distance, 0.0f, 100000.0f, "Max Aim Distance", "%.0f");
                }

                else if (tab == 2) {

                    menu::offset_y = 45 + 1;

                    menu::SectionWrapper(canvas, font, L"ANTI-AIM", fvector2d(200, 325));
                    menu::offset_y -= 10;
                    menu::Checkbox(font, L"Anti-Aim", &globals::misc::spinner);
                    if (globals::misc::spinner) {
                        globals::misc::aa = true;
                        menu::Checkbox(font, L"Anti-aim (server sided)", &globals::misc::aa);
                    }
                    else {
                        globals::misc::aa = false;
                    }

                    menu::Checkbox(font, L"Fast Duck", &globals::misc::fakeduck);
                    menu::Checkbox(font, L"Desync Move", &globals::misc::jitter_move);
                    menu::offset_y += 15;

                    float advanced_aa_height = 600 - (menu::offset_y + 10);
                    menu::SectionWrapper(canvas, font, L"ANTI-AIM SETTINGS", fvector2d(200, advanced_aa_height));
                    menu::offset_y -= 10;

                    menu::offset_y += 10;
                    menu::SliderFloat(font, &globals::misc::spinvalue, 0.0f, 140.0f, "Spin value", "%.1f");
                    menu::offset_y += 20;
                    menu::SliderFloat(font, &globals::misc::fake_lag_ticks, 0.0f, 64.0f, "Fake lag", "%.0f");
                    menu::offset_y += 20;
                    menu::SliderFloat(font, &globals::misc::jitter_range, 0.0f, 360.0f, "Jitter range", "%.1f°");
                    menu::offset_y += 20;
                    menu::SliderFloat(font, &globals::misc::desync_range, 0.0f, 360.0f, "Desync range", "%.1f°");
                    menu::offset_y += 20;

             
                    menu::Checkbox(font, L"Anti Aim Control", &globals::misc::pitch_enabled);
                    if (globals::misc::pitch_enabled) {
                        menu::offset_y += 10;
                        menu::SliderFloat(font, &globals::misc::pitch_value, -90.0f, 90.0f, "Pitch Value", "%.1f°");
                        menu::offset_y += 10;
                        menu::SliderFloat(font, &globals::misc::yaw_add, -180.0f, 180.0f, "Yaw Value", "%.1f°");
                        menu::offset_y += 10;
                    }
                    menu::offset_y += 20;
                    menu::Checkbox(font, L"Jitter on back", &globals::misc::jitter_on_back);
                    menu::Checkbox(font, L"Jitter Enabled", &globals::misc::jitter_enabled);
                    menu::offset_x = 310;
                    menu::offset_y = 45 + 1;

                    float aa_status_height = 600 - (menu::offset_y + 10);
                    menu::SectionWrapper(canvas, font, L"ANTI-AIM STATUS", fvector2d(200, aa_status_height));
                    menu::offset_y -= 10;


                    menu::offset_y += 10;
                    if (globals::misc::spinner) {
                        menu::TextCenter(L"ANTI-AIM ACTIVE", fvector2d(menu::menu_pos.x + menu::offset_x + 150, menu::menu_pos.y + menu::offset_y), hooks::menu::RGBtoFLC(0, 255, 0), false);
                    }
                    else {
                        menu::TextCenter(L"ANTI-AIM DISABLED", fvector2d(menu::menu_pos.x + menu::offset_x + 150, menu::menu_pos.y + menu::offset_y), hooks::menu::RGBtoFLC(255, 0, 0), false);
                    }
                    menu::offset_y += -3;

                    const wchar_t* mode_text = L"Mode: Normal";
                    switch (globals::misc::aa_mode) {
                    case 1: mode_text = L"Mode: Random"; break;
                    case 2: mode_text = L"Mode: Yaw"; break;
                    case 3: mode_text = L"Mode: 3-Way"; break;
                    case 4: mode_text = L"Mode: Backwards"; break;
                    }

                    menu::TextCenter(mode_text, fvector2d(menu::menu_pos.x + menu::offset_x + 150, menu::menu_pos.y + menu::offset_y), hooks::menu::RGBtoFLC(255, 255, 255), false);
                    menu::offset_y += -3;

                    menu::Checkbox(font, L"Wall Standing", &globals::misc::manual_aa);
                    menu::Checkbox(font, L"Freestanding", &globals::misc::freestanding);
                    menu::offset_y += -3;
                    menu::Checkbox(font, L"Center Jitter", &globals::misc::atomic_aa);
                    if (globals::misc::atomic_aa) {
                        menu::offset_y += -3;
                        menu::SliderFloat(font, &globals::misc::atomic_speed, 0.1f, 3.0f, "Center Speed", "%.1f");
                        menu::offset_y += 20;
                        int combobox_index = menu::elements_count + 1;
                        menu::Combobox(font, fvector2d(201, 24), &globals::misc::atomic_mode,
                            L"Normal", L"Inverter", L"Flicker", NULL);
                   
                  if (menu::checkbox_enabled[combobox_index]) {
                        menu::offset_y += 50;
                    }

                    menu::offset_y += -3;
                    menu::Checkbox(font, L"Prediction Resolver", &globals::misc::prediction_breaker);
                    if (globals::misc::prediction_breaker) {
                        menu::offset_y += 5;
                        menu::SliderFloat(font, &globals::misc::breaker_intensity, 0.5f, 5.0f, "Resolver Intensity", "%.1f");
                    }
                    }
                    menu::offset_y += 20;
                    menu::Combobox(font, fvector2d(201, 24), &globals::misc::aa_mode, L"Normal", L"Random", L"Backwards", L"3-Way", L"Lag-jitter", NULL);

                    static int last_aa_mode = -1;
                    if (last_aa_mode != globals::misc::aa_mode) {
                        if (globals::misc::aa_mode == 2) {
                            globals::misc::pitch_enabled = true;
                            globals::misc::pitch_value = -90.0f;
                            globals::misc::yaw_add = -180.0f;
                            globals::misc::jitter_enabled = true;
                            globals::misc::jitter_range = 25.0f;
                        }
                        else if (last_aa_mode == 2) {
                            globals::misc::pitch_enabled = false;
                            globals::misc::jitter_enabled = false;
                        }
                        last_aa_mode = globals::misc::aa_mode;
                    }

                    switch (globals::misc::aa_mode) {
                    case 1:
                        globals::misc::aa_spin = true;
                        globals::misc::aa_jitter = false;
                        globals::misc::aa_threeway = false;
                        break;
                    case 2:
                        globals::misc::aa_spin = false;
                        globals::misc::aa_jitter = true;
                        globals::misc::aa_threeway = false;
                        break;
                    case 3:
                        globals::misc::aa_spin = false;
                        globals::misc::aa_jitter = false;
                        globals::misc::aa_threeway = true;
                        break;
                    case 4:
                        globals::misc::aa_spin = false;
                        globals::misc::aa_jitter = false;
                        globals::misc::aa_threeway = true;
                        break;
                    case 5:
                        globals::misc::aa_spin = false;
                        globals::misc::aa_jitter = false;
                        globals::misc::aa_threeway = false;
                        globals::misc::aa_desync = true;
                        break;
                    default:
                        globals::misc::aa_spin = false;
                        globals::misc::aa_jitter = false;
                        globals::misc::aa_threeway = false;
                        globals::misc::aa_desync = false;
                        break;
                    }
                }
          else if (tab == 3) {

              float outline_section_height = 600 - (menu::offset_y + 10);
              menu::SectionWrapper(canvas, font, L"OUTLINE SETTINGS", fvector2d(200, outline_section_height));
              menu::offset_y -= 10;

              menu::Checkbox(font, L"Outline Enemy", &globals::visuals::outline_enabled);
              menu::Checkbox(font, L"Galaxy Self / Enemy", &globals::visuals::self_galaxy_enabled);
              menu::Checkbox(font, L"Dynamic Fresnel Outline", &globals::visuals::dynamic_fresnel_outline);
              menu::Checkbox(font, L"Crystal Outline Self / Hand", &globals::visuals::crystal_chams_enabled);
              menu::Checkbox(font, L"Galaxy Gun", &globals::visuals::galaxy_gun);
              menu::Checkbox(font, L"Self Wireframe", &globals::visuals::self_wireframe);
              menu::Checkbox(font, L"Wireframe hand", &globals::visuals::wireframe_hands);


              if (globals::visuals::outline_enabled) {
                  globals::visuals::usepresetedoutlines = true;
              }

              if (globals::visuals::self_galaxy_enabled) {
                  globals::visuals::outline_enabled = true;
                  globals::visuals::usepresetedoutlines = true;
              }

              int combobox_index = menu::elements_count + 1;

              if (globals::visuals::self_galaxy_enabled) {
                  menu::offset_y += 10;
                  menu::TextCenter(L"SELF GALAXY PRESET", fvector2d(menu::menu_pos.x + menu::offset_x + 150, menu::menu_pos.y + menu::offset_y), hooks::menu::RGBtoFLC(148, 0, 211), false);
                  menu::offset_y += 20;
                  menu::Combobox(font, fvector2d(201, 25), &globals::visuals::self_galaxy_preset,
                      L"Galaxy", L"Green Fresnel", L"Purple Fresnel", L"Blue Fresnel", NULL);
                  menu::offset_y += 10;
              }

              if (globals::visuals::crystal_chams_enabled) {
                  menu::offset_y += 10;
                  menu::TextCenter(L"CRYSTAL CHAMS PRESET", fvector2d(menu::menu_pos.x + menu::offset_x + 150, menu::menu_pos.y + menu::offset_y), hooks::menu::RGBtoFLC(0, 191, 255), false);
                  menu::offset_y += 20;
                  menu::Combobox(font, fvector2d(201, 25), &globals::visuals::crystal_chams_preset,
                      L"Option 1", L"Option 2", L"Option 3", L"Option 4", L"Option 5", NULL);
                  menu::offset_y += 10;
              }

              if (globals::visuals::dynamic_fresnel_outline) {
                  menu::offset_y += 10;
                  menu::TextCenter(L"DYNAMIC FRESNEL PRESET", fvector2d(menu::menu_pos.x + menu::offset_x + 150, menu::menu_pos.y + menu::offset_y), hooks::menu::RGBtoFLC(255, 165, 0), false);
                  menu::offset_y += 20;
                  menu::Combobox(font, fvector2d(201, 25), &globals::visuals::dynamic_fresnel_preset,
                      L"Dynamic Green", L"Dynamic Danger", L"Dynamic Purple Burn", L"Dynamic Yellow", L"Dynamic Red", L"Dynamic Burn", NULL);
                  menu::offset_y += 10;
              }

              if (menu::checkbox_enabled[combobox_index]) {
                  menu::offset_y += 120;
              }

              menu::offset_y += 27;
              float outline_hand_height = 600 - (menu::offset_y + 10);
              menu::SectionWrapper(canvas, font, L"OUTLINE HAND", fvector2d(200, outline_hand_height));
              menu::offset_y -= 10;

              menu::Checkbox(font, L"Outline Hand Chams", &globals::misc::hand_outline);
              menu::Checkbox(font, L"Hand Fresnel", &globals::misc::handchamsd2);
              menu::Checkbox(font, L"Rainbow Fresnel", &globals::visuals::rainbow_chams);

              menu::offset_y += 27;
              float visible_presets_height = 600 - (menu::offset_y + 10);
              menu::SectionWrapper(canvas, font, L"VISIBLE PRESETS", fvector2d(200, visible_presets_height));
              menu::offset_y -= 10;

              menu::Combobox(font, fvector2d(201, 25), &globals::visuals::visiblepreset,
                  L"Galaxy", L"Quantum Flux", L"Neon Mirage", L"Solar Flare",
                  L"Crystal Aura", L"Cyber Matrix", L"Arc Pulse", L"Magma Rush",
                  L"Bloom", L"Nova Blaze", L"Cosmic Dream", L"Stellar Burst", NULL);

              menu::offset_x = 310;
              menu::offset_y = 45 + 1;

              float intensity_settings_height = 600 - (menu::offset_y + 10);
              menu::SectionWrapper(canvas, font, L"INTENSITY SETTINGS", fvector2d(200, intensity_settings_height));
              menu::offset_y -= 10;

              menu::SliderFloat(font, &globals::visuals::outlineintensityvisibleoutline, 100.1f, 500.0f, "Intensity visible chams", "%.2f");
              menu::offset_y += 20;
              menu::SliderFloat(font, &globals::visuals::outlineintensityinvisbleoutline, 100.1f, 500.0f, "Intensity invisible chams", "%.2f");
              menu::offset_y += 20;
              menu::SliderFloat(font, &globals::visuals::intensityvisibleoutline, 10.1f, 30.0f, "Intensity Hand/Self/Weapon", "%.2f");
            
              menu::offset_y += 20;
              if (globals::visuals::outline_enabled || globals::visuals::self_galaxy_enabled || globals::visuals::dynamic_fresnel_outline || globals::visuals::crystal_chams_enabled) {
                  if (globals::visuals::self_galaxy_enabled) {
                      menu::TextCenter(L"GALAXY CHAMS ACTIVE", fvector2d(menu::menu_pos.x + menu::offset_x + 150, menu::menu_pos.y + menu::offset_y), hooks::menu::RGBtoFLC(148, 0, 211), false);
                  }
                  else if (globals::visuals::crystal_chams_enabled) {
                      menu::TextCenter(L"CRYSTAL CHAMS ACTIVE", fvector2d(menu::menu_pos.x + menu::offset_x + 150, menu::menu_pos.y + menu::offset_y), hooks::menu::RGBtoFLC(0, 191, 255), false);
                  }
                  else if (globals::visuals::dynamic_fresnel_outline) {
                      menu::TextCenter(L"DYNAMIC FRESNEL ACTIVE", fvector2d(menu::menu_pos.x + menu::offset_x + 150, menu::menu_pos.y + menu::offset_y), hooks::menu::RGBtoFLC(255, 165, 0), false);
                  }
                  else {
                      menu::TextCenter(L"Outline Active", fvector2d(menu::menu_pos.x + menu::offset_x + 150, menu::menu_pos.y + menu::offset_y), hooks::menu::RGBtoFLC(0, 255, 0), false);
                  }
              }
              else {
                  menu::TextCenter(L"Outline Disabled", fvector2d(menu::menu_pos.x + menu::offset_x + 150, menu::menu_pos.y + menu::offset_y), hooks::menu::RGBtoFLC(255, 0, 0), false);
              }

              menu::offset_y += 27;
              float invisible_presets_height = 600 - (menu::offset_y + 10);
              menu::SectionWrapper(canvas, font, L"INVISIBLE PRESETS", fvector2d(200, invisible_presets_height));
              menu::offset_y -= 10;

              menu::Combobox(font, fvector2d(201, 25), &globals::visuals::invisiblepreset,
                  L"Shadow Veil", L"Inferno Rush", L"Volt Surge", L"Glacial Peak",
                  L"Crimson Moon", L"Ghost Shade", L"Wraith Flame", L"Venom Chill",
                  L"Crimson Default", L"Volcanic Rage", L"Electric Surge", L"Arctic Blast",
                  L"Blood Eclipse", L"Dark Lightning", NULL);
                  }

            else if (tab == 4) {
                float players_section_height = 600 - (menu::offset_y + 10);
                menu::SectionWrapper(canvas, font, L"PLAYERS", fvector2d(200, players_section_height));
                menu::offset_y -= 10;

                menu::Checkbox(font, L"Ignore Dormants", &globals::visuals::dormant);
                menu::Checkbox(font, L"Visible Check", &globals::visuals::visiblecheck);
                menu::Checkbox(font, L"3d Box", &globals::visuals::box3d);
                menu::Checkbox(font, L"2d Box", &globals::visuals::box2d);
                menu::Checkbox(font, L"Distance", &globals::visuals::dstc);
                menu::Checkbox(font, L"Snaplines", &globals::visuals::snapl1ne);
                menu::Checkbox(font, L"Skeleton", &globals::visuals::sk3let0n);
                menu::Checkbox(font, L"Agent Icon", &globals::visuals::agenticon);
                menu::Checkbox(font, L"Health Bar", &globals::visuals::h3althbar);
                menu::Checkbox(font, L"Health Text", &globals::visuals::HealthText);
                menu::Checkbox(font, L"Agent Name", &globals::visuals::agent_name);
                menu::Checkbox(font, L"Weapon Esp", &globals::visuals::weaponesp);
                menu::Checkbox(font, L"Chinese Hat", &globals::visuals::chinese_hat);
                menu::Checkbox(font, L"Chinese Hat Self", &globals::visuals::chinese_hat_self);
                menu::Checkbox(font, L"Head Box", &globals::visuals::headb0x);
                menu::Checkbox(font, L"Offscreen ESP", &globals::visuals::offscreen_esp);
                if (globals::visuals::offscreen_esp) {
                    menu::offset_y += 5;
                    menu::SliderFloat(font, &globals::visuals::offscreen_radius, 50.0f, 500.0f, "Radius", "%.0f");
                    menu::offset_y += 5;
                    menu::SliderFloat(font, &globals::visuals::offscreen_size, 10.0f, 50.0f, "Arrow Size", "%.0f");
                }

                menu::offset_y += 27;

                float visuals_section_height = 600 - (menu::offset_y + 10);
                menu::SectionWrapper(canvas, font, L"VISUALS", fvector2d(200, visuals_section_height));
                menu::offset_y -= 10;

                menu::Checkbox(font, L"Normal Chams", &globals::visuals::chamsvsbd);

                if (globals::visuals::chamsvsbd) {
                    globals::visuals::visible_check_ch = true;
                    menu::Checkbox(font, L"Apply Self Refresh Press P", &globals::visuals::chams);
                }
                else {
                    globals::visuals::visible_check_ch = false;
                }

                menu::Checkbox(font, L"Bullet Tracers", &globals::visuals::bullet_tracers);
                menu::Checkbox(font, L"Wireframe weapon", &globals::visuals::wireframe_weapon);
                menu::Checkbox(font, L"Hand Chams", &globals::misc::handchams2);

                menu::offset_x = 310;
                menu::offset_y = 45 + 1;

               
                float player_info_height = 600 - (menu::offset_y + 10);
                menu::SectionWrapper(canvas, font, L"PLAYER INFO", fvector2d(200, player_info_height));
                menu::offset_y -= 10;

                // Yeni eklenen ESP özellikleri - SLIDERLARIN YERİNE BUNLAR GELDİ
                menu::Checkbox(font, L"Player Name", &globals::visuals::nmpl);
                menu::Checkbox(font, L"Platform Info", &globals::visuals::nmpl34);
                menu::Checkbox(font, L"Rank Info", &globals::visuals::nmpl2);
                menu::Checkbox(font, L"Rank Label", &globals::visuals::pclp);

                menu::offset_y += 27;

                // HAND CHAMS SETTINGS
                int combobox_index = menu::elements_count + 1;
                float hand_chams_height = 600 - (menu::offset_y + 10);
                menu::SectionWrapper(canvas, font, L"HAND CHAMS SETTINGS", fvector2d(200, hand_chams_height));
                menu::offset_y -= 10;
             

                fvector2d comboboxSize = { 286, 24 };
                menu::Combobox(font, comboboxSize, &globals::misc::handchams_material_index1,
                    L"Glow",
                    L"Ghost",
                    L"Red Devil",
                    L"Holographic",
                    L"Hell",
                    nullptr);

                menu::offset_y += 15;
                if (menu::checkbox_enabled[combobox_index]) {
                    menu::offset_y += 70;
                }

                menu::SliderFloat(font, &globals::misc::handchams_intensity, 0.1f, 10.0f, "glow intensity", "%.1f");
                menu::offset_y += 12;
                menu::SliderFloat(font, &globals::misc::handchams_color.r, 0.0f, 10.0f, "red", "%.2f");
                menu::offset_y += 12;
                menu::SliderFloat(font, &globals::misc::handchams_color.g, 0.0f, 10.0f, "green", "%.2f");
                menu::offset_y += 12;
                menu::SliderFloat(font, &globals::misc::handchams_color.b, 0.0f, 10.0f, "blue", "%.2f");
}

            else if (tab == 5) {
                static int last_preset_index = -1;

                menu::SectionWrapper(canvas, font, L"SKYBOX CONTROLS", fvector2d(200, 325));
                menu::offset_y -= 10;

                menu::Checkbox(font, L"Enable Skybox", &globals::misc::skybox);
                menu::Checkbox(font, L"Rainbow Skybox", &globals::misc::skyboxrgb);

                menu::offset_y += 47;

                float traps_height = 600 - (menu::offset_y + 10);
                menu::SectionWrapper(canvas, font, L"TRAPS", fvector2d(200, traps_height));
                menu::offset_y -= 10;

                menu::Checkbox(font, L"Spike ESP", &globals::misc::gdg);
                menu::Checkbox(font, L"Spike Timer", &globals::misc::spktimer);
                menu::Checkbox(font, L"World ESP", &globals::misc::cpp);
                menu::Checkbox(font, L"Cypher Traps", &globals::misc::world_esp);
                menu::Checkbox(font, L"Gadgets", &globals::misc::gadgets);

                menu::offset_x = 310;
                menu::offset_y = 45 + 1;

                float colors_height = 600 - (menu::offset_y + 10);
                menu::SectionWrapper(canvas, font, L"SKYBOX PRESETS", fvector2d(200, colors_height));
                menu::offset_y -= 10;

                int combobox_index = menu::elements_count + 1;

                fvector2d comboboxSize = { 286, 24 };
                menu::Combobox(font, comboboxSize, &globals::misc::skybox_preset_index,
                    L"Default", L"Night", L"Galaxy", L"Neon", nullptr);

                // PRESET SADECE DEĞİŞTİĞİNDE 1 KERE UYGULA
                if (last_preset_index != globals::misc::skybox_preset_index) {
                    switch (globals::misc::skybox_preset_index) {
                    case 0: // Default
                        globals::misc::Overall = { 1.0f, 1.0f, 1.0f };
                        globals::misc::Zenith = { 0.7f, 0.8f, 1.0f };
                        globals::misc::Horizon = { 0.9f, 0.9f, 0.9f };
                        globals::misc::Cloud = { 1.0f, 1.0f, 1.0f };
                        globals::misc::SkySunColor = { 1.0f, 1.0f, 0.9f };
                        globals::misc::CloudSpeed = 1.0f;
                        globals::misc::CloudOpacity = 1.0f;
                        globals::misc::StarsBrightness = 1.0f;
                        globals::misc::SkyNoisePower1 = 1.0f;
                        globals::misc::SkyNoisePower2 = 1.0f;
                        globals::misc::SkySunRadius = 1.0f;
                        globals::misc::SkySunBrightness = 1.0f;
                        globals::misc::SkySunHeight = 0.0f;
                        break;
                    case 1: // Night
                        globals::misc::Overall = { 0.1f, 0.1f, 0.2f };
                        globals::misc::Zenith = { 0.0f, 0.0f, 0.1f };
                        globals::misc::Horizon = { 0.1f, 0.1f, 0.2f };
                        globals::misc::Cloud = { 0.2f, 0.2f, 0.3f };
                        globals::misc::SkySunColor = { 0.5f, 0.5f, 0.6f };
                        globals::misc::CloudSpeed = 1.0f;
                        globals::misc::CloudOpacity = 1.0f;
                        globals::misc::StarsBrightness = 2.0f;
                        globals::misc::SkyNoisePower1 = 1.0f;
                        globals::misc::SkyNoisePower2 = 1.0f;
                        globals::misc::SkySunRadius = 0.5f;
                        globals::misc::SkySunBrightness = 0.5f;
                        globals::misc::SkySunHeight = -1.0f;
                        break;
                    case 2: // Galaxy
                        globals::misc::Overall = { 0.00f, 0.00f, 0.00f };
                        globals::misc::Zenith = { 0.00f, 0.00f, 0.00f };
                        globals::misc::Horizon = { 0.00f, 3.55f, 5.00f };
                        globals::misc::Cloud = { 5.00f, 5.00f, 5.00f };
                        globals::misc::SkySunColor = { 5.00f, 5.00f, 5.00f };
                        globals::misc::CloudSpeed = 10.00f;
                        globals::misc::CloudOpacity = 2.00f;
                        globals::misc::StarsBrightness = 5.00f;
                        globals::misc::SkyNoisePower1 = 10.00f;
                        globals::misc::SkyNoisePower2 = 10.00f;
                        globals::misc::SkySunRadius = 5.00f;
                        globals::misc::SkySunBrightness = 0.00f;
                        globals::misc::SkySunHeight = -5.00f;
                        break;
                    case 3: // Neon
                        globals::misc::Overall = { 5.00f, 5.00f, 4.28f };
                        globals::misc::Zenith = { 5.00f, 3.58f, 5.00f };
                        globals::misc::Horizon = { 5.00f, 0.10f, 5.00f };
                        globals::misc::Cloud = { 5.00f, 5.00f, 5.00f };
                        globals::misc::SkySunColor = { 5.00f, 5.00f, 5.00f };
                        globals::misc::CloudSpeed = 10.00f;
                        globals::misc::CloudOpacity = 2.00f;
                        globals::misc::StarsBrightness = 3.65f;
                        globals::misc::SkyNoisePower1 = 10.00f;
                        globals::misc::SkyNoisePower2 = 0.00f;
                        globals::misc::SkySunRadius = 4.51f;
                        globals::misc::SkySunBrightness = 0.00f;
                        globals::misc::SkySunHeight = 5.00f;
                        break;
                    }
                    last_preset_index = globals::misc::skybox_preset_index;
                }

                if (menu::checkbox_enabled[combobox_index]) {
                    menu::offset_y += 100;
                }

                menu::offset_y += 20;

                // CUSTOMIZE SLIDERLARI
                float effects_height = 600 - (menu::offset_y + 10);
                menu::SectionWrapper(canvas, font, L"SKYBOX CUSTOMIZE", fvector2d(200, effects_height));
                menu::offset_y -= 10;

                menu::SliderFloat(font, &globals::misc::CloudSpeed, 0.0f, 10.0f, "Cloud Speed", "%.2f");
                menu::offset_y += 12;
                menu::SliderFloat(font, &globals::misc::StarsBrightness, 0.0f, 5.0f, "Stars Brightness", "%.2f");
                menu::offset_y += 12;
                menu::SliderFloat(font, &globals::misc::CloudOpacity, 0.0f, 2.0f, "Cloud Opacity", "%.2f");
                menu::offset_y += 12;
                menu::SliderFloat(font, &globals::misc::SkySunRadius, 0.0f, 5.0f, "Sun Radius", "%.2f");
                menu::offset_y += 12;
                menu::SliderFloat(font, &globals::misc::SkySunBrightness, 0.0f, 10.0f, "Sun Brightness", "%.2f");
                menu::offset_y += 12;
                menu::SliderFloat(font, &globals::misc::SkyNoisePower1, 0.0f, 10.0f, "Noise Power 1", "%.2f");
                menu::offset_y += 12;
                menu::SliderFloat(font, &globals::misc::SkyNoisePower2, 0.0f, 10.0f, "Noise Power 2", "%.2f");
                }

                else if (tab == 6) {

                    float skins_section_height = 600 - (menu::offset_y + 10);
                    menu::SectionWrapper(canvas, font, L"SKINS", fvector2d(200, skins_section_height));
                    menu::offset_y -= 10;

                    menu::Checkbox(font, L"Apply custom skins", &globals::misc::playerchamsself);
                    menu::Checkbox(font, L"Unlock all", &globals::misc::sk1n_chang3r);
                    menu::Checkbox(font, L"Gun Chams", &globals::misc::customgun);
                    menu::Checkbox(font, L"Gun Materials", &globals::misc::rdy);
                    menu::offset_y += 47;


                    float view_model_height = 600 - (menu::offset_y + 10);
                    menu::SectionWrapper(canvas, font, L"MISC", fvector2d(200, view_model_height));
                    menu::offset_y -= 10;

                    menu::Checkbox(font, L"Advanced Resolver", &globals::aimbot::vsr);
                    menu::Checkbox(font, L"View model changer", &globals::misc::rmsdw);
                    menu::Checkbox(font, L"Big Gun", &globals::misc::BigGun3p);
                    menu::Checkbox(font, L"Self Resizer", &globals::misc::BigSelf);
                    menu::Checkbox(font, L"Finisher", &globals::misc::finisher);

                    if (globals::misc::finisher) {
                        menu::Checkbox(font, L"Only Last Kill", &globals::misc::onlylastkill);
                    }

                    menu::Checkbox(font, L"Kill Sounds", &globals::misc::killsound);


                    if (globals::misc::killsound) {
                        menu::offset_y += 5;


                        int combobox_index = menu::elements_count + 1;

                        menu::Combobox(font, fvector2d(201, 25), &globals::misc::killsound_selection,
                            L"neverlose hit",
                            L"unstoppable hit",
                            L"succes hit",
                            NULL);


                        if (menu::checkbox_enabled[combobox_index]) {
                            menu::offset_y += 80;
                        }

                        menu::offset_y += 5;
                    }

                    menu::Checkbox(font, L"Killsay", &globals::misc::killsays);
                    menu::Checkbox(font, L"Dynamic Hitsound", &globals::misc::hitsound);


                    menu::offset_y += 5;
                    menu::Checkbox(font, L"Chat Spammer F2", &globals::misc::chat_spammer);
                    menu::Text(L"Chat Message:", false, false);

                    fvector2d mouse_pos = menu::CursorPos();
                    bool mouse_clicked = GetAsyncKeyState(VK_LBUTTON) & 1;

                    fvector2d input_pos = fvector2d{
                        menu::menu_pos.x + 15,
                        menu::menu_pos.y + menu::offset_y - 5
                    };

                    menu::handle_input(canvas, font, input_pos, 240.0f, mouse_pos, mouse_clicked, globals::misc::chat_message);
                    menu::offset_y += 35;
                    menu::Checkbox(font, L"Kill Counter", &globals::misc::show_kill_counter);
             /*       menu::Checkbox(font, L"Watermark", &globals::misc::w4t4);*/
                /*    if (globals::misc::w4t4) {
                        menu::SliderFloat(font, &globals::misc::watermark_pos_x, 0.0f, 2000.0f, "Watermark X", "%.0f");
                        menu::SliderFloat(font, &globals::misc::watermark_pos_y, 0.0f, 1000.0f, "Watermark Y", "%.0f");
                        menu::SliderFloat(font, &globals::misc::watermark_scale, 0.5f, 3.0f, "Watermark Scale", "%.1f");
                    }*/
                    menu::offset_y += 20;


                    menu::offset_x = 310;
                    menu::offset_y = 45 + 1;


                    float exploit_height = 600 - (menu::offset_y + 10);
                    menu::SectionWrapper(canvas, font, L"EXPLOIT", fvector2d(200, exploit_height));
                    menu::offset_y -= 10;

                    menu::Checkbox(font, L"Remove flash", &globals::misc::antiflash);
                    menu::Checkbox(font, L"Bunny hop", &globals::misc::bunnyhop);
                    menu::Checkbox(font, L"Fast crouch", &globals::misc::fastcrouch);
                    menu::Checkbox(font, L"Free Cam", &globals::misc::freecam_enabled);
                    menu::Hotkey(font, "Freecam Key", fvector2d(9, 18), &globals::misc::freecam_key);
                    menu::SliderFloat(font, &globals::misc::freecam_speed, 100.0f, 5000.0f, "Freecam Speed", "%.0f");
                    menu::Checkbox(font, L"Skip Tutorial", &globals::misc::disconnect_server);
                    menu::Checkbox(font, L"Unload", &globals::misc::nld);


                    menu::offset_y += 47;
                    float aspect_ratio_height = 600 - (menu::offset_y + 10);
                    menu::SectionWrapper(canvas, font, L"FUTURE", fvector2d(200, aspect_ratio_height));
                    menu::offset_y -= 10;

                    menu::Checkbox(font, L"Custom Aspect Ratio", &globals::misc::aspect_ratio_enabled);
                    menu::Checkbox(font, L"Third Person (H)", &globals::misc::tperson);
                    menu::Checkbox(font, L"Fov Changer", &globals::misc::FovChangor);

                    if (globals::misc::FovChangor) {
                        menu::SliderFloat(font, &globals::misc::Fovchangerfloat, 70, 120, "fov", "%.0f°");
                    }

                    menu::SliderFloat(font, &globals::misc::aspect_ratio_value, 0.5f, 3.0f, "Aspect ratio", "%.2f");
                    menu::offset_y += 20;
                    menu::SliderFloat(font, &globals::misc::PlayerDistance, 10, 1000, "Thirdperson distance", "%.0f");
                    menu::SliderFloat(font, &globals::misc::arm_width, 0.1f, 15.0f, "Arm width", "%.0f");
                    menu::SliderFloat(font, &globals::misc::arm_height, 0.1f, 15.0f, "Arm height", "%.0f");
                    menu::SliderFloat(font, &globals::misc::arm_length, 0.1f, 15.0f, "Arm lenght", "%.0f");
                    //menu::SliderFloat(font, &globals::misc::knife_width, 0.1f, 15.0f, "Knife width", "%.0f");
                    //menu::SliderFloat(font, &globals::misc::knife_height, 0.1f, 15.0f, "Knife height", "%.0f");
                    //menu::SliderFloat(font, &globals::misc::knife_length, 0.1f, 15.0f, "Knife length", "%.0f");
                    //menu::SliderFloat(font, &globals::misc::knife_x, -10.0f, 10.0f, "Knife X position", "%.1f");
                    //menu::SliderFloat(font, &globals::misc::knife_y, -10.0f, 10.0f, "Knife Y position", "%.1f");
                    //menu::SliderFloat(font, &globals::misc::knife_z, -10.0f, 10.0f, "Knife Z position", "%.1f");
                }

                else if (tab == 7) {
                    float self_section_height = 600 - (menu::offset_y + 10);
                    menu::SectionWrapper(canvas, font, L"SELF CHAMS", fvector2d(200, self_section_height));
                    menu::offset_y -= 10;

                    menu::Checkbox(font, L"Self Chams", &globals::visuals::self_chams);
                    menu::Checkbox(font, L"Self Galaxy", &globals::visuals::self_galaxy_enabled);
                    menu::Checkbox(font, L"Wireframe", &globals::visuals::self_wireframe);
                    menu::Checkbox(font, L"Self Chinese Hat", &globals::visuals::chinese_hat_self);
                    menu::Checkbox(font, L"Hand Wireframe", &globals::visuals::wireframe_hands);
                    menu::Checkbox(font, L"Weapon Wireframe", &globals::visuals::wireframe_weapon);
                    menu::Checkbox(font, L"Mosca Wireframe", &globals::misc::mosca_wireframe);
                    menu::Checkbox(font, L"Viewmodel Changer", &globals::misc::ViewModelChanger);
                    menu::Checkbox(font, L"Custom Cs2 Skins", &globals::misc::custom_obj_enabled);

                    menu::offset_x = 310;
                    menu::offset_y = 45 + 1;

                    float self_info_height = 600 - (menu::offset_y + 10);
                    menu::SectionWrapper(canvas, font, L"SELF INFO", fvector2d(200, self_info_height));
                    menu::offset_y -= 10;

                    menu::Checkbox(font, L"Hand Chams", &globals::misc::handchams);
                    menu::Checkbox(font, L"Hand Outline", &globals::misc::hand_outline);
                    menu::Checkbox(font, L"Rainbow Chams", &globals::visuals::rainbow_chams);

                    menu::offset_y += 10;
                }

                else if (tab == 8) {
                    // Sol panel - Config bölümü
                    float config_section_height = 600 - (menu::offset_y + 10);
                    menu::SectionWrapper(canvas, font, L"CONFIG", fvector2d(200, config_section_height));
                    menu::offset_y -= 10;

                    static bool save_confirmation = false;
                    static bool load_confirmation = false;

                    fvector2d mouse_pos = menu::CursorPos();
                    bool mouse_clicked = GetAsyncKeyState(VK_LBUTTON) & 1;

                    fvector2d save_button_pos = fvector2d{ menu::menu_pos.x + menu::offset_x + 15, menu::menu_pos.y + menu::offset_y };
                    if (menu::draw_button(canvas, font,
                        save_confirmation ? L"Click again to confirm save" : L"Save Config",
                        save_button_pos, 201, 30,
                        menu::RGBtoFLC(1, 1, 1), menu::RGBtoFLC(2, 2, 2), menu::RGBtoFLC(80, 160, 255),
                        mouse_pos, mouse_clicked))
                    {
                        if (save_confirmation) {
                            save_config();
                            save_confirmation = false;
                        }
                        else {
                            save_confirmation = true;
                        }
                    }
                    menu::offset_y += 35;

                    fvector2d load_button_pos = fvector2d{ menu::menu_pos.x + menu::offset_x + 15, menu::menu_pos.y + menu::offset_y };
                    if (menu::draw_button(canvas, font,
                        load_confirmation ? L"Click again to confirm load" : L"Load Config",
                        load_button_pos, 201, 30,
                        menu::RGBtoFLC(1, 1, 1), menu::RGBtoFLC(2, 2, 2), menu::RGBtoFLC(80, 160, 255),
                        mouse_pos, mouse_clicked))
                    {
                        if (load_confirmation) {
                            load_config();
                            load_confirmation = false;
                        }
                        else {
                            load_confirmation = true;
                        }
                    }

                    menu::offset_y += 47;

                    // Sol panel - Menu Key bölümü
                    float ui_section_height = 600 - (menu::offset_y + 10);
                    menu::SectionWrapper(canvas, font, L"Menu Key", fvector2d(200, ui_section_height));
                    menu::offset_y -= 10;

                    menu::Hotkey(font, "Menu Key", fvector2d(63, 16.5), &globals::misc::kky);
                    menu::offset_y += 20;
                    menu::SliderFloat(font, &globals::misc::ui_scale, 0.25f, 2.5f, "ui scale", "%.1f");

                    // Sağ panel - Insta Lock bölümü
                    menu::offset_x = 310;
                    menu::offset_y = 45 + 1;

                    float insta_lock_height = 600 - (menu::offset_y + 10);
                    menu::SectionWrapper(canvas, font, L"INSTA LOCK", fvector2d(200, insta_lock_height));
                    menu::offset_y -= 10;

                    // Insta Lock checkbox - Encrypt'li
                    menu::Checkbox(font, Encrypt(L"INSTA LOCK").decrypt(), &globals::il::enable);

                    if (globals::il::enable) {
                        // Tüm agent'leri wchar_t ile encrypt'le
                        auto astra = Encrypt(L"Astra");
                        auto breach = Encrypt(L"Breach");
                        auto brimstone = Encrypt(L"Brimstone");
                        auto chamber = Encrypt(L"Chamber");
                        auto cypher = Encrypt(L"Cypher");
                        auto fade = Encrypt(L"Fade");
                        auto jett = Encrypt(L"Jett");
                        auto kayo = Encrypt(L"Kayo");
                        auto killjoy = Encrypt(L"Killjoy");
                        auto neon = Encrypt(L"Neon");
                        auto omen = Encrypt(L"Omen");
                        auto phoenix = Encrypt(L"Phoenix");
                        auto raze = Encrypt(L"Raze");
                        auto reyna = Encrypt(L"Reyna");
                        auto sage = Encrypt(L"Sage");
                        auto skye = Encrypt(L"Skye");
                        auto sova = Encrypt(L"Sova");
                        auto viper = Encrypt(L"Viper");
                        auto yoru = Encrypt(L"Yoru");
                        auto gekko = Encrypt(L"Gekko");

                        menu::offset_y += 10;

                        // Agent seçim combobox - decrypt'li
                        menu::TextCenter(Encrypt(L"SELECT AGENT").decrypt(), fvector2d(menu::menu_pos.x + menu::offset_x + 150, menu::menu_pos.y + menu::offset_y), hooks::menu::RGBtoFLC(255, 255, 255), false);
                        menu::offset_y += 20;

                        menu::Combobox(font, fvector2d(201, 25), &globals::il::lock_agent,
                            astra.decrypt(), breach.decrypt(), brimstone.decrypt(), chamber.decrypt(),
                            cypher.decrypt(), fade.decrypt(), jett.decrypt(), kayo.decrypt(),
                            killjoy.decrypt(), neon.decrypt(), omen.decrypt(), phoenix.decrypt(),
                            raze.decrypt(), reyna.decrypt(), sage.decrypt(), skye.decrypt(),
                            sova.decrypt(), viper.decrypt(), yoru.decrypt(), gekko.decrypt(), NULL);

                        menu::offset_y += 10;
                    }

                    // Combobox'tan sonra offset ayarı
                    menu::offset_y += 47;



                }
            }


            if (open_canvas) {
                menu::Draw_Cursor(true);
            }
        }
    }


    // OLD MENU ADD MISSING FEATURES FROM THERE IF NEEDED

    //static int keybind = 0;
    //static int boxstyle = 0;
    //static bool test = false;
    //static bool test2 = false;
    //static float number = 0.0f;

    //namespace burat {

    //    float LineamountFov = 50.0f;
    //    static flinearcolor fovcolor = { 1.0f, 1.0f, 1.0f, 1.0f };
    //    fvector2d pos = { -10, -10 };

    //    static void text_wrapper_ooo(ucanvas* canvas, uobject* font, fvector2d position, flinearcolor c, bool center, fstring text) noexcept
    //    {
    //        flinearcolor shadow_color = { 0.f, 0.f, 0.f, 0.6f };
    //        fvector2d shadow_offset = { 1.5f, 1.5f };


    //        canvas->k2_drawtext(font, text, { position.x + shadow_offset.x, position.y + shadow_offset.y },
    //            fvector2d(1.1f, 1.1f), shadow_color, 0.f, flinearcolor(), position, center, center, false, flinearcolor(0.f, 0.f, 0.f, 1.f));


    //        canvas->k2_drawtext(font, text, position, fvector2d(1.1f, 1.1f), c, 0.f, flinearcolor(),
    //            position, center, center, false, flinearcolor(0.f, 0.f, 0.f, 1.f));
    //    }

    //    void hk_draw_canvas(uobject* font, bool open_canvas, ucanvas* canvas) {
    //        if (!canvas || !open_canvas) return;

    //        menu::SetupCanvas(canvas);
    //        input::handle();


    //        
    //        flinearcolor accent_color = { 0.0f, 0.8f, 1.0f, 1.0f };
    //        flinearcolor accent_secondary = { 0.2f, 0.4f, 0.9f, 1.0f };
    //        flinearcolor bg_color = { 0.03f, 0.03f, 0.05f, 0.98f };
    //        flinearcolor dark_accent = { 0.08f, 0.08f, 0.12f, 1.0f };
    //        flinearcolor text_color = { 0.98f, 0.98f, 0.98f, 1.0f };
    //        flinearcolor text_secondary = { 0.7f, 0.7f, 0.75f, 1.0f };
    //        flinearcolor line_color = { 1.0f, 1.0f, 1.0f, 0.15f };
    //        flinearcolor hover_color = { 0.15f, 0.15f, 0.2f, 1.0f };
    //        flinearcolor active_color = { 0.1f, 0.6f, 1.0f, 0.3f };

    //        static float menu_x = (GetSystemMetrics(SM_CXSCREEN) - 960) / 2.0f;
    //        static float menu_y = (GetSystemMetrics(SM_CYSCREEN) - 650) / 2.0f;
    //        static bool is_dragging = false;
    //        static fvector2d drag_offset = { 0,0 };

    //        POINT mouse_point;
    //        GetCursorPos(&mouse_point);
    //        ScreenToClient(GetActiveWindow(), &mouse_point);
    //        fvector2d mouse_pos = { (float)mouse_point.x, (float)mouse_point.y };
    //        bool mouse_clicked = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
    //        static bool prev_mouse_clicked = false;

    //        if (mouse_clicked && !prev_mouse_clicked) {
    //            if (mouse_pos.x >= menu_x && mouse_pos.x <= menu_x + 960 &&
    //                mouse_pos.y >= menu_y && mouse_pos.y <= menu_y + 60) {
    //                is_dragging = true;
    //                drag_offset = { mouse_pos.x - menu_x, mouse_pos.y - menu_y };
    //            }
    //        }

    //        if (is_dragging) {
    //            if (mouse_clicked) {
    //                menu_x = mouse_pos.x - drag_offset.x;
    //                menu_y = mouse_pos.y - drag_offset.y;
    //            }
    //            else is_dragging = false;
    //        }
    //        prev_mouse_clicked = mouse_clicked;

    //        fvector2d pos = { menu_x, menu_y };
    //        float ui_scale = globals::misc::ui_scale;

    //        if (menu::Window(canvas, font, L"1.0.2", L"", &pos, fvector2d{ 960.0f * ui_scale, 800.0f * ui_scale }, open_canvas)) {
    //            float header_height = 55.0f * ui_scale;

    //            
    //            menu::drawGradientFilledRect({ pos.x, pos.y }, 960.0f * ui_scale, header_height,
    //                dark_accent, { 0.05f, 0.05f, 0.08f, 1.0f }, dark_accent, 15);

    //            
    //            hooks::draw_text(canvas, font, L"Sense", text_color, { pos.x + 480.0f * ui_scale, pos.y + 12.0f * ui_scale });

    //            
    //            canvas->k2_drawtext(font, L"", { pos.x + 480.0f * ui_scale, pos.y + 28.0f * ui_scale },
    //                { 0.65f * ui_scale, 0.65f * ui_scale },
    //                text_secondary, 0.f, {}, {}, true, false, false, {});


    //            static int tab = 0;
    //            const wchar_t* tab_names[] = { L"AIMBOT", L"VISUALS", L"MISC", L"ANTI-AIM" };
    //            int tab_count = 4;
    //            float tab_width = 135.0f * ui_scale, tab_height = 35.0f * ui_scale, tab_spacing = 15.0f * ui_scale;
    //            fvector2d tab_pos = { pos.x + ((960.0f * ui_scale) - (tab_width * tab_count + tab_spacing * (tab_count - 1))) / 2.0f,
    //                                   pos.y + header_height + 10.0f * ui_scale };

    //            for (int i = 0; i < tab_count; ++i) {
    //                flinearcolor current_color = (tab == i) ? active_color : dark_accent;
    //                flinearcolor border_color = (tab == i) ? accent_color : dark_accent;

    //                
    //                flinearcolor gradient_color = { current_color.r * 0.7f, current_color.g * 0.7f, current_color.b * 0.7f, current_color.a };
    //                menu::drawGradientFilledRect(tab_pos, tab_width, tab_height,
    //                    current_color, gradient_color, current_color, 8);

    //                
    //                menu::drawFilledRect({ tab_pos.x, tab_pos.y + tab_height - 1.5f }, tab_width, 1.5f * ui_scale, border_color);

    //                fvector2d text_pos = { tab_pos.x + tab_width / 2.0f, tab_pos.y + tab_height / 2.0f };
    //                flinearcolor tab_text_color = (tab == i) ? text_color : text_secondary;
    //                canvas->k2_drawtext(font, tab_names[i], text_pos, { 0.8f * ui_scale, 0.8f * ui_scale }, tab_text_color, 0.f, {}, {}, true, true, false, {});

    //                if (menu::MouseInZone(tab_pos, { tab_width, tab_height }) && input::is_mouse_clicked(0, 0, false))
    //                    tab = i;

    //                tab_pos.x += tab_width + tab_spacing;
    //            }

    //            
    //            float panel_left_x = pos.x + 50.0f * ui_scale;
    //            float panel_right_x = pos.x + 480.0f * ui_scale;
    //            float panel_top_y = pos.y + header_height + 55.0f * ui_scale;
    //            float step;


    //            if (tab == 0) {
    //                float rx = panel_left_x + 25.0f * ui_scale;
    //                float ry = panel_top_y + 15.0f * ui_scale;
    //                step = 32.0f * ui_scale; 

    //                menu::Checkbox(font, L"Enable Aim", &globals::aimbot::a1mbot, rx, ry); ry += step;
    //                menu::Checkbox(font, L"Show Target FOV", &globals::aimbot::draw_f0v, rx, ry); ry += step;
    //                menu::Checkbox(font, L"Recoil Control", &globals::aimbot::reco1l_contr0l, rx, ry); ry += step;
    //                menu::Checkbox(font, L"No Spread", &globals::aimbot::spread_comp, rx, ry); ry += step;
    //                menu::Checkbox(font, L"Auto Shoot", &globals::aimbot::autoshot, rx, ry); ry += step;
    //                menu::Checkbox(font, L"Visibility Check", &globals::aimbot::v1sh_ch3ck, rx, ry); ry += step;
    //                menu::Hotkey(font, "Aim Key", fvector2d(350.0f * ui_scale, 28.0f * ui_scale), &globals::aimbot::a1m_k3y, rx, ry); ry += step;

    //                float rx_right = panel_right_x + 25.0f * ui_scale;
    //                float ry_right = panel_top_y + 15.0f * ui_scale;
    //                menu::SliderFloat(font, L"Smoothness", &globals::aimbot::a1m_sm00th, 1.0f, 100.0f, rx_right, ry_right); ry_right += step;
    //                menu::SliderFloat(font, L"Aim Fov", &globals::aimbot::a1m_f0v, 1.0f, 100000.0f, rx_right, ry_right); ry_right += step;
    //            }


    //            else if (tab == 1) {
    //                float rx = panel_left_x + 25.0f * ui_scale;
    //                float ry = panel_top_y + 15.0f * ui_scale;
    //                step = 30.0f * ui_scale; 

    //              
    //                menu::Checkbox(font, L"Ignore Dormants", &globals::visuals::dormant, rx, ry); ry += step;
    //                menu::Checkbox(font, L"Visible Check", &globals::visuals::visiblecheck, rx, ry); ry += step;
    //                ry += 8.0f * ui_scale; 

    //                
    //                menu::Checkbox(font, L"3D Box", &globals::visuals::box3d, rx, ry); ry += step;
    //                menu::Checkbox(font, L"2D Box", &globals::visuals::box2d, rx, ry); ry += step;
    //                menu::Checkbox(font, L"Corner Box", &globals::visuals::cornerbox, rx, ry); ry += step;
    //                menu::Checkbox(font, L"Distance", &globals::visuals::dstc, rx, ry); ry += step;
    //                menu::Checkbox(font, L"Snaplines", &globals::visuals::snapl1ne, rx, ry); ry += step;
    //                menu::Checkbox(font, L"Skeleton", &globals::visuals::sk3let0n, rx, ry); ry += step;
    //                menu::Checkbox(font, L"Agent Icon", &globals::visuals::agenticon, rx, ry); ry += step;
    //                menu::Checkbox(font, L"Health Bar", &globals::visuals::h3althbar, rx, ry); ry += step;
    //                menu::Checkbox(font, L"Chinese Hat", &globals::visuals::chinese_hat, rx, ry); ry += step;
    //                ry += 8.0f * ui_scale; 
    //               /* menu::Checkbox(font, L"Chinese Hat Self", &globals::visuals::chinese_hat_self, rx, ry); ry += step;*/


    //                
    //                menu::Checkbox(font, L"Chams", &globals::visuals::chams, rx, ry); ry += step;
    //                menu::Checkbox(font, L"Rainbow Chams", &globals::visuals::rainbow_chams, rx, ry); ry += step;
    //               /* menu::Checkbox(font, L"Galaxy Enemy Chams", &globals::visuals::galaxy_enemy_chams, rx, ry); ry += step;
    //                ry += 8.0f * ui_scale; */
    //                menu::Checkbox(font, L"Visible/Invisible Outlines", &globals::visuals::chams_visible_invisible, rx, ry); ry += step;
    //         

    //                menu::Checkbox(font, L"Wireframe Hand", &globals::visuals::a_hands, rx, ry); ry += step;
    //                menu::Checkbox(font, L"Wireframe Weapon", &globals::visuals::wireframe_weapon, rx, ry); ry += step;
    //                menu::Checkbox(font, L"Glow ESP", &globals::visuals::glow_esp, rx, ry); ry += step;

    //                
    //                float rx_right = panel_right_x + 25.0f * ui_scale;
    //                float ry_right = panel_top_y + 15.0f * ui_scale;

    //                
    //                menu::SliderFloat(font, L"Fresnel Intensıty", &globals::visuals::chams_intensity, 0.1f, 5.0f, rx_right, ry_right); ry_right += step;
    //                menu::SliderFloat(font, L"Chams Red", &globals::visuals::chams_color.r, 0.0f, 1.0f, rx_right, ry_right); ry_right += step;
    //                menu::SliderFloat(font, L"Chams Green", &globals::visuals::chams_color.g, 0.0f, 1.0f, rx_right, ry_right); ry_right += step;
    //                menu::SliderFloat(font, L"Chams Blue", &globals::visuals::chams_color.b, 0.0f, 1.0f, rx_right, ry_right); ry_right += step;
    //                menu::SliderFloat(font, L"Chams Alpha", &globals::visuals::chams_color.a, 0.0f, 1.0f, rx_right, ry_right); ry_right += step;
    //                ry_right += 8.0f * ui_scale; 

    //                
    //                menu::SliderFloat(font, L"Glow Intensity", &globals::visuals::glow_intensity, 0.1f, 5.0f, rx_right, ry_right); ry_right += step;
    //                ry_right += 8.0f * ui_scale; 

    //                
    //               /* menu::Checkbox(font, L"Hand Chams", &globals::misc::handchams, rx_right, ry_right); ry_right += step;
    //                menu::Checkbox(font, L"Hand Glow", &globals::misc::handglow, rx_right, ry_right); ry_right += step;*/
    //                /*menu::Checkbox(font, L"Rainbow Hands", &globals::misc::handchams_rainbow, rx_right, ry_right); ry_right += step*/;
    //                /*menu::Checkbox(font, L"Galaxy Hand Chams", &globals::misc::galaxy_hand_chams, rx_right, ry_right); ry_right += step;*/
    //               /* menu::Checkbox(font, L"Galaxy v3", &globals::misc::ashen_crystal_v3, rx_right, ry_right); ry_right += step;
    //                menu::Checkbox(font, L"Galaxy v2", &globals::misc::ashen_crystal_v2, rx_right, ry_right); ry_right += step;
    //                ry_right += 8.0f * ui_scale; */

    //                
    //                menu::SliderFloat(font, L"Hand Color R", &globals::misc::handchams_color.r, 0.0f, 1.0f, rx_right, ry_right); ry_right += step;
    //                menu::SliderFloat(font, L"Hand Color G", &globals::misc::handchams_color.g, 0.0f, 1.0f, rx_right, ry_right); ry_right += step;
    //                menu::SliderFloat(font, L"Hand Color B", &globals::misc::handchams_color.b, 0.0f, 1.0f, rx_right, ry_right); ry_right += step;
    //                menu::SliderFloat(font, L"Hand Glow Intensity", &globals::misc::handchams_intensity, 1.0f, 10.0f, rx_right, ry_right); ry_right += step;
    //                menu::SliderFloat(font, L"Galaxy Glow Intensity", &globals::misc::ashen_intensity, 0.0f, 20.0f, rx_right, ry_right); ry_right += step;
    //                ry_right += 8.0f * ui_scale; 

    //                
    //                menu::Checkbox(font, L"Apply Custom skins", &globals::misc::playerchamsself, rx_right, ry_right);
    //                ry_right += step;

    //                fvector2d comboboxSize = { 150.0f * ui_scale, 25.0f * ui_scale };

    //                menu::Combobox(font, L"Self Custom Skins", comboboxSize, &globals::misc::chams_material_index, 680.0f,
    //                    L"Deadpool Material",
    //                    L"Molten Core",
    //                    L"Bulletstorm",
    //                    L"Crystal Nova",
    //                    L"Shadow Fang",
    //                    L"Neon Vortex",
    //                    L"Solar Flare",
    //                    L"Abyssal Wave",
    //                    L"Prism Break",
    //                    L"Luminous Rift",
    //                    L"Phantom Eclipse",
    //                    nullptr);

    //                menu::Combobox(font, L"Enemy Custom Skins", comboboxSize, &globals::misc::enemy_chams_material_index, 740.0f,
    //                    L"Deadpool Material",
    //                    L"Molten Core",
    //                    L"Bulletstorm",
    //                    L"Crystal Nova",
    //                    L"Shadow Fang",
    //                    L"Neon Vortex",
    //                    L"Solar Flare",
    //                    L"Abyssal Wave",
    //                    L"Prism Break",
    //                    L"Luminous Rift",
    //                    L"Phantom Eclipse",
    //                    nullptr);

    //                }

    //            else if (tab == 2) {
    //                float rx = panel_left_x + 25.0f * ui_scale;
    //                float ry = panel_top_y + 15.0f * ui_scale;
    //                step = 30.0f * ui_scale; 
    //                
    //                menu::Checkbox(font, L"Custom Aspect Ratio", &globals::misc::aspect_ratio_enabled, rx, ry); ry += step;
    //                menu::Checkbox(font, L"Third Person", &globals::misc::tperson, rx, ry); ry += step;
    //                menu::Checkbox(font, L"FOV Changer", &globals::misc::FovChangor, rx, ry); ry += step;
    //                ry += 8.0f * ui_scale; 
    //                menu::Checkbox(font, L"Skybox Changer", &globals::misc::skybox_changer, rx, ry); ry += step;


    //                
    //                menu::Checkbox(font, L"Skip Tutorial", &globals::misc::disconnect_server, rx, ry); ry += step;
    //                /*menu::Checkbox(font, L"KillSay", &globals::misc::kill_say, rx, ry); ry += step;*/
    //                menu::Checkbox(font, L"Unlock All", &globals::misc::sk1n_chang3r, rx, ry); ry += step;
    //                ry += 8.0f * ui_scale; 

    //                
    //                menu::Checkbox(font, L"View Model Changer", &globals::misc::rmsdw, rx, ry); ry += step;
    //                menu::Checkbox(font, L"Custom Gun", &globals::misc::customgun, rx, ry); ry += step;
    //                menu::Checkbox(font, L"Bunny Hop", &globals::misc::bunnyhop, rx, ry); ry += step;
    //                menu::Checkbox(font, L"Fast Crouch", &globals::misc::fastcrouch, rx, ry); ry += step;
    //                ry += 8.0f * ui_scale; 
    //                menu::Checkbox(font, L"Anti Flash", &globals::misc::antiflash, rx, ry); ry += step;
    //                ry += 8.0f * ui_scale;
    //                menu::Checkbox(font, L"Big Gun", &globals::misc::BigGun3p, rx, ry); ry += step;
    //                ry += 8.0f * ui_scale;
    //                menu::Checkbox(font, L"Big Self", &globals::misc::BigSelf, rx, ry); ry += step;
    //                ry += 8.0f * ui_scale;



    //              
    //                menu::SliderFloat(font, L"UI Scale", &globals::misc::ui_scale, 0.5f, 1.5f, rx, ry); ry += step;

    //                
    //                float rx_right = panel_right_x + 25.0f * ui_scale;
    //                float ry_right = panel_top_y + 15.0f * ui_scale;

    //                
    //                menu::SliderFloat(font, L"Aspect Ratio Value", &globals::misc::aspect_ratio_value, 0.5f, 3.0f, rx_right, ry_right); ry_right += step;
    //                menu::SliderFloat(font, L"Third Person Distance", &globals::misc::PlayerDistance, 10.0f, 1000.0f, rx_right, ry_right); ry_right += step;
    //                menu::SliderFloat(font, L"FOV Value", &globals::misc::Fovchangerfloat, 70.0f, 120.0f, rx_right, ry_right); ry_right += step;
    //                ry_right += 8.0f * ui_scale; 
    //                menu::SliderFloat(font, L"Sky Red", &globals::misc::sky_overall.r, 0.0f, 1.0f, rx_right, ry_right); ry_right += step;
    //                menu::SliderFloat(font, L"Sky Green", &globals::misc::sky_overall.g, 0.0f, 1.0f, rx_right, ry_right); ry_right += step;
    //                menu::SliderFloat(font, L"Sky Blue", &globals::misc::sky_overall.b, 0.0f, 1.0f, rx_right, ry_right); ry_right += step;

    //                
    //                menu::SliderFloat(font, L"Wide Arm Width", &globals::misc::arm_width, 0.1f, 15.0f, rx_right, ry_right); ry_right += step;
    //                menu::SliderFloat(font, L"Wide Arm Height", &globals::misc::arm_height, 0.1f, 15.0f, rx_right, ry_right); ry_right += step;
    //                menu::SliderFloat(font, L"Wide Arm Length", &globals::misc::arm_length, 0.1f, 15.0f, rx_right, ry_right); ry_right += step;
    //            }


    //            else if (tab == 3) {
    //                float rx = panel_left_x + 25.0f * ui_scale;
    //                float ry = panel_top_y + 15.0f * ui_scale;
    //                step = 30.0f * ui_scale; // Reduced spacing

    //                // === SOL PANEL: ANTI-AIM AYARLARI ===
    //                // Ana Ayarlar
    //                menu::Checkbox(font, L"Enable Anti-Aim", &globals::misc::spinner, rx, ry); ry += step;
    //                menu::Checkbox(font, L"Anti-Aim (Server Sided)", &globals::misc::aa, rx, ry); ry += step;
    //                ry += 8.0f * ui_scale; 

    //                
    //                fvector2d combo_size = { 180.0f * ui_scale, 22.0f * ui_scale };
    //                menu::Combobox(font, L"AA Mode", combo_size, &globals::misc::aa_mode, ry + 8.0f * ui_scale,
    //                    L"Normal", L"Random", L"Yaw", L"3-Way", L"Backwards", nullptr);
    //                ry += step + 8.0f * ui_scale;

    //                // === SAĞ PANEL: DEĞER AYARLARI ===
    //                float rx_right = panel_right_x + 25.0f * ui_scale;
    //                float ry_right = panel_top_y + 15.0f * ui_scale;

    //                // Genel Değerler
    //                menu::SliderFloat(font, L"Spin Value", &globals::misc::spinvalue, 0.0f, 140.0f, rx_right, ry_right); ry_right += step;
    //                menu::SliderFloat(font, L"Fake Lag Ticks", &globals::misc::fake_lag_ticks, 0.0f, 64.0f, rx_right, ry_right); ry_right += step;
    //                ry_right += 8.0f * ui_scale; // Reduced spacing

    //                // Mode'a özel ayarlar
    //                if (globals::misc::aa_mode == 2) {
    //                    menu::SliderFloat(font, L"Jitter Range", &globals::misc::jitter_range, 0.0f, 360.0f, rx_right, ry_right); ry_right += step;
    //                }

    //                if (globals::misc::aa_mode == 4) {
    //                    menu::SliderFloat(font, L"Desync Range", &globals::misc::desync_range, 0.0f, 360.0f, rx_right, ry_right); ry_right += step;
    //                }

    //                // --- AA Mode'a göre flagleri eşle ---
    //                switch (globals::misc::aa_mode) {
    //                case 1: // Normal
    //                    globals::misc::aa_spin = true;
    //                    globals::misc::aa_jitter = false;
    //                    globals::misc::aa_threeway = false;
    //                    break;
    //                case 2: // Random
    //                    globals::misc::aa_spin = false;
    //                    globals::misc::aa_jitter = true;
    //                    globals::misc::aa_threeway = false;
    //                    break;
    //                case 3: // Yaw
    //                    globals::misc::aa_spin = false;
    //                    globals::misc::aa_jitter = false;
    //                    globals::misc::aa_threeway = true;
    //                    break;
    //                case 4: // 3-Way
    //                    globals::misc::aa_spin = false;
    //                    globals::misc::aa_jitter = false;
    //                    globals::misc::aa_threeway = true;
    //                    break;
    //                case 5: // Backwards
    //                    globals::misc::aa_spin = false;
    //                    globals::misc::aa_jitter = false;
    //                    globals::misc::aa_threeway = false;
    //                    globals::misc::aa_desync = true;
    //                    break;
    //                default:
    //                    globals::misc::aa_spin = false;
    //                    globals::misc::aa_jitter = false;
    //                    globals::misc::aa_threeway = false;
    //                    globals::misc::aa_desync = false;
    //                    break;
    //                }
    //            }


    //            menu::Render(font);
    //        }



    //    }
    //}

    flinearcolor convert_to_flinearcolor(int r, int g, int b, int a) {
        return flinearcolor(
            (float)r / 255.0f,
            (float)g / 255.0f,
            (float)b / 255.0f,
            (float)a / 255.0f
        );
    }


    /*void DrawAdaptiveBoundingBox(ucanvas* canvas, aplayercontroller* my_controller, uskeletalmeshcomponent* mesh, flinearcolor color)
    {
        if (!canvas || !my_controller || !mesh) return;

        fvector vHeadBone = mesh->get_bone_location(8);
        fvector vBaseBone = mesh->get_bone_location(0);

        if (!vHeadBone.is_valid() || !vBaseBone.is_valid()) return;

        fvector2d bottom1, bottom2, bottom3, bottom4;
        fvector2d top1, top2, top3, top4;

        bool valid_projection =
            my_controller->project_world_location_to_screen(fvector(vBaseBone.x + 53, vBaseBone.y - 55, vBaseBone.z), bottom1, 0) && bottom1.is_valid() &&
            my_controller->project_world_location_to_screen(fvector(vBaseBone.x - 53, vBaseBone.y - 55, vBaseBone.z), bottom2, 0) && bottom2.is_valid() &&
            my_controller->project_world_location_to_screen(fvector(vBaseBone.x - 53, vBaseBone.y + 55, vBaseBone.z), bottom3, 0) && bottom3.is_valid() &&
            my_controller->project_world_location_to_screen(fvector(vBaseBone.x + 53, vBaseBone.y + 55, vBaseBone.z), bottom4, 0) && bottom4.is_valid() &&
            my_controller->project_world_location_to_screen(fvector(vHeadBone.x + 53, vHeadBone.y - 55, vHeadBone.z + 26), top1, 0) && top1.is_valid() &&
            my_controller->project_world_location_to_screen(fvector(vHeadBone.x - 53, vHeadBone.y - 55, vHeadBone.z + 26), top2, 0) && top2.is_valid() &&
            my_controller->project_world_location_to_screen(fvector(vHeadBone.x - 53, vHeadBone.y + 55, vHeadBone.z + 26), top3, 0) && top3.is_valid() &&
            my_controller->project_world_location_to_screen(fvector(vHeadBone.x + 53, vHeadBone.y + 55, vHeadBone.z + 26), top4, 0) && top4.is_valid();

        if (!valid_projection) return;

        float left_most = fmin(fmin(bottom1.x, bottom2.x), fmin(bottom3.x, bottom4.x)) - 1.0f;
        float right_most = fmax(fmax(top1.x, top2.x), fmax(top3.x, top4.x)) + 1.0f;
        float top_most = fmin(fmin(top1.y, top2.y), fmin(top3.y, top4.y)) - 5.0f;
        float bottom_most = fmax(fmax(bottom1.y, bottom2.y), fmax(bottom3.y, bottom4.y)) + 5.0f;

        fvector2d top_left = { left_most, top_most };
        fvector2d bottom_right = { right_most, bottom_most };

        if (globals::visuals::box2d) {
            canvas->k2_drawline(top_left, { bottom_right.x, top_left.y }, 1.5f, color);
            canvas->k2_drawline(top_left, { top_left.x, bottom_right.y }, 1.5f, color);
            canvas->k2_drawline(bottom_right, { bottom_right.x, top_left.y }, 1.5f, color);
            canvas->k2_drawline(bottom_right, { top_left.x, bottom_right.y }, 1.5f, color);
        }

        if (globals::visuals::box) {
            float lineW = (right_most - left_most) / 4.f;
            float lineH = (bottom_most - top_most) / 4.f;

            canvas->k2_drawline(top_left, { top_left.x + lineW, top_left.y }, 1.5f, color);
            canvas->k2_drawline(top_left, { top_left.x, top_left.y + lineH }, 1.5f, color);

            canvas->k2_drawline({ bottom_right.x - lineW, top_left.y }, { bottom_right.x, top_left.y }, 1.5f, color);
            canvas->k2_drawline({ bottom_right.x, top_left.y }, { bottom_right.x, top_left.y + lineH }, 1.5f, color);

            canvas->k2_drawline({ top_left.x, bottom_right.y - lineH }, { top_left.x, bottom_right.y }, 1.5f, color);
            canvas->k2_drawline({ top_left.x, bottom_right.y }, { top_left.x + lineW, bottom_right.y }, 1.5f, color);

            canvas->k2_drawline({ bottom_right.x - lineW, bottom_right.y }, { bottom_right.x, bottom_right.y }, 1.5f, color);
            canvas->k2_drawline({ bottom_right.x, bottom_right.y - lineH }, { bottom_right.x, bottom_right.y }, 1.5f, color);
        }
    }*/

    static bool bFlickSilent = true;
    static bool bLockedCameraRotation = false;

    fvector2d head_scren;

    double screen_center_x;
    double screen_center_y;
    /*float screen_center_x;
    float screen_center_y;*/

    fvector	LocalCameraLocation;
    float LocalCameraFOV;
    fvector	LocalCameraRotation;

#include <random>
#include "zagzou.h"

    int random_int(int min, int max) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(min, max);
        return dist(gen);
    }

    static flinearcolor MakeFromHSV8(uint8_t H, uint8_t S, uint8_t V)
    {
        float Hue = (float)H * 360.0f / 255.0f;
        float Saturation = (float)S / 255.0f;
        float Value = (float)V / 255.0f;

        float R = 0, G = 0, B = 0;

        int i = (int)(Hue / 60.0f) % 6;
        float f = (Hue / 60.0f) - i;
        float p = Value * (1.0f - Saturation);
        float q = Value * (1.0f - f * Saturation);
        float t = Value * (1.0f - (1.0f - f) * Saturation);

        switch (i)
        {
        case 0: R = Value; G = t;     B = p;     break;
        case 1: R = q;     G = Value; B = p;     break;
        case 2: R = p;     G = Value; B = t;     break;
        case 3: R = p;     G = q;     B = Value; break;
        case 4: R = t;     G = p;     B = Value; break;
        case 5: R = Value; G = p;     B = q;     break;
        }

        return flinearcolor(R, G, B, 1.0f);
    }

    void SetCameraCachePOVHook(aplayercameramanager* PlayerCameraManager, FMinimalViewInfo* ViewInfo)
    {
        bool aimbot_key_current = GetAsyncKeyState(globals::aimbot::a1m_k3y) != 0;

        LocalCameraLocation = ViewInfo->Location;

        if (globals::misc::aspect_ratio_enabled &&
            controllers &&
            character &&
            character->is_alive() &&
            ViewInfo)
        {
            ViewInfo->bConstrainAspectRatio = true;
            ViewInfo->AspectRatio = globals::misc::aspect_ratio_value;
        }

        static float spinAngle = 0.0f;
        static bool jitterFlip = false;
        static int threewayStep = 0;
        static bool aaEnabled = false;

        if (!controllers || !character || !ViewInfo) {
            return;
        }

        bool freecam_active = globals::misc::freecam_enabled;
        if (globals::misc::freecam_key != 0) {
            freecam_active = freecam_active && (GetAsyncKeyState(globals::misc::freecam_key) & 0x8000);
        }

        if (freecam_active) {
            if (!globals::misc::freecam_initialized) {
                globals::misc::freecam_pos = ViewInfo->Location;
                globals::misc::freecam_rot = ViewInfo->Rotation;
                globals::misc::freecam_initialized = true;
            }

            fvector forward, right;
            float radPitch = globals::misc::freecam_rot.x * (M_PI / 180.0f);
            float radYaw = globals::misc::freecam_rot.y * (M_PI / 180.0f);

            forward.x = cosf(radPitch) * cosf(radYaw);
            forward.y = cosf(radPitch) * sinf(radYaw);
            forward.z = sinf(radPitch);

            right.x = cosf(radYaw + (M_PI / 2.0f));
            right.y = sinf(radYaw + (M_PI / 2.0f));
            right.z = 0.0f;

            float speed = globals::misc::freecam_speed * 0.016f;
            if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
                speed *= 3.0f;

            if (GetAsyncKeyState('W') & 0x8000) {
                globals::misc::freecam_pos.x += forward.x * speed;
                globals::misc::freecam_pos.y += forward.y * speed;
                globals::misc::freecam_pos.z += forward.z * speed;
            }
            if (GetAsyncKeyState('S') & 0x8000) {
                globals::misc::freecam_pos.x -= forward.x * speed;
                globals::misc::freecam_pos.y -= forward.y * speed;
                globals::misc::freecam_pos.z -= forward.z * speed;
            }
            if (GetAsyncKeyState('D') & 0x8000) {
                globals::misc::freecam_pos.x += right.x * speed;
                globals::misc::freecam_pos.y += right.y * speed;
            }
            if (GetAsyncKeyState('A') & 0x8000) {
                globals::misc::freecam_pos.x -= right.x * speed;
                globals::misc::freecam_pos.y -= right.y * speed;
            }
            if (GetAsyncKeyState(VK_SPACE) & 0x8000)
                globals::misc::freecam_pos.z += speed;
            if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
                globals::misc::freecam_pos.z -= speed;

            float deltaX = 0.f, deltaY = 0.f;
            controllers->GetInputMouseDelta(deltaX, deltaY);
            float sensitivity = controllers->GetMouseSensitivity();
            globals::misc::freecam_rot.x += deltaY * sensitivity;
            globals::misc::freecam_rot.y += deltaX * sensitivity;

            ViewInfo->Location = globals::misc::freecam_pos;
            ViewInfo->Rotation = globals::misc::freecam_rot;

            hooks::SetCameraCachePOVOriginal(PlayerCameraManager, ViewInfo);
            return;
        }
        else {
            globals::misc::freecam_initialized = false;
        }

        if (!character->is_alive()) {
            if (auto mesh3p = character->get_mesh()) {
                mesh3p->set_world_rotation(fvector(0, LocalCameraRotation.y, 0), 0, 0);
            }
            aaEnabled = false;
            hooks::SetCameraCachePOVOriginal(PlayerCameraManager, ViewInfo);
            return;
        }

        if (!globals::misc::spinner) {
            aaEnabled = false;

            if (globals::misc::tperson && ::memory::IsValidPointer) {
                float radPitch = ViewInfo->Rotation.x * (M_PI / 180.0f);
                float radYaw = ViewInfo->Rotation.y * (M_PI / 180.0f);

                fvector forward;
                forward.x = cosf(radPitch) * cosf(radYaw);
                forward.y = cosf(radPitch) * sinf(radYaw);
                forward.z = sinf(radPitch);

                ViewInfo->Location.x -= forward.x * globals::misc::PlayerDistance;
                ViewInfo->Location.y -= forward.y * globals::misc::PlayerDistance;
                ViewInfo->Location.z -= forward.z * globals::misc::PlayerDistance;
            }

            hooks::SetCameraCachePOVOriginal(PlayerCameraManager, ViewInfo);
            return;
        }

        float deltaX = 0.f, deltaY = 0.f;
        controllers->GetInputMouseDelta(deltaX, deltaY);
        float sensitivity = controllers->GetMouseSensitivity();

        LocalCameraRotation.x += deltaY * sensitivity;
        LocalCameraRotation.y += deltaX * sensitivity;

        ViewInfo->Rotation = LocalCameraRotation;
        character->K2_SetActorRelativeRotation(fvector{ 0, LocalCameraRotation.y, 0 }, false, false);

        static bool lastTState = false;
        bool currentTState = (GetAsyncKeyState(0x54) & 1);

        if (currentTState && !lastTState) {
            aaEnabled = !aaEnabled;

            if (!aaEnabled) {
                spinAngle = LocalCameraRotation.y;
                threewayStep = 0;
                jitterFlip = false;
            }
        }
        lastTState = currentTState;

        if (aaEnabled) {
            SPOOF_FUNC;

            float fakeYaw = LocalCameraRotation.y;
            float fakePitch = LocalCameraRotation.x;


            if (globals::misc::pitch_enabled) {
                fakePitch = globals::misc::pitch_value;
            }


            fakeYaw += globals::misc::yaw_add;


            bool backKeyPressed = false;
            float direction = 0.0f;

            if (GetAsyncKeyState(0x463f4) & 0x8000) {
                backKeyPressed = true;
                direction = -90.f;
            }
            else if (GetAsyncKeyState(0x463f4) & 0x8000) {
                backKeyPressed = true;
                direction = 90.f;
            }
            else if (GetAsyncKeyState(0x4f634) & 0x8000) {
                backKeyPressed = true;
                direction = 180.f;
            }


            if (backKeyPressed) {
                if (globals::misc::jitter_enabled && globals::misc::jitter_on_back) {

                    fakeYaw += direction + (jitterFlip = !jitterFlip ? globals::misc::jitter_range : -globals::misc::jitter_range);
                }
                else {

                    fakeYaw += direction;
                }
            }

            else if (globals::misc::aa_spin) {
                spinAngle = fmodf(spinAngle + globals::misc::spinvalue, 360.f);
                fakeYaw = spinAngle;
            }
            else if (globals::misc::aa_jitter) {
                fakeYaw += (jitterFlip = !jitterFlip) ? globals::misc::jitter_range : -globals::misc::jitter_range;
            }
            else if (globals::misc::aa_threeway) {
                threewayStep = (threewayStep + 1) % 3;
                fakeYaw += (threewayStep == 0) ? 90.f : (threewayStep == 1) ? -90.f : 180.f;
            }

            else if (globals::misc::aa_desync) {
                static float desync_timer = 0.0f;
                desync_timer += 0.02f;

                float wave_desync = sinf(desync_timer) * globals::misc::desync_range;

                if (globals::misc::jitter_enabled) {
                    static int desync_jitter_counter = 0;
                    desync_jitter_counter++;
                    if (desync_jitter_counter % 8 == 0) {
                        wave_desync += (rand() % 60 - 30);
                    }
                }

                fakeYaw += wave_desync;
            }
            else if (globals::misc::aa_backwards) fakeYaw += 180.f;

            else if (globals::misc::atomic_aa) {
                static float atomic_timer = 0.0f;
                atomic_timer += 0.01f * globals::misc::atomic_speed;

                switch (globals::misc::atomic_mode) {
                case 0:
                    fakeYaw += sinf(atomic_timer * 5.0f) * 120.0f +
                        cosf(atomic_timer * 3.0f) * 60.0f;
                    break;

                case 1:
                    fakeYaw += (sinf(atomic_timer * 8.0f) > 0 ? 180.0f : -180.0f);
                    break;

                case 2:
                    static bool flicker_state = false;
                    static int flicker_counter = 0;
                    flicker_counter++;

                    if (flicker_counter % 5 == 0) {
                        flicker_state = !flicker_state;
                        fakeYaw += flicker_state ? 135.0f : -135.0f;
                    }
                    break;
                }


                if (globals::misc::jitter_enabled) {
                    fakeYaw += jitterFlip ? globals::misc::jitter_range * 0.5f : -globals::misc::jitter_range * 0.5f;
                    jitterFlip = !jitterFlip;
                }
            }

            else if (globals::misc::prediction_breaker) {
                static float breaker_timer = 0.0f;
                breaker_timer += 0.01f * globals::misc::breaker_intensity;


                float breaker_yaw =
                    sinf(breaker_timer * 3.0f) * 90.0f +
                    cosf(breaker_timer * 7.0f) * 45.0f +
                    sinf(breaker_timer * 13.0f) * 30.0f;

                fakeYaw += breaker_yaw;


                static float flick_timer = 0.0f;
                flick_timer += 0.01f;
                if (flick_timer > 2.0f) {
                    flick_timer = 0.0f;
                    fakeYaw += 180.0f;
                }
            }

            controllers->set_control_rotation(fvector(fakePitch, fakeYaw, 0));

            if (auto mesh3p = character->get_mesh()) {
                mesh3p->set_world_rotation(fvector(0, fakeYaw, 0), 0, 0);
            }
        }
        else {
            controllers->set_control_rotation(fvector(LocalCameraRotation.x, LocalCameraRotation.y, 0));

            if (auto mesh3p = character->get_mesh()) {
                mesh3p->set_world_rotation(fvector(0, LocalCameraRotation.y, 0), 0, 0);
            }
        };



        if (globals::misc::tperson && ::memory::IsValidPointer) {
            float radPitch = ViewInfo->Rotation.x * (M_PI / 180.0f);
            float radYaw = ViewInfo->Rotation.y * (M_PI / 180.0f);

            fvector forward;
            forward.x = cosf(radPitch) * cosf(radYaw);
            forward.y = cosf(radPitch) * sinf(radYaw);
            forward.z = sinf(radPitch);

            ViewInfo->Location.x -= forward.x * globals::misc::PlayerDistance;
            ViewInfo->Location.y -= forward.y * globals::misc::PlayerDistance;
            ViewInfo->Location.z -= forward.z * globals::misc::PlayerDistance;
        }

        hooks::SetCameraCachePOVOriginal(PlayerCameraManager, ViewInfo);
    }


    void Clamp(fvector& Ang) {
        if (Ang.x < 0.f)
            Ang.x += 360.f;

        if (Ang.x > 360.f)
            Ang.x -= 360.f;
        //alr
        if (Ang.y < 0.f) Ang.y += 360.f;
        if (Ang.y > 360.f) Ang.y -= 360.f;

    }

    float deg_2_rad(float degrees)
    {
        float radians;
        radians = degrees * (M_PI / 180);
        return radians;
    }

    float get_real_time()
    {
        static LARGE_INTEGER frequency;
        static bool use_qpc = QueryPerformanceFrequency(&frequency);

        if (use_qpc)
        {
            LARGE_INTEGER now;
            QueryPerformanceCounter(&now);
            return static_cast<float>(now.QuadPart) / frequency.QuadPart;
        }
        else
        {
            return static_cast<float>(GetTickCount64()) / 1000.0f;
        }
    }

    static float rainbowTime2 = 0.0f;
    static const float rainbowSpeed = 0.001f;
    static const float rainbowFrequency = 0.33f;

    const float PI2 = 6.28318530718f;

    flinearcolor calculate_smooth_rainbow(float t) {
        float r = 0.5f + 0.5f * sinf(t * PI2);
        float g = 0.5f + 0.5f * sinf((t + 0.333f) * PI2);
        float b = 0.5f + 0.5f * sinf((t + 0.666f) * PI2);
        return { r, g, b, 1.0f };
    }

    flinearcolor get_color(bool use_rainbow, const flinearcolor& default_color) {
        if (use_rainbow) {
            return calculate_smooth_rainbow(rainbowTime2);
        }
        return default_color;
    }

    namespace helper {
        fstring convert_weapon_name(fstring weapon_name)
        {
            std::wstring weapon_name_str = weapon_name.wide();

            if (weapon_name_str.find(L"Ability_Melee_Base_C") != std::wstring::npos)
                return L"Melee";
            else if (weapon_name_str.find(L"BasePistol_C") != std::wstring::npos)
                return L"Classic";
            else if (weapon_name_str.find(L"SawedOffShotgun_C") != std::wstring::npos)
                return L"Shorty";
            else if (weapon_name_str.find(L"AutomaticPistol_C") != std::wstring::npos)
                return L"Frenzy";
            else if (weapon_name_str.find(L"LugerPistol_C") != std::wstring::npos)
                return L"Ghost";
            else if (weapon_name_str.find(L"RevolverPistol_C") != std::wstring::npos)
                return L"Sheriff";
            else if (weapon_name_str.find(L"Vector_C") != std::wstring::npos)
                return L"Stinger";
            else if (weapon_name_str.find(L"SubMachineGun_MP5") != std::wstring::npos)
                return L"Spectre";
            else if (weapon_name_str.find(L"PumpShotgun_C") != std::wstring::npos)
                return L"Bucky";
            else if (weapon_name_str.find(L"AutomaticShotgun_C") != std::wstring::npos)
                return L"Judge";
            else if (weapon_name_str.find(L"AssaultRifle_Burst_C") != std::wstring::npos)
                return L"Bulldog";
            else if (weapon_name_str.find(L"DMR_C") != std::wstring::npos)
                return L"Guardian";
            else if (weapon_name_str.find(L"AssaultRifle_ACR_C") != std::wstring::npos)
                return L"Phantom";
            else if (weapon_name_str.find(L"AssaultRifle_AK_C") != std::wstring::npos)
                return L"Vandal";
            else if (weapon_name_str.find(L"LeverSniperRifle_C") != std::wstring::npos)
                return L"Marshal";
            else if (weapon_name_str.find(L"BoltSniper_C") != std::wstring::npos)
                return L"Operator";
            else if (weapon_name_str.find(L"LightMachineGun_C") != std::wstring::npos)
                return L"Ares";
            else if (weapon_name_str.find(L"HeavyMachineGun_C") != std::wstring::npos)
                return L"Odin";
            else if (weapon_name_str.find(L"Gun_Deadeye_Q_Pistol_C") != std::wstring::npos)
                return L"Headhunter";
            else if (weapon_name_str.find(L"Ability_Wushu_X_Dagger_Production_C") != std::wstring::npos)
                return L"Blade storm";
            else if (weapon_name_str.find(L"Gun_Sprinter_X_HeavyLightningGun_Production_C") != std::wstring::npos)
                return L"Overdrive";
            else if (weapon_name_str.find(L"DS_Gun_C") != std::wstring::npos)
                return L"Outlaw";
            else if (weapon_name_str.find(L"Gun_Deadeye_X_Giantslayer_Prototype_C") != std::wstring::npos)
                return L"Tour de force";
            return L"Invalid";
        }
    }

 //   // wall bang akc((
 //   struct FWallSpanInfo {
 //       FHitResult Entrance;
 //       FHitResult Exit;
 //   };

 //   struct FWallSpanList {
 //       tarray<FWallSpanInfo> Spans;
 //       bool bLastPointInWall;
 //       uint8_t Pad[0x7];
 //       FHitResult EntranceToLastPoint;
 //   };

 //   class UShooterBlueprintLibrary : public uobject {
 //   public:
 //       static void GetWallPenetrationSpans(uobject* WorldContextObject, fvector StartLocation, fvector EndLocation,
 //           tarray<uobject*> IgnoreActors, int Channel, float MinimumPlayableSpan, FWallSpanList& Spans) {
 //           static uobject* function = uobject::find_object<uobject*>(L"ShooterGame.ShooterBlueprintLibrary.GetWallPenetrationSpans");

 //           struct {
 //               uobject* WorldContextObject;
 //               fvector StartLocation;
 //               fvector EndLocation;
 //               tarray<uobject*> IgnoreActors;
 //               int Channel;
 //               float MinimumPlayableSpan;
 //               FWallSpanList Spans;
 //           } params;

 //           params.WorldContextObject = WorldContextObject;
 //           params.StartLocation = StartLocation;
 //           params.EndLocation = EndLocation;
 //           params.IgnoreActors = IgnoreActors;
 //           params.Channel = Channel;
 //           params.MinimumPlayableSpan = MinimumPlayableSpan;

 //           variables.blueprints->process_event(function, &params);
 //           Spans = params.Spans;
 //       }
 //   };

 //   namespace AutoWallSystem {
 //   
 //       enum class EAresSurfaceType {
 //           Default = 0,
 //           Concrete,
 //           Dirt,
 //           Gravel,
 //           Water,
 //           Metal,
 //           Wood,
 //           Grass,
 //           Glass,
 //           Flesh,
 //           Snow,
 //           MetalThin,
 //           BrokenGlass,
 //           Impenetrable,  
 //           Linoleum,
 //           BubbleCage,
 //           MetalNonResonant,
 //           CarpetOnWood,
 //           MetalPipe,
 //           ConcretePuddle,
 //           GarbageBag,
 //           Thorns,
 //           Sand,
 //           Mud,
 //           Tree,
 //           Ice,
 //           ShootinRangeTarget,
 //           Cloth,
 //           CobbleStone,
 //           CeramicTile,
 //           CarpetOnConcrete,
 //           EtherGlass,
 //           CosmicFabric,
 //           GoldenRipple,
 //           PlasticHollow,
 //           Shield,
 //           Count,
 //           MAX
 //       };

 //       struct SurfaceMaterial {
 //           float PenetrationModifier; 
 //           float DamageModifier;      
 //           bool CanPenetrate;       
 //       };

 //       std::map<EAresSurfaceType, SurfaceMaterial> SurfaceMaterials = {
 //           { EAresSurfaceType::Concrete,           { 0.4f, 0.25f, true } },
 //           { EAresSurfaceType::Metal,              { 0.3f, 0.4f, true } },
 //           { EAresSurfaceType::MetalThin,          { 0.6f, 0.35f, true } },
 //           { EAresSurfaceType::Wood,               { 0.7f, 0.15f, true } },
 //           { EAresSurfaceType::Glass,              { 0.9f, 0.05f, true } },
 //           { EAresSurfaceType::BrokenGlass,        { 0.95f, 0.02f, true } },
 //           { EAresSurfaceType::PlasticHollow,      { 0.8f, 0.1f, true } },
 //           { EAresSurfaceType::Cloth,              { 0.9f, 0.08f, true } },
 //           { EAresSurfaceType::CarpetOnConcrete,   { 0.85f, 0.12f, true } },
 //           { EAresSurfaceType::Linoleum,           { 0.75f, 0.18f, true } },

 //           { EAresSurfaceType::Impenetrable,       { 0.0f, 0.0f, false } },
 //           { EAresSurfaceType::Shield,             { 0.0f, 0.0f, false } },
 //           { EAresSurfaceType::BubbleCage,         { 0.0f, 0.0f, false } },
 //           { EAresSurfaceType::EtherGlass,         { 0.0f, 0.0f, false } },

 //           { EAresSurfaceType::Default,            { 0.5f, 0.3f, true } }
 //       };

 //       struct WallPenetrationResult {
 //           bool CanPenetrate;
 //           bool IsLethal;
 //           float EstimatedDamage;
 //           int WallCount;
 //           float TotalWallThickness;
 //           fvector OptimalAimPoint;
 //           FWallSpanList WallSpans;
 //           fstring HitBoneName;
 //       };

 //       struct WeaponPenetrationData {
 //           float HeadDamage;
 //           float BodyDamage;
 //           float LegDamage;
 //           float PenetrationPower;
 //           float DamageReductionPerWall;
 //           bool CanPenetrateWalls;
 //       };

 //       std::map<std::wstring, WeaponPenetrationData> WeaponDatabase = {
 //           { L"Vandal",     { 160.0f, 160.0f, 134.0f, 0.75f, 0.35f, true } },
 //           { L"Phantom",    { 156.0f, 156.0f, 130.0f, 0.75f, 0.35f, true } },
 //           { L"Operator",   { 255.0f, 150.0f, 120.0f, 0.90f, 0.25f, true } },
 //           { L"Marshal",    { 202.0f, 101.0f,  85.0f, 0.85f, 0.30f, true } },
 //           { L"Sheriff",    { 159.0f,  55.0f,  46.0f, 0.70f, 0.40f, true } },
 //           { L"Guardian",   { 195.0f,  65.0f,  49.0f, 0.80f, 0.30f, true } },
 //           { L"Outlaw",     { 140.0f, 140.0f, 119.0f, 0.78f, 0.32f, true } },
 //           { L"Ghost",      { 105.0f,  30.0f,  25.0f, 0.65f, 0.45f, true } },
 //           { L"Classic",    {  78.0f,  26.0f,  22.0f, 0.50f, 0.60f, false } },
 //           { L"Shorty",     {  20.0f,  12.0f,  10.0f, 0.20f, 0.80f, false } },
 //           { L"Frenzy",     {  78.0f,  26.0f,  21.0f, 0.55f, 0.55f, false } },
 //           { L"Spectre",    {  78.0f,  26.0f,  22.0f, 0.60f, 0.50f, true } },
 //           { L"Stinger",    {  67.0f,  27.0f,  22.0f, 0.58f, 0.52f, true } },
 //           { L"Bucky",      {  40.0f,  20.0f,  17.0f, 0.30f, 0.70f, false } },
 //           { L"Judge",      {  34.0f,  17.0f,  14.0f, 0.35f, 0.65f, false } },
 //           { L"Bulldog",    { 115.0f,  35.0f,  29.0f, 0.68f, 0.38f, true } },
 //           { L"Ares",       {  72.0f,  30.0f,  25.0f, 0.62f, 0.48f, true } },
 //           { L"Odin",       {  95.0f,  38.0f,  32.0f, 0.72f, 0.36f, true } }
 //       };

 //       EAresSurfaceType GetSurfaceTypeFromHitResult(const FHitResult& Hit) {
 //           static uobject* GetSurfaceTypeFunc = uobject::find_object<uobject*>(L"Engine.GameplayStatics.GetSurfaceType");

 //           if (!GetSurfaceTypeFunc)
 //               return EAresSurfaceType::Default;

 //           struct {
 //               FHitResult Hit;
 //               int ReturnValue; 
 //           } params;

 //           params.Hit = Hit;
 //           variables.blueprints->process_event(GetSurfaceTypeFunc, &params);

 //           return static_cast<EAresSurfaceType>(params.ReturnValue);
 //       }

 //       WeaponPenetrationData GetWeaponData(ashootercharacter* Player, const fstring& BoneName) {
 //           auto current_wep = Player->get_inventory()->get_current_equippable();
 //           fstring obj_name = helper::convert_weapon_name(system::get_object_name(current_wep));

 //           std::wstring weapon_name = obj_name.c_str();
 //           auto it = WeaponDatabase.find(weapon_name);
 //           if (it != WeaponDatabase.end()) {
 //               return it->second;
 //           }

 //           return { 100.0f, 35.0f, 25.0f, 0.60f, 0.40f, true };
 //       }

 //       float GetBoneDamageMultiplier(const fstring& BoneName, const WeaponPenetrationData& WeaponData) {
 //           std::wstring boneStr = BoneName.c_str();
 //           if (boneStr.find(L"Head") != std::wstring::npos || boneStr.find(L"head") != std::wstring::npos)
 //               return WeaponData.HeadDamage;
 //           else if (boneStr.find(L"Spine") != std::wstring::npos || boneStr.find(L"Chest") != std::wstring::npos || boneStr.find(L"Pelvis") != std::wstring::npos)
 //               return WeaponData.BodyDamage;
 //           else
 //               return WeaponData.LegDamage;
 //       }

 //       float CalculateWallThickness(const FWallSpanInfo& Span) {
 //           fvector entrance = Span.Entrance.Location;
 //           fvector exit = Span.Exit.Location;
 //           fvector diff = exit - entrance;
 //           float distance = diff.size();

 //           fvector hit_normal = Span.Entrance.Normal;
 //           fvector normalized_diff = diff;
 //           normalized_diff.normalize();
 //           float angle_factor = std::abs(hit_normal.dot(normalized_diff));

 //           return distance * (1.0f + (1.0f - angle_factor) * 0.5f);
 //       }

 //       float CalculatePenetrationDamage(const WeaponPenetrationData& WeaponData, const fstring& BoneName,
 //           float WallThickness, int WallCount, EAresSurfaceType SurfaceType) {

 //           auto surfaceIt = SurfaceMaterials.find(SurfaceType);
 //           if (surfaceIt == SurfaceMaterials.end() || !surfaceIt->second.CanPenetrate) {
 //               printf("[WALL] Impenetrable surface: %d\n", (int)SurfaceType);
 //               return 0.0f;
 //           }

 //           const SurfaceMaterial& Surface = surfaceIt->second;
 //           float base_damage = GetBoneDamageMultiplier(BoneName, WeaponData);

 //           printf("[WALL] Surface: %d, BaseDamage: %.1f, Thickness: %.2f\n",
 //               (int)SurfaceType, base_damage, WallThickness);

 //           float thickness_factor = WallThickness / 80.0f;
 //           if (thickness_factor > 1.5f)
 //               thickness_factor = 1.5f;

 //           float surface_efficiency = Surface.PenetrationModifier * WeaponData.PenetrationPower;
 //           float penetration_efficiency = surface_efficiency * (1.0f - thickness_factor * 0.3f);

 //           float damage_reduction = WeaponData.DamageReductionPerWall * (1.0f - penetration_efficiency);

 //           float final_damage = base_damage;
 //           for (int i = 0; i < WallCount; i++) {
 //               final_damage *= (1.0f - damage_reduction);
 //               final_damage *= Surface.DamageModifier;
 //           }

 //           float min_damage = base_damage * 0.15f * Surface.DamageModifier;

 //           float result_damage = final_damage;
 //           if (min_damage > final_damage)
 //               result_damage = min_damage;

 //           printf("[WALL] FinalDamage: %.1f, WallCount: %d\n", result_damage, WallCount);

 //           return result_damage;
 //       }

 //       fstring GetBoneNameFromIndex(int bone_index) {
 //           switch (bone_index) {
 //           case 0: return L"Head";
 //           case 1: return L"Neck";
 //           case 2: return L"Body";
 //           default: return L"Body";
 //           }
 //       }

 //       WallPenetrationResult CalculateWallPenetration(uworld* current_world, ashootercharacter* LocalPlayer, ashootercharacter* Target, fvector TargetBone, int BoneIndex) {
 //           WallPenetrationResult Result;
 //           Result.CanPenetrate = false;
 //           Result.IsLethal = false;
 //           Result.EstimatedDamage = 0.0f;
 //           Result.WallCount = 0;
 //           Result.TotalWallThickness = 0.0f;
 //           Result.OptimalAimPoint = TargetBone;
 //           Result.HitBoneName = GetBoneNameFromIndex(BoneIndex);

 //           if (!LocalPlayer || !Target || !Target->is_alive())
 //               return Result;

 //           fvector StartPos = LocalPlayer->GetPawnViewLocation();
 //           auto WeaponData = GetWeaponData(LocalPlayer, Result.HitBoneName);

 //           if (!WeaponData.CanPenetrateWalls) {
 //               return Result;
 //           }

 //           FWallSpanList WallSpans;
 //           tarray<uobject*> IgnoreActors;
 //           IgnoreActors.add(LocalPlayer);
 //           IgnoreActors.add(Target);

 //           UShooterBlueprintLibrary::GetWallPenetrationSpans(
 //               reinterpret_cast<uobject*>(current_world),
 //               StartPos,
 //               TargetBone,
 //               IgnoreActors,
 //               3, 
 //               0.0f,
 //               WallSpans
 //           );

 //           Result.WallSpans = WallSpans;
 //           Result.WallCount = WallSpans.Spans.Num();

 //           if (Result.WallCount == 0) {
 //               Result.CanPenetrate = true;
 //               Result.EstimatedDamage = GetBoneDamageMultiplier(Result.HitBoneName, WeaponData);
 //               Result.IsLethal = (Result.EstimatedDamage >= Target->health());
 //               return Result;
 //           }

 //           float TotalThickness = 0.0f;
 //           EAresSurfaceType WorstSurface = EAresSurfaceType::Default;

 //           for (int i = 0; i < WallSpans.Spans.Num(); i++) {
 //               TotalThickness += CalculateWallThickness(WallSpans.Spans[i]);

 //               EAresSurfaceType surface = GetSurfaceTypeFromHitResult(WallSpans.Spans[i].Entrance);
 //               if (SurfaceMaterials[surface].PenetrationModifier < SurfaceMaterials[WorstSurface].PenetrationModifier) {
 //                   WorstSurface = surface;
 //               }
 //           }

 //           Result.TotalWallThickness = TotalThickness;
 //           Result.EstimatedDamage = CalculatePenetrationDamage(
 //               WeaponData, Result.HitBoneName, TotalThickness, Result.WallCount, WorstSurface
 //           );

 //           float TargetHealth = Target->health();
 //           Result.IsLethal = (Result.EstimatedDamage >= TargetHealth);

 //           auto surfaceIt = SurfaceMaterials.find(WorstSurface);
 //           if (surfaceIt != SurfaceMaterials.end() && !surfaceIt->second.CanPenetrate) {
 //               Result.CanPenetrate = false;
 //               Result.EstimatedDamage = 0.0f;
 //           }
 //           else {
 //               float min_effective_damage = GetBoneDamageMultiplier(Result.HitBoneName, WeaponData) * 0.20f;
 //               Result.CanPenetrate = (Result.EstimatedDamage >= min_effective_damage);
 //           }

 //           if (Result.CanPenetrate && WallSpans.Spans.Num() > 0) {
 //               fvector LastExit = WallSpans.Spans[WallSpans.Spans.Num() - 1].Exit.Location;
 //               fvector to_target = TargetBone - LastExit;
 //               to_target.normalize();
 //               Result.OptimalAimPoint = LastExit + (to_target * 5.0f);
 //           }

 //           return Result;
 //       }

 //       bool ShouldShootThroughWalls(uworld* current_world, ashootercharacter* LocalPlayer, ashootercharacter* Target, fvector& BestAimPoint, fstring& BestBoneName, int Mode) {
 //           printf("[AUTOWALL] === ShouldShootThroughWalls STARTED ===\n");
 //           printf("[AUTOWALL] Target: %p, LocalPlayer: %p\n", Target, LocalPlayer);

 //           if (!Target || !Target->is_alive()) {
 //               printf("[AUTOWALL] ❌ Target invalid or dead\n");
 //               return false;
 //           }

 //           struct BonePenetration {
 //               fvector Bone;
 //               int BoneIndex;
 //               fstring BoneName;
 //               WallPenetrationResult Result;
 //           };

 //           std::vector<BonePenetration> BoneChecks;
 //           uskeletalmeshcomponent* Mesh = Target->get_mesh();
 //           if (!Mesh) {
 //               printf("[AUTOWALL] ❌ Target mesh is null\n");
 //               return false;
 //           }

 //           printf("[AUTOWALL] Getting bone matrices...\n");
 //           BoneChecks.push_back({ get_target_bone_matrix(Mesh, 0), 0, L"Head", {} });
 //           BoneChecks.push_back({ get_target_bone_matrix(Mesh, 2), 2, L"Body", {} });

 //           WallPenetrationResult* BestResult = nullptr;
 //           int valid_bones = 0;

 //           for (auto& BoneCheck : BoneChecks) {
 //               printf("[AUTOWALL] Checking bone %d...\n", BoneCheck.BoneIndex);

 //               if (BoneCheck.Bone.is_valid()) {
 //                   valid_bones++;
 //                   printf("[AUTOWALL] ✅ Bone %d is valid, calculating penetration...\n", BoneCheck.BoneIndex);

 //                   BoneCheck.Result = CalculateWallPenetration(current_world, LocalPlayer, Target, BoneCheck.Bone, BoneCheck.BoneIndex);

 //                   printf("[AUTOWALL] Bone %d - CanPenetrate: %d, WallCount: %d, Damage: %.1f\n",
 //                       BoneCheck.BoneIndex, BoneCheck.Result.CanPenetrate, BoneCheck.Result.WallCount, BoneCheck.Result.EstimatedDamage);

 //                   if (BoneCheck.Result.CanPenetrate && BoneCheck.Result.WallCount > 0) {
 //                       printf("[AUTOWALL] ✅ Bone %d CAN penetrate walls!\n", BoneCheck.BoneIndex);

 //                       if (Mode == 0) {
 //                           if (BoneCheck.Result.IsLethal || BoneCheck.Result.EstimatedDamage >= globals::aimbot::auto_wall_min_damage) {
 //                               if (!BestResult || BoneCheck.Result.EstimatedDamage > BestResult->EstimatedDamage) {
 //                                   BestResult = &BoneCheck.Result;
 //                                   BestAimPoint = BoneCheck.Result.OptimalAimPoint;
 //                                   BestBoneName = BoneCheck.BoneName;
 //                                   printf("[AUTOWALL] 🎯 New best target: Bone %d, Damage: %.1f\n", BoneCheck.BoneIndex, BoneCheck.Result.EstimatedDamage);
 //                               }
 //                           }
 //                       }
 //                       else if (Mode == 1) {
 //                           if (!BestResult || BoneCheck.Result.EstimatedDamage > BestResult->EstimatedDamage) {
 //                               BestResult = &BoneCheck.Result;
 //                               BestAimPoint = BoneCheck.Result.OptimalAimPoint;
 //                               BestBoneName = BoneCheck.BoneName;
 //                               printf("[AUTOWALL] 🎯 New best target: Bone %d, Damage: %.1f\n", BoneCheck.BoneIndex, BoneCheck.Result.EstimatedDamage);
 //                           }
 //                       }
 //                   }
 //                   else {
 //                       printf("[AUTOWALL] ❌ Bone %d cannot penetrate walls\n", BoneCheck.BoneIndex);
 //                   }
 //               }
 //               else {
 //                   printf("[AUTOWALL] ❌ Bone %d is INVALID\n", BoneCheck.BoneIndex);
 //               }
 //           }

 //           bool final_result = (BestResult != nullptr);
 //           printf("[AUTOWALL] Valid bones: %d/%d, Final result: %d\n", valid_bones, BoneChecks.size(), final_result);
 //           printf("[AUTOWALL] === ShouldShootThroughWalls FINISHED ===\n\n");

 //           return final_result;
 //       }
 //}
    void use_blind_manager_component(uobject* target_object)
    {
        SPOOF_FUNC
            auto blind_manager = static_cast<UBlindManagerComponent*>(target_object);

        if (blind_manager == nullptr)
            return;

        bool blinded = blind_manager->IsBlinded();

        if (blinded)
        {
            blind_manager->SetBlinded(false);

            blind_manager->ClientCleanseBlinds();
        }
    }


    void meshp3_material12(acknowledgedpawn* pawn, ashootercharacter* shooter_character)
    {
        if (!shooter_character || !pawn || !memory::IsValidPointer(uintptr_t(pawn)))
            return;

        static const wchar_t* material_paths[] =
        {
         L"/Game/Equippables/_Core/Materials/SpecialMaterials/Esportsinvitational/1P_Esportsinvitational_Crystal_Melee_v1_MI.1P_Esportsinvitational_Crystal_Melee_v1_MI",
        L"/Game/Equippables/_Core/Materials/SpecialMaterials/Esportsinvitational/1P_Esportsinvitational_Crystal_Melee_v2_MI.1P_Esportsinvitational_Crystal_Melee_v2_MI",
        L"/Game/Equippables/_Core/Materials/SpecialMaterials/Esportsinvitational/1P_Esportsinvitational_Crystal_Melee_v3_MI.1P_Esportsinvitational_Crystal_Melee_v3_MI",
            L"/Game/Equippables/_Core/Materials/SpecialMaterials/Atlas/1P_Atlas_Glass_MI.1P_Atlas_Glass_MI",
        L"/Game/Equippables/_Core/Materials/SpecialMaterials/Atlas/1P_Atlas_Emissive_Lv3_MI_v3.1P_Atlas_Emissive_Lv3_MI_v3",
        L"/Game/Equippables/_Core/Materials/SpecialMaterials/Atlas/1P_Atlas_Holographic_Sticker_MI.1P_Atlas_Holographic_Sticker_MI",
                L"/Game/Equippables/_Core/Materials/SpecialMaterials/Stylistic/1p_Weapon_Stylistic_MI.1p_Weapon_Stylistic_MI",
          L"/Game/Equippables/_Core/Materials/SpecialMaterials/Alien/1P_Alien_Decals_MI.1P_Alien_Decals_MI",
             L"/Game/Equippables/_Core/Materials/SpecialMaterials/Syndra/Syndra_Crystal_Front_MI.Syndra_Crystal_Front_MI",
             L"/Game/Equippables/_Core/Materials/SpecialMaterials/CosmosShader/SovWorld/3p_SovWorld_MI.3p_SovWorld_MI",
        };

        int material_count = sizeof(material_paths) / sizeof(material_paths[0]);
        int selected_material = globals::misc::chams_material_index;

        if (selected_material < 0 || selected_material >= material_count)
            selected_material = 0;

        uobject* material = uobject::static_load_object(nullptr, nullptr, material_paths[selected_material]);
        if (!material || !memory::IsValidPointer(uintptr_t(material)))
            return;

        UPrimitiveComponent* myselfchams = shooter_character->GetCosmeticMesh3P();
        if (!myselfchams || !memory::IsValidPointer(uintptr_t(myselfchams)))
            return;

        if (globals::misc::playerchamsself)
        {
            auto num_materials = myselfchams->get_num_materials();
            if (num_materials <= 0 || num_materials > 50)
                return;


            for (int i = 0; i < num_materials; i++)
            {
                UMaterialInstanceDynamic* dynamic_mat = myselfchams->create_and_set_material_instance_dynamic_from_material(i, material)->cast<UMaterialInstanceDynamic>();
                if (!dynamic_mat || !memory::IsValidPointer(uintptr_t(dynamic_mat)))
                    continue;


                if (globals::visuals::chams_visible_invisible)
                {
                    dynamic_mat->set_scalar_parameter_value(string::string_to_name(L"IgnoreDepth"), 1.0f);
                }
                else
                {
                    dynamic_mat->set_scalar_parameter_value(string::string_to_name(L"IgnoreDepth"), 0.0f);
                }


                if (selected_material == 3)
                {
                    fname diffuse_overlay = string::string_to_name(L"Diffuse Overlay Intensity");
                    fname inner_b_emissive = string::string_to_name(L"Inner (B) Emissive Intenstiy");
                    fname inner_g_emissive = string::string_to_name(L"Inner (G) Emissive Intenstiy");
                    fname bump_offset = string::string_to_name(L"Bump Offset Height");
                    fname texture_tiling = string::string_to_name(L"Texture Tiling");
                    fname reflection_vector = string::string_to_name(L"Reflection Vector Intensity");
                    fname flow_map_speed = string::string_to_name(L"Flow Map Speed Y");
                    fname panner_y = string::string_to_name(L"Panner Y");
                    fname diffuse_multiply = string::string_to_name(L"Diffuse Multiply");
                    fname diffuse_power = string::string_to_name(L"Diffuse Power");
                    fname refraction_bias = string::string_to_name(L"RefractionDepthBias");

                    dynamic_mat->set_scalar_parameter_value(diffuse_overlay, 20.0f);
                    dynamic_mat->set_scalar_parameter_value(inner_b_emissive, 5.0f);
                    dynamic_mat->set_scalar_parameter_value(inner_g_emissive, 5.0f);
                    dynamic_mat->set_scalar_parameter_value(bump_offset, -5.0f);
                    dynamic_mat->set_scalar_parameter_value(texture_tiling, 120.0f);
                    dynamic_mat->set_scalar_parameter_value(reflection_vector, 8.0f);
                    dynamic_mat->set_scalar_parameter_value(flow_map_speed, 0.5f);
                    dynamic_mat->set_scalar_parameter_value(panner_y, 10.0f);
                    dynamic_mat->set_scalar_parameter_value(diffuse_multiply, 6.0f);
                    dynamic_mat->set_scalar_parameter_value(diffuse_power, 5.5f);
                    dynamic_mat->set_scalar_parameter_value(refraction_bias, 3.0f);

                    fname emissive_surface = string::string_to_name(L"Emissive Surface Color");
                    fname diffuse_tint = string::string_to_name(L"Diffuse Tint");

                    flinearcolor galaxy_color = { 0.8f, 0.2f, 2.5f, 1.0f };
                    flinearcolor tint_color = { 1.5f, 0.5f, 4.0f, 1.0f };

                    dynamic_mat->set_vector_parameter_value1(emissive_surface, galaxy_color);
                    dynamic_mat->set_vector_parameter_value1(diffuse_tint, tint_color);
                }
            }
        }
    }



    //void meshp3_meshchange(acknowledgedpawn* pawn, ashootercharacter* shooter_character, const wchar_t* mesh_path)
    //{
    //    if (!shooter_character || !pawn || !memory::IsValidPointer(uintptr_t(pawn)))
    //        return;

    //  
    //    uskeletalmeshcomponent* loaded_mesh = (uskeletalmeshcomponent*)uobject::static_load_object(nullptr, nullptr, mesh_path);
    //    if (!loaded_mesh || !memory::IsValidPointer(uintptr_t(loaded_mesh)))
    //        return;

    //    UPrimitiveComponent* mesh_component = shooter_character->GetCosmeticMesh3P();
    //    if (!mesh_component || !memory::IsValidPointer(uintptr_t(mesh_component)))
    //        return;

    //    uskeletalmeshcomponent* skeletal_mesh_component = mesh_component->cast<uskeletalmeshcomponent>();
    //    if (!skeletal_mesh_component)
    //        return;

    //    
    //    skeletal_mesh_component->setsketeletalmesh(loaded_mesh, true);
    //    skeletal_mesh_component->updatemesh();
    //}


    //void test_all_meshes(acknowledgedpawn* pawn, ashootercharacter* shooter_character)
    //{
    //    
    //    const wchar_t* mesh_paths[] = {
    //        L"/Game/Characters/Player1/Meshes/Player1_Mesh.Player1_Mesh",
    //        L"/Game/Characters/Player2/Meshes/Player2_Mesh.Player2_Mesh",
    //        L"/Game/Characters/Player3/Meshes/Player3_Mesh.Player3_Mesh",
    //        L"/Game/Characters/Player4/Meshes/Player4_Mesh.Player4_Mesh"
    //    };

    //    
    //    int selected_mesh = 0; 

    //    if (selected_mesh >= 0 && selected_mesh < 4) {
    //        meshp3_meshchange(pawn, shooter_character, mesh_paths[selected_mesh]);
    //    }
    //}

    //
    //void on_hotkey_press(acknowledgedpawn* pawn, ashootercharacter* shooter_character)
    //{
    //    static int current_mesh = 0;
    //    const wchar_t* mesh_paths[] = {
    //        L"/Game/Characters/Player1/Meshes/Player1_Mesh.Player1_Mesh",
    //        L"/Game/Characters/Player2/Meshes/Player2_Mesh.Player2_Mesh",
    //        L"/Game/Characters/Player3/Meshes/Player3_Mesh.Player3_Mesh"
    //    };

    //    current_mesh = (current_mesh + 1) % 3; // 3 mesh arasında dönüşüm
    //    meshp3_meshchange(pawn, shooter_character, mesh_paths[current_mesh]);
    //}




    //helperim )) 

  
    struct BulletTracer {
        fvector Start;
        fvector End;
        float Lifetime;
    };

    inline std::vector<BulletTracer> BulletTracerList;

    inline std::chrono::steady_clock::time_point g_LastFrameTime;
    inline float GetManualDeltaTime()
    {
        using namespace std::chrono;

        static bool initialized = false;
        if (!initialized)
        {
            g_LastFrameTime = steady_clock::now();
            initialized = true;
            return 0.016f;
        }

        auto now = steady_clock::now();
        duration<float> delta = now - g_LastFrameTime;
        g_LastFrameTime = now;

        return delta.count();
    }


    namespace AutoWallSystem {
        bool CanShootThroughWalls(ashootercharacter* LocalPlayer, ashootercharacter* Target, fvector TargetBone) {
            if (!LocalPlayer || !Target || !Target->is_alive())
                return false;

            auto current_wep = LocalPlayer->get_inventory()->get_current_equippable();
            fstring weapon_name = helper::convert_weapon_name(system::get_object_name(current_wep));

            bool can_penetrate = false;
            if (weapon_name.wide() == L"Operator" || weapon_name.wide() == L"Marshal" ||
                weapon_name.wide() == L"Vandal" || weapon_name.wide() == L"Phantom" ||
                weapon_name.wide() == L"Sheriff" || weapon_name.wide() == L"Guardian" ||
                weapon_name.wide() == L"Bulldog" || weapon_name.wide() == L"Odin" ||
                weapon_name.wide() == L"Ares" || weapon_name.wide() == L"Spectre" ||
                weapon_name.wide() == L"Stinger" || weapon_name.wide() == L"Outlaw") {
                can_penetrate = true;
            }

            return can_penetrate;
        }
    }

    namespace NoSpread436467
    {

        static fvector calc_spread(ashootercharacter* actor, uint64_t firing_state_component, currentequippable* weapon, fvector direction)
        {
            if (!actor || !firing_state_component || !weapon)
                return fvector(0, 0, 0);

            uint64_t stability_component = memory::read<uint64_t>(firing_state_component + offsets::stability_component);
            if (!stability_component)
                return fvector(0, 0, 0);

            alignas(16) static uint8_t error_values[4096];
            alignas(16) static uint8_t seed_data_snapshot[4096];
            alignas(16) static uint8_t spread_angles[4096];
            alignas(16) static uint8_t out_spread_angles[4096];

            static auto func1_fn = (float* (__fastcall*)(uint64_t, float*))(memory::module_base + offsets::get_spread_values);
            static auto func2_fn = (void(__fastcall*)(uint64_t, fvector*, float, float, int, int, uint64_t))(memory::module_base + offsets::get_spread_angles);
            static auto func3_fn = (fvector * (__fastcall*)(fvector*, fvector*))(memory::module_base + offsets::to_vector_and_normalize);
            static auto func4_fn = (fvector * (__fastcall*)(fvector*, fvector*))(memory::module_base + offsets::to_angle_and_normalize);
            static auto func5_fn = (uintptr_t(__fastcall*)(__int64, float*))(memory::module_base + offsets::get_spread_values);

            *(uint64_t*)(&out_spread_angles[0]) = (uint64_t)&spread_angles[0];
            *(int*)(&out_spread_angles[0] + 8) = 1;
            *(int*)(&out_spread_angles[0] + 12) = 1;

            uint64_t seed_data = memory::read<uint64_t>(firing_state_component + offsets::seed_data);
            if (!seed_data)
                return fvector(0, 0, 0);

            memcpy((void*)seed_data_snapshot, (void*)seed_data, sizeof(seed_data_snapshot));

            reinterpret_cast<float* (__cdecl*)(uint64_t, float*, uintptr_t, void*)>(
                spoofcall_stub)(stability_component, (float*)&error_values[0], offsets::magic, func1_fn);

            fvector temp1, temp2 = fvector(0, 0, 0);
            fvector previous_firing_direction, firing_direction = fvector(0, 0, 0);

            actor->get_firing_location_and_direction(&temp1, &previous_firing_direction, false);

            reinterpret_cast<fvector* (__cdecl*)(fvector*, fvector*, uintptr_t, void*)>(
                spoofcall_stub)(&previous_firing_direction, &temp2, offsets::magic, func3_fn);
            reinterpret_cast<fvector* (__cdecl*)(fvector*, fvector*, uintptr_t, void*)>(
                spoofcall_stub)(&temp2, &temp1, offsets::magic, func4_fn);

            previous_firing_direction = temp1;

            temp1.x += *(float*)(&error_values[0] + 12);
            temp1.y += *(float*)(&error_values[0] + 16);

            reinterpret_cast<fvector* (__cdecl*)(fvector*, fvector*, uintptr_t, void*)>(
                spoofcall_stub)(&temp1, &firing_direction, offsets::magic, func3_fn);

            float test[20];
            uintptr_t v38 = reinterpret_cast<uintptr_t(__cdecl*)(__int64, float*, uintptr_t, void*)>(
                spoofcall_stub)(stability_component, test, offsets::magic, func5_fn);

            float v46 = memory::read<float>(v38 + 0x14);
            float v48 = *(float*)(&error_values[0] + 8) + *(float*)(&error_values[0] + 4);
            int error_retries = memory::read<int>(firing_state_component + offsets::error_retries);

            reinterpret_cast<void(__cdecl*)(
                uint64_t, fvector*, float, float, int, int, uint64_t, uintptr_t, void*)>(
                    spoofcall_stub)(
                        ((uint64_t)&seed_data_snapshot[0]) + 0xD8, &firing_direction,
                        v48, v46, error_retries, 1,
                        (uint64_t)&out_spread_angles[0], offsets::magic, func2_fn);

            fvector spread_vector = *(fvector*)(&spread_angles[0]);

            reinterpret_cast<fvector* (__cdecl*)(fvector*, fvector*, uintptr_t, void*)>(
                spoofcall_stub)(&spread_vector, &firing_direction, offsets::magic, func4_fn);

            return firing_direction - previous_firing_direction;
        }
    }

    /* void ChangeSkybox()
     {
         if (!globals::misc::skybox_changer) return;


         static uobject* SkyDomeClass = nullptr;
         if (!SkyDomeClass) {
             SkyDomeClass = uobject::find_object<uobject*>(L"Engine.SkyLight");
             if (!SkyDomeClass) return;
         }


         tarray<gameobject*> SkyDomes;
         game_statics::get_all_actors_of_class(world, SkyDomeClass, &SkyDomes);

         for (int i = 0; i < SkyDomes.size(); i++) {
             auto SkyDome = SkyDomes[i];
             if (!SkyDome) continue;


             auto Mesh = memory::read<UPrimitiveComponent*>((uintptr_t)SkyDome + 0x3B8);
             if (!Mesh) continue;


             auto matPath = L"/Engine/EngineSky/M_Sky_Panning_Clouds2.M_Sky_Panning_Clouds2";
             uobject* material = uobject::StaticLoadObject(matPath);
             if (!material) continue;

             static uobject* dynMat = nullptr;

             if (!dynMat) {
                 Mesh->set_material(0, material);
                 dynMat = Mesh->create_and_set_material_instance_dynamic_from_material(0, material);
             }

             if (dynMat) {
                 auto num_materials = Mesh->get_num_materials();
                 for (int j = 0; j < num_materials; j++) {
                     auto material_dynamic_obj = Mesh->create_and_set_material_instance_dynamic_from_material(j, material);
                     if (material_dynamic_obj) {
                         auto material_dynamic = material_dynamic_obj->cast<UMaterialInstanceDynamic>();
                         if (material_dynamic) {
                             material_dynamic->set_vector_parameter_value1(
                                 string::string_to_name(L"Horizon color"),
                                 globals::misc::sky_horizon
                             );
                             material_dynamic->set_vector_parameter_value1(
                                 string::string_to_name(L"Zenith Color"),
                                 globals::misc::sky_zenith
                             );
                             material_dynamic->set_vector_parameter_value1(
                                 string::string_to_name(L"Overall Color"),
                                 globals::misc::sky_overall
                             );
                         }
                     }
                 }
             }
         }
     }*/



    flinearcolor rainbowrgbf(float time)
    {
        const float PI = 3.14159265359f;
        float r = 0.5f + 0.5f * sin(time);
        float g = 0.5f + 0.5f * sin(time + 2.0f * PI / 3.0f);
        float b = 0.5f + 0.5f * sin(time + 4.0f * PI / 3.0f);
        return flinearcolor(r, g, b, 1.0f);
    }

    fvector RotatorToVector(const FRotator& rot)
    {
        float radPitch = rot.Pitch * PI / 180.f;
        float radYaw = rot.Yaw * PI / 180.f;

        float CP = cosf(radPitch);
        float SP = sinf(radPitch);
        float CY = cosf(radYaw);
        float SY = sinf(radYaw);

        return fvector(CP * CY, CP * SY, SP);
    }
    fvector2d GetScreenSize(ucanvas* canvas) {
        float clipX = *reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(canvas) + 0x38);
        float clipY = *reinterpret_cast<float*>(reinterpret_cast<uintptr_t>(canvas) + 0x3C);
        return fvector2d(clipX, clipY);
    }

#define MAX_TRACERS 100
#define TRACER_LIFETIME 4.5f

    struct Tracer {
        fvector worldStart;
        fvector worldEnd;
        float timeCreated;
        flinearcolor color;
    };

    struct FFiringResults {
        fvector FiringDirection;
        fvector StartLocation;
    };

    struct FCustom_OnShot_Params
    {
        firing_state* FiringState;
        int32_t ShotIndex;
        bool bTracerEnabled;
        bool bWasLastShot;
        tarray<FFiringResults> FiringResults;
    };

    Tracer tracers[MAX_TRACERS];
    int currentTracerIndex = 0;

    float GetCurrentGameTime()
    {
        return GetTickCount64() / 1000.0f;
    }

    bool PerformLineTrace(fvector Start, fvector Direction, float MaxDistance, fvector& OutHitLocation)
    {
        uworld* world = uworld::getworld2();
        if (!world)
        {
            OutHitLocation = Start + (Direction * MaxDistance);
            return false;
        }

        fvector End = Start + (Direction * MaxDistance);
        FHitResult HitResult;
        std::vector<AActor*> ActorsToIgnore;

        bool bHit = system::ares_line_trace_single_by_channel(
            (uobject*)world,
            Start,
            End,
            ActorsToIgnore,
            &HitResult,
            ECollisionChannel::ECC_Visibility,
            false,
            true
        );

        if (bHit)
        {
            OutHitLocation = HitResult.Location;
            return true;
        }

        OutHitLocation = End;
        return false;
    }

    using tProcessEvent = void(*)(void*, uobject*, void*, uintptr_t, void*);
    tProcessEvent oProcessEvent = nullptr;
    shadow_vmt1 process_event_hook;

    void hkProcessEvent(void* class_, uobject* function, void* params, uintptr_t magic, void* original_fn)
    {
        static bool didLogInit = false;
        if (!didLogInit)
        {
            printf("[+] ProcessEvent hook initialized.\n");
            didLogInit = true;
        }

        if (!function || !class_)
            return oProcessEvent(class_, function, params, magic, original_fn);

        fstring functionName = system::get_object_name(function);

        if (functionName.ToString() == ("Custom_OnShot"))
        {
            if (!params) {
                return oProcessEvent(class_, function, params, magic, original_fn);
            }

            auto* shotParams = static_cast<FCustom_OnShot_Params*>(params);

            if (!shotParams) {
                return oProcessEvent(class_, function, params, magic, original_fn);
            }

            if (shotParams->bTracerEnabled && shotParams->FiringResults.Num() > 0)
            {
                float currentTime = GetCurrentGameTime();

                // DAHA PARLAK RENKLER
                static const std::vector<flinearcolor> vibrantColors = {
                    flinearcolor(1.0f, 0.0f, 0.0f, 1.0f),    // TAM KIRMIZI
                    flinearcolor(0.0f, 1.0f, 0.0f, 1.0f),    // TAM YEŞİL
                    flinearcolor(0.0f, 0.5f, 1.0f, 1.0f),    // PARLAK MAVİ
                    flinearcolor(1.0f, 1.0f, 0.0f, 1.0f),    // TAM SARI
                    flinearcolor(1.0f, 0.0f, 1.0f, 1.0f),    // TAM PEMBE
                    flinearcolor(0.0f, 1.0f, 1.0f, 1.0f),    // CAMGÖBEĞİ
                    flinearcolor(1.0f, 0.5f, 0.0f, 1.0f),    // TURUNCU
                    flinearcolor(0.5f, 0.0f, 1.0f, 1.0f)     // MOR
                };

                for (int i = 0; i < shotParams->FiringResults.Num(); i++)
                {
                    FFiringResults& result = shotParams->FiringResults[i];

                    fvector actualEndLocation;
                    float maxRange = 50000.0f;

                    bool bHit = PerformLineTrace(
                        result.StartLocation,
                        result.FiringDirection,
                        maxRange,
                        actualEndLocation
                    );

                    static int colorCounter = 0;
                    int colorIndex = colorCounter % vibrantColors.size();
                    colorCounter++;

                    flinearcolor tracerColor = vibrantColors[colorIndex];
                    tracerColor.a = 1.0f; // TAM OPAK BAŞLANGIÇ

                    if (currentTracerIndex >= MAX_TRACERS) {
                        currentTracerIndex = 0;
                    }

                    tracers[currentTracerIndex] = {
                        result.StartLocation,
                        actualEndLocation,
                        currentTime,
                        tracerColor
                    };

                    currentTracerIndex = (currentTracerIndex + 1) % MAX_TRACERS;
                }

                printf("[Tracer] Added %d shots | Buffer: %d/%d\n",
                    shotParams->FiringResults.Num(),
                    currentTracerIndex,
                    MAX_TRACERS);
            }
        }

        oProcessEvent(class_, function, params, magic, original_fn);
    }

    void RenderBulletTracers(ucanvas* canvas, aplayercontroller* controller, fvector cameraLocation, fvector cameraForward, ashootercharacter* MyShooter)
    {
        if (!canvas || !controller || !MyShooter) return;

        if (!tracers) return;

        float currentTime = GetCurrentGameTime();
        fvector2d screenSize = canvas->get_screen_size();

        for (int i = 0; i < MAX_TRACERS; ++i)
        {
            if (i < 0 || i >= MAX_TRACERS) continue;

            Tracer& tracer = tracers[i];
            float age = currentTime - tracer.timeCreated;

            if (age < TRACER_LIFETIME && age >= 0.0f)
            {
                fvector start = tracer.worldStart;
                fvector end = tracer.worldEnd;

                fvector toStart = start - cameraLocation;
                fvector toEnd = end - cameraLocation;
                float startDot = toStart.dot(cameraForward);
                float endDot = toEnd.dot(cameraForward);

                if (startDot < 1.f && endDot < 1.f)
                    continue;

                if (startDot < 1.f) {
                    float t = (1.f - startDot) / (endDot - startDot);
                    start = start + (end - start) * std::clamp(t, 0.f, 1.f);
                }
                if (endDot < 1.f) {
                    float t = (1.f - startDot) / (endDot - startDot);
                    end = start + (end - start) * std::clamp(t, 0.f, 1.f);
                }

                fvector2d screenStart, screenEnd;
                if (controller->project_world_location_to_screen(start, screenStart, false) &&
                    controller->project_world_location_to_screen(end, screenEnd, false))
                {
                    // GARANTİLİ FADE SİSTEMİ
                    float normalizedAge = age / TRACER_LIFETIME;

                    // ÇOK YUMUŞAK FADE - KESİN ÇALIŞIR
                    float fadeFactor;
                    if (normalizedAge < 0.8f) {
                        fadeFactor = 1.0f - (normalizedAge * 0.4f); // İlk %80'de yavaş fade
                    }
                    else {
                        float remaining = (normalizedAge - 0.8f) / 0.2f;
                        fadeFactor = 0.68f * (1.0f - remaining); // Son %20'de lineer fade
                    }

                    float lineThickness = 0.9f + (0.3f * normalizedAge);
                    flinearcolor finalColor = tracer.color;
                    finalColor.a = fadeFactor; // DOĞRUDAN FADE FACTOR KULLAN

                    // DEBUG: Fade değerlerini kontrol et
                    static int debugCounter = 0;
                    if (debugCounter++ % 20 == 0) {
                        printf("[Tracer] Age: %.2f, Fade: %.3f, Alpha: %.3f\n", age, fadeFactor, finalColor.a);
                    }

                    canvas->k2_drawline(screenStart, screenEnd, lineThickness, finalColor);
                }
            }
        }
    }

    void InstallProcessEventHook(uobject* anyUObject)
    {
        if (!anyUObject) return;

        constexpr int ProcessEventIndex = 0x53;

        process_event_hook.g47ghf234h79g8f237h89<tProcessEvent>(
            memory::module_base,
            (uintptr_t)anyUObject,
            ProcessEventIndex,
            (void*)hkProcessEvent,
            &oProcessEvent
        );
    }
    //void draw_bullet_tracers2(
    //    ucanvas* canvas,
    //    aplayercameramanager* camera,
    //    aplayercontroller* controllers,
    //    ashootercharacter* local
    //) {
    //    try {
    //        if (!canvas || !camera || !controllers || !local) {
    //            return;
    //        }

    //        static std::vector<Tracer> tracers;
    //        float current_time = GetTickCount64() / 1000.0f;

    //        if (!globals::visuals::bullet_tracers) {
    //            tracers.clear();
    //            return;
    //        }

    //        // Yeni tracer oluştur
    //        if (globals::visuals::bullet_tracer_fire) {
    //            fvector camera_location = camera->get_camera_location();
    //            fvector camera_rotation = camera->get_camera_rotation();

    //            fvector forward = camera_rotation.Vector();
    //            forward.Normalize();
    //            fvector trace_end = camera_location + (forward * 50000.0f);

    //            FHitResult hit_result;
    //            tarray<ashootercharacter*> ignore_actors;
    //            ignore_actors.add(local);

    //            // COLOR DEĞİŞKENLERİNİ TANIMLA
    //            flinearcolor trace_color(1.0f, 0.0f, 0.0f, 1.0f);
    //            flinearcolor trace_hit_color(1.0f, 0.0f, 0.0f, 1.0f);

    //            bool hit = ashootercharacter::line_trace_single(
    //                world,
    //                camera_location,
    //                trace_end,
    //                ETraceTypeQuery::TraceTypeQuery1,
    //                false,
    //                ignore_actors,
    //                EDrawDebugTrace::None,
    //                &hit_result,
    //                true,
    //                trace_color, // DEĞİŞKEN OLARAK VER
    //                trace_hit_color, // DEĞİŞKEN OLARAK VER
    //                0.0f
    //            );

    //            fvector tracer_end;
    //            bool hasHit = false;
    //            if (hit && hit_result.bBlockingHit) {
    //                tracer_end = hit_result.ImpactPoint;
    //                hasHit = true;
    //            }
    //            else {
    //                tracer_end = trace_end;
    //            }

    //            // ARKADAŞININ KODUNDAKİ GİBİ VARIABLES'A KAYDET
    //            if (Variables::LastBulletIndexPushed > 4) {
    //                Variables::LastBulletIndexPushed = 0;
    //            }
    //            Variables::Last5BulletImpacts[Variables::LastBulletIndexPushed] = tracer_end;
    //            Variables::Last5BulletImpactsMuzzle[Variables::LastBulletIndexPushed] = camera_location;
    //            Variables::LastBulletIndexPushed += 1;

    //            float r = 0.4f + static_cast<float>(rand() % 60) / 100.0f;
    //            float g = 0.4f + static_cast<float>(rand() % 60) / 100.0f;
    //            float b = 0.4f + static_cast<float>(rand() % 60) / 100.0f;

    //            tracers.push_back({
    //                camera_location,
    //                tracer_end,
    //                current_time,
    //                {r, g, b, 1.0f},
    //                hasHit,
    //                (tracer_end - camera_location).Size()
    //                });

    //            globals::visuals::bullet_tracer_fire = false;
    //        }

    //        // Çizim kısmı AYNI KALIYOR
    //        for (auto it = tracers.begin(); it != tracers.end();) {
    //            float age = current_time - it->timeCreated;

    //            if (age >= 4.5f) {
    //                it = tracers.erase(it);
    //                continue;
    //            }

    //            fvector2d screen_start, screen_end;

    //            if (controllers->project_world_location_to_screen(it->worldStart, screen_start, true) &&
    //                controllers->project_world_location_to_screen(it->worldEnd, screen_end, true)) {

    //                float alpha = 1.0f - (age / 4.5f);
    //                flinearcolor tracer_color = it->color;
    //                tracer_color.a = alpha;

    //                canvas->k2_drawline(screen_start, screen_end, 1.5f, tracer_color);

    //                if (it->hasHit && it->distance < 9999.0f) {
    //                    constexpr float hitmarker_size = 6.0f;
    //                    fvector2d points[4][2] = {
    //                        {{screen_end.x - hitmarker_size, screen_end.y - hitmarker_size}, {screen_end.x - 2.0f, screen_end.y - 2.0f}},
    //                        {{screen_end.x + hitmarker_size, screen_end.y - hitmarker_size}, {screen_end.x + 2.0f, screen_end.y - 2.0f}},
    //                        {{screen_end.x - hitmarker_size, screen_end.y + hitmarker_size}, {screen_end.x - 2.0f, screen_end.y + 2.0f}},
    //                        {{screen_end.x + hitmarker_size, screen_end.y + hitmarker_size}, {screen_end.x + 2.0f, screen_end.y + 2.0f}}
    //                    };

    //                    flinearcolor hitmarker_color = { 1.0f, 0.0f, 0.0f, alpha };

    //                    for (int i = 0; i < 4; i++) {
    //                        canvas->k2_drawline(points[i][0], points[i][1], 1.5f, hitmarker_color);
    //                    }
    //                }
    //            }
    //            ++it;
    //        }
    //    }
    //    catch (...) {
    //        static std::vector<Tracer> tracers;
    //        tracers.clear();
    //    }
    //}

    //void apply_self_chams(ashootercharacter* local_player, ugameviewportclient* viewportclient)
    //{
    //    if (!local_player || !viewportclient) return;

    //    UPrimitiveComponent* self_mesh = local_player->GetCosmeticMesh3P();
    //    if (!self_mesh) return;

    //    uworld* world = reinterpret_cast<uworld*>(viewportclient->get_world());
    //    if (!world) return;

    //    // Apply preset colors if enabled for self chams
    //    if (globals::visuals::usepresetedoutlines)
    //    {
    //        // SELF VISIBLE PRESETS
    //        if (globals::visuals::visiblepreset == 0) // Default Green
    //        {
    //            globals::visuals::CenterEdgeR_Visible = 0.0f;
    //            globals::visuals::CenterEdgeG_Visible = 0.01f;
    //            globals::visuals::CenterEdgeB_Visible = 0.0f;
    //            globals::visuals::InnerEdgeR_Visible = 0.0f;
    //            globals::visuals::InnerEdgeG_Visible = 0.1f;
    //            globals::visuals::InnerEdgeB_Visible = 0.0f;
    //            globals::visuals::OuterEdgeR_Visible = 0.0f;
    //            globals::visuals::OuterEdgeG_Visible = 1.0f;
    //            globals::visuals::OuterEdgeB_Visible = 0.0f;
    //        }
    //        else if (globals::visuals::visiblepreset == 1) // Toxic Glow
    //        {
    //            globals::visuals::CenterEdgeR_Visible = 0.0f;
    //            globals::visuals::CenterEdgeG_Visible = 0.4f;
    //            globals::visuals::CenterEdgeB_Visible = 0.2f;
    //            globals::visuals::InnerEdgeR_Visible = 0.0f;
    //            globals::visuals::InnerEdgeG_Visible = 0.7f;
    //            globals::visuals::InnerEdgeB_Visible = 0.3f;
    //            globals::visuals::OuterEdgeR_Visible = 0.1f;
    //            globals::visuals::OuterEdgeG_Visible = 1.0f;
    //            globals::visuals::OuterEdgeB_Visible = 0.4f;
    //        }
    //        // Diğer preset'leri buraya ekleyebilirsiniz...
    //    }

    //    // Self outline application logic
    //    if (globals::visuals::outlinetype == 2) {
    //        SPOOF_FUNC
    //            reinterpret_cast<uskeletalmeshcomponent* (*__fastcall)(uskeletalmeshcomponent*, int, bool)>(memory::module_base + offsets::set_ares_outline_mode)(
    //                reinterpret_cast<uskeletalmeshcomponent*>(self_mesh), 0, true);
    //        return;
    //    }

    //    if (globals::visuals::outlinetype == 1) {
    //        SPOOF_FUNC
    //            reinterpret_cast<uskeletalmeshcomponent* (*__fastcall)(uskeletalmeshcomponent*, int, bool)>(memory::module_base + offsets::set_ares_outline_mode)(
    //                reinterpret_cast<uskeletalmeshcomponent*>(self_mesh), 0, true);
    //        return;
    //    }

    //    // Self outline materials setup
    //    float self_glowIntensity = globals::visuals::GlowVisible;
    //    flinearcolor self_centerEdgeColor = flinearcolor(globals::visuals::CenterEdgeR_Visible, globals::visuals::CenterEdgeG_Visible, globals::visuals::CenterEdgeB_Visible, globals::visuals::intensityvisibleoutline);
    //    flinearcolor self_innerEdgeColor = flinearcolor(globals::visuals::InnerEdgeR_Visible, globals::visuals::InnerEdgeG_Visible, globals::visuals::InnerEdgeB_Visible, globals::visuals::intensityvisibleoutline);
    //    flinearcolor self_outerEdgeColor = flinearcolor(globals::visuals::OuterEdgeR_Visible, globals::visuals::OuterEdgeG_Visible, globals::visuals::OuterEdgeB_Visible, globals::visuals::intensityvisibleoutline);

    //    static fname silohuette_color_name, center_edge_color_name, inner_edge_color_name, outer_edge_color_name, glow_intensity_param;
    //    if (!silohuette_color_name.comparison_index) {
    //        silohuette_color_name = string::string_to_name(L"SilohuetteColor");
    //        center_edge_color_name = string::string_to_name(L"CenterEdgeColor");
    //        inner_edge_color_name = string::string_to_name(L"InnerEdgeColor");
    //        outer_edge_color_name = string::string_to_name(L"OuterEdgeColor");
    //        glow_intensity_param = string::string_to_name(L"GlowIntensity");
    //    }

    //    uobject* self_visible_material = uobject::static_load_object(nullptr, nullptr, L"/Game/Characters/BountyHunter/S0/VFX/Materials/BountyHunterReveal_MI.BountyHunterReveal_MI");

    //    if (!self_visible_material) return;

    //    // Apply outline materials to self mesh
    //    auto num_materials = self_mesh->get_num_materials();
    //    for (int i = 0; i < num_materials; i++) {
    //        auto material_instance_dynamic = self_mesh->create_and_set_material_instance_dynamic_from_material(i, self_visible_material);
    //        auto dynCast = material_instance_dynamic->cast<UMaterialInstanceDynamic>();
    //        if (!dynCast) continue;

    //        dynCast->set_vector_parameter_value1(silohuette_color_name, self_outerEdgeColor);
    //        dynCast->set_vector_parameter_value1(center_edge_color_name, self_centerEdgeColor);
    //        dynCast->set_vector_parameter_value1(inner_edge_color_name, self_innerEdgeColor);
    //        dynCast->set_vector_parameter_value1(outer_edge_color_name, self_outerEdgeColor);
    //        dynCast->set_scalar_parameter_value(glow_intensity_param, self_glowIntensity);
    //    }

    //    // Eski sistemle uyumluluk için
    //    if (globals::visuals::self_chamsvsb && globals::visuals::self_visible_check_ch) {
    //        SPOOF_FUNC
    //            reinterpret_cast<uskeletalmeshcomponent* (*__fastcall)(uskeletalmeshcomponent*, int, bool)>(memory::module_base + offsets::set_ares_outline_mode)(
    //                reinterpret_cast<uskeletalmeshcomponent*>(self_mesh), 4, true);
    //    }
    //    else if (globals::visuals::self_chams) {
    //        SPOOF_FUNC
    //            reinterpret_cast<uskeletalmeshcomponent* (*__fastcall)(uskeletalmeshcomponent*, int, bool)>(memory::module_base + offsets::set_ares_outline_mode)(
    //                reinterpret_cast<uskeletalmeshcomponent*>(self_mesh), 1, true);
    //    }
    //    else if (globals::visuals::self_chamsal) {
    //        SPOOF_FUNC
    //            reinterpret_cast<uskeletalmeshcomponent* (__fastcall*)(uskeletalmeshcomponent*, int, bool)>(memory::module_base + offsets::set_ares_outline_mode)(
    //                reinterpret_cast<uskeletalmeshcomponent*>(self_mesh), 4, true);
    //    }
    //    else if (globals::visuals::self_chamsbg) {
    //        SPOOF_FUNC
    //            static float TimePassed = 0.0f;
    //        TimePassed += 0.02f * globals::visuals::self_brps;
    //        flinearcolor bng = GetRainbowColor(TimePassed);

    //        reinterpret_cast<uskeletalmeshcomponent* (*__fastcall)(uskeletalmeshcomponent*, int, bool)>(memory::module_base + offsets::set_ares_outline_mode)(
    //            reinterpret_cast<uskeletalmeshcomponent*>(self_mesh), 4, true);
    //    }
    //    else {
    //        SPOOF_FUNC
    //            reinterpret_cast<uskeletalmeshcomponent* (*__fastcall)(uskeletalmeshcomponent*, int, bool)>(memory::module_base + offsets::set_ares_outline_mode)(
    //                reinterpret_cast<uskeletalmeshcomponent*>(self_mesh), 0, true);
    //    }
    //}





//Galaxy chams

void apply_crystal_chams_to_self(ashootercharacter* local_player, ugameinstance* gameinstance)
{
    if (!local_player || !gameinstance) return;

    static int self_frame_counter = 0;
    static int last_preset = -1;

    self_frame_counter++;
    if (self_frame_counter % 6 != 0) return;

    if (last_preset != globals::visuals::crystal_chams_preset) {
        switch (globals::visuals::crystal_chams_preset) {
        case 0: // Crystal 1 - Mor/Mavi (PjGWwiK)
            globals::visuals::Self_CenterEdgeR = 0.53f;
            globals::visuals::Self_CenterEdgeG = 0.58f;
            globals::visuals::Self_CenterEdgeB = 0.52f;
            globals::visuals::Self_InnerEdgeR = 12.64f;
            globals::visuals::Self_InnerEdgeG = 15.00f;
            globals::visuals::Self_InnerEdgeB = 0.89f;
            globals::visuals::Self_OuterEdgeR = 2.47f;
            globals::visuals::Self_OuterEdgeG = 11.64f;
            globals::visuals::Self_OuterEdgeB = 0.00f;

            globals::visuals::GlowVisible = 1.5f;
            globals::visuals::AlphaBasePower = 2.0f;
            globals::visuals::AlphaColorMult = 1.2f;
            globals::visuals::DepthBias = 0.1f;
            globals::visuals::AlphaDissolveOpacity = 0.8f;
            globals::visuals::BoundingBox = 1.0f;
            globals::visuals::InnerEdgeThickness = 0.3f;
            globals::visuals::OuterEdgeThickness = 0.2f;
            globals::visuals::RimFresnel = 2.5f;
            globals::visuals::RimMultiply = 1.0f;
            globals::visuals::RimPower = 3.0f;
            globals::visuals::OcclusionDepth = 0.5f;
            globals::visuals::OcclusionBehindWall = 0.3f;
            globals::visuals::OcclusionState = 1.0f;
            globals::visuals::RefractionDepthBias = 0.05f;
            break;

        case 1: // Crystal 2 - Yeşil (SiK5dU8)
            globals::visuals::Self_CenterEdgeR = 0.58f;
            globals::visuals::Self_CenterEdgeG = 0.63f;
            globals::visuals::Self_CenterEdgeB = 0.52f;
            globals::visuals::Self_InnerEdgeR = 0.00f;
            globals::visuals::Self_InnerEdgeG = 0.00f;
            globals::visuals::Self_InnerEdgeB = 0.00f;
            globals::visuals::Self_OuterEdgeR = 2.67f;
            globals::visuals::Self_OuterEdgeG = 0.00f;
            globals::visuals::Self_OuterEdgeB = 0.00f;

            globals::visuals::GlowVisible = 1.8f;
            globals::visuals::AlphaBasePower = 2.2f;
            globals::visuals::AlphaColorMult = 1.0f;
            globals::visuals::DepthBias = 0.15f;
            globals::visuals::AlphaDissolveOpacity = 0.9f;
            globals::visuals::BoundingBox = 1.0f;
            globals::visuals::InnerEdgeThickness = 0.4f;
            globals::visuals::OuterEdgeThickness = 0.25f;
            globals::visuals::RimFresnel = 3.0f;
            globals::visuals::RimMultiply = 1.2f;
            globals::visuals::RimPower = 2.5f;
            globals::visuals::OcclusionDepth = 0.6f;
            globals::visuals::OcclusionBehindWall = 0.4f;
            globals::visuals::OcclusionState = 1.0f;
            globals::visuals::RefractionDepthBias = 0.08f;
            break;

        case 2: // Crystal 3 - Pembe/Mavi (SONBlYh)
            globals::visuals::Self_CenterEdgeR = 0.63f;
            globals::visuals::Self_CenterEdgeG = 0.63f;
            globals::visuals::Self_CenterEdgeB = 0.58f;
            globals::visuals::Self_InnerEdgeR = 0.00f;
            globals::visuals::Self_InnerEdgeG = 12.74f;
            globals::visuals::Self_InnerEdgeB = 13.64f;
            globals::visuals::Self_OuterEdgeR = 3.36f;
            globals::visuals::Self_OuterEdgeG = 0.00f;
            globals::visuals::Self_OuterEdgeB = 0.00f;

            globals::visuals::GlowVisible = 2.0f;
            globals::visuals::AlphaBasePower = 1.8f;
            globals::visuals::AlphaColorMult = 1.5f;
            globals::visuals::DepthBias = 0.12f;
            globals::visuals::AlphaDissolveOpacity = 0.7f;
            globals::visuals::BoundingBox = 1.0f;
            globals::visuals::InnerEdgeThickness = 0.35f;
            globals::visuals::OuterEdgeThickness = 0.18f;
            globals::visuals::RimFresnel = 2.8f;
            globals::visuals::RimMultiply = 1.1f;
            globals::visuals::RimPower = 3.2f;
            globals::visuals::OcclusionDepth = 0.4f;
            globals::visuals::OcclusionBehindWall = 0.2f;
            globals::visuals::OcclusionState = 1.0f;
            globals::visuals::RefractionDepthBias = 0.06f;
            break;

        case 3: // Crystal 4 - Mavi (DaWphR5)
            globals::visuals::Self_CenterEdgeR = 0.68f;
            globals::visuals::Self_CenterEdgeG = 0.63f;
            globals::visuals::Self_CenterEdgeB = 0.58f;
            globals::visuals::Self_InnerEdgeR = 0.00f;
            globals::visuals::Self_InnerEdgeG = 12.74f;
            globals::visuals::Self_InnerEdgeB = 13.64f;
            globals::visuals::Self_OuterEdgeR = 3.36f;
            globals::visuals::Self_OuterEdgeG = 0.00f;
            globals::visuals::Self_OuterEdgeB = 0.00f;

            globals::visuals::GlowVisible = 1.6f;
            globals::visuals::AlphaBasePower = 2.5f;
            globals::visuals::AlphaColorMult = 0.9f;
            globals::visuals::DepthBias = 0.08f;
            globals::visuals::AlphaDissolveOpacity = 0.85f;
            globals::visuals::BoundingBox = 1.0f;
            globals::visuals::InnerEdgeThickness = 0.25f;
            globals::visuals::OuterEdgeThickness = 0.15f;
            globals::visuals::RimFresnel = 2.2f;
            globals::visuals::RimMultiply = 0.8f;
            globals::visuals::RimPower = 2.8f;
            globals::visuals::OcclusionDepth = 0.7f;
            globals::visuals::OcclusionBehindWall = 0.5f;
            globals::visuals::OcclusionState = 1.0f;
            globals::visuals::RefractionDepthBias = 0.04f;
            break;

        case 4: 
            globals::visuals::Self_CenterEdgeR = 0.00f;
            globals::visuals::Self_CenterEdgeG = 0.63f;
            globals::visuals::Self_CenterEdgeB = 0.47f;
            globals::visuals::Self_InnerEdgeR = 0.00f;
            globals::visuals::Self_InnerEdgeG = 12.74f;
            globals::visuals::Self_InnerEdgeB = 13.64f;
            globals::visuals::Self_OuterEdgeR = 3.25f;
            globals::visuals::Self_OuterEdgeG = 0.00f;
            globals::visuals::Self_OuterEdgeB = 0.00f;

            globals::visuals::GlowVisible = 2.2f;
            globals::visuals::AlphaBasePower = 1.9f;
            globals::visuals::AlphaColorMult = 1.3f;
            globals::visuals::DepthBias = 0.18f;
            globals::visuals::AlphaDissolveOpacity = 0.75f;
            globals::visuals::BoundingBox = 1.0f;
            globals::visuals::InnerEdgeThickness = 0.45f;
            globals::visuals::OuterEdgeThickness = 0.28f;
            globals::visuals::RimFresnel = 3.5f;
            globals::visuals::RimMultiply = 1.4f;
            globals::visuals::RimPower = 2.6f;
            globals::visuals::OcclusionDepth = 0.35f;
            globals::visuals::OcclusionBehindWall = 0.25f;
            globals::visuals::OcclusionState = 1.0f;
            globals::visuals::RefractionDepthBias = 0.09f;
            break;
        }
        last_preset = globals::visuals::crystal_chams_preset;
    }

    if (!globals::visuals::crystal_chams_enabled) {
        auto self_main_mesh = local_player->get_mesh();
        if (self_main_mesh) {
            local_player->reset_character_materials_internal(self_main_mesh);
        }
        uskeletalmeshcomponent* self_cosmetic_mesh = local_player->GetCosmeticMesh3P();
        if (self_cosmetic_mesh) {
            local_player->reset_character_materials_internal(self_cosmetic_mesh);
        }

        auto mesh1p = memory::read<uskeletalmeshcomponent*>((uintptr_t)local_player + 0x0F10);
        auto meshOverlay = memory::read<uskeletalmeshcomponent*>((uintptr_t)local_player + 0x0F18);
        if (mesh1p) local_player->reset_character_materials_internal(mesh1p);
        if (meshOverlay) local_player->reset_character_materials_internal(meshOverlay);
        return;
    }

    uobject* crystal_material = uobject::static_load_object(nullptr, nullptr,
        L"/Game/Characters/BountyHunter/S0/VFX/Materials/BountyHunterReveal_MI.BountyHunterReveal_MI");

    if (!crystal_material) return;

    
    fname silohuette_color_name = string::string_to_name(L"SilohuetteColor");
    fname center_edge_color_name = string::string_to_name(L"CenterEdgeColor");
    fname inner_edge_color_name = string::string_to_name(L"InnerEdgeColor");
    fname outer_edge_color_name = string::string_to_name(L"OuterEdgeColor");
    fname glow_intensity_param = string::string_to_name(L"GlowIntensity");

   
    fname alpha_base_power_name = string::string_to_name(L"Alpha_Base_Power");
    //fname alpha_colormult_name = string::string_to_name(L"Alpha_ColorMult");
    fname depth_bias_name = string::string_to_name(L"DepthBias");
    fname alpha_dissolve_opacity_name = string::string_to_name(L"Alpha_Dissolve_Opacity");
    fname bounding_box_name = string::string_to_name(L"BoundingBox");
    fname inner_edge_thickness_name = string::string_to_name(L"InnerEdgeThickness");
    fname outer_edge_thickness_name = string::string_to_name(L"OuterEdgeThickness");
    fname rim_fresnel_name = string::string_to_name(L"Rim_Fresnel");
    fname rim_multiply_name = string::string_to_name(L"Rim_Multiply");
    fname rim_power_name = string::string_to_name(L"Rim_Power");
    //fname occlusion_depth_name = string::string_to_name(L"OcclusionDepth");
    fname occlusion_behind_wall_name = string::string_to_name(L"OcclusionDepth_BehindWall");
    fname occlusion_state_name = string::string_to_name(L"OcclusionState");
    fname refraction_depth_bias_name = string::string_to_name(L"RefractionDepthBias");

    
    float self_glowIntensity = globals::visuals::GlowVisible;
    float alpha_base_power = globals::visuals::AlphaBasePower;
    float alpha_colormult = globals::visuals::AlphaColorMult;
    float depth_bias = globals::visuals::DepthBias;
    float alpha_dissolve_opacity = globals::visuals::AlphaDissolveOpacity;
    float bounding_box = globals::visuals::BoundingBox;
    float inner_edge_thickness = globals::visuals::InnerEdgeThickness;
    float outer_edge_thickness = globals::visuals::OuterEdgeThickness;
    float rim_fresnel = globals::visuals::RimFresnel;
    float rim_multiply = globals::visuals::RimMultiply;
    float rim_power = globals::visuals::RimPower;
    //float occlusion_depth = globals::visuals::OcclusionDepth;
    float occlusion_behind_wall = globals::visuals::OcclusionBehindWall;
    float occlusion_state = globals::visuals::OcclusionState;
    float refraction_depth_bias = globals::visuals::RefractionDepthBias;

    flinearcolor self_centerEdgeColor = flinearcolor(
        globals::visuals::Self_CenterEdgeR,
        globals::visuals::Self_CenterEdgeG,
        globals::visuals::Self_CenterEdgeB,
        globals::visuals::intensityvisibleoutline
    );
    flinearcolor self_innerEdgeColor = flinearcolor(
        globals::visuals::Self_InnerEdgeR,
        globals::visuals::Self_InnerEdgeG,
        globals::visuals::Self_InnerEdgeB,
        globals::visuals::intensityvisibleoutline
    );
    flinearcolor self_outerEdgeColor = flinearcolor(
        globals::visuals::Self_OuterEdgeR,
        globals::visuals::Self_OuterEdgeG,
        globals::visuals::Self_OuterEdgeB,
        globals::visuals::intensityvisibleoutline
    );

   
    auto apply_material = [&](uskeletalmeshcomponent* mesh) {
        if (!mesh) return;

        int num_materials = mesh->get_num_materials();
        for (int i = 0; i < num_materials; i++) {
            auto material_instance_dynamic = mesh->create_and_set_material_instance_dynamic_from_material(i, crystal_material);
            auto dynCast = material_instance_dynamic->cast<UMaterialInstanceDynamic>();
            if (!dynCast) continue;

      
            dynCast->set_vector_parameter_value1(silohuette_color_name, self_outerEdgeColor);
            dynCast->set_vector_parameter_value1(center_edge_color_name, self_centerEdgeColor);
            dynCast->set_vector_parameter_value1(inner_edge_color_name, self_innerEdgeColor);
            dynCast->set_vector_parameter_value1(outer_edge_color_name, self_outerEdgeColor);
            dynCast->set_scalar_parameter_value(glow_intensity_param, self_glowIntensity);
            dynCast->set_scalar_parameter_value(alpha_base_power_name, alpha_base_power);
            //dynCast->set_scalar_parameter_value(alpha_colormult_name, alpha_colormult);
            dynCast->set_scalar_parameter_value(depth_bias_name, depth_bias);
            dynCast->set_scalar_parameter_value(alpha_dissolve_opacity_name, alpha_dissolve_opacity);
            dynCast->set_scalar_parameter_value(bounding_box_name, bounding_box);
            dynCast->set_scalar_parameter_value(inner_edge_thickness_name, inner_edge_thickness);
            dynCast->set_scalar_parameter_value(outer_edge_thickness_name, outer_edge_thickness);
            dynCast->set_scalar_parameter_value(rim_fresnel_name, rim_fresnel);
            dynCast->set_scalar_parameter_value(rim_multiply_name, rim_multiply);
            dynCast->set_scalar_parameter_value(rim_power_name, rim_power);
            //dynCast->set_scalar_parameter_value(occlusion_depth_name, occlusion_depth);
            dynCast->set_scalar_parameter_value(occlusion_behind_wall_name, occlusion_behind_wall);
            dynCast->set_scalar_parameter_value(occlusion_state_name, occlusion_state);
            dynCast->set_scalar_parameter_value(refraction_depth_bias_name, refraction_depth_bias);
        }
        };

   
    apply_material(local_player->get_mesh());
    apply_material(local_player->GetCosmeticMesh3P());

    auto mesh1p = memory::read<uskeletalmeshcomponent*>((uintptr_t)local_player + 0x0F10);
    auto meshOverlay = memory::read<uskeletalmeshcomponent*>((uintptr_t)local_player + 0x0F18);

    apply_material(mesh1p);
    apply_material(meshOverlay);
}




void apply_galaxy_chams_to_self(ashootercharacter* local_player, ugameinstance* gameinstance)
{
    if (!local_player || !gameinstance) return;

    static int self_frame_counter = 0;
    static int last_preset = -1;

    self_frame_counter++;
    if (self_frame_counter % 6 != 0) return;


    if (last_preset != globals::visuals::self_galaxy_preset) {
        switch (globals::visuals::self_galaxy_preset) {
        case 0:
            globals::visuals::Self_CenterEdgeR = 0.53f;
            globals::visuals::Self_CenterEdgeG = 0.27f;
            globals::visuals::Self_CenterEdgeB = 0.47f;
            globals::visuals::Self_InnerEdgeR = 0.0f;
            globals::visuals::Self_InnerEdgeG = 0.27f;
            globals::visuals::Self_InnerEdgeB = 1.0f;
            globals::visuals::Self_OuterEdgeR = 0.04f;
            globals::visuals::Self_OuterEdgeG = 0.23f;
            globals::visuals::Self_OuterEdgeB = 0.21f;
            break;
        case 1:
            globals::visuals::Self_CenterEdgeR = 0.00f;
            globals::visuals::Self_CenterEdgeG = 0.26f;
            globals::visuals::Self_CenterEdgeB = 0.00f;
            globals::visuals::Self_InnerEdgeR = 0.00f;
            globals::visuals::Self_InnerEdgeG = 0.25f;
            globals::visuals::Self_InnerEdgeB = 0.00f;
            globals::visuals::Self_OuterEdgeR = 0.00f;
            globals::visuals::Self_OuterEdgeG = 0.48f;
            globals::visuals::Self_OuterEdgeB = 0.21f;
            break;
        case 2:
            globals::visuals::Self_CenterEdgeR = 1.00f;
            globals::visuals::Self_CenterEdgeG = 0.00f;
            globals::visuals::Self_CenterEdgeB = 1.00f;
            globals::visuals::Self_InnerEdgeR = 0.00f;
            globals::visuals::Self_InnerEdgeG = 0.00f;
            globals::visuals::Self_InnerEdgeB = 0.00f;
            globals::visuals::Self_OuterEdgeR = 0.002f;
            globals::visuals::Self_OuterEdgeG = 0.25f;
            globals::visuals::Self_OuterEdgeB = 0.67f;
            break;
        case 3:
            globals::visuals::Self_CenterEdgeR = 0.00f;
            globals::visuals::Self_CenterEdgeG = 0.00f;
            globals::visuals::Self_CenterEdgeB = 1.00f;
            globals::visuals::Self_InnerEdgeR = 0.00f;
            globals::visuals::Self_InnerEdgeG = 0.00f;
            globals::visuals::Self_InnerEdgeB = 0.00f;
            globals::visuals::Self_OuterEdgeR = 0.22f;
            globals::visuals::Self_OuterEdgeG = 0.49f;
            globals::visuals::Self_OuterEdgeB = 1.00f;
            break;
        }
        last_preset = globals::visuals::self_galaxy_preset;
    }

    if (!globals::visuals::self_galaxy_enabled) {
        auto self_main_mesh = local_player->get_mesh();
        if (self_main_mesh) {
            local_player->reset_character_materials_internal(self_main_mesh);
        }
        uskeletalmeshcomponent* self_cosmetic_mesh = local_player->GetCosmeticMesh3P();
        if (self_cosmetic_mesh) {
            local_player->reset_character_materials_internal(self_cosmetic_mesh);
        }

        auto mesh1p = memory::read<uskeletalmeshcomponent*>((uintptr_t)local_player + 0x0F10);
        auto meshOverlay = memory::read<uskeletalmeshcomponent*>((uintptr_t)local_player + 0x0F18);
        if (mesh1p) local_player->reset_character_materials_internal(mesh1p);
        if (meshOverlay) local_player->reset_character_materials_internal(meshOverlay);
        return;
    }

    uobject* galaxy_material = uobject::static_load_object(nullptr, nullptr,
        L"/Game/Characters/BountyHunter/S0/VFX/Materials/BountyHunterReveal_MI.BountyHunterReveal_MI");

    if (!galaxy_material) return;
    fname silohuette_color_name = string::string_to_name(L"SilohuetteColor");
    fname center_edge_color_name = string::string_to_name(L"CenterEdgeColor");
    fname inner_edge_color_name = string::string_to_name(L"InnerEdgeColor");
    fname outer_edge_color_name = string::string_to_name(L"OuterEdgeColor");
    fname glow_intensity_param = string::string_to_name(L"GlowIntensity");


    /*   fname alpha_base_power_name = string::string_to_name(L"Alpha_Base_Power");*/
       //fname alpha_colormult_name = string::string_to_name(L"Alpha_ColorMult");
    fname depth_bias_name = string::string_to_name(L"DepthBias");
    fname alpha_dissolve_opacity_name = string::string_to_name(L"Alpha_Dissolve_Opacity");
    fname bounding_box_name = string::string_to_name(L"BoundingBox");
    //fname inner_edge_thickness_name = string::string_to_name(L"InnerEdgeThickness");
    //fname outer_edge_thickness_name = string::string_to_name(L"OuterEdgeThickness");
    //fname rim_fresnel_name = string::string_to_name(L"Rim_Fresnel");
    //fname rim_multiply_name = string::string_to_name(L"Rim_Multiply");
    //fname rim_power_name = string::string_to_name(L"Rim_Power");
    fname occlusion_depth_name = string::string_to_name(L"OcclusionDepth");
    fname occlusion_behind_wall_name = string::string_to_name(L"OcclusionDepth_BehindWall");
    fname occlusion_state_name = string::string_to_name(L"OcclusionState");
    fname refraction_depth_bias_name = string::string_to_name(L"RefractionDepthBias");


    float alpha_base_power = globals::visuals::AlphaBasePower;
    float alpha_colormult = globals::visuals::AlphaColorMult;
    float depth_bias = globals::visuals::DepthBias;
    float alpha_dissolve_opacity = globals::visuals::AlphaDissolveOpacity;
    float bounding_box = globals::visuals::BoundingBox;
    float inner_edge_thickness = globals::visuals::InnerEdgeThickness;
    float outer_edge_thickness = globals::visuals::OuterEdgeThickness;
    float rim_fresnel = globals::visuals::RimFresnel;
    float rim_multiply = globals::visuals::RimMultiply;
    float rim_power = globals::visuals::RimPower;
    float occlusion_depth = globals::visuals::OcclusionDepth;
    float occlusion_behind_wall = globals::visuals::OcclusionBehindWall;
    float occlusion_state = globals::visuals::OcclusionState;
    float refraction_depth_bias = globals::visuals::RefractionDepthBias;

    float self_glowIntensity = globals::visuals::GlowVisible;
    flinearcolor self_centerEdgeColor = flinearcolor(
        globals::visuals::Self_CenterEdgeR,
        globals::visuals::Self_CenterEdgeG,
        globals::visuals::Self_CenterEdgeB,
        globals::visuals::intensityvisibleoutline
    );
    flinearcolor self_innerEdgeColor = flinearcolor(
        globals::visuals::Self_InnerEdgeR,
        globals::visuals::Self_InnerEdgeG,
        globals::visuals::Self_InnerEdgeB,
        globals::visuals::intensityvisibleoutline
    );
    flinearcolor self_outerEdgeColor = flinearcolor(
        globals::visuals::Self_OuterEdgeR,
        globals::visuals::Self_OuterEdgeG,
        globals::visuals::Self_OuterEdgeB,
        globals::visuals::intensityvisibleoutline
    );

   
    auto self_main_mesh = local_player->get_mesh();
    if (self_main_mesh) {
        int num_materials = min(self_main_mesh->get_num_materials(), 3);
        for (int i = 0; i < num_materials; i++) {
            auto material_instance_dynamic = self_main_mesh->create_and_set_material_instance_dynamic_from_material(i, galaxy_material);
            auto dynCast = material_instance_dynamic->cast<UMaterialInstanceDynamic>();
            if (!dynCast) continue;

            dynCast->set_vector_parameter_value1(silohuette_color_name, self_outerEdgeColor);
            dynCast->set_vector_parameter_value1(center_edge_color_name, self_centerEdgeColor);
            dynCast->set_vector_parameter_value1(inner_edge_color_name, self_innerEdgeColor);
            dynCast->set_vector_parameter_value1(outer_edge_color_name, self_outerEdgeColor);
            dynCast->set_scalar_parameter_value(glow_intensity_param, self_glowIntensity);
            //dynCast->set_scalar_parameter_value(alpha_base_power_name, alpha_base_power);
            //dynCast->set_scalar_parameter_value(alpha_colormult_name, alpha_colormult);
            dynCast->set_scalar_parameter_value(depth_bias_name, depth_bias);
            //dynCast->set_scalar_parameter_value(alpha_dissolve_opacity_name, alpha_dissolve_opacity);
            dynCast->set_scalar_parameter_value(bounding_box_name, bounding_box);
            //dynCast->set_scalar_parameter_value(inner_edge_thickness_name, inner_edge_thickness);
            //dynCast->set_scalar_parameter_value(outer_edge_thickness_name, outer_edge_thickness);
            //dynCast->set_scalar_parameter_value(rim_fresnel_name, rim_fresnel);
            //dynCast->set_scalar_parameter_value(rim_multiply_name, rim_multiply);
            //dynCast->set_scalar_parameter_value(rim_power_name, rim_power);
            //dynCast->set_scalar_parameter_value(occlusion_depth_name, occlusion_depth);
            //dynCast->set_scalar_parameter_value(occlusion_behind_wall_name, occlusion_behind_wall);
            //dynCast->set_scalar_parameter_value(occlusion_state_name, occlusion_state);
            //dynCast->set_scalar_parameter_value(refraction_depth_bias_name, refraction_depth_bias);

        }
    }

  
    uskeletalmeshcomponent* self_cosmetic_mesh = local_player->GetCosmeticMesh3P();
    if (self_cosmetic_mesh) {
        int num_materials = min(self_cosmetic_mesh->get_num_materials(), 2);
        for (int i = 0; i < num_materials; i++) {
            auto material_instance_dynamic = self_cosmetic_mesh->create_and_set_material_instance_dynamic_from_material(i, galaxy_material);
            auto dynCast = material_instance_dynamic->cast<UMaterialInstanceDynamic>();
            if (!dynCast) continue;

            dynCast->set_vector_parameter_value1(silohuette_color_name, self_outerEdgeColor);
            dynCast->set_vector_parameter_value1(center_edge_color_name, self_centerEdgeColor);
            dynCast->set_vector_parameter_value1(inner_edge_color_name, self_innerEdgeColor);
            dynCast->set_vector_parameter_value1(outer_edge_color_name, self_outerEdgeColor);
            dynCast->set_scalar_parameter_value(glow_intensity_param, self_glowIntensity);
            //dynCast->set_scalar_parameter_value(alpha_base_power_name, alpha_base_power);
            //dynCast->set_scalar_parameter_value(alpha_colormult_name, alpha_colormult);
            dynCast->set_scalar_parameter_value(depth_bias_name, depth_bias);
            //dynCast->set_scalar_parameter_value(alpha_dissolve_opacity_name, alpha_dissolve_opacity);
            dynCast->set_scalar_parameter_value(bounding_box_name, bounding_box);
            //dynCast->set_scalar_parameter_value(inner_edge_thickness_name, inner_edge_thickness);
            //dynCast->set_scalar_parameter_value(outer_edge_thickness_name, outer_edge_thickness);
            //dynCast->set_scalar_parameter_value(rim_fresnel_name, rim_fresnel);
            //dynCast->set_scalar_parameter_value(rim_multiply_name, rim_multiply);
            //dynCast->set_scalar_parameter_value(rim_power_name, rim_power);
            //dynCast->set_scalar_parameter_value(occlusion_depth_name, occlusion_depth);
            //dynCast->set_scalar_parameter_value(occlusion_behind_wall_name, occlusion_behind_wall);
            //dynCast->set_scalar_parameter_value(occlusion_state_name, occlusion_state);
            //dynCast->set_scalar_parameter_value(refraction_depth_bias_name, refraction_depth_bias);


        }
    }

  
    auto mesh1p = memory::read<uskeletalmeshcomponent*>((uintptr_t)local_player + 0x0F10);
    if (mesh1p) {
        int num_materials = min(mesh1p->get_num_materials(), 2);
        for (int i = 0; i < num_materials; i++) {
            auto material_instance_dynamic = mesh1p->create_and_set_material_instance_dynamic_from_material(i, galaxy_material);
            auto dynCast = material_instance_dynamic->cast<UMaterialInstanceDynamic>();
            if (!dynCast) continue;

            dynCast->set_vector_parameter_value1(silohuette_color_name, self_outerEdgeColor);
            dynCast->set_vector_parameter_value1(center_edge_color_name, self_centerEdgeColor);
            dynCast->set_vector_parameter_value1(inner_edge_color_name, self_innerEdgeColor);
            dynCast->set_vector_parameter_value1(outer_edge_color_name, self_outerEdgeColor);
            dynCast->set_scalar_parameter_value(glow_intensity_param, self_glowIntensity);
            //dynCast->set_scalar_parameter_value(alpha_base_power_name, alpha_base_power);
            //dynCast->set_scalar_parameter_value(alpha_colormult_name, alpha_colormult);
            dynCast->set_scalar_parameter_value(depth_bias_name, depth_bias);
            //dynCast->set_scalar_parameter_value(alpha_dissolve_opacity_name, alpha_dissolve_opacity);
            dynCast->set_scalar_parameter_value(bounding_box_name, bounding_box);
       /*     dynCast->set_scalar_parameter_value(inner_edge_thickness_name, inner_edge_thickness);
            dynCast->set_scalar_parameter_value(outer_edge_thickness_name, outer_edge_thickness);
            dynCast->set_scalar_parameter_value(rim_fresnel_name, rim_fresnel);
            dynCast->set_scalar_parameter_value(rim_multiply_name, rim_multiply);
            dynCast->set_scalar_parameter_value(rim_power_name, rim_power);*/
            //dynCast->set_scalar_parameter_value(occlusion_depth_name, occlusion_depth);
            //dynCast->set_scalar_parameter_value(occlusion_behind_wall_name, occlusion_behind_wall);
            //dynCast->set_scalar_parameter_value(occlusion_state_name, occlusion_state);
            //dynCast->set_scalar_parameter_value(refraction_depth_bias_name, refraction_depth_bias);

        }
    }

  
    auto meshOverlay = memory::read<uskeletalmeshcomponent*>((uintptr_t)local_player + 0x0F18);
    if (meshOverlay) {
        int num_materials = min(meshOverlay->get_num_materials(), 2);
        for (int i = 0; i < num_materials; i++) {
            auto material_instance_dynamic = meshOverlay->create_and_set_material_instance_dynamic_from_material(i, galaxy_material);
            auto dynCast = material_instance_dynamic->cast<UMaterialInstanceDynamic>();
            if (!dynCast) continue;

            dynCast->set_vector_parameter_value1(silohuette_color_name, self_outerEdgeColor);
            dynCast->set_vector_parameter_value1(center_edge_color_name, self_centerEdgeColor);
            dynCast->set_vector_parameter_value1(inner_edge_color_name, self_innerEdgeColor);
            dynCast->set_vector_parameter_value1(outer_edge_color_name, self_outerEdgeColor);
            dynCast->set_scalar_parameter_value(glow_intensity_param, self_glowIntensity);
            //dynCast->set_scalar_parameter_value(alpha_base_power_name, alpha_base_power);
            //dynCast->set_scalar_parameter_value(alpha_colormult_name, alpha_colormult);
            dynCast->set_scalar_parameter_value(depth_bias_name, depth_bias);
            //dynCast->set_scalar_parameter_value(alpha_dissolve_opacity_name, alpha_dissolve_opacity);
            dynCast->set_scalar_parameter_value(bounding_box_name, bounding_box);
      /*      dynCast->set_scalar_parameter_value(inner_edge_thickness_name, inner_edge_thickness);
            dynCast->set_scalar_parameter_value(outer_edge_thickness_name, outer_edge_thickness);
            dynCast->set_scalar_parameter_value(rim_fresnel_name, rim_fresnel);
            dynCast->set_scalar_parameter_value(rim_multiply_name, rim_multiply);
            dynCast->set_scalar_parameter_value(rim_power_name, rim_power);*/
            //dynCast->set_scalar_parameter_value(occlusion_depth_name, occlusion_depth);
            //dynCast->set_scalar_parameter_value(occlusion_behind_wall_name, occlusion_behind_wall);
            //dynCast->set_scalar_parameter_value(occlusion_state_name, occlusion_state);
            //dynCast->set_scalar_parameter_value(refraction_depth_bias_name, refraction_depth_bias);

        }
    }
}



void apply_dynamic_fresnel_presets()
{
    switch (globals::visuals::dynamic_fresnel_preset) {
    case 0: 
        globals::visuals::Self_CenterEdgeR = 0.00f;
        globals::visuals::Self_CenterEdgeG = 0.00f;
        globals::visuals::Self_CenterEdgeB = 0.00f;
        globals::visuals::Self_InnerEdgeR = 0.00f;
        globals::visuals::Self_InnerEdgeG = 0.00f;
        globals::visuals::Self_InnerEdgeB = 0.00f;
        globals::visuals::Self_OuterEdgeR = 0.87f;
        globals::visuals::Self_OuterEdgeG = 2.45f;
        globals::visuals::Self_OuterEdgeB = 14.34f;
        break;
    case 1: 
        globals::visuals::Self_CenterEdgeR = 0.00f;
        globals::visuals::Self_CenterEdgeG = 0.00f;
        globals::visuals::Self_CenterEdgeB = 0.00f;
        globals::visuals::Self_InnerEdgeR = 0.00f;
        globals::visuals::Self_InnerEdgeG = 0.00f;
        globals::visuals::Self_InnerEdgeB = 0.00f;
        globals::visuals::Self_OuterEdgeR = 0.87f;
        globals::visuals::Self_OuterEdgeG = 2.45f;
        globals::visuals::Self_OuterEdgeB = 0.00f;
        break;
    case 2: 
        globals::visuals::Self_CenterEdgeR = 0.70f;
        globals::visuals::Self_CenterEdgeG = 0.17f;
        globals::visuals::Self_CenterEdgeB = 1.00f;
        globals::visuals::Self_InnerEdgeR = 39.34f;
        globals::visuals::Self_InnerEdgeG = 0.00f;
        globals::visuals::Self_InnerEdgeB = 0.00f;
        globals::visuals::Self_OuterEdgeR = 0.87f;
        globals::visuals::Self_OuterEdgeG = 2.62f;
        globals::visuals::Self_OuterEdgeB = 1.00f;
        break;
    case 3: 
        globals::visuals::Self_CenterEdgeR = 0.00f;
        globals::visuals::Self_CenterEdgeG = 0.00f;
        globals::visuals::Self_CenterEdgeB = 0.00f;
        globals::visuals::Self_InnerEdgeR = 0.00f;
        globals::visuals::Self_InnerEdgeG = 0.00f;
        globals::visuals::Self_InnerEdgeB = 0.00f;
        globals::visuals::Self_OuterEdgeR = 0.87f;
        globals::visuals::Self_OuterEdgeG = 0.52f;
        globals::visuals::Self_OuterEdgeB = 0.00f;
        break;
    case 4: 
        globals::visuals::Self_CenterEdgeR = 0.17f;
        globals::visuals::Self_CenterEdgeG = 0.00f;
        globals::visuals::Self_CenterEdgeB = 0.00f;
        globals::visuals::Self_InnerEdgeR = 0.00f;
        globals::visuals::Self_InnerEdgeG = 0.00f;
        globals::visuals::Self_InnerEdgeB = 0.00f;
        globals::visuals::Self_OuterEdgeR = 0.87f;
        globals::visuals::Self_OuterEdgeG = 0.00f;
        globals::visuals::Self_OuterEdgeB = 0.00f;
        break;
    case 5: 
        globals::visuals::Self_CenterEdgeR = 0.70f;
        globals::visuals::Self_CenterEdgeG = 0.17f;
        globals::visuals::Self_CenterEdgeB = 0.00f;
        globals::visuals::Self_InnerEdgeR = 40.34f;
        globals::visuals::Self_InnerEdgeG = 0.00f;
        globals::visuals::Self_InnerEdgeB = 0.00f;
        globals::visuals::Self_OuterEdgeR = 0.87f;
        globals::visuals::Self_OuterEdgeG = 6.99f;
        globals::visuals::Self_OuterEdgeB = 1.00f;
        break;
    case 6: 
        globals::visuals::Self_CenterEdgeR = 0.70f;
        globals::visuals::Self_CenterEdgeG = 0.17f;
        globals::visuals::Self_CenterEdgeB = 0.00f;
        globals::visuals::Self_InnerEdgeR = 40.34f;
        globals::visuals::Self_InnerEdgeG = 0.00f;
        globals::visuals::Self_InnerEdgeB = 0.00f;
        globals::visuals::Self_OuterEdgeR = 0.87f;
        globals::visuals::Self_OuterEdgeG = 6.99f;
        globals::visuals::Self_OuterEdgeB = 1.00f;
        break;
    }
}

void apply_dynamic_fresnel_outline(ashootercharacter* local_player, ugameinstance* gameinstance)
{
    if (!local_player || !gameinstance) return;

    if (!globals::visuals::dynamic_fresnel_outline) {
        
        auto self_main_mesh = local_player->get_mesh();
        if (self_main_mesh) {
            local_player->reset_character_materials_internal(self_main_mesh);
        }
        uskeletalmeshcomponent* self_cosmetic_mesh = local_player->GetCosmeticMesh3P();
        if (self_cosmetic_mesh) {
            local_player->reset_character_materials_internal(self_cosmetic_mesh);
        }

        auto mesh1p = memory::read<uskeletalmeshcomponent*>((uintptr_t)local_player + 0x0F10);
        auto meshOverlay = memory::read<uskeletalmeshcomponent*>((uintptr_t)local_player + 0x0F18);
        if (mesh1p) local_player->reset_character_materials_internal(mesh1p);
        if (meshOverlay) local_player->reset_character_materials_internal(meshOverlay);
        return;
    }

    static int self_frame_counter = 0;
    static int last_preset = -1;

    self_frame_counter++;
    if (self_frame_counter % 6 != 0) return;

   
    if (last_preset != globals::visuals::dynamic_fresnel_preset) {
        apply_dynamic_fresnel_presets();
        last_preset = globals::visuals::dynamic_fresnel_preset;
    }

  
    uobject* fresnel_material = uobject::static_load_object(nullptr, nullptr,
        L"/Game/Characters/BountyHunter/S0/VFX/Materials/BountyHunterReveal_MI.BountyHunterReveal_MI");

    if (!fresnel_material) return;


    fname bounding_box_name = string::string_to_name(L"BoundingBox");
    fname alpha_dissolve_opacity_name = string::string_to_name(L"Alpha_Dissolve_Opacity");
    fname alpha_base_power_name = string::string_to_name(L"Alpha_Base_Power");
    fname depth_bias_name = string::string_to_name(L"DepthBias");
    fname silohuette_color_name = string::string_to_name(L"SilohuetteColor");
    fname center_edge_color_name = string::string_to_name(L"CenterEdgeColor");
    fname inner_edge_color_name = string::string_to_name(L"InnerEdgeColor");
    fname outer_edge_color_name = string::string_to_name(L"OuterEdgeColor");
    fname glow_intensity_param = string::string_to_name(L"GlowIntensity");
    fname inner_edge_thickness_name = string::string_to_name(L"InnerEdgeThickness");
    fname outer_edge_thickness_name = string::string_to_name(L"OuterEdgeThickness");
    fname rim_power_name = string::string_to_name(L"Rim_Power");
    fname rim_multiply_name = string::string_to_name(L"Rim_Multiply");
    fname rim_fresnel_name = string::string_to_name(L"Rim_Fresnel");
    fname occlusion_state_name = string::string_to_name(L"OcclusionState");
    fname occlusion_behind_wall_name = string::string_to_name(L"OcclusionDepth_BehindWall");
    float alpha_base_power = globals::visuals::AlphaBasePower;
    float alpha_colormult = globals::visuals::AlphaColorMult;
    float alpha_dissolve_opacity = globals::visuals::AlphaDissolveOpacity;
    float bounding_box = globals::visuals::BoundingBox;
    float inner_edge_thickness = globals::visuals::InnerEdgeThickness;
    float outer_edge_thickness = globals::visuals::OuterEdgeThickness;
    float rim_fresnel = globals::visuals::RimFresnel;
    float rim_multiply = globals::visuals::RimMultiply;
    float rim_power = globals::visuals::RimPower;
    float occlusion_depth = globals::visuals::OcclusionDepth;
    float occlusion_behind_wall = globals::visuals::OcclusionBehindWall;
    float occlusion_state = globals::visuals::OcclusionState;
    float refraction_depth_bias = globals::visuals::RefractionDepthBias;
    float self_glowIntensity = globals::visuals::GlowVisible;
    float inner_thickness = globals::visuals::InnerEdgeThickness;
    float outer_thickness = globals::visuals::OuterEdgeThickness;
    float rim_power_val = globals::visuals::RimPower;
    float rim_multiply_val = globals::visuals::RimMultiply;
    float rim_fresnel_val = globals::visuals::RimFresnel;
    float depth_bias = globals::visuals::DepthBias;

    flinearcolor self_centerEdgeColor = flinearcolor(
        globals::visuals::Self_CenterEdgeR,
        globals::visuals::Self_CenterEdgeG,
        globals::visuals::Self_CenterEdgeB,
        globals::visuals::intensityvisibleoutline
    );
    flinearcolor self_innerEdgeColor = flinearcolor(
        globals::visuals::Self_InnerEdgeR,
        globals::visuals::Self_InnerEdgeG,
        globals::visuals::Self_InnerEdgeB,
        globals::visuals::intensityvisibleoutline
    );
    flinearcolor self_outerEdgeColor = flinearcolor(
        globals::visuals::Self_OuterEdgeR,
        globals::visuals::Self_OuterEdgeG,
        globals::visuals::Self_OuterEdgeB,
        globals::visuals::intensityvisibleoutline
    );

    auto apply_material = [&](uskeletalmeshcomponent* mesh, int max_mats) {
        if (!mesh) return;
        int num_materials = min(mesh->get_num_materials(), max_mats);
        for (int i = 0; i < num_materials; i++) {
            auto material_instance_dynamic = mesh->create_and_set_material_instance_dynamic_from_material(i, fresnel_material);
            auto dynCast = material_instance_dynamic->cast<UMaterialInstanceDynamic>();
            if (!dynCast) continue;

            dynCast->set_vector_parameter_value1(silohuette_color_name, self_outerEdgeColor);
            dynCast->set_vector_parameter_value1(center_edge_color_name, self_centerEdgeColor);
            dynCast->set_vector_parameter_value1(inner_edge_color_name, self_innerEdgeColor);
            dynCast->set_vector_parameter_value1(outer_edge_color_name, self_outerEdgeColor);
            dynCast->set_scalar_parameter_value(bounding_box_name, bounding_box);
            dynCast->set_scalar_parameter_value(depth_bias_name, depth_bias);

            dynCast->set_scalar_parameter_value(glow_intensity_param, self_glowIntensity);
            dynCast->set_scalar_parameter_value(inner_edge_thickness_name, inner_thickness);
            dynCast->set_scalar_parameter_value(outer_edge_thickness_name, outer_thickness);
            dynCast->set_scalar_parameter_value(rim_power_name, rim_power_val);
            dynCast->set_scalar_parameter_value(rim_multiply_name, rim_multiply_val);
            dynCast->set_scalar_parameter_value(rim_fresnel_name, rim_fresnel_val);
            dynCast->set_scalar_parameter_value(occlusion_state_name, occlusion_state);
            dynCast->set_scalar_parameter_value(occlusion_behind_wall_name, occlusion_behind_wall);
        }
        };

    apply_material(local_player->get_mesh(), 3);
    apply_material(local_player->GetCosmeticMesh3P(), 2);

    auto mesh1p = memory::read<uskeletalmeshcomponent*>((uintptr_t)local_player + 0x0F10);
    auto meshOverlay = memory::read<uskeletalmeshcomponent*>((uintptr_t)local_player + 0x0F18);

    apply_material(mesh1p, 2);
    apply_material(meshOverlay, 2);
}

//void apply_self_fresnel_presets()
//{
//    switch (globals::visuals::self_galaxy_preset) {
//    case 0: // Purple Galaxy
//        globals::visuals::Self_CenterEdgeR = 0.53f;
//        globals::visuals::Self_CenterEdgeG = 0.27f;
//        globals::visuals::Self_CenterEdgeB = 0.47f;
//        globals::visuals::Self_InnerEdgeR = 0.0f;
//        globals::visuals::Self_InnerEdgeG = 0.27f;
//        globals::visuals::Self_InnerEdgeB = 1.0f;
//        globals::visuals::Self_OuterEdgeR = 0.04f;
//        globals::visuals::Self_OuterEdgeG = 0.23f;
//        globals::visuals::Self_OuterEdgeB = 0.21f;
//        break;
//    case 1: // Green Energy
//        globals::visuals::Self_CenterEdgeR = 0.00f;
//        globals::visuals::Self_CenterEdgeG = 0.26f;
//        globals::visuals::Self_CenterEdgeB = 0.00f;
//        globals::visuals::Self_InnerEdgeR = 0.00f;
//        globals::visuals::Self_InnerEdgeG = 0.25f;
//        globals::visuals::Self_InnerEdgeB = 0.00f;
//        globals::visuals::Self_OuterEdgeR = 0.00f;
//        globals::visuals::Self_OuterEdgeG = 0.48f;
//        globals::visuals::Self_OuterEdgeB = 0.21f;
//        break;
//    case 2: // Pink Cyan
//        globals::visuals::Self_CenterEdgeR = 1.00f;
//        globals::visuals::Self_CenterEdgeG = 0.00f;
//        globals::visuals::Self_CenterEdgeB = 1.00f;
//        globals::visuals::Self_InnerEdgeR = 0.00f;
//        globals::visuals::Self_InnerEdgeG = 0.00f;
//        globals::visuals::Self_InnerEdgeB = 0.00f;
//        globals::visuals::Self_OuterEdgeR = 0.002f;
//        globals::visuals::Self_OuterEdgeG = 0.25f;
//        globals::visuals::Self_OuterEdgeB = 0.67f;
//        break;
//    case 3: // Blue Ice
//        globals::visuals::Self_CenterEdgeR = 0.00f;
//        globals::visuals::Self_CenterEdgeG = 0.00f;
//        globals::visuals::Self_CenterEdgeB = 1.00f;
//        globals::visuals::Self_InnerEdgeR = 0.00f;
//        globals::visuals::Self_InnerEdgeG = 0.00f;
//        globals::visuals::Self_InnerEdgeB = 0.00f;
//        globals::visuals::Self_OuterEdgeR = 0.22f;
//        globals::visuals::Self_OuterEdgeG = 0.49f;
//        globals::visuals::Self_OuterEdgeB = 1.00f;
//        break;
//    }
//}    //void apply_galaxy_chams_to_self(ashootercharacter* local_player, ugameinstance* gameinstance)
    //{
    //    if (!local_player || !gameinstance) return;

    // 
    //    static int self_frame_counter = 0;
    //    self_frame_counter++;
    //    if (self_frame_counter % 6 != 0) return;

    //    
    //    bool self_visible = true;


    //    if (!globals::visuals::self_galaxy_enabled) {
    //        auto self_main_mesh = local_player->get_mesh();
    //        if (self_main_mesh) {
    //            local_player->reset_character_materials_internal(self_main_mesh);
    //        }
    //        uskeletalmeshcomponent* self_cosmetic_mesh = local_player->GetCosmeticMesh3P();
    //        if (self_cosmetic_mesh) {
    //            local_player->reset_character_materials_internal(self_cosmetic_mesh);
    //        }

    //      
    //        auto mesh1p = memory::read<uskeletalmeshcomponent*>((uintptr_t)local_player + 0x0F10);
    //        auto meshOverlay = memory::read<uskeletalmeshcomponent*>((uintptr_t)local_player + 0x0F18);
    //        if (mesh1p) local_player->reset_character_materials_internal(mesh1p);
    //        if (meshOverlay) local_player->reset_character_materials_internal(meshOverlay);

    //        return;
    //    }

    //   
    //    uobject* galaxy_material = uobject::static_load_object(nullptr, nullptr,
    //        L"/Game/Characters/BountyHunter/S0/VFX/Materials/BountyHunterReveal_MI.BountyHunterReveal_MI");

    //    if (!galaxy_material) return;

    // 
    //    fname silohuette_color_name = string::string_to_name(L"SilohuetteColor");
    //    fname center_edge_color_name = string::string_to_name(L"CenterEdgeColor");
    //    fname inner_edge_color_name = string::string_to_name(L"InnerEdgeColor");
    //    fname outer_edge_color_name = string::string_to_name(L"OuterEdgeColor");
    //    fname glow_intensity_param = string::string_to_name(L"GlowIntensity");

    //   
    //    float self_glowIntensity = globals::visuals::GlowVisible;
    //    flinearcolor self_centerEdgeColor = flinearcolor(0.53f, 0.27f, 0.47f, globals::visuals::intensityvisibleoutline);
    //    flinearcolor self_innerEdgeColor = flinearcolor(0.0f, 0.27f, 1.0f, globals::visuals::intensityvisibleoutline);
    //    flinearcolor self_outerEdgeColor = flinearcolor(0.04f, 0.23f, 0.21f, globals::visuals::intensityvisibleoutline);

    //   
    //    auto self_main_mesh = local_player->get_mesh();
    //    if (self_main_mesh) {
    //        int num_materials = min(self_main_mesh->get_num_materials(), 3);
    //        for (int i = 0; i < num_materials; i++) {
    //            auto material_instance_dynamic = self_main_mesh->create_and_set_material_instance_dynamic_from_material(i, galaxy_material);
    //            auto dynCast = material_instance_dynamic->cast<UMaterialInstanceDynamic>();
    //            if (!dynCast) continue;

    //            dynCast->set_vector_parameter_value1(silohuette_color_name, self_outerEdgeColor);
    //            dynCast->set_vector_parameter_value1(center_edge_color_name, self_centerEdgeColor);
    //            dynCast->set_vector_parameter_value1(inner_edge_color_name, self_innerEdgeColor);
    //            dynCast->set_vector_parameter_value1(outer_edge_color_name, self_outerEdgeColor);
    //            dynCast->set_scalar_parameter_value(glow_intensity_param, self_glowIntensity);
    //        }
    //    }

    //    
    //    uskeletalmeshcomponent* self_cosmetic_mesh = local_player->GetCosmeticMesh3P();
    //    if (self_cosmetic_mesh) {
    //        int num_materials = min(self_cosmetic_mesh->get_num_materials(), 2);
    //        for (int i = 0; i < num_materials; i++) {
    //            auto material_instance_dynamic = self_cosmetic_mesh->create_and_set_material_instance_dynamic_from_material(i, galaxy_material);
    //            auto dynCast = material_instance_dynamic->cast<UMaterialInstanceDynamic>();
    //            if (!dynCast) continue;

    //            dynCast->set_vector_parameter_value1(silohuette_color_name, self_outerEdgeColor);
    //            dynCast->set_vector_parameter_value1(center_edge_color_name, self_centerEdgeColor);
    //            dynCast->set_vector_parameter_value1(inner_edge_color_name, self_innerEdgeColor);
    //            dynCast->set_vector_parameter_value1(outer_edge_color_name, self_outerEdgeColor);
    //            dynCast->set_scalar_parameter_value(glow_intensity_param, self_glowIntensity);
    //        }
    //    }

    //   
    //    auto mesh1p = memory::read<uskeletalmeshcomponent*>((uintptr_t)local_player + 0x0F10);
    //    auto meshOverlay = memory::read<uskeletalmeshcomponent*>((uintptr_t)local_player + 0x0F18);

    //    if (mesh1p) {
    //        int num_materials = min(mesh1p->get_num_materials(), 2);
    //        for (int i = 0; i < num_materials; i++) {
    //            auto material_instance_dynamic = mesh1p->create_and_set_material_instance_dynamic_from_material(i, galaxy_material);
    //            auto dynCast = material_instance_dynamic->cast<UMaterialInstanceDynamic>();
    //            if (!dynCast) continue;

    //            dynCast->set_vector_parameter_value1(silohuette_color_name, self_outerEdgeColor);
    //            dynCast->set_vector_parameter_value1(center_edge_color_name, self_centerEdgeColor);
    //            dynCast->set_vector_parameter_value1(inner_edge_color_name, self_innerEdgeColor);
    //            dynCast->set_vector_parameter_value1(outer_edge_color_name, self_outerEdgeColor);
    //            dynCast->set_scalar_parameter_value(glow_intensity_param, self_glowIntensity);
    //        }
    //    }

    //    if (meshOverlay) {
    //        int num_materials = min(meshOverlay->get_num_materials(), 2);
    //        for (int i = 0; i < num_materials; i++) {
    //            auto material_instance_dynamic = meshOverlay->create_and_set_material_instance_dynamic_from_material(i, galaxy_material);
    //            auto dynCast = material_instance_dynamic->cast<UMaterialInstanceDynamic>();
    //            if (!dynCast) continue;

    //            dynCast->set_vector_parameter_value1(silohuette_color_name, self_outerEdgeColor);
    //            dynCast->set_vector_parameter_value1(center_edge_color_name, self_centerEdgeColor);
    //            dynCast->set_vector_parameter_value1(inner_edge_color_name, self_innerEdgeColor);
    //            dynCast->set_vector_parameter_value1(outer_edge_color_name, self_outerEdgeColor);
    //            dynCast->set_scalar_parameter_value(glow_intensity_param, self_glowIntensity);
    //        }
    //    }
    //}



    void apply_outline_chams(acknowledgedpawn* pawn, ashootercharacter* actor, aplayercontroller* controllers)
    {

        if (!pawn || !actor || !controllers) return;


        static int frame_counter = 0;
        frame_counter++;
        if (frame_counter % 8 != 0) return;


        if (globals::visuals::usepresetedoutlines)
        {

            if (globals::visuals::visiblepreset == 0)
            {
                globals::visuals::CenterEdgeR_Visible = 0.53f;
                globals::visuals::CenterEdgeG_Visible = 0.27f;
                globals::visuals::CenterEdgeB_Visible = 0.30f;
                globals::visuals::InnerEdgeR_Visible = 0.0f;
                globals::visuals::InnerEdgeG_Visible = 0.27f;
                globals::visuals::InnerEdgeB_Visible = 1.0f;
                globals::visuals::OuterEdgeR_Visible = 0.0f;
                globals::visuals::OuterEdgeG_Visible = 0.0f;
                globals::visuals::OuterEdgeB_Visible = 0.0f;
            }
            else if (globals::visuals::visiblepreset == 1)
            {
                globals::visuals::CenterEdgeR_Visible = 0.0f;
                globals::visuals::CenterEdgeG_Visible = 0.4f;
                globals::visuals::CenterEdgeB_Visible = 0.2f;
                globals::visuals::InnerEdgeR_Visible = 0.0f;
                globals::visuals::InnerEdgeG_Visible = 0.7f;
                globals::visuals::InnerEdgeB_Visible = 0.3f;
                globals::visuals::OuterEdgeR_Visible = 0.1f;
                globals::visuals::OuterEdgeG_Visible = 1.0f;
                globals::visuals::OuterEdgeB_Visible = 0.4f;
            }
            else if (globals::visuals::visiblepreset == 2)
            {
                globals::visuals::CenterEdgeR_Visible = 0.0f;
                globals::visuals::CenterEdgeG_Visible = 0.8f;
                globals::visuals::CenterEdgeB_Visible = 1.0f;
                globals::visuals::InnerEdgeR_Visible = 0.0f;
                globals::visuals::InnerEdgeG_Visible = 0.6f;
                globals::visuals::InnerEdgeB_Visible = 1.0f;
                globals::visuals::OuterEdgeR_Visible = 0.1f;
                globals::visuals::OuterEdgeG_Visible = 1.0f;
                globals::visuals::OuterEdgeB_Visible = 1.0f;
            }
            else if (globals::visuals::visiblepreset == 3)
            {
                globals::visuals::CenterEdgeR_Visible = 0.6f;
                globals::visuals::CenterEdgeG_Visible = 0.5f;
                globals::visuals::CenterEdgeB_Visible = 0.0f;
                globals::visuals::InnerEdgeR_Visible = 0.9f;
                globals::visuals::InnerEdgeG_Visible = 0.8f;
                globals::visuals::InnerEdgeB_Visible = 0.2f;
                globals::visuals::OuterEdgeR_Visible = 1.0f;
                globals::visuals::OuterEdgeG_Visible = 1.0f;
                globals::visuals::OuterEdgeB_Visible = 0.4f;
            }
            else if (globals::visuals::visiblepreset == 4)
            {
                globals::visuals::CenterEdgeR_Visible = 0.4f;
                globals::visuals::CenterEdgeG_Visible = 0.0f;
                globals::visuals::CenterEdgeB_Visible = 0.6f;
                globals::visuals::InnerEdgeR_Visible = 0.6f;
                globals::visuals::InnerEdgeG_Visible = 0.2f;
                globals::visuals::InnerEdgeB_Visible = 1.0f;
                globals::visuals::OuterEdgeR_Visible = 0.9f;
                globals::visuals::OuterEdgeG_Visible = 0.3f;
                globals::visuals::OuterEdgeB_Visible = 1.0f;
            }
            else if (globals::visuals::visiblepreset == 5) // Ghost White
            {
                globals::visuals::CenterEdgeR_Visible = 0.7f;
                globals::visuals::CenterEdgeG_Visible = 0.7f;
                globals::visuals::CenterEdgeB_Visible = 0.7f;
                globals::visuals::InnerEdgeR_Visible = 0.9f;
                globals::visuals::InnerEdgeG_Visible = 0.9f;
                globals::visuals::InnerEdgeB_Visible = 0.9f;
                globals::visuals::OuterEdgeR_Visible = 1.0f;
                globals::visuals::OuterEdgeG_Visible = 1.0f;
                globals::visuals::OuterEdgeB_Visible = 1.0f;
            }
            else if (globals::visuals::visiblepreset == 6)
            {
                globals::visuals::CenterEdgeR_Visible = 0.2f;
                globals::visuals::CenterEdgeG_Visible = 0.4f;
                globals::visuals::CenterEdgeB_Visible = 0.8f;
                globals::visuals::InnerEdgeR_Visible = 0.4f;
                globals::visuals::InnerEdgeG_Visible = 0.6f;
                globals::visuals::InnerEdgeB_Visible = 0.9f;
                globals::visuals::OuterEdgeR_Visible = 0.6f;
                globals::visuals::OuterEdgeG_Visible = 0.8f;
                globals::visuals::OuterEdgeB_Visible = 1.0f;
            }
            else if (globals::visuals::visiblepreset == 7)
            {
                globals::visuals::CenterEdgeR_Visible = 1.0f;
                globals::visuals::CenterEdgeG_Visible = 0.3f;
                globals::visuals::CenterEdgeB_Visible = 0.0f;
                globals::visuals::InnerEdgeR_Visible = 1.0f;
                globals::visuals::InnerEdgeG_Visible = 0.5f;
                globals::visuals::InnerEdgeB_Visible = 0.1f;
                globals::visuals::OuterEdgeR_Visible = 1.0f;
                globals::visuals::OuterEdgeG_Visible = 0.7f;
                globals::visuals::OuterEdgeB_Visible = 0.2f;
            }
            else if (globals::visuals::visiblepreset == 8)
            {
                globals::visuals::CenterEdgeR_Visible = 0.6f;
                globals::visuals::CenterEdgeG_Visible = 0.6f;
                globals::visuals::CenterEdgeB_Visible = 0.9f;
                globals::visuals::InnerEdgeR_Visible = 0.7f;
                globals::visuals::InnerEdgeG_Visible = 0.7f;
                globals::visuals::InnerEdgeB_Visible = 1.0f;
                globals::visuals::OuterEdgeR_Visible = 0.9f;
                globals::visuals::OuterEdgeG_Visible = 0.9f;
                globals::visuals::OuterEdgeB_Visible = 1.0f;
            }
            else if (globals::visuals::visiblepreset == 9)
            {
                globals::visuals::CenterEdgeR_Visible = 0.6f;
                globals::visuals::CenterEdgeG_Visible = 0.2f;
                globals::visuals::CenterEdgeB_Visible = 0.6f;
                globals::visuals::InnerEdgeR_Visible = 0.8f;
                globals::visuals::InnerEdgeG_Visible = 0.4f;
                globals::visuals::InnerEdgeB_Visible = 0.9f;
                globals::visuals::OuterEdgeR_Visible = 1.0f;
                globals::visuals::OuterEdgeG_Visible = 0.6f;
                globals::visuals::OuterEdgeB_Visible = 1.0f;
            }
            else if (globals::visuals::visiblepreset == 10)
            {
                globals::visuals::CenterEdgeR_Visible = 0.0f;
                globals::visuals::CenterEdgeG_Visible = 0.9f;
                globals::visuals::CenterEdgeB_Visible = 1.0f;
                globals::visuals::InnerEdgeR_Visible = 0.2f;
                globals::visuals::InnerEdgeG_Visible = 1.0f;
                globals::visuals::InnerEdgeB_Visible = 1.0f;
                globals::visuals::OuterEdgeR_Visible = 0.6f;
                globals::visuals::OuterEdgeG_Visible = 1.0f;
                globals::visuals::OuterEdgeB_Visible = 1.0f;
            }
            else if (globals::visuals::visiblepreset == 11)
            {
                globals::visuals::CenterEdgeR_Visible = 1.0f;
                globals::visuals::CenterEdgeG_Visible = 0.2f;
                globals::visuals::CenterEdgeB_Visible = 0.0f;
                globals::visuals::InnerEdgeR_Visible = 1.0f;
                globals::visuals::InnerEdgeG_Visible = 0.4f;
                globals::visuals::InnerEdgeB_Visible = 0.1f;
                globals::visuals::OuterEdgeR_Visible = 1.0f;
                globals::visuals::OuterEdgeG_Visible = 0.6f;
                globals::visuals::OuterEdgeB_Visible = 0.2f;
            }
            else if (globals::visuals::visiblepreset == 12)
            {
                globals::visuals::CenterEdgeR_Visible = 0.0f;
                globals::visuals::CenterEdgeG_Visible = 0.3f;
                globals::visuals::CenterEdgeB_Visible = 0.5f;
                globals::visuals::InnerEdgeR_Visible = 0.0f;
                globals::visuals::InnerEdgeG_Visible = 0.5f;
                globals::visuals::InnerEdgeB_Visible = 0.7f;
                globals::visuals::OuterEdgeR_Visible = 0.0f;
                globals::visuals::OuterEdgeG_Visible = 0.8f;
                globals::visuals::OuterEdgeB_Visible = 1.0f;
            }
            else if (globals::visuals::visiblepreset == 13)
            {
                globals::visuals::CenterEdgeR_Visible = 0.5f;
                globals::visuals::CenterEdgeG_Visible = 0.8f;
                globals::visuals::CenterEdgeB_Visible = 1.0f;
                globals::visuals::InnerEdgeR_Visible = 0.7f;
                globals::visuals::InnerEdgeG_Visible = 0.9f;
                globals::visuals::InnerEdgeB_Visible = 1.0f;
                globals::visuals::OuterEdgeR_Visible = 1.0f;
                globals::visuals::OuterEdgeG_Visible = 1.0f;
                globals::visuals::OuterEdgeB_Visible = 1.0f;
            }
            else if (globals::visuals::visiblepreset == 14)
            {
                globals::visuals::CenterEdgeR_Visible = 1.0f;
                globals::visuals::CenterEdgeG_Visible = 0.2f;
                globals::visuals::CenterEdgeB_Visible = 0.0f;
                globals::visuals::InnerEdgeR_Visible = 1.0f;
                globals::visuals::InnerEdgeG_Visible = 0.5f;
                globals::visuals::InnerEdgeB_Visible = 0.2f;
                globals::visuals::OuterEdgeR_Visible = 1.0f;
                globals::visuals::OuterEdgeG_Visible = 0.8f;
                globals::visuals::OuterEdgeB_Visible = 0.4f;
            }
            else if (globals::visuals::visiblepreset == 15)
            {
                globals::visuals::CenterEdgeR_Visible = 0.0f;
                globals::visuals::CenterEdgeG_Visible = 0.41f;
                globals::visuals::CenterEdgeB_Visible = 0.30f;
                globals::visuals::InnerEdgeR_Visible = 1.0f;
                globals::visuals::InnerEdgeG_Visible = 0.3f;
                globals::visuals::InnerEdgeB_Visible = 0.9f;
                globals::visuals::OuterEdgeR_Visible = 0.1f;
                globals::visuals::OuterEdgeG_Visible = 0.29f;
                globals::visuals::OuterEdgeB_Visible = 0.25f;
            }


            if (globals::visuals::invisiblepreset == 0)
            {
                globals::visuals::CenterEdgeR_Invisible = 0.01f;
                globals::visuals::CenterEdgeG_Invisible = 0.0f;
                globals::visuals::CenterEdgeB_Invisible = 0.0f;
                globals::visuals::InnerEdgeR_Invisible = 0.1f;
                globals::visuals::InnerEdgeG_Invisible = 0.0f;
                globals::visuals::InnerEdgeB_Invisible = 0.0f;
                globals::visuals::OuterEdgeR_Invisible = 1.0f;
                globals::visuals::OuterEdgeG_Invisible = 0.0f;
                globals::visuals::OuterEdgeB_Invisible = 0.0f;
            }
            else if (globals::visuals::invisiblepreset == 1)
            {
                globals::visuals::CenterEdgeR_Invisible = 0.6f;
                globals::visuals::CenterEdgeG_Invisible = 0.1f;
                globals::visuals::CenterEdgeB_Invisible = 0.0f;
                globals::visuals::InnerEdgeR_Invisible = 0.8f;
                globals::visuals::InnerEdgeG_Invisible = 0.2f;
                globals::visuals::InnerEdgeB_Invisible = 0.0f;
                globals::visuals::OuterEdgeR_Invisible = 1.0f;
                globals::visuals::OuterEdgeG_Invisible = 0.3f;
                globals::visuals::OuterEdgeB_Invisible = 0.0f;
            }
            else if (globals::visuals::invisiblepreset == 2)
            {
                globals::visuals::CenterEdgeR_Invisible = 0.4f;
                globals::visuals::CenterEdgeG_Invisible = 0.0f;
                globals::visuals::CenterEdgeB_Invisible = 0.4f;
                globals::visuals::InnerEdgeR_Invisible = 0.6f;
                globals::visuals::InnerEdgeG_Invisible = 0.0f;
                globals::visuals::InnerEdgeB_Invisible = 0.7f;
                globals::visuals::OuterEdgeR_Invisible = 1.0f;
                globals::visuals::OuterEdgeG_Invisible = 0.0f;
                globals::visuals::OuterEdgeB_Invisible = 1.0f;
            }
            else if (globals::visuals::invisiblepreset == 3)
            {
                globals::visuals::CenterEdgeR_Invisible = 0.2f;
                globals::visuals::CenterEdgeG_Invisible = 0.0f;
                globals::visuals::CenterEdgeB_Invisible = 0.5f;
                globals::visuals::InnerEdgeR_Invisible = 0.3f;
                globals::visuals::InnerEdgeG_Invisible = 0.0f;
                globals::visuals::InnerEdgeB_Invisible = 0.9f;
                globals::visuals::OuterEdgeR_Invisible = 0.6f;
                globals::visuals::OuterEdgeG_Invisible = 0.0f;
                globals::visuals::OuterEdgeB_Invisible = 1.0f;
            }
            else if (globals::visuals::invisiblepreset == 4)
            {
                globals::visuals::CenterEdgeR_Invisible = 0.0f;
                globals::visuals::CenterEdgeG_Invisible = 0.3f;
                globals::visuals::CenterEdgeB_Invisible = 0.6f;
                globals::visuals::InnerEdgeR_Invisible = 0.0f;
                globals::visuals::InnerEdgeG_Invisible = 0.6f;
                globals::visuals::InnerEdgeB_Invisible = 1.0f;
                globals::visuals::OuterEdgeR_Invisible = 0.3f;
                globals::visuals::OuterEdgeG_Invisible = 1.0f;
                globals::visuals::OuterEdgeB_Invisible = 1.0f;
            }
            else if (globals::visuals::invisiblepreset == 5)
            {
                globals::visuals::CenterEdgeR_Invisible = 0.2f;
                globals::visuals::CenterEdgeG_Invisible = 0.6f;
                globals::visuals::CenterEdgeB_Invisible = 0.2f;
                globals::visuals::InnerEdgeR_Invisible = 0.4f;
                globals::visuals::InnerEdgeG_Invisible = 0.3f;
                globals::visuals::InnerEdgeB_Invisible = 0.3f;
                globals::visuals::OuterEdgeR_Invisible = 0.8f;
                globals::visuals::OuterEdgeG_Invisible = 0.2f;
                globals::visuals::OuterEdgeB_Invisible = 0.4f;
            }
            else if (globals::visuals::invisiblepreset == 6)
            {
                globals::visuals::CenterEdgeR_Invisible = 0.3f;
                globals::visuals::CenterEdgeG_Invisible = 0.0f;
                globals::visuals::CenterEdgeB_Invisible = 0.0f;
                globals::visuals::InnerEdgeR_Invisible = 0.6f;
                globals::visuals::InnerEdgeG_Invisible = 0.0f;
                globals::visuals::InnerEdgeB_Invisible = 0.0f;
                globals::visuals::OuterEdgeR_Invisible = 1.0f;
                globals::visuals::OuterEdgeG_Invisible = 0.0f;
                globals::visuals::OuterEdgeB_Invisible = 0.1f;
            }
            else if (globals::visuals::invisiblepreset == 7)
            {
                globals::visuals::CenterEdgeR_Invisible = 0.2f;
                globals::visuals::CenterEdgeG_Invisible = 0.2f;
                globals::visuals::CenterEdgeB_Invisible = 0.5f;
                globals::visuals::InnerEdgeR_Invisible = 0.3f;
                globals::visuals::InnerEdgeG_Invisible = 0.3f;
                globals::visuals::InnerEdgeB_Invisible = 0.7f;
                globals::visuals::OuterEdgeR_Invisible = 0.5f;
                globals::visuals::OuterEdgeG_Invisible = 0.5f;
                globals::visuals::OuterEdgeB_Invisible = 1.0f;
            }
            else if (globals::visuals::invisiblepreset == 8)
            {
                globals::visuals::CenterEdgeR_Invisible = 0.5f;
                globals::visuals::CenterEdgeG_Invisible = 0.2f;
                globals::visuals::CenterEdgeB_Invisible = 0.0f;
                globals::visuals::InnerEdgeR_Invisible = 0.7f;
                globals::visuals::InnerEdgeG_Invisible = 0.3f;
                globals::visuals::InnerEdgeB_Invisible = 0.0f;
                globals::visuals::OuterEdgeR_Invisible = 1.0f;
                globals::visuals::OuterEdgeG_Invisible = 0.5f;
                globals::visuals::OuterEdgeB_Invisible = 0.2f;
            }
            else if (globals::visuals::invisiblepreset == 9)
            {
                globals::visuals::CenterEdgeR_Invisible = 0.0f;
                globals::visuals::CenterEdgeG_Invisible = 0.3f;
                globals::visuals::CenterEdgeB_Invisible = 0.5f;
                globals::visuals::InnerEdgeR_Invisible = 0.0f;
                globals::visuals::InnerEdgeG_Invisible = 0.6f;
                globals::visuals::InnerEdgeB_Invisible = 0.9f;
                globals::visuals::OuterEdgeR_Invisible = 0.0f;
                globals::visuals::OuterEdgeG_Invisible = 0.9f;
                globals::visuals::OuterEdgeB_Invisible = 1.0f;
            }
            else if (globals::visuals::invisiblepreset == 10)
            {
                globals::visuals::CenterEdgeR_Invisible = 0.4f;
                globals::visuals::CenterEdgeG_Invisible = 0.1f;
                globals::visuals::CenterEdgeB_Invisible = 0.5f;
                globals::visuals::InnerEdgeR_Invisible = 0.6f;
                globals::visuals::InnerEdgeG_Invisible = 0.2f;
                globals::visuals::InnerEdgeB_Invisible = 0.8f;
                globals::visuals::OuterEdgeR_Invisible = 0.9f;
                globals::visuals::OuterEdgeG_Invisible = 0.4f;
                globals::visuals::OuterEdgeB_Invisible = 1.0f;
            }
            else if (globals::visuals::invisiblepreset == 11)
            {
                globals::visuals::CenterEdgeR_Invisible = 0.5f;
                globals::visuals::CenterEdgeG_Invisible = 0.5f;
                globals::visuals::CenterEdgeB_Invisible = 0.6f;
                globals::visuals::InnerEdgeR_Invisible = 0.7f;
                globals::visuals::InnerEdgeG_Invisible = 0.7f;
                globals::visuals::InnerEdgeB_Invisible = 0.9f;
                globals::visuals::OuterEdgeR_Invisible = 0.9f;
                globals::visuals::OuterEdgeG_Invisible = 0.9f;
                globals::visuals::OuterEdgeB_Invisible = 1.0f;
            }
            else if (globals::visuals::invisiblepreset == 12)
            {
                globals::visuals::CenterEdgeR_Invisible = 0.2f;
                globals::visuals::CenterEdgeG_Invisible = 0.0f;
                globals::visuals::CenterEdgeB_Invisible = 0.4f;
                globals::visuals::InnerEdgeR_Invisible = 0.3f;
                globals::visuals::InnerEdgeG_Invisible = 0.0f;
                globals::visuals::InnerEdgeB_Invisible = 0.7f;
                globals::visuals::OuterEdgeR_Invisible = 0.5f;
                globals::visuals::OuterEdgeG_Invisible = 0.0f;
                globals::visuals::OuterEdgeB_Invisible = 1.0f;
            }
            else if (globals::visuals::invisiblepreset == 13)
            {
                globals::visuals::CenterEdgeR_Invisible = 0.3f;
                globals::visuals::CenterEdgeG_Invisible = 0.3f;
                globals::visuals::CenterEdgeB_Invisible = 0.3f;
                globals::visuals::InnerEdgeR_Invisible = 0.6f;
                globals::visuals::InnerEdgeG_Invisible = 0.6f;
                globals::visuals::InnerEdgeB_Invisible = 0.6f;
                globals::visuals::OuterEdgeR_Invisible = 0.9f;
                globals::visuals::OuterEdgeG_Invisible = 0.9f;
                globals::visuals::OuterEdgeB_Invisible = 0.9f;
            }
            else if (globals::visuals::invisiblepreset == 14)
            {
                globals::visuals::CenterEdgeR_Invisible = 0.1f;
                globals::visuals::CenterEdgeG_Invisible = 0.6f;
                globals::visuals::CenterEdgeB_Invisible = 0.3f;
                globals::visuals::InnerEdgeR_Invisible = 0.3f;
                globals::visuals::InnerEdgeG_Invisible = 0.8f;
                globals::visuals::InnerEdgeB_Invisible = 0.5f;
                globals::visuals::OuterEdgeR_Invisible = 0.5f;
                globals::visuals::OuterEdgeG_Invisible = 1.0f;
                globals::visuals::OuterEdgeB_Invisible = 0.7f;
            }
        }


        if (globals::visuals::outlinetype == 2) return;


        auto is_visible = controllers->line_of_sight(actor);


        if (globals::visuals::outlinetype == 1 && is_visible) {
            auto main_mesh = actor->get_mesh();
            if (main_mesh) {
                actor->reset_character_materials_internal(main_mesh);
            }
            uskeletalmeshcomponent* mesh_cosmetic_3p = actor->GetCosmeticMesh3P();
            if (mesh_cosmetic_3p) {
                actor->reset_character_materials_internal(mesh_cosmetic_3p);
            }
            return;
        }

        float glowIntensity;
        flinearcolor centerEdgeColor, innerEdgeColor, outerEdgeColor;


        if (is_visible) {

            centerEdgeColor = flinearcolor(globals::visuals::CenterEdgeR_Visible, globals::visuals::CenterEdgeG_Visible, globals::visuals::CenterEdgeB_Visible, globals::visuals::outlineintensityvisibleoutline);
            innerEdgeColor = flinearcolor(globals::visuals::InnerEdgeR_Visible, globals::visuals::InnerEdgeG_Visible, globals::visuals::InnerEdgeB_Visible, globals::visuals::outlineintensityvisibleoutline);
            outerEdgeColor = flinearcolor(globals::visuals::OuterEdgeR_Visible, globals::visuals::OuterEdgeG_Visible, globals::visuals::OuterEdgeB_Visible, globals::visuals::outlineintensityvisibleoutline);
            glowIntensity = globals::visuals::GlowVisible;
        }
        else {

            centerEdgeColor = flinearcolor(globals::visuals::CenterEdgeR_Invisible, globals::visuals::CenterEdgeG_Invisible, globals::visuals::CenterEdgeB_Invisible, globals::visuals::outlineintensityinvisbleoutline);
            innerEdgeColor = flinearcolor(globals::visuals::InnerEdgeR_Invisible, globals::visuals::InnerEdgeG_Invisible, globals::visuals::InnerEdgeB_Invisible, globals::visuals::outlineintensityinvisbleoutline);
            outerEdgeColor = flinearcolor(globals::visuals::OuterEdgeR_Invisible, globals::visuals::OuterEdgeG_Invisible, globals::visuals::OuterEdgeB_Invisible, globals::visuals::outlineintensityinvisbleoutline);
            glowIntensity = globals::visuals::GlowInvisible;
        }

        static fname silohuette_color_name, center_edge_color_name, inner_edge_color_name, outer_edge_color_name, glow_intensity_param;
        if (!silohuette_color_name.comparison_index) {
            silohuette_color_name = string::string_to_name(L"SilohuetteColor");
            center_edge_color_name = string::string_to_name(L"CenterEdgeColor");
            inner_edge_color_name = string::string_to_name(L"InnerEdgeColor");
            outer_edge_color_name = string::string_to_name(L"OuterEdgeColor");
            glow_intensity_param = string::string_to_name(L"GlowIntensity");
        }

        uobject* visible_material = uobject::static_load_object(nullptr, nullptr, L"/Game/Characters/BountyHunter/S0/VFX/Materials/BountyHunterReveal_MI.BountyHunterReveal_MI");
        uobject* invisible_material = uobject::static_load_object(nullptr, nullptr, L"/Game/VFX/Materials/HunterReveal_MI.HunterReveal_MI");

        if (!visible_material || !invisible_material) return;

        auto main_mesh = actor->get_mesh();
        if (main_mesh) {
            auto num_materials = main_mesh->get_num_materials();
            for (int i = 0; i < num_materials; i++) {
                auto material_instance_dynamic = main_mesh->create_and_set_material_instance_dynamic_from_material(i, is_visible ? visible_material : invisible_material);
                auto dynCast = material_instance_dynamic->cast<UMaterialInstanceDynamic>();
                if (!dynCast) continue;

                dynCast->set_vector_parameter_value1(silohuette_color_name, outerEdgeColor);
                dynCast->set_vector_parameter_value1(center_edge_color_name, centerEdgeColor);
                dynCast->set_vector_parameter_value1(inner_edge_color_name, innerEdgeColor);
                dynCast->set_vector_parameter_value1(outer_edge_color_name, outerEdgeColor);
                dynCast->set_scalar_parameter_value(glow_intensity_param, glowIntensity);
            }
        }

        uskeletalmeshcomponent* mesh_cosmetic_3p = actor->GetCosmeticMesh3P();
        if (mesh_cosmetic_3p) {
            auto num_materials = mesh_cosmetic_3p->get_num_materials();
            for (int i = 0; i < num_materials; i++) {
                auto material_instance_dynamic = mesh_cosmetic_3p->create_and_set_material_instance_dynamic_from_material(i, is_visible ? visible_material : invisible_material);
                auto dynCast = material_instance_dynamic->cast<UMaterialInstanceDynamic>();
                if (!dynCast) continue;

                dynCast->set_vector_parameter_value1(silohuette_color_name, outerEdgeColor);
                dynCast->set_vector_parameter_value1(center_edge_color_name, centerEdgeColor);
                dynCast->set_vector_parameter_value1(inner_edge_color_name, innerEdgeColor);
                dynCast->set_vector_parameter_value1(outer_edge_color_name, outerEdgeColor);
                dynCast->set_scalar_parameter_value(glow_intensity_param, glowIntensity);
            }
        }
    }



    //void apply_outline_chams(acknowledgedpawn* pawn, ashootercharacter* actor, aplayercontroller* controllers, ashootercharacter* local_player)
    //{
    //    if (!pawn || !actor || !character || !controllers || !local_player) return;
    //
    //    // Frame limiter'ı KALDIR (test için)
    //    // static int frame_counter = 0;
    //    // frame_counter++;
    //    // if (frame_counter % 2 != 0) return;
    //
    //    // Preset renkleri uygula
    //    if (globals::visuals::usepresetedoutlines)
    //    {
    //        // VISIBLE PRESETS - tümünü ekle
    //        if (globals::visuals::visiblepreset == 0) // Default Green
    //        {
    //            globals::visuals::CenterEdgeR_Visible = 0.0f;
    //            globals::visuals::CenterEdgeG_Visible = 0.01f;
    //            globals::visuals::CenterEdgeB_Visible = 0.0f;
    //            globals::visuals::InnerEdgeR_Visible = 0.0f;
    //            globals::visuals::InnerEdgeG_Visible = 0.1f;
    //            globals::visuals::InnerEdgeB_Visible = 0.0f;
    //            globals::visuals::OuterEdgeR_Visible = 0.0f;
    //            globals::visuals::OuterEdgeG_Visible = 1.0f;
    //            globals::visuals::OuterEdgeB_Visible = 0.0f;
    //        }
    //        // ... diğer presetleri ekle
    //        else if (globals::visuals::visiblepreset == 15) // Galaxy Chams
    //        {
    //            globals::visuals::CenterEdgeR_Visible = 0.53f;
    //            globals::visuals::CenterEdgeG_Visible = 0.27f;
    //            globals::visuals::CenterEdgeB_Visible = 0.30f;
    //            globals::visuals::InnerEdgeR_Visible = 0.0f;
    //            globals::visuals::InnerEdgeG_Visible = 0.27f;
    //            globals::visuals::InnerEdgeB_Visible = 1.0f;
    //            globals::visuals::OuterEdgeR_Visible = 0.0f;
    //            globals::visuals::OuterEdgeG_Visible = 0.0f;
    //            globals::visuals::OuterEdgeB_Visible = 0.0f;
    //        }
    //    }
    //
    //    // Outline type kontrolü
    //    if (globals::visuals::outlinetype == 2) return;
    //
    //    // DÜŞMAN için visibility kontrolü
    //    auto is_visible = controllers->line_of_sight(actor);
    //
    //    if (globals::visuals::outlinetype == 1 && is_visible) {
    //        // Reset kodu
    //        auto main_mesh = actor->get_mesh();
    //        if (main_mesh) {
    //            actor->reset_character_materials_internal(main_mesh);
    //        }
    //        uskeletalmeshcomponent* mesh_cosmetic_3p = actor->GetCosmeticMesh3P();
    //        if (mesh_cosmetic_3p) {
    //            actor->reset_character_materials_internal(mesh_cosmetic_3p);
    //        }
    //        return;
    //    }
    //
    //    // Renkleri hazırla
    //    float glowIntensity;
    //    flinearcolor centerEdgeColor, innerEdgeColor, outerEdgeColor;
    //
    //    if (is_visible) {
    //        centerEdgeColor = flinearcolor(globals::visuals::CenterEdgeR_Visible, globals::visuals::CenterEdgeG_Visible, globals::visuals::CenterEdgeB_Visible, globals::visuals::intensityvisibleoutline);
    //        innerEdgeColor = flinearcolor(globals::visuals::InnerEdgeR_Visible, globals::visuals::InnerEdgeG_Visible, globals::visuals::InnerEdgeB_Visible, globals::visuals::intensityvisibleoutline);
    //        outerEdgeColor = flinearcolor(globals::visuals::OuterEdgeR_Visible, globals::visuals::OuterEdgeG_Visible, globals::visuals::OuterEdgeB_Visible, globals::visuals::intensityvisibleoutline);
    //        glowIntensity = globals::visuals::GlowVisible;
    //    }
    //    else {
    //        centerEdgeColor = flinearcolor(globals::visuals::CenterEdgeR_Invisible, globals::visuals::CenterEdgeG_Invisible, globals::visuals::CenterEdgeB_Invisible, globals::visuals::intensityinvisbleoutline);
    //        innerEdgeColor = flinearcolor(globals::visuals::InnerEdgeR_Invisible, globals::visuals::InnerEdgeG_Invisible, globals::visuals::InnerEdgeB_Invisible, globals::visuals::intensityinvisbleoutline);
    //        outerEdgeColor = flinearcolor(globals::visuals::OuterEdgeR_Invisible, globals::visuals::OuterEdgeG_Invisible, globals::visuals::OuterEdgeB_Invisible, globals::visuals::intensityinvisbleoutline);
    //        glowIntensity = globals::visuals::GlowInvisible;
    //    }
    //
    //    // SELF için SADECE VISIBLE renkleri
    //    flinearcolor self_centerEdgeColor = flinearcolor(globals::visuals::CenterEdgeR_Visible, globals::visuals::CenterEdgeG_Visible, globals::visuals::CenterEdgeB_Visible, globals::visuals::intensityvisibleoutline);
    //    flinearcolor self_innerEdgeColor = flinearcolor(globals::visuals::InnerEdgeR_Visible, globals::visuals::InnerEdgeG_Visible, globals::visuals::InnerEdgeB_Visible, globals::visuals::intensityvisibleoutline);
    //    flinearcolor self_outerEdgeColor = flinearcolor(globals::visuals::OuterEdgeR_Visible, globals::visuals::OuterEdgeG_Visible, globals::visuals::OuterEdgeB_Visible, globals::visuals::intensityvisibleoutline);
    //    float self_glowIntensity = globals::visuals::GlowVisible;
    //
    //    // Material yükle
    //    static uobject* visible_material = uobject::static_load_object(nullptr, nullptr, L"/Game/Characters/BountyHunter/S0/VFX/Materials/BountyHunterReveal_MI.BountyHunterReveal_MI");
    //    static uobject* invisible_material = uobject::static_load_object(nullptr, nullptr, L"/Game/VFX/Materials/HunterReveal_MI.HunterReveal_MI");
    //
    //    if (!visible_material || !invisible_material) return;
    //
    //    // Parameter isimleri
    //    static fname silohuette_color_name = string::string_to_name(L"SilohuetteColor");
    //    static fname center_edge_color_name = string::string_to_name(L"CenterEdgeColor");
    //    static fname inner_edge_color_name = string::string_to_name(L"InnerEdgeColor");
    //    static fname outer_edge_color_name = string::string_to_name(L"OuterEdgeColor");
    //    static fname glow_intensity_param = string::string_to_name(L"GlowIntensity");
    //
    //    // Karaktere outline uygula
    //    auto apply_to_character = [&](ashootercharacter* character, bool is_self = false) {
    //        if (!character) return;
    //
    //        // SELF ise SADECE visible renkleri kullan
    //        flinearcolor final_center = is_self ? self_centerEdgeColor : centerEdgeColor;
    //        flinearcolor final_inner = is_self ? self_innerEdgeColor : innerEdgeColor;
    //        flinearcolor final_outer = is_self ? self_outerEdgeColor : outerEdgeColor;
    //        float final_glow = is_self ? self_glowIntensity : glowIntensity;
    //        uobject* final_material = is_self ? visible_material : (is_visible ? visible_material : invisible_material);
    //
    //        // Main mesh
    //        auto main_mesh = character->get_mesh();
    //        if (main_mesh) {
    //            auto num_materials = main_mesh->get_num_materials();
    //            for (int i = 0; i < num_materials; i++) {
    //                auto material_instance_dynamic = main_mesh->create_and_set_material_instance_dynamic_from_material(i, final_material);
    //                auto dynCast = material_instance_dynamic->cast<UMaterialInstanceDynamic>();
    //                if (!dynCast) continue;
    //
    //                dynCast->set_vector_parameter_value1(silohuette_color_name, final_outer);
    //                dynCast->set_vector_parameter_value1(center_edge_color_name, final_center);
    //                dynCast->set_vector_parameter_value1(inner_edge_color_name, final_inner);
    //                dynCast->set_vector_parameter_value1(outer_edge_color_name, final_outer);
    //                dynCast->set_scalar_parameter_value(glow_intensity_param, final_glow);
    //            }
    //        }
    //
    //        // Cosmetic mesh
    //        uskeletalmeshcomponent* mesh_cosmetic_3p = character->GetCosmeticMesh3P();
    //        if (mesh_cosmetic_3p) {
    //            auto num_materials = mesh_cosmetic_3p->get_num_materials();
    //            for (int i = 0; i < num_materials; i++) {
    //                auto material_instance_dynamic = mesh_cosmetic_3p->create_and_set_material_instance_dynamic_from_material(i, final_material);
    //                auto dynCast = material_instance_dynamic->cast<UMaterialInstanceDynamic>();
    //                if (!dynCast) continue;
    //
    //                dynCast->set_vector_parameter_value1(silohuette_color_name, final_outer);
    //                dynCast->set_vector_parameter_value1(center_edge_color_name, final_center);
    //                dynCast->set_vector_parameter_value1(inner_edge_color_name, final_inner);
    //                dynCast->set_vector_parameter_value1(outer_edge_color_name, final_outer);
    //                dynCast->set_scalar_parameter_value(glow_intensity_param, final_glow);
    //            }
    //        }
    //        };
    //
    //    // Uygula
    //    apply_to_character(actor, false);      // Düşman
    //    apply_to_character(local_player, true); // Self
    //}

    //void apply_outline_chams(acknowledgedpawn* pawn, ashootercharacter* actor, aplayercontroller* controllers, ashootercharacter* local_player)
    //{
    //    // Hızlı null check
    //    if (!pawn || !actor || !controllers || !local_player)
    //        return;
    //
    //    // FPS için: Sadece gerekli durumlarda çalışsın
    //    static int frame_counter = 0;
    //    frame_counter++;
    //    if (frame_counter % 2 != 0) return;
    //
    //    try
    //    {
    //        // Preset renkleri - sadece değiştiyse uygula
    //        static int last_visible_preset = -1;
    //        static int last_invisible_preset = -1;
    //
    //        if (globals::visuals::usepresetedoutlines)
    //        {
    //            if (last_visible_preset != globals::visuals::visiblepreset ||
    //                last_invisible_preset != globals::visuals::invisiblepreset)
    //            {
    //                // VISIBLE PRESETS
    //                switch (globals::visuals::visiblepreset) {
    //                case 0: // Default Green
    //                    globals::visuals::CenterEdgeR_Visible = 0.0f;
    //                    globals::visuals::CenterEdgeG_Visible = 0.01f;
    //                    globals::visuals::CenterEdgeB_Visible = 0.0f;
    //                    globals::visuals::InnerEdgeR_Visible = 0.0f;
    //                    globals::visuals::InnerEdgeG_Visible = 0.1f;
    //                    globals::visuals::InnerEdgeB_Visible = 0.0f;
    //                    globals::visuals::OuterEdgeR_Visible = 0.0f;
    //                    globals::visuals::OuterEdgeG_Visible = 1.0f;
    //                    globals::visuals::OuterEdgeB_Visible = 0.0f;
    //                    break;
    //                case 1: // Toxic Glow
    //                    globals::visuals::CenterEdgeR_Visible = 0.0f;
    //                    globals::visuals::CenterEdgeG_Visible = 0.4f;
    //                    globals::visuals::CenterEdgeB_Visible = 0.2f;
    //                    globals::visuals::InnerEdgeR_Visible = 0.0f;
    //                    globals::visuals::InnerEdgeG_Visible = 0.7f;
    //                    globals::visuals::InnerEdgeB_Visible = 0.3f;
    //                    globals::visuals::OuterEdgeR_Visible = 0.1f;
    //                    globals::visuals::OuterEdgeG_Visible = 1.0f;
    //                    globals::visuals::OuterEdgeB_Visible = 0.4f;
    //                    break;
    //                case 2: // Neon Ice
    //                    globals::visuals::CenterEdgeR_Visible = 0.0f;
    //                    globals::visuals::CenterEdgeG_Visible = 0.8f;
    //                    globals::visuals::CenterEdgeB_Visible = 1.0f;
    //                    globals::visuals::InnerEdgeR_Visible = 0.0f;
    //                    globals::visuals::InnerEdgeG_Visible = 0.6f;
    //                    globals::visuals::InnerEdgeB_Visible = 1.0f;
    //                    globals::visuals::OuterEdgeR_Visible = 0.1f;
    //                    globals::visuals::OuterEdgeG_Visible = 1.0f;
    //                    globals::visuals::OuterEdgeB_Visible = 1.0f;
    //                    break;
    //                case 3: // Solar Flare
    //                    globals::visuals::CenterEdgeR_Visible = 0.6f;
    //                    globals::visuals::CenterEdgeG_Visible = 0.5f;
    //                    globals::visuals::CenterEdgeB_Visible = 0.0f;
    //                    globals::visuals::InnerEdgeR_Visible = 0.9f;
    //                    globals::visuals::InnerEdgeG_Visible = 0.8f;
    //                    globals::visuals::InnerEdgeB_Visible = 0.2f;
    //                    globals::visuals::OuterEdgeR_Visible = 1.0f;
    //                    globals::visuals::OuterEdgeG_Visible = 1.0f;
    //                    globals::visuals::OuterEdgeB_Visible = 0.4f;
    //                    break;
    //                case 4: // Void Spark
    //                    globals::visuals::CenterEdgeR_Visible = 0.4f;
    //                    globals::visuals::CenterEdgeG_Visible = 0.0f;
    //                    globals::visuals::CenterEdgeB_Visible = 0.6f;
    //                    globals::visuals::InnerEdgeR_Visible = 0.6f;
    //                    globals::visuals::InnerEdgeG_Visible = 0.2f;
    //                    globals::visuals::InnerEdgeB_Visible = 1.0f;
    //                    globals::visuals::OuterEdgeR_Visible = 0.9f;
    //                    globals::visuals::OuterEdgeG_Visible = 0.3f;
    //                    globals::visuals::OuterEdgeB_Visible = 1.0f;
    //                    break;
    //                case 5: // Ghost White
    //                    globals::visuals::CenterEdgeR_Visible = 0.7f;
    //                    globals::visuals::CenterEdgeG_Visible = 0.7f;
    //                    globals::visuals::CenterEdgeB_Visible = 0.7f;
    //                    globals::visuals::InnerEdgeR_Visible = 0.9f;
    //                    globals::visuals::InnerEdgeG_Visible = 0.9f;
    //                    globals::visuals::InnerEdgeB_Visible = 0.9f;
    //                    globals::visuals::OuterEdgeR_Visible = 1.0f;
    //                    globals::visuals::OuterEdgeG_Visible = 1.0f;
    //                    globals::visuals::OuterEdgeB_Visible = 1.0f;
    //                    break;
    //                case 6: // Aurora Dream
    //                    globals::visuals::CenterEdgeR_Visible = 0.2f;
    //                    globals::visuals::CenterEdgeG_Visible = 0.4f;
    //                    globals::visuals::CenterEdgeB_Visible = 0.8f;
    //                    globals::visuals::InnerEdgeR_Visible = 0.4f;
    //                    globals::visuals::InnerEdgeG_Visible = 0.6f;
    //                    globals::visuals::InnerEdgeB_Visible = 0.9f;
    //                    globals::visuals::OuterEdgeR_Visible = 0.6f;
    //                    globals::visuals::OuterEdgeG_Visible = 0.8f;
    //                    globals::visuals::OuterEdgeB_Visible = 1.0f;
    //                    break;
    //                case 7: // Cyber Ember
    //                    globals::visuals::CenterEdgeR_Visible = 1.0f;
    //                    globals::visuals::CenterEdgeG_Visible = 0.3f;
    //                    globals::visuals::CenterEdgeB_Visible = 0.0f;
    //                    globals::visuals::InnerEdgeR_Visible = 1.0f;
    //                    globals::visuals::InnerEdgeG_Visible = 0.5f;
    //                    globals::visuals::InnerEdgeB_Visible = 0.1f;
    //                    globals::visuals::OuterEdgeR_Visible = 1.0f;
    //                    globals::visuals::OuterEdgeG_Visible = 0.7f;
    //                    globals::visuals::OuterEdgeB_Visible = 0.2f;
    //                    break;
    //                case 8: // Lunar Fade
    //                    globals::visuals::CenterEdgeR_Visible = 0.6f;
    //                    globals::visuals::CenterEdgeG_Visible = 0.6f;
    //                    globals::visuals::CenterEdgeB_Visible = 0.9f;
    //                    globals::visuals::InnerEdgeR_Visible = 0.7f;
    //                    globals::visuals::InnerEdgeG_Visible = 0.7f;
    //                    globals::visuals::InnerEdgeB_Visible = 1.0f;
    //                    globals::visuals::OuterEdgeR_Visible = 0.9f;
    //                    globals::visuals::OuterEdgeG_Visible = 0.9f;
    //                    globals::visuals::OuterEdgeB_Visible = 1.0f;
    //                    break;
    //                case 9: // Mystic Flame
    //                    globals::visuals::CenterEdgeR_Visible = 0.6f;
    //                    globals::visuals::CenterEdgeG_Visible = 0.2f;
    //                    globals::visuals::CenterEdgeB_Visible = 0.6f;
    //                    globals::visuals::InnerEdgeR_Visible = 0.8f;
    //                    globals::visuals::InnerEdgeG_Visible = 0.4f;
    //                    globals::visuals::InnerEdgeB_Visible = 0.9f;
    //                    globals::visuals::OuterEdgeR_Visible = 1.0f;
    //                    globals::visuals::OuterEdgeG_Visible = 0.6f;
    //                    globals::visuals::OuterEdgeB_Visible = 1.0f;
    //                    break;
    //                case 10: // Arc Light
    //                    globals::visuals::CenterEdgeR_Visible = 0.0f;
    //                    globals::visuals::CenterEdgeG_Visible = 0.9f;
    //                    globals::visuals::CenterEdgeB_Visible = 1.0f;
    //                    globals::visuals::InnerEdgeR_Visible = 0.2f;
    //                    globals::visuals::InnerEdgeG_Visible = 1.0f;
    //                    globals::visuals::InnerEdgeB_Visible = 1.0f;
    //                    globals::visuals::OuterEdgeR_Visible = 0.6f;
    //                    globals::visuals::OuterEdgeG_Visible = 1.0f;
    //                    globals::visuals::OuterEdgeB_Visible = 1.0f;
    //                    break;
    //                case 11: // Burning Core
    //                    globals::visuals::CenterEdgeR_Visible = 1.0f;
    //                    globals::visuals::CenterEdgeG_Visible = 0.2f;
    //                    globals::visuals::CenterEdgeB_Visible = 0.0f;
    //                    globals::visuals::InnerEdgeR_Visible = 1.0f;
    //                    globals::visuals::InnerEdgeG_Visible = 0.4f;
    //                    globals::visuals::InnerEdgeB_Visible = 0.1f;
    //                    globals::visuals::OuterEdgeR_Visible = 1.0f;
    //                    globals::visuals::OuterEdgeG_Visible = 0.6f;
    //                    globals::visuals::OuterEdgeB_Visible = 0.2f;
    //                    break;
    //                case 12: // Deep Ocean
    //                    globals::visuals::CenterEdgeR_Visible = 0.0f;
    //                    globals::visuals::CenterEdgeG_Visible = 0.3f;
    //                    globals::visuals::CenterEdgeB_Visible = 0.5f;
    //                    globals::visuals::InnerEdgeR_Visible = 0.0f;
    //                    globals::visuals::InnerEdgeG_Visible = 0.5f;
    //                    globals::visuals::InnerEdgeB_Visible = 0.7f;
    //                    globals::visuals::OuterEdgeR_Visible = 0.0f;
    //                    globals::visuals::OuterEdgeG_Visible = 0.8f;
    //                    globals::visuals::OuterEdgeB_Visible = 1.0f;
    //                    break;
    //                case 13: // Crystal Edge
    //                    globals::visuals::CenterEdgeR_Visible = 0.5f;
    //                    globals::visuals::CenterEdgeG_Visible = 0.8f;
    //                    globals::visuals::CenterEdgeB_Visible = 1.0f;
    //                    globals::visuals::InnerEdgeR_Visible = 0.7f;
    //                    globals::visuals::InnerEdgeG_Visible = 0.9f;
    //                    globals::visuals::InnerEdgeB_Visible = 1.0f;
    //                    globals::visuals::OuterEdgeR_Visible = 1.0f;
    //                    globals::visuals::OuterEdgeG_Visible = 1.0f;
    //                    globals::visuals::OuterEdgeB_Visible = 1.0f;
    //                    break;
    //                case 14: // Magma Burn
    //                    globals::visuals::CenterEdgeR_Visible = 1.0f;
    //                    globals::visuals::CenterEdgeG_Visible = 0.2f;
    //                    globals::visuals::CenterEdgeB_Visible = 0.0f;
    //                    globals::visuals::InnerEdgeR_Visible = 1.0f;
    //                    globals::visuals::InnerEdgeG_Visible = 0.5f;
    //                    globals::visuals::InnerEdgeB_Visible = 0.2f;
    //                    globals::visuals::OuterEdgeR_Visible = 1.0f;
    //                    globals::visuals::OuterEdgeG_Visible = 0.8f;
    //                    globals::visuals::OuterEdgeB_Visible = 0.4f;
    //                    break;
    //                case 15: // Galaxy Chams
    //                    globals::visuals::CenterEdgeR_Visible = 0.53f;
    //                    globals::visuals::CenterEdgeG_Visible = 0.27f;
    //                    globals::visuals::CenterEdgeB_Visible = 0.30f;
    //                    globals::visuals::InnerEdgeR_Visible = 0.0f;
    //                    globals::visuals::InnerEdgeG_Visible = 0.27f;
    //                    globals::visuals::InnerEdgeB_Visible = 1.0f;
    //                    globals::visuals::OuterEdgeR_Visible = 0.0f;
    //                    globals::visuals::OuterEdgeG_Visible = 0.0f;
    //                    globals::visuals::OuterEdgeB_Visible = 0.0f;
    //                    break;
    //                }
    //
    //                // INVISIBLE PRESETS (kısaltıyorum)
    //                switch (globals::visuals::invisiblepreset) {
    //                case 0: // Default Red
    //                    globals::visuals::CenterEdgeR_Invisible = 0.01f;
    //                    globals::visuals::CenterEdgeG_Invisible = 0.0f;
    //                    globals::visuals::CenterEdgeB_Invisible = 0.0f;
    //                    globals::visuals::InnerEdgeR_Invisible = 0.1f;
    //                    globals::visuals::InnerEdgeG_Invisible = 0.0f;
    //                    globals::visuals::InnerEdgeB_Invisible = 0.0f;
    //                    globals::visuals::OuterEdgeR_Invisible = 1.0f;
    //                    globals::visuals::OuterEdgeG_Invisible = 0.0f;
    //                    globals::visuals::OuterEdgeB_Invisible = 0.0f;
    //                    break;
    //                    // ... diğer invisible presetler
    //                }
    //
    //                last_visible_preset = globals::visuals::visiblepreset;
    //                last_invisible_preset = globals::visuals::invisiblepreset;
    //            }
    //        }
    //
    //        // ... kalan kod aynen devam edecek (outline type, material, vs.)
    //
    //    }
    //    catch (...) {
    //        return;
    //    }
    //}




    void initialize_materials() {
        SPOOF_FUNC;
        std::lock_guard<std::mutex> lock(materials_mutex);
        if (!materials_initialized)
        {
            hand_materials[0] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Afterglow/LEDs/1P_Afterglow_Emissive_Mat.1P_Afterglow_Emissive_Mat").decrypt());
            hand_materials[1] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Tokyo/1P_Tokyo_Decals_MI.1P_Tokyo_Decals_MI").decrypt());
            hand_materials[2] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Champions2/Emissive/1P_Champions2_Emissive_Lit_MAT.1P_Champions2_Emissive_Lit_MAT").decrypt());
            hand_materials[3] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Champions2/Glass/1P_Champions2_Glass_MAT.1P_Champions2_Glass_MAT").decrypt());
            hand_materials[4] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/VCTCaps24/1P_VCTCaps24_Glass_v1_MAT.1P_VCTCaps24_Glass_v1_MAT").decrypt());
            hand_materials[5] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Lofi/1P_Lofi_MAT.1P_Lofi_MAT").decrypt());
            hand_materials[6] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/ComicBook/1P_ComicBook_Outlines_MI.1P_ComicBook_Outlines_MI").decrypt());
            hand_materials[7] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Atlas/1P_Atlas_Emissive_Lv3_MI_v2.1P_Atlas_Emissive_Lv3_MI_v2").decrypt());
            hand_materials[8] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Atlas/1P_Infinity_Atlas_Triangle_Lv3_MI.1P_Infinity_Atlas_Triangle_Lv3_MI").decrypt());
            hand_materials[9] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Atlas/1P_Atlas_Emissive_Lv3_MI_v3.1P_Atlas_Emissive_Lv3_MI_v3").decrypt());
            hand_materials[10] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Atlas/1P_Atlas_Holographic_Sticker_MI.1P_Atlas_Holographic_Sticker_MI").decrypt());
            hand_materials[11] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Champions2/Outline/1P_Champions2_Outline_Fresnel_MI.1P_Champions2_Outline_Fresnel_MI").decrypt());
            hand_materials[12] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Emissive/1P_Weapon_Emissive_Gem_MI.1P_Weapon_Emissive_Gem_MI").decrypt());
            hand_materials[13] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Fury/1P_Fury_MI.1P_Fury_MI").decrypt());
            hand_materials[14] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Jinju/1P_Jinju_MI.1P_Jinju_MI").decrypt());
            hand_materials[15] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Kingdom2/1P_Kingdom2_Decals_Black_MI.1P_Kingdom2_Decals_Black_MI").decrypt());
            hand_materials[16] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Atlas/1P_Atlas_Glass_MI.1P_Atlas_Glass_MI").decrypt());
            hand_materials[17] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Hieroglyphs/1P_Hieroglyphs_Crystal_MI.1P_Hieroglyphs_Crystal_MI").decrypt());
            hand_materials[18] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Hydrodip/1P_Hydrodip_Tritium_MI.1P_Hydrodip_Tritium_MI").decrypt());
            hand_materials[19] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Analog/1P_Analog_Tritium_MI.1P_Analog_Tritium_MI").decrypt()); // Analog Tritium
            hand_materials[20] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Acrylic/1P_Acrylic_Chroma_v1_Tritium_MI.1P_Acrylic_Chroma_v1_Tritium_MI").decrypt()); // Acrylic Chroma
            hand_materials[21] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Dynasty/Dynasty_Emissive_Gem_1P_MI.Dynasty_Emissive_Gem_1P_MI").decrypt()); // Dynasty Emissive Gem
            hand_materials[22] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Dynasty/Dynasty_Emissive_Gem_1P_v1_MI.Dynasty_Emissive_Gem_1P_v1_MI").decrypt()); // Dynasty Emissive v1
            // 2
            hand_materials[25] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Esportsinvitational/1P_Esportsinvitational_Crystal_Melee_v3_MI.1P_Esportsinvitational_Crystal_Melee_v3_MI").decrypt());
            hand_materials[26] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/InnerRage/1p_InnerRage_Emissive_MI.1p_InnerRage_Emissive_MI").decrypt());
            hand_materials[27] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Ninja/1P_Ninja_Decals_V3_MI.1P_Ninja_Decals_V3_MI").decrypt());
            hand_materials[28] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/OrangeHighlight/1p_OrangeHighlight_Emissive_MI.1p_OrangeHighlight_Emissive_MI").decrypt());
            hand_materials[29] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/OrangeHighlight/1P_OrangeHighlight_PanningEmissive_MI.1P_OrangeHighlight_PanningEmissive_MI").decrypt());
            hand_materials[30] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Melee/RoboMecha/Materials/1p_RoboMecha_Emissive_MI.1p_RoboMecha_Emissive_MI").decrypt());
            hand_materials[31] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/ShaderAnimation/1P_SineWaveVertexMove_MI.1P_SineWaveVertexMove_MI").decrypt());
            hand_materials[32] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Snowglobe/LightGlow/1P_Snowglobe_LightGlow_MI.1P_Snowglobe_LightGlow_MI").decrypt());
            hand_materials[33] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Spirit/1P_Sprit_Emissive_MI.1P_Sprit_Emissive_MI").decrypt());
            hand_materials[34] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/StreetWear/StreetWear_Emissive_v3_1P_MI.StreetWear_Emissive_v3_1P_MI").decrypt());
            hand_materials[35] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Syndra/1P_Syndra_Emissive_Gradient_LUT_MI.1P_Syndra_Emissive_Gradient_LUT_MI").decrypt());
            hand_materials[36] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Stylistic/1p_Weapon_Stylistic_MI.1p_Weapon_Stylistic_MI").decrypt());
            hand_materials[37] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Voyager/1P_Voyager_Ropes_v1_MI.1P_Voyager_Ropes_v1_MI").decrypt());
            hand_materials[38] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Gunslinger/1p_Gunslinger_Emissive_v3_MI.1p_Gunslinger_Emissive_v3_MI").decrypt());
            hand_materials[39] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Demonstone/1P_Demonstone_Decals_v2_MI.1P_Demonstone_Decals_v2_MI").decrypt());
            hand_materials[40] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/IndustrialX/1p_IndustrialX_Emissive_MI.1p_IndustrialX_Emissive_MI").decrypt());
            hand_materials[41] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Esportsinvitational/1P_Esportsinvitational_Crystal_Melee_v1_MI.1P_Esportsinvitational_Crystal_Melee_v1_MI").decrypt());
            hand_materials[42] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Esportsinvitational/1P_Esportsinvitational_Crystal_Melee_v2_MI.1P_Esportsinvitational_Crystal_Melee_v2_MI").decrypt());
            hand_materials[43] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Esportsinvitational/1P_Esportsinvitational_Crystal_Melee_v3_MI.1P_Esportsinvitational_Crystal_Melee_v3_MI").decrypt());
            hand_materials[44] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Esportsinvitational/1P_Esportsinvitational_Crystal_Melee_MI.1P_Esportsinvitational_Crystal_Melee_MI").decrypt());
            hand_materials[45] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Champions2/Outline/1P_Champions2024_Outline_Fresnel_MI.1P_Champions2024_Outline_Fresnel_MI").decrypt());
            hand_materials[46] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Champions2/Outline/1P_Champions2024_Outline_MI.1P_Champions2024_Outline_MI").decrypt());
            hand_materials[47] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Champions2023/1P_Champions2023_Emissive_MAT.1P_Champions2023_Emissive_MAT").decrypt());
            hand_materials[48] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Alien/1P_Alien_Decals_MI.1P_Alien_Decals_MI").decrypt());
            hand_materials[49] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Jellyfish/1P_Jellyfish_Rayplane_MI.1P_Jellyfish_Rayplane_MI").decrypt());
            hand_materials[50] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/CatHeadPhone/1P_CatHeadPhone_Buddy_Idle_Glow_MI.1P_CatHeadPhone_Buddy_Idle_Glow_MI").decrypt());

            gun_materials[0] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Afterglow/LEDs/1P_Afterglow_Emissive_Mat.1P_Afterglow_Emissive_Mat").decrypt());
            gun_materials[1] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Tokyo/1P_Tokyo_Decals_MI.1P_Tokyo_Decals_MI").decrypt());
            gun_materials[2] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Champions2/Emissive/1P_Champions2_Emissive_Lit_MAT.1P_Champions2_Emissive_Lit_MAT").decrypt());
            gun_materials[3] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Champions2/Glass/1P_Champions2_Glass_MAT.1P_Champions2_Glass_MAT").decrypt());
            gun_materials[4] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/VCTCaps24/1P_VCTCaps24_Glass_v1_MAT.1P_VCTCaps24_Glass_v1_MAT").decrypt());
            gun_materials[5] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Lofi/1P_Lofi_MAT.1P_Lofi_MAT").decrypt());
            gun_materials[6] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/ComicBook/1P_ComicBook_Outlines_MI.1P_ComicBook_Outlines_MI").decrypt());
            gun_materials[7] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Atlas/1P_Atlas_Emissive_Lv3_MI_v2.1P_Atlas_Emissive_Lv3_MI_v2").decrypt());
            gun_materials[8] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Atlas/1P_Infinity_Atlas_Triangle_Lv3_MI.1P_Infinity_Atlas_Triangle_Lv3_MI").decrypt());
            gun_materials[9] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Atlas/1P_Atlas_Emissive_Lv3_MI_v3.1P_Atlas_Emissive_Lv3_MI_v3").decrypt());
            gun_materials[10] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Atlas/1P_Atlas_Holographic_Sticker_MI.1P_Atlas_Holographic_Sticker_MI").decrypt());
            gun_materials[11] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Champions2/Outline/1P_Champions2_Outline_Fresnel_MI.1P_Champions2_Outline_Fresnel_MI").decrypt());
            gun_materials[12] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Emissive/1P_Weapon_Emissive_Gem_MI.1P_Weapon_Emissive_Gem_MI").decrypt());
            gun_materials[13] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Fury/1P_Fury_MI.1P_Fury_MI").decrypt());
            gun_materials[14] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Jinju/1P_Jinju_MI.1P_Jinju_MI").decrypt());
            gun_materials[15] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Kingdom2/1P_Kingdom2_Decals_Black_MI.1P_Kingdom2_Decals_Black_MI").decrypt());
            gun_materials[16] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Atlas/1P_Atlas_Glass_MI.1P_Atlas_Glass_MI").decrypt());
            gun_materials[17] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Hieroglyphs/1P_Hieroglyphs_Crystal_MI.1P_Hieroglyphs_Crystal_MI").decrypt());
            gun_materials[18] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Hydrodip/1P_Hydrodip_Tritium_MI.1P_Hydrodip_Tritium_MI").decrypt());
            gun_materials[19] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Hydrodip/1P_Hydrodip_Tritium_MI.1P_Hydrodip_Tritium_MI").decrypt());
            gun_materials[20] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Analog/1P_Analog_Tritium_MI.1P_Analog_Tritium_MI").decrypt());
            gun_materials[21] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Acrylic/1P_Acrylic_Chroma_v1_Tritium_MI.1P_Acrylic_Chroma_v1_Tritium_MI").decrypt());
            gun_materials[22] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Dynasty/Dynasty_Emissive_Gem_1P_MI.Dynasty_Emissive_Gem_1P_MI").decrypt());
            gun_materials[23] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Dynasty/Dynasty_Emissive_Gem_1P_v1_MI.Dynasty_Emissive_Gem_1P_v1_MI").decrypt());
            gun_materials[24] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Dynasty/Dynasty_Emissive_Gem_1P_MI.Dynasty_Emissive_Gem_1P_MI").decrypt());

            // 2
            gun_materials[25] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Esportsinvitational/1P_Esportsinvitational_Crystal_Melee_v3_MI.1P_Esportsinvitational_Crystal_Melee_v3_MI").decrypt());
            gun_materials[26] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/InnerRage/1p_InnerRage_Emissive_MI.1p_InnerRage_Emissive_MI").decrypt());
            gun_materials[27] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Ninja/1P_Ninja_Decals_V3_MI.1P_Ninja_Decals_V3_MI").decrypt());
            gun_materials[28] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/OrangeHighlight/1p_OrangeHighlight_Emissive_MI.1p_OrangeHighlight_Emissive_MI").decrypt());
            gun_materials[29] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/OrangeHighlight/1P_OrangeHighlight_PanningEmissive_MI.1P_OrangeHighlight_PanningEmissive_MI").decrypt());
            gun_materials[30] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Melee/RoboMecha/Materials/1p_RoboMecha_Emissive_MI.1p_RoboMecha_Emissive_MI").decrypt());
            gun_materials[31] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/ShaderAnimation/1P_SineWaveVertexMove_MI.1P_SineWaveVertexMove_MI").decrypt());
            gun_materials[32] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Snowglobe/LightGlow/1P_Snowglobe_LightGlow_MI.1P_Snowglobe_LightGlow_MI").decrypt());
            gun_materials[33] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Spirit/1P_Sprit_Emissive_MI.1P_Sprit_Emissive_MI").decrypt());
            gun_materials[34] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/StreetWear/StreetWear_Emissive_v3_1P_MI.StreetWear_Emissive_v3_1P_MI").decrypt());
            gun_materials[35] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Syndra/1P_Syndra_Emissive_Gradient_LUT_MI.1P_Syndra_Emissive_Gradient_LUT_MI").decrypt());
            gun_materials[36] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Stylistic/1p_Weapon_Stylistic_MI.1p_Weapon_Stylistic_MI").decrypt());
            gun_materials[37] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Voyager/1P_Voyager_Ropes_v1_MI.1P_Voyager_Ropes_v1_MI").decrypt());
            gun_materials[38] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Gunslinger/1p_Gunslinger_Emissive_v3_MI.1p_Gunslinger_Emissive_v3_MI").decrypt());
            gun_materials[39] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Demonstone/1P_Demonstone_Decals_v2_MI.1P_Demonstone_Decals_v2_MI").decrypt());
            gun_materials[40] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/IndustrialX/1p_IndustrialX_Emissive_MI.1p_IndustrialX_Emissive_MI").decrypt());
            gun_materials[41] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Esportsinvitational/1P_Esportsinvitational_Crystal_Melee_v1_MI.1P_Esportsinvitational_Crystal_Melee_v1_MI").decrypt());
            gun_materials[42] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Esportsinvitational/1P_Esportsinvitational_Crystal_Melee_v2_MI.1P_Esportsinvitational_Crystal_Melee_v2_MI").decrypt());
            gun_materials[43] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Esportsinvitational/1P_Esportsinvitational_Crystal_Melee_v3_MI.1P_Esportsinvitational_Crystal_Melee_v3_MI").decrypt());
            gun_materials[44] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Esportsinvitational/1P_Esportsinvitational_Crystal_Melee_MI.1P_Esportsinvitational_Crystal_Melee_MI").decrypt());
            gun_materials[45] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Champions2/Outline/1P_Champions2024_Outline_Fresnel_MI.1P_Champions2024_Outline_Fresnel_MI").decrypt());
            gun_materials[46] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Champions2/Outline/1P_Champions2024_Outline_MI.1P_Champions2024_Outline_MI").decrypt());
            gun_materials[47] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Champions2023/1P_Champions2023_Emissive_MAT.1P_Champions2023_Emissive_MAT").decrypt());
            gun_materials[48] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Alien/1P_Alien_Decals_MI.1P_Alien_Decals_MI").decrypt());
            gun_materials[49] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Jellyfish/1P_Jellyfish_Rayplane_MI.1P_Jellyfish_Rayplane_MI").decrypt());
            gun_materials[50] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/CatHeadPhone/1P_CatHeadPhone_Buddy_Idle_Glow_MI.1P_CatHeadPhone_Buddy_Idle_Glow_MI").decrypt());

            c_ctm[0] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Airplane/Models/GN_AK_Airplane_Lv1_Skelmesh.GN_AK_Airplane_Lv1_Skelmesh").decrypt()));
            c_ctm[1] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/MonkeyKing/Models/GN_AK_MonkeyKing_Lv3_Skelmesh.GN_AK_MonkeyKing_Lv3_Skelmesh").decrypt()));
            c_ctm[2] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/IndustrialX/Models/GN_AK_IndustrialX_Lv1_Skelmesh.GN_AK_IndustrialX_Lv1_Skelmesh").decrypt()));
            c_ctm[3] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Legion/Models/GN_AK_Legion_Lv3_Skelmesh.GN_AK_Legion_Lv3_Skelmesh").decrypt()));
            c_ctm[4] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Exo/Models/GN_AK_Exo_Lv1_Skelmesh.GN_AK_Exo_Lv1_Skelmesh").decrypt()));
            c_ctm[5] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Astronaut/Models/GN_AK_Astronaut_Lv1_Skelmesh.GN_AK_Astronaut_Lv1_Skelmesh").decrypt()));
            c_ctm[6] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Assault/Models/GN_AK_Assault_Lv3_Skelmesh.GN_AK_Assault_Lv3_Skelmesh").decrypt()));
            c_ctm[7] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Comet/Models/GN_AK_Comet_Lv1_Skelmesh.GN_AK_Comet_Lv1_Skelmesh").decrypt()));
            c_ctm[8] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Edge2/Models/GN_AK_Edge2_Lv2_Skelmesh.GN_AK_Edge2_Lv2_Skelmesh").decrypt()));
            c_ctm[9] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Egypt/Models/GN_AK_Egypt_Lv1_Skelmesh.GN_AK_Egypt_Lv1_Skelmesh").decrypt()));
            c_ctm[10] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/F1/Models/GN_AK_F1_Lv1_Skelmesh.GN_AK_F1_Lv1_Skelmesh").decrypt()));
            c_ctm[11] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Fallen/Models/GN_AK_Fallen_Skelmesh.GN_AK_Fallen_Skelmesh").decrypt()));
            c_ctm[12] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Flush/Models/GN_AK_Flush_Skelmesh.GN_AK_Flush_Skelmesh").decrypt()));
            c_ctm[13] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Gothic/Models/GN_AK_Gothic_Lv1_Skelmesh.GN_AK_Gothic_Lv1_Skelmesh").decrypt()));
            c_ctm[14] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Grid2/Models/GN_AK_Grid2_Lv1_Skelmesh.GN_AK_Grid2_Lv1_Skelmesh").decrypt()));
            c_ctm[15] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Hellfire/Models/GN_AK_Hellfire_Skelmesh.GN_AK_Hellfire_Skelmesh").decrypt()));
            c_ctm[16] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Hypedragon/Models/GN_AK_Hypedragon_Lv1_Skelmesh.GN_AK_Hypedragon_Lv1_Skelmesh").decrypt()));
            c_ctm[17] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Kingdom2/Models/GN_AK_Kingdom2_Lv1_Skelmesh.GN_AK_Kingdom2_Lv1_Skelmesh").decrypt()));
            c_ctm[18] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Motorbike/Models/GN_AK_Motorbike_Lv3_Skelmesh.GN_AK_Motorbike_Lv3_Skelmesh").decrypt()));
            c_ctm[19] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Mythic/Models/GN_AK_Mythic_Lv1_Skelmesh.GN_AK_Mythic_Lv1_Skelmesh").decrypt()));
            c_ctm[20] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Ninja/Models/GN_AK_Ninja_Lv3_Skelmesh.GN_AK_Ninja_Lv3_Skelmesh").decrypt()));
            c_ctm[21] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Oni2/Models/GN_AK_Oni2_Lv1_Skelmesh.GN_AK_Oni2_Lv1_Skelmesh").decrypt()));
            c_ctm[22] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Permafrost/Models/GN_AK_Permafrost_Lv2_Skelmesh.GN_AK_Permafrost_Lv2_Skelmesh").decrypt()));
            c_ctm[23] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Rabbit/Models/GN_AK_Rabbit_Lv1_Skelmesh.GN_AK_Rabbit_Lv1_Skelmesh").decrypt()));
            c_ctm[24] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/RoboMecha/Models/GN_AK_RoboMecha_Lv1_Skelmesh.GN_AK_RoboMecha_Lv1_Skelmesh").decrypt()));

            c_ctm[25] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/SilverWolf/Models/GN_AK_SilverWolf_Lv1_Skelmesh.GN_AK_SilverWolf_Lv1_Skelmesh").decrypt()));
            c_ctm[26] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/SkatePark/Models/GN_AK_SkatePark_Lv1_Skelmesh.GN_AK_SkatePark_Lv1_Skelmesh").decrypt()));
            c_ctm[27] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Sleek/Models/GN_AK_Sleek_Lv1_Skelmesh.GN_AK_Sleek_Lv1_Skelmesh").decrypt()));
            c_ctm[28] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/SmoothEngine/Models/GN_AK_SmoothEngine_Lv1_Skelmesh.GN_AK_SmoothEngine_Lv1_Skelmesh").decrypt()));
            c_ctm[29] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Soulstealer/Models/GN_AK_Soulstealer_Skelmesh.GN_AK_Soulstealer_Skelmesh").decrypt()));
            c_ctm[30] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Spikes/Models/GN_AK_Spikes_Lv1_Skelmesh.GN_AK_Spikes_Lv1_Skelmesh").decrypt()));
            c_ctm[31] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Starpower/Models/GN_AK_Starpower_Lv3_Skelmesh.GN_AK_Starpower_Lv3_Skelmesh").decrypt()));
            c_ctm[32] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Syndra/Models/GN_AK_Syndra_Lv3_Skelmesh.GN_AK_Syndra_Lv3_Skelmesh").decrypt()));
            c_ctm[33] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/TravelerFantasy/Models/GN_AK_TravelerFantasy_Lv1_Skelmesh.GN_AK_TravelerFantasy_Lv1_Skelmesh").decrypt()));
            c_ctm[34] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Voyager/Models/GN_AK_Voyager_Lv1_Skelmesh.GN_AK_Voyager_Lv1_Skelmesh").decrypt()));
            c_ctm[35] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Wasteland/Models/GN_AK_Wasteland_Lv1_Skelmesh.GN_AK_Wasteland_Lv1_Skelmesh").decrypt()));
            c_ctm[36] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/_Core/Ejectables/Bullets/Comet/Models/Bullet_Comet_50bmg_StaticMesh.Bullet_Comet_50bmg_StaticMesh").decrypt()));
            c_ctm[37] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Bomb/S0/1P/Models/EQ_Bomb_S0_Skelmesh.EQ_Bomb_S0_Skelmesh").decrypt()));
            c_ctm[38] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Bomb/S0/1P/Models/EQ_Bomb_Defuser_S0_Skelmesh.EQ_Bomb_Defuser_S0_Skelmesh").decrypt()));
            c_ctm[39] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Finishers/Coven/Models/Coven_Finisher_Skelmesh.Coven_Finisher_Skelmesh").decrypt()));
            c_ctm[40] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Finishers/Demonstone/Models/Finisher_Chains_Skelmesh.Finisher_Chains_Skelmesh").decrypt()));
            c_ctm[41] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Finishers/Dragon/Models/Dragon_Finisher_Head_SkelM.Dragon_Finisher_Head_SkelM").decrypt()));
            c_ctm[42] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Finishers/HypeBeast/Models/Finisher_Wolf_HypeBeast_Skelmesh.Finisher_Wolf_HypeBeast_Skelmesh").decrypt()));
            c_ctm[43] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Finishers/Hypedragon/Models/Hypedragon_Finisher_Head_Skelmesh.Hypedragon_Finisher_Head_Skelmesh").decrypt()));
            c_ctm[44] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Finishers/Protocol/Models/Protocol_Finisher_Mecha_Skelmesh.Protocol_Finisher_Mecha_Skelmesh").decrypt()));
            c_ctm[45] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Finishers/Snake/Models/Finisher_Snake_Skelmesh.Finisher_Snake_Skelmesh").decrypt()));
            c_ctm[46] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Finishers/Hologram/Models/Finisher_Hologram_Skelmesh.Finisher_Hologram_Skelmesh").decrypt()));
            c_ctm[47] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Finishers/Hellfire/Models/Finisher_Hellfire_Hand_Skelmesh.Finisher_Hellfire_Hand_Skelmesh").decrypt()));
            c_ctm[48] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Finishers/Dynasty/Models/Dynasty_Finisher_Dragon_Skelmesh.Dynasty_Finisher_Dragon_Skelmesh").decrypt()));
            c_ctm[49] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Finishers/Aquarium/Models/Aquarium_Finisher_Skelmesh.Aquarium_Finisher_Skelmesh").decrypt()));
            c_ctm[50] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Melee/Cybercity/Models/EQ_Melee_Cybercity_Skelmesh.EQ_Melee_Cybercity_Skelmesh").decrypt()));
            c_ctm[51] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/SniperRifles/Boltsniper/Fallen/1P/Models/GN_Boltsniper_Fallen_Skelmesh.GN_Boltsniper_Fallen_Skelmesh").decrypt()));
            c_ctm[52] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/SniperRifles/Boltsniper/Raygun/Models/GN_Boltsniper_Raygun_Skelmesh.GN_Boltsniper_Raygun_Skelmesh").decrypt()));
            c_ctm[53] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/SniperRifles/Boltsniper/LostTechnology/Models/GN_Boltsniper_LostTechnology_Lv1_Skelmesh.GN_Boltsniper_LostTechnology_Lv1_Skelmesh").decrypt()));
            c_ctm[54] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/SniperRifles/Boltsniper/Tiger/Models/GN_Boltsniper_Tiger_Lv1_Skelmesh.GN_Boltsniper_Tiger_Lv1_Skelmesh").decrypt()));
            c_ctm[55] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/SniperRifles/Boltsniper/SmoothEngine/Models/GN_Boltsniper_SmoothEngine_Lv1_Skelmesh.GN_Boltsniper_SmoothEngine_Lv1_Skelmesh").decrypt()));
            c_ctm[56] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/SniperRifles/Boltsniper/Historical/Models/GN_Boltsniper_Historical_Lv1_Skelmesh.GN_Boltsniper_Historical_Lv1_Skelmesh").decrypt()));
            c_ctm[57] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/SniperRifles/Boltsniper/Dynasty/Models/GN_Boltsniper_Dynasty_Lv1_Skelmesh.GN_Boltsniper_Dynasty_Lv1_Skelmesh").decrypt()));
            c_ctm[58] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/SniperRifles/Boltsniper/Arcade/Models/GN_Boltsniper_Arcade_Skelmesh.GN_Boltsniper_Arcade_Skelmesh").decrypt()));
            c_ctm[59] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Melee/Airplane/Models/EQ_Melee_Airplane_Lv1_Skelmesh.EQ_Melee_Airplane_Lv1_Skelmesh").decrypt()));
            c_ctm[60] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/BountyHunter/S0/Ability_4/1P/Models/AB_BountyHunter_S0_4_TrailCreature_Skelmesh.AB_BountyHunter_S0_4_TrailCreature_Skelmesh").decrypt()));
            c_ctm[61] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Cashew/S0/Ability_E/1P/Models/AB_Cashew_S0_E_RocketSingle_Skelmesh.AB_Cashew_S0_E_RocketSingle_Skelmesh").decrypt()));
            c_ctm[62] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Deadeye/S0/Ability_Q/1P/Models/AB_Deadeye_S0_Q_Skelmesh.AB_Deadeye_S0_Q_Skelmesh").decrypt()));
            c_ctm[63] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Deadeye/S0/Ability_X/1P/Models/AB_Deadeye_S0_X_Sniper_Skelmesh.AB_Deadeye_S0_X_Sniper_Skelmesh").decrypt()));
            c_ctm[64] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Wushu/S0/Ability_X/1P/Models/AB_Wushu_S0_X_Staticmesh.AB_Wushu_S0_X_Staticmesh").decrypt()));
            c_ctm[65] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/HvyMachineGuns/HMG/Cyberknight/Models/GN_HMG_Cyberknight_Lv3_Skelmesh.GN_HMG_Cyberknight_Lv3_Skelmesh").decrypt()));
            c_ctm[66] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Finishers/HypeBeast/Models/Finisher_Wolf_HypeBeast_Skelmesh.Finisher_Wolf_HypeBeast_Skelmesh").decrypt()));
            c_ctm[67] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Finishers/Dynasty/Models/Dynasty_Finisher_Dragon_Skelmesh.Dynasty_Finisher_Dragon_Skelmesh").decrypt()));
            c_ctm[68] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Finishers/Protocol/Models/Protocol_Finisher_Mecha_Skelmesh.Protocol_Finisher_Mecha_Skelmesh").decrypt()));
            c_ctm[69] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Finishers/Snake/Models/Finisher_Snake_Skelmesh.Finisher_Snake_Skelmesh").decrypt()));
            c_ctm[70] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Finishers/Coven/Models/Coven_Finisher_Skelmesh.Coven_Finisher_Skelmesh").decrypt()));
            c_ctm[71] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Totems/Tactibear/Models/Totem_Toys_Skelmesh.Totem_Toys_Skelmesh").decrypt()));


            va_ctm[0] = static_cast<uanimationasset*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/_Core/1P/Animations/FP_Core_Grenade_OverhandThrow.FP_Core_Grenade_OverhandThrow").decrypt()));


            materials_initialized = true;
        }
    }

    void initialize_materials12() {

        SPOOF_FUNC;

        std::lock_guard<std::mutex> lock(materials_mutex);
        if (!materials_initialized)
        {
            c1_ctm[0] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Airplane/Models/GN_AK_Airplane_Lv1_Skelmesh.GN_AK_Airplane_Lv1_Skelmesh").decrypt()));
            c1_ctm[1] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/MonkeyKing/Models/GN_AK_MonkeyKing_Lv3_Skelmesh.GN_AK_MonkeyKing_Lv3_Skelmesh").decrypt()));
            c1_ctm[2] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/IndustrialX/Models/GN_AK_IndustrialX_Lv1_Skelmesh.GN_AK_IndustrialX_Lv1_Skelmesh").decrypt()));
            c1_ctm[3] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Legion/Models/GN_AK_Legion_Lv3_Skelmesh.GN_AK_Legion_Lv3_Skelmesh").decrypt()));
            c1_ctm[4] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Exo/Models/GN_AK_Exo_Lv1_Skelmesh.GN_AK_Exo_Lv1_Skelmesh").decrypt()));
            c1_ctm[5] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Astronaut/Models/GN_AK_Astronaut_Lv1_Skelmesh.GN_AK_Astronaut_Lv1_Skelmesh").decrypt()));
            c1_ctm[6] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Assault/Models/GN_AK_Assault_Lv3_Skelmesh.GN_AK_Assault_Lv3_Skelmesh").decrypt()));
            c1_ctm[7] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Comet/Models/GN_AK_Comet_Lv1_Skelmesh.GN_AK_Comet_Lv1_Skelmesh").decrypt()));
            c1_ctm[8] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Edge2/Models/GN_AK_Edge2_Lv2_Skelmesh.GN_AK_Edge2_Lv2_Skelmesh").decrypt()));
            c1_ctm[9] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Egypt/Models/GN_AK_Egypt_Lv1_Skelmesh.GN_AK_Egypt_Lv1_Skelmesh").decrypt()));
            c1_ctm[10] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/F1/Models/GN_AK_F1_Lv1_Skelmesh.GN_AK_F1_Lv1_Skelmesh").decrypt()));
            c1_ctm[11] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Fallen/Models/GN_AK_Fallen_Skelmesh.GN_AK_Fallen_Skelmesh").decrypt()));
            c1_ctm[12] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Flush/Models/GN_AK_Flush_Skelmesh.GN_AK_Flush_Skelmesh").decrypt()));
            c1_ctm[13] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Gothic/Models/GN_AK_Gothic_Lv1_Skelmesh.GN_AK_Gothic_Lv1_Skelmesh").decrypt()));
            c1_ctm[14] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Grid2/Models/GN_AK_Grid2_Lv1_Skelmesh.GN_AK_Grid2_Lv1_Skelmesh").decrypt()));
            c1_ctm[15] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Hellfire/Models/GN_AK_Hellfire_Skelmesh.GN_AK_Hellfire_Skelmesh").decrypt()));
            c1_ctm[16] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Hypedragon/Models/GN_AK_Hypedragon_Lv1_Skelmesh.GN_AK_Hypedragon_Lv1_Skelmesh").decrypt()));
            c1_ctm[17] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Kingdom2/Models/GN_AK_Kingdom2_Lv1_Skelmesh.GN_AK_Kingdom2_Lv1_Skelmesh").decrypt()));
            c1_ctm[18] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Motorbike/Models/GN_AK_Motorbike_Lv3_Skelmesh.GN_AK_Motorbike_Lv3_Skelmesh").decrypt()));
            c1_ctm[19] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Mythic/Models/GN_AK_Mythic_Lv1_Skelmesh.GN_AK_Mythic_Lv1_Skelmesh").decrypt()));
            c1_ctm[20] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Ninja/Models/GN_AK_Ninja_Lv3_Skelmesh.GN_AK_Ninja_Lv3_Skelmesh").decrypt()));
            c1_ctm[21] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Oni2/Models/GN_AK_Oni2_Lv1_Skelmesh.GN_AK_Oni2_Lv1_Skelmesh").decrypt()));
            c1_ctm[22] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Permafrost/Models/GN_AK_Permafrost_Lv2_Skelmesh.GN_AK_Permafrost_Lv2_Skelmesh").decrypt()));
            c1_ctm[23] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Rabbit/Models/GN_AK_Rabbit_Lv1_Skelmesh.GN_AK_Rabbit_Lv1_Skelmesh").decrypt()));
            c1_ctm[24] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/RoboMecha/Models/GN_AK_RoboMecha_Lv1_Skelmesh.GN_AK_RoboMecha_Lv1_Skelmesh").decrypt()));

            c1_ctm[25] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/SilverWolf/Models/GN_AK_SilverWolf_Lv1_Skelmesh.GN_AK_SilverWolf_Lv1_Skelmesh").decrypt()));
            c1_ctm[26] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/SkatePark/Models/GN_AK_SkatePark_Lv1_Skelmesh.GN_AK_SkatePark_Lv1_Skelmesh").decrypt()));
            c1_ctm[27] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Sleek/Models/GN_AK_Sleek_Lv1_Skelmesh.GN_AK_Sleek_Lv1_Skelmesh").decrypt()));
            c1_ctm[28] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/SmoothEngine/Models/GN_AK_SmoothEngine_Lv1_Skelmesh.GN_AK_SmoothEngine_Lv1_Skelmesh").decrypt()));
            c1_ctm[29] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Soulstealer/Models/GN_AK_Soulstealer_Skelmesh.GN_AK_Soulstealer_Skelmesh").decrypt()));
            c1_ctm[30] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Spikes/Models/GN_AK_Spikes_Lv1_Skelmesh.GN_AK_Spikes_Lv1_Skelmesh").decrypt()));
            c1_ctm[31] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Starpower/Models/GN_AK_Starpower_Lv3_Skelmesh.GN_AK_Starpower_Lv3_Skelmesh").decrypt()));
            c1_ctm[32] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Syndra/Models/GN_AK_Syndra_Lv3_Skelmesh.GN_AK_Syndra_Lv3_Skelmesh").decrypt()));
            c1_ctm[33] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/TravelerFantasy/Models/GN_AK_TravelerFantasy_Lv1_Skelmesh.GN_AK_TravelerFantasy_Lv1_Skelmesh").decrypt()));
            c1_ctm[34] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Voyager/Models/GN_AK_Voyager_Lv1_Skelmesh.GN_AK_Voyager_Lv1_Skelmesh").decrypt()));
            c1_ctm[35] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/Rifles/AK/Wasteland/Models/GN_AK_Wasteland_Lv1_Skelmesh.GN_AK_Wasteland_Lv1_Skelmesh").decrypt()));
            c1_ctm[36] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/_Core/Ejectables/Bullets/Comet/Models/Bullet_Comet_50bmg_StaticMesh.Bullet_Comet_50bmg_StaticMesh").decrypt()));
            c1_ctm[37] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Bomb/S0/1P/Models/EQ_Bomb_S0_Skelmesh.EQ_Bomb_S0_Skelmesh").decrypt()));
            c1_ctm[38] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Bomb/S0/1P/Models/EQ_Bomb_Defuser_S0_Skelmesh.EQ_Bomb_Defuser_S0_Skelmesh").decrypt()));
            c1_ctm[39] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Finishers/Coven/Models/Coven_Finisher_Skelmesh.Coven_Finisher_Skelmesh").decrypt()));
            c1_ctm[40] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Finishers/Demonstone/Models/Finisher_Chains_Skelmesh.Finisher_Chains_Skelmesh").decrypt()));
            c1_ctm[41] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Finishers/Dragon/Models/Dragon_Finisher_Head_SkelM.Dragon_Finisher_Head_SkelM").decrypt()));
            c1_ctm[42] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Finishers/HypeBeast/Models/Finisher_Wolf_HypeBeast_Skelmesh.Finisher_Wolf_HypeBeast_Skelmesh").decrypt()));
            c1_ctm[43] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Finishers/Hypedragon/Models/Hypedragon_Finisher_Head_Skelmesh.Hypedragon_Finisher_Head_Skelmesh").decrypt()));
            c1_ctm[44] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Finishers/Protocol/Models/Protocol_Finisher_Mecha_Skelmesh.Protocol_Finisher_Mecha_Skelmesh").decrypt()));
            c1_ctm[45] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Finishers/Snake/Models/Finisher_Snake_Skelmesh.Finisher_Snake_Skelmesh").decrypt()));
            c1_ctm[46] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Finishers/Hologram/Models/Finisher_Hologram_Skelmesh.Finisher_Hologram_Skelmesh").decrypt()));
            c1_ctm[47] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Finishers/Hellfire/Models/Finisher_Hellfire_Hand_Skelmesh.Finisher_Hellfire_Hand_Skelmesh").decrypt()));
            c1_ctm[48] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Finishers/Dynasty/Models/Dynasty_Finisher_Dragon_Skelmesh.Dynasty_Finisher_Dragon_Skelmesh").decrypt()));
            c1_ctm[49] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Finishers/Aquarium/Models/Aquarium_Finisher_Skelmesh.Aquarium_Finisher_Skelmesh").decrypt()));
            c1_ctm[50] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Melee/Cybercity/Models/EQ_Melee_Cybercity_Skelmesh.EQ_Melee_Cybercity_Skelmesh").decrypt()));
            c1_ctm[51] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/SniperRifles/Boltsniper/Fallen/1P/Models/GN_Boltsniper_Fallen_Skelmesh.GN_Boltsniper_Fallen_Skelmesh").decrypt()));
            c1_ctm[52] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/SniperRifles/Boltsniper/Raygun/Models/GN_Boltsniper_Raygun_Skelmesh.GN_Boltsniper_Raygun_Skelmesh").decrypt()));
            c1_ctm[53] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/SniperRifles/Boltsniper/LostTechnology/Models/GN_Boltsniper_LostTechnology_Lv1_Skelmesh.GN_Boltsniper_LostTechnology_Lv1_Skelmesh").decrypt()));
            c1_ctm[54] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/SniperRifles/Boltsniper/Tiger/Models/GN_Boltsniper_Tiger_Lv1_Skelmesh.GN_Boltsniper_Tiger_Lv1_Skelmesh").decrypt()));
            c1_ctm[55] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/SniperRifles/Boltsniper/SmoothEngine/Models/GN_Boltsniper_SmoothEngine_Lv1_Skelmesh.GN_Boltsniper_SmoothEngine_Lv1_Skelmesh").decrypt()));
            c1_ctm[56] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/SniperRifles/Boltsniper/Historical/Models/GN_Boltsniper_Historical_Lv1_Skelmesh.GN_Boltsniper_Historical_Lv1_Skelmesh").decrypt()));
            c1_ctm[57] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/SniperRifles/Boltsniper/Dynasty/Models/GN_Boltsniper_Dynasty_Lv1_Skelmesh.GN_Boltsniper_Dynasty_Lv1_Skelmesh").decrypt()));
            c1_ctm[58] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Guns/SniperRifles/Boltsniper/Arcade/Models/GN_Boltsniper_Arcade_Skelmesh.GN_Boltsniper_Arcade_Skelmesh").decrypt()));
            c1_ctm[59] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/Melee/Airplane/Models/EQ_Melee_Airplane_Lv1_Skelmesh.EQ_Melee_Airplane_Lv1_Skelmesh").decrypt()));

            h_ctm[0] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/TrainingBot/S1/1P/Models/FP_TrainingBot_S1_Skelmesh.FP_TrainingBot_S1_Skelmesh").decrypt()));
            h_ctm[1] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/_Core/1P/Models/FP_Breach_Placeholder_Skelmesh.FP_Breach_Placeholder_Skelmesh").decrypt()));
            h_ctm[2] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/_Core/1P/Models/FP_Shatter_Placeholder_Skelmesh.FP_Shatter_Placeholder_Skelmesh").decrypt()));
            h_ctm[3] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/_Core/1P/Models/FP_Grenadier_S0_Skelmesh.FP_Grenadier_S0_Skelmesh").decrypt()));
            h_ctm[4] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/AggroBot/S0/1P/Models/FP_AggroBot_S0_Skelmesh.FP_AggroBot_S0_Skelmesh").decrypt()));
            h_ctm[5] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/BountyHunter/S0/1P/Models/FP_BountyHunter_S0_Skelmesh.FP_BountyHunter_S0_Skelmesh").decrypt()));
            h_ctm[6] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/BountyHunter/S0/1P/Models/FP_BountyHunter_S0_Skelemesh.FP_BountyHunter_S0_Skelemesh").decrypt()));
            h_ctm[7] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Cable/S0/1P/Models/FP_Cable_S0_Skelmesh.FP_Cable_S0_Skelmesh").decrypt()));
            h_ctm[8] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Cashew/S0/1P/Models/FP_Cashew_S0_Skelmesh.FP_Cashew_S0_Skelmesh").decrypt()));
            h_ctm[9] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Clay/S0/1P/Models/FP_Clay_S0_Skelmesh.FP_Clay_S0_Skelmesh").decrypt()));
            h_ctm[10] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Deadeye/S0/1P/Models/FP_Deadeye_S0_Skelmesh.FP_Deadeye_S0_Skelmesh").decrypt()));
            h_ctm[11] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Grenadier/S0/1P/Models/FP_Grenadier_S0_Skelmesh.FP_Grenadier_S0_Skelmesh").decrypt()));
            h_ctm[12] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Guide/S0/1P/Models/FP_Guide_S0_Skelmesh.FP_Guide_S0_Skelmesh").decrypt()));
            h_ctm[13] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Gumshoe/S0/1P/Models/FP_Gumshoe_S0_Skelmesh.FP_Gumshoe_S0_Skelmesh").decrypt()));
            h_ctm[14] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Hunter/S0/1P/Models/FP_Hunter_S0_Skelmesh.FP_Hunter_S0_Skelmesh").decrypt()));
            h_ctm[15] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Joules/S0/1P/Models/FP_Joules_S0_Skelmesh.FP_Joules_S0_Skelmesh").decrypt()));
            h_ctm[16] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Killjoy/S0/1P/Models/FP_Killjoy_S0_Skelmesh.FP_Killjoy_S0_Skelmesh").decrypt()));
            h_ctm[17] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Mage/S0/1P/Models/FP_Mage_S0_Skelmesh.FP_Mage_S0_Skelmesh").decrypt()));
            h_ctm[18] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Nox/S0/1P/Models/FP_Nox_S0_Skelmesh.FP_Nox_S0_Skelmesh").decrypt()));
            h_ctm[19] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Pandemic/S0/1P/Models/FP_Pandemic_S0_Skelmesh.FP_Pandemic_S0_Skelmesh").decrypt()));
            h_ctm[20] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Phoenix/S0/1P/Models/FP_Phoenix_S0_Skelmesh.FP_Phoenix_S0_Skelmesh").decrypt()));
            h_ctm[21] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Rift/S0/1P/Models/FP_Rift_S0_Skelmesh.FP_Rift_S0_Skelmesh").decrypt()));
            h_ctm[22] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Sarge/S0/1P/Models/FP_Sarge_S0_Skelmesh.FP_Sarge_S0_Skelmesh").decrypt()));
            h_ctm[23] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Sequoia/S0/1P/Models/FP_Sequoia_S0_Skelmesh.FP_Sequoia_S0_Skelmesh").decrypt()));
            h_ctm[24] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Smonk/S0/1P/Models/FP_Smonk_S0_Skelmesh.FP_Smonk_S0_Skelmesh").decrypt()));
            h_ctm[25] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Sprinter/S0/1P/Models/FP_Sprinter_S0_Skelmesh.FP_Sprinter_S0_Skelmesh").decrypt()));
            h_ctm[26] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Stealth/S0/1P/Models/FP_Stealth_S0_Skelmesh.FP_Stealth_S0_Skelmesh").decrypt()));
            h_ctm[27] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Terra/S0/1P/Models/FP_Terra_S0_Skelmesh.FP_Terra_S0_Skelmesh").decrypt()));
            h_ctm[28] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/TrainingBot/S2/1P/Models/FP_TrainingBot_S2_Skelmesh.FP_TrainingBot_S2_Skelmesh").decrypt()));
            h_ctm[29] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Vampire/S0/1P/Models/FP_Vampire_S0_Skelmesh.FP_Vampire_S0_Skelmesh").decrypt()));
            h_ctm[30] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Wraith/S0/1P/Models/FP_Wraith_S0_Skelmesh.FP_Wraith_S0_Skelmesh").decrypt()));
            h_ctm[31] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Wushu/S0/1P/Models/FP_Wushu_S0_Skelmesh.FP_Wushu_S0_Skelmesh").decrypt()));

            r_ctm[0] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Atlas/3P_Infinity_Atlas_Triangle_Lv1_MI.3P_Infinity_Atlas_Triangle_Lv1_MI").decrypt());
            r_ctm[1] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Environment/Materials/Instances/Mat_Emissive_BlueGlowInfinity.Mat_Emissive_BlueGlowInfinity").decrypt());
            r_ctm[2] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Environment/Materials/Instances/Mat_Emissive_GoldGlowB.Mat_Emissive_GoldGlowB").decrypt());
            r_ctm[3] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Environment/Materials/Instances/Emissive_KingdomLightBlue_Flicker_MI.Emissive_KingdomLightBlue_Flicker_MI").decrypt());
            r_ctm[4] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Thorne/S0/3P/Models/Materials/CS_Thorne_S0_Hair_MI.CS_Thorne_S0_Hair_MI").decrypt());
            r_ctm[5] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Thorne/S0/3P/Models/Materials/TP_Thorne_S0_Hair_MRAE.TP_Thorne_S0_Hair_MRAE").decrypt());
            r_ctm[6] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Thorne/S0/3P/Models/Materials/TP_Thorne_S0_Hair_NM.TP_Thorne_S0_Hair_NM").decrypt());
            r_ctm[7] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Thorne/S0/3P/Models/Materials/TP_Thorne_S0_Orb_MI.TP_Thorne_S0_Orb_MI").decrypt());
            r_ctm[8] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/TrainingBot/S0/3P/Materials/TP_TrainingBot_S3_MI.TP_TrainingBot_S3_MI").decrypt());
            r_ctm[9] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Wraith/S0/3P/Materials/Omen_Overlays/Omen_Overlay_Ally_MI.Omen_Overlay_Ally_MI").decrypt());
            r_ctm[10] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/_Core/3P/Materials/Hair/TP_Base_V5_S0_MI_HAIR.TP_Base_V5_S0_MI_HAIR").decrypt());
            r_ctm[11] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/BaseMaterials/3P_Constellation_v3_Tritium_MI.3P_Constellation_v3_Tritium_MI").decrypt());
            r_ctm[12] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/VFX/Materials/Edge2_Lines_v3_Melee_MI.Edge2_Lines_v3_Melee_MI").decrypt());

            materials_initialized = true;
        }
    }

    void initialize_materials144() {

        SPOOF_FUNC;

        std::lock_guard<std::mutex> lock(materials_mutex);
        if (!materials_initialized)
        {
            e_ctm[0] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/TrainingBot/S1/3P/Models/TP_TrainingBot_S1_Skelmesh.TP_TrainingBot_S1_Skelmesh").decrypt()));
            e_ctm[1] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/_Core/3P/Models/TP_Breach_Placeholder_Skelmesh.TP_Breach_Placeholder_Skelmesh").decrypt()));
            e_ctm[2] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/_Core/3P/Models/TP_Shatter_Placeholder_Skelmesh.TP_Shatter_Placeholder_Skelmesh").decrypt()));
            e_ctm[3] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/_Core/3P/Models/TP_Grenadier_S0_Skelmesh.TP_Grenadier_S0_Skelmesh").decrypt()));
            e_ctm[4] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/AggroBot/S0/3P/Models/TP_AggroBot_S0_Skelmesh.TP_AggroBot_S0_Skelmesh").decrypt()));
            e_ctm[5] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/BountyHunter/S0/3P/Models/TP_BountyHunter_S0_Skelmesh.TP_BountyHunter_S0_Skelmesh").decrypt()));
            e_ctm[6] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/BountyHunter/S0/3P/Models/TP_BountyHunter_S0_Skelemesh.TP_BountyHunter_S0_Skelemesh").decrypt()));
            e_ctm[7] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Cable/S0/3P/Models/TP_Cable_S0_Skelmesh.TP_Cable_S0_Skelmesh").decrypt()));
            e_ctm[8] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Cashew/S0/3P/Models/TP_Cashew_S0_Skelmesh.TP_Cashew_S0_Skelmesh").decrypt()));
            e_ctm[9] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Clay/S0/3P/Models/TP_Clay_S0_Skelmesh.TP_Clay_S0_Skelmesh").decrypt()));
            e_ctm[10] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Deadeye/S0/3P/Models/TP_Deadeye_S0_Skelmesh.TP_Deadeye_S0_Skelmesh").decrypt()));
            e_ctm[11] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Grenadier/S0/3P/Models/TP_Grenadier_S0_Skelmesh.TP_Grenadier_S0_Skelmesh").decrypt()));
            e_ctm[12] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Guide/S0/3P/Models/TP_Guide_S0_Skelmesh.TP_Guide_S0_Skelmesh").decrypt()));
            e_ctm[13] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Gumshoe/S0/3P/Models/TP_Gumshoe_S0_Skelmesh.TP_Gumshoe_S0_Skelmesh").decrypt()));
            e_ctm[14] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Hunter/S0/3P/Models/TP_Hunter_S0_Skelmesh.TP_Hunter_S0_Skelmesh").decrypt()));
            e_ctm[15] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Joules/S0/3P/Models/TP_Joules_S0_Skelmesh.TP_Joules_S0_Skelmesh").decrypt()));
            e_ctm[16] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Killjoy/S0/3P/Models/TP_Killjoy_S0_Skelmesh.TP_Killjoy_S0_Skelmesh").decrypt()));
            e_ctm[17] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Mage/S0/3P/Models/TP_Mage_S0_Skelmesh.TP_Mage_S0_Skelmesh").decrypt()));
            e_ctm[18] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Nox/S0/3P/Models/TP_Nox_S0_Skelmesh.TP_Nox_S0_Skelmesh").decrypt()));
            e_ctm[19] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Pandemic/S0/3P/Models/TP_Pandemic_S0_Skelmesh.TP_Pandemic_S0_Skelmesh").decrypt()));
            e_ctm[20] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Phoenix/S0/3P/Models/TP_Phoenix_S0_Skelmesh.TP_Phoenix_S0_Skelmesh").decrypt()));
            e_ctm[21] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Rift/S0/3P/Models/TP_Rift_S0_Skelmesh.TP_Rift_S0_Skelmesh").decrypt()));
            e_ctm[22] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Sarge/S0/3P/Models/TP_Sarge_S0_Skelmesh.TP_Sarge_S0_Skelmesh").decrypt()));
            e_ctm[23] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Sequoia/S0/3P/Models/TP_Sequoia_S0_Skelmesh.TP_Sequoia_S0_Skelmesh").decrypt()));
            e_ctm[24] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Smonk/S0/3P/Models/TP_Smonk_S0_Skelmesh.TP_Smonk_S0_Skelmesh").decrypt()));
            e_ctm[25] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Sprinter/S0/3P/Models/TP_Sprinter_S0_Skelmesh.TP_Sprinter_S0_Skelmesh").decrypt()));
            e_ctm[26] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Stealth/S0/3P/Models/TP_Stealth_S0_Skelmesh.TP_Stealth_S0_Skelmesh").decrypt()));
            e_ctm[27] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Terra/S0/3P/Models/TP_Terra_S0_Skelmesh.TP_Terra_S0_Skelmesh").decrypt()));
            e_ctm[28] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/TrainingBot/S2/3P/Models/TP_TrainingBot_S2_Skelmesh.TP_TrainingBot_S2_Skelmesh").decrypt()));
            e_ctm[29] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Vampire/S0/3P/Models/TP_Vampire_S0_Skelmesh.TP_Vampire_S0_Skelmesh").decrypt()));
            e_ctm[30] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Wraith/S0/3P/Models/TP_Wraith_S0_Skelmesh.TP_Wraith_S0_Skelmesh").decrypt()));
            e_ctm[31] = static_cast<uskeletalmeshcomponent*>(uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Characters/Wushu/S0/3P/Models/TP_Wushu_S0_Skelmesh.TP_Wushu_S0_Skelmesh").decrypt()));

            a_mts[0] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Atlas/3P_Infinity_Atlas_Triangle_Lv1_MI.3P_Infinity_Atlas_Triangle_Lv1_MI").decrypt());
            a_mts[1] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Idol/3P_Idol_MI.3P_Idol_MI").decrypt());
            a_mts[2] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/InnerRage/InnerRage_Emissive_Radial_3p_MI.InnerRage_Emissive_Radial_3p_MI").decrypt());
            a_mts[3] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/LittleNightmare/LittleNightmare_Emissive_v2_3P_MI.LittleNightmare_Emissive_v2_3P_MI").decrypt());
            a_mts[4] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Atlas/3P_Infinity_Atlas_Triangle_Lv1_MI.3P_Infinity_Atlas_Triangle_Lv1_MI").decrypt());
            a_mts[5] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Constellation/3P_Constellation_v1_Tritium_MI.3P_Constellation_v1_Tritium_MI").decrypt());
            a_mts[6] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Hydrodip/3P_Hydrodip_Tritium_MI.3P_Hydrodip_Tritium_MI").decrypt());
            a_mts[7] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Iridescence/Iridescence2_Tritium_v3_3P_MI.Iridescence2_Tritium_v3_3P_MI").decrypt());
            a_mts[8] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Emissive/3P_Weapon_Emissive_Gem_MI.3P_Weapon_Emissive_Gem_MI").decrypt());
            a_mts[9] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Kingdom/Kingdom_Emissive_3P_MI.Kingdom_Emissive_3P_MI").decrypt());
            a_mts[10] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Kingdom2/3P_Kingdom2_Decals_MI.3P_Kingdom2_Decals_MI").decrypt());
            a_mts[11] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Legion/Legion_Emissive_v3_3p_MI.Legion_Emissive_v3_3p_MI").decrypt());
            a_mts[12] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Legion/Legion_Emissive_v2_3p_MI.Legion_Emissive_v2_3p_MI").decrypt());
            a_mts[13] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Legion/Legion_Emissive_3p_MI.Legion_Emissive_3p_MI").decrypt());
            a_mts[14] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Gems/Exo_Gem_3P_MI.Exo_Gem_3P_MI").decrypt());
            a_mts[15] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/CuteButLethal/3P_CuteButLethal_Tritium_MI.3P_CuteButLethal_Tritium_MI").decrypt());
            a_mts[16] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Atlas/3P_Atlas_Emissive_Lv3_MI.3P_Atlas_Emissive_Lv3_MI").decrypt());
            a_mts[17] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Atlas/3P_Atlas_Emissive_MI.3P_Atlas_Emissive_MI").decrypt());
            a_mts[18] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Atlas/3P_Atlas_Holographic_Sticker_MI.3P_Atlas_Holographic_Sticker_MI").decrypt());
            a_mts[19] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Atlas/3P_Infinity_Atlas_Lv3_MI.3P_Infinity_Atlas_Lv3_MI").decrypt());
            a_mts[20] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Atlas/3P_Atlas_Decal_White_MI.3P_Atlas_Decal_White_MI").decrypt());
            a_mts[21] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Gothic/Gothic_Gem_3P_MI.Gothic_Gem_3P_MI").decrypt());
            a_mts[22] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Gunslinger/3p_Gunslinger_Emissive_v3_MI.3p_Gunslinger_Emissive_v3_MI").decrypt());
            a_mts[23] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Gunslinger/3p_Gunslinger_Emissive_v2_MI.3p_Gunslinger_Emissive_v2_MI").decrypt());
            a_mts[24] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Gunslinger/3p_Gunslinger_Emissive_v1_MI.3p_Gunslinger_Emissive_v1_MI").decrypt());

            a_mts[25] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Gunslinger/3p_Gunslinger_Emissive_MI.3p_Gunslinger_Emissive_MI").decrypt());
            a_mts[26] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Gunslinger/Gunslinger_Glass_v3_3P_TEMP_MI.Gunslinger_Glass_v3_3P_TEMP_MI").decrypt());
            a_mts[27] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Jinju/Tritium_Jinju_3P_MI.Tritium_Jinju_3P_MI").decrypt());
            a_mts[28] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Luxury/Luxury_Tritium_3P_MI.Luxury_Tritium_3P_MI").decrypt());
            a_mts[29] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Oblivion/Oblivion_3P_Emissive.Oblivion_3P_Emissive").decrypt());
            a_mts[30] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Oblivion/Oblivion_Glass_3P_MI.Oblivion_Glass_3P_MI").decrypt());
            a_mts[31] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Oni/Oni_Emissive_3P_MI.Oni_Emissive_3P_MI").decrypt());
            a_mts[32] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Oni/Oni_Black_Eye_3P_MI.Oni_Black_Eye_3P_MI").decrypt());
            a_mts[33] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Oni/Oni_Emissive_Green_3P_MI.Oni_Emissive_Green_3P_MI").decrypt());
            a_mts[34] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Oni/Oni_Emissive_White_3P_MI.Oni_Emissive_White_3P_MI").decrypt());
            a_mts[35] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Polyfrog/Tritium_Polyfrog_Pink_3p_MI.Tritium_Polyfrog_Pink_3p_MI").decrypt());
            a_mts[36] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Protocol/Protocol_3P_Emissive_MI.Protocol_3P_Emissive_MI").decrypt());
            a_mts[37] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Raygun/Raygun_Emissive_3p_MI.Raygun_Emissive_3p_MI").decrypt());
            a_mts[38] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Raygun/Raygun_Emissive_Green_3p_MI.Raygun_Emissive_Green_3p_MI").decrypt());
            a_mts[39] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Raygun/Raygun_Emissive_Yellow_3p_MI.Raygun_Emissive_Yellow_3p_MI").decrypt());
            a_mts[40] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/RetroLA/3P_RetroLA_Tritium_MI.3P_RetroLA_Tritium_MI").decrypt());
            a_mts[41] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Shellfish/Shellfish_Pearl_3P_MI.Shellfish_Pearl_3P_MI").decrypt());
            a_mts[42] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Sportscar/Sportscar_Emissive_3P_MI.Sportscar_Emissive_3P_MI").decrypt());
            a_mts[43] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Syndra/3P_Syndra_Crystal_Front_v3_MI.3P_Syndra_Crystal_Front_v3_MI").decrypt());
            a_mts[44] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Syndra/Syndra_Flow_DepthFade_3P_MI.Syndra_Flow_DepthFade_3P_MI").decrypt());
            a_mts[45] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Syndra/Syndra_Emissive_3P_MI.Syndra_Emissive_3P_MI").decrypt());
            a_mts[46] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Syndra/Syndra_v3_Emissive_3P_MI.Syndra_v3_Emissive_3P_MI").decrypt());
            a_mts[47] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Syndra/Syndra_v2_Emissive_3P_MI.Syndra_v2_Emissive_3P_MI").decrypt());
            a_mts[48] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Syndra/Syndra_v1_Emissive_3P_MI.Syndra_v1_Emissive_3P_MI").decrypt());
            a_mts[49] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Synthwave/3P_Synthwave_Tritium_MI.3P_Synthwave_Tritium_MI").decrypt());

            materials_initialized = true;
        }
    }

    void initialize_materials155() {

        SPOOF_FUNC;

        std::lock_guard<std::mutex> lock(materials_mutex);
        if (!materials_initialized)
        {
            hand_wfs[0] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Arcade/Arcade_Emissive_Yellow_MI.Arcade_Emissive_Yellow_MI").decrypt()); // YELLOW
            hand_wfs[1] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Arcade/Arcade_Emissive_Red_MI.Arcade_Emissive_Red_MI").decrypt());     // RED
            hand_wfs[2] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Arcade/Arcade_Emissive_Blue_MI.Arcade_Emissive_Blue_MI").decrypt());   // BLUE
            hand_wfs[3] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Arcade/Arcade_Emissive_Purple_MI.Arcade_Emissive_Purple_MI").decrypt()); // PURPLE
            hand_wfs[4] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Atlas/1P_Atlas_Emissive_Lv3_MI_v2.1P_Atlas_Emissive_Lv3_MI_v2").decrypt()); // ATLAS
            hand_wfs[5] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Dynasty/Dynasty_Emissive_Gem_1P_MI.Dynasty_Emissive_Gem_1P_MI").decrypt()); // DYNASTY A
            hand_wfs[6] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Dynasty/Dynasty_Emissive_Gem_1P_v1_MI.Dynasty_Emissive_Gem_1P_v1_MI").decrypt());
            hand_wfs[7] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Hieroglyphs/1P_Hieroglyphs_Crystal_MI.1P_Hieroglyphs_Crystal_MI").decrypt());

            materials_initialized = true;
        }
    }

    void initialize_materials166() {

        SPOOF_FUNC;

        std::lock_guard<std::mutex> lock(materials_mutex);
        if (!materials_initialized)
        {
            gun_wfs[0] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Arcade/Arcade_Emissive_Yellow_MI.Arcade_Emissive_Yellow_MI").decrypt()); // YELLOW
            gun_wfs[1] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Arcade/Arcade_Emissive_Red_MI.Arcade_Emissive_Red_MI").decrypt());     // RED
            gun_wfs[2] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Arcade/Arcade_Emissive_Blue_MI.Arcade_Emissive_Blue_MI").decrypt());   // BLUE
            gun_wfs[3] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Arcade/Arcade_Emissive_Purple_MI.Arcade_Emissive_Purple_MI").decrypt()); // PURPLE
            gun_wfs[4] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Atlas/1P_Atlas_Emissive_Lv3_MI_v2.1P_Atlas_Emissive_Lv3_MI_v2").decrypt()); // ATLAS
            gun_wfs[5] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Dynasty/Dynasty_Emissive_Gem_1P_MI.Dynasty_Emissive_Gem_1P_MI").decrypt()); // DYNASTY A
            gun_wfs[6] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Dynasty/Dynasty_Emissive_Gem_1P_v1_MI.Dynasty_Emissive_Gem_1P_v1_MI").decrypt());
            gun_wfs[7] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Hieroglyphs/1P_Hieroglyphs_Crystal_MI.1P_Hieroglyphs_Crystal_MI").decrypt());

            materials_initialized = true;
        }
    }

    void initialize_materials177() {

        SPOOF_FUNC;

        std::lock_guard<std::mutex> lock(materials_mutex);
        if (!materials_initialized)
        {
            epl_wfs[0] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Atlas/3P_Infinity_Atlas_Triangle_Lv1_MI.3P_Infinity_Atlas_Triangle_Lv1_MI").decrypt());
            epl_wfs[1] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Constellation/3P_Constellation_v1_Tritium_MI.3P_Constellation_v1_Tritium_MI").decrypt());
            epl_wfs[2] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Hydrodip/3P_Hydrodip_Tritium_MI.3P_Hydrodip_Tritium_MI").decrypt());
            epl_wfs[3] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Iridescence/Iridescence2_Tritium_v3_3P_MI.Iridescence2_Tritium_v3_3P_MI").decrypt());
            epl_wfs[4] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Emissive/3P_Weapon_Emissive_Gem_MI.3P_Weapon_Emissive_Gem_MI").decrypt());
            epl_wfs[5] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Kingdom/Kingdom_Emissive_3P_MI.Kingdom_Emissive_3P_MI").decrypt());
            epl_wfs[6] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Kingdom2/3P_Kingdom2_Decals_MI.3P_Kingdom2_Decals_MI").decrypt());
            epl_wfs[7] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Legion/Legion_Emissive_v3_3p_MI.Legion_Emissive_v3_3p_MI").decrypt());
            epl_wfs[8] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Legion/Legion_Emissive_v2_3p_MI.Legion_Emissive_v2_3p_MI").decrypt());
            epl_wfs[9] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Legion/Legion_Emissive_3p_MI.Legion_Emissive_3p_MI").decrypt());
            epl_wfs[10] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Gems/Exo_Gem_3P_MI.Exo_Gem_3P_MI").decrypt());
            epl_wfs[11] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/CuteButLethal/3P_CuteButLethal_Tritium_MI.3P_CuteButLethal_Tritium_MI").decrypt());
            epl_wfs[12] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Atlas/3P_Atlas_Emissive_Lv3_MI.3P_Atlas_Emissive_Lv3_MI").decrypt());
            epl_wfs[13] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Atlas/3P_Atlas_Emissive_MI.3P_Atlas_Emissive_MI").decrypt());
            epl_wfs[14] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Atlas/3P_Atlas_Holographic_Sticker_MI.3P_Atlas_Holographic_Sticker_MI").decrypt());
            epl_wfs[15] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Atlas/3P_Infinity_Atlas_Lv3_MI.3P_Infinity_Atlas_Lv3_MI").decrypt());
            epl_wfs[16] = uobject::static_load_object(nullptr, nullptr, crypt(L"/Game/Equippables/_Core/Materials/SpecialMaterials/Atlas/3P_Atlas_Decal_White_MI.3P_Atlas_Decal_White_MI").decrypt());

            materials_initialized = true;
        }
    }

    uobject* get_finisher_from_skin(const SkinData& skinData) {
        std::wstring assetName = skinData.skin;

        // Remove known prefix
        const std::wstring defaultPrefix = crypt(L"Default__").decrypt();
        if (assetName.find(defaultPrefix) == 0) {
            assetName = assetName.substr(defaultPrefix.length());
        }

        // Find and extract the skin identifier (e.g., Commando, Syndra, etc.)
        size_t firstUnderscore = assetName.find(L'_');
        size_t lastUnderscore = assetName.rfind(crypt(L"_PrimaryAsset_C").decrypt());

        if (firstUnderscore == std::wstring::npos || lastUnderscore == std::wstring::npos || lastUnderscore <= firstUnderscore) {
            return nullptr; // Invalid format
        }

        std::wstring skinNameW = assetName.substr(firstUnderscore + 1, lastUnderscore - firstUnderscore - 1);
        std::string skinName(skinNameW.begin(), skinNameW.end());

        // Try full match
        std::string obj = crypt("FXC_Finisher_").decrypt() + skinName + crypt("_Victim_C").decrypt();
        std::wstring wobj(obj.begin(), obj.end());
        uobject* effect = uobject::find_object<uobject*>(wobj.c_str(), reinterpret_cast<uobject*>(-1));

        // Fallback: remove trailing digits
        if (!effect && !skinName.empty()) {
            while (!skinName.empty() && std::isdigit(skinName.back())) {
                skinName.pop_back();
            }

            obj = crypt("FXC_Finisher_").decrypt() + skinName + crypt("_Victim_C").decrypt();
            wobj = std::wstring(obj.begin(), obj.end());
            effect = uobject::find_object<uobject*>(wobj.c_str(), reinterpret_cast<uobject*>(-1));
        }

        return effect;
    }


    using FinisherFn = void* (__fastcall*)(uintptr_t a1);
    inline void* PlayFinisherEffect(uintptr_t a1)
    {
        SPOOF_FUNC;
        static FinisherFn fn = nullptr;
        if (!fn)
            fn = reinterpret_cast<FinisherFn>(memory::module_base + offsets::player_finisher_effect);

        return fn(a1);
    }

    void(__fastcall* oHkDeath)(void*, void*);

    static std::unordered_map<uobject*, std::string> objectNameCache;
    inline std::string get_cached_name(uobject* obj) {
        auto it = objectNameCache.find(obj);
        if (it != objectNameCache.end()) return it->second;
        std::string name = system::get_object_name(obj).ToString();
        objectNameCache[obj] = name;
        return name;
    }




    /*   namespace KillEffect {

           void hk_death(ashootercharacter* shooter_character, UDamageResponse* a2) {
               try {
                   if (!shooter_character || !memory::IsValidPointer((uintptr_t)shooter_character)) {
                       return oHkDeath(shooter_character, a2);
                   }

                   acknowledgedpawn* pawn = controllers->get_acknowledged_pawn();
                   ashootercharacter* character_context = character;
                   acknowledgedpawn* local_pawn_context = pawn;
                   auto damage_response = a2;

                   if (!character_context || !local_pawn_context || !damage_response) {
                       return oHkDeath(shooter_character, a2);
                   }

                   auto component = (uintptr_t)memory::read<uobject*>((uintptr_t)shooter_character + offsets::death_reaction_component);
                   if (!component || !memory::IsValidPointer(component)) {
                       return oHkDeath(shooter_character, a2);
                   }

                   BYTE b1 = memory::read<BYTE>(component + 0x15A);
                   BYTE b2 = memory::read<BYTE>(component + 0x168);

                   if (!(b1 == 0 || b2 == 1)) {
                       return oHkDeath(shooter_character, a2);
                   }

                   auto killer = damage_response->GetDamageCauser();
                   auto equippable = damage_response->GetEquippableUsed();

                   if (!killer || !equippable) {
                       return oHkDeath(shooter_character, a2);
                   }

                   uworld* world_save = nullptr;
                   uintptr_t* uworld_state_ptr = *(uintptr_t**)(memory::module_base + offsets::State);
                   if (uworld_state_ptr) {
                       world_save = *(uworld**)uworld_state_ptr;
                   }

                   if (!world_save) {
                       return oHkDeath(shooter_character, a2);
                   }

                   tarray<ashootercharacter*> enemies = blueprints::find_all_shooters_with_alliance(
                       world_save, character, earesalliance::enemy, false, true);

                   currentequippable* my_weapon = character->get_inventory()->get_current_equippable();

                   if ((globals::misc::finisher || globals::misc::killsound) &&
                       character->is_alive() &&
                       character->health() > 0) {

                       if (killer == local_pawn_context) {
                           int num_enemies = enemies.count;
                           for (int i = 0; i < enemies.count; ++i) {
                               if (enemies[i] == shooter_character) {
                                   num_enemies -= 1;
                                   break;
                               }
                           }

                           if (globals::misc::killsound) {
                               static int sound_index = 0;
                               const LPCWSTR system_sounds[] = {
                                   L"SystemAsterisk",
                                   L"SystemExclamation",
                                   L"SystemExit",
                                   L"SystemStart",
                                   L"SystemHand"
                               };

                               PlaySoundW(system_sounds[sound_index], NULL, SND_ALIAS | SND_ASYNC);
                               sound_index = (sound_index + 1) % 5;
                           }

                           bool shouldPlayFinisher = globals::misc::onlylastkill ? (num_enemies == 0) : true;

                           if (globals::misc::finisher && shouldPlayFinisher && my_weapon) {
                               std::string weapon_name = get_cached_name(my_weapon);

                               constexpr std::size_t montage_effect_override_offset = 0x110;
                               constexpr std::size_t montage_effect_override_context_offset = 0x118;

                               memory::write<uobject*>(component + montage_effect_override_offset, nullptr);
                               memory::write<uobject*>(component + montage_effect_override_context_offset, nullptr);

                               uobject* finisher = nullptr;

                               if (finisher) {
                                   memory::write<uobject*>(component + montage_effect_override_offset, finisher);
                                   memory::write<uobject*>(component + montage_effect_override_context_offset, local_pawn_context);
                               }

                               PlayFinisherEffect(component);
                           }
                       }
                   }

                   return oHkDeath(shooter_character, a2);
               }
               catch (...) {
                   return oHkDeath(shooter_character, a2);
               }
           }
        }*/

#pragma pack(push, 1)
    union fp_flag_store {
        unsigned char raw;
        struct {
            unsigned char f0 : 1;
            unsigned char f1 : 1;
            unsigned char f2 : 6;
        } bits;
    };
#pragma pack(pop)

    struct ViewModelCache {
        uskeletalmeshcomponent* mesh1p = nullptr;
        uskeletalmeshcomponent* overlayMesh = nullptr;
        uskeletalmeshcomponent* weaponMesh1P = nullptr;
        uskeletalmeshcomponent* cosmeticMesh1P = nullptr;
        uskeletalmeshcomponent* meleeMesh1P = nullptr;
        uskeletalmeshcomponent* offHandMesh = nullptr;
        currentequippable* lastWeapon = nullptr;
        currentequippable* lastMelee = nullptr;
        ULONGLONG lastCacheTime = 0;

        void Clear() {
            mesh1p = overlayMesh = weaponMesh1P = cosmeticMesh1P = nullptr;
            meleeMesh1P = offHandMesh = nullptr;
            lastWeapon = lastMelee = nullptr;
        }

        bool IsValid() const {
            return mesh1p != nullptr && weaponMesh1P != nullptr;
        }
    };

    inline bool IsValidViewModelPointer(uintptr_t ptr) {
        if (ptr == 0 || ptr == (uintptr_t)-1 || ptr < 0x10000 || ptr > 0x7FFFFFFFFFFF) {
            return false;
        }

        __try {
            volatile unsigned char test = *(unsigned char*)ptr;
            (void)test;
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            return false;
        }
    }

    inline bool IsValidViewModelObject(void* obj) {
        if (!obj) return false;
        return IsValidViewModelPointer((uintptr_t)obj);
    }

    inline tarray<USceneComponent*> GetChildrenComponents(USceneComponent* component, bool bIncludeAllDescendants) {
        tarray<USceneComponent*> result;
        if (!component || !IsValidViewModelObject(component)) return result;

        static uobject* Function = nullptr;
        if (!Function) {
            auto function_name = (L"Engine.SceneComponent.GetChildrenComponents");
            Function = uobject::find_object<uobject*>(function_name);
        }

        if (!Function || !IsValidViewModelObject(Function)) return result;

        struct {
            bool bIncludeAllDescendants;
            tarray<USceneComponent*> Children;
        } Args;

        Args.bIncludeAllDescendants = bIncludeAllDescendants;
        Args.Children.data = nullptr;
        Args.Children.count = 0;
        Args.Children.max = 0;

        __try {
            component->process_event(Function, &Args);
            return Args.Children;
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            return result;
        }
    }

    currentequippable* GetLocalMeleeWeapon() {
        static currentequippable* CachedMelee = nullptr;
        static ULONGLONG lastCacheTime = 0;

        ULONGLONG currentTime = GetTickCount64();
        if (CachedMelee && (currentTime - lastCacheTime) < 2000) {
            return CachedMelee;
        }

        CachedMelee = nullptr;
        if (!UWorldSave) return nullptr;

        tarray<AGameObject*> Objects;
        GameplayStatics::GetAllActorsOfClass2(UWorldSave, Class::Actors(), &Objects);

        for (int i = 0; i < Objects.size(); ++i) {
            AGameObject* Object = Objects[i];
            if (!Object) continue;

            auto name = system::get_object_name(Object);
            if (!name.is_valid()) continue;

            std::string name_str = name.ToString();
            if (name_str.find("Ability_Melee_Base_C") != std::string::npos) {
                CachedMelee = (currentequippable*)Object;
                lastCacheTime = currentTime;
                return CachedMelee;
            }
        }

        return nullptr;
    }

    template<typename T>
    inline bool SafeRead(uintptr_t address, T& value) {
        if (!IsValidViewModelPointer(address)) return false;

        __try {
            value = *reinterpret_cast<T*>(address);
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            return false;
        }
    }

    template<typename T>
    inline bool SafeWrite(uintptr_t address, const T& value) {
        if (!IsValidViewModelPointer(address)) return false;

        __try {
            *reinterpret_cast<T*>(address) = value;
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            return false;
        }
    }

    inline bool SafeProcessFlag(uskeletalmeshcomponent* mesh, uintptr_t flag_offset, bool clear_flag) {
        if (!mesh || !IsValidViewModelObject(mesh)) return false;

        uintptr_t flag_addr = (uintptr_t)mesh + flag_offset;
        if (!IsValidViewModelPointer(flag_addr)) return false;

        fp_flag_store state;
        if (!SafeRead(flag_addr, state.raw)) return false;

        if (clear_flag) {
            state.bits.f0 = 0;
            return SafeWrite(flag_addr, state.raw);
        }

        return true;
    }

    inline void SafeLockDescendants(USceneComponent* component) {
        if (!component || !IsValidViewModelObject(component)) return;

        tarray<USceneComponent*> allChildren;
        __try {
            allChildren = GetChildrenComponents(component, true);
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            return;
        }

        for (int i = 0; i < allChildren.Num(); i++) {
            USceneComponent* child = allChildren[i];
            if (child && IsValidViewModelObject(child)) {
                uintptr_t child_flag_addr = (uintptr_t)child + 0x364;
                SafeWrite(child_flag_addr, (unsigned char)0x00);
            }
        }
    }

    inline void process_fp_mode(ashootercharacter* shooter) {
        if (!shooter) return;

        uintptr_t shooter_ptr = (uintptr_t)shooter;
        if (shooter_ptr == 0 || shooter_ptr == (uintptr_t)-1 || shooter_ptr < 0x10000 || shooter_ptr > 0x7FFFFFFFFFFF) {
            return;
        }

        __try {
            volatile uintptr_t test = *(uintptr_t*)shooter_ptr;
            (void)test;
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            return;
        }

        bool isAlive = false;
        __try {
            isAlive = shooter->is_alive();
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            return;
        }

        static ViewModelCache cache;

        if (!isAlive) {
            cache.Clear();
            return;
        }

        static bool last_force_key_state = false;
        ULONGLONG current_time = GetTickCount64();
        bool force_key_pressed = GetAsyncKeyState(VK_F8) & 0x8000;
        bool force_reapply = force_key_pressed && !last_force_key_state;
        last_force_key_state = force_key_pressed;

        uinventory* inventory = nullptr;
        __try {
            inventory = shooter->get_inventory();
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            cache.Clear();
            return;
        }

        if (!inventory || !IsValidViewModelObject(inventory)) {
            cache.Clear();
            return;
        }

        currentequippable* weapon = nullptr;
        __try {
            weapon = inventory->get_current_equippable();
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            cache.Clear();
            return;
        }

        if (!weapon || !IsValidViewModelObject(weapon)) {
            cache.Clear();
            return;
        }

        bool needs_refresh = false;
        if (!cache.IsValid() ||
            weapon != cache.lastWeapon ||
            (current_time - cache.lastCacheTime) >= 2000 ||
            force_reapply) {
            needs_refresh = true;
        }

        if (needs_refresh) {
            cache.Clear();
            cache.lastCacheTime = current_time;
            cache.lastWeapon = weapon;

            __try {
                cache.mesh1p = shooter->GetMesh1P();
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {
                cache.Clear();
                return;
            }

            if (!cache.mesh1p || !IsValidViewModelObject(cache.mesh1p)) {
                cache.Clear();
                return;
            }

            __try {
                cache.overlayMesh = shooter->GetOverlayMesh1P();
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {}

            __try {
                cache.weaponMesh1P = weapon->GetMesh1P();
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {
                cache.Clear();
                return;
            }

            if (!cache.weaponMesh1P || !IsValidViewModelObject(cache.weaponMesh1P)) {
                cache.Clear();
                return;
            }

            uintptr_t cosmetic_ptr = (uintptr_t)weapon + 0x1188;
            if (IsValidViewModelPointer(cosmetic_ptr)) {
                __try {
                    cache.cosmeticMesh1P = memory::read<uskeletalmeshcomponent*>(cosmetic_ptr);
                }
                __except (EXCEPTION_EXECUTE_HANDLER) {}
            }

            auto meleeWeapon = GetLocalMeleeWeapon();
            if (meleeWeapon && IsValidViewModelObject(meleeWeapon)) {
                cache.lastMelee = meleeWeapon;

                __try {
                    cache.meleeMesh1P = meleeWeapon->GetMesh1P();
                }
                __except (EXCEPTION_EXECUTE_HANDLER) {
                    cache.meleeMesh1P = nullptr;
                }

                if (cache.meleeMesh1P) {
                    uintptr_t offhand_ptr = (uintptr_t)meleeWeapon + 0x1220;
                    if (IsValidViewModelPointer(offhand_ptr)) {
                        __try {
                            cache.offHandMesh = memory::read<uskeletalmeshcomponent*>(offhand_ptr);
                        }
                        __except (EXCEPTION_EXECUTE_HANDLER) {
                            cache.offHandMesh = nullptr;
                        }
                    }
                }
            }
        }

        if (!cache.IsValid() || !cache.mesh1p || !cache.weaponMesh1P) {
            return;
        }

        const uintptr_t flag_offset = 0x364;

        bool should_process_flags = false;
        fp_flag_store main_state;

        uintptr_t mesh_flag_addr = (uintptr_t)cache.mesh1p + flag_offset;
        if (SafeRead(mesh_flag_addr, main_state.raw)) {
            should_process_flags = (main_state.bits.f0 != 0) || force_reapply;
        }

        if (should_process_flags) {
            SafeProcessFlag(cache.mesh1p, flag_offset, true);

            if (cache.overlayMesh && IsValidViewModelObject(cache.overlayMesh)) {
                SafeProcessFlag(cache.overlayMesh, flag_offset, true);
            }

            if (cache.weaponMesh1P && IsValidViewModelObject(cache.weaponMesh1P)) {
                SafeProcessFlag(cache.weaponMesh1P, flag_offset, true);
            }

            if (cache.cosmeticMesh1P && IsValidViewModelObject(cache.cosmeticMesh1P)) {
                SafeProcessFlag(cache.cosmeticMesh1P, flag_offset, true);
            }

            if (cache.meleeMesh1P && IsValidViewModelObject(cache.meleeMesh1P)) {
                SafeProcessFlag(cache.meleeMesh1P, flag_offset, true);
            }

            if (cache.offHandMesh && IsValidViewModelObject(cache.offHandMesh)) {
                SafeProcessFlag(cache.offHandMesh, flag_offset, true);
            }
        }

        if (cache.mesh1p && IsValidViewModelObject(cache.mesh1p)) {
            SafeLockDescendants((USceneComponent*)cache.mesh1p);
        }

        if (cache.weaponMesh1P && IsValidViewModelObject(cache.weaponMesh1P)) {
            SafeLockDescendants((USceneComponent*)cache.weaponMesh1P);
        }

        if (cache.meleeMesh1P && IsValidViewModelObject(cache.meleeMesh1P)) {
            SafeLockDescendants((USceneComponent*)cache.meleeMesh1P);
        }
    }


    struct USceneComponentHelpers
    {
        static void Detach(void* Target)
        {
            static uobject* fn = nullptr;
            if (!fn)
                fn = uobject::find_object<uobject*>(L"Engine.SceneComponent.K2_DetachFromComponent");

            if (!fn || !Target) return;

            struct
            {
                int LocationRule;
                int RotationRule;
                int ScaleRule;
                bool bCallModify;
            } params;

            params.LocationRule = 0;
            params.RotationRule = 0;
            params.ScaleRule = 0;
            params.bCallModify = true;

            ((uobject*)Target)->process_event(fn, &params);
        }

        static void K2_DetachFromComponent(void* Target, int LocationRule, int RotationRule, int ScaleRule, bool bCallModify)
        {
            static uobject* Function = nullptr;
            if (!Function)
                Function = uobject::find_object<uobject*>(L"Engine.SceneComponent.K2_DetachFromComponent");

            if (!Function || !Target) return;

            struct
            {
                int LocationRule;
                int RotationRule;
                int ScaleRule;
                bool bCallModify;
            } params;

            params.LocationRule = LocationRule;
            params.RotationRule = RotationRule;
            params.ScaleRule = ScaleRule;
            params.bCallModify = bCallModify;

            ((uobject*)Target)->process_event(Function, &params);
        }

        static fname GetAttachSocketName(uskeletalmeshcomponent* TargetComponent)
        {
            static uobject* Function = nullptr;
            if (!Function)
                Function = uobject::find_object<uobject*>(L"Engine.SceneComponent.GetAttachSocketName");

            if (!Function || !TargetComponent) return fname();

            struct
            {
                fname ReturnValue;
            } params;

            TargetComponent->process_event(Function, &params);
            return params.ReturnValue;
        }

        static bool AttachTo(uskeletalmeshcomponent* Target, uskeletalmeshcomponent* Parent, fname SocketName,
            int LocationRule, int RotationRule, int ScaleRule, bool bWeldSimulatedBodies)
        {
            static uobject* Function = nullptr;
            if (!Function)
                Function = uobject::find_object<uobject*>(L"Engine.SceneComponent.K2_AttachToComponent");

            if (!Function || !Target) return false;

            struct
            {
                void* Parent;
                fname SocketName;
                int LocationRule;
                int RotationRule;
                int ScaleRule;
                bool bWeldSimulatedBodies;
                bool ReturnValue;
            } params;

            params.Parent = Parent;
            params.SocketName = SocketName;
            params.LocationRule = LocationRule;
            params.RotationRule = RotationRule;
            params.ScaleRule = ScaleRule;
            params.bWeldSimulatedBodies = bWeldSimulatedBodies;

            Target->process_event(Function, &params);
            return params.ReturnValue;
        }

        static void SetRelativeLocation(void* Target, const fvector& Location, bool bSweep = false, bool bTeleport = true)
        {
            static uobject* fn = nullptr;
            if (!fn)
                fn = uobject::find_object<uobject*>(L"Engine.SceneComponent.K2_SetRelativeLocation");

            if (!fn || !Target) return;

            struct
            {
                fvector NewLocation;
                bool bSweep;
                FHitResult SweepHitResult;
                bool bTeleport;
            } params;

            params.NewLocation = Location;
            params.bSweep = bSweep;
            params.bTeleport = bTeleport;
            memset(&params.SweepHitResult, 0, sizeof(FHitResult));

            ((uobject*)Target)->process_event(fn, &params);
        }

        static void SetRelativeRotation(void* Target, const FRotator& Rotation, bool bSweep = false, bool bTeleport = true)
        {
            static uobject* fn = nullptr;
            if (!fn)
                fn = uobject::find_object<uobject*>(L"Engine.SceneComponent.K2_SetRelativeRotation");

            if (!fn || !Target) return;

            struct
            {
                FRotator NewRotation;
                bool bSweep;
                FHitResult SweepHitResult;
                bool bTeleport;
            } params;

            params.NewRotation = Rotation;
            params.bSweep = bSweep;
            params.bTeleport = bTeleport;
            memset(&params.SweepHitResult, 0, sizeof(FHitResult));

            ((uobject*)Target)->process_event(fn, &params);
        }

        static uobject* ImportFileAsTexture2D(uworld* WorldContextObject, const fstring& Filename)
        {
            static uobject* fn = nullptr;
            if (!fn)
                fn = uobject::find_object<uobject*>(L"Engine.KismetRenderingLibrary.ImportFileAsTexture2D");

            if (!fn || !WorldContextObject) return nullptr;

            struct
            {
                uworld* WorldContextObject;
                fstring Filename;
                uobject* ReturnValue;
            } params;

            params.WorldContextObject = WorldContextObject;
            params.Filename = Filename;

            fn->process_event(fn, &params);
            return params.ReturnValue;
        }
    };

    //namespace sense
    //{
    //    namespace insta_lock_agents
    //    {
    //        uobject* astra = nullptr;
    //        uobject* breach = nullptr;
    //        uobject* brimstone = nullptr;
    //        uobject* chamber = nullptr;
    //        uobject* cypher = nullptr;
    //        uobject* fade = nullptr;
    //        uobject* jett = nullptr;
    //        uobject* kayo = nullptr;
    //        uobject* killjoy = nullptr;
    //        uobject* neon = nullptr;
    //        uobject* omen = nullptr;
    //        uobject* phoenix = nullptr;
    //        uobject* raze = nullptr;
    //        uobject* reyna = nullptr;
    //        uobject* sage = nullptr;
    //        uobject* skye = nullptr;
    //        uobject* sova = nullptr;
    //        uobject* viper = nullptr;
    //        uobject* yoru = nullptr;
    //        uobject* gekko = nullptr;

    //        void run()
    //        {
    //            auto enc_astra = Encrypt(L"Default__Rift_PrimaryAsset_C");
    //            astra = uobject::find_object<uobject*>(enc_astra.decrypt()), enc_astra.clear();

    //            auto enc_breach = Encrypt(L"Default__Breach_PrimaryAsset_C");
    //            breach = uobject::find_object<uobject*>(enc_breach.decrypt()), enc_breach.clear();

    //            auto enc_brimstone = Encrypt(L"Default__Sarge_PrimaryAsset_C");
    //            brimstone = uobject::find_object<uobject*>(enc_brimstone.decrypt()), enc_brimstone.clear();

    //            auto enc_chamber = Encrypt(L"Default__Deadeye_PrimaryAsset_C");
    //            chamber = uobject::find_object<uobject*>(enc_chamber.decrypt()), enc_chamber.clear();

    //            auto enc_cypher = Encrypt(L"Default__Gumshoe_PrimaryAsset_C");
    //            cypher = uobject::find_object<uobject*>(enc_cypher.decrypt()), enc_cypher.clear();

    //            auto enc_fade = Encrypt(L"Default__BountyHunter_PrimaryAsset_C");
    //            fade = uobject::find_object<uobject*>(enc_fade.decrypt()), enc_fade.clear();

    //            auto enc_jett = Encrypt(L"Default__Wushu_PrimaryAsset_C");
    //            jett = uobject::find_object<uobject*>(enc_jett.decrypt()), enc_jett.clear();

    //            auto enc_kayo = Encrypt(L"Default__Grenadier_PrimaryAsset_C");
    //            kayo = uobject::find_object<uobject*>(enc_kayo.decrypt()), enc_kayo.clear();

    //            auto enc_killjoy = Encrypt(L"Default__Killjoy_PrimaryAsset_C");
    //            killjoy = uobject::find_object<uobject*>(enc_killjoy.decrypt()), enc_killjoy.clear();

    //            auto enc_neon = Encrypt(L"Default__Sprinter_PrimaryAsset_C");
    //            neon = uobject::find_object<uobject*>(enc_neon.decrypt()), enc_neon.clear();

    //            auto enc_omen = Encrypt(L"Default__Wraith_PrimaryAsset_C");
    //            omen = uobject::find_object<uobject*>(enc_omen.decrypt()), enc_omen.clear();

    //            auto enc_phoenix = Encrypt(L"Default__Phoenix_PrimaryAsset_C");
    //            phoenix = uobject::find_object<uobject*>(enc_phoenix.decrypt()), enc_phoenix.clear();

    //            auto enc_raze = Encrypt(L"Default__Clay_PrimaryAsset_C");
    //            raze = uobject::find_object<uobject*>(enc_raze.decrypt()), enc_raze.clear();

    //            auto enc_reyna = Encrypt(L"Default__Vampire_PrimaryAsset_C");
    //            reyna = uobject::find_object<uobject*>(enc_reyna.decrypt()), enc_reyna.clear();

    //            auto enc_sage = Encrypt(L"Default__Thorne_PrimaryAsset_C");
    //            sage = uobject::find_object<uobject*>(enc_sage.decrypt()), enc_sage.clear();

    //            auto enc_skye = Encrypt(L"Default__guide_PrimaryAsset_C");
    //            skye = uobject::find_object<uobject*>(enc_skye.decrypt()), enc_skye.clear();

    //            auto enc_sova = Encrypt(L"Default__Hunter_PrimaryAsset_C");
    //            sova = uobject::find_object<uobject*>(enc_sova.decrypt()), enc_sova.clear();

    //            auto enc_viper = Encrypt(L"Default__Pandemic_PrimaryAsset_C");
    //            viper = uobject::find_object<uobject*>(enc_viper.decrypt()), enc_viper.clear();

    //            auto enc_yoru = Encrypt(L"Default__Stealth_PrimaryAsset_C");
    //            yoru = uobject::find_object<uobject*>(enc_yoru.decrypt()), enc_yoru.clear();

    //            auto enc_gekko = Encrypt(L"Default__AggroBot_PrimaryAsset_C");
    //            gekko = uobject::find_object<uobject*>(enc_gekko.decrypt()), enc_gekko.clear();
    //        }

    //        uobject* get_agent_object(int id)
    //        {
    //            if (id == 0) return astra;
    //            else if (id == 1) return breach;
    //            else if (id == 2) return brimstone;
    //            else if (id == 3) return chamber;
    //            else if (id == 4) return cypher;
    //            else if (id == 5) return fade;
    //            else if (id == 6) return jett;
    //            else if (id == 7) return kayo;
    //            else if (id == 8) return killjoy;
    //            else if (id == 9) return neon;
    //            else if (id == 10) return omen;
    //            else if (id == 11) return phoenix;
    //            else if (id == 12) return raze;
    //            else if (id == 13) return reyna;
    //            else if (id == 14) return sage;
    //            else if (id == 15) return skye;
    //            else if (id == 16) return sova;
    //            else if (id == 17) return viper;
    //            else if (id == 18) return yoru;
    //            else if (id == 19) return gekko;
    //            else return nullptr;
    //        }
    //    }

    //    namespace insta_lock
    //    {
    //        int old_time = NULL;
    //        int agent_counter = 0;

    //        static void agent_roulette(aplayercontroller* controller) {
    //            static uobject* _class = nullptr;
    //            if (!_class)
    //                _class = uobject::find_object<uobject*>(crypt(L"ShooterGame.PregamePlayerController"));
    //            if (math::class_is_child_of(controller->class_private, _class))
    //                if (pregame_view_controller* pregame_view_controller = controller->get_pregame_view_controller())
    //                    if (pregame_view_model* pregame_view_model = pregame_view_controller->get_pregame_view_model())
    //                        if (!pregame_view_model->is_local_player_locked_in())
    //                        {
    //                            if (!old_time) old_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    //                            int current_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    //                            if (current_time > old_time)
    //                            {
    //                                old_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() + 50;
    //                                pregame_view_controller->select_character(insta_lock_agents::get_agent_object(agent_counter));

    //                                agent_counter++;
    //                                if (agent_counter >= 20)
    //                                    agent_counter = 0;

    //                            }
    //                        }
    //                        else if (globals::il::random_agent == true)
    //                            globals::il::random_agent = false;
    //        }

    //        void run(aplayercontroller* controller)
    //        {
    //            if (globals::il::random_agent)
    //                agent_roulette(controller);

    //            if (globals::il::enable) {
    //                static uobject* _class = nullptr;
    //                if (!_class)
    //                    _class = uobject::find_object<uobject*>(crypt(L"ShooterGame.PregamePlayerController"));
    //                if (math::class_is_child_of(controller->class_private, _class))
    //                    if (pregame_view_controller* pregame_view_controller = controller->get_pregame_view_controller())
    //                        if (pregame_view_model* pregame_view_model = pregame_view_controller->get_pregame_view_model())
    //                            if (!pregame_view_model->is_local_player_locked_in())
    //                                if (insta_lock_agents::get_agent_object(globals::il::lock_agent))
    //                                {
    //                                    pregame_view_controller->lock_character(insta_lock_agents::get_agent_object(globals::il::lock_agent));
    //                                    globals::il::enable = false;
    //                                }

    //            }
    //        }
    //    }
    //}



#pragma once
#include <array>
#include <algorithm>
#include <map>
#include <cmath>
#include <vector>
#include <cfloat>
#include <unordered_map>
#include <string>

float AngleDiff(float a, float b) {
    float diff = fmod(b - a + 180.0f, 360.0f) - 180.0f;
    return diff < -180.0f ? diff + 360.0f : diff;
}

namespace resolver_math {
    __forceinline float AngleDiff(float a, float b) {
        float diff = fmod(b - a + 180.0f, 360.0f) - 180.0f;
        return diff < -180.0f ? diff + 360.0f : diff;
    }
    __forceinline float clamp(float value, float min_val, float max_val) {
        return value < min_val ? min_val : (value > max_val ? max_val : value);
    }
    __forceinline float lerp(float a, float b, float t) { return a + t * (b - a); }
}

template<typename T, size_t N>
struct UltimateCircularBuffer {
    std::array<T, N> data;
    size_t head = 0;
    size_t size = 0;

    __forceinline void push_back(const T& value) {
        data[head] = value;
        head = (head + 1) % N;
        size = (size < N) ? size + 1 : N;
    }

    __forceinline T& operator[](size_t index) { return data[(head + N - size + index) % N]; }
    __forceinline const T& operator[](size_t index) const { return data[(head + N - size + index) % N]; }
    __forceinline T& back() { return (*this)[size - 1]; }
    __forceinline T& front() { return (*this)[0]; }
    __forceinline bool empty() const { return size == 0; }
    __forceinline void clear() { size = 0; head = 0; }
};

struct UltimateResolverData {
    UltimateCircularBuffer<frotator, 48> rotation_history;
    UltimateCircularBuffer<fvector, 32> position_history;
    UltimateCircularBuffer<fvector, 24> velocity_history;
    UltimateCircularBuffer<float, 96> yaw_pattern;
    UltimateCircularBuffer<float, 96> pitch_pattern;

    UltimateCircularBuffer<float, 32> movement_angles;
    UltimateCircularBuffer<float, 32> acceleration_pattern;
    UltimateCircularBuffer<bool, 64> visibility_history;

    float base_yaw = 0.0f;
    float real_yaw = 0.0f;
    float fake_yaw = 0.0f;
    float pattern_frequency = 0.0f;
    float pattern_amplitude = 0.0f;
    float resolver_confidence = 1.0f;
    float last_successful_resolve = 0.0f;
    float desync_range = 58.0f;

    uint32_t pattern_analysis_ticks = 0;
    uint32_t shots_fired = 0;
    uint32_t shots_hit = 0;
    uint32_t resolver_updates = 0;

    int8_t pattern_type = 0;
    int8_t resolved_side = 0;
    int8_t last_resolved_side = 0;
    int8_t network_role = 0;

    bool was_moving : 1;
    bool requires_prediction : 1;
    bool is_desyncing : 1;
    bool was_visible : 1;
    bool brute_force_active : 1;
    bool adaptive_learning : 1;

    int8_t brute_force_step = 0;
    float brute_force_timer = 0.0f;
    std::array<bool, 8> attempted_sides = { false };

    fvector last_resolved_head_pos;
    fvector last_original_head_pos;
    fvector last_predicted_pos;
    float last_confidence = 0.0f;
    int last_pattern_type = 0;

    UltimateResolverData() : was_moving(false), requires_prediction(false),
        is_desyncing(false), was_visible(false), brute_force_active(false),
        adaptive_learning(true) {
    }
};

static std::array<UltimateResolverData, 64> ultimate_resolver_states;
static std::array<ashootercharacter*, 64> resolver_target_map;
static std::array<float, 64> resolver_confidence_cache;
static uint32_t resolver_frame_counter = 0;
static uint32_t last_cleanup_frame = 0;

class UltimateValorantResolver {
private:
    ashootercharacter* m_target;
    ashootercharacter* m_local;
    UltimateResolverData* m_data;
    uint32_t m_target_index;
    float m_current_time;
    float m_last_update_time;

    float m_position_variance = 0.0f;
    float m_movement_consistency = 0.0f;
    float m_pattern_entropy = 0.0f;
    float m_yaw_variance = 0.0f;
    float m_pitch_variance = 0.0f;

public:
    UltimateValorantResolver(ashootercharacter* target, ashootercharacter* local)
        : m_target(target), m_local(local), m_current_time(0.0f), m_last_update_time(0.0f) {
        m_target_index = FindOrCreateTargetIndex(target);
        m_data = &ultimate_resolver_states[m_target_index];
        m_current_time = GetTickCount64() * 0.001f;
        m_last_update_time = m_current_time;
        InitializeResolver();
    }

    ~UltimateValorantResolver() {}

    fvector ResolveHeadPosition(fvector current_head, fvector velocity) {
        if (!IsValidForResolution()) return current_head;

        float delta_time = m_current_time - m_last_update_time;
        m_current_time = GetTickCount64() * 0.001f;

        UpdateTargetData();

        AnalyzeMovementAdvanced();
        AnalyzePositionPatterns();
        AnalyzeRotationAdvanced();
        AnalyzeNetworkStateAdvanced();
        AnalyzeVisibilityPattern();
        AnalyzeStrafingPatterns();

        fvector resolved_position = ApplyPositionResolution(current_head, velocity);

        m_data->last_successful_resolve = m_current_time;
        m_data->resolver_updates++;
        m_last_update_time = m_current_time;

        return resolved_position;
    }

    void RegisterShotFired() {
        m_data->shots_fired++;
        UpdateConfidenceMetrics();
    }

    void RegisterShotHit() {
        m_data->shots_hit++;
        UpdateConfidenceMetrics();
        if (m_data->shots_hit > 5) {
            float hit_ratio = float(m_data->shots_hit) / float(m_data->shots_fired);
            m_data->resolver_confidence = min(1.0f, hit_ratio + 0.1f);
            if (hit_ratio > 0.8f) m_data->adaptive_learning = false;
        }
    }

    float GetConfidence() const { return m_data->resolver_confidence; }
    int GetPatternType() const { return m_data->pattern_type; }
    UltimateResolverData* GetResolverData() const { return m_data; }

    void UpdateVisualizationData(fvector original_head, fvector resolved_head) {
        m_data->last_original_head_pos = original_head;
        m_data->last_resolved_head_pos = resolved_head;
        m_data->last_confidence = m_data->resolver_confidence;
        m_data->last_pattern_type = m_data->pattern_type;
    }

private:
    uint32_t FindOrCreateTargetIndex(ashootercharacter* target) {
        for (uint32_t i = 0; i < 64; i++) {
            if (resolver_target_map[i] == target) {
                resolver_confidence_cache[i] = ultimate_resolver_states[i].resolver_confidence;
                return i;
            }
        }

        uint32_t oldest_index = resolver_frame_counter % 64;
        for (uint32_t i = 0; i < 64; i++) {
            if (resolver_target_map[i] == nullptr) {
                oldest_index = i;
                break;
            }
        }

        resolver_target_map[oldest_index] = target;
        ultimate_resolver_states[oldest_index] = UltimateResolverData();
        resolver_confidence_cache[oldest_index] = 1.0f;

        return oldest_index;
    }

    bool IsValidForResolution() const {
        if (!m_target || !m_local) return false;
        if (!m_target->is_alive() || !m_local->is_alive()) return false;

        fvector target_pos = m_target->k2_get_actor_location();
        fvector local_pos = m_local->k2_get_actor_location();
        float distance = (target_pos - local_pos).size();
        return distance > 0.0f && distance < 5000.0f;
    }

    void InitializeResolver() {
        m_data->brute_force_active = false;
        m_data->brute_force_step = 0;
        m_data->brute_force_timer = 0.0f;
        m_data->attempted_sides.fill(false);
    }

    void UpdateTargetData() {
        frotator current_rot = m_target->k2_get_actor_rotation();
        fvector current_pos = m_target->k2_get_actor_location();
        fvector current_vel = m_target->GetVelocity();

        m_data->rotation_history.push_back(current_rot);
        m_data->position_history.push_back(current_pos);
        m_data->velocity_history.push_back(current_vel);
        m_data->yaw_pattern.push_back(current_rot.yaw);
        m_data->pitch_pattern.push_back(current_rot.pitch);

        fvector head_pos = m_target->get_mesh()->get_bone_location(8);

        bool is_visible = true;
        m_data->visibility_history.push_back(is_visible);

        m_data->pattern_analysis_ticks++;
        resolver_frame_counter++;
    }

    void AnalyzeMovementAdvanced() {
        if (m_data->velocity_history.size < 3) return;

        fvector current_vel = m_data->velocity_history.back();
        fvector previous_vel = m_data->velocity_history[m_data->velocity_history.size - 2];
        float speed = current_vel.size();
        m_data->was_moving = (speed > 10.0f);
        m_data->requires_prediction = (speed > 2.0f);

        if (speed > 1.0f) {
            float movement_angle = atan2(current_vel.y, current_vel.x) * (180.0f / 3.14159265358979323846f);
            m_data->movement_angles.push_back(movement_angle);
        }
        AnalyzeMovementConsistency();
    }

    void AnalyzeMovementConsistency() {
        if (m_data->movement_angles.size < 4) return;

        float consistency = 0.0f;
        for (size_t i = 1; i < m_data->movement_angles.size; i++) {
            float diff = std::abs(AngleDiff(m_data->movement_angles[i], m_data->movement_angles[i - 1]));
            consistency += (1.0f - (diff / 180.0f));
        }
        m_movement_consistency = consistency / (m_data->movement_angles.size - 1);
    }

    void AnalyzeStrafingPatterns() {
        if (m_data->velocity_history.size < 8) return;

        int direction_changes = 0;
        fvector prev_dir = m_data->velocity_history[0];

        for (size_t i = 1; i < m_data->velocity_history.size; i++) {
            fvector current_dir = m_data->velocity_history[i];
            float dot = prev_dir.dot(current_dir) / (prev_dir.size() * current_dir.size());

            if (dot < -0.5f) {
                direction_changes++;
            }
            prev_dir = current_dir;
        }

        if (direction_changes > m_data->velocity_history.size / 3) {
            m_data->is_desyncing = true;
        }
    }

    void AnalyzeRotationAdvanced() {
        if (m_data->yaw_pattern.size < 8) return;

        CalculateYawStatistics();
        DetectPatternType();
        CalculatePatternMetrics();
        AnalyzeDesyncRange();
    }

    void CalculateYawStatistics() {
        float sum = 0.0f, sum_sq = 0.0f;
        float min_yaw = FLT_MAX, max_yaw = -FLT_MAX;
        for (size_t i = 0; i < m_data->yaw_pattern.size; i++) {
            float yaw = m_data->yaw_pattern[i];
            sum += yaw;
            sum_sq += yaw * yaw;
            min_yaw = min(min_yaw, yaw);
            max_yaw = max(max_yaw, yaw);
        }
        float mean = sum / m_data->yaw_pattern.size;
        m_yaw_variance = (sum_sq / m_data->yaw_pattern.size) - (mean * mean);
        m_data->pattern_amplitude = max_yaw - min_yaw;
        m_data->base_yaw = mean;
    }

    void DetectPatternType() {
        if (m_yaw_variance > 5000.0f) {
            m_data->pattern_type = 1; // Spin
        }
        else if (m_yaw_variance > 500.0f && m_data->pattern_amplitude < 180.0f) {
            m_data->pattern_type = 2; // Jitter
        }
        else if (m_yaw_variance > 100.0f && m_data->pattern_amplitude > 45.0f) {
            m_data->pattern_type = 3; // Desync
        }
        else if (m_yaw_variance < 50.0f && m_data->was_moving) {
            m_data->pattern_type = 4; // Static while moving
        }
        else {
            m_data->pattern_type = 0; // Legit
        }
    }

    void CalculatePatternMetrics() {
        if (m_data->yaw_pattern.size < 16) return;

        int best_lag = 1;
        float max_correlation = -1.0f;

        for (int lag = 1; lag <= 8; lag++) {
            float correlation = 0.0f;
            int count = 0;

            for (size_t i = lag; i < m_data->yaw_pattern.size; i++) {
                correlation += std::cos(AngleDiff(m_data->yaw_pattern[i], m_data->yaw_pattern[i - lag]) * (3.14159265358979323846f / 180.0f));
                count++;
            }

            if (count > 0) {
                correlation /= count;
                if (correlation > max_correlation) {
                    max_correlation = correlation;
                    best_lag = lag;
                }
            }
        }

        m_data->pattern_frequency = (best_lag > 0) ? (1.0f / best_lag) : 0.0f;
    }

    void AnalyzeDesyncRange() {
        if (m_data->yaw_pattern.size < 12) return;

        std::map<float, int> angle_counts;
        for (size_t i = 0; i < m_data->yaw_pattern.size; i++) {
            float rounded = std::round(m_data->yaw_pattern[i] / 5.0f) * 5.0f;
            angle_counts[rounded]++;
        }

        float primary_angle = 0.0f;
        int max_count = 0;
        for (const auto& pair : angle_counts) {
            if (pair.second > max_count) {
                max_count = pair.second;
                primary_angle = pair.first;
            }
        }

        float secondary_angle = 0.0f;
        int second_count = 0;
        for (const auto& pair : angle_counts) {
            if (pair.second > second_count && std::abs(pair.first - primary_angle) > 10.0f) {
                second_count = pair.second;
                secondary_angle = pair.first;
            }
        }

        m_data->desync_range = std::abs(AngleDiff(primary_angle, secondary_angle));
    }

    void AnalyzeNetworkStateAdvanced() {
        m_data->network_role = m_target->GetLocalRole();

        switch (m_data->network_role) {
        case 3: // SimProxy
            m_data->resolver_confidence *= 1.1f;
            break;
        case 2: // AutoProxy
            m_data->resolver_confidence *= 0.9f;
            break;
        default:
            m_data->resolver_confidence *= 0.8f;
            break;
        }

        m_data->resolver_confidence = std::clamp(m_data->resolver_confidence, 0.1f, 1.0f);
    }

    void AnalyzeVisibilityPattern() {
        if (m_data->visibility_history.size < 8) return;

        int visible_count = 0;
        for (size_t i = 0; i < m_data->visibility_history.size; i++) {
            if (m_data->visibility_history[i]) visible_count++;
        }

        float visibility_ratio = float(visible_count) / m_data->visibility_history.size;
        m_data->was_visible = (visibility_ratio > 0.7f);
    }

    void AnalyzePositionPatterns() {
        if (m_data->position_history.size < 8) return;

        CalculatePositionStatistics();
    }

    void CalculatePositionStatistics() {
        if (m_data->position_history.size < 8) return;

        fvector sum = fvector(0, 0, 0);
        fvector sum_sq = fvector(0, 0, 0);

        for (size_t i = 0; i < m_data->position_history.size; i++) {
            fvector pos = m_data->position_history[i];
            sum = sum + pos;
            sum_sq.x += pos.x * pos.x;
            sum_sq.y += pos.y * pos.y;
            sum_sq.z += pos.z * pos.z;
        }

        fvector mean = sum / float(m_data->position_history.size);
        m_position_variance = (sum_sq.x / m_data->position_history.size) - (mean.x * mean.x);
    }

    fvector ApplyPositionResolution(fvector current_head, fvector velocity) {
        switch (m_data->pattern_type) {
        case 1: return ResolveSpinAA(current_head, velocity);
        case 2: return ResolveJitterAA(current_head, velocity);
        case 3: return ResolveDesyncAA(current_head, velocity);
        case 4: return ResolveStaticAA(current_head, velocity);
        default: return ResolveLegitAA(current_head, velocity);
        }
    }

    fvector ResolveSpinAA(fvector head, fvector velocity) {
        const float prediction_time = 0.1f;
        fvector predicted = head + velocity * prediction_time;

        if (m_data->pattern_frequency > 0.1f) {
            float phase = fmod(m_current_time * m_data->pattern_frequency * 360.0f, 360.0f);
            float radius = m_data->desync_range * 0.5f;
            predicted.x += cos(phase * (3.14159265358979323846f / 180.0f)) * radius;
            predicted.y += sin(phase * (3.14159265358979323846f / 180.0f)) * radius;
        }

        return predicted;
    }

    fvector ResolveJitterAA(fvector head, fvector velocity) {
        if (m_data->position_history.size < 4) return head;

        std::vector<fvector> valid_positions;
        fvector mean = head;

        for (size_t i = 0; i < m_data->position_history.size; i++) {
            fvector pos = m_data->position_history[i];
            float distance = (pos - mean).size();
            if (distance < 50.0f) {
                valid_positions.push_back(pos);
            }
        }

        if (!valid_positions.empty()) {
            fvector sum = fvector(0, 0, 0);
            for (const fvector& pos : valid_positions) sum = sum + pos;
            return sum / float(valid_positions.size());
        }

        return head;
    }

    fvector ResolveDesyncAA(fvector head, fvector velocity) {
        float side_multiplier = DetermineOptimalSide();

        float position_offset = m_data->desync_range * 0.1f * side_multiplier;

        fvector right_vec = m_target->GetActorRightVector();
        fvector corrected = head + right_vec * position_offset;

        if (velocity.size() > 5.0f) {
            corrected = corrected + velocity * 0.05f;
        }

        return corrected;
    }

    fvector ResolveStaticAA(fvector head, fvector velocity) {
        if (m_data->was_moving && !m_data->movement_angles.empty()) {
            float movement_angle = m_data->movement_angles.back();
            float movement_rad = movement_angle * (3.14159265358979323846f / 180.0f);

            head.x += cos(movement_rad) * 5.0f;
            head.y += sin(movement_rad) * 5.0f;
        }
        return head;
    }

    fvector ResolveLegitAA(fvector head, fvector velocity) {
        if (velocity.size() > 2.0f) {
            return head + velocity * 0.05f;
        }
        return head;
    }

    float DetermineOptimalSide() {
        float movement_side = DetermineMovementSide();
        float history_side = DetermineHistoricalSide();
        return (movement_side * 0.7f) + (history_side * 0.3f);
    }

    float DetermineMovementSide() {
        if (m_data->velocity_history.empty()) return 0.0f;

        fvector velocity = m_data->velocity_history.back();
        if (velocity.size() < 5.0f) return 0.0f;

        fvector right_vec = m_target->GetActorRightVector();
        float dot = velocity.dot(right_vec) / velocity.size();
        return (dot > 0.0f) ? 1.0f : -1.0f;
    }

    float DetermineHistoricalSide() {
        if (m_data->resolved_side == 0) return 0.0f;
        return (m_data->resolved_side > 0) ? 1.0f : -1.0f;
    }

    void UpdateConfidenceMetrics() {
        if (m_data->shots_fired > 0) {
            float hit_ratio = float(m_data->shots_hit) / float(m_data->shots_fired);
            if (hit_ratio > 0.7f) m_data->resolver_confidence = min(1.0f, m_data->resolver_confidence + 0.05f);
            else if (hit_ratio < 0.3f) m_data->resolver_confidence = max(0.1f, m_data->resolver_confidence - 0.1f);
        }
    }
};

class ResolverVisualizer {
private:
    static float m_pulse_time;
    static float m_rainbow_hue;
    static float m_hitmarker_time;
    static uobject* m_font; 

public:
   
    static void SetFont(uobject* font) {
        m_font = font;
    }

    static void DrawModernResolverInfo(ucanvas* canvas, aplayercontroller* controller,
        ashootercharacter* target, UltimateResolverData* resolver_data) {
        try {
            if (!canvas || !controller || !target || !resolver_data || !m_font) return; 

            m_pulse_time += 0.02f;
            if (m_pulse_time > 6.28318530718f) m_pulse_time = 0.0f;

            m_rainbow_hue += 0.001f;
            if (m_rainbow_hue > 1.0f) m_rainbow_hue = 0.0f;

            if (m_hitmarker_time > 0.0f) {
                m_hitmarker_time -= 0.05f;
            }

            fvector2d original_screen, resolved_screen;
            bool original_visible = false;
            bool resolved_visible = false;

            try {
                original_visible = controller->project_world_location_to_screen(resolver_data->last_original_head_pos, original_screen, true);
                resolved_visible = controller->project_world_location_to_screen(resolver_data->last_resolved_head_pos, resolved_screen, true);
            }
            catch (...) {
                return;
            }

            if (original_visible && resolved_visible) {
                try {
                    DrawAdvanced3DVisualization(canvas, original_screen, resolved_screen, resolver_data);
                }
                catch (...) {}
            }

            try {
                DrawModernResolverHUD(canvas, resolver_data, original_screen);
            }
            catch (...) {}

            if (m_hitmarker_time > 0.0f && resolved_visible) {
                try {
                    DrawModernHitmarker(canvas, resolved_screen, resolver_data->last_confidence);
                }
                catch (...) {}
            }
        }
        catch (...) {}
    }

    static void RegisterHit() {
        try {
            m_hitmarker_time = 2.0f;
        }
        catch (...) {}
    }

private:
    static void DrawAdvanced3DVisualization(ucanvas* canvas, const fvector2d& original,
        const fvector2d& resolved, UltimateResolverData* data) {
        try {
            if (!canvas || !data) return;

            float pulse = (sin(m_pulse_time) + 1.0f) * 0.5f;
            flinearcolor high_conf_color = { 0.0f, 1.0f, 0.0f, 1.0f };
            flinearcolor low_conf_color = { 1.0f, 0.0f, 0.0f, 1.0f };
            flinearcolor confidence_color = LerpColor(low_conf_color, high_conf_color, data->last_confidence);

            if (data->last_confidence > 0.8f) {
                confidence_color = HueToRGB(m_rainbow_hue);
                confidence_color.a = 0.8f + pulse * 0.2f;
            }

            
            if (!data->velocity_history.empty() && data->velocity_history.back().size() > 10.0f) {
                DrawMovementSphere(canvas, resolved);
            }

           
            DrawSimpleMarker(canvas, original, { 1.0f, 1.0f, 1.0f, 0.8f });
            DrawSimpleMarker(canvas, resolved, confidence_color);
        }
        catch (...) {}
    }

    static void DrawModernResolverHUD(ucanvas* canvas, UltimateResolverData* data, const fvector2d& screen_pos) {
        try {
            if (!canvas || !data) return;

            fvector2d hud_pos = { screen_pos.x - 42.5f, screen_pos.y - 140.0f };
            
            DrawModernPanel(canvas, hud_pos, { 120.0f, 110.0f }, { 0.08f, 0.08f, 0.12f, 0.95f });
            
            flinearcolor header_color = HueToRGB(m_rainbow_hue);
            float panel_center_x = hud_pos.x + (120.0f / 2.0f);
            
            DrawTextSafe(canvas, L"RESOLVER", { panel_center_x - 6.0f, hud_pos.y + 5.0f }, header_color, 0.8f);
            canvas->k2_drawline({ hud_pos.x + 10.0f, hud_pos.y + 22.0f }, { hud_pos.x + 110.0f, hud_pos.y + 22.0f }, 1.2f, { 0.3f, 0.3f, 0.4f, 0.7f });
            
            DrawAdvancedProgressBar(canvas, { hud_pos.x + 10.0f, hud_pos.y + 28.0f }, 100.0f, data->last_confidence, L"CONFIDENCE");
            float velocity_progress = 0.0f;
            if (!data->velocity_history.empty()) {
                velocity_progress = resolver_math::clamp(data->velocity_history.back().size() / 500.0f, 0.0f, 1.0f);
            }
            
            DrawAdvancedProgressBar(canvas, { hud_pos.x + 10.0f, hud_pos.y + 43.0f }, 100.0f, velocity_progress, L"VELOCITY");
            float prediction_progress = data->pattern_frequency;
            
            DrawAdvancedProgressBar(canvas, { hud_pos.x + 10.0f, hud_pos.y + 58.0f }, 100.0f, prediction_progress, L"PREDICTION");
            std::wstring desync_text = L"DESYNC: " + std::to_wstring((int)data->desync_range) + L"°";
            
            DrawTextSafe(canvas, desync_text.c_str(), { hud_pos.x + 10.0f, hud_pos.y + 73.0f }, { 0.8f, 0.8f, 1.0f, 1.0f }, 0.5f);
            std::wstring pattern_text = GetPatternTypeName(data->last_pattern_type);
            
            DrawTextSafe(canvas, pattern_text.c_str(), { hud_pos.x + 70.0f, hud_pos.y + 73.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, 0.5f);
            std::wstring shots_text = L"SHOTS: " + std::to_wstring(data->shots_fired);
           
            DrawTextSafe(canvas, shots_text.c_str(), { hud_pos.x + 10.0f, hud_pos.y + 85.0f }, { 0.9f, 0.9f, 0.9f, 0.9f }, 0.45f);
            if (data->shots_fired > 0) {
                float hit_rate = (float)data->shots_hit / (float)data->shots_fired * 100.0f;
                std::wstring hit_text = L"HIT: " + std::to_wstring((int)hit_rate) + L"%";
                DrawTextSafe(canvas, hit_text.c_str(), { hud_pos.x + 70.0f, hud_pos.y + 85.0f }, { 0.7f, 1.0f, 0.7f, 0.9f }, 0.45f);
            }

           
            std::wstring state_text = data->resolver_confidence > 0.7f ? L"OPTIMAL" : L"LEARNING";
            flinearcolor state_color = data->resolver_confidence > 0.7f ? flinearcolor{ 0.2f, 0.8f, 0.2f, 0.9f } : flinearcolor{ 0.8f, 0.8f, 0.2f, 0.9f };
            DrawTextSafe(canvas, state_text.c_str(), { hud_pos.x + 10.0f, hud_pos.y + 97.0f }, state_color, 0.45f);
        }
        catch (...) {}
    }


    static void DrawMovementSphere(ucanvas* canvas, const fvector2d& center) {
        try {
            if (!canvas) return;

            float sphere_radius = 6.0f;
            flinearcolor sphere_color = { 1.0f, 1.0f, 1.0f, 0.7f };

      
            int segments = 8;
            for (int i = 0; i < segments; i++) {
                float angle1 = (i * 2 * 3.14159265358979323846f) / segments;
                float angle2 = ((i + 1) * 2 * 3.14159265358979323846f) / segments;

                fvector2d point1 = center + fvector2d(cos(angle1) * sphere_radius, sin(angle1) * sphere_radius);
                fvector2d point2 = center + fvector2d(cos(angle2) * sphere_radius, sin(angle2) * sphere_radius);

                canvas->k2_drawline(point1, point2, 1.5f, sphere_color);
            }
        }
        catch (...) {}
    }

    static void DrawSimpleMarker(ucanvas* canvas, const fvector2d& position, const flinearcolor& color) {
        try {
            if (!canvas) return;

            float size = 4.0f;
            canvas->k2_drawline({ position.x - size, position.y }, { position.x + size, position.y }, 1.5f, color);
            canvas->k2_drawline({ position.x, position.y - size }, { position.x, position.y + size }, 1.5f, color);
        }
        catch (...) {}
    }

    static void DrawAdvancedProgressBar(ucanvas* canvas, const fvector2d& position, float width,
        float progress, const wchar_t* label) {
        try {
            if (!canvas) return;

            // BACKGROUND - ESKİ HALİ
            fvector2d bg_start = position;
            fvector2d bg_end = { position.x + width, position.y };
            canvas->k2_drawline(bg_start, bg_end, 4.0f, { 0.2f, 0.2f, 0.2f, 0.9f });

            // PROGRESS - ESKİ RENKLER
            flinearcolor progress_color;
            if (progress < 0.3f) progress_color = { 1.0f, 0.0f, 0.0f, 0.9f };
            else if (progress < 0.7f) progress_color = { 1.0f, 1.0f, 0.0f, 0.9f };
            else progress_color = { 0.0f, 1.0f, 0.0f, 0.9f };

            fvector2d progress_end = { position.x + width * progress, position.y };
            canvas->k2_drawline(position, progress_end, 4.0f, progress_color);

            // LABEL - ESKİ HALİ
            std::wstring progress_text = std::to_wstring(int(progress * 100)) + L"%";

            // LABEL YAZISI
            canvas->k2_drawtext(m_font, fstring(label), { position.x, position.y - 8.0f }, { 0.5f, 0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, 0.0f,
                { 0,0,0,0.8f }, { 1,1 }, true, true, true, { 0,0,0,0.8f });

            // YÜZDE DEĞERİ
            canvas->k2_drawtext(m_font, fstring(progress_text.c_str()), { position.x + width + 2.0f, position.y - 8.0f }, { 0.5f, 0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, 0.0f,
                { 0,0,0,0.8f }, { 1,1 }, true, true, true, { 0,0,0,0.8f });
        }
        catch (...) {}
    }

    static void DrawModernPanel(ucanvas* canvas, const fvector2d& position, const fvector2d& size,
        const flinearcolor& color) {
        try {
            if (!canvas) return;

            fvector2d points[4] = {
                position,
                {position.x + size.x, position.y},
                {position.x + size.x, position.y + size.y},
                {position.x, position.y + size.y}
            };

            // DAHA KALIN ÇERÇEVE
            for (int i = 0; i < 4; i++) {
                int next = (i + 1) % 4;
                canvas->k2_drawline(points[i], points[next], 1.5f, color);
            }

            // DAHA BELİRGİN GRADIENT BORDER
            flinearcolor top_border_color = { 0.4f, 0.6f, 0.9f, 0.7f };
            canvas->k2_drawline(points[0], points[1], 1.2f, top_border_color);
        }
        catch (...) {}
    }

    static void DrawModernHitmarker(ucanvas* canvas, const fvector2d& position, float confidence) {
        try {
            if (!canvas) return;

            float hitmarker_size = 8.0f + m_hitmarker_time * 3.0f;
            float pulse = (sin(m_hitmarker_time * 10.0f) + 1.0f) * 0.5f;

            flinearcolor hitmarker_color = { 1.0f, 1.0f, 0.0f, 0.8f * pulse };

            canvas->k2_drawline({ position.x - hitmarker_size, position.y }, { position.x - 2.0f, position.y }, 2.0f, hitmarker_color);
            canvas->k2_drawline({ position.x + hitmarker_size, position.y }, { position.x + 2.0f, position.y }, 2.0f, hitmarker_color);
            canvas->k2_drawline({ position.x, position.y - hitmarker_size }, { position.x, position.y - 2.0f }, 2.0f, hitmarker_color);
            canvas->k2_drawline({ position.x, position.y + hitmarker_size }, { position.x, position.y + 2.0f }, 2.0f, hitmarker_color);
        }
        catch (...) {}
    }

    static void DrawTextSafe(ucanvas* canvas, const wchar_t* text, const fvector2d& position,
        const flinearcolor& color, float scale) {
        try {
            if (!canvas || !text || !m_font) return; 
            canvas->k2_drawtext(m_font, fstring(text), position, { scale, scale }, color, 0.0f,
                { 0,0,0,0 }, { 0,0 }, true, true, true, { 0,0,0,0 });
        }
        catch (...) {}
    }

    static flinearcolor HueToRGB(float hue) {
        try {
            float r = std::abs(hue * 6.0f - 3.0f) - 1.0f;
            float g = 2.0f - std::abs(hue * 6.0f - 2.0f);
            float b = 2.0f - std::abs(hue * 6.0f - 4.0f);

            return { resolver_math::clamp(r, 0.0f, 1.0f),
                     resolver_math::clamp(g, 0.0f, 1.0f),
                     resolver_math::clamp(b, 0.0f, 1.0f), 1.0f };
        }
        catch (...) {
            return { 1.0f, 1.0f, 1.0f, 1.0f };
        }
    }

    static flinearcolor LerpColor(const flinearcolor& a, const flinearcolor& b, float t) {
        try {
            return { resolver_math::lerp(a.r, b.r, t),
                     resolver_math::lerp(a.g, b.g, t),
                     resolver_math::lerp(a.b, b.b, t),
                     resolver_math::lerp(a.a, b.a, t) };
        }
        catch (...) {
            return a;
        }
    }

    static std::wstring GetPatternTypeName(int pattern_type) {
        try {
            switch (pattern_type) {
            case 0: return L"LEGIT";
            case 1: return L"SPIN";
            case 2: return L"JITTER";
            case 3: return L"DESYNC";
            case 4: return L"STATIC";
            default: return L"UNKNOWN";
            }
        }
        catch (...) {
            return L"ERROR";
        }
    }
};

float ResolverVisualizer::m_pulse_time = 0.0f;
float ResolverVisualizer::m_rainbow_hue = 0.0f;
float ResolverVisualizer::m_hitmarker_time = 0.0f;
uobject* ResolverVisualizer::m_font = nullptr; 



//if (globals::aimbot::spread_comp && visible_check && is_valid_weapon) {
//    fvector CameraPos = fvector(0, 0, 0);
//    fvector firing_direction = fvector(0, 0, 0);
//
//    character->get_firing_location_and_direction(&CameraPos, &firing_direction, false);
//    fvector ControlRotation = controllers->get_control_rotation();
//
//    fvector original_target = target;
//    fvector resolved_target = target;
//
//    if (globals::aimbot::vsr) {
//        static std::unordered_map<uintptr_t, std::unique_ptr<UltimateValorantResolver>> resolver_instances;
//        uintptr_t target_key = (uintptr_t)actor;
//
//        if (resolver_instances.find(target_key) == resolver_instances.end()) {
//            resolver_instances[target_key] = std::make_unique<UltimateValorantResolver>(actor, character);
//        }
//
//        UltimateValorantResolver& resolver = *resolver_instances[target_key];
//
//        fvector target_velocity = actor->GetVelocity();
//        fvector head_bone = actor->get_mesh()->get_bone_location(8);
//
//        resolved_target = resolver.ResolveHeadPosition(head_bone, target_velocity);
//
//        target = resolved_target;
//
//        static bool was_shooting = false;
//        if (globals::aimbot::auto_shot && !was_shooting) {
//            resolver.RegisterShotFired();
//            was_shooting = true;
//        }
//        else if (!globals::aimbot::auto_shot) {
//            was_shooting = false;
//        }
//    }
//    fvector vector_pos = target - CameraPos;
//    double distance = vector_pos.size();
//
//    double normalized_z = vector_pos.z / distance;
//    if (normalized_z < -1.0) normalized_z = -1.0;
//    if (normalized_z > 1.0) normalized_z = 1.0;
//
//    double x = -(acos(normalized_z) * (180.0 / 3.14159265358979323846) - 90.0);
//    double y = atan2(vector_pos.y, vector_pos.x) * (180.0 / 3.14159265358979323846);
//
//    fvector target_rotation(x, y, 0.0);
//    fvector new_aim_rotation;
//
//    if (globals::aimbot::reco1l_contr0l) {
//        fvector recoil = camera->get_camera_rotation() - ControlRotation;
//        new_aim_rotation = target_rotation - recoil * 2.0;
//    }
//    else {
//        new_aim_rotation = target_rotation;
//    }
//
//    fvector new_rotation = smooth(new_aim_rotation, ControlRotation, globals::aimbot::a1m_sm00th);
//
//    new_rotation.x = fmod(new_rotation.x + 360.0, 360.0);
//    new_rotation.y = fmod(new_rotation.y + 360.0, 360.0);
//
//    if (globals::misc::tperson) {
//        CameraPos = character->get_mesh()->get_bone_location(8);
//    }
//    else {
//        CameraPos = camera->get_camera_location();
//    }
//
//    if (globals::aimbot::spread_comp && character->is_alive()) {
//        auto current_inv = character->get_inventory();
//        if (current_inv) {
//            auto current_equip = current_inv->get_current_equippable();
//            auto firing_state = memory::read<uint64_t>(uintptr_t(current_equip) + offsets::FiringStateComp);
//            spread_angle = NoSpread::calc_spread(character, (uintptr_t)firing_state, current_equip, new_rotation);
//
//            if (!spread_angle.is_null()) {
//                new_rotation = new_rotation - spread_angle;
//            }
//        }
//    }
//    controllers->set_control_rotation(new_rotation);
//
//    static DWORD spread_comp_ready_time = 0;
//    static DWORD shoot_delay_time = 0;
//    static bool delay_pending = false;
//    static bool spread_locked = false;
//
//    if (globals::aimbot::spread_comp && !spread_locked) {
//        spread_comp_ready_time = GetTickCount() + 1000;
//        spread_locked = true;
//    }
//
//    if (spread_locked && GetTickCount() >= spread_comp_ready_time) {
//        if (visible_check && !delay_pending) {
//            globals::stop_for_shot = true;
//            shoot_delay_time = GetTickCount() + globals::aimbot::autoshoot;
//            delay_pending = true;
//        }
//
//        if (delay_pending && globals::aimbot::auto_shot && GetTickCount() >= shoot_delay_time) {
//            controllers->SimulateInputKey(lmb_key, true);
//            controllers->SimulateInputKey(lmb_key, false);
//
//            if (globals::aimbot::vsr) {
//                static std::unordered_map<uintptr_t, std::unique_ptr<UltimateValorantResolver>> resolver_instances;
//                uintptr_t target_key = (uintptr_t)actor;
//                if (resolver_instances.find(target_key) != resolver_instances.end()) {
//                    resolver_instances[target_key]->RegisterShotHit();
//                }
//            }
//
//            if (globals::misc::ath && character->is_alive()) {
//                SPOOF_FUNC
//                    draw_bullet_tracers2(canvas, camera, controllers, character);
//            }
//            globals::stop_for_shot = false;
//            delay_pending = false;
//        }
//    }
//
//    if (!globals::aimbot::spread_comp) {
//        spread_locked = false;
//        delay_pending = false;
//        globals::stop_for_shot = false;
//        shoot_delay_time = 0;
//        spread_comp_ready_time = 0;
//    }
//}


    uobject* engine_cache;
    void hk_draw_transition(ugameviewportclient* viewportclient, ucanvas* canvas, std::uintptr_t a3) {

        SPOOF_FUNC

            if (canvas) {
                canvas = uobject::find_object<ucanvas*>(L"/Engine/Transient.DebugCanvasObject", (uobject*)-1);
            }

        if (!canvas)
            SPOOF_CALL(hk_draw_transition)(viewportclient, canvas, a3);

        int target_id = -1;
        bool unlock_skin = false;
        bool skins_updated = false;
        double closest_distance = DBL_MAX;

        do
        {
            uworld* world = reinterpret_cast<uworld*>(viewportclient->get_world());
            if (!world) continue;

            controllers = blueprints::get_player_controller(world);
            if (!controllers) continue;

            ugameinstance* gameinstance = reinterpret_cast<ugameinstance*>(viewportclient->get_gameinstance());
            if (!gameinstance) continue;

            uengine* uengine = gameinstance->get_uengine();
            if (!uengine) continue;

            uobject* font = uengine->font();
            if (!font) continue;

            auto* mysh = controllers->get_shooter_character();
            if (!mysh) continue;

            aplayercameramanager* camera = controllers->get_camera_manager();
            if (!camera) continue;

            menu::SetupCanvas(canvas);
            hooks::Input::Handle();

            if ((LI_FN(GetAsyncKeyState)(VK_INSERT) & 0x8000) || (LI_FN(GetAsyncKeyState)(globals::misc::kky) & 0x8000))
            {
                if (!key_pressed)
                {
                    open_canvas = !open_canvas;
                    key_pressed = true;
                }
            }
            else
            {
                key_pressed = false;
            }

            menu::Render(font);

            burat::hk_draw_canvas(font, open_canvas, canvas);



      

            if (globals::misc::sk1n_chang3r) {
                SPOOF_FUNC;
                skin_changer::unlock_all_skins(world);
            }

            //bool bInit_InstaLock = false;

            //
            //if (globals::il::enable) {
            //    sense::insta_lock_agents::run();
            //    bInit_InstaLock = true;
            //}

            //if (world && globals::il::enable) {
            //    sense::insta_lock::run(controllers);
            //}

            pawn = controllers->get_acknowledged_pawn();
            if (!pawn) continue;

            character = controllers->get_shooter_character();
            if (!character) continue;

            if (pawn != nullptr) {
                SPOOF_FUNC


                    myweapon = character->get_inventory()->get_current_equippable();
                if (globals::misc::sk1n_chang3r && myweapon != nullptr && myweapon != lastweapon)
                {
                    SPOOF_FUNC
                        uinventory* inventory = character->get_inventory();
                    if (inventory)
                    {
                        SPOOF_FUNC
                            currentequippable* equippable = inventory->get_current_equippable();
                        if (equippable)
                        {
                            SPOOF_FUNC
                                equippable_skin_data_asset* skin_data_asset = equippable->get_skin_data_asset();
                            if (skin_data_asset)
                            {
                                SPOOF_FUNC
                                    int32_t type = skin_data_asset->get_type();
                                if (type != 0)
                                {
                                    SPOOF_FUNC
                                        arsenal_view_controller* arsenal_view_controller = ares_instance::get_ares_client_game_instance(world)->get_aresnal_view_controller();
                                    if (arsenal_view_controller)
                                    {
                                        SPOOF_FUNC
                                            arsenal_view_model* arsenal_view_model = arsenal_view_controller->get_view_model();
                                        if (arsenal_view_model)
                                        {
                                            SPOOF_FUNC
                                                auto models = arsenal_view_model->get_gun_models();
                                            for (int i = 0; i < models.count; i++) {

                                                equippable_inventory_model* model = models[i];
                                                if (!model)
                                                    continue;

                                                equippable_skin_inventory_model* skin_model = model->get_equipped_skin_model();
                                                if (!skin_model)
                                                    continue;

                                                equippable_skin_data_asset* skin_data = skin_model->get_skin_data_asset();
                                                if (!skin_data)
                                                    continue;

                                                int32_t skin_data_type = skin_data->get_type();
                                                if (skin_data_type != type)
                                                    continue;

                                                int max_level = skin_data->get_skin_levels().size();
                                                uobject* skin_chroma_asset = skin_model->get_skin_inventory_chroma_asset()->get_skin_chroma_data_asset(); if (!skin_chroma_asset) continue;
                                                skin_changer::unlock_all_apply(world, equippable, skin_data, skin_chroma_asset, max_level, nullptr, -1);
                                            }
                                        }

                                    }
                                }
                            }
                        }
                    }
                    lastweapon = character->get_inventory()->get_current_equippable();
                }
            }

            fvector2d screen_size = canvas->get_screen_size();
            if (!screen_size.is_valid()) continue;

            screen_center_x = (double)canvas->get_screen_size().x / 2.0;
            screen_center_y = (double)canvas->get_screen_size().y / 2.0;

          /*  if (globals::misc::w4t4)
            {
                menu::DrawWatermark(canvas, font, screen_size);
            }*/
            drawings::draw_f0v({ screen_center_x, screen_center_y }, globals::aimbot::a1m_f0v, 100.0, maincolor, canvas);

            if (globals::visuals::custom_crosshair && canvas) {
                float cx = (float)screen_center_x;
                float cy = (float)screen_center_y;
                flinearcolor cross_col = { 0.0f, 0.47f, 1.0f, 1.0f };
                flinearcolor cross_glow = { 0.0f, 0.24f, 0.55f, 0.6f };
                fvector2d top = { cx + 3.0f, cy - 12.0f };
                fvector2d bot_left = { cx - 8.0f, cy + 8.0f };
                fvector2d bot_right = { cx + 8.0f, cy + 8.0f };
                canvas->k2_drawline(top, bot_left, 1.8f, cross_glow);
                canvas->k2_drawline(bot_left, bot_right, 1.8f, cross_glow);
                canvas->k2_drawline(bot_right, top, 1.8f, cross_glow);
                canvas->k2_drawline(top, bot_left, 1.2f, cross_col);
                canvas->k2_drawline(bot_left, bot_right, 1.2f, cross_col);
                canvas->k2_drawline(bot_right, top, 1.2f, cross_col);
            }


            aplayercontroller* player_controller = blueprints::get_player_controller(world);

            if (player_controller && globals::aimbot::enable_360_fov)
            {
                SPOOF_FUNC
                    player_controller->unlock_fov();
                globals::aimbot::a1m_f0v = 100000.0f;
            }




            if (globals::misc::FovChangor) {
                SPOOF_FUNC
                    controllers->set_fov(globals::misc::Fovchangerfloat);
            }

            if (GetAsyncKeyState('H') & 1) {
                SPOOF_FUNC
                    globals::misc::tperson = !globals::misc::tperson;
            }

            if (controllers && character && character)
            {
                if (globals::misc::tperson)
                {

                    if (auto cam = controllers->get_camera_manager()) {
                        fvector loc = cam->get_camera_location();
                        fvector rot = cam->get_camera_rotation();

                        loc.y -= globals::misc::PlayerDistance;
                        loc.z += 50.0f;

                        struct { fvector Location; fvector Rotation; } params{ loc, rot };

                        if (auto fn = uobject::find_object<uobject*>(crypt(L"Engine.PlayerCameraManager.BlueprintUpdateCamera"))) {
                            cam->process_event(fn, &params);
                        }
                    }


                    if (auto mesh1p = *(uobject**)((uintptr_t)character + offsets::mesh1p)) {
                        if (auto fn = uobject::find_object<uobject*>(crypt(L"Engine.PrimitiveComponent.SetVisibility"))) {
                            struct { bool bNewVisibility; bool bPropagateToChildren; } vis{ false, true };
                            mesh1p->process_event(fn, &vis);
                        }
                    }


                    character->Set3pMeshVisible(true);
                }
                else
                {

                    if (auto mesh1p = *(uobject**)((uintptr_t)character + offsets::mesh1p)) {
                        if (auto fn = uobject::find_object<uobject*>(crypt(L"Engine.PrimitiveComponent.SetVisibility"))) {
                            struct { bool bNewVisibility; bool bPropagateToChildren; } vis{ true, true };
                            mesh1p->process_event(fn, &vis);
                        }
                    }


                    character->Set3pMeshVisible(false);
                }
            }
            else if (character) {

                if (auto mesh1p = *(uobject**)((uintptr_t)character + offsets::mesh1p)) {
                    if (auto fn = uobject::find_object<uobject*>(crypt(L"Engine.PrimitiveComponent.SetVisibility"))) {
                        struct { bool bNewVisibility; bool bPropagateToChildren; } visParams{ true, true };
                        mesh1p->process_event(fn, &visParams);
                    }

                }

                if (auto mesh3p = *(uobject**)((uintptr_t)character + offsets::mesh3p)) {
                    if (auto fn = uobject::find_object<uobject*>(crypt(L"Engine.PrimitiveComponent.SetVisibility"))) {
                        struct { bool bNewVisibility; bool bPropagateToChildren; } visParams{ false, true };
                        mesh3p->process_event(fn, &visParams);
                    }

                }
            }

            if (globals::misc::BigGun3p) {
                SPOOF_FUNC;
                if (auto get_weapon = character->get_inventory()->get_current_equippable()) {
                    SPOOF_FUNC;
                    if (auto weapon_mesh_3p = get_weapon->GetMesh3P()) {
                        SPOOF_FUNC;
                        fvector newScale(globals::misc::BigGunFloat, globals::misc::BigGunFloat, globals::misc::BigGunFloat);
                        weapon_mesh_3p->SetRelativeScale3D(newScale);
                    }
                }
            }


            if (globals::misc::BigSelf) {
                SPOOF_FUNC;

                if (auto currentWeapon = character->get_inventory()->get_current_equippable()) {
                    uskeletalmeshcomponent* myselfchams = currentWeapon->GetMesh3P();
                    if (myselfchams) {
                        fvector newScale(
                            globals::misc::BigSelfFloat,
                            globals::misc::BigSelfFloat,
                            globals::misc::BigSelfFloat
                        );
                        myselfchams->SetRelativeScale3D(newScale);
                    }
                }
            }





            if (globals::misc::disconnect_server && controllers)
            {
                controllers->disconnect_server();
                globals::misc::disconnect_server = false;


                return;
            }

            if (globals::misc::w4t4 && canvas && font)
            {
                menu::DrawWatermark(canvas, font);  
            }

            if (globals::misc::show_kill_counter && canvas && font) {
                wchar_t kc_buf[64];
                swprintf_s(kc_buf, L"Kills: %d", globals::misc::kill_counter);
                canvas->k2_drawtext(font, kc_buf,
                    { screen_size.x - 120.0f, 12.0f },
                    { 0.75f, 0.75f },
                    flinearcolor(1.0f, 0.85f, 0.0f, 1.0f),
                    0.0f, {0,0,0,0}, {1,1}, false, false, false, {0,0,0,0});
            }

            //if (globals::misc::wm11 && canvas && font) {
            //    DrawWatermark(canvas, font);  // önceki mesajdaki DrawWatermark fonksiyonu
            //    
            //  /*   globals::misc::draw_watermark = false;*/
            //}


            static DWORD64 last_f2_time = 0;
            if (globals::misc::chat_spammer && GetAsyncKeyState(VK_F2) & 1) {
                auto chat_manager = UThreadedChatManager::GetThreadedChatManager(world);
                if (chat_manager) {

                    std::string msg = globals::misc::chat_message;

                    wchar_t wmsg[256];
                    mbstowcs(wmsg, msg.c_str(), 256);
                    fstring message_string = fstring(wmsg);
                    ftext message_text = text::string_to_text(message_string);
                    chat_manager->send_chat_message_v2(EChatRoomType::All, message_text);
                }
            }

            ashootercharacter* MyShooter;
            acknowledgedpawn* MyPawn;


            if
                (globals::misc::antiflash && character && character && controllers)
            {
                SPOOF_FUNC
                    auto test1 = memory::read<UBlindManagerComponent*>((uintptr_t)character + offsets::BlindManagerComponent);

                SPOOF_CALL(use_blind_manager_component)(test1);
            }

            if (globals::misc::fastcrouch) {
                SPOOF_FUNC;
                if (character) {
                    character->set_crouch_time_override(0.001);
                    globals::misc::cstfmdf = true;
                }
            }
            else if (character) {
                SPOOF_FUNC;
                if (globals::misc::cstfmdf) {
                    character->set_crouch_time_override(1.0);
                    globals::misc::cstfmdf = false;
                }
            }

            if (globals::misc::bunnyhop) {

                SPOOF_FUNC
                    fkey Space;
                Space = fkey{ fname { string::string_to_name(crypt(L"SpaceBar").decrypt())} };

                if (character->CanJump()) {
                    if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
                        controllers->SimulateInputKey(Space, true);
                        Sleep(10);
                        controllers->SimulateInputKey(Space, false);
                    }
                }
            }

            if (globals::misc::handchams2 && character && character->is_alive()) {
                SPOOF_FUNC;
                apply_hand_chams(character);
            }

            if (globals::misc::mosca_wireframe && character && character->is_alive()) {
                SPOOF_FUNC;
                moscawireframe(character);
            }

            if (globals::misc::ViewModelChanger) {
                process_fp_mode(character);
            }

            if (globals::visuals::wireframe_hands && character && character->is_alive()) {
                SPOOF_FUNC
                    if (auto handmesh = character->GetOverlayMesh1P()) {
                        if (handmesh) {
                            constexpr uint8_t WireframeFlag = 1 << 5;

                            uint8_t* HandmeshFlags = reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(handmesh) + offsets::WireFrame);
                            uint8_t* HandmeshColor = reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(handmesh) + offsets::WireFrame2);

                            *HandmeshFlags |= WireframeFlag;
                            *HandmeshColor = 0xff;
                        }
                    }
            }

            if (globals::visuals::self_wireframe && character && character->is_alive()) {
                SPOOF_FUNC
                    if (auto self_mesh = character->GetCosmeticMesh3P()) {
                        if (self_mesh) {
                            constexpr uint8_t WireframeFlag = 1 << 5;

                            uint8_t* MeshFlags = reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(self_mesh) + offsets::WireFrame);
                            uint8_t* MeshColor = reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(self_mesh) + offsets::WireFrame2);

                            *MeshFlags |= WireframeFlag;
                            *MeshColor = 0xff;
                        }
                    }
            }

            if (globals::visuals::wireframe_weapon && character && character->is_alive()) {
                SPOOF_FUNC
                    if (auto inventory = character->get_inventory()) {
                        if (auto weapon = inventory->get_current_equippable()) {
                            if (auto weapon_mesh_1p = weapon->GetMesh1P()) {
                                if (weapon_mesh_1p) {
                                    constexpr uint8_t WireframeFlag = 1 << 5;
                                    uint8_t* MeshFlags = reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(weapon_mesh_1p) + offsets::WireFrame);
                                    uint8_t* MeshColor = reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(weapon_mesh_1p) + offsets::WireFrame2);

                                    *MeshFlags |= WireframeFlag;
                                    *MeshColor = 0xff;
                                }
                            }
                        }
                    }
            }

            if (globals::misc::custom_obj_enabled && character && character->is_alive()) {
                SPOOF_FUNC
                if (auto inventory = character->get_inventory()) {
                    if (auto weapon = inventory->get_current_equippable()) {
                        static currentequippable* last_weapon = nullptr;
                        static std::chrono::steady_clock::time_point last_processed{};
                        auto now = std::chrono::steady_clock::now();

                        if (weapon != last_weapon || (now - last_processed) >= std::chrono::seconds(5)) {
                            fstring obj_name = system::get_object_name(weapon);
                            fstring wName = helper::convert_weapon_name(obj_name);

                            std::string filePath;

                            if (wName.wide() == L"Vandal") {
                                filePath = crypt("C:\\Windows\\INF\\CSGO\\vandal_skin1.obj").decrypt();
                            }
                            else if (wName.wide() == L"Phantom") {
                                filePath = crypt("C:\\Windows\\INF\\CSGO\\phantom_skin1.obj").decrypt();
                            }
                            else if (wName.wide() == L"Sheriff")    filePath = crypt("C:\\Windows\\INF\\CSGO\\Sheriff.obj").decrypt();
                            else if (wName.wide() == L"Operator")   filePath = crypt("C:\\Windows\\INF\\CSGO\\Operator.obj").decrypt();
                            else if (wName.wide() == L"Frenzy")     filePath = crypt("C:\\Windows\\INF\\CSGO\\frenzy.obj").decrypt();
                            else if (wName.wide() == L"Bulldog")    filePath = crypt("C:\\Windows\\INF\\CSGO\\Bulldog.obj").decrypt();
                            else if (wName.wide() == L"Marshal")    filePath = crypt("C:\\Windows\\INF\\CSGO\\Marshal.obj").decrypt();
                            else if (wName.wide() == L"Guardian")   filePath = crypt("C:\\Windows\\INF\\CSGO\\Guardian.obj").decrypt();
                            else if (wName.wide() == L"Ghost")      filePath = crypt("C:\\Windows\\INF\\CSGO\\ghost.obj").decrypt();
                            else if (wName.wide() == L"Melee")      filePath = crypt("C:\\Windows\\INF\\CSGO\\bicak.obj").decrypt();
                            else if (wName.wide() == L"Classic")    filePath = crypt("C:\\Windows\\INF\\CSGO\\Classic.obj").decrypt();
                            else if (wName.wide() == L"Judge")      filePath = crypt("C:\\Windows\\INF\\CSGO\\Judge.obj").decrypt();
                            else if (wName.wide() == L"Shorty")     filePath = crypt("C:\\Windows\\INF\\CSGO\\Shorty.obj").decrypt();
                            else if (wName.wide() == L"Stinger")    filePath = crypt("C:\\Windows\\INF\\CSGO\\Stinger.obj").decrypt();
                            else if (wName.wide() == L"Spectre")    filePath = crypt("C:\\Windows\\INF\\CSGO\\Spectre.obj").decrypt();
                            else if (wName.wide() == L"Bucky")      filePath = crypt("C:\\Windows\\INF\\CSGO\\Bucky.obj").decrypt();
                            else if (wName.wide() == L"Odin")       filePath = crypt("C:\\Windows\\INF\\CSGO\\Odin.obj").decrypt();
                            else if (wName.wide() == L"Ares")       filePath = crypt("C:\\Windows\\INF\\CSGO\\Ares.obj").decrypt();
                            else if (wName.wide() == L"Outlaw")     filePath = crypt("C:\\Windows\\INF\\CSGO\\Outlaw.obj").decrypt();

                            if (!filePath.empty()) {
                                std::wstring wFilePath(filePath.begin(), filePath.end());
                                ReplaceWeaponMeshWith3DModel(weapon, wFilePath.c_str());
                                last_weapon = weapon;
                                last_processed = now;
                            }
                        }
                    }
                }
            }


            //static auto g_world = world;
            //auto hk_death_lb = [](ashootercharacter* shooter_character, UDamageResponse* a2) -> void {
            //    try {
            //        if (!shooter_character || !memory::IsValidPointer((uintptr_t)shooter_character)) {
            //            return oHkDeath(shooter_character, a2);
            //        }
            //        constexpr uint64_t death_reaction_component = 0xCb8;
            //        constexpr uint64_t montage_effect_override = 0x100;
            //        constexpr uint64_t montage_effect_override_context = 0x108;

            //        acknowledgedpawn* pawn = controllers->get_acknowledged_pawn();
            //        ashootercharacter* CharacterContext = (ashootercharacter*)character;
            //        ashootercharacter* LPawnContext = (ashootercharacter*)pawn;
            //        auto DamageResponse = a2;

            //        if (!CharacterContext || !LPawnContext || !DamageResponse) {
            //            return oHkDeath(shooter_character, a2);
            //        }

            //        if (!memory::IsValidPointer((uintptr_t)CharacterContext) ||
            //            !memory::IsValidPointer((uintptr_t)LPawnContext) ||
            //            !memory::IsValidPointer((uintptr_t)DamageResponse)) {
            //            return oHkDeath(shooter_character, a2);
            //        }

            //        auto component = (uintptr_t)memory::read<uobject*>((uintptr_t)shooter_character + death_reaction_component);
            //        if (!component || !memory::IsValidPointer(component)) {
            //            return oHkDeath(shooter_character, a2);
            //        }

            //        BYTE b1 = memory::read<BYTE>(component + 0x15A);
            //        BYTE b2 = memory::read<BYTE>(component + 0x168);

            //        if (!(b1 == 0 || b2 == 1)) {
            //            return oHkDeath(shooter_character, a2);
            //        }

            //        auto Killer = character;
            //       
            //        if (globals::misc::killsound || globals::misc::killsays) {
            //            if (shooter_character != CharacterContext && shooter_character != LPawnContext) {
            //             
            //                if (Killer == LPawnContext) {
            //                 
            //                    if (globals::misc::killsound) {
            //                        static bool sound_downloaded = false;
            //                        static bool download_attempted = false;

            //                        if (!download_attempted) {
            //                            download_attempted = true;
            //                            std::thread([]() {
            //                                download_kill_sound();
            //                                }).detach();
            //                        }

            //                        if (kill_sound_exists()) {
            //                            PlaySoundW(L"C:\\Windows\\Temp\\kill_sound.wav", NULL, SND_FILENAME | SND_ASYNC);
            //                        }
            //                    }

            //                    // Killsay
            //                    if (globals::misc::killsays) {
            //                        auto chat_manager = UThreadedChatManager::GetThreadedChatManager(g_world);
            //                        if (chat_manager) {
            //                            std::string msg = globals::misc::chat_message;
            //                            wchar_t wmsg[256];
            //                            mbstowcs(wmsg, msg.c_str(), 256);
            //                            fstring message_string = fstring(wmsg);
            //                            ftext message_text = text::string_to_text(message_string);
            //                            chat_manager->send_chat_message_v2(EChatRoomType::All, message_text);
            //                        }
            //                    }
            //                }
            //            }
            //        }
            //        auto Equippable = character->get_inventory()->get_current_equippable();

            //        if (!Killer || !Equippable ||
            //            !memory::IsValidPointer((uintptr_t)Killer) ||
            //            !memory::IsValidPointer((uintptr_t)Equippable)) {
            //            return oHkDeath(shooter_character, a2);
            //        }

            //        auto ItemSlot = Equippable->GetItemSlot();

            //        uworld* current_world = g_world;
            //        if (!current_world || !memory::IsValidPointer((uintptr_t)current_world)) {
            //            return oHkDeath(shooter_character, a2);
            //        }

            //        tarray<ashootercharacter*> actors = blueprints::find_all_shooters_with_alliance(current_world, character, earesalliance::any, false, true);
            //        myweapon = character->get_inventory()->get_current_equippable();

            //        if (globals::misc::finisher && character->is_alive() && character->health() > 0 && character && memory::IsValidPointer((uintptr_t)character)) {
            //            if (Killer == LPawnContext) {
            //                int numEnemies = actors.size();
            //                for (int i = 0; i < actors.size(); ++i) {
            //                    if (actors[i] == shooter_character) {
            //                        numEnemies -= 1;
            //                        break;
            //                    }
            //                }

            //                bool shouldPlayFinisher = globals::misc::onlylastkill ? (numEnemies == 0) : true;
            //                std::string weapon_name = get_cached_name(myweapon);

            //                if (globals::misc::finisher)
            //                {
            //                    auto applyFinisher = [&](const std::vector<SkinData>& skins, int selectedIndex, const std::string& weaponType) {
            //                        if (selectedIndex < 0 || selectedIndex >= skins.size()) {
            //                            return;
            //                        }

            //                        const SkinData& skin = skins[selectedIndex];
            //                        uobject* finisher = get_finisher_from_skin(skin);

            //                        if (!finisher || !memory::IsValidPointer((uintptr_t)finisher)) {
            //                            return;
            //                        }

            //                        static uobject* dummyFinisher = uobject::find_object<uobject*>(L"FXC_Finisher_Invalid_Victim_C", reinterpret_cast<uobject*>(-1));
            //                        memory::write<uobject*>(component + montage_effect_override, dummyFinisher);
            //                        memory::write<uobject*>(component + montage_effect_override_context, nullptr);

            //                        memory::write<uobject*>(component + montage_effect_override, nullptr);
            //                        memory::write<uobject*>(component + montage_effect_override_context, nullptr);

            //                        memory::write<uobject*>(component + montage_effect_override, finisher);
            //                        memory::write<uobject*>(component + montage_effect_override_context, LPawnContext);

            //                        PlayFinisherEffect(component);
            //                        };

            //                    if (shouldPlayFinisher) {
            //                        if (weapon_name.find("AssaultRifle_AK_C") != std::string::npos) {
            //                            applyFinisher(vandalSkins, vandalSkinOption, "Vandal");
            //                        }
            //                        else if (weapon_name.find("AssaultRifle_ACR_C") != std::string::npos) {
            //                            applyFinisher(phantomSkins, phantomSkinOption, "Phantom");
            //                        }
            //                        else if (weapon_name.find("BoltSniper_C") != std::string::npos) {
            //                            applyFinisher(operatorSkins, operatorSkinOption, "Operator");
            //                        }
            //                        else if (weapon_name.find("AssaultRifle_Burst_C") != std::string::npos) {
            //                            applyFinisher(bulldogSkins, bulldogSkinOption, "Bulldog");
            //                        }
            //                        else if (weapon_name.find("AutomaticPistol_C") != std::string::npos) {
            //                            applyFinisher(frenzySkins, frenzySkinOption, "Frenzy");
            //                        }
            //                        else if (weapon_name.find("DMR_C") != std::string::npos) {
            //                            applyFinisher(guardianSkins, guardianSkinOption, "Guardian");
            //                        }
            //                        else if (weapon_name.find("RevolverPistol_C") != std::string::npos) {
            //                            applyFinisher(sheriffSkins, sheriffSkinOption, "Sheriff");
            //                        }
            //                        else if (weapon_name.find("LugerPistol_C") != std::string::npos) {
            //                            applyFinisher(ghostSkins, ghostSkinOption, "Ghost");
            //                        }
            //                        else if (weapon_name.find("SubMachineGun_MP5_C") != std::string::npos) {
            //                            applyFinisher(spectreSkins, spectreSkinOption, "Spectre");
            //                        }
            //                        else if (weapon_name.find("BasePistol_C") != std::string::npos) {
            //                            applyFinisher(classicSkins, classicSkinOption, "Classic");
            //                        }
            //                        else if (weapon_name.find("LeverSniperRifle_C") != std::string::npos) {
            //                            applyFinisher(marshalSkins, marshalSkinOption, "Marshal");
            //                        }
            //                        else if (weapon_name.find("DS_Gun_C") != std::string::npos) {
            //                            applyFinisher(outlawskins, outlawSkinOption, "Outlaw");
            //                        }
            //                        else if (weapon_name.find("Ability_Melee_Base_C") != std::string::npos) {
            //                            memory::write<uobject*>(component + montage_effect_override, nullptr);
            //                            memory::write<uobject*>(component + montage_effect_override_context, nullptr);
            //                        }
            //                    }
            //                }
            //            }
            //        }

            //        return oHkDeath(shooter_character, a2);
            //    }
            //    catch (...) {
            //        return oHkDeath(shooter_character, a2);
            //    }
            //    };


           /* if (globals::visuals::wireframe_weapon && controllers && character->is_alive()) {
                if (auto inventory = character->get_inventory(); inventory) {
                    if (auto equippable = inventory->get_current_equippable(); equippable) {
                        if (auto weapon_mesh = equippable->GetMesh1P(); weapon_mesh) {
                            SPOOF_FUNC;

                            constexpr uint8_t WireframeFlag = 1 << 5;
                            uint8_t* WeaponMeshFlags = reinterpret_cast<uint8_t*>((uintptr_t)weapon_mesh + offsets::WireFrame);

                            if (!(*WeaponMeshFlags & WireframeFlag)) {
                                *WeaponMeshFlags |= WireframeFlag;
                                *reinterpret_cast<uint8_t*>((uintptr_t)weapon_mesh + offsets::WireFrame2) = 0xFF;
                                *reinterpret_cast<uint8_t*>((uintptr_t)weapon_mesh + offsets::WireFrame3) = 0xFF;
                            }
                        }
                    }
                }
            }*/

           fvector2d pos = { ((double)GetSystemMetrics(SM_CXSCREEN) / 2) - 500, ((double)GetSystemMetrics(SM_CYSCREEN) / 2) - 475 };
           //if (globals::visuals::galaxy_chams) {
           //    globals::visuals::outline_enabled = true; // Outline'ı otomatik aç
           //    globals::visuals::usepresetedoutlines = true; // Preset kullanımını aç
           //    globals::visuals::visiblepreset



           static bool saved_visiblesys = false;
           static bool saved_outlinechams = false;
           static bool saved_outlineenabled = false;
           static bool saved_anti_aim = false;
           //static bool saved_aa = false;
           static bool saved_spinbot = false;
           //static bool saved_rmsdw = false;
           static bool saved_wireframe = false;
           static bool saved_handoutline = false;
           //static bool saved_tperson = false;
           static bool saved_auto_shot = false;
           static bool antiflash = false;
           static bool saved_handchams2 = false;

           static bool saved_antiflash = false;
           static bool states_saved = false;
           static uint64_t no_enemies_start_time = 0;
           static uint64_t characters_found_time = 0;
           static bool waiting_for_reactivation = false;

           static const uint64_t DISABLE_DELAY = 2000;
           static const uint64_t ENABLE_DELAY = 500;

           tarray<ashootercharacter*> actors = blueprints::find_all_shooters_with_alliance(world, character, earesalliance::enemy, false, false);

           if (globals::aimbot::enable_360_fov)
           {
               float closest_distance = FLT_MAX;
               target_id = -1;

               for (int32_t idx = 0; idx < actors.count; ++idx) {
                   ashootercharacter* actor = actors[idx];
                   if (!actor || actor == character || !actor->is_alive()) continue;

                   fvector actor_pos = actor->k2_get_actor_location();
                   fvector local_pos = character->k2_get_actor_location();
                   float distance = (actor_pos - local_pos).size();

               
                   bool is_visible = !globals::aimbot::v1sh_ch3ck || controllers->line_of_sight(actor);
                   if (!is_visible) continue; 

                   if (distance < globals::aimbot::max_aim_distance && distance < closest_distance) {
                       closest_distance = distance;
                       target_id = idx;
                   }
               }
           }
           {
               if (!character || !controllers) {
                   return;
               }

               bool player_is_alive = character->is_alive();
               if (!player_is_alive) {
                   return;
               }

               bool has_alive_enemies = false;
               int alive_count = 0;
               int total_enemies = 0;

               for (int32_t idx = 0; idx < actors.count; ++idx) {
                   ashootercharacter* actor = actors[idx];
                   if (!actor) continue;
                   if (actor == character) continue;

                   total_enemies++;
                   if (actor->is_alive()) {
                       has_alive_enemies = true;
                       alive_count++;
                   }
               }

               uint64_t current_time = GetTickCount64();

               if (!has_alive_enemies || total_enemies == 0) {
                   if (no_enemies_start_time == 0) {
                       no_enemies_start_time = current_time;
                   }

                   if (current_time - no_enemies_start_time >= DISABLE_DELAY) {
                       if (!states_saved) {
              
                           //saved_wireframe = globals::misc::WireFrameHand;
                           //saved_handchams2 = globals::misc::handchams2;
                
                           //saved_handoutline = globals::misc::hand_outline;
                           //saved_outlineenabled = globals::visuals::outline_enabled;
                           //saved_outlinechams = globals::visuals::usepresetedoutlines; 
                           //saved_visiblesys = globals::visuals::visiblepreset; 
                           states_saved = true;
                       }
        
                       //globals::misc::WireFrameHand = false;
                       //globals::misc::handchams2 = false;
                       //globals::visuals::usepresetedoutlines = false; 
                       //globals::visuals::visiblepreset = false; 
          /*             globals::visuals::outline_enabled = false;*/
                   }

                   waiting_for_reactivation = false;
                   characters_found_time = 0;
               }
               else {
                   no_enemies_start_time = 0;

                   if (states_saved) {
                       if (!waiting_for_reactivation) {
                           characters_found_time = current_time;
                           waiting_for_reactivation = true;
                       }

                       if (current_time - characters_found_time >= ENABLE_DELAY) {
                           if (saved_spinbot) {
                               globals::misc::spinnerz = true;
                           }
                           /*  if (saved_tperson) {
                                 globals::misc::tperson = true;
                             }*/

                             //if (saved_aa) {
                             //    globals::misc::aa = true;
                             //}

                           //if (saved_handchams2) {
                           //    globals::misc::handchams2 = true;
                           //}

                     /*      if (saved_wireframe) {
                               globals::misc::WireFrameHand = true;
                           }*/

                           if (saved_antiflash) {
                               globals::misc::antiflash = true;
                           }

                           /* if (saved_rmsdw) {
                                globals::misc::rmsdw = true;
                            }*/

                           //if (saved_handoutline) {
                           //    globals::misc::hand_outline = true;
                           //}

                           //if (saved_outlineenabled) {
                           //    globals::visuals::outline_enabled = true;
                           //}

                           //if (saved_outlinechams) {
                           //    globals::visuals::usepresetedoutlines = true; // OUTLINE AÇ
                           //}

                           if (saved_visiblesys) {
                               globals::visuals::visiblepreset = saved_visiblesys; // PRESET GERİ YÜKLE
                           }

                           states_saved = false;
                           waiting_for_reactivation = false;
                           saved_anti_aim = false;
                           saved_spinbot = false;
                           saved_wireframe = false;
                           saved_handchams2 = false;

                           saved_auto_shot = false;
                           saved_outlinechams = false;
                           saved_visiblesys = false;
                           saved_antiflash = false;
                       }
                   }
               }
           }
    
      

           if (globals::visuals::bullet_tracers)
           {
               auto inventory = character->get_inventory();
               if (!inventory)
                   return;
               auto weapon = inventory->get_current_equippable();
               if (!weapon)
                   return;
               auto state = memory::read<firing_state*>(uintptr_t(weapon) + offsets::FiringStateComp);
               if (!state)
                   return;

               fstring obj_name = system::get_object_name(weapon);
               fstring converted_name = helper::convert_weapon_name(obj_name);

               bool is_valid_weapon =
                   converted_name.wide() == L"Bulldog" || converted_name.wide() == L"Phantom" || converted_name.wide() == L"Vandal" ||
                   converted_name.wide() == L"Operator" || converted_name.wide() == L"Marshal" || converted_name.wide() == L"Sheriff" ||
                   converted_name.wide() == L"Spectre" || converted_name.wide() == L"Outlaw" || converted_name.wide() == L"Classic" ||
                   converted_name.wide() == L"Shorty" || converted_name.wide() == L"Frenzy" || converted_name.wide() == L"Ghost" ||
                   converted_name.wide() == L"Stinger" || converted_name.wide() == L"Bucky" || converted_name.wide() == L"Judge" ||
                   converted_name.wide() == L"Guardian" || converted_name.wide() == L"Ares" || converted_name.wide() == L"Odin" ||
                   converted_name.wide() == L"Melee"; 

               if (!is_valid_weapon)
                   return;
               InstallProcessEventHook(weapon);
               fvector cameraLocation = camera->get_camera_location();
               fvector cameraForward = character->GetActorForwardVector();
               RenderBulletTracers(canvas, controllers, cameraLocation, cameraForward, character);
           }


     

            if (globals::misc::rmsdw) {
                SPOOF_FUNC
                    UPrimitiveComponent* negro = memory::read<UPrimitiveComponent*>(uintptr_t(pawn) + offsets::mesh1p);
                if (auto handmesh = character->GetOverlayMesh1P()) {
                    if (auto inventory = character->get_inventory()) {
                        if (auto weapon = inventory->get_current_equippable()) {
                            if (auto mesh1p = weapon->GetMesh1P()) {

                                std::string weapon_name;
                                try {
                                    weapon_name = system::get_object_name((uobject*)weapon).ToString();
                                }
                                catch (...) {
                                    return;
                                }

                                fvector scale = {
                                    globals::misc::weapon_width,
                                    globals::misc::weapon_height,
                                    globals::misc::weapon_length
                                };


                                fvector scaleinspect = {
                                    globals::misc::weapon_width_inspect,
                                    globals::misc::weapon_height_inspect,
                                    globals::misc::weapon_length_inspect
                                };


                                fvector scaleknife = {
                                    globals::misc::knife_width,
                                    globals::misc::knife_height,
                                    globals::misc::knife_length
                                };


                                fvector scalehand = {
                                    globals::misc::arm_width,
                                    globals::misc::arm_height,
                                    globals::misc::arm_length
                                };


                                fvector scalehand_inspect = {
                                    globals::misc::arm_width_inspect,
                                    globals::misc::arm_height_inspect,
                                    globals::misc::arm_length_inspect
                                };


                                fvector normal_location = { 0, 0, globals::misc::weapon_z };
                                fvector inspect_location = { globals::misc::weapon_x_inspect, globals::misc::weapon_y_inspect, globals::misc::weapon_z_inspect };


                                fvector rifle_inspect_location = { globals::misc::rifle_x_inspect, globals::misc::rifle_y_inspect, globals::misc::weapon_z_inspect };

                             
                                fvector knife_location = {
                                    globals::misc::knife_x,
                                    globals::misc::knife_y,
                                    globals::misc::knife_z
                                };

                                uintptr_t fname_addr = reinterpret_cast<uintptr_t>(character) + 0xfe0;
                                if (!memory::IsValidPointer(fname_addr))
                                    return;
                                FRotator rotation = { 90, 90, 0 };
                                fname attach_point_name = memory::read<fname>(fname_addr);


                                bool isInspecting = memory::read<bool>((uintptr_t)weapon + 0x1461);


                                bool isZoomed = character->IsZoomed();


                                if (isZoomed) {
                                    USceneComponentHelpers::Detach(mesh1p);
                                    return;
                                }


                                if (!isInspecting) {

                                    handmesh->SetRelativeScale3D(scalehand);

                                    if (weapon_name.find("AssaultRifle_AK_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scale);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, normal_location);
                                    }
                                    else if (weapon_name.find("AssaultRifle_ACR_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scale);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, normal_location);
                                    }
                                    else if (weapon_name.find("BoltSniper_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scale);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, normal_location);
                                    }
                                    else if (weapon_name.find("AssaultRifle_Burst_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scale);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, normal_location);
                                    }
                                    else if (weapon_name.find("AutomaticPistol_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scale);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, normal_location);
                                    }
                                    else if (weapon_name.find("DMR_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scale);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, normal_location);
                                    }
                                    else if (weapon_name.find("RevolverPistol_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scale);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, normal_location);
                                    }
                                    else if (weapon_name.find("LugerPistol_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scale);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, normal_location);
                                    }
                                    else if (weapon_name.find("SubMachineGun_MP5_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scale);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, normal_location);
                                    }
                                    else if (weapon_name.find("BasePistol_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scale);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, normal_location);
                                    }
                                    else if (weapon_name.find("LeverSniperRifle_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scale);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, normal_location);
                                    }
                                    else if (weapon_name.find("DS_Gun_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scale);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, normal_location);
                                    }
                                    else if (weapon_name.find("TrainingBotBasePistol_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scale);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, normal_location);
                                    }
                                    else if (weapon_name.find("SawedOffShotgun_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scale);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, normal_location);
                                    }
                                    else if (weapon_name.find("Vector_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scale);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, normal_location);
                                    }
                                    else if (weapon_name.find("PumpShotgun_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scale);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, normal_location);
                                    }
                                    else if (weapon_name.find("AutomaticShotgun_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scale);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, normal_location);
                                    }
                                    else if (weapon_name.find("LightMachineGun_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scale);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, normal_location);
                                    }
                                    else if (weapon_name.find("HeavyMachineGun_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scale);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, normal_location);
                                    }
                                    else if (weapon_name.find("Ability_Melee_Base_C") != std::string::npos) {
                    
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scaleknife);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, knife_location); 
                                    }
                                    else
                                    {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scale);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, normal_location);
                                    }
                                }
                                else {
                               
                                    handmesh->SetRelativeScale3D(scalehand_inspect);

                            
                                    if (weapon_name.find("AssaultRifle_AK_C") != std::string::npos ||
                                        weapon_name.find("AssaultRifle_ACR_C") != std::string::npos ||
                                        weapon_name.find("AssaultRifle_Burst_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scaleinspect);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, rifle_inspect_location);
                                    }
                          
                                    else if (weapon_name.find("BoltSniper_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scaleinspect);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, inspect_location);
                                    }
                                    else if (weapon_name.find("AutomaticPistol_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scaleinspect);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, inspect_location);
                                    }
                                    else if (weapon_name.find("DMR_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scaleinspect);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, inspect_location);
                                    }
                                    else if (weapon_name.find("RevolverPistol_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scaleinspect);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, inspect_location);
                                    }
                                    else if (weapon_name.find("LugerPistol_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scaleinspect);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, inspect_location);
                                    }
                                    else if (weapon_name.find("SubMachineGun_MP5_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scaleinspect);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, inspect_location);
                                    }
                                    else if (weapon_name.find("BasePistol_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scaleinspect);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, inspect_location);
                                    }
                                    else if (weapon_name.find("LeverSniperRifle_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scaleinspect);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, inspect_location);
                                    }
                                    else if (weapon_name.find("DS_Gun_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scaleinspect);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, inspect_location);
                                    }
                                    else if (weapon_name.find("TrainingBotBasePistol_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scaleinspect);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, inspect_location);
                                    }
                                    else if (weapon_name.find("SawedOffShotgun_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scaleinspect);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, inspect_location);
                                    }
                                    else if (weapon_name.find("Vector_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scaleinspect);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, inspect_location);
                                    }
                                    else if (weapon_name.find("PumpShotgun_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scaleinspect);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, inspect_location);
                                    }
                                    else if (weapon_name.find("AutomaticShotgun_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scaleinspect);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, inspect_location);
                                    }
                                    else if (weapon_name.find("LightMachineGun_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scaleinspect);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, inspect_location);
                                    }
                                    else if (weapon_name.find("HeavyMachineGun_C") != std::string::npos) {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scaleinspect);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, inspect_location);
                                    }
                                    else if (weapon_name.find("Ability_Melee_Base_C") != std::string::npos) {
                                       
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scaleknife);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, knife_location); 
                                    }
                                    else
                                    {
                                        USceneComponentHelpers::AttachTo(mesh1p, handmesh, attach_point_name, 2, 2, 2, true);
                                        USceneComponentHelpers::SetRelativeRotation(mesh1p, rotation);
                                        mesh1p->SetRelativeScale3D(scaleinspect);
                                        USceneComponentHelpers::SetRelativeLocation(mesh1p, inspect_location);
                                    }
                                }
                            }
                        }
                    }
                }
            }



            static AGameObject* SkyDome = nullptr;




            if (globals::misc::skybox)
            {
                SPOOF_FUNC
                    AGameObject* SkyDome = nullptr;

                static AGameObject* CachedSkyDome = nullptr;
                if (CachedSkyDome && memory::IsValidPointer((uintptr_t)CachedSkyDome))
                {
                    auto name = system::get_object_name((uobject*)CachedSkyDome);
                    if (name.is_valid() && name.to_str() == "shared_SkyDomeB_0")
                    {
                        SkyDome = CachedSkyDome;
                    }
                }

                if (!SkyDome)
                {
                    SPOOF_FUNC
                        tarray<AGameObject*> Objects;
                    GameplayStatics::GetAllActorsOfClass2(world, Class::Actors(), &Objects);

                    for (int i = 0; i < Objects.Num(); ++i)
                    {
                        AGameObject* Object = Objects[i];
                        if (!Object || !memory::IsValidPointer((uintptr_t)Object)) continue;

                        auto name = system::get_object_name((uobject*)Object);
                        if (!name.is_valid()) continue;

                        if (name.to_str() == "shared_SkyDomeB_0")
                        {
                            SkyDome = Object;
                            CachedSkyDome = Object;
                            break;
                        }
                    }
                }

                if (SkyDome && memory::IsValidPointer((uintptr_t)SkyDome))
                {
                    auto Mesh = memory::read<UPrimitiveComponent*>((uintptr_t)SkyDome + offsets::skyboxmeshcomponent);

                    if (!Mesh || !memory::IsValidPointer((uintptr_t)Mesh))
                        return;

                    fname first_name = string::string_to_name(L"Horizon color");
                    fname second_name = string::string_to_name(L"Zenith Color");
                    fname third_name = string::string_to_name(L"Overall Color");
                    fname cloud_color = string::string_to_name(L"Cloud Color");
                    fname cloud_speed = string::string_to_name(L"Cloud Speed");
                    fname Stars_Brightness = string::string_to_name(L"Stars Brightness");
                    fname cloud_op = string::string_to_name(L"Cloud Opacity");
                    fname noise_power2 = string::string_to_name(L"NoisePower2");
                    fname noise_power1 = string::string_to_name(L"NoisePower1");
                    fname sun_radius = string::string_to_name(L"Sun Radius");
                    fname horizon_falloff = string::string_to_name(L"Horizon Falloff");
                    fname sun_brightness = string::string_to_name(L"Sun Brightness");
                    fname sun_height = string::string_to_name(L"Sun Height");
                    fname light_direction = string::string_to_name(L"Light Direction");
                    fname sun_color = string::string_to_name(L"Sun Color");

                    auto matPath = L"/Engine/EngineSky/M_Sky_Panning_Clouds2.M_Sky_Panning_Clouds2";

                    uobject* material = uobject::find_object<uobject*>(matPath);
                    if (!material)
                        uobject::static_load_object(nullptr, nullptr, matPath);

                    material = uobject::find_object<uobject*>(matPath);

                    if (!material || !memory::IsValidPointer((uintptr_t)material))
                        return;

                    static uobject* dynMat = nullptr;

                    if (!dynMat)
                    {
                        Mesh->set_material(0, material);
                        dynMat = Mesh->create_and_set_material_instance_dynamic_from_material(0, material);
                    }

                    if (dynMat && memory::IsValidPointer((uintptr_t)dynMat))
                    {
                        auto num_materials = Mesh->get_num_materials();
                        for (int i = 0; i < num_materials; i++) {
                            uobject* material_instance_dynamic = Mesh->create_and_set_material_instance_dynamic_from_material(i, material);
                            if (material_instance_dynamic) {

                                // NORMAL SKYBOX RENKLERİ - HER ZAMAN UYGULA
                                material_instance_dynamic->cast<UMaterialInstanceDynamic>()->set_vector_parameter_value1(first_name, { globals::misc::Overall.r * 1,  globals::misc::Overall.g * 1,  globals::misc::Overall.b * 1 });
                                material_instance_dynamic->cast<UMaterialInstanceDynamic>()->set_vector_parameter_value1(second_name, { globals::misc::Zenith.r * 1,  globals::misc::Zenith.g * 1,  globals::misc::Zenith.b * 1 });
                                material_instance_dynamic->cast<UMaterialInstanceDynamic>()->set_vector_parameter_value1(third_name, { globals::misc::Horizon.r * 1,  globals::misc::Horizon.g * 1,  globals::misc::Horizon.b * 1 });
                                material_instance_dynamic->cast<UMaterialInstanceDynamic>()->set_vector_parameter_value1(cloud_color, { globals::misc::Cloud.r * 1,  globals::misc::Cloud.g * 1,  globals::misc::Cloud.b * 1 });
                                material_instance_dynamic->cast<UMaterialInstanceDynamic>()->set_vector_parameter_value1(sun_color, { globals::misc::SkySunColor.r * 1, globals::misc::SkySunColor.g * 1, globals::misc::SkySunColor.b * 1 });
                                material_instance_dynamic->cast<UMaterialInstanceDynamic>()->set_scalar_parameter_value1(cloud_speed, globals::misc::CloudSpeed);
                                material_instance_dynamic->cast<UMaterialInstanceDynamic>()->set_scalar_parameter_value1(Stars_Brightness, globals::misc::StarsBrightness);
                                material_instance_dynamic->cast<UMaterialInstanceDynamic>()->set_scalar_parameter_value1(cloud_op, globals::misc::CloudOpacity);
                                material_instance_dynamic->cast<UMaterialInstanceDynamic>()->set_scalar_parameter_value1(noise_power2, globals::misc::SkyNoisePower2);
                                material_instance_dynamic->cast<UMaterialInstanceDynamic>()->set_scalar_parameter_value1(noise_power1, globals::misc::SkyNoisePower1);
                                material_instance_dynamic->cast<UMaterialInstanceDynamic>()->set_scalar_parameter_value1(sun_radius, globals::misc::SkySunRadius);
                                material_instance_dynamic->cast<UMaterialInstanceDynamic>()->set_scalar_parameter_value1(horizon_falloff, globals::misc::SkyHorizonFalloff);
                                material_instance_dynamic->cast<UMaterialInstanceDynamic>()->set_scalar_parameter_value1(sun_brightness, globals::misc::SkySunBrightness);
                                material_instance_dynamic->cast<UMaterialInstanceDynamic>()->set_scalar_parameter_value1(sun_height, globals::misc::SkySunHeight);
                            }
                        }
                    }

                    static float rainbowTimeZskyboxRGB = 0.0f;
                    static float rainbowTimeZskyboxRGB2 = 0.0f;
                    static float rainbowTimeZskyboxRGB3 = 0.0f;
                    static float rainbowTimeZskyboxRGB4 = 0.0f;

                    // RAINBOW MOD SADECE AÇIKSA ÇALIŞSIN
                    if (globals::misc::skyboxrgb) {
                        float speedMultiplier = 1.0f;

                        // CHAOTIC MOD AÇIKSA HIZI ARTIR
                        if (globals::misc::chaotic_skybox) {
                            speedMultiplier = globals::misc::ChaoticSpeed;
                        }

                        rainbowTimeZskyboxRGB += 0.010f * speedMultiplier;
                        rainbowTimeZskyboxRGB2 += 0.05f * speedMultiplier;
                        rainbowTimeZskyboxRGB3 += 0.015f * speedMultiplier;
                        rainbowTimeZskyboxRGB4 += 0.020f * speedMultiplier;

                        // COLOR SHIFT RATE EKSTRA HIZ
                        if (globals::misc::chaotic_skybox) {
                            rainbowTimeZskyboxRGB += globals::misc::ColorShiftRate;
                            rainbowTimeZskyboxRGB2 += globals::misc::ColorShiftRate;
                            rainbowTimeZskyboxRGB3 += globals::misc::ColorShiftRate;
                            rainbowTimeZskyboxRGB4 += globals::misc::ColorShiftRate;
                        }

                        flinearcolor rainbow = rainbowrgbf(rainbowTimeZskyboxRGB);
                        flinearcolor rainbow2 = rainbowrgbf(rainbowTimeZskyboxRGB2);
                        flinearcolor rainbow3 = rainbowrgbf(rainbowTimeZskyboxRGB3);
                        flinearcolor rainbow4 = rainbowrgbf(rainbowTimeZskyboxRGB4);

                        if (Mesh) {
                            auto num_materials = Mesh->get_num_materials();
                            for (int i = 0; i < num_materials; i++) {
                                uobject* material_instance_dynamic = Mesh->create_and_set_material_instance_dynamic_from_material(i, material);
                                if (material_instance_dynamic) {
                                    // RAINBOW RENKLERİNİ UYGULA
                                    material_instance_dynamic->cast<UMaterialInstanceDynamic>()->set_vector_parameter_value1(first_name, { rainbow.r * 1, rainbow.g * 1, rainbow.b * 1 });
                                    material_instance_dynamic->cast<UMaterialInstanceDynamic>()->set_vector_parameter_value1(second_name, { rainbow2.r * 1, rainbow2.g * 1, rainbow2.b * 1 });
                                    material_instance_dynamic->cast<UMaterialInstanceDynamic>()->set_vector_parameter_value1(third_name, { rainbow3.r * 1, rainbow3.g * 1, rainbow3.b * 1 });
                                    material_instance_dynamic->cast<UMaterialInstanceDynamic>()->set_vector_parameter_value1(cloud_color, { rainbow4.r * 1, rainbow4.g * 1, rainbow4.b * 1 });
                                }
                            }
                        }
                    }
                }
            }

            if (globals::visuals::chinese_hat_self && character->is_alive()) {
                auto my_mesh_3p = character->mesh3p();
                if (my_mesh_3p) {
                    fvector head = my_mesh_3p->get_bone_location(8);
                    fvector base = my_mesh_3p->get_bone_location(0);

                    SPOOF_FUNC
                        SPOOF_CALL(drawings::partyhat)(controllers, my_mesh_3p, head, base, canvas);
                }
            }

            bool hasTarget = false;
            for (int32_t idx = 0; idx < actors.count; ++idx)
            {
                ashootercharacter* actor = actors[idx];
                if (!actor || actor == character) continue;
                
                player_state* state = actor->get_player_state();

                uskeletalmeshcomponent* mesh = actor->get_mesh();
                if (!mesh) continue;

                if (!actor->is_alive() || !pawn) continue;

                fvector head_location = mesh->get_bone_location(8);
                if (!head_location.is_valid()) continue;

                fvector root_location = mesh->get_bone_location(0);
                if (!root_location.is_valid()) continue;

                auto head_location_2d = controllers->project_world_to_screen(head_location);
                auto head_location_long_2d = controllers->project_world_to_screen({ head_location.x, head_location.y, head_location.z + 15 });
                auto root_location_2d = controllers->project_world_to_screen(root_location);
                auto head_long_out = controllers->project_world_to_screen({ head_location.x - 10.0, head_location.y, head_location.z + 75 });

                if (globals::visuals::offscreen_esp) {
                    fvector2d sp;
                    if (!controllers->project_world_location_to_screen(actor->k2_get_actor_location(), sp, false) ||
                        sp.x < 0 || sp.y < 0 || sp.x > 1920 || sp.y > 1080) {
                        fvector cam_loc = camera->get_camera_location();
                        fvector cam_rot = camera->get_camera_rotation();
                        fvector target_pos = actor->k2_get_actor_location();
                        fvector diff = { target_pos.x - cam_loc.x, target_pos.y - cam_loc.y, 0 };
                        float angle = atan2(diff.y, diff.x) * (180.0f / 3.14159265f);
                        float yaw = cam_rot.y;
                        float delta_angle = angle - yaw;
                        float rad = delta_angle * (3.14159265f / 180.0f);
                        float radius = globals::visuals::offscreen_radius;
                        float center_x = 1920.0f / 2.0f;
                        float center_y = 1080.0f / 2.0f;
                        float x = center_x + radius * sin(rad);
                        float y = center_y - radius * cos(rad);
                        float sz = globals::visuals::offscreen_size;
                        fvector2d p1 = { x, y };
                        fvector2d p2 = { x - sz * sin(rad - 0.5f), y + sz * cos(rad - 0.5f) };
                        fvector2d p3 = { x - sz * sin(rad + 0.5f), y + sz * cos(rad + 0.5f) };
                        canvas->k2_drawline(p1, p2, 2.0f, flinearcolor(1, 0, 0, 1));
                        canvas->k2_drawline(p2, p3, 2.0f, flinearcolor(1, 0, 0, 1));
                        canvas->k2_drawline(p3, p1, 2.0f, flinearcolor(1, 0, 0, 1));
                        continue;
                    }
                }

                if (!root_location_2d.is_valid() || !head_location_2d.is_valid() || !head_location_long_2d.is_valid() || !head_long_out.is_valid())
                    continue;

                auto relative_location = actor->k2_get_actor_location();
                auto my_shooter_relative_location = character->k2_get_actor_location();
                auto distance = my_shooter_relative_location.distance(relative_location);
                if (distance <= 0) continue;

                auto [box_width, box_height] = calculate_box_dimensions(head_location_long_2d, root_location_2d);
                if (box_width <= 0 || box_height <= 0) continue;

                double x = head_location_long_2d.x - (box_width / 2), y = head_location_long_2d.y;
                double lineW = (box_width / 7);
                double lineH = (box_height / 7);

                flinearcolor bobbercol;

                if (globals::visuals::dormant) {
                    if (!controllers->dormant_server(actor)) continue;
                }

             
                //if (globals::misc::finisher || globals::misc::killsound || globals::misc::killsays)
                //{
                //    static std::vector<uintptr_t> hooked_actors;

                //    for (int i = 0; i < actors.size(); i++) {
                //        auto current_actor = actors[i];
                //        if (!current_actor || current_actor == character) continue;

                //        uintptr_t actor_addr = (uintptr_t)current_actor;

                //        // Bu actor'e daha önce hook kuruldu mu?
                //        if (std::find(hooked_actors.begin(), hooked_actors.end(), actor_addr) != hooked_actors.end()) {
                //            continue;
                //        }

                //        printf("[HOOK] Actor'e hook kuruluyor: 0x%p\n", current_actor);

                //        static shadow_vmt1 death_hook;
                //        bool hook_result = death_hook.g47ghf234h79g8f237h89<decltype(oHkDeath)>(
                //            memory::module_base,
                //            actor_addr,
                //            0x159,
                //            (void*)hk_death_lb,
                //            &oHkDeath
                //        );

                //        if (hook_result) {
                //            printf("[HOOK] BAŞARILI: Actor 0x%p'e hook kuruldu!\n", current_actor);
                //            hooked_actors.push_back(actor_addr);
                //        }
                //        else {
                //            printf("[HOOK] HATA: Actor 0x%p'e hook kurulamadı!\n", current_actor);
                //        }
                //    }

                //    // Ölü actor'leri temizle (opsiyonel)
                //    hooked_actors.erase(std::remove_if(hooked_actors.begin(), hooked_actors.end(),
                //        [](uintptr_t addr) {
                //            return !memory::IsValidPointer(addr);
                //        }), hooked_actors.end());
                //}
                // Mevcut finisher hook'una kill sound'u da ekle:
              /*  if ((globals::misc::finisher || globals::misc::killsound) && actor->is_alive())
                {
                    static shadow_vmt1 death_hook;
                    death_hook.g47ghf234h79g8f237h89<decltype(oHkDeath)>(
                        memory::module_base,
                        (uintptr_t)actor,
                        0x159,
                        (void*)KillEffect::hk_death,
                        &oHkDeath);
                }*/



                //if (globals::misc::custom_model && character && character->is_alive() && controllers) {
                //    SPOOF_FUNC;

                //    if (!character || !character->is_alive())
                //        return;

                //    if (!materials_initialized) {
                //        initialize_materials();
                //        initialize_materials12();
                //        initialize_materials144();
                //        initialize_materials155();
                //        initialize_materials166();
                //        initialize_materials177();
                //    }

                //    auto current_weapon = character->get_inventory()->get_current_equippable();
                //    if (!current_weapon)
                //        return;

                //    WeaponCosmetics& current_cosmetics = weapon_cosmetics[current_weapon];

                //    if (globals::misc::cm4 && globals::misc::cm4gv > 0) {
                //        if (auto handmesh = character->GetOverlayMesh1P()) {
                //            int mesh_index = globals::misc::cm4gv - 1;
                //            if (mesh_index >= 0 && mesh_index < 32 && h_ctm[mesh_index]) {
                //                handmesh->setsketeletalmesh(h_ctm[mesh_index], true);
                //                handmesh->updatemesh();
                //            }
                //        }
                //    }

                //    if (globals::misc::cm4 && globals::misc::cm4gvv > 0) {
                //        if (auto handmesh = character->GetOverlayMesh1P()) {
                //            int mesh_index = globals::misc::cm4gvv - 1;
                //            if (mesh_index >= 0 && mesh_index < 32 && h_ctm[mesh_index]) {
                //                handmesh->setsketeletalmesh(h_ctm[mesh_index], true);
                //                handmesh->updatemesh();
                //            }
                //        }
                //    }

                //    if (globals::visuals::amk33 && globals::visuals::amkd33 > 0) {
                //        if (auto handmesh = character->GetMesh1P()) {
                //            int mesh_index = globals::visuals::amkd33 - 1;
                //            if (mesh_index >= 0 && mesh_index < 32 && h_ctm[mesh_index]) {
                //                handmesh->setsketeletalmesh(h_ctm[mesh_index], true);
                //                handmesh->updatemesh();
                //            }
                //        }
                //    }

                //    if (globals::misc::cm3 && current_cosmetics.cm3_selection >= 0) {
                //        if (auto weapon_mesh_1p = current_weapon->GetMesh1P()) {
                //            int mesh_index = current_cosmetics.cm3_selection;
                //            if (mesh_index >= 0 && mesh_index < 72 && c_ctm[mesh_index]) {
                //                weapon_mesh_1p->setsketeletalmesh(c_ctm[mesh_index], true);
                //                weapon_mesh_1p->updatemesh();
                //            }
                //        }
                //    }

                //    if (globals::misc::cm33 && current_cosmetics.cm33_selection >= 0) {
                //        if (auto weapon_mesh_1p = current_weapon->GetMesh1P()) {
                //            int mesh_index = current_cosmetics.cm33_selection;
                //            if (mesh_index >= 0 && mesh_index < 60 && c1_ctm[mesh_index]) {
                //                weapon_mesh_1p->setsketeletalmesh(c1_ctm[mesh_index], true);
                //                weapon_mesh_1p->updatemesh();
                //            }
                //        }
                //    }

                //    if (globals::misc::cm55 && current_cosmetics.cm55_selection >= 0) {
                //        if (auto weapon_mesh_1p = current_weapon->GetMesh1P()) {
                //            int mesh_index = current_cosmetics.cm55_selection;
                //            if (mesh_index >= 0 && mesh_index < 60 && c1_ctm[mesh_index]) {
                //                weapon_mesh_1p->setsketeletalmesh(c1_ctm[mesh_index], true);
                //                weapon_mesh_1p->updatemesh();
                //            }
                //        }
                //    }

                    if (globals::misc::modelmesh && globals::misc::mesh4 > 0) {
                        if (auto char_mesh_3p = character->mesh3p()) {
                            int mesh_index = globals::misc::mesh4 - 1;
                            if (mesh_index >= 0 && mesh_index < 32 && e_ctm[mesh_index]) {
                                char_mesh_3p->setsketeletalmesh(e_ctm[mesh_index], true);
                                char_mesh_3p->updatemesh();
                            }
                        }
                    }

                //    if (globals::misc::etr3 && globals::misc::etrv3 > 0) {
                //        if (auto char_mesh_3p = character->mesh3p()) {
                //            int mesh_index = globals::misc::etrv3 - 1;
                //            if (mesh_index >= 0 && mesh_index < 32 && h_ctm[mesh_index]) {
                //                char_mesh_3p->setsketeletalmesh(h_ctm[mesh_index], true);
                //                char_mesh_3p->updatemesh();
                //            }
                //        }
                //    }

                //    if (globals::visuals::cp3 && globals::visuals::cnmd > 0) {
                //        if (auto cosmetic_mesh_3p = character->GetCosmeticMesh3P()) {
                //            int mesh_index = globals::visuals::cnmd - 1;
                //            if (mesh_index >= 0 && mesh_index < 32 && e_ctm[mesh_index]) {
                //                cosmetic_mesh_3p->setsketeletalmesh(e_ctm[mesh_index], true);
                //                cosmetic_mesh_3p->updatemesh();
                //            }
                //        }
                //    }

                //    if (globals::visuals::amk && globals::visuals::amkd > 0) {
                //        if (auto enemy_mesh = character->get_mesh()) {
                //            int mesh_index = globals::visuals::amkd - 1;
                //            if (mesh_index >= 0 && mesh_index < 32 && e_ctm[mesh_index]) {
                //                enemy_mesh->setsketeletalmesh(e_ctm[mesh_index], true);
                //                enemy_mesh->updatemesh();
                //            }
                //        }
                //    }
                //}

                if (globals::visuals::sk3let0n && actor->is_alive()) {
                    SPOOF_FUNC
                        bool isVisible = controllers && controllers->line_of_sight(actor);
                    flinearcolor skeleton_color = isVisible ?
                        defines::VisibleSkeletonColor :
                        defines::InvisibleSkeletonColor;

                    SPOOF_CALL(drawings::draw_skeleton)(controllers, mesh, memory::read<int32_t>((uintptr_t)mesh + offsets::bone_cout), skeleton_color, canvas);
                }

                flinearcolor clr5 = get_color(globals::visuals::vsbg5, vlsclr);

                if (globals::visuals::dstc && actor->is_alive())
                {
                    SPOOF_FUNC
                        wchar_t distance_text[256];

                    swprintf_s(distance_text, L"[ %.fm ]", distance);
                    fvector2d meow = { head_location_2d.x, head_location_2d.y - 45 };

                    SPOOF_CALL(draw_text)(canvas, font, distance_text, clr5, meow);

                }

                if (globals::visuals::cornerbox && actor->is_alive()) {
                    fvector base = mesh->get_bone_location(0);
                    fvector head = mesh->get_bone_location(8);

                    if (controllers) {
                        SPOOF_FUNC
                            SPOOF_CALL(drawings::drawcorner)(controllers, mesh, head, base, defines::visuals_color, canvas);
                    }
                }
                if (globals::visuals::h3althbar && actor->is_alive()) {
                    SPOOF_FUNC
                        double health = actor->health();
                    double shield = actor->shield();

                   
                    if (health >= 75) {
                        defines::health_color = { 0.3f, 0.8f, 0.3f, 1.0f };
                    }
                    else if (health >= 44) {
                        defines::health_color = { 0.9f, 0.7f, 0.1f, 1.0f };
                    }
                    else {
                        defines::health_color = { 0.8f, 0.2f, 0.1f, 1.0f };
                    }

                    fvector base = mesh->get_bone_location(0);
                    fvector head = mesh->get_bone_location(8);

                    SPOOF_CALL(drawings::draw_horizontal_health_bar)(
                        controllers,
                        mesh,
                        head,
                        base,
                        box_height,
                        health,
                        shield,
                        defines::health_color,
                        canvas
                        );
                }

                // player rank, name, ping, bla bla bla

                if (globals::visuals::nmpl && actor->is_alive()) {
                    SPOOF_FUNC
                        fvector2d name_position = { head_location_2d.x, head_location_2d.y - 37 };

                    double time = static_cast<double>(GetTickCount64() % 100000) / 1000.0;
                    float slow_wave = sinf(time * 0.25 + (head_location_2d.x + head_location_2d.y) * 0.002) * 0.02 + 0.98;

                    flinearcolor animated_color = {
                         menu::Colors::Checkbox_Enabled.r * slow_wave,
                         menu::Colors::Checkbox_Enabled.g * slow_wave,
                         menu::Colors::Checkbox_Enabled.b * slow_wave,
                         menu::Colors::Checkbox_Enabled.a
                    };

                    flinearcolor outline_color = { 0.0f, 0.0f, 0.0f, 0.8f };

                    if (state) {
                        auto name = state->get_player_name();
                        if (name.is_valid()) {
                            canvas->k2_drawtext(
                                font,
                                name.c_str(),
                                name_position,
                                { 0.7f, 0.7f },
                                animated_color,
                                0.f,
                                { 0, 0, 0, 0.0f },
                                { 0, 0 },
                                true,
                                false,
                                true,
                                outline_color
                            );
                        }
                    }
                    else {
                        canvas->k2_drawtext(
                            font,
                            L"bot",
                            name_position,
                            { 0.7f, 0.7f },
                            animated_color,
                            0.f,
                            { 0, 0, 0, 0.0f },
                            { 0, 0 },
                            true,
                            false,
                            true,
                            outline_color
                        );
                    }
                }

                //if (globals::visuals::nmpl34 && actor->is_alive()) {
                //    SPOOF_FUNC
                //        fvector2d name_position = { head_location_2d.x, head_location_2d.y - 27 };

                //    double time = 0.0;
                //    if (GetTickCount64) {
                //        DWORD tick_count = GetTickCount64();
                //        time = static_cast<double>(tick_count % 100000) / 1000.0;
                //    }

                //    double slow_wave = 1.0;
                //    if (head_location_2d.x != 0 || head_location_2d.y != 0) {
                //        slow_wave = sinf(time * 0.25 + (head_location_2d.x + head_location_2d.y) * 0.002) * 0.02 + 0.98;
                //    }

                //    flinearcolor animated_color = menu::Colors::Checkbox_Enabled;
                //    animated_color.r *= slow_wave;
                //    animated_color.g *= slow_wave;
                //    animated_color.b *= slow_wave;

                //    flinearcolor outline_color = { 0.0f, 0.0f, 0.0f, 0.8f };

                //    std::wstring platform_str = L"Unknown";

                //    static uobject* platform_name_func = []
                //        {
                //            return uobject::find_object<uobject*>(L"Engine.GameplayStatics.GetPlatformName");
                //        }();

                //    static uobject* platform_type_func = []
                //        {
                //            return uobject::find_object<uobject*>(L"ShooterGame.AresPlatformBlueprintFunctionLibrary.GetClientPlatformType");
                //        }();

                //    fstring platform_name;
                //    EAresPlatformType platform_type = EAresPlatformType::None;

                //    if (platform_name_func) {
                //        struct NameParams {
                //            fstring output;
                //        } name_params;

                //        reinterpret_cast<uobject*>(actor)->process_event(platform_name_func, &name_params);
                //        platform_name = name_params.output;
                //    }

                //    if (platform_type_func) {
                //        struct TypeParams {
                //            EAresPlatformType output;
                //        } type_params;

                //        reinterpret_cast<uobject*>(actor)->process_event(platform_type_func, &type_params);
                //        platform_type = type_params.output;
                //    }

                //    platform_str = L"";

                //    if (platform_name.c_str() && platform_name.c_str()[0] != '\0') {
                //        platform_str += platform_name.c_str();
                //    }
                //    else {
                //        platform_str += L"Unknown";
                //    }

                //    platform_str += L" (";
                //    switch (platform_type) {
                //    case EAresPlatformType::Desktop: platform_str += L"PC"; break;
                //    case EAresPlatformType::Mobile: platform_str += L"Mobile"; break;
                //    case EAresPlatformType::Console: platform_str += L"Console"; break;
                //    default: platform_str += L"Unknown Type"; break;
                //    }
                //    platform_str += L")";

                //    canvas->k2_drawtext(
                //        font,
                //        platform_str.c_str(),
                //        name_position,
                //        { 0.65f, 0.65f },
                //        animated_color,
                //        0.f,
                //        { 0, 0, 0, 0.0f },
                //        { 0, 0 },
                //        true,
                //        false,
                //        true,
                //        outline_color
                //    );
                //}

                //if (globals::visuals::nmpl2 && actor->is_alive()) {
                //    fvector2d name_position = { head_location_2d.x, head_location_2d.y - 50 };

                //    flinearcolor outline_color = { 0.0f, 0.0f, 0.0f, 0.8f };

                //    uintptr_t player_state_ptr = memory::read<uintptr_t>((uintptr_t)actor + offsets::player_state);
                //    if (player_state_ptr) {
                //        int32_t player_id = memory::read<int32_t>(player_state_ptr + offsets::get_player_id);
                //        uint16_t ping = memory::read<uint16_t>(player_state_ptr + offsets::get_ping);

                //        uintptr_t platform_player_ptr = memory::read<uintptr_t>(player_state_ptr + offsets::PlatformPlayer);
                //        if (platform_player_ptr) {
                //            int32_t competitive_tier = memory::read<int32_t>(platform_player_ptr + offsets::CompetitiveTier);
                //            int32_t account_level = memory::read<int32_t>(platform_player_ptr + offsets::AccountLevel);
                //            int32_t leaderboard_pos = memory::read<int32_t>(platform_player_ptr + offsets::LeaderboardPosition);

                //            const wchar_t* rank_name = L"[ Unranked ]";
                //            flinearcolor rank_color = { 0.71, 0.71, 0.71, 1.0 };

                //            switch (static_cast<ECompetitiveTier>(competitive_tier)) {
                //            case ECompetitiveTier::ECompetitiveTier__Iron1:     rank_name = L"[ Iron 1 ]";     rank_color = { 0.43, 0.43, 0.43, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Iron2:     rank_name = L"[ Iron 2 ]";     rank_color = { 0.43, 0.43, 0.43, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Iron3:     rank_name = L"[ Iron 3 ]";     rank_color = { 0.43, 0.43, 0.43, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Bronze1:   rank_name = L"[ Bronze 1] ";   rank_color = { 0.78, 0.49, 0.24, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Bronze2:   rank_name = L"[ Bronze 2 ]";   rank_color = { 0.78, 0.49, 0.24, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Bronze3:   rank_name = L"[ Bronze 3 ]";   rank_color = { 0.78, 0.49, 0.24, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Silver1:   rank_name = L"[ Silver 1 ]";   rank_color = { 0.71, 0.71, 0.78, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Silver2:   rank_name = L"[ Silver 2 ]";   rank_color = { 0.71, 0.71, 0.78, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Silver3:   rank_name = L"[ Silver 3 ]";   rank_color = { 0.71, 0.71, 0.78, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Gold1:     rank_name = L"[ Gold 1 ]";     rank_color = { 1.0, 0.84, 0.0, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Gold2:     rank_name = L"[ Gold 2 ]";     rank_color = { 1.0, 0.84, 0.0, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Gold3:     rank_name = L"[ Gold 3 ]";     rank_color = { 1.0, 0.84, 0.0, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Platinum1: rank_name = L"[ Platinum 1 ]"; rank_color = { 0.33, 0.86, 0.75, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Platinum2: rank_name = L"[ Platinum 2 ]"; rank_color = { 0.33, 0.86, 0.75, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Platinum3: rank_name = L"[ Platinum 3 ]"; rank_color = { 0.33, 0.86, 0.75, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Diamond1:  rank_name = L"[ Diamond 1 ]";  rank_color = { 0.45, 0.39, 1.0, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Diamond2:  rank_name = L"[ Diamond 2 ]";  rank_color = { 0.45, 0.39, 1.0, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Diamond3:  rank_name = L"[ Diamond 3 ]";  rank_color = { 0.45, 0.39, 1.0, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Immortal1: rank_name = L"[ Immortal 1 ]"; rank_color = { 0.67, 0.18, 0.35, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Immortal2: rank_name = L"[ Immortal 2 ]"; rank_color = { 0.67, 0.18, 0.35, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Immortal3: rank_name = L"[ Immortal 3 ]"; rank_color = { 0.67, 0.18, 0.35, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Radiant:   rank_name = L"[ Radiant ]";    rank_color = { 1.0, 0.78, 0.04, 1.0 }; break;
                //            }

                //            std::wstring full_info = std::wstring(rank_name);

                //            if (account_level > 0)
                //                full_info += L" | Level: " + std::to_wstring(account_level);
                //            full_info += L" | Ping: " + std::to_wstring(ping) + L"ms";

                //            if (leaderboard_pos > 0)
                //                full_info += L" | Leaderboard Rank: #" + std::to_wstring(leaderboard_pos);

                //            canvas->k2_drawtext(
                //                font,
                //                full_info.c_str(),
                //                name_position,
                //                { 0.65f, 0.65f },
                //                rank_color,
                //                0.f,
                //                { 0, 0, 0, 0.0f },
                //                { 0, 0 },
                //                true,
                //                false,
                //                true,
                //                outline_color
                //            );
                //        }
                //    }
                //}

                //if (globals::visuals::pclp && actor->is_alive()) {
                //    fvector2d name_position = { head_location_2d.x, head_location_2d.y - 25 };

                //    flinearcolor outline_color = { 0.0f, 0.0f, 0.0f, 0.8f };

                //    uintptr_t player_state_ptr = memory::read<uintptr_t>((uintptr_t)actor + offsets::player_state);
                //    if (player_state_ptr) {
                //        uintptr_t platform_player_ptr = memory::read<uintptr_t>(player_state_ptr + offsets::PlatformPlayer);
                //        if (platform_player_ptr) {
                //            int32_t competitive_tier = memory::read<int32_t>(platform_player_ptr + offsets::CompetitiveTier);

                //            const wchar_t* rank_name = L"UNRANKED";
                //            flinearcolor rank_color = flinearcolor(1.0, 1.0, 1.0, 1.0);

                //            switch (static_cast<ECompetitiveTier>(competitive_tier)) {
                //            case ECompetitiveTier::ECompetitiveTier__Iron1:     rank_name = L"Iron 1";     rank_color = { 0.43, 0.43, 0.43, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Iron2:     rank_name = L"Iron 2";     rank_color = { 0.43, 0.43, 0.43, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Iron3:     rank_name = L"Iron 3";     rank_color = { 0.43, 0.43, 0.43, 1.0 }; break;

                //            case ECompetitiveTier::ECompetitiveTier__Bronze1:   rank_name = L"Bronze 1";   rank_color = { 0.78, 0.49, 0.24, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Bronze2:   rank_name = L"Bronze 2";   rank_color = { 0.78, 0.49, 0.24, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Bronze3:   rank_name = L"Bronze 3";   rank_color = { 0.78, 0.49, 0.24, 1.0 }; break;

                //            case ECompetitiveTier::ECompetitiveTier__Silver1:   rank_name = L"Silver 1";   rank_color = { 0.71, 0.71, 0.78, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Silver2:   rank_name = L"Silver 2";   rank_color = { 0.71, 0.71, 0.78, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Silver3:   rank_name = L"Silver 3";   rank_color = { 0.71, 0.71, 0.78, 1.0 }; break;

                //            case ECompetitiveTier::ECompetitiveTier__Gold1:     rank_name = L"Gold 1";     rank_color = { 1.0, 0.84, 0.0, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Gold2:     rank_name = L"Gold 2";     rank_color = { 1.0, 0.84, 0.0, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Gold3:     rank_name = L"Gold 3";     rank_color = { 1.0, 0.84, 0.0, 1.0 }; break;

                //            case ECompetitiveTier::ECompetitiveTier__Platinum1: rank_name = L"Platinum 1"; rank_color = { 0.33, 0.86, 0.75, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Platinum2: rank_name = L"Platinum 2"; rank_color = { 0.33, 0.86, 0.75, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Platinum3: rank_name = L"Platinum 3"; rank_color = { 0.33, 0.86, 0.75, 1.0 }; break;

                //            case ECompetitiveTier::ECompetitiveTier__Diamond1:  rank_name = L"Diamond 1";  rank_color = { 0.45, 0.39, 1.0, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Diamond2:  rank_name = L"Diamond 2";  rank_color = { 0.45, 0.39, 1.0, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Diamond3:  rank_name = L"Diamond 3";  rank_color = { 0.45, 0.39, 1.0, 1.0 }; break;

                //            case ECompetitiveTier::ECompetitiveTier__Immortal1: rank_name = L"Immortal 1"; rank_color = { 0.67, 0.18, 0.35, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Immortal2: rank_name = L"Immortal 2"; rank_color = { 0.67, 0.18, 0.35, 1.0 }; break;
                //            case ECompetitiveTier::ECompetitiveTier__Immortal3: rank_name = L"Immortal 3"; rank_color = { 0.67, 0.18, 0.35, 1.0 }; break;

                //            case ECompetitiveTier::ECompetitiveTier__Radiant:   rank_name = L"Radiant";    rank_color = { 1.0, 0.78, 0.04, 1.0 }; break;

                //            default:                                            rank_name = L"UNRANKED";  rank_color = { 0.71, 0.71, 0.71, 1.0 }; break;
                //            }

                //            std::wstring label = L"[ " + std::wstring(rank_name) + L" ]";

                //            canvas->k2_drawtext(
                //                font,
                //                label.c_str(),
                //                name_position,
                //                { 0.7f, 0.7f },
                //                rank_color,
                //                0.f,
                //                { 0, 0, 0, 0.0f },
                //                { 0, 0 },
                //                true,
                //                false,
                //                true,
                //                outline_color
                //            );
                //        }
                //    }
                //}

                if (globals::visuals::weaponesp && actor->is_alive() && distance >= 1.2f) {
                    SPOOF_FUNC
                        auto inventory = actor->get_inventory();
                    if (inventory) {
                        auto equippable = inventory->get_current_equippable();
                        if (equippable) {
                            fstring weapon_name = system::get_object_name(equippable);
                            if (weapon_name.c_str() && weapon_name.c_str()[0] != L'\0') {
                                fstring weapon_display_name = Names::WeaponName(weapon_name);
                                if (weapon_display_name.c_str() && weapon_display_name.c_str()[0] != L'\0') {

                                    fvector2d text_pos = { head_location_2d.x, head_location_2d.y + box_height + 19 }; 

                                    flinearcolor text_color = { 0.9f, 0.9f, 0.9f, 1.0f };
                                    flinearcolor outline_color = { 0.0f, 0.0f, 0.0f, 0.8f };
                                    canvas->k2_drawtext(
                                        font,
                                        weapon_display_name.c_str(),
                                        text_pos,
                                        { 0.65f, 0.65f },
                                        text_color,
                                        0.f,
                                        { 0, 0, 0, 0.0f },
                                        { 0, 0 },
                                        true,
                                        false,
                                        true,
                                        outline_color
                                    );
                                }
                            }
                        }
                    }
                }

                if (actor->is_alive()) {

                    bool isVisible = controllers && controllers->line_of_sight(actor);
                    flinearcolor box_color = isVisible ? flinearcolor{ 1.f, 1.f, 1.f, 1.f }
                    : flinearcolor{ 1.f, 0.f, 0.f, 1.f };

                    fvector base = mesh->get_bone_location(0);
                    fvector head = mesh->get_bone_location(8);

                    if (globals::visuals::box3d) {
                        if (controllers) {
                            SPOOF_FUNC
                                SPOOF_CALL(drawings::draw_3d)(controllers, mesh, head, base, box_color, canvas);
                        }
                    }

                    if (globals::visuals::box2d && actor->is_alive()) {
                        if (controllers) {
                            SPOOF_FUNC
                                bool isVisible = controllers && controllers->line_of_sight(actor);
                            flinearcolor box_color = isVisible ?
                                defines::VisibleBox_ESPColor :
                                defines::Invisible_ESPColor;

                            SPOOF_CALL(drawings::draw_2d_box)(controllers, mesh, head, base, box_color, canvas);
                        }
                    }


                    if (globals::visuals::box2ds) {
                        if (controllers) {
                            SPOOF_FUNC
                                /* SPOOF_CALL(drawings::draw_2d)(controllers, mesh, head, base, box_color, canvas);*/
                        }
                    }
                }




                if (globals::visuals::chinese_hat)
                {
                    if (actor->is_alive() && controllers && mesh)
                    {
                        fvector head = mesh->get_bone_location(8);
                        fvector base = mesh->get_bone_location(0);

                        SPOOF_FUNC
                            SPOOF_CALL(drawings::partyhat)(controllers, mesh, head, base, canvas);
                    }
                }

                /* if (GetAsyncKeyState(0x50) & 1) {
                     globals::visuals::chams = !globals::visuals::chams;
                 }

                 if (globals::visuals::chams) {

                 }*/


                 
                if (globals::visuals::self_galaxy_enabled &&
                    mysh && gameinstance &&
                    mysh->is_alive() &&
                    mysh->get_mesh()) {

                    apply_galaxy_chams_to_self(mysh, gameinstance);  
                }

                if (globals::visuals::crystal_chams_enabled &&
                    mysh && gameinstance &&
                    mysh->is_alive() &&
                    mysh->get_mesh()) {

                    apply_crystal_chams_to_self(mysh, gameinstance);
                }

                if (globals::visuals::dynamic_fresnel_outline &&
                    mysh && gameinstance &&
                    mysh->is_alive() &&
                    mysh->get_mesh()) {

                    apply_dynamic_fresnel_outline(mysh, gameinstance);
                }

                if (globals::visuals::outline_enabled &&
                    pawn && actor && controllers && mysh &&
                    actor->is_alive() && mysh->is_alive() &&
                    actor->get_mesh() && mysh->get_mesh()) {

                    apply_outline_chams(pawn, actor, controllers);
                }


                if (globals::visuals::headb0x) {
                    SPOOF_FUNC;
                    fvector2d position = { head_location_long_2d.x, head_location_long_2d.y };
                    drawings::head_circle(position, lineW, lineH, defines::visuals_color, canvas);
                }
       

                if (globals::visuals::agenticon) {
                    SPOOF_FUNC;
                    fvector2d position1 = { head_location_long_2d.x + 35.f, head_location_long_2d.y };
                    drawings::agent_icon(actor, position1, distance, canvas);
                }
               
                if (globals::visuals::agent_name && actor->is_alive() && distance >= 1.2f) {
                    SPOOF_FUNC

                        fstring object_name = system::get_object_name(actor);

                    if (object_name.c_str() && object_name.c_str()[0] != L'\0') {
                        fstring agent_display_name = Names::CharacterName(object_name);

                        if (agent_display_name.c_str() && agent_display_name.c_str()[0] != L'\0') {

                            fvector2d text_pos = { head_location_2d.x, head_location_2d.y - 15 }; // -15'ten -25'e (daha yukarı)


                            flinearcolor text_color = { 0.9f, 0.9f, 0.9f, 1.0f };
                            flinearcolor outline_color = { 0.0f, 0.0f, 0.0f, 0.8f };


                            canvas->k2_drawtext(
                                font,
                                agent_display_name.c_str(),
                                text_pos,
                                { 0.50f, 0.50f },
                                text_color,
                                0.f,
                                { 0, 0, 0, 0.0f },
                                { 0, 0 },
                                true,
                                false,
                                true,
                                outline_color
                            );
                        }
                    }
                }

                if (globals::visuals::snapl1ne && actor->is_alive()) {
                    SPOOF_FUNC
                        SPOOF_CALL(drawings::draw_snapline)(character, head_location_2d, defines::visuals_color, canvas);
                }

             

                if (globals::visuals::visiblecheck && actor->is_alive()) {
                    SPOOF_FUNC
                        defines::visuals_color = (controllers->line_of_sight(actor) ?
                            flinearcolor{ 0.0, 255.0 ,0.0, 1.0 } : flinearcolor{ 255.0, 0.0, 0.0, 1.0 });

                }

                flinearcolor clr3 = get_color(globals::visuals::vsbg3, vlsclr);

                if (globals::visuals::box3dd && actor->is_alive()) {
                    SPOOF_FUNC
                        SPOOF_CALL(drawings::draw_3d)(controllers, mesh, fvector(head_location.x, head_location.y, head_location.z), fvector(root_location.x, root_location.y, root_location.z), clr3, canvas);
                }


                if (globals::visuals::chamsvsb && globals::visuals::visible_check_ch) {
                    SPOOF_FUNC
                        reinterpret_cast<uskeletalmeshcomponent* (*__fastcall)(uskeletalmeshcomponent*, int, bool)>(memory::module_base + offsets::set_ares_outline_mode)(mesh, 4, true);

                    ares_outline::setoutlinemode1(world,
                        { globals::visuals::chams_color.r * globals::visuals::glow_intensity,
                          globals::visuals::chams_color.g * globals::visuals::glow_intensity,
                          globals::visuals::chams_color.b * globals::visuals::glow_intensity,
                          globals::visuals::chams_color.a * globals::visuals::chams_intensity });
                }
                else if (globals::visuals::chamssd) {
                    SPOOF_FUNC
                        reinterpret_cast<uskeletalmeshcomponent* (*__fastcall)(uskeletalmeshcomponent*, int, bool)>(memory::module_base + offsets::set_ares_outline_mode)(mesh, 1, true);

                    flinearcolor ChamsColorvni = { 1.0f, 0.0f, 0.0f, 1.0f };
                    ares_outline::setoutlinemode1(world,
                        { ChamsColorvni.r * globals::visuals::glow_intensity,
                          ChamsColorvni.g * globals::visuals::glow_intensity,
                          ChamsColorvni.b * globals::visuals::glow_intensity,
                          ChamsColorvni.a * globals::visuals::chams_intensity });
                }
                else if (globals::visuals::chamsal) {
                    SPOOF_FUNC
                        reinterpret_cast<uskeletalmeshcomponent* (__fastcall*)(uskeletalmeshcomponent*, int, bool)>(memory::module_base + offsets::set_ares_outline_mode)(mesh, 4, true);
                    ares_outline::setoutlinemode(world,
                        { globals::visuals::chams_color.r * globals::visuals::glow_intensity,
                          globals::visuals::chams_color.g * globals::visuals::glow_intensity,
                          globals::visuals::chams_color.b * globals::visuals::glow_intensity,
                          globals::visuals::chams_color.a * globals::visuals::chams_intensity },
                        { globals::visuals::chams_color.r * globals::visuals::glow_intensity,
                          globals::visuals::chams_color.g * globals::visuals::glow_intensity,
                          globals::visuals::chams_color.b * globals::visuals::glow_intensity,
                          globals::visuals::chams_color.a * globals::visuals::chams_intensity });
                }
                else if (globals::visuals::chamsbg) {
                    SPOOF_FUNC
                        static float TimePassed = 0.0f;
                    TimePassed += 0.02f * globals::visuals::brps;
                    flinearcolor bng = GetRainbowColor(TimePassed);

                    reinterpret_cast<uskeletalmeshcomponent* (*__fastcall)(uskeletalmeshcomponent*, int, bool)>(memory::module_base + offsets::set_ares_outline_mode)(mesh, 4, true);

                    ares_outline::setoutlinemode(world,
                        { bng.r * globals::visuals::glow_intensity,
                          bng.g * globals::visuals::glow_intensity,
                          bng.b * globals::visuals::glow_intensity,
                          bng.a * globals::visuals::chams_intensity },
                        { bng.r * globals::visuals::glow_intensity,
                          bng.g * globals::visuals::glow_intensity,
                          bng.b * globals::visuals::glow_intensity,
                          bng.a * globals::visuals::chams_intensity });
                }
                else {
                    SPOOF_FUNC
                        reinterpret_cast<uskeletalmeshcomponent* (*__fastcall)(uskeletalmeshcomponent*, int, bool)>(memory::module_base + offsets::set_ares_outline_mode)(mesh, 0, true);
                }



                if (globals::visuals::chamsfsd && world && mesh && character && controllers && character->is_alive())
                {
                    SPOOF_FUNC;

                    static const wchar_t* material_paths[] =
                    {
                     L"/Game/Equippables/_Core/Materials/SpecialMaterials/Esportsinvitational/1P_Esportsinvitational_Crystal_Melee_v3_MI.1P_Esportsinvitational_Crystal_Melee_v3_MI",
                     L"/Game/Equippables/_Core/Materials/SpecialMaterials/Syndra/3P_Syndra_Crystal_Front_MI.3P_Syndra_Crystal_Front_MI",
                     L"/Game/Equippables/_Core/Materials/SpecialMaterials/Ninja/AK_Ninja_Shuriken_MI.AK_Ninja_Shuriken_MI",
                     L"/Game/Equippables/_Core/Materials/SpecialMaterials/Arcade/Arcade_Emissive_Blue_MI.Arcade_Emissive_Blue_MI",
                     L"/Game/Equippables/_Core/Materials/SpecialMaterials/Afterglow3/BakedLight/Afterglow3_BakedLight_MI.Afterglow3_BakedLight_MI",
                     L"/Game/Equippables/_Core/Materials/SpecialMaterials/CosmosShader/UnderTheSea/UnderTheSea_MI.UnderTheSea_MI",
                     L"/Game/Equippables/_Core/Materials/SpecialMaterials/Sovereign2/Sovereign2_v3_Gem_3P_MI.Sovereign2_v3_Gem_3P_MI",
                     L"/Game/Equippables/_Core/Materials/SpecialMaterials/Syndra/Syndra_Crystal_Front_MI.Syndra_Crystal_Front_MI",
                     L"/Game/Equippables/_Core/Materials/SpecialMaterials/CosmosShader/SovWorld/3p_SovWorld_MI.3p_SovWorld_MI",
                    };

                    int material_count = sizeof(material_paths) / sizeof(material_paths[0]);
                    int selected = globals::misc::enemy_chams_material_index;

                    if (selected < 0 || selected >= material_count)
                        selected = 0;

                    uobject* material = uobject::static_load_object(nullptr, nullptr, material_paths[selected]);
                    if (!material || !memory::IsValidPointer(uintptr_t(material)))
                        return;

                    int num_materials = mesh->get_num_materials();
                    if (num_materials <= 0 || num_materials > 50)
                        return;

                    for (int i = 0; i < num_materials; i++)
                    {
                        UMaterialInstanceDynamic* dynamic_mat = mesh->create_and_set_material_instance_dynamic_from_material(i, material)->cast<UMaterialInstanceDynamic>();
                        if (!dynamic_mat || !memory::IsValidPointer(uintptr_t(dynamic_mat)))
                            continue;

                        // Wallhack toggle (visible/invisible)
                        if (globals::visuals::chams_visible_invisible)
                        {
                            dynamic_mat->set_scalar_parameter_value(string::string_to_name(L"IgnoreDepth"), 1.0f);
                        }
                        else
                        {
                            dynamic_mat->set_scalar_parameter_value(string::string_to_name(L"IgnoreDepth"), 0.0f);
                        }

                    }

                    flinearcolor finalColor{ 1.f, 1.f, 1.f, 1.f };

                    if (globals::visuals::rainbow_chams)
                    {
                        SPOOF_FUNC;

                        float t = GetTickCount64() * 0.002f;

                        finalColor = flinearcolor(
                            (sinf(t + 0.5f) * 0.5f + 0.5f) * globals::visuals::chams_intensity,
                            (sinf(t + 2.0f) * 0.5f + 0.5f) * globals::visuals::chams_intensity,
                            (sinf(t + 4.0f) * 0.5f + 0.5f) * globals::visuals::chams_intensity,
                            1.0f

                        );
                    }



                    /* if (globals::visuals::self_chams && mysh && mysh->is_alive())
                     {
                         SPOOF_FUNC;
                         apply_self_chams(mysh, viewportclient);
                     }

                */





                    ares_outline::setoutlinemode(world, finalColor, finalColor);


                    uintptr_t fresnel = *(uintptr_t*)((uintptr_t)mesh + offsets::fresnelcomponent);
                    if (fresnel)
                    {
                        *(float*)(fresnel + 0x10) = 1000.0f * globals::visuals::chams_intensity;
                        *(float*)(fresnel + 0x14) = 10.0f * globals::visuals::chams_intensity;
                    }

                    uintptr_t fresnel3 = *(uintptr_t*)((uintptr_t)mesh + offsets::fr3scomp);
                    if (fresnel3)
                    {
                        *(float*)(fresnel3 + 0x10) = 1000.0f * globals::visuals::chams_intensity;
                        *(float*)(fresnel3 + 0x14) = 10.0f * globals::visuals::chams_intensity;
                    }
                }


                if (globals::aimbot::a1mbot && actor->is_alive()) {
                    SPOOF_FUNC

                        uskeletalmeshcomponent* mesh = actor->get_mesh();
                    if (!mesh) continue;

                    bool is_visible = !globals::aimbot::v1sh_ch3ck || controllers->line_of_sight(actor);
                    if (!is_visible) continue;

                    double delta_x = head_location_2d.x - screen_center_x;
                    double delta_y = head_location_2d.y - screen_center_y;

                    double distance = sqrtf(delta_x * delta_x + delta_y * delta_y);
                    double screen_distance = math::distance_2d(head_location_2d, { screen_center_x, screen_center_y });


                    if (globals::aimbot::target_selection == 0) {
                        float real_distance = my_shooter_relative_location.distance(relative_location);
                        if (real_distance < closest_distance) {
                            target_id = idx;
                            closest_distance = real_distance;
                        }
                    }
                    else {
                        if (screen_distance < closest_distance) {
                            target_id = idx;
                            closest_distance = screen_distance;
                        }
                    }
                }
                }
            if (character && controllers) {

                if (globals::misc::aspect_ratio_enabled || globals::misc::aa || globals::misc::tperson) {
                    uintptr_t current_camera = uintptr_t(camera);

                    if (camera_engine != current_camera || should_hook_gay) {
                        SPOOF_FUNC
                            camera_engine = current_camera;

                        if (character && character->is_alive())
                        {
                            static shadow_vmt1 camera_hook;
                            camera_hook.g47ghf234h79g8f237h89<decltype(hooks::SetCameraCachePOVOriginal)>(
                                memory::module_base,
                                (uintptr_t)camera_engine,
                                0xf2,
                                (void*)hooks::SetCameraCachePOVHook,
                                &hooks::SetCameraCachePOVOriginal
                            );
                        }

                        should_hook_gay = false;
                    }
                }

                static float last_health[100] = { 100.0f };
                static bool was_visible[100] = { false };
                static bool kill_message_sent[100] = { false };
                static bool download_started = false;
                if (!download_started) {
                    download_started = true;
                    std::thread([]() {
                        if (!kill_sound1_exists()) download_kill_sound1();
                        if (!kill_sound2_exists()) download_kill_sound2();
                        if (!kill_sound3_exists()) download_kill_sound3();
                        }).detach();
                }
                for (int i = 0; i < actors.count; i++) {
                    auto actor = actors[i];
                    if (actor && actor != character) {
                        float current_health = actor->health();
                        bool currently_visible = controllers->line_of_sight(actor);
                        if (last_health[i] > 0 && current_health <= 0 && was_visible[i]) {
                            if (globals::misc::killsound) {
                                if (globals::misc::killsound_selection == 0) {
                                    if (kill_sound1_exists()) {
                                        PlaySoundW(L"C:\\Sound\\kill_sound1.wav", NULL, SND_FILENAME | SND_ASYNC);
                                    }
                                }
                                else if (globals::misc::killsound_selection == 1) {
                                    if (kill_sound2_exists()) {
                                        PlaySoundW(L"C:\\Sound\\kill_sound2.wav", NULL, SND_FILENAME | SND_ASYNC);
                                    }
                                }
                                else if (globals::misc::killsound_selection == 2) {
                                    if (kill_sound3_exists()) {
                                        PlaySoundW(L"C:\\Sound\\kill_sound3.wav", NULL, SND_FILENAME | SND_ASYNC);
                                    }
                                }
                            }
                        }


                        if (globals::misc::killsays && last_health[i] > 0 && current_health <= 0 && was_visible[i] && !kill_message_sent[i]) {
                            globals::misc::kill_counter++;
                            auto chat_manager = UThreadedChatManager::GetThreadedChatManager(world);
                            if (chat_manager) {
                                std::string msg = globals::misc::chat_message;
                                wchar_t wmsg[256];
                                mbstowcs(wmsg, msg.c_str(), 256);
                                fstring message_string = fstring(wmsg);
                                ftext message_text = text::string_to_text(message_string);
                                chat_manager->send_chat_message_v2(EChatRoomType::All, message_text);
                                kill_message_sent[i] = true;
                            }
                        }


                        if (current_health > 0) {
                            kill_message_sent[i] = false;
                        }

                        last_health[i] = current_health;
                        was_visible[i] = currently_visible;
                    }
                }

                
                if (target_id != -1 && globals::aimbot::a1mbot)
                {

                 /*   if (globals::aimbot::enable_360_fov)
                    {
                        controllers->unlock_fov();
                        character->UnlockFOV();
                    }*/
                    ashootercharacter* actor = actors[target_id];
                    if (!actor || actor == character) continue;

                    uskeletalmeshcomponent* mesh = actor->get_mesh();
                    if (!mesh) continue;

                    if (actor->is_alive()) {
                        fvector2d head_screen;
                        fvector target = get_target_bone_matrix(mesh, globals::aimbot::a1m_b0ne);
                        fvector spread_angle;
                        static const fkey lmb_key{ fname{ string::string_to_name(crypt(L"LeftMouseButton").decrypt()) } };

                        if (!target.is_valid()) continue;

                        bool aim_key_pressed = GetAsyncKeyState(globals::aimbot::a1m_k3y);

                        fvector BestAimPoint;
                        fstring BestBoneName;
                        bool CanAutoWall = false;

                        bool visible_check = controllers->line_of_sight(actor);
                        bool can_shoot = (!globals::aimbot::v1sh_ch3ck || visible_check);
                        fvector final_target = target;

                        auto current_wep = character->get_inventory()->get_current_equippable();
                        fstring obj_name = helper::convert_weapon_name(system::get_object_name(current_wep));

                        bool is_valid_weapon =
                            obj_name.wide() == L"Bulldog" || obj_name.wide() == L"Phantom" || obj_name.wide() == L"Vandal" ||
                            obj_name.wide() == L"Operator" || obj_name.wide() == L"Marshal" || obj_name.wide() == L"Sheriff" ||
                            obj_name.wide() == L"Spectre" || obj_name.wide() == L"Outlaw" || obj_name.wide() == L"Classic" ||
                            obj_name.wide() == L"Shorty" || obj_name.wide() == L"Frenzy" || obj_name.wide() == L"Ghost" ||
                            obj_name.wide() == L"Stinger" || obj_name.wide() == L"Bucky" || obj_name.wide() == L"Judge" ||
                            obj_name.wide() == L"Guardian" || obj_name.wide() == L"Ares" || obj_name.wide() == L"Odin";

                        if (aim_key_pressed && can_shoot && actor->is_alive()) {
                            SPOOF_FUNC
                                fvector CameraPos = camera->get_camera_location();
                            fvector ControlRotation = controllers->get_control_rotation();
                            fvector vector_pos = final_target - CameraPos;
                            double distance = vector_pos.size();

                            if (distance <= 0) continue;

                            double normalized_z = vector_pos.z / distance;
                            if (normalized_z < -1.0) normalized_z = -1.0;
                            if (normalized_z > 1.0) normalized_z = 1.0;

                            double x = -(acos(normalized_z) * (180.0 / 3.14159265358979323846) - 90.0);
                            double y = atan2(vector_pos.y, vector_pos.x) * (180.0 / 3.14159265358979323846);

                            fvector target_rotation(x, y, 0.0);
                            fvector new_aim_rotation;

                            if (globals::aimbot::reco1l_contr0l) {
                                fvector recoil = camera->get_camera_rotation() - ControlRotation;
                                new_aim_rotation = target_rotation - recoil * 2.0;
                            }
                            else {
                                new_aim_rotation = target_rotation;
                            }

                            fvector new_rotation = smooth(new_aim_rotation, ControlRotation, globals::aimbot::a1m_sm00th);

                            new_rotation.x = fmod(new_rotation.x + 360.0, 360.0);
                            new_rotation.y = fmod(new_rotation.y + 360.0, 360.0);

                            if (!new_rotation.is_valid()) continue;

                            controllers->set_control_rotation(new_rotation);

                        }
                    }

                }


                if (target_id != -1 && globals::aimbot::a1mbot)
                {
                   /* if (globals::aimbot::enable_360_fov)
                    {
                        controllers->unlock_fov();
                        character->UnlockFOV();
                    }*/
                    ashootercharacter* actor = actors[target_id];
                    if (!actor || actor == character) continue;

                    uskeletalmeshcomponent* mesh = actor->get_mesh();
                    if (!mesh) continue;

                    if (actor->is_alive()) {
                        fvector2d head_screen;
                        fvector target = get_target_bone_matrix(mesh, globals::aimbot::a1m_b0ne);
                        fvector spread_angle;
                        static const fkey lmb_key{ fname{ string::string_to_name(crypt(L"LeftMouseButton").decrypt()) } };

                        if (!target.is_valid()) continue;

                        bool aim_key_pressed = GetAsyncKeyState(globals::aimbot::a1m_k3y);

                        fvector BestAimPoint;
                        fstring BestBoneName;
                        bool CanAutoWall = false;

                        bool visible_check = controllers->line_of_sight(actor);
                        bool can_shoot = (!globals::aimbot::v1sh_ch3ck || visible_check);
                        fvector final_target = target;

                        auto current_wep = character->get_inventory()->get_current_equippable();
                        fstring obj_name = helper::convert_weapon_name(system::get_object_name(current_wep));

                        bool is_valid_weapon =
                            obj_name.wide() == L"Bulldog" || obj_name.wide() == L"Phantom" || obj_name.wide() == L"Vandal" ||
                            obj_name.wide() == L"Operator" || obj_name.wide() == L"Marshal" || obj_name.wide() == L"Sheriff" ||
                            obj_name.wide() == L"Spectre" || obj_name.wide() == L"Outlaw" || obj_name.wide() == L"Classic" ||
                            obj_name.wide() == L"Shorty" || obj_name.wide() == L"Frenzy" || obj_name.wide() == L"Ghost" ||
                            obj_name.wide() == L"Stinger" || obj_name.wide() == L"Bucky" || obj_name.wide() == L"Judge" ||
                            obj_name.wide() == L"Guardian" || obj_name.wide() == L"Ares" || obj_name.wide() == L"Odin";

                        if (aim_key_pressed && can_shoot && actor->is_alive()) {
                            SPOOF_FUNC
                                fvector CameraPos = camera->get_camera_location();
                            fvector ControlRotation = controllers->get_control_rotation();
                            fvector vector_pos = final_target - CameraPos;
                            double distance = vector_pos.size();

                            if (distance <= 0) continue;

                            double normalized_z = vector_pos.z / distance;
                            if (normalized_z < -1.0) normalized_z = -1.0;
                            if (normalized_z > 1.0) normalized_z = 1.0;

                            double x = -(acos(normalized_z) * (180.0 / 3.14159265358979323846) - 90.0);
                            double y = atan2(vector_pos.y, vector_pos.x) * (180.0 / 3.14159265358979323846);

                            fvector target_rotation(x, y, 0.0);
                            fvector new_aim_rotation;

                            if (globals::aimbot::reco1l_contr0l) {
                                fvector recoil = camera->get_camera_rotation() - ControlRotation;
                                new_aim_rotation = target_rotation - recoil * 2.0;
                            }
                            else {
                                new_aim_rotation = target_rotation;
                            }

                            fvector new_rotation = smooth(new_aim_rotation, ControlRotation, globals::aimbot::a1m_sm00th);

                            new_rotation.x = fmod(new_rotation.x + 360.0, 360.0);
                            new_rotation.y = fmod(new_rotation.y + 360.0, 360.0);

                            if (!new_rotation.is_valid()) continue;

                            controllers->set_control_rotation(new_rotation);
                        }
                    }

                }

                if (target_id != -1 && (globals::aimbot::a1mbot || globals::aimbot::spread_comp))
                {
           /*         if (globals::aimbot::enable_360_fov)
                    {
                        controllers->unlock_fov();
                        character->UnlockFOV();
                    }*/
                    ashootercharacter* actor = actors[target_id];
                    if (!actor || actor == character) continue;

                    uskeletalmeshcomponent* mesh = actor->get_mesh();
                    if (!mesh) continue;

                    if (actor->is_alive()) {
                        fvector2d head_screen;
                        fvector target = get_target_bone_matrix(mesh, globals::aimbot::a1m_b0ne);
                        fvector spread_angle;
                        static const fkey lmb_key{ fname{ string::string_to_name(crypt(L"LeftMouseButton").decrypt()) } };

                        if (!target.is_valid()) continue;

                        bool aim_key_pressed = GetAsyncKeyState(globals::aimbot::a1m_k3y);
                        auto current_wep = character->get_inventory()->get_current_equippable();
                        fstring obj_name = helper::convert_weapon_name(system::get_object_name(current_wep));

                        bool is_valid_weapon =
                            obj_name.wide() == L"Bulldog" || obj_name.wide() == L"Phantom" || obj_name.wide() == L"Vandal" ||
                            obj_name.wide() == L"Operator" || obj_name.wide() == L"Marshal" || obj_name.wide() == L"Sheriff" ||
                            obj_name.wide() == L"Spectre" || obj_name.wide() == L"Outlaw" || obj_name.wide() == L"Classic" ||
                            obj_name.wide() == L"Shorty" || obj_name.wide() == L"Frenzy" || obj_name.wide() == L"Ghost" ||
                            obj_name.wide() == L"Stinger" || obj_name.wide() == L"Bucky" || obj_name.wide() == L"Judge" ||
                            obj_name.wide() == L"Guardian" || obj_name.wide() == L"Ares" || obj_name.wide() == L"Odin";



                        fvector BestAimPoint;
                        fstring BestBoneName;
                        bool CanAutoWall = false;

                        bool visible_check = controllers->line_of_sight(actor);
                        bool can_shoot = (!globals::aimbot::v1sh_ch3ck || visible_check);
                        fvector final_target = target;

           

                        if ((aim_key_pressed || (globals::aimbot::auto_fire_mode == 1 && globals::aimbot::autoshot)) && can_shoot && is_valid_weapon) {
                            fvector CameraPos = fvector(0, 0, 0);
                            fvector firing_direction = fvector(0, 0, 0);

                            character->get_firing_location_and_direction(&CameraPos, &firing_direction, false);
                            fvector ControlRotation = controllers->get_control_rotation();
                            fvector original_target = final_target;
                            fvector resolved_target = final_target;
                            static std::unordered_map<uintptr_t, std::unique_ptr<UltimateValorantResolver>> resolver_instances;

                            if (globals::aimbot::vsr) {
                                uintptr_t target_key = (uintptr_t)actor;

                                if (resolver_instances.find(target_key) == resolver_instances.end()) {
                                    resolver_instances[target_key] = std::make_unique<UltimateValorantResolver>(actor, character);
                                }

                                UltimateValorantResolver& resolver = *resolver_instances[target_key];

                                fvector target_velocity = actor->GetVelocity();
                                fvector head_bone = actor->get_mesh()->get_bone_location(8);

                                resolved_target = resolver.ResolveHeadPosition(head_bone, target_velocity);
                                final_target = resolved_target;
                                resolver.UpdateVisualizationData(original_target, resolved_target);

                                static bool was_shooting = false;
                                if (globals::aimbot::autoshot && !was_shooting) {
                                    resolver.RegisterShotFired();
                                    was_shooting = true;
                                }
                                else if (!globals::aimbot::autoshot) {
                                    was_shooting = false;
                                }
                            }


                            fvector vector_pos = final_target - CameraPos;
                            double distance = vector_pos.size();

                            if (distance <= 0) continue;

                            double normalized_z = vector_pos.z / distance;
                            if (normalized_z < -1.0) normalized_z = -1.0;
                            if (normalized_z > 1.0) normalized_z = 1.0;

                            double x = -(acos(normalized_z) * (180.0 / 3.14159265358979323846) - 90.0);
                            double y = atan2(vector_pos.y, vector_pos.x) * (180.0 / 3.14159265358979323846);

                            fvector target_rotation(x, y, 0.0);
                            fvector new_aim_rotation;

                            if (globals::aimbot::reco1l_contr0l) {
                                fvector recoil = camera->get_camera_rotation() - ControlRotation;
                                new_aim_rotation = target_rotation - recoil * 2.0;
                            }
                            else {
                                new_aim_rotation = target_rotation;
                            }

                            fvector new_rotation = smooth(new_aim_rotation, ControlRotation, globals::aimbot::a1m_sm00th);

                            new_rotation.x = fmod(new_rotation.x + 360.0, 360.0);
                            new_rotation.y = fmod(new_rotation.y + 360.0, 360.0);

                            if (globals::misc::tperson) {
                                CameraPos = character->get_mesh()->get_bone_location(8);
                            }
                            else {
                                CameraPos = camera->get_camera_location();
                            }

                            if (globals::aimbot::spread_comp && character->is_alive()) {
                                auto current_inv = character->get_inventory();
                                if (current_inv) {
                                    auto current_equip = current_inv->get_current_equippable();
                                    auto firing_state = memory::read<uint64_t>(uintptr_t(current_equip) + offsets::FiringStateComp);
                                    spread_angle = NoSpread436467::calc_spread(character, (uintptr_t)firing_state, current_equip, new_rotation);

                                    if (!spread_angle.is_null()) {
                                        if (globals::aimbot::spread_comp_strength != 1.0f) {
                                            spread_angle = spread_angle * globals::aimbot::spread_comp_strength;
                                        }
                                        new_rotation = new_rotation - spread_angle;
                                    }
                                }
                            }
                            controllers->set_control_rotation(new_rotation);

                            static DWORD spread_comp_ready_time = 0;
                            static DWORD shoot_delay_time = 0;
                            static bool delay_pending = false;
                            static bool spread_locked = false;

                            bool anti_aim_enabled = globals::misc::spinner || globals::misc::aa;

                            if (globals::aimbot::spread_comp && !spread_locked)
                            {
                                spread_comp_ready_time = GetTickCount() + (DWORD)globals::aimbot::spread_comp_delay;
                                spread_locked = true;
                                delay_pending = false;
                            }

                            if (anti_aim_enabled) {
                                if (spread_locked && GetTickCount() >= spread_comp_ready_time)
                                {

                                    if (can_shoot && !delay_pending)
                                    {
                                        globals::stop_for_shot = true;
                                        shoot_delay_time = GetTickCount() + (DWORD)globals::aimbot::autoshoot_delay;
                                        delay_pending = true;
                                    }

                                    if (globals::aimbot::auto_fire_mode == 0)
                                    {
                                        if (delay_pending && globals::aimbot::autoshot && aim_key_pressed && GetTickCount() >= shoot_delay_time)
                                        {
                                            controllers->SimulateInputKey(lmb_key, true);
                                            controllers->SimulateInputKey(lmb_key, false);

                                            if (globals::aimbot::vsr) {
                                                uintptr_t target_key = (uintptr_t)actor;
                                                if (resolver_instances.find(target_key) != resolver_instances.end()) {
                                                    resolver_instances[target_key]->RegisterShotHit();
                                                    ResolverVisualizer::RegisterHit();
                                                }
                                            }

                                            globals::stop_for_shot = false;
                                            delay_pending = false;
                                            spread_locked = false;
                                        }
                                    }
                                    else if (globals::aimbot::auto_fire_mode == 1)
                                    {
                                        if (delay_pending && GetTickCount() >= shoot_delay_time)
                                        {
                                            controllers->SimulateInputKey(lmb_key, true);
                                            controllers->SimulateInputKey(lmb_key, false);


                                            if (globals::aimbot::vsr) {
                                                uintptr_t target_key = (uintptr_t)actor;
                                                if (resolver_instances.find(target_key) != resolver_instances.end()) {
                                                    resolver_instances[target_key]->RegisterShotHit();
                                                    ResolverVisualizer::RegisterHit();
                                                }
                                            }

                                            globals::stop_for_shot = false;
                                            delay_pending = false;
                                            spread_locked = false;
                                        }
                                    }
                                }
                            }
                            else {
                                if (globals::aimbot::autoshot && can_shoot)
                                {
                                    static DWORD last_shot_time = 0;

                                    if (globals::aimbot::auto_fire_mode == 0 && !aim_key_pressed) {
                                        return;
                                    }

                                    if (GetTickCount() - last_shot_time > (DWORD)globals::aimbot::autoshoot_delay)
                                    {
                                        controllers->SimulateInputKey(lmb_key, true);
                                        controllers->SimulateInputKey(lmb_key, false);


                                        if (globals::aimbot::vsr) {
                                            uintptr_t target_key = (uintptr_t)actor;
                                            if (resolver_instances.find(target_key) != resolver_instances.end()) {
                                                resolver_instances[target_key]->RegisterShotHit();
                                                ResolverVisualizer::RegisterHit();
                                            }
                                        }

                                        last_shot_time = GetTickCount();
                                    }
                                }
                            }

                            if (!globals::aimbot::spread_comp)
                            {
                                spread_locked = false;
                                delay_pending = false;
                                globals::stop_for_shot = false;
                                shoot_delay_time = 0;
                                spread_comp_ready_time = 0;
                            }

                            if (globals::aimbot::vsr) {
                                uintptr_t target_key = (uintptr_t)actor;
                                if (resolver_instances.find(target_key) != resolver_instances.end()) {
                                    UltimateResolverData* resolver_data = resolver_instances[target_key]->GetResolverData();


                                    static bool font_set = false;
                                    if (!font_set) {
                                        ResolverVisualizer::SetFont(font);
                                        font_set = true;
                                    }


                                    ResolverVisualizer::DrawModernResolverInfo(
                                        canvas,
                                        controllers,
                                        actor,
                                        resolver_data
                                    );
                                }
    }
    }
                            static bool is_firing = false;

    }
    }
    }
    }
        while (false);

        return draw_transition_o(viewportclient, canvas, a3);
    }

    void call_draw_transition_hook(uintptr_t* viewportclient, ucanvas* _canvas, std::uintptr_t a3) {
        SPOOF_FUNC
            return reinterpret_cast<void(*)(uintptr_t * viewportclient, ucanvas * _canvas, std::uintptr_t a3, uintptr_t, void*)>(spoofcall_stub)(viewportclient, _canvas, a3, offsets::magic, (void*)hk_draw_transition);
    }

    //void nti() {
    //    AllocConsole();
    //    freopen("CONOUT$", "w", stdout);
    //    SetConsoleTitleA("Debug Console");

    //    memory::module_base = memory::get_module(crypt(L"VALORANT-Win64-Shipping.exe"));
    //    if (!memory::module_base) {
    //        printf("[ERROR] Failed to get module base (VALORANT-Win64-Shipping.exe)\n");
    //        while (true);
    //        return;
    //    }

    //    printf("[OK] Module base resolved at 0x%p\n", memory::module_base);

    //    (initialize_spoofcall)((uint8_t*)memory::module_base);
    //    printf("[OK] Spoofcall successfully initialized\n");

    //    variables.init_variables();
    //    printf("[OK] Game variables initialized\n");

    //    uworld* UWorldClass = nullptr;
    //    uintptr_t* uworld_state_ptr = *(uintptr_t**)(memory::module_base + DecryptOffsetClear(offsets::State));
    //    if (uworld_state_ptr) {
    //        UWorldClass = *(uworld**)uworld_state_ptr;
    //        if (UWorldClass) {
    //            printf("[OK] GWorld resolved at 0x%p\n", UWorldClass);
    //        }
    //        else {
    //            printf("[-] GWorld pointer is null.\n");
    //        }
    //    }
    //    else {
    //        printf("[-] GWorld state pointer is null.\n");
    //    }

    //    try {
    //        if (!UWorldClass) throw std::runtime_error("UWorldClass is null after direct offset resolution.");

    //        ugameinstance* gameinstance = memory::read<ugameinstance*>(uintptr_t(UWorldClass) + offsets::game_instance);
    //        printf("[OK] game_instance = 0x%p\n", gameinstance);
    //        if (!gameinstance) throw std::runtime_error("game_instance is null.");

    //        ulocalplayer* localplayer = gameinstance->local_players()[0];
    //        printf("[OK] local_players[0] = 0x%p\n", localplayer);
    //        if (!localplayer) throw std::runtime_error("local_player is null.");

    //        ugameviewportclient* viewportclient = localplayer->viewport_client();
    //        printf("[OK] viewport_client = 0x%p\n", viewportclient);
    //        if (!viewportclient) throw std::runtime_error("viewport_client is null.");

    //        aplayercontroller* LocalController = memory::read<aplayercontroller*>((uintptr_t)localplayer + 0x38);
    //        printf("[OK] LocalController = 0x%p\n", LocalController);
    //        if (!LocalController) throw std::runtime_error("LocalController is null.");

    //        aplayercontroller* PlayerCameraManager = memory::read<aplayercontroller*>((uintptr_t)LocalController + offsets::cameramaneger);
    //        printf("[OK] PlayerCameraManager = 0x%p\n", PlayerCameraManager);
    //        if (!PlayerCameraManager) throw std::runtime_error("PlayerCameraManager is null.");

    //        uintptr_t Engine = memory::read<uintptr_t>((uintptr_t)gameinstance + 0x28);
    //        printf("[OK] Engine = 0x%p\n", Engine);
    //        if (!Engine) throw std::runtime_error("Engine is null.");

    //        LocalCameraLocation = memory::read<uintptr_t>((uintptr_t)PlayerCameraManager + offsets::camerapos);
    //        printf("[OK] LocalCameraLocation = 0x%p\n", LocalCameraLocation);

    //        LocalCameraFOV = memory::read<float>((uintptr_t)PlayerCameraManager + offsets::camerafov);
    //        printf("[OK] LocalCameraFOV = %.2f\n", LocalCameraFOV);

    //        LocalCameraRotation = memory::read<uintptr_t>((uintptr_t)PlayerCameraManager + offsets::camerarot);
    //        printf("[OK] LocalCameraRotation = 0x%p\n", LocalCameraRotation);

    //        keys::space = string::string_to_name(crypt(L"SpaceBar").decrypt());
    //        keys::left_mouse = string::string_to_name(crypt(L"LeftMouseButton").decrypt());

    //        static shadow_vmt1 viewport_hook;
    //        bool hook_success = viewport_hook.g47ghf234h79g8f237h89<decltype(hooks::draw_transition_o)>(
    //            memory::module_base,
    //            (uintptr_t)viewportclient,
    //            99, // or 0x78
    //            (void*)call_draw_transition_hook,
    //            &hooks::draw_transition_o
    //        );

    //        if (hook_success) {
    //            printf("[+] Viewport hook successfully applied!\n");
    //        }
    //        else {
    //            throw std::runtime_error("Failed to hook viewport transition function.");
    //        }
    //    }
    //    catch (const std::exception& e) {
    //        DWORD err = GetLastError();
    //        printf("\n=====================================================\n");
    //        printf("[-] Critical Exception Caught!\n");
    //        printf("[-] Reason     : %s\n", e.what());
    //        printf("[-] LastError  : 0x%X\n", err);
    //        printf("[-] Execution frozen for debugging. Attach debugger or kill process manually.\n");
    //        printf("=====================================================\n");
    //        while (true);
    //    }
    //    catch (...) {
    //        DWORD err = GetLastError();
    //        printf("\n=====================================================\n");
    //        printf("[-] Unknown Exception Caught!\n");
    //        printf("[-] Reason     : Unidentified exception type\n");
    //        printf("[-] LastError  : 0x%X\n", err);
    //        printf("[-] Execution frozen for debugging. Attach debugger or kill process manually.\n");
    //        printf("=====================================================\n");
    //        while (true);
    //    }
    //}

    void nti() { // you have updated haned chams etc?

        SPOOF_FUNC

            memory::module_base = memory::get_module(crypt(L"VALORANT-Win64-Shipping.exe"));
        if (!memory::module_base) {
            return;
        }

        (initialize_spoofcall)((uint8_t*)memory::module_base);

        variables.init_variables();

        uworld* UWorldClass = nullptr;
        uintptr_t* uworld_state_ptr = *(uintptr_t**)(memory::module_base + offsets::State);
        if (uworld_state_ptr) {
            UWorldClass = *(uworld**)uworld_state_ptr;
        }

        if (!UWorldClass) return;

        ugameinstance* gameinstance = memory::read<ugameinstance*>(uintptr_t(UWorldClass) + offsets::game_instance);
        if (!gameinstance) return;

        ulocalplayer* localplayer = gameinstance->local_players()[0];
        if (!localplayer) return;

        ugameviewportclient* viewportclient = localplayer->viewport_client();
        if (!viewportclient) return;

        aplayercontroller* LocalController = memory::read<aplayercontroller*>((uintptr_t)localplayer + offsets::local_controller);
        if (!LocalController) return;

        aplayercontroller* PlayerCameraManager = memory::read<aplayercontroller*>((uintptr_t)LocalController + offsets::cameramaneger);
        if (!PlayerCameraManager) return;

        uintptr_t Engine = memory::read<uintptr_t>((uintptr_t)gameinstance + offsets::engine);
        if (!Engine) return;

        static shadow_vmt1 viewport_hook;
        viewport_hook.g47ghf234h79g8f237h89<decltype(hooks::draw_transition_o)>(
            memory::module_base,
            (uintptr_t)viewportclient,
            99, // or 37 or 78 or 112
            (void*)call_draw_transition_hook,
            &hooks::draw_transition_o
        );
    }
}