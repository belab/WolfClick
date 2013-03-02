#pragma once

#ifdef HOOKS_LIBRARY
# define HOOKS_API __declspec (dllexport)
#else // HOOKS_LIBRARY
# define HOOKS_API __declspec (dllimport)
#endif // HOOKS_LIBRARY

typedef int BOOL;

extern "C"
{
HOOKS_API BOOL InstallHook( void* hWnd );
HOOKS_API BOOL UninstallHook(void*);
}
