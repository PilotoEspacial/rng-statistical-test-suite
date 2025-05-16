# Compila y ejecuta los tests unitarios
1. Asegurate estar en la raiz del proyecto.
2. Asegurate de hacer la llamada a CMake con el flag necesario.
   ```bash
   cmake -B build -S . -DBUILD_TESTS=ON ...
   ```
3. Ejecuta los tests.
   ```bash
   cmake --build build
   ctest --test-dir build/tests --output-on-failure
   ```