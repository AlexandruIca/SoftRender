pushd ${HOME}/vcpkg
git init
git remote add origin "https://github.com/Microsoft/vcpkg.git"
git fetch origin master
git checkout -b master origin/master
./bootstrap-vcpkg.sh
./vcpkg install sdl2
popd
