param(
    [string]$BuildType = "Release"
)

$BuildDir = "build/$BuildType"

Write-Host "Configuring ($BuildType) into $BuildDir..."
cmake -S . -B $BuildDir -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=$BuildType

Write-Host "Building..."
cmake --build $BuildDir

Write-Host "Build Complete"