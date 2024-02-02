#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <array>
#include <functional>
#include <map>
#include <fstream>
#include <ctime>
#include <random>
#include <algorithm>


#include "..\\xlog\\CXLog.h"
#ifdef _WIN64
#ifdef _DEBUG
#pragma comment( lib, "..\\x64\\Debug\\xlog.lib")
#else
#pragma comment( lib, "..\\x64\\Release\\xlog.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment( lib, "..\\Debug\\xlog.lib")
#else
#pragma comment( lib, "..\\Release\\xlog.lib")
#endif
#endif