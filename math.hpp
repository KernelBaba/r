#pragma once

#pragma once
#include <cmath>
#define _USE_MATH_DEFINES
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif





struct FRotator
{
	double Pitch, Yaw, Roll;

	FRotator()
		: Pitch(0.0), Yaw(0.0), Roll(0.0)
	{
	}

	FRotator(double pitch, double yaw, double roll) : Pitch(pitch), Yaw(yaw), Roll(roll) {}

	FRotator operator+ (const FRotator& other) const { return FRotator(Pitch + other.Pitch, Yaw + other.Yaw, Roll + other.Roll); }

	FRotator operator- (const FRotator& other) const { return FRotator(Pitch - other.Pitch, Yaw - other.Yaw, Roll - other.Roll); }

	FRotator operator* (double scalar) const { return FRotator(Pitch * scalar, Yaw * scalar, Roll * scalar); }

	FRotator& operator=  (const FRotator& other) { Pitch = other.Pitch; Yaw = other.Yaw; Roll = other.Roll; return *this; }

	FRotator& operator+= (const FRotator& other) { Pitch += other.Pitch; Yaw += other.Yaw; Roll += other.Roll; return *this; }

	FRotator& operator-= (const FRotator& other) { Pitch -= other.Pitch; Yaw -= other.Yaw; Roll -= other.Roll; return *this; }

	FRotator& operator*= (const double other) { Yaw *= other; Pitch *= other; Roll *= other; return *this; }

	struct FQuat Quaternion() const;
};

struct fvector2d
{
	double x, y;

	fvector2d() : x(0.0), y(0.0) {}

	fvector2d(double x, double y) : x(x), y(y) {}

	fvector2d operator + (const fvector2d& other) const { return fvector2d(x + other.x, y + other.y); }

	fvector2d operator - (const fvector2d& other) const { return fvector2d(x - other.x, y - other.y); }

	fvector2d operator * (double scalar) const { return fvector2d(x * scalar, y * scalar); }

	fvector2d& operator =  (const fvector2d& other) { x = other.x; y = other.y; return *this; }

	fvector2d& operator += (const fvector2d& other) { x += other.x; y += other.y; return *this; }

	fvector2d& operator -= (const fvector2d& other) { x -= other.x; y -= other.y; return *this; }

	fvector2d& operator *= (const double other) { x *= other; y *= other; return *this; }

	friend bool operator == (const fvector2d& one, const fvector2d& two) { return one.x == two.x && one.y == two.y; }

	friend bool operator != (const fvector2d& one, const fvector2d& two) { return !(one == two); }

	friend bool operator > (const fvector2d& one, const fvector2d& two) { return one.x > two.x && one.y > two.y; }

	friend bool operator < (const fvector2d& one, const fvector2d& two) { return one.x < two.x && one.y < two.y; }

	bool is_valid() { return !(x == 0.0 || y == 0.0); }
};

class frotator1 {
public:
	frotator1() : pitch2(0.f), yaw2(0.f), roll2(0.f) {}
	frotator1(double pitch, double yaw) : pitch2(pitch), yaw2(yaw), roll2(0.f) {}
	frotator1(double pitch, double yaw, double roll) : pitch2(pitch), yaw2(yaw), roll2(roll) {}

	frotator1 operator + (const frotator1& other) const { return { this->pitch2 + other.pitch2, this->yaw2 + other.yaw2, this->roll2 + other.roll2 }; }
	frotator1 operator - (const frotator1& other) const { return { this->pitch2 - other.pitch2, this->yaw2 - other.yaw2, this->roll2 - other.roll2 }; }
	frotator1 operator * (double scalar) const { return { this->pitch2 * scalar, this->yaw2 * scalar, this->roll2 * scalar }; }
	frotator1 operator / (double divide) const { return { this->pitch2 / divide, this->yaw2 / divide, this->roll2 / divide }; }

	frotator1& operator *= (const double other) { this->yaw2 *= other; this->pitch2 *= other; this->roll2 *= other; return *this; }
	frotator1& operator /= (const double other) { this->yaw2 /= other; this->pitch2 /= other; this->roll2 /= other; return *this; }

