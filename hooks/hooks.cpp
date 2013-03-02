#include "hooks.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <stdio.h>

#include <iostream>

#pragma data_seg ("shared")
HHOOK g_hMouseHook = NULL;
HINSTANCE g_hInst = NULL;
HWND g_hWnd = NULL;
#pragma data_seg()
#pragma comment(linker, "/SECTION:shared,RWS")

LRESULT CALLBACK MouseProc( int nCode, WPARAM wParam, LPARAM lParam );

BOOL APIENTRY DllMain( HINSTANCE hInst, DWORD, LPVOID )
{
    if( !g_hInst )
        g_hInst = hInst;
    return TRUE;
}





BOOL InstallHook( void* hWnd )
{
    g_hWnd = HWND( hWnd );
    if( g_hMouseHook != NULL )
        return TRUE;
    g_hMouseHook = SetWindowsHookEx( WH_MOUSE_LL, MouseProc, g_hInst, 0);
    if( g_hMouseHook == NULL )
        return FALSE;
    return TRUE;
}


BOOL UninstallHook(void*)
{
    if( g_hMouseHook != NULL )
    {
        UnhookWindowsHookEx( g_hMouseHook );
        g_hMouseHook = NULL;
    }
    return TRUE;
}

LRESULT CALLBACK MouseProc( int nCode, WPARAM wParam, LPARAM lParam )
{
    if( ( nCode >= 0 ) && ( nCode == HC_ACTION ) )
    {
        switch( wParam )
        {
        case WM_LBUTTONDOWN:
        case WM_NCLBUTTONDOWN:
            {
                MOUSEHOOKSTRUCT* mhs = (MOUSEHOOKSTRUCT*)lParam;
                HWND hwnd = g_hWnd;
//                HWND caller = FindWindow(0, L"WolfClick" );
                if( hwnd )
                    PostMessage( hwnd, WM_USER+123, 0, MAKELPARAM( mhs->pt.x, mhs->pt.y ) );
//                if( caller )
//                    PostMessage( caller, WM_USER+123, 0, MAKELPARAM( mhs->pt.x, mhs->pt.y ) );
            }
            break;
        default:
            break;
        }
    }
    else
    {
        std::cout << "hello ncode" << std::endl;
    }
    return CallNextHookEx( g_hMouseHook, nCode, wParam, lParam );
}

