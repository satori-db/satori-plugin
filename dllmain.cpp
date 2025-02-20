// dllmain.cpp : Define el punto de entrada de la aplicación DLL.
#include "pch.h"
#include <object.h>

#include <string>
#include <map>
#include <nlohmann/json.hpp>

using namespace Satori;
using namespace nlohmann;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

extern "C" __declspec(dllexport)  std::string id() {
    //Specify plugin id, this will be the command to execute it
    return "HI";
}

extern "C" __declspec(dllexport) std::string plugin(std::map<std::string, Object>& satori, std::map<std::string, Object>& users, std::map<std::string, std::vector<std::string>>& owners, std::map<std::string, std::pair<std::string, int>>& peers, std::map<std::string, std::pair<std::string, std::string(*)(json)>>& functions, std::string(*is_main_owner)(json, std::string(*jic)(json)), void(*is_owner)(json), void(*)(std::string, std::string), std::string(*is_closest_owner)(json, std::string) , json rq) {
   //Specify command behavior
    return "HI!";
}

extern "C" __declspec(dllexport) std::string startup(std::map<std::string, Object>& satori, std::map<std::string, Object>& users) {
   //Specify if command should make any actions at startup
    return "OK";
}