	frotator1& operator =  (const frotator1& other) { this->pitch2 = other.pitch2; this->yaw2 = other.yaw2; this->roll2 = other.roll2; return *this; }
	frotator1& operator += (const frotator1& other) { this->pitch2 += other.pitch2; this->yaw2 += other.yaw2; this->roll2 += other.roll2; return *this; }
	frotator1& operator -= (const frotator1& other) { this->pitch2 -= other.pitch2; this->yaw2 -= other.yaw2; this->roll2 -= other.roll2; return *this; }
	frotator1& operator *= (const frotator1& other) { this->pitch2 *= other.pitch2; this->yaw2 *= other.yaw2; this->roll2 *= other.roll2; return *this; }
	frotator1& operator /= (const frotator1& other) { this->pitch2 /= other.pitch2; this->yaw2 /= other.yaw2; this->roll2 /= other.roll2; return *this; }

	operator bool()
	{
		return bool(this->pitch2 && this->yaw2 && this->roll2);
	}

	friend bool operator==(const frotator1& first, const frotator1& second)
	{
		return first.pitch2 == second.pitch2 && first.yaw2 == second.yaw2 && first.roll2 == second.roll2;
	}

	friend bool operator!=(const frotator1& first, const frotator1& second)
	{
		return !(first == second);
	}


public:
	double pitch2 = 0.f;
	double yaw2 = 0.f;
	double roll2 = 0.f;
};

struct fvector
{
	double x, y, z;

	fvector() : x(0.0), y(0.0), z(0.0) {}

	fvector(double x, double y, double z) : x(x), y(y), z(z) {}

	fvector(double InF) : x(InF), y(InF), z(InF) {}

	fvector operator+(const fvector& other) const { return fvector(x + other.x, y + other.y, z + other.z); }

	fvector operator-(const fvector& other) const { return fvector(x - other.x, y - other.y, z - other.z); }

	fvector operator*(const fvector& V) const { return fvector(x * V.x, y * V.y, z * V.z); }

	fvector operator/(const fvector& V) const { return fvector(x / V.x, y / V.y, z / V.z); }

	bool operator==(const fvector& V) const { return x == V.x && y == V.y && z == V.z; }

	bool operator!=(const fvector& V) const { return x != V.x || y != V.y || z != V.z; }

	fvector operator-() const { return fvector(-x, -y, -z); }

	fvector operator+(double Bias) const { return fvector(x + Bias, y + Bias, z + Bias); }

	fvector operator-(double Bias) const { return fvector(x - Bias, y - Bias, z - Bias); }

	fvector operator*(double Scale) const { return fvector(x * Scale, y * Scale, z * Scale); }

	fvector operator/(double Scale) const { const double RScale = 1.0 / Scale; return fvector(x * RScale, y * RScale, z * RScale); }

	fvector operator=(const fvector& V) { x = V.x; y = V.y; z = V.z; return *this; }

	fvector operator+=(const fvector& V) { x += V.x; y += V.y; z += V.z; return *this; }

	fvector operator-=(const fvector& V) { x -= V.x; y -= V.y; z -= V.z; return *this; }

	fvector operator*=(const fvector& V) { x *= V.x; y *= V.y; z *= V.z; return *this; }

	fvector operator/=(const fvector& V) { x /= V.x; y /= V.y; z /= V.z; return *this; }

	fvector operator*=(double Scale) { x *= Scale; y *= Scale; z *= Scale; return *this; }

	fvector operator/=(double V) { const double RV = 1.0 / V; x *= RV; y *= RV; z *= RV; return *this; }

	double operator|(const fvector& V) const { return x * V.x + y * V.y + z * V.z; }

	fvector operator^(const fvector& V) const { return fvector(y * V.z - z * V.y, z * V.x - x * V.z, x * V.y - y * V.x); }

	bool is_valid() { return !(x == 0.0 || y == 0.0); }

	bool is_null() { return x == 0.0 && y == 0.0 && z == 0.0; }

	inline double distance(fvector v) { double dx = x - v.x, dy = y - v.y, dz = z - v.z; return sqrt((dx * dx) + (dy * dy) + (dz * dz)) * 0.03048; }

	double size() const { return sqrt(x * x + y * y + z * z); }

	double size_2d() const { return sqrt(x * x + y * y); }

	double length() const { return sqrt(x * x + y * y + z * z); }

	double distance_squared(const fvector& a, const fvector& b) {
		double dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
		return dx * dx + dy * dy + dz * dz;
	}

	double size_squared() const { return x * x + y * y + z * z; }

