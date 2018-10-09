/*
 * Copyright (C) 2018 Yura Zhivaga <yzhivaga@gmail.com>
 *
 * This file is part of rz4m.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef RZ4M_UTILS_H
#define RZ4M_UTILS_H

#include <iostream>
#include <cstring>
#include <map>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <boost/format.hpp>

namespace rz4m {
    namespace Utils {
        int CharMatch(const char *Buffer, unsigned int BufferSize, char Needle, unsigned int Offset = 0);
        long long MemToll(std::string str);
        std::string HumanizeSize(uintmax_t Bytes);
        std::string GenerateUniqueFolderName(std::string FirstPrefix, std::string SecondPrefix);
    }
}


#endif //RZ4M_UTILS_H