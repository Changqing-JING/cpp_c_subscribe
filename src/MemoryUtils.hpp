#pragma once
#include <cstdint>
#include <cstdlib>

size_t getMemoryPageSize();
uint8_t* allocExecutableMemory(size_t size);
void freeAlignedMemroy(void* ptr);
uint8_t* reallocExecutableMemory(uint8_t* oldCodeStart, size_t oldSize, size_t& newSize);