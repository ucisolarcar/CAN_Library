### Requirements
- Linux (or WSL https://code.visualstudio.com/docs/remote/wsl)
- cmake
- make

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

### TODO
- [x] write CMake file
- [x] make build, clean, test scripts
- [x] create files for new classes
- [x] LV sensors
- [x] mppt
- [ ] mcu
- [ ] bms 
- [ ] faults
- [ ] final verification
- [ ] compile on arduino
- [ ] figure out python integration
- [ ] integrate into each platform
