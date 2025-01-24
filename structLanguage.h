#ifndef STRUCT_LANGUAGE_H
#define STRUCT_LANGUAGE_H

const char* const logFileName = "LOG_LANGUAGE.html";
const int MAX_NUMBER_ID = 1024;

Language* LanguageCtor ();
void      LanguageDtor (Language* languageData);


#endif