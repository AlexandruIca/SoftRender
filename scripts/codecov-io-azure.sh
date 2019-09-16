for dir in src/CMakeFiles/*.dir; do
    gcov-9 $dir/src/*.gcno
done

for dir2 in tests/CMakeFiles/*.dir/*.gcno; do
    gcov-9 $dir2
done

bash <(curl -s https://codecov.io/bash)
