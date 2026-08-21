// ============================================================
// offsets.hpp – GÜNCEL VE EKSİKSİZ
// ============================================================
#pragma once
#include <Windows.h>
#include <iostream>
#include <cstdio>
#include "xor.hpp"
#include "structs.hpp"
#include "math.hpp"
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <vector>

namespace offsets
{
    // === WORLD / ENGINE ===
    constexpr uint64_t GWorld = 0xCED2E90;
    constexpr uint64_t State = GWorld;
    constexpr uint64_t uworldstate = GWorld;
    constexpr uint64_t FNameState = 0xCF5F530;
    constexpr uint64_t ObjectArray = 0xCF4FC50;
    constexpr uint64_t GObjects = 0xCF4FC50;
    constexpr uint64_t FnamePool = 0xD09F540;
    constexpr uint64_t fname_pool = 0xE17570;

    // === PROCESS / EVENT / BONE / MEMORY ===
    constexpr uint64_t process_event = 0x1EBF9E0;
    constexpr uint64_t bone_matrix = 0x4399A10;
    constexpr uint64_t fmemory_malloc = 0x1AB00C0;
    constexpr uint64_t static_find_object = 0x1EEC7B0;
    constexpr uint64_t static_laod_object = 0x1EEFF10;

    // === OUTLINE / MAGIC / CHARMS ===
    constexpr uint64_t set_ares_outline_mode = 0x432F1E0;
    constexpr uint64_t magic = 0x52A3450;
    constexpr uint64_t charm_map = 0x440;
    constexpr uint64_t projectile_component = 0x464;

    // === RELATIVE / TIMER / VEHICLE ===
    constexpr uint64_t RelativeScale3D = 0x1A0;
    constexpr uint64_t TriggerVEH = 0x1AE68F6;
    constexpr uint64_t DefuseTimer = 0x05D0;
    constexpr uint64_t Timer = 0x05A8;
    constexpr uint64_t relative_rotation = 0x188;
    constexpr uint64_t RelativeRotation = 0x188;

    // === CAMERA / MESH / PLAYER ===
    constexpr uint64_t cameramaneger = 0x528;
    constexpr uint64_t PlayerCameraManager = 0x528;
    constexpr uint64_t mesh = 0x4F0;
    constexpr uint64_t Mesh = 0x4F0;
    constexpr uint64_t CameraPrivate = 0x17B0;
    constexpr uint64_t camerapos = 0x17C0;
    constexpr uint64_t camerafov = 0x17F0;
    constexpr uint64_t camerarot = 0x17D8;
    constexpr uint64_t CameraRotation = 0x59C;
    constexpr uint64_t CameraFOV = 0x580;

    // === GAME INSTANCE / LOCAL PLAYERS ===
    constexpr uint64_t game_instance = 0x1D8;
    constexpr uint64_t OwningGameInstance = 0x1D8;
    constexpr uint64_t local_players = 0x40;
    constexpr uint64_t LocalPlayers = 0x40;
    constexpr uint64_t viewport_client = 0x80;
    constexpr uint64_t engine = 0x28;
    constexpr uint64_t local_controller = 0x38;
    constexpr uint64_t PlayerController = 0x38;

    // === FINISHER / DEATH / MONTAGE ===
    constexpr uint64_t play_finisher_effect = 0x6A15330;
    constexpr uint64_t player_finisher_effect = play_finisher_effect; // EKLENDI
    constexpr uint64_t death_reaction_component_offset = 0xCA8;
    constexpr uint64_t death_reaction_component = 0xCA8;
    constexpr uint64_t montage_effect_override_offset = 0x100;
    constexpr uint64_t montage_effect_override = 0x100;
    constexpr uint64_t montage_effect_override_context_offset = 0x108;
    constexpr uint64_t montage_effect_override_context = 0x108;

    // === OBJECT / CLASS ===
    constexpr uint64_t mtkv = 99;
    constexpr uint64_t object_class = 0x10;
    constexpr uint64_t super_class = 0x48;

    // === SKINS / CHARMS / LEVELS ===
    constexpr uint64_t get_skin_levels = 0x88;
    constexpr uint64_t get_skin_data_asset = 0x120;
    constexpr uint64_t get_skin_chroma_data_asset = 0x120;
    constexpr uint64_t get_charm_data_asset = 0x68;
    constexpr uint64_t get_charm_level_data_asset = 0x70;
    constexpr uint64_t get_charm_level = 0xE0;
    constexpr uint64_t EquippableModels = 0xF0;
    constexpr uint64_t PossibleSkins = 0x168;
    constexpr uint64_t PossibleLevels = 0x150;
    constexpr uint64_t bIsOwned = 0x10A;
    constexpr uint64_t bIsUnlockedByConfig = 0x116;
    constexpr uint64_t bIsFavorite = 0xF3;
    constexpr uint64_t PossibleChromas = 0x140;
    constexpr uint64_t equippable_models = EquippableModels;
    constexpr uint64_t skins = PossibleSkins;
    constexpr uint64_t possible_levels = PossibleLevels;
    constexpr uint64_t possible_levels1 = bIsOwned;
    constexpr uint64_t possible_levels2 = bIsUnlockedByConfig;
    constexpr uint64_t possible_chromas = PossibleChromas;
    constexpr uint64_t skin_pointer = 0x3B8;
    constexpr uint64_t skin_pointer_2 = 0x0B0;
    constexpr uint64_t skin_pointer_3 = 0x080;
    constexpr uint64_t skin_data_asset = 0xFB0;

    // === SCREEN / FRESNEL / INVENTORY ===
    constexpr uint64_t get_screen_size1 = 0x48;
    constexpr uint64_t get_screen_size2 = 0x4C;
    constexpr uint64_t fr3scomp = 0xCD0;
    constexpr uint64_t was_invisible = 0xF72;
    constexpr uint64_t inventory_icon = 0xF30;
    constexpr uint64_t font = 0x98;
    constexpr uint64_t skymeshcomponent = 0x290;
    constexpr uint64_t skyboxmeshcomponent = skymeshcomponent;

    // === MESH (1P / 3P / OVERLAY) ===
    constexpr uint64_t mesh1p = 0xF50;
    constexpr uint64_t mesh3p = 0xF90;
    constexpr uint64_t mesh1p_overlay = 0xF58;
    constexpr uint64_t mesh_cosmetic_3p = 0xF60;
    constexpr uint64_t coolchams = 0x418;
    constexpr uint64_t mesh1pgun = 0xDE0;
    constexpr uint64_t mesh3pgun = 0xDF0;
    constexpr uint64_t mesh_fp_flag = 0x394;

    // === FRESNEL / BLIND / FLASH ===
    constexpr uint64_t fresnelcomponent = 0xA98;
    constexpr uint64_t BlindManagerComponent = 0xA28;
    constexpr uint64_t flashend = 0x10;

    // === WIREFRAME / VIEWPORT ===
    constexpr uint64_t WireFrame = 0x92E;
    constexpr uint64_t bForceWireframe = WireFrame;
    constexpr uint64_t WireFrame2 = 0xC0;
    constexpr uint64_t WireFrame3 = 0xFF;
    constexpr uint64_t viewport_world = 0x80;
    constexpr uint64_t SetCameraPOVHook = 0xF2;
    constexpr uint64_t viewport_gameinstance = 0x88;

