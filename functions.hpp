#pragma once
#include "offsets.hpp"
#include "memory.hpp"
#include "math.hpp"
#include "structs.hpp"
#include "xor.hpp"
#include <Windows.h>
#include "ret_spoof.h"
#include "spoof.h"
#include <set>

class fmemory {
public:
	static uint64_t malloc(int32_t size, uint32_t aligment);
};

class uclass
{
public:
	uclass* super_class();
};

class uclass;
class uobject {
public:
	uclass* object_class();
	uobject* class_private;
	/*uobject* StaticFindObject(const wchar_t* name, const wchar_t* obj_class = nullptr)
	{
		SPOOF_FUNC;

		static uobject* (*StaticFindObjectInternal)(
			uobject * Class,
			uobject * InOuter,
			const wchar_t* Name,
			bool ExactClass
			) = reinterpret_cast<decltype(StaticFindObjectInternal)>(memory::module_base + offsets::static_find_object);

		return StaticFindObjectInternal(nullptr, nullptr, name, false);
	}*/


	template <typename t>
	static t static_find_object(uobject* klass, uobject* outer, const wchar_t* name) {

		SPOOF_FUNC

			return reinterpret_cast<t(*)(uobject*, uobject*, const wchar_t*, uintptr_t, void*)>(spoofcall_stub)(klass, outer, name, offsets::magic, (void*)(memory::module_base + offsets::static_find_object));
	}

	template <typename t>
	static t find_object(const wchar_t* name, uobject* outer = nullptr) {
		SPOOF_FUNC

			return uobject::static_find_object<t>(nullptr, outer, name);
	}

	template<typename type = uobject> static inline type* find_object1(const wchar_t* name, uobject* outer = nullptr, bool exact = true) {

		SPOOF_FUNC

			return uobject::static_find_object<type*>(nullptr, outer, name);
	}

	//static uobject* StaticFindObject(uclass* Class, uobject* InOuter, const wchar_t* Name, bool ExactClass)
	//{
	//	static uintptr_t StaticFindObjectAddress = memory::module_base + offsets::static_find_object;

	//	auto StaticFindObjectFN = reinterpret_cast<uobject * (__fastcall*)(uclass*, uobject*, const wchar_t*, bool)>(StaticFindObjectAddress);

	//	return StaticFindObjectFN(Class, InOuter, Name, ExactClass);
	//}

	static uobject* StaticFindObject(const wchar_t* Name)
	{

		static uintptr_t StaticFindObjectAddress = memory::module_base + offsets::static_find_object;
		return reinterpret_cast<uobject * (__fastcall*)(uobject*, uobject*, const wchar_t*, bool, uintptr_t, void*)>(spoofcall_stub)(nullptr, reinterpret_cast<uobject*>(-1), Name, false, offsets::magic, (void*)StaticFindObjectAddress);
	}

	void process_event2(void* class_, uobject* function, void* params);

	//void process_event2(void* class_, uobject* function, void* params);

	static uobject* StaticFindObject(uclass* Class, uobject* InOuter, const wchar_t* Name, bool ExactClass)
	{
		SPOOF_FUNC

			static uintptr_t StaticFindObjectAddress = memory::module_base + offsets::static_find_object;

		return reinterpret_cast<uobject * (*)(uclass*, uobject*, const wchar_t*, bool, uintptr_t, void*)>(
			spoofcall_stub
			)(Class, InOuter, Name, ExactClass, offsets::magic,
				reinterpret_cast<void*>(StaticFindObjectAddress)
				);
	}

	/*uobject* StaticLoadObject(uobject* Class, uobject* InOuter, const wchar_t* Name)
	{
		SPOOF_FUNC;
		static uintptr_t StaticLoadObjectAddress = memory::module_base + offsets::static_laod_object;
		return reinterpret_cast<uobject * (__fastcall*)(uobject*, uobject*, const wchar_t*, bool, uintptr_t, void*)>(spoofcall_stub)(nullptr, reinterpret_cast<uobject*>(-1), Name, false, offsets::magic, (void*)StaticLoadObjectAddress);
	}

	uobject* StaticFindObject(uobject* Class, uobject* InOuter, const wchar_t* Name, bool ExactClass)
	{
		SPOOF_FUNC;
		static uintptr_t StaticFindObjectAddress = memory::module_base + offsets::static_find_object;
		return reinterpret_cast<uobject * (*)(uobject*, uobject*, const wchar_t*, bool, uintptr_t, void*)>(spoofcall_stub)(Class, InOuter, Name, ExactClass, offsets::magic, (void*)StaticFindObjectAddress);
	}*/

	void ProcessEvent(void* class_, void* params);

	void ProcessEvent(void* class_, uobject* function, void* params);

	void process_event(uobject* function, void* args);

	static uobject* static_load_object(uobject* Class, uobject* InOuter, const wchar_t* Name);

	static uobject* StaticLoadObject(const wchar_t* ObjectPath);

	bool k2_set_actor_location_and_rotation(fvector NewLocation, fvector NewRotation);
	bool k2_set_actor_location_and_rotation2(fvector NewLocation, frotator NewRotation);

	ftext GetItemNameText();

	bool is_child_of(uclass* parent);

	template <typename type = uobject>
	type* cast() {
		return reinterpret_cast<type*>(this);
	}
};

template<class type> class enum_as_byte {
public:
	enum_as_byte() {}
	enum_as_byte(type value) : value(static_cast<std::uint8_t>(value)) {}

	explicit enum_as_byte(std::int32_t value) : value(static_cast<std::uint8_t>(value)) {}
	explicit enum_as_byte(std::uint8_t value) : value(value) {}

	operator type() const { return type(value); }
	type get() const { return type(value); }

private:
	std::uint8_t value;
};

static enum search_case : std::uint8_t {
	case_sensitive, ignore_case
};

enum class EObjectTypeQuery : uint8_t
{
	ObjectTypeQuery1 = 0,
	ObjectTypeQuery2 = 1,
	ObjectTypeQuery3 = 2,
	ObjectTypeQuery4 = 3,
	ObjectTypeQuery5 = 4,
	ObjectTypeQuery6 = 5,
	ObjectTypeQuery7 = 6,
	ObjectTypeQuery8 = 7,
	ObjectTypeQuery9 = 8,
	ObjectTypeQuery10 = 9,
	ObjectTypeQuery11 = 10,
	ObjectTypeQuery12 = 11,
	ObjectTypeQuery13 = 12,
	ObjectTypeQuery14 = 13,
	ObjectTypeQuery15 = 14,
	ObjectTypeQuery16 = 15,
	ObjectTypeQuery17 = 16,
	ObjectTypeQuery18 = 17,
	ObjectTypeQuery19 = 18,
	ObjectTypeQuery20 = 19,
	ObjectTypeQuery21 = 20,
	ObjectTypeQuery22 = 21,
	ObjectTypeQuery23 = 22,
	ObjectTypeQuery24 = 23,
	ObjectTypeQuery25 = 24,
	ObjectTypeQuery26 = 25,
	ObjectTypeQuery27 = 26,
	ObjectTypeQuery28 = 27,
	ObjectTypeQuery29 = 28,
	ObjectTypeQuery30 = 29,
	ObjectTypeQuery31 = 30,
	ObjectTypeQuery32 = 31,
	ObjectTypeQuery_MAX = 32,
	EObjectTypeQuery_MAX = 33,
};

enum class EDrawDebugTrace : uint8_t
{
	None = 0,
	ForOneFrame = 1,
	ForDuration = 2,
	Persistent = 3,
	EDrawDebugTrace_MAX = 4,
};

enum class ETraceTypeQuery : uint8_t
{
	TraceTypeQuery1 = 0,
	TraceTypeQuery2 = 1,
	TraceTypeQuery3 = 2,
	TraceTypeQuery4 = 3,
	TraceTypeQuery5 = 4,
	TraceTypeQuery6 = 5,
	TraceTypeQuery7 = 6,
	TraceTypeQuery8 = 7,
	TraceTypeQuery9 = 8,
	TraceTypeQuery10 = 9,
	TraceTypeQuery11 = 10,
	TraceTypeQuery12 = 11,
	TraceTypeQuery13 = 12,
	TraceTypeQuery14 = 13,
	TraceTypeQuery15 = 14,
	TraceTypeQuery16 = 15,
	TraceTypeQuery17 = 16,
	TraceTypeQuery18 = 17,
	TraceTypeQuery19 = 18,
	TraceTypeQuery20 = 19,
	TraceTypeQuery21 = 20,
	TraceTypeQuery22 = 21,
	TraceTypeQuery23 = 22,
	TraceTypeQuery24 = 23,
	TraceTypeQuery25 = 24,
	TraceTypeQuery26 = 25,
	TraceTypeQuery27 = 26,
	TraceTypeQuery28 = 27,
	TraceTypeQuery29 = 28,
	TraceTypeQuery30 = 29,
	TraceTypeQuery31 = 30,
	TraceTypeQuery32 = 31,
	TraceTypeQuery_MAX = 32,
	ETraceTypeQuery_MAX = 33,
};

struct FHitResult
{
public:
	int32_t FaceIndex;                                         // 0x0000(0x0004)
	float Time;                                                // 0x0004(0x0004)
	float Distance;                                            // 0x0008(0x0004)
	uint8_t Pad_C[0x8];                                        // 0x000C(0x0008)
	fvector Location;                                          // 0x0014(0x0018)
	fvector ImpactPoint;                                       // 0x002C(0x0018)
	fvector Normal;                                            // 0x0044(0x0018)
	fvector ImpactNormal;                                      // 0x005C(0x0018)
	fvector TraceStart;                                        // 0x0074(0x0018)
	fvector TraceEnd;                                          // 0x008C(0x0018)
	float PenetrationDepth;                                    // 0x00A4(0x0004)
	int32_t MyItem;                                            // 0x00A8(0x0004)
	int32_t Item;                                              // 0x00AC(0x0004)
	uint8_t ElementIndex;                                      // 0x00B0(0x0001)
	uint8_t bBlockingHit : 1;                                  // 0x00B1(0x0001) - BITFIELD
	uint8_t bStartPenetrating : 1;                             // 0x00B1(0x0001) - BITFIELD
	uint8_t Pad_B2[0x6];                                       // 0x00B2(0x0006)
	fname BoneName;                                            // 0x00B8(0x000C)
	fname MyBoneName;                                          // 0x00C4(0x000C)
	// Total size: 0xD0 (208 bytes)
};// Class Engine.Actor
// Size: 0x3b8 (Inherited: 0x30)
struct AActor : public uobject {
	char bLocallyHidden : 1; // 0x60(0x01)
	char pad_60_1 : 7; // 0x60(0x01)
	char pad_61[0x7]; // 0x61(0x07)
	char pad_78[0xa4]; // 0x78(0xa4)
	char bNetTemporary : 1; // 0x11c(0x01)
	char bNetStartup : 1; // 0x11c(0x01)
	char bOnlyRelevantToOwner : 1; // 0x11c(0x01)
	char bAlwaysRelevant : 1; // 0x11c(0x01)
	char bReplicateMovement : 1; // 0x11c(0x01)
	char bHidden : 1; // 0x11c(0x01)
	char bTearOff : 1; // 0x11c(0x01)
	char bForceNetAddressable : 1; // 0x11c(0x01)
	char bExchangedRoles : 1; // 0x11d(0x01)
	char bNetLoadOnClient : 1; // 0x11d(0x01)
	char bNetUseOwnerRelevancy : 1; // 0x11d(0x01)
	char bRelevantForNetworkReplays : 1; // 0x11d(0x01)
	char bRelevantForLevelBounds : 1; // 0x11d(0x01)
	char bReplayRewindable : 1; // 0x11d(0x01)
	char bAllowTickBeforeBeginPlay : 1; // 0x11d(0x01)
	char bAutoDestroyWhenFinished : 1; // 0x11d(0x01)
	char bCanBeDamaged : 1; // 0x11e(0x01)
	char bBlockInput : 1; // 0x11e(0x01)
	char bCollideWhenPlacing : 1; // 0x11e(0x01)
	char bFindCameraComponentWhenViewTarget : 1; // 0x11e(0x01)
	char bGenerateOverlapEventsDuringLevelStreaming : 1; // 0x11e(0x01)
	char bIgnoresOriginShifting : 1; // 0x11e(0x01)
	char bEnableAutoLODGeneration : 1; // 0x11e(0x01)
	char bIsEditorOnlyActor : 1; // 0x11e(0x01)
	char bChildActorsManuallySpawn : 1; // 0x11f(0x01)
	char bActorSeamlessTraveled : 1; // 0x11f(0x01)
	char bReplicates : 1; // 0x11f(0x01)
	char bCanBeInCluster : 1; // 0x11f(0x01)
	char bAllowReceiveTickEventOnDedicatedServer : 1; // 0x11f(0x01)
	char pad_11F_5 : 3; // 0x11f(0x01)
	char pad_120_0 : 5; // 0x120(0x01)
	char bActorEnableCollision : 1; // 0x120(0x01)
	char bActorIsBeingDestroyed : 1; // 0x120(0x01)
	char pad_120_7 : 1; // 0x120(0x01)
	char pad_121[0x1]; // 0x121(0x01)
	int32_t InputPriority; // 0x1d8(0x04)
	char pad_1DC[0x4]; // 0x1dc(0x04)
	struct UInputComponent* InputComponent; // 0x1e0(0x08)
	float NetCullDistanceSquared; // 0x1e8(0x04)
	int32_t NetTag; // 0x1ec(0x04)
	float NetUpdateFrequency; // 0x1f0(0x04)
	float MinNetUpdateFrequency; // 0x1f4(0x04)
	float NetPriority; // 0x1f8(0x04)
	char pad_1FC[0x24]; // 0x1fc(0x24)
	struct APawn* Instigator; // 0x220(0x08)
	char pad_296[0x2]; // 0x296(0x02)
	char pad_2AA[0x6]; // 0x2aa(0x06)
	char pad_2D0[0xb8]; // 0x2d0(0xb8)
	char pad_3A8[0x10]; // 0x3a8(0x10)

	float CustomTimeDilation;
};

enum class ECollisionEnabled : uint8_t {
	NoCollision = 0,
	QueryOnly = 1,
	PhysicsOnly = 2,
	QueryAndPhysics = 3,
	ECollisionEnabled_MAX = 4
};

// Enum Engine.ECollisionChannel
enum class ECollisionChannel : uint8_t {
	ECC_WorldStatic = 0,
	ECC_WorldDynamic = 1,
	ECC_Pawn = 2,
	ECC_Visibility = 3,
	ECC_Camera = 4,
	ECC_PhysicsBody = 5,
	ECC_Vehicle = 6,
	ECC_Destructible = 7,
	ECC_EngineTraceChannel1 = 8,
	ECC_EngineTraceChannel2 = 9,
	ECC_EngineTraceChannel3 = 10,
	ECC_EngineTraceChannel4 = 11,
	ECC_EngineTraceChannel5 = 12,
	ECC_EngineTraceChannel6 = 13,
	ECC_GameTraceChannel1 = 14,
	ECC_GameTraceChannel2 = 15,
	ECC_GameTraceChannel3 = 16,
	ECC_GameTraceChannel4 = 17,
	ECC_GameTraceChannel5 = 18,
	ECC_GameTraceChannel6 = 19,
	ECC_GameTraceChannel7 = 20,
	ECC_GameTraceChannel8 = 21,
	ECC_GameTraceChannel9 = 22,
	ECC_GameTraceChannel10 = 23,
	ECC_GameTraceChannel11 = 24,
	ECC_GameTraceChannel12 = 25,
	ECC_GameTraceChannel13 = 26,
	ECC_GameTraceChannel14 = 27,
	ECC_GameTraceChannel15 = 28,
	ECC_GameTraceChannel16 = 29,
	ECC_GameTraceChannel17 = 30,
	ECC_GameTraceChannel18 = 31,
	ECC_OverlapAll_Deprecated = 32,
	ECC_MAX = 33
};

// Enum Engine.ECollisionResponse
enum class ECollisionResponse : uint8_t {
	ECR_Ignore = 0,
	ECR_Overlap = 1,
	ECR_Block = 2,
	ECR_MAX = 3
};

//class utexture : public uobject
//{
//public:
//	int32_t LODBias;
//	uint8_t StreamingImportance;
//	uint8_t CompressionSettings;
//	uint8_t Filter;
//	uint8_t MipLoadOptions;
//	uint8_t LODGroup;
//	float Downscale;
//	uint8_t DownscaleOptions;
//	uint8_t SRGB : 1;
//	uint8_t bNoTiling : 1;
//	uint8_t VirtualTextureStreaming : 1;
//	uint8_t CompressionYCoCg : 1;
//	uint8_t bNotOfflineProcessed : 1;
//	int32_t ForcedStreamingRefCount;
//	uint8_t bAsyncResourceReleaseHasBeenStarted : 1;
//
//	static uobject* StaticClass()
//	{
//		return uobject::find_object<uobject*>(crypt(L"Engine.Texture"));
//	}
//};

struct utexture : public uobject {
	char pad_68[0x8]; // 0x68(0x08)
	int32_t LODBias; // 0x80(0x04)
	//enum class TextureGroup LODGroup; // 0x88(0x01)
	char pad_89[0x3]; // 0x89(0x03)
	char SRGB : 1; // 0x91(0x01)
	char bNoTiling : 1; // 0x91(0x01)
	char VirtualTextureStreaming : 1; // 0x91(0x01)
	char CompressionYCoCg : 1; // 0x91(0x01)
	char bNotOfflineProcessed : 1; // 0x91(0x01)
	char pad_91_5 : 3; // 0x91(0x01)
	char pad_92[0x2]; // 0x92(0x02)
	int32_t ForcedStreamingRefCount; // 0x94(0x04)
	char bAsyncResourceReleaseHasBeenStarted : 1; // 0x98(0x01)
	char pad_98_1 : 7; // 0x98(0x01)
	char pad_99[0x7]; // 0x99(0x07)
	tarray<struct UAssetUserData*> AssetUserData; // 0xa0(0x10)
	char pad_B0[0xe0]; // 0xb0(0xe0)
};

class utexture2d : public utexture
{
public:
	int32_t LevelIndex;
	int32_t FirstResourceMemMip;
	uint8_t bTemporarilyDisableStreaming : 1;
	uint8_t Pad_193[0x1];
	uint8_t Pad_19C[0x14];
};

class system : public uobject
{
public:
	static fstring get_object_name(uobject* object);
	static bool contains_string(const wchar_t* search_in, const wchar_t* sub_string, bool use_case = false, bool search_from_end = false);
	static bool starts_with(const wchar_t* source, const wchar_t* prefix, const enum_as_byte<search_case>& search_case = ignore_case);
	uobject* get_outer_object(uobject* object);

	static fvector find_look_at_rotation(fvector start, fvector end);

	static bool ares_line_trace_single_by_channel(uobject* world_context, const fvector& start, const fvector& end, const std::vector<AActor*> actors_to_ignore, FHitResult* out_hit, ECollisionChannel trace_channel, bool trace_complex, bool include_moving_objects);

	static utexture2d* import_file_as_texture2d(uobject* world_context_object, fstring filename);

	//static bool line_trace_single(uobject* world_context_object, fvector& start, fvector& end, ETraceTypeQuery trace_channel, bool b_trace_complex, tarray<ashootercharacter*>& actors_to_ignore, EDrawDebugTrace draw_debug_type, FHitResult* out_hit, bool b_ignore_self, flinearcolor& trace_color, flinearcolor& trace_hit_color, float draw_time);
	/*static bool line_trace_single_by_profile(uobject* world_context_object, fvector& start, fvector& end, fname& profile_name, bool b_trace_complex, tarray<ashootercharacter*>& actors_to_ignore, EDrawDebugTrace draw_debug_type, FHitResult* out_hit, bool b_ignore_self, flinearcolor& trace_color, flinearcolor& trace_hit_color, float draw_time);
	static bool line_trace_single_for_objects(uobject* world_context_object, fvector& start, fvector& end, tarray<EObjectTypeQuery>& object_types, bool b_trace_complex, tarray<ashootercharacter*>& actors_to_ignore, EDrawDebugTrace draw_debug_type, FHitResult* out_hit, bool b_ignore_self, flinearcolor& trace_color, flinearcolor& trace_hit_color, float draw_time);*/
	static void draw_debug_line(uobject* world_context_object, fvector& line_start, fvector& line_end, flinearcolor& line_color, float duration, float thickness);

	//static bool line_trace_single1(uobject* world_context, fvector start, fvector end, ETraceTypeQuery trace_channel, bool trace_complex, std::vector<ashootercharacter*> actors_to_ignore, EDrawDebugTrace debug_type, FHitResult out_hit, bool ignore_self, flinearcolor trace_color, flinearcolor trace_hit_color, float draw_time);

	/*static inline __int64 decrypt_parent(uobject* parent) {
		SPOOF_FUNC
		static __int64(__fastcall * decrypt_function)(__int64);
		if (!decrypt_function) {
			decrypt_function = reinterpret_cast<decltype(decrypt_function)>(DecryptOffsetClear(offsets::skin_decrypt) + memory::module_base);
		}

		if (!decrypt_function) return 0x0;

		return decrypt_function((__int64)parent);
	}*/
};

class string : public uobject
{
public:
	static fname string_to_name(fstring string);
	static bool contains(fstring SearchIn, fstring Substring, bool bUseCase = false, bool bSearchFromEnd = false);
	static fstring int_to_string(const int value);
};

class equippable_skin_data_asset : public uobject
{
public:
	int32_t get_type() {
		fstring name = system::get_object_name(this);

		if (string::contains(name, crypt(L"Default__BasePistol").decrypt(), true, false)) {
			return 1;
		}
		else if (string::contains(name, crypt(L"Default__SawedOffShotgun").decrypt(), true, false) || string::contains(name, crypt(L"Default__Slim").decrypt(), true, false)) {
			return 2;
		}
		else if (string::contains(name, crypt(L"Default__AutoPistol").decrypt(), true, false) || string::contains(name, crypt(L"Default__AutomaticPistol").decrypt(), true, false)) {
			return 3;
		}
		else if (string::contains(name, crypt(L"Default__Luger").decrypt(), true, false)) {
			return 4;
		}
		else if (string::contains(name, crypt(L"Default__Revolver").decrypt(), true, false)) {
			return 5;
		}
		else if (string::contains(name, crypt(L"Default__Vector").decrypt(), true, false)) {
			return 6;
		}
		else if (string::contains(name, crypt(L"Default__MP5").decrypt(), true, false) || string::contains(name, crypt(L"Default__SubMachineGun_MP5").decrypt(), true, false)) {
			return 7;
		}
		else if (string::contains(name, crypt(L"Default__PumpShotgun").decrypt(), true, false)) {
			return 8;
		}
		else if (string::contains(name, crypt(L"Default__AutomaticShotgun").decrypt(), true, false) || string::contains(name, crypt(L"Default__AutoShotgun").decrypt(), true, false)) {
			return 9;
		}
		else if (string::contains(name, crypt(L"Default__Burst").decrypt(), true, false) || string::contains(name, crypt(L"Default__AssaultRifle_Burst").decrypt(), true, false)) {
			return 10;
		}
		else if (string::contains(name, crypt(L"Default__DMR").decrypt(), true, false)) {
			return 11;
		}
		else if (string::contains(name, crypt(L"Default__AssaultRifle_ACR").decrypt(), true, false) || string::contains(name, crypt(L"Default__Carbine").decrypt(), true, false)) {
			return 12;
		}
		else if (string::contains(name, crypt(L"Default__AK").decrypt(), true, false) || string::contains(name, crypt(L"Default__AssaultRifle_AK").decrypt(), true, false)) {
			return 13;
		}
		else if (string::contains(name, crypt(L"Default__LeverSniperRifle").decrypt(), true, false) || string::contains(name, crypt(L"Default__LeverSniper").decrypt(), true, false)) {
			return 14;
		}
		else if (string::contains(name, crypt(L"Default__BoltSniper").decrypt(), true, false)) {
			return 15;
		}
		else if (string::contains(name, crypt(L"Default__LMG").decrypt(), true, false) || string::contains(name, crypt(L"Default__LightMachineGun").decrypt(), true, false)) {
			return 16;
		}
		else if (string::contains(name, crypt(L"Default__HMG").decrypt(), true, false) || string::contains(name, crypt(L"Default__HeavyMachineGun").decrypt(), true, false)) {
			return 17;
		}
		else if (string::contains(name, crypt(L"Default__Melee").decrypt(), true, false)) {
			return 18;
		}
		else if (string::contains(name, crypt(L"Default__DS_Gun").decrypt(), true, false)) {
			return 19;
		}
		return 0;
	}

	tarray<int> get_skin_levels();
};

class equippable_skin_chroma_inventory_model : public uobject
{
public:
	uobject* get_skin_chroma_data_asset();
};

class equippable_skin_inventory_model : public uobject
{
public:
	equippable_skin_data_asset* get_skin_data_asset();
	equippable_skin_chroma_inventory_model* get_skin_inventory_chroma_asset();
};

template<class k, class e>
class tmap
{
public:
	k Key;
	e Element;
	char __pad0x[0x8];
};

template<class type> class array {
public: friend class fstring;
public:
	array() : data(nullptr), count(std::int32_t()), maxx(std::int32_t()) {}
	array(type* data, std::int32_t count, std::int32_t maxx) : data(data), count(count), maxx(maxx) {}

	const bool is_valid() const noexcept
	{
		return !(this->data == nullptr);
	}

	const std::int32_t size() const noexcept
	{
		return this->count;
	}

	type& operator[](std::int32_t index) noexcept
	{
		return this->data[index];
	}

	const type& operator[](std::int32_t index) const noexcept
	{
		return this->data[index];
	}

	bool is_valid_index(std::int32_t index) const noexcept
	{
		return index < this->size();
	}

protected:
	type* data;
	std::int32_t count;
	std::int32_t maxx;
};

class equippable_charm_level_data_asset : public uobject
{
public:
	int get_charm_level();
};

class equippable_charm_instance_inventory_model : public uobject
{
public:
	uobject* get_charm_data_asset();
	equippable_charm_level_data_asset* get_charm_level_data_asset();
	equippable_charm_instance_inventory_model* get_equipped_charm_instance();
};

class equippable_inventory_model : public uobject
{
public:
	equippable_skin_inventory_model* get_equipped_skin_model();
	equippable_charm_instance_inventory_model* get_equipped_charm_instance();
};

enum class EAresOutlineMode : uint8_t {
	None = 0,
	Outline = 1,
	Block = 2,
	Enemy = 3,
	AlwaysOutline = 4,
	AlwaysEnemy = 5,
	EAresOutlineMode_MAX = 6
};

class uammocomponent : public uobject
{
public:
	void FullReload()
	{
		static uobject* function;
		if (!function)
			function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AmmoComponent.FullReload"));

		this->process_event(function, nullptr);
	}

	void SetMaxReserveAmmo(bool bInfiniteReserve, int32_t NewMax)
	{
		static uobject* function;
		if (!function)
			function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AmmoComponent.SetMaxReserveAmmo"));

		struct
		{
			bool bInfiniteReserve;
			int32_t NewMax;
		} params;

		params.bInfiniteReserve = bInfiniteReserve;
		params.NewMax = NewMax;

		this->process_event(function, &params);
	}

	int32_t GetAmmo()
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

	bool CanReload()
	{
		static uobject* function;
		if (!function)
			function = uobject::find_object<uobject*>(crypt(L"ShooterGame.AmmoComponent.CanReload"));

		struct
		{
			bool ReturnValue;
		} params;

		this->process_event(function, &params);

		return params.ReturnValue;
	}
	int32_t GetMaxAmmo();
};


class umaterialinterface : public uobject
{
public:
	class usubsurfaceprofile* SubsurfaceProfile;
	tarray<struct fmaterialtextureinfo>            TextureStreamingData;
	tarray<class uassetuserdata*>                  AssetUserData;

	//public:
	//	class umaterial* GetBaseMaterial()
	//	{
	//		static uobject* function = nullptr;
	//		if (!function)
	//			function = uobject::find_object<uobject*>(crypt(L"Engine.MaterialInterface.GetBaseMaterial"));
	//
	//		struct
	//		{
	//			class umaterial* ReturnValue;
	//		} params;
	//
	//		this->process_event(function, &params);
	//		return params.ReturnValue;
	//	}
	//
	//	void SetForceMipLevelsToBeResident(bool OverrideForceMiplevelsToBeResident, bool bForceMiplevelsToBeResidentValue, float ForceDuration, int32_t CinematicTextureGroups, bool bFastResponse)
	//	{
	//		static uobject* function = nullptr;
	//		if (!function)
	//			function = uobject::find_object<uobject*>(crypt(L"Engine.MaterialInterface.SetForceMipLevelsToBeResident"));
	//
	//		struct
	//		{
	//			bool OverrideForceMiplevelsToBeResident;
	//			bool bForceMiplevelsToBeResidentValue;
	//			float ForceDuration;
	//			int32_t CinematicTextureGroups;
	//			bool bFastResponse;
	//		} params;
	//
	//		params.OverrideForceMiplevelsToBeResident = OverrideForceMiplevelsToBeResident;
	//		params.bForceMiplevelsToBeResidentValue = bForceMiplevelsToBeResidentValue;
	//		params.ForceDuration = ForceDuration;
	//		params.CinematicTextureGroups = CinematicTextureGroups;
	//		params.bFastResponse = bFastResponse;
	//
	//		this->process_event(function, &params);
	//	}
	//
	//	class uphysicalmaterial* GetPhysicalMaterial() const
	//	{
	//		static uobject* function = nullptr;
	//		if (!function)
	//			function = uobject::find_object<uobject*>(crypt(L"Engine.MaterialInterface.GetPhysicalMaterial"));
	//
	//		struct
	//		{
	//			class uphysicalmaterial* ReturnValue;
	//		} params;
	//
	//		const_cast<umaterialinterface*>(this)->process_event(function, &params);
	//		return params.ReturnValue;
	//	}
	//
	//	class uphysicalmaterial* GetPhysicalMaterialFromMap(int32_t Index_0) const
	//	{
	//		static uobject* function = nullptr;
	//		if (!function)
	//			function = uobject::find_object<uobject*>(crypt(L"Engine.MaterialInterface.GetPhysicalMaterialFromMap"));
	//
	//		struct
	//		{
	//			int32_t Index_0;
	//			class uphysicalmaterial* ReturnValue;
	//		} params;
	//
	//		params.Index_0 = Index_0;
	//
	//		const_cast<umaterialinterface*>(this)->process_event(function, &params);
	//		return params.ReturnValue;
	//	}
	//
	//	class uphysicalmaterialmask* GetPhysicalMaterialMask() const
	//	{
	//		static uobject* function = nullptr;
	//		if (!function)
	//			function = uobject::find_object<uobject*>(crypt(L"Engine.MaterialInterface.GetPhysicalMaterialMask"));
	//
	//		struct
	//		{
	//			class uphysicalmaterialmask* ReturnValue;
	//		} params;
	//
	//		const_cast<umaterialinterface*>(this)->process_event(function, &params);
	//		return params.ReturnValue;
	//	}
};

