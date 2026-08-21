#pragma once
#include <windows.h>
#include <cstdint>

#pragma once
#include <windows.h>
#include <cstdint>

#include <array>
#include <vector>
#include <string>  
#include <chrono>
#include "definitions.hpp"
#include "spoof.h"

#define null NULL
#define class_ptr uintptr_t(this)



typedef enum _MEMORY_INFORMATION_CLASS {
    MemoryBasicInformation
} MEMORY_INFORMATION_CLASS;

extern "C" NTSTATUS __query_virtual_memory(
    HANDLE p_handle,
    void* base_addr,
    MEMORY_INFORMATION_CLASS memory_info_class,
    void* mbi,
    std::size_t mbi_length,
    std::size_t* mbi_out_length
);

namespace memory
{
    inline uintptr_t module_base = null;

    inline bool is_bad_write_ptr(LPVOID ptr, uint64_t size)
    {
        SPOOF_FUNC
            return ptr ? false : true;
    }

    inline bool valid_pointer(uint64_t address)
    {
        SPOOF_FUNC
            if (!is_bad_write_ptr((LPVOID)address, (uint64_t)8)) return true;
            else return false;
    }

    inline bool IsValidPointer(uintptr_t address, bool requireWrite = false) {
        MEMORY_BASIC_INFORMATION mbi;
        if (!VirtualQuery(reinterpret_cast<LPCVOID>(address), &mbi, sizeof(mbi))) {
            return false;
        }
        if (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS)) {
            return false;
        }
        if (requireWrite) {
            // List of writable page protections (for usermode)
            if (!(mbi.Protect & PAGE_READWRITE) &&
                !(mbi.Protect & PAGE_WRITECOPY) &&
                !(mbi.Protect & PAGE_EXECUTE_READWRITE) &&
                !(mbi.Protect & PAGE_EXECUTE_WRITECOPY)) {
                return false;
            }
        }
        return true;
    }

    template<typename t>
    inline t read(DWORD_PTR address, const t& def = t())
    {
        SPOOF_FUNC
            if (SPOOF_CALL(valid_pointer)(address)) {
                SPOOF_FUNC
                    return *(t*)(address);
            }
    }

    /*template <typename T>
    T ReadStub(std::uintptr_t Address)
    {
        return reinterpret_cast<T(*)(std::uintptr_t)>(memory::module_base + offsets::TriggerVEH)(Address - 0x8);
    }*/

    template<typename t>
    inline bool write(DWORD_PTR address, const t& value)
    {
        SPOOF_FUNC
            if (SPOOF_CALL(valid_pointer)(address)) {
                SPOOF_FUNC
                    * (t*)(address) = value;
                return true;
            }
        return false;
    }


    inline uint64_t get_module(wchar_t* name) {
        SPOOF_FUNC
            const ntos::peb* peb = reinterpret_cast<ntos::peb*>(__readgsqword(0x60));
        if (!peb) return uint64_t(0);

        const ntos::list_entry head = peb->Ldr->InMemoryOrderModuleList;

        for (auto curr = head; curr.Flink != &peb->Ldr->InMemoryOrderModuleList; curr = *curr.Flink) {
            ntos::ldr_data_table_entry* mod = reinterpret_cast<ntos::ldr_data_table_entry*>(contains_record(curr.Flink, ntos::ldr_data_table_entry, InMemoryOrderLinks));

            if (mod->BaseDllName.Buffer)
                if (crt::wcsicmp_insensitive(mod->BaseDllName.Buffer, name))
                {
                    SPOOF_FUNC
                        return uint64_t(mod->DllBase);
                }
        }

        return uint64_t(0);
    }

    inline uintptr_t resolve_api(const char* module, const char* func) {

        SPOOF_FUNC

            auto hMod = SPOOF_CALL(LoadLibraryA)(module);
        return reinterpret_cast<uintptr_t>(SPOOF_CALL(GetProcAddress)(hMod, func));
    }

    inline void clear_pe_header(HMODULE hModule) {

        SPOOF_FUNC

            DWORD old;
        SPOOF_CALL(VirtualProtect)(hModule, 0x1000, PAGE_EXECUTE_READWRITE, &old);
        SPOOF_CALL(memset)(hModule, 0, 0x1000);
        SPOOF_CALL(VirtualProtect)(hModule, 0x1000, old, &old);
    }
}