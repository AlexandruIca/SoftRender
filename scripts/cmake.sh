cmake -DCMAKE_BUILD_TYPE=${BUILD_MODE}\
    -DSOFTRENDER_BUILD_TESTS=ON\
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON\
    -DCMAKE_TOOLCHAIN_FILE=${HOME}/vcpkg/scripts/buildsystems/vcpkg.cmake ..

mv compile_commands.json ..
