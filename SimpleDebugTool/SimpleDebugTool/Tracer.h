#pragma once

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

class SIMPLEDEBUGTOOL_API Tracer
{
public:
	Tracer(char const *filename, unsigned const line);
	auto operator()(wchar_t const *format, ...) const -> void;

private:
	char const *m_filename;
	unsigned int m_line;
};
