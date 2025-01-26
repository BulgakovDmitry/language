#include "myLib.h"

size_t getSizeOfFile(FILE* file, const char* const nameFile)
{
    assert(file);

    struct stat st;     
    stat(nameFile, &st);                                                                             
    size_t size = st.st_size;

    return size;
}

char* readFileToBuffer(FILE* file, size_t size_file)
{
    assert(file);
    assert(size_file);

    char* buffer = (char*)calloc(size_file, sizeof(char));    // СОЗДАНИЕ БУФФЕРА
    assert(buffer);

    size_file = fread(buffer, sizeof(char), size_file, file); // ЗАПОЛЕНИЕ БУФФЕРА

    return buffer;
}