#pragma once

#ifdef EXPERIMENT_FRAMEWORK_EXPORTS
#define EXPERIMENT_FRAMEWORK_API __declspec(dllexport)
#else
#define EXPERIMENT_FRAMEWORK_API __declspec(dllimport)
#endif