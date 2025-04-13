cmake -S . -B build
cd build
make
ln -s compile_commands.json ../
cd ..
