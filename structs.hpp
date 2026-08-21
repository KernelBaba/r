#pragma once
#include <string>
#include <cstdint>

#include "crt.hpp"

class fname {
public:
	fname() : comparison_index(std::uint32_t()), number(std::int32_t()) {};
	fname(std::uint32_t index) : comparison_index(index), number(std::int32_t()) {};

public:
	std::uint32_t comparison_index;
	std::int32_t number;
};

class fkey {
public:
	fkey() : name() {}
	fkey(fname name) : name(name) {}

public:
	fname name;
	std::uint8_t details[24] = {};
};

class ftextdata {
public:
	char pad_0[0x30];
	wchar_t* name;
	__int32 length;
};

class ftext {
public:
	ftextdata* data;
	char pad_0[0x10];

	wchar_t* c_str() const {
		if (this->data) {
			return data->name;
		}

		return nullptr;
	}
};

template <class type>
struct tarray {
public:
	tarray() { this->data = nullptr; this->count = this->max = 0; };

	type* data;
	std::int32_t count, max;

	type& operator[](int i) {
		return this->data[i];
	};

	int size() {
		return this->count;
	}

	bool valid(int i) {
		return bool(i < this->count);
	}

	int Num() const
	{
		return count;
	}

	void add(const type& item) {
		if (count >= max) {
			std::int32_t new_max = (max == 0) ? 1 : max * 2;
			type* new_data = (type*)::operator new[](new_max * sizeof(type));
			if (data) {
				memcpy(new_data, data, count * sizeof(type));
				::operator delete[](data);
			}
			data = new_data;
			max = new_max;
		}
		data[count++] = item;
	}

};


class fstring : public tarray<wchar_t>
{
public:
	inline fstring()
	{
	};

	fstring(const wchar_t* other)
	{
		max = count = *other ? static_cast<int>(crt::wcslen(other)) + 1 : 0;

		if (count)
		{
			data = const_cast<wchar_t*>(other);
		}
	};

	fstring(const wchar_t* other, int count)
	{
		data = const_cast<wchar_t*>(other);;
		max = count = count;
	};

	bool is_valid() const
	{
		return data != nullptr;
	}

	const wchar_t* wide() const
	{
		return data;
	}

	const wchar_t* c_str() const
	{
		return this->data;
	}

	std::string to_str() const
	{
		auto length = crt::wcslen(data);

		std::string str(length, '\0');

		for (size_t i = 0; i < length; ++i) {
			wchar_t wc = data[i];

			if (wc >= 0 && wc < 128) {
				str[i] = static_cast<char>(wc);
			}
			else {
				str[i] = '?';
			}
		}

		return str;
	}

	std::string ToString() const
	{
		auto length = std::wcslen(data);

		std::string str(length, '\0');

		std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(data, data + length, '?', &str[0]);

		return str;
	}
};

struct flinearcolor
{
	float r, g, b, a;
	flinearcolor() : r(0), g(0), b(0), a(0) {}
	flinearcolor(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
	flinearcolor(float r, float g, float b) : r(r), g(g), b(b), a(1.f) {}
};

enum class earesalliance : uint8_t {
	ally = 0,
	enemy = 1,
	neutral = 2,
	any = 3,
	count = 4
};

enum class EBlendMode : uint8_t
{
	BLEND_Opaque = 0,
	BLEND_Masked = 1,
	BLEND_Translucent = 2,
	BLEND_Additive = 3,
	BLEND_Modulate = 4,
	BLEND_AlphaComposite = 5,
	BLEND_AlphaHoldout = 6,
	BLEND_MAX = 7,
};

// Define the FPlane struct
struct FPlane {
	float X;
	float Y;
	float Z;
	float W;
};

// Define the FMatrix struct using FPlane
struct FMatrix {
	FPlane XPlane;
	FPlane YPlane;
	FPlane ZPlane;
	FPlane WPlane;
};
