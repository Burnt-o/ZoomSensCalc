#pragma once
#include <string>
#include <array>
#include <vector>
#include <iomanip>

/// <summary>
/// UTF-8 string to UTF-16 widestring
/// </summary>
/// <param name="wstr"></param>
/// <returns></returns>
static inline std::wstring StringToWString(const std::string& str)
{
	std::wstring wstr;
	size_t size;
	wstr.resize(str.length());
	mbstowcs_s(&size, &wstr[0], wstr.size() + 1, str.c_str(), str.size());
	return wstr;
}

/// <summary>
/// UTF-16 widestring to UTF-8 string
/// </summary>
/// <param name="wstr"></param>
/// <returns></returns>
static inline std::string WStringToString(const std::wstring& wstr)
{
	std::string str;
	size_t size;
	str.resize(wstr.length());
	wcstombs_s(&size, &str[0], str.size() + 1, wstr.c_str(), wstr.size());
	return str;
}

/// <summary>
/// Returns a string representation of a single-precision float with the minimum necessary decimal digits to exactly/uniquely represent it.
/// </summary>
/// <param name="f"></param>
/// <returns></returns>
static inline std::string ExactFloatToString(float f)
{
	std::array<char, 64> buf;
	auto result = std::to_chars(buf.data(), buf.data() + buf.size(), f, std::chars_format::fixed);
	return std::string(buf.data(), result.ptr - buf.data());
}