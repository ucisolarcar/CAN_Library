### Requirements
- Linux (or WSL https://code.visualstudio.com/docs/remote/wsl)
- cmake
- make

### Installation
- clone this repo
- then run
``` bash
    git submodule update --init --recursive
```

### Build
- run this script to compile the library and the test files
- this will generate the executable
``` bash
    ./build.sh
```

### Clean
- deletes all build files
``` bash
    ./clean.sh
```

### Testing 
- write tests in the test_main.cpp file
- build the program using the build script
``` bash
    ./test.sh
```
