@echo off

set PROJ_DIR=%~1
set PROJ_DIR=%PROJ_DIR:'=%

cd %PROJ_DIR%
cd ../
move ti_msp_dl_config.c Core/src
move ti_msp_dl_config.h Core/inc

