#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <cstdint>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "UniFox/Core/Log.h"
#include "UniFox/Debug/Instrumentor.h"

#ifdef UF_PLATFORM_WINDOWS
    #include <Windows.h>
#endif