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


# write first record to log
WriteLog "Virables activated, build log started at $Env:LogFolder"

function InitPython() {
	# Create virtual evnirement if it is not created
	if (!(Test-Path -Path $Env:VenvPath)) {
		WriteLog "Creating python virtual evnirement"
		python3 -m venv $Env:VenvPath
		if ($LASTEXITCODE -eq 0) {
			WriteLog "Virtual envirement created successful"
		} else {
			WriteLog "Virtual envirement created with error code $LASTEXITCODE"
			throw "Virtual envirement created with error code $LASTEXITCODE"
		}
	} else {
		WriteLog "Python virtual evnirement is already created";
	}

	# Activate virtual envirement if it is created
	if (!($Env:VIRTUAL_ENV)) {
		WriteLog "Activating python virtual envirement"
		Invoke-Expression $Env:VenvActivatePath
		if ($LASTEXITCODE -eq 0) {
			WriteLog "Virtual envirement activated successful"
		} else {
			WriteLog "Virtual envirement activated with error code $LASTEXITCODE"
			throw "Virtual envirement activated with error code $LASTEXITCODE"
		}
	} else {
		WriteLog "Venv is already activated"
	}

	# Install python dependencies in virtual invirement
	if ($Env:VIRTUAL_ENV) {
		WriteLog "Intalling python dependecies";
		pip3 install -r requirements.txt;
		if ($LASTEXITCODE -eq 0) {
			WriteLog "Python dependencies installed successful";
		} else {
			WriteLog "Python dependencies installed with error code $LASTEXITCODE";
			throw "Python dependencies installed with error code $LASTEXITCODE";
		}
	} else {
		WriteLog "Virtual envirement is not active, dependencies is not installed";
	}
}

function CleanPython() {
	if ($Env:VIRTUAL_ENV) {
		WriteLog "Deactivating python virtual envirement";
		deactivate
		if ($LASTEXITCODE -eq 0) {
			WriteLog "Virtual envirement deactivated successful";
		} else {
			WriteLog "Virtual envirement deactivated with error code $LASTEXITCODE";
		}
	} else {
		WriteLog "Venv is not active";
	}

	WriteLog "Removing venv folder";
	if (Test-Path -Path $Env:VenvPath) {
		Remove-Item $Env:VenvPath -Recurse
	} else {
		WriteLog "Venv is already removed";
	}
	if ($LASTEXITCODE -eq 0) {
		WriteLog "Venv removed seccessful";
	} else {
		WriteLog "Venv removed with error code $LASTEXITCODE";
	}
}

function CleanLog() {
	WriteLog "Removing log folder";
	if (Test-Path -Path $Env:LogFolder) {
		Remove-Item $Env:LogFolder -Recurse
	} 
}

function CleanGeneratedProject() {
	WriteLog "Removing generated project folder";
	if (Test-Path -Path $Env:BuildPath) {
		Remove-Item $Env:BuildPath -Recurse
	} else {
		WriteLog "Genereated project folder is already removed";
	}
	if ($LASTEXITCODE -eq 0) {
		WriteLog "Genereated project folder removed seccessful";
	} else {
		WriteLog "Genereated project folder removed with error code $LASTEXITCODE";
	}
}

function GenerateProject() {
	if (!(Test-Path -Path $Env:BuildPath))
	{
		New-Item -ItemType "directory" -Path $Env:BuildPath
	}

	WriteLog "Installing conan dependencies"
	Set-Location $Env:BuildPath
	conan install $Env:ProjectPath --build=missing
	if ($LASTEXITCODE -eq 0) {
		WriteLog "Conan dependencides installed seccessful"
	} else {
		WriteLog "Conan dependencides installed with error code $LASTEXITCODE"
	}

	WriteLog "Generating project with cmake"
	Set-Location $Env:ProjectPath
	cmake -S $Env:ProjectPath -B $Env:BuildPath -G $Env:DefaultGenerator
	if ($LASTEXITCODE -eq 0) {
		WriteLog "Generating project finished seccessfuly"
	} else {
		WriteLog "Generating project finished with error code $LASTEXITCODE"
	}
}

function BuildProject() {
	WriteLog "Bilding project"
	cmake --build $Env:BuildPath --config Release
	if ($LASTEXITCODE -eq 0) {
		WriteLog "Build project finished seccessfuly"
	} else {
		WriteLog "Build project finished with error code $LASTEXITCODE"
	}
}


# -init init python
# -generate generate project
# -build build project
# -cproject clear project
# -call clear all
# -clog clear log

if ($args.Contains("-init")) {
	InitPython
}
if ($args.Contains("-generate")) {
	GenerateProject
}
if ($args.Contains("-build")) {
	BuildProject
}
if ($args.Contains("-cproject")) {
	CleanGeneratedProject
}
if ($args.Contains("-clog")) {
	CleanLog
}
if ($args.Contains("-call")) {
	CleanPython
	CleanGeneratedProject
	CleanLog
}
