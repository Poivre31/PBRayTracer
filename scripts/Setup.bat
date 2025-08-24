@echo off

cd ..
vendor\premake\premake5.exe vs2022 --file=Build.lua
popd
pause