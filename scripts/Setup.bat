@echo off

pushd ..
scripts\premake5.exe --file=Build.lua vs2022
popd
pause