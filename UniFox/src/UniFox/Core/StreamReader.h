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
    class StreamReader {
    public:
        virtual ~StreamReader() = default;

        virtual bool IsStreamGood() const = 0;
        virtual uint64_t GetStreamPosition() = 0;
        virtual void SetStreamPosition(uint64_t position) = 0;
        virtual bool ReadData(char* data, size_t size) = 0;

        
        void ReadBuffer(Buffer& buffer);
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
        uint32_t ReadArray(T*& array, uint32_t size = 0) {
            if(size == 0)
                ReadRaw<uint32_t>(size);

            array = new T[size];

            for(uint32_t i = 0; i < size; i++) {
                //if (std::is_trivial<T>::value)
                    ReadRaw<T>(array[i]);
                //else
                //    ReadObject<T>(array[i]);
            }

            return size;
        }
        
        template<typename T, size_t N>
        void ReadArray(T (&array)[N], uint32_t size = 0) {
            if(size == 0)
                ReadRaw<uint32_t>(size);

            if (size != N) {
                return;
            }

            for (uint32_t i = 0; i < size; i++) {
                if constexpr (std::is_trivial<T>())
                    ReadRaw<T>(array[i]);
                else
                    ReadObject<T>(array[i]);
            }
        }
        
        template<typename T>
        void ReadArray(std::vector<T>& array, uint32_t size = 0) {
            if(size == 0)
                ReadRaw<uint32_t>(size);

            array.resize(size);

            for(uint32_t i = 0; i < size; i++) {
                if constexpr(std::is_trivial<T>())
                    ReadRaw<T>(array[i]);
                else
                    ReadObject<T>(array[i]);
            }
        }

        template<typename Key, typename Value>
        void ReadMap(std::map<Key, Value>& map, uint32_t size = 0) {
            if(size == 0)
                ReadRaw<uint32_t>(size);

            for(uint32_t i = 0; i < size; i++) {
                Key key;
                if constexpr(std::is_trivial<Key>())
                    ReadRaw<Key>(key);
                else
                    ReadObject<Key>(key);
                
                if constexpr(std::is_trivial<Value>())
                    WriteRaw<Value>(map[key]);
                else
                    WriteObject<Value>(map[key]);
            }
        }
        
        template<typename Key, typename Value>
        void ReadMap(std::unordered_map<Key, Value>& map, uint32_t size = 0) {
            if(size == 0)
                ReadRaw<uint32_t>(size);

            for(uint32_t i = 0; i < size; i++) {
                Key key;
                if constexpr(std::is_trivial<Key>())
                    ReadRaw<Key>(key);
                else
                    ReadObject<Key>(key);
                
                if constexpr(std::is_trivial<Value>())
                    WriteRaw<Value>(map[key]);
                else
                    WriteObject<Value>(map[key]);
            }
        }
        
        template<typename Value>
        void ReadSet(std::set<Value>& set, uint32_t size = 0) {
            if(size == 0)
                ReadRaw<uint32_t>(size);

            for(uint32_t i = 0; i < size; i++) {
                Value value;
                
                if constexpr(std::is_trivial<Value>())
                    ReadRaw<Value>(value);
                else
                    ReadObject<Value>(value);

                set.insert(value);
            }
        }
        
        template<typename Value>
        void ReadSet(std::unordered_set<Value>& set, uint32_t size = 0) {
            if(size == 0)
                ReadRaw<uint32_t>(size);

            for(uint32_t i = 0; i < size; i++) {
                Value value;
                
                if constexpr(std::is_trivial<Value>())
                    ReadRaw<Value>(value);
                else
                    ReadObject<Value>(value);

                set.insert(value);
            }
        }
    };
}