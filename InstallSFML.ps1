$SFMLDownloadUrl = "https://www.sfml-dev.org/files/SFML-3.0.2-windows-vc17-64-bit.zip"
Invoke-WebRequest $SFMLDownloadUrl -OutFile "$($PSScriptRoot)\SFML.zip"
Expand-Archive -Path "$($PSScriptRoot)\SFML.zip" -DestinationPath $PSScriptRoot
New-Item -Path "$($PSScriptRoot)\build" -ItemType Directory
Move-Item -Path "$($PSScriptRoot)\SFML-3.0.2\bin\sfml-graphics-3.dll" -Destination "$($PSScriptRoot)\build"
Move-Item -Path "$($PSScriptRoot)\SFML-3.0.2\bin\sfml-window-3.dll" -Destination "$($PSScriptRoot)\build"
Move-Item -Path "$($PSScriptRoot)\SFML-3.0.2\bin\sfml-audio-3.dll" -Destination "$($PSScriptRoot)\build"
Move-Item -Path "$($PSScriptRoot)\SFML-3.0.2\bin\sfml-network-3.dll" -Destination "$($PSScriptRoot)\build"
Move-Item -Path "$($PSScriptRoot)\SFML-3.0.2\bin\sfml-system-3.dll" -Destination "$($PSScriptRoot)\build"
return 0