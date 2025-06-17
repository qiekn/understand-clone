make -j10 -C build-win
if ($lastexitcode -eq 0) {
    ./build-win/game
} else {
    Write-Host "Make failed"
}
