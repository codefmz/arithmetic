param (
    [string]$t,
    [string]$t2
)

Write-Host "compile target : $t"
cmake -Dtarget::STRING=$t -S . -B build
cmake --build build --target $t


Write-Host "begin execute target : $t"
Write-Host "`n=============================================`n"
if ([string]::IsNullOrEmpty($t2)) {
    & bin/Debug/$t.exe
} else {
    & bin/Debug/$t.exe --gtest_filter=$t2
}