#pragma once

#ifdef HOOKS_LIBRARY
# define HOOKS_API __declspec (dllexport)
#else // HOOKS_LIBRARY
# define HOOKS_API __declspec (dllimport)
#endif // HOOKS_LIBRARY

typedef int BOOL;

extern "C"
{
HOOKS_API BOOL InstallMouseHook( void* hWnd );
HOOKS_API BOOL UninstallMouseHook(void*);
HOOKS_API BOOL InstallKeyHook( void* hWnd );
HOOKS_API BOOL UninstallKeyHook(void*);

}
