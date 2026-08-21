//#pragma once
//
//#include <Windows.h>
//#include <cstdint>
//#include <memory>
//#include <vector>
//#include <cstring>
//#include <iostream>
//#include <random>
//
//#include <Windows.h>
//#include <winternl.h>
//
//// If winternl.h doesn't provide all the necessary definitions, add these:
//#ifndef _MEMORY_INFORMATION_CLASS_
//#define _MEMORY_INFORMATION_CLASS_
//
//typedef enum _MEMORY_INFORMATION_CLASS {
//    MemoryBasicInformation,
//    MemoryWorkingSetInformation,
//    MemoryMappedFilenameInformation,
//    MemoryRegionInformation,
//    MemoryWorkingSetExInformation,
//    MemorySharedCommitInformation,
//    MemoryImageInformation,
//    MemoryRegionInformationEx,
//    MemoryPrivilegedBasicInformation,
//    MemoryEnclaveImageInformation,
//    MemoryBasicInformationCapped,
//    MemoryPhysicalContiguityInformation,
//    MemoryBadInformation,
//    MemoryBadInformationAllProcesses,
//    MemoryImageExtensionInformation,
//    MaxMemoryInfoClass
//} MEMORY_INFORMATION_CLASS;
//
//#endif // _MEMORY_INFORMATION_CLASS_
//
//// Define the function prototype for NtQueryVirtualMemory if it's not already defined
//typedef NTSTATUS(NTAPI* PFN_NT_QUERY_VIRTUAL_MEMORY)(
//    HANDLE ProcessHandle,
//    PVOID BaseAddress,
//    MEMORY_INFORMATION_CLASS MemoryInformationClass,
//    PVOID MemoryInformation,
//    SIZE_T MemoryInformationLength,
//    PSIZE_T ReturnLength
//    );
//
//// SIMPLE
//// 
////class VTableHook {
////public:
////	void* object = nullptr;
////	std::uintptr_t* orig_vtable = nullptr;
////	std::unique_ptr<std::uintptr_t[]> shadow_vtable;
////	size_t vtable_len = 0;
////
////	bool hooked = false;
////
////	std::vector<void*> trampolines;
////
////	std::uintptr_t find_rwx_cave() {
////		MEMORY_BASIC_INFORMATION mbi = {};
////		std::uintptr_t address = 0;
////		while (VirtualQuery((LPCVOID)address, &mbi, sizeof(mbi)) == sizeof(mbi)) {
////			if (
////				mbi.Protect == PAGE_EXECUTE_READWRITE &&
////				mbi.AllocationProtect == PAGE_EXECUTE_READWRITE &&
////				mbi.State == MEM_COMMIT &&
////				mbi.Type == MEM_PRIVATE
////				) {
////				uint8_t* mem = reinterpret_cast<uint8_t*>(mbi.BaseAddress);
////				size_t count = 0;
////				for (size_t i = 0; i < mbi.RegionSize; ++i)
////					count += (mem[i] == 0);
////
////				if (count > 128)
////					return reinterpret_cast<std::uintptr_t>(mbi.BaseAddress);
////			}
////			address += mbi.RegionSize;
////		}
////		return 0;
////	}
////
////	static size_t get_vtable_length(std::uintptr_t* vtab) {
////		size_t count = 0;
////		while (vtab[count] != 0 && vtab[count] > 0x10000 && vtab[count] < 0xF000000000000) ++count;
////		return count;
////	}
////
////	void* hook(void* instance, void* detour, int index) {
////		if (!instance || !detour || index < 0) return nullptr;
////
////		object = instance;
////		orig_vtable = *reinterpret_cast<std::uintptr_t**>(object);
////		if (!orig_vtable) return nullptr;
////
////		vtable_len = get_vtable_length(orig_vtable);
////		if (index >= (int)vtable_len) return nullptr;
////
////		shadow_vtable.reset(new std::uintptr_t[vtable_len]);
////		std::memcpy(shadow_vtable.get(), orig_vtable, sizeof(std::uintptr_t) * vtable_len);
////
////		void* original_func = reinterpret_cast<void*>(shadow_vtable[index]);
////
////		void* trampoline = nullptr;
////		std::uintptr_t cave = find_rwx_cave();
////
////		if (cave) {
////			trampoline = reinterpret_cast<void*>(cave + 0x80 + (trampolines.size() * 16));
////			if (reinterpret_cast<std::uintptr_t>(trampoline) < (cave + 0x1000)) {
////				if ((reinterpret_cast<std::uintptr_t>(trampoline) + 16) > (cave + 0x1000)) {
////					cave = 0;
////				}
////			}
////			else {
////				cave = 0;
////			}
////		}
////
////		if (!cave) {
////			trampoline = VirtualAlloc(nullptr, 16, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
////			if (!trampoline) return nullptr;
////		}
////
////		BYTE shellcode[] = {
////			0x48, 0xB8,
////			0, 0, 0, 0, 0, 0, 0, 0,
////			0xFF, 0xE0
////		};
////		*reinterpret_cast<uintptr_t*>(&shellcode[2]) = reinterpret_cast<uintptr_t>(detour);
////		std::memcpy(trampoline, shellcode, sizeof(shellcode));
////
////		if (!cave) {
////			DWORD old_protect;
////			VirtualProtect(trampoline, sizeof(shellcode), PAGE_EXECUTE_READ, &old_protect);
////		}
////
////		trampolines.push_back(trampoline);
////
////		shadow_vtable[index] = reinterpret_cast<uintptr_t>(trampoline);
////
////		*reinterpret_cast<std::uintptr_t**>(object) = shadow_vtable.get();
////
////		hooked = true;
////		return original_func;
////	}
////
////
////	void restore() {
////		if (object && orig_vtable)
////			*reinterpret_cast<std::uintptr_t**>(object) = orig_vtable;
////		hooked = false;
////	}
////
////	~VTableHook() {
////		restore();
////		for (auto t : trampolines) {
////			MEMORY_BASIC_INFORMATION mbi = {};
////			if (VirtualQuery(t, &mbi, sizeof(mbi)) && mbi.AllocationProtect != PAGE_EXECUTE_READWRITE) {
////				VirtualFree(t, 0, MEM_RELEASE);
////			}
////		}
////		trampolines.clear();
////	}
////};
//
//// GOOD
//// 
////class VTableHook {
////public:
////	void* object = nullptr;
////	std::uintptr_t* orig_vtable = nullptr;
////	std::unique_ptr<std::uintptr_t[]> shadow_vtable;
////	size_t vtable_len = 0;
////	bool hooked = false;
////
////	std::vector<void*> trampolines;
////
////	std::uintptr_t find_rwx_cave() {
////		MEMORY_BASIC_INFORMATION mbi = {};
////		std::uintptr_t address = 0;
////		while (VirtualQuery(reinterpret_cast<LPCVOID>(address), &mbi, sizeof(mbi))) {
////			if (mbi.State == MEM_COMMIT &&
////				mbi.Protect == PAGE_EXECUTE_READWRITE &&
////				mbi.Type == MEM_PRIVATE) {
////				uint8_t* mem = static_cast<uint8_t*>(mbi.BaseAddress);
////				bool valid = true;
////				for (size_t i = 0; i < 256; ++i) {
////					if (mem[i] != 0) {
////						valid = false;
////						break;
////					}
////				}
////				if (valid) return reinterpret_cast<std::uintptr_t>(mem);
////			}
////			address += mbi.RegionSize;
////		}
////		return 0;
////	}
////
////	static size_t get_vtable_length(std::uintptr_t* vtab) {
////		size_t count = 0;
////		while (vtab[count] != 0 &&
////			vtab[count] > 0x10000 &&
////			vtab[count] < 0x00007FFFFFFF0000) ++count;
////		return count;
////	}
////
////	void* G35H7B9G3H499H4G334GHJ(void* instance, void* detour, int index) {
////		if (!instance || !detour || index < 0) return nullptr;
////
////		object = instance;
////		orig_vtable = *reinterpret_cast<std::uintptr_t**>(object);
////		if (!orig_vtable) return nullptr;
////
////		vtable_len = get_vtable_length(orig_vtable);
////		if (index >= static_cast<int>(vtable_len)) return nullptr;
////
////		shadow_vtable.reset(new std::uintptr_t[vtable_len]);
////		memcpy(shadow_vtable.get(), orig_vtable, sizeof(std::uintptr_t) * vtable_len);
////
////		void* original_func = reinterpret_cast<void*>(shadow_vtable[index]);
////
////		void* trampoline = nullptr;
////		std::uintptr_t cave = find_rwx_cave();
////
////		if (cave) {
////			trampoline = reinterpret_cast<void*>((cave + 0x100) & ~0xF);
////			if (reinterpret_cast<std::uintptr_t>(trampoline) + 16 > cave + 0x1000) {
////				cave = 0;
////			}
////		}
////
////		if (!cave) {
////			trampoline = VirtualAlloc(nullptr, 16, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
////			if (!trampoline) {
////				shadow_vtable.reset();
////				return nullptr;
////			}
////		}
////
////		std::random_device rd;
////		std::mt19937 gen(rd());
////		std::uniform_int_distribution<unsigned short> dist(0, 255);
////
////		alignas(16) BYTE shellcode[16];
////		for (auto& b : shellcode) {
////			b = static_cast<BYTE>(dist(gen));
////		}
////
////		shellcode[0] = 0x48;
////		shellcode[1] = 0xB8;
////		*reinterpret_cast<uintptr_t*>(&shellcode[2]) = reinterpret_cast<uintptr_t>(detour);
////		shellcode[10] = 0xFF;
////		shellcode[11] = 0xE0;
////
////		DWORD old_protect;
////		if (!cave) {
////			if (!VirtualProtect(trampoline, sizeof(shellcode), PAGE_EXECUTE_READ, &old_protect)) {
////				VirtualFree(trampoline, 0, MEM_RELEASE);
////				shadow_vtable.reset();
////				return nullptr;
////			}
////		}
////
////		memcpy(trampoline, shellcode, sizeof(shellcode));
////		trampolines.push_back(trampoline);
////		shadow_vtable[index] = reinterpret_cast<std::uintptr_t>(trampoline);
////
////		*reinterpret_cast<std::uintptr_t**>(object) = shadow_vtable.get();
////
////		hooked = true;
////		return original_func;
////	}
////
////	void restore() {
////		if (object && orig_vtable) {
////			*reinterpret_cast<std::uintptr_t**>(object) = orig_vtable;
////		}
////		hooked = false;
////
////		for (auto t : trampolines) {
////			MEMORY_BASIC_INFORMATION mbi = {};
////			if (VirtualQuery(t, &mbi, sizeof(mbi))) {
////				if (mbi.AllocationProtect == PAGE_READWRITE ||
////					mbi.AllocationProtect == PAGE_EXECUTE_READ) {
////					VirtualFree(t, 0, MEM_RELEASE);
////				}
////			}
////		}
////		trampolines.clear();
////	}
////
////	~VTableHook() {
////		restore();
////	}
////};
//
////GOOD V2 EVEN BETTER !!!!
//
////#include <Windows.h>
////#include <winternl.h>
////#include <array>
////#include <random>
////#include <vector>
////#include <memory>
////#include <cstdint>
////
////#pragma comment(lib, "ntdll.lib")
////
////class VTableHook {
////public:
////    struct TrampolineInfo {
////        void* address;
////        bool is_code_cave;
////    };
////
////    void* object = nullptr;
////    std::uintptr_t* orig_vtable = nullptr;
////    std::unique_ptr<std::uintptr_t[]> shadow_vtable;
////    size_t vtable_len = 0;
////    bool hooked = false;
////
////    std::vector<TrampolineInfo> trampolines;
////
////private:
////    static inline std::uintptr_t rwx_cave = 0;
////    static inline int total_functions = 0;
////
////    static NTSTATUS NTAPI NtQueryVirtualMemory(
////        HANDLE ProcessHandle,
////        PVOID BaseAddress,
////        MEMORY_INFORMATION_CLASS MemoryInformationClass,
////        PVOID MemoryInformation,
////        SIZE_T MemoryInformationLength,
////        PSIZE_T ReturnLength
////    ) {
////        static auto func = []() -> decltype(&NtQueryVirtualMemory) {
////            auto ntdll = GetModuleHandleW(L"ntdll.dll");
////            return reinterpret_cast<decltype(&NtQueryVirtualMemory)>(
////                GetProcAddress(ntdll, "NtQueryVirtualMemory"));
////            }();
////        return func(ProcessHandle, BaseAddress, MemoryInformationClass,
////            MemoryInformation, MemoryInformationLength, ReturnLength);
////    }
////
////    std::uintptr_t find_whitelisted_rwx_cave() {
////        MEMORY_BASIC_INFORMATION mbi = {};
////        std::uintptr_t address = 0;
////        SIZE_T returnLength;
////
////        while (NtQueryVirtualMemory(
////            HANDLE(-1),
////            reinterpret_cast<PVOID>(address),
////            MemoryBasicInformation,
////            &mbi,
////            sizeof(mbi),
////            &returnLength
////        ) >= 0) {
////            if (mbi.State == MEM_COMMIT &&
////                mbi.Protect == PAGE_EXECUTE_READWRITE &&
////                mbi.AllocationProtect == PAGE_EXECUTE_READWRITE &&
////                mbi.Type == MEM_PRIVATE) {
////
////                uint8_t* mem = static_cast<uint8_t*>(mbi.BaseAddress);
////
////                if (mem[0] == 0x48 && mem[1] == 0x89 && mem[2] == 0x5C && mem[3] == 0x24) {
////                    bool is_empty_end = true;
////                    bool pattern_valid = true;
////
////                    for (size_t i = 100; i < mbi.RegionSize; ++i) {
////                        if (mem[i] != 0) {
////                            if (!is_empty_end) {
////                                pattern_valid = false;
////                                break;
////                            }
////                            is_empty_end = false;
////                        }
////                        else {
////                            if (is_empty_end) continue;
////                            is_empty_end = true;
////                        }
////                    }
////
////                    if (pattern_valid && is_empty_end) {
////                        return reinterpret_cast<std::uintptr_t>(mem);
////                    }
////                }
////            }
////            address += mbi.RegionSize;
////        }
////        return 0;
////    }
////
////    std::uintptr_t bind_to_cave(void* detour) {
////        constexpr std::array<uint8_t, 18> stub = {
////            0xFF, 0x25, 0x00, 0x00, 0x00, 0x00,
////            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
////            0xCC, 0xCC, 0xCC, 0xCC
////        };
////
////        std::array<uint8_t, 18> code = stub;
////        *reinterpret_cast<void**>(&code[6]) = detour;
////
////        const std::uintptr_t address = rwx_cave + 0x100 + (total_functions * code.size());
////        __movsb(reinterpret_cast<uint8_t*>(address), code.data(), code.size());
////        total_functions++;
////
////        return address;
////    }
////
////public:
////    static size_t get_vtable_length(std::uintptr_t* vtab) {
////        size_t count = 0;
////        while (vtab[count] &&
////            vtab[count] > 0x10000 &&
////            vtab[count] < 0x00007FFFFFFF0000) ++count;
////        return count;
////    }
////
////    void* fg34hh3478h87f34h378g4h34g343g(void* instance, void* detour, int index) {
////        if (!instance || !detour || index < 0) return nullptr;
////
////        if (rwx_cave == 0) {
////            rwx_cave = find_whitelisted_rwx_cave();
////        }
////
////        object = instance;
////        orig_vtable = *reinterpret_cast<std::uintptr_t**>(object);
////        if (!orig_vtable) return nullptr;
////
////        vtable_len = get_vtable_length(orig_vtable);
////        if (index >= static_cast<int>(vtable_len)) return nullptr;
////
////        shadow_vtable.reset(new std::uintptr_t[vtable_len]);
////        memcpy(shadow_vtable.get(), orig_vtable, sizeof(std::uintptr_t) * vtable_len);
////
////        void* original_func = reinterpret_cast<void*>(shadow_vtable[index]);
////        void* trampoline = nullptr;
////        bool is_cave = false;
////
////        if (rwx_cave) {
////            trampoline = reinterpret_cast<void*>(bind_to_cave(detour));
////            is_cave = true;
////        }
////
////        if (!trampoline) {
////            constexpr size_t size = 32;
////            trampoline = VirtualAlloc(nullptr, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
////            if (!trampoline) {
////                shadow_vtable.reset();
////                return nullptr;
////            }
////
////            std::independent_bits_engine<std::mt19937_64, 8, unsigned short> gen(
////                static_cast<unsigned int>(__rdtsc())
////            );
////
////            alignas(16) uint8_t shellcode[size] = {};
////            for (auto& b : shellcode) b = static_cast<uint8_t>(gen());
////
////            shellcode[0] = 0x48; shellcode[1] = 0xB8;
////            *reinterpret_cast<void**>(shellcode + 2) = detour;
////            shellcode[10] = 0xFF; shellcode[11] = 0xE0;
////
////            for (size_t i = 12; i < size - 4; ++i) {
////                shellcode[i] = 0x90;
////            }
////
////            DWORD old_protect;
////            VirtualProtect(trampoline, size, PAGE_EXECUTE_READ, &old_protect);
////            memcpy(trampoline, shellcode, sizeof(shellcode));
////        }
////
////        shadow_vtable[index] = reinterpret_cast<std::uintptr_t>(trampoline);
////        trampolines.push_back({ trampoline, is_cave });
////        *reinterpret_cast<std::uintptr_t**>(object) = shadow_vtable.get();
////
////        hooked = true;
////        return original_func;
////    }
////
////    void restore() {
////        if (object && orig_vtable) {
////            *reinterpret_cast<std::uintptr_t**>(object) = orig_vtable;
////        }
////        hooked = false;
////
////        for (auto& ti : trampolines) {
////            if (ti.is_code_cave) {
////                constexpr std::array<uint8_t, 18> stub = {
////                    0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
////                    0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
////                    0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC
////                };
////                __movsb(static_cast<uint8_t*>(ti.address), stub.data(), stub.size());
////            }
////            else {
////                VirtualFree(ti.address, 0, MEM_RELEASE);
////            }
////        }
////        trampolines.clear();
////    }
////
////    ~VTableHook() {
////        restore();
////        if (rwx_cave && trampolines.empty()) {
////            total_functions = 0;
////        }
////    }
////};
//
//#include <Windows.h>
//#include <winternl.h>
//#include <array>
//#include <vector>
//#include <memory>
//#include <cstdint>
//#include <random>
//
//#pragma comment(lib, "ntdll.lib")
//
//class VTableHook {
//public:
//    struct TrampolineInfo {
//        void* address;
//        bool is_code_cave;
//    };
//
//    void* object = nullptr;
//    std::uintptr_t* orig_vtable = nullptr;
//    std::unique_ptr<std::uintptr_t[]> shadow_vtable;
//    size_t vtable_len = 0;
//    bool hooked = false;
//
//    std::vector<TrampolineInfo> trampolines;
//
//private:
//    static inline std::uintptr_t rwx_cave = 0;
//    static inline int total_functions = 0;
//
//    static NTSTATUS NTAPI NtQueryVirtualMemory(
//
//        HANDLE ProcessHandle,
//        PVOID BaseAddress,
//        MEMORY_INFORMATION_CLASS MemoryInformationClass,
//        PVOID MemoryInformation,
//        SIZE_T MemoryInformationLength,
//        PSIZE_T ReturnLength
//    ) {
//        static auto func = []() -> decltype(&NtQueryVirtualMemory) {
//
//            SPOOF_FUNC
//
//                auto ntdll = GetModuleHandleW(L"ntdll.dll");
//            return reinterpret_cast<decltype(&NtQueryVirtualMemory)>(
//                SPOOF_CALL(GetProcAddress)(ntdll, "NtQueryVirtualMemory"));
//            }();
//        return func(ProcessHandle, BaseAddress, MemoryInformationClass,
//            MemoryInformation, MemoryInformationLength, ReturnLength);
//    }
//
//    std::uintptr_t find_whitelisted_rwx_cave() {
//
//        SPOOF_FUNC
//
//            MEMORY_BASIC_INFORMATION mbi = {};
//        std::uintptr_t address = 0;
//        SIZE_T returnLength;
//
//        while (SPOOF_CALL(NtQueryVirtualMemory)(
//            HANDLE(-1),
//            reinterpret_cast<PVOID>(address),
//            MemoryBasicInformation,
//            &mbi,
//            sizeof(mbi),
//            &returnLength
//            ) >= 0) {
//            if (mbi.State == MEM_COMMIT &&
//                mbi.Protect == PAGE_EXECUTE_READWRITE &&
//                mbi.AllocationProtect == PAGE_EXECUTE_READWRITE &&
//                mbi.Type == MEM_PRIVATE) {
//
//                uint8_t* mem = static_cast<uint8_t*>(mbi.BaseAddress);
//                if (mem[0] == 0x48 && mem[1] == 0x89 && mem[2] == 0x5C && mem[3] == 0x24) {
//                    bool is_empty_end = true;
//                    bool pattern_valid = true;
//
//                    for (size_t i = 100; i < mbi.RegionSize; ++i) {
//                        if (mem[i] != 0) {
//                            if (!is_empty_end) {
//                                pattern_valid = false;
//                                break;
//                            }
//                            is_empty_end = false;
//                        }
//                        else {
//                            if (is_empty_end) continue;
//                            is_empty_end = true;
//                        }
//                    }
//
//                    if (pattern_valid && is_empty_end) {
//                        return reinterpret_cast<std::uintptr_t>(mem);
//                    }
//                }
//            }
//            address += mbi.RegionSize;
//        }
//        return 0;
//    }
//
//    std::uintptr_t bind_to_cave(void* detour) {
//
//        SPOOF_FUNC
//
//            constexpr std::array<uint8_t, 18> stub = {
//                0xFF, 0x25, 0x00, 0x00, 0x00, 0x00,
//                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//                0xCC, 0xCC, 0xCC, 0xCC
//        };
//
//        std::array<uint8_t, 18> code = stub;
//        *reinterpret_cast<void**>(&code[6]) = detour;
//
//        const std::uintptr_t address = rwx_cave + 0x100 + (total_functions * code.size());
//        __movsb(reinterpret_cast<uint8_t*>(address), code.data(), code.size());
//        total_functions++;
//
//        return address;
//
//    }
//
//public:
//    static size_t get_vtable_length(std::uintptr_t* vtab) {
//
//        SPOOF_FUNC
//
//            size_t count = 0;
//        while (vtab[count] &&
//            vtab[count] > 0x10000 &&
//            vtab[count] < 0x00007FFFFFFF0000) ++count;
//        return count;
//
//    }
//
//    void* fg34hh3478h87f34h378g4h34g343g(void* instance, void* detour, int index) {
//
//        SPOOF_FUNC
//
//            if (!instance || !detour || index < 0) return nullptr;
//
//        if (rwx_cave == 0) {
//            rwx_cave = find_whitelisted_rwx_cave();
//        }
//
//        object = instance;
//        orig_vtable = *reinterpret_cast<std::uintptr_t**>(object);
//        if (!orig_vtable) return nullptr;
//
//        vtable_len = get_vtable_length(orig_vtable);
//        if (index >= static_cast<int>(vtable_len)) return nullptr;
//
//        shadow_vtable.reset(new std::uintptr_t[vtable_len]);
//        SPOOF_CALL(memcpy)(shadow_vtable.get(), orig_vtable, sizeof(std::uintptr_t) * vtable_len);
//
//        void* original_func = reinterpret_cast<void*>(shadow_vtable[index]);
//        void* trampoline = nullptr;
//        bool is_cave = false;
//
//        if (rwx_cave) {
//            trampoline = reinterpret_cast<void*>(bind_to_cave(detour));
//            is_cave = true;
//        }
//
//        if (!trampoline) {
//            constexpr size_t size = 64;
//            trampoline = SPOOF_CALL(VirtualAlloc)(nullptr, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
//            if (!trampoline) {
//                shadow_vtable.reset();
//                return nullptr;
//            }
//
//            BYTE shellcode[] = {
//                0x68, 0x00, 0x00, 0x00, 0x00,             // push lower 32-bits
//                0xC7, 0x44, 0x24, 0x04, 0x00, 0x00, 0x00, 0x00, // mov [rsp+4], upper 32-bits
//                0xC3                                      // ret
//            };
//
//            auto detour_address = reinterpret_cast<uintptr_t>(detour);
//            *reinterpret_cast<uint32_t*>(&shellcode[1]) = static_cast<uint32_t>(detour_address & 0xFFFFFFFF);
//            *reinterpret_cast<uint32_t*>(&shellcode[9]) = static_cast<uint32_t>((detour_address >> 32) & 0xFFFFFFFF);
//
//            alignas(16) uint8_t encrypted[size] = {};
//            for (size_t i = 0; i < sizeof(shellcode); ++i)
//                encrypted[i] = shellcode[i] ^ 0x5A;
//
//            for (size_t i = sizeof(shellcode); i < size; ++i)
//                encrypted[i] = 0x90 ^ 0x5A;
//
//            SPOOF_CALL(memcpy)(trampoline, encrypted, size);
//
//            DWORD oldProtect;
//            SPOOF_CALL(VirtualProtect)(trampoline, size, PAGE_EXECUTE_READ, &oldProtect);
//
//            for (size_t i = 0; i < size; ++i)
//                reinterpret_cast<volatile uint8_t*>(trampoline)[i] ^= 0x5A;
//        }
//
//        shadow_vtable[index] = reinterpret_cast<std::uintptr_t>(trampoline);
//        trampolines.push_back({ trampoline, is_cave });
//        *reinterpret_cast<std::uintptr_t**>(object) = shadow_vtable.get();
//
//        hooked = true;
//        return original_func;
//    }
//
//    void restore() {
//
//        SPOOF_FUNC
//
//            if (object && orig_vtable) {
//                *reinterpret_cast<std::uintptr_t**>(object) = orig_vtable;
//            }
//        hooked = false;
//
//        for (auto& ti : trampolines) {
//            if (ti.is_code_cave) {
//                constexpr std::array<uint8_t, 18> stub = {
//                    0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
//                    0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
//                    0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC
//                };
//                __movsb(static_cast<uint8_t*>(ti.address), stub.data(), stub.size());
//            }
//            else {
//                volatile uint8_t* mem = reinterpret_cast<volatile uint8_t*>(ti.address);
//                for (size_t i = 0; i < 64; ++i)
//                    mem[i] = 0xCC;
//                SPOOF_CALL(VirtualFree)(ti.address, 0, MEM_RELEASE);
//            }
//        }
//        trampolines.clear();
//
//    }
//
//    ~VTableHook() {
//        restore();
//        if (rwx_cave && trampolines.empty()) {
//            total_functions = 0;
//        }
//    }
//};
//
////#include <Windows.h>
////#include <winternl.h>
////#include <vector>
////#include <array>
////#include <memory>
////#include <cstdint>
////#include <immintrin.h>
////
////#pragma comment(lib, "ntdll.lib")
////
////class VTableHook {
////public:
////    struct TrampolineInfo {
////        void* address;
////        bool is_code_cave;
////    };
////
////    void* object = nullptr;
////    std::uintptr_t* orig_vtable = nullptr;
////    std::unique_ptr<std::uintptr_t[]> shadow_vtable;
////    size_t vtable_len = 0;
////
////    std::vector<TrampolineInfo> trampolines;
////
////private:
////    static inline std::uintptr_t rwx_cave = 0;
////    static inline int total_functions = 0;
////
////    static NTSTATUS NTAPI NtQueryVirtualMemory(
////        HANDLE ProcessHandle,
////        PVOID BaseAddress,
////        MEMORY_INFORMATION_CLASS MemoryInformationClass,
////        PVOID MemoryInformation,
////        SIZE_T MemoryInformationLength,
////        PSIZE_T ReturnLength
////    ) {
////        static auto func = []() -> decltype(&NtQueryVirtualMemory) {
////            auto ntdll = GetModuleHandleW(L"ntdll.dll");
////            return reinterpret_cast<decltype(&NtQueryVirtualMemory)>(
////                GetProcAddress(ntdll, "NtQueryVirtualMemory"));
////            }();
////        return func(ProcessHandle, BaseAddress, MemoryInformationClass,
////            MemoryInformation, MemoryInformationLength, ReturnLength);
////    }
////
////
////    static uint32_t hw_rand() {
////        unsigned int r = 0;
////        if (_rdseed32_step(&r)) return r;
////        if (_rdrand32_step(&r)) return r;
////        return static_cast<uint32_t>(__rdtsc());
////    }
////
////
////    static std::uintptr_t find_code_cave() {
////        MEMORY_BASIC_INFORMATION mbi{};
////        std::uintptr_t address = 0;
////        SIZE_T returnLength;
////        while (NtQueryVirtualMemory(
////            HANDLE(-1),
////            reinterpret_cast<PVOID>(address),
////            MemoryBasicInformation,
////            &mbi,
////            sizeof(mbi),
////            &returnLength
////        ) >= 0) {
////            if (mbi.State == MEM_COMMIT &&
////                mbi.Protect == PAGE_EXECUTE_READWRITE &&
////                mbi.AllocationProtect == PAGE_EXECUTE_READWRITE &&
////                mbi.Type == MEM_PRIVATE)
////            {
////                auto mem = static_cast<uint8_t*>(mbi.BaseAddress);
////                if (mem[0] == 0x48 && mem[1] == 0x89 && mem[2] == 0x5C && mem[3] == 0x24) {
////
////                    return reinterpret_cast<std::uintptr_t>(mbi.BaseAddress);
////                }
////            }
////            address += mbi.RegionSize;
////        }
////        return 0;
////    }
////
////    static void* create_trampoline(void* detour) {
////        constexpr size_t size = 32;
////        alignas(16) uint8_t shellcode[size] = {};
////        constexpr std::array<uint8_t, 4> nops = { 0x90, 0x66, 0x0F, 0x1F };
////        size_t offset = 2 + (hw_rand() % 10);
////        for (size_t i = 0; i < offset; ++i)
////            shellcode[i] = nops[hw_rand() % nops.size()];
////
////        size_t p = offset;
////
////        shellcode[p++] = 0x48;
////        shellcode[p++] = 0xB8;
////        *reinterpret_cast<void**>(shellcode + p) = detour;
////        p += 8;
////        shellcode[p++] = 0xFF; shellcode[p++] = 0xE0;
////        while (p < size) shellcode[p++] = nops[hw_rand() % nops.size()];
////
////        void* trampoline = VirtualAlloc(nullptr, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
////        if (trampoline) {
////            memcpy(trampoline, shellcode, size);
////            DWORD old;
////            VirtualProtect(trampoline, size, PAGE_EXECUTE_READ, &old);
////        }
////        return trampoline;
////    }
////
////    static std::uintptr_t bind_to_cave(void* detour) {
////        constexpr std::array<uint8_t, 18> stub = {
////            0xFF, 0x25, 0x00, 0x00, 0x00, 0x00,
////            0,0,0,0,0,0,0,0,
////            0xCC,0xCC,0xCC,0xCC
////        };
////
////        std::array<uint8_t, 18> code = stub;
////        *reinterpret_cast<void**>(&code[6]) = detour;
////
////        std::uintptr_t addr = rwx_cave + 0x100 + (total_functions * code.size());
////        __movsb(reinterpret_cast<uint8_t*>(addr), code.data(), code.size());
////        total_functions++;
////        return addr;
////    }
////
////
////public:
////    static size_t get_vtable_length(std::uintptr_t* vtab) {
////        size_t count = 0;
////        while (vtab[count] &&
////            vtab[count] > 0x10000 &&
////            vtab[count] < 0x00007FFFFFFF0000) ++count;
////        return count;
////    }
////
////    void* fg34hh3478h87f34h378g4h34g343g(void* instance, void* detour, int index) {
////        if (!instance || !detour || index < 0) return nullptr;
////
////        if (rwx_cave == 0) rwx_cave = find_code_cave();
////
////        object = instance;
////        orig_vtable = *reinterpret_cast<std::uintptr_t**>(object);
////        if (!orig_vtable) return nullptr;
////
////        vtable_len = get_vtable_length(orig_vtable);
////        if (index >= static_cast<int>(vtable_len)) return nullptr;
////
////        shadow_vtable.reset(new std::uintptr_t[vtable_len]);
////        memcpy(shadow_vtable.get(), orig_vtable, sizeof(std::uintptr_t) * vtable_len);
////
////        void* original_func = reinterpret_cast<void*>(shadow_vtable[index]);
////        void* trampoline = nullptr;
////        bool is_cave = false;
////
////        if (rwx_cave) {
////            trampoline = reinterpret_cast<void*>(bind_to_cave(detour));
////            is_cave = true;
////        }
////
////        if (!trampoline) {
////            trampoline = create_trampoline(detour);
////            if (!trampoline) {
////                shadow_vtable.reset();
////                return nullptr;
////            }
////        }
////
////        shadow_vtable[index] = reinterpret_cast<std::uintptr_t>(trampoline);
////        trampolines.push_back({ trampoline, is_cave });
////
////        InterlockedExchangePointer(reinterpret_cast<void**>(object), shadow_vtable.get());
////
////        return original_func;
////    }
////
////    void restore() {
////        if (object && orig_vtable) {
////            InterlockedExchangePointer(reinterpret_cast<void**>(object), orig_vtable);
////        }
////
////        for (auto& ti : trampolines) {
////            if (ti.is_code_cave) {
////                constexpr std::array<uint8_t, 18> stub = {
////                    0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
////                    0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
////                    0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC
////                };
////                __movsb(static_cast<uint8_t*>(ti.address), stub.data(), stub.size());
////            }
////            else if (ti.address) {
////                VirtualFree(ti.address, 0, MEM_RELEASE);
////            }
////        }
////        trampolines.clear();
////    }
////
////    ~VTableHook() {
////        restore();
////        if (rwx_cave && trampolines.empty()) {
////            total_functions = 0;
////        }
////    }
////};
//
//
//class shadow_vmt
//{
//public:
//
//    void virtual_hook(void* addr, void* pDes, int index, void** ret) {
//
//        SPOOF_FUNC
//
//            auto vtable = memory::read<uintptr_t*>(std::uintptr_t(addr));
//        int methods = 0;
//
//        for (int i = 0; memory::read<uintptr_t>((uintptr_t)vtable + (i * 0x8)); i++) methods++;
//
//        auto vtable_buf = new uint64_t[methods * 0x8];
//        for (int count = 0; count < methods; ++count) {
//            vtable_buf[count] = memory::read<uintptr_t>((uintptr_t)vtable + (count * 0x8));
//
//            *ret = (void*)vtable[index];
//
//            vtable_buf[index] = (uintptr_t)(pDes);
//
//            memory::write<uint64_t*>(std::uintptr_t(addr), vtable_buf);
//        }
//
//    }
//
//    void VMT(void* addr, void* pDes, int index, void** ret)
//    {
//
//        SPOOF_FUNC
//
//            auto vtable = *(uintptr_t**)addr;
//        int methods = 0;
//        do {
//            ++methods;
//        } while (*(uintptr_t*)((uintptr_t)vtable + (methods * 0x8)));
//        auto vtable_buf = new uint64_t[methods * 0x8];
//        for (auto count = 0; count < methods; ++count) {
//            vtable_buf[count] = *(uintptr_t*)((uintptr_t)vtable + (count * 0x8));
//
//            *ret = (void*)vtable[index];
//
//            vtable_buf[index] = (uintptr_t)(pDes);
//            *(uint64_t**)addr = vtable_buf;
//        }
//    }
//
//    void vhi3(void* instance, void* destination, int index, void** original) {
//
//        uintptr_t** vtable_ptr = reinterpret_cast<uintptr_t**>(instance);
//        uintptr_t* vtable = *vtable_ptr;
//
//        int method_count = 0;
//        while (vtable[method_count]) ++method_count;
//
//        uintptr_t* shadow_vtable = static_cast<uintptr_t*>(SPOOF_CALL(malloc)(sizeof(uintptr_t) * method_count));
//        if (!shadow_vtable) return;
//
//        SPOOF_CALL(memcpy)(shadow_vtable, vtable, sizeof(uintptr_t) * method_count);
//        *original = reinterpret_cast<void*>(shadow_vtable[index]);
//
//        BYTE shellcode[] = {
//            0x48, 0xB8,
//            0, 0, 0, 0, 0, 0, 0, 0,
//            0xFF, 0xE0
//        };
//        *reinterpret_cast<uintptr_t*>(&shellcode[2]) = reinterpret_cast<uintptr_t>(destination);
//
//        void* shell_tramp = SPOOF_CALL(VirtualAlloc)(nullptr, sizeof(shellcode), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
//        if (shell_tramp) {
//            SPOOF_CALL(memcpy)(shell_tramp, shellcode, sizeof(shellcode));
//            DWORD old_protect;
//            SPOOF_CALL(VirtualProtect)(shell_tramp, sizeof(shellcode), PAGE_EXECUTE_READ, &old_protect);
//        }
//        else {
//            SPOOF_CALL(free)(shadow_vtable);
//            return;
//        }
//
//        shadow_vtable[index] = reinterpret_cast<uintptr_t>(shell_tramp);
//        *vtable_ptr = shadow_vtable;
//    }
//
//    /*static uint32_t secureRand1() noexcept {
//        unsigned int val;
//        return _rdrand32_step(&val) ? val :
//            __rdtsc() ^ GetCurrentThreadId();
//    }
//
//    __declspec(noinline) void vhi33(
//        void* instance,
//        void* detour,
//        int index,
//        void** original
//    ) noexcept {
//        thread_local VTableHook hooker;
//
//        if (GetTickCount64() % 7919 < 500) {
//            volatile uint64_t waste = 0;
//            for (uint32_t i = 0; i < (secureRand1() % 1024); ++i) {
//                waste += _rotl64(secureRand1(), i % 64);
//            }
//        }
//
//        if (auto orig = hooker.fg34hh3478h87f34h378g4h34g343g(instance, detour, index)) {
//            if (original) *original = orig;
//        }
//        else {
//            if (original) *original = nullptr;
//        }
//    }*/
//
//    void __cdecl vhi4(void* instance, void* destination, int index, void** original) {
//
//        SPOOF_FUNC
//
//            static thread_local VTableHook hooker;
//        if (void* orig = hooker.fg34hh3478h87f34h378g4h34g343g(instance, destination, index)) {
//            if (original) *original = orig;
//        }
//        else {
//            if (original) *original = nullptr;
//        }
//
//    }
//
//    // GOOD
//
//    /*void vhi33(void* instance, void* destination, int index, void** original) {
//        thread_local VTableHook hooker;
//        if (void* orig = hooker.G35H7B9G3H499H4G334GHJ(instance, destination, index)) {
//            if (original) *original = orig;
//        }
//        else {
//            if (original) *original = nullptr;
//        }
//    }*/
//
//    // BASIC
//
//    /*void vhi33(void* instance, void* destination, int index, void** original) {
//        static VTableHook hooker;
//        void* orig = hooker.G35H7B9G3H499H4G334GHJ(instance, destination, index);
//        if (original) *original = orig;
//    }*/
//
//    /*template <typename type>
//    bool hook(uint64_t module_base, uint64_t address, int index, void* function, type* original)
//    {
//        g97hf23fh3h928f;
//        fg82f31gh78df23;
//        hh17d39h789d;
//
//        SPOOF_FUNC
//
//            this->virtual_table = *(uintptr_t**)(address);
//
//        if (reinterpret_cast<void*>(this->virtual_table[index]) != function)
//        {
//            while (this->virtual_table[this->vtable_size])
//            {
//                this->vtable_size++;
//            }
//
//            if (index < this->vtable_size)
//            {
//                this->allocated_vtable = reinterpret_cast<uintptr_t*>(fmemory::malloc(this->vtable_size * sizeof(uintptr_t), 0x10));
//
//                for (int i = 0; i < this->vtable_size; i++)
//                {
//                    this->allocated_vtable[i] = this->virtual_table[i];
//                }
//
//                *original = reinterpret_cast<type>(this->virtual_table[index]);
//
//                this->allocated_vtable[index] = reinterpret_cast<uintptr_t>(function);
//
//                *(uintptr_t**)(address) = this->allocated_vtable;
//
//                return true;
//            }
//        }
//
//        return false;
//
//        gh92g4h982fh9f23;
//        f7hfh473h89;
//        h2cd3gw67g6eqw2;
//    }*/
//
//    template <typename type>
//    bool bu3e2bbl23ere(void* object_ptr, void* function, int index, type* original)
//    {
//        // Get the object's vtable pointer (pointer-to-pointer)
//        uintptr_t** vtable_ptr = reinterpret_cast<uintptr_t**>(object_ptr);
//
//        // Dereference to get the actual vtable array (pointer to function pointers)
//        this->virtual_table = *vtable_ptr;
//
//        if (reinterpret_cast<void*>(this->virtual_table[index]) != function)
//        {
//            this->vtable_size = 0;
//            while (this->virtual_table[this->vtable_size])
//            {
//                this->vtable_size++;
//            }
//
//            if (index < this->vtable_size)
//            {
//                this->allocated_vtable = reinterpret_cast<uintptr_t*>(
//                    spoofed_malloc(this->vtable_size * sizeof(uintptr_t), PAGE_EXECUTE_READWRITE)
//                    );
//
//                memcpy(this->allocated_vtable, this->virtual_table, this->vtable_size * sizeof(uintptr_t));
//
//                *original = reinterpret_cast<type>(this->virtual_table[index]);
//                this->allocated_vtable[index] = reinterpret_cast<uintptr_t>(function);
//
//                // Replace the object's vtable pointer through the double pointer
//                *vtable_ptr = this->allocated_vtable;
//                return true;
//            }
//        }
//        return false;
//    }
//
//
//private:
//
//    uint64_t spoofed_malloc(int32_t size, uint32_t alignment)
//    {
//        return reinterpret_cast<uint64_t(__cdecl*)(int32_t, uint32_t, uintptr_t, void*)>(spoofcall_stub)(
//            size,
//            alignment,
//            0x46C4660,
//            (void*)&fmemory::malloc
//            );
//    }
//
//    uintptr_t* virtual_table;
//    uintptr_t* allocated_vtable;
//    int vtable_size;
//};