	fvector GetSafeNormal(double Tolerance = 1.e-4) {
		double SquareSum = x * x + y * y + z * z;
		if (SquareSum < Tolerance) return fvector(0.0);
		double Scale = 1.0 / sqrt(SquareSum);
		return fvector(x * Scale, y * Scale, z * Scale);
	}

	fvector GetSafeNormal2D(double Tolerance = 1.e-4) const {
		double SquareSum = x * x + y * y;
		if (SquareSum < Tolerance) return fvector(0.0);
		double Scale = 1.0 / sqrt(SquareSum);
		return fvector(x * Scale, y * Scale, z);
	}

	frotator1 rotation() const {
		frotator1 rot;
		rot.yaw2 = atan2(y, x) * (180.0 / 3.14159265358979323846);
		rot.pitch2 = atan2(z, sqrt(x * x + y * y)) * (180.0 / 3.14159265358979323846);
		rot.roll2 = 0.0;
		return rot;
	}

	double dot(fvector other) { return x * other.x + y * other.y + z * other.z; }
	inline static double DotProduct(const fvector& A, const fvector& B)
	{
		return (A.x * B.x) + (A.y * B.y) + (A.z * B.z);
	}
	fvector get_normalized() {
		double len_sqr = x * x + y * y + z * z;
		if (len_sqr < 1e-6) return fvector(0.0, 0.0, 0.0);
		double inv_len = 1.0 / sqrt(len_sqr);
		return fvector(x * inv_len, y * inv_len, z * inv_len);
	}

	void normalize() {
		double len = sqrt(x * x + y * y + z * z);
		if (len > 0.0) {
			double inv_len = 1.0 / len;
			x *= inv_len; y *= inv_len; z *= inv_len;
		}
	}

	float Size() {
		return std::sqrt(x * x + y * y + z * z);
	}

	fvector Vector() {
		float radX = x * (3.14159265359f / 180.0f);
		float radY = y * (3.14159265359f / 180.0f);

		float cosX = cosf(radX);
		float sinX = sinf(radX);
		float cosY = cosf(radY);
		float sinY = sinf(radY);

		return fvector(cosX * cosY, cosX * sinY, sinX);
	}

	void Normalize() {
		float len = Size();
		if (len > 0.00001f) {
			x /= len;
			y /= len;
			z /= len;
		}
	}

};

class frotator {
public:
	frotator() : pitch(0), yaw(0), roll(0) {}
	frotator(double pitch, double yaw) : pitch(pitch), yaw(yaw), roll(0) {}
	frotator(double pitch, double yaw, double roll) : pitch(pitch), yaw(yaw), roll(roll) {}

	frotator operator + (const frotator& other) const { return { this->pitch + other.pitch, this->yaw + other.yaw, this->roll + other.roll }; }
	frotator operator - (const frotator& other) const { return { this->pitch - other.pitch, this->yaw - other.yaw, this->roll - other.roll }; }
	frotator operator * (double scalar) const { return { this->pitch * scalar, this->yaw * scalar, this->roll * scalar }; }
	frotator operator / (double divide) const { return { this->pitch / divide, this->yaw / divide, this->roll / divide }; }

	frotator& operator *= (const double other) { this->yaw *= other; this->pitch *= other; this->roll *= other; return *this; }
	frotator& operator /= (const double other) { this->yaw /= other; this->pitch /= other; this->roll /= other; return *this; }

	frotator& operator =  (const frotator& other) { this->pitch = other.pitch; this->yaw = other.yaw; this->roll = other.roll; return *this; }
	frotator& operator += (const frotator& other) { this->pitch += other.pitch; this->yaw += other.yaw; this->roll += other.roll; return *this; }
	frotator& operator -= (const frotator& other) { this->pitch -= other.pitch; this->yaw -= other.yaw; this->roll -= other.roll; return *this; }
	frotator& operator *= (const frotator& other) { this->pitch *= other.pitch; this->yaw *= other.yaw; this->roll *= other.roll; return *this; }
	frotator& operator /= (const frotator& other) { this->pitch /= other.pitch; this->yaw /= other.yaw; this->roll /= other.roll; return *this; }

	operator bool()
	{
		return bool(this->pitch && this->yaw && this->roll);
	}

	friend bool operator==(const frotator& first, const frotator& second)
	{
		return first.pitch == second.pitch && first.yaw == second.yaw && first.roll == second.roll;
	}

