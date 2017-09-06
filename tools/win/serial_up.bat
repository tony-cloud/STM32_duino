@Echo off
Rem: Note %~dp0 get path of this batch file
Rem: Need to change drive if My Documents is on a drive other than C:
set driverLetter=%~dp0
set driverLetter=%driverLetter:~0,2%
rem %driverLetter%
cd %~dp0

set str=%3

set str=%str:/=\%

set commport=%1

set commportnum=%commport:COM=%

if "%2"=="CH340"     goto CH340
if "%2"=="PL2303"    goto PL2303
if "%2"=="ATKMINI"   goto ATKMINI

if "%2"=="F407V11"   goto F407V11

if "%2"=="F103R"     goto F103R
if "%2"=="F103C"     goto F103C
if "%2"=="UNUSED"    goto UNUSED
goto UPLOAD


:STM407V11_STM
"%ProgramFiles%\STMicroelectronics\Software\Flash Loader Demo\STMFlashLoader.exe"  -c --pn %commportnum% --br 230400 --co ON --to 10000 -Dtr --Lo -Rts --Lo  -Rts --Hi -Dtr --Hi  -i %4 -d --a %5 --fn  %str% -r  --a %6
goto EXIT


:CH340
echo for CH340  Dtr_Lo Rts_Lo2Hi
:NOTE                                         -2,-1,1,2       #for all CH340 USB2SERIAL
stm32flash -b 230400 -w %str% %1 -S%5 -g%6 -i -2,-1,1,2 -n 40
goto EXIT

:F407V11
:NOTE -Dtr --Lo  -Rts --Lo  -Rts --Hi -Dtr --Hi
:NOTE  -2        -1            1       2        #for all CH340 USB2SERIAL
echo for F407V11 Board Dtr_Lo Rts_Lo2Hi
stm32flash -b 230400 -w %str% %1 -S%5 -g%6 -i -2,-1,1,2 -n 40
goto EXIT



:PL2303
:NOTE dtr-rest rts-boot0   entry   rest_0 ,boot0_0, rest_1: boot0_1 rest_1 #for all pl2303  USB2SERIAL
echo for PL2303 Rts_Hi Dtr_Lo2Hi
stm32flash -b 230400 -w %str% %1 -S%5 -g%6 -i 1,-2,2,-1 -n 40
goto EXIT

:ATKMINI
:NOTE GPIO_RTS = 1, GPIO_DTR 2, GPIO_BRK 3,
:NOTE dtr-rest rts-boot0   entry   rest_0 ,boot0_0, rest_1: boot0_1 rest_1 #for all pl2303  USB2SERIAL
echo for ATKMINI Board  Rts_Hi Dtr_Lo2Hi
stm32flash -b 230400 -w %str% %1 -S%5 -g%6 -i 1,-2,2,-1 -n 40
goto EXIT


:F103C
:F103R
:UPLOAD
:UNUSED
echo for General Board Dtr/Rts unused
stm32flash -b 115200 -w %str% %1 -S%5 -g%6 -n 40

:EXIT