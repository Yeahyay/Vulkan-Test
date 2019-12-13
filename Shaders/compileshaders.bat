@echo off

:userinput

set FRAG=0
set VERT=0
set SHADER=0

set /p SHADER="Enter shader name: "
set FRAG=%SHADER%
set VERT=%SHADER%

if EXIST %SHADER%.vert (
	if EXIST %SHADER%.frag (
		echo COMPILING
		%VK_SDK_PATH%\Bin32\glslc.exe %VERT%.vert -o %VERT%_vert.spv
		%VK_SDK_PATH%\Bin32\glslc.exe %FRAG%.frag -o %FRAG%_frag.spv
	 	rem glslangValidator -V "%VERT%.vert" -o "%VERT%_vert.spv"
		rem glslangValidator -V "%FRAG%.frag" -o "%FRAG%_frag.spv"
		rem glslangValidator -V --variable-name %VERT%VertexCode -o vertex.h %VERT%.vert
		rem glslangValidator -V --variable-name %FRAG%FragmentCode -o fragment.h %FRAG%.frag
		echo COMPILED
	)
) else (
	echo "%SHADER%.frag and %SHADER%.vert do not exist"
	GOTO userinput
)
pause
