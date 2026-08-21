#include "functions.hpp"
#include "offsets.hpp"
#include "spoof.h"
#include <fstream>
#include <sstream>
#include <vector>


extern uworld* world;





void SetScalarParamOnMesh(uskeletalmeshcomponent* mesh, const wchar_t* paramName, float value)
{
	if (!mesh) return;

	static uobject* fn = uobject::find_object<uobject*>(
		L"Function Engine.SkinnedMeshComponent.SetScalarParameterValueOnMaterials"
	);
	if (!fn) return;

	struct
	{
		const wchar_t* ParameterName;
		float Value;
	} params;

	params.ParameterName = paramName;
	params.Value = value;

	mesh->ProcessEvent(fn, &params);
}


//void ApplyCustomJettTexture(ashootercharacter* MyShooter)
//{
//	if (!MyShooter) return;
//
//	auto mesh = MyShooter->get_core_mesh_3p();
//	if (!mesh) return;
//
//	
//	uobject* baseMat = uobject::StaticLoadObject(
//		L"/Game/Characters/Wushu/S0/3P/Materials/TP_Wushu_S0_MI.TP_Wushu_S0_MI"
//	);
//	if (!baseMat) return;
//
//	
//	utexture2d* myTex = system::import_file_as_texture2d(
//		world,
//		L"C:/TP_Wushu_S0_DF_00000.png"
//	);
//	if (!myTex) return;
//
//	
//	auto dynMatObj = mesh->create_and_set_material_instance_dynamic_from_material(0, baseMat);
//	auto dynMat = dynMatObj->cast<UMaterialInstanceDynamic>(); 
//	if (!dynMat) return;
//
//	
//	..dynMat->set_texture_parameter_value(fname(L"Albedo"), myTex);
//}

bool uobject::is_child_of(uclass* parent) {
	for (auto super = this->object_class(); super; super = super->super_class()) {
		if (super == parent) {
			return true;
		}
	}
	return false;
}

uclass* uobject::object_class() {
	SPOOF_FUNC
		return memory::read<uclass*>(class_ptr + offsets::object_class);
}

uclass* uclass::super_class() {
	SPOOF_FUNC
		return memory::read<uclass*>(class_ptr + offsets::super_class);
}

tarray<int> equippable_skin_data_asset::get_skin_levels() {
	SPOOF_FUNC
		return memory::read<tarray<int>>(std::uintptr_t(this) + offsets::get_skin_levels);
}

equippable_skin_data_asset* equippable_skin_inventory_model::get_skin_data_asset() {
	SPOOF_FUNC
		return memory::read<equippable_skin_data_asset*>(std::uintptr_t(this) + offsets::get_skin_data_asset);
}

uobject* equippable_skin_chroma_inventory_model::get_skin_chroma_data_asset() {
	SPOOF_FUNC
		return memory::read<uobject*>(std::uintptr_t(this) + offsets::get_skin_chroma_data_asset);
}

uobject* equippable_charm_instance_inventory_model::get_charm_data_asset() {
	SPOOF_FUNC
		return memory::read<uobject*>(std::uintptr_t(this) + offsets::get_charm_data_asset);
}

equippable_charm_level_data_asset* equippable_charm_instance_inventory_model::get_charm_level_data_asset() {
	SPOOF_FUNC
		return memory::read<equippable_charm_level_data_asset*>(std::uintptr_t(this) + offsets::get_charm_level_data_asset);
}

int equippable_charm_level_data_asset::get_charm_level() {
	SPOOF_FUNC
		return memory::read<int>(std::uintptr_t(this) + offsets::get_charm_level);
}

void uobject::ProcessEvent(void* function, void* params) {

	SPOOF_FUNC

		reinterpret_cast<void(*)(uobject*, uobject*, void*, uintptr_t, void*)>(
			spoofcall_stub
			)(this, static_cast<uobject*>(function), params, offsets::magic,
				reinterpret_cast<void*>(memory::module_base + offsets::process_event)
				);
}



void apply_hand_chams(ashootercharacter* shooter)
{
	if (!shooter) return;

	static const wchar_t* material_paths[] = {
		// 0: Esportsinvitational
		L"/Game/Equippables/_Core/Materials/SpecialMaterials/Emissive/1P_Weapon_Emissive_Gem_MI.1P_Weapon_Emissive_Gem_MI",

		L"/Game/Equippables/_Core/Materials/SpecialMaterials/Snowglobe/LightGlow/1P_Snowglobe_LightGlow_MI.1P_Snowglobe_LightGlow_MI",
		L"/Game/Equippables/_Core/Materials/SpecialMaterials/Esportsinvitational/1P_Esportsinvitational_Crystal_Melee_MI.1P_Esportsinvitational_Crystal_Melee_MI",

		// 2: Weapon Emissive Gem


		// 3: Hieroglyphs
		L"/Game/Equippables/_Core/Materials/SpecialMaterials/Hieroglyphs/1P_Hieroglyphs_Crystal_MI.1P_Hieroglyphs_Crystal_MI",

		// 4: Atlas Emissive Lv3
		L"/Game/Equippables/_Core/Materials/SpecialMaterials/Atlas/1P_Atlas_Emissive_Lv3_MI_v3.1P_Atlas_Emissive_Lv3_MI_v3"
	};

	int material_count = sizeof(material_paths) / sizeof(material_paths[0]);
	int selected_material = globals::misc::handchams_material_index1;


	if (selected_material < 0 || selected_material >= material_count)
		selected_material = 0;

	uobject* material = uobject::StaticLoadObject(material_paths[selected_material]);
	if (!material) return;

	auto mesh1p = memory::read<uskeletalmeshcomponent*>((uintptr_t)shooter + offsets::mesh1p);
	auto meshOverlay = memory::read<uskeletalmeshcomponent*>((uintptr_t)shooter + offsets::mesh1p_overlay);

	if (!mesh1p && !meshOverlay) return;

	flinearcolor color = globals::misc::handchams_color;
	color.r *= globals::misc::handchams_intensity;
	color.g *= globals::misc::handchams_intensity;
	color.b *= globals::misc::handchams_intensity;

	auto applyMaterial = [&](uskeletalmeshcomponent* mesh) {
		if (!mesh) return;
		int numMaterials = mesh->get_num_materials();
		for (int i = 0; i < numMaterials; i++) {
			auto dynMatObj = mesh->create_and_set_material_instance_dynamic_from_material(i, material);
			if (!dynMatObj) continue;

			auto mid = dynMatObj->cast<UMaterialInstanceDynamic>();
			if (!mid) continue;

			mid->set_vector_parameter_value1(string::string_to_name(L"Emissive Color"), color);
			mid->set_vector_parameter_value1(string::string_to_name(L"Inner Color"), color);
			mid->set_vector_parameter_value1(string::string_to_name(L"Diffuse Tint"), color);
		}
		};

	applyMaterial(mesh1p);
	applyMaterial(meshOverlay);
}

void moscawireframe(ashootercharacter* local_player) {
    if (!local_player || !local_player->is_alive()) return;

    static uobject* crystal_material = nullptr;
    if (!crystal_material) {
        crystal_material = uobject::static_load_object(nullptr, nullptr,
            L"/Game/Equippables/_Core/Materials/Weapon_Holo_Translucent_Mi.Weapon_Holo_Translucent_Mi");
        if (!crystal_material) return;
    }
    if (!memory::IsValidPointer((uintptr_t)crystal_material)) return;

    float R = globals::visuals::MoscaRed / 255.0f;
    float G = globals::visuals::MoscaGreen / 255.0f;
    float B = globals::visuals::MoscaBlue / 255.0f;
    float glow = globals::visuals::HandChamsGlow;
    float fresnel_base = globals::visuals::AlphaBasePower;
    float fade = globals::visuals::HandFadeStrength;

    flinearcolor main_color(R, G, B, 1.0f);
    float gray = (R + G + B) / 3.0f;
    flinearcolor hand_color(
        R + (gray - R) * fade * 0.6f,
        G + (gray - G) * fade * 0.6f,
        B + (gray - B) * fade * 0.6f,
        1.0f
    );

    auto apply_mesh1p = [&](uskeletalmeshcomponent* mesh) {
        if (!mesh || !memory::IsValidPointer((uintptr_t)mesh)) return;
        int num = mesh->get_num_materials();
        for (int i = 0; i < num; i++) {
            uobject* inst = mesh->create_and_set_material_instance_dynamic_from_material(i, crystal_material);
            if (!inst || !memory::IsValidPointer((uintptr_t)inst)) continue;
            UMaterialInstanceDynamic* mid = inst->cast<UMaterialInstanceDynamic>();
            if (!mid) continue;

            mid->set_vector_parameter_value1(string::string_to_name(L"BaseColor"), main_color);
            mid->set_vector_parameter_value1(string::string_to_name(L"Diffuse"), main_color);
            mid->set_vector_parameter_value1(string::string_to_name(L"Spec Color"), main_color);
            mid->set_vector_parameter_value1(string::string_to_name(L"Spec"), main_color);
            mid->set_scalar_parameter_value(string::string_to_name(L"FresnelPower"), fresnel_base);
            mid->set_scalar_parameter_value(string::string_to_name(L"Fresnel Exponent"), 1.5f);
            mid->set_scalar_parameter_value(string::string_to_name(L"Emissive Boost"), glow / 10.0f);
            mid->set_scalar_parameter_value(string::string_to_name(L"Opacity"), 1.0f);
            mid->set_scalar_parameter_value(string::string_to_name(L"Metallic Add"), 0.0f);
            mid->set_scalar_parameter_value(string::string_to_name(L"Roughness Add"), 0.25f);
            mid->set_scalar_parameter_value(string::string_to_name(L"SpecTile"), 1.0f);
            mid->set_scalar_parameter_value(string::string_to_name(L"AO Clamp"), 0.0f);
            mid->set_scalar_parameter_value(string::string_to_name(L"Use Normal Map"), 1.0f);
            mid->set_scalar_parameter_value(string::string_to_name(L"Use Diffuse Color"), 1.0f);
        }
        };

    auto apply_overlay = [&](uskeletalmeshcomponent* mesh) {
        if (!mesh || !memory::IsValidPointer((uintptr_t)mesh)) return;
        int num = mesh->get_num_materials();
        for (int i = 0; i < num; i++) {
            uobject* inst = mesh->create_and_set_material_instance_dynamic_from_material(i, crystal_material);
            if (!inst || !memory::IsValidPointer((uintptr_t)inst)) continue;
            UMaterialInstanceDynamic* mid = inst->cast<UMaterialInstanceDynamic>();
            if (!mid) continue;

            mid->set_vector_parameter_value1(string::string_to_name(L"BaseColor"), hand_color);
            mid->set_vector_parameter_value1(string::string_to_name(L"Diffuse"), hand_color);
            mid->set_vector_parameter_value1(string::string_to_name(L"Spec Color"), hand_color);
            mid->set_vector_parameter_value1(string::string_to_name(L"Spec"), hand_color);
            mid->set_scalar_parameter_value(string::string_to_name(L"FresnelPower"), 8.0f + fade * 4.0f);
            mid->set_scalar_parameter_value(string::string_to_name(L"Fresnel Exponent"), 4.0f + fade * 2.0f);
            mid->set_scalar_parameter_value(string::string_to_name(L"Emissive Boost"), 0.2f);
            mid->set_scalar_parameter_value(string::string_to_name(L"Opacity"), 0.9f);
            mid->set_scalar_parameter_value(string::string_to_name(L"Metallic Add"), 0.0f);
            mid->set_scalar_parameter_value(string::string_to_name(L"Roughness Add"), 0.7f + fade * 0.3f);
            mid->set_scalar_parameter_value(string::string_to_name(L"SpecTile"), 1.0f);
            mid->set_scalar_parameter_value(string::string_to_name(L"AO Clamp"), 0.0f);
            mid->set_scalar_parameter_value(string::string_to_name(L"Use Normal Map"), 1.0f);
            mid->set_scalar_parameter_value(string::string_to_name(L"Use Diffuse Color"), 1.0f);
        }
        };

    uskeletalmeshcomponent* mesh1p = local_player->GetMesh1P();
    uskeletalmeshcomponent* meshOverlay = local_player->GetOverlayMesh1P();

    if (mesh1p) apply_mesh1p(mesh1p);
    if (meshOverlay) apply_overlay(meshOverlay);
}
																												

void uobject::ProcessEvent(void* class_, uobject* function, void* params)
{
	SPOOF_FUNC

		reinterpret_cast<void(*)(void*, uobject*, void*, uintptr_t, void*)>(
			spoofcall_stub
			)(class_, function, params, offsets::magic,
				reinterpret_cast<void*>(memory::module_base + offsets::process_event)
				);
}

//void uobject::process_event(uobject* function, void* args) {
//
//	SPOOF_FUNC
//
//		try {
//		if (!memory::module_base) {
//			printf("[-] process_event failed: memory::module_base is null\n");
//			while (true);
//		}
//
//		if (!this || !function) {
//			printf("[-] process_event failed: 'this' or 'function' is null (this: 0x%p, function: 0x%p)\n", this, function);
//			while (true);
//		}
//
//		auto fn = reinterpret_cast<void(*)(uobject*, uobject*, void*, uintptr_t, void*)>(spoofcall_stub);
//		fn(this, function, args, 0x46C4660, (void*)(memory::module_base + offsets::process_event));
//	}
//	catch (const std::exception& e) {
//		printf("[-] Exception in process_event: %s\n", e.what());
//		printf("    this: 0x%p | function: 0x%p | args: 0x%p\n", this, function, args);
//		while (true);
//	}
//	catch (...) {
//		printf("[-] Unknown exception in process_event\n");
//		printf("    this: 0x%p | function: 0x%p | args: 0x%p\n", this, function, args);
//		while (true);
//	}
//}

//void uobject::process_event(uobject* function, void* args)
//{
//	SPOOF_FUNC
//
//		void** vtable = *reinterpret_cast<void***>(this);
//	if (!vtable)
//		return;
//
//	void(*fProcessEvent)(void*, void*, void*) = reinterpret_cast<decltype(fProcessEvent)>(vtable[0x53]);
//	if (!fProcessEvent)
//		return;
//
//	fProcessEvent(this, function, args);
//}

void uobject::process_event(uobject* function, void* args) {

	SPOOF_FUNC

		return reinterpret_cast<void(*)(uobject*, uobject*, void*, uintptr_t, void*)>(spoofcall_stub)(this, function, args, offsets::magic, (void*)(memory::module_base + offsets::process_event));
}

void uobject::process_event2(void* class_, uobject* function, void* params)
{
	SPOOF_FUNC

		return reinterpret_cast<void(*)(uobject*, void*, uobject*, void*, uintptr_t, void*)>(spoofcall_stub)(this, class_, function, params, offsets::magic, (void*)(memory::module_base + offsets::process_event));
}

uint64_t fmemory::malloc(int32_t size, uint32_t aligment) {
	SPOOF_FUNC
		return reinterpret_cast<uint64_t(__cdecl*)(uint64_t, int)>(memory::module_base + offsets::fmemory_malloc)(size, aligment);
}

//uint64_t fmemory::malloc(int32_t size, uint32_t alignment) {
//	void* target = reinterpret_cast<void*>(memory::module_base + offsets::fmemory_malloc);
//	return reinterpret_cast<uint64_t(*)(int32_t, uint32_t, uintptr_t, void*)>(spoofcall_stub)(
//		size, alignment, 0, target
//		);
//}

fstring system::get_object_name(uobject* object) {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetSystemLibrary.GetObjectName"));

	struct
	{
		uobject* object;
		fstring output;
	} params;

	params.object = { object };

	variables.kismet_system->process_event(function, &params);
	return params.output;
}

bool system::contains_string(const wchar_t* search_in, const wchar_t* sub_string, bool use_case, bool search_from_end) {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetStringLibrary.Contains"));

	struct {
		fstring search_in;
		fstring sub_string;
		bool use_case;
		bool search_from_end;
		bool return_value;
	} params = { search_in, sub_string, use_case , search_from_end };

	variables.kismet_string->process_event(function, &params);
	return params.return_value;
}

bool system::starts_with(const wchar_t* source, const wchar_t* prefix, const enum_as_byte<search_case>& search_case) {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetStringLibrary.StartsWith"));

	struct {
		fstring source;
		fstring prefix;
		std::uint8_t search_case;
		bool return_value;
	} params = { source, prefix, search_case.get() };

	variables.kismet_string->process_event(function, &params);

	return params.return_value;
}


void umaterial_instance::set_vector_parameter_value(fname ParameterName, flinearcolor Value) {
	static uobject* Function;
	if (!Function)
		Function = uobject::find_object<uobject*>(crypt(L"Engine.MaterialInstanceDynamic.SetVectorParameterValue"));

	struct
	{
		fname ParameterName;
		flinearcolor Value;
	} params;

	params.ParameterName = ParameterName;
	params.Value = Value;

	this->process_event(Function, &params);
}
void umaterial_instance::set_scalar_parameter_value(fname parameter_name, float value)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.MaterialInstanceDynamic.SetScalarParameterValue"));

	struct
	{
		fname parameter_name;
		float value;
	} params;

	params.parameter_name = parameter_name;
	params.value = value;

	this->process_event(function, &params);
}


uobject* system::get_outer_object(uobject* object) {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetSystemLibrary.GetOuterObject"));

	struct
	{
		uobject* object;
		uobject* output;
	} params;

	variables.kismet_system->process_event(function, &params);

	return params.output;
}

fname string::string_to_name(fstring string) {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetStringLibrary.Conv_StringToName"));;

	struct
	{
		fstring string;
		fname output;
	} params;

	params.string = string;

	variables.kismet_string->process_event(function, &params);

	return params.output;
}

fstring text::text_to_string(ftext string) {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetTextLibrary.Conv_TextToString"));

	struct
	{
		ftext text;
		fstring output;
	} params;

	params.text = string;

	variables.kismet_text->process_event(function, &params);

	return params.output;
}

ftext text::string_to_text(const fstring& InString)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetTextLibrary.Conv_StringToText"));

	struct
	{
		fstring InString;
		ftext ReturnValue;
	} params;

	params.InString = InString;

	variables.kismet_text->process_event(function, &params);

	return params.ReturnValue;
}

fstring text::fname_to_string(const fname& name) {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetStringLibrary.Conv_NameToString"));

	struct
	{
		fname InName;
		fstring ReturnValue;
	} params;

	params.InName = name;

	variables.kismet_string->process_event(function, &params);

	return params.ReturnValue;
}

ugameinstance* uworld::game_instance() {
	SPOOF_FUNC
		return memory::read<ugameinstance*>(class_ptr + offsets::game_instance);
}

tarray<ulocalplayer*> ugameinstance::local_players() {
	SPOOF_FUNC
		return memory::read<tarray<ulocalplayer*>>(class_ptr + offsets::local_players);
}

ugameviewportclient* ulocalplayer::viewport_client() {
	SPOOF_FUNC
		return memory::read<ugameviewportclient*>(class_ptr + offsets::viewport_client);
}
 uworld* uworld::getworld2()
{
	uintptr_t* UWorldRead_SECOND = memory::read<uintptr_t*>(memory::module_base + offsets::uworldstate); // wrong
	auto UWorld_RESULT_SECOND = memory::read<uworld*>(uintptr_t(UWorldRead_SECOND));
	return UWorld_RESULT_SECOND;
}
uworld* ugameviewportclient::get_world() {
	SPOOF_FUNC
		return memory::read<uworld*>(class_ptr + offsets::viewport_world);
}

ugameinstance* ugameviewportclient::get_gameinstance() {
	SPOOF_FUNC
		return memory::read<ugameinstance*>(class_ptr + offsets::viewport_gameinstance);
}

void ashootercharacter::get_firing_location_and_direction(fvector* loc, fvector* rot, bool apply_recoil)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetFiringLocationAndDirection"));

	struct
	{
		fvector location;
		fvector rotation;
		bool apply_recoil;
	} params;

	params.apply_recoil = apply_recoil;

	this->process_event(function, &params);

	*loc = params.location;
	*rot = params.rotation;
}
void ashootercharacter::get_firing_location_and_direction2(fvector* loc, FRotator* rot, bool apply_recoil)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetFiringLocationAndDirection"));

	struct
	{
		fvector location;
		FRotator rotation;
		bool apply_recoil;
	} params;

	params.apply_recoil = apply_recoil;

	this->process_event(function, &params);

	*loc = params.location;
	*rot = params.rotation;
}


//void ashootercharacter::get_firing_location_and_direction(fvector* loc, fvector* rot)
//{
//	static uobject* function = nullptr;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetFiringLocationAndDirection"));
//
//	struct
//	{
//		fvector location;
//		fvector rotation;
//	} params;
//
//	this->process_event(function, &params);
//
//	*loc = params.location;
//	*rot = params.rotation;
//}




void ashootercharacter::get_firing_location_and_direction_sd(fvector* Loc, fvector* Rot, bool bApplyRecoil) {
	static uobject* function;
	if (!function)
		function = this->StaticFindObject(0, 0, L"ShooterGame.ShooterCharacter.GetFiringLocationAndDirection", false);
	struct
	{
		fvector location;
		fvector rotation;
		bool bapplyrecoil;
	} params;

	params.bapplyrecoil = bApplyRecoil;

	this->ProcessEvent(this, function, &params);

	*Loc = params.location;
	*Rot = params.rotation;
}

tarray<ashootercharacter*> blueprints::find_all_shooters_with_alliance(uobject* context, ashootercharacter* viewer, earesalliance alliance, bool only_player, bool only_alive) {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterBlueprintLibrary.FindAllShooterCharactersWithAlliance"));

	struct
	{
		uobject* context;
		ashootercharacter* viewer;
		earesalliance alliance;
		bool only_player;
		bool only_alive;
		tarray<ashootercharacter*> output;
	} params;

	params.context = context;
	params.viewer = viewer;
	params.alliance = alliance;
	params.only_player = only_player;
	params.only_alive = only_alive;

	variables.blueprints->process_event(function, &params);

	return params.output;
}

tarray<ashootercharacter*> blueprints::find_all_game_objects(uworld* world_context) {
	static uobject* function = 0; if (!function) function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterBlueprintLibrary.FindAllGameObjects"));

	if (function == nullptr || world_context == nullptr) return {};

	struct {
		uworld* world_context;
		tarray<ashootercharacter*> return_value;
	} params = { world_context };

	variables.blueprints->process_event(function, &params);
	return params.return_value;
}

aplayercontroller* blueprints::get_local_controller(uobject* context) {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterBlueprintLibrary.GetLocalController"));

	struct {
		uobject* world_context;
		aplayercontroller* return_value;
	} params = { context };

	variables.blueprints->process_event(function, &params);

	return params.return_value;
}

aplayercontroller* blueprints::get_player_controller(uobject* context)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterBlueprintLibrary.GetFirstLocalPlayerController"));

	struct
	{
		uobject* context;
		aplayercontroller* output;
	} params;

	params.context = context;

	variables.blueprints->process_event(function, &params);

	return params.output;
}

void game_statics::get_all_actors_of_class(uobject* context, uobject* _class, tarray<gameobject*>* output) {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.GameplayStatics.GetAllActorsOfClass"));

	struct
	{
		uobject* context;
		uobject* _class;
		tarray<gameobject*> output;
	} params;

	params.context = context;
	params._class = _class;

	variables.gameplay_statics->process_event(function, &params);

	*output = params.output;
}

void content_library::apply_skin(currentequippable* equippable, uobject* skin_asset, uobject* chroma_asset, int level, uobject* charm_data, int buddie_level) {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ContentLibrary.ApplySkin"));

	struct
	{
		currentequippable* equippable;
		uobject* skin_asset;
		uobject* chroma_asset;
		int level;
		uobject* charm_data;
		int buddie_level;
	} params;

	params.equippable = equippable;
	params.skin_asset = skin_asset;
	params.chroma_asset = chroma_asset;
	params.level = level;
	params.charm_data = charm_data;
	params.buddie_level = buddie_level;

	variables.content_library->process_event(function, &params);
}

void content_library::clear_weapon_components(currentequippable* equippable) {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ContentLibrary.ClearWeaponComponents"));

	struct
	{
		currentequippable* equippable;
	} params;

	params.equippable = equippable;

	variables.content_library->process_event(function, &params);
}

ashootercharacter* aplayercontroller::get_shooter_character() {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerController.GetShooterCharacter"));

	struct
	{
		ashootercharacter* output;
	} params{};

	this->process_event(function, &params);

	return params.output;
}

void aplayercontroller::HandleThreadedChatManagerSentInGameMessage(const fstring& Msg, int ChatMode)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.AresPlayerController.HandleThreadedChatManagerSentInGameMessage");

	struct
	{
		fstring Msg;
		int ChatMode;
	} Args;

	Args.Msg = Msg;
	Args.ChatMode = ChatMode;

	this->process_event(function, &Args);
}

bool ashootercharacter::can_jump() {
	uobject* function = uobject::find_object<uobject*>(crypt(L"Engine.Character.CanJump"));

	bool return_value;
	this->process_event(function, &return_value);

	return return_value;
}

bool ashootercharacter::can_jump1()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Character.CanJump"));

	struct
	{
		bool return_value;
	} params;

	this->process_event(function, &params);

	return params.return_value;
}

void ashootercharacter::set_crouch_time_override(float override_value)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.SetCrouchTimeOverride"));

	struct
	{
		float override;
	} params;

	params.override = override_value;

	this->process_event(function, &params);
}

void ashootercharacter::ClientFly()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.ClientFly"));

	this->process_event(function, nullptr);
}

void ashootercharacter::GiveUltimate()
{
	uobject* Function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCheatManager.GiveUltimate"));
	if (!Function)
	{
		return;
	}
	struct
	{
	}Parameters;
	Function->ProcessEvent(this, Function, &Parameters);
	return;
}

void ashootercharacter::GameModeCheat(const fstring& CheatString)
{
	uobject* Function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCheatManager.GameModeCheat"));
	if (!Function)
	{
		return;
	}
	struct
	{
		fstring CheatString;
		ashootercharacter* return_value;

	}Parameters;

	Parameters.CheatString = CheatString;

	Function->ProcessEvent(this, Function, &Parameters);
	return;
}

void ashootercharacter::Heal(int32_t Amount)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCheatManager.Heal"));

	struct
	{
		int32_t Amount;
	} params;

	params.Amount = Amount;

	this->process_event(function, &params);
}

void ashootercharacter::MoveRight(float Val)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.MoveRight"));

	struct
	{
		float Val;
	} params;

	params.Val = Val;

	this->process_event(function, &params);
}

void ashootercharacter::ForceStrafe(fvector& PlayerRelativeInputDirection, float ChangeDirectionTime)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.ForceStrafe"));

	struct
	{
		fvector PlayerRelativeInputDirection;
		float ChangeDirectionTime;
	} params;

	params.PlayerRelativeInputDirection = PlayerRelativeInputDirection;
	params.ChangeDirectionTime = ChangeDirectionTime;

	this->process_event(function, &params);
}

void ashootercharacter::Hide3P(bool should_hide)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCheatManager.Hide3P"));

	struct
	{
		bool should_hide;
	} params;

	params.should_hide = should_hide;

	this->process_event(function, &params);
}

//bool ashootercharacter::is_input_key_down(fkey key) {
//	uobject* function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.IsInputKeyDown"));
//
//	struct {
//		fkey key;
//		bool return_value;
//	} params = { key };
//
//	this->process_event(function, &params);
//
//	return params.return_value;
//}

bool ashootercharacter::was_input_key_just_pressed(fkey key) {
	uobject* function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.WasInputKeyJustPressed"));

	struct {
		fkey key;
		bool return_value;
	} params = { key };

	this->process_event(function, &params);

	return params.return_value;
}

pregame_view_controller* aplayercontroller::get_pregame_view_controller() {
	return memory::read<pregame_view_controller*>(std::uintptr_t(this) + offsets::pregame_view_controller);
}

bool aplayercontroller::dormant_server(ashootercharacter* actor) {
	return memory::read<bool>(reinterpret_cast<uintptr_t>(actor) + offsets::dormant_server);
}

