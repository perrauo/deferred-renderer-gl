#ifdef GHOSTGAME_ENGINE_EXPORTS
#define GHOSTGAME_ENGINE_API __declspec(dllexport)
#else
#define GHOSTGAME_ENGINE_API __declspec(dllimport)
#endif