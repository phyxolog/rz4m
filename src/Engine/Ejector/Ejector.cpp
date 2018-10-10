/*
 * Copyright (C) 2018 Yura Zhivaga <yzhivaga@gmail.com>
 *
 * This file is part of rz4.
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

#include "Ejector.hpp"

namespace rz4 {
    namespace Engine {
        namespace fs = boost::filesystem;

        Ejector::Ejector(std::string FileName, unsigned int BufferSize) : FileName(FileName), BufferSize(BufferSize) {
            File.open(FileName, std::fstream::binary);
            FileSize = fs::file_size(FileName);

            if (FileSize < BufferSize) {
                BufferSize = static_cast<unsigned int>(FileSize);
            }
        }

        bool Ejector::Extract(uintmax_t Offset, uintmax_t Size, std::string OutFileName) {
            File.seekg(Offset, std::fstream::beg);
            unsigned int LocalBufferSize = BufferSize;

            if (Size < LocalBufferSize) {
                LocalBufferSize = static_cast<unsigned int>(Size);
            }

            if (Size > FileSize) {
                Size = FileSize;
            }

            uintmax_t ReadBytes = 0;
            char *Buffer = new char[LocalBufferSize];
            std::ofstream OutFile(OutFileName);

            if (!OutFile.is_open()) {
                return false;
            }

            while (ReadBytes < Size) {
                if ((ReadBytes + LocalBufferSize) > Size) {
                    LocalBufferSize = static_cast<unsigned int>(Size - ReadBytes);
                    delete[] Buffer;
                    Buffer = new char[LocalBufferSize];
                }

                File.read(Buffer, LocalBufferSize);
                OutFile.write(Buffer, LocalBufferSize);
                ReadBytes += LocalBufferSize;
            }

            delete[] Buffer;
            OutFile.close();

            return true;
        }

        Ejector::~Ejector() {
            if (File.is_open()) {
                File.close();
            }
        }
    }
}
