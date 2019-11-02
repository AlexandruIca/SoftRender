#!/usr/bin/sh

cmake-format -i CMakeLists.txt
cmake-format -i src/CMakeLists.txt
cmake-format -i tests/CMakeLists.txt
cmake-format -i tests/basic_flat_shading_render/CMakeLists.txt
cmake-format -i tests/basic_wire_render/CMakeLists.txt
cmake-format -i examples/CMakeLists.txt
cmake-format -i examples/simple_snake/CMakeLists.txt
