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


uworld* world;
uobject* class_private;
ashooterplayerstate* plste;
uskeletalmeshcomponent* mashe;
ashootercharacter* chara;

#define DefusePercentageMax 6.984602
#define CurrentDefuseSectionMax 2

static float  Gloww = 5.0f;
static flinearcolor ChamsColorw{ 1.0f, 0.5f, 0.0f, 0.9f };

namespace G
{
    currentequippable* MyWeapon = nullptr;
    currentequippable* LastWeapon = nullptr;
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

struct DamageInfo {
    float damage;
    fvector position;
    float time;
    bool isHeadshot;

    DamageInfo(float d, const fvector& pos, float t, bool hs)
        : damage(d), position(pos), time(t), isHeadshot(hs) {
    }
};

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
//    UKismetRenderingLibrary* par;
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


    namespace menu
    {
        flinearcolor RGBtoFLC(float r, float g, float b)
        {
            return { r / 255, g / 255, b / 255, 1 };
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
        namespace Colors
        {
            // Modern dark theme with blue/purple accent
            flinearcolor Text{ 0.95f, 0.95f, 0.98f, 1.0f }; // Almost white
            flinearcolor Text_Shadow{ 0.95f, 0.95f, 0.98f, 1.0f };
            flinearcolor Text_Outline{ 1.0f, 1.0f, 1.0f, 1.0f };
            flinearcolor Text_Active{ 0.6f, 0.6f, 1.0f, 0.8f }; // Light blue accent

            flinearcolor Button_Idle{ 0.13f, 0.15f, 0.22f, 1.0f }; // Dark blue
            flinearcolor Button_Hovered{ 0.22f, 0.25f, 0.38f, 1.0f }; // Lighter blue
            flinearcolor Button_Active{ 0.45f, 0.18f, 0.65f, 1.0f }; // Purple accent

            flinearcolor Checkbox_Idle{ 0.18f, 0.20f, 0.28f, 1.0f };
            flinearcolor Checkbox_Hovered{ 0.30f, 0.32f, 0.45f, 1.0f };
            flinearcolor Checkbox_Enabled{ 0.45f, 0.18f, 0.65f, 1.0f }; // Purple accent

            flinearcolor Combobox_Idle{ 0.13f, 0.15f, 0.22f, 1.0f };
            flinearcolor Combobox_Hovered{ 0.22f, 0.25f, 0.38f, 1.0f };
            flinearcolor Combobox_Elements{ 0.45f, 0.18f, 0.65f, 0.5f };

            flinearcolor Slider_Idle{ 0.13f, 0.15f, 0.22f, 1.0f };
            flinearcolor Slider_Hovered{ 0.22f, 0.25f, 0.38f, 1.0f };
            flinearcolor Slider_Progress{ 0.45f, 0.18f, 0.65f, 1.0f };
            flinearcolor Slider_Button{ 0.6f, 0.6f, 1.0f, 1.0f };

            flinearcolor ColorPicker_Background{ 0.10f, 0.10f, 0.15f, 0.95f };
            flinearcolor Outline{ 1.0f, 1.0f, 1.0f, 1.0f }; // White outline
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
                fvector2d cursorPos = CursorPos();
                drawFilledRect(fvector2d(cursorPos.x - 5, cursorPos.y - 5), 10, 10, flinearcolor(255, 255, 255, 255));
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
        bool Window(ucanvas* canvas, uobject* font, fstring title, fstring domain, fvector2d* pos, fvector2d size, bool isOpen)
        {
            elements_count = 0;

            if (!isOpen)
                return false;

            bool isHovered = MouseInZone(fvector2d{ pos->x, pos->y }, size);

            //Drop last element
            if (current_element != -1 && !GetAsyncKeyState(0x1))
            {
                current_element = -1;
            }

            // Removed drag functionality to keep menu fixed in position

            offset_x = 0.0f; offset_y = 0.0f;
            menu_pos = fvector2d{ pos->x, pos->y };
            first_element_pos = fvector2d{ 0, 0 };
            current_element_pos = fvector2d{ 0, 0 };
            current_element_size = fvector2d{ 0, 0 };

            drawFilledRect(fvector2d(pos->x, pos->y), size.x, size.y, RGBtoFLC(1, 1, 1));
            drawFilledRect(fvector2d(pos->x + 20, pos->y + 20), 160, 61, RGBtoFLC(6, 6, 6));
            drawFilledRect(fvector2d(pos->x + 21, pos->y + 21), 160 - 2, 61 - 2, RGBtoFLC(2, 2, 2));

            draw_text77(canvas, font, title, RGBtoFLC(255, 255, 255), { pos->x + 21 + (160 / 2) - 17, pos->y + 21 + (61 / 2) });
            draw_text77(canvas, font, domain, RGBtoFLC(0, 145, 255), { pos->x + 21 + (160 / 2) + 14, pos->y + 21 + (61 / 2) });

            drawFilledRect(fvector2d(pos->x + 160 + 40, pos->y + 20), 660, 61, RGBtoFLC(6, 6, 6));
            drawFilledRect(fvector2d(pos->x + 160 + 41, pos->y + 21), 660 - 2, 61 - 2, RGBtoFLC(2, 2, 2));

            drawFilledRect(fvector2d(pos->x + 660 + 160 + 60, pos->y + 20), 62, 61, RGBtoFLC(6, 6, 6));
            drawFilledRect(fvector2d(pos->x + 660 + 160 + 61, pos->y + 21), 62 - 2, 61 - 2, RGBtoFLC(2, 2, 2));

            drawFilledRect(fvector2d(pos->x + 20, pos->y + 61 + 40), 160, 530, RGBtoFLC(6, 6, 6));
            drawFilledRect(fvector2d(pos->x + 21, pos->y + 61 + 41), 160 - 2, 530 - 2, RGBtoFLC(2, 2, 2));

            menu::offset_x = 21 + 19;
            menu::offset_y = 61 + 41 + 19;

            return true;
        }

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

            fvector2d textPos = fvector2d{ pos.x + size.x / 2, pos.y + size.y / 2 };

            //Bg
            if (active)
            {
                drawFilledRect(fvector2d(pos.x, pos.y), size.x, size.y, RGBtoFLC(6, 6, 6));
                drawFilledRect(fvector2d(pos.x + 1, pos.y + 1), size.x - 2, size.y - 2, RGBtoFLC(2, 2, 2));

                drawFilledRect(fvector2d(pos.x + size.x - 3, pos.y + 7), 2, 21, RGBtoFLC(0, 145, 255));
                draw_text77(canvas, font, name, RGBtoFLC(0, 145, 255), { pos.x + 10, pos.y + 15 });

                canvas->k2_drawtext(font, name, textPos, fvector2d(0.98, 0.98), RGBtoFLC(0, 145, 255), 0.0f, RGBtoFLC(0, 0, 0), fvector2d(0, 0), true, true, false, RGBtoFLC(0, 0, 0));
            }
            else if (isHovered)
            {
                canvas->k2_drawtext(font, name, textPos, fvector2d(0.98, 0.98), RGBtoFLC(120, 120, 120), 0.0f, RGBtoFLC(0, 0, 0), fvector2d(0, 0), true, true, false, RGBtoFLC(0, 0, 0));
                hover_element = true;
            }
            else
            {
                canvas->k2_drawtext(font, name, textPos, fvector2d(0.98, 0.98), RGBtoFLC(60, 60, 60), 0.0f, RGBtoFLC(0, 0, 0), fvector2d(0, 0), true, true, false, RGBtoFLC(0, 0, 0));
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

        void SectionWrapper(ucanvas* canvas, uobject* font, fstring name, fvector2d size)
        {
            fvector2d padding = fvector2d{ 0, 0 };
            fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
            if (sameLine)
            {
                pos.x = menu_pos.x + padding.x + offset_x;
                pos.y = menu_pos.y + padding.y + offset_y;
            }

            drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, RGBtoFLC(6, 6, 6));
            drawFilledRect(fvector2d{ pos.x + 1, pos.y + 1 }, size.x - 2, size.y - 2, RGBtoFLC(2, 2, 2));

            canvas->k2_drawtext(font, name, fvector2d(pos.x + 10, pos.y + 15), fvector2d(1.1, 1.1), RGBtoFLC(0, 145, 255), 0.0f, RGBtoFLC(0, 0, 0), fvector2d(0, 0), false, true, false, RGBtoFLC(0, 0, 0));

            menu::offset_y += 27;

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

        void SameLine(float offset = 0.0f) {
            if (offset != 0.0f) {
                cursor_x += offset;
            }
            else {
                cursor_x += same_line_offset;
            }
            same_line_offset = 0;
        }

        void Checkbox(uobject* font, const wchar_t* name, bool* value, float relative_x, float relative_y)
        {
            elements_count++;

            float sizex = 31;
            float sizey = 11.5;
            float xsize = 2;
            fvector2d padding = fvector2d{ 10,8 };

            // Use the provided relative position instead of global offsets
            fvector2d pos = fvector2d{ relative_x, relative_y };

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
            }
            bool isHovered = MouseInZone(fvector2d{ pos.x + 300, pos.y }, fvector2d{ sizex, sizey });

            fvector2d textPos = fvector2d{ pos.x, pos.y - xsize };

            drawFilledRect(fvector2d{ pos.x + 300 + 2, pos.y }, sizex, sizey, RGBtoFLC(14, 14, 14));

            if (!sameLine)
                offset_y = pos.y + sizex + padding.y - menu_pos.y;

            if (*value)
            {
                drawFilledRect(fvector2d{ pos.x + 300 + 1 + (30.0f - 11.5f), pos.y - xsize }, 17, 18, RGBtoFLC(0, 145, 255));
                canvas->k2_drawtext(font, name, textPos, fvector2d(1.0f, 1.0f), RGBtoFLC(255, 255, 255), 0.0f, flinearcolor(), fvector2d(0, 0), false, false, false, flinearcolor());
                //drawFilledRect(fvector2d{ pos.x + 9, pos.y + 9 }, size - 18, size - 18, Colors::Checkbox_Hovered);
            }
            else {
                drawFilledRect(fvector2d{ pos.x + 300 - 1, pos.y - xsize }, 17, 18, RGBtoFLC(40, 40, 40));
                canvas->k2_drawtext(font, name, textPos, fvector2d(1.0f, 1.0f), RGBtoFLC(255, 255, 255), 0.0f, flinearcolor(), fvector2d(0, 0), false, false, false, flinearcolor());

            }

            sameLine = false;
            last_element_pos = pos;
            //last_element_size = size;
            if (first_element_pos.x == 0.0f)
                first_element_pos = pos;

            if (isHovered && input::is_mouse_clicked(0, elements_count, false))
                *value = !*value;
        }

        bool checkbox_enabled[256];
        void Combobox(uobject* font, const wchar_t* name, fvector2d size, int* value, const wchar_t* arg, ...)
        {
            elements_count++;

            fvector2d padding = fvector2d{ 14, 30 };
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

            //Bg
            if (isHovered || checkbox_enabled[elements_count])
            {
                drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, RGBtoFLC(10, 10, 10));
                drawFilledRect(fvector2d{ pos.x + 1, pos.y + 1 }, size.x - 2, size.y - 2, RGBtoFLC(3, 3, 3));

                hover_element = true;
            }
            else
            {
                drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, RGBtoFLC(10, 10, 10));
                drawFilledRect(fvector2d{ pos.x + 1, pos.y + 1 }, size.x - 2, size.y - 2, RGBtoFLC(2, 2, 2));
            }

            if (!sameLine)
                offset_y += size.y + padding.y;

            //Text (clean, no shadow/outline)
            fvector2d textPos = fvector2d{ pos.x - 2.0f, pos.y - size.y + 2.0f };
            canvas->k2_drawtext(font, name, textPos, fvector2d(1.0f, 1.0f), RGBtoFLC(255, 255, 255), 0.0f, flinearcolor(), fvector2d(0, 0), false, false, false, flinearcolor());

            canvas->k2_drawtext(font, s2wc("+"), fvector2d{ pos.x + size.x - 17, pos.y + size.y / 2 }, fvector2d(1.0f, 1.0f), RGBtoFLC(255, 255, 255), 0.0f, flinearcolor(), fvector2d(0, 0), false, true, false, flinearcolor());

            //Elements
            bool isHovered2 = false;
            fvector2d element_pos = pos;
            int num = 0;

            if (checkbox_enabled[elements_count])
            {
                current_element_size.x = element_pos.x - 5.0f;
                current_element_size.y = element_pos.y - 5.0f;
            }
            va_list arguments;
            for (va_start(arguments, arg); arg != NULL; arg = va_arg(arguments, const wchar_t*))
            {
                //Selected Element (clean text)
                if (num == *value)
                {
                    fvector2d _textPos = fvector2d{ pos.x + 5, pos.y + size.y / 2 };
                    canvas->k2_drawtext(font, arg, _textPos, fvector2d(1.0f, 1.0f), RGBtoFLC(255, 255, 255), 0.0f, flinearcolor(), fvector2d(0, 0), false, true, false, flinearcolor());
                }

                if (checkbox_enabled[elements_count])
                {
                    element_pos.y += 25.0f;

                    isHovered2 = MouseInZone(fvector2d{ element_pos.x, element_pos.y }, fvector2d{ size.x, 25.0f });
                    if (isHovered2)
                    {
                        hover_element = true;
                        PostRenderer::drawFilledRect(fvector2d{ element_pos.x, element_pos.y }, size.x, 25.0f, RGBtoFLC(4, 4, 4));

                        //Click
                        if (input::is_mouse_clicked(0, elements_count, false))
                        {
                            *value = num;
                            checkbox_enabled[elements_count] = false;
                        }
                    }
                    else
                    {
                        PostRenderer::drawFilledRect(fvector2d{ element_pos.x, element_pos.y }, size.x, 25.0f, RGBtoFLC(3, 3, 3));
                    }

                    // Element list text (clean white)
                    PostRenderer::TextLeft(arg, fvector2d{ element_pos.x + 10.0f, element_pos.y + 5.0f }, RGBtoFLC(255, 255, 255), true);
                }
                num++;
            }
            va_end(arguments);
            if (checkbox_enabled[elements_count])
            {
                current_element_size.x = element_pos.x + 5.0f;
                current_element_size.y = element_pos.y + 5.0f;
            }

            sameLine = false;
            last_element_pos = pos;
            last_element_size = size;
            if (first_element_pos.x == 0.0f)
                first_element_pos = pos;

            if (isHovered && input::is_mouse_clicked(0, elements_count, false))
            {
                checkbox_enabled[elements_count] = !checkbox_enabled[elements_count];
            }
            if (!isHovered && !isHovered2 && input::is_mouse_clicked(0, elements_count, false))
            {
                checkbox_enabled[elements_count] = false;
            }
        }


