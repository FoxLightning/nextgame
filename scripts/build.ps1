# First of all - setting up envirement variables
# end script with error if variables is not setup
. ./scripts/variables.ps1
if (!($Env:IsVarActive)) {
	throw "Variables is not setup"
}

# setting up build log file
$Logfile = "$Env:LogFolder/$Env:ProjectName" +
		   (Get-Date).toString("ddMMyyyy_HH-mm-ss") +
		   ".log"
function WriteLog {
	Param ([string]$LogString)
	$Stamp = (Get-Date).toString($Env:TimeStamp)
	$LogMessage = "$Stamp $LogString"
	Write-Output $LogMessage

	if (!(Test-Path -Path $Env:LogFolder)) {
		New-Item -ItemType "directory" -Path $Env:LogFolder
	}
	Add-content $LogFile -value $LogMessage
}

function LogPreviousCommandStatus {
	Param ([int]$RiseError=0)

	if ($LASTEXITCODE -eq 0) {
		WriteLog "Result successful"
	} else {
		$ErrorMesage = "Result with error code: $LASTEXITCODE"
		WriteLog $ErrorMesage
		if (!(RiseError -eq 0))
		{
			throw $ErrorMesage
		}
	}
}

function InitPython {
	# Create virtual evnirement if it is not created
	if (!(Test-Path -Path $Env:VenvPath)) {
		WriteLog "Creating python virtual evnirement"
		python3 -m venv $Env:VenvPath
		LogPreviousCommandStatus
	} else {
		WriteLog "Python virtual evnirement is already created";
	}

	# Activate virtual envirement if it is created
	if (!($Env:VIRTUAL_ENV)) {
		WriteLog "Activating python virtual envirement"
		Invoke-Expression $Env:VenvActivatePath
		LogPreviousCommandStatus 1
	} else {
		WriteLog "Venv is already activated"
	}

	# Install python dependencies in virtual invirement
	if ($Env:VIRTUAL_ENV) {
		WriteLog "Intalling python dependecies";
		pip3 install -r requirements.txt;
		LogPreviousCommandStatus 1
	} else {
		WriteLog "Virtual envirement is not active, dependencies is not installed";
	}
}

function CleanPython {
	if ($Env:VIRTUAL_ENV) {
		WriteLog "Deactivating python virtual envirement";
		deactivate
		LogPreviousCommandStatus
	} else {
		WriteLog "Venv is not active";
	}

	WriteLog "Removing venv folder";
	if (Test-Path -Path $Env:VenvPath) {
		Remove-Item $Env:VenvPath -Recurse
	} else {
		WriteLog "Venv is already removed";
	}
	LogPreviousCommandStatus
}

function CleanLog {
	WriteLog "Removing log folder";
	if (Test-Path -Path $Env:LogFolder) {
		Remove-Item $Env:LogFolder -Recurse
	} 
}

function CleanGeneratedProject {
	WriteLog "Removing generated project folder";
	if (Test-Path -Path $Env:BuildPath) {
		Remove-Item $Env:BuildPath -Recurse
	} else {
		WriteLog "Genereated project folder is already removed";
	}
	LogPreviousCommandStatus
}

function GenerateProject {
	if (!(Test-Path -Path $Env:BuildPath))
	{
		New-Item -ItemType "directory" -Path $Env:BuildPath
	}

	WriteLog "Installing conan dependencies"
	Set-Location $Env:BuildPath
	conan install $Env:ProjectPath --build=missing
	LogPreviousCommandStatus

	WriteLog "Generating project with cmake"
	Set-Location $Env:ProjectPath
	cmake -S $Env:ProjectPath -B $Env:BuildPath -G $Env:DefaultGenerator
	LogPreviousCommandStatus
}

function BuildProject {
	WriteLog "Bilding project"
	cmake --build $Env:BuildPath --config Release
	LogPreviousCommandStatus
}

function CleanAll {
	CleanPython
	CleanGeneratedProject
	CleanLog
}

# write first record to log
WriteLog "Virables activated, build log started at $Env:LogFolder"

foreach ($arg in $args) {
	if ($arg -eq "-init") {
		InitPython
	} elseif ($arg -eq "-generate") {
		GenerateProject
	} elseif ($arg -eq "-build") {
		BuildProject
	} elseif ($arg -eq "-generate") {
		GenerateProject
	} elseif ($arg -eq "-clog") {
		CleanLog
	} elseif ($arg -eq "-call") {
		CleanAll
	} elseif ($arg -eq "-help") {
		Write-Output $Env:Instruction
	} else {
		WriteLog "Invalid argument: '$arg'"
		Write-Output $Env:Instruction
		break
	}
}