enum class EAnimationMode : uint8_t
{
	AnimationBlueprint = 0,
	AnimationSingleNode = 1,
	AnimationCustomMode = 2,
	EAnimationMode_MAX = 3,
};

class uanimationasset : public uobject
{
public:
	uint8_t pad_30[0x10];
	uint8_t pad_48[0x20];
	uint8_t pad_78[0x4];
	uint32_t skeleton_hash;

public:
	static uclass* static_class()
	{
		return find_object<uclass*>(crypt(L"AnimationAsset"));
	}
};

struct fskeletalmaterial final
{
public:
	umaterialinterface* MaterialInterface;                                 // 0x0000(0x0008)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	fname                                   MaterialSlotName;                                  // 0x0008(0x000C)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};


// Class Engine.CapsuleComponent
// Size: 0x570 (Inherited: 0x570)
struct UCapsuleComponent : public uobject {
public:
	float CapsuleHalfHeight; // 0x568(0x04)
	float CapsuleRadius;
public:
	void set_collision_response_to_channel1(ECollisionChannel channel, ECollisionResponse new_response);
};

struct UActorComponent : uobject {
	char pad_30[0x18]; // 0x30(0x18)
	tarray<struct FName> ComponentTags; // 0x78(0x10)
	struct tarray<struct UAssetUserData*> AssetUserData; // 0x88(0x10)
	char pad_98[0x4]; // 0x98(0x04)
	int32_t UCSSerializationIndex; // 0x9c(0x04)
	char pad_A0_0 : 3; // 0xa0(0x01)
	char bNetAddressable : 1; // 0xa0(0x01)
	char bReplicates : 1; // 0xa0(0x01)
	char pad_A0_5 : 3; // 0xa0(0x01)
	char pad_A1[0x7]; // 0xa1(0x07)
	uint64_t TickTimingsAccumulatedTotal; // 0xa8(0x08)
	uint64_t TickTimingsAccumulatedBP; // 0xb0(0x08)
	uint64_t TickTimingsStart; // 0xb8(0x08)
	char pad_C0[0x1]; // 0xc0(0x01)
	char pad_C1_0 : 3; // 0xc1(0x01)
	char bAutoActivate : 1; // 0xc1(0x01)
	char bIsActive : 1; // 0xc1(0x01)
	char bEditableWhenInherited : 1; // 0xc1(0x01)
	char pad_C1_6 : 1; // 0xc1(0x01)
	char bCanEverAffectNavigation : 1; // 0xc1(0x01)
	char pad_C2_0 : 1; // 0xc2(0x01)
	char bIsEditorOnly : 1; // 0xc2(0x01)
	char pad_C2_2 : 6; // 0xc2(0x01)
	char pad_C3[0x1]; // 0xc3(0x01)
	char pad_C7[0x1]; // 0xc7(0x01)
	tarray<struct FSimpleMemberReference> UCSModifiedProperties; // 0xc8(0x10)
	char pad_D8[0x10]; // 0xd8(0x10)
};

//struct USceneComponentHelpers
//{
//public:
//	static bool AttachTo(uskeletalmeshcomponent* Target, uskeletalmeshcomponent* Parent, fname SocketName,
//		int LocationRule, int RotationRule, int ScaleRule, bool bWeldSimulatedBodies)
//	{
//		static uobject* Function = uobject::find_object1((L"Engine.SceneComponent.K2_AttachToComponent"));
//
//		struct
//		{
//			void* Parent;
//			fname SocketName;
//			int LocationRule;
//			int RotationRule;
//			int ScaleRule;
//			bool bWeldSimulatedBodies;
//			bool ReturnValue;
//		} params;
//
//		params.Parent = Parent;
//		params.SocketName = SocketName;
//		params.LocationRule = LocationRule;
//		params.RotationRule = RotationRule;
//		params.ScaleRule = ScaleRule;
//		params.bWeldSimulatedBodies = bWeldSimulatedBodies;
//
//		if (Function && Target)
//			Function->ProcessEvent(Target, Function, &params);
//
//		return params.ReturnValue;
//	}
//
//	static void SetRelativeRotation(void* Target, const FRotator& Location, bool bSweep = false, bool bTeleport = true)
//	{
//		static uobject* fn = uobject::find_object1((L"Engine.SceneComponent.K2_SetRelativeRotation"));
//
//		struct
//		{
//			FRotator NewLocation;
//			bool bSweep;
//			FHitResult SweepHitResult;  // output param
//			bool bTeleport;
//		} params;
//
//		params.NewLocation = Location;
//		params.bSweep = bSweep;
//		params.bTeleport = bTeleport;
//		memset(&params.SweepHitResult, 0, sizeof(FHitResult)); // safe zero init
//
//		if (Target && fn)
//			fn->ProcessEvent(Target, fn, &params);
//	}
//
//};
class alignas(0x10) USceneComponent : public UActorComponent
{
public:
	uint8_t                                         Pad_A0[0x8];                                       // 0x00A0(0x0008)(Fixing Size After Last Property [ Dumper-7 ])
	//TWeakObjectPtr<class APhysicsVolume>          PhysicsVolume;                                     // 0x00A8(0x0008)(ZeroConstructor, Transient, IsPlainOldData, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	USceneComponent* AttachParent;                                      // 0x00B0(0x0008)(ExportObject, Net, ZeroConstructor, InstancedReference, RepNotify, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	fname                                   AttachSocketName;                                  // 0x00B8(0x0008)(Net, ZeroConstructor, IsPlainOldData, RepNotify, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	uint8_t                                         Pad_C0[0x8];                                       // 0x00C0(0x0008)(Fixing Size After Last Property [ Dumper-7 ])
	tarray<USceneComponent*>                AttachChildren;                                    // 0x00C8(0x0010)(ExportObject, Net, ZeroConstructor, Transient, RepNotify, ContainsInstancedReference, UObjectWrapper, NativeAccessSpecifierPrivate)
	tarray<USceneComponent*>                ClientAttachedChildren;                            // 0x00D8(0x0010)(ExportObject, ZeroConstructor, Transient, ContainsInstancedReference, UObjectWrapper, NativeAccessSpecifierPrivate)
	uint8_t                                         Pad_E8[0x40];                                      // 0x00E8(0x0040)(Fixing Size After Last Property [ Dumper-7 ])
	fvector                                RelativeLocation;                                  // 0x0128(0x0018)(Edit, BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, IsPlainOldData, RepNotify, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	frotator                               RelativeRotation;                                  // 0x0140(0x0018)(Edit, BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, IsPlainOldData, RepNotify, NoDestructor, NativeAccessSpecifierPrivate)
	fvector                                RelativeScale3D;                                   // 0x0158(0x0018)(Edit, BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, IsPlainOldData, RepNotify, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	fvector                                ComponentVelocity;                                 // 0x0170(0x0018)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         bComponentToWorldUpdated : 1;                      // 0x0188(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Transient, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate))
	uint8_t                                         BitPad_188_1 : 1;                                  // 0x0188(0x0001)(Fixing Bit-Field Size Between Bits [ Dumper-7 ])
	uint8_t                                         bAbsoluteLocation : 1;                             // 0x0188(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, Net, RepNotify, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPrivate))
	uint8_t                                         bAbsoluteRotation : 1;                             // 0x0188(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, Net, RepNotify, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPrivate))
	uint8_t                                         bAbsoluteScale : 1;                                // 0x0188(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, Net, RepNotify, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPrivate))
	uint8_t                                         bVisible : 1;                                      // 0x0188(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, Net, RepNotify, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate))
	uint8_t                                         bShouldBeAttached : 1;                             // 0x0188(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Net, Transient, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate))
	uint8_t                                         bShouldSnapLocationWhenAttached : 1;               // 0x0188(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Net, Transient, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate))
	uint8_t                                         bShouldSnapRotationWhenAttached : 1;               // 0x0189(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Net, Transient, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate))
	uint8_t                                         bShouldSnapScaleWhenAttached : 1;                  // 0x0189(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Net, Transient, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate))
	uint8_t                                         bShouldUpdatePhysicsVolume : 1;                    // 0x0189(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPrivate))
	uint8_t                                         bHiddenInGame : 1;                                 // 0x0189(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bUseAttachParentBound : 1;                         // 0x018B(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bComputeFastLocalBounds : 1;                       // 0x018B(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bComputeBoundsOnceForGame : 1;                     // 0x018B(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bComputedBoundsOnceForGame : 1;                    // 0x018B(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bIsNotRenderAttachmentRoot : 1;                    // 0x018B(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         Pad_18C[0x1];                                      // 0x018C(0x0001)(Fixing Size After Last Property [ Dumper-7 ])
	uint8_t                                         Pad_190[0xA0];                                     // 0x0190(0x00A0)(Fixing Struct Size After Last Property [ Dumper-7 ])
};

struct UMaterialInstanceDynamic;

struct UPrimitiveComponent : uobject {
public:
	void set_material(int32_t element_index, uobject* material);

	uobject* create_and_set_material_instance_dynamic_from_material(int32_t element_index, uobject* parent) {
		if (!this || !parent) return nullptr;

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

	UMaterialInstanceDynamic* get_material(int32_t element_index);
	int32_t get_num_materials();
};

enum class EAttachLocation : uint8_t
{
	KeepRelativeOffset = 0,
	KeepWorldPosition = 1,
	SnapToTarget = 2,
	SnapToTargetIncludingScale = 3,
	EAttachLocation_MAX = 4,
};

enum class EAttachmentRule : uint8_t
{
	KeepRelative = 0,
	KeepWorld = 1,
	SnapToTarget = 2,
	EAttachmentRule_MAX = 3,
};

enum class EDetachmentRule : uint8_t
{
	KeepRelative = 0,
	KeepWorld = 1,
	EDetachmentRule_MAX = 2,
};


class uskeletalmeshcomponent : public UPrimitiveComponent
{
public:
	void SetRelativeScale3D(fvector NewScale3D);
	void SetMaterial(int32_t ElementIndex, uobject* Material);
	void SetMaterialByName(fname MaterialSlotName, uobject* Material);
	void set_materials(const tarray<fskeletalmaterial>& in_materials);
	int32_t get_num_materials();
	uobject* create_and_set_material_instance_dynamic_from_material(int32_t element_index, uobject* parent);
	void SetPhysMaterialOverride(uobject* NewPhysMaterial);
	void SetTextureParameterValue(fname ParameterName, uobject* Value);
	void SetVectorParamOnMesh(uskeletalmeshcomponent* mesh, const wchar_t* param_name, const fvector& color);
	void setsketeletalmesh(uskeletalmeshcomponent* newmesh, bool breinitpose);
	void updatemesh();
	void set_animation(uanimationasset* new_anim_to_play);
	void set_animation_mode(EAnimationMode in_animation_mode);
	void SetMesh(uskeletalmeshcomponent* InMesh);
	fvector get_bone_location(int32_t index);	
	void SetOutlineMode(EAresOutlineMode Mode);
	void GetThirdPersonMesh(struct USkeletalMeshComponent*& Mesh); // Function Ability_Melee_Base.Ability_Melee_Base_C.GetThirdPersonMesh // (Public|HasOutParms|BlueprintCallable|BlueprintEvent) // @ game+0x19a85c0

	void set_collision_enabled(ECollisionEnabled new_type);
	void set_collision_response_to_channel(ECollisionChannel channel, ECollisionResponse new_response);
	void set_capsule_size1(float in_radius, float in_half_height, bool update_overlaps);
	void set_bounds_scale(float new_bounds_scale);
	bool AttachTo(uskeletalmeshcomponent* InParent, fname InSocketName, EAttachLocation AttachType, bool bWeldSimulatedBodies);
	int32_t get_num_bones();
	void set_equippable_charm(int new_equippable_charm);
	void set_world_rotation(fvector NewRotation, bool bsweep, bool bteleport);
	fvector get_control_rotationn();
};

enum class EAresItemSlot : uint8_t
{
	Primary = 0,
	Secondary = 1,
	Melee = 2,
	GrenadeAbility = 3,
	Ability1 = 4,
	Ability2 = 5,
	Passive = 6,
	Level = 7,
	Invisible = 8,
	Ultimate = 9,
	Unarmed = 10,
	Armor = 11,
	Backpack = 12,
	Totem = 13,
	PrimaryStorage = 14,
	SecondaryStorage = 15,
	Count = 16,
	Any = 253,
	Invalid = 254,
	EAresItemSlot_MAX = 255,
};

class currentequippable : public uobject
{
public:
	struct type {
		const wchar_t* search = nullptr;
		const char* config = nullptr;
		std::int32_t index = 0;

		const bool is_valid() const noexcept {
			return this->search != nullptr || this->config != nullptr;
		}
	};


	static inline currentequippable::type types[] = {
			{ crypt(L"basepistol").decrypt(), crypt("classic").decrypt()},
			{crypt(L"sawedoffshotgun").decrypt(), crypt("shorty").decrypt() },
			{crypt(L"automaticpistol").decrypt(), crypt("frenzy").decrypt() },
			{crypt(L"lugerpistol").decrypt(), crypt("ghost").decrypt() },
			{crypt(L"revolverpistol").decrypt(), crypt("sheriff").decrypt() },

			{crypt(L"vector").decrypt(), crypt("stinger").decrypt() },
			{crypt(L"submachinegun_mp5").decrypt(), crypt("spectre").decrypt() },

			{crypt(L"pumpshotgun").decrypt(), crypt("bucky").decrypt() },
			{crypt(L"automaticshotgun").decrypt(), crypt("judge").decrypt() },

			{crypt(L"assaultrifle_burst").decrypt(), crypt("bulldog").decrypt() },
			{crypt(L"dmr").decrypt(), "guardian" },
			{crypt(L"assaultrifle_acr").decrypt(), crypt("phantom").decrypt() },
			{crypt(L"assaultrifle_ak").decrypt(), crypt("vandal").decrypt() },

			{crypt(L"leversniperrifle").decrypt(), crypt("marshal").decrypt() },
			{crypt(L"boltsniper").decrypt(), crypt("operator").decrypt() },

			{crypt(L"lightmachinegun").decrypt(), crypt("ares").decrypt() },
			{crypt(L"heavymachinegun").decrypt(), crypt("odin").decrypt() },

			{crypt(L"ability_melee_base").decrypt(), crypt("knife").decrypt() },

			{crypt(L"gun_sprinter_x_heavylightninggun_production").decrypt(), crypt("neon_x").decrypt() },
			{crypt(L"ability_wushu_x_dagger_production").decrypt(), crypt("jett_dagger").decrypt() }
	};

	currentequippable::type get_type() {
		const fstring& name = system::get_object_name(this);

		for (std::int32_t index = 0; index < sizeof(currentequippable::types) / sizeof(currentequippable::type); index++) {
			currentequippable::type type = currentequippable::types[index];

			if (type.index == 0)
				type.index = index;

			if (system::starts_with(name.c_str(), type.search))
				return { type.search, type.config, type.index };
		}

		return {};
	}

	equippable_skin_data_asset* get_skin_data_asset();

	ftext GetSkinNameText();

	EAresItemSlot GetItemSlot();

	uskeletalmeshcomponent* GetMesh3P();
	

	fvector GetSocketLocation_wp(fname InSocketName);

	void UpdateMaterial(int32_t Index_0, uobject* Material);

	uammocomponent* GetAmmoComponent();

	int32_t GetAmmo();

	int32_t GetMaxAmmo();

	const ftransform get_muzzle_transform();

	uskeletalmeshcomponent* GetMesh1P();

	uobject* get_item_icon();
};
class uinventory : public uobject
{
public:
	
	currentequippable* get_current_equippable();
};


class arsenal_view_model : public uobject
{
public:
	tarray<equippable_inventory_model*> get_gun_models();
};

class UEquippableAttachmentInventoryModel : public uobject
{
public:
	class UEquippableAttachmentDataAsset* EquippableAttachmentDataAsset;                     // 0x0108(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class UEquippableInventoryModel* ParentEquippable;                                  // 0x0110(0x0008)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

class UEquippableCharmInstanceInventoryModel : public uobject
{
public:
	class UEquippableDataAsset* AssignedEquippable;                                // 0x0138(0x0008)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class UEquippableCharmDataAsset* EquippableCharmDataAsset;                          // 0x0140(0x0008)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class UEquippableCharmLevelDataAsset* EquippableCharmLevelDataAsset;                     // 0x0148(0x0008)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

class ULevelBorderDataAsset : public uobject
{
public:
	int32_t                                         StartingLevel;                                     // 0x0080(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_84[0x4];                                       // 0x0084(0x0004)(Fixing Struct Size After Last Property [ Dumper-7 ])
};

class UPlayerCardDataAsset : public uobject
{
};

class USprayDataAsset : public uobject
{
};

class UPlayerTitleDataAsset : public uobject
{
public:
	class ftext                                   TitleText;                                         // 0x0080(0x0018)(Edit, BlueprintVisible, BlueprintReadOnly, DisableEditOnInstance, NativeAccessSpecifierPublic)
	class ftext                                   TitleTextAllCaps;                                  // 0x0098(0x0018)(Edit, DisableEditOnInstance, NativeAccessSpecifierPublic)
};

class USprayEquipSlotDataAsset : public uobject
{
public:
	int32_t                                         SprayCategoriesAllowed;                            // 0x0080(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32_t                                         SlotOrder;                                         // 0x0084(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

class charm_data_asset : public uobject {
public:
	uobject* get_charm_level(int level_number) {
		uobject* function = uobject::find_object<uobject*>(crypt(L"ShooterGame.EquippableCharmDataAsset.GetCharmLevel"));

		struct {
			int level_number;
			uobject* return_value;
		} params = { level_number };

		this->process_event(function, &params);

		return params.return_value;
	}
};


struct FConnectToServerDetails final
{
public:
	fstring                                 Host;                                              // 0x0000(0x0010)(BlueprintVisible, ZeroConstructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32_t                                         Port;                                              // 0x0010(0x0004)(BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_14[0x4];                                       // 0x0014(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	fstring                                 DisplayName;                                       // 0x0018(0x0010)(BlueprintVisible, ZeroConstructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	fstring                                 Subject;                                           // 0x0028(0x0010)(BlueprintVisible, ZeroConstructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	fstring                                 Team;                                              // 0x0038(0x0010)(BlueprintVisible, ZeroConstructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	fstring                                 Map;                                               // 0x0048(0x0010)(BlueprintVisible, ZeroConstructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

class arsenal_view_controller : public uobject
{
public:
	arsenal_view_model* get_view_model();
	void EquipAttachment(UEquippableAttachmentInventoryModel* AttachmentModel);
	void EquipBuddy(equippable_skin_data_asset* Equippable, UEquippableCharmInstanceInventoryModel* CharmInstance);
	void EquipLevelBorder(ULevelBorderDataAsset* LevelBorder);
	void EquipPlayerCard(UPlayerCardDataAsset* PlayerCard);
	void EquipPlayerTitle(UPlayerTitleDataAsset* PlayerTitle);
	void EquipSkin(equippable_skin_inventory_model* Value);
	void EquipSpray(USprayEquipSlotDataAsset* SprayEquipSlot, USprayDataAsset* Spray);
	arsenal_view_controller* GetCharmLevel(int32_t LevelNumber);
};

class inventorymanager : public uobject
{
public:
	currentequippable* get_current_weapon();
};

class ares_client_game_instace : public uobject
{
public:
	arsenal_view_controller* get_aresnal_view_controller();
	inventorymanager* get_inventory_manager();
};

class ares_instance : public uobject
{
public:
	static ares_client_game_instace* get_ares_client_game_instance(uobject* world_context);
	void ConnectToServer(FConnectToServerDetails& Details);
	void DisconnectFromServer();
	bool should_allow_leave_match();
	void StartPatchDownload();
	void TriggerVanguardBanNotification(const fstring& Subject);
};


class aplayercameramanager : public uobject
{
public:
	fvector get_camera_location();
	fvector get_camera_rotation();
	frotator get_camera_rotation_fr();

	void SetAspectRatio(float InAspectRatio);
	
};

struct ReticlePair
{
	unsigned short TableValue;
	unsigned short TableOffset;
};

class umaterial_instance : public uobject
{
public:
	void set_vector_parameter_value(fname ParameterName, flinearcolor Value);
	void set_scalar_parameter_value(fname parameter_name, float value);
};

class umaterialinstancedynamic : public uobject
{
public:
	/*void CopyInterpParameters(umaterialinstance* Source);
	void CopyParameterOverrides(umaterialinstance* MaterialInstance);
	void FlattenMaterialInstanceParameters();
	void K2_CopyMaterialInstanceParameters(umaterialinterface* Source, bool bQuickParametersOnly);
	float K2_GetScalarParameterValue(fname ParameterName);
	float K2_GetScalarParameterValueByInfo(const fmaterialparameterinfo& ParameterInfo);
	utexture* K2_GetTextureParameterValue(fname ParameterName);
	utexture* K2_GetTextureParameterValueByInfo(const fmaterialparameterinfo& ParameterInfo);
	flinearcolor K2_GetVectorParameterValue(fname ParameterName);
	flinearcolor K2_GetVectorParameterValueByInfo(const fmaterialparameterinfo& ParameterInfo);
	void K2_InterpolateMaterialInstanceParams(umaterialinstance* SourceA, umaterialinstance* SourceB, float Alpha);
	void SetScalarParameterValue(fname ParameterName, float Value);
	void SetScalarParameterValueByInfo(const fmaterialparameterinfo& ParameterInfo, float Value);
	void SetTextureParameterValue(fname ParameterName, utexture* Value);
	void SetTextureParameterValueByInfo(const fmaterialparameterinfo& ParameterInfo, utexture* Value);
	void SetVectorParameterValue(fname ParameterName, const flinearcolor& Value);
	void SetVectorParameterValueByInfo(const fmaterialparameterinfo& ParameterInfo, const flinearcolor& Value);*/

	static uobject* StaticClass()
	{
		return uobject::find_object<uobject*>(L"MaterialInstanceDynamic");
	}

	// Function implementations
	void CopyInterpParameters(umaterial_instance* Source)
	{
		static uobject* function = nullptr;
		if (!function)
			function = uobject::find_object<uobject*>(L"Engine.MaterialInstanceDynamic.CopyInterpParameters");

		struct
		{
			umaterial_instance* Source;
		} params;

		params.Source = Source;

		this->process_event(function, &params);
	}

	void CopyParameterOverrides(umaterial_instance* MaterialInstance)
	{
		static uobject* function = nullptr;
		if (!function)
			function = uobject::find_object<uobject*>(L"Engine.MaterialInstanceDynamic.CopyParameterOverrides");

		struct
		{
			umaterial_instance* MaterialInstance;
		} params;

		params.MaterialInstance = MaterialInstance;

		this->process_event(function, &params);
	}

	void FlattenMaterialInstanceParameters()
	{
		static uobject* function = nullptr;
		if (!function)
			function = uobject::find_object<uobject*>(L"Engine.MaterialInstanceDynamic.FlattenMaterialInstanceParameters");

		this->process_event(function, nullptr);
	}

	void K2_CopyMaterialInstanceParameters(umaterialinterface* Source, bool bQuickParametersOnly)
	{
		static uobject* function = nullptr;
		if (!function)
			function = uobject::find_object<uobject*>(L"Engine.MaterialInstanceDynamic.K2_CopyMaterialInstanceParameters");

		struct
		{
			umaterialinterface* Source;
			bool bQuickParametersOnly;
		} params;

		params.Source = Source;
		params.bQuickParametersOnly = bQuickParametersOnly;

		this->process_event(function, &params);
	}

	float K2_GetScalarParameterValue(fname ParameterName)
	{
		static uobject* function = nullptr;
		if (!function)
			function = uobject::find_object<uobject*>(L"Engine.MaterialInstanceDynamic.K2_GetScalarParameterValue");

		struct
		{
			fname ParameterName;
			float ReturnValue;
		} params;

		params.ParameterName = ParameterName;

		this->process_event(function, &params);

		return params.ReturnValue;
	}

	void SetVectorParameterValue(fname ParameterName, const flinearcolor& Value)
	{
		static uobject* function = nullptr;
		if (!function)
			function = uobject::find_object<uobject*>(L"Engine.MaterialInstanceDynamic.SetVectorParameterValue");

		struct
		{
			fname ParameterName;
			flinearcolor Value;
		} params;

		params.ParameterName = ParameterName;
		params.Value = Value;

		this->process_event(function, &params);
	}

	void SetScalarParameterValue(fname ParameterName, float Value)
	{
		static uobject* function = nullptr;
		if (!function)
			function = uobject::find_object<uobject*>(L"Engine.MaterialInstanceDynamic.SetScalarParameterValue");

		struct
		{
			fname ParameterName;
			float Value;
		} params;

		params.ParameterName = ParameterName;
		params.Value = Value;

		this->process_event(function, &params);
	}

	umaterialinstancedynamic* Create(uobject* Parent, uobject* Owner)
	{
		static uobject* function;
		if (!function)
			function = uobject::find_object<uobject*>(crypt(L"Engine.MaterialInstanceDynamic.Create"));

		struct
		{
			uobject* Parent;
			uobject* Owner;
			umaterialinstancedynamic* ReturnValue;
		} params;

		params.Parent = Parent;
		params.Owner = Owner;

		this->process_event(function, &params);

		return params.ReturnValue;
	}

};

struct fappliedmaterialhandle final
{
public:
	uint8_t                                         Pad_0[0x20];                                       // 0x0000(0x0020)(Fixing Size After Last Property [ Dumper-7 ])
	class UMaterialInterface* Material;                                          // 0x0020(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_28[0x8];                                       // 0x0028(0x0008)(Fixing Struct Size After Last Property [ Dumper-7 ])
};

enum class EMeshPlayerView : uint8_t
{
	FirstPerson = 0,
	
	son = 1,
	EMeshPlayerView_MAX = 2,
};

enum class EMaterialPriority : uint8_t
{
	Normal = 0,
	High = 1,
	EMaterialPriority_MAX = 2,
};

class umeshmaterialmanagercomponent : public uobject
{
public:
	uskeletalmeshcomponent* CharacterMesh3P;
	uskeletalmeshcomponent* CharacterMesh1P;

	fappliedmaterialhandle SetAllMaterials(EMeshPlayerView MeshPlayerView, umaterialinterface* Material, EMaterialPriority Priority);
	fappliedmaterialhandle SetMaterial(EMeshPlayerView MeshPlayerView, int32_t ElementIndex, umaterialinterface* Material, EMaterialPriority Priority);
};

class umeshcomponent : public uobject
{
public:
	bool bOverrideDisableOcclusionQuery;
	flinearcolor OverlayColor;
	bool bEnableMaterialParameterCaching;

	static uclass* StaticClass()
	{
		return uobject::find_object<uclass*>(L"MeshComponent");
	}

	// Function implementations
	void EmptyOverrideMaterials()
	{
		static uobject* function = nullptr;
		if (!function)
			function = uobject::find_object<uobject*>(L"Engine.MeshComponent.EmptyOverrideMaterials");

		this->process_event(function, nullptr);
	}

	void PrestreamTextures(float Seconds, bool bPrioritizeCharacterTextures, int32_t CinematicTextureGroups)
	{
		static uobject* function = nullptr;
		if (!function)
			function = uobject::find_object<uobject*>(L"Engine.MeshComponent.PrestreamTextures");

		struct
		{
			float Seconds;
			bool bPrioritizeCharacterTextures;
			int32_t CinematicTextureGroups;
		} params;

		params.Seconds = Seconds;
		params.bPrioritizeCharacterTextures = bPrioritizeCharacterTextures;
		params.CinematicTextureGroups = CinematicTextureGroups;

		this->process_event(function, &params);
	}

	void SetScalarParameterValueOnMaterials(const fname& ParameterName, float ParameterValue)
	{
		static uobject* function = nullptr;
		if (!function)
			function = uobject::find_object<uobject*>(L"Engine.MeshComponent.SetScalarParameterValueOnMaterials");

		struct
		{
			fname ParameterName;
			float ParameterValue;
		} params;

		params.ParameterName = ParameterName;
		params.ParameterValue = ParameterValue;

		this->process_event(function, &params);
	}

	void SetVectorParameterValueOnMaterials(const fname& ParameterName, const fvector& ParameterValue)
	{
		static uobject* function = nullptr;
		if (!function)
			function = uobject::find_object<uobject*>(L"Engine.MeshComponent.SetVectorParameterValueOnMaterials");

		struct
		{
			fname ParameterName;
			fvector ParameterValue;
		} params;

		params.ParameterName = ParameterName;
		params.ParameterValue = ParameterValue;

		this->process_event(function, &params);
	}

	int32_t GetMaterialIndex(const fname& MaterialSlotName) const
	{
		static uobject* function = nullptr;
		if (!function)
			function = uobject::find_object<uobject*>(L"Engine.MeshComponent.GetMaterialIndex");

		struct
		{
			fname MaterialSlotName;
			int32_t ReturnValue;
		} params;

		params.MaterialSlotName = MaterialSlotName;

		const_cast<umeshcomponent*>(this)->process_event(function, &params);

		return params.ReturnValue;
	}

