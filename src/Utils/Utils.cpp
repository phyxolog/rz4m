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

#include "Utils.h"

namespace rz4m {
    namespace Utils {
        /*
         * Find char in array.
         * If found - return index.
         * If not - return -1.
         */
        int CharMatch(const char *buffer, unsigned int buffer_size, char needle, unsigned int offset) {
            if (offset >= buffer_size) {
                return -1;
            }

            buffer_size -= offset;
            const char* result = reinterpret_cast<const char*>(std::memchr(buffer + offset, needle, buffer_size));
            return result ? static_cast<int>(result - buffer) : -1;
        }

        /*
         * Convert a string representing an amount of memory into the number of
         * bytes, so for instance memtoll("1Gb") will return 1073741824 that is
         * (1024*1024*1024).
         */
        long long MemToll(std::string str) {
            if (str.length() == 0) {
                return 0;
            }

            size_t nondigit_pos = str.find_first_not_of("0123456789");

            if (nondigit_pos == std::string::npos) {
                return std::stoll(str);
            }

            long long result = 0;
            std::string digits = str.substr(0, nondigit_pos);
            std::string u = str.substr(nondigit_pos, str.length());
            std::transform(u.begin(), u.end(), u.begin(), ::tolower);

            if (digits.length() == 0) {
                return result;
            } else {
                result = std::stoll(digits);
            }

            std::map<std::string, long> umul = {
                    { "b",  1                   },
                    { "k",  1000                },
                    { "kb", 1024                },
                    { "m",  1000  * 1000        },
                    { "mb", 1024  * 1024        },
                    { "g",  1000L * 1000 * 1000 },
                    { "gb", 1024L * 1024 * 1024 },
            };

            auto mul = umul.find(u);
            if (mul != umul.end()) {
                return result * mul->second;
            } else {
                return result;
            }
        }
    }
}
