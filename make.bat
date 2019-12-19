@echo off

set input=%1
findstr /i /r /c:"^[ ]*:%input%\>" "%~f0" >nul 2>nul && goto %input%

call :testLabelExist %1 && goto %1 || echo COMMAND DOES NOT EXIST && exit /B

:setup
    call %comspec% /k "d:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\VC\Auxiliary\Build\vcvars64.bat"
    VsDevCmd -host_arch=amd64 -arch=amd64
    exit /B

:configure
    rem call :clean
    cmake -B build/ -G "NMake Makefiles"
    exit /B

:build
    pushd build\
    nmake
    popd
    exit /B

:run
    pushd build\
    lagerexample.exe
    popd
    exit /B

:clean
    rmdir /S /Q build\

:testLabelExist
    for /f "delims=" %%t in (
        'forfiles /p "%~dp0." /m "%~nx0" /c "cmd /d /c @echo 0x09"'
    ) do (
        findstr /i /m /r /c:"^[^:]*[ %%t]*:%~1[ %%t:;,=+]" /c:"^[^:]*[ %%t]*:%~1$" "%~f0" >nul 2>nul
    )
    exit /b %errorlevel%
