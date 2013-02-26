#include "mainwindow.h"
#include <QApplication>

#include <QtCore/qt_windows.h>

typedef bool (CALLBACK *MYFUNC)(void*);
MYFUNC InstallHook = 0;
MYFUNC UninstallHook = 0;

int main(int argc, char *argv[])
{
    HINSTANCE hDLL = LoadLibrary(L"hooks.dll");
    if( hDLL, NULL )
    {
        MessageBox( NULL, L"Fehler beim Laden der dll", L"Fehler", MB_OK );
        return FALSE;
    }

    InstallHook = (MYFUNC) GetProcAddress( hDLL, "InstallHook");
    if( InstallHook == NULL )
    {
        MessageBox( NULL, L"Fehler: InstallHook nicht gefunden", L"Fehler", MB_OK );
        return FALSE;
    }

    UninstallHook = (MYFUNC) GetProcAddress( hDLL, "UninstallHook");
    if( UninstallHook == NULL )
    {
        MessageBox( NULL, L"Fehler: UninstallHook nicht gefunden", L"Fehler", MB_OK );
        return FALSE;
    }



    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    InstallHook((void*)w.winId());
    SetWindowPos((HWND)w.winId(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    int result = a.exec();
    UninstallHook(0);
    FreeLibrary( hDLL );
    return result;
}
