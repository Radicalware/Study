#!/usr/bin/env pwsh

param (
    [switch] $Debug,
    [switch] $Clean, 
    [switch] $Overwrite,

    [switch] $NoCmake,
    [switch] $NoMake,
    [switch] $NoInstall
)

Import-Module "../../Cmake/Arg_Struct.ps1" -Force
Import-Module "../../Cmake/PS_Builder.ps1" -Force
Import-Module "../../Cmake/Run_CMake.ps1"  -Force

# -----------------------------------
$proj_name  = "EXECUTABLE";
$executable = $true;
# -----------------------------------

# cmd.exe /c "uic.exe -o ui_QuickApp.h QuickApp.ui"
# cmd.exe /c "copy /Y /V ui_QuickApp.h .\Solution\include"

Set-Location $(Split-Path -parent $PSCommandPath);
$ArgStruct = [Arg_Struct]::new($proj_name, $PSScriptRoot, [bool[]]($executable, $Debug, $Clean, $Overwrite, $NoCmake, $NoMake, $NoInstall));
$run = [Run_CMake]::new($ArgStruct).Print_Config().Link_n_Compile();


