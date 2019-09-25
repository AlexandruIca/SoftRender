for softrender_dir in src/CMakeFiles/*.dir; do
    pushd $softrender_dir
    gcov-9 *.gcno
    popd
done

for tests_dir in tests/CMakeFiles/*.dir; do
    pushd $tests_dir
    gcov-9 *.gcno
    popd
done

for subdirs in tests/*/CMakeFiles/*.dir; do
    pushd $subdirs
    gcov-9 *.gcno
    popd
done

bash <(curl -s https://codecov.io/bash)
