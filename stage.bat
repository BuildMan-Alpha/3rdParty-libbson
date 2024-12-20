@echo off

if "%A5_LIBBSON%" == "" goto nothing
set A53RDPARTYBUILD_LIBSON=%A5BLDROOT%\%A5COMPILERVERSION%\3rdParty\Libbson\
xcopy "%A5_LIBBSON%" "%A53RDPARTYBUILD_LIBSON%" /s /y
cd %A53RDPARTYBUILD_LIBSON%
REM c:\dev\3rdparty\CMake\x86\3.7.1\bin\cmake -G "%A5CMAKEGENERATOR%"
REM c:\dev\3rdparty\CMake\3.15.4\x86\bin\cmake -G "%A5CMAKEGENERATOR%" -A Win32
c:\dev\3rdparty\CMake\3.21.4\bin\cmake -G "%A5CMAKEGENERATOR%" -A Win32
echo "%A5_LIBBSON% source files have been staged to build location" 
goto done
:nothing
echo "A5_LIBBSON needs to be defined"
:done