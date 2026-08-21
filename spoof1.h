#pragma once

#ifdef _KERNEL_MODE
#include <ntddk.h>
#include <ntdef.h>
#else
#include <Windows.h>
#include <utility>
#endif

#include <intrin.h>

/*
 *  Copyright 2022 Barracudach
 *
 * Licensed under the Apache License, Version 2.0
 *
 * Distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND.
 */

#define SPOOF_FUNC CallSpoofer::SpoofFunction spoof(_AddressOfReturnAddress());
#ifdef _KERNEL_MODE
#define SPOOF_CALL1(ret_type, name) (CallSpoofer::SafeCall<ret_type, std::remove_reference_t<decltype(*name)>>(name))
#else
#define SPOOF_CALL1(name) (CallSpoofer::SafeCall(name))
#endif

#define MAX_FUNC_BUFFERED 100
#define SHELLCODE_GENERATOR_SIZE 500

namespace CallSpoofer
{
#ifdef _KERNEL_MODE
    typedef unsigned __int64 uintptr_t, size_t;
#endif

    class SpoofFunction
    {
    public:
        uintptr_t temp = 0;
        const uintptr_t xor_key = 0xFF00FF00FF00FF00;
        void* ret_addr_in_stack = 0;

        SpoofFunction(void* addr) : ret_addr_in_stack(addr)
        {
            temp = *(uintptr_t*)ret_addr_in_stack;
            temp ^= xor_key;
            *(uintptr_t*)ret_addr_in_stack = 0;
        }

        ~SpoofFunction()
        {
            temp ^= xor_key;
            *(uintptr_t*)ret_addr_in_stack = temp;
        }
    };

#ifdef _KERNEL_MODE
    __forceinline PVOID LocateShellCode(PVOID func, size_t size = SHELLCODE_GENERATOR_SIZE)
    {
        void* addr = ExAllocatePoolWithTag(NonPagedPool, size, (ULONG)'File');
        if (!addr)
            return nullptr;
        return memcpy(addr, func, size);
    }
#else
    __forceinline PVOID LocateShellCode(PVOID func, size_t size = SHELLCODE_GENERATOR_SIZE)
    {
        void* addr = VirtualAlloc(NULL, size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        if (!addr)
            return nullptr;
        return memcpy(addr, func, size);
    }
#endif

    template <typename RetType, typename Func, typename... Args>
    __forceinline decltype(auto) ShellCodeGenerator(Func f, Args&&... args)
    {
        const uintptr_t xor_key = 0xFF00FF00FF00FF00;
        void* ret_addr_in_stack = _AddressOfReturnAddress();
        uintptr_t temp = *(uintptr_t*)ret_addr_in_stack;
        temp ^= xor_key;
        *(uintptr_t*)ret_addr_in_stack = 0;

        if constexpr (std::is_same_v<RetType, void>)
        {
            f(std::forward<Args>(args)...);
            temp ^= xor_key;
            *(uintptr_t*)ret_addr_in_stack = temp;
        }
        else
        {
            RetType ret = f(std::forward<Args>(args)...);
            temp ^= xor_key;
            *(uintptr_t*)ret_addr_in_stack = temp;
            return ret;
        }
    }

#ifdef _KERNEL_MODE
    template<typename RetType, class Func>
#else
    template<class Func>
#endif
    class SafeCall
    {
        Func* funcPtr;

    public:
        explicit SafeCall(Func* func) : funcPtr(func) {}

        template<typename... Args>
        __forceinline decltype(auto) operator()(Args&&... args)
        {
            SPOOF_FUNC;

#ifdef _KERNEL_MODE
            using return_type = RetType;
            using p_shell_code_generator_type = decltype(&ShellCodeGenerator<RetType, Func*, Args&&...>);
            PVOID self_addr = static_cast<PVOID>(&ShellCodeGenerator<RetType, Func*, Args&&...>);
#else
            using return_type = decltype(std::declval<Func>()(std::declval<Args>()...));
            using p_shell_code_generator_type = decltype(&ShellCodeGenerator<return_type, Func*, Args&&...>);
            p_shell_code_generator_type self_addr = static_cast<p_shell_code_generator_type>(&ShellCodeGenerator<return_type, Func*, Args&&...>);
#endif

            p_shell_code_generator_type p_shellcode{};

            static size_t count{};
            static p_shell_code_generator_type orig_generator[MAX_FUNC_BUFFERED]{};
            static p_shell_code_generator_type alloc_generator[MAX_FUNC_BUFFERED]{};

            unsigned index{};
            while (orig_generator[index])
            {
                if (orig_generator[index] == self_addr)
                {
                    p_shellcode = alloc_generator[index];
                    break;
                }
                index++;
            }

            if (!p_shellcode)
            {
                p_shellcode = reinterpret_cast<p_shell_code_generator_type>(LocateShellCode(self_addr));
                orig_generator[count] = self_addr;
                alloc_generator[count] = p_shellcode;
                count++;
            }

            return p_shellcode(funcPtr, std::forward<Args>(args)...);
        }
    };
}
