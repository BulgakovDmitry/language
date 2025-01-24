#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include "myLib/myLib.h"
#include "language.h"
#include "structLanguage.h"

//FILE* Graph_File;
//FILE* Graph_File_Utf8;

Language* LanguageCtor()
{
    FILE* logFile = fopen(logFileName, "w");
    ASSERT(logFile, "loGFile = NULL", stdout);

    fprintf (logFile, "<pre>");

    Language* languageData = (Language*)calloc(1, sizeof(Language));
    ASSERT(languageData, "languageData = NULL", logFile);

    languageData->buffer = (char*)calloc(1, sizeof(char));
    ASSERT(languageData->buffer, "onegin_data = NULL", logFile);

    languageData->nameTable = (NameTable*)calloc(MAX_NUMBER_ID, sizeof(NameTable));
    ASSERT(languageData->nameTable, "name_table = NULL", logFile);

    FCLOSE(logFile);
    return languageData;
}

void LanguageDtor(Language* languageData)
{
    FILE* logFile = fopen(logFileName, "w");
    ASSERT(logFile, "loGFile = NULL", stdout);

    ASSERT(languageData, "languageData = NULL, it is impossible to close this file", logFile);

    ASSERT(languageData->buffer, "languageData->buffer = NULL, it is impossible to do FREE", logFile);
    FREE(languageData->buffer);

    ASSERT(languageData->nameTable, "languageData->nameTable = NULL, it is impossible to do FREE", logFile);
    FREE(languageData->nameTable);

    FREE(languageData);

    FCLOSE(logFile);    
}
