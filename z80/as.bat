@echo off
set file=%1
if "%1"=="" goto hilfe
set bin=C:\my\aswcurr\bin
%bin%\asw.exe -L "%file%.asm" -i C:\Daten\Z80\aswcurr\include
%bin%\p2bin.exe -r $-$ "%file%.p"
del "%file%.p"
rem bdiff "%file%.rom" "%file%.bin"
goto end
:hilfe
echo Aufruf: as.bat file (ohne Endung .asm)
echo erzeugt aus file.asm Datei file.bin
:end
