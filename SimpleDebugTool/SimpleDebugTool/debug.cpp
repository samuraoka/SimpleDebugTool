#include "stdafx.h"
#include "debug.h"

using KennyKerr::Tracer;

Tracer::Tracer(char const *filename, unsigned const line) :
	m_pid{ _getpid() },
	m_filename{ filename },
	m_line{ line }
{
}