	bool IsMaterialSlotNameValid(const fname& MaterialSlotName) const
	{
		static uobject* function = nullptr;
		if (!function)
			function = uobject::find_object<uobject*>(L"Engine.MeshComponent.IsMaterialSlotNameValid");

		struct
		{
			fname MaterialSlotName;
			bool ReturnValue;
		} params;

		params.MaterialSlotName = MaterialSlotName;

		const_cast<umeshcomponent*>(this)->process_event(function, &params);

		return params.ReturnValue;
	}
};

class ufresnelcomponent : public uobject
{
public:
	bool bDirty;
	std::set<umaterialinstancedynamic*> Materials1P;
	std::set<umaterialinstancedynamic*> Materials3P;
	bool UseColorBlindPreferences;
	float FresnelIntensity;
	float FresnelOffset;
	float OriginalFresnelIntensity;
	float OriginalFresnelOffset;

	void HandleMeshMaterialChanged(umeshmaterialmanagercomponent* MeshMaterialManager, umeshcomponent* Mesh, int32_t ElementIndex, umaterialinterface* Material, EMeshPlayerView MeshPlayerView, umaterialinterface* OldMaterial);

	void SetIntensity(float NewIntensity);
	void SetMaterials1P(const std::set<umaterialinstancedynamic*>& FresnelMaterials);
	void SetMaterials3P(const std::set<umaterialinstancedynamic*>& FresnelMaterials);
	void SetOffset(float NewOffset);

	static uclass* StaticClass()
	{
		return uobject::find_object<uclass*>(L"FresnelComponent");
	}
};

class aplayerstate : public uobject
{
public:

	int32_t                                         player_id;
	uint16_t                                        ping;
	uint8_t                                         pad_3be[0x1];
	uint8_t                                         should_update_replicated_ping : 1;
	uint8_t                                         is_spectator : 1;
	uint8_t                                         only_spectator : 1;
	uint8_t                                         is_a_bot : 1;
	uint8_t                                         bit_pad_3bf_4 : 1;
	uint8_t                                         is_inactive : 1;
	uint8_t                                         from_previous_level : 1;
	int32_t                                         start_time;
	uint8_t                                         pad_3c4[0x4];
	uint8_t                                         pad_3d0[0x8];
	fstring                                         saved_network_address;
	uint8_t                                         pad_410[0x10];
	uint8_t                                         pad_428[0x78];
	fstring                                         player_name_private;
	uint8_t                                         pad_4b0[0x10];
};

class UMaterial : public uobject
{
public:

};

enum class e_blend_mode : uint8_t
{
	opaque = 0,
	masked = 1,
	translucent = 2,
	additive = 3,
	modulate = 4,
	alpha_composite = 5,
	max = 6,
};

struct UMaterialInstance : uobject
{
public:
	e_blend_mode GetBlendMode();

};

struct UMaterialInstanceDynamic : UMaterialInstance {
public:
	e_blend_mode get_blend_mode();
	void set_vector_parameter_value2(fname parameter_name, flinearcolor value);
	void set_scalar_parameter_value(fname parameter_name, double value);
	void set_scalar_parameter_value1(fname parameter_name, double value);
	//void set_scalar_parameter_value(fname parameter_name, float value);
	void set_vector_parameter_value1(fname parameter_name, flinearcolor value);
	//void set_scalar_parameter_value(fname parameter_name, float value);
	void set_texture_parameter_value(fname parameter_name, uobject* texture);
};



enum class EMovementMode : uint8_t {
	MOVE_None = 0,
	MOVE_Walking = 1,
	MOVE_NavWalking = 2,
	MOVE_Falling = 3,
	MOVE_Swimming = 4,
	MOVE_Flying = 5,
	MOVE_Custom = 6,
	MOVE_MAX = 7
};

class UPawnMovementComponent : public uobject {
public:
	void SetMaxWalkSpeed(float NewSpeed) {
		static uobject* function = nullptr;
		if (!function)
			function = uobject::find_object<uobject*>(L"Engine.CharacterMovementComponent.SetMaxWalkSpeed");

		struct {
			float NewSpeed;
		} params = { NewSpeed };

		this->process_event(function, &params);
	}

	void SetJumpZVelocity(float NewVelocity) {
		static uobject* function = nullptr;
		if (!function)
			function = uobject::find_object<uobject*>(L"Engine.CharacterMovementComponent.SetJumpZVelocity");

		struct {
			float NewVelocity;
		} params = { NewVelocity };

		this->process_event(function, &params);
	}

	float GetMaxWalkSpeed() {
		static uobject* function = nullptr;
		if (!function)
			function = uobject::find_object<uobject*>(L"Engine.CharacterMovementComponent.GetMaxWalkSpeed");

		struct {
			float ReturnValue;
		} params;

		this->process_event(function, &params);
		return params.ReturnValue;
	}

	float GetJumpZVelocity() {
		static uobject* function = nullptr;
		if (!function)
			function = uobject::find_object<uobject*>(L"Engine.CharacterMovementComponent.GetJumpZVelocity");

		struct {
			float ReturnValue;
		} params;

		this->process_event(function, &params);
		return params.ReturnValue;
	}
};


enum class ESpawnActorCollisionHandlingMethod : uint8_t
{
	Undefined = 0,
	AlwaysSpawn = 1,
	AdjustIfPossibleButAlwaysSpawn = 2,
	AdjustIfPossibleButDontSpawnIfColliding = 3,
	DontSpawnIfColliding = 4,
	ESpawnActorCollisionHandlingMethod_MAX = 5,
};

// Spawn parameters structure
// Spawn parameters structure
struct FActorSpawnParameters {
	uobject* Owner = nullptr;  // Use generic uobject* instead of specific type
	ESpawnActorCollisionHandlingMethod SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
};


struct UCharacterMovementComponent : UPawnMovementComponent {
public:
	char pad_178[0x10];
	//ACharacter* CharacterOwner;
	float GravityScale;
	float MaxStepHeight;
	bool bBackOffDuringStep;
	bool bStepUpWhenMovingVertically;
	char pad_19A[0x2];
	float JumpZVelocity;
	float JumpOffJumpZFactor;
	float JumpStepUpUnits;
	char pad_1A8[0x10];
	float WalkableFloorAngle;
	float WalkableFloorZ;
	EMovementMode MovementMode;
	char CustomMovementMode;
	//ENetworkSmoothingMode NetworkSmoothingMode;
	char pad_1C3[0x1];
	float GroundFriction;
	char pad_1C8[0x24];
	float MaxWalkSpeed;
	float MaxWalkSpeedCrouched;
	float MaxSwimSpeed;
	float MaxFlySpeed;
	float MaxCustomMovementSpeed;
	float MaxAcceleration;
	float MinAnalogWalkSpeed;
	float BrakingFrictionFactor;
	float BrakingFriction;
	float BrakingSubStepTime;
	float BrakingDecelerationWalking;
	float BrakingDecelerationFalling;
	float BrakingDecelerationSwimming;
	float BrakingDecelerationFlying;
	float AirControl;
	float AirControlBoostMultiplier;
	float AirControlBoostVelocityThreshold;
	float FallingLateralFriction;
	float CrouchedHalfHeight;
	float Buoyancy;
	float PerchRadiusThreshold;
	float PerchAdditionalHeight;

	//acknowledgedpawn* PawnOwner;
	frotator RotationRate;
	uint8_t bUseSeparateBrakingFriction : 1;
	uint8_t bApplyGravityWhileJumping : 1;
	uint8_t bUseControllerDesiredRotation : 1;
	uint8_t bOrientRotationToMovement : 1;
	uint8_t bSweepWhileNavWalking : 1;
	uint8_t pad_flags_250 : 3;
	uint8_t bEnableScopedMovementUpdates : 1;
	uint8_t bEnableServerDualMoveScopedMovementUpdates : 1;
	uint8_t bForceMaxAccel : 1;
	uint8_t bRunPhysicsWithNoController : 1;
	uint8_t bForceNextFloorCheck : 1;
	uint8_t bShrinkProxyCapsule : 1;
	uint8_t bCanWalkOffLedges : 1;
	uint8_t bCanWalkOffLedgesWhenCrouching : 1;
	char pad_252[0x6];
	float MaxOutOfWaterStepHeight;
	float OutofWaterZ;
	float Mass;
	float StandingDownwardForceScale;
	float InitialPushForceFactor;
	float PushForceFactor;
	float PushForcePointZOffsetFactor;
	float TouchForceFactor;
	float MinTouchForce;
	float MaxTouchForce;
	float RepulsionForce;
	fvector Acceleration;
	char pad_298[0x8];
	//FQuat LastUpdateRotation;
	fvector LastUpdateLocation;
	fvector LastUpdateVelocity;
	float ServerLastTransformUpdateTimeStamp;
	float ServerLastClientGoodMoveAckTime;
	float ServerLastClientAdjustmentTime;
	fvector PendingImpulseToApply;
	fvector PendingForceToApply;
	float AnalogInputModifier;
	char pad_2F0[0xc];
	float MaxSimulationTimeStep;
	int32_t MaxSimulationIterations;
	int32_t MaxJumpApexAttemptsPerSimulation;
	float MaxDepenetrationWithGeometry;
	float MaxDepenetrationWithGeometryAsProxy;
	float MaxDepenetrationWithPawn;
	float MaxDepenetrationWithPawnAsProxy;
	float NetworkSimulatedSmoothLocationTime;
	float NetworkSimulatedSmoothRotationTime;
	float ListenServerNetworkSimulatedSmoothLocationTime;
	float ListenServerNetworkSimulatedSmoothRotationTime;
	float NetProxyShrinkRadius;
	float NetProxyShrinkHalfHeight;
	float NetworkMaxSmoothUpdateDistance;
	float NetworkNoSmoothUpdateDistance;
	float NetworkMinTimeBetweenClientAckGoodMoves;
	float NetworkMinTimeBetweenClientAdjustments;
	float NetworkMinTimeBetweenClientAdjustmentsLargeCorrection;
	float NetworkLargeClientCorrectionDistance;
	float LedgeCheckThreshold;
	float JumpOutOfWaterPitch;

	//FFindFloorResult CurrentFloor;
	EMovementMode DefaultLandMovementMode;
	EMovementMode DefaultWaterMovementMode;
	EMovementMode GroundMovementMode;
	uint8_t bMaintainHorizontalGroundVelocity : 1;
	uint8_t bImpartBaseVelocityX : 1;
	uint8_t bImpartBaseVelocityY : 1;
	uint8_t bImpartBaseVelocityZ : 1;
	uint8_t bImpartBaseAngularVelocity : 1;
	uint8_t bJustTeleported : 1;
	uint8_t bIsSimGravityDisabled : 1;
	char pad_rest[0x460];
	UPrimitiveComponent* get_movement_base();
};

// Enum Engine.EAutoPossessAI
// NumValues: 0x0005
enum class EAutoPossessAI : uint8_t
{
	Disabled = 0,
	PlacedInWorld = 1,
	Spawned = 2,
	PlacedInWorldOrSpawned = 3,
	EAutoPossessAI_MAX = 4,
};

// Enum Engine.EAutoReceiveInput
// NumValues: 0x000A
enum class EAutoReceiveInput : uint8_t
{
	Disabled = 0,
	Player0 = 1,
	Player1 = 2,
	Player2 = 3,
	Player3 = 4,
	Player4 = 5,
	Player5 = 6,
	Player6 = 7,
	Player7 = 8,
	EAutoReceiveInput_MAX = 9,
};

class AAIController : public uobject {
public:
	void Destroy() {
		static uobject* function = nullptr;
		if (!function)
			function = uobject::find_object<uobject*>(L"Engine.Actor.Destroy");
		this->process_event(function, nullptr);
	}

	void UnPossess() {  // Removed static
		static uobject* function = nullptr;
		if (!function)
			function = uobject::find_object<uobject*>(L"Engine.Controller.UnPossess");
		this->process_event(function, nullptr);
	}

	void Possess(uobject* InPawn) {  // Removed static, changed parameter type
		static uobject* function = nullptr;
		if (!function)
			function = uobject::find_object<uobject*>(L"Engine.Controller.Possess");

		struct {
			uobject* InPawn;
		} params = { InPawn };

		this->process_event(function, &params);
	}
};


class acknowledgedpawn : public uobject
{
public:
	uint8_t                                         Pad_3B8[0x8];                                      // 0x03B8(0x0008)(Fixing Size After Last Property [ Dumper-7 ])
	uint8_t                                         bUseControllerRotationPitch : 1;                   // 0x03C0(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bUseControllerRotationYaw : 1;                     // 0x03C0(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bUseControllerRotationRoll : 1;                    // 0x03C0(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bCanAffectNavigationGeneration : 1;                // 0x03C0(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         Pad_3C1[0x3];                                      // 0x03C1(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         BaseEyeHeight;                                     // 0x03C4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	EAutoReceiveInput                             AutoPossessPlayer;                                 // 0x03C8(0x0001)(Edit, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	EAutoPossessAI                                AutoPossessAI;                                     // 0x03C9(0x0001)(Edit, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint16_t                                        RemoteViewPitch;                                   // 0x03CA(0x0002)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_3CC[0x4];                                      // 0x03CC(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	class APlayerState* PlayerState;                                       // 0x03D8(0x0008)(BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, IsPlainOldData, RepNotify, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	uint8_t                                         Pad_3E0[0x8];                                      // 0x03E0(0x0008)(Fixing Size After Last Property [ Dumper-7 ])
	class AController* LastHitBy;                                         // 0x03E8(0x0008)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, Transient, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class AController* Controller;                                        // 0x03F0(0x0008)(Net, ZeroConstructor, IsPlainOldData, RepNotify, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_3F8[0x4];                                      // 0x03F8(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	fvector                                ControlInputVector;                                // 0x03FC(0x000C)(ZeroConstructor, Transient, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
	fvector                                LastControlInputVector;                            // 0x0408(0x000C)(ZeroConstructor, Transient, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
	uint8_t                                         Pad_414[0x4];
public:
	fvector get_controlrotation();
	UPrimitiveComponent* GetOverlayMesh1P2();
	UPrimitiveComponent* GetMesh1P2();

	fvector k2_get_actor_location1();
	frotator k2_get_actor_rotation1();

	void flush_net_dormancy1();
	void force_net_update1();

	UPawnMovementComponent* get_movement_component();
	UPawnMovementComponent* GetMovementComponent();
};


class gameobject : public uobject
{
public:
};

//enum class TextureGroup : uint8_t {
//	TEXTUREGROUP_World = 0,
//	TEXTUREGROUP_WorldNormalMap = 1,
//	TEXTUREGROUP_WorldSpecular = 2,
//	TEXTUREGROUP_Character = 3,
//	TEXTUREGROUP_CharacterNormalMap = 4,
//	TEXTUREGROUP_CharacterSpecular = 5,
//	TEXTUREGROUP_Weapon = 6,
//	TEXTUREGROUP_WeaponNormalMap = 7,
//	TEXTUREGROUP_WeaponSpecular = 8,
//	TEXTUREGROUP_Vehicle = 9,
//	TEXTUREGROUP_VehicleNormalMap = 10,
//	TEXTUREGROUP_VehicleSpecular = 11,
//	TEXTUREGROUP_Cinematic = 12,
//	TEXTUREGROUP_Effects = 13,
//	TEXTUREGROUP_EffectsNotFiltered = 14,
//	TEXTUREGROUP_Skybox = 15,
//	TEXTUREGROUP_UI = 16,
//	TEXTUREGROUP_Lightmap = 17,
//	TEXTUREGROUP_RenderTarget = 18,
//	TEXTUREGROUP_MobileFlattened = 19,
//	TEXTUREGROUP_ProcBuilding_Face = 20,
//	TEXTUREGROUP_ProcBuilding_LightMap = 21,
//	TEXTUREGROUP_Shadowmap = 22,
//	TEXTUREGROUP_ColorLookupTable = 23,
//	TEXTUREGROUP_Terrain_Heightmap = 24,
//	TEXTUREGROUP_Terrain_Weightmap = 25,
//	TEXTUREGROUP_Bokeh = 26,
//	TEXTUREGROUP_IESLightProfile = 27,
//	TEXTUREGROUP_Pixels2D = 28,
//	TEXTUREGROUP_HierarchicalLOD = 29,
//	TEXTUREGROUP_Impostor = 30,
//	TEXTUREGROUP_ImpostorNormalDepth = 31,
//	TEXTUREGROUP_8BitData = 32,
//	TEXTUREGROUP_16BitData = 33,
//	TEXTUREGROUP_Project01 = 34,
//	TEXTUREGROUP_Project02 = 35,
//	TEXTUREGROUP_Project03 = 36,
//	TEXTUREGROUP_Project04 = 37,
//	TEXTUREGROUP_Project05 = 38,
//	TEXTUREGROUP_Project06 = 39,
//	TEXTUREGROUP_Project07 = 40,
//	TEXTUREGROUP_Project08 = 41,
//	TEXTUREGROUP_Project09 = 42,
//	TEXTUREGROUP_Project10 = 43,
//	TEXTUREGROUP_Project11 = 44,
//	TEXTUREGROUP_Project12 = 45,
//	TEXTUREGROUP_Project13 = 46,
//	TEXTUREGROUP_Project14 = 47,
//	TEXTUREGROUP_Project15 = 48,
//	TEXTUREGROUP_MAX = 49
//};


enum class EAresEquippableState : uint8_t
{
	Unknown = 0,
	Idle = 1,
	Equipping = 2,
	Inspecting = 3,
	Attacking = 4,
	Firing = 5,
	Reloading = 6,
	ADS_Idle = 7,
	ADS_Firing = 8,
	Count = 9,
	EAresEquippableState_MAX = 10,
};

struct FEffectID
{
	fname   SourceID;   // or const char*
	int64_t EffectID;
	bool    bLocalEffect;
	bool    bTransient;
	UINT8   Pad[6];
};


struct FActiveBlind {
	uint32_t      BlindId;              // 0x0C
	FEffectID     BlindEffectID;        // 0x10
	float         InitialDuration;      // 0x30
	float         StartNetMovementTime; // 0x34
	uclass* BlindConfig;          // 0x38
	void* CausingActor;         // 0x40
};

class pregame_view_model : public uobject {
public:
	bool is_local_player_locked_in()
	{
		uobject* function = uobject::find_object<uobject*>(crypt(L"ShooterGame.PregameViewModel.IsLocalPlayerLockedIn"));

		if (function == nullptr)
			return false;

		struct
		{
			bool return_value;
		} params;

		this->process_event(function, &params);

		return params.return_value;
	}
};

class pregame_view_controller : public uobject {
public:
	pregame_view_model* get_pregame_view_model() {
		uobject* function = uobject::find_object<uobject*>(crypt(L"ShooterGame.PregameViewController.GetViewModel"));

		if (function == nullptr)
			return nullptr;

		struct
		{
			pregame_view_model* return_value;
		} params;

		this->process_event(function, &params);

		return params.return_value;
	}

	void lock_character(uobject* agent)
	{
		uobject* function = uobject::find_object<uobject*>(crypt(L"ShooterGame.PregameViewController.LockCharacter"));

		if (function == nullptr)
			return;

		struct
		{
			uobject* agent;
		} params = { agent };

		this->process_event(function, &params);
	}

	void select_character(uobject* agent)
	{
		uobject* function = uobject::find_object<uobject*>(crypt(L"ShooterGame.PregameViewController.SelectCharacter"));

		if (function == nullptr)
			return;

		struct
		{
			uobject* agent;
		} params = { agent };

		this->process_event(function, &params);
	}
	void UnlockAllCharacters();
	void CheatUnlockAllCharacters();
	void PregameExit();
	void PregameStart();
	void SetConfigurationValue(const fstring& Name, const fstring& Value);
	void ShowUI(bool Show);
	void PickSide(const fname& Side);
	void OverrideCharacter(const fstring& CharacterPath);
	void SetCharacter(const uobject* Character);
	void UpdateModel();
};

enum class EAresMovementType : uint8_t
{
	Walking = 0,
	Running = 1,
	Jumping = 2,
	Crouching = 3,
	OnAscender = 4,
	Flying = 5,
	Count = 6,
	Invalid = 254,
	EAresMovementType_MAX = 255,
};

struct FMMRPlayer
{
	int32_t Rank;
	float MMR;
};

struct FMMRMatchInfo
{
	int32_t Rank;
	float MMR;
};

template<class T>
class TWeakObjectPtr {
};

//class UCharacterDataAsset : public uobject {
//public:
//	wchar_t* CharacterCodeName;
//	wchar_t* CharacterFullName;
//	wchar_t* CharacterRole;
//	wchar_t* CharacterOrigin;
//	int32_t CharacterDifficulty;
//
//	wchar_t* AbilityQName;
//	wchar_t* AbilityEName;
//	wchar_t* AbilityCName;
//	wchar_t* AbilityXName;
//
//	uobject* CharacterIcon;
//	uobject* CharacterPortrait;
//
//	float BaseMovementSpeed;
//	float BaseHealth;
//	float BaseArmor;
//};
//
//class UAresInventory : public uobject {
//public:
//	tarray<uobject*> Weapons;
//	tarray<uobject*> Abilities;
//	int32_t Credits;
//	int32_t ArmorValue;
//	bool bHasHeavyArmor;
//	bool bHasSpike;
//};
class ugameviewportclient : public uobject {
public:
	struct uworld* get_world();
	struct ugameinstance* get_gameinstance();
};

class ulocalplayer : public uobject {
public:
	ugameviewportclient* viewport_client();
};

class uengine : public uobject
{
public:
	uobject* font();
};

class ugameinstance : public uobject {
public:
	uengine* get_uengine();
	tarray<ulocalplayer*> local_players();
};

class AInfo
{
public:
};

class AWorldSettings : public AInfo
{
public:
	uint8_t                                        Pad_3B8[0x8];
	int32_t                                        VisibilityCellSize;
	uint8_t                                        bPrecomputeVisibility : 1;
	uint8_t                                        bPlaceCellsOnlyAlongCameraTracks : 1;
	uint8_t                                        bEnableWorldBoundsChecks : 1;
	uint8_t                                        bEnableNavigationSystem : 1;
	uint8_t                                        bEnableAISystem : 1;
	uint8_t                                        bEnableWorldComposition : 1;
	uint8_t                                        bUseClientSideLevelStreamingVolumes : 1;
	uint8_t                                        bEnableWorldOriginRebasing : 1;
	uint8_t                                        bWorldGravitySet : 1;
	uint8_t                                        bGlobalGravitySet : 1;
	uint8_t                                        bMinimizeBSPSections : 1;
	uint8_t                                        bForceNoPrecomputedLighting : 1;
	uint8_t                                        bHighPriorityLoading : 1;
	uint8_t                                        bHighPriorityLoadingLocal : 1;
	uint8_t                                        bOverrideDefaultBroadphaseSettings : 1;
	uint8_t                                        Pad_3C7[0x1];
	class UNavigationSystemConfig* NavigationSystemConfig;
	class UNavigationSystemConfig* NavigationSystemConfigOverride;
	float                                          WorldToMeters;
	float                                          KillZ;
	float                                          WorldGravityZ;
	float                                          GlobalGravityZ;
	int32_t                                        PackedLightAndShadowMapTextureSize;
	fvector                                 DefaultColorScale;
	float                                          DefaultMaxDistanceFieldOcclusionDistance;
	float                                          GlobalDistanceFieldViewDistance;
	float                                          DynamicIndirectShadowsSelfShadowingIntensity;
	float                                          SmallestOccluder;
	float                                          BackfaceLimit;
	float                                          SmallestHole;
	float                                          CollisionRadius;
	bool                                           bIncludeUmbraViewVolumesAsSubLevel;
	bool                                           bIncludeStreamedSublevelsInUmbra;
	bool                                           bIncludeStreamedSublevelsInZPrepass;
	uint8_t                                        Pad_43F[0x1];
	uint8_t                                        Pad_484[0x4];
	class USoundMix* DefaultBaseSoundMix;
	float                                          TimeDilation;
	float                                          MatineeTimeDilation;
	float                                          DemoPlayTimeDilation;
	float                                          MinGlobalTimeDilation;
	float                                          MaxGlobalTimeDilation;
	float                                          MinUndilatedFrameTime;
	float                                          MaxUndilatedFrameTime;
	uint8_t                                        Pad_4EC[0x4];
	class ASphereReflectionCapture* AresAmbientReflection;
	class ASphereReflectionCapture* AresAmbientEnvironmentReflection;
	class ASphereReflectionCapture* AresAmbientEnvironmentAlternativeReflection;
	bool                                           bAresLevelIgnoresZPrepass;
	uint8_t                                        Pad_509[0x7];
	class UStaticMesh* AresZPrepassMesh;
	float                                          ZPrepassBoundsCullRadius;
	float                                          ZPrepassPercentTriangles;
	float                                          ZPrepassMinimumTriangleArea;
	float                                          ZPrepassMinimumMeshSurfaceArea;
	class APlayerState* Pauser;
	class APlayerState* PauserPlayerState;
	int32_t                                        MaxNumberOfBookmarks;
	uint8_t                                        Pad_55C[0x4];
};

class uworld : public uobject
{
public:
	ugameinstance* game_instance();
	static uworld* getworld2();
	void RecaptureSky1();
	void SetLightColor1(flinearcolor NewLightColor);
	void SetLowerHemisphereColor1(flinearcolor InLowerHemisphereColor);
	AWorldSettings* k2_get_world_settings();
	AAIController* SpawnActor(uclass* Class, fvector const& Location, frotator const& Rotation, FActorSpawnParameters const& SpawnParameters);
};

class UFogOfWarComponent
{
public:
	bool bCanMakeActorsVisionRelevant;
	bool bBoundsIncludesOnlyCollidingComponents;
	bool bUseCachedBounds;
	float LookAheadTime;
	bool bOwnerIsRelevantToClient;
	bool bOwnerIsHiddenForClient;
	bool bReceivedNetUpdate;
	tarray<class UFogOfWarBoundsComponent*> ExtraFogOfWarBounds;
	tarray<class AActor*> CachedAttachedActors;
	tarray<class UFogOfWarComponent*> CachedAttachedFoWComponents;
	bool bCacheNeedsRebuilding;
	class UFogOfWarDebugComponent* DebugComponent;
	class UFogOfWarManagerComponent* ManagerComponent;

public:
};

class UShooterCharacterFogOfWarComponent final : public UFogOfWarComponent
{
public:
	float JumpVelocityContribution;
	float MaxSpeedContribution;
	float MaxSpeed;
	float InitialJumpVelocity;
	bool bCachedMaxSpeed;
	bool bCachedJumpVelocity;
	class UBaseTeamComponent* CachedTeamComponent;
};

struct UActorComponents : public uobject
{
public:
	uint8_t                                       Pad_30[0x18];
	tarray<class FName>                           ComponentTags;
	tarray<class UAssetUserData*>                 AssetUserData;
	uint8_t                                       Pad_98[0x4];
	int32_t                                       UCSSerializationIndex;
	uint8_t                                       BitPad_A0_0 : 3;
	uint8_t                                       bNetAddressable : 1;
	uint8_t                                       bReplicates : 1;
	uint8_t                                       Pad_A1[0x7];
	uint64_t                                      TickTimingsAccumulatedTotal;
	uint64_t                                      TickTimingsAccumulatedBP;
	uint64_t                                      TickTimingsStart;
	uint8_t                                       Pad_C0[0x1];
	uint8_t                                       BitPad_C1_0 : 3;
	uint8_t                                       bAutoActivate : 1;
	uint8_t                                       bIsActive : 1;
	uint8_t                                       bEditableWhenInherited : 1;
	uint8_t                                       BitPad_C1_6 : 1;
	uint8_t                                       bCanEverAffectNavigation : 1;
	uint8_t                                       BitPad_C2_0 : 1;
	uint8_t                                       bIsEditorOnly : 1;
	uint8_t                                       Pad_C3[0x1];
	uint8_t                                       Pad_C7[0x1];
	uint8_t                                       Pad_D8[0x10];
};


class UBasicCombatStatsComponent final : public UActorComponents
{
public:
	int32_t AggregateKills;
	int32_t AggregateDeaths;
	int32_t AggregateAssists;
};

class AOwnerExclusivePlayerInfo final : public AInfo
{
public:
	uint8_t                                       Pad_408[0x10];
	class AController* AresController;
	tarray<float>                                 CurrentResources;
	int32_t                                       NumDeathStreak;
	int32_t                                       StartOfRoundMoneyCache;
	int32_t                                       StartOfRoundLoadoutValueCache;
	uint8_t                                       Pad_44C[0x4];
	tarray<struct FAresTrackedReward>             TrackedRewards;
	int32_t                                       EndOfRoundBeforeRewardsMoney;
	bool                                          bLoadoutFinalized;
	bool                                          bCanProgressAchievements;
	uint8_t                                       Pad_466[0x2];
	fstring                                 AuthPlayerGameSessionStartTime;
	tarray<struct FAresPlayerRoundInfo>           RoundInfos;
	uint8_t                                       Pad_4B9[0x7];
	class UPersonalizationComponent* PersonalizationComponent;
	class USprayLoadoutComponent* SprayLoadoutComponent;
	class UTotemLoadoutComponent* TotemLoadoutComponent;
	tarray<struct FObfuscatedPlayerInformation>   AllPlayersObfuscatedPlayerInformation;
	uint8_t                                       Pad_4E8[0x108];
};

class aaresplayerstatebase : public aplayerstate
{
public:
	uint8_t                                         pad_4c0[0x104];
	bool                                            has_ever_connected;
	uint8_t                                         pad_5c6[0x2];
	uint8_t                                         pad_5e8[0x8];
	bool                                            pending_disassociate;
	uint8_t                                         pad_5f1[0x3];
	int32_t                                         competitive_tier;
	aaresplayerstatebase* spectated_player;
	bool                                            has_ever_begun_connecting;
	uint8_t                                         pad_629[0xf];
	fstring                                         auth_megapacket_game_name;
	fstring                                         auth_megapacket_tag_line;
};

class ashooterplayerstate final : public aaresplayerstatebase
{
public:
	uint8_t                                         pad_658[0x38];
	//ashootercharacter* spawned_character;
	//ashootercharacter* client_prev_spawned_character;
	//ashootercharacter* possessed_character;
	int32_t                                       num_ultimate_points;
	int32_t                                       total_acquired_ultimate_points;
	int32_t                                       num_refundable_ultimate_points;
	uint8_t                                       pad_9bc[0x4];
	tarray<ashooterplayerstate*>                  map_pings_muted;
	bool                                          is_drop_in_player;
	uint8_t                                       pad_a31[0x3];
	bool                                          is_cheat_invulnerable;
	bool                                          is_cheat_auto_resurrect;
	uint8_t                                       pad_a46[0x32];
	fvector                                       auto_resurrect_location;
	frotator                                      auto_resurrect_rotation;
	bool                                          is_cheat_ghost;
	uint8_t                                       pad_a91[0x3];
	int32_t                                       combat_report_index;
	bool                                          allow_agent_specific_keybinds;
	bool                                          should_init_coach;
	bool                                          is_coach;
	uint8_t                                       pad_aab[0x1];
	fname                                         auth_coach_team;
	bool                                          use_agent_name_as_player_name;
	uint8_t                                       pad_ac9[0x7];

