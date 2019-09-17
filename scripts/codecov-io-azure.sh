for dir in src/CMakeFiles/*.dir; do
    gcov-9 $dir/*.gcno
done

for dir2 in tests/CMakeFiles/*.dir/*.gcno; do
    gcov-9 $dir2
done

for dir3 in tests/basic_wire_render/CMakeFiles/*.dir/*.gcno; do
    gcov-9 $dir3
done

bash <(curl -s https://codecov.io/bash)
