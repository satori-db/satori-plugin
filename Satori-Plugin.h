// El siguiente bloque ifdef muestra la forma estándar de crear macros que hacen la exportación
// de un DLL más sencillo. Todos los archivos de este archivo DLL se compilan con SATORIPLUGIN_EXPORTS
// símbolo definido en la línea de comandos. Este símbolo no debe definirse en ningún proyecto
// que use este archivo DLL. De este modo, otros proyectos cuyos archivos de código fuente incluyan el archivo verán
// interpretan que las funciones SATORIPLUGIN_API se importan de un archivo DLL, mientras que este archivo DLL interpreta los símbolos
// definidos en esta macro como si fueran exportados.
#ifdef SATORIPLUGIN_EXPORTS
#define SATORIPLUGIN_API __declspec(dllexport)
#else
#define SATORIPLUGIN_API __declspec(dllimport)
#endif

// Clase exportada del DLL
class SATORIPLUGIN_API CSatoriPlugin {
public:
	CSatoriPlugin(void);
	// TODO: agregar métodos aquí.
};

extern SATORIPLUGIN_API int nSatoriPlugin;

SATORIPLUGIN_API int fnSatoriPlugin(void);