	/*int32_t get_money();
	ashooterplayerstate* GetPlayerState();*/
};

class UMatchDetailsViewModel final : public uobject
{
public:
	//struct FProcessedMatchDetails                 Data;                                              // 0x0030(0x0278)(BlueprintVisible, BlueprintReadOnly, NativeAccessSpecifierPublic)
	fstring                                 TargetSubject;                                     // 0x02A8(0x0010)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	//FMulticastInlineDelegateProperty_             OnContentLoaded;                                   // 0x02B8(0x0010)(ZeroConstructor, InstancedReference, BlueprintAssignable, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_2C8[0x8];
	tarray<fname> GetAllyCharacterNames();
	tarray<fname> GetEnemyCharacterNames();
	// 0x02C8(0x0008)(Fixing Struct Size After Last Property [ Dumper-7 ])
};

enum class ECameraProjectionMode : uint8_t
{
	Perspective = 0,
	Orthographic = 1,
	ECameraProjectionMode_MAX = 2,
};

struct FPostProcessSettings : public uobject
{
public:
	uint8_t                                         bOverride_TemperatureType : 1;                     // 0x0000(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_WhiteTemp : 1;                           // 0x0000(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_WhiteTint : 1;                           // 0x0000(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorSaturation : 1;                     // 0x0000(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorContrast : 1;                       // 0x0000(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorGamma : 1;                          // 0x0000(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorGain : 1;                           // 0x0000(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorOffset : 1;                         // 0x0000(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorSaturationShadows : 1;              // 0x0001(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorContrastShadows : 1;                // 0x0001(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorGammaShadows : 1;                   // 0x0001(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorGainShadows : 1;                    // 0x0001(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorOffsetShadows : 1;                  // 0x0001(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorSaturationMidtones : 1;             // 0x0001(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorContrastMidtones : 1;               // 0x0001(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorGammaMidtones : 1;                  // 0x0001(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorGainMidtones : 1;                   // 0x0002(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorOffsetMidtones : 1;                 // 0x0002(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorSaturationHighlights : 1;           // 0x0002(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorContrastHighlights : 1;             // 0x0002(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorGammaHighlights : 1;                // 0x0002(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorGainHighlights : 1;                 // 0x0002(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorOffsetHighlights : 1;               // 0x0002(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorCorrectionShadowsMax : 1;           // 0x0002(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorCorrectionHighlightsMin : 1;        // 0x0003(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorCorrectionHighlightsMax : 1;        // 0x0003(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_BlueCorrection : 1;                      // 0x0003(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ExpandGamut : 1;                         // 0x0003(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ToneCurveAmount : 1;                     // 0x0003(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmSlope : 1;                           // 0x0003(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmToe : 1;                             // 0x0003(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmShoulder : 1;                        // 0x0003(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmBlackClip : 1;                       // 0x0004(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmWhiteClip : 1;                       // 0x0004(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_SceneColorTint : 1;                      // 0x0004(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_SceneFringeIntensity : 1;                // 0x0004(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ChromaticAberrationStartOffset : 1;      // 0x0004(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AmbientCubemapTint : 1;                  // 0x0004(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AmbientCubemapIntensity : 1;             // 0x0004(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_BloomMethod : 1;                         // 0x0004(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_BloomIntensity : 1;                      // 0x0005(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_BloomThreshold : 1;                      // 0x0005(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_Bloom1Tint : 1;                          // 0x0005(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_Bloom1Size : 1;                          // 0x0005(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_Bloom2Size : 1;                          // 0x0005(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_Bloom2Tint : 1;                          // 0x0005(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_Bloom3Tint : 1;                          // 0x0005(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_Bloom3Size : 1;                          // 0x0005(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_Bloom4Tint : 1;                          // 0x0006(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_Bloom4Size : 1;                          // 0x0006(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_Bloom5Tint : 1;                          // 0x0006(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_Bloom5Size : 1;                          // 0x0006(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_Bloom6Tint : 1;                          // 0x0006(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_Bloom6Size : 1;                          // 0x0006(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_BloomSizeScale : 1;                      // 0x0006(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_BloomConvolutionTexture : 1;             // 0x0006(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_BloomConvolutionScatterDispersion : 1;   // 0x0007(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_BloomConvolutionSize : 1;                // 0x0007(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_BloomConvolutionCenterUV : 1;            // 0x0007(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_BloomConvolutionPreFilter : 1;           // 0x0007(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_BloomConvolutionPreFilterMin : 1;        // 0x0007(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_BloomConvolutionPreFilterMax : 1;        // 0x0007(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_BloomConvolutionPreFilterMult : 1;       // 0x0007(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_BloomConvolutionBufferScale : 1;         // 0x0007(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_BloomDirtMaskIntensity : 1;              // 0x0008(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_BloomDirtMaskTint : 1;                   // 0x0008(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_BloomDirtMask : 1;                       // 0x0008(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_CameraShutterSpeed : 1;                  // 0x0008(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_CameraISO : 1;                           // 0x0008(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AutoExposureMethod : 1;                  // 0x0008(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AutoExposureLowPercent : 1;              // 0x0008(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AutoExposureHighPercent : 1;             // 0x0008(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AutoExposureMinBrightness : 1;           // 0x0009(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AutoExposureMaxBrightness : 1;           // 0x0009(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AutoExposureCalibrationConstant : 1;     // 0x0009(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AutoExposureSpeedUp : 1;                 // 0x0009(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AutoExposureSpeedDown : 1;               // 0x0009(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AutoExposureBias : 1;                    // 0x0009(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AutoExposureBiasCurve : 1;               // 0x0009(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AutoExposureMeterMask : 1;               // 0x0009(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AutoExposureApplyPhysicalCameraExposure : 1; // 0x000A(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_HistogramLogMin : 1;                     // 0x000A(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_HistogramLogMax : 1;                     // 0x000A(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LocalExposureContrastScale : 1;          // 0x000A(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LocalExposureHighlightContrastScale : 1; // 0x000A(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LocalExposureShadowContrastScale : 1;    // 0x000A(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LocalExposureHighlightContrastCurve : 1; // 0x000A(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LocalExposureShadowContrastCurve : 1;    // 0x000A(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LocalExposureHighlightThreshold : 1;     // 0x000B(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LocalExposureShadowThreshold : 1;        // 0x000B(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LocalExposureDetailStrength : 1;         // 0x000B(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LocalExposureBlurredLuminanceBlend : 1;  // 0x000B(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LocalExposureBlurredLuminanceKernelSizePercent : 1; // 0x000B(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LocalExposureMiddleGreyBias : 1;         // 0x000B(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LensFlareIntensity : 1;                  // 0x000B(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LensFlareTint : 1;                       // 0x000B(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LensFlareTints : 1;                      // 0x000C(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LensFlareBokehSize : 1;                  // 0x000C(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LensFlareBokehShape : 1;                 // 0x000C(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LensFlareThreshold : 1;                  // 0x000C(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_VignetteIntensity : 1;                   // 0x000C(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_Sharpen : 1;                             // 0x000C(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_GrainIntensity : 1;                      // 0x000C(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_GrainJitter : 1;                         // 0x000C(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmGrainIntensity : 1;                  // 0x000D(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmGrainIntensityShadows : 1;           // 0x000D(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmGrainIntensityMidtones : 1;          // 0x000D(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmGrainIntensityHighlights : 1;        // 0x000D(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmGrainShadowsMax : 1;                 // 0x000D(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmGrainHighlightsMin : 1;              // 0x000D(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmGrainHighlightsMax : 1;              // 0x000D(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmGrainTexelSize : 1;                  // 0x000D(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_FilmGrainTexture : 1;                    // 0x000E(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AmbientOcclusionIntensity : 1;           // 0x000E(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AmbientOcclusionStaticFraction : 1;      // 0x000E(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AmbientOcclusionRadius : 1;              // 0x000E(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AmbientOcclusionFadeDistance : 1;        // 0x000E(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AmbientOcclusionFadeRadius : 1;          // 0x000E(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AmbientOcclusionDistance : 1;            // 0x000E(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AmbientOcclusionRadiusInWS : 1;          // 0x000E(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AmbientOcclusionPower : 1;               // 0x000F(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AmbientOcclusionBias : 1;                // 0x000F(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AmbientOcclusionQuality : 1;             // 0x000F(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AmbientOcclusionMipBlend : 1;            // 0x000F(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AmbientOcclusionMipScale : 1;            // 0x000F(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AmbientOcclusionMipThreshold : 1;        // 0x000F(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_AmbientOcclusionTemporalBlendWeight : 1; // 0x000F(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         BitPad_F_7 : 1;                                    // 0x000F(0x0001)(Fixing Bit-Field Size For New Byte [ Dumper-7 ])
	uint8_t                                         bOverride_RayTracingAO : 1;                        // 0x0010(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_RayTracingAOSamplesPerPixel : 1;         // 0x0010(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_RayTracingAOIntensity : 1;               // 0x0010(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_RayTracingAORadius : 1;                  // 0x0010(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         BitPad_10_4 : 4;                                   // 0x0010(0x0001)(Fixing Bit-Field Size For New Byte [ Dumper-7 ])
	uint8_t                                         Pad_11[0x3];                                       // 0x0011(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	uint8_t                                         bOverride_LPVIntensity : 1;                        // 0x0014(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LPVDirectionalOcclusionIntensity : 1;    // 0x0014(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LPVDirectionalOcclusionRadius : 1;       // 0x0014(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LPVDiffuseOcclusionExponent : 1;         // 0x0014(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LPVSpecularOcclusionExponent : 1;        // 0x0014(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LPVDiffuseOcclusionIntensity : 1;        // 0x0014(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LPVSpecularOcclusionIntensity : 1;       // 0x0014(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LPVSize : 1;                             // 0x0014(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LPVSecondaryOcclusionIntensity : 1;      // 0x0015(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LPVSecondaryBounceIntensity : 1;         // 0x0015(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LPVGeometryVolumeBias : 1;               // 0x0015(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LPVVplInjectionBias : 1;                 // 0x0015(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LPVEmissiveInjectionIntensity : 1;       // 0x0015(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LPVFadeRange : 1;                        // 0x0015(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LPVDirectionalOcclusionFadeRange : 1;    // 0x0015(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_IndirectLightingColor : 1;               // 0x0015(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_IndirectLightingIntensity : 1;           // 0x0016(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorGradingIntensity : 1;               // 0x0016(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ColorGradingLUT : 1;                     // 0x0016(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldFocalDistance : 1;           // 0x0016(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldFstop : 1;                   // 0x0016(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldMinFstop : 1;                // 0x0016(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldBladeCount : 1;              // 0x0016(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldSensorWidth : 1;             // 0x0016(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldSqueezeFactor : 1;           // 0x0017(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldDepthBlurRadius : 1;         // 0x0017(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldUseHairDepth : 1;            // 0x0017(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldDepthBlurAmount : 1;         // 0x0017(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldFocalRegion : 1;             // 0x0017(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldNearTransitionRegion : 1;    // 0x0017(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldFarTransitionRegion : 1;     // 0x0017(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldScale : 1;                   // 0x0017(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldNearBlurSize : 1;            // 0x0018(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldFarBlurSize : 1;             // 0x0018(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_MobileHQGaussian : 1;                    // 0x0018(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldOcclusion : 1;               // 0x0018(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldSkyFocusDistance : 1;        // 0x0018(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DepthOfFieldVignetteSize : 1;            // 0x0018(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_MotionBlurAmount : 1;                    // 0x0018(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_MotionBlurMax : 1;                       // 0x0018(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_MotionBlurTargetFPS : 1;                 // 0x0019(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_MotionBlurPerObjectSize : 1;             // 0x0019(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ScreenPercentage : 1;                    // 0x0019(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ReflectionMethod : 1;                    // 0x0019(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LumenReflectionQuality : 1;              // 0x0019(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ScreenSpaceReflectionIntensity : 1;      // 0x0019(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ScreenSpaceReflectionQuality : 1;        // 0x0019(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ScreenSpaceReflectionMaxRoughness : 1;   // 0x0019(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_ScreenSpaceReflectionRoughnessScale : 1; // 0x001A(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         BitPad_1A_1 : 7;                                   // 0x001A(0x0001)(Fixing Bit-Field Size For New Byte [ Dumper-7 ])
	uint8_t                                         Pad_1B[0x1];                                       // 0x001B(0x0001)(Fixing Size After Last Property [ Dumper-7 ])
	uint8_t                                         bOverride_ReflectionsType : 1;                     // 0x001C(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Deprecated, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_RayTracingReflectionsMaxRoughness : 1;   // 0x001C(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_RayTracingReflectionsMaxBounces : 1;     // 0x001C(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_RayTracingReflectionsSamplesPerPixel : 1; // 0x001C(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_RayTracingReflectionsShadows : 1;        // 0x001C(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_RayTracingReflectionsTranslucency : 1;   // 0x001C(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_TranslucencyType : 1;                    // 0x001C(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_RayTracingTranslucencyMaxRoughness : 1;  // 0x001C(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_RayTracingTranslucencyRefractionRays : 1; // 0x001D(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_RayTracingTranslucencySamplesPerPixel : 1; // 0x001D(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_RayTracingTranslucencyShadows : 1;       // 0x001D(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_RayTracingTranslucencyRefraction : 1;    // 0x001D(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_DynamicGlobalIlluminationMethod : 1;     // 0x001D(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LumenSceneLightingQuality : 1;           // 0x001D(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LumenSceneDetail : 1;                    // 0x001D(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LumenSceneViewDistance : 1;              // 0x001D(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LumenSceneLightingUpdateSpeed : 1;       // 0x001E(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LumenFinalGatherQuality : 1;             // 0x001E(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LumenFinalGatherLightingUpdateSpeed : 1; // 0x001E(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LumenFinalGatherScreenTraces : 1;        // 0x001E(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LumenMaxTraceDistance : 1;               // 0x001E(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LumenDiffuseColorBoost : 1;              // 0x001E(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LumenSkylightLeaking : 1;                // 0x001E(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LumenFullSkylightLeakingDistance : 1;    // 0x001E(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         Pad_1F[0x1];                                       // 0x001F(0x0001)(Fixing Size After Last Property [ Dumper-7 ])
	uint8_t                                         bOverride_LumenRayLightingMode : 1;                // 0x0020(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LumenReflectionsScreenTraces : 1;        // 0x0020(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LumenFrontLayerTranslucencyReflections : 1; // 0x0020(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         BitPad_20_3 : 5;                                   // 0x0020(0x0001)(Fixing Bit-Field Size For New Byte [ Dumper-7 ])
	uint8_t                                         Pad_21[0x3];                                       // 0x0021(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	uint8_t                                         bOverride_LumenMaxRoughnessToTraceReflections : 1; // 0x0024(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LumenMaxReflectionBounces : 1;           // 0x0024(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_LumenMaxRefractionBounces : 1;           // 0x0024(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         BitPad_24_3 : 5;                                   // 0x0024(0x0001)(Fixing Bit-Field Size For New Byte [ Dumper-7 ])
	uint8_t                                         Pad_25[0x3];                                       // 0x0025(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	uint8_t                                         bOverride_LumenSurfaceCacheResolution : 1;         // 0x0028(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         BitPad_28_1 : 7;                                   // 0x0028(0x0001)(Fixing Bit-Field Size For New Byte [ Dumper-7 ])
	uint8_t                                         Pad_29[0x3];                                       // 0x0029(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	uint8_t                                         bOverride_RayTracingGI : 1;                        // 0x002C(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_RayTracingGIMaxBounces : 1;              // 0x002C(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_RayTracingGISamplesPerPixel : 1;         // 0x002C(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_PathTracingMaxBounces : 1;               // 0x002C(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_PathTracingSamplesPerPixel : 1;          // 0x002C(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_PathTracingMaxPathExposure : 1;          // 0x002C(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_PathTracingEnableEmissiveMaterials : 1;  // 0x002C(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_PathTracingEnableReferenceDOF : 1;       // 0x002C(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_PathTracingEnableReferenceAtmosphere : 1; // 0x002D(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_PathTracingEnableDenoiser : 1;           // 0x002D(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_PathTracingIncludeEmissive : 1;          // 0x002D(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_PathTracingIncludeDiffuse : 1;           // 0x002D(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_PathTracingIncludeIndirectDiffuse : 1;   // 0x002D(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_PathTracingIncludeSpecular : 1;          // 0x002D(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_PathTracingIncludeIndirectSpecular : 1;  // 0x002D(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_PathTracingIncludeVolume : 1;            // 0x002D(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bOverride_PathTracingIncludeIndirectVolume : 1;    // 0x002E(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         BitPad_2E_1 : 7;                                   // 0x002E(0x0001)(Fixing Bit-Field Size For New Byte [ Dumper-7 ])
	uint8_t                                         Pad_2F[0x1];                                       // 0x002F(0x0001)(Fixing Size After Last Property [ Dumper-7 ])
	uint8_t                                         bMobileHQGaussian : 1;                             // 0x0030(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	float                                         WhiteTemp;                                         // 0x0034(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         WhiteTint;                                         // 0x0038(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_3C[0x4];                                       // 0x003C(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         ColorCorrectionHighlightsMin;                      // 0x02C0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         ColorCorrectionHighlightsMax;                      // 0x02C4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         ColorCorrectionShadowsMax;                         // 0x02C8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         BlueCorrection;                                    // 0x02CC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         ExpandGamut;                                       // 0x02D0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         ToneCurveAmount;                                   // 0x02D4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FilmSlope;                                         // 0x02D8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FilmToe;                                           // 0x02DC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FilmShoulder;                                      // 0x02E0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FilmBlackClip;                                     // 0x02E4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FilmWhiteClip;                                     // 0x02E8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	flinearcolor                           SceneColorTint;                                    // 0x02EC(0x0010)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         SceneFringeIntensity;                              // 0x02FC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         ChromaticAberrationStartOffset;                    // 0x0300(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         BloomIntensity;                                    // 0x0304(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         BloomThreshold;                                    // 0x0308(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         BloomSizeScale;                                    // 0x030C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         Bloom1Size;                                        // 0x0310(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         Bloom2Size;                                        // 0x0314(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         Bloom3Size;                                        // 0x0318(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         Bloom4Size;                                        // 0x031C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         Bloom5Size;                                        // 0x0320(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         Bloom6Size;                                        // 0x0324(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	flinearcolor                           Bloom1Tint;                                        // 0x0328(0x0010)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	flinearcolor                           Bloom2Tint;                                        // 0x0338(0x0010)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	flinearcolor                           Bloom3Tint;                                        // 0x0348(0x0010)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	flinearcolor                           Bloom4Tint;                                        // 0x0358(0x0010)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	flinearcolor                           Bloom5Tint;                                        // 0x0368(0x0010)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	flinearcolor                           Bloom6Tint;                                        // 0x0378(0x0010)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         BloomConvolutionScatterDispersion;                 // 0x0388(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         BloomConvolutionSize;                              // 0x038C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	fvector2d                             BloomConvolutionCenterUV;                          // 0x0398(0x0010)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         BloomConvolutionPreFilterMin;                      // 0x03A8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         BloomConvolutionPreFilterMax;                      // 0x03AC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         BloomConvolutionPreFilterMult;                     // 0x03B0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         BloomConvolutionBufferScale;                       // 0x03B4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class UTexture* BloomDirtMask;                                     // 0x03B8(0x0008)(Edit, BlueprintVisible, ZeroConstructor, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         BloomDirtMaskIntensity;                            // 0x03C0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)EDynamicGlobalIlluminationMethod              DynamicGlobalIlluminationMethod;                   // 0x03D4(0x0001)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_3D5[0x3];                                      // 0x03D5(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	flinearcolor                           IndirectLightingColor;                             // 0x03D8(0x0010)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         IndirectLightingIntensity;                         // 0x03E8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LumenSceneLightingQuality;                         // 0x03EC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LumenSceneDetail;                                  // 0x03F0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LumenSceneViewDistance;                            // 0x03F4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LumenSceneLightingUpdateSpeed;                     // 0x03F8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LumenFinalGatherQuality;                           // 0x03FC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LumenFinalGatherLightingUpdateSpeed;               // 0x0400(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         LumenFinalGatherScreenTraces : 1;                  // 0x0404(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         Pad_405[0x3];                                      // 0x0405(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         LumenMaxTraceDistance;                             // 0x0408(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LumenDiffuseColorBoost;                            // 0x040C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LumenSkylightLeaking;                              // 0x0410(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LumenFullSkylightLeakingDistance;                  // 0x0414(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LumenSurfaceCacheResolution;                       // 0x0418(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)	
	uint8_t                                         Pad_41E[0x2];                                      // 0x041E(0x0002)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         LumenReflectionQuality;                            // 0x0420(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         LumenReflectionsScreenTraces : 1;                  // 0x0425(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         LumenFrontLayerTranslucencyReflections : 1;        // 0x0425(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         Pad_426[0x2];                                      // 0x0426(0x0002)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         LumenMaxRoughnessToTraceReflections;               // 0x0428(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32_t                                         LumenMaxReflectionBounces;                         // 0x042C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32_t                                         LumenMaxRefractionBounces;                         // 0x0430(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         ScreenSpaceReflectionIntensity;                    // 0x0434(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         ScreenSpaceReflectionQuality;                      // 0x0438(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         ScreenSpaceReflectionMaxRoughness;                 // 0x043C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	flinearcolor                           AmbientCubemapTint;                                // 0x0440(0x0010)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AmbientCubemapIntensity;                           // 0x0450(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_454[0x4];                                      // 0x0454(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	class UTextureCube* AmbientCubemap;                                    // 0x0458(0x0008)(Edit, BlueprintVisible, ZeroConstructor, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         CameraShutterSpeed;                                // 0x0460(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         CameraISO;                                         // 0x0464(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DepthOfFieldFstop;                                 // 0x0468(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DepthOfFieldMinFstop;                              // 0x046C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32_t                                         DepthOfFieldBladeCount;                            // 0x0470(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AutoExposureBias;                                  // 0x0474(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AutoExposureBiasBackup;                            // 0x0478(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         bOverride_AutoExposureBiasBackup : 1;              // 0x047C(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         BitPad_47C_1 : 7;                                  // 0x047C(0x0001)(Fixing Bit-Field Size For New Byte [ Dumper-7 ])
	uint8_t                                         Pad_47D[0x3];                                      // 0x047D(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	uint8_t                                         AutoExposureApplyPhysicalCameraExposure : 1;       // 0x0480(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         Pad_481[0x7];                                      // 0x0481(0x0007)(Fixing Size After Last Property [ Dumper-7 ])
	class UCurveFloat* AutoExposureBiasCurve;                             // 0x0488(0x0008)(Edit, BlueprintVisible, ZeroConstructor, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class UTexture* AutoExposureMeterMask;                             // 0x0490(0x0008)(Edit, BlueprintVisible, ZeroConstructor, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AutoExposureLowPercent;                            // 0x0498(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AutoExposureHighPercent;                           // 0x049C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AutoExposureMinBrightness;                         // 0x04A0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AutoExposureMaxBrightness;                         // 0x04A4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AutoExposureSpeedUp;                               // 0x04A8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AutoExposureSpeedDown;                             // 0x04AC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         HistogramLogMin;                                   // 0x04B0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         HistogramLogMax;                                   // 0x04B4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AutoExposureCalibrationConstant;                   // 0x04B8(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LocalExposureContrastScale;                        // 0x04BC(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LocalExposureHighlightContrastScale;               // 0x04C0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LocalExposureShadowContrastScale;                  // 0x04C4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class UCurveFloat* LocalExposureHighlightContrastCurve;               // 0x04C8(0x0008)(Edit, BlueprintVisible, ZeroConstructor, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class UCurveFloat* LocalExposureShadowContrastCurve;                  // 0x04D0(0x0008)(Edit, BlueprintVisible, ZeroConstructor, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LocalExposureHighlightThreshold;                   // 0x04D8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LocalExposureShadowThreshold;                      // 0x04DC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LocalExposureDetailStrength;                       // 0x04E0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LocalExposureBlurredLuminanceBlend;                // 0x04E4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LocalExposureBlurredLuminanceKernelSizePercent;    // 0x04E8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LocalExposureMiddleGreyBias;                       // 0x04EC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LensFlareIntensity;                                // 0x04F0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	flinearcolor                           LensFlareTint;                                     // 0x04F4(0x0010)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LensFlareBokehSize;                                // 0x0504(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LensFlareThreshold;                                // 0x0508(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_50C[0x4];                                      // 0x050C(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	class UTexture* LensFlareBokehShape;                               // 0x0510(0x0008)(Edit, BlueprintVisible, ZeroConstructor, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	flinearcolor                           LensFlareTints[0x8];                               // 0x0518(0x0010)(Edit, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         VignetteIntensity;                                 // 0x0598(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         Sharpen;                                           // 0x059C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         GrainJitter;                                       // 0x05A0(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         GrainIntensity;                                    // 0x05A4(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FilmGrainIntensity;                                // 0x05A8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FilmGrainIntensityShadows;                         // 0x05AC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FilmGrainIntensityMidtones;                        // 0x05B0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FilmGrainIntensityHighlights;                      // 0x05B4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FilmGrainShadowsMax;                               // 0x05B8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FilmGrainHighlightsMin;                            // 0x05BC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FilmGrainHighlightsMax;                            // 0x05C0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         FilmGrainTexelSize;                                // 0x05C4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class UTexture2D* FilmGrainTexture;                                  // 0x05C8(0x0008)(Edit, BlueprintVisible, ZeroConstructor, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AmbientOcclusionIntensity;                         // 0x05D0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AmbientOcclusionStaticFraction;                    // 0x05D4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AmbientOcclusionRadius;                            // 0x05D8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         AmbientOcclusionRadiusInWS : 1;                    // 0x05DC(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         Pad_5DD[0x3];                                      // 0x05DD(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         AmbientOcclusionFadeDistance;                      // 0x05E0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AmbientOcclusionFadeRadius;                        // 0x05E4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AmbientOcclusionDistance;                          // 0x05E8(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AmbientOcclusionPower;                             // 0x05EC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AmbientOcclusionBias;                              // 0x05F0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AmbientOcclusionQuality;                           // 0x05F4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AmbientOcclusionMipBlend;                          // 0x05F8(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AmbientOcclusionMipScale;                          // 0x05FC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AmbientOcclusionMipThreshold;                      // 0x0600(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         AmbientOcclusionTemporalBlendWeight;               // 0x0604(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         RayTracingAO : 1;                                  // 0x0608(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         Pad_609[0x3];                                      // 0x0609(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	int32_t                                         RayTracingAOSamplesPerPixel;                       // 0x060C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         RayTracingAOIntensity;                             // 0x0610(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         RayTracingAORadius;                                // 0x0614(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         ColorGradingIntensity;                             // 0x0618(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_61C[0x4];                                      // 0x061C(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	class UTexture* ColorGradingLUT;                                   // 0x0620(0x0008)(Edit, BlueprintVisible, ZeroConstructor, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DepthOfFieldSensorWidth;                           // 0x0628(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DepthOfFieldSqueezeFactor;                         // 0x062C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DepthOfFieldFocalDistance;                         // 0x0630(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DepthOfFieldDepthBlurAmount;                       // 0x0634(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DepthOfFieldDepthBlurRadius;                       // 0x0638(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         DepthOfFieldUseHairDepth : 1;                      // 0x063C(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         Pad_63D[0x3];                                      // 0x063D(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         DepthOfFieldFocalRegion;                           // 0x0640(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DepthOfFieldNearTransitionRegion;                  // 0x0644(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DepthOfFieldFarTransitionRegion;                   // 0x0648(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DepthOfFieldScale;                                 // 0x064C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DepthOfFieldNearBlurSize;                          // 0x0650(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DepthOfFieldFarBlurSize;                           // 0x0654(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DepthOfFieldOcclusion;                             // 0x0658(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DepthOfFieldSkyFocusDistance;                      // 0x065C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DepthOfFieldVignetteSize;                          // 0x0660(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         MotionBlurAmount;                                  // 0x0664(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         MotionBlurMax;                                     // 0x0668(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32_t                                         MotionBlurTargetFPS;                               // 0x066C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         MotionBlurPerObjectSize;                           // 0x0670(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LPVIntensity;                                      // 0x0674(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LPVVplInjectionBias;                               // 0x0678(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LPVSize;                                           // 0x067C(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LPVSecondaryOcclusionIntensity;                    // 0x0680(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LPVSecondaryBounceIntensity;                       // 0x0684(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LPVGeometryVolumeBias;                             // 0x0688(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LPVEmissiveInjectionIntensity;                     // 0x068C(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LPVDirectionalOcclusionIntensity;                  // 0x0690(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LPVDirectionalOcclusionRadius;                     // 0x0694(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LPVDiffuseOcclusionExponent;                       // 0x0698(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LPVSpecularOcclusionExponent;                      // 0x069C(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LPVDiffuseOcclusionIntensity;                      // 0x06A0(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LPVSpecularOcclusionIntensity;                     // 0x06A4(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_6A9[0x3];                                      // 0x06A9(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         RayTracingTranslucencyMaxRoughness;                // 0x06AC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32_t                                         RayTracingTranslucencyRefractionRays;              // 0x06B0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32_t                                         RayTracingTranslucencySamplesPerPixel;             // 0x06B4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         RayTracingTranslucencyRefraction : 1;              // 0x06B9(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         Pad_6BA[0x2];                                      // 0x06BA(0x0002)(Fixing Size After Last Property [ Dumper-7 ])
	int32_t                                         PathTracingMaxBounces;                             // 0x06BC(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32_t                                         PathTracingSamplesPerPixel;                        // 0x06C0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         PathTracingMaxPathExposure;                        // 0x06C4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         PathTracingEnableEmissiveMaterials : 1;            // 0x06C8(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         PathTracingEnableReferenceDOF : 1;                 // 0x06C8(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         PathTracingEnableReferenceAtmosphere : 1;          // 0x06C8(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         PathTracingEnableDenoiser : 1;                     // 0x06C8(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         PathTracingIncludeEmissive : 1;                    // 0x06C8(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         PathTracingIncludeDiffuse : 1;                     // 0x06C8(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         PathTracingIncludeIndirectDiffuse : 1;             // 0x06C8(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         PathTracingIncludeSpecular : 1;                    // 0x06C8(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         PathTracingIncludeIndirectSpecular : 1;            // 0x06C9(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         PathTracingIncludeVolume : 1;                      // 0x06C9(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         PathTracingIncludeIndirectVolume : 1;              // 0x06C9(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         Pad_6CA[0x2];                                      // 0x06CA(0x0002)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         LPVFadeRange;                                      // 0x06CC(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         LPVDirectionalOcclusionFadeRange;                  // 0x06D0(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         ScreenPercentage;                                  // 0x06D4(0x0004)(ZeroConstructor, Deprecated, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_6E8[0x8];                                      // 0x06E8(0x0008)(Fixing Struct Size After Last Property [ Dumper-7 ])
};

struct FMinimalViewInfo {
	fvector Location;
	fvector Rotation;
	float FOV;
	float DesiredFOV;
	float OrthoWidth;
	float OrthoNearClipPlane;
	float OrthoFarClipPlane;
	float PerspectiveNearClipPlane;
	float AspectRatio;
	char bConstrainAspectRatio : 1;
	char pad_30_2 : 6;
	char pad_31[0x3];
	char pad_35[0x3];
	float PostProcessBlendWeight;
	char pad_3C[0x4];
	FPostProcessSettings PostProcessSettings;
	fvector2d OffCenterProjectionOffset;
	char pad_658[0x48];
};

// Class Engine.CameraComponent
// Size: 0x920 (Inherited: 0x290)
struct UCameraComponent : uobject {
public:
	bool bOverrideFov; // 0x288(0x01)
	bool bOverrideCameraRenderSettings; // 0x289(0x01)
	float fieldOfView; // 0x28c(0x04)
	float OrthoWidth; // 0x290(0x04)
	float OrthoNearClipPlane; // 0x294(0x04)
	float OrthoFarClipPlane; // 0x298(0x04)
	float AspectRatio; // 0x29c(0x04)
	char bConstrainAspectRatio : 1; // 0x2a0(0x01)
	char bUseFieldOfViewForLOD : 1; // 0x2a0(0x01)
	char bLockToHmd : 1; // 0x2a0(0x01)
	char bUsePawnControlRotation : 1; // 0x2a0(0x01)
	ECameraProjectionMode ProjectionMode; // 0x2a1(0x01)
	char pad_2A7_4 : 4; // 0x2a7(0x01)
	char pad_2A8[0x38]; // 0x2a8(0x38)
	float PostProcessBlendWeight; // 0x2e0(0x04)
	char pad_2E4[0x2c]; // 0x2e4(0x2c)
	FPostProcessSettings PostProcessSettings;

