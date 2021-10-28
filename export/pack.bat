@echo off

if not exist "ggpo_gml-for-GMS1" mkdir "ggpo_gml-for-GMS1"
cmd /C copyre ..\ggpo_gml.gmx\extensions\ggpo_gml.extension.gmx ggpo_gml-for-GMS1\ggpo_gml.extension.gmx
cmd /C copyre ..\ggpo_gml.gmx\extensions\ggpo_gml ggpo_gml-for-GMS1\ggpo_gml
cmd /C copyre ..\ggpo_gml.gmx\datafiles\ggpo_gml.html ggpo_gml-for-GMS1\ggpo_gml\Assets\datafiles\ggpo_gml.html
cd ggpo_gml-for-GMS1
cmd /C 7z a ggpo_gml-for-GMS1.7z *
move /Y ggpo_gml-for-GMS1.7z ../ggpo_gml-for-GMS1.gmez
cd ..

if not exist "ggpo_gml-for-GMS2\extensions" mkdir "ggpo_gml-for-GMS2\extensions"
if not exist "ggpo_gml-for-GMS2\datafiles" mkdir "ggpo_gml-for-GMS2\datafiles"
if not exist "ggpo_gml-for-GMS2\datafiles_yy" mkdir "ggpo_gml-for-GMS2\datafiles_yy"
cmd /C copyre ..\ggpo_gml_yy\extensions\ggpo_gml ggpo_gml-for-GMS2\extensions\ggpo_gml
cmd /C copyre ..\ggpo_gml_yy\datafiles\ggpo_gml.html ggpo_gml-for-GMS2\datafiles\ggpo_gml.html
cmd /C copyre ..\ggpo_gml_yy\datafiles_yy\ggpo_gml.html.yy ggpo_gml-for-GMS2\datafiles_yy\ggpo_gml.html.yy
cd ggpo_gml-for-GMS2
cmd /C 7z a ggpo_gml-for-GMS2.zip *
move /Y ggpo_gml-for-GMS2.zip ../ggpo_gml-for-GMS2.yymp
cd ..

if not exist "ggpo_gml-for-GMS2.3+\extensions" mkdir "ggpo_gml-for-GMS2.3+\extensions"
if not exist "ggpo_gml-for-GMS2.3+\datafiles" mkdir "ggpo_gml-for-GMS2.3+\datafiles"
cmd /C copyre ..\ggpo_gml_23\extensions\ggpo_gml ggpo_gml-for-GMS2.3+\extensions\ggpo_gml
cmd /C copyre ..\ggpo_gml_23\datafiles\ggpo_gml.html ggpo_gml-for-GMS2.3+\datafiles\ggpo_gml.html
cd ggpo_gml-for-GMS2.3+
cmd /C 7z a ggpo_gml-for-GMS2.3+.zip *
move /Y ggpo_gml-for-GMS2.3+.zip ../ggpo_gml-for-GMS2.3+.yymps
cd ..

pause