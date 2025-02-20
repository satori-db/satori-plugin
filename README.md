# Satori-Plugin

# Introduction
This repo holds the template for a Satori plugin on Windows. This is a Visual Studio 2022 project for building a DLL.

## Installation
Just copy the shared library to a folder called dll at the same path where Satori is located.

## What are extensions in Satori
At the present moment Satori supports extensions in the form of shared libraries (dlls for windows and shared objects for linux), in future iterations the extension system will be unified and simplified.

# Structure
A Satori extension has 3 functions. **ID**, **PLUGIN**, **STARTUP**.

## ID
This functions takes no parameters and returns an string with the plugin id, this id will be the command you must call to execute the plugin.

## PLUGIN
This function is defined like this
```cpp
extern "C" __declspec(dllexport) std::string plugin(std::map<std::string, Object>& satori, std::map<std::string, Object>& users, std::map<std::string, std::vector<std::string>>& owners, std::map<std::string, std::pair<std::string, int>>& peers, std::map<std::string, std::pair<std::string, std::string(*)(json)>>& functions, std::string(*redirection)(json, std::string(*jic)(json)), void(*notify)(json), void(*notify_ownership)(std::string, std::string), std::string(*specific_redirect)(json, std::string) , json rq) {
   //Specify command behavior
    return "HI!";
}
```
Parameters:
- satori is the map wich holds all of the app's information.
- users is a map that holds the database's users information.
- owners is a map that holds the owners (nodes that hold the actual data) of all of the Objects stored in your app
- peers is a map that links the owner name with it's ip
- functions is a map that holds functions pointers to all of Satori's built-in functions
- redirection is a function that redirects a request to the node that should handle it. It takes as parameters the request and a fallback function pointer to execute if the node that should handle the request is the current node
- notify is a functions that notifies all owner nodes of the modified Object that they must execute the request that was executed in the current node, this request is the first and only parameter of the function
- notify_ownership notifies to an specific node in the network that the current node is the owner of an specific object. The first parameter is the object key and the second is the node id of the node that must be notified
- specific_redirect redirects a request(first parameter) to an sepecific node (second parameter)
- rq is the current request encoded as json

Return: Command status

## STARTUP
It's defined like this:
```cpp
extern "C" __declspec(dllexport) std::string startup(std::map<std::string, Object>& satori, std::map<std::string, Object>& users) {
   //Specify if command should make any actions at startup
    return "OK";
}
```
This functions specifies actions that must be taken at the start of Satori and it returns an string describing the function status.

# DISTRIBUTED
Satori provides the users with the functions needed to make their extensions work in a distributed enviroment. Keep in mind that distributed capabilities are still in experimental fase and can be unstable, so, use them wisely. You need to implement the distributed behavior of your extension from scratch, we hope to make this process easier with future iterations of Satori.

# Platforms
Although this repo provides a template for a Windows Satori extension, you can use whatever build system you want to. The posibilities with Satori extensions are endless, an extensions just needs to be a shared library and have defined the three functions listed previously.
