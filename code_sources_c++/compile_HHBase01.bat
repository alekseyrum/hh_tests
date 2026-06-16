@echo off

SET "PREFIX=%~dp0"
echo %PREFIX%

SET "SRCFILE=HHBase01.cpp"
SET "CXXEXE=HHBase01.exe"
SET "LOGFILE=HHBase01.log"
SET "CXX=g^+^+.exe"
SET "CXXFLAGS=-o %CXXEXE% -O2"

rem -o <file>  		- вывести результат в файл
rem -x <language>	- язык компилятора: c c++ assembler none
rem 		SET "EFLAGS=-m32"

if exist .\%CXXEXE% (
	ECHO old file exists: DELETE
	DEL /f .\%CXXEXE% 
)

%CXX% %CXXFLAGS% -x c++ %SRCFILE% 
rem > %LOGFILE%

	IF NOT %errorlevel% == 0 (
		ECHO Error: Failed to build C++ application.
		pause
		exit /b 1
	) 

CALL .\%CXXEXE%
pause

