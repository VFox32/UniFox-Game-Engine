#include "ufpch.h"

#include "UniFox/Util/StreamReader.h"

namespace UniFox {
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
    
    template<typename T>
    uint32_t StreamReader::ReadArray(T*& array, uint32_t size) {
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
    void StreamReader::ReadArray(T (&array)[N], uint32_t size) {
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
    void StreamReader::ReadArray(std::vector<T>& array, uint32_t size) {
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
    void StreamReader::ReadMap(std::map<Key, Value>& map, uint32_t size) {
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
    void StreamReader::ReadMap(std::unordered_map<Key, Value>& map, uint32_t size) {
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
    void StreamReader::ReadSet(std::set<Value>& set, uint32_t size) {
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
    void StreamReader::ReadSet(std::unordered_set<Value>& set, uint32_t size) {
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
}