//bool ashootercharacter::is_input_key_down(fkey key)
//{
//	static uobject* function;
//
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.IsInputKeyDown"));
//
//	struct
//	{
//		fkey key;
//		bool return_value;
//	} params = { key };
//
//	this->process_event(function, &params);
//
//	return params.return_value;
//}

bool aplayercontroller::is_input_key_down(fkey key)
{
	static uobject* function;

	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.IsInputKeyDown"));

	struct
	{
		fkey key;
		bool return_value;
	} params = { key };

	this->process_event(function, &params);

	return params.return_value;
}

void aplayercontroller::disconnect_server() {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerController.DisconnectFromServer"));

	this->process_event(function, nullptr);
}

void ares_instance::ConnectToServer(FConnectToServerDetails& Details)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresClientGameInstance.ConnectToServer"));

	struct {
		FConnectToServerDetails Details;
	} params;

	params.Details = Details;

	variables.ares_instance->process_event(function, &params);
}

void ares_instance::DisconnectFromServer()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresClientGameInstance.DisconnectFromServer"));

	variables.ares_instance->process_event(function, nullptr);
}

void ashootercharacter::ShowUI(int32_t Show)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresCheatManager.ShowUI"));

	if (function)
	{
		struct
		{
			int32_t Show;
		} params;

		params.Show = Show;

		this->process_event(function, &params);
	}
}

void ashootercharacter::ShowUI1(bool Show)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.PregameCheatManager.ShowUI"));

	if (function)
	{
		struct
		{
			bool Show;
		} params;

		params.Show = Show;

		this->process_event(function, &params);
	}
}

void ashootercharacter::ShowUI2(int32_t Show)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ReplayPlayerController.ShowUI"));

	if (function)
	{
		struct
		{
			int32_t Show;
		} params;

		params.Show = Show;

		this->process_event(function, &params);
	}
}

bool ares_instance::should_allow_leave_match() {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresClientGameInstance.ShouldAllowLeaveMatch"));

	struct {
		bool return_value;
	} params;

	if (globals::misc::fl25)
	{
		return true;
	}

	variables.ares_instance->process_event(function, &params);

	return params.return_value;
}

void pregame_view_controller::UnlockAllCharacters() {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.PregameCheatManager.UnlockAllCharacters"));

	this->process_event(function, nullptr);
}

void pregame_view_controller::CheatUnlockAllCharacters() {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.PregamePlayerController.CheatUnlockAllCharacters"));

	this->process_event(function, nullptr);
}

void pregame_view_controller::PregameExit() {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.PregameCheatManager.PregameExit"));

	this->process_event(function, nullptr);
}

void pregame_view_controller::PregameStart() {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.PregameCheatManager.PregameStart"));

	this->process_event(function, nullptr);
}

void pregame_view_controller::SetConfigurationValue(const fstring& Name, const fstring& Value) {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.PregameCheatManager.SetConfigurationValue"));

	struct {
		fstring Name;
		fstring Value;
	} params;
	params.Name = Name;
	params.Value = Value;

	this->process_event(function, &params);
}

void pregame_view_controller::ShowUI(bool Show) {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.PregameCheatManager.ShowUI"));

	struct {
		bool Show;
	} params;
	params.Show = Show;

	this->process_event(function, &params);
}

void pregame_view_controller::PickSide(const fname& Side) {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.PregameViewController.PickSide"));

	struct {
		fname Side;
	} params;
	params.Side = Side;

	this->process_event(function, &params);
}

void pregame_view_controller::OverrideCharacter(const fstring& CharacterPath) {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.PregameCharacterSelectSpawner.OverrideCharacter"));

	struct {
		fstring CharacterPath;
	} params;
	params.CharacterPath = CharacterPath;

	this->process_event(function, &params);
}

void pregame_view_controller::SetCharacter(const uobject* Character) {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.PregameCharacterSelectSpawner.SetCharacter"));

	struct {
		const uobject* Character;
	} params;
	params.Character = Character;

	this->process_event(function, &params);
}

void pregame_view_controller::UpdateModel() {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.PregameCharacterSelectSpawner.UpdateModel"));

	this->process_event(function, nullptr);
}


bool aplayercontroller::line_of_sight(ashootercharacter* enemy) {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Controller.LineOfSightTo"));

	struct {
		ashootercharacter* Enemy;
		fvector ViewPoint;
		bool bAlternateCheck;
		bool ReturnValue;
	} params;
	params.Enemy = enemy;
	params.ViewPoint = fvector(0, 0, 0);
	params.bAlternateCheck = false;

	this->process_event(function, &params);
	return params.ReturnValue;
}



void ashootercharacter::reset_character_materials_internal(uskeletalmeshcomponent* mesh_to_reset)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.ShooterCharacter.ResetCharacterMaterials");

	if (!function) return;

	struct {
		uskeletalmeshcomponent* mesh_to_reset;
	} params;

	params.mesh_to_reset = mesh_to_reset;

	this->process_event(function, &params);
}


uskeletalmeshcomponent* currentequippable::GetMesh3P()
{
	uobject* function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresEquippable.GetMesh3P").decrypt());

	struct
	{
		uskeletalmeshcomponent* Out;
	}Parameters;
	function->ProcessEvent(this, function, &Parameters);
	return Parameters.Out;
}

uskeletalmeshcomponent* ashootercharacter::GetCosmeticMesh3P()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetCosmeticMesh3P"));

	struct
	{
		uskeletalmeshcomponent* ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

uskeletalmeshcomponent* ashootercharacter::get_core_mesh_3p()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetCoreMesh3P"));

	struct
	{
		uskeletalmeshcomponent* ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

uskeletalmeshcomponent* ashootercharacter::mesh3p() {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetCoreMesh3P"));

	struct
	{
		uskeletalmeshcomponent* output;
	} params;

	this->process_event(function, &params);

	return params.output;
}

bool ashootercharacter::IsZoomed()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.IsZoomed"));

	struct
	{
		bool ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

bool ashootercharacter::IsInvisibleToActor(const uobject* Actor)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.IsInvisibleToActor"));

	struct
	{
		const uobject* Actor;
		bool ReturnValue;
	} params;

	params.Actor = Actor;

	this->process_event(function, &params);

	return params.ReturnValue;
}

bool ashootercharacter::IsAIControlled()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.IsAIControlled"));

	struct
	{
		bool ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

bool ashootercharacter::Is3PCameraEnabled()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.Is3PCameraEnabled"));

	struct
	{
		bool ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

bool ashootercharacter::GetCrouchHeld()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetCrouchHeld"));

	struct
	{
		bool ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

void ashootercharacter::crouch(bool bclientsimulation)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Function Engine.Character.Crouch"));

	struct
	{
		bool bclientsimulation;
	} params;

	params.bclientsimulation = bclientsimulation;

	this->process_event(function, &params);
}


float ashootercharacter::ReduceShield(float Amount)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.ReduceShield"));

	struct
	{
		float Amount;
		float ReturnValue;
	} params;

	params.Amount = Amount;

	this->process_event(function, &params);

	return params.ReturnValue;
}

bool ashootercharacter::GetPlayer(FMMRPlayer* OutPlayer)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.MMRManager.GetPlayer"));

	struct
	{
		FMMRPlayer OutPlayer;
		bool ReturnValue;
	} params;

	this->process_event(function, &params);

	if (OutPlayer)
		*OutPlayer = params.OutPlayer;

	return params.ReturnValue;
}

bool ashootercharacter::GetCompetitiveUpdateForMatch(const fstring& MatchID, FMMRMatchInfo* OutMatchInfo)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.MMRManager.GetCompetitiveUpdateForMatch"));

	struct
	{
		fstring MatchID;
		FMMRMatchInfo OutMatchInfo;
		bool ReturnValue;
	} params;

	params.MatchID = MatchID;

	this->process_event(function, &params);

	if (OutMatchInfo)
		*OutMatchInfo = params.OutMatchInfo;

	return params.ReturnValue;
}

int32_t ashootercharacter::GetCurrentRank()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.RankedAbilityChargeComponent.GetCurrentRank"));

	struct
	{
		int32_t ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

bool ashootercharacter::IsLeftHanded()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.IsLeftHanded"));

	struct
	{
		bool ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

//FRotator ashootercharacter::GetAimOffsets()
//{
//	static uobject* function;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetAimOffsets"));
//
//	struct
//	{
//		FRotator ReturnValue;
//	} params;
//
//	this->process_event(function, &params);
//
//	return params.ReturnValue;
//}

fvector ashootercharacter::GetSocketLocation(fname InSocketName)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.SceneComponent.GetSocketLocation"));

	struct
	{
		fname InSocketName;
		fvector ReturnValue;
	} params;

	params.InSocketName = InSocketName;

	this->process_event(function, &params);

	return params.ReturnValue;
}

fvector currentequippable::GetSocketLocation_wp(fname InSocketName)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.SceneComponent.GetSocketLocation"));

	struct
	{
		fname InSocketName;
		fvector ReturnValue;
	} params;

	params.InSocketName = InSocketName;

	this->process_event(function, &params);

	return params.ReturnValue;
}

/*bool uobject::LineTraceSingle(uobject* WorldContextObject, fvector& Start, fvector& End, ETraceTypeQuery TraceChannel, bool bTraceComplex, EDrawDebugTrace DrawDebugType, FHitResult& OutHit, bool bIgnoreSelf, flinearcolor& TraceColor, flinearcolor& TraceHitColor, float DrawTime)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetSystemLibrary.LineTraceSingle"));

		struct
	{
		uobject* WorldContextObject;
		fvector Start;
		fvector End;
		ETraceTypeQuery TraceChannel;
		bool bTraceComplex;
		EDrawDebugTrace DrawDebugType;
		FHitResult OutHit;
		bool bIgnoreSelf;
		flinearcolor TraceColor;
		flinearcolor TraceHitColor;
		float DrawTime;
		bool ReturnValue;
	} params;

	params.WorldContextObject = WorldContextObject;
	params.Start = Start;
	params.End = End;
	params.TraceChannel = TraceChannel;
	params.bTraceComplex = bTraceComplex;
	params.DrawDebugType = DrawDebugType;
	params.bIgnoreSelf = bIgnoreSelf;
	params.TraceColor = TraceColor;
	params.TraceHitColor = TraceHitColor;
	params.DrawTime = DrawTime;

	variables.kismet_system->process_event(function, &params);

	OutHit = params.OutHit;
	return params.ReturnValue;
}

void uobject::DrawDebugLine(uobject* WorldContextObject, fvector& LineStart, fvector& LineEnd, flinearcolor& LineColor, float Duration, float Thickness)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetSystemLibrary.DrawDebugLine"));

		struct
	{
		uobject* WorldContextObject;
		fvector LineStart;
		fvector LineEnd;
		flinearcolor LineColor;
		float Duration;
		float Thickness;
	} params;

	params.WorldContextObject = WorldContextObject;
	params.LineStart = LineStart;
	params.LineEnd = LineEnd;
	params.LineColor = LineColor;
	params.Duration = Duration;
	params.Thickness = Thickness;

	variables.kismet_system->process_event(function, &params);
}

void uobject::DrawDebugPlane(uobject* WorldContextObject, const fplane& PlaneCoordinates, const fvector& Location, float Size, const flinearcolor& PlaneColor, float Duration)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetSystemLibrary.DrawDebugPlane"));

		struct
	{
		uobject* WorldContextObject;
		fplane PlaneCoordinates;
		fvector Location;
		float Size;
		flinearcolor PlaneColor;
		float Duration;
	} params;

	params.WorldContextObject = WorldContextObject;
	params.PlaneCoordinates = PlaneCoordinates;
	params.Location = Location;
	params.Size = Size;
	params.PlaneColor = PlaneColor;
	params.Duration = Duration;

	variables.kismet_system->process_event(function, &params);
}*/

fvector ashootercharacter::RandomUnitVectorInConeInDegrees(const fvector& ConeDir, float ConeHalfAngleInDegrees)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetMathLibrary.RandomUnitVectorInConeInDegrees"));

	struct
	{
		fvector ConeDir;
		float ConeHalfAngleInDegrees;
		fvector ReturnValue;
	} params;

	params.ConeDir = ConeDir;
	params.ConeHalfAngleInDegrees = ConeHalfAngleInDegrees;

	this->process_event(function, &params);

	return params.ReturnValue;
}

tarray<TWeakObjectPtr<uobject>> ashootercharacter::GetAllFocusProjectiles()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetAllFocusProjectiles"));

	struct
	{
		tarray<TWeakObjectPtr<uobject>> ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

fstring ashootercharacter::GetWwisePerspective()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetWwisePerspective"));

	struct
	{
		fstring ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

//bool ashootercharacter::GetFiringLocationAndDirection(fvector* Location, FRotator* Rotation, bool bApplyRecoil)
//{
//	static uobject* function;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetFiringLocationAndDirection"));
//
//	struct
//	{
//		fvector Location;
//		FRotator Rotation;
//		bool bApplyRecoil;
//		bool ReturnValue;
//	} params;
//
//	params.bApplyRecoil = bApplyRecoil;
//
//	this->process_event(function, &params);
//
//	if (Location)
//		*Location = params.Location;
//	if (Rotation)
//		*Rotation = params.Rotation;
//
//	return params.ReturnValue;
//}

EAresMovementType ashootercharacter::get_movement_type()
{
	static uobject* function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetMovementType"));

	if (function)
	{
		struct
		{
			EAresMovementType ReturnValue;
		} params;

		this->process_event(function, &params);
		return params.ReturnValue;
	}
	return EAresMovementType::Walking;
}

fvector ashootercharacter::GetPawnViewLocation()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetPawnViewLocation"));

	struct
	{
		fvector ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

fvector ashootercharacter::GetActorForwardVector()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.GetActorForwardVector"));

	struct
	{
		fvector ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

fvector ashootercharacter::GetActorRightVector()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.GetActorRightVector"));

	struct
	{
		fvector ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

fvector ashootercharacter::GetActorUpVector()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.GetActorUpVector"));

	struct
	{
		fvector ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}


bool ashootercharacter::K2_TeleportTo(const fvector& DestLocation, const frotator& DestRotation)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.K2_TeleportTo"));

	struct {
		fvector DestLocation;
		frotator DestRotation;
		bool ReturnValue;
	} params;

	params.DestLocation = DestLocation;
	params.DestRotation = DestRotation;

	this->process_event(function, &params);

	return params.ReturnValue;
}

void ashootercharacter::GetActorEyesViewPoint(fvector* OutLocation, frotator* OutRotation)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.GetActorEyesViewPoint"));

	struct
	{
		fvector OutLocation;
		frotator OutRotation;
	} params;

	this->process_event(function, &params);

	if (OutLocation)
		*OutLocation = params.OutLocation;
	if (OutRotation)
		*OutRotation = params.OutRotation;
}

fvector ashootercharacter::GetVelocity()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.GetVelocity"));

	struct
	{
		fvector ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

fvector  ashootercharacter::GetActorScale3D() {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.GetActorScale3D"));

	struct {
		fvector ReturnValue;
	} params;

	this->process_event(function, &params);
	return params.ReturnValue;
}

void ashootercharacter::SetActorScale3D(const fvector& NewScale3D)
{
	static uobject* function = nullptr;

	if (function == nullptr)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.SetActorScale3D"));

	struct {
		fvector NewScale3D;
	} params;

	params.NewScale3D = NewScale3D;

	this->process_event(function, &params);
}



void uskeletalmeshcomponent::SetRelativeScale3D(fvector NewScale3D)
{
	static uobject* function = nullptr;

	if (function == nullptr)
		function = uobject::find_object<uobject*>(crypt(L"Engine.SceneComponent.SetRelativeScale3D"));

	struct {
		fvector NewScale3D;
	} params;

	params.NewScale3D = NewScale3D;

	this->process_event(function, &params);
}

fvector ashootercharacter::get_actor_relative_scale3d() {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.GetActorRelativeScale3D"));

	struct {
		fvector return_value;
	} params;

	this->process_event(function, &params);
	return params.return_value;
}

void UProceduralMeshComponent::SetRelativeRotation(FRotator NewRotation, bool bSweep, bool bTeleport)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.SceneComponent.K2_SetRelativeRotation"));

	struct {
		FRotator NewRotation;
		bool bSweep;
		FHitResult SweepHitResult;
		bool bTeleport;
	} params;
	params.NewRotation = NewRotation;
	params.bSweep = bSweep;
	params.SweepHitResult = FHitResult();
	params.bTeleport = bTeleport;
	this->process_event(function, &params);
}

void UProceduralMeshComponent::SetRelativeScale3D(fvector NewScale3D)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.SceneComponent.SetRelativeScale3D"));

	struct {
		fvector NewScale3D;
	} params;
	params.NewScale3D = NewScale3D;
	this->process_event(function, &params);
}

void UProceduralMeshComponent::SetRelativeLocation(fvector NewLocation, bool bSweep, bool bTeleport)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.SceneComponent.K2_SetRelativeLocation"));

	struct {
		fvector NewLocation;
		bool bSweep;
		FHitResult SweepHitResult;
		bool bTeleport;
	} params;
	params.NewLocation = NewLocation;
	params.bSweep = bSweep;
	params.SweepHitResult = FHitResult();
	params.bTeleport = bTeleport;
	this->process_event(function, &params);
}

void UProceduralMeshComponent::RegisterComponent()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.ActorComponent.RegisterComponent"));
	this->process_event(function, nullptr);
}

void UProceduralMeshComponent::SetVisibility(bool bNewVisibility, bool bPropagateToChildren)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.SceneComponent.SetVisibility"));

	struct {
		bool bNewVisibility;
		bool bPropagateToChildren;
	} params;
	params.bNewVisibility = bNewVisibility;
	params.bPropagateToChildren = bPropagateToChildren;
	this->process_event(function, &params);
}

bool UProceduralMeshComponent::K2_AttachToComponent(uobject* Parent, fname SocketName, int LocationRule, int RotationRule, int ScaleRule, bool bWeldSimulatedBodies)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.SceneComponent.K2_AttachToComponent"));

	struct {
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
	this->process_event(function, &params);
	return params.ReturnValue;
}


void ashootercharacter::set_actor_relative_scale3d(const fvector& new_relative_scale) {

	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.SetActorRelativeScale3D"));

	struct {
		fvector new_relative_scale;
	} params;

	params.new_relative_scale = new_relative_scale;

	this->process_event(function, &params);
}


float ashootercharacter::GetLifeSpan() {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.GetLifeSpan"));

	struct {
		float ReturnValue;
	} params;

	this->process_event(function, &params);
	return params.ReturnValue;
}

void ashootercharacter::SetLifeSpan(float InLifespan) {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.SetLifeSpan"));

	struct {
		float InLifespan;
	} params;

	params.InLifespan = InLifespan;

	this->process_event(function, &params);
}

void ashootercharacter::set_owner(ashootercharacter* new_owner)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Function Engine.Actor.SetOwner"));

	struct
	{
		ashootercharacter* new_owner;
	} params;

	params.new_owner = new_owner;

	this->process_event(function, &params);
}


void ashootercharacter::apply_glow(ashootercharacter* actor, bool enable) {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PrimitiveComponent.SetRenderCustomDepth"));

	struct { bool bValue; } params;
	params.bValue = enable;

	actor->process_event(function, &params);
} // ⬅️ burası kapandı

// ⬇️ bundan sonra yeni fonksiyon
void ApplyGlow(uobject* mesh, float intensity, flinearcolor color) {
	if (!mesh)
		return;

	// Fresnel intensity
	if (auto fn = uobject::find_object<uobject*>(crypt(L"Engine.MeshComponent.SetScalarParameterValueOnMaterials"))) {
		struct { wchar_t* ParamName; float Value; } params{ (wchar_t*)L"FresnelIntensity", intensity };
		mesh->process_event(fn, &params);
	}

	// Fresnel color
	if (auto fn = uobject::find_object<uobject*>(crypt(L"Engine.MeshComponent.SetVectorParameterValueOnMaterials"))) {
		struct { wchar_t* ParamName; flinearcolor Value; } params{ (wchar_t*)L"FresnelColor", color };
		mesh->process_event(fn, &params);
	}
}


bool ashootercharacter::GetHiddenInGame() {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.GetHiddenInGame"));

	struct {
		bool ReturnValue;
	} params;

	this->process_event(function, &params);
	return params.ReturnValue;
}

void ashootercharacter::DisableInput(aplayercontroller12* PlayerController) {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.DisableInput"));

	struct {
		aplayercontroller12* PlayerController;
	} params;

	params.PlayerController = PlayerController;

	this->process_event(function, &params);
}

void ashootercharacter::EnableInput(aplayercontroller12* PlayerController) {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.EnableInput"));

	struct {
		aplayercontroller12* PlayerController;
	} params;

	params.PlayerController = PlayerController;

	this->process_event(function, &params);
}

void ashootercharacter::set_replicates(bool in_replicates) {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.SetReplicates"));

	struct {
		bool in_replicates;
	} params;

	params.in_replicates = in_replicates;

	this->process_event(function, &params);
}

ftransform ashootercharacter::get_transform() {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.GetTransform"));

	struct {
		ftransform return_value;
	} params;

	this->process_event(function, &params);
	return params.return_value;
}

float ashootercharacter::k2_get_timer_remaining_time(uobject* object, const fstring& function_name) {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetSystemLibrary.K2_GetTimerRemainingTime"));

	struct {
		uobject* object;
		fstring function_name;
		float return_value;
	} params;

	params.object = object;
	params.function_name = function_name;

	variables.kismet_system->process_event(function, &params);
	return params.return_value;
}

ftimerhandle ashootercharacter::k2_get_life_span_timer() {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.K2_GetLifeSpanTimer"));

	struct {
		ftimerhandle return_value;
	} params;

	this->process_event(function, &params);
	return params.return_value;
}

void ashootercharacter::teleport_actor(ashootercharacter* actor, const fvector& dest_location, const frotator& dest_rotation) {
	if (actor) {
		uobject* function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.K2_TeleportTo"));
		if (function) {
			struct {
				fvector DestLocation;
				frotator DestRotation;
				bool ReturnValue;
			} params;

			params.DestLocation = dest_location;
			params.DestRotation = dest_rotation;

			this->process_event(function, &params);
		}
	}
}

void ashootercharacter::TearOff() {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.TearOff"));

	this->process_event(function, nullptr);
}

void ashootercharacter::UserConstructionScript() {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.UserConstructionScript"));

	this->process_event(function, nullptr);
}

bool ashootercharacter::GetActorEnableCollision() {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.GetActorEnableCollision"));

	struct {
		bool ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

void ashootercharacter::SetActorEnableCollision(bool bNewActorEnableCollision) {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.SetActorEnableCollision"));

	struct {
		bool bNewActorEnableCollision;
	} params;

	params.bNewActorEnableCollision = bNewActorEnableCollision;

	this->process_event(function, &params);
}

uaccountxpmanager* ashootercharacter::get_account_xp_manager(uworld* world) {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AccountXPManager.Get"));

	struct {
		uworld* FromWorld;
		uaccountxpmanager* ReturnValue;
	} params;

	params.FromWorld = world;

	this->process_event(function, &params);

	return params.ReturnValue;
}

int32_t ashootercharacter::get_level_max_xp(uaccountxpmanager* xp_manager) {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AccountXPManager.GetLevelMaxXP"));

	struct {
		int32_t ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

int32_t ashootercharacter::get_win_of_day_ap(uaccountxpmanager* xp_manager) {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AccountXPManager.GetWinOfTheDayAP"));

	struct {
		int32_t ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

void ashootercharacter::set_account_level_cheat(uaccountxpmanager* xp_manager, int32_t level) {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AccountXPManager.SetAccountLevelCheat"));

	struct {
		int32_t Level;
	} params;

	params.Level = level;

	this->process_event(function, &params);
}

void ashootercharacter::trigger_refresh_player(uaccountxpmanager* xp_manager) {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AccountXPManager.TriggerRefreshPlayer"));

	this->process_event(function, nullptr);
}

bool ashootercharacter::GetWalkHeld()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetWalkHeld"));

	struct
	{
		bool ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

bool ashootercharacter::GetJumpHeld()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetJumpHeld"));

	struct
	{
		bool ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

void ashootercharacter::ClientCheatFly()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Character.ClientCheatFly"));

	if (function)
	{
		this->process_event(function, nullptr);
	}
}

void ashootercharacter::ServerCheatFly()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterPlayerControllerDebugComponent.ServerCheatFly"));

	if (function)
	{
		struct
		{
			ashootercharacter* TargetCharacter;
		} params;

		params.TargetCharacter = this;

		aplayercontroller* playerController;
		if (playerController)
		{
			playerController->process_event(function, &params);
		}
	}
}

void ashootercharacter::SetMovementMode(EMovementMode NewMovementMode, uint8_t NewCustomMode)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.CharacterMovementComponent.SetMovementMode"));

	if (function)
	{
		struct
		{
			EMovementMode NewMovementMode;
			uint8_t NewCustomMode;
		} params;

		params.NewMovementMode = NewMovementMode;
		params.NewCustomMode = NewCustomMode;

		this->process_event(function, &params);
	}
}

void ashootercharacter::EnableFly()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.ClientFly"));

	if (function)
	{
		this->process_event(function, nullptr);
	}

	SetMovementMode(EMovementMode::MOVE_Flying, 0);
}

void ashootercharacter::DisableFly()
{
	SetMovementMode(EMovementMode::MOVE_Walking, 0);
}


uobject* uobject::static_load_object(uobject* Class, uobject* InOuter, const wchar_t* Name)
{
	static uintptr_t StaticLoadObjectAddress = memory::module_base + offsets::static_laod_object;
	auto StaticLoadObjectFN = reinterpret_cast<uobject * (__fastcall*)(uobject*, uobject*, const wchar_t*, bool)>(StaticLoadObjectAddress);
	return reinterpret_cast<uobject * (__fastcall*)(uobject*, uobject*, const wchar_t*, bool, uintptr_t, void*)>(spoofcall_stub)(nullptr, reinterpret_cast<uobject*>(-1), Name, false, offsets::magic, (void*)StaticLoadObjectFN);
}
uobject* uobject::StaticLoadObject(const wchar_t* ObjectPath) {

	if (!ObjectPath)
		return nullptr;


	static uintptr_t StaticLoadObjectAddress = memory::module_base + offsets::static_laod_object;
	return reinterpret_cast<uobject * (__fastcall*)(uobject*, uobject*, const wchar_t*, const wchar_t*, uint32_t, uint32_t, void*, uintptr_t, void*)>(spoofcall_stub)(nullptr, nullptr, ObjectPath, nullptr, 0, 0, nullptr, offsets::magic, (void*)StaticLoadObjectAddress);


}

void uskeletalmeshcomponent::SetMaterial(int32_t ElementIndex, uobject* Material) {
	uobject* function = uobject::find_object<uobject*>(crypt(L"Engine.PrimitiveComponent.SetMaterial"));
	if (!function) {
		return;
	}

	struct {
		int32_t ElementIndex;
		uobject* Material;
	} Parameters;

	Parameters.ElementIndex = ElementIndex;
	Parameters.Material = Material;
	this->process_event(function, &Parameters);
}

void uskeletalmeshcomponent::SetMaterialByName(fname MaterialSlotName, uobject* Material)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PrimitiveComponent.SetMaterialByName"));

	struct
	{
		fname MaterialSlotName;
		uobject* Material;
	} params;

	params.MaterialSlotName = MaterialSlotName;
	params.Material = Material;

	this->process_event(function, &params);
}

void uskeletalmeshcomponent::SetPhysMaterialOverride(uobject* NewPhysMaterial)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PrimitiveComponent.SetPhysMaterialOverride"));

	struct
	{
		uobject* NewPhysMaterial;
	} params;

	params.NewPhysMaterial = NewPhysMaterial;

	this->process_event(function, &params);
}


void uskeletalmeshcomponent::SetTextureParameterValue(fname ParameterName, uobject* Value)
{
	static uobject* function = nullptr;

	if (function == nullptr)
		function = uobject::find_object<uobject*>(crypt(L"Engine.MaterialInstanceDynamic.SetTextureParameterValue"));

	struct
	{
		fname ParameterName;
		uobject* Value;
	} params;

	params.ParameterName = ParameterName;
	params.Value = Value;

	this->process_event(function, &params);
}

void uskeletalmeshcomponent::SetVectorParamOnMesh(uskeletalmeshcomponent* mesh, const wchar_t* param_name, const fvector& color)
{
	if (!mesh || !param_name)
		return;

	static uobject* function = uobject::find_object<uobject*>(crypt(L"Engine.MeshComponent.SetVectorParameterValueOnMaterials"));
	if (!function)
		return;

	struct {
		fname ParameterName;
		fvector ParameterValue;
	} params;

	fstring fstr = fstring(param_name);
	params.ParameterName = string::string_to_name(fstr);
	params.ParameterValue = color;

	mesh->process_event(function, &params);
}

//fstring ashootercharacter::GetPlayerName()
//{
//	static uobject* function = nullptr;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerState.GetPlayerName"));
//
//	if (function)
//	{
//		struct
//		{
//			fstring ReturnValue;
//		} params;
//
//		this->process_event(function, &params);
//		return params.ReturnValue;
//	}
//
//	return fstring(L"Unknown");
//}

void currentequippable::UpdateMaterial(int32_t Index_0, uobject* Material)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresEquippable.UpdateMaterial"));

	struct
	{
		int32_t Index_0;
		uobject* Material;
	} params;

	params.Index_0 = Index_0;
	params.Material = Material;

	this->process_event(function, &params);
}

void GetThirdPersonMesh(struct USkeletalMeshComponent*& Mesh); // Function Ability_Melee_Base.Ability_Melee_Base_C.GetThirdPersonMesh // (Public|HasOutParms|BlueprintCallable|BlueprintEvent) // @ game+0x19a85c0


void uskeletalmeshcomponent::setsketeletalmesh(uskeletalmeshcomponent* newmesh, bool breinitpose)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.SkinnedMeshComponent.SetSkeletalMesh")); // thats needed for custom mesh i looked these func yeup

	struct
	{
		uskeletalmeshcomponent* newmesh;
		bool breinitpose;
	} params;

	params.newmesh = newmesh;
	params.breinitpose = breinitpose;

	this->process_event(function, &params);
} // ill check if still same on UE5

