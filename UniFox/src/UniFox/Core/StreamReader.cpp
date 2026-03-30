#include "ufpch.h"

#include "UniFox/Core/StreamReader.h"

namespace UniFox {
    void StreamReader::ReadBuffer(Buffer& buffer) {
        uint64_t size;
        ReadData((char*)&size, sizeof(uint64_t));
        buffer.Allocate(size);

        ReadData((char*)buffer.Data, size);
    }

    void StreamReader::ReadZero(uint64_t size) {
        char zero;
        for(uint32_t i = 0; i < size; i++)
            ReadData(&zero, 1);
    }

    void StreamReader::ReadString(std::string& string) {
        size_t size;
        ReadData((char*)&size, sizeof(size_t));

        string.resize(size);

        if (size > 0) {
            ReadData(string.data(), size);
        }
    }
}