# Build

Build with cmake normally, eg:
```
cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Debug -GNinja
cmake --build build
```

# Run
```
build/main
```

# Unit Testing
Use regular cmake/ctest conventions
```
ctest --test-dir build
```