	void GetCameraView(float DeltaTime, FMinimalViewInfo* DesiredView);;
	// 0x310(0x610)
};

class aplayercontroller12 : public uobject
{
public:

	bool project_world_location_to_screen12(fvector world_location, fvector2d& screen_location, bool player_viewport_relative);
};

struct ftimerhandle final
{
public:
	uint64_t Handle;
};

class UDamageType : public uobject
{
public:
	uint8_t                                         bCausedByWorld : 1;                                // 0x0030(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bScaleMomentumByMass : 1;                          // 0x0030(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bRadialDamageVelChange : 1;                        // 0x0030(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         Pad_31[0x3];                                       // 0x0031(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         DamageImpulse;                                     // 0x0034(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DestructibleImpulse;                               // 0x0038(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DestructibleDamageSpreadScale;                     // 0x003C(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         DamageFalloff;                                     // 0x0040(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_44[0x4];                                       // 0x0044(0x0004)(Fixing Struct Size After Last Property [ Dumper-7 ])
};

class uaccountxpmanager final
{
public:
	class UConfigManager* ConfigManager;                                     // 0x00A0(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	class URSOManager* RSOManager;                                        // 0x00A8(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	class UContentIndex* ContentIndex;                                      // 0x00B0(0x0008)(ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	class URMSManager* RMSManager;                                        // 0x00B8(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	class UAccountXPService* AccountXPService;                                  // 0x00C0(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	class UAccountXPViewModel* ViewModel;                                         // 0x00C8(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	int32_t                                         LevelCheatOverride;                                // 0x00D0(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	uint8_t                                         Pad_D4[0x44];                                      // 0x00D4(0x0044)(Fixing Struct Size After Last Property [ Dumper-7 ])
};

struct fcanvasuvtri final
{
public:
	fvector2d                              V0_Pos;                                            // 0x0000(0x0008)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	fvector2d                              V0_UV;                                             // 0x0008(0x0008)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	flinearcolor                           V0_Color;                                          // 0x0010(0x0010)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	fvector2d                              V1_Pos;                                            // 0x0020(0x0008)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	fvector2d                               V1_UV;                                             // 0x0028(0x0008)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	flinearcolor                           V1_Color;                                          // 0x0030(0x0010)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	fvector2d                               V2_Pos;                                            // 0x0040(0x0008)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	fvector2d                               V2_UV;                                             // 0x0048(0x0008)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	flinearcolor                           V2_Color;                                          // 0x0050(0x0010)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

class UMatineeCameraShake
{
public:
	float OscillationDuration;                               // 0x00A8(0x0004)
	float OscillationBlendInTime;                            // 0x00AC(0x0004)
	float OscillationBlendOutTime;                           // 0x00B0(0x0004)
	float AnimPlayRate;                                      // 0x0108(0x0004)
	float AnimScale;                                         // 0x010C(0x0004)
	float AnimBlendInTime;                                   // 0x0110(0x0004)
	float AnimBlendOutTime;                                  // 0x0114(0x0004)
	float RandomAnimSegmentDuration;                         // 0x0118(0x0004)
	char pad_011C[0x4];                                      // 0x011C(0x0004)
	class UCameraAnim* Anim;                                 // 0x0120(0x0008)
	class UCameraAnimationSequence* AnimSequence;            // 0x0128(0x0008)
	char bRandomAnimSegment : 1;                             // 0x0130(0x0001)
	char pad_0131[0x3];                                      // 0x0131(0x0003)
	float OscillatorTimeRemaining;                           // 0x0134(0x0004)
	class UCameraAnimInst* AnimInst;                         // 0x0138(0x0008)
	char pad_0140[0x40];                                     // 0x0140(0x0040)
	class USequenceCameraShakePattern* SequenceShakePattern; // 0x0180(0x0008)
	char pad_0188[0x28];
};

enum class ECameraShakePlaySpace : uint8_t
{
	CameraLocal = 0,
	World = 1,
	UserDefined = 2,
	ECameraShakePlaySpace_MAX = 3,
};

//enum class ECompetitiveTier : uint8_t
//{
//	Iron1 = 3,
//	Iron2 = 4,
//	Iron3 = 5,
//	Bronze1 = 6,
//	Bronze2 = 7,
//	Bronze3 = 8,
//	Silver1 = 9,
//	Silver2 = 10,
//	Silver3 = 11,
//	Gold1 = 12,
//	Gold2 = 13,
//	Gold3 = 14,
//	Platinum1 = 15,
//	Platinum2 = 16,
//	Platinum3 = 17,
//	Diamond1 = 18,
//	Diamond2 = 19,
//	Diamond3 = 20,
//	Immortal1 = 21,
//	Immortal2 = 22,
//	Immortal3 = 23,
//	Radiant = 24,
//	ECompetitiveTier_MAX = 25,
//};

//enum class ECompetitiveTier : uint8_t {
//	Iron1 = 3,
//	Iron2 = 4,
//	Iron3 = 5,
//	Bronze1 = 6,
//	Bronze2 = 7,
//	Bronze3 = 8,
//	Silver1 = 9,
//	Silver2 = 10,
//	Silver3 = 11,
//	Gold1 = 12,
//	Gold2 = 13,
//	Gold3 = 14,
//	Platinum1 = 15,
//	Platinum2 = 16,
//	Platinum3 = 17,
//	Diamond1 = 18,
//	Diamond2 = 19,
//	Diamond3 = 20,
//	Immortal1 = 21,
//	Immortal2 = 22,
//	Immortal3 = 23,
//	Radiant = 24,
//	ECompetitiveTier_MAX = 25
//};

/// Enum /Script/ShooterGame.ECompetitiveTier
/// Size: 0x01 (1 bytes)
enum class ECompetitiveTier : uint8_t
{
	ECompetitiveTier__Iron1 = 3,
	ECompetitiveTier__Iron2 = 4,
	ECompetitiveTier__Iron3 = 5,
	ECompetitiveTier__Bronze1 = 6,
	ECompetitiveTier__Bronze2 = 7,
	ECompetitiveTier__Bronze3 = 8,
	ECompetitiveTier__Silver1 = 9,
	ECompetitiveTier__Silver2 = 10,
	ECompetitiveTier__Silver3 = 11,
	ECompetitiveTier__Gold1 = 12,
	ECompetitiveTier__Gold2 = 13,
	ECompetitiveTier__Gold3 = 14,
	ECompetitiveTier__Platinum1 = 15,
	ECompetitiveTier__Platinum2 = 16,
	ECompetitiveTier__Platinum3 = 17,
	ECompetitiveTier__Diamond1 = 18,
	ECompetitiveTier__Diamond2 = 19,
	ECompetitiveTier__Diamond3 = 20,
	ECompetitiveTier__Immortal1 = 21,
	ECompetitiveTier__Immortal2 = 22,
	ECompetitiveTier__Immortal3 = 23,
	ECompetitiveTier__Radiant = 24
};

enum class EAresPartyAccessibility : uint8_t
{
	INVALID = 0,
	OPEN = 1,
	CLOSED = 2,
	EAresPartyAccessibility_MAX = 3,
};

enum class EChatPresenceState : uint8_t
{
	CHAT = 0,
	AWAY = 1,
	DND = 2,
	OFFLINE = 3,
	UNKNOWN = 4,
	EChatPresenceState_MAX = 5,
};

enum class EChatPresenceProduct : uint8_t
{
	ARES = 0,
	LEAGUE = 1,
	BACON = 2,
	KEYSTONE = 3,
	WILDRIFT = 4,
	TFT = 5,
	LION = 6,
	RIOT_MOBILE = 7,
	UNKNOWN = 8,
	NONE = 9,
	EChatPresenceProduct_MAX = 10,
};

class UDirectionalLightComponent : public uobject
{
public:
	float ShadowCascadeBiasDistribution;
	uint8_t bEnableLightShaftOcclusion : 1;
	float OcclusionMaskDarkness;
	float OcclusionDepthRange;
	fvector LightShaftOverrideDirection;
	float WholeSceneDynamicShadowRadius;
	float DynamicShadowDistanceMovableLight;
	float DynamicShadowDistanceStationaryLight;
	int32_t DynamicShadowCascades;
	float CascadeDistributionExponent;
	float CascadeTransitionFraction;
	float ShadowDistanceFadeoutFraction;
	uint8_t bUseInsetShadowsForMovableObjects : 1;
	int32_t FarShadowCascadeCount;
	float FarShadowDistance;
	float DistanceFieldShadowDistance;
	float LightSourceAngle;
	float LightSourceSoftAngle;
	float ShadowSourceAngleFactor;
	float TraceDistance;
	uint8_t bUsedAsAtmosphereSunLight : 1;
	int32_t AtmosphereSunLightIndex;
	flinearcolor AtmosphereSunDiskColorScale;
	uint8_t bPerPixelAtmosphereTransmittance : 1;
	uint8_t bCastShadowsOnClouds : 1;
	uint8_t bCastShadowsOnAtmosphere : 1;
	uint8_t bCastCloudShadows : 1;
	float CloudShadowStrength;
	float CloudShadowOnAtmosphereStrength;
	float CloudShadowOnSurfaceStrength;
	float CloudShadowDepthBias;
	float CloudShadowExtent;
	float CloudShadowMapResolutionScale;
	float CloudShadowRaySampleCountScale;
	flinearcolor CloudScatteredLuminanceScale;
	uint8_t bCastModulatedShadows : 1;
	float ShadowAmount;
};

class UTextureCube : public utexture
{
public:
	uint8_t                                         Pad_188[0x58];
};

class USkyAtmosphereComponent : public uobject
{
public:
	float BottomRadius;
	float AtmosphereHeight;
	float MultiScatteringFactor;
	float TraceSampleCountScale;
	float RayleighScatteringScale;
	flinearcolor RayleighScattering;
	float RayleighExponentialDistribution;
	float MieScatteringScale;
	flinearcolor MieScattering;
	float MieAbsorptionScale;
	flinearcolor MieAbsorption;
	float MieAnisotropy;
	float MieExponentialDistribution;
	float OtherAbsorptionScale;
	flinearcolor OtherAbsorption;
	flinearcolor SkyLuminanceFactor;
	float AerialPespectiveViewDistanceScale;
	float HeightFogContribution;
	float TransmittanceMinLightElevationAngle;
	float AerialPerspectiveStartDepth;

public:

	flinearcolor GetAtmosphereTransmitanceOnGroundAtPlanetTop(UDirectionalLightComponent* DirectionalLight);

	void OverrideAtmosphereLightDirection(int32_t AtmosphereLightIndex, fvector& LightDirection);

	void SetAerialPespectiveViewDistanceScale(float NewValue);

	void SetAtmosphereHeight(float NewValue);

	void SetHeightFogContribution(float NewValue);

	void SetMieScattering(flinearcolor& NewValue);

	void SetRayleighScattering(flinearcolor& NewValue);

	void SetRayleighExponentialDistribution(float value);

	void SetMieAnisotropy(float value);

	void SetMieExponentialDistribution(float value);

	void SetMultiScatteringFactor(float factor);

	void SetSkyLuminanceFactor(flinearcolor factor);

};

struct ULeaderboardPlayerModel : uobject {
public:
	struct fstring Subject; // 0x30(0x10)
	struct fstring GameName; // 0x40(0x10)
	struct fstring TagLine; // 0x50(0x10)
	struct UPlayerCardDataAsset* PlayerCard; // 0x60(0x08)
	struct UPlayerTitleDataAsset* Title; // 0x68(0x08)
	int32_t RankedRating; // 0x70(0x04)
	int32_t CompetitiveTier; // 0x74(0x04)
	int32_t NumberOfWins; // 0x78(0x04)
	int32_t Rank; // 0x7c(0x04)
	bool IsAnonymized; // 0x80(0x01)
	bool IsBanned; // 0x81(0x01)
	bool IsSeparator; // 0x82(0x01)
	char pad_83[0x5]; // 0x83(0x05)
};

struct ULeaderboardViewModel : uobject {
public:
	char pad_30[0x20]; // 0x30(0x20)
	struct tmap<int32_t, struct ULeaderboardPlayerModel*> Players; // 0x50(0x50)
	struct USeasonDataAsset* season; // 0xa0(0x08)
	struct UCompetitiveSeasonDataAsset* CompetitiveSeason; // 0xa8(0x08)
	int32_t TotalSeparators; // 0x100(0x04)
	int32_t TotalPlayers; // 0x104(0x04)
	char pad_108[0x8];
	bool get_leaderboard_players(int32_t start_index, int32_t end_index, tarray<ULeaderboardPlayerModel*>& out_players);
	// 0x108(0x08)
};

struct FDisplayName final : public uobject
{
public:
	fstring                                 FullName;                                          // 0x0000(0x0010)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	fstring                                 GameName;                                          // 0x0010(0x0010)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	fstring                                 TagLine;                                           // 0x0020(0x0010)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

class UPlatformPlayer final : public uobject
{
public:
	char pad_3C0[0x298];
	bool HideAccountLevel;
	char pad_659[0x3];
	int32_t AccountLevel;
	int32_t CompetitiveTier;
	int32_t LeaderboardPosition;
	char pad_668[0x130];
	struct tarray<struct USubscriptionDataAsset*> ActiveSubscriptions;
	struct UGameFlowStateManager* GameFlowStateManager;
	/*uint8_t                                         Pad_3A0[0x298];
	bool                                          HideAccountLevel;
	uint8_t                                         Pad_639[0x3];
	int32_t                                         AccountLevel;
	int32_t                                         CompetitiveTier;
	int32_t                                         LeaderboardPosition;
	uint8_t                                         Pad_648[0xF8];
	tarray<class USubscriptionDataAsset*>         ActiveSubscriptions;*/
public:
	FDisplayName GetTrueDisplayName();
	/*void DebugSetSeasonBadgeInfo(const struct FMMRSeasonBadgeInfo& NewValue);
	const struct FDisplayName GetDesiredDisplayName();
	const class USubscriptionDataAsset* GetSubscriptionWithHighestPriority();
	bool IsPlayerInRosterParty(const class fstring& RosterID);
	bool PlayerHasAccessToAllAgentsFromSubscription();

	int32_t GetAccountLevel() const;
	int32_t GetCompetitiveTier() const;
	bool GetHasValidPlayerCardID() const;
	bool GetHideAccountLevel() const;
	bool GetIsAnonymous() const;
	bool GetIsInvitable() const;
	bool GetIsKickable() const;
	bool GetIsMe() const;
	bool GetIsOwnerTransferrable() const;
	bool GetIsPartyOwner() const;
	bool GetIsRealPlayer() const;
	bool GetIsValidAresPresence() const;
	int32_t GetLeaderboardPosition() const;
	class ULevelBorderDataAsset* GetLevelBorder() const;
	bool GetLoyaltyStatus() const;
	class fstring GetMatchMap() const;
	EAresPartyAccessibility GetPartyAccessibility() const;
	class fstring GetPartyClientVersion() const;
	class fstring GetPartyID() const;
	class fstring GetPartyOwnerMatchCurrentTeam() const;
	class fstring GetPartyOwnerMatchMap() const;
	EAresPlatformType GetPlatformType() const;
	class UPlayerCardDataAsset* GetPlayerCard() const;
	class UPlayerTitleDataAsset* GetPlayerTitle() const;
	EChatPresenceState GetPresenceState() const;
	EChatPresenceProduct GetProduct() const;
	struct FDateTime GetQueueEntryTime() const;
	class fstring GetQueueID() const;
	const struct FMMRSeasonBadgeInfo GetSeasonBadgeInfo() const;
	class fstring GetSubject() const;
	bool GetTempValueW() const;
	class fstring GetTempValueX() const;
	class fstring GetTempValueY() const;
	bool GetTempValueZ() const;
	struct FTournamentData GetTournamentData() const;
	const struct FDisplayName GetTrueDisplayName() const;
	class fstring GetXboxNetworkAliasSuffix() const;
	bool IsActivePlatformFriend() const;
	bool IsBlocked() const;
	bool IsFriend() const;
	bool IsInvited() const;
	bool IsPlatformBlocked() const;
	bool IsRiotBlocked() const;
	bool IsRiotFriend() const;*/
};

class APerformanceCaptureLocationActor
{
public:
	tarray<fstring> CharacterNames;

};

enum class EChatRoomType : uint8_t
{
	Party = 0,
	Pregame = 1,
	All = 2,
	Team = 3,
	InGameSystem = 4,
	System = 5,
	Whisper = 6,
	Count = 7,
	EChatRoomType_MAX = 8,
};

class ITextChatConversation : public uobject
{
public:
	bool send_message(ftext message);
	EChatRoomType get_conversation_type();
};

// Class ShooterGame.TextChatRoomV2
// Size: 0x1a0 (Inherited: 0x30)
struct UTextChatRoomV2 : public uobject {
	char pad_30[0x8]; // 0x30(0x08)
	char pad_58[0x10]; // 0x58(0x10)
	fstring RoomID; // 0x68(0x10)
	bool bIsRestricted; // 0x78(0x01)
	char pad_79[0x7]; // 0x79(0x07)
	struct UTextChatService* ChatService; // 0x80(0x08)
	struct URSOManager* RSOManager; // 0x88(0x08)
	char pad_90[0x8]; // 0x90(0x08)
	char pad_160[0x40]; // 0x160(0x40)
};

struct UThreadedChatManager : public uobject {
	struct UTextChatService* ChatService; // 0xe0(0x08)
	struct tarray<struct FUnifiedChatMessage> Messages; // 0xe8(0x10)
	UTextChatRoomV2* PartyRoom; // 0x148(0x08)
	UTextChatRoomV2* PregameRoom; // 0x150(0x08)
	UTextChatRoomV2* AllRoom; // 0x158(0x08)
	UTextChatRoomV2* TeamRoom; // 0x160(0x08)
	struct UPartyManager* PartyManager; // 0x168(0x08)
	struct UCoreGameManager* CoreGameManager; // 0x170(0x08)
	struct UPregameManager* PregameManager; // 0x178(0x08)
	struct UWhisperChatManager* WhisperChatManager; // 0x180(0x08)
	struct UMutedPatternsManager* MutedPatternsManager; // 0x188(0x08)
	struct UTextChatManagerV2* TextChatManager; // 0x190(0x08)
	struct UEmojiMapping* EmojiMapping; // 0x198(0x08)
	struct URSOManager* RSOManager; // 0x1a0(0x08)
	char pad_1A8[0x8];
public:
	static UThreadedChatManager* GetThreadedChatManager(uobject* world_context);
	void send_chat_message_v2(EChatRoomType room_type, ftext message);

	static uobject* GetDefaultObj() {
		static uobject* default_obj = uobject::find_object<uobject*>(L"ShooterGame.Default__ThreadedChatManager");
		return default_obj;
	}
	// 0x1a8(0x08)
};

//class platform_player
//{
//public:
//	int get_competitive_tier();
//};

// Class ShooterGame.PingManager
// 0x0130 (0x01B0 - 0x0080)
class UPingManager final : public uobject
{
public:
	uint8_t                                         Pad_80[0x18];                                      // 0x0080(0x0018)(Fixing Size After Last Property [ Dumper-7 ])
	class UPlatformSessionManager* SessionManager;                                    // 0x0098(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	class UPartyManager* PartyManager;                                      // 0x00A0(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	class UPingService* PingService;                                       // 0x00A8(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	class UConfigManager* ConfigManager;                                     // 0x00B0(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	class UObject* Outer_0;                                           // 0x00B8(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	uint8_t                                         Pad_C0[0x8];                                       // 0x00C0(0x0008)(Fixing Size After Last Property [ Dumper-7 ])

	uint8_t                                         Pad_168[0x48];                                     // 0x0168(0x0048)(Fixing Struct Size After Last Property [ Dumper-7 ])

public:
	void process_ping_packet_received(fstring destination, fstring destination_address, int32_t ping_in_millis);
	void request_refresh();
	void update_pings();
};

class player_state : public uobject
{
public:
	fstring get_player_name()
	{
		return memory::read<fstring>(reinterpret_cast<uintptr_t>(this) + offsets::player_name_private);
	}

public:
	int32_t get_player_id()
	{
		return memory::read<int32_t>(reinterpret_cast<uintptr_t>(this) + offsets::get_player_id);
	}

	uint16_t get_ping()
	{
		return memory::read<uint16_t>(reinterpret_cast<uintptr_t>(this) + offsets::get_ping);
	}
};

class ashootercharacter : public uobject
{
public:
	void SetAspectRatio(float InAspectRatio);
	//void get_firing_location_and_direction(fvector* loc, fvector* rot, bool apply_recoil);
	//void get_firing_location_and_direction(fvector* loc, fvector* rot);
	void get_firing_location_and_direction(fvector* loc, fvector* rot, bool apply_recoil);
	void get_firing_location_and_direction2(fvector* loc, FRotator* rot, bool apply_recoil);
	void get_firing_location_and_direction_sd(fvector* Loc, fvector* Rot, bool bApplyRecoil);
	bool can_jump();
	bool can_jump1();
	void ClientFly();
	void GiveUltimate();
	void GameModeCheat(const fstring& CheatString);
	void Heal(int32_t Amount);
	void MoveRight(float Val);
	void ForceStrafe(fvector& PlayerRelativeInputDirection, float ChangeDirectionTime);
	void Hide3P(bool should_hide);
	bool is_input_key_down(fkey key);
	void ShowUI(int32_t Show);
	void ShowUI1(bool Show);
	void ShowUI2(int32_t Show);
	void reset_character_materials_internal(uskeletalmeshcomponent* mesh_to_reset);
	uskeletalmeshcomponent* GetCosmeticMesh3P();
	uskeletalmeshcomponent* get_core_mesh_3p();
	uskeletalmeshcomponent* mesh3p();
	void set_crouch_time_override(float override_value);
	EAresMovementType GetMovementType();
	void set_actor_hidden_in_game(bool new_hidden);
	void flush_net_dormancy();
	void set_movement_mode(EMovementMode NewMode);
	void set_capsule_size(float in_radius, float in_half_height, bool update_overlaps);
	void stop_movement_immediately_mov();
	UPingManager* get_ping_manager();
	void server_set_health(int32_t new_health);
	int32_t get_max_health();
	int32_t GetLocalRole();
	int32_t GetRemoteRole();
	bool IsZoomed();
	bool IsInvisibleToActor(const uobject* Actor);
	bool IsAIControlled();
	bool Is3PCameraEnabled();
	bool GetCrouchHeld(); 
	void crouch(bool bclientsimulation);
	float ReduceShield(float Amount);
	bool GetPlayer(FMMRPlayer* OutPlayer);
	bool GetCompetitiveUpdateForMatch(const fstring& MatchID, FMMRMatchInfo* OutMatchInfo);
	int32_t GetCurrentRank();
	bool IsLeftHanded();
	frotator GetAimOffsets();
	fvector GetSocketLocation(fname InSocketName);
	fvector RandomUnitVectorInConeInDegrees(const fvector& ConeDir, float ConeHalfAngleInDegrees);
	tarray<TWeakObjectPtr<uobject>> GetAllFocusProjectiles();
	fstring GetWwisePerspective();
	bool GetFiringLocationAndDirection(fvector* Location, frotator* Rotation, bool bApplyRecoil);
	EAresMovementType get_movement_type();
	fvector GetPawnViewLocation();
	fvector GetActorForwardVector();
	fvector GetActorRightVector();
	fvector GetActorUpVector();
	bool K2_TeleportTo(const fvector& DestLocation, const frotator& DestRotation);
	void GetActorEyesViewPoint(fvector* OutLocation, frotator* OutRotation);
	fvector GetActorScale3D();
	void SetActorScale3D(const fvector& NewScale3D);
	fvector get_actor_relative_scale3d();
	void set_actor_relative_scale3d(const fvector& new_relative_scale);
	float GetLifeSpan();
	void SetLifeSpan(float InLifespan);
	void set_owner(ashootercharacter* new_owner);
	void apply_glow(ashootercharacter* actor, bool enable);
	bool GetHiddenInGame();
	void DisableInput(aplayercontroller12* PlayerController);
	void EnableInput(aplayercontroller12* PlayerController);
	bool GetActorEnableCollision();
	void SetActorEnableCollision(bool bNewActorEnableCollision);
	uaccountxpmanager* get_account_xp_manager(uworld* world);
	int32_t get_level_max_xp(uaccountxpmanager* xp_manager);
	int32_t get_win_of_day_ap(uaccountxpmanager* xp_manager);
	void set_account_level_cheat(uaccountxpmanager* xp_manager, int32_t level);
	void trigger_refresh_player(uaccountxpmanager* xp_manager);
	bool GetWalkHeld();
	bool GetJumpHeld();
	void ClientCheatFly();
	void ServerCheatFly();
	void SetMovementMode(EMovementMode NewMovementMode, uint8_t NewCustomMode);
	void EnableFly();
	void DisableFly();
	fstring GetPlayerName();
	int32_t GetMatchCombatScore();
	void SwapTeam();
	void ClientPlayAimpunchSimple(UMatineeCameraShake* CameraMod, float ShakeStrength, bool bSharesWeaponShakeCooldown);
	void ClientPlayAimpunch(UMatineeCameraShake* CameraMod, float ShakeStrength, ECameraShakePlaySpace CameraShakePlaySpace, const frotator& UserPlaySpaceRot, bool bSharesWeaponShakeCooldown);
	void apply_no_spread(ashootercharacter* character);
	void set_replicate_movement(bool in_replicate_movement);
	void force_net_update();
	void client_set_location(const fvector& new_location, const frotator& new_rotation);
	static bool line_trace_single(uworld* world_context_object, fvector& start, fvector& end, ETraceTypeQuery trace_channel, bool b_trace_complex, tarray<AActor*>& actors_to_ignore, EDrawDebugTrace draw_debug_type, FHitResult& out_hit, bool b_ignore_self, flinearcolor& trace_color, flinearcolor& trace_hit_color, float draw_time);
	void set_replicates(bool in_replicates);
	ftransform get_transform();
	float k2_get_timer_remaining_time(uobject* object, const fstring& function_name);
	ftimerhandle k2_get_life_span_timer();
	float ReceiveAnyDamage(UDamageType* DamageType, aplayercontroller12* InstigatedBy, ashootercharacter* DamageCauser);
	ashootercharacter* GetShooterCharacterMovement();
	void AddControllerPitchInput(float Val);
	void AddControllerRollInput(float Val);
	void AddControllerYawInput(float Val);
	void GetPlayerViewPoint(fvector* Out_Location, frotator* Out_Rotation);
	fvector GetPlayerViewLocation();
	int32_t GetNumPointsNeededForUltimate();
	bool GetIsAFK();
	int32_t GetMoney();
	float GetTimeUntilRespawn();
	bool IsCoach();
	bool IsUltimateReady();
	void SetOutlineMode(EAresOutlineMode OutlineMode);
	void UpdateOutlineMode();
	void ResetAbilityCooldowns();
	fstring GetShortPlayerName();
	int32_t GetPlayerCompetitiveTier();
	EChatPresenceState GetPresenceState();
	void UnlockFOV();
	tarray<fstring> get_all_morph_target_names();
	void SetDisplayName(const ftext& InDisplayName);
	void SetDisplayName1(const ftext& NewName);
	tarray<fname> GetAllyCharacterNames();
	tarray<fname> GetEnemyCharacterNames();
	float get_time_dilation();
	void set_time_dilation(float multiplier);
	UPlatformPlayer* GetPlatformPlayer1(uobject* socialPlayer);
	UPlatformPlayer* GetPlatformPlayer2(uobject* partyPlayerModel);
	UPlatformPlayer* GetPlatformPlayer3(uobject* pregamePlayerModel);
	bool SendMessage1(const ftext& Message);
	void SetTimeDilation(float Multiplier);
	//int GetPlayerCompetitiveTier();
	int32_t GetNumUltimatePoints();
	void SetFieldOfView(float InFieldOfView);
	bool CanJump();
	bool CanJumpInternal();
	void Jump();
	void OnJump();
	void StopJumping();
	bool HasSpike();
	void teleport_actor(ashootercharacter* actor, const fvector& dest_location, const frotator& dest_rotation);
	void TearOff();
	void UserConstructionScript();
	fvector GetVelocity();
	/*void get_actor_bounds(bool only_colliding_components, fvector* origin, fvector* box_extent, bool include_from_child_actors);
	void auth_set_floor_movement_velocity(const fvector& movement_speed);
	void on_jump(EAresMovementType movement_type);
	void on_landed(ashootercharacter* character, const FHitResult& hit);
	void play_footstep_sound();
	bool is_moving_on_ground();
	bool is_moving();*/
	/*UShooterCharacterFogOfWarComponent* get_shooter_character_fog_of_war();
	void OnTeleported(ashootercharacter* Character);
	void modify_fog_of_war(UShooterCharacterFogOfWarComponent* fog_component);
	fstring get_player_name();
	int32_t get_kills();
	int32_t get_deaths();
	int32_t get_assists();
	float get_kd();*/
	/*UCharacterDataAsset* GetDataAsset();
	UAresInventory* GetInventory();*/
	bool was_input_key_just_pressed(fkey key);
	void simulate_input_key(fkey key, bool pressed);
	void K2_SetActorRelativeRotation(fvector NewRelativeRotation, bool bSweep, bool bTeleport);
	void K2_SetActorRelativeRotation_rota(frotator NewRelativeRotation, bool bSweep, bool bTeleport);
	uskeletalmeshcomponent* get_mesh();
	uskeletalmeshcomponent* GetOverlayMesh1P();
	uskeletalmeshcomponent* GetMesh1P();