void uskeletalmeshcomponent::updatemesh()
{
	static uobject* function = nullptr;

	if (function == nullptr)
		function = uobject::find_object<uobject*>(crypt(L"Engine.SplineMeshComponent.UpdateMesh"));

	if (function)
	{
		this->process_event(function, nullptr);
	}
}

void uskeletalmeshcomponent::set_animation(uanimationasset* new_anim_to_play)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.SkeletalMeshComponent.SetAnimation"));

	struct
	{
		uanimationasset* NewAnimToPlay;
	} params;

	params.NewAnimToPlay = new_anim_to_play;

	this->process_event(function, &params);
}

void uskeletalmeshcomponent::set_animation_mode(EAnimationMode in_animation_mode)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.SkeletalMeshComponent.SetAnimationMode"));

	struct
	{
		EAnimationMode InAnimationMode;
	} params;

	params.InAnimationMode = in_animation_mode;

	this->process_event(function, &params);
}


void uskeletalmeshcomponent::SetMesh(uskeletalmeshcomponent* InMesh)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"HoudiniEngineRuntime.HoudiniStaticMeshComponent.SetMesh"));

	struct
	{
		uskeletalmeshcomponent* InMesh;
	} params;

	params.InMesh = InMesh;

	this->process_event(function, &params);
}


float ashootercharacter::ReceiveAnyDamage(UDamageType* DamageType, aplayercontroller12* InstigatedBy, ashootercharacter* DamageCauser)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.ReceiveAnyDamage"));

	struct
	{
		float Damage;
		UDamageType* DamageType;
		aplayercontroller12* InstigatedBy;
		ashootercharacter* DamageCauser;
		float ReturnValue;
	} params;

	params.DamageType = DamageType;
	params.InstigatedBy = InstigatedBy;
	params.DamageCauser = DamageCauser;

	this->process_event(function, &params);

	this->lastDamageReceived = params.Damage;

	return params.ReturnValue;
}

void ufresnelcomponent::HandleMeshMaterialChanged(umeshmaterialmanagercomponent* MeshMaterialManager, umeshcomponent* Mesh, int32_t ElementIndex, umaterialinterface* Material, EMeshPlayerView MeshPlayerView, umaterialinterface* OldMaterial)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.FresnelComponent.HandleMeshMaterialChanged");

	struct
	{
		umeshmaterialmanagercomponent* MeshMaterialManager;
		umeshcomponent* Mesh;
		int32_t ElementIndex;
		umaterialinterface* Material;
		EMeshPlayerView MeshPlayerView;
		umaterialinterface* OldMaterial;
	} params;

	params.MeshMaterialManager = MeshMaterialManager;
	params.Mesh = Mesh;
	params.ElementIndex = ElementIndex;
	params.Material = Material;
	params.MeshPlayerView = MeshPlayerView;
	params.OldMaterial = OldMaterial;

	this->process_event(function, &params);
}

void ufresnelcomponent::SetIntensity(float NewIntensity)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.FresnelComponent.SetIntensity");

	struct
	{
		float NewIntensity;
	} params;

	params.NewIntensity = NewIntensity;

	this->process_event(function, &params);
}

void ufresnelcomponent::SetMaterials1P(const std::set<umaterialinstancedynamic*>& FresnelMaterials)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.FresnelComponent.SetMaterials1P");

	struct
	{
		std::set<umaterialinstancedynamic*> FresnelMaterials;
	} params;

	params.FresnelMaterials = FresnelMaterials;

	this->process_event(function, &params);
}

void ufresnelcomponent::SetMaterials3P(const std::set<umaterialinstancedynamic*>& FresnelMaterials)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.FresnelComponent.SetMaterials3P");

	struct
	{
		std::set<umaterialinstancedynamic*> FresnelMaterials;
	} params;

	params.FresnelMaterials = FresnelMaterials;

	this->process_event(function, &params);
}

void ufresnelcomponent::SetOffset(float NewOffset)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.FresnelComponent.SetOffset");

	struct
	{
		float NewOffset;
	} params;

	params.NewOffset = NewOffset;

	this->process_event(function, &params);
}

fappliedmaterialhandle umeshmaterialmanagercomponent::SetAllMaterials(EMeshPlayerView MeshPlayerView, umaterialinterface* Material, EMaterialPriority Priority)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.MeshMaterialManagerComponent.SetAllMaterials");

	struct
	{
		EMeshPlayerView MeshPlayerView;
		umaterialinterface* Material;
		EMaterialPriority Priority;
		fappliedmaterialhandle ReturnValue;
	} params;

	params.MeshPlayerView = MeshPlayerView;
	params.Material = Material;
	params.Priority = Priority;

	this->process_event(function, &params);

	return params.ReturnValue;
}

fappliedmaterialhandle umeshmaterialmanagercomponent::SetMaterial(EMeshPlayerView MeshPlayerView, int32_t ElementIndex, umaterialinterface* Material, EMaterialPriority Priority)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.MeshMaterialManagerComponent.SetMaterial");

	struct
	{
		EMeshPlayerView MeshPlayerView;
		int32_t ElementIndex;
		umaterialinterface* Material;
		EMaterialPriority Priority;
		fappliedmaterialhandle ReturnValue;
	} params;

	params.MeshPlayerView = MeshPlayerView;
	params.ElementIndex = ElementIndex;
	params.Material = Material;
	params.Priority = Priority;

	this->process_event(function, &params);

	return params.ReturnValue;
}

ashootercharacter* ashootercharacter::GetShooterCharacterMovement()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetShooterCharacterMovement"));

	struct
	{
		ashootercharacter* output;
	} params;

	this->process_event(function, &params);

	return params.output;
}

uammocomponent* currentequippable::GetAmmoComponent()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresEquippable.GetAmmoComponent"));

	struct
	{
		uammocomponent* output;
	} params;

	this->process_event(function, &params);

	return params.output;
}

int32_t uammocomponent::GetMaxAmmo()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AmmoComponent.GetMaxAmmo"));

	struct
	{
		int32_t ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

int32_t currentequippable::GetAmmo()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AmmoComponent.GetAmmo"));

	struct
	{
		int32_t ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

int32_t currentequippable::GetMaxAmmo()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AmmoComponent.GetMaxAmmo"));

	struct
	{
		int32_t ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

void ashootercharacter::AddControllerPitchInput(float Val)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Pawn.AddControllerPitchInput"));

	struct
	{
		float Val;
	} params;

	params.Val = Val;

	this->process_event(function, &params);
}

void ashootercharacter::AddControllerRollInput(float Val)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Pawn.AddControllerRollInput"));

	struct
	{
		float Val;
	} params;

	params.Val = Val;

	this->process_event(function, &params);
}

void ashootercharacter::AddControllerYawInput(float Val)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Pawn.AddControllerYawInput"));

	struct
	{
		float Val;
	} params;

	params.Val = Val;

	this->process_event(function, &params);
}

//void ashootercharacter::GetPlayerViewPoint(fvector& location, frotator& rotation)
//{
//	static uobject* function;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerController.GetPlayerViewPoint"));
//
//	struct { fvector location; frotator rotation; } params;
//
//	location = params.location;
//	rotation = params.rotation;
//
//	this->process_event(function, &params);
//}

void ashootercharacter::GetPlayerViewPoint(fvector* Out_Location, frotator* Out_Rotation)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerController.GetPlayerViewPoint"));

	struct
	{
		fvector Out_Location;
		frotator Out_Rotation;
	} params;

	this->process_event(function, &params);

	if (Out_Location)
		*Out_Location = params.Out_Location;

	if (Out_Rotation)
		*Out_Rotation = params.Out_Rotation;
}

fvector ashootercharacter::GetPlayerViewLocation()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerController.GetPlayerViewLocation"));

	struct
	{
		fvector ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

float aplayercontroller::GetSmokeOverlay()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerController.GetSmokeOverlay"));

	struct
	{
		float ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

int32_t ashootercharacter::GetNumPointsNeededForUltimate()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterPlayerStateDataModel.GetNumPointsNeededForUltimate"));

	struct
	{
		int32_t ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

int32_t ashootercharacter::GetNumUltimatePoints()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterPlayerStateDataModel.GetNumUltimatePoints"));

	struct
	{
		int32_t ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

bool ashootercharacter::HasSpike()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterPlayerStateDataModel.HasSpike"));

	struct
	{
		bool ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

fstring ashootercharacter::GetPlayerName()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterPlayerStateDataModel.GetPlayerName"));

	struct
	{
		fstring ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

int32_t ashootercharacter::GetMatchCombatScore()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterPlayerStateDataModel.GetMatchCombatScore"));

	struct
	{
		int32_t ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

void ashootercharacter::SwapTeam()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCheatManager.SwapTeam_ClientHack"));

	this->process_event(function, nullptr);
}

void ashootercharacter::ClientPlayAimpunchSimple(UMatineeCameraShake* CameraMod, float ShakeStrength, bool bSharesWeaponShakeCooldown)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.ClientPlayAimpunchSimple"));

	struct
	{
		UMatineeCameraShake* CameraMod;
		float ShakeStrength;
		bool bSharesWeaponShakeCooldown;
	} params;

	params.CameraMod = CameraMod;
	params.ShakeStrength = ShakeStrength;
	params.bSharesWeaponShakeCooldown = bSharesWeaponShakeCooldown;

	this->process_event(function, &params);
}

//bool CanWallBang(ashootercharacter* local_player) {
//	auto weapon = local_player->get_inventory()->get_current_equippable();
//	if (!weapon) return false;
//
//	fstring weapon_name = system::get_object_name(weapon);
//	std::wstring weapon_str = weapon_name.wide();
//
//
//	if (weapon_str.find(L"Vandal") != std::wstring::npos) return true;
//	if (weapon_str.find(L"Phantom") != std::wstring::npos) return true;
//	if (weapon_str.find(L"Operator") != std::wstring::npos) return true;
//	if (weapon_str.find(L"Marshal") != std::wstring::npos) return true;
//	if (weapon_str.find(L"Guardian") != std::wstring::npos) return true;
//	if (weapon_str.find(L"Spectre") != std::wstring::npos) return true;
//	if (weapon_str.find(L"Sheriff") != std::wstring::npos) return true;
//	if (weapon_str.find(L"Outlaw") != std::wstring::npos) return true;
//	if (weapon_str.find(L"Stinger") != std::wstring::npos) return true;
//	if (weapon_str.find(L"Bulldog") != std::wstring::npos) return true;
//	if (weapon_str.find(L"Ares") != std::wstring::npos) return true;
//	if (weapon_str.find(L"Odin") != std::wstring::npos) return true;
//
//	return false;
//}



//void ashootercharacter::ClientPlayAimpunch(UMatineeCameraShake* CameraMod, float ShakeStrength, ECameraShakePlaySpace CameraShakePlaySpace, const struct FRotator& UserPlaySpaceRot, bool bSharesWeaponShakeCooldown)
//{
//	static auto function = uobject::find_object<uobject*>(crypt(L"Function ShooterGame.ShooterCharacter.ClientPlayAimpunch"));
//	if (function)
//	{
//		struct
//		{
//			UMatineeCameraShake* CameraMod;
//			float ShakeStrength;
//			ECameraShakePlaySpace CameraShakePlaySpace;
//			FRotator UserPlaySpaceRot;
//			bool bSharesWeaponShakeCooldown;
//		} params;
//
//		params.CameraMod = CameraMod;
//		params.ShakeStrength = ShakeStrength;
//		params.CameraShakePlaySpace = CameraShakePlaySpace;
//		params.UserPlaySpaceRot = UserPlaySpaceRot;
//		params.bSharesWeaponShakeCooldown = bSharesWeaponShakeCooldown;
//
//		this->process_event(function, &params);
//	}
//}


//namespace NoSpread2 
//{
//
//
//
//	fvector get_error_angle(uint64_t actor, uint64_t firing_state_component) {
//		SPOOF_FUNC;
//		if (!actor || !firing_state_component) return fvector(0, 0, 0);
//
//		// Modül base zaten nti() ile initialize edilmiş olmalı
//		if (!memory::module_base) return fvector(0, 0, 0);
//
//		auto get_spread_values_fn = (float* (__fastcall*)(uint64_t, float*))(memory::module_base + offsets::get_spread_values); // 0x5AFAF70
//		auto get_spread_angles_fn = (void(__fastcall*)(uint64_t, fvector*, float, float, int, int, uint64_t))(memory::module_base + offsets::get_spread_angles); // 0x659CBD0
//		auto get_firing_location_and_direction_fn = (void(__fastcall*)(uint64_t, fvector*, fvector*))(memory::module_base + offsets::get_firing_location); // 0x3BF2000
//		auto to_vector_and_normalize_fn = (fvector * (__fastcall*)(fvector*, fvector*))(memory::module_base + offsets::to_vector_and_normalize); // 0x16500B0
//		auto to_angle_and_normalize_fn = (fvector * (__fastcall*)(fvector*, fvector*))(memory::module_base + offsets::to_angle_and_normalize); // 0x164AA60
//
//		static uint8_t error_values[4096];
//		static uint8_t seed_data_snapshot[4096];
//		static uint8_t spread_angles[4096];
//		static uint8_t out_spread_angles[4096];
//
//		if (!actor || !firing_state_component)
//			return fvector(0, 0, 0);
//
//		memset(error_values, 0, sizeof(error_values));
//		memset(seed_data_snapshot, 0, sizeof(seed_data_snapshot));
//		memset(spread_angles, 0, sizeof(spread_angles));
//		memset(out_spread_angles, 0, sizeof(out_spread_angles));
//
//		*(uint64_t*)(&out_spread_angles[0]) = (uint64_t)&spread_angles[0];
//		*(int*)(&out_spread_angles[0] + 8) = 1;
//		*(int*)(&out_spread_angles[0] + 12) = 1;
//
//		uint64_t seed_data = memory::read<uint64_t>(firing_state_component + offsets::seed_data); // 0x4A0
//		memcpy((void*)seed_data_snapshot, (void*)seed_data, sizeof(seed_data_snapshot));
//
//		uint64_t stability_component = memory::read<uint64_t>(firing_state_component + offsets::stability_component); // 0x490
//		if (stability_component) {
//			get_spread_values_fn(stability_component, (float*)&error_values[0]);
//		}
//
//		fvector temp1, temp2 = fvector(0, 0, 0);
//		fvector previous_firing_direction, firing_direction = fvector(0, 0, 0);
//		get_firing_location_and_direction_fn(actor, &temp1, &previous_firing_direction);
//		to_vector_and_normalize_fn(&previous_firing_direction, &temp2);
//		to_angle_and_normalize_fn(&temp2, &temp1);
//		previous_firing_direction = temp1;
//		temp1.x += *(float*)(&error_values[0] + 12); // Horizontal offset
//		temp1.y += *(float*)(&error_values[0] + 16); // Vertical offset
//		to_vector_and_normalize_fn(&temp1, &firing_direction);
//
//		float error_degrees = *(float*)(&error_values[0] + 8) + *(float*)(&error_values[0] + 4);
//		float error_power = memory::read<float>(firing_state_component + offsets::error_power); // 0x49c
//		int error_retries = memory::read<int>(firing_state_component + offsets::error_retries); // 0x470
//		get_spread_angles_fn(((uint64_t)&seed_data_snapshot[0]) + 0xE8, &firing_direction, error_degrees, error_power, error_retries, 1, (uint64_t)&out_spread_angles[0]);
//
//		fvector spread_vector = *(fvector*)(&spread_angles[0]);
//		to_angle_and_normalize_fn(&spread_vector, &firing_direction);
//
//		return firing_direction - previous_firing_direction;
//	}
//
//		fvector calc_spread(ashootercharacter* actor, uint64_t firing_state_component, currentequippable* weapon, fvector direction) {
//			SPOOF_FUNC;
//			if (!actor || !firing_state_component || !weapon) return fvector(0, 0, 0);
//
//			uint64_t stability_component = memory::read<uint64_t>(firing_state_component + offsets::stability_component);
//			if (!stability_component) return fvector(0, 0, 0);
//
//			static uint8_t error_values[4096];
//			static uint8_t seed_data_snapshot[4096];
//			static uint8_t spread_angles[4096];
//			static uint8_t out_spread_angles[4096];
//
//			if (!memory::module_base) return fvector(0, 0, 0);
//
//			auto func1_fn = (float* (__fastcall*)(uint64_t, float*))(memory::module_base + offsets::get_spread_values);
//			auto func2_fn = (void(__fastcall*)(uint64_t, fvector*, float, float, int, int, uint64_t))(memory::module_base + offsets::get_spread_angles);
//			auto func3_fn = (fvector * (__fastcall*)(fvector*, fvector*))(memory::module_base + offsets::to_vector_and_normalize);
//			auto func4_fn = (fvector * (__fastcall*)(fvector*, fvector*))(memory::module_base + offsets::to_angle_and_normalize);
//
//			*(uint64_t*)(&out_spread_angles[0]) = (uint64_t)&spread_angles[0];
//			*(int*)(&out_spread_angles[0] + 8) = 1;
//			*(int*)(&out_spread_angles[0] + 12) = 1;
//
//			uint64_t seed_data = memory::read<uint64_t>(firing_state_component + offsets::seed_data);
//			if (!seed_data) return fvector(0, 0, 0);
//			memcpy((void*)seed_data_snapshot, (void*)seed_data, sizeof(seed_data_snapshot));
//
//			reinterpret_cast<float* (__cdecl*)(uint64_t, float*, uintptr_t, void*)>(
//				spoofcall_stub)(stability_component, (float*)&error_values[0], offsets::magic, func1_fn);
//
//			fvector temp1, temp2 = fvector(0, 0, 0);
//			fvector previous_firing_direction = direction; // Başlangıç yönü
//			fvector firing_direction = direction;
//
//			reinterpret_cast<fvector* (__cdecl*)(fvector*, fvector*, uintptr_t, void*)>(
//				spoofcall_stub)(&previous_firing_direction, &temp2, offsets::magic, func3_fn);
//			reinterpret_cast<fvector* (__cdecl*)(fvector*, fvector*, uintptr_t, void*)>(
//				spoofcall_stub)(&temp2, &temp1, offsets::magic, func4_fn);
//
//			previous_firing_direction = temp1;
//			temp1.x += *(float*)(&error_values[0] + 12);
//			temp1.y += *(float*)(&error_values[0] + 16);
//
//			reinterpret_cast<fvector* (__cdecl*)(fvector*, fvector*, uintptr_t, void*)>(
//				spoofcall_stub)(&temp1, &firing_direction, offsets::magic, func3_fn);
//
//			float error_degrees = *(float*)(&error_values[0] + 8) + *(float*)(&error_values[0] + 4);
//			float error_power = memory::read<float>(firing_state_component + offsets::error_power);
//			int error_retries = memory::read<int>(firing_state_component + offsets::error_retries);
//
//			reinterpret_cast<void(__cdecl*)(uint64_t, fvector*, float, float, int, int, uint64_t, uintptr_t, void*)>(
//				spoofcall_stub)(((uint64_t)&seed_data_snapshot[0]) + 0xE8, &firing_direction,
//					error_degrees, error_power, error_retries, 1, (uint64_t)&out_spread_angles[0], offsets::magic, func2_fn);
//
//			fvector spread_vector = *(fvector*)(&spread_angles[0]);
//			reinterpret_cast<fvector* (__cdecl*)(fvector*, fvector*, uintptr_t, void*)>(
//				spoofcall_stub)(&spread_vector, &firing_direction, offsets::magic, func4_fn);
//
//			return firing_direction - previous_firing_direction;
//		}
//	}

//int32_t ashootercharacter::GetNumUltimatePoints()
//{
//	static uobject* function = nullptr;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterPlayerState.GetNumUltimatePoints"));
//
//	struct
//	{
//		int32_t ReturnValue;
//	} params;
//
//	this->process_event(function, &params);
//
//	return params.ReturnValue;
//}
//
//int32_t ashootercharacter::GetNumPointsNeededForUltimate()
//{
//	static uobject* function = nullptr;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterPlayerState.GetNumPointsNeededForUltimate"));
//
//	struct
//	{
//		int32_t ReturnValue;
//	} params;
//
//	this->process_event(function, &params);
//
//	return params.ReturnValue;
//}

bool ashootercharacter::GetIsAFK()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterPlayerState.GetIsAFK"));

	struct
	{
		bool ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

int32_t ashootercharacter::GetMoney()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterPlayerState.GetMoney"));

	struct
	{
		int32_t ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

float ashootercharacter::GetTimeUntilRespawn()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterPlayerState.GetTimeUntilRespawn"));

	struct
	{
		float ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

bool ashootercharacter::IsCoach()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterPlayerState.IsCoach"));

	struct
	{
		bool ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

bool ashootercharacter::IsUltimateReady()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterPlayerState.IsUltimateReady"));

	struct
	{
		bool ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

void ashootercharacter::SetOutlineMode(EAresOutlineMode OutlineMode)
{
	static auto function = uobject::find_object<uobject*>(crypt(L"Function ShooterGame.AresOutlineComponent.SetOutlineMode"));
	if (function)
	{
		struct
		{
			EAresOutlineMode OutlineMode;
		} params;

		params.OutlineMode = OutlineMode;

		this->process_event(function, &params);
	}
}
void ashootercharacter::SetAspectRatio(float InAspectRatio) 
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.CameraComponent.SetAspectRatio"));

	if (function)
	{
		struct { float InAspectRatio; } params;
		params.InAspectRatio = InAspectRatio;
		this->process_event(function, &params);
	}
}

void ashootercharacter::UpdateOutlineMode()
{
	static auto function = uobject::find_object<uobject*>(crypt(L"Function ShooterGame.AresOutlineComponent.UpdateOutlineMode"));
	if (function)
	{
		this->process_event(function, nullptr);
	}
}

void ashootercharacter::ResetAbilityCooldowns()
{
	static auto function = uobject::find_object<uobject*>(crypt(L"Function ShooterGame.ShooterCharacter.ResetAbilityCooldowns"));
	if (function)
	{
		this->process_event(function, nullptr);
	}
}

fstring ashootercharacter::GetShortPlayerName()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerStateBase.GetShortPlayerName"));

	struct
	{
		fstring ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

int32_t ashootercharacter::GetPlayerCompetitiveTier()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerStateBase.GetPlayerCompetitiveTier"));

	struct
	{
		int32_t ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

EChatPresenceState ashootercharacter::GetPresenceState()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.PlatformPlayer.GetPresenceState"));

	struct
	{
		EChatPresenceState ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

void ashootercharacter::UnlockFOV()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerController.UnlockFOV"));

	this->process_event(function, nullptr);
}

void aplayercontroller::show_colored_muzzle_flashes_for_player(bool bEnable)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerController.ShowColoredMuzzleFlashesForPlayer"));

	struct { bool bEnable; } params;
	params.bEnable = bEnable;

	this->process_event(function, &params);
}

bool blueprints::is_colored_muzzle_flash_setting_enabled()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterBlueprintLibrary.IsColoredMuzzleFlashSettingEnabled"));

	struct { bool ReturnValue; } params;
	variables.blueprints->process_event(function, &params);
	return params.ReturnValue;
}

const ftransform currentequippable::get_muzzle_transform()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresEquippable.GetMuzzleTransform"));

	struct
	{
		ftransform ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

tarray<fstring> ashootercharacter::get_all_morph_target_names()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.SkeletalMesh.K2_GetAllMorphTargetNames"));

	struct
	{
		tarray<fstring> ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

void uskeletalmeshcomponent::set_equippable_charm(int new_equippable_charm)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.EquippableCharmLevelDataAsset.SetEquippableCharm"));

	struct
	{
		int new_equippable_charm;
	} params;

	params.new_equippable_charm = new_equippable_charm;

	this->process_event(function, &params);
}

//void UCheatManager::Fly()
//{
//	static uobject* function = nullptr;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"Engine.CheatManager.Fly"));
//
//	if (function)
//	{
//		this->process_event(function, nullptr);
//	}
//}

void aplayercontroller::SetName(fstring& S)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.SetName"));

	if (function)
	{
		struct
		{
			fstring S;
		} params;

		params.S = S;

		this->process_event(function, &params);
	}
}

void aplayercontroller::SetCinematicMode(bool bInCinematicMode, bool bHidePlayer, bool bAffectsHUD, bool bAffectsMovement, bool bAffectsTurning)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.SetCinematicMode"));

	if (function)
	{
		struct
		{
			bool bInCinematicMode;
			bool bHidePlayer;
			bool bAffectsHUD;
			bool bAffectsMovement;
			bool bAffectsTurning;
		} params;

		params.bInCinematicMode = bInCinematicMode;
		params.bHidePlayer = bHidePlayer;
		params.bAffectsHUD = bAffectsHUD;
		params.bAffectsMovement = bAffectsMovement;
		params.bAffectsTurning = bAffectsTurning;

		this->process_event(function, &params);
	}
}

void aplayercontroller::client_draw_debug_lines(const tarray<FAresDebugLineReplicated>& debug_lines) {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.AresPlayerController.ClientDrawDebugLines");

	struct
	{
		tarray<FAresDebugLineReplicated> debug_lines;
	} params;

	params.debug_lines = debug_lines;

	this->process_event(function, &params);
}


void aplayercontroller::setcontrollerlightcolor(const fcolor& color)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.SetControllerLightColor"));

	struct
	{
		fcolor color;
	} params;

	params.color = color;

	this->process_event(function, &params);
}

void aplayercontroller::ServerExec(fstring& Msg)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.ServerExec"));

	if (function)
	{
		struct
		{
			fstring Msg;
		} params;

		params.Msg = Msg;

		this->process_event(function, &params);
	}
}

void aplayercontroller::ServerExecRPC(fstring& Msg)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.ServerExecRPC"));

	if (function)
	{
		struct
		{
			fstring Msg;
		} params;

		params.Msg = Msg;

		this->process_event(function, &params);
	}
}

void aplayercontroller::ServerPause()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.ServerPause"));

	if (function)
	{
		this->process_event(function, nullptr);
	}
}

void aplayercontroller::ServerChangeName(fstring& S)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.ServerChangeName"));

	if (function)
	{
		struct
		{
			fstring S;
		} params;

		params.S = S;

		this->process_event(function, &params);
	}
}

void aplayercontroller::Pause()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.Pause"));

	if (function)
	{
		this->process_event(function, nullptr);
	}
}

void aplayercontroller::LocalTravel(fstring& URL)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.LocalTravel"));

	if (function)
	{
		struct
		{
			fstring URL;
		} params;

		params.URL = URL;

		this->process_event(function, &params);
	}
}

void aplayercontroller::K2_ClientPlayForceFeedback(uobject* ForceFeedbackEffect, fname Tag, bool bLooping, bool bIgnoreTimeDilation, bool bPlayWhilePaused)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.K2_ClientPlayForceFeedback"));

	if (function)
	{
		struct
		{
			uobject* ForceFeedbackEffect;
			fname Tag;
			bool bLooping;
			bool bIgnoreTimeDilation;
			bool bPlayWhilePaused;
		} params;

		params.ForceFeedbackEffect = ForceFeedbackEffect;
		params.Tag = Tag;
		params.bLooping = bLooping;
		params.bIgnoreTimeDilation = bIgnoreTimeDilation;
		params.bPlayWhilePaused = bPlayWhilePaused;

		this->process_event(function, &params);
	}
}

