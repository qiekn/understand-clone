make -j10 -C build
if ($lastexitcode -eq 0) {
    ./build/game
} else {
    Write-Host "Make failed"
}
