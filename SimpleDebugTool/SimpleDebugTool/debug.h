#pragma once

#include <Windows.h>
#include <cstdio>
#include <cstdlib>
#include <process.h>

#ifdef _DEBUG
#include <crtdbg.h>
#endif // _DEBUG

#ifdef _DEBUG
#define ASSERT _ASSERTE
#define VERIFY ASSERT
#define VERIFY_(result, expression) ASSERT(result == expression)
#else
#define ASSERT __noop
#define VERIFY(expression) (expression)
#define VERIFY_(result, expression) (expression)
#endif // _DEBUG

#ifdef _DEBUG
#define TRACE KennyKerr::Tracer(__FILE__, __LINE__)
#else
#define TRACE __noop
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
		auto operator()(wchar_t const *format, Args... args) const -> void
		{
			wchar_t buffer[1024];
			auto count = swprintf_s(buffer, L"[%d] %S(%d): ", m_pid, m_filename, m_line);
			ASSERT(-1 != count);

			ASSERT(-1 != _snwprintf_s(buffer + count, _countof(buffer) - count,
				_countof(buffer) - count - 1, format, args...));

			OutputDebugString(buffer);
		}

		int m_pid;
		char const *m_filename;
		unsigned int m_line;
	};
}
