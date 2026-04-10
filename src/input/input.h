#pragma once

#ifdef TUI_PLATFORM_WINDOWS
#include "input_windows.h"
#endif

#ifdef TUI_PLATFORM_LINUX
#include "input_linux.h"
#endif