cmake -S . -B build
cd build
make
cd ..
if [ !  -L "compile_commands.json" ]; then
    ln -s build/compile_commands.json .
    echo "Linking compile commands to project root"
fi
