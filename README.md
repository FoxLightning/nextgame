#### Build workflow

1. Install Pyhton 3 https://www.python.org/downloads/
2. Make sure that PowerShell installed and works correctly. ```Set-ExecutionPolicy -ExecutionPolicy Bypass```
4. Run build script
``` PS1
.\scripts\build.ps1 -init -generate -build
```

#### Build script overview

command line params:
* ```-init``` init python
* ```-generate``` generate project
* ```-build``` build project
* ```-cproject``` clear project
* ```-call``` clear all
* ```-clog``` clear log