void aplayercontroller::PlayDynamicForceFeedback(float Intensity, float Duration, bool bAffectsLeftLarge, bool bAffectsLeftSmall, bool bAffectsRightLarge, bool bAffectsRightSmall, EDynamicForceFeedbackAction Action, FLatentActionInfo& LatentInfo)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.PlayDynamicForceFeedback"));

	if (function)
	{
		struct
		{
			float Intensity;
			float Duration;
			bool bAffectsLeftLarge;
			bool bAffectsLeftSmall;
			bool bAffectsRightLarge;
			bool bAffectsRightSmall;
			EDynamicForceFeedbackAction Action;
			FLatentActionInfo LatentInfo;
		} params;

		params.Intensity = Intensity;
		params.Duration = Duration;
		params.bAffectsLeftLarge = bAffectsLeftLarge;
		params.bAffectsLeftSmall = bAffectsLeftSmall;
		params.bAffectsRightLarge = bAffectsRightLarge;
		params.bAffectsRightSmall = bAffectsRightSmall;
		params.Action = Action;
		params.LatentInfo = LatentInfo;

		this->process_event(function, &params);
	}
}

void aplayercontroller::ConsoleKey(const fkey& Key)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.ConsoleKey"));

	if (function)
	{
		struct
		{
			fkey Key;
		} params;

		params.Key = Key;

		this->process_event(function, &params);
	}
}

void ares_instance::StartPatchDownload()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresClientGameInstance.StartPatchDownload"));

	if (function)
	{
		this->process_event(function, nullptr);
	}
}

void ares_instance::TriggerVanguardBanNotification(const fstring& Subject)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresClientGameInstance.TriggerVanguardBanNotification"));

	if (function)
	{
		struct
		{
			fstring Subject;
		} params;

		params.Subject = Subject;

		this->process_event(function, &params);
	}
}

void ashootercharacter::SetDisplayName(const ftext& InDisplayName)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.SettingsOptionViewModel.SetDisplayName"));

	if (function)
	{
		struct
		{
			ftext InDisplayName;
		} params;

		params.InDisplayName = InDisplayName;

		this->process_event(function, &params);
	}
}

void ashootercharacter::SetDisplayName1(const ftext& NewName)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.BaseContentUIData.SetDisplayName"));

	if (function)
	{
		struct
		{
			ftext NewName;
		} params;

		params.NewName = NewName;

		this->process_event(function, &params);
	}
}

tarray<fname> ashootercharacter::GetAllyCharacterNames()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.MatchDetailsViewModel.GetAllyCharacterNames"));

	struct
	{
		tarray<fname> ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

tarray<fname> ashootercharacter::GetEnemyCharacterNames()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.MatchDetailsViewModel.GetEnemyCharacterNames"));

	struct
	{
		tarray<fname> ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

bool ULeaderboardViewModel::get_leaderboard_players(int32_t start_index, int32_t end_index, tarray<ULeaderboardPlayerModel*>& out_players)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.LeaderboardViewModel.GetLeaderboardPlayers"));

	struct
	{
		int32_t StartIndex;
		int32_t EndIndex;
		tarray<ULeaderboardPlayerModel*> OutPlayers;
		bool ReturnValue;
	} params;

	params.StartIndex = start_index;
	params.EndIndex = end_index;

	this->process_event(function, &params);

	out_players = std::move(params.OutPlayers);

	return params.ReturnValue;
}

void aplayercontroller::client_message(const fstring& message, const fname& type, float duration)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.ClientMessage"));

	struct
	{
		fstring S;
		fname Type;
		float Duration;
	} params;

	params.S = message;
	params.Type = type;
	params.Duration = duration;

	this->process_event(function, &params);
}

void aplayercontroller::aim_at_character(ashootercharacter* target, const fname& bone_name)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerAutomation.AimAtCharacter"));

	struct
	{
		ashootercharacter* Target;
		fname BoneName;
	} params;

	params.Target = target;
	params.BoneName = bone_name;

	this->process_event(function, &params);
}

void aplayercontroller::unlock_fov()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerController.UnlockFOV"));

	this->process_event(function, nullptr);
}

float aplayercontroller::get_player_hfov(const ashootercharacter* viewer)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterBlueprintLibrary.GetPlayerHFoV"));

	struct
	{
		const ashootercharacter* Viewer;
		float ReturnValue;
	} params;

	params.Viewer = viewer;

	this->process_event(function, &params);

	return params.ReturnValue;
}

float aplayercontroller::get_fov_angle()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerCameraManager.GetFOVAngle"));

	struct
	{
		float ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

float aplayercontroller::get_fov_angle_1p()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerCameraManager.GetFOVAngle1P"));

	struct
	{
		float ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

void aplayercontroller::setbotstospawn(int32_t numbotstospawn)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterGameMode.SetBotsToSpawn"));

	struct
	{
		int32_t numbotstospawn;
	} params;

	params.numbotstospawn = numbotstospawn;

	this->process_event(function, &params);
}

aplayercontroller* aplayercontroller::spawnbot(int32_t botnumber, uskeletalmeshcomponent* botmesh, ashootercharacter* commandingcharacter, EAresTeamRole targetrole, bool buseagentasname)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterGameMode.SpawnBot"));

	struct
	{
		int32_t botnumber;
		uskeletalmeshcomponent* botmesh;
		ashootercharacter* commandingcharacter;
		EAresTeamRole targetrole;
		bool buseagentasname;
		aplayercontroller* returnvalue;
	} params;

	params.botnumber = botnumber;
	params.botmesh = botmesh;
	params.commandingcharacter = commandingcharacter;
	params.targetrole = targetrole;
	params.buseagentasname = buseagentasname;

	this->process_event(function, &params);

	return params.returnvalue;
}


void aplayercontroller::SetViewTarget(ashootercharacter* NewViewTarget, FViewTargetTransitionParams& TransitionParams)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.SetViewTarget"));

	if (function)
	{
		struct
		{
			ashootercharacter* NewViewTarget;
			FViewTargetTransitionParams TransitionParams;
		} params;

		params.NewViewTarget = NewViewTarget;
		params.TransitionParams = TransitionParams;

		this->process_event(function, &params);
	}
}

void aplayercontroller::SetViewTargetWithBlend(ashootercharacter* NewViewTarget, float BlendTime, EViewTargetBlendFunction BlendFunc, float BlendExp, bool bLockOutgoing)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.SetViewTargetWithBlend"));

	if (function)
	{
		struct
		{
			ashootercharacter* NewViewTarget;
			float BlendTime;
			EViewTargetBlendFunction BlendFunc;
			float BlendExp;
			bool bLockOutgoing;
		} params;

		params.NewViewTarget = NewViewTarget;
		params.BlendTime = BlendTime;
		params.BlendFunc = BlendFunc;
		params.BlendExp = BlendExp;
		params.bLockOutgoing = bLockOutgoing;

		this->process_event(function, &params);
	}
}

void aplayercontroller::ClientSetViewTarget(uobject* A, const FViewTargetTransitionParams& TransitionParams)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.ClientSetViewTarget"));

	if (function)
	{
		struct
		{
			uobject* A;
			FViewTargetTransitionParams TransitionParams;
		} params;

		params.A = A;
		params.TransitionParams = TransitionParams;

		this->process_event(function, &params);
	}
}

void aplayercontroller::ServerVerifyViewTarget()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.ServerVerifyViewTarget"));

	if (function)
	{
		this->process_event(function, nullptr);
	}
}

void aplayercontroller::ServerViewNextPlayer()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.ServerViewNextPlayer"));

	if (function)
	{
		this->process_event(function, nullptr);
	}
}

void aplayercontroller::ServerViewPrevPlayer()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.ServerViewPrevPlayer"));

	if (function)
	{
		this->process_event(function, nullptr);
	}
}

void aplayercontroller::ServerViewSelf(const FViewTargetTransitionParams& TransitionParams)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.ServerViewSelf"));

	if (function)
	{
		struct
		{
			FViewTargetTransitionParams TransitionParams;
		} params;

		params.TransitionParams = TransitionParams;

		this->process_event(function, &params);
	}
}

void aplayercontroller::ClientReturnToMainMenu(const fstring& ReturnReason)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.ClientReturnToMainMenu"));

	if (function)
	{
		struct
		{
			fstring ReturnReason;
		} params;

		params.ReturnReason = ReturnReason;

		this->process_event(function, &params);
	}
}

void aplayercontroller::ClientReset()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.ClientReset"));

	if (function)
	{
		this->process_event(function, nullptr);
	}
}

void aplayercontroller::ClientRestart(acknowledgedpawn* NewPawn)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.ClientRestart"));

	if (function)
	{
		struct
		{
			acknowledgedpawn* NewPawn;
		} params;

		params.NewPawn = NewPawn;

		this->process_event(function, &params);
	}
}


void aplayercontroller::ClientClearCameraLensEffects()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.ClientClearCameraLensEffects"));

	if (function)
	{
		this->process_event(function, nullptr);
	}
}

void aplayercontroller::ClientSetCameraMode(fname NewCamMode)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.ClientSetCameraMode"));

	if (function)
	{
		struct
		{
			fname NewCamMode;
		} params;

		params.NewCamMode = NewCamMode;

		this->process_event(function, &params);
	}
}

void aplayercontroller::ToggleConsoleCheatsMenu()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerController.ToggleConsoleCheatsMenu"));

	if (function)
	{
		this->process_event(function, nullptr);
	}
}

bool aplayercontroller::ShowBloodForPlayer()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerController.ShowBloodForPlayer"));

	bool return_value = false;
	if (function)
	{
		this->process_event(function, &return_value);
	}
	return return_value;
}

bool aplayercontroller::ShowCorpsesForPlayer()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerController.ShowCorpsesForPlayer"));

	bool return_value = false;
	if (function)
	{
		this->process_event(function, &return_value);
	}
	return return_value;
}

void aplayercontroller::ToggleShop()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerController.ToggleShop"));

	if (function)
	{
		this->process_event(function, nullptr);
	}
}

void aplayercontroller::ShowCheatMenuCommandFunc()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerController.ShowCheatMenuCommandFunc"));

	if (function)
	{
		this->process_event(function, nullptr);
	}
}

void aplayercontroller::OnShowDeveloperMenu()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerController.OnShowDeveloperMenu"));

	if (function)
	{
		this->process_event(function, nullptr);
	}
}

void aplayercontroller::TogglePause()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.TogglePause"));

	if (function)
	{
		this->process_event(function, nullptr);
	}
}


void aplayercontroller::ClientInternalOnScreenDebugMessage(const fstring& Message, const flinearcolor& Color, float Duration)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerController.ClientInternalOnScreenDebugMessage"));

	if (function)
	{
		struct
		{
			fstring Message;
			flinearcolor Color;
			float Duration;
		} params;

		params.Message = Message;
		params.Color = Color;
		params.Duration = Duration;

		this->process_event(function, &params);
	}
}

void aplayercontroller::ClientEndOnlineGame()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerController.ClientEndOnlineGame"));

	if (function)
	{
		this->process_event(function, nullptr);
	}
}

void aplayercontroller::ClientStartOnlineGame()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerController.ClientStartOnlineGame"));

	if (function)
	{
		this->process_event(function, nullptr);
	}
}

void aplayercontroller::ClientStartOnlineSession()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.ClientStartOnlineSession"));

	if (function)
	{
		this->process_event(function, nullptr);
	}
}

float ashootercharacter::get_time_dilation()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.TimedStateComponent.GetTimeDilation"));

	if (function)
	{
		struct
		{
			float return_value;
		} params;

		this->process_event(function, &params);

		return params.return_value;
	}

	return 1.0f;
}

void ashootercharacter::set_time_dilation(float multiplier)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.TimedStateComponent.SetTimeDilation"));

	if (function)
	{
		struct
		{
			float multiplier;
		} params;

		params.multiplier = multiplier;

		this->process_event(function, &params);
	}
}

void aplayercontroller::request_toggle_free_cam()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.FreeCamComponent.RequestToggleFreeCam"));

	if (function)
	{
		this->process_event(function, nullptr);
	}
}

bool aplayercontroller::is_free_cam_enabled()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.FreeCamComponent.IsFreeCamEnabled"));

	if (function)
	{
		struct
		{
			bool ReturnValue;
		} params;

		this->process_event(function, &params);
		return params.ReturnValue;
	}
	return false;
}

void aplayercontroller::server_toggle_free_cam()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.FreeCamComponent.ServerToggleFreeCam"));

	if (function)
	{
		this->process_event(function, nullptr);
	}
}

UPlatformPlayer* ashootercharacter::GetPlatformPlayer1(uobject* socialPlayer)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.SocialPlayer.GetPlatformPlayer"));

	struct
	{
		UPlatformPlayer* ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

UPlatformPlayer* ashootercharacter::GetPlatformPlayer2(uobject* partyPlayerModel)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.PartyPlayerModel.GetPlatformPlayer"));

	struct
	{
		UPlatformPlayer* ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

UPlatformPlayer* ashootercharacter::GetPlatformPlayer3(uobject* pregamePlayerModel)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.PregamePlayerModel.GetPlatformPlayer"));

	struct
	{
		UPlatformPlayer* ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

bool ashootercharacter::SendMessage1(const ftext& Message)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.TextChatConversation.SendMessage"));

	struct
	{
		ftext Message;
		bool ReturnValue;
	} params;

	params.Message = Message;

	this->process_event(function, &params);

	return params.ReturnValue;
}

void ashootercharacter::SetTimeDilation(float Multiplier)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.TimedStateComponent.SetTimeDilation"));

	struct
	{
		float Multiplier;
	} params;

	params.Multiplier = Multiplier;

	this->process_event(function, &params);
}

//void aplayercontroller::ClientTravel(const fstring& URL, ETravelType TravelType, bool bSeamless, const FGuid& MapPackageGuid)
//{
//	static uobject* function = nullptr;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.ClientTravel"));
//
//	if (function)
//	{
//		struct
//		{
//			fstring URL;
//			ETravelType TravelType;
//			bool bSeamless;
//			FGuid MapPackageGuid;
//		} params;
//
//		params.URL = URL;
//		params.TravelType = TravelType;
//		params.bSeamless = bSeamless;
//		params.MapPackageGuid = MapPackageGuid;
//
//		this->process_event(function, &params);
//	}
//}
//
//void aplayercontroller::ClientTravelInternal(const fstring& URL, ETravelType TravelType, bool bSeamless, const FGuid& MapPackageGuid)
//{
//	static uobject* function = nullptr;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.ClientTravelInternal"));
//
//	if (function)
//	{
//		struct
//		{
//			fstring URL;
//			ETravelType TravelType;
//			bool bSeamless;
//			FGuid MapPackageGuid;
//		} params;
//
//		params.URL = URL;
//		params.TravelType = TravelType;
//		params.bSeamless = bSeamless;
//		params.MapPackageGuid = MapPackageGuid;
//
//		this->process_event(function, &params);
//	}
//}

//int ashootercharacter::GetPlayerCompetitiveTier()
//{
//	static uobject* function = nullptr;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerStateBase.GetPlayerCompetitiveTier"));
//
//	struct
//	{
//		int ReturnValue;
//	} params;
//
//	this->process_event(function, &params);
//
//	return params.ReturnValue;
//}


//void set_fresnel_intensity(ufresnelcomponent* fresnel_component, float intensity) {
//	static uobject* function = nullptr;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.FresnelComponent.SetIntensity"));
//
//	struct {
//		float NewIntensity;
//	} params;
//
//	params.NewIntensity = intensity;
//
//	fresnel_component->process_event(function, &params);
//}
//
//void set_fresnel_materials(ufresnelcomponent* fresnel_component, const std::set<umaterialinstancedynamic*>& fresnel_materials) {
//	static uobject* function = nullptr;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.FresnelComponent.SetMaterials1P"));
//
//	struct {
//		std::set<umaterialinstancedynamic*> FresnelMaterials;
//	} params;
//
//	params.FresnelMaterials = fresnel_materials;
//
//	fresnel_component->process_event(function, &params);
//}
//
//void handle_mesh_material_changed(ufresnelcomponent* fresnel_component, umeshmaterialmanagercomponent* mesh_material_manager, uskeletalmeshcomponent* mesh, int32 element_index, umaterialinterface* material, emeshplayerview mesh_player_view, umaterialinterface* old_material) {
//	static uobject* function = nullptr;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.FresnelComponent.HandleMeshMaterialChanged"));
//
//	struct {
//		umeshmaterialmanagercomponent* MeshMaterialManager;
//		uskeletalmeshcomponent* Mesh;
//		int32 ElementIndex;
//		umaterialinterface* Material;
//		emeshplayerview MeshPlayerView;
//		umaterialinterface* OldMaterial;
//	} params;
//
//	params.MeshMaterialManager = mesh_material_manager;
//	params.Mesh = mesh;
//	params.ElementIndex = element_index;
//	params.Material = material;
//	params.MeshPlayerView = mesh_player_view;
//	params.OldMaterial = old_material;
//
//	fresnel_component->process_event(function, &params);
//}

//void ashootercharacter::get_actor_bounds(bool only_colliding_components, fvector* origin, fvector* box_extent, bool include_from_child_actors)
//{
//	static uobject* function = nullptr;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.GetActorBounds"));
//
//	struct
//	{
//		bool only_colliding_components;
//		fvector origin;
//		fvector box_extent;
//		bool include_from_child_actors;
//	} params;
//
//	params.only_colliding_components = only_colliding_components;
//	params.include_from_child_actors = include_from_child_actors;
//
//	this->process_event(function, &params);
//
//	if (origin)
//		*origin = params.origin;
//
//	if (box_extent)
//		*box_extent = params.box_extent;
//}
//
//
//void ashootercharacter::auth_set_floor_movement_velocity(const fvector& movement_speed)
//{
//	static uobject* function = nullptr;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.FootstepsComponent.AuthSetFloorMovementVelocity"));
//
//	struct
//	{
//		fvector movement_speed;
//	} params;
//
//	params.movement_speed = movement_speed;
//
//	this->process_event(function, &params);
//}
//
//void ashootercharacter::on_jump(EAresMovementType movement_type)
//{
//	static uobject* function = nullptr;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.FootstepsComponent.OnJump"));
//
//	struct
//	{
//		EAresMovementType movement_type;
//	} params;
//
//	params.movement_type = movement_type;
//
//	this->process_event(function, &params);
//}
//
//void ashootercharacter::on_landed(ashootercharacter* character, const FHitResult& hit)
//{
//	static uobject* function = nullptr;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.FootstepsComponent.OnLanded"));
//
//	struct
//	{
//		ashootercharacter* character;
//		FHitResult hit;
//	} params;
//
//	params.character = character;
//	params.hit = hit;
//
//	this->process_event(function, &params);
//}
//
//void ashootercharacter::play_footstep_sound()
//{
//	static uobject* function = nullptr;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.FootstepsComponent.PlayFootstepSound"));
//
//	this->process_event(function, nullptr);
//}
//
//bool ashootercharacter::is_moving_on_ground()
//{
//	static uobject* function = nullptr;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"Engine.NavMovementComponent.IsMovingOnGround"));
//
//	struct
//	{
//		bool return_value;
//	} params;
//
//	this->process_event(function, &params);
//
//	return params.return_value;
//}
//
//bool ashootercharacter::is_moving()
//{
//	static uobject* function = nullptr;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacterMovement.IsMoving"));
//
//	struct
//	{
//		bool return_value;
//	} params;
//
//	this->process_event(function, &params);
//
//	return params.return_value;
//}
//ashooterplayerstate* ashooterplayerstate::GetPlayerState()
//{
//	static uobject* function = nullptr;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetPlayerState"));
//
//	struct
//	{
//		ashooterplayerstate* ReturnValue;
//	} params;
//
//	this->process_event(function, &params);
//
//	return params.ReturnValue;
//}
//
//int32_t ashooterplayerstate::get_money()
//{
//	static uobject* function = nullptr;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterPlayerState.GetMoney"));
//
//	struct
//	{
//		int32_t ReturnValue;
//	} params;
//
//	this->process_event(function, &params);
//
//	return params.ReturnValue;
//}

//UShooterCharacterFogOfWarComponent* ashootercharacter::get_shooter_character_fog_of_war()
//{
//	static uobject* function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetShooterCharacterFogOfWar"));
//
//	if (function)
//	{
//		struct
//		{
//			UShooterCharacterFogOfWarComponent* ReturnValue;
//		} params;
//
//		this->process_event(function, &params);
//		return params.ReturnValue;
//	}
//	return nullptr;
//}
//
//void ashootercharacter::OnTeleported(ashootercharacter* Character)
//{
//	static uobject* function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacterFogOfWarComponent.OnTeleported"));
//
//	if (function)
//	{
//		struct
//		{
//			ashootercharacter* Character;
//		} params;
//
//		params.Character = Character;
//
//		this->process_event(function, &params);
//	}
//}
//
//void ashootercharacter::modify_fog_of_war(UShooterCharacterFogOfWarComponent* fog_component)
//{
//	if (fog_component)
//	{
//		memory::write<float>(reinterpret_cast<uintptr_t>(fog_component) + 0x324, 100000.0f);
//		memory::write<float>(reinterpret_cast<uintptr_t>(fog_component) + 0x320, 100000.0f);
//		memory::write<float>(reinterpret_cast<uintptr_t>(fog_component) + 0x328, 100000.0f);
//		memory::write<float>(reinterpret_cast<uintptr_t>(fog_component) + 0x32C, 100000.0f);
//		memory::write<bool>(reinterpret_cast<uintptr_t>(fog_component) + 0x330, true);
//		memory::write<bool>(reinterpret_cast<uintptr_t>(fog_component) + 0x331, true);
//
//		UFogOfWarComponent* base_fog_component = static_cast<UFogOfWarComponent*>(fog_component);
//		memory::write<bool>(reinterpret_cast<uintptr_t>(base_fog_component) + 0x158, true);
//		memory::write<bool>(reinterpret_cast<uintptr_t>(base_fog_component) + 0x1B8, true);
//		memory::write<bool>(reinterpret_cast<uintptr_t>(base_fog_component) + 0x1B9, false);
//		memory::write<float>(reinterpret_cast<uintptr_t>(base_fog_component) + 0x15C, 1000.0f);
//		memory::write<bool>(reinterpret_cast<uintptr_t>(base_fog_component) + 0x308, true);
//
//		OnTeleported(this);
//	}
//}
//
//fstring ashootercharacter::get_player_name()
//{
//	static uobject* get_player_name_func = uobject::find_object<uobject*>(crypt(L"Engine.PlayerState.GetPlayerName"));
//	if (get_player_name_func)
//	{
//		struct { fstring ReturnValue; } params;
//		this->process_event(get_player_name_func, &params);
//		return params.ReturnValue;
//	}
//	return L"Unknown";
//}
//
//int32_t ashootercharacter::get_kills()
//{
//	static uobject* get_kills_func = uobject::find_object<uobject*>(crypt(L"ShooterGame.BasicCombatStatsComponent.GetKills"));
//	if (get_kills_func)
//	{
//		struct { int32_t ReturnValue; } params;
//		this->process_event(get_kills_func, &params);
//		return params.ReturnValue;
//	}
//}
//
//int32_t ashootercharacter::get_deaths()
//{
//	static uobject* get_deaths_func = uobject::find_object<uobject*>(crypt(L"ShooterGame.BasicCombatStatsComponent.GetDeaths"));
//	if (get_deaths_func)
//	{
//		struct { int32_t ReturnValue; } params;
//		this->process_event(get_deaths_func, &params);
//		return params.ReturnValue;
//	}
//}
//
//int32_t ashootercharacter::get_assists()
//{
//	static uobject* get_assists_func = uobject::find_object<uobject*>(crypt(L"ShooterGame.BasicCombatStatsComponent.GetAssists"));
//	if (get_assists_func)
//	{
//		struct { int32_t ReturnValue; } params;
//		this->process_event(get_assists_func, &params);
//		return params.ReturnValue;
//	}
//}
//
//float ashootercharacter::get_kd()
//{
//	static uobject* get_kd_func = uobject::find_object<uobject*>(crypt(L"ShooterGame.BasicCombatStatsComponent.GetKD"));
//	if (get_kd_func)
//	{
//		struct { float ReturnValue; } params;
//		this->process_event(get_kd_func, &params);
//		return params.ReturnValue;
//	}
//}


//UCharacterDataAsset* ashootercharacter::GetDataAsset()
//{
//	static uobject* function;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetDataAsset"));
//
//	struct
//	{
//		UCharacterDataAsset* ReturnValue;
//	} params;
//
//	this->process_event(function, &params);
//
//	return params.ReturnValue;
//}
//
//UAresInventory* ashootercharacter::GetInventory()
//{
//	static uobject* function;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetInventory"));
//
//	struct
//	{
//		UAresInventory* ReturnValue;
//	} params;
//
//	this->process_event(function, &params);
//
//	return params.ReturnValue;
//}

fvector2d aplayercontroller::project_world_to_screen(fvector world) {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.ProjectWorldLocationToScreen"));

	struct
	{
		fvector world;
		fvector2d screen;
		bool relative_viewport;
	} params;

	params.world = world;
	params.relative_viewport = true;

	this->process_event(function, &params);
	return params.screen;
}

bool aplayercontroller::project_world_location_to_screen(fvector world_location, fvector2d& screen_location, bool player_viewport_relative) {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.ProjectWorldLocationToScreen"));

	struct {
		fvector world_location;
		fvector2d screen_location;
		bool player_viewport_relativee;
		bool return_value;
	} params;
	params.world_location = world_location;
	params.player_viewport_relativee = player_viewport_relative;

	this->process_event(function, &params);
	screen_location = params.screen_location;

	return params.return_value;
}

bool aplayercontroller12::project_world_location_to_screen12(fvector world_location, fvector2d& screen_location, bool player_viewport_relative) {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.ProjectWorldLocationToScreen"));

	struct {
		fvector world_location;
		fvector2d screen_location;
		bool player_viewport_relativee;
		bool return_value;
	} params;
	params.world_location = world_location;
	params.player_viewport_relativee = player_viewport_relative;

	this->process_event(function, &params);
	screen_location = params.screen_location;

	return params.return_value;
}

fvector acknowledgedpawn::get_controlrotation()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Controller.GetControlRotation"));

	struct
	{
		fvector Rot;
	} params;

	this->process_event(function, &params);
	return params.Rot;
}

