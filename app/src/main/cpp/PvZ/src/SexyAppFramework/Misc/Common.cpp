//
// Created by 28636 on 2025/5/26.
//

#include "PvZ/SexyAppFramework/Misc/Common.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#include "PvZ/SexyAppFramework/Misc/PerfTimer.h"

//std::string Sexy::vformat(const char* fmt, va_list argPtr)
//{
//    // We draw the line at a 1MB string.
//    const int maxSize = 1000000;
//
//    // If the string is less than 161 characters,
//    // allocate it on the stack because this saves
//    // the malloc/free time.
//    const int bufSize = 161;
//    char stackBuffer[bufSize];
//
//    int attemptedSize = bufSize - 1;
//
//    int numChars = 0;
//#ifdef _WIN32
//    numChars = _vsnprintf(stackBuffer, attemptedSize, fmt, argPtr);
//#else
//    numChars = vsnprintf(stackBuffer, attemptedSize, fmt, argPtr);
//#endif
//
//    //cout << "NumChars: " << numChars << endl;
//
//    if ((numChars >= 0) && (numChars <= attemptedSize))
//    {
//        // Needed for case of 160-character printf thing
//        stackBuffer[numChars] = '\0';
//
//        // Got it on the first try.
//        return std::string(stackBuffer);
//    }
//
//    // Now use the heap.
//    char* heapBuffer = NULL;
//
//    while (((numChars == -1) || (numChars > attemptedSize)) &&
//           (attemptedSize < maxSize))
//    {
//        // Try a bigger size
//        attemptedSize *= 2;
//        heapBuffer = (char*)realloc(heapBuffer, (attemptedSize + 1));
//#ifdef _WIN32
//        numChars = _vsnprintf(heapBuffer, attemptedSize, fmt, argPtr);
//#else
//        numChars = vsnprintf(heapBuffer, attemptedSize, fmt, argPtr);
//#endif
//    }
//
//    heapBuffer[numChars] = 0;
//
//    std::string result = std::string(heapBuffer);
//
//    free(heapBuffer);
//    return result;
//}
//
//std::string Sexy::StrFormat(const char* fmt ...)
//{
//    va_list argList;
//    va_start(argList, fmt);
//    std::string result = vformat(fmt, argList);
//    va_end(argList);
//
//    return result;
//}
//
//void Sexy::StrDelete(const SexyString &fmt) {
//    auto my_exchange_and_add = [](int *ptr, int value) -> int {
//        int original_value = *ptr;
//        *ptr += value;
//        return original_value;
//    };
//
//    int ptr = fmt[0] - 12;
//    if (my_exchange_and_add((int *)(fmt[0] - 4), -1) <= 0) {
//        operator delete((int *)ptr);
//    }
//}