setlocal
rmdir /s /q build
mkdir build
cd build
git clone https://github.com/Microsoft/vcpkg.git
call .\vcpkg\bootstrap-vcpkg.bat

reg Query "HKLM\Hardware\Description\System\CentralProcessor\0" | find /i "x86" > NUL && set OS=32BIT || set OS=64BIT

set target_triplet=x86-windows-static
if %OS%==64BIT set target_triplet=x64-windows-static

.\vcpkg\vcpkg install box2d glfw3 --triplet=%target_triplet%
cmake -B . -S .. -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake -DBUILDING_WITH_AUTO_SCRIPT=True -DVCPKG_APPLOCAL_DEPS=True -DVCPKG_TARGET_TRIPLET=%target_triplet%