    // === SPREAD / FIRING ===
    constexpr uint64_t get_spread_values = 0x6AB3800;
    constexpr uint64_t get_spread_angles = 0x76EB960;
    constexpr uint64_t to_vector_and_normalize = 0x1BA8A70;
    constexpr uint64_t to_angle_and_normalize = 0x1BA3560;
    constexpr uint64_t FiringStateComp = 0x1228;
    constexpr uint64_t get_firing_location_direction = 0x7242C20;
    constexpr uint64_t get_firing_location_and_direction = 0x7242C20;
    constexpr uint64_t GetFiringLocationAndDirection = 0x7242C20;
    constexpr uint64_t seed_data = 0x4A0;
    constexpr uint64_t seed_dataadd = 0xD8;
    constexpr uint64_t stability_component = 0x490;
    constexpr uint64_t error_power = 0x49C;
    constexpr uint64_t error_retries = 0x470;

    // === INVENTORY / EQUIPPABLE / ACCOUNT ===
    constexpr uint64_t Inventory = 0xC08;
    constexpr uint64_t Equippable = 0x278;
    constexpr uint64_t AccountLevel = 0x77C;
    constexpr uint64_t HideAccountLevel = 0x778;
    constexpr uint64_t player_state = 0x488;
    constexpr uint64_t PlayerState = 0x488;
    constexpr uint64_t player_name_private = 0x500;
    constexpr uint64_t get_player_id = 0x460;
    constexpr uint64_t get_ping = 0x464;

    // === BONE ===
    constexpr uint64_t bone_cout = 0x768;                 // EKLENDI
    constexpr uint64_t BoneArray = 0x760;
    constexpr uint64_t BoneCount = 0x768;

    // === PLATFORM / ROOT / RADAR ===
    constexpr uint64_t PlatformPlayer = 0x6A0;
    constexpr uint64_t RiotTag = 0xA0;
    constexpr uint64_t RiotName = 0xB8;
    constexpr uint64_t CompetitiveTier = 0x734;
    constexpr uint64_t LeaderboardPosition = 0x6C4;
    constexpr uint64_t Rootcomponent = 0x290;
    constexpr uint64_t RootComponent = 0x290;
    constexpr uint64_t root_position = 0x170;
    constexpr uint64_t RelativeLocation = 0x170;
    constexpr uint64_t CameraRadar = 0x20A0;

    // === PAK / SIGNING ===
    constexpr uint64_t get_fpak_platform_file = 0xCF04AA8;
    constexpr uint64_t bypass_pak_signing = 0xD2AA288;
    constexpr uint64_t mount_custom_pak = 0x2BD2B00;
    constexpr uint64_t mount = 0x2BD2B00;

    // === OTHERS ===
    constexpr uint64_t pregame_view_controller = 0xD40;
    constexpr uint64_t MakeRenderStateDirty = 0x17A9320;
    constexpr uint64_t dormant_server = 0x101;
    constexpr uint64_t fpak_platform_file = 0xCD33A28;
    constexpr uint64_t GetFiringLocationAndDirection_old = 0x7105BC0;
}

// ============================================================
// GLOBALS – AYARLAR (Aynen korundu)
// ============================================================
namespace globals
{
    namespace visuals {
        // Basic Settings
        inline bool crystal_chams_enabled = false;
        inline int crystal_chams_preset = 0;
        inline float Brightness = 1.0f;
        inline float FresnelIntensity = 1.0f;
        inline float Saturation = 1.0f;
        inline float LightingBrightness = 5.0f;
        inline float ShadowIntensity = 0.0f;
        inline float Specular = 0.4f;
        inline float EmissiveAmount = 0.2f;
        inline float SkinIntensity = 0.5f;
        inline float OcclusionDepth = 0.0f;
        // Color Settings
        inline float SkinUnderColor_R = 1.0f;
        inline float SkinUnderColor_G = 0.76848f;
        inline float SkinUnderColor_B = 0.0f;
        inline float outlineintensityvisibleoutline = 200.0f;
        inline float outlineintensityinvisbleoutline = 200.0f;
        // Deep Layer Animation
        inline  float DeepSpeedX = 0.06f;
        inline  float DeepSpeedY = 0.06f;
        inline float AlphaDissolveOpacity = 0.207412f;
        // Shallow Layer Animation  
        inline float ShallowSpeedX = 0.055f;
        inline float ShallowSpeedY = 0.055f;
        inline float BoundingBox = -50.0f;
        // Inner Layer
        inline float InnerSpeedX = 0.12f;
        inline float InnerSpeedY = 0.06f;
        inline float InnerTile = 1.5f;
        inline float InnerAmount = 2.0f;
        inline float InnerPower = 1.5f;
        inline float InnerContrast = 1.9f;
        inline float DepthBias = -0.1f;
        // Outer Layer
        inline float OuterSpeedX = 0.015f;
        inline float OuterSpeedY = 0.03f;
        inline float OuterTile = 6.0f;
        inline float OuterAmount = 0.25f;
        inline  float OuterPower = 1.5f;
        inline float OuterContrast = 1.0f;

        inline float Alpha_Layer1_OffsetU = 0.424779f;
        inline float Alpha_Layer1_OffsetV = 0.362832f;
        inline float Alpha_Layer1_ScaleU = 0.111504f;
        inline float Alpha_Layer1_ScaleV = 0.2f;
        inline  float RefractionDepthBias = 0.0f;
        inline float TextureAlpha = 0.941758f;
        inline float EdgeThickness = 21.277576f;
        inline float TextureMultiply = 20.0f;
        inline float TextureOffsetU = 0.794286f;
        inline float TextureOffsetV = 0.068571f;
        inline float TextureTileU = 0.651585f;
        inline float TextureTileV = 0.405714f;
        inline float TexturePower = 1.0f;
        inline float TextureContrast = 0.0f;
        inline  float OpacityMultiplier = 1.0f;
        inline  float AlphaBoost = 1.0f;

        // Color Parameters
        inline float ColorA_R = 0.0f;
        inline float ColorA_G = 2.895575f;
        inline  float ColorA_B = 5.0f;
        inline float ColorA_A = 1.0f;
        inline float AlphaBasePower = 0.1f;
        inline float AlphaColorMult = 0.0f;
        inline float EdgeColor_R = 10.0f;
        inline float EdgeColor_G = 7.549591f;
        inline float EdgeColor_B = 0.0f;
        inline float EdgeColor_A = 0.0f;
        inline float AlphaScaleU = 0.2f;
        inline float AlphaScaleV = 2.0f;
        inline float ErosionEdgeSoftness = 0.5f;

        inline float MoscaRed = 255.0f;
        inline float MoscaGreen = 0.0f;
        inline float MoscaBlue = 0.0f;
        inline float HandChamsGlow = 1.0f;
        inline float HandFadeStrength = 1.0f;
    