        void SliderFloat(uobject* font, const wchar_t* name, float* value, float min, float max, float relative_x, float relative_y, const char* format = "%.0f")
        {
            elements_count++;
            fvector2d size = fvector2d{ 335, 22.5 };
            fvector2d slider_size = fvector2d{ 335, 12.5 };
            fvector2d adjust_zone = fvector2d{ 0, 20 };
            fvector2d padding = fvector2d{ 10, 5 };
            fvector2d pos = fvector2d{ relative_x, relative_y };
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
            }
            bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y + slider_size.y + padding.y - adjust_zone.y }, fvector2d{ slider_size.x, slider_size.y + adjust_zone.y * 1.5f });

            if (!sameLine)
                offset_y = pos.y + size.y + padding.y - menu_pos.y;

            //Bg
            if (isHovered || current_element == elements_count)
            {
                //Drag
                if (input::is_mouse_clicked(0, elements_count, true))
                {
                    current_element = elements_count;

                    fvector2d cursorPos = CursorPos();
                    *value = ((cursorPos.x - pos.x) * ((max - min) / slider_size.x)) + min;
                    if (*value < min) *value = min;
                    if (*value > max) *value = max;
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

            //Text (clean)
            fvector2d textPos = fvector2d{ pos.x, pos.y - 2.0f };
            canvas->k2_drawtext(font, name, textPos, fvector2d(1.0f, 1.0f), RGBtoFLC(255, 255, 255), 0.0f, flinearcolor(), fvector2d(0, 0), false, false, false, flinearcolor());

            //Value
            float oneP = slider_size.x / (max - min);
            drawFilledRect(fvector2d{ pos.x + 1, pos.y + slider_size.y + padding.y + 1 }, oneP * (*value - min) - 2, slider_size.y - 2, RGBtoFLC(0, 145, 255));
            drawFilledRect(fvector2d{ pos.x + oneP * (*value - min), pos.y + slider_size.y + padding.y + 1 - 3 }, 17, 18, RGBtoFLC(7, 7, 7));

            char buffer[32];
            sprintf_s(buffer, format, *value);
            canvas->k2_drawtext(font, s2wc(buffer), fvector2d(pos.x + slider_size.x - 8.0f, pos.y - 2.0f), fvector2d(1.0f, 1.0f), RGBtoFLC(255, 255, 255), 0.0f, flinearcolor(), fvector2d(0, 0), true, false, false, flinearcolor());

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
        void Hotkey(uobject* font, const char* name, fvector2d size, int* key, float relative_x, float relative_y)
        {
            elements_count++;
            fvector2d padding = fvector2d{ 80, 4 };
            fvector2d pos = fvector2d{ relative_x, relative_y };
            if (sameLine)
            {
                pos.x = last_element_pos.x + last_element_size.x + padding.x;
                pos.y = last_element_pos.y - padding.y;
            }
            if (pushY)
            {
                pos.y = pushYvalue;
                pushY = false;
                pushYvalue = 0.0f;
            }
            bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, size);

            drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, RGBtoFLC(10, 10, 10));
            drawFilledRect(fvector2d{ pos.x + 1, pos.y + 1 }, size.x - 2, size.y - 2, RGBtoFLC(2, 2, 2));

            if (!sameLine)
                offset_y = pos.y + size.y + padding.y - menu_pos.y;

            if (active_hotkey == elements_count)
            {
                //Text
                fvector2d textPos = fvector2d{ pos.x + size.x / 2, pos.y + size.y / 2 };
                canvas->k2_drawtext(font, L"...", textPos, fvector2d(0.96, 0.94), RGBtoFLC(60, 60, 60), 0.0f, Colors::Text_Shadow, fvector2d(0, 0), true, true, true, Colors::Text_Outline);

                if (!input::is_any_mouse_down())
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
                //Text
                fvector2d textPos = fvector2d{ pos.x + size.x / 2, pos.y + size.y / 2 };
                canvas->k2_drawtext(font, s2wc(VirtualKeyCodeToString(*key).c_str()), textPos, fvector2d(0.99, 0.99), RGBtoFLC(60, 60, 60), 0.0f, Colors::Text_Shadow, fvector2d(0, 0), true, true, true, Colors::Text_Outline);


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
            last_element_size = size;
            if (first_element_pos.x == 0.0f)
                first_element_pos = pos;
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

        static void text_wrapper_ooo(ucanvas* canvas, uobject* font, fvector2d position, flinearcolor c, bool center, fstring text) noexcept
        {
            canvas->k2_drawtext(font, text, position, fvector2d(1.1f, 1.1f), c, 0.f, flinearcolor(), position, center, center, false, flinearcolor(0.f, 0.f, 0.f, 1.f));
        }

        void hk_draw_canvas(uobject* font, bool open_canvas, ucanvas* canvas) {
            if (!canvas || !open_canvas) return;

            menu::SetupCanvas(canvas);
            input::handle();

            flinearcolor accent_color = { 0.45f, 0.20f, 0.85f, 1.0f };
            flinearcolor bg_color = { 0.06f, 0.04f, 0.12f, 0.97f };
            flinearcolor dark_accent = { 0.12f, 0.06f, 0.18f, 1.0f };
            flinearcolor text_color = { 0.95f, 0.95f, 0.95f, 1.0f };
            flinearcolor highlight = { 0.55f, 0.25f, 0.95f, 1.0f };
            flinearcolor secondary = { 0.45f, 0.40f, 0.55f, 1.0f };

            static float menu_x = (GetSystemMetrics(SM_CXSCREEN) - 960) / 2.0f;
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
                if (mouse_pos.x >= menu_x && mouse_pos.x <= menu_x + 960 &&
                    mouse_pos.y >= menu_y && mouse_pos.y <= menu_y + 60) {
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
            prev_mouse_clicked = mouse_clicked;

            fvector2d pos = { menu_x, menu_y };

            if (menu::Window(canvas, font, L"", L"", &pos, fvector2d{ 960, 650 }, open_canvas)) {
                float header_height = 60;

                // Header
                menu::drawGradientFilledRect({ pos.x, pos.y }, 960, header_height,
                    flinearcolor{ 0.10f, 0.05f, 0.15f, 0.95f * pulse_effect },
                    flinearcolor{ 0.04f, 0.02f, 0.08f, 0.98f },
                    flinearcolor{ 0.10f, 0.05f, 0.15f, 0.95f * pulse_effect },
                    30);

                {
                    const wchar_t* hdr_brand = L"VacsenSoftware";
                    float hdr_rainbow = (float)GetTickCount64() / 300.0f;
                    float total_text_w = (float)wcslen(hdr_brand) * 16.0f;
                    float hdr_start_x = pos.x + (960.0f - total_text_w) / 2.0f;
                    for (int ci = 0; ci < (int)wcslen(hdr_brand); ci++) {
                        float hue = fmodf((hdr_rainbow / 360.0f + ci * 0.07f), 1.0f);
                        flinearcolor rgb_c = HSVtoRGB(hue, 1.0f, 1.0f);
                        wchar_t single[2] = { hdr_brand[ci], L'\0' };
                        canvas->k2_drawtext(font, single, { hdr_start_x + ci * 16.0f, pos.y + 12 }, { 1.0f, 1.0f }, rgb_c, 0.f, { 0,0,0,0.5f }, { 1,1 }, false, false, true, { 0,0,0,0.8f });
                    }
                }
                canvas->k2_drawtext(font, L"by Vacsen", { pos.x + 480, pos.y + 32 }, { 0.65f, 0.65f },
                    { 0.55f, 0.50f, 0.65f, 0.7f * pulse_effect }, 0.f, {}, {}, true, false, false, {});

                // Tabs
                static int tab = 0;
                const wchar_t* tab_names[] = { L"AIMBOT", L"VISUALS", L"MISC" };
                int tab_count = 3;
                float tab_width = 150, tab_height = 36, tab_spacing = 15;
                fvector2d tab_pos = { pos.x + (960 - (tab_width * tab_count + tab_spacing * (tab_count - 1))) / 2,
                                      pos.y + header_height + 12 };

                for (int i = 0; i < tab_count; i++) {
                    flinearcolor tab_color = (tab == i) ? highlight : secondary;
                    menu::drawGradientFilledRect(tab_pos, tab_width, tab_height,
                        { tab_color.r, tab_color.g, tab_color.b, 0.8f },
                        { tab_color.r * 0.7f, tab_color.g * 0.7f, tab_color.b * 0.7f, 0.6f },
                        { tab_color.r, tab_color.g, tab_color.b, 0.8f }, 10);

                    fvector2d text_pos = { tab_pos.x + tab_width / 2, tab_pos.y + tab_height / 2 };
                    canvas->k2_drawtext(font, tab_names[i], text_pos, { 0.85f, 0.85f }, text_color,
                        0.f, {}, {}, true, true, false, {});

                    if (menu::MouseInZone(tab_pos, { tab_width, tab_height }) && input::is_mouse_clicked(0, 0, false))
                        tab = i;

                    tab_pos.x += tab_width + tab_spacing;
                }

                // İçerik
                static fvector2d current_menu_pos = pos;
                current_menu_pos = pos;

                // Sol panel çizgisi
                menu::drawGradientFilledRect({ pos.x, pos.y + header_height + tab_height + 24 }, 960, 1,
                    { 0.3f, 0.2f, 0.5f, 0.4f }, { 0.5f, 0.3f, 0.7f, 0.6f }, { 0.3f, 0.2f, 0.5f, 0.4f }, 20);

                float content_top = pos.y + header_height + tab_height + 34;
                float step = 36;

                if (tab == 0) {
                    // AIMBOT
                    fvector2d left_panel_pos = { current_menu_pos.x + 30, content_top };
                    fvector2d right_panel_pos = { current_menu_pos.x + 490, content_top };

                    // Sol panel - Checkbox
                    float rx = left_panel_pos.x + 30, ry = left_panel_pos.y + 15;
                    menu::Checkbox(font, L"Enable Aim", &globals::aimbot::a1mbot, rx, ry); ry += step;
                    menu::Checkbox(font, L"Show Target FOV", &globals::aimbot::draw_f0v, rx, ry); ry += step;
                    menu::Checkbox(font, L"Recoil Control", &globals::aimbot::reco1l_contr0l, rx, ry); ry += step;
                    menu::Checkbox(font, L"Visibility Check", &globals::aimbot::v1sh_ch3ck, rx, ry); ry += step;
                    menu::Hotkey(font, "Aim Key", fvector2d(380, 28), &globals::aimbot::a1m_k3y, rx, ry);

                    // Sag panel - Slider
                    rx = right_panel_pos.x + 30; ry = right_panel_pos.y + 15;
                    menu::SliderFloat(font, L"Smoothness", &globals::aimbot::a1m_sm00th, 1.0f, 100.0f, rx, ry); ry += step;
                    menu::SliderFloat(font, L"Target Radius", &globals::aimbot::a1m_f0v, 1.0f, 1000.0f, rx, ry);
                }
                else if (tab == 1) {
                    // VISUALS
                    fvector2d left_panel_pos = { current_menu_pos.x + 30, content_top };
                    fvector2d right_panel_pos = { current_menu_pos.x + 490, content_top };

                    // Sol panel - ESP
                    float rx = left_panel_pos.x + 30, ry = left_panel_pos.y + 15;
                    menu::Checkbox(font, L"Ignore Dormants", &globals::visuals::dormant, rx, ry); ry += step;
                    menu::Checkbox(font, L"Visible Check", &globals::visuals::visiblecheck, rx, ry); ry += step;
                    menu::Checkbox(font, L"2D Box", &globals::visuals::box2d, rx, ry); ry += step;
                    menu::Checkbox(font, L"Corner Box", &globals::visuals::box, rx, ry); ry += step;
                    menu::Checkbox(font, L"Distance", &globals::visuals::dstc, rx, ry); ry += step;
                    menu::Checkbox(font, L"Snaplines", &globals::visuals::snapl1ne, rx, ry); ry += step;
                    menu::Checkbox(font, L"Skeleton", &globals::visuals::sk3let0n, rx, ry); ry += step;
                    menu::Checkbox(font, L"Health Bar", &globals::visuals::h3althbar, rx, ry); ry += step;

                    // Sag panel - Chams
                    rx = right_panel_pos.x + 30; ry = right_panel_pos.y + 15;
                    menu::Checkbox(font, L"Chams", &globals::visuals::chams, rx, ry); ry += step;
                    menu::SliderFloat(font, L"Chams Intensity", &globals::visuals::chams_intensity, 0.1f, 5.0f, rx, ry); ry += step;
                    menu::Checkbox(font, L"Rainbow Chams", &globals::visuals::rainbow_chams, rx, ry); ry += step;
                    menu::SliderFloat(font, L"Chams R", &globals::visuals::chams_color.r, 0.0f, 1.0f, rx, ry); ry += step;
                    menu::SliderFloat(font, L"Chams G", &globals::visuals::chams_color.g, 0.0f, 1.0f, rx, ry); ry += step;
                    menu::SliderFloat(font, L"Chams B", &globals::visuals::chams_color.b, 0.0f, 1.0f, rx, ry); ry += step;
                    menu::SliderFloat(font, L"Chams A", &globals::visuals::chams_color.a, 0.0f, 1.0f, rx, ry); ry += step;
                }
                else if (tab == 2) {
                    // MISC
                    fvector2d left_panel_pos = { current_menu_pos.x + 30, content_top };
                    fvector2d right_panel_pos = { current_menu_pos.x + 490, content_top };

                    // Sol panel - Kamera ve Gorunum
                    float rx = left_panel_pos.x + 30, ry = left_panel_pos.y + 15;
                    menu::Checkbox(font, L"Custom Aspect Ratio", &globals::misc::aspect_ratio_enabled, rx, ry); ry += step;
                    menu::SliderFloat(font, L"Aspect Ratio Value", &globals::misc::aspect_ratio_value, 1.0f, 3.0f, rx, ry); ry += step;
                    menu::Checkbox(font, L"Third Person", &globals::misc::tperson, rx, ry); ry += step;
                    menu::SliderFloat(font, L"Third Person Distance", &globals::misc::PlayerDistance, 50.0f, 400.0f, rx, ry); ry += step;
                    menu::Checkbox(font, L"FOV Changer", &globals::misc::FovChangor, rx, ry); ry += step;
                    menu::SliderFloat(font, L"FOV Value", &globals::misc::Fovchangerfloat, 70.0f, 120.0f, rx, ry); ry += step;
                    menu::Checkbox(font, L"Disconnect From Server", &globals::misc::disconnect_server, rx, ry); ry += step;
                    menu::Checkbox(font, L"Unlock All", &globals::misc::sk1n_chang3r, rx, ry); ry += step;

                    // Sag panel - Weapon & Anti-Aim
                    rx = right_panel_pos.x + 30; ry = right_panel_pos.y + 15;
                    menu::Checkbox(font, L"Wide Arms", &globals::misc::rmsdw, rx, ry); ry += step;
                    menu::Checkbox(font, L"Wireframe Hands", &globals::visuals::wireframe_hands, rx, ry); ry += step;
                    menu::Checkbox(font, L"Hand Chams", &globals::visuals::handchams, rx, ry); ry += step;
                    menu::SliderFloat(font, L"Arm Width", &globals::misc::arm_width, 0.1f, 5.0f, rx, ry); ry += step;
                    menu::SliderFloat(font, L"Arm Height", &globals::misc::arm_height, 0.1f, 5.0f, rx, ry); ry += step;
                    menu::SliderFloat(font, L"Arm Length", &globals::misc::arm_length, 0.1f, 5.0f, rx, ry); ry += step;
                    menu::Checkbox(font, L"Anti-Aim", &globals::misc::aa, rx, ry); ry += step;
                    menu::SliderFloat(font, L"Spin Value", &globals::misc::spinvalue, 0.0f, 360.0f, rx, ry);
                }

                menu::Render(font);
            }
        }
        }

    flinearcolor convert_to_flinearcolor(int r, int g, int b, int a) {
        return flinearcolor(
            (float)r / 255.0f,
            (float)g / 255.0f,
            (float)b / 255.0f,
            (float)a / 255.0f
        );
    }

    std::wstring to_wide_string(const std::string& str) {
        return std::wstring(str.begin(), str.end());
    }

    flinearcolor RGBtoFLC(float R, float G, float B)
    {
        return { R / 255, G / 255, B / 255, 1 };
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

        if (!globals::misc::aa) {

            LocalCameraRotation = ViewInfo->Rotation;
        }
        else {

            if (!GetAsyncKeyState(VK_LBUTTON)) {
                ViewInfo->Rotation = LocalCameraRotation;
            }
            else {
                ViewInfo->Rotation = ViewInfo->Rotation;
            }
        }

        if (globals::misc::aspect_ratio_enabled) {
            ViewInfo->AspectRatio = globals::misc::aspect_ratio_value;
        }

        if (globals::misc::tperson) {
            fvector forward;

            float radPitch = ViewInfo->Rotation.x * (M_PI / 180.0f);
            float radYaw = ViewInfo->Rotation.y * (M_PI / 180.0f);

            forward.x = cosf(radPitch) * cosf(radYaw);
            forward.y = cosf(radPitch) * sinf(radYaw);
            forward.z = sinf(radPitch);

            ViewInfo->Location.x -= forward.x * globals::misc::PlayerDistance;
            ViewInfo->Location.y -= forward.y * globals::misc::PlayerDistance;
            ViewInfo->Location.z -= forward.z * globals::misc::PlayerDistance;
        }


        /*if (!globals::misc::spinner && ViewInfo) {
            LocalCameraRotation = ViewInfo->Rotation;
        }
        else {
            float deltaX, deltaY;
            controllers->GetInputMouseDelta(deltaX, deltaY);
            float sensitivity = controllers->GetMouseSensitivity();
            LocalCameraRotation.x += deltaY * sensitivity;
            LocalCameraRotation.y += deltaX * sensitivity;

            character->K2_SetActorRelativeRotation(fvector{ 0, LocalCameraRotation.y, 0 }, false, false);

            ViewInfo->Rotation = LocalCameraRotation;
        }*/

        hooks::SetCameraCachePOVOriginal(PlayerCameraManager, ViewInfo);
    }

    void Clamp(fvector& Ang) {
        if (Ang.x < 0.f)
            Ang.x += 360.f;

        if (Ang.x > 360.f)
            Ang.x -= 360.f;

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

            drawings::draw_f0v({ screen_center_x, screen_center_y }, globals::aimbot::a1m_f0v, 100.0, maincolor, canvas);

            if (globals::misc::FovChangor) {
                SPOOF_FUNC
                    controllers->set_fov(globals::misc::Fovchangerfloat);
            }

            if (globals::misc::aspect_ratio_enabled && controllers)
            {
                aplayercameramanager* cam = controllers->get_camera_manager();
                if (cam)
                {
                    cam->SetAspectRatio(globals::misc::aspect_ratio_value);
                }
            }

            if (globals::misc::aspect_ratio_enabled && controllers) {
                aplayercameramanager* cam = controllers->get_camera_manager();
                if (cam) {
                    cam->SetAspectRatio(globals::misc::aspect_ratio_value);
                }
            }

           
            if (GetAsyncKeyState('H') & 1) {
                globals::misc::tperson = !globals::misc::tperson;
            }

            if (controllers && character)
            {
                if (globals::misc::tperson)
                {
                    // Kamera geri çek
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

                    // 1P mesh gizle
                    if (auto mesh1p = *(uobject**)((uintptr_t)character + offsets::mesh1p)) {
                        if (auto fn = uobject::find_object<uobject*>(crypt(L"Engine.PrimitiveComponent.SetVisibility"))) {
                            struct { bool bNewVisibility; bool bPropagateToChildren; } vis{ false, true };
                            mesh1p->process_event(fn, &vis);
                        }
                    }

                    // 3P mesh aç
                    character->Set3pMeshVisible(true);
                }
                else
                {
                    // 1P mesh geri aç
                    if (auto mesh1p = *(uobject**)((uintptr_t)character + offsets::mesh1p)) {
                        if (auto fn = uobject::find_object<uobject*>(crypt(L"Engine.PrimitiveComponent.SetVisibility"))) {
                            struct { bool bNewVisibility; bool bPropagateToChildren; } vis{ true, true };
                            mesh1p->process_event(fn, &vis);
                        }
                    }

                    // 3P mesh kapat
                    character->Set3pMeshVisible(false);
                }
            }
            else if (character) {
                
                if (auto mesh1p = *(uobject**)((uintptr_t)character + offsets::mesh1p)) {
                    if (auto fn = uobject::find_object<uobject*>(crypt(L"Engine.PrimitiveComponent.SetVisibility"))) {
                        struct { bool bNewVisibility; bool bPropagateToChildren; } visParams{ true, true };
                        mesh1p->process_event(fn, &visParams);
                    }
                    printf("[+] 1P mesh geri açıldı\n");
                }

                if (auto mesh3p = *(uobject**)((uintptr_t)character + offsets::mesh3p)) {
                    if (auto fn = uobject::find_object<uobject*>(crypt(L"Engine.PrimitiveComponent.SetVisibility"))) {
                        struct { bool bNewVisibility; bool bPropagateToChildren; } visParams{ false, true };
                        mesh3p->process_event(fn, &visParams);
                    }
                    printf("[+] 3P mesh gizlendi\n");
                }
            }

            if (globals::misc::disconnect_server && controllers)
            {
                controllers->disconnect_server();
                globals::misc::disconnect_server = false;

                
                return;
            }

            if (globals::misc::rmsdw) {
                SPOOF_FUNC
                    UPrimitiveComponent* negro = memory::read<UPrimitiveComponent*>(uintptr_t(pawn) + offsets::mesh1p);
                if (auto handmesh = character->GetOverlayMesh1P()) {
                    if (auto inventory = character->get_inventory()) {
                        if (auto weapon = inventory->get_current_equippable()) {
                            if (auto mesh1p = weapon->GetMesh1P()) {
                                std::string weapon_name = system::get_object_name((uobject*)G::MyWeapon).ToString();

                               
                                fvector wide_scale = {
                                    max(0.1f, globals::misc::arm_width),
                                    max(0.1f, globals::misc::arm_height),
                                    max(0.1f, globals::misc::arm_length)
                                };

                                
                                handmesh->SetRelativeScale3D(wide_scale);

                                uintptr_t fname_addr = reinterpret_cast<uintptr_t>(character) + 0xFB8;
                                if (!memory::IsValidPointer(fname_addr))
                                    return;

                                frotator rotation = { 90, 90, 0 };
                                fname attach_point_name = memory::read<fname>(fname_addr);

                               
                                if (weapon_name.find("AssaultRifle_AK_C") != std::string::npos) {
                                    mesh1p->AttachTo(handmesh, attach_point_name, (EAttachLocation)2, true);
                                    mesh1p->SetRelativeRotation(rotation);
                                    mesh1p->SetRelativeScale3D({ 1,1,1 });
                                }
                                else if (weapon_name.find("AssaultRifle_ACR_C") != std::string::npos) {
                                    mesh1p->AttachTo(handmesh, attach_point_name, (EAttachLocation)2, true);
                                    mesh1p->SetRelativeRotation(rotation);
                                    mesh1p->SetRelativeScale3D({ 1,1,1 });
                                }
                                else if (weapon_name.find("BoltSniper_C") != std::string::npos) {
                                    mesh1p->AttachTo(handmesh, attach_point_name, (EAttachLocation)2, true);
                                    mesh1p->SetRelativeRotation(rotation);
                                    mesh1p->SetRelativeScale3D({ 1,1,1 });
                                }
                                else if (weapon_name.find("AssaultRifle_Burst_C") != std::string::npos) {
                                    mesh1p->AttachTo(handmesh, attach_point_name, (EAttachLocation)2, true);
                                    mesh1p->SetRelativeRotation(rotation);
                                    mesh1p->SetRelativeScale3D({ 1,1,1 });
                                }
                                else if (weapon_name.find("AutomaticPistol_C") != std::string::npos) {
                                    mesh1p->AttachTo(handmesh, attach_point_name, (EAttachLocation)2, true);
                                    mesh1p->SetRelativeRotation(rotation);
                                    mesh1p->SetRelativeScale3D({ 1,1,1 });
                                }
                                else if (weapon_name.find("DMR_C") != std::string::npos) {
                                    mesh1p->AttachTo(handmesh, attach_point_name, (EAttachLocation)2, true);
                                    mesh1p->SetRelativeRotation(rotation);
                                    mesh1p->SetRelativeScale3D({ 1,1,1 });
                                }
                                else if (weapon_name.find("RevolverPistol_C") != std::string::npos) {
                                    mesh1p->AttachTo(handmesh, attach_point_name, (EAttachLocation)2, true);
                                    mesh1p->SetRelativeRotation(rotation);
                                    mesh1p->SetRelativeScale3D({ 1,1,1 });
                                }
                                else if (weapon_name.find("LugerPistol_C") != std::string::npos) {
                                    mesh1p->AttachTo(handmesh, attach_point_name, (EAttachLocation)2, true);
                                    mesh1p->SetRelativeRotation(rotation);
                                    mesh1p->SetRelativeScale3D({ 1,1,1 });
                                }
                                else if (weapon_name.find("SubMachineGun_MP5_C") != std::string::npos) {
                                    mesh1p->AttachTo(handmesh, attach_point_name, (EAttachLocation)2, true);
                                    mesh1p->SetRelativeRotation(rotation);
                                    mesh1p->SetRelativeScale3D({ 1,1,1 });
                                }
                                else if (weapon_name.find("BasePistol_C") != std::string::npos) {
                                    mesh1p->AttachTo(handmesh, attach_point_name, (EAttachLocation)2, true);
                                    mesh1p->SetRelativeRotation(rotation);
                                    mesh1p->SetRelativeScale3D({ 1,1,1 });
                                }
                                else if (weapon_name.find("LeverSniperRifle_C") != std::string::npos) {
                                    mesh1p->AttachTo(handmesh, attach_point_name, (EAttachLocation)2, true);
                                    mesh1p->SetRelativeRotation(rotation);
                                    mesh1p->SetRelativeScale3D({ 1,1,1 });
                                }
                                else if (weapon_name.find("DS_Gun_C") != std::string::npos) {
                                    mesh1p->AttachTo(handmesh, attach_point_name, (EAttachLocation)2, true);
                                    mesh1p->SetRelativeRotation(rotation);
                                    mesh1p->SetRelativeScale3D({ 1,1,1 });
                                }
                                else if (weapon_name.find("TrainingBotBasePistol_C") != std::string::npos) {
                                    mesh1p->AttachTo(handmesh, attach_point_name, (EAttachLocation)2, true);
                                    mesh1p->SetRelativeRotation(rotation);
                                    mesh1p->SetRelativeScale3D({ 1,1,1 });
                                }
                                else if (weapon_name.find("SawedOffShotgun_C") != std::string::npos) {
                                    mesh1p->AttachTo(handmesh, attach_point_name, (EAttachLocation)2, true);
                                    mesh1p->SetRelativeRotation(rotation);
                                    mesh1p->SetRelativeScale3D({ 1,1,1 });
                                }
                                else if (weapon_name.find("Vector_C") != std::string::npos) {
                                    mesh1p->AttachTo(handmesh, attach_point_name, (EAttachLocation)2, true);
                                    mesh1p->SetRelativeRotation(rotation);
                                    mesh1p->SetRelativeScale3D({ 1,1,1 });
                                }
                                else if (weapon_name.find("PumpShotgun_C") != std::string::npos) {
                                    mesh1p->AttachTo(handmesh, attach_point_name, (EAttachLocation)2, true);
                                    mesh1p->SetRelativeRotation(rotation);
                                    mesh1p->SetRelativeScale3D({ 1,1,1 });
                                }
                                else if (weapon_name.find("AutomaticShotgun_C") != std::string::npos) {
                                    mesh1p->AttachTo(handmesh, attach_point_name, (EAttachLocation)2, true);
                                    mesh1p->SetRelativeRotation(rotation);
                                    mesh1p->SetRelativeScale3D({ 1,1,1 });
                                }
                                else if (weapon_name.find("LightMachineGun_C") != std::string::npos) {
                                    mesh1p->AttachTo(handmesh, attach_point_name, (EAttachLocation)2, true);
                                    mesh1p->SetRelativeRotation(rotation);
                                    mesh1p->SetRelativeScale3D({ 1,1,1 });
                                }
                                else if (weapon_name.find("HeavyMachineGun_C") != std::string::npos) {
                                    mesh1p->AttachTo(handmesh, attach_point_name, (EAttachLocation)2, true);
                                    mesh1p->SetRelativeRotation(rotation);
                                    mesh1p->SetRelativeScale3D({ 1,1,1 });
                                }
                                else if (weapon_name.find("Ability_Melee_Base_C") != std::string::npos) {
                                    mesh1p->AttachTo(handmesh, attach_point_name, (EAttachLocation)2, true);
                                    mesh1p->SetRelativeRotation(rotation);
                                    mesh1p->SetRelativeScale3D({ 0.483117f, 1.0f, 1.0f });
                                }
                                else {
                                    mesh1p->AttachTo(handmesh, attach_point_name, (EAttachLocation)2, true);
                                    mesh1p->SetRelativeRotation(rotation);
                                    mesh1p->SetRelativeScale3D({ 1,1,1 });
                                }
                            }
                        }
                    }
                }
            }

            if (character && (globals::visuals::handchams || globals::visuals::wireframe_hands))
            {
                if (auto mesh1p = character->GetMesh1P())
                {
                    // Skeletal mesh olarak cast et
                    auto primComp = reinterpret_cast<uskeletalmeshcomponent*>(mesh1p);

                    int mat_count = primComp->get_num_materials();

                    for (int i = 0; i < mat_count; i++)
                    {
                        auto mat = primComp->get_material(i);
                        if (!mat) continue;

                        auto dyn_mat = reinterpret_cast<UMaterialInstanceDynamic*>(mat);

                        // 🎨 Hand Chams
                        if (globals::visuals::handchams)
                        {
                            flinearcolor cham_color(
                                globals::visuals::chams_color.r,
                                globals::visuals::chams_color.g,
                                globals::visuals::chams_color.b,
                                globals::misc::handchams_opacity
                            );

                            dyn_mat->set_vector_parameter_value2(fname(L"BaseColor"), cham_color);
                            dyn_mat->set_vector_parameter_value2(fname(L"EmissiveColor"), cham_color);
                        }

                        // 🔲 Wireframe
                        if (globals::visuals::wireframe_hands)
                        {
                            dyn_mat->set_scalar_parameter_value(fname(L"Wireframe"), 1.0f);
                        }
                    }
                }
            }
            if (globals::misc::aa)
            {
                SPOOF_FUNC
                    if (globals::misc::spinner && character && character->is_alive())
                    {
                        SPOOF_FUNC
                            float deltaX, deltaY;
                        controllers->GetInputMouseDelta(deltaX, deltaY);
                        float sensitivity = controllers->GetMouseSensitivity();
                        LocalCameraRotation.x += deltaY * sensitivity;
                        LocalCameraRotation.y += deltaX * sensitivity;
                        character->K2_SetActorRelativeRotation(fvector{ 0, LocalCameraRotation.y, 0 }, false, true);
                        controllers->set_control_rotation(fvector(271, controllers->get_control_rotation().y - globals::misc::spinvalue, 0));

                    }
            }

            fvector2d pos = { ((double)GetSystemMetrics(SM_CXSCREEN) / 2) - 500, ((double)GetSystemMetrics(SM_CYSCREEN) / 2) - 475 }; 

            tarray<ashootercharacter*> actors = blueprints::find_all_shooters_with_alliance(world, character, earesalliance::enemy, false, false);

            bool hasTarget = false;
            for (int32_t idx = 0; idx < actors.count; ++idx)
            {
                ashootercharacter* actor = actors[idx];
                if (!actor || actor == character) continue;

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

                if (globals::visuals::sk3let0n) {
                    SPOOF_FUNC
                    SPOOF_CALL(drawings::draw_skeleton)(controllers, mesh, memory::read<int32_t>((uintptr_t)mesh + offsets::bone_cout), defines::Name_Color, canvas);
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

                if (globals::visuals::h3althbar && actor->is_alive()) {
                    SPOOF_FUNC
                    static double last_health = actor->is_alive() ? actor->health() : 100;
                    double health = (actor->is_alive() ? actor->health() : 0);
                    double shield = (actor->is_alive() ? actor->shield() : 0);

                    double damage_taken = (last_health > health) ? (last_health - health) : 0;
                    last_health = health;

                    defines::health_color = health >= 75 ? defines::high_health :
                        (health <= 74 && health >= 44) ? defines::normal_health : defines::low_heath;

                    if (health <= 100) {
                        drawings::draw_health_and_shield(health, shield,
                            { root_location_2d.x, root_location_2d.y + 2.0 },
                            box_width + 12.5, box_height, distance, defines::health_color, canvas);
                    }
                }

                if (globals::visuals::snapl1ne && actor->is_alive()) {
                    SPOOF_FUNC
                    SPOOF_CALL(drawings::draw_snapline)(character, head_location_2d, defines::visuals_color, canvas);
                }

                if (globals::visuals::dormant && actor->is_alive()) {
                    SPOOF_FUNC
                    if (!controllers->dormant_server(actor)) continue;
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

                fvector2d bonePositions[14];

                /*if (globals::visuals::box || globals::visuals::box2d && actor->is_alive()) {
                    SPOOF_FUNC
                    SPOOF_CALL(DrawAdaptiveBoundingBox)(canvas, controllers, mesh, defines::visuals_color);
                }*/
                if (globals::visuals::chams && world && mesh)
                {
                    SPOOF_FUNC;

                    // Mesh Outline Mode
                    reinterpret_cast<uskeletalmeshcomponent* (__fastcall*)(uskeletalmeshcomponent*, int, bool)>(
                        memory::module_base + offsets::set_ares_outline_mode
                        )(mesh, 4, true);

                    flinearcolor finalColor;

                    if (globals::visuals::rainbow_chams)
                    {
                        float t = GetTickCount64() * 0.002f;
                        finalColor = flinearcolor(
                            (sinf(t + 0.5f) * 0.5f + 0.5f) * globals::visuals::chams_intensity,
                            (sinf(t + 2.0f) * 0.5f + 0.5f) * globals::visuals::chams_intensity,
                            (sinf(t + 4.0f) * 0.5f + 0.5f) * globals::visuals::chams_intensity,
                            1.0f
                        );
                    }
                    else
                    {
                        auto col = globals::visuals::chams_color;
                        float intensity = globals::visuals::chams_intensity;
                        finalColor = flinearcolor(
                            col.r * intensity,
                            col.g * intensity,
                            col.b * intensity,
                            1.0f // alpha sabit
                        );
                    }

                   
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
                    double delta_x = head_location_2d.x - screen_center_x;
                    double delta_y = head_location_2d.y - screen_center_y;

                    double distance = sqrtf(delta_x * delta_x + delta_y * delta_y);
                    double screen_distance = math::distance_2d(head_location_2d, { screen_center_x, screen_center_y });

                    if (distance < closest_distance && screen_distance < globals::aimbot::a1m_f0v) {
                        target_id = idx;
                        closest_distance = screen_distance;
                    }
                }
            }

            if (character && controllers) {
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
                            (void*)SetCameraCachePOVHook,
                            &hooks::SetCameraCachePOVOriginal
                        );
                    }

                    should_hook_gay = false;
                }
            }

            if (target_id != -1)
            {
                ashootercharacter* actor = actors[target_id];
                if (!actor || actor == character) continue;

                uskeletalmeshcomponent* mesh = actor->get_mesh();
                if (!mesh) continue;

                if (actor->is_alive()) {
                    SPOOF_FUNC
                    fvector2d head_screen;
                    fvector target = get_target_bone_matrix(mesh, globals::aimbot::a1m_b0ne);

                    if (!target.is_valid()) continue;

                    bool aim_key_pressed = GetAsyncKeyState(globals::aimbot::a1m_k3y);
                    bool visible_check = (globals::aimbot::v1sh_ch3ck && controllers->line_of_sight(actor)) || !globals::aimbot::v1sh_ch3ck;

                    if (aim_key_pressed && visible_check && actor->is_alive()) {
                        SPOOF_FUNC
                        fvector CameraPos = camera->get_camera_location();
                        fvector ControlRotation = controllers->get_control_rotation();
                        fvector vector_pos = target - CameraPos;
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

    } while (false);
    return draw_transition_o(viewportclient, canvas, a3);
}

    void call_draw_transition_hook(uintptr_t* viewportclient, ucanvas* _canvas, std::uintptr_t a3) {
        SPOOF_FUNC
        return reinterpret_cast<void(*)(uintptr_t * viewportclient, ucanvas * _canvas, std::uintptr_t a3, uintptr_t, void*)>(spoofcall_stub)(viewportclient, _canvas, a3, offsets::magic, (void*)hk_draw_transition);
    }

    void nti() {

        SPOOF_FUNC

            memory::module_base = memory::get_module(crypt(L"VALORANT-Win64-Shipping.exe"));
        if (!memory::module_base) {
            return;
        }

        (initialize_spoofcall)((uint8_t*)memory::module_base);

        variables.init_variables();

        uworld* UWorldClass = nullptr;
        uintptr_t* uworld_state_ptr = *(uintptr_t**)(memory::module_base + DecryptOffsetClear(offsets::State));
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

    //void nti() {

    //    SPOOF_FUNC

    //    memory::module_base = memory::get_module(crypt(L"VALORANT-Win64-Shipping.exe"));
    //    if (!memory::module_base) {
    //        return;
    //    }

    //    (initialize_spoofcall)((uint8_t*)memory::module_base);

    //    variables.init_variables();

    //    uworld* UWorldClass = nullptr;
    //    uintptr_t* uworld_state_ptr = *(uintptr_t**)(memory::module_base + DecryptOffsetClear(offsets::State));
    //    if (uworld_state_ptr) {
    //        UWorldClass = *(uworld**)uworld_state_ptr;
    //    }

    //    if (!UWorldClass) return;

    //    ugameinstance* gameinstance = memory::read<ugameinstance*>(uintptr_t(UWorldClass) + offsets::game_instance);
    //    if (!gameinstance) return;

    //    ulocalplayer* localplayer = gameinstance->local_players()[0];
    //    if (!localplayer) return;

    //    ugameviewportclient* viewportclient = localplayer->viewport_client();
    //    if (!viewportclient) return;

    //    aplayercontroller* LocalController = memory::read<aplayercontroller*>((uintptr_t)localplayer + offsets::local_controller);
    //    if (!LocalController) return;

    //    aplayercontroller* PlayerCameraManager = memory::read<aplayercontroller*>((uintptr_t)LocalController + offsets::cameramaneger);
    //    if (!PlayerCameraManager) return;

    //    uintptr_t Engine = memory::read<uintptr_t>((uintptr_t)gameinstance + offsets::engine);
    //    if (!Engine) return;

    //    static shadow_vmt1 viewport_hook;
    //    viewport_hook.g47ghf234h79g8f237h89<decltype(hooks::draw_transition_o)>(
    //        memory::module_base,
    //        (uintptr_t)viewportclient,
    //        99, // or 37 or 78 or 112
    //        (void*)hooks::hk_draw_transition,
    //        &hooks::draw_transition_o
    //    );
    //}

}