void uskeletalmeshcomponent::set_world_rotation(fvector NewRotation, bool bsweep, bool bteleport)
{

	static uobject* function = 0; if (!function) function = uobject::find_object<uobject*>(crypt(L"Engine.SceneComponent.K2_SetWorldRotation"));

	if (function == nullptr)
		return;

	struct {
		fvector NewRotation;
		bool bsweep;
		uintptr_t FHitResult;
		bool bTeleport;
	} params = { NewRotation, bsweep, 0, bteleport };

	this->process_event(function, &params);
}

fvector aplayercontroller::get_control_rotation()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Controller.GetControlRotation"));

	struct
	{
		fvector Rot;
	} params;

	this->process_event(function, &params);
	return params.Rot;
}

frotator aplayercontroller::get_control_rotation_wp()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Controller.GetControlRotation"));

	struct
	{
		frotator Rot;
	} params;

	this->process_event(function, &params);
	return params.Rot;
}

void aplayercontroller::set_control_rotation(fvector angle) {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Controller.SetControlRotation"));

	struct
	{
		fvector angle;
	} params;

	params.angle = angle;

	this->process_event(function, &params);
}

void aplayercontroller::set_control_rotation2(frotator angle) {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Controller.SetControlRotation"));

	struct
	{
		frotator angle;
	} params;

	params.angle = angle;

	this->process_event(function, &params);
}

bool uobject::k2_set_actor_location_and_rotation(fvector NewLocation, fvector NewRotation)
{
	static uobject* function = 0;
	if (!function) function = uobject::find_object<uobject*>(crypt(L"Actor.K2_SetActorLocationAndRotation"));

	struct {
		fvector NewLocation;
		fvector NewRotation;
		bool bSweep;
		FHitResult SweepHitResult;
		bool bTeleport;
		bool ReturnValue;
	} params = { NewLocation, NewRotation, false, FHitResult(), true };

	this->process_event(function, &params);

	return params.ReturnValue;
}

bool uobject::k2_set_actor_location_and_rotation2(fvector NewLocation, frotator NewRotation)
{
	static uobject* function = 0;
	if (!function) function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.K2_SetActorLocationAndRotation"));

	struct {
		fvector NewLocation;
		frotator NewRotation;
		bool bSweep;
		FHitResult SweepHitResult;
		bool bTeleport;
		bool ReturnValue;
	} params = { NewLocation, NewRotation, false, FHitResult(), true };

	this->process_event(function, &params);

	return params.ReturnValue;
}


void ashootercharacter::K2_SetActorRelativeRotation(struct fvector NewRelativeRotation, bool bSweep, bool bTeleport)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.K2_SetActorRelativeRotation"));

	struct
	{
		struct fvector NewRelativeRotation;
		bool bSweep;
		bool bTeleport;
	}params;
	params.NewRelativeRotation = NewRelativeRotation;
	params.bSweep = bSweep;
	params.bTeleport = bTeleport;
	this->process_event(function, &params);
	return;
}

void ashootercharacter::K2_SetActorRelativeRotation_rota(frotator NewRelativeRotation, bool bSweep, bool bTeleport)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.K2_SetActorRelativeRotation"));

	struct
	{
		frotator NewRelativeRotation;
		bool bSweep;
		bool bTeleport;
	}params;
	params.NewRelativeRotation = NewRelativeRotation;
	params.bSweep = bSweep;
	params.bTeleport = bTeleport;
	this->process_event(function, &params);
	return;
}

fvector AGameObject::GetObjectLocation()
{
	uobject* function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.K2_GetActorLocation"));

	struct {
		fvector Out;
	} Args;

	this->process_event(function, &Args);
	return Args.Out;
}

float AGameObject::GetObjectHealth()
{
	uobject* function = uobject::find_object<uobject*>(crypt(L"ShooterGame.GameObject.GetHealth"));

	struct {
		float Out;
	} Args;

	this->process_event(function, &Args);
	return Args.Out;
}


uobject* Class::ShooterGameObject()
{
	return  uobject::find_object<uobject*>(crypt(L"ShooterGame.GameObject"));
}

uobject* GameplayStatics::GameplayStatics()
{
	return  uobject::find_object<uobject*>(crypt(L"Engine.Default__GameplayStatics"));
}

UDisplayNameManager* UDisplayNameManager::get_display_name_manager() {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.AresClientGameInstance.GetDisplayNameManager");

	struct
	{
		UDisplayNameManager* output;
	} params;

	this->process_event(function, &params);

	return params.output;
}


fstring UDisplayNameManager::get_display_name(fstring subject) {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.DisplayNameManager.GetDisplayName");

	struct
	{
		fstring subject;
		fstring output;
	} params;

	params.subject = subject;

	this->process_event(function, &params);

	return params.output;
}


uskeletalmeshcomponent* ashootercharacter::get_mesh() {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetPawnMesh"));

	struct
	{
		uskeletalmeshcomponent* output;
	} params;

	this->process_event(function, &params);

	return params.output;
}



uskeletalmeshcomponent* currentequippable::GetMesh1P()
{

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresEquippable.GetMesh1P"));

	struct
	{
		uskeletalmeshcomponent* Out;
	}Parameters;
	this->process_event(function, &Parameters);
	return Parameters.Out;
}

fvector uskeletalmeshcomponent::get_control_rotationn()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Controller.GetControlRotation"));

	struct
	{
		fvector Rot;
	} params;

	this->process_event(function, &params);
	return params.Rot;
}

//void UMaterialInstanceDynamic::set_vector_parameter_value(fname parameter_name, flinearcolor value)
//{
//	static uobject* function;
//	if (!function)
//		function = uobject::find_object<uobject*>(L"MaterialInstanceDynamic.SetVectorParameterValue");
//
//	struct {
//		fname parameter_name;
//		flinearcolor value;
//	} params = { parameter_name, value };
//
//	this->process_event(function, &params);
//}
//
// 
//
//void UMaterialInstanceDynamic::set_texture_parameter_value(fname parameter_name, uobject* texture)
//{
//	static uobject* function;
//	if (!function)
//		function = uobject::find_object<uobject*>(L"MaterialInstanceDynamic.SetTextureParameterValue");
//
//	struct {
//		fname parameter_name;
//		uobject* value;
//	} params = { parameter_name, texture };
//
//	this->process_event(function, &params);
//}
//
//void UPrimitiveComponent::set_material(int32_t element_index, uobject* material)
//{
//	static uobject* function;
//	if (!function)
//		function = uobject::find_object<uobject*>(L"Engine.PrimitiveComponent.SetMaterial");
//
//	struct {
//		int32_t element_index;
//		uobject* material;
//	} params = { element_index, material };
//
//	this->process_event(function, &params);
//}
//
//void UPrimitiveComponent::CreateAndSetMaterialInstanceDynamicFromMaterial(int32_t element_index, uobject* parent)
//{
//	static uobject* function;
//	if (!function)
//		function = uobject::find_object<uobject*>(L"Engine.PrimitiveComponent.CreateAndSetMaterialInstanceDynamicFromMaterial");
//
//	struct {
//		int32_t element_index;
//		uobject* parent;
//	} params = { element_index, parent };
//
//	this->process_event(function, &params);
//}
//
//UMaterialInstanceDynamic* UPrimitiveComponent::get_material(int32_t element_index)
//{
//	static uobject* function;
//	if (!function)
//		function = uobject::find_object<uobject*>(L"Engine.PrimitiveComponent.GetMaterial");
//
//	struct {
//		int32_t element_index;
//		UMaterialInstanceDynamic* return_value;
//	} params = { element_index };
//
//	this->process_event(function, &params);
//
//	return params.return_value;
//}
//
//int32_t UPrimitiveComponent::get_num_materials()
//{
//	static uobject* function;
//	if (!function)
//		function = uobject::find_object<uobject*>(L"Engine.PrimitiveComponent.GetNumMaterials");
//
//	struct {
//		int32_t return_value;
//	} params;
//
//	this->process_event(function, &params);
//
//	return params.return_value;
//}
//
//e_blend_mode UMaterialInterface::GetBlendMode() {
//	uobject* function = uobject::find_object<uobject*>(L"MaterialInterface.GetBlendMode");
//
//	struct {
//		e_blend_mode ReturnValue;
//	} Params = {  };
//
//	this->process_event(function, &Params);
//
//	return Params.ReturnValue;
//}
//
//void UMaterialInstanceDynamic::SetVectorParameterValue(fname ParameterName, flinearcolor Value) {
//	uobject* Function = uobject::find_object<uobject*>(L"MaterialInstanceDynamic.SetVectorParameterValue");
//
//	struct {
//		fname ParameterName;
//		flinearcolor Value;
//	} Params = { ParameterName, Value };
//
//	this->ProcessEvent(Function, &Params);
//}

void uskeletalmeshcomponent::set_materials(const tarray<fskeletalmaterial>& in_materials)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.SkeletalMesh.SetMaterials"));

	struct
	{
		tarray<fskeletalmaterial> in_materials;
	} params;

	params.in_materials = in_materials;

	this->process_event(function, &params);
}

void UPrimitiveComponent::set_material(int32_t element_index, uobject* material) {
	static uobject* Function = nullptr;
	if (!Function)
		Function = uobject::find_object<uobject*>(L"Engine.PrimitiveComponent.SetMaterial");

	struct params_t {
		int32_t element_index;
		uobject* material;
	} params = { element_index, material };

	process_event(Function, &params);
}

UMaterialInstanceDynamic* UPrimitiveComponent::get_material(int32_t element_index) {
	static uobject* Function = nullptr;
	if (!Function)
		Function = uobject::find_object<uobject*>(L"Engine.PrimitiveComponent.GetMaterial");

	struct params_t {
		int32_t element_index;
		UMaterialInstanceDynamic* return_value;
	} params = { element_index };

	process_event(Function, &params);
	return params.return_value;
}

int32_t UPrimitiveComponent::get_num_materials() {
	static uobject* Function = nullptr;
	if (!Function)
		Function = uobject::find_object<uobject*>(L"Engine.PrimitiveComponent.GetNumMaterials");

	struct params_t {
		int32_t return_value;
	} params = {};

	process_event(Function, &params);
	return params.return_value;
}

e_blend_mode UMaterialInstanceDynamic::get_blend_mode() {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(L"MaterialInterface.GetBlendMode");

	struct params_t {
		e_blend_mode return_value;
	} params = {};

	process_event(function, &params);
	return params.return_value;
}

void UMaterialInstanceDynamic::set_vector_parameter_value2(fname parameter_name, flinearcolor value) {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(L"MaterialInstanceDynamic.SetVectorParameterValue");

	struct params_t {
		fname parameter_name;
		flinearcolor value;
	} params = { parameter_name, value };

	process_event(function, &params);
}

void UMaterialInstanceDynamic::set_scalar_parameter_value(fname parameter_name, double value)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"MaterialInstanceDynamic.SetScalarParameterValue");

	struct {
		fname parameter_name;
		float value;
	} params = { parameter_name, value };

	this->process_event(function, &params);
}

void UMaterialInstanceDynamic::set_scalar_parameter_value1(fname parameter_name, double value)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"MaterialInstanceDynamic.SetScalarParameterValue");

	struct {
		fname parameter_name;
		double value;
	} params = { parameter_name, value };

	this->process_event(function, &params);
}
//void UMaterialInstanceDynamic::set_vector_parameter_value(FName_ parameter_name, flinearcolor value) {
//	static uobject* function = nullptr;
//	if (!function)
//		function = uobject::find_object<uobject*>(L"MaterialInstanceDynamic.SetVectorParameterValue");
//
//	struct params_t {
//		FName_ parameter_name;
//		int shift;
//		flinearcolor value;
//	} params = { parameter_name, 0, value };
//
//	process_event(function, &params);
//}
//
//void UMaterialInstanceDynamic::set_scalar_parameter_value(FName_ parameter_name, float value) {
//	static uobject* function = nullptr;
//	if (!function)
//		function = uobject::find_object<uobject*>(L"MaterialInstanceDynamic.SetScalarParameterValue");
//
//	struct params_t {
//		FName_ parameter_name;
//		int shift;
//		float value;
//	} params = { parameter_name, 0, value };
//
//	process_event(function, &params);
//}
//
//void UMaterialInstanceDynamic::set_texture_parameter_value(FName_ parameter_name, uobject* texture) {
//	static uobject* function = nullptr;
//	if (!function)
//		function = uobject::find_object<uobject*>(L"MaterialInstanceDynamic.SetTextureParameterValue");
//
//	struct params_t {
//		FName_ parameter_name;
//		int shift;
//		uobject* value;
//	} params = { parameter_name, 0, texture };
//
//	process_event(function, &params);
//}

int32_t uskeletalmeshcomponent::get_num_materials() {
	static uobject* Function = nullptr;

	if (!Function)
		Function = uobject::find_object<uobject*>(L"Engine.PrimitiveComponent.GetNumMaterials");

	struct params_t {
		int32_t return_value;
	} params = {};

	process_event(Function, &params);
	return params.return_value;
}


uobject* uskeletalmeshcomponent::create_and_set_material_instance_dynamic_from_material(int32_t element_index, uobject* parent) {
	static uobject* fn = nullptr;

	if (!fn)
		fn = uobject::find_object<uobject*>(L"Engine.PrimitiveComponent.CreateAndSetMaterialInstanceDynamicFromMaterial");

	struct params_t {
		int32_t element_index;
		uobject* parent;
		uobject* return_value;
	} params = { element_index, parent };

	process_event(fn, &params);
	return params.return_value;
}

void UMaterialInstanceDynamic::set_vector_parameter_value1(fname parameter_name, flinearcolor value) {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(L"MaterialInstanceDynamic.SetVectorParameterValue");

	struct params_t {
		fname parameter_name;
		int shift;
		flinearcolor value;
	} params = { parameter_name, 0, value };

	process_event(function, &params);
}

void UMaterialInstanceDynamic::set_texture_parameter_value(fname parameter_name, uobject* texture) {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(L"MaterialInstanceDynamic.SetTextureParameterValue");

	struct params_t {
		fname parameter_name;
		int shift;
		uobject* value;
	} params = { parameter_name, 0, texture };

	process_event(function, &params);
}

uskeletalmeshcomponent* ashootercharacter::GetOverlayMesh1P()
{


	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetOverlayMesh1P"));

	struct
	{
		uskeletalmeshcomponent* Out;
	}Parameters;
	this->process_event(function, &Parameters);
	return Parameters.Out;
}

uskeletalmeshcomponent* ashootercharacter::GetMesh1P()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetMesh1P"));

	struct
	{
		uskeletalmeshcomponent* returnvalue;
	} parameters;

	this->process_event(function, &parameters);

	return parameters.returnvalue;
}

UPrimitiveComponent* acknowledgedpawn::GetOverlayMesh1P2()
{


	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetOverlayMesh1P"));

	struct
	{
		UPrimitiveComponent* Out;
	}Parameters;
	this->process_event(function, &Parameters);
	return Parameters.Out;
}

UPrimitiveComponent* acknowledgedpawn::GetMesh1P2()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetMesh1P"));

	struct
	{
		UPrimitiveComponent* returnvalue;
	} parameters;

	this->process_event(function, &parameters);

	return parameters.returnvalue;
}

uinventory* ashootercharacter::get_inventory() {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetInventory"));

	struct
	{
		uinventory* output;
	} params;

	this->process_event(function, &params);

	return params.output;
}

currentequippable* uinventory::get_current_equippable()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresInventory.GetCurrentEquippable"));

	struct
	{
		currentequippable* output;
	} params;

	this->process_event(function, &params);

	return params.output;
}



fvector ashootercharacter::k2_get_actor_location()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.K2_GetActorLocation"));

	struct
	{
		fvector Out;
	} params;
	this->process_event(function, &params);

	return params.Out;
}

frotator ashootercharacter::k2_get_actor_rotation() {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.K2_GetActorRotation"));

	struct {
		frotator return_value;
	} params;

	this->process_event(function, &params);
	return params.return_value;
}

fvector acknowledgedpawn::k2_get_actor_location1()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.K2_GetActorLocation"));

	struct
	{
		fvector Out;
	} params;
	this->process_event(function, &params);

	return params.Out;
}

frotator acknowledgedpawn::k2_get_actor_rotation1() {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.K2_GetActorRotation"));

	struct {
		frotator return_value;
	} params;

	this->process_event(function, &params);
	return params.return_value;
}

bool ashootercharacter::k2_set_actor_rotation(frotator& NewRotation, bool bTeleportPhysics)
{
	static uobject* func;
	if (!func)
		func = uobject::find_object<uobject*>(crypt(L"Function Engine.Actor.K2_SetActorRotation"));

	struct
	{
		frotator NewRotation;
		bool bTeleportPhysics;
		bool ReturnValue;
	} params;

	params.NewRotation = NewRotation;
	params.bTeleportPhysics = bTeleportPhysics;

	this->process_event(func, &params);

	return params.ReturnValue;
}

void ashootercharacter::set_rel_actr_root(struct fvector NewRelativeRotation, bool bSweep, bool bTeleport)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.K2_SetActorRelativeRotation"));

	struct
	{
		struct fvector NewRelativeRotation;
		bool bSweep;
		bool bTeleport;
	}params;
	params.NewRelativeRotation = NewRelativeRotation;
	params.bSweep = bSweep;
	params.bTeleport = bTeleport;
	this->process_event(function, &params);
	return;
}

uobject* ashootercharacter::get_character_icon()
{

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetCharacterIcon"));

	struct
	{
		uobject* Out;
	} params;

	this->process_event(function, &params);
	return params.Out;
}


void ashootercharacter::Set3pMeshVisible(bool val)
{
	uobject* Function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.Set3PMeshVisible"));
	if (!Function)
	{
		return;
	}
	struct
	{
		bool a1;
	}Parameters;
	Parameters.a1 = val;
	this->process_event(Function, &Parameters);
	return;
}


//bool ashootercharacter::can_jump() {
//	static uobject* function;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"Engine.Character.CanJump"));
//
//	struct
//	{
//		bool output;
//	} params;
//
//	this->process_event(function, &params);
//
//	return params.output;
//}
//
//bool ashootercharacter::can_jump_inter() {
//	static uobject* function;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"Engine.Character.CanJumpInternal"));
//
//	struct
//	{
//		bool output;
//	} params;
//
//	this->process_event(function, &params);
//
//	return params.output;
//}
//
//bool ashootercharacter::jump() {
//	static uobject* function;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"Engine.Character.Jump"));
//
//	struct
//	{
//		bool jump;
//	} params;
//
//	params.jump;
//	this->process_event(function, &params);
//	return params.jump;
//}
//
//bool ashootercharacter::stop_jump() {
//	static uobject* function;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"Engine.Character.StopJumping"));
//
//	struct
//	{
//		bool stopjump;
//	} params;
//
//	params.stopjump;
//	this->process_event(function, &params);
//	return params.stopjump;
//}
//
//bool ashootercharacter::gh0st() {
//	static uobject* function;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"Engine.Character.ClientCheatGhost"));
//
//	struct
//	{
//		bool invic;
//	} params;
//
//	this->process_event(function, &params);
//
//	params.invic;
//	return params.invic;
//}

bool ashootercharacter::is_alive() {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.IsAlive"));

	struct
	{
		bool output;
	} params;

	this->process_event(function, &params);

	return params.output;
}

bool ashootercharacter::is_dead_and_settled() {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.IsDeadAndSettled"));

	struct
	{
		bool Out;
	} params;

	this->process_event(function, &params);
	return params.Out;
}

bool ashootercharacter::was_invisible() {
	return memory::read<bool>(class_ptr + offsets::was_invisible);
}

float ashootercharacter::health() {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetHealth"));

	struct
	{
		float output;
	} params;

	this->process_event(function, &params);

	return params.output;
}

player_state* ashootercharacter::get_player_state() {
	return memory::read<player_state*>(class_ptr + offsets::player_state);
}

float ashootercharacter::shield() {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetShield"));

	struct
	{
		float output;
	} params;

	this->process_event(function, &params);

	return params.output;
}

//fstring player_state::PlayerNamePrivate() {
//	return memory::read<fstring>(class_ptr + offsets::PlayerNamePrivate);
//}
//
//platform_player* ashootercharacter::get_plateform_player() {
//	return memory::read<platform_player*>(class_ptr + offsets::PlatformPlayer);
//}
//
//int platform_player::get_competitive_tier() {
//	return memory::read<int>(class_ptr + offsets::CompetitiveTier);
//}

bool ITextChatConversation::send_message(ftext message) {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.TextChatConversation.SendMessage");

	struct {
		ftext message;
		bool return_value;
	} params;

	params.message = message;

	this->process_event(function, &params);

	return params.return_value;
}

UThreadedChatManager* UThreadedChatManager::GetThreadedChatManager(uobject* world_context) {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.ThreadedChatManager.GetThreadedChatManager");

	struct {
		uobject* world_context;
		UThreadedChatManager* return_value;
	} params;

	params.world_context = world_context;

	GetDefaultObj()->process_event(function, &params);

	return params.return_value;
}

void UThreadedChatManager::send_chat_message_v2(EChatRoomType room_type, ftext message) {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.ThreadedChatManager.SendChatMessageV2");

	struct {
		EChatRoomType room_type;
		ftext message;
	} params;

	params.room_type = room_type;
	params.message = message;

	this->process_event(function, &params);
}

EChatRoomType ITextChatConversation::get_conversation_type() {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.TextChatConversation.GetConversationType");

	struct {
		EChatRoomType return_value;
	} params;

	this->process_event(function, &params);

	return params.return_value;
}

fvector uskeletalmeshcomponent::get_bone_location(int32_t index) {
	fmatrix matrix;
	reinterpret_cast<fmatrix* (__fastcall*)(uskeletalmeshcomponent*, fmatrix*, int)>(memory::module_base + offsets::bone_matrix)(this, &matrix, index);
	return { matrix.wplane.x, matrix.wplane.y, matrix.wplane.z };
}

uobject* uengine::font() {
	return memory::read<ugameinstance*>(class_ptr + offsets::font);
}

uengine* ugameinstance::get_uengine() {
	return memory::read<uengine*>(class_ptr + offsets::engine);
}

fvector math::SmoothAim(fvector target, fvector delta_rotation, float smooth) {
	fvector diff = target - delta_rotation;
	normalize(diff);
	return delta_rotation + diff / smooth;
}

double math::distance_2d(fvector2d v1, fvector2d v2)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetMathLibrary.Distance2D"));

	struct
	{
		fvector2d v1;
		fvector2d v2;
		double output;
	} params;

	params.v1 = v1;
	params.v2 = v2;

	variables.math_system->process_event(function, &params);
	return params.output;
}

float math::atan(float A)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetMathLibrary.Atan"));

	struct
	{
		float A;
		float output;
	} params;

	params.A = A;

	variables.math_system->process_event(function, &params);
	return params.output;
}

float math::atan2(float Y, float X)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetMathLibrary.Atan2"));

	struct
	{
		float Y;
		float X;
		float output;
	} params;

	params.Y = Y;
	params.X = X;

	variables.math_system->process_event(function, &params);
	return params.output;
}

float math::cos(float A)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetMathLibrary.Cos"));

	struct
	{
		float A;
		float output;
	} params;

	params.A = A;

	variables.math_system->process_event(function, &params);
	return params.output;
}

float math::sin(float A)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetMathLibrary.Sin"));

	struct
	{
		float A;
		float output;
	} params;

	params.A = A;

	variables.math_system->process_event(function, &params);
	return params.output;
}

float math::sqrt(float A)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetMathLibrary.Sqrt"));

	struct
	{
		float A;
		float output;
	} params;

	params.A = A;

	variables.math_system->process_event(function, &params);
	return params.output;
}

//fvector math::find_look_at_rotation(fvector start, fvector end)
//{
//	static uobject* function;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetMathLibrary.FindLookAtRotation"));
//
//	struct
//	{
//		fvector start;
//		fvector end;
//		fvector output;
//	} params;
//
//	params.start = start;
//	params.end = end;
//
//	variables.math_system->process_event(function, &params);
//	return params.output;
//}

fvector math::find_look_at_rotation(fvector start, fvector end)
{

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetMathLibrary.FindLookAtRotation").decrypt());

	struct
	{
		fvector start;
		fvector end;
		fvector output;
	} params;

	params.start = start;
	params.end = end;

	variables.math_system->process_event(function, &params);
	return params.output;
}

frotator math::find_look_at_rotation2(fvector start, fvector target)
{
	static uobject* function = 0;
	if (!function) function = uobject::find_object<uobject*>(crypt(L"Engine.KismetMathLibrary.FindLookAtRotation"));

	struct {
		fvector start;
		fvector target;
		frotator output;
	} params = { start, target };

	variables.math_system->process_event(function, &params);

	return params.output;
}

bool math::class_is_child_of(uobject* test_class, uobject* parent_class)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetMathLibrary.ClassIsChildOf"));

	struct
	{
		uobject* test_class;
		uobject* parent_class;
		bool return_value;
	} params;

	params.test_class = test_class;
	params.parent_class = parent_class;

	variables.math_system->process_event(function, &params);
	return params.return_value;
}

fvector aplayercameramanager::get_camera_location()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerCameraManager.GetCameraLocation"));

	struct
	{
		fvector output;
	} params;

	this->process_event(function, &params);
	return params.output;
}


uobject* AresOutlineRendering::Static_Class()
{
	return uobject::find_object<uobject*>(crypt(L"Renderer.Default__AresOutlineRendering"));
}

void AresOutlineRendering::SetOutlineColorsForRender(uworld* WorldContextObject, flinearcolor AllyColor, flinearcolor EnemyColor)
{
	uobject* function = uobject::find_object<uobject*>(crypt(L"Renderer.AresOutlineRendering.SetOutlineColorsForRender"));

	struct {
		uobject* WorldContextObject;
		flinearcolor AllyColor;
		flinearcolor EnemyColor;
	}Parameters;
	Parameters.WorldContextObject = WorldContextObject;
	Parameters.AllyColor = AllyColor;
	Parameters.EnemyColor = EnemyColor;
	function->ProcessEvent(Static_Class(), function, &Parameters);

}

struct USkeletalMeshComponentRE
{


};

void uskeletalmeshcomponent::SetOutlineMode(EAresOutlineMode Mode)
{
	uobject* function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresOutlineComponent.SetOutlineMode"));
	struct
	{
		EAresOutlineMode Mode;
	}Parameters;
	Parameters.Mode = Mode;

	function->ProcessEvent(this, function, &Parameters);
}

fvector aplayercameramanager::get_camera_rotation()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerCameraManager.GetCameraRotation"));

	struct
	{
		fvector output;
	} params;

	this->process_event(function, &params);
	return params.output;
}

frotator aplayercameramanager::get_camera_rotation_fr()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerCameraManager.GetCameraRotation"));

	struct
	{
		frotator output;
	} params;

	this->process_event(function, &params);
	return params.output;
}

aplayercameramanager* aplayercontroller::get_camera_manager() {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerController.GetPlayerCameraManager"));

	struct
	{
		aplayercameramanager* output;
	} params;

	this->process_event(function, &params);

	return params.output;
}

void aplayercontroller::GetInputMouseDelta(float& DeltaX, float& DeltaY) {
	static uobject* Function;
	if (!Function)
		Function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.GetInputMouseDelta"));
	struct
	{
		float DeltaX;
		float DeltaY;
	}Parameters;

	this->process_event(Function, &Parameters);
	DeltaX = Parameters.DeltaX;
	DeltaY = Parameters.DeltaY;
}

float aplayercontroller::GetMouseSensitivity()
{
	static uobject* Function;
	if (!Function)
		Function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterPlayerController.GetMouseSensitivity"));
	struct {
		float Out;
	} Parameters;

	this->process_event(Function, &Parameters);
	return Parameters.Out;
}

void aplayercontroller::K2_SetActorRelativeRotation(fvector NewRelativeRotation, bool bSweep, bool bTeleport)
{
	static uobject* Function;
	if (!Function) Function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.K2_SetActorRelativeRotation"));

	struct
	{
		fvector NewRelativeRotation;
		bool bSweep;
		bool bTeleport;
	}Parameters;
	Parameters.NewRelativeRotation = NewRelativeRotation;
	Parameters.bSweep = bSweep;
	Parameters.bTeleport = bTeleport;
	this->process_event(Function, &Parameters);
}