        inline bool b0x = false;
        inline bool minimap = false;
        inline bool outline_enabled = 0;
        inline bool self_galaxy_enabled = false;
        inline int b0x_type = 1;
        inline bool use_preset_outlines = false;
        inline int visiblepreset = 0;
        inline int invisiblepreset = 0;
        inline int self_galaxy_preset = 0;
        inline bool weaponstate = false;
        inline bool box2dfl = false;
        inline bool box3d = false;
        inline bool box2d = false;
        inline bool box2ds = false;
        inline bool outlineinvisible = true;
        inline bool chinese_hat = false;
        inline bool chinese_hat_self = false;
        inline bool box3dd = false;
        inline bool crnr = false;
        inline bool HealthText = false;
        inline bool agenticon = false;
        inline bool bullet_tracers = false;
        inline bool agent_name = false;
        inline bool bullet_tracer_fire = false;
        inline DWORD bullet_tracer_end_time = 0;


        inline bool custom_crosshair = false;
        inline bool cornerbox = false;
        inline bool headb0x = false;
        inline bool sk3let0n = false;
        inline bool snapl1ne = false;
        inline bool h3althbar = false;
        inline bool weaponesp = false;
        inline bool d4m4 = false;
        inline bool b00ms = false;
        inline bool b44ms = false;
        inline bool b11ms = false;
        inline bool b22ms = false;
        inline bool dstc = false;
        inline bool angle = false;
        inline bool lnd = false;

        inline bool mawmawmawmaw = false;
        inline bool mawmawmaw = false;
        inline bool mawmaw = false;
        inline bool mumuf = false;
        inline bool dormant = true;
        inline bool visiblecheck = false;
        inline bool offscreen_esp = false;
        inline float offscreen_radius = 200.0f;
        inline float offscreen_size = 20.0f;
        inline bool abilitiesspike = false;
        inline bool abilities = false;
        inline bool chams2 = false;
        inline bool chams = false;
        inline bool chamsfsd = false;
        inline bool last_enemy_state = false;
        inline bool outline = false;
        inline int outlinetype = 0;
        inline int health_bar_type = 0;
        
        // Görünür durum renkleri

        inline bool dynamic_fresnel_outline = false;
        inline int dynamic_fresnel_preset = 0;

        inline bool self_galaxy_outline_enabled = false;
        inline int self_galaxy_outline_preset = 0;

        // RENK DEĞERLERİ
        inline float self_galaxy_outline_CenterEdgeR = 0.53f;
        inline float self_galaxy_outline_CenterEdgeG = 0.27f;
        inline float self_galaxy_outline_CenterEdgeB = 0.47f;

        inline float self_galaxy_outline_InnerEdgeR = 0.0f;
        inline float self_galaxy_outline_InnerEdgeG = 0.27f;
        inline float self_galaxy_outline_InnerEdgeB = 1.0f;

        inline float self_galaxy_outline_OuterEdgeR = 0.04f;
        inline float self_galaxy_outline_OuterEdgeG = 0.23f;
        inline float self_galaxy_outline_OuterEdgeB = 0.21f;

        // DİĞER PARAMETRELER
        inline float self_galaxy_outline_GlowVisible = 1.0f;
        inline float self_galaxy_outline_intensity = 1.0f;

        inline float InnerEdgeThickness = 0.1f;
        inline float OuterEdgeThickness = 0.37f;
        inline float RimPower = 1.0f;
        inline float RimMultiply = 1.0f;
        inline float RimFresnel = 1.0f;
        inline float OcclusionState = 1.0f;
        inline float OcclusionBehindWall = 1.0f;

        inline float CenterEdgeR_Visible = 1.0f;
        inline float CenterEdgeG_Visible = 0.0f;
        inline float CenterEdgeB_Visible = 0.0f;

        inline float InnerEdgeR_Visible = 1.0f;
        inline float InnerEdgeG_Visible = 0.0f;
        inline float InnerEdgeB_Visible = 0.0f;

        inline float OuterEdgeR_Visible = 1.0f;
        inline float OuterEdgeG_Visible = 0.0f;
        inline float OuterEdgeB_Visible = 0.0f;

        inline float intensityvisibleoutline = 18.20f;
        inline float GlowVisible = 200.0f;
        inline int visible_color_preset = 0;
        inline int invisible_color_preset = 1;

        // Görünmez durum renkleri
        inline float CenterEdgeR_Invisible = 0.0f;
        inline float CenterEdgeG_Invisible = 1.0f;
        inline float CenterEdgeB_Invisible = 0.0f;

        inline float InnerEdgeR_Invisible = 0.0f;
        inline float InnerEdgeG_Invisible = 1.0f;
        inline float InnerEdgeB_Invisible = 0.0f;

        inline float OuterEdgeR_Invisible = 0.0f;
        inline float OuterEdgeG_Invisible = 1.0f;

        inline float OuterEdgeB_Invisible = 0.0f;

        inline float intensityinvisbleoutline = 1.0f;
        inline float GlowInvisible = 5.0f;
        
        inline float Self_CenterEdgeR = 0.53f;
        inline float Self_CenterEdgeG = 0.27f;
        inline float Self_CenterEdgeB = 0.47f;

        inline float Self_InnerEdgeR = 0.0f;
        inline float Self_InnerEdgeG = 0.27f;
        inline float Self_InnerEdgeB = 1.0f;

        inline float Self_OuterEdgeR = 0.04f;
        inline float Self_OuterEdgeG = 0.23f;
        inline float Self_OuterEdgeB = 0.21f;
        inline float tracer_intensity = 0.21f;
        inline bool wireframe_hands = false;
        inline bool wireframe_weapon = false;
        inline float wireframe_opacity = 1.0f;
        inline bool handchams = false;
        inline float chams_intensity = 5.00f;

        inline bool glow_esp = false;
        inline float glow_intensity = 0.1f;
        inline bool rainbow_chams = false;
        inline bool galaxy_chams = false;
        inline float rainbowTimeZRGB = 0.0f;
        inline flinearcolor chams_color = { 4.41f, 0.28f, 0.14f, 9.13f };
        inline bool self_chams = false;
        inline bool self_wireframe = false;
        inline bool galaxy_gun = false;
        inline float self_wireframe_opacity = 1.0f;
        inline bool usepresetedoutlines = false;
        inline bool self_chamsvsb = false;
        inline bool self_chamsal = false;
        inline bool self_chamsbg = false;
        inline bool self_visible_check_ch = false;
        inline float self_glow_intensity = 1.0f;
        inline float self_chams_intensity = 1.0f;
        inline float self_brps = 1.0f;
        inline flinearcolor self_chams_color = { 0.17f, 3.15f, 0.14f, 10.0f };
        inline bool galaxy_enemy_chams = false;
        inline bool galaxy_enemy_mesh3p = false;


        inline bool galaxy_enemy_cosmetic = false;
        inline bool galaxy_enemy_third = false;
        inline bool chamsvsb = false;
        inline bool chamsvsbd = false;
        inline bool chamsvsbff = false;
        inline bool chamssd = false;
        inline bool visible_check_ch = false;
        inline bool chamsal = false;
        inline bool chams_visible_invisible = false;

        inline bool chamsbg = false;

        inline bool hch = false;


