#include "myLib.h"

size_t getSizeOfFile(FILE* file, const char* const nameFile)
{
    assert(file);
    assert(nameFile);

    struct stat st;     
    stat(nameFile, &st);                                                                             
    size_t size = st.st_size;
    assert(size);

    return size;
}