#pragma once

#include "UniFox/Core/Buffer.h"

#include <memory>

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

namespace UniFox {
    class StreamWriter {
    public:
        virtual ~StreamWriter() = default;

        virtual bool IsStreamGood() const = 0;
        virtual uint64_t GetStreamPosition() = 0;
        virtual void SetStreamPosition(uint64_t position) = 0;
        virtual bool WriteData(const char* data, size_t size) = 0;

        operator bool() const {return IsStreamGood();}

        void WriteBuffer(const Buffer buffer);
        void WriteZero(const uint64_t size);
        void WriteString(const std::string& string);

        template<typename T>
        void WriteRaw(const T& type) {
            bool success = WriteData((char*)&type, sizeof(T));
        }

        template<typename T>
        void WriteObject(const T& obj) {
            T::Serialize(this, obj);
        }

        template<typename T>
        void WriteArray(const T* array, const uint32_t size, bool writeSize = true) {
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
        void WriteArray(const T (&array)[N], bool writeSize = true) {
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
        void WriteArray(const std::vector<T>& array, bool writeSize = true) {
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
        void WriteMap(const std::map<Key, Value>& map, bool writeSize = true) {
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
        void WriteMap(const std::unordered_map<Key, Value>& map, bool writeSize = true) {
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
        void WriteSet(const std::set<Value>& set, bool writeSize = true) {
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
        void WriteSet(const std::unordered_set<Value>& set, bool writeSize = true) {
            if(writeSize)
                WriteRaw<uint32_t>((uint32_t)set.size());

            for(const Value value : set) {
                if constexpr(std::is_trivial<Value>())
                    WriteRaw<Value>(value);
                else
                    WriteObject<Value>(value);
            }
        }
    };
}