        inline bool fr3s = false;
        inline bool fr3sl = false;
        inline bool fr3sla = false;
        inline bool fr4s = false;
        inline bool fr5s = false;
        inline bool fr6s = false;
        inline bool fr7s = false;
        inline bool fr8s = false;
        inline bool fr3vs = false;
        inline bool cp3 = false;
        inline bool cp3g = false;
        inline bool mov8 = false;
        inline bool scp8 = false;
        inline bool scp19 = false;
        inline bool scp20r = false;
        inline bool scp20 = false;
        inline bool scp20s = false;
        inline bool scp20sr = false;
        inline bool scp9 = false;
        inline bool scp6 = false;
        inline bool scp5 = false;
        inline bool scp4 = false;
        inline bool scp3 = false;
        inline bool scp2 = false;
        inline bool scp1 = false;
        inline bool scp0 = false;
        inline bool adt = false;
        inline bool ctivt = false;
        inline bool lct = false;
        inline bool sh8 = false;
        inline bool mn = false;
        inline bool dpw = false;
        inline bool pst = false;
        inline bool vln = false;
        inline bool psm = false;
        inline bool tlr = false;
        inline bool tlrsv = false;
        inline bool vlnsv = false;
        inline bool psmsv = false;
        inline float esf = 1.5f;
        inline bool esfb = false;
        inline bool esfbc = false;
        inline bool gdmt = false;
        inline bool chtlr = false;
        inline bool drt = false;
        inline bool vrt = false;
        inline bool hdm = false;
        inline bool hdm1 = false;
        inline bool hdm2 = false;
        inline bool hdm3 = false;
        inline bool hdm4 = false;
        inline bool hdm5 = false;
        inline bool hdm6 = false;
        inline bool hdm7 = false;
        inline bool hdm8 = false;
        inline bool hdsm = false;
        inline bool stp = false;
        inline bool sdn = false;
        inline bool nma = false;
        inline bool maw2 = false;
        inline bool maw3 = false;
        inline bool maw4 = false;
        inline bool maw5 = false;
        inline bool maw6 = false;
        inline bool maw7 = false;
        inline bool maw8 = false;
        inline bool xtx = false;
        inline bool skch = false;
        inline bool skl = false;
        inline bool mh = false;
        inline bool mh1 = false;
        inline bool cp4 = false;
        inline bool wfrs = false;
        inline bool wfrs1 = false;
        inline bool dvm = false;
        inline bool vlk = false;
        inline bool spk = false;
        inline bool gltc = false;
        inline bool spe = false;
        inline bool spc = false;
        inline bool sps = false;
        inline bool ff = false;
        inline bool ffe = false;
        inline bool ffe1 = false;
        inline bool ffe2 = false;
        inline bool ffe3 = false;
        inline bool ffe4 = false;
        inline bool ffe5 = false;
        inline bool ffe6 = false;
        inline bool ffe7 = false;
        inline bool ffe8 = false;
        inline bool ffe9 = false;
        inline bool ffe10 = false;
        inline bool hld = false;
        inline bool scp65 = false;
        inline bool scp21 = false;
        inline bool lmk = false;
        inline bool amk = false;
        inline bool pmk = false;
        inline bool mts = false;
        inline bool lbt = false;
        inline bool tblt = false;
        inline bool amk33 = false;
        inline bool vsbg = false;
        inline bool vsbg1 = false;
        inline bool vsbg2 = false;
        inline bool vsbg3 = false;
        inline bool vsbg4 = false;
        inline bool vsbg5 = false;
        inline bool vsbg6 = false;
        inline bool vsbg7 = false;
        inline bool vsbg8 = false;
        inline bool drmdr = false;
        inline bool cnm = false;
        inline bool resolver3 = false;
        inline bool sldb = false;
        inline bool spi = false;
        inline bool spi1 = false;
        inline bool spvi = false;
        inline bool drd = false;
        inline bool drd3 = false;
        inline bool plnm = false;
        inline bool ttl = false;
        inline bool acclvl = false;
        inline bool kr = false;
        inline bool hdacc = false;
        inline bool ovs = false;
        inline bool nmpl = false;
        inline bool nmpllft = false;
        inline bool pclp = false;
        inline bool pclp1 = false;
        inline bool pclp2 = false;
        inline bool nmpl1 = false;
        inline bool nmpl2 = false;
        inline bool nmpl34 = false;
        inline bool handChamsRGB = false;
        inline bool hitsound = false;
        inline bool hitmarker = false;
        inline bool selfchth = false;
        inline bool chth = false;

        inline float brps = 0.01f;
        inline float time = 0.5f;


        inline int psmd = 0;
        inline int tlrm = 0;
        inline int hmdmd = 0;
        inline int hmdmd1 = 0;
        inline int hmdmdd = 0;
        inline int gnmd = 0;
        inline int gnmdd = 0;
        inline int cnmd = 0;
        inline int amkd = 0;
        inline int amkdd = 0;
        inline int pmkd = 0;
        inline int pmkdd = 0;
        inline int amkd33 = 0;
        inline int amkdd33 = 0;
        inline int hst = 0;


        inline float step_esp_radius = 30.0f;
        inline float step_esp_duration = 1.0f;
        inline int step_esp_circle_segments = 32;

        inline float run_speed_threshold = 5.0f;
        inline float step_interval = 0.15f;

        inline float isnt = 10.0f;

    }


    namespace aimbot {
        inline bool a1mbot = false;
        inline bool is_knife = false;
        inline bool s1lt0 = false;
        inline bool triggermaw = false;
        inline bool uto8 = false;
        inline bool autoshot = false;
        inline bool enable_360_fov = false;
        inline int uto8_mode = 1;
        inline int silent_mode = 1;
        inline bool uto9 = false;
        inline bool pvc = false;
        inline bool vsr = false;
        inline int auto_fire_mode = 0; 
        inline bool mbg = false;
        inline bool tgb = false;
        inline bool wall_penetrate = false;
        inline float auto_wall_min_damage = 50.0f;
        inline bool tgb1 = false;
        inline bool inter = false;
        inline float min_damage = 0;
        inline float min_hitchance = 0;
        inline bool aim_assist = false;
        inline bool v1sh_ch3ck = 1;
        inline bool a1_v1sh_ch3ck = 1;
        inline bool recoilcrosshair = 0;
        inline bool reco1l_contr0l = 0;
        inline bool spread_comp = 0;
        inline bool spreadempty_comp = 0;
        inline bool spread_comp1 = 0;
        inline bool nospread = false;
        inline bool auto_scope = false;
        inline bool n3s = 0;
        inline bool draw_f0v = 0;
        inline bool draw_f0vrainbow = 0;
        inline bool fov360 = false;
        inline bool detect_3d_world = true;
        inline float max_aim_distance = 100000.0f;
        inline float autoshoot = 50.0f;
        inline float a1m_sm00th = 1.0f;
        inline bool smart_wall_bang = false;
        inline float fovtrigger = 5.0f;
        inline float a1m_f0v = 100.0f;
        inline int a1m_b0ne = 0;
        inline int a1m_k3y = 0;
        inline int trigger_k3y = 0x78;
        inline int canvaMAW = 0x70;
        inline int silent_key = 0;
        inline int silent_key1 = 0;
        inline bool nss = false;
        inline float spread_comp_delay =100.0f;
        inline float autoshoot_delay = 20.0f;
        inline float spread_comp_strength = 1.0f;
        inline int fire_mode = 0; 

        inline  bool auto_wall = true;
        inline bool auto_wall_visualize = true;
        inline bool auto_wall_autoshoot = true;
        inline int auto_wall_mode = 0;

