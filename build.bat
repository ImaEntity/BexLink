@echo off

set compress=1

:: Handle parameters and set correct flags
:paramHandler
if not "%1"=="" (
  if "%1"=="--nocompress" set compress=0

  shift
  goto :paramHandler
)

:: Setup
if not exist bin mkdir bin >nul

:: Compile and link
gcc -s src/main.c -Os -Wall -Werror -o bin/main.exe ^
-lkernel32 -luser32 -lshell32 ^
-fno-asynchronous-unwind-tables -fno-ident -falign-functions=1 -falign-jumps=1 -ffreestanding ^
-Wl,-e,CRTBootstrapper -Wl,--file-alignment=1 -Wl,--section-alignment=1 ^
-nostdlib -nostartfiles -nodefaultlibs -static

:: Compress if flag is set
if %compress%==1 mpress -s bin/main.exe >nul