	acknowledgedpawn* GetOverlayMesh1P1();

	void Set3pMeshVisible(bool val);

	/*bool can_jump();
	bool can_jump_inter();
	bool jump();
	bool stop_jump();
	bool is_on_ground();*/
	player_state* get_player_state();
	acknowledgedpawn* GetMesh1P1();

	uinventory* get_inventory();
	fvector k2_get_actor_location();
	frotator k2_get_actor_rotation();
	bool k2_set_actor_rotation(frotator& NewRotation, bool bTeleportPhysics);
	void set_rel_actr_root(fvector NewRelativeRotation, bool bSweep, bool bTeleport);
	uobject* get_character_icon();
	//bool gh0st();
	bool is_alive();
	bool was_invisible();
	float health();
	float shield();
	//platform_player* get_plateform_player();
	bool is_dead_and_settled();

public:
	bool bIsFlying = false;
	float lastDamageReceived = 0.0f;
};

class UDamageResponse : public uobject
{
public:
	uint8_t                                         Pad_30[0x8];                                       // 0x0030(0x0008)(Fixing Size After Last Property [ Dumper-7 ])
	AActor* DamagedActor; // 0x38(0x08)
public:
	bool DamageKilledTarget();
	bool DamageWasBlocked();
	acknowledgedpawn* GetDamageCauser();
	acknowledgedpawn* GetDamagedActor();
	float GetDamageDealt();
	fvector GetDamageOrigin();
	float GetDamageTaken();
	currentequippable* GetEquippableUsed();
	acknowledgedpawn* GetEventInstigatorPawn();
};

enum class EAresPlayerViewTargetMode : uint8_t
{
	None = 0,
	WatchPossessed = 1,
	SpectateAllies = 2,
	SpectateEveryone = 4,
	SpectateFreeCam = 8,
	WatchGameStateFocusObject = 16,
	NoValidViewTarget = 32,
	SpectateProjectile = 64,
	WatchSpawned = 128,
	Count = 8,
	All = 255,
	EAresPlayerViewTargetMode_MAX = 256,
};
struct FViewTargetInfo final : public uobject
{
public:
	class ashootercharacter* TargetActor;                                       // 0x0000(0x0008)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	EAresPlayerViewTargetMode                     Mode;                                              // 0x0008(0x0001)(BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_9[0x7];                                        // 0x0009(0x0007)(Fixing Struct Size After Last Property [ Dumper-7 ])
};

struct NoSpread {
	static fvector calc_spread(ashootercharacter* actor, uint64_t firing_state_component, currentequippable* weapon, fvector direction);
};

struct firing_state : public uobject {
public:
	float cooldown() {
		static uobject* function = nullptr;
		if (!function)
			function = uobject::find_object<uobject*>(L"ShooterGame.FiringStateComponent.GetCooldownTimeRemaining");

		if (!function || this == nullptr)
			return 0.f;

		struct { float ret; } params{};
		this->process_event(function, &params);
		return params.ret;
	}
};



class UViewTargetComponent final : public uobject
{
public:
	uint8_t                                         Pad_128[0x40];                                     // 0x0128(0x0040)(Fixing Size After Last Property [ Dumper-7 ])
	bool                                          bTickModeEnabled;                                  // 0x0178(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	bool                                          bRequestedViewTargetUpdate;                        // 0x0179(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	bool                                          bHasViewTargetBeenCameraReady;                     // 0x017A(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	uint8_t                                         Pad_17B[0x1];                                      // 0x017B(0x0001)(Fixing Size After Last Property [ Dumper-7 ])
	EAresPlayerViewTargetMode                     DefaultMode;                                       // 0x017C(0x0001)(Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	uint8_t                                         Pad_17D[0x3];                                      // 0x017D(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	FViewTargetInfo                        ViewTargetInfo;                                    // 0x0180(0x0010)(Net, RepNotify, NoDestructor, NativeAccessSpecifierPrivate)
	ashootercharacter* LocalPlayerViewTarget;                             // 0x0190(0x0008)(ZeroConstructor, Transient, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	ashootercharacter* LastTargetBeforeFreeCam;                           // 0x0198(0x0008)(ZeroConstructor, Transient, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	class UPlayspaceComponent* CachedViewTargetPlayspace;
	ashootercharacter* GetSpectatedSpawnedCharacter();
	ashootercharacter* GetTargetCharacter();
	bool IsInPlayerSpectatingMode();
	bool IsInSpectatorMode();
	bool IsSpectating(ashootercharacter* InActor);
	//bool IsSpectating(AActor* InActor);
	bool IsViewingLocal(ashooterplayerstate* InPlayerState);
};

class UCheatManager : public uobject
{
public:
	class ADebugCameraController* DebugCameraControllerRef;                          // 0x0030(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	tarray<class UCheatManagerExtension*>         CheatManagerExtensions;                            // 0x0080(0x0010)(ZeroConstructor, Transient, Protected, NativeAccessSpecifierProtected)

public:
	void Fly();
	void Ghost();
	void God();
};

enum class EViewTargetBlendFunction : uint8_t
{
	VTBlend_Linear = 0,
	VTBlend_Cubic = 1,
	VTBlend_EaseIn = 2,
	VTBlend_EaseOut = 3,
	VTBlend_EaseInOut = 4,
	VTBlend_PreBlended = 5,
	VTBlend_MAX = 6,
};

struct FViewTargetTransitionParams final
{
public:
	float                                         BlendTime;                                         // 0x0000(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	EViewTargetBlendFunction                      BlendFunction;                                     // 0x0004(0x0001)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_5[0x3];                                        // 0x0005(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         BlendExp;                                          // 0x0008(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         bLockOutgoing : 1;                                 // 0x000C(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         Pad_D[0x3];                                        // 0x000D(0x0003)(Fixing Struct Size After Last Property [ Dumper-7 ])
};

enum class EDynamicForceFeedbackAction : uint8_t
{
	Start = 0,
	Update = 1,
	Stop = 2,
	EDynamicForceFeedbackAction_MAX = 3,
};

struct FLatentActionInfo final
{
public:
	int32_t                                         Linkage;                                           // 0x0000(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32_t                                         UUID;                                              // 0x0004(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	fname                                   ExecutionFunction;                                 // 0x0008(0x000C)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_14[0x4];                                       // 0x0014(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	uobject* CallbackTarget;                                    // 0x0018(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

enum class EAresTeamRole : uint8_t {
	None = 0,
	Attacker = 1,
	Defender = 2,
	FreeForAll = 3,
	Any = 4,
	Role_Count = 5,
	EAresTeamRole_MAX = 6
};

struct AShooterGameMode : uobject {
public:
	struct AOwnerExclusivePlayerInfo* PlayerInfoClass; // 0x4a8(0x08)
	//struct TSet<enum class EGameModeSublevelKey> GameModeSublevelKeys; // 0x4b0(0x50)
	//struct TArray<struct AAresEquippable*> StartingEquippableClasses; // 0x500(0x10)
	//struct TArray<struct TSoftClassPtr<uobject>> DefaultTotemClasses; // 0x510(0x10)
	bool bDisableCharacterMeshTickWhileInFogOfWar; // 0x520(0x01)
	bool bDisableCharacterMeshTickWhileHiddenToHumanPlayers; // 0x521(0x01)
	char pad_522[0x6]; // 0x522(0x06)
	//struct TArray<struct ULevelStreaming*> ClientOnlySublevelsToStream; // 0x528(0x10)
	struct APawn* BotPawnClass; // 0x5f8(0x08)
	//struct TSoftClassPtr<uobject> BotPawnClassAsset; // 0x600(0x30)
	//struct fstring BotControllerClassPath; // 0x630(0x10)
	//struct TSoftClassPtr<uobject> BotControllerClass; // 0x640(0x30)
	//struct TArray<struct FName> AllowedBotDataAssetDeveloperNames; // 0x670(0x10)
	bool bLimitBotCharacterUniquenessToOnlyTeam; // 0x680(0x01)
	char pad_681[0x7]; // 0x681(0x07)
	//struct FMulticastInlineDelegate OnDefaultWeaponChanged; // 0x688(0x10)
	struct UAresGameEventLog* GameEventLog; // 0x698(0x08)
	struct UMatchResultEventCollector* MatchResultEventCollector; // 0x6a0(0x08)
	bool bAlwaysAllowWeaponSelling; // 0x6a8(0x01)
	bool bCarryOverPickedUpEquippablesToNextRound; // 0x6a9(0x01)
	bool bCarryOverAmmoToNextRound; // 0x6aa(0x01)
	char pad_6AB[0x5]; // 0x6ab(0x05)
	struct UAresCeremonyComponent* CeremonyComponent; // 0x6b0(0x08)
	struct UBehaviorScoreTrackerManagerComponent* BehaviorScoreTrackerManagerComponent; // 0x6b8(0x08)
	struct UVoteManagerComponent* VoteManagerComponent; // 0x6c0(0x08)
	struct UAFKDetectionComponent* AFKHandlingType; // 0x6c8(0x08)
	struct UFeedingDetectionComponent* FeedingHandlingType; // 0x6d0(0x08)
	struct UGameModeReplayComponent* ReplayComponent; // 0x6d8(0x08)
	struct UDropInManagerComponent* DropInManagerComponent; // 0x6e0(0x08)
	struct UServerPerRoundTelemetryComponent* ServerPerRoundTelemetryComponent; // 0x6e8(0x08)
	struct UServerMovementTimingComponent* ServerMovementTimingComponent; // 0x6f0(0x08)
	char pad_6F8[0x8]; // 0x6f8(0x08)
	bool bForceBotTargetSite; // 0x700(0x01)
	char pad_701[0x7]; // 0x701(0x07)
	//fstring BotTargetSite; // 0x708(0x10)
	char pad_718[0x4]; // 0x718(0x04)
	int32_t KillScore; // 0x71c(0x04)
	int32_t AssistScore; // 0x720(0x04)
	float DamageSelfScale; // 0x724(0x04)
	float DamageAllyScale; // 0x728(0x04)
	int32_t MaxBots; // 0x72c(0x04)
	//struct TArray<struct AShooterAIController*> BotControllers; // 0x730(0x10)
	struct UStateMachineComponent* StateMachine; // 0x740(0x08)
	struct AAresRespawnManager* RespawnManager; // 0x748(0x08)
	//struct FMatchResults DropOutMatchResults; // 0x750(0x70)
	char pad_7C0[0x10]; // 0x7c0(0x10)
	float GameEventTickRate; // 0x7d0(0x04)
	float MaxRespawnDelay; // 0x7d4(0x04)
	float MaxRespawnDelayTime; // 0x7d8(0x04)
	float MinRespawnDelayValue; // 0x7dc(0x04)
	struct AAresRespawnManager* RespawnManagerClass; // 0x7e0(0x08)
	//struct TSoftClassPtr<uobject> RespawnManagerClassAsset; // 0x7e8(0x30)
	//struct TMap<enum class EAresTeamRole, int32_t> SpawnSetForRole; // 0x818(0x50)
	//struct TArray<struct FAresGameRewardTuning> KillBountyTable; // 0x868(0x10)
	//struct TArray<struct FAresGameRewardTuning> DeathPenaltyTable; // 0x878(0x10)
	char pad_888[0x4]; // 0x888(0x04)
	float GamePhaseStartTime; // 0x88c(0x04)
	struct UFogOfWarManagerComponent* FogOfWarManager; // 0x890(0x08)
	struct UServerTeamVisibilityComponent* ServerTeamVisibilityComponent; // 0x898(0x08)
	char pad_8A0[0x18]; // 0x8a0(0x18)
	struct UMegapacketComponent* MegapacketComponent; // 0x8b8(0x08)
	bool bIsLoadTestEnabled; // 0x8c0(0x01)
	char pad_8C1[0x1]; // 0x8c1(0x01)
	bool bGameplayStartsImmediately; // 0x8c2(0x01)
	bool bDownsampleServerCharacterAnims; // 0x8c3(0x01)
	int32_t ServerAnimUpdateRate; // 0x8c4(0x04)
	float BotNumMovementTicksPerSecond; // 0x8c8(0x04)
	char pad_8CC[0x4]; // 0x8cc(0x04)
	//struct FGameServerInstanceInfo ServerInstanceInfo; // 0x8d0(0xb8)
	//struct FMulticastInlineDelegate OnBuyPhaseUpdated; // 0x988(0x10)
	//struct TArray<struct AShooterCharacter*> RegisteredCharactersNeedingEnemyHitRegInfo; // 0x998(0x10)
	bool bIsFriendlyFireEnabled; // 0x9a8(0x01)
	char pad_9A9[0x3]; // 0x9a9(0x03)
	float MaxSecondsToWaitForInactivePlayers; // 0x9ac(0x04)
	float MaxSecondsToWaitForInactivePlayersNativePlatform; // 0x9b0(0x04)
	bool bIsRoundBeingReset; // 0x9b4(0x01)
	char pad_9B5[0x13]; // 0x9b5(0x13)
	bool bIsChangingRoles; // 0x9c8(0x01)
	char pad_9C9[0x7]; // 0x9c9(0x07)
};

struct alignas(0x04) fcolor final
{
public:
	uint8_t                                         B;
	uint8_t                                         G;
	uint8_t                                         R;
	uint8_t                                         A;
};

// ScriptStruct ShooterGame.AresDebugLineReplicated
// 0x002C (0x002C - 0x0000)
struct FAresDebugLineReplicated final
{
public:
	fvector                                LineStart;                                         // 0x0000(0x000C)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	fvector                                LineEnd;                                           // 0x000C(0x000C)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	fcolor                                 Color;                                             // 0x0018(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                          bPersistentLines;                                  // 0x001C(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_1D[0x3];                                       // 0x001D(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         LifeTime;                                          // 0x0020(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         DepthPriority;                                     // 0x0024(0x0001)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_25[0x3];                                       // 0x0025(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         Thickness;                                         // 0x0028(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Class Engine.HUD
// Size: 0x4b8 (Inherited: 0x3b8)
struct AHUD : public uobject {
public:
	struct APlayerController* PlayerOwner; // 0x3b8(0x08)
	char bLostFocusPaused : 1; // 0x3c0(0x01)
	char bShowHUD : 1; // 0x3c0(0x01)
	char bShowDebugInfo : 1; // 0x3c0(0x01)
	char pad_3C0_3 : 5; // 0x3c0(0x01)
	char pad_3C1[0x3]; // 0x3c1(0x03)
	int32_t CurrentTargetIndex; // 0x3c4(0x04)
	char bShowHitBoxDebugInfo : 1; // 0x3c8(0x01)
	char bShowOverlays : 1; // 0x3c8(0x01)
	char bEnableDebugTextShadow : 1; // 0x3c8(0x01)
	char pad_3C8_3 : 5; // 0x3c8(0x01)
	char pad_3C9[0x7]; // 0x3c9(0x07)
	struct tarray<struct AActor*> PostRenderedActors; // 0x3d0(0x10)
	char pad_3E0[0x8]; // 0x3e0(0x08)
	struct tarray<fname> DebugDisplay; // 0x3e8(0x10)
	struct tarray<fname> ToggledDebugCategories; // 0x3f8(0x10)
	struct tarray<fname> DisabledInstanceNames; // 0x408(0x10)
	struct UCanvas* Canvas; // 0x418(0x08)
	struct UCanvas* DebugCanvas; // 0x420(0x08)
	struct tarray<struct FDebugTextInfo> DebugTextList; // 0x428(0x10)
	struct AActor* ShowDebugTargetDesiredClass; // 0x438(0x08)
	struct AActor* ShowDebugTargetActor; // 0x440(0x08)
	char pad_448[0x70];
public:
	void draw_text(fstring text, flinearcolor color, float x, float y, uobject* font, float scale, bool scale_position);
};

struct USoundBase : uobject {
public:
	char pad_30[0x8];
	struct USoundClass* SoundClassObject;
	char bDebug : 1;
	char bOverrideConcurrency : 1;
	char bEnableBusSends : 1;
	char bEnableBaseSubmix : 1;
	char bEnableSubmixSends : 1;
	char bHasDelayNode : 1;
	char bHasConcatenatorNode : 1;
	char bBypassVolumeScaleForPriority : 1;
	char pad_42[0x56]; // 0x42(0x56)
	float Duration;
	float MaxDistance;
	float TotalSamples;
	float Priority;
	struct USoundAttenuation* AttenuationSettings;
	struct USoundSubmixBase* SoundSubmixObject;
	tarray<struct FSoundSubmixSendInfo> SoundSubmixSends;
	struct USoundEffectSourcePresetChain* SourceEffectChain;
	tarray<struct FSoundSourceBusSendInfo> BusSends;
	tarray<struct FSoundSourceBusSendInfo> PreEffectBusSends;
	tarray<struct UAssetUserData*> AssetUserData;
};

struct USoundWave : USoundBase {
public:
	int32_t CompressionQuality;
	int32_t StreamingPriority;
	char pad_181[0x1];
	char bLooping : 1;
	char bStreaming : 1;
	char bSeekableStreaming : 1;
	char pad_183_3 : 5;
	char pad_185_0 : 6;
	char bMature : 1;
	char bManualWordWrap : 1;
	char bSingleLine : 1;
	char bIsAmbisonics : 1;
	char pad_186_2 : 6;
	char pad_187[0x1];
	tarray<float> FrequenciesToAnalyze;
	tarray<struct FSoundWaveSpectralTimeData> CookedSpectralTimeData;
	tarray<struct FSoundWaveEnvelopeTimeData> CookedEnvelopeTimeData;
	int32_t InitialChunkSize;
	char pad_204[0x44];
	fstring SpokenText;
	float SubtitlePriority;
	float Volume;
	float Pitch;
	int32_t NumChannels;
	int32_t SampleRate;
	char pad_26C[0xc];
	tarray<struct FSubtitleCue> Subtitles;
	struct UCurveTable* Curves;
	struct UCurveTable* InternalCurves;
	char pad_298[0xe8];
};

class aplayercontroller : public uobject
{
public:
	pregame_view_controller* get_pregame_view_controller();
	bool is_input_key_down(fkey key);
	bool dormant_server(ashootercharacter* actor);
	ashootercharacter* get_shooter_character();
	bool line_of_sight(ashootercharacter* other);
	float GetSmokeOverlay();
	void show_colored_muzzle_flashes_for_player(bool bEnable);
	void SetName(fstring& S);
	void SetCinematicMode(bool bInCinematicMode, bool bHidePlayer, bool bAffectsHUD, bool bAffectsMovement, bool bAffectsTurning);
	void client_draw_debug_lines(const tarray<FAresDebugLineReplicated>& debug_lines);
	void setcontrollerlightcolor(const fcolor& color);
	void ServerExec(fstring& Msg);
	void ServerExecRPC(fstring& Msg);
	void Pause();
	void LocalTravel(fstring& URL);
	void K2_ClientPlayForceFeedback(uobject* ForceFeedbackEffect, fname Tag, bool bLooping, bool bIgnoreTimeDilation, bool bPlayWhilePaused);
	void PlayDynamicForceFeedback(float Intensity, float Duration, bool bAffectsLeftLarge, bool bAffectsLeftSmall, bool bAffectsRightLarge, bool bAffectsRightSmall, EDynamicForceFeedbackAction Action, FLatentActionInfo& LatentInfo);
	void ConsoleKey(const fkey& Key);
	void client_message(const fstring& message, const fname& type, float duration);
	void aim_at_character(ashootercharacter* target, const fname& bone_name);
	void unlock_fov();
	float get_player_hfov(const ashootercharacter* viewer);
	float get_fov_angle();
	float get_fov_angle_1p();
	void setbotstospawn(int32_t numbotstospawn);
	void simulate_input_key(fkey key, bool bpressed);
	aplayercontroller* spawnbot(int32_t botnumber, uskeletalmeshcomponent* botmesh, ashootercharacter* commandingcharacter, EAresTeamRole targetrole, bool buseagentasname);
	void SetViewTarget(ashootercharacter* NewViewTarget, FViewTargetTransitionParams& TransitionParams);
	void SetViewTargetWithBlend(ashootercharacter* NewViewTarget, float BlendTime, EViewTargetBlendFunction BlendFunc, float BlendExp, bool bLockOutgoing);
	void ClientSetViewTarget(uobject* A, const FViewTargetTransitionParams& TransitionParams);
	void ServerVerifyViewTarget();
	void ServerViewNextPlayer();
	void ServerViewPrevPlayer();			
	void ServerViewSelf(const FViewTargetTransitionParams& TransitionParams);
	void ClientReturnToMainMenu(const fstring& ReturnReason);
	void ClientReset();
	void ClientRestart(acknowledgedpawn* NewPawn);
	void ClientClearCameraLensEffects();
	void ToggleConsoleCheatsMenu();
	bool ShowBloodForPlayer();
	bool ShowCorpsesForPlayer();
	void ToggleShop();
	void ServerPause();
	void ServerChangeName(fstring& S);
	void ShowCheatMenuCommandFunc();
	void OnShowDeveloperMenu();
	void TogglePause();
	void ClientInternalOnScreenDebugMessage(const fstring& Message, const flinearcolor& Color, float Duration);
	void ClientEndOnlineGame();
	void ClientStartOnlineGame();
	void ClientStartOnlineSession();
	void request_toggle_free_cam();
	bool is_free_cam_enabled();
	void server_toggle_free_cam();
	fvector2d project_world_to_screen(fvector world);
	fvector get_control_rotation();
	frotator get_control_rotation_wp();
	bool project_world_location_to_screen(fvector world_location, fvector2d& screen_location, bool player_viewport_relative);
	void set_control_rotation(fvector angle);
	void set_control_rotation2(frotator angle);
	aplayercameramanager* get_camera_manager();
	void set_fov(float fov); // Corrected declaration
	acknowledgedpawn* get_acknowledged_pawn();
	void ClientFreeCamAtCurrentLocation();
	void ClientTeleportFreeCamToPosition(const fvector& Position, const frotator& Rotation, bool bCheckCollision);
	void ClientUpdateFreeCamPosition(ashootercharacter* ViewTargetToMatch);
	float get_input_axis_value(const fname& input_axis_name);
	void set_control_rotation_rg(frotator angle);
	void set_ignore_look_input(bool bnew_look_input);
	void client_set_hud(uclass* new_hud_class);
	AHUD* get_hud();
	void client_start_camera_shake(uclass* shake_class, float scale, ECameraShakePlaySpace play_space, frotator user_play_space_rot);
	void client_play_sound(USoundBase* sound, float volume_multiplier, float pitch_multiplier);
	void UnPossess();
	void Possess(acknowledgedpawn* InPawn);
	void disconnect_server();
	void HandleThreadedChatManagerSentInGameMessage(const fstring& Msg, int ChatMode);
	void GetInputMouseDelta(float& DeltaX, float& DeltaY);
	float GetMouseSensitivity();
	void ClientSetCameraMode(fname NewCamMode);
	void K2_SetActorRelativeRotation(fvector NewRelativeRotation, bool bSweep, bool bTeleport);
	void SimulateInputKey(fkey Key, bool bPressed);
	bool is_input_key_down(aplayercontroller* controller, const fkey key);
};

namespace skin_changer {
	//void unlock_all_apply(currentequippable* current_equippable, uobject* skin_data_asset, uobject* skin_chroma_asset, int max_level, uobject* world);
	void unlock_all_apply(uobject* world, currentequippable* current_equippable, uobject* skin_data_asset, uobject* skin_chroma_asset, int max_level, uobject* skin_charm_data_asset, int skin_charm_level_data_asset);
	void unlock_all_apply564(currentequippable* current_equippable, uobject* skin_data_asset, uobject* skin_chroma_asset, int max_level, uobject* world);
	void unlock_all_skins(uobject* world);
	//void unlock_all_apply(currentequippable* current_equippable, uobject* skin_data_asset, uobject* skin_chroma_asset, int max_level, uobject* skin_charm_data_asset, int skin_charm_level_data_asset);
	//void apply_weapon_charm(currentequippable* current_equippable, uobject* skin_data_asset, uobject* skin_chroma_asset, int max_level, uobject* skin_charm_data_asset, int skin_charm_level_data_asset);
}


namespace AresOutlineRendering {
	uobject* Static_Class();
	void SetOutlineColorsForRender(uworld* WorldContextObject, flinearcolor AllyColor, flinearcolor EnemyColor);
}


class ucanvas : public uobject {
public:
	fvector2d get_screen_size();

	void k2_drawline(fvector2d screenpos_a, fvector2d screenpos_b, float thickness, flinearcolor color);
	void k2_drawtransparentline(const fvector2d& screen_position_a, const fvector2d& screen_position_b, float thickness, const flinearcolor& render_color);
	void draw_material_on_screen(ucanvas* canvas, umaterialinterface* material, const fvector2d& screen_position, const fvector2d& screen_size);
	void k2_drawtexture(uobject* texture, fvector2d screen_position, fvector2d screen_size, fvector2d coordinate_position, fvector2d coordinate_size, flinearcolor render_color, e_blend_mode blend_mode, float rotation, fvector2d pivot_point);
	void k2_drawpolygon(utexture* render_texture, const fvector2d& screen_position, const fvector2d& radius, int32_t number_of_sides, const flinearcolor& render_color);
	void k2_drawtriangle(utexture* render_texture, const tarray<fcanvasuvtri>& triangles);
	void k2_drawtext(uobject* font, fstring text, fvector2d screenposition, fvector2d scale, flinearcolor color, float kerning, flinearcolor shadowcolor, fvector2d shadowoffset, bool centrex, bool centrey, bool outline, flinearcolor outlinecolor);
	void K2_DrawBox(fvector2d ScreenPosition, fvector2d ScreenSize, float Thickness, flinearcolor RenderColor);
	fvector2d get_string_size(uobject* RenderFont, const wchar_t* RenderText, const fvector2d& Scale);

};
class text : public uobject
{
public:
	static fstring text_to_string(ftext string);
	static ftext string_to_text(const fstring& InString);
	fstring fname_to_string(const fname& name);
};

class blueprints : public uobject
{
public:
	static aplayercontroller* get_player_controller(uobject* context);
	static bool is_colored_muzzle_flash_setting_enabled();
	static aplayercontroller* get_local_controller(uobject* context);
	static tarray<ashootercharacter*> find_all_shooters_with_alliance(uobject* context, ashootercharacter* viewer, earesalliance alliance, bool only_player, bool only_alive);
	static tarray<ashootercharacter*> find_all_game_objects(uworld* world_context);
};

class math : public uobject
{
public:
	static double distance_2d(fvector2d v1, fvector2d v2);
	static float atan(float A);
	static float atan2(float Y, float X);
	static float cos(float A);
	static float sin(float A);
	static float sqrt(float A);
	static fvector find_look_at_rotation(fvector start, fvector end);
	static frotator find_look_at_rotation2(fvector start, fvector target);
	static bool class_is_child_of(uobject* test_class, uobject* parent_class);
	static int32_t random_int(int32_t min, int32_t max);
	static fvector SmoothAim(fvector target, fvector delta_rotation, float smooth);

