#pragma once

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
        void WriteArray(const T* array, const uint32_t size, bool writeSize = true);

        template<typename T, size_t N>
        void WriteArray(const T (&array)[N], bool writeSize = true);

        template<typename T>
        void WriteArray(const std::vector<T>& array, bool writeSize = true);

        template<typename Key, typename Value>
        void WriteMap(const std::map<Key, Value>& map, bool writeSize = true);
        
        template<typename Key, typename Value>
        void WriteMap(const std::unordered_map<Key, Value>& map, bool writeSize = true);
        
        template<typename Value>
        void WriteSet(const std::set<Value>& set, bool writeSize = true);
        
        template<typename Value>
        void WriteSet(const std::unordered_set<Value>& set, bool writeSize = true);
    };
}