@echo off
echo Checking for Graphics_Engine.exe...
echo.

cd /d "C:\Users\Ahmed\source\repos\Graphics_Engine"

echo Searching in x64\Debug...
if exist "x64\Debug\Graphics_Engine.exe" (
    echo FOUND: x64\Debug\Graphics_Engine.exe
    dir "x64\Debug\SDL3.dll" 2>nul
    if errorlevel 1 (
        echo SDL3.dll NOT FOUND in x64\Debug\
        echo Copying SDL3.dll...
        copy "libraries\SDL\bin\SDL3.dll" "x64\Debug\"
    ) else (
        echo SDL3.dll EXISTS in x64\Debug\
    )
)

echo.
echo Searching in x64\Release...
if exist "x64\Release\Graphics_Engine.exe" (
    echo FOUND: x64\Release\Graphics_Engine.exe
    dir "x64\Release\SDL3.dll" 2>nul
    if errorlevel 1 (
        echo SDL3.dll NOT FOUND in x64\Release\
        echo Copying SDL3.dll...
        copy "libraries\SDL\bin\SDL3.dll" "x64\Release\"
    ) else (
        echo SDL3.dll EXISTS in x64\Release\
    )
)

echo.
echo Searching in Debug...
if exist "Debug\Graphics_Engine.exe" (
    echo FOUND: Debug\Graphics_Engine.exe
    dir "Debug\SDL3.dll" 2>nul
    if errorlevel 1 (
        echo SDL3.dll NOT FOUND in Debug\
        echo Copying SDL3.dll...
        copy "libraries\SDL\bin\SDL3.dll" "Debug\"
    ) else (
        echo SDL3.dll EXISTS in Debug\
    )
)

echo.
echo Searching in Release...
if exist "Release\Graphics_Engine.exe" (
    echo FOUND: Release\Graphics_Engine.exe
    dir "Release\SDL3.dll" 2>nul
    if errorlevel 1 (
        echo SDL3.dll NOT FOUND in Release\
        echo Copying SDL3.dll...
        copy "libraries\SDL\bin\SDL3.dll" "Release\"
    ) else (
        echo SDL3.dll EXISTS in Release\
    )
)

echo.
echo Done!
pause
