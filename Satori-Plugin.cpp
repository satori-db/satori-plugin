// Satori-Plugin.cpp : Define las funciones exportadas del archivo DLL.
//

#include "pch.h"
#include "framework.h"
#include "Satori-Plugin.h"


// Ejemplo de variable exportada
SATORIPLUGIN_API int nSatoriPlugin=0;

// Ejemplo de función exportada.
SATORIPLUGIN_API int fnSatoriPlugin(void)
{
    return 0;
}

// Constructor de clase exportada.
CSatoriPlugin::CSatoriPlugin()
{
    return;
}