	friend bool operator!=(const frotator& first, const frotator& second)
	{
		return !(first == second);
	}

	double pitch1, yaw1, roll1;

	fvector to_vector() const
	{
		double CP = cos(pitch * 3.14159265358979323846 / 180.0);
		double SP = sin(pitch * 3.14159265358979323846 / 180.0);
		double CY = cos(yaw * 3.14159265358979323846 / 180.0);
		double SY = sin(yaw * 3.14159265358979323846 / 180.0);
		return fvector(CP * CY, CP * SY, -SP);
	}

	void normalize()
	{
		while (yaw > 180.0)  yaw -= 360.0;
		while (yaw < -180.0) yaw += 360.0;

		if (pitch > 89.0)  pitch = 89.0;
		if (pitch < -89.0) pitch = -89.0;

		if (roll > 180.0)  roll -= 360.0;
		if (roll < -180.0) roll += 360.0;
	}

	bool is_valid() const
	{
		return !(std::isnan(pitch) || std::isnan(yaw) || std::isnan(roll));
	}


public:
	double pitch = 0;
	double yaw = 0;
	double roll = 0;
};

struct alignas(16) fplane : public fvector {
	float w;
};


static void normalize(fvector& in)
{
	if (in.x > 89.f) in.x -= 360.f;
	else if (in.x < -89.f) in.x += 360.f;

	while (in.y > 180)in.y -= 360;
	while (in.y < -180)in.y += 360;
	in.z = 0;
}

static fvector smooth(fvector target, fvector delta_rotation, double smooth) {
	fvector diff = target - delta_rotation;
	normalize(diff);
	return delta_rotation + diff / smooth;
}

struct linear_values
{
	float h;
	float u;
	float v;
};

struct fquat
{
	double x;
	double y;
	double z;
	double w;

	fvector RotateVector(const fvector& V) const
	{
		double vx = V.x, vy = V.y, vz = V.z;

		double qx = x, qy = y, qz = z, qw = w;

		double ix = qw * vx + qy * vz - qz * vy;
		double iy = qw * vy + qz * vx - qx * vz;
		double iz = qw * vz + qx * vy - qy * vx;
		double iw = -qx * vx - qy * vy - qz * vz;

		double rx = ix * qw + iw * -qx + iy * -qz - iz * -qy;
		double ry = iy * qw + iw * -qy + iz * -qx - ix * -qz;
		double rz = iz * qw + iw * -qz + ix * -qy - iy * -qx;

		return { static_cast<float>(rx), static_cast<float>(ry), static_cast<float>(rz) };
	}
};

struct fmath {
	static __forceinline void sin_cos(float* ScalarSin, float* ScalarCos, float  Value);
	static __forceinline float fmod(float X, float Y);
	template<class T>
	static __forceinline T clam(const T X, const T Min, const T Max) { return X < Min ? Min : X < Max ? X : Max; }
	template<class T>
	static __forceinline T Min(const T A, const T B) { return A < B ? A : B; }
	template<class T>
	static __forceinline T Max(const T A, const T B) { return A > B ? A : B; }
	template<class T>
	static __forceinline T lerp(const T A, const T B, const float Alpha) { return A + Alpha * (B - A); }
	void SinCos(float* ScalarSin, float* ScalarCos, float Value);
	float Fmod(float X, float Y);
};

struct fmatrix {
	struct fplane xplane;
	struct fplane yplane;
	struct fplane zplane;
	struct fplane wplane;
};

struct ftransform
{
	fquat rot;
	fvector translation;
	char pad[4];
	fvector scale;
	char pad1[4];
};
inline frotator to_rotator(const fvector& vec) {
	frotator rot;
	rot.pitch = atan2(vec.z, sqrt(vec.x * vec.x + vec.y * vec.y)) * (180.0 / M_PI);
	rot.yaw = atan2(vec.y, vec.x) * (180.0 / M_PI);
	rot.roll = 0.0;
	return rot;
}

inline fvector RotationToVector(const fvector& rot) {
	float radPitch = rot.x * M_PI / 180.0f;
	float radYaw = rot.y * M_PI / 180.0f;

	return fvector(
		cosf(radPitch) * cosf(radYaw),
		cosf(radPitch) * sinf(radYaw),
		sinf(radPitch)
	);
}

