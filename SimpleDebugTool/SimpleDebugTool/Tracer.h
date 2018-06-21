#pragma once

#ifdef _DEBUG
#define TRACE Tracer(__FILE__, __LINE__)
#else
#define TRACE __noop
#endif

class Tracer
{
public:
	Tracer(char const *filename, unsigned const line);

	template <typename... Args>
	auto operator()(wchar_t const *format, Args... args) const -> void;

private:
	char const *m_filename;
	unsigned int m_line;
};
