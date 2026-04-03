#pragma once

#include "UniFox/Util/StreamWriter.h"
#include "UniFox/Util/StreamReader.h"

#include "UniFox/Core/Buffer.h"

#include <filesystem>
#include <fstream>

namespace UniFox {
    class MemoryStreamWriter : public StreamWriter {
    public:
        MemoryStreamWriter(Buffer& buffer);
        MemoryStreamWriter(const MemoryStreamWriter&) = delete;
        virtual ~MemoryStreamWriter();

        bool IsStreamGood() const final {return m_WritePos < m_Buffer.Size;}
        uint64_t GetStreamPosition() final {return m_WritePos;}
        void SetStreamPosition(uint64_t position) final {m_WritePos = position;}
        bool WriteData(const char* data, size_t size) final;
    private:
        Buffer& m_Buffer;
        size_t m_WritePos = 0;
    };

    class MemoryStreamReader : public StreamReader {
    public:
        MemoryStreamReader(Buffer& buffer);
        MemoryStreamReader(const MemoryStreamReader&) = delete;
        virtual ~MemoryStreamReader();

        bool IsStreamGood() const final {return m_ReadPos < m_Buffer.Size;}
        uint64_t GetStreamPosition() final {return m_ReadPos;}
        void SetStreamPosition(uint64_t position) final {m_ReadPos = position;}
        bool ReadData(char* data, size_t size) final;
    private:
        Buffer& m_Buffer;
        size_t m_ReadPos = 0;
    };
}