#pragma once

#ifdef GHOSTGAME_FRAMEWORK_EXPORTS
#define GHOSTGAME_FRAMEWORK_API __declspec(dllexport)
#else
#define GHOSTGAME_FRAMEWORK_API __declspec(dllimport)
#endif