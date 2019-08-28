for dir in CMakeFiles/*.dir; do
    gcov $dir/src/*.gcno
done

for dir2 in tests/CMakeFiles/Testing/*.dir; do
    gcov $dir/*.gcno
done

bash <(curl -s https://codecov.io/bash)
