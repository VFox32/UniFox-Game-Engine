#include "ufpch.h"

#include "UniFox/Util/MemoryStream.h"

namespace UniFox {
    MemoryStreamWriter::MemoryStreamWriter(Buffer& buffer) 
        : m_Buffer(buffer) {
    }

    MemoryStreamWriter::~MemoryStreamWriter() {
    }

    bool MemoryStreamWriter::WriteData(const char* data, size_t size) {
        std::memcpy(m_Buffer.Data + m_WritePos, data, size);
        m_WritePos += size;
        return true;
    }
        

    MemoryStreamReader::MemoryStreamReader(Buffer& buffer) 
        : m_Buffer(buffer) {
    }

    MemoryStreamReader::~MemoryStreamReader() {
    }

    bool MemoryStreamReader::ReadData(char* data, size_t size) {
        std::memcpy(data, m_Buffer.Data + m_ReadPos, size);
        m_ReadPos += size;
        return true;
    }
}