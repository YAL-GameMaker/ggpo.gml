@echo off
echo ========================================================================================
set args=-std=c++17 -g
call :addfiles ggpo_gml/*.cpp
call :addfiles src/lib/ggpo/backends/*.cpp
call :addfiles src/lib/ggpo/network/*.cpp
call :addfiles src/lib/ggpo/*.cpp
::echo "%args%"
::-s EXPORT_ALL=1
::-Wl,-rpath,assets/
cmd /C emcc %args% ^
  -fPIC ^
  -DGML_SOCKETS ^
  -DWASM ^
  -s WASM=1 ^
  -s NO_EXIT_RUNTIME=1 ^
  -s EXPORTED_FUNCTIONS=["_malloc","_realloc","_free","_main"] ^
  -s EXPORTED_RUNTIME_METHODS=["ccall","cwrap"] ^
  -Isrc/include ^
  -Isrc/lib/ggpo ^
  -o wasm/ggpo_gml_wasm.html
if %ERRORLEVEL% NEQ 0 goto :emcc_trouble
echo Compile OK!

echo Copying...

copy /Y wasm\ggpo_gml_wasm.wasm ggpo_gml_23\datafiles\ggpo_gml_wasm.wasm
if %ERRORLEVEL% NEQ 0 goto :copy_trouble

copy /Y wasm\ggpo_gml_wasm.js ggpo_gml_23\datafiles\ggpo_gml_wasm.js
if %ERRORLEVEL% NEQ 0 goto :copy_trouble

echo OK!
goto eof

:addfiles
	set dir=%~dp1
	::echo %1 %dir%
	for %%f in (%1) do call :addfile %dir%%%f
	goto :eof

:addfile
	::echo "%1" "%args%"
	set args=%args% %1
	goto :eof

:emcc_trouble
	echo EMCC didn't exit cleanly
	goto :eof
:copy_trouble
	echo Failed to copy!
	goto :eof

:eof