//void aplayercontroller::set_fov(float fov)
//{
//
//
//	static uobject* function;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerController.SetFOV"));
//
//	struct {
//		float fov;
//	}Args;
//	Args.fov = fov;
//	function->process_event2(this, function, &Args);
//}


void aplayercontroller::set_fov(float fov)
{
	uobject* function = uobject::find_object1(crypt(L"ShooterGame.AresPlayerController.SetFOV"));


	struct {
		float fov;
	}Args;
	Args.fov = fov;
	this->process_event(function, &Args);
}

void UCameraComponent::GetCameraView(float DeltaTime, FMinimalViewInfo* DesiredView)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.CameraComponent.GetCameraView"));

	struct
	{
		float DeltaTime;
		FMinimalViewInfo* DesiredView;
	} params;

	params.DeltaTime = DeltaTime;
	params.DesiredView = DesiredView;

	this->process_event(function, &params);

	if (DesiredView)
	{
		if (globals::misc::FovChangor)
		{
			DesiredView->DesiredFOV = globals::misc::vchr;  // senin var olan FOV değiştiricin
		}
	}
}

void aplayercameramanager::SetAspectRatio(float InAspectRatio)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.CameraComponent.SetAspectRatio"));

	if (function)
	{
		struct
		{
			float InAspectRatio;
		} params;

		params.InAspectRatio = InAspectRatio;

		this->process_event(function, &params);
	}
}

void ashootercharacter::SetFieldOfView(float InFieldOfView)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.CameraComponent.SetFieldOfView"));

	if (function)
	{
		struct
		{
			float InFieldOfView;
		} params;

		params.InFieldOfView = InFieldOfView;

		this->process_event(function, &params);
	}
}

bool ashootercharacter::CanJump() {
	static uobject* Function = uobject::find_object<uobject*>(crypt(L"Engine.Character.CanJump"));
	if (!Function) {
		return false;
	}
	struct {
		bool Out;
	} Parameters;

	this->process_event(Function, &Parameters);
	return Parameters.Out;
}

bool ashootercharacter::CanJumpInternal() {
	static uobject* Function = uobject::StaticFindObject(0, 0, L"Engine.Character.CanJumpInternal", false);
	if (!Function) {
		return false;
	}
	struct {
		bool Out;
	} Parameters;

	this->process_event(Function, &Parameters);
	return Parameters.Out;
}

void ashootercharacter::Jump() {
	SPOOF_FUNC
		static uobject* Function = uobject::find_object<uobject*>(crypt(L"Engine.Character.Jump"));
	if (!Function) {
		return;
	}
	struct {

	} Parameters;

	this->process_event(Function, &Parameters);
}

void ashootercharacter::OnJump() {
	static uobject* Function = uobject::find_object<uobject*>(crypt(L"Engine.Character.OnJumped"));
	if (!Function) {
		return;
	}
	struct {

	} Parameters;

	this->process_event(Function, &Parameters);
}

void ashootercharacter::StopJumping() {
	static uobject* Function = uobject::find_object<uobject*>(crypt(L"Engine.Character.StopJumping"));
	if (!Function) {
		return;
	}
	struct {

	} Parameters;

	this->process_event(Function, &Parameters);
}

void aplayercontroller::SimulateInputKey(fkey Key, bool bPressed) {
	SPOOF_FUNC
		static uobject* Function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresPlayerController.SimulateInputKey"));
	if (!Function) {
		return;
	}
	struct {
		fkey Key;
		bool bPressed;
	} Parameters;
	Parameters.Key = Key;
	Parameters.bPressed = bPressed;
	this->process_event(Function, &Parameters);
}

bool aplayercontroller::is_input_key_down(aplayercontroller* controller, const fkey key)
{
	static uobject* Function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.IsInputKeyDown"));

	struct
	{
		fkey Key;
		bool ReturnValue;
	} params;

	params.Key = key;

	this->process_event(Function, &params);
	return params.ReturnValue;
}

acknowledgedpawn* aplayercontroller::get_acknowledged_pawn() {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Controller.K2_GetPawn"));

	struct
	{
		acknowledgedpawn* output;
	} params;

	this->process_event(function, &params);
	return params.output;
}


currentequippable* inventorymanager::get_current_weapon() {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresInventory.GetCurrentEquippable"));

	struct
	{
		currentequippable* out;
	} params;

	this->process_event(function, &params);
	return params.out;
}

equippable_skin_data_asset* currentequippable::get_skin_data_asset() {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresEquippable.GetEquippableSkinDataAsset"));

	struct {
		equippable_skin_data_asset* Out;
	} params;

	this->process_event(function, &params);
	return params.Out;
}

fvector2d ucanvas::get_screen_size() {
	return fvector2d(memory::read<int32_t>(class_ptr + offsets::get_screen_size1), memory::read<int32_t>(class_ptr + offsets::get_screen_size2));
}

void ucanvas::k2_drawline(fvector2d screenpos_a, fvector2d screenpos_b, float thickness, flinearcolor color) {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Canvas.K2_DrawLine"));

	struct
	{
		fvector2d screenpos_a;
		fvector2d screenpos_b;
		float thickness;
		flinearcolor color;
	} params;

	params.screenpos_a = screenpos_a;
	params.screenpos_b = screenpos_b;
	params.thickness = thickness;
	params.color = color;

	this->process_event(function, &params);
}

void ucanvas::K2_DrawBox(fvector2d ScreenPosition, fvector2d ScreenSize, float Thickness, flinearcolor RenderColor) {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Canvas.K2_DrawBox"));

	struct
	{
		fvector2d ScreenPosition;
		fvector2d ScreenSize;
		float Thickness;
		flinearcolor RenderColor;
	} params;

	params.ScreenPosition = ScreenPosition;
	params.ScreenSize = ScreenSize;
	params.Thickness = Thickness;
	params.RenderColor = RenderColor;

	this->process_event(function, &params);
}

void ucanvas::k2_drawtransparentline(const fvector2d& screen_position_a, const fvector2d& screen_position_b, float thickness, const flinearcolor& render_color) {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Canvas.K2_DrawTransparentLine"));

	struct {
		fvector2d ScreenPositionA;
		fvector2d ScreenPositionB;
		float Thickness;
		flinearcolor RenderColor;
	} params;

	params.ScreenPositionA = screen_position_a;
	params.ScreenPositionB = screen_position_b;
	params.Thickness = thickness;
	params.RenderColor = render_color;

	this->process_event(function, &params);
}


void ucanvas::draw_material_on_screen(ucanvas* canvas, umaterialinterface* material, const fvector2d& screen_position, const fvector2d& screen_size) {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Canvas.K2_DrawMaterial"));

	struct {
		umaterialinterface* RenderMaterial;
		fvector2d ScreenPosition;
		fvector2d ScreenSize;
		fvector2d CoordinatePosition;
		fvector2d CoordinateSize;
		float Rotation;
		fvector2d PivotPoint;
	} params;

	params.RenderMaterial = material;
	params.ScreenPosition = screen_position;
	params.ScreenSize = screen_size;
	params.CoordinatePosition = fvector2d(0.0f, 0.0f); // Default coordinate position
	params.CoordinateSize = fvector2d(1.0f, 1.0f); // Default coordinate size
	params.Rotation = 0.0f; // No rotation
	params.PivotPoint = fvector2d(0.5f, 0.5f); // Center pivot point

	canvas->process_event(function, &params);
}

void ucanvas::k2_drawtexture(uobject* texture, fvector2d screen_position, fvector2d screen_size, fvector2d coordinate_position, fvector2d coordinate_size, flinearcolor render_color, e_blend_mode blend_mode, float rotation, fvector2d pivot_point)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Canvas.K2_DrawTexture"));

	struct {
		uobject* texture;
		fvector2d screen_position;
		fvector2d screen_size;
		fvector2d coordinate_position;
		fvector2d coordinate_size;
		flinearcolor render_color;
		e_blend_mode blend_mode;
		float rotation;
		fvector2d pivot_point;
	} params;
	params.texture = texture;
	params.screen_position = screen_position;
	params.screen_size = screen_size;
	params.coordinate_position = coordinate_position;
	params.coordinate_size = coordinate_size;
	params.render_color = render_color;
	params.blend_mode = blend_mode;
	params.rotation = rotation;
	params.pivot_point = pivot_point;

	this->process_event(function, &params);
}

void ucanvas::k2_drawpolygon(utexture* render_texture, const fvector2d& screen_position, const fvector2d& radius, int32_t number_of_sides, const flinearcolor& render_color) {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Canvas.K2_DrawPolygon"));

	struct {
		utexture* RenderTexture;
		fvector2d ScreenPosition;
		fvector2d Radius;
		int32_t NumberOfSides;
		flinearcolor RenderColor;
	} params;

	params.RenderTexture = render_texture;
	params.ScreenPosition = screen_position;
	params.Radius = radius;
	params.NumberOfSides = number_of_sides;
	params.RenderColor = render_color;

	this->process_event(function, &params);
}

void ucanvas::k2_drawtriangle(utexture* render_texture, const tarray<fcanvasuvtri>& triangles) {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Canvas.K2_DrawTriangle"));

	struct {
		utexture* RenderTexture;
		tarray<fcanvasuvtri> Triangles;
	} params;

	params.RenderTexture = render_texture;
	params.Triangles = triangles;

	this->process_event(function, &params);
}

void ucanvas::k2_drawtext(uobject* font, fstring text, fvector2d screenposition, fvector2d scale, flinearcolor color, float kerning, flinearcolor shadowcolor, fvector2d shadowoffset, bool centrex, bool centrey, bool outline, flinearcolor outlinecolor)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Canvas.K2_DrawText"));

	struct
	{
		uobject* font;
		fstring text;
		fvector2d screenposition;
		fvector2d scale;
		flinearcolor color;
		float kerning;
		flinearcolor shadowcolor;
		fvector2d shadowoffset;
		bool centrex;
		bool centrey;
		bool outline;
		flinearcolor outlinecolor;
	} params;

	params.font = font;
	params.text = text;
	params.screenposition = screenposition;
	params.scale = scale;
	params.color = color;
	params.kerning = kerning;
	params.shadowcolor = shadowcolor;
	params.shadowoffset = shadowoffset;
	params.centrex = centrex;
	params.centrey = centrey;
	params.outline = outline;
	params.outlinecolor = outlinecolor;

	this->process_event(function, &params);
}

fvector2d ucanvas::get_string_size(uobject* RenderFont, const wchar_t* RenderText, const fvector2d& Scale)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Canvas.K2_TextSize"));

	struct
	{
		uobject* RenderFont;
		fstring RenderText;
		fvector2d Scale;
		fvector2d ReturnValue;
	} params;

	params.RenderFont = RenderFont;
	params.RenderText = RenderText;
	params.Scale = Scale;

	this->process_event(function, &params);

	return params.ReturnValue;
}

ares_client_game_instace* ares_instance::get_ares_client_game_instance(uobject* world_context) {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresClientGameInstance.GetAresClientGameInstance"));

	struct {
		uobject* uworld;
		ares_client_game_instace* return_value;
	} params = { world_context };

	variables.ares_instance->process_event(function, &params);

	return params.return_value;
}

struct USkeletalMeshComponent_hand {
	UMaterialInterface* GetMaterial(int32_t ElementIndex)
	{

		static uobject* function;
		if (!function)
			function = uobject::find_object<uobject*>(crypt(L"Engine.PrimitiveComponent.GetMaterial"));
		struct
		{
			int32_t ElementIndex;
			UMaterialInterface* ReturnValue;
		} Parameters;
		Parameters.ElementIndex = ElementIndex;
		function->process_event2(this, function, &Parameters);
		return Parameters.ReturnValue;
	}

	void SetMaterial(int32_t ElementIndex, UMaterialInterface* Material)
	{

		static uobject* function;
		if (!function)
			function = uobject::find_object<uobject*>(crypt(L"Engine.PrimitiveComponent.SetMaterial"));
		struct
		{
			int32_t ElementIndex;
			UMaterialInterface* Material;
		} Parameters;
		Parameters.ElementIndex = ElementIndex;
		Parameters.Material = Material;
		function->process_event2(this, function, &Parameters);
	}

};

inventorymanager* ares_client_game_instace::get_inventory_manager() {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresClientGameInstance.GetInventoryManager"));

	struct {
		inventorymanager* out;
	} result;


	this->process_event(function, &result);
	return result.out;
}

arsenal_view_controller* ares_client_game_instace::get_aresnal_view_controller() {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresClientGameInstance.GetArsenalViewController"));

	struct {
		arsenal_view_controller* out;
	} params;

	this->process_event(function, &params);
	return params.out;
}

equippable_skin_inventory_model* equippable_inventory_model::get_equipped_skin_model() {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.EquippableInventoryModel.GetEquippedSkin"));

	struct {
		equippable_skin_inventory_model* return_value;
	} params;

	this->process_event(function, &params);
	return params.return_value;

}

equippable_charm_instance_inventory_model* equippable_inventory_model::get_equipped_charm_instance() {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.EquippableInventoryModel.GetEquippedCharmInstance"));

	struct {
		equippable_charm_instance_inventory_model* return_value;
	} params;

	this->process_event(function, &params);
	return params.return_value;
}

tarray<equippable_inventory_model*> arsenal_view_model::get_gun_models() {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ArsenalViewModel.GetGunModels"));

	struct {
		tarray<equippable_inventory_model*> out;
	} params;

	this->process_event(function, &params);
	return params.out;
}

arsenal_view_model* arsenal_view_controller::get_view_model() {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ArsenalViewController.GetViewModel"));

	struct {
		arsenal_view_model* out;
	} params;
	this->process_event(function, &params);
	return params.out;
}

equippable_skin_chroma_inventory_model* equippable_skin_inventory_model::get_skin_inventory_chroma_asset() {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.EquippableSkinInventoryModel.GetEquippedChroma"));

	struct {
		equippable_skin_chroma_inventory_model* return_value;
	} params;

	this->process_event(function, &params);
	return params.return_value;
}

void arsenal_view_controller::EquipAttachment(UEquippableAttachmentInventoryModel* AttachmentModel)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ArsenalViewController.EquipAttachment"));

	struct
	{
		class UEquippableAttachmentInventoryModel* AttachmentModel;
	} params;

	params.AttachmentModel = AttachmentModel;

	this->process_event(function, &params);
}

void arsenal_view_controller::EquipBuddy(equippable_skin_data_asset* Equippable, UEquippableCharmInstanceInventoryModel* CharmInstance)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ArsenalViewController.EquipBuddy"));

	struct
	{
		equippable_skin_data_asset* Equippable;
		UEquippableCharmInstanceInventoryModel* CharmInstance;
	} params;

	params.Equippable = Equippable;
	params.CharmInstance = CharmInstance;

	this->process_event(function, &params);
}

void arsenal_view_controller::EquipLevelBorder(ULevelBorderDataAsset* LevelBorder)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ArsenalViewController.EquipLevelBorder"));

	struct
	{
		ULevelBorderDataAsset* LevelBorder;
	} params;

	params.LevelBorder = LevelBorder;

	this->process_event(function, &params);
}

void arsenal_view_controller::EquipPlayerCard(UPlayerCardDataAsset* PlayerCard)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ArsenalViewController.EquipPlayerCard"));

	struct
	{
		UPlayerCardDataAsset* PlayerCard;
	} params;

	params.PlayerCard = PlayerCard;

	this->process_event(function, &params);
}

void arsenal_view_controller::EquipPlayerTitle(UPlayerTitleDataAsset* PlayerTitle)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ArsenalViewController.EquipPlayerTitle"));

	struct
	{
		UPlayerTitleDataAsset* PlayerTitle;
	} params;

	params.PlayerTitle = PlayerTitle;

	this->process_event(function, &params);
}

void arsenal_view_controller::EquipSkin(equippable_skin_inventory_model* Value)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ArsenalViewController.EquipSkin"));

	struct
	{
		equippable_skin_inventory_model* Value;
	} params;

	params.Value = Value;

	this->process_event(function, &params);
}

void arsenal_view_controller::EquipSpray(USprayEquipSlotDataAsset* SprayEquipSlot, USprayDataAsset* Spray)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ArsenalViewController.EquipSpray"));

	struct
	{
		USprayEquipSlotDataAsset* SprayEquipSlot;
		USprayDataAsset* Spray;
	} params;

	params.SprayEquipSlot = SprayEquipSlot;
	params.Spray = Spray;

	this->process_event(function, &params);
}

arsenal_view_controller* arsenal_view_controller::GetCharmLevel(int32_t LevelNumber)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.EquippableCharmDataAsset.GetCharmLevel"));

	struct
	{
		int32_t LevelNumber;
		arsenal_view_controller* ReturnValue;
	} params;

	params.LevelNumber = LevelNumber;

	this->process_event(function, &params);

	return params.ReturnValue;
}

equippable_charm_instance_inventory_model* equippable_charm_instance_inventory_model::get_equipped_charm_instance()
{
	uobject* function = uobject::find_object<uobject*>(crypt(L"ShooterGame.EquippableInventoryModel.GetEquippedCharmInstance"));

	if (function == nullptr)
		return nullptr;

	struct {
		equippable_charm_instance_inventory_model* return_value;
	} params;


	this->process_event(function, &params);

	return params.return_value;
}

void ares_outline::setoutlinemode(uworld* WorldContextObject, flinearcolor AllyColor, flinearcolor EnemyColor)
{
	uobject* Function = uobject::find_object<uobject*>(crypt(L"Renderer.AresOutlineRendering.SetOutlineColorsForRender"));
	if (!Function)
	{
		return;
	}
	struct {
		uworld* WorldContextObject;
		flinearcolor AllyColor;
		flinearcolor EnemyColor;
	}Parameters;
	Parameters.WorldContextObject = WorldContextObject;
	Parameters.AllyColor = AllyColor;
	Parameters.EnemyColor = EnemyColor;
	variables.ares_outline_rendering->process_event(Function, &Parameters);
}


void ares_outline::setoutlinemode1(uworld* WorldContextObject, flinearcolor EnemyColor)
{
	uobject* Function = uobject::find_object<uobject*>(crypt(L"Renderer.AresOutlineRendering.SetOutlineColorsForRender"));
	if (!Function)
	{
		return;
	}
	struct {
		uworld* WorldContextObject;
		flinearcolor EnemyColor;
	}Parameters;
	Parameters.WorldContextObject = WorldContextObject;
	Parameters.EnemyColor = EnemyColor;
	variables.ares_outline_rendering->process_event(Function, &Parameters);
}

void ares_outline::setoutlinemode3(uobject* WorldContextObject, flinearcolor EnemyColor)
{
	uobject* Function = uobject::find_object<uobject*>(crypt(L"Renderer.AresOutlineRendering.SetOutlineColorsForRender"));
	if (!Function)
	{
		return;
	}
	struct {
		uobject* WorldContextObject;
		flinearcolor EnemyColor;
	}Parameters;
	Parameters.WorldContextObject = WorldContextObject;
	Parameters.EnemyColor = EnemyColor;
	variables.ares_outline_rendering->process_event(Function, &Parameters);
}



//namespace skin_changer_utils {
//	equippable_inventory_model* get_arsenal_gun_models(uobject* uworld, int type_index) {
//		if (aplayercontroller* player_controller = blueprints::get_local_controller(uworld))
//			if (ares_client_game_instace* ares = ares_instance::get_ares_client_game_instance(uworld))
//				if (arsenal_view_controller* arsenal_view_controller = ares->get_aresnal_view_controller())
//					if (arsenal_view_model* arsenal_view_model = arsenal_view_controller->get_view_model())
//					{
//						auto models = arsenal_view_model->get_gun_models();
//						for (int i = 0; i < models.size(); i++)
//						{
//							auto model = models[i];
//
//							if (equippable_skin_data_asset* skin_data = model->get_equipped_skin_model()->get_skin_data_asset())
//								if (equippable_skin_data_asset::type type = skin_data->get_type(); type.is_valid())
//									if (type.index == type_index)
//										return model;
//						}
//					}
//		return nullptr;
//	}
//}

bool basecomponent::is_ally(ashootercharacter* enemy, ashootercharacter* self) {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.BaseTeamComponent.IsAlly"));

	struct {
		ashootercharacter* enemy;
		ashootercharacter* self;
		bool return_value;
	} params;

	variables.base_component->process_event(function, &params);
	return params.return_value;
}

//void skin_changer::unlock_all_apply(currentequippable* current_equippable, uobject* skin_data_asset, uobject* skin_chroma_asset, int max_level, uobject* skin_charm_data_asset, int skin_charm_level_data_asset) {
//
//	g97hf23fh3h928f;
//	fg82f31gh78df23;
//	hh17d39h789d;
//
//	SPOOF_FUNC
//
//	auto decrypted = system::decrypt_parent(current_equippable);
//	auto a1 = memory::read<uintptr_t>(decrypted + offsets::skin_pointer);
//	if (a1) {
//		a1 = memory::read<uintptr_t>(a1 + offsets::skin_pointer_2);
//		if (a1) {
//			auto old_value = memory::read<int>(a1 + offsets::skin_pointer_3);
//			memory::write<int>(a1 + offsets::skin_pointer_3, 2);
//
//			content_library::clear_weapon_components(current_equippable);
//			content_library::apply_skin(current_equippable, skin_data_asset, skin_chroma_asset, max_level, skin_charm_data_asset, skin_charm_level_data_asset);
//			memory::write<int>(a1 + offsets::skin_pointer_3, old_value);
//		}
//	}
//
//	gh92g4h982fh9f23;
//	f7hfh473h89;
//	h2cd3gw67g6eqw2;
//}
//
//void skin_changer::unlock_all_skins(uobject* world) {
//
//	g97hf23fh3h928f;
//	fg82f31gh78df23;
//	hh17d39h789d;
//
//	SPOOF_FUNC
//
//	if (inventorymanager* manager = ares_instance::get_ares_client_game_instance(world)->get_inventory_manager()) {
//		tarray<uobject*> equippable_models = memory::read<tarray<uobject*>>(std::uintptr_t(manager) + 0xe0);
//
//		if (globals::misc::sk1n_chang3r) {
//			for (int i = 0; i < equippable_models.size(); i++) {
//				if (auto model = equippable_models[i]) {
//					tarray<uobject*> skins = memory::read<tarray<uobject*>>(std::uintptr_t(model) + 0x150);
//
//					if (skins.size() > 0) {
//						for (int a = 0; a < skins.size(); a++) {
//							if (auto skin = skins[a]) {
//
//								tarray<uobject*> possible_levels = memory::read<tarray<uobject*>>(std::uintptr_t(skin) + 0x138);
//								for (int a = 0; a < possible_levels.size(); a++)
//									if (uobject* xyz = possible_levels[a])
//										memory::write<bool>(std::uintptr_t(xyz) + 0xfe, true),
//										memory::write<bool>(std::uintptr_t(xyz) + 0xf2, true);
//
//
//								tarray<uobject*> possible_chromas = memory::read<tarray<uobject*>>(std::uintptr_t(skin) + 0x128);
//								for (int a = 0; a < possible_chromas.size(); a++)
//									if (uobject* xyz = possible_chromas[a])
//										memory::write<bool>(std::uintptr_t(xyz) + 0xfe, true),
//										memory::write<bool>(std::uintptr_t(xyz) + 0xf2, true);
//
//
//								memory::write<bool>(std::uintptr_t(skin) + 0xfe, true);
//								memory::write<bool>(std::uintptr_t(skin) + 0xf2, true);
//
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//
//	gh92g4h982fh9f23;
//	f7hfh473h89;
//	h2cd3gw67g6eqw2;
//}

//void skin_changer::unlock_all_apply(currentequippable* current_equippable, uobject* skin_data_asset, uobject* skin_chroma_asset, int max_level, uobject* world) {
//
//	auto deEncrypted = system::decrypt_parent(current_equippable);
//	auto a1 = memory::read<uintptr_t>(deEncrypted + offsets::skin_pointer);
//	if (a1) {
//		a1 = memory::read<uintptr_t>(a1 + offsets::skin_pointer_2);
//		if (a1) {
//			auto old_value = memory::read<int>(a1 + offsets::skin_pointer_3);
//			memory::write<int>(a1 + offsets::skin_pointer_3, 2);
//
//			if (globals::buddy::enabled) {
//				inventorymanager* manager = SPOOF_CALL(ares_instance::get_ares_client_game_instance)(world)->get_inventory_manager();
//				auto charm_instances = memory::read<tarray<tmap<uobject*, uobject*>>>(std::uintptr_t(manager) + offsets::charm_map);
//				uobject* buddy = charm_instances[globals::buddy::index].Key;
//
//				content_library::clear_weapon_components(current_equippable);
//				content_library::apply_skin(current_equippable, skin_data_asset, skin_chroma_asset, max_level, buddy, 1);
//				memory::write<int>(a1 + offsets::skin_pointer_3, old_value);
//			}
//			else {
//				content_library::clear_weapon_components(current_equippable);
//				content_library::apply_skin(current_equippable, skin_data_asset, skin_chroma_asset, max_level, nullptr, -1);
//				memory::write<int>(a1 + offsets::skin_pointer_3, old_value);
//			}
//		}
//	}
//}

//void skin_changer::unlock_all_apply(uobject* world, currentequippable* current_equippable, uobject* skin_data_asset, uobject* skin_chroma_asset, int max_level, uobject* skin_charm_data_asset, int skin_charm_level_data_asset) {
//
//
//	auto ares_client_game_instance = ares_instance::get_ares_client_game_instance(world);
//	auto a1 = memory::read<uintptr_t>((uintptr_t)ares_client_game_instance + offsets::skin_pointer);
//
//	if (a1) {
//		a1 = memory::read<uintptr_t>(a1 + offsets::skin_pointer_2);
//		if (a1) {
//			auto old_value = memory::read<int>(a1 + offsets::skin_pointer_3);
//			memory::write<int>(a1 + offsets::skin_pointer_3, 2);
//
//
//			SPOOF_CALL(content_library::clear_weapon_components)(current_equippable);
//
//
//			if (globals::buddy::enabled) {
//
//				inventorymanager* manager = (ares_instance::get_ares_client_game_instance)(world)->get_inventory_manager();
//				auto charm_instances = memory::read<tarray<tmap<uobject*, uobject*>>>(std::uintptr_t(manager) + 0x430);
//
//
//				uobject* selected_buddy = charm_instances[globals::buddy::index].Key;
//
//
//				SPOOF_CALL(content_library::apply_skin)(current_equippable, skin_data_asset, skin_chroma_asset, max_level, selected_buddy, 1);
//			}
//			else {
//
//				if (skin_charm_data_asset != nullptr) {
//					SPOOF_CALL(content_library::apply_skin)(current_equippable, skin_data_asset, skin_chroma_asset, max_level, skin_charm_data_asset, skin_charm_level_data_asset);
//				}
//				else {
//
//					SPOOF_CALL(content_library::apply_skin)(current_equippable, skin_data_asset, skin_chroma_asset, max_level, nullptr, -1);
//				}
//			}
//			memory::write<int>(a1 + offsets::skin_pointer_3, old_value);
//		}
//	}
//}
//
//void skin_changer::unlock_all_apply564(
//	currentequippable* current_equippable,
//	uobject* skin_data_asset,
//	uobject* skin_chroma_asset,
//	int max_level,
//	uobject* world)
//{
//	auto ares_client_game_instance = ares_instance::get_ares_client_game_instance(world);
//	auto a1 = memory::read<uintptr_t>((uintptr_t)ares_client_game_instance + offsets::skin_pointer);
//
//	if (!a1) return;
//
//	a1 = memory::read<uintptr_t>(a1 + offsets::skin_pointer_2);
//	if (!a1) return;
//
//	auto old_value = memory::read<int>(a1 + offsets::skin_pointer_3);
//	memory::write<int>(a1 + offsets::skin_pointer_3, 2);
//
//	SPOOF_CALL(content_library::clear_weapon_components)(current_equippable);
//
//	if (globals::buddy::enabled)
//	{
//		inventorymanager* manager = ares_client_game_instance->get_inventory_manager();
//		auto charm_instances = memory::read<tarray<tmap<uobject*, uobject*>>>(reinterpret_cast<uintptr_t>(manager) + 0x430);
//
//		uobject* selected_buddy = charm_instances[globals::buddy::index].Key;
//
//		SPOOF_CALL(content_library::apply_skin)(current_equippable, skin_data_asset, skin_chroma_asset, max_level, selected_buddy, 1);
//	}
//	else
//	{
//		SPOOF_CALL(content_library::apply_skin)(current_equippable, skin_data_asset, skin_chroma_asset, max_level, nullptr, -1);
//	}
//
//	memory::write<int>(a1 + offsets::skin_pointer_3, old_value);
//}
//
//
//void skin_changer::unlock_all_skins(uobject* world) {
//	SPOOF_FUNC;
//	if (inventorymanager* manager = ares_instance::get_ares_client_game_instance(world)->get_inventory_manager()) {
//		tarray<uobject*> equippable_models = memory::read<tarray<uobject*>>(std::uintptr_t(manager) + offsets::equippable_models);
//		SPOOF_FUNC;
//		if (globals::misc::sk1n_chang3r) {
//			SPOOF_FUNC;
//			for (int i = 0; i < equippable_models.size(); i++) {
//				SPOOF_FUNC;
//				if (auto model = equippable_models[i]) {
//					SPOOF_FUNC;
//					tarray<uobject*> skins = memory::read<tarray<uobject*>>(std::uintptr_t(model) + offsets::skins);
//
//					if (skins.size() > 0) {
//						for (int a = 0; a < skins.size(); a++) {
//							if (auto skin = skins[a]) {
//								SPOOF_FUNC;
//								tarray<uobject*> possible_levels = memory::read<tarray<uobject*>>(std::uintptr_t(skin) + offsets::possible_levels);
//								for (int a = 0; a < possible_levels.size(); a++)
//									if (uobject* xyz = possible_levels[a])
//										memory::write<bool>(std::uintptr_t(xyz) + offsets::possible_levels1, true),
//										memory::write<bool>(std::uintptr_t(xyz) + offsets::possible_levels2, true);
//
//
//								tarray<uobject*> possible_chromas = memory::read<tarray<uobject*>>(std::uintptr_t(skin) + offsets::possible_chromas);
//								for (int a = 0; a < possible_chromas.size(); a++)
//									if (uobject* xyz = possible_chromas[a])
//										memory::write<bool>(std::uintptr_t(xyz) + offsets::possible_levels1, true),
//										memory::write<bool>(std::uintptr_t(xyz) + offsets::possible_levels2, true);
//
//
//								memory::write<bool>(std::uintptr_t(skin) + offsets::possible_levels1, true);
//								memory::write<bool>(std::uintptr_t(skin) + offsets::possible_levels2, true);
//
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//}

