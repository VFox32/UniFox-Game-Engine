#pragma once

#include <memory>

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

namespace UniFox {
    class StreamReader {
    public:
        virtual ~StreamReader() = default;

        virtual bool IsStreamGood() const = 0;
        virtual uint64_t GetStreamPosition() = 0;
        virtual void SetStreamPosition(uint64_t position) = 0;
        virtual bool ReadData(char* data, size_t size) = 0;

        
        void ReadZero(uint64_t size);
        void ReadString(std::string& string);

        operator bool() const {return IsStreamGood();}

        template<typename T>
        void ReadRaw(T& type) {
            bool success = ReadData((char*)&type, sizeof(T));
        }

        template<typename T>
        void ReadObject(T& obj) {
            T::DeSerialize(this, obj);
        }
        
        template<typename T>
        uint32_t ReadArray(T*& array, uint32_t size = 0);
        
        template<typename T, size_t N>
        void ReadArray(T (&array)[N], uint32_t size = 0);
        
        template<typename T>
        void ReadArray(std::vector<T>& array, uint32_t size = 0);

        template<typename Key, typename Value>
        void ReadMap(std::map<Key, Value>& map, uint32_t size = 0);
        
        template<typename Key, typename Value>
        void ReadMap(std::unordered_map<Key, Value>& map, uint32_t size = 0);
        
        template<typename Value>
        void ReadSet(std::set<Value>& set, uint32_t size = 0);
        
        template<typename Value>
        void ReadSet(std::unordered_set<Value>& set, uint32_t size = 0);
    };
}