@echo off

if "%A5_REDISCLIENT%" == "" goto nothing

if "%A5_LIBBSON%" == "" goto nothing
set A53RDPARTYBUILD_LIBSON=%A5BLDROOT%\%A5COMPILERVERSION%\3rdParty\Libbson\

xcopy %A53RDPARTYBUILD_LIBSON%Debug\libbson-1.0.dll %A5_LIBBSON%\bin\%A5COMPILERVERSION%\debug\
xcopy %A53RDPARTYBUILD_LIBSON%Debug\libbson-1.0.pdb %A5_LIBBSON%\bin\%A5COMPILERVERSION%\debug\
xcopy %A53RDPARTYBUILD_LIBSON%Release\libbson-1.0.dll %A5_LIBBSON%\bin\%A5COMPILERVERSION%\release\

xcopy %A53RDPARTYBUILD_LIBSON%Debug\bson-1.0.lib %A5_LIBBSON%\bin\%A5COMPILERVERSION%\debug\
xcopy %A53RDPARTYBUILD_LIBSON%Release\bson-1.0.lib %A5_LIBBSON%\bin\%A5COMPILERVERSION%\release\
xcopy %A53RDPARTYBUILD_LIBSON%Debug\bson-static-1.0.lib %A5_LIBBSON%\bin\%A5COMPILERVERSION%\debug\
xcopy %A53RDPARTYBUILD_LIBSON%Release\bson-static-1.0.lib %A5_LIBBSON%\bin\%A5COMPILERVERSION%\release\

goto done
:nothing
echo "A5_LIBBSON needs to be defined"
:done