for dir in src/CMakeFiles/*.dir; do
    pushd $dir
    gcov-9 *.gcno
    popd
done

for dir2 in tests/CMakeFiles/*.dir; do
    pushd $dir2
    gcov-9 *.gcno
    popd
done

for dir3 in tests/basic_wire_render/CMakeFiles/*.dir; do
    pushd $dir3
    gcov-9 *.gcno
    popd
done

bash <(curl -s https://codecov.io/bash)
