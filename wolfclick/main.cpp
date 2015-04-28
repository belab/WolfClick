#include "mainwindow.h"

#include <QApplication>

#include <QtCore/qt_windows.h>

typedef bool (CALLBACK *MYFUNC)(void*);

int main(int argc, char *argv[])
{
    HINSTANCE hDLL = LoadLibrary(L"hooks.dll");
    if( hDLL, NULL )
    {
        MessageBox( NULL, L"Error while loading dll", L"Error", MB_OK );
        return FALSE;
    }

    MYFUNC InstallMouseHook = (MYFUNC) GetProcAddress( hDLL, "InstallMouseHook");
    if( InstallMouseHook == NULL )
    {
        MessageBox( NULL, L"Error: InstallMouseHook not found", L"Error", MB_OK );
        return FALSE;
    }

    MYFUNC UninstallMouseHook = (MYFUNC) GetProcAddress( hDLL, "UninstallMouseHook");
    if( UninstallMouseHook == NULL )
    {
        MessageBox( NULL, L"Error: UninstallMouseHook not found", L"Error", MB_OK );
        return FALSE;
    }

    MYFUNC InstallKeyHook = (MYFUNC) GetProcAddress( hDLL, "InstallKeyHook");
    if( InstallKeyHook == NULL )
    {
        MessageBox( NULL, L"Error: InstallKeyHook not found", L"Error", MB_OK );
        return FALSE;
    }

    MYFUNC UninstallKeyHook = (MYFUNC) GetProcAddress( hDLL, "UninstallKeyHook");
    if( UninstallKeyHook == NULL )
    {
        MessageBox( NULL, L"Error: UninstallKeyHook not found", L"Error", MB_OK );
        return FALSE;
    }


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    InstallMouseHook((void*)w.winId());
    InstallKeyHook((void*)w.winId());
//    SetWindowPos((HWND)w.winId(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    int result = a.exec();
    UninstallMouseHook(0);
    UninstallKeyHook(0);
    FreeLibrary( hDLL );
    return result;
}
