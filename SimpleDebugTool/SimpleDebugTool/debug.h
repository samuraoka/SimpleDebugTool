#pragma once

#include <Windows.h>
#include <cstdio>
#include <cstdlib>
#include <process.h>

#ifdef _DEBUG
#include <crtdbg.h>
#endif // _DEBUG

#ifdef _DEBUG
#define SIMPLE_ASSERT _ASSERTE
#define SIMPLE_VERIFY SIMPLE_ASSERT
#define SIMPLE_VERIFY_(result, expression) SIMPLE_ASSERT(result == expression)
#else
#define SIMPLE_ASSERT __noop
#define SIMPLE_VERIFY(expression) (expression)
#define SIMPLE_VERIFY_(result, expression) (expression)
#endif // _DEBUG

#ifdef _DEBUG
#define SIMPLE_TRACE KennyKerr::Tracer(__FILE__, __LINE__)
#else
#define SIMPLE_TRACE __noop
#endif

#ifdef SIMPLEDEBUGTOOL_EXPORTS
#define SIMPLEDEBUGTOOL_API __declspec(dllexport)
#else
#define SIMPLEDEBUGTOOL_API __declspec(dllimport)
#endif

namespace KennyKerr
{
	struct SIMPLEDEBUGTOOL_API Tracer
	{
		Tracer(char const *filename, unsigned const line);

		template <typename... Args>
		auto operator()(
			wchar_t const *format, Args... args) const -> void
		{
			wchar_t buffer[1024];
			auto count = swprintf_s(
				buffer, L"[%d][%d] %S(%d): ",
				m_pid, GetCurrentThreadId(),
				m_filename, m_line);
			ASSERT(-1 != count);

			ASSERT(-1 != _snwprintf_s(buffer + count,
				_countof(buffer) - count, _countof(buffer) - count - 1,
				format, args...));

			OutputDebugString(buffer);
		}

		int m_pid;
		char const *m_filename;
		unsigned int m_line;
	};
}
