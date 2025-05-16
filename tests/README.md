# Compile and run the unit tests
1. Ensure that you are in the root directory of the project.
2. Make sure you use the correct flag when calling CMake.
   ```bash
   cmake -B build -S . -DBUILD_TESTS=ON ...
   ```
3. Run unit tests.
   ```bash
   cmake --build build
   ctest --test-dir build/tests --output-on-failure
   ```