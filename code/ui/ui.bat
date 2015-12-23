@set include=
@set savedpath=%path%
@set path=%path%;..\..\..\bin

del /q vm
if not exist vm\nul mkdir vm
cd vm

set cc=..\..\..\bin\lcc -DQ3_VM -DJK2_UI -S -Wf-target=bytecode -Wf-g -I..\..\cgame -I..\..\game -I..\..\ui %1

%cc% ../ui_main.c
@if errorlevel 1 goto quit
%cc% ../../game/bg_misc.c
@if errorlevel 1 goto quit
%cc% ../../game/bg_weapons.c
@if errorlevel 1 goto quit
%cc% ../../game/bg_lib.c
@if errorlevel 1 goto quit
%cc% ../../game/q_math.c
@if errorlevel 1 goto quit
%cc% ../../game/q_shared.c
@if errorlevel 1 goto quit
%cc% ../ui_atoms.c
@if errorlevel 1 goto quit
%cc% ../ui_force.c
@if errorlevel 1 goto quit
%cc% ../ui_shared.c
@if errorlevel 1 goto quit
%cc% ../ui_gameinfo.c
@if errorlevel 1 goto quit

%cc% ../ui_multiversion.c
@if errorlevel 1 goto quit
%cc% ../ui_multiversion_syscalls.c
@if errorlevel 1 goto quit
%cc% ../../game/bg_multiversion.c
@if errorlevel 1 goto quit

..\..\..\bin\q3asm -f ../ui
@if errorlevel 1 goto quit

:quit
@set path=%savedpath%
@set savedpath=

cd ..
