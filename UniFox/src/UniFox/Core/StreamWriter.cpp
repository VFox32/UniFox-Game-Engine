#include "ufpch.h"

#include "UniFox/Core/StreamWriter.h"

namespace UniFox {
    void StreamWriter::WriteBuffer(const Buffer buffer) {
        WriteData((char*)&buffer.Size, sizeof(uint64_t));

        WriteData((char*)buffer.Data, buffer.Size);
    }

    void StreamWriter::WriteZero(const uint64_t size) {
        char zero = 0;
        for(uint32_t i = 0; i < size; i++)
            WriteData(&zero, 1);
    }

    void StreamWriter::WriteString(const std::string& string) {
        size_t size = string.size();
        WriteData((char*)&size, sizeof(size_t));
        WriteData((char*)string.data(), sizeof(char) * string.size());
    }
}