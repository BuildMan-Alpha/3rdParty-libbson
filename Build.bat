@echo off

cd \dev\a5v12\src
call SetBuildEnvironment.bat
cd \dev\3rdparty\libbson
call stage.bat
start /B /WAIT MSbuild.exe /m /p:UseEnv=true;Configuration=Release;Platform=Win32 %A53RDPARTYBUILD_LIBSON%\libbson.sln
start /B /WAIT MSbuild.exe /m /p:UseEnv=true;Configuration=Debug;Platform=Win32 %A53RDPARTYBUILD_LIBSON%\libbson.sln
cd \dev\3rdparty\libbson
call updatebin.bat
