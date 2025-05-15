# Genera y valida un vector de prueba
1. Abre un terminal y ejecuta lo siguiente:
   ```bash
   time dd if=/dev/random of=random_file.bin bs=1 count=4096
   ```
2. Ejecuta el validador de entropia estadístico.
   ```bash
   ./entropy_validator random_file.bin
   ```
3. Prueba de nuevo ajustando a tu gusto el tamaño de bytes, el tamaño de bloque y/o el archivo de salida.