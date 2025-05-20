#include "./include/types.h"
#include "./include/bex.h"
#include "./include/coff.h"

#include <windows.h>

u64 LengthStr(const wstring str) {
    u64 len = 0;
    while(str[len++]);
    return len;
}

void error(const wstring msg) {
    WriteConsoleW(
        GetStdHandle(STD_OUTPUT_HANDLE),
        msg,
        LengthStr(msg),
        null,
        null
    );
    
    ExitProcess(1);
}

#define CompareMem(b0, b1, size) (RtlCompareMemory(b0, b1, size) == (size))
boolean CompareStr(wstring str0, wstring str1) {
    u64 len0 = LengthStr(str0);
    u64 len1 = LengthStr(str1);

    if(len0 != len1) return false;
    u64 len = len0 < len1 ? len0 : len1;

    return CompareMem(str0, str1, len);
}

wstring nextArg(int argc, wstring *argv, int idx) {
    if(idx >= argc)
        error(L"Unexpected end of arguments!");

    return argv[idx];
}

void CRTBootstrapper() {
    int argc;
    wstring *argv = CommandLineToArgvW(GetCommandLineW(), &argc);

    if(argc < 2)
        error(L"No input files specified!");

    // Who tf would need more than this
    u8 inputFileCount = 0;
    wstring inputFileNames[64];
    wstring outputFile = null;
    wstring entrySymbol = null;

    int idx = 1;
    while(idx < argc) {
        if(CompareStr(argv[idx], L"-e"))      entrySymbol = nextArg(argc, argv, ++idx);
        else if(CompareStr(argv[idx], L"-o")) outputFile  = nextArg(argc, argv, ++idx);
        else
            inputFileNames[inputFileCount++] = argv[idx];

        idx++;
    }

    if(outputFile == null)
        outputFile = L"a.bex";
    
    if(inputFileCount == 0)
        error(L"No input files specified!");

    HANDLE *inputFiles = LocalAlloc(LMEM_FIXED, sizeof(HANDLE) * inputFileCount);
    for(u8 i = 0; i < inputFileCount; i++) {
        inputFiles[i] = CreateFileW(
            inputFileNames[i],
            GENERIC_READ,
            FILE_SHARE_READ,
            null,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            null
        );

        if(inputFiles[i] == INVALID_HANDLE_VALUE)
            error(L"Failed to open input file!");
    }
    
    LocalFree(inputFiles);
    ExitProcess(0);
}