@echo off
set dllPath=%~1
set solutionDir=%~2
set projectDir=%~3
set arch=%~4
set config=%~5

echo Running pre-build for %config%

where /q GmlCppExtFuncs
if %ERRORLEVEL% EQU 0 (
	echo Running GmlCppExtFuncs...
	GmlCppExtFuncs ^
	--prefix ggpo_gml^
	--wasm^
	--cpp "%projectDir%autogen.cpp"^
	--gml "%solutionDir%ggpo_gml_23/extensions/ggpo_gml/autogen.gml"^
	%projectDir%ggpo_*.cpp
)