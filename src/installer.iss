;----------------------------------------
; Instalador para Stagex (v1.J.0)
;----------------------------------------

[Setup]
AppName=Stagex
AppVersion=1.0
DefaultDirName={pf}\Stagex
DefaultGroupName=Stagex
OutputBaseFilename=Stagex_Installer
SetupIconFile=C:\Users\Bau_M\OneDrive\Desktop\Juegos\Stagex\v1.J.0\icon.ico
Compression=lzma
SolidCompression=yes
DisableProgramGroupPage=yes

[Languages]
Name: "spanish"; MessagesFile: "compiler:Languages\Spanish.isl"

[Files]
; Ejecutable
Source: "C:\Users\Bau_M\OneDrive\Desktop\Juegos\Stagex\v1.J.0\Stagex.exe"; DestDir: "{app}"; Flags: ignoreversion
; DLLs de SFML
Source: "C:\Users\Bau_M\OneDrive\Desktop\Juegos\Stagex\v1.J.0\sfml-graphics-2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Bau_M\OneDrive\Desktop\Juegos\Stagex\v1.J.0\sfml-window-2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Bau_M\OneDrive\Desktop\Juegos\Stagex\v1.J.0\sfml-system-2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Bau_M\OneDrive\Desktop\Juegos\Stagex\v1.J.0\sfml-audio-2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Bau_M\OneDrive\Desktop\Juegos\Stagex\v1.J.0\openal32.dll"; DestDir: "{app}"; Flags: ignoreversion
; Carpeta de assets (sprites y sounds)
Source: "C:\Users\Bau_M\OneDrive\Desktop\Juegos\Stagex\v1.J.0\src\*"; DestDir: "{app}\src"; Flags: recursesubdirs ignoreversion

[Icons]
Name: "{userdesktop}\Stagex"; Filename: "{app}\Stagex.exe"; IconFilename: "C:\Users\Bau_M\OneDrive\Desktop\Juegos\Stagex\v1.J.0\icon.ico"

[Run]
Filename: "{app}\Stagex.exe"; Description: "Ejecutar Stagex"; Flags: nowait postinstall skipifsilent