void skin_changer::unlock_all_apply(uobject* world, currentequippable* current_equippable, uobject* skin_data_asset, uobject* skin_chroma_asset, int max_level, uobject* skin_charm_data_asset, int skin_charm_level_data_asset) {


	auto ares_client_game_instance = ares_instance::get_ares_client_game_instance(world);
	auto a1 = memory::read<uintptr_t>((uintptr_t)ares_client_game_instance + offsets::skin_pointer);

	if (a1) {
		a1 = memory::read<uintptr_t>(a1 + offsets::skin_pointer_2);
		if (a1) {
			auto old_value = memory::read<int>(a1 + offsets::skin_pointer_3);
			memory::write<int>(a1 + offsets::skin_pointer_3, 2);


			SPOOF_CALL(content_library::clear_weapon_components)(current_equippable);


			if (skin_charm_data_asset != nullptr) {
				SPOOF_CALL(content_library::apply_skin)(current_equippable, skin_data_asset, skin_chroma_asset, max_level, skin_charm_data_asset, skin_charm_level_data_asset);
			}
			else {

				SPOOF_CALL(content_library::apply_skin)(current_equippable, skin_data_asset, skin_chroma_asset, max_level, nullptr, -1);
			}

			memory::write<int>(a1 + offsets::skin_pointer_3, old_value);
		}
	}
}

void skin_changer::unlock_all_skins(uobject* world) {
	if (inventorymanager* manager = ares_instance::get_ares_client_game_instance(world)->get_inventory_manager()) {
		tarray<uobject*> equippable_models = memory::read<tarray<uobject*>>(std::uintptr_t(manager) + 0xf0);

		if (globals::misc::sk1n_chang3r) {
			for (int32_t i = 0; i < equippable_models.size(); i++) {
				if (auto model = equippable_models[i]) {
					tarray<uobject*> skins = memory::read<tarray<uobject*>>(std::uintptr_t(model) + 0x168);

					if (skins.size() > 0) {
						for (int32_t a = 0; a < skins.size(); a++) {
							if (auto skin = skins[a]) {

								tarray<uobject*> possible_levels = memory::read<tarray<uobject*>>(std::uintptr_t(skin) + 0x150);
								for (int a = 0; a < possible_levels.size(); a++)
									if (uobject* xyz = possible_levels[a])
										memory::write<bool>(std::uintptr_t(xyz) + 0x10a, true),
										memory::write<bool>(std::uintptr_t(xyz) + 0x10a, true);


								tarray<uobject*> possible_chromas = memory::read<tarray<uobject*>>(std::uintptr_t(skin) + 0x140);
								for (int a = 0; a < possible_chromas.size(); a++)
									if (uobject* xyz = possible_chromas[a])
										memory::write<bool>(std::uintptr_t(xyz) + 0x10a, true),
										memory::write<bool>(std::uintptr_t(xyz) + 0x10a, true);


								memory::write<bool>(std::uintptr_t(skin) + 0x10a, true);
								memory::write<bool>(std::uintptr_t(skin) + 0x10a, true);

							}
						}
					}
				}
			}
		}
	}
}

bool string::contains(fstring SearchIn, fstring Substring, bool bUseCase, bool bSearchFromEnd) {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetStringLibrary.Contains"));

	struct {
		fstring SearchIn;
		fstring Substring;
		bool bUseCase;
		bool bSearchFromEnd;
		bool ReturnValue;
	}params;
	params.SearchIn = SearchIn;
	params.Substring = Substring;
	params.bUseCase = bUseCase;
	params.bSearchFromEnd = bSearchFromEnd;

	variables.kismet_string->process_event(function, &params);

	return params.ReturnValue;
}

fstring string::int_to_string(const int value) {
	static uobject* function = 0; if (!function) function = uobject::find_object<uobject*>(crypt(L"Engine.KismetStringLibrary.Conv_IntToString"));

	if (function == nullptr)
		return {};

	struct
	{
		int value;
		fstring return_value;
	} params;

	params.value = value;

	variables.kismet_string->process_event(function, &params);

	return params.return_value;
}

EAresMovementType ashootercharacter::GetMovementType()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetMovementType"));

	struct
	{
		EAresMovementType ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

flinearcolor USkyAtmosphereComponent::GetAtmosphereTransmitanceOnGroundAtPlanetTop(UDirectionalLightComponent* DirectionalLight)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.SkyAtmosphereComponent.GetAtmosphereTransmitanceOnGroundAtPlanetTop"));

	struct
	{
		UDirectionalLightComponent* DirectionalLight;
		flinearcolor ReturnValue;
	} params;

	params.DirectionalLight = DirectionalLight;

	this->process_event(function, &params);

	return params.ReturnValue;
}

void USkyAtmosphereComponent::OverrideAtmosphereLightDirection(int32_t AtmosphereLightIndex, fvector& LightDirection)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.SkyAtmosphereComponent.OverrideAtmosphereLightDirection"));

	struct
	{
		int32_t AtmosphereLightIndex;
		fvector LightDirection;
	} params;

	params.AtmosphereLightIndex = AtmosphereLightIndex;
	params.LightDirection = LightDirection;

	this->process_event(function, &params);
}

void USkyAtmosphereComponent::SetAerialPespectiveViewDistanceScale(float NewValue)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.SkyAtmosphereComponent.SetAerialPespectiveViewDistanceScale"));

	struct
	{
		float NewValue;
	} params;

	params.NewValue = NewValue;

	this->process_event(function, &params);
}

void USkyAtmosphereComponent::SetAtmosphereHeight(float NewValue)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.SkyAtmosphereComponent.SetAtmosphereHeight"));

	struct
	{
		float NewValue;
	} params;

	params.NewValue = NewValue;

	this->process_event(function, &params);
}

void USkyAtmosphereComponent::SetHeightFogContribution(float NewValue)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.SkyAtmosphereComponent.SetHeightFogContribution"));

	struct
	{
		float NewValue;
	} params;

	params.NewValue = NewValue;

	this->process_event(function, &params);
}

void USkyAtmosphereComponent::SetMieScattering(flinearcolor& NewValue)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.SkyAtmosphereComponent.SetMieScattering"));

	struct
	{
		flinearcolor NewValue;
	} params;

	params.NewValue = NewValue;

	this->process_event(function, &params);
}

void USkyAtmosphereComponent::SetRayleighScattering(flinearcolor& NewValue)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.SkyAtmosphereComponent.SetRayleighScattering"));

	struct
	{
		flinearcolor NewValue;
	} params;

	params.NewValue = NewValue;

	this->process_event(function, &params);
}

void USkyAtmosphereComponent::SetRayleighExponentialDistribution(float value)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.SkyAtmosphereComponent.SetRayleighExponentialDistribution"));

	struct
	{
		float value;
	} params;

	params.value = value;

	this->process_event(function, &params);
}

void USkyAtmosphereComponent::SetMieAnisotropy(float value)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.SkyAtmosphereComponent.SetMieAnisotropy"));

	struct
	{
		float value;
	} params;

	params.value = value;

	this->process_event(function, &params);
}

void USkyAtmosphereComponent::SetMieExponentialDistribution(float value)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.SkyAtmosphereComponent.SetMieExponentialDistribution"));

	struct
	{
		float value;
	} params;

	params.value = value;

	this->process_event(function, &params);
}

void USkyAtmosphereComponent::SetMultiScatteringFactor(float factor)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.SkyAtmosphereComponent.SetMultiScatteringFactor"));

	struct
	{
		float factor;
	} params;

	params.factor = factor;

	this->process_event(function, &params);
}

void USkyAtmosphereComponent::SetSkyLuminanceFactor(flinearcolor factor)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.SkyAtmosphereComponent.SetSkyLuminanceFactor"));

	struct
	{
		flinearcolor factor;
	} params;

	params.factor = factor;

	this->process_event(function, &params);
}

void aplayercontroller::ClientFreeCamAtCurrentLocation()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.FreeCamComponent.ClientFreeCamAtCurrentLocation"));

	this->process_event(function, nullptr);
}

void aplayercontroller::ClientTeleportFreeCamToPosition(const fvector& Position, const frotator& Rotation, bool bCheckCollision)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.FreeCamComponent.ClientTeleportFreeCamToPosition"));

	struct
	{
		fvector Position;
		frotator Rotation;
		bool bCheckCollision;
	} params;

	params.Position = Position;
	params.Rotation = Rotation;
	params.bCheckCollision = bCheckCollision;

	this->process_event(function, &params);
}

void aplayercontroller::ClientUpdateFreeCamPosition(ashootercharacter* ViewTargetToMatch)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.FreeCamComponent.ClientUpdateFreeCamPosition"));

	struct
	{
		ashootercharacter* ViewTargetToMatch;
	} params;

	params.ViewTargetToMatch = ViewTargetToMatch;

	this->process_event(function, &params);
}

float aplayercontroller::get_input_axis_value(const fname& input_axis_name)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.GetInputAxisValue"));

	struct
	{
		fname input_axis_name;
		float return_value;
	} params;

	params.input_axis_name = input_axis_name;

	this->process_event(function, &params);

	return params.return_value;
}

FDisplayName UPlatformPlayer::GetTrueDisplayName()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.PlatformPlayer.GetTrueDisplayName").decrypt());

	struct
	{
		FDisplayName ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

ashootercharacter* UViewTargetComponent::GetSpectatedSpawnedCharacter()
{
	static uobject* Function = nullptr;
	if (!Function)
		Function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ViewTargetComponent.GetSpectatedSpawnedCharacter"));

	struct
	{
		ashootercharacter* ReturnValue;
	} Parameters;

	this->process_event(Function, &Parameters);
	return Parameters.ReturnValue;
}

ashootercharacter* UViewTargetComponent::GetTargetCharacter()
{
	static uobject* Function = nullptr;
	if (!Function)
		Function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ViewTargetComponent.GetTargetCharacter"));

	struct
	{
		ashootercharacter* ReturnValue;
	} Parameters;

	this->process_event(Function, &Parameters);
	return Parameters.ReturnValue;
}

bool UViewTargetComponent::IsInPlayerSpectatingMode()
{
	static uobject* Function = nullptr;
	if (!Function)
		Function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ViewTargetComponent.IsInPlayerSpectatingMode"));

	struct
	{
		bool ReturnValue;
	} Parameters;

	this->process_event(Function, &Parameters);
	return Parameters.ReturnValue;
}

bool UViewTargetComponent::IsInSpectatorMode()
{
	static uobject* Function = nullptr;
	if (!Function)
		Function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ViewTargetComponent.IsInSpectatorMode"));

	struct
	{
		bool ReturnValue;
	} Parameters;

	this->process_event(Function, &Parameters);
	return Parameters.ReturnValue;
}

bool UViewTargetComponent::IsSpectating(ashootercharacter* InActor)
{
	static uobject* Function = nullptr;
	if (!Function)
		Function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ViewTargetComponent.IsSpectating"));

	struct
	{
		ashootercharacter* InActor;
		bool ReturnValue;
	} Parameters;

	Parameters.InActor = InActor;
	this->process_event(Function, &Parameters);
	return Parameters.ReturnValue;
}

bool UViewTargetComponent::IsViewingLocal(ashooterplayerstate* InPlayerState)
{
	static uobject* Function = nullptr;
	if (!Function)
		Function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ViewTargetComponent.IsViewingLocal"));

	struct
	{
		ashooterplayerstate* InPlayerState;
		bool ReturnValue;
	} Parameters;

	Parameters.InPlayerState = InPlayerState;
	this->process_event(Function, &Parameters);
	return Parameters.ReturnValue;
}

fvector system::find_look_at_rotation(fvector start, fvector end)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetMathLibrary.FindLookAtRotation"));

	struct
	{
		fvector start;
		fvector end;
		fvector output;
	} params;

	params.start = start;
	params.end = end;

	variables.math_system->process_event(function, &params);
	return params.output;
}

void aplayercontroller::set_control_rotation_rg(frotator angle) {

	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Controller.SetControlRotation"));

	struct
	{
		frotator angle;
	} params;

	params.angle = angle;

	this->process_event(function, &params);
}

void aplayercontroller::set_ignore_look_input(bool bnew_look_input)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Controller.SetIgnoreLookInput"));

	struct
	{
		bool bnew_look_input;
	} params;

	params.bnew_look_input = bnew_look_input;

	this->process_event(function, &params);
}

void UProjectileMovementComponent::move_interpolation_target(const fvector& NewLocation, const frotator& NewRotation)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.ProjectileMovementComponent.MoveInterpolationTarget"));

	struct
	{
		fvector NewLocation;
		frotator NewRotation;
	} params = { NewLocation, NewRotation };

	this->process_event(function, &params);
}

void UProjectileMovementComponent::stop_movement_immediately()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.MovementComponent.StopMovementImmediately"));

	this->process_event(function, nullptr);
}

void aplayercontroller::client_set_hud(uclass* new_hud_class)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.ClientSetHUD"));

	struct
	{
		uclass* NewHUDClass;
	} params;

	params.NewHUDClass = new_hud_class;

	this->process_event(function, &params);
}

AHUD* aplayercontroller::get_hud()
{
	static uobject* fn = nullptr;
	if (!fn)
		fn = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.GetHUD"));

	struct
	{
		AHUD* ReturnValue;
	} params;

	this->process_event(fn, &params);
	return params.ReturnValue;
}

void AHUD::draw_text(fstring text, flinearcolor color, float x, float y, uobject* font, float scale, bool scale_position)
{
	static uobject* fn = nullptr;
	if (!fn)
		fn = uobject::find_object<uobject*>(crypt(L"Engine.HUD.DrawText"));

	struct
	{
		fstring Text;
		flinearcolor TextColor;
		float ScreenX;
		float ScreenY;
		uobject* Font;
		float Scale;
		bool bScalePosition;
	} params;

	params.Text = text;
	params.TextColor = color;
	params.ScreenX = x;
	params.ScreenY = y;
	params.Font = font;
	params.Scale = scale;
	params.bScalePosition = scale_position;

	this->process_event(fn, &params);
}

void ashootercharacter::set_actor_hidden_in_game(bool new_hidden)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.SetActorHiddenInGame"));

	struct
	{
		bool bNewHidden;
	} params;

	params.bNewHidden = new_hidden;

	this->process_event(function, &params);
}

void ashootercharacter::flush_net_dormancy()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.FlushNetDormancy"));

	this->process_event(function, nullptr);
}

void acknowledgedpawn::flush_net_dormancy1()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.FlushNetDormancy"));

	this->process_event(function, nullptr);
}

void uskeletalmeshcomponent::set_collision_enabled(ECollisionEnabled new_type)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PrimitiveComponent.SetCollisionEnabled"));

	struct
	{
		ECollisionEnabled NewType;
	} params;

	params.NewType = new_type;

	this->process_event(function, &params);
}

void ashootercharacter::set_movement_mode(EMovementMode NewMode)
{
	static uobject* Function = nullptr;
	if (!Function)
		Function = uobject::find_object<uobject*>(crypt(L"Engine.CharacterMovementComponent.SetMovementMode"));

	struct Params {
		EMovementMode NewMovementMode;
		uint8_t NewCustomMode; // Char-sized enum
	};

	Params params;
	params.NewMovementMode = NewMode;
	params.NewCustomMode = 0; // Default custom mode

	this->ProcessEvent(Function, &params);
}

void uskeletalmeshcomponent::set_collision_response_to_channel(ECollisionChannel channel, ECollisionResponse new_response)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PrimitiveComponent.SetCollisionResponseToChannel"));

	struct
	{
		ECollisionChannel Channel;
		ECollisionResponse NewResponse;
	} params;

	params.Channel = channel;
	params.NewResponse = new_response;

	this->process_event(function, &params);
}

void UCapsuleComponent::set_collision_response_to_channel1(ECollisionChannel channel, ECollisionResponse new_response)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PrimitiveComponent.SetCollisionResponseToChannel"));

	struct
	{
		ECollisionChannel Channel;
		ECollisionResponse NewResponse;
	} params;

	params.Channel = channel;
	params.NewResponse = new_response;

	this->process_event(function, &params);
}

void ashootercharacter::set_capsule_size(float in_radius, float in_half_height, bool update_overlaps)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.CapsuleComponent.SetCapsuleSize"));

	struct
	{
		float InRadius;
		float InHalfHeight;
		bool bUpdateOverlaps;
	} params;

	params.InRadius = in_radius;
	params.InHalfHeight = in_half_height;
	params.bUpdateOverlaps = update_overlaps;

	this->process_event(function, &params);
}

void uskeletalmeshcomponent::set_capsule_size1(float in_radius, float in_half_height, bool update_overlaps)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.CapsuleComponent.SetCapsuleSize"));

	struct
	{
		float InRadius;
		float InHalfHeight;
		bool bUpdateOverlaps;
	} params;

	params.InRadius = in_radius;
	params.InHalfHeight = in_half_height;
	params.bUpdateOverlaps = update_overlaps;

	this->process_event(function, &params);
}

void uskeletalmeshcomponent::set_bounds_scale(float new_bounds_scale)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PrimitiveComponent.SetBoundsScale"));

	struct
	{
		float NewBoundsScale;
	} params;

	params.NewBoundsScale = new_bounds_scale;

	this->process_event(function, &params);
}

void ashootercharacter::stop_movement_immediately_mov()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.MovementComponent.StopMovementImmediately"));

	this->process_event(function, nullptr);
}

bool system::ares_line_trace_single_by_channel(
	uobject* world_context,
	const fvector& start,
	const fvector& end,
	const std::vector<AActor*> actors_to_ignore,
	FHitResult* out_hit,
	ECollisionChannel trace_channel,
	bool trace_complex,
	bool include_moving_objects)
{
	static uobject* function = nullptr;
	if (!function)
	{
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterBlueprintLibrary.AresLineTraceSingleByChannel"));
		if (!function)
		{
			printf("[Trace] Failed to find blueprint function!\n");
			return false;
		}
	}

	
	if (!world_context)
	{
		printf("[Trace] World context is null.\n");
		return false;
	}

	if (!variables.blueprints)
	{
		printf("[Trace] Blueprint processor is null.\n");
		return false;
	}

	struct
	{
		uobject* WorldContextObject;
		fvector Start;
		fvector End;
		std::vector<AActor*> ActorsToIgnore;
		FHitResult OutHit;
		ECollisionChannel TraceChannel;
		bool bTraceComplex;
		bool bIncludeMovingObjects;
		bool ReturnValue;
	} params{};

	// Assign parameters
	params.WorldContextObject = world_context;
	params.Start = start;
	params.End = end;
	params.ActorsToIgnore = actors_to_ignore;
	params.TraceChannel = trace_channel;
	params.bTraceComplex = trace_complex;
	params.bIncludeMovingObjects = include_moving_objects;

	// Debug logging
	printf("[Trace] ===== Executing Ares Line Trace =====\n");
	printf("[Trace] Start: [%.1f, %.1f, %.1f] -> End: [%.1f, %.1f, %.1f]\n",
		start.x, start.y, start.z,
		end.x, end.y, end.z);
	printf("[Trace] Actors to ignore: %zu | Complex: %d | MovingObjs: %d\n",
		actors_to_ignore.size(),
		trace_complex,
		include_moving_objects);

	// Call blueprint function
	variables.blueprints->process_event(function, &params);

	// Output result
	if (out_hit)
		*out_hit = params.OutHit;

	if (params.ReturnValue)
	{
		printf("[Trace] Hit! Location: [%.1f, %.1f, %.1f]\n",
			params.OutHit.ImpactPoint.x,
			params.OutHit.ImpactPoint.y,
			params.OutHit.ImpactPoint.z);
	}
	else
	{
		printf("[Trace] No hit detected.\n");
	}

	return params.ReturnValue;
}


UPingManager* ashootercharacter::get_ping_manager()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AresClientGameInstance.GetPingManager"));

	struct
	{
		UPingManager* return_value;
	} params;

	this->process_event(function, &params);
	return params.return_value;
}

void UPingManager::process_ping_packet_received(fstring destination, fstring destination_address, int32_t ping_in_millis)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.PingManager.ProcessPingPacketReceived"));

	struct
	{
		fstring Destination;
		fstring DestinationAddress;
		int32_t PingInMillis;
	} params;

	params.PingInMillis = ping_in_millis;

	this->process_event(function, &params);

	destination = params.Destination;
	destination_address = params.DestinationAddress;
}

void UPingManager::request_refresh()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.PingManager.RequestRefresh"));

	this->process_event(function, nullptr);
}

void UPingManager::update_pings()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.PingManager.UpdatePings"));

	this->process_event(function, nullptr);
}

void aplayercontroller::client_start_camera_shake(
	uclass* shake_class,
	float scale,
	ECameraShakePlaySpace play_space,
	frotator user_play_space_rot)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.ClientStartCameraShake"));

	struct
	{
		uclass* Shake;
		float Scale;
		ECameraShakePlaySpace PlaySpace;
		frotator UserPlaySpaceRot;
	} params;

	params.Shake = shake_class;
	params.Scale = scale;
	params.PlaySpace = play_space;
	params.UserPlaySpaceRot = user_play_space_rot;

	this->process_event(function, &params);
}

void ashootercharacter::server_set_health(int32_t new_health)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterPlayerControllerDebugComponent.ServerSetHealth"));

	struct
	{
		int32_t new_health;
	} params;

	params.new_health = new_health;

	this->process_event(function, &params);
}

int32_t ashootercharacter::get_max_health()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacter.GetMaxHealth"));

	struct
	{
		int32_t return_value;
	} params;

	this->process_event(function, &params);
	return params.return_value;
}

void ashootercharacter::set_replicate_movement(bool replicate)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.SetReplicateMovement"));

	struct
	{
		bool bInReplicateMovement;
	} params;

	params.bInReplicateMovement = replicate;

	this->process_event(function, &params);
}

void ashootercharacter::force_net_update()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.ForceNetUpdate"));

	this->process_event(function, nullptr);
}

void acknowledgedpawn::force_net_update1()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.ForceNetUpdate"));

	this->process_event(function, nullptr);
}

void ashootercharacter::client_set_location(const fvector& new_location, const frotator& new_rotation)
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Controller.ClientSetLocation"));

	struct
	{
		fvector new_location;
		frotator new_rotation;
	} params;

	params.new_location = new_location;
	params.new_rotation = new_rotation;

	this->process_event(function, &params);
}

AWorldSettings* uworld::k2_get_world_settings()
{
	static uobject* function = nullptr;

	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.World.K2_GetWorldSettings"));

	struct
	{
		AWorldSettings* return_value;
	} params;

	this->process_event(function, &params);

	return params.return_value;
}

UPrimitiveComponent* UCharacterMovementComponent::get_movement_base()
{
	static uobject* function = nullptr;

	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.CharacterMovementComponent.GetMovementBase"));

	struct
	{
		UPrimitiveComponent* return_value;
	} params;

	this->process_event(function, &params);

	return params.return_value;
}

UPawnMovementComponent* acknowledgedpawn::get_movement_component()
{
	static uobject* function = nullptr;

	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Pawn.GetMovementComponent"));

	struct
	{
		UPawnMovementComponent* return_value;
	} params;

	this->process_event(function, &params);

	return params.return_value;
}

void aplayercontroller::client_play_sound(USoundBase* sound, float volume_multiplier, float pitch_multiplier)
{
	static uobject* function = nullptr;

	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.PlayerController.ClientPlaySound"));

	struct {
		USoundBase* Sound;
		float VolumeMultiplier;
		float PitchMultiplier;
	} params;

	params.Sound = sound;
	params.VolumeMultiplier = volume_multiplier;
	params.PitchMultiplier = pitch_multiplier;

	this->process_event(function, &params);
}

bool UDamageResponse::DamageKilledTarget()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.DamageResponse.DamageKilledTarget");

	struct
	{
		bool ReturnValue;
	} params{};

	this->process_event(function, &params);

	return params.ReturnValue;
}

bool UDamageResponse::DamageWasBlocked()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.DamageResponse.DamageWasBlocked");

	struct
	{
		bool ReturnValue;
	} params{};

	this->process_event(function, &params);

	return params.ReturnValue;
}

acknowledgedpawn* UDamageResponse::GetDamageCauser()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.DamageResponse.GetDamageCauser");

	struct
	{
		acknowledgedpawn* ReturnValue;
	} params{};

	this->process_event(function, &params);

	return params.ReturnValue;
}

acknowledgedpawn* UDamageResponse::GetDamagedActor()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.DamageResponse.GetDamagedActor");

	struct
	{
		acknowledgedpawn* ReturnValue;
	} params{};

	this->process_event(function, &params);

	return params.ReturnValue;
}

float UDamageResponse::GetDamageDealt()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.DamageResponse.GetDamageDealt");

	struct
	{
		float ReturnValue;
	} params{};

	this->process_event(function, &params);

	return params.ReturnValue;
}

fvector UDamageResponse::GetDamageOrigin()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.DamageResponse.GetDamageOrigin");

	struct
	{
		fvector ReturnValue;
	} params{};

	this->process_event(function, &params);

	return params.ReturnValue;
}

float UDamageResponse::GetDamageTaken()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.DamageResponse.GetDamageTaken");

	struct
	{
		float ReturnValue;
	} params{};

	this->process_event(function, &params);

	return params.ReturnValue;
}