        inline bool silent1 = false;
        inline int target_selection = 0; 


        inline float n3sv = 2.0f;

        inline bool silent = false;
        inline bool duh1 = false;
        inline bool duh2 = false;
        inline bool duh3 = false;
        inline bool duh4 = false;
        inline bool duh5 = false;

        inline int UTO8_TOGGLE_KEY = 0;

    }

    namespace misc {
        inline bool aspect_ratio_enabled = false;
        inline float aspect_ratio_value = 1.30f;
        inline bool disconnect_server = false;
        inline bool nld= false;

        inline bool freecam_enabled = false;
        inline float freecam_speed = 1800.0f;
        inline fvector freecam_pos = { 0.0, 0.0, 0.0 };
        inline fvector freecam_rot = { 0.0, 0.0, 0.0 };
        inline bool freecam_initialized = false;
        inline int freecam_key = 0;

        inline bool kill_say = false;
        inline bool snap_back_key = false;
        inline bool snap_right_key = false;
        inline bool snap_left_key = false;
        inline bool chaotic_skybox = false;
        inline float ChaoticSpeed = 1.0f;
        inline float ColorShiftRate = 0.1f;

        inline fstring kill_say_msg = L"discord.gg/spv";
        inline bool wm11 = true;
        inline bool nospreadcalismayan = false;
        inline bool sk1ptut0rial = false;
        inline bool mesh_swap_index = false;
        inline bool HandChamsMaterial = false;
        inline bool mosca_wireframe = false;
        inline bool ViewModelChanger = false;
        inline bool custom_obj_enabled = false;
        inline bool bunnyhop = false;
        inline bool MeshCrouchModifed = false;
        inline bool sk1ptut0rial1 = false;
        inline bool sk1n_chang3r = false;
        inline bool is_aimbot_active = false;
        inline bool is_firing = false;
        inline bool fakeduck = false;
        inline bool jitter_move = false;
        inline float yaw_add = 0;
        inline float pitch = 0;
        inline float watermark_pos_x = 0.0f;
        inline float watermark_pos_y = 49.0f;
        inline float watermark_scale = 1.0f;
        inline float at_target = false;
        inline bool freestanding = false;
        inline bool manual_aa = false;
        inline bool jitter_enabled = false;
        inline bool jitter_on_back = false;
        inline bool pitch_enabled = false;
        inline float pitch_value = 0;
        inline bool atomic_aa = false;
        inline float real_rotation_x = 0;
        inline float real_rotation_y = 0;
        inline float real_rotation_z = 0;
        inline float atomic_speed = 1.0f;
        inline int atomic_mode = 0;
        inline bool ThirdPerson = false;
        inline bool WireFrameHand = false;
        inline bool customgun = false;
        inline bool rdy = false;
        inline bool fastcrouch = false;
        inline bool expl0 = false;
        inline bool aa = false;
        inline int aa_mode = 0;
        inline bool aa_spin = false;
        inline bool aa_jitter = false;
        inline bool aa_threeway = false;
        inline bool aa_backwards = false;
        inline bool aa_desync = false;

        inline int aa_left_key = 0x4A;
        inline int aa_back_key = 0x4B;
        inline int aa_right_key = 0x4C;

        inline int chams_color_index = 0;


        inline bool custom_head = false;
        inline float custom_head_pitch = 0.f;
        inline float custom_head_yaw = 0.f;
        inline bool viewmodel_offset_enabled = false;

        inline double ashen_flow_map_speed = 0.1 * 100;
        inline double ashen_panner_y = 0.05 * 100;

        inline float jitter_range = 0.f;
        inline float desync_range = 0.f;
        inline float fake_lag_ticks = 0;
        inline bool world_esp = false;
        inline bool gdg = false;
        inline bool cpp = false;
        inline bool gadgets = false;
        inline bool spktimer = false;
        inline static int chams_material_index = 0;
        inline int handchams_material_index1 = 0;
        inline int handchams_material_index2 = 0;
        inline int enemy_chams_material_index = 0;
        inline bool playerchamsself = false;

        inline bool BuddyChanger = false;
        inline bool ant1 = false;
        inline bool w4t4 = true;
        inline bool bjop = false;
        inline int bjopky = 0;

        inline bool finisher = false;
        inline bool onlylastkill = false;
        inline int bdky = 0;
        inline int instl = 0;
        inline bool sk1 = false;
        inline bool got = false;
        inline bool tch = false;
        inline bool nst = false;
        inline bool bda = false;
        inline bool flai = false;
        inline bool glvut = false;
        inline bool hl = false;
        inline bool gm = false;
        inline bool mv = false;
        inline bool sk = false;
        inline bool at = false;
        inline bool shd = false;
        inline bool lcl = false;
        inline bool klm = false;
        inline bool hide_3p = false;
        inline bool hide_3p_toggle = false;
        inline bool auto6 = false;
        inline bool auto5 = false;
        inline bool auto4 = false;
        inline bool ath = false;
        inline bool htb = false;
        inline bool grph = false;
        inline bool tkdmg = false;
        inline bool swp = false;
        inline bool swpn = false;
        inline bool f8g = false;
        inline bool kysrt = false;
        inline bool lfp = false;
        inline bool hdo = false;
        inline bool dai = false;
        inline bool hlcl = false;
        inline bool rpl = false;
        inline bool ht23 = false;
        inline bool ta = false;
        inline bool fds = false;
        inline bool tds = false;
        inline bool zds = false;
        inline bool kds = false;
        inline bool ids = false;
        inline bool xpl0it = false;
        inline bool gl0 = false;
        inline bool drt = false;
        inline bool zrt = false;
        inline bool lmk = false;
        inline bool klr = false;
        inline bool trx = false;
        inline bool ual = false;
        inline bool pgm = false;
        inline bool pgmu = false;
        inline bool pgm1 = false;
        inline bool pgm2 = false;
        inline bool pgm3 = false;
        inline bool sw = false;
        inline bool cgv = false;
        inline bool cm3 = false;
        inline bool cm33 = false;
        inline bool cm55 = false;
        inline bool pmg = false;
        inline bool amj = false;
        inline bool stf = false;
        inline bool ads = false;
        inline bool adp = false;
        inline bool adv = false;
        inline bool mh = false;
        inline bool tsp = false;
        inline bool psd = false;
        inline bool dlt = false;
        inline bool khp = false;
        inline bool hm3 = false;
        inline bool modelmesh = false;
        inline bool etr3 = false;
        inline bool etr6 = false;
        inline bool hgd = false;
        inline bool bdcchg = false;
        inline bool bdcch = false;
        inline bool cm4 = false;
        inline bool fl9 = false;
        inline bool fl10 = false;
        inline bool fl11 = false;
        inline bool fl12 = false;
        inline bool fl13 = false;
        inline bool fl14 = false;
        inline bool fl15 = false;
        inline bool fl16 = false;
        inline bool fl17 = false;
        inline bool fl18 = false;
        inline bool fl19 = false;
        inline bool fl20 = false;
        inline bool fl21 = false;
        inline bool fl22 = false;
        inline bool fl23 = false;
        inline bool fl24 = false;
        inline bool fl25 = false;
        inline bool fl26 = false;
        inline bool fl27 = false;
        inline bool fl28 = false;
        inline bool fl29 = false;
        inline bool fl30 = false;
        inline bool fl31 = false;
        inline bool fl32 = false;
        inline bool fl33 = false;
        inline bool fl34 = false;
        inline bool fl35 = false;
        inline bool fl36 = false;
        inline bool fl37 = false;
        inline bool fl38 = false;
        inline bool fl39 = false;
        inline bool fl40 = false;
        inline bool fl41 = false;
        inline bool fl42 = false;
        inline bool fl88 = false;
        inline bool fl89 = false;
        inline bool fl90 = false;
        inline bool fl91 = false;
        inline bool fl92 = false;
        inline bool fl93 = false;
        inline bool fl94 = false;
        inline bool fl95 = false;
        inline bool uld = false;
        inline bool skt = false;
        inline bool clrs = false;
        inline bool clrstr = false;
        inline bool dhd = false;
        inline bool aba = false;
        inline bool frc = false;
        inline bool cjr = false;
        inline bool wjr = false;
        inline bool skon = false;
        inline bool unlock_fov = false;
        inline bool spb = false;
        inline bool spm = false;
        inline bool tld = false;
        inline bool fr44c4m = false;
        inline bool fr44c4m2 = false;
        inline bool fr44c4m3 = false;
        inline bool fr44c4m4 = false;
        inline bool trs = false;
        inline bool fvo = false;
        inline bool tro = false;
        inline bool tro1 = false;
        inline bool tro2 = false;
        inline bool tro3 = false;
        inline bool tro4 = false;
        inline bool tro5 = false;
        inline bool tro6 = false;
        inline bool tro7 = false;
        inline bool tro8 = false;
        inline bool tro9 = false;
        inline bool tro10 = false;
        inline bool tro11 = false;
        inline bool tro12 = false;
        inline bool md = false;
        inline bool skybox_changer = false;
        inline bool skybox_changer1 = false;
        inline flinearcolor sky_overall = { 1.0f, 0.0f, 0.0f, 1.0f };   
        inline flinearcolor sky_zenith = { 0.0f, 1.0f, 0.0f, 1.0f };     
        inline flinearcolor sky_horizon = { 0.0f, 0.0f, 1.0f, 1.0f };    
        inline bool sky_color = false;
        inline bool skybox_changer2 = false;
        inline bool skybox_changer0 = false;
        inline bool skybox_changer3 = false;
        inline bool skybox_changer4 = false;
        inline bool skybox_changer5 = false;
        inline bool skybox_changer6 = false;
        inline bool skybox_changer7 = false;
        inline bool skybox_changer8 = false;
        inline bool skybox_changer9 = false;
        inline bool skybox_changer10 = false;
        inline bool skybox_changer11 = false;
        inline bool skybox_changer12 = false;
        inline bool skybox_changer13 = false;
        inline bool skybox_changer14 = false;
        inline bool skybox_changer15 = false;
        inline bool skybox_changer16 = false;
        inline bool skybox_changer17 = false;

