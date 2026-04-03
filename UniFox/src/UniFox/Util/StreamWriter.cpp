#include "ufpch.h"

#include "UniFox/Util/StreamWriter.h"

namespace UniFox {
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

    template<typename T>
    void StreamWriter::WriteArray(const T* array, const uint32_t size, bool writeSize) {
        if(writeSize)
            WriteRaw<uint32_t>(size);

        for(uint32_t i = 0; i < size; i++) {
            //if constexpr(std::is_trivial<T>())
                WriteRaw<T>(array[i]);
            //else
            //    WriteObject<T>(array[i]);
        }
    }

    template<typename T, size_t N>
    void StreamWriter::WriteArray(const T (&array)[N], bool writeSize) {
        uint32_t size = N;
        if(writeSize)
            WriteRaw<uint32_t>(size);

        for(uint32_t i = 0; i < size; i++) {
            if constexpr(std::is_trivial<T>())
                WriteRaw<T>(array[i]);
            else
                WriteObject<T>(array[i]);
        }
    }

    template<typename T>
    void StreamWriter::WriteArray(const std::vector<T>& array, bool writeSize) {
        if(writeSize)
            WriteRaw<uint32_t>((uint32_t)array.size());

        for(const auto& element : array) {
            if constexpr(std::is_trivial<T>())
                WriteRaw<T>(element);
            else
                WriteObject<T>(element);
        }
    }

    template<typename Key, typename Value>
    void StreamWriter::WriteMap(const std::map<Key, Value>& map, bool writeSize) {
        if(writeSize)
            WriteRaw<uint32_t>((uint32_t)map.size());

        for(const auto& [key, vlaue] : map) {
            if constexpr(std::is_trivial<Key>())
                WriteRaw<Key>(key);
            else
                WriteObject<Key>(key);
            
            if constexpr(std::is_trivial<Value>())
                WriteRaw<Value>(vlaue);
            else
                WriteObject<Value>(vlaue);
        }
    }
        
    template<typename Key, typename Value>
    void StreamWriter::WriteMap(const std::unordered_map<Key, Value>& map, bool writeSize) {
        if(writeSize)
            WriteRaw<uint32_t>((uint32_t)map.size());

        for(const auto& [key, vlaue] : map) {
            if constexpr(std::is_trivial<Key>())
                WriteRaw<Key>(key);
            else
                WriteObject<Key>(key);
            
            if constexpr(std::is_trivial<Value>())
                WriteRaw<Value>(vlaue);
            else
                WriteObject<Value>(vlaue);
        }
    }
        
    template<typename Value>
    void StreamWriter::WriteSet(const std::set<Value>& set, bool writeSize) {
        if(writeSize)
            WriteRaw<uint32_t>((uint32_t)set.size());

        for(const Value value : set) {
            if constexpr(std::is_trivial<Value>())
                    WriteRaw<Value>(value);
            else
                WriteObject<Value>(value);
        }
    }
        
    template<typename Value>
    void StreamWriter::WriteSet(const std::unordered_set<Value>& set, bool writeSize) {
        if(writeSize)
            WriteRaw<uint32_t>((uint32_t)set.size());

        for(const Value value : set) {
            if constexpr(std::is_trivial<Value>())
                WriteRaw<Value>(value);
            else
                WriteObject<Value>(value);
        }
    }
}