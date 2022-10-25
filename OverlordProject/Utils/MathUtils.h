#pragma once
#include <stdafx.h>
#include "Utils/MathHelper.h"

#pragma region Operators

inline bool operator==(const DirectX::XMFLOAT2& a, const DirectX::XMFLOAT2& b)
{
	return MathHelper::XMFloat2Equals(a, b);
}

inline bool operator==(const DirectX::XMFLOAT3& a, const DirectX::XMFLOAT3& b)
{
	return MathHelper::XMFloat3Equals(a, b);
}

inline bool operator==(const DirectX::XMFLOAT4& a, const DirectX::XMFLOAT4& b)
{
	return MathHelper::XMFloat4Equals(a, b);
}

inline bool operator==(const XMINT2& a, const XMINT2& b)
{
	return a.x == b.x && a.y == b.y;
}

inline XMINT2 operator+(const XMINT2& a, const XMINT2& b)
{
	XMINT2 res{ a };
	res.x += b.x;
	res.y += b.y;
	return res;
}

#pragma endregion

#pragma region Random
// Max inclusive
inline int RandomInRange(int min, int max)
{
	return min + (rand() % static_cast<int>(max - min + 1));
}
#pragma endregion

#pragma region Lerp
inline XMFLOAT3 Lerp(const DirectX::XMFLOAT3& a, const DirectX::XMFLOAT3& b, float t)
{
	XMFLOAT3 res{};
	res.x = std::lerp(a.x, b.x, t);
	res.y = std::lerp(a.y, b.y, t);
	res.z = std::lerp(a.z, b.z, t);
	return res;
}
#pragma endregion