        inline bool wdrms = false;
        inline bool spinner1 = false;
        inline bool spinnerjt = false;
        inline bool spinnerds = false;
        inline bool spinnerat = false;
        inline bool bdychgr = false;
        inline bool ctsf = false;
        inline bool cstfmdf = false;
        inline bool rmsdw = false;



        inline float arm_width = 3.0f;
        inline float arm_height = 1.8f;
        inline float arm_length = 1.0f;
        inline float weapon_width = 1.0f;
        inline float weapon_height = 1.1f;
        inline float weapon_length = 1.0f;
        inline float weapon_z = 0.0f;

        inline float weapon_x_inspect = 0.0f;
        inline float weapon_y_inspect = 0.0f;
        inline float weapon_z_inspect = 7.7f;

        inline float rifle_x_inspect = 0.0f;
        inline float rifle_y_inspect = -1.0f;

        inline float arm_width_inspect = 2.5f;
        inline float arm_height_inspect = 1.0f;
        inline float arm_length_inspect = 1.0f;
        inline float weapon_width_inspect = 0.3f;
        inline float weapon_height_inspect = 0.9f;
        inline float weapon_length_inspect = 1.0f;

        inline float knife_width = 0.483117f;
        inline float knife_height = 1.0f;
        inline float knife_length = 1.0f;
        inline float knife_x = 0.0f;
        inline float knife_y = 0.0f;
        inline float knife_z = 0.0f;

        inline float rotation_x = 0.0f;
        inline float rotation_y = 0.0f;
        inline float rotation_z = 0.0f;

        inline bool rmsdwwp = false;
        inline bool nvis = false;
        inline bool handchams = false;
        inline bool handchams2 = false;
        inline bool handchamsd2 = false;
        inline bool hand_outline = false;
        inline bool gunchams = false;
        inline bool cstmsk = false;
        inline bool p3chams = false;
        inline bool handchamsrgb = false;
        inline bool handglow = false;


        inline flinearcolor handchams_color = flinearcolor(0.f, 0.5f, 1.f, 1.f);
        inline bool galaxy_hand_chams = false;
        inline bool galaxy_chams = false;
        inline bool ashen_crystal_v2 = false;
        inline bool ashen_crystal_v3 = false;
        inline float ashen_intensity = 5.0f;
        inline bool handchams_rainbow = true;

        inline float handchams_intensity = 5.0f;


        inline float cosmos_inner_brightness = 3.38f;
        inline float cosmos_inner_boost = 55.0f;
        inline float cosmos_core_power = 6.8f;
        inline float cosmos_sphere_opacity = 6.0f;

        inline bool playerchams = false;

        inline bool playerchamsrgb = false;
        inline bool lagcmp = false;
        inline bool rdt = false;
        inline bool fake_lag_enabled = false;
        inline bool health_hack = false;
        inline bool fl96 = false;
        inline bool quantum_desync = false;
        inline bool neural_parry = false;
        inline bool time_dilation = false;
        inline bool camera_shake_enabled = false;
        inline bool agt = false;
        inline bool world_view = false;
        inline bool custom_hand = false;
        inline bool dropped_gun = false;
        inline bool dropped_spike = false;
        inline bool antiflash = false;
        inline bool skybox = false;
        inline bool skyboxrgb = false;
        inline bool lastkill = false;
        inline bool chat_spammer = false;
        inline bool killsays = false;
        inline bool show_kill_counter = false;
        inline int kill_counter = 0;
        inline bool killsound = false;
        inline int killsound_selection = 0;
        inline bool hitsound = false;
        inline std::string chat_message = "discord.gg/9zWrfkearX";
        inline bool custom_skybox = false;
        inline std::wstring custom_skybox_path = L"";




        inline float horizontal_fov = 0.0f;
        inline float fov_angle = 0.0f;
        inline float fov_angle_1p = 0.0f;
        inline float handchams_opacity = 0.75f;
        inline float handchams_fresnel = 1.5f;
        inline float enemy_opacity = 0.66f;
        inline float enemy_fresnel = 3.5f;
        inline float enemy_refraction = 0.07f;
        inline float enemy_rim_intensity = 2.2f;
        inline float ttck = 2.2f;

