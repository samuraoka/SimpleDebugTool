#pragma once

#ifdef _DEBUG
#include <Windows.h>
#include <crtdbg.h>
//TODO
#endif // _DEBUG

#ifdef _DEBUG
#define ASSERT _ASSERTE
#define VERIFY ASSERT
//TODO
#else
#define ASSERT __noop
#define VERIFY(expression) (expression)
//TODO
#endif // _DEBUG

#ifdef _DEBUG
#define TRACE Tracer(__FILE__, __LINE__)
#else
#define TRACE __noop
#endif

#ifdef SIMPLEDEBUGTOOL_EXPORTS
#define SIMPLEDEBUGTOOL_API __declspec(dllexport)
#else
#define SIMPLEDEBUGTOOL_API __declspec(dllimport)
#endif

#ifdef _DEBUG
struct SIMPLEDEBUGTOOL_API Tracer
{
	Tracer(char const *filename, unsigned const line);
	auto operator()(wchar_t const *format, ...) const -> void;

	int m_pid;
	char const *m_filename;
	unsigned int m_line;
};
#endif // _DEBUG