currentequippable* UDamageResponse::GetEquippableUsed()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.DamageResponse.GetEquippableUsed");

	struct
	{
		currentequippable* ReturnValue;
	} params{};

	this->process_event(function, &params);

	return params.ReturnValue;
}

acknowledgedpawn* UDamageResponse::GetEventInstigatorPawn()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.DamageResponse.GetEventInstigatorPawn");

	struct
	{
		acknowledgedpawn* ReturnValue;
	} params{};

	this->process_event(function, &params);

	return params.ReturnValue;
}

EAresItemSlot currentequippable::GetItemSlot()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.AresItem.GetItemSlot");

	struct
	{
		EAresItemSlot ReturnValue;
	} params{};

	this->process_event(function, &params);

	return params.ReturnValue;
}


utexture2d* system::import_file_as_texture2d(uobject* world_context_object, fstring filename)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"Engine.KismetRenderingLibrary.ImportFileAsTexture2D");

	struct
	{
		uobject* world_context_object;
		fstring filename;
		utexture2d* return_value;
	} params;

	params.world_context_object = world_context_object;
	params.filename = filename;

	variables.rendering_library->process_event(function, &params);
	return params.return_value;
}

void aplayercontroller::UnPossess() {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(L"Engine.Controller.UnPossess");
	this->process_event(function, nullptr);
}

void aplayercontroller::Possess(acknowledgedpawn* InPawn) {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(L"Engine.Controller.Possess");

	struct {
		acknowledgedpawn* InPawn;
	} params = { InPawn };

	this->process_event(function, &params);
}

AAIController* uworld::SpawnActor(uclass* Class, fvector const& Location, frotator const& Rotation, FActorSpawnParameters const& SpawnParameters) {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(L"Engine.World.SpawnActor");

	struct {
		uclass* Class;
		fvector Location;
		frotator Rotation;
		FActorSpawnParameters SpawnParameters;
		AAIController* ReturnValue;
	} params = { Class, Location, Rotation, SpawnParameters, nullptr };

	this->process_event(function, &params);
	return params.ReturnValue;
}

UPawnMovementComponent* acknowledgedpawn::GetMovementComponent() {
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(L"Engine.Pawn.GetMovementComponent");

	struct {
		UPawnMovementComponent* ReturnValue;
	} params;

	this->process_event(function, &params);
	return params.ReturnValue;
}

bool UBlindManagerComponent::IsBlinded()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.BlindManagerComponent.IsBlinded");

	struct
	{
		bool ReturnValue;
	} params{};

	this->process_event(function, &params);

	return params.ReturnValue;
}

void UBlindManagerComponent::SetBlinded(bool bNewBlinded)
{
	uobject* function = uobject::find_object<uobject*>(L"ShooterGame.BlindManagerComponent.SetBlinded");

	if (!function)
		return;

	struct
	{
		bool bNewBlinded;
	} params = { bNewBlinded };

	this->process_event(function, &params);
}

void UBlindManagerComponent::ClientCleanseBlinds()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"ShooterGame.BlindManagerComponent.ClientCleanseBlinds");

	struct
	{
	} params;

	this->process_event(function, &params);
}

void USkyLightComponent::RecaptureSky()
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"Engine.SkyLightComponent.RecaptureSky");

	struct {
	} params;

	this->process_event(function, &params);
}

void USkyLightComponent::SetCharacterCubemapContrastFresnelExponent(float InCharacterCubemapContrastFresnelExponent)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"Engine.SkyLightComponent.SetCharacterCubemapContrastFresnelExponent");

	struct {
		float InCharacterCubemapContrastFresnelExponent;
	} params;
	params.InCharacterCubemapContrastFresnelExponent = InCharacterCubemapContrastFresnelExponent;

	this->process_event(function, &params);
}

void USkyLightComponent::SetCubemap(class UTextureCube* NewCubemap)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"Engine.SkyLightComponent.SetCubemap");

	struct {
		class UTextureCube* NewCubemap;
	} params;
	params.NewCubemap = NewCubemap;

	this->process_event(function, &params);
}

void USkyLightComponent::SetCubemapBlend(class UTextureCube* SourceCubemap, class UTextureCube* DestinationCubemap, float InBlendFraction)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"Engine.SkyLightComponent.SetCubemapBlend");

	struct {
		class UTextureCube* SourceCubemap;
		class UTextureCube* DestinationCubemap;
		float InBlendFraction;
	} params;
	params.SourceCubemap = SourceCubemap;
	params.DestinationCubemap = DestinationCubemap;
	params.InBlendFraction = InBlendFraction;

	this->process_event(function, &params);
}

void USkyLightComponent::SetDestinationCubemapAngle(float NewValue)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"Engine.SkyLightComponent.SetDestinationCubemapAngle");

	struct {
		float NewValue;
	} params;
	params.NewValue = NewValue;

	this->process_event(function, &params);
}

void USkyLightComponent::SetIndirectLightingIntensity(float NewIntensity)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"Engine.SkyLightComponent.SetIndirectLightingIntensity");

	struct {
		float NewIntensity;
	} params;
	params.NewIntensity = NewIntensity;

	this->process_event(function, &params);
}

void USkyLightComponent::SetIntensity(float NewIntensity)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"Engine.SkyLightComponent.SetIntensity");

	struct {
		float NewIntensity;
	} params;
	params.NewIntensity = NewIntensity;

	this->process_event(function, &params);
}

void USkyLightComponent::SetLightColor(flinearcolor& NewLightColor)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"Engine.SkyLightComponent.SetLightColor");

	struct {
		flinearcolor NewLightColor;
	} params;
	params.NewLightColor = NewLightColor;

	this->process_event(function, &params);
}

void USkyLightComponent::SetLowerHemisphereColor(flinearcolor& InLowerHemisphereColor)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"Engine.SkyLightComponent.SetLowerHemisphereColor");

	struct {
		flinearcolor InLowerHemisphereColor;
	} params;
	params.InLowerHemisphereColor = InLowerHemisphereColor;

	this->process_event(function, &params);
}

void USkyLightComponent::SetMinOcclusion(float InMinOcclusion)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"Engine.SkyLightComponent.SetMinOcclusion");

	struct {
		float InMinOcclusion;
	} params;
	params.InMinOcclusion = InMinOcclusion;

	this->process_event(function, &params);
}

void USkyLightComponent::SetMobileCharacterSkylightIntensity(float InMobileIntensity)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"Engine.SkyLightComponent.SetMobileCharacterSkylightIntensity");

	struct {
		float InMobileIntensity;
	} params;
	params.InMobileIntensity = InMobileIntensity;

	this->process_event(function, &params);
}

void USkyLightComponent::SetMobileLightColor(flinearcolor& NewLightColor)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"Engine.SkyLightComponent.SetMobileLightColor");

	struct {
		flinearcolor NewLightColor;
	} params;
	params.NewLightColor = NewLightColor;

	this->process_event(function, &params);
}

void USkyLightComponent::SetMobileSkylightIntensity(float InMobileIntensity)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"Engine.SkyLightComponent.SetMobileSkylightIntensity");

	struct {
		float InMobileIntensity;
	} params;
	params.InMobileIntensity = InMobileIntensity;

	this->process_event(function, &params);
}

void USkyLightComponent::SetOcclusionContrast(float InOcclusionContrast)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"Engine.SkyLightComponent.SetOcclusionContrast");

	struct {
		float InOcclusionContrast;
	} params;
	params.InOcclusionContrast = InOcclusionContrast;

	this->process_event(function, &params);
}

void USkyLightComponent::SetOcclusionExponent(float InOcclusionExponent)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"Engine.SkyLightComponent.SetOcclusionExponent");

	struct {
		float InOcclusionExponent;
	} params;
	params.InOcclusionExponent = InOcclusionExponent;

	this->process_event(function, &params);
}

//void USkyLightComponent::SetOcclusionTint(FColor& InTint)
//{
//	static uobject* function;
//	if (!function)
//		function = uobject::find_object<uobject*>(L"Engine.SkyLightComponent.SetOcclusionTint");
//
//	struct {
//		FColor InTint;
//	} params;
//	params.InTint = InTint;
//
//	this->process_event(function, &params);
//}

void USkyLightComponent::SetSkyDistanceThreshold(float DistanceThreshold)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"Engine.SkyLightComponent.SetSkyDistanceThreshold");

	struct {
		float DistanceThreshold;
	} params;
	params.DistanceThreshold = DistanceThreshold;

	this->process_event(function, &params);
}

void USkyLightComponent::SetSourceCubemapAngle(float NewValue)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"Engine.SkyLightComponent.SetSourceCubemapAngle");

	struct {
		float NewValue;
	} params;
	params.NewValue = NewValue;

	this->process_event(function, &params);
}

void USkyLightComponent::SetVolumetricScatteringIntensity(float NewIntensity)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"Engine.SkyLightComponent.SetVolumetricScatteringIntensity");

	struct {
		float NewIntensity;
	} params;
	params.NewIntensity = NewIntensity;

	this->process_event(function, &params);
}

bool uskeletalmeshcomponent::AttachTo(uskeletalmeshcomponent* InParent, fname InSocketName, EAttachLocation AttachType, bool bWeldSimulatedBodies)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"Engine.SceneComponent.K2_AttachTo");

	struct
	{
		uskeletalmeshcomponent* InParent;
		fname InSocketName;
		EAttachLocation AttachType;
		bool bWeldSimulatedBodies;
		bool ReturnValue;
	} params;

	params.InParent = InParent;
	params.InSocketName = InSocketName;
	params.AttachType = AttachType;
	params.bWeldSimulatedBodies = bWeldSimulatedBodies;

	this->process_event(function, &params);

	return params.ReturnValue;
}



//bool uskeletalmeshcomponent::AttachToComponent(USceneComponent* Parent, fname SocketName,
//	EAttachmentRule LocationRule, EAttachmentRule RotationRule,
//	EAttachmentRule ScaleRule, bool bWeldSimulatedBodies)
//{
//	static uobject* function;
//	if (!function)
//		function = uobject::find_object<uobject*>(L"Engine.SceneComponent.K2_AttachToComponent");
//
//	struct
//	{
//		USceneComponent* Parent;
//		fname SocketName;
//		EAttachmentRule LocationRule;
//		EAttachmentRule RotationRule;
//		EAttachmentRule ScaleRule;
//		bool bWeldSimulatedBodies;
//		bool ReturnValue;
//	} params;
//
//	params.Parent = Parent;
//	params.SocketName = SocketName;
//	params.LocationRule = LocationRule;
//	params.RotationRule = RotationRule;
//	params.ScaleRule = ScaleRule;
//	params.bWeldSimulatedBodies = bWeldSimulatedBodies;
//
//	this->process_event(function, &params);
//
//	return params.ReturnValue;
//}

int32_t math::random_int(int32_t min, int32_t max) {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(L"Engine.KismetMathLibrary.RandomIntegerInRange");

	struct
	{
		int32_t min;
		int32_t max;
		int32_t output;
	} params = { min, max };


	variables.math_system->process_event(function, &params);
	return params.output;
}

int32_t uskeletalmeshcomponent::get_num_bones() {
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.SkinnedMeshComponent.GetNumBones"));
	struct {
		int32_t return_value;
	} params;
	this->process_event(function, &params);
	return params.return_value;
}
      
bool ashootercharacter::line_trace_single(
	uworld* world_context_object,
	fvector& start,
	fvector& end,
	ETraceTypeQuery trace_channel,
	bool b_trace_complex,
	tarray<AActor*>& actors_to_ignore,
	EDrawDebugTrace draw_debug_type,
	FHitResult& out_hit,
	bool b_ignore_self,
	flinearcolor& trace_color,
	flinearcolor& trace_hit_color,
	float draw_time)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetSystemLibrary.LineTraceSingle"));


	struct
	{
		const uworld* world_context_object;
		fvector             start;
		fvector             end;
		ETraceTypeQuery  trace_channel;
		bool                b_trace_complex;
		tarray<AActor*>     actors_to_ignore;
		EDrawDebugTrace  draw_debug_type;
		FHitResult          out_hit;
		bool                b_ignore_self;
		flinearcolor        trace_color;
		flinearcolor        trace_hit_color;
		float               draw_time;
		bool                return_value;
	} params;

	params.world_context_object = world_context_object;
	params.start = start;
	params.end = end;
	params.trace_channel = trace_channel;
	params.b_trace_complex = b_trace_complex;
	params.actors_to_ignore = actors_to_ignore;
	params.draw_debug_type = draw_debug_type;
	params.b_ignore_self = b_ignore_self;
	params.trace_color = trace_color;
	params.trace_hit_color = trace_hit_color;
	params.draw_time = draw_time;

	variables.kismet_system->process_event(function, &params);

	
		out_hit = params.out_hit;

	return params.return_value;
}

bool ClipLineToScreen(fvector2d& start, fvector2d& end, float screenWidth, float screenHeight)
{
	auto ComputeOutCode = [](float x, float y, float w, float h) -> int {
		int code = 0;
		if (x < 0) code |= 1;
		if (x > w) code |= 2;
		if (y < 0) code |= 4;
		if (y > h) code |= 8;
		return code;
		};

	int outcode0 = ComputeOutCode(start.x, start.y, screenWidth, screenHeight);
	int outcode1 = ComputeOutCode(end.x, end.y, screenWidth, screenHeight);

	while (true)
	{
		if (!(outcode0 | outcode1)) return true;
		if (outcode0 & outcode1) return false;

		int outcodeOut = outcode0 ? outcode0 : outcode1;
		float x, y;

		if (outcodeOut & 8) {
			x = start.x + (end.x - start.x) * (screenHeight - start.y) / (end.y - start.y);
			y = screenHeight;
		}
		else if (outcodeOut & 4) {
			x = start.x + (end.x - start.x) * (0 - start.y) / (end.y - start.y);
			y = 0;
		}
		else if (outcodeOut & 2) {
			y = start.y + (end.y - start.y) * (screenWidth - start.x) / (end.x - start.x);
			x = screenWidth;
		}
		else {
			y = start.y + (end.y - start.y) * (0 - start.x) / (end.x - start.x);
			x = 0;
		}

		if (outcodeOut == outcode0) {
			start.x = x;
			start.y = y;
			outcode0 = ComputeOutCode(start.x, start.y, screenWidth, screenHeight);
		}
		else {
			end.x = x;
			end.y = y;
			outcode1 = ComputeOutCode(end.x, end.y, screenWidth, screenHeight);
		}
	}
}


//bool system::line_trace_single_by_profile(
//	uobject* world_context_object,
//	fvector& start,
//	fvector& end,
//	fname& profile_name,
//	bool b_trace_complex,
//	tarray<ashootercharacter*>& actors_to_ignore,
//	EDrawDebugTrace draw_debug_type,
//	FHitResult* out_hit,
//	bool b_ignore_self,
//	flinearcolor& trace_color,
//	flinearcolor& trace_hit_color,
//	float draw_time)
//{
//	static uobject* function;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetSystemLibrary.LineTraceSingleByProfile"));
//
//	struct
//	{
//		uobject* world_context_object;
//		fvector             start;
//		fvector             end;
//		fname               profile_name;
//		bool                b_trace_complex;
//		tarray<ashootercharacter*>     actors_to_ignore;
//		EDrawDebugTrace  draw_debug_type;
//		FHitResult          out_hit;
//		bool                b_ignore_self;
//		flinearcolor        trace_color;
//		flinearcolor        trace_hit_color;
//		float               draw_time;
//		bool                return_value;
//	} params;
//
//	params.world_context_object = world_context_object;
//	params.start = start;
//	params.end = end;
//	params.profile_name = profile_name;
//	params.b_trace_complex = b_trace_complex;
//	params.actors_to_ignore = actors_to_ignore;
//	params.draw_debug_type = draw_debug_type;
//	params.b_ignore_self = b_ignore_self;
//	params.trace_color = trace_color;
//	params.trace_hit_color = trace_hit_color;
//	params.draw_time = draw_time;
//
//	variables.kismet_system->process_event(function, &params);
//
//	if (out_hit)
//		*out_hit = params.out_hit;
//
//	return params.return_value;
//}
//
//bool system::line_trace_single_for_objects(
//	uobject* world_context_object,
//	fvector& start,
//	fvector& end,
//	tarray<EObjectTypeQuery>& object_types,
//	bool b_trace_complex,
//	tarray<ashootercharacter*>& actors_to_ignore,
//	EDrawDebugTrace draw_debug_type,
//	FHitResult* out_hit,
//	bool b_ignore_self,
//	flinearcolor& trace_color,
//	flinearcolor& trace_hit_color,
//	float draw_time)
//{
//	static uobject* function;
//	if (!function)
//		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetSystemLibrary.LineTraceSingleForObjects"));
//
//	struct
//	{
//		uobject* world_context_object;
//		fvector                     start;
//		fvector                     end;
//		tarray<EObjectTypeQuery> object_types;
//		bool                        b_trace_complex;
//		tarray<ashootercharacter*>             actors_to_ignore;
//		EDrawDebugTrace          draw_debug_type;
//		FHitResult                  out_hit;
//		bool                        b_ignore_self;
//		flinearcolor                trace_color;
//		flinearcolor                trace_hit_color;
//		float                       draw_time;
//		bool                        return_value;
//	} params;
//
//	params.world_context_object = world_context_object;
//	params.start = start;
//	params.end = end;
//	params.object_types = object_types;
//	params.b_trace_complex = b_trace_complex;
//	params.actors_to_ignore = actors_to_ignore;
//	params.draw_debug_type = draw_debug_type;
//	params.b_ignore_self = b_ignore_self;
//	params.trace_color = trace_color;
//	params.trace_hit_color = trace_hit_color;
//	params.draw_time = draw_time;
//
//	variables.kismet_system->process_event(function, &params);
//
//	if (out_hit)
//		*out_hit = params.out_hit;
//
//	return params.return_value;
//}

void system::draw_debug_line(
	uobject* world_context_object,
	fvector& line_start,
	fvector& line_end,
	flinearcolor& line_color,
	float duration,
	float thickness)
{
	static uobject* function;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.KismetSystemLibrary.DrawDebugLine"));

	struct
	{
		uobject* world_context_object;
		fvector          line_start;
		fvector          line_end;
		flinearcolor     line_color;
		float            duration;
		float            thickness;
	} params;

	params.world_context_object = world_context_object;
	params.line_start = line_start;
	params.line_end = line_end;
	params.line_color = line_color;
	params.duration = duration;
	params.thickness = thickness;

	variables.kismet_system->process_event(function, &params);
}

int32_t ashootercharacter::GetLocalRole()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.GetLocalRole"));

	struct
	{
		int32_t ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

int32_t ashootercharacter::GetRemoteRole()
{
	static uobject* function = nullptr;
	if (!function)
		function = uobject::find_object<uobject*>(crypt(L"Engine.Actor.GetRemoteRole"));

	struct
	{
		int32_t ReturnValue;
	} params;

	this->process_event(function, &params);

	return params.ReturnValue;
}

FAttachmentTransformRules FAttachmentTransformRules::SnapToTargetNotIncludingScale = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, false);

bool meshcreated = false;

MeshData ParseOBJFile(const wchar_t* filepath) {
	MeshData data;

	std::ifstream file(filepath);
	if (!file.is_open()) {
		return data;
	}

	std::vector<fvector> temp_vertices;
	std::vector<fvector2d> temp_uvs;
	std::vector<fvector> temp_normals;

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string type;
		iss >> type;

		if (type == "v") {
			float x, y, z;
			iss >> x >> y >> z;
			temp_vertices.push_back(fvector(x * 100.0f, y * 100.0f, z * 100.0f));
		}
		else if (type == "vt") {
			float u, v;
			iss >> u >> v;
			temp_uvs.push_back(fvector2d(u, 1.0f - v));
		}
		else if (type == "vn") {
			float x, y, z;
			iss >> x >> y >> z;
			temp_normals.push_back(fvector(x, y, z));
		}
		else if (type == "f") {
			std::string v1, v2, v3;
			iss >> v1 >> v2 >> v3;

			auto parse_face_vertex = [&](const std::string& vert_data) {
				std::istringstream vss(vert_data);
				std::string index_str;
				int v_idx = 0, vt_idx = 0, vn_idx = 0;

				std::getline(vss, index_str, '/');
				v_idx = std::stoi(index_str) - 1;

				std::getline(vss, index_str, '/');
				if (!index_str.empty()) vt_idx = std::stoi(index_str) - 1;

				std::getline(vss, index_str, '/');
				if (!index_str.empty()) vn_idx = std::stoi(index_str) - 1;

			int current_index = data.Vertices.Num();
			data.Vertices.add(temp_vertices[v_idx]);

			if (vt_idx >= 0 && vt_idx < (int)temp_uvs.size()) {
				data.UV0.add(temp_uvs[vt_idx]);
			}
			else {
				data.UV0.add(fvector2d(0, 0));
			}

			if (vn_idx >= 0 && vn_idx < (int)temp_normals.size()) {
				data.Normals.add(temp_normals[vn_idx]);
			}
			else {
				data.Normals.add(fvector(0, 0, 1));
			}

			data.VertexColors.add(FColor(255, 255, 255, 255));

				return current_index;
			};

			int i1 = parse_face_vertex(v1);
			int i2 = parse_face_vertex(v2);
			int i3 = parse_face_vertex(v3);

			data.Triangles.add(i1);
			data.Triangles.add(i2);
			data.Triangles.add(i3);
		}
	}

	file.close();

	for (int i = 0; i < data.Vertices.Num(); i++) {
		FProcMeshTangent tangent;
		tangent.TangentX = fvector(1, 0, 0);
		tangent.bFlipTangentY = false;
		data.Tangents.add(tangent);
	}

	return data;
}

void ReplaceWeaponMeshWith3DModel(currentequippable* Weapon, const wchar_t* objFilePath) {
	if (!Weapon || !Weapon->GetMesh1P()) {
		return;
	}

	static uclass* ProcMeshClass = nullptr;
	if (!ProcMeshClass) {
		ProcMeshClass = uobject::find_object<uclass*>(
			crypt(L"ProceduralMeshComponent.ProceduralMeshComponent")
		);
	}
	if (!ProcMeshClass) return;

	static uobject* AddComponentFunc = uobject::find_object<uobject*>(
		crypt(L"ShooterGame.ShooterBlueprintLibrary.AddComponentByClass")
	);
	if (!AddComponentFunc) return;

	struct {
		AActor* Actor;
		UActorComponent* ComponentClass;
		bool bManualAttachment;
		ftransform* RelativeTransform;
		UActorComponent* ReturnValue;
	} Params = { (AActor*)Weapon, (UActorComponent*)ProcMeshClass, false, nullptr, nullptr };

	Weapon->process_event(AddComponentFunc, &Params);
	auto* ProcMesh = (UProceduralMeshComponent*)Params.ReturnValue;

	if (!ProcMesh) return;

	MeshData weaponMesh = ParseOBJFile(objFilePath);
	if (weaponMesh.Vertices.Num() == 0) return;

	for (int i = 0; i < weaponMesh.Normals.Num(); i++) {
		weaponMesh.Normals[i] = weaponMesh.Normals[i] * -1.0;
	}

	for (int i = 0; i < weaponMesh.Triangles.Num(); i += 3) {
		int32_t temp = weaponMesh.Triangles[i + 1];
		weaponMesh.Triangles[i + 1] = weaponMesh.Triangles[i + 2];
		weaponMesh.Triangles[i + 2] = temp;
	}

	if (weaponMesh.VertexColors.Num() == 0) {
		for (int i = 0; i < weaponMesh.Vertices.Num(); i++) {
			weaponMesh.VertexColors.add(FColor(255, 255, 255, 255));
		}
	}

	static uobject* CreateMeshFunc = uobject::find_object<uobject*>(
		crypt(L"ProceduralMeshComponent.ProceduralMeshComponent.CreateMeshSection")
	);
	if (!CreateMeshFunc) return;

	struct {
		int32_t SectionIndex;
		tarray<fvector> Vertices;
		tarray<int32_t> Triangles;
		tarray<fvector> Normals;
		tarray<fvector2d> UV0;
		tarray<FColor> VertexColors;
		tarray<FProcMeshTangent> Tangents;
		bool bCreateCollision;
	} CreateParams = {
		0, weaponMesh.Vertices, weaponMesh.Triangles, weaponMesh.Normals,
		weaponMesh.UV0, weaponMesh.VertexColors, weaponMesh.Tangents, false
	};

	ProcMesh->process_event(CreateMeshFunc, &CreateParams);

	auto* OriginalMesh = Weapon->GetMesh1P();

	static uobject* GetMaterialFunc = uobject::find_object<uobject*>(
		crypt(L"Engine.MeshComponent.GetMaterial")
	);

	if (GetMaterialFunc) {
		struct { int32_t ElementIndex; UMaterialInterface* ReturnValue; } GetMatParams = { 0, nullptr };
		OriginalMesh->process_event(GetMaterialFunc, &GetMatParams);

		if (GetMatParams.ReturnValue) {
			static uobject* SetMaterialFunc = uobject::find_object<uobject*>(
				crypt(L"Engine.MeshComponent.SetMaterial")
			);
			if (SetMaterialFunc) {
				struct { int32_t ElementIndex; UMaterialInterface* Material; } SetMatParams = { 0, GetMatParams.ReturnValue };
				ProcMesh->process_event(SetMaterialFunc, &SetMatParams);
			}
		}
	}

	static uobject* AttachFunc = uobject::find_object<uobject*>(
		crypt(L"Engine.SceneComponent.K2_AttachToComponent")
	);
	fname WeaponPoint = string::string_to_name(L"R_WeaponPoint");
	if (AttachFunc) {
		struct {
			void* Parent;
			fname SocketName;
			int LocationRule;
			int RotationRule;
			int ScaleRule;
			bool bWeldSimulatedBodies;
			bool ReturnValue;
		} AttachParams;
		AttachParams.Parent = OriginalMesh;
		AttachParams.SocketName = WeaponPoint;
		AttachParams.LocationRule = (int)EAttachmentRule::SnapToTarget;
		AttachParams.RotationRule = (int)EAttachmentRule::SnapToTarget;
		AttachParams.ScaleRule = (int)EAttachmentRule::KeepRelative;
		AttachParams.bWeldSimulatedBodies = false;
		ProcMesh->process_event(AttachFunc, &AttachParams);
	}

	ProcMesh->SetRelativeRotation(FRotator(0, -90, 0), false, true);

	static uobject* SetRelativeLocationFunc = uobject::find_object<uobject*>(
		crypt(L"Engine.SceneComponent.K2_SetRelativeLocation")
	);
	if (SetRelativeLocationFunc) {
		struct {
			fvector NewLocation;
			bool bSweep;
			FHitResult SweepHitResult;
			bool bTeleport;
		} LocParams = { fvector(0, 0, 0), false, FHitResult(), false };
		ProcMesh->process_event(SetRelativeLocationFunc, &LocParams);
	}

	ProcMesh->SetRelativeScale3D(fvector(1, 1, 1));

	static uobject* SetVisibilityFunc = uobject::find_object<uobject*>(
		crypt(L"Engine.SceneComponent.SetVisibility")
	);

	if (SetVisibilityFunc) {
		struct { bool bNewVisibility; bool bPropagateToChildren; } VisParams;

		VisParams.bNewVisibility = false;
		VisParams.bPropagateToChildren = true;
		OriginalMesh->process_event(SetVisibilityFunc, &VisParams);

		VisParams.bNewVisibility = true;
		ProcMesh->process_event(SetVisibilityFunc, &VisParams);
	}

	static uobject* RegisterFunc = uobject::find_object<uobject*>(
		crypt(L"Engine.ActorComponent.RegisterComponent")
	);
	if (RegisterFunc) {
		ProcMesh->process_event(RegisterFunc, nullptr);
	}

	fvector location = fvector(-0.9434f, 0.943392f, -2.83019f);
	FRotator rotation = FRotator(0, 90, -90);
	fvector scale = fvector(1.5f, 1.5f, 1.5f);

	ProcMesh->SetRelativeScale3D(scale);
	ProcMesh->SetRelativeRotation(rotation, false, true);

	meshcreated = true;
}