	static inline fvector vector_to_rotator(fvector direction)
	{
		constexpr float PI_VALUE = 3.14159265358979323846f;

		fvector rot;
		rot.x = -((acosf(direction.z) * 180.0f / PI_VALUE) - 90.0f);
		rot.y = atan2f(direction.y, direction.x) * 180.0f / PI_VALUE;
		rot.z = 0.0f;
		return rot;
	}

};

class game_statics : public uobject
{
public:
	static void get_all_actors_of_class(uobject* context, uobject* _class, tarray<gameobject*>* output);
};

class content_library
{
public:
	static void apply_skin(currentequippable* equippable, uobject* skin_asset, uobject* chroma_asset, int level, uobject* charm_data, int buddie_level);
	static void clear_weapon_components(currentequippable* equippable);
};

class ares_outline : public uobject
{
public:
	static void setoutlinemode(uworld* WorldContextObject, flinearcolor AllyColor, flinearcolor EnemyColor);
	static void setoutlinemode1(uworld* WorldContextObject, flinearcolor EnemyColor);
	static void setoutlinemode3(uobject* WorldContextObject, flinearcolor EnemyColor);
};

namespace basecomponent {
	bool is_ally(ashootercharacter* enemy, ashootercharacter* self);
}

class variables_construct
{
public:
	uobject* blueprints;
	uobject* gameplay_statics;
	uobject* kismet_system;
	uobject* kismet_string;
	uobject* kismet_text;
	uobject* math_system;
	uobject* bobber;
	uobject* rendering_library;
	uobject* content_library;
	uobject* ares_outline_rendering;
	uobject* ares_equippable;
	uobject* ares_instance;
	uobject* base_component;

	
	fkey f1;
	fkey spacebar;
	fkey leftmousebutton;
	fkey n_key;
	fkey left_mouse;

		void init_variables() {

			base_component = uobject::find_object<uobject*>(crypt(L"ShooterGame.Default__BaseTeamComponent"));
			blueprints = uobject::find_object<uobject*>(crypt(L"ShooterGame.Default__ShooterBlueprintLibrary"));
			gameplay_statics = uobject::find_object<uobject*>(crypt(L"Engine.Default__GameplayStatics"));
			kismet_system = uobject::find_object<uobject*>(crypt(L"Engine.Default__KismetSystemLibrary"));
			kismet_string = uobject::find_object<uobject*>(crypt(L"Engine.Default__KismetStringLibrary"));
			rendering_library = uobject::find_object<uobject*>(crypt(L"Engine.Default__KismetRenderingLibrary"));
			kismet_text = uobject::find_object<uobject*>(crypt(L"Engine.Default__KismetTextLibrary"));
			math_system = uobject::find_object<uobject*>(crypt(L"Engine.Default__KismetMathLibrary"));
			bobber = uobject::find_object<uobject*>(crypt(L"Engine.MeshComponent.SetAresOutlineMode"));
			content_library = uobject::find_object<uobject*>(crypt(L"ShooterGame.Default__ContentLibrary"));
			ares_outline_rendering = uobject::find_object<uobject*>(crypt(L"Renderer.Default__AresOutlineRendering"));
			ares_equippable = uobject::find_object<uobject*>(crypt(L"ShooterGame.Default__AresEquippable"));
			ares_instance = uobject::find_object<uobject*>(crypt(L"ShooterGame.Default__AresClientGameInstance"));
		}
	};

class CLSSSK {
public:
	uobject* gameobject = uobject::find_object<uobject*>(crypt(L"ShooterGame.GameObject"));
	uobject* pawn = uobject::find_object<uobject*>(crypt(L"ShooterGame.Pawn"));
	uobject* patch = uobject::find_object<uobject*>(crypt(L"ShooterGame.PatchManager"));
	uobject* projectile = uobject::find_object<uobject*>(crypt(L"ShooterGame.Projectile"));


};


inline variables_construct variables;

class drawings {
public:

	static void draw_rect(fvector2d initial_pos, double w, double h, flinearcolor color, ucanvas* canvas)
	{
		canvas->k2_drawline(initial_pos, { initial_pos.x + w, initial_pos.y }, 1.2, color);
		canvas->k2_drawline(initial_pos, { initial_pos.x, initial_pos.y + h }, 1.2, color);
		canvas->k2_drawline({ initial_pos.x + w, initial_pos.y }, { initial_pos.x + w, initial_pos.y + h }, 1.2, color);
		canvas->k2_drawline({ initial_pos.x, initial_pos.y + h }, { initial_pos.x + w, initial_pos.y + h }, 1.2, color);
	}

	static void draw_vertical_health_bar(aplayercontroller* my_controller, uskeletalmeshcomponent* mesh,
		fvector vHeadBone, fvector vBaseBone, float box_height,
		double health, double shield, flinearcolor health_color, ucanvas* canvas)
	{
		if (!my_controller || !mesh || !canvas) return;

		fvector2d head_pos, base_pos;
		if (!my_controller->project_world_location_to_screen(vHeadBone, head_pos, false) ||
			!my_controller->project_world_location_to_screen(vBaseBone, base_pos, false))
			return;

		float height = fabs(base_pos.y - head_pos.y);
		if (height < 1.10f) return;

		float width = height * 0.65f;

		// DAHA UZUN BAR
		float barThickness = 4.0f; // Biraz daha kalın
		float barOffset = 8.0f; // Daha uzak
		float barExtraHeight = height * 0.1f; // %10 daha uzun

		float barX = head_pos.x + width / 2 + barOffset;
		float barY = head_pos.y - barExtraHeight / 2; // Yukarı uzat
		float totalBarHeight = height + barExtraHeight; // Toplam yükseklik

		float healthHeight = (health / 100.0f) * totalBarHeight;
		healthHeight = Clamp(healthHeight, 0.0f, totalBarHeight);

		float shieldHeight = (shield / 50.0f) * totalBarHeight;
		shieldHeight = Clamp(shieldHeight, 0.0f, totalBarHeight);

		// KOYU RENKLER
		flinearcolor healthColor;
		if (health >= 75) {
			healthColor = flinearcolor(0.0f, 0.6f, 0.0f, 1.0f); // Koyu yeşil
		}
		else if (health >= 44) {
			healthColor = flinearcolor(0.6f, 0.6f, 0.0f, 1.0f); // Koyu sarı
		}
		else {
			healthColor = flinearcolor(0.5f, 0.0f, 0.0f, 1.0f); // Koyu kırmızı
		}

		const flinearcolor shieldColor(0.0f, 0.3f, 0.6f, 1.0f); // Koyu mavi shield
		const flinearcolor outlineColor(0.0f, 0.0f, 0.0f, 0.8f); // Siyah outline

		// HEALTH BAR - TEK TEK ÇİZGİLER
		const int step = 2;
		for (int i = 0; i < healthHeight; i += step) {
			canvas->k2_drawline(
				fvector2d(barX, barY + totalBarHeight - i - 1),
				fvector2d(barX + barThickness, barY + totalBarHeight - i - 1),
				1.0f, healthColor
			);
		}

		// SHIELD BAR - HEALTH'İN ÜSTÜNDE
		if (shield > 0 && shieldHeight > 0) {
			for (int i = 0; i < shieldHeight; i += step) {
				canvas->k2_drawline(
					fvector2d(barX, barY + totalBarHeight - healthHeight - i - 1),
					fvector2d(barX + barThickness, barY + totalBarHeight - healthHeight - i - 1),
					1.0f, shieldColor
				);
			}
		}

		// OUTLINE
		canvas->k2_drawline(fvector2d(barX, barY), fvector2d(barX + barThickness, barY), 1.0f, outlineColor);
		canvas->k2_drawline(fvector2d(barX, barY + totalBarHeight), fvector2d(barX + barThickness, barY + totalBarHeight), 1.0f, outlineColor);
		canvas->k2_drawline(fvector2d(barX, barY), fvector2d(barX, barY + totalBarHeight), 1.0f, outlineColor);
		canvas->k2_drawline(fvector2d(barX + barThickness, barY), fvector2d(barX + barThickness, barY + totalBarHeight), 1.0f, outlineColor);
	}

	static void draw_horizontal_health_bar(aplayercontroller* my_controller, uskeletalmeshcomponent* mesh,
		fvector vHeadBone, fvector vBaseBone, float box_height,
		double health, double shield, flinearcolor health_color, ucanvas* canvas)
	{
		if (!my_controller || !mesh || !canvas) return;

		fvector2d head_pos, base_pos;
		if (!my_controller->project_world_location_to_screen(vHeadBone, head_pos, false) ||
			!my_controller->project_world_location_to_screen(vBaseBone, base_pos, false))
			return;

		float height = fabs(base_pos.y - head_pos.y);
		if (height < 1.10f) return;

		float width = height * 0.75f; // BİRAZ DAHA UZUN

		// DAHA İNCE BAR
		float barHeight = 3.0f; // 4'ten 3'e incelt
		float barOffset = 6.0f;

		float barStartX = head_pos.x - width / 2;
		float barY = head_pos.y + height + barOffset;

		float healthWidth = (health / 100.0f) * width;
		healthWidth = Clamp(healthWidth, 0.0f, width);

		float shieldWidth = (shield / 50.0f) * width;
		shieldWidth = Clamp(shieldWidth, 0.0f, width);

		// DAHA CANLI YEŞİL VE RENKLER
		flinearcolor healthColor;
		if (health >= 75) {
			healthColor = flinearcolor(0.2f, 1.0f, 0.2f, 1.0f); // DAHA CANLI YEŞİL
		}
		else if (health >= 44) {
			healthColor = flinearcolor(1.0f, 0.9f, 0.2f, 1.0f); // CANLI SARI
		}
		else {
			healthColor = flinearcolor(1.0f, 0.3f, 0.2f, 1.0f); // CANLI KIRMIZI
		}

		const flinearcolor shieldColor(0.0f, 0.0f, 0.0f, 1.0f); // SİYAH SHIELD
		const flinearcolor outlineColor(0.0f, 0.0f, 0.0f, 0.9f);

		// HEALTH BAR
		const int step = 2;
		for (int i = 0; i < healthWidth; i += step) {
			canvas->k2_drawline(
				fvector2d(barStartX + i, barY),
				fvector2d(barStartX + i, barY + barHeight),
				1.0f, healthColor
			);
		}

		// SHIELD BAR - SİYAH
		if (shield > 0 && shieldWidth > 0) {
			float shieldY = barY + barHeight + 1.0f;

			for (int i = 0; i < shieldWidth; i += step) {
				canvas->k2_drawline(
					fvector2d(barStartX + i, shieldY),
					fvector2d(barStartX + i, shieldY + barHeight),
					1.0f, shieldColor
				);
			}

			// SHIELD OUTLINE
			canvas->k2_drawline(fvector2d(barStartX, shieldY), fvector2d(barStartX + width, shieldY), 1.0f, outlineColor);
			canvas->k2_drawline(fvector2d(barStartX, shieldY + barHeight), fvector2d(barStartX + width, shieldY + barHeight), 1.0f, outlineColor);
			canvas->k2_drawline(fvector2d(barStartX, shieldY), fvector2d(barStartX, shieldY + barHeight), 1.0f, outlineColor);
			canvas->k2_drawline(fvector2d(barStartX + width, shieldY), fvector2d(barStartX + width, shieldY + barHeight), 1.0f, outlineColor);
		}

		// HEALTH OUTLINE
		canvas->k2_drawline(fvector2d(barStartX, barY), fvector2d(barStartX + width, barY), 1.0f, outlineColor);
		canvas->k2_drawline(fvector2d(barStartX, barY + barHeight), fvector2d(barStartX + width, barY + barHeight), 1.0f, outlineColor);
		canvas->k2_drawline(fvector2d(barStartX, barY), fvector2d(barStartX, barY + barHeight), 1.0f, outlineColor);
		canvas->k2_drawline(fvector2d(barStartX + width, barY), fvector2d(barStartX + width, barY + barHeight), 1.0f, outlineColor);
	}

	static void draw_health_text(aplayercontroller* controller, uskeletalmeshcomponent* mesh,
		double health, double shield, ucanvas* canvas, uobject* font)
	{
		if (!controller || !mesh || !canvas) return;

		float total_health = health + shield;
		wchar_t health_text[256];
		swprintf_s(health_text, L"%.0f", total_health); // Sadece sayı, daha profesyonel

		fvector head = mesh->get_bone_location(8);
		fvector base = mesh->get_bone_location(0);

		fvector2d head_pos, base_pos;
		if (controller->project_world_location_to_screen(head, head_pos, false) &&
			controller->project_world_location_to_screen(base, base_pos, false)) {

			float height = fabs(base_pos.y - head_pos.y);
			float textY = head_pos.y + height + 12; // Daha yakın

			fvector2d text_pos = { head_pos.x, textY };

			// Koyu beyaz ve outline'li
			flinearcolor text_color = { 0.9f, 0.9f, 0.9f, 1.0f }; // Koyu beyaz
			flinearcolor outline_color = { 0.0f, 0.0f, 0.0f, 0.8f }; // Siyah outline

			// Daha küçük ve profesyonel
			canvas->k2_drawtext(
				font,
				health_text,
				text_pos,
				{ 0.65f, 0.65f }, // Daha küçük scale
				text_color,
				0.f,
				{ 0, 0, 0, 0.0f }, // Shadow'u kaldırdık
				{ 0, 0 },
				true, // Center X
				false, // Center Y değil
				true, // Outline açık
				outline_color // Siyah outline
			);
		}
	}

	static void drawcorner(aplayercontroller* my_controller,
		uskeletalmeshcomponent* mesh,
		fvector vHeadBone,
		fvector vBaseBone,
		flinearcolor unused_color,
		ucanvas* canvas)
	{
		if (!my_controller || !mesh || !canvas) return;
		if (!vHeadBone.is_valid() || !vBaseBone.is_valid()) return;

		flinearcolor cornerColor = flinearcolor(1.f, 0.f, 0.f, 1.f); 

			
		std::array<fvector, 8> worldCorners = {
			fvector(vBaseBone.x + 53, vBaseBone.y - 55, vBaseBone.z),
			fvector(vBaseBone.x - 53, vBaseBone.y - 55, vBaseBone.z),
			fvector(vBaseBone.x - 53, vBaseBone.y + 55, vBaseBone.z),
			fvector(vBaseBone.x + 53, vBaseBone.y + 55, vBaseBone.z),
			fvector(vHeadBone.x + 53, vHeadBone.y - 55, vHeadBone.z + 26),
			fvector(vHeadBone.x - 53, vHeadBone.y - 55, vHeadBone.z + 26),
			fvector(vHeadBone.x - 53, vHeadBone.y + 55, vHeadBone.z + 26),
			fvector(vHeadBone.x + 53, vHeadBone.y + 55, vHeadBone.z + 26)
		};

		std::array<fvector2d, 8> screenPts;
		for (size_t i = 0; i < worldCorners.size(); ++i) {
			bool ok = my_controller->project_world_location_to_screen(worldCorners[i], screenPts[i], 0);
			if (!ok || !screenPts[i].is_valid() ||
				!std::isfinite(screenPts[i].x) || !std::isfinite(screenPts[i].y))
				return;
		}

		const float COORD_LIMIT = 100000.f;
		for (const auto& p : screenPts) {
			if (std::fabs(p.x) > COORD_LIMIT || std::fabs(p.y) > COORD_LIMIT) return;
		}

		
		const float cornerLen = 15.f;

		auto drawCorner = [&](const fvector2d& p1, const fvector2d& p2) {
			fvector2d dir = { p2.x - p1.x, p2.y - p1.y };
			float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
			if (len < 0.001f) return;
			dir.x /= len; dir.y /= len;

			fvector2d end = { p1.x + dir.x * cornerLen, p1.y + dir.y * cornerLen };
			canvas->k2_drawline({ p1.x, p1.y }, { end.x, end.y }, 1.6f, cornerColor);
			};

		
		for (int i = 0; i < 4; ++i) {
			const fvector2d& p1 = screenPts[i];
			const fvector2d& p2 = screenPts[(i + 1) % 4];
			drawCorner(p1, p2);
			drawCorner(p2, p1);
		}

		
		for (int i = 4; i < 8; ++i) {
			const fvector2d& p1 = screenPts[i];
			const fvector2d& p2 = screenPts[(i == 7) ? 4 : i + 1];
			drawCorner(p1, p2);
			drawCorner(p2, p1);
		}

		
		for (int i = 0; i < 4; ++i) {
			drawCorner(screenPts[i], screenPts[i + 4]);
			drawCorner(screenPts[i + 4], screenPts[i]);
		}
	}


	static void draw_3d(aplayercontroller* my_controller,
		uskeletalmeshcomponent* mesh,
		fvector vHeadBone,
		fvector vBaseBone,
		flinearcolor box_color, 
		ucanvas* canvas)
	{
		if (!my_controller || !mesh || !canvas) return;
		if (!vHeadBone.is_valid() || !vBaseBone.is_valid()) return;

		std::array<fvector, 8> worldCorners = {
			fvector(vBaseBone.x + 53, vBaseBone.y - 55, vBaseBone.z),
			fvector(vBaseBone.x - 53, vBaseBone.y - 55, vBaseBone.z),
			fvector(vBaseBone.x - 53, vBaseBone.y + 55, vBaseBone.z),
			fvector(vBaseBone.x + 53, vBaseBone.y + 55, vBaseBone.z),
			fvector(vHeadBone.x + 53, vHeadBone.y - 55, vHeadBone.z + 26),
			fvector(vHeadBone.x - 53, vHeadBone.y - 55, vHeadBone.z + 26),
			fvector(vHeadBone.x - 53, vHeadBone.y + 55, vHeadBone.z + 26),
			fvector(vHeadBone.x + 53, vHeadBone.y + 55, vHeadBone.z + 26)
		};

		std::array<fvector2d, 8> screenPts;
		for (size_t i = 0; i < worldCorners.size(); ++i) {
			bool ok = my_controller->project_world_location_to_screen(worldCorners[i], screenPts[i], 0);
			if (!ok || !screenPts[i].is_valid() || !std::isfinite(screenPts[i].x) || !std::isfinite(screenPts[i].y))
				return;
		}

		const float COORD_LIMIT = 100000.f;
		for (const auto& p : screenPts) {
			if (std::fabs(p.x) > COORD_LIMIT || std::fabs(p.y) > COORD_LIMIT) return;
		}

		
		for (int i = 0; i < 4; ++i) {
			canvas->k2_drawline({ screenPts[i].x, screenPts[i].y },
				{ screenPts[i + 4].x, screenPts[i + 4].y },
				1.35f, box_color);
		}

		
		for (int i = 0; i < 4; ++i) {
			const fvector2d& p1 = screenPts[i];
			const fvector2d& p2 = screenPts[(i + 1) % 4];
			canvas->k2_drawline({ p1.x, p1.y }, { p2.x, p2.y }, 1.35f, box_color);
		}

		
		for (int i = 4; i < 8; ++i) {
			const fvector2d& p1 = screenPts[i];
			const fvector2d& p2 = screenPts[(i == 7) ? 4 : i + 1];
			canvas->k2_drawline({ p1.x, p1.y }, { p2.x, p2.y }, 1.35f, box_color);
		}
	}


	static void draw_2d_box(aplayercontroller* my_controller, uskeletalmeshcomponent* mesh,
		fvector vHeadBone, fvector vBaseBone, flinearcolor box_color, ucanvas* canvas)
	{
		if (!my_controller || !canvas || !mesh)
			return;

		fvector2d head_pos, base_pos;
		if (!my_controller->project_world_location_to_screen(vHeadBone, head_pos, false) ||
			!my_controller->project_world_location_to_screen(vBaseBone, base_pos, false))
			return;

		float height = fabs(base_pos.y - head_pos.y);
		if (height < 1.10f) return;

		float width = height * 0.65f;
		float vertical_scale = 1.2f; 
		float vertical_offset_top = height * (vertical_scale - 1.0f) * 0.7f; 
		float vertical_offset_bottom = height * (vertical_scale - 1.0f) * 0.3f;

		float centerX = (head_pos.x + base_pos.x) / 2.0f;
		float topY = min(head_pos.y, base_pos.y) - vertical_offset_top; 
		float bottomY = max(head_pos.y, base_pos.y) + vertical_offset_bottom;

		fvector2d top_left(centerX - width / 2, topY);
		fvector2d box_size(width, bottomY - topY);

		flinearcolor outlineColor = box_color;
		outlineColor.a = 1.0f;

		canvas->K2_DrawBox(top_left, box_size, 1.5f, outlineColor);
	}



	static void partyhat(aplayercontroller* my_controller, uskeletalmeshcomponent* mesh, fvector head, fvector base, ucanvas* canvas)
	{
		if (!canvas || !my_controller)
			return;

		fvector tip = { head.x, head.y, head.z + 20.0f }; 
		fvector2d screen_tip;

		if (!my_controller->project_world_location_to_screen(tip, screen_tip, false))
			return;

		tarray<fvector2d> base_points_2d;

		
		static float total_time = 0.0f;
		total_time += 0.016f; 
		float time = total_time;

		float rotation_speed = 1.5f;
		float rotation = time * rotation_speed;

		float radius = 30.0f;
		int segments = 16;

		for (int i = 0; i < segments; ++i)
		{
			float angle = (2.0f * 3.14159265358979323846f / segments) * i + rotation;
			float x = cosf(angle) * radius;
			float y = sinf(angle) * radius;

			fvector base_point_3d = { head.x + x, head.y + y, head.z + 5.0f };
			fvector2d screen_base;

			if (my_controller->project_world_location_to_screen(base_point_3d, screen_base, false))
			{
				base_points_2d.add(screen_base);
			}
		}

		if (base_points_2d.size() < 2)
			return;

		float thickness = 1.0f;
		float outline_thickness = thickness + 1.8f;
		bool bOutline = false;

		
		for (int i = 0; i < base_points_2d.size(); ++i)
		{
			int next = (i + 1) % base_points_2d.size();

			
			float r = (sinf(time * 2.0f + i * 0.3f) + 1.0f) * 0.5f;
			float g = (sinf(time * 2.0f + i * 0.3f + 2.0f) + 1.0f) * 0.5f;
			float b = (sinf(time * 2.0f + i * 0.3f + 4.0f) + 1.0f) * 0.5f;
			flinearcolor rainbow_color = { r, g, b, 0.8f }; 

		
			for (float t = 0.0f; t <= 1.0f; t += 0.1f) {
				fvector2d interpolated_point = {
					screen_tip.x + (base_points_2d[i].x - screen_tip.x) * t,
					screen_tip.y + (base_points_2d[i].y - screen_tip.y) * t
				};

				fvector2d interpolated_next = {
					screen_tip.x + (base_points_2d[next].x - screen_tip.x) * t,
					screen_tip.y + (base_points_2d[next].y - screen_tip.y) * t
				};

				canvas->k2_drawline(interpolated_point, interpolated_next, 2.0f, rainbow_color);
			}

			
			canvas->k2_drawline(screen_tip, base_points_2d[i], 2.0f, rainbow_color);
			canvas->k2_drawline(base_points_2d[i], base_points_2d[next], 2.0f, rainbow_color);
			canvas->k2_drawline(base_points_2d[next], screen_tip, 2.0f, rainbow_color);
		}

	
		for (int i = 0; i < base_points_2d.size(); ++i)
		{
			int next = (i + 1) % base_points_2d.size();

		
			float r = (sinf(time * 2.0f + i * 0.3f) + 1.0f) * 0.5f;
			float g = (sinf(time * 2.0f + i * 0.3f + 2.0f) + 1.0f) * 0.5f;
			float b = (sinf(time * 2.0f + i * 0.3f + 4.0f) + 1.0f) * 0.5f;
			flinearcolor rainbow_color = { r, g, b, 1.0f }; 

		
			canvas->k2_drawline(screen_tip, base_points_2d[i], 3.0f, rainbow_color);
			canvas->k2_drawline(base_points_2d[i], base_points_2d[next], 3.0f, rainbow_color);
		}
	}

	static void head_box(fvector2d position, float width, float height, flinearcolor color, ucanvas* canvas)
	{
		float X = position.x - (width / 2);
		float Y = position.y;
		float lineW = (width / 3);
		float lineH = (height / 3);

		canvas->k2_drawline(fvector2d(X, Y), fvector2d(X, Y + lineH), 1.5f, color);
		canvas->k2_drawline(fvector2d(X, Y), fvector2d(X + lineW, Y), 1.5f, color);
		canvas->k2_drawline(fvector2d(X + width - lineW, Y), fvector2d(X + width, Y), 1.5f, color);
		canvas->k2_drawline(fvector2d(X + width, Y), fvector2d(X + width, Y + lineH), 1.5f, color);
		canvas->k2_drawline(fvector2d(X, Y + height - lineH), fvector2d(X, Y + height), 1.5f, color);
		canvas->k2_drawline(fvector2d(X, Y + height), fvector2d(X + lineW, Y + height), 1.5f, color);
		canvas->k2_drawline(fvector2d(X + width - lineW, Y + height), fvector2d(X + width, Y + height), 1.5f, color);
		canvas->k2_drawline(fvector2d(X + width, Y + height - lineH), fvector2d(X + width, Y + height), 1.5f, color);
	}

	static void head_circle(fvector2d position, float width, float height, flinearcolor color, ucanvas* canvas)
	{
		const float centerX = position.x;
		const float centerY = position.y + (height / 2);
		const float radiusX = width / 2;
		const float radiusY = height / 2;

		const int numSegments = 32;
		const float angleIncrement = 2 * 3.14159265358979323846f / numSegments;

		
		float angle = 0.0f;
		float cosAngle = cos(angle);
		float sinAngle = sin(angle);
		fvector2d prevPoint(
			centerX + radiusX * cosAngle,
			centerY + radiusY * sinAngle
		);

		for (int i = 1; i <= numSegments; ++i)
		{
			angle += angleIncrement;
			cosAngle = cos(angle);
			sinAngle = sin(angle);

			fvector2d nextPoint(
				centerX + radiusX * cosAngle,
				centerY + radiusY * sinAngle
			);

			canvas->k2_drawline(prevPoint, nextPoint, 1.5f, color);

			prevPoint = nextPoint;
		}
	}

	static void agent_icon(ashootercharacter* actor, fvector2d base_out, float distance, ucanvas* canvas) {

		uobject* icon = actor->get_character_icon();

		
		if (!icon || !canvas || distance <= 0.0f)
			return;

		
		fvector2d baseSize = fvector2d(8.5f, 8.5f);
		float scaleFactor = 100.0f / distance;  

		fvector2d newSize = baseSize * scaleFactor;

		
		if (newSize.x <= 0.0f || newSize.y <= 0.0f)
			return;

		
		canvas->k2_drawtexture(icon, base_out, newSize,
			fvector2d(0.0f, 0.0f),
			fvector2d(1.0f, 1.0f),
			flinearcolor(1, 1, 1, 1), e_blend_mode::opaque, 0.0f, fvector2d(0.5f, 0.5f));
	}


	static void draw_skeleton(aplayercontroller* my_controller, uskeletalmeshcomponent* mesh, int bone_count, flinearcolor color, ucanvas* canvas)
	{
		if (!my_controller || !mesh || !canvas)
			return;

		struct BoneIDs {
			int hip, neck, upperArmLeft, leftHand, leftHand1, upperArmRight, rightHand, rightHand1;
			int leftThigh, leftCalf, leftFoot, rightThigh, rightCalf, rightFoot;
			int head;
		};

		BoneIDs boneIDs;

		switch (bone_count)
		{
		case 101:
			boneIDs = { 3, 21, 23, 24, 25, 49, 50, 51, 75, 76, 78, 82, 83, 85, 20 };
			break;
		case 103:
			boneIDs = { 3, 9, 33, 30, 32, 58, 55, 57, 63, 65, 69, 77, 79, 83, 8 };
			break;
		case 104:
			boneIDs = { 3, 21, 23, 24, 25, 49, 50, 51, 77, 78, 80, 84, 85, 87, 20 };
			break;
		default:
			return;
		}

		auto ProjectAndCheck = [&](int boneIndex, fvector2d& out) -> bool {
			fvector worldLocation = mesh->get_bone_location(boneIndex);
			if (!worldLocation.is_valid()) return false;
			return my_controller->project_world_location_to_screen(worldLocation, out, false) && out.is_valid();
			};

		fvector2d vHipOut, vNeckOut, vUpperArmLeftOut, vLeftHandOut, vLeftHandOut1;
		fvector2d vUpperArmRightOut, vRightHandOut, vRightHandOut1;
		fvector2d vLeftThighOut, vLeftCalfOut, vLeftFootOut;
		fvector2d vRightThighOut, vRightCalfOut, vRightFootOut;
		fvector2d vHeadOut;

		bool bValidProjection =
			ProjectAndCheck(boneIDs.hip, vHipOut) &&
			ProjectAndCheck(boneIDs.neck, vNeckOut) &&
			ProjectAndCheck(boneIDs.upperArmLeft, vUpperArmLeftOut) &&
			ProjectAndCheck(boneIDs.leftHand, vLeftHandOut) &&
			ProjectAndCheck(boneIDs.leftHand1, vLeftHandOut1) &&
			ProjectAndCheck(boneIDs.upperArmRight, vUpperArmRightOut) &&
			ProjectAndCheck(boneIDs.rightHand, vRightHandOut) &&
			ProjectAndCheck(boneIDs.rightHand1, vRightHandOut1) &&
			ProjectAndCheck(boneIDs.leftThigh, vLeftThighOut) &&
			ProjectAndCheck(boneIDs.leftCalf, vLeftCalfOut) &&
			ProjectAndCheck(boneIDs.leftFoot, vLeftFootOut) &&
			ProjectAndCheck(boneIDs.rightThigh, vRightThighOut) &&
			ProjectAndCheck(boneIDs.rightCalf, vRightCalfOut) &&
			ProjectAndCheck(boneIDs.rightFoot, vRightFootOut) &&
			ProjectAndCheck(boneIDs.head, vHeadOut);

		if (bValidProjection)
		{
			float thickness = 1.2f; // İnce ve temiz

			// Gövde
			canvas->k2_drawline(vHipOut, vNeckOut, thickness, color);
			canvas->k2_drawline(vNeckOut, vHeadOut, thickness, color);

			// Kollar
			canvas->k2_drawline(vUpperArmLeftOut, vNeckOut, thickness, color);
			canvas->k2_drawline(vUpperArmRightOut, vNeckOut, thickness, color);
			canvas->k2_drawline(vLeftHandOut, vUpperArmLeftOut, thickness, color);
			canvas->k2_drawline(vRightHandOut, vUpperArmRightOut, thickness, color);
			canvas->k2_drawline(vLeftHandOut, vLeftHandOut1, thickness, color);
			canvas->k2_drawline(vRightHandOut, vRightHandOut1, thickness, color);

			// Bacaklar
			canvas->k2_drawline(vLeftThighOut, vHipOut, thickness, color);
			canvas->k2_drawline(vRightThighOut, vHipOut, thickness, color);
			canvas->k2_drawline(vLeftCalfOut, vLeftThighOut, thickness, color);
			canvas->k2_drawline(vRightCalfOut, vRightThighOut, thickness, color);
			canvas->k2_drawline(vLeftFootOut, vLeftCalfOut, thickness, color);
			canvas->k2_drawline(vRightFootOut, vRightCalfOut, thickness, color);
		}
	}


