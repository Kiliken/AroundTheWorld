
New-Item -Path "$($PSScriptRoot)\dep" -ItemType Directory
New-Item -Path "$($PSScriptRoot)\build" -ItemType Directory
New-Item -Path "$($PSScriptRoot)\dep\include" -ItemType Directory
New-Item -Path "$($PSScriptRoot)\dep\lib" -ItemType Directory

$glewDownloadUrl = "https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0-win32.zip"
$glmDownloadUrl = "https://github.com/g-truc/glm/releases/download/1.0.2/glm-1.0.2.zip"
$imguiDownloadUrl = "https://github.com/ocornut/imgui/archive/refs/tags/v1.92.5.zip"
$sdlDownloadUrl = "https://github.com/libsdl-org/SDL/releases/download/release-3.2.28/SDL3-devel-3.2.28-mingw.zip"

$wc = New-Object Net.WebClient
Add-Type -AssemblyName System.IO.Compression.FileSystem

# Downloads
Write-Output "[openGL-portable-setup] Downloading GLEW..."
$wc.DownloadFile($glewDownloadUrl, "$($PSScriptRoot)\dep\glew.zip")
Write-Output "[openGL-portable-setup] Downloading GLM..."
$wc.DownloadFile($glmDownloadUrl, "$($PSScriptRoot)\dep\glm.zip")
Write-Output "[openGL-portable-setup] Downloading ImGUI..."
$wc.DownloadFile($imguiDownloadUrl, "$($PSScriptRoot)\dep\imgui.zip")
Write-Output "[openGL-portable-setup] Downloading SDL3..."
$wc.DownloadFile($sdlDownloadUrl, "$($PSScriptRoot)\dep\sdl.zip")

# Extract
Write-Output "[openGL-portable-setup] Extracting GLEW..."
[System.IO.Compression.ZipFile]::ExtractToDirectory("$($PSScriptRoot)\dep\glew.zip", "$($PSScriptRoot)\dep\")
Write-Output "[openGL-portable-setup] Extracting GLM..."
[System.IO.Compression.ZipFile]::ExtractToDirectory("$($PSScriptRoot)\dep\glm.zip", "$($PSScriptRoot)\dep\glm")
Write-Output "[openGL-portable-setup] Extracting ImGUI..."
[System.IO.Compression.ZipFile]::ExtractToDirectory("$($PSScriptRoot)\dep\imgui.zip", "$($PSScriptRoot)\dep\include")
Write-Output "[openGL-portable-setup] Extracting SDL3..."
[System.IO.Compression.ZipFile]::ExtractToDirectory("$($PSScriptRoot)\dep\sdl.zip", "$($PSScriptRoot)\dep\")

# Dependencies Setup
Copy-Item -Path "$($PSScriptRoot)\dep\glew-2.2.0\include\GL" -Destination "$($PSScriptRoot)\dep\include" -Recurse
Copy-Item -Path "$($PSScriptRoot)\dep\glm\glm" -Destination "$($PSScriptRoot)\dep\include" -Recurse

Copy-Item -Path "$($PSScriptRoot)\dep\SDL3-3.2.28\x86_64-w64-mingw32\include\SDL3" -Destination "$($PSScriptRoot)\dep\include" -Recurse
Copy-Item -Path "$($PSScriptRoot)\dep\SDL3-3.2.28\x86_64-w64-mingw32\bin\SDL3.dll" -Destination "$($PSScriptRoot)\build" -Force
Copy-Item -Path "$($PSScriptRoot)\dep\SDL3-3.2.28\x86_64-w64-mingw32\lib\libSDL3.dll.a" -Destination "$($PSScriptRoot)\dep\lib" -Force

Rename-Item -Path "$($PSScriptRoot)\dep\include\imgui-1.92.5" -NewName "imgui"
Copy-Item -Path "$($PSScriptRoot)\dep\include\imgui\backends\imgui_impl_opengl3.cpp" -Destination "$($PSScriptRoot)\dep\include\imgui"
Copy-Item -Path "$($PSScriptRoot)\dep\include\imgui\backends\imgui_impl_opengl3.h" -Destination "$($PSScriptRoot)\dep\include\imgui"
Copy-Item -Path "$($PSScriptRoot)\dep\include\imgui\backends\imgui_impl_opengl3_loader.h" -Destination "$($PSScriptRoot)\dep\include\imgui"
Copy-Item -Path "$($PSScriptRoot)\dep\include\imgui\backends\imgui_impl_sdl3.cpp" -Destination "$($PSScriptRoot)\dep\include\imgui"
Copy-Item -Path "$($PSScriptRoot)\dep\include\imgui\backends\imgui_impl_sdl3.h" -Destination "$($PSScriptRoot)\dep\include\imgui"


Copy-Item -Path "$($PSScriptRoot)\GenerateLibs.bat" -Destination "$($PSScriptRoot)\dep\glew-2.2.0\bin\Release\x64" -Force
Push-Location "$($PSScriptRoot)\dep\glew-2.2.0\bin\Release\x64"
& ".\GenerateLibs.bat"
Pop-Location

# Clean Dependencies
Remove-Item -Path "$($PSScriptRoot)\dep\glew-2.2.0" -Recurse -Force
Remove-Item -Path "$($PSScriptRoot)\dep\glm" -Recurse -Force
Remove-Item -Path "$($PSScriptRoot)\dep\SDL3-3.2.28" -Recurse -Force

return 0