        inline float CloudSpeed = 1.0f;
        inline float StarsBrightness = 1.0f;
        inline float CloudOpacity = 1.0f;
        inline float SkyNoisePower2 = 1.0f;
        inline float SkyNoisePower1 = 1.0f;
        inline float SkySunRadius = 1.0f;
        inline float SkyHorizonFalloff = 1.0f;
        inline float SkySunBrightness = 1.0f;
        inline float SkySunHeight = 1.0f;
        inline float SkyLightDirection = 1.0f;
        inline int sky_overall_preset = 0;
        inline int sun_color_preset = 0;
        inline int skybox_preset_index = 0;

        static flinearcolor SkySunColor = { 1.0f, 1.0f, 1.0f, 1.0f };


        static flinearcolor Overall = { 1.0f, 1.0f, 1.0f, 1.0f };
        static flinearcolor Zenith = { 1.0f, 1.0f, 1.0f, 1.0f };
        static flinearcolor Horizon = { 1.0f, 1.0f, 1.0f, 1.0f };
        static flinearcolor Cloud = { 1.0f, 1.0f, 1.0f, 1.0f };

        inline bool sker = false;
        inline std::wstring sker1;
        inline bool sker2 = false;

        inline bool insta_lock_enabled = false;
        inline bool random_agent = false;
        inline int insta_lock_agent_id = 0;

        inline int mvky = 0;
        inline int flaiky = 0;
        inline int kky = 0;
        inline int cci = 0;
        inline int pcci = 0;
        inline int cm3gv = 0;
        inline int cm3gvv = 0;
        inline int cm33gv = 0;
        inline int cm33gvv = 0;
        inline int cm55gv = 0;
        inline int cm55gvv = 0;
        inline int hm3gv = 0;
        inline int hm3gvv = 0;
        inline int mesh4 = 0;
        inline int etrv3 = 0;
        inline int etrv6 = 0;
        inline int hgdd = 0;
        inline int cm4gv = 0;
        inline int cm4gvv = 0;
        inline int nsk = 0;
        inline int skonky = 0;
        inline int lft = 0;
        inline int rht = 0;
        inline int bk = 0;
        inline int bdychgrky = 0;
        inline int bdychgr_selected_buddy = 0;
        inline int materials = 0;
        static int anti_aim_pitch = 0;
        static int anti_aim_yaw = 0;

        inline int sbktr = 0;

        inline int aatp = 0;
        inline int aawy = 0;

        inline int pitchmode = 1;
        inline int baseyaw = 1;
        inline float offset = 118;
        inline int yawmodifier = 0;
        inline float modifieroffset = 139;

        inline float cachepitch = 90.0f;
        inline float cachebaseyaw = 23.0f;
        inline float cacheoffset = 10.0f;

        inline float sk1dmn = 1;
        inline float ThirdpersonFloat = 15.0f;
        inline bool tperson;
        inline float PlayerDistance = 270;

        inline bool skinchangor = false;
        inline bool FovChangor = false;
        inline bool vcr = false;
        inline bool rcr = false;
        inline bool BigGun = false;
        inline bool BigSelf = false;
        inline bool BigSelf1 = false;
        inline bool BigGun3p = false;
        inline bool spinner = false;
        inline bool spinnerz = false;
        inline bool prediction_breaker = false;
        inline float breaker_intensity = 2.0f;
        inline bool aastsm = false;
        inline float spinvalue = 90;

        inline bool aaEnabled = false;
        inline float fakeYaw = 0.f;


        inline bool thirdperson2Wireframe = false;
        inline float ui_scale = 1.0f;


        inline float BigGunFloat = 2.0f;
        inline float BigSelfFloat = 2.0f;
        inline float BigSelfFloat1 = 2.0f;
        inline float Fovchangerfloat = 70.0f;
        inline float vchr = 100.0f;
        inline float archr = 100.0f;
        inline float tldf = 2.0f;
        inline float psa = 100.0f;
        inline float GlowFloat = 1.0f;

        inline float asprfver = 1.777f;
        inline float asprfver1 = 140.0f;
        inline float asprfhor = 0.0f;
        inline float asprfvert = 0.0f;

        inline float fvof = 120.0f;
        inline float ovrt = 512.0f;
        inline float ovrt1 = 512.0f;
        inline float ovrt2 = 512.0f;
        inline float ovrt3 = 512.0f;
        inline float ovrt4 = 512.0f;
        inline float ovrt5 = 512.0f;

        inline float rmsdwf = 1.5f;
        inline float rmsdwfwp = 1.5f;



        inline std::string spam_input_text = "";
        inline float spam_delay_ms = 1000.0f;
        inline bool spam_active = false;
        inline bool drag_flag = false;

    }

    namespace tr1g {
        inline bool onne = false;
        inline bool v1sh_ch3ck = 1;
        inline float tr1g_f0v = 5.f;
        inline int tr1g_k3y = 0;
    }

    namespace buddy {
        inline bool enabled = false;
        inline int index = 0;
    }

    namespace il {
        inline bool enable = false;
        inline bool random_agent = false;

        inline int lock_agent = 0;
    }

    namespace bot {
        inline bool auto_possess = false;
        inline bool possession_active = false;

        inline float original_walk_speed = 0.0f;
        inline float original_jump_velocity = 0.0f;

        inline float speed_multiplier = 2.0f;
        inline float jump_multiplier = 1.5f;
        inline bool perfect_aim = false;
    }

    namespace pak {
        inline bool enabled = true;
        inline bool bypass = true;
    }

    inline bool stop_for_shot = false;
}

// ============================================================
// ANTI-AIM
// ============================================================
namespace AntiAim {
    static float jitter_speed = 15.0f;
    static float micro_jitter_amount = 2.0f;
    static float desync_offset = 0.0f;
    static int tick_counter = 0;
    static float last_real_yaw = 0.0f;
    static float fake_yaw_offset = 0.0f;
    static bool direction_switch = false;
    static float smooth_transition = 0.0f;

    static int three_way_state = 0;
    static float three_way_angles[3] = { -90.0f, 0.0f, 90.0f };

    static float jitter_base = 0.0f;
    static int jitter_tick = 0;

    static float pattern_time = 0.0f;
    static int pattern_state = 0;
}

