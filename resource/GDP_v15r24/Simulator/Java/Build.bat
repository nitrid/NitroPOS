@echo off

@echo Compiling...

set PRJ_DIR=%CD%
set OUT_DIR=%CD%\..\..\Gmp3Java

@rd /s /q "%OUT_DIR%" > nul 2> nul
@md "%OUT_DIR%" > nul 2> nul

if exist "C:\Program Files\Java\jdk1.8.0_221" set JAVA_HOME=C:\Program Files\Java\jdk1.8.0_221
if exist "D:\Program Files\Java\jdk1.8.0_221" set JAVA_HOME=D:\Program Files\Java\jdk1.8.0_221


if "%JAVA_HOME%"=="" (
	@echo invalid Java Home
	pause
	goto :Exit
)

rem aşağıdakiler her sistemde birkez yapılması gerekebilir.
rem cd D:\Program Files\apache-ant-1.10.7
rem bin\ant -f fetch.xml -Ddest=system
rem cd %PRJ_DIR%

@call "E:\ant\bin\ant" -f %PRJ_DIR%\build.xml

@echo %errorlevel%
if NOT "%errorlevel%"=="0" (
	@echo Compile error
	pause
	goto :Exit
)

@copy %PRJ_DIR%\dist\*.* %OUT_DIR%\*.*

:Exit
pause
