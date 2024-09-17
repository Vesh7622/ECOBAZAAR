@echo off
REM Build script for the project

REM Set the source file and output binary name
set SRC_FILE=Main.c Buyer.c Seller.c product_management.c User_Management.c
set OUTPUT=bin.exe

REM Compile the source file
gcc %SRC_FILE% -o %OUTPUT%

REM Check if the build was successful
if %errorlevel% equ 0 (
    echo Build succeeded.
    echo Running the executable...
    %OUTPUT%
) else (
    echo Build failed.
)