	template <typename T>
	T static Clamp(T value, T min_value, T max_value) {
		return (value < min_value) ? min_value : (value > max_value) ? max_value : value;
	}


	static void draw_snapline(ashootercharacter* shooter_character, fvector2d head_out, flinearcolor color, ucanvas* canvas) {
		double radius = 58.0;
		double screen_center_x = (double)canvas->get_screen_size().x / 2;
		double screen_center_y = (double)canvas->get_screen_size().y / 2;

		double a = head_out.y - screen_center_y;
		double b = head_out.x - screen_center_x;

		if (b == 0)
			b = 0.0001;	

		double angle = atan(a / b);
		double x3, y3;

		if (b > 0) {
			x3 = radius * cos(angle) + screen_center_x;
			y3 = radius * sin(angle) + screen_center_y;
		}
		else {
			x3 = radius * (-cos(angle)) + screen_center_x;
			y3 = radius * (-sin(angle)) + screen_center_y;
		}

		if (sqrt(a * a + b * b) >= radius) {
			canvas->k2_drawline(fvector2d(head_out.x, head_out.y), fvector2d(x3, y3), 1.0, color);
		}
	}

	static inline const flinearcolor default_color = { 1.0f, 1.0f, 1.0f, 1.0f };

	static inline double rainbowTime2 = 0.0;
	static inline const double rainbowSpeed = 0.001;
	static inline const double rainbowFrequency = 0.33;

	static inline const double PI2 = 6.28318530718;

	static flinearcolor calculate_smooth_rainbow(double t) {
		float r = 0.5f + 0.5f * sinf(t * PI2);
		float g = 0.5f + 0.5f * sinf((t + 0.333) * PI2);
		float b = 0.5f + 0.5f * sinf((t + 0.666) * PI2);
		return { r, g, b, 1.0f };
	}

	static flinearcolor get_color(bool use_rainbow, const flinearcolor& default_color) {
		if (use_rainbow) {
			return calculate_smooth_rainbow(rainbowTime2);
		}
		return default_color;
	}

	static void draw_f0v(fvector2d pos, double radius, int numSegments, flinearcolor color, ucanvas* canvas)
	{

		if (globals::aimbot::draw_f0v) {
			const double PI = 3.1415927;

			double Step = PI * 2.0 / numSegments;
			fvector2d V[128];

			for (int i = 0; i < numSegments; i++) {
				double Angle = i * Step;
				double X = radius * cos(Angle) + pos.x;
				double Y = radius * sin(Angle) + pos.y;

				V[i].x = X;
				V[i].y = Y;
			}

			for (int i = 0; i < numSegments - 1; i++) {
				canvas->k2_drawline(fvector2d{ V[i].x, V[i].y }, fvector2d{ V[i + 1].x, V[i + 1].y }, 1.0, color);
			}

			canvas->k2_drawline(fvector2d{ V[numSegments - 1].x, V[numSegments - 1].y }, fvector2d{ V[0].x, V[0].y }, 1.0, color);
		}

	}

};

struct AGameObject : public uobject {
	char pad_0[0x4a0];
	fvector GetObjectLocation();
	float GetObjectHealth();
};
namespace GameplayStatics {
	uobject* GameplayStatics();
	template<typename type>
	static inline tarray<type*> GetAllActorsOfClass(uworld* world_context, uobject* actor_class) {
		uobject* function = uobject::find_object<uobject*>(crypt(L"Engine.GameplayStatics.GetAllActorsOfClass"));
		struct {
			uworld* world_context;
			uobject* actor_class;
			tarray<type*> return_value;
		} params = { world_context, actor_class };

		GameplayStatics()->process_event(function, &params);
		return params.return_value;
	}

	static inline void GetAllActorsOfClass2(uworld* WorldContextObject, uobject* ActorClass, tarray<AGameObject*>* OutActors)
	{
		static uobject* function;
		if (!function)
			function = uobject::find_object<uobject*>(L"GameplayStatics.GetAllActorsOfClass");

		struct
		{
			uworld* WorldContextObject;
			uobject* ActorClass;
			tarray<AGameObject*> OutActors;
		} params;

		params.WorldContextObject = WorldContextObject;
		params.ActorClass = ActorClass;

		GameplayStatics()->process_event(function, &params);

		if (OutActors)
			*OutActors = params.OutActors;
	}
}

namespace Class {
	uobject* ShooterGameObject();

	static inline uobject* Actors()
	{
		static uobject* function;
		if (!function)
			function = uobject::find_object<uobject*>(L"Engine.Actor");

		return function;
	}

}

namespace keys
{
	static fkey space;
	static fkey left_mouse;
}

namespace Variables
{
	static int LastBulletIndexPushed = 0;
	static fvector Last5BulletImpacts[5];
	static fvector Last5BulletImpactsMuzzle[5];

	static fvector BulletTeleportHead = fvector();

	namespace GetDamageStartLocation
	{
		static bool bSilentAimActive = false;
		static fvector SilentLocationTarget = fvector();
		static frotator LastTargetRotation = frotator();
	}

	namespace GetTargetingTransform
	{
		static bool bPickaxeRangeActive = false;
		static bool bShouldStartAtLocationTarget = true;
		static fvector LocationTarget = fvector();
	}

	namespace GetPlayerViewPoint
	{
		static bool bShouldStartAtLocationTarget = true;
		static fvector SilentLocationTarget = fvector();
		static frotator LastTargetRotation = frotator();
		static fvector OriginalLocation = fvector();
		static frotator OriginalRotation = frotator();
	}
	namespace GetCameraViewPoint
	{
		static bool bFreecamActive = false;

		static frotator LastStickyRotation = frotator();
		static fvector StickyLocation = fvector();
		static fvector CachedFreecamLocation = fvector();
	}
}

struct AProjectile : uobject {
	char pad_3B8[0x8]; // 0x3b8(0x08)
	//struct FMulticastInlineDelegate OnTeleported; // 0x3c0(0x10)
	bool bIsDisarmed; // 0x3d0(0x01)
	char pad_3D1[0x7]; // 0x3d1(0x07)
	char pad_418[0x30]; // 0x418(0x30)
	bool bShouldAlwaysCollideWithAllies; // 0x458(0x01)
	bool bIgnoreFriendlyFireModifiers; // 0x459(0x01)
	bool bSimulation; // 0x45a(0x01)
	bool bIsReusable; // 0x45b(0x01)
	bool bUseProjectilePooling; // 0x45c(0x01)
	bool bIsCleanedUpForReuse; // 0x45d(0x01)
	bool bIsBeingReused; // 0x45e(0x01)
	char pad_45F[0x1]; // 0x45f(0x01)
	float InitializedForUseTimestamp; // 0x460(0x04)
	float SpeedScale; // 0x464(0x04)
	float DefaultDestroyDelay; // 0x468(0x04)
	char pad_46E[0x2]; // 0x46e(0x02)
	float DestroyDelay; // 0x470(0x04)
	char pad_474[0xc]; // 0x474(0x0c)
	int32_t CreationRandomSeed; // 0x490(0x04)
	char pad_495[0xb]; // 0x495(0x0b)
	bool bNormalizeImpartedVelocity; // 0x4e8(0x01)
	char pad_4E9[0x7]; // 0x4e9(0x07)
};

// Class Engine.ProjectileMovementComponent
// 0x00E8 (0x0210 - 0x0128)
class alignas(0x10) UProjectileMovementComponent final : public uobject
{
public:
	float                                         InitialSpeed;                                      // 0x0128(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         MaxSpeed;                                          // 0x012C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         bRotationFollowsVelocity : 1;                      // 0x0130(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bRotationRemainsVertical : 1;                      // 0x0130(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bShouldBounce : 1;                                 // 0x0130(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bInitialVelocityInLocalSpace : 1;                  // 0x0130(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bForceSubStepping : 1;                             // 0x0130(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bSimulationEnabled : 1;                            // 0x0130(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bSweepCollision : 1;                               // 0x0130(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bIsHomingProjectile : 1;                           // 0x0130(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bBounceAngleAffectsFriction : 1;                   // 0x0131(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bIsSliding : 1;                                    // 0x0131(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, DisableEditOnTemplate, EditConst, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bInterpMovement : 1;                               // 0x0131(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bInterpRotation : 1;                               // 0x0131(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         Pad_132[0x2];                                      // 0x0132(0x0002)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         PreviousHitTime;                                   // 0x0134(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnTemplate, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	fvector                                PreviousHitNormal;                                 // 0x0138(0x000C)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnTemplate, EditConst, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         ProjectileGravityScale;                            // 0x0144(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         Buoyancy;                                          // 0x0148(0x0004)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         Bounciness;                                        // 0x014C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         Friction;                                          // 0x0150(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         BounceVelocityStopSimulatingThreshold;             // 0x0154(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         MinFrictionFraction;                               // 0x0158(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_15C[0x4];                                      // 0x015C(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         HomingAccelerationMagnitude;                       // 0x0180(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	TWeakObjectPtr<class USceneComponent>         HomingTargetComponent;                             // 0x0184(0x0008)(Edit, BlueprintVisible, ExportObject, ZeroConstructor, DisableEditOnTemplate, EditConst, InstancedReference, IsPlainOldData, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         MaxSimulationTimeStep;                             // 0x018C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32_t                                         MaxSimulationIterations;                           // 0x0190(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32_t                                         BounceAdditionalIterations;                        // 0x0194(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         InterpLocationTime;                                // 0x0198(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         InterpRotationTime;                                // 0x019C(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         InterpLocationMaxLagDistance;                      // 0x01A0(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         InterpLocationSnapToTargetDistance;                // 0x01A4(0x0004)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_1A8[0x68];                                     // 0x01A8(0x0068)(Fixing Struct Size After Last Property [ Dumper-7 ])

public:

	void move_interpolation_target(const fvector& NewLocation, const frotator& NewRotation);
	void stop_movement_immediately();
};

class UDisplayNameManager final : public uobject
{
public:
	class UConfigManager* ConfigManager;                                     // 0x0080(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	class URSOManager* RSOManager;                                        // 0x0088(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	class UDisplayNameService* DisplayNameService;                                // 0x0090(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	class UFriendsModel* FriendsModel;                                      // 0x0098(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	class UPlayerAliasManager* PlayerAliasManager;                                // 0x00A0(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	tmap<fstring, FDisplayName>      CachedDisplayNames;                                // 0x00A8(0x0050)(NativeAccessSpecifierPrivate)
	class UGameInstance* GameInstance;                                      // 0x00F8(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	class URGIFriendsSubsystem* RGIFriendsSubsystem;                               // 0x0100(0x0008)(ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	uint8_t                                         Pad_108[0x38];

public:
	UDisplayNameManager* get_display_name_manager();
	fstring get_display_name(fstring subject);
	// 0x0108(0x0038)(Fixing Struct Size After Last Property [ Dumper-7 ])
};

// Class Engine.MovementComponent
// 0x0040 (0x0128 - 0x00E8)
class UMovementComponent : public uobject
{
public:
	UPrimitiveComponent* UpdatedPrimitive;                                  // 0x00F0(0x0008)(BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, Transient, InstancedReference, DuplicateTransient, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_F8[0x4];                                       // 0x00F8(0x0004)(Fixing Size After Last Property [ Dumper-7 ])
	fvector                                Velocity;                                          // 0x00FC(0x000C)(Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	fvector                                PlaneConstraintNormal;                             // 0x0108(0x000C)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
	fvector                                PlaneConstraintOrigin;                             // 0x0114(0x000C)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, Protected, HasGetValueTypeHash, NativeAccessSpecifierProtected)
	uint8_t                                         bUpdateOnlyIfRendered : 1;                         // 0x0120(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bAutoUpdateTickRegistration : 1;                   // 0x0120(0x0001)(BitIndex: 0x01, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bTickBeforeOwner : 1;                              // 0x0120(0x0001)(BitIndex: 0x02, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bAutoRegisterUpdatedComponent : 1;                 // 0x0120(0x0001)(BitIndex: 0x03, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bConstrainToPlane : 1;                             // 0x0120(0x0001)(BitIndex: 0x04, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bSnapToPlaneAtStart : 1;                           // 0x0120(0x0001)(BitIndex: 0x05, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bAutoRegisterPhysicsVolumeUpdates : 1;             // 0x0120(0x0001)(BitIndex: 0x06, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         bComponentShouldUpdatePhysicsVolume : 1;           // 0x0120(0x0001)(BitIndex: 0x07, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         Pad_121[0x2];                                      // 0x0121(0x0002)(Fixing Size After Last Property [ Dumper-7 ])
	//EPlaneConstraintAxisSetting                   PlaneConstraintAxisSetting;                        // 0x0123(0x0001)(Edit, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPrivate)
	uint8_t                                         Pad_124[0x4];
	// 0x0124(0x0004)(Fixing Struct Size After Last Property [ Dumper-7 ])
};

struct ULightComponentBase : USceneComponent {
	float Brightness; // 0x298(0x04)
	float Intensity; // 0x29c(0x04)
	struct fcolor LightColor; // 0x2a0(0x04)
	char bAffectsWorld : 1; // 0x2a4(0x01)
	char CastShadows : 1; // 0x2a4(0x01)
	char CastStaticShadows : 1; // 0x2a4(0x01)
	char CastDynamicShadows : 1; // 0x2a4(0x01)
	char bAffectTranslucentLighting : 1; // 0x2a4(0x01)
	char bTransmission : 1; // 0x2a4(0x01)
	char bCastVolumetricShadow : 1; // 0x2a4(0x01)
	char bCastDeepShadow : 1; // 0x2a4(0x01)
	char bCastRaytracedShadow : 1; // 0x2a5(0x01)
	char bAffectReflection : 1; // 0x2a5(0x01)
	char bAffectGlobalIllumination : 1; // 0x2a5(0x01)
	float DeepShadowLayerDistribution; // 0x2a8(0x04)
	float IndirectLightingIntensity; // 0x2ac(0x04)
	float VolumetricScatteringIntensity; // 0x2b0(0x04)
	int32_t SamplesPerPixel; // 0x2b4(0x04)
	bool bLightProbeIntensityOverride; // 0x2b8(0x01)
	bool bLightProbeColorOverride; // 0x2b9(0x01)
	bool bLightProbeIndirectIntensityOverride; // 0x2ba(0x01)
	float LightProbeIntensity; // 0x2bc(0x04)
	fcolor LightProbeColor; // 0x2c0(0x04)
	float LightProbeIndirectIntensity; // 0x2c4(0x04)
	char pad_2CC_3 : 5; // 0x2cc(0x01)
	char pad_2CD[0x3]; // 0x2cd(0x03)

	void SetSamplesPerPixel(int32_t NewValue); // Function Engine.LightComponentBase.SetSamplesPerPixel // (Final|Native|Public|BlueprintCallable) // @ game+0x6e71600
	void SetCastVolumetricShadow(bool bNewValue); // Function Engine.LightComponentBase.SetCastVolumetricShadow // (Final|Native|Public|BlueprintCallable) // @ game+0x6e714f0
	void SetCastShadows(bool bNewValue); // Function Engine.LightComponentBase.SetCastShadows // (Final|Native|Public|BlueprintCallable) // @ game+0x6e71460
	void SetCastRaytracedShadow(bool bNewValue); // Function Engine.LightComponentBase.SetCastRaytracedShadow // (Final|Native|Public|BlueprintCallable) // @ game+0x6e713d0
	void SetCastDeepShadow(bool bNewValue); // Function Engine.LightComponentBase.SetCastDeepShadow // (Final|Native|Public|BlueprintCallable) // @ game+0x6e71340
	void SetAffectReflection(bool bNewValue); // Function Engine.LightComponentBase.SetAffectReflection // (Final|Native|Public|BlueprintCallable) // @ game+0x6e71230
	void SetAffectGlobalIllumination(bool bNewValue); // Function Engine.LightComponentBase.SetAffectGlobalIllumination // (Final|Native|Public|BlueprintCallable) // @ game+0x6e711a0
	flinearcolor GetLightColor(); // Function Engine.LightComponentBase.GetLightColor // (Final|Native|Public|HasDefaults|BlueprintCallable|BlueprintPure|Const) // @ game+0x6e71050
};


// Class Engine.SkyLightComponent
// 0x01E0 (0x0450 - 0x0270)
class USkyLightComponent final : public ULightComponentBase
{
public:
	bool                                          bRealTimeCapture;                                  // 0x0268(0x0001)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	//ESkyLightSourceType                           SourceType;                                        // 0x0269(0x0001)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_26A[0x6];                                      // 0x026A(0x0006)(Fixing Size After Last Property [ Dumper-7 ])
	class UTextureCube* Cubemap;                                           // 0x0270(0x0008)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         SourceCubemapAngle;                                // 0x0278(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32_t                                         CubemapResolution;                                 // 0x027C(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         MobileIntensity;                                   // 0x0280(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         MobileCharacterIntensity;                          // 0x0284(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         ContrastFresnelExponentCharacterCubemap;           // 0x0288(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         SkyDistanceThreshold;                              // 0x028C(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                          bCaptureEmissiveOnly;                              // 0x0290(0x0001)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                          bLowerHemisphereIsBlack;                           // 0x0291(0x0001)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_292[0x2];                                      // 0x0292(0x0002)(Fixing Size After Last Property [ Dumper-7 ])
	flinearcolor                           LowerHemisphereColor;                              // 0x0294(0x0010)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, AdvancedDisplay, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         OcclusionMaxDistance;                              // 0x02A4(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         Contrast;                                          // 0x02A8(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         OcclusionExponent;                                 // 0x02AC(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         MinOcclusion;                                      // 0x02B0(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         bCloudAmbientOcclusion : 1;                        // 0x02B8(0x0001)(BitIndex: 0x00, PropSize: 0x0001 (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic))
	uint8_t                                         Pad_2B9[0x3];                                      // 0x02B9(0x0003)(Fixing Size After Last Property [ Dumper-7 ])
	float                                         CloudAmbientOcclusionStrength;                     // 0x02BC(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, Interp, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         CloudAmbientOcclusionExtent;                       // 0x02C0(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         CloudAmbientOcclusionMapResolutionScale;           // 0x02C4(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                         CloudAmbientOcclusionApertureScale;                // 0x02C8(0x0004)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	//EOcclusionCombineMode                         OcclusionCombineMode;                              // 0x02CC(0x0001)(Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	uint8_t                                         Pad_2CD[0xAB];                                     // 0x02CD(0x00AB)(Fixing Size After Last Property [ Dumper-7 ])
	class UTextureCube* BlendDestinationCubemap;                           // 0x0378(0x0008)(ZeroConstructor, Transient, NoDestructor, Protected, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierProtected)
	uint8_t                                         Pad_380[0xD0];                                     // 0x0380(0x00D0)(Fixing Struct Size After Last Property [ Dumper-7 ])

public:
	void RecaptureSky();
	void SetCharacterCubemapContrastFresnelExponent(float InCharacterCubemapContrastFresnelExponent);
	void SetCubemap(UTextureCube* NewCubemap);
	void SetCubemapBlend(UTextureCube* SourceCubemap, UTextureCube* DestinationCubemap, float InBlendFraction);
	void SetDestinationCubemapAngle(float NewValue);
	void SetIndirectLightingIntensity(float NewIntensity);
	void SetIntensity(float NewIntensity);
	void SetLightColor(flinearcolor& NewLightColor);
	void SetLowerHemisphereColor(flinearcolor& InLowerHemisphereColor);
	void SetMinOcclusion(float InMinOcclusion);
	void SetMobileCharacterSkylightIntensity(float InMobileIntensity);
	void SetMobileLightColor(flinearcolor& NewLightColor);
	void SetMobileSkylightIntensity(float InMobileIntensity);
	void SetOcclusionContrast(float InOcclusionContrast);
	void SetOcclusionExponent(float InOcclusionExponent);
	//void SetOcclusionTint(FColor& InTint);
	void SetSkyDistanceThreshold(float DistanceThreshold);
	void SetSourceCubemapAngle(float NewValue);
	void SetVolumetricScatteringIntensity(float NewIntensity);
};

// Class ShooterGame.BlindManagerComponent
// 0x00F0 (0x01C8 - 0x00D8)
class UBlindManagerComponent final : public UActorComponent
{
public:
	uint8_t                                         Pad_D8[0x8];                                       // 0x00D8(0x0008)(Fixing Size After Last Property [ Dumper-7 ])
	//FMulticastInlineDelegateProperty_             OnBlindedChanged;                                  // 0x00E0(0x0010)(ZeroConstructor, InstancedReference, BlueprintAssignable, NativeAccessSpecifierPublic)
	//FMulticastInlineDelegateProperty_             OnFailedBlindApplicationTagRequirements;           // 0x00F0(0x0010)(ZeroConstructor, InstancedReference, BlueprintAssignable, NativeAccessSpecifierPublic)
	//struct FBlindManagerState                     AuthBlindManagerState;                             // 0x0100(0x0018)(Net, RepNotify, NativeAccessSpecifierPrivate)
	//struct FBlindManagerState                     LocalBlindManagerState;                            // 0x0118(0x0018)(NativeAccessSpecifierPrivate)
	uint8_t                                         Pad_130[0x30];                                     // 0x0130(0x0030)(Fixing Size After Last Property [ Dumper-7 ])
	tarray<struct FBlindSpawnParams>              ScheduledBlinds;                                   // 0x0160(0x0010)(ZeroConstructor, NativeAccessSpecifierPrivate)
	uint8_t                                         Pad_170[0x58];                                     // 0x0170(0x0058)(Fixing Struct Size After Last Property [ Dumper-7 ])

public:
	bool IsBlinded();
	void SetBlinded(bool bNewBlinded);
	void ClientCleanseBlinds();
};

 
 
class ushootercharacterdeathreactioncomponent : public uobject {
public:
	bool is_death_reaction_queued() {
		static uobject* function;
		if (!function)
			function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacterDeathReactionComponent.IsDeathReactionQueued"));

		if (!function)
			return false;

		struct {
			bool return_value;
		} params;

		this->process_event(function, &params);
		return params.return_value;
	}

	void play_finisher_effect(bool b_local_only) {
		static uobject* function;
		if (!function)
			function = uobject::find_object<uobject*>(crypt(L"ShooterGame.ShooterCharacterDeathReactionComponent.PlayFinisherEffect"));

		if (!function)
			return;

		struct {
			bool b_local_only;
		} params;

		params.b_local_only = b_local_only;
		this->process_event(function, &params);
	}

	void start_effect(ashootercharacter* target, uobject* context, float start_time, bool first_person) {
		static uobject* function;
		if (!function)
			function = uobject::find_object<uobject*>(crypt(L"ShooterGame.EffectComponent.StartEffect"));

		if (!function)
			return;

		struct {
			ashootercharacter* target;
			uobject* context;
			float start_time;
			bool first_person;
		} params;

		params.target = target;
		params.context = context;
		params.start_time = start_time;
		params.first_person = first_person;

		this->process_event(function, &params);
	}

	ushootercharacterdeathreactioncomponent* get_death_reaction_component() {
		static uobject* function = nullptr;
		if (!function)
			function = uobject::find_object<uobject*>(
				crypt(L"ShooterGame.ShooterCharacter.GetDeathReactionComponent")
			);

		if (!function)
			return nullptr;

		struct {
			ushootercharacterdeathreactioncomponent* return_value;
		} params{};

		this->process_event(function, &params);
		return params.return_value;
	}

};

struct fxc_finisher_base_victim_c : uobject {
	void start_effect(ashootercharacter* target, uobject* context, float start_time, bool first_person) {
		static uobject* function;
		if (!function)
			function = uobject::find_object<uobject*>(crypt(L"ShooterGame.EffectComponent.StartEffect"));

		if (!function)
			return;

		struct {
			ashootercharacter* target;
			uobject* context;
			float start_time;
			bool first_person;
		} params;

		params.target = target;
		params.context = context;
		params.start_time = start_time;
		params.first_person = first_person;

		this->process_event(function, &params);
	}
};

enum class EAresPlatformType : uint8_t
{
	None = 0,
	Desktop = 1,
	Mobile = 2,
	Console = 4,
	All = 7,
	EAresPlatformType_MAX = 8,
};

struct Plateformee : public uobject {
public:
	fstring get_platform_name() {
		static uobject* function = nullptr;
		if (!function)
			function = uobject::find_object<uobject*>(L"Function Engine.GameplayStatics.GetPlatformName");

		if (!function || !this) return fstring();

		struct Params {
			fstring output;
		} params;

		this->process_event(function, &params);
		return params.output;
	}

	EAresPlatformType get_client_platform_type() {
		static uobject* function = nullptr;
		if (!function)
			function = uobject::find_object<uobject*>(L"ShooterGame.AresPlatformBlueprintFunctionLibrary.GetClientPlatformType");

		if (!function || !this) return EAresPlatformType::None;

		struct Params {
			EAresPlatformType output;
		} params;

		this->process_event(function, &params);
		return params.output;
	}
};


struct FColor final
{
	uint8_t B;
	uint8_t G;
	uint8_t R;
	uint8_t A;
	FColor() : B(255), G(255), R(255), A(255) {}
	FColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : B(b), G(g), R(r), A(a) {}
};

struct FProcMeshTangent final
{
	fvector TangentX;
	bool bFlipTangentY;
	uint8_t Pad_19[0x7];
	FProcMeshTangent() : TangentX(fvector(1, 0, 0)), bFlipTangentY(false) { memset(Pad_19, 0, sizeof(Pad_19)); }
};

struct FAttachmentTransformRules
{
	EAttachmentRule LocationRule;
	EAttachmentRule RotationRule;
	EAttachmentRule ScaleRule;
	bool bWeldSimulatedBodies;
	FAttachmentTransformRules() : LocationRule(EAttachmentRule::SnapToTarget), RotationRule(EAttachmentRule::SnapToTarget), ScaleRule(EAttachmentRule::SnapToTarget), bWeldSimulatedBodies(false) {}
	FAttachmentTransformRules(EAttachmentRule loc, EAttachmentRule rot, EAttachmentRule scale, bool weld) : LocationRule(loc), RotationRule(rot), ScaleRule(scale), bWeldSimulatedBodies(weld) {}
	static FAttachmentTransformRules SnapToTargetNotIncludingScale;
};

class UProceduralMeshComponent : public uobject
{
public:
	void SetRelativeRotation(FRotator NewRotation, bool bSweep, bool bTeleport);
	void SetRelativeScale3D(fvector NewScale3D);
	void SetRelativeLocation(fvector NewLocation, bool bSweep, bool bTeleport);
	void RegisterComponent();
	void SetVisibility(bool bNewVisibility, bool bPropagateToChildren);
	bool K2_AttachToComponent(uobject* Parent, fname SocketName, int LocationRule, int RotationRule, int ScaleRule, bool bWeldSimulatedBodies);
};

struct MeshData {
	tarray<fvector> Vertices;
	tarray<int32_t> Triangles;
	tarray<fvector> Normals;
	tarray<fvector2d> UV0;
	tarray<FColor> VertexColors;
	tarray<FProcMeshTangent> Tangents;
};

MeshData ParseOBJFile(const wchar_t* filepath);
void ReplaceWeaponMeshWith3DModel(currentequippable* Weapon, const wchar_t* objFilePath);

void mesh1p_material_chams(acknowledgedpawn* MyPawn, ashootercharacter* MyShooter);
void ApplyCustomJettTexture(ashootercharacter* MyShooter);
void apply_hand_chams(ashootercharacter* shooter);
void moscawireframe(ashootercharacter* local_player);
void apply2_outline_hand_chams(ashootercharacter* shooter);

void apply_galaxy_chams(ashootercharacter* character);
void apply_galaxy_chams_enemy(ashootercharacter* character);
void apply_custom_gun(ashootercharacter* character);
bool ClipLineToScreen(fvector2d& start, fvector2d& end, float screenWidth, float screenHeight);


// sa ben akctwo bunu tum otobatlara yazıyorum 


// sa ben akctwo bunu tum otobatlara yazıyorum 