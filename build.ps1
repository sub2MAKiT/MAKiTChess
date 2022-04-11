param (
    [switch]$DEBUG = $false,
    [switch]$open = $false,
    [switch]$fast = $false
)
if ($DEBUG) {
    $DEBUGS = "-DDEBUGCHESS"
} else {
    $DEBUGS = ""
}
g++  $DEBUGS $((Get-ChildItem -Filter *.cpp -Recurse).FullName) -o ./build/main -I C:\sdk\include -fpermissive -L C:\sdk\lib -luser32 -lgdi32 -lopengl32 -lgdiplus -lShlwapi -ldwmapi -lstdc++fs -static -std=c++17 $(If ($fast) {"-Ofast"} Else {""})
if($open)
{
    .\build\main.exe 
}