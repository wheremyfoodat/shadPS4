#pragma once
#include "../types.h"

constexpr u64 SYSTEM_RESERVED = 0x800000000u;
constexpr u64 CODE_BASE_OFFSET = 0x100000000u;

namespace Memory
{
	enum class MemoryMode : u32
	{
		NoAccess = 0,
		Read = 1,
		Write = 2,
		ReadWrite =3,
		Execute = 4,
		ExecuteRead = 5,
		ExecuteWrite = 6,
		ExecuteReadWrite = 7,
	};

	namespace VirtualMemory {
		u64 memory_alloc(u64 address, u64 size, MemoryMode mode);
		bool memory_protect(u64 address, u64 size, MemoryMode mode, MemoryMode* old_mode);
        bool memory_flush(u64 address, u64 size);
        bool memory_patch(u64 vaddr, u64 value);
	}
}