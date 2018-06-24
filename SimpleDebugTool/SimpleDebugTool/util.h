#pragma once

#include <Windows.h>

#ifdef SIMPLEDEBUGTOOL_EXPORTS
#define SIMPLEDEBUGTOOL_API __declspec(dllexport)
#else
#define SIMPLEDEBUGTOOL_API __declspec(dllimport)
#endif

namespace KennyKerr
{
	struct SIMPLEDEBUGTOOL_API windows_exception
	{
		DWORD error;

		explicit windows_exception(DWORD const value = GetLastError());
	};

	auto SIMPLEDEBUGTOOL_API wait_one(
		HANDLE const h, DWORD const milliseconds = INFINITE) -> bool;

	//auto pack(HANDLE *) -> void {}

	template <typename T, typename... Args>
	auto pack(HANDLE * left, T const & right, Args const & ... args) -> void
	{
		*left = right.get();
		pack(++left, args...);
	}

	template <typename... Args>
	auto wait_all(Args const & ... args) -> DWORD
	{
		HANDLE handles[sizeof...(Args)];
		pack(handles, args...);

		auto ret = WaitForMultipleObjects(
			sizeof...(Args), handles, true, INFINITE);
		VERIFY_(WAIT_OBJECT_0, ret);

		return ret;
	}
}
