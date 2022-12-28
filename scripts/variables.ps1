# setting up envirement variables
Write-Output "Setting up the evnirement variables"
$Env:DirSeparator = '/'

# project variables
$Env:ProjectPath = (Get-Location).ToString();
$Env:ProjectName = "nextgame"
$Env:BuildPath = $Env:ProjectPath + $Env:DirSeparator + "build"
$Env:DefaultGenerator = "Visual Studio 17 2022";


# log variables
$Env:TimeStamp = "[dd.MM HH:mm:ss]"
$Env:LogFolder = $Env:ProjectPath + $Env:DirSeparator + "buildlog"

# python virtual envirement variables
$Env:VenvFolderName = ".venv"
$Env:VenvPath = $Env:ProjectPath + $Env:DirSeparator + $Env:VenvFolderName
$Env:VenvActivatePath = $Env:VenvPath + $Env:DirSeparator + "Scripts" + $Env:DirSeparator + "activate.ps1" # Platform dependent

# if errors is not occurs, set flag active
$Env:IsVarActive = "true"
