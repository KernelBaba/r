#pragma once
#define _AMD64_
#include <cstdint>
#include <map>
#include <vector>
#include <minwindef.h>
#include <memoryapi.h>

#include <intrin.h>


extern "C"  void spoofcall_stub();

extern "C" uintptr_t proxy_call_returns[];
extern "C" size_t proxy_call_fakestack_size;
extern "C" uintptr_t* proxy_call_fakestack;

#define FIELD_OFFSET(type, field)    ((long)(LONG_PTR)&(((type *)0)->field))

#define IMAGE_FIRST_SECTION( ntheader ) ((PIMAGE_SECTION_HEADER)        \
    ((ULONG_PTR)(ntheader) +                                            \
     FIELD_OFFSET( IMAGE_NT_HEADERS, OptionalHeader ) +                 \
     ((ntheader))->FileHeader.SizeOfOptionalHeader   \
    ))

inline unsigned custom_rand(int start, int end)
{
	int start_range = start;
	int end_range = end;

	static unsigned int rand = 0xACE1U;

	if (start_range == end_range)
	{
		return start_range;
	}

	rand += 0x3AD;
	rand %= (end_range - start_range + 1);

	while (rand < start_range)
	{
		rand = rand + (end_range - start_range + 1);
	}

	return rand;
}




inline void initialize_spoofcall(uint8_t* module_, uint32_t max_fakestack = 12)
{
	std::map<int8_t, std::vector<uintptr_t>> proxy_clean_returns;

	auto dos = reinterpret_cast<IMAGE_DOS_HEADER*>(module_);
	auto nt = reinterpret_cast<IMAGE_NT_HEADERS*>(module_ + dos->e_lfanew);
	auto image_size = nt->OptionalHeader.SizeOfImage;

	auto section = IMAGE_FIRST_SECTION(nt);

	MEMORY_BASIC_INFORMATION mbi;

	for (auto i = 0; i < nt->FileHeader.NumberOfSections; i++)
	{
		if ((section->Characteristics & 0x02000000) == 0)
		{
			auto address = module_ + section->VirtualAddress;
			while (true)
			{
				__stosb((PBYTE)&mbi, 0, sizeof(mbi));

				if (!VirtualQuery(address, &mbi, sizeof(mbi))) break;

				auto base_page = (uint8_t*)mbi.BaseAddress;

				if (mbi.Protect == 0x20 ||
					mbi.Protect == 0x40 ||
					mbi.Protect == 0x80)
				{
					for (auto i = 0u; i < (mbi.RegionSize - 0x10); i++)
					{
						if (i >= 6 && base_page[i - 6] == 0xFF &&
							base_page[i - 5] == 0x15 &&
							base_page[i] == 0x48 &&
							base_page[i + 1] == 0x83 &&
							base_page[i + 2] == 0xC4 &&
							base_page[i + 4] == 0xC3)
						{


							proxy_clean_returns[base_page[i + 3]].push_back(uintptr_t(base_page + i));
						}
					}
				}
				address = base_page + mbi.RegionSize;
				if (address >= (module_ + section->VirtualAddress + section->Misc.VirtualSize))
					break;
			}
		}
		section++;
	}


	std::vector<int8_t> proxy_clean_returns_keys;
	proxy_clean_returns_keys.reserve(proxy_clean_returns.size());

	std::vector<uintptr_t> fakestack;
	fakestack.reserve(max_fakestack * 2);


	for (auto& it : proxy_clean_returns)
	{
		const auto index = (it.first / sizeof(uintptr_t));
		proxy_call_returns[index] = it.second.at(custom_rand(10, 30) % it.second.size());

		if (index < 10 && index % 2 == 1)
			proxy_clean_returns_keys.push_back(it.first);
	}

	while (fakestack.size() < max_fakestack)
	{
		const auto pseudo_random_number = custom_rand(10, 30);
		const auto return_length = proxy_clean_returns_keys.at(pseudo_random_number % proxy_clean_returns_keys.size());
		const auto params = (return_length / sizeof(uintptr_t));
		const auto& address_array = proxy_clean_returns[return_length];
		const auto random_address = address_array.at(pseudo_random_number % address_array.size());

		fakestack.push_back(random_address);
		for (auto i = 0u; i < params; i++)
			fakestack.push_back(uintptr_t(module_) + (custom_rand(10, 30) % image_size));
	}

	proxy_call_fakestack_size = fakestack.size();
	proxy_call_fakestack = new uintptr_t[fakestack.size()];
	__movsb((PBYTE)proxy_call_fakestack, (BYTE*)fakestack.data(), proxy_call_fakestack_size * sizeof(uintptr_t));



}