// ============================================================
// NAMES
// ============================================================
namespace Names
{
    inline fstring CharacterName(fstring in)
    {
        if (in.to_str().find("Training") != std::string::npos)
            return fstring(L"Bot Lobby");
        if (in.to_str().find("BountyHunter_PC_C") != std::string::npos)
            return fstring(L"Fade");
        if (in.to_str().find("Stealth_PC_C") != std::string::npos)
            return fstring(L"Yoru");
        if (in.to_str().find("Pandemic_PC_C") != std::string::npos)
            return fstring(L"Viper");
        if (in.to_str().find("Hunter_PC_C") != std::string::npos)
            return fstring(L"Sova");
        if (in.to_str().find("Guide_PC_C") != std::string::npos)
            return fstring(L"Skye");
        if (in.to_str().find("Thorne_PC_C") != std::string::npos)
            return fstring(L"Sage");
        if (in.to_str().find("Vampire_PC_C") != std::string::npos)
            return fstring(L"Reyna");
        if (in.to_str().find("Clay_PC_C") != std::string::npos)
            return fstring(L"Raze");
        if (in.to_str().find("Phoenix_PC_C") != std::string::npos)
            return fstring(L"Phoenix");
        if (in.to_str().find("Wraith_PC_C") != std::string::npos)
            return fstring(L"Omen");
        if (in.to_str().find("Sprinter_PC_C") != std::string::npos)
            return fstring(L"Neon");
        if (in.to_str().find("Killjoy_PC_C") != std::string::npos)
            return fstring(L"Killjoy");
        if (in.to_str().find("Grenadier_PC_C") != std::string::npos)
            return fstring(L"Kayo");
        if (in.to_str().find("Terra_PC_C") != std::string::npos)
            return fstring(L"Waylay");
        if (in.to_str().find("Cashew_PC_C") != std::string::npos)
            return fstring(L"Tejo");
        if (in.to_str().find("Wushu_PC_C") != std::string::npos)
            return fstring(L"Jett");
        if (in.to_str().find("Gumshoe_PC_C") != std::string::npos)
            return fstring(L"Cypher");
        if (in.to_str().find("Deadeye_PC_C") != std::string::npos)
            return fstring(L"Chamber");
        if (in.to_str().find("Sarge_PC_C") != std::string::npos)
            return fstring(L"Brimstone");
        if (in.to_str().find("Breach_PC_C") != std::string::npos)
            return fstring(L"Breach");
        if (in.to_str().find("Rift_TargetingForm_PC_C") != std::string::npos)
            return fstring(L"Astra");
        if (in.to_str().find("Rift_PC_C") != std::string::npos)
            return fstring(L"Astra");
        if (in.to_str().find("Mage_PC_C") != std::string::npos)
            return fstring(L"Harbor");
        if (in.to_str().find("AggroBot_PC_C") != std::string::npos)
            return fstring(L"Gekko");
        if (in.to_str().find("Cable_PC_C") != std::string::npos)
            return fstring(L"DeadLock");
        if (in.to_str().find("Pawn_TrainingBot_DanceHall_Easy_C") != std::string::npos)
            return fstring(L"Bot Lobby");
        if (in.to_str().find("Pawn_TrainingBot_Defuse_Ultimate_C") != std::string::npos)
            return fstring(L"Bot Lobby");
        if (in.to_str().find("Sequoia_PC_C") != std::string::npos)
            return fstring(L"Iso");
        if (in.to_str().find("Smonk_PC_C") != std::string::npos)
            return fstring(L"Clove");
        if (in.to_str().find("Nox_PC_C") != std::string::npos)
            return fstring(L"Vyse");
        else
            return fstring(L"");
    }
    inline fstring WeaponName(fstring in)
    {
        if (in.to_str().find("Ability_Melee_Base_C") != std::string::npos)
            return fstring(L"Knife");
        if (in.to_str().find("BasePistol_C") != std::string::npos)
            return fstring(L"Classic");
        if (in.to_str().find("TrainingBotBasePistol_C") != std::string::npos)
            return fstring(L"Classic");
        if (in.to_str().find("SawedOffShotgun_C") != std::string::npos)
            return fstring(L"Shorty");
        if (in.to_str().find("AutomaticPistol_C") != std::string::npos)
            return fstring(L"Frenzy");
        if (in.to_str().find("LugerPistol_C") != std::string::npos)
            return fstring(L"Ghost");
        if (in.to_str().find("RevolverPistol_C") != std::string::npos)
            return fstring(L"Sheriff");
        if (in.to_str().find("Vector_C") != std::string::npos)
            return fstring(L"Stinger");
        if (in.to_str().find("SubMachineGun_MP5_C") != std::string::npos)
            return fstring(L"Spectre");
        if (in.to_str().find("PumpShotgun_C") != std::string::npos)
            return fstring(L"Bucky");
        if (in.to_str().find("AutomaticShotgun_C") != std::string::npos)
            return fstring(L"Judge");
        if (in.to_str().find("AssaultRifle_Burst_C") != std::string::npos)
            return fstring(L"Bulldog");
        if (in.to_str().find("DMR_C") != std::string::npos)
            return fstring(L"Guardian");
        if (in.to_str().find("AssaultRifle_ACR_C") != std::string::npos)
            return fstring(L"Phantom");
        if (in.to_str().find("AssaultRifle_AK_C") != std::string::npos)
            return fstring(L"Vandal");
        if (in.to_str().find("LeverSniperRifle_C") != std::string::npos)
            return fstring(L"Marshall");
        if (in.to_str().find("BoltSniper_C") != std::string::npos)
            return fstring(L"Operator");
        if (in.to_str().find("LightMachineGun_C") != std::string::npos)
            return fstring(L"Ares");
    
            return fstring(L"Odin");
        if (in.to_str().find("DS_Gun_C") != std::string::npos)
            return fstring(L"Outlaw");
        else
            return fstring(L"");
    }

    inline fstring ItsGamerDoc(fstring in)
    {
        if (in.to_str().find("Ability_Melee_Base_C") != std::string::npos)
            return fstring(L"ItsGamerDoc");
        if (in.to_str().find("BasePistol_C") != std::string::npos)
            return fstring(L"ItsGamerDoc");
        if (in.to_str().find("TrainingBotBasePistol_C") != std::string::npos)
            return fstring(L"ItsGamerDoc");
        if (in.to_str().find("SawedOffShotgun_C") != std::string::npos)
            return fstring(L"ItsGamerDoc");
        if (in.to_str().find("AutomaticPistol_C") != std::string::npos)
            return fstring(L"ItsGamerDoc");
        if (in.to_str().find("LugerPistol_C") != std::string::npos)
            return fstring(L"ItsGamerDoc");
        if (in.to_str().find("RevolverPistol_C") != std::string::npos)
            return fstring(L"ItsGamerDoc");
        if (in.to_str().find("Vector_C") != std::string::npos)
            return fstring(L"ItsGamerDoc");
        if (in.to_str().find("SubMachineGun_MP5_C") != std::string::npos)
            return fstring(L"ItsGamerDoc");
        if (in.to_str().find("PumpShotgun_C") != std::string::npos)
            return fstring(L"ItsGamerDoc");
        if (in.to_str().find("AutomaticShotgun_C") != std::string::npos)
            return fstring(L"ItsGamerDoc");
        if (in.to_str().find("AssaultRifle_Burst_C") != std::string::npos)
            return fstring(L"ItsGamerDoc");
        if (in.to_str().find("DMR_C") != std::string::npos)
            return fstring(L"ItsGamerDoc");
        if (in.to_str().find("AssaultRifle_ACR_C") != std::string::npos)
            return fstring(L"ItsGamerDoc");
        if (in.to_str().find("AssaultRifle_AK_C") != std::string::npos)
            return fstring(L"ItsGamerDoc");
        if (in.to_str().find("LeverSniperRifle_C") != std::string::npos)
            return fstring(L"ItsGamerDoc");
        if (in.to_str().find("BoltSniper_C") != std::string::npos)
            return fstring(L"ItsGamerDoc");
        if (in.to_str().find("LightMachineGun_C") != std::string::npos)
            return fstring(L"ItsGamerDoc");
        if (in.to_str().find("HeavyMachineGun_C") != std::string::npos)
            return fstring(L"ItsGamerDoc");
        else
            return fstring(L"ItsGamerDoc");
    }
}