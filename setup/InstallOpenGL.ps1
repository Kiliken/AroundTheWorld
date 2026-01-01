
$ProjectRoot = "$($PSScriptRoot)\.."

Write-Output "[openGL-portable-setup] $($ProjectRoot)\setup"

New-Item -Path "$($ProjectRoot)\dep" -ItemType Directory
New-Item -Path "$($ProjectRoot)\build" -ItemType Directory
New-Item -Path "$($ProjectRoot)\dep\include" -ItemType Directory
New-Item -Path "$($ProjectRoot)\dep\lib" -ItemType Directory


$sdlDownloadUrl = "https://github.com/libsdl-org/SDL/releases/download/release-3.2.28/SDL3-devel-3.2.28-mingw.zip"
$glewDownloadUrl = "https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0-win32.zip"
$glmDownloadUrl = "https://github.com/g-truc/glm/releases/download/1.0.2/glm-1.0.2.zip"
$imguiDownloadUrl = "https://github.com/ocornut/imgui/archive/refs/tags/v1.92.5.zip"

$wc = New-Object Net.WebClient
Add-Type -AssemblyName System.IO.Compression.FileSystem

# Downloads
Write-Output "[openGL-portable-setup] Downloading SDL3..."
$wc.DownloadFile($sdlDownloadUrl, "$($PSScriptRoot)\sdl.zip")
Write-Output "[openGL-portable-setup] Downloading GLEW..."
$wc.DownloadFile($glewDownloadUrl, "$($PSScriptRoot)\glew.zip")
Write-Output "[openGL-portable-setup] Downloading GLM..."
$wc.DownloadFile($glmDownloadUrl, "$($PSScriptRoot)\glm.zip")
Write-Output "[openGL-portable-setup] Downloading ImGUI..."
$wc.DownloadFile($imguiDownloadUrl, "$($PSScriptRoot)\imgui.zip")

# Extract
Write-Output "[openGL-portable-setup] Extracting SDL3..."
[System.IO.Compression.ZipFile]::ExtractToDirectory("$($PSScriptRoot)\sdl.zip", "$($PSScriptRoot)")
Write-Output "[openGL-portable-setup] Extracting GLEW..."
[System.IO.Compression.ZipFile]::ExtractToDirectory("$($PSScriptRoot)\glew.zip", "$($PSScriptRoot)")
Write-Output "[openGL-portable-setup] Extracting GLM..."
[System.IO.Compression.ZipFile]::ExtractToDirectory("$($PSScriptRoot)\glm.zip", "$($PSScriptRoot)")
Write-Output "[openGL-portable-setup] Extracting ImGUI..."
[System.IO.Compression.ZipFile]::ExtractToDirectory("$($PSScriptRoot)\imgui.zip", "$($ProjectRoot)\dep\include")



# Dependencies Setup
Copy-Item -Path "$($PSScriptRoot)\SDL3-3.2.28\x86_64-w64-mingw32\include\SDL3" -Destination "$($ProjectRoot)\dep\include" -Recurse
Copy-Item -Path "$($PSScriptRoot)\SDL3-3.2.28\x86_64-w64-mingw32\bin\SDL3.dll" -Destination "$($ProjectRoot)\build" -Force
Copy-Item -Path "$($PSScriptRoot)\SDL3-3.2.28\x86_64-w64-mingw32\lib\libSDL3.dll.a" -Destination "$($ProjectRoot)\dep\lib" -Force

Copy-Item -Path "$($PSScriptRoot)\glew-2.2.0\include\GL" -Destination "$($ProjectRoot)\dep\include" -Recurse
Copy-Item -Path "$($PSScriptRoot)\glm\glm" -Destination "$($ProjectRoot)\dep\include" -Recurse

Rename-Item -Path "$($ProjectRoot)\dep\include\imgui-1.92.5" -NewName "imgui"
Copy-Item -Path "$($ProjectRoot)\dep\include\imgui\backends\imgui_impl_opengl3.cpp" -Destination "$($ProjectRoot)\dep\include\imgui"
Copy-Item -Path "$($ProjectRoot)\dep\include\imgui\backends\imgui_impl_opengl3.h" -Destination "$($ProjectRoot)\dep\include\imgui"
Copy-Item -Path "$($ProjectRoot)\dep\include\imgui\backends\imgui_impl_opengl3_loader.h" -Destination "$($ProjectRoot)\dep\include\imgui"
Copy-Item -Path "$($ProjectRoot)\dep\include\imgui\backends\imgui_impl_sdl3.cpp" -Destination "$($ProjectRoot)\dep\include\imgui"
Copy-Item -Path "$($ProjectRoot)\dep\include\imgui\backends\imgui_impl_sdl3.h" -Destination "$($ProjectRoot)\dep\include\imgui"

Copy-Item -Path "$($PSScriptRoot)\GenerateLibs.bat" -Destination "$($PSScriptRoot)\glew-2.2.0\bin\Release\x64" -Force
Push-Location "$($PSScriptRoot)\glew-2.2.0\bin\Release\x64"
& ".\GenerateLibs.bat"
Pop-Location

# Clean Dependencies
Remove-Item -Path "$($PSScriptRoot)\SDL3-3.2.28" -Recurse -Force
Remove-Item -Path "$($PSScriptRoot)\glew-2.2.0" -Recurse -Force
Remove-Item -Path "$($PSScriptRoot)\glm" -Recurse -Force

return 0
