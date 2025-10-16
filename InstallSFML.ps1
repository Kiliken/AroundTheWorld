
$BuildProj = $Args[1]
$SfmlVersion = $Args[2]

$SfmlDownloadUrl = "https://www.sfml-dev.org/files/SFML-$SfmlVersion-windows-vc17-64-bit.zip"

$wc = New-Object Net.WebClient
Add-Type -AssemblyName System.IO.Compression.FileSystem

Write-Output "[sfml-vsbt-setup] Downloading SFML-$SfmlVersion-windows-vc17-64-bit..."
$wc.DownloadFile($SfmlDownloadUrl, "$($PSScriptRoot)\SFML.zip")

Write-Output "[sfml-vsbt-setup] Extracting SFML-$SfmlVersion-windows-vc17-64-bit..."
[System.IO.Compression.ZipFile]::ExtractToDirectory("$($PSScriptRoot)\SFML.zip", $PSScriptRoot)

if ($BuildProj -eq 1) {
	Write-Output "[openSiv-vsbt-setup] No avible project detected"
	Write-Output "[openSiv-vsbt-setup] Setting up template..."
	
	New-Item -Path "$($PSScriptRoot)\build" -ItemType Directory
	Move-Item -Path "$($PSScriptRoot)\SFML-$SfmlVersion\bin\sfml-graphics-3.dll" -Destination "$($PSScriptRoot)\build"
	Move-Item -Path "$($PSScriptRoot)\SFML-$SfmlVersion\bin\sfml-window-3.dll" -Destination "$($PSScriptRoot)\build"
	Move-Item -Path "$($PSScriptRoot)\SFML-$SfmlVersion\bin\sfml-audio-3.dll" -Destination "$($PSScriptRoot)\build"
	Move-Item -Path "$($PSScriptRoot)\SFML-$SfmlVersion\bin\sfml-network-3.dll" -Destination "$($PSScriptRoot)\build"
	Move-Item -Path "$($PSScriptRoot)\SFML-$SfmlVersion\bin\sfml-system-3.dll" -Destination "$($PSScriptRoot)\build"
	
	Add-Content -Path "$($PSScriptRoot)\.gitignore" -Value "/[Ss]FML-$SfmlVersion/"
	(Get-Content -Path "$($PSScriptRoot)\BuildGame.bat") -replace 'xVersioNx', $SfmlVersion | Set-Content -Path "$($PSScriptRoot)\BuildGame.bat"

	
}

<#
Template Download:
	https://siv3d.jp/downloads/Siv3D/manual/0.6.6/OpenSiv3D_0.6.6.zip
#>
return 0
