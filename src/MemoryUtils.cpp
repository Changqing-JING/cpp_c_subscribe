#include <cstdio>
#include <cstdlib>
#include <errno.h>

#include <exception>
#include <memory.h>
#include <algorithm>
#include <malloc.h>

#include "MemoryUtils.hpp"

static int addExecuteAccess(uint8_t* codeStart, size_t len);
static void* allocAlignedMemory(size_t alignment, size_t size);

#if __unix__
#include <unistd.h>
#include <sys/mman.h>

static int addExecuteAccess(uint8_t* codeStart, size_t len){
    int res = mprotect(codeStart, len, PROT_EXEC|PROT_READ|PROT_WRITE);
    if(res)
    {
        perror("mprotect error");
        return 1;
    }else{
        return 0;
    }

}



size_t getMemoryPageSize() {
    long pageSize = sysconf(_SC_PAGE_SIZE);
    return pageSize;
}


static void* allocAlignedMemory(size_t alignment, size_t size) {

    return (uint8_t*)std::aligned_alloc(alignment, size);
}

void freeAlignedMemroy(void* ptr) {

    free(ptr);
}

static void* alignedRealloc(void* ptr, size_t size, size_t alignment){
    (void)(alignment);
    return realloc(ptr, size);
}  

#elif _WIN32
#include <windows.h>
#include <malloc.h>

static int addExecuteAccess(uint8_t* codeStart, size_t len){
    DWORD flNewProtect = PAGE_EXECUTE_READWRITE;
    DWORD flOldProtect;
    int success = VirtualProtect(codeStart, len, flNewProtect, &flOldProtect);
    if(success)
    {
        return 0;
    }else{
        int errorCode = GetLastError();
        printf("VirtualProtect error failed with error code\n", errorCode);
        perror("VirtualProtect error");
        return 1;
    }

}

static void* allocAlignedMemory(size_t alignment, size_t size) {
    return _aligned_malloc(size, alignment);
}

void freeAlignedMemroy(void* ptr) {

    _aligned_free(ptr);
}

size_t getMemoryPageSize() {
    SYSTEM_INFO sysInfo;

    GetSystemInfo(&sysInfo);

    return sysInfo.dwPageSize;
}

static void* alignedRealloc(void* ptr, size_t size, size_t alignment){
    return _aligned_realloc(ptr, size, alignment);
} 

#else

#error "not supported OS"

#endif


static size_t getPagedSize(long pageSize, size_t size){

    size_t numPages = size/pageSize;

    if(size%pageSize!=0){
        numPages+=1;
    }

    size_t pagedSize = numPages * pageSize;

    return pagedSize;
}

static uint8_t* allocExecutableMomoryImpl(long pageSize, size_t size){
    uint8_t* codeStart = (uint8_t*)allocAlignedMemory(pageSize, size);

    if(codeStart == NULL){
        perror("out of memory");
        throw std::bad_alloc();
    }

    int error = addExecuteAccess(codeStart, size);

    if(error){
        throw std::bad_alloc();
    }
    return codeStart;
}

uint8_t* allocExecutableMemory(size_t size){
    
    long pageSize = getMemoryPageSize();
    
    size = getPagedSize(pageSize, size);

    uint8_t* codeStart = allocExecutableMomoryImpl(pageSize, size);

    return codeStart;
}

uint8_t* reallocExecutableMemory(uint8_t* oldCodeStart, size_t oldSize, size_t& newSize){
    uint8_t* newCodeStart;
    long pageSize = getMemoryPageSize();
    newSize = getPagedSize(pageSize, newSize);

    if(oldSize == newSize){
        return oldCodeStart;
    }else if(newSize<oldSize){
        newCodeStart = (uint8_t*)alignedRealloc(oldCodeStart, newSize, pageSize);
        if(newCodeStart == oldCodeStart){
            return newCodeStart;
        }else{
            oldCodeStart = newCodeStart;//corner case, address changed when reduce size
        }
    }

    newCodeStart = allocExecutableMomoryImpl(pageSize, newSize);

    memcpy(newCodeStart, oldCodeStart, std::min<size_t>(oldSize, newSize));

    freeAlignedMemroy(oldCodeStart);

    return newCodeStart;
}