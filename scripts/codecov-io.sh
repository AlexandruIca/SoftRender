for dir in CMakeFiles/*.dir; do
    gcov-8 $dir/src/*.gcno
done

for dir2 in tests/CMakeFiles/*.dir/*.gcno; do
    gcov-8 $dir2
done

bash <(curl -s https://codecov.io/bash)
