#pragma once

#include <stdint.h>
#include <cstring>

#include "UniFox/Util/StreamWriter.h"
#include "UniFox/Util/StreamReader.h"

namespace UniFox {
	struct Buffer {
		uint8_t* Data = nullptr;
		uint64_t Size = 0;

		Buffer() = default;
		
        static void Serialize(StreamWriter* serializer, const Buffer& instance) {
			serializer->WriteRaw(instance.Size);
			serializer->WriteArray(instance.Data, instance.Size, false);
        }
        static void DeSerialize(StreamReader* deserializer, Buffer& instance) {
			deserializer->ReadRaw(instance.Size);
			instance.Allocate(instance.Size);
			deserializer->ReadArray(instance.Data, instance.Size);
        }

		Buffer(uint64_t size) {
			Allocate(size);
		}

		Buffer(const void* data, uint64_t size = 0) {
			Allocate(size);
			Data = (uint8_t*)data;	
		}

		Buffer(const Buffer&) = default;

		static Buffer Copy(Buffer other) {
			Buffer result(other.Size);
			memcpy(result.Data, other.Data, other.Size);
			return result;
		}

		static Buffer Copy(const void* data, uint64_t size = 0) {
			Buffer result(size);
			memcpy(result.Data, data, size);
			return result;
		}

		void Allocate(uint64_t size) {
			Release();

			Data = new uint8_t[size];
			Size = size;
		}

		void Release() {
			delete[] Data;
			Data = nullptr;
			Size = 0;
		}

		template<typename T>
		T* As() {
			return (T*)Data;
		}

		operator bool() const {
			return (bool)Data;
		}

	};
}