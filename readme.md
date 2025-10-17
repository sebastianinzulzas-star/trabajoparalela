Trabajo de Computación Paralela – Corrección de Pruebas PAES
Descripción

Este proyecto implementa un programa en C++ con soporte de paralelismo mediante OpenMP.
El objetivo es corregir exámenes tipo PAES a partir de archivos CSV con información de estudiantes, respuestas y claves correctas.
El sistema incluye versiones secuencial y paralela del corrector, así como herramientas de benchmarking para medir el rendimiento con distintos números de hilos.

Requisitos del sistema

Sistema operativo:

Ubuntu 22.04 o superior (recomendado Ubuntu Server 24.04)

Dependencias:

g++ versión 9 o superior

make

git

Al clonar en Ubuntu, bastará con:

git clone https://github.com/TU_USUARIO/trabajoparalela.git
cd trabajoparalela
make
./dist/programa -e data/small/estudiantes.csv -p data/small/paes.csv -c data/small/correctas.csv -r data/processed/resultados.csv




Instalación de dependencias:

sudo apt update
sudo apt install -y g++ make git

Para compilar el programa en Ubuntu, ejecute los siguientes comandos desde la raíz del proyecto:

make

Esto generará el binario compilado en la carpeta dist/ con el nombre:

dist/programa

Para limpiar los binarios generados:

make clean

Ejecución del programa

El programa se ejecuta desde la línea de comandos y recibe los siguientes argumentos:

-e : archivo CSV con los datos de los estudiantes

-p : archivo CSV con las respuestas PAES

-c : archivo CSV con las respuestas correctas

-r : archivo CSV de salida donde se guardarán los resultados

Modo de pruebas:

./dist/programa -e data/small/estudiantes.csv -p data/small/paes.csv -c data/small/correctas.csv -r data/processed/resultados.csv

Modo real:

./dist/programa -e data/raw/estudiantes.csv -p data/raw/paes.csv -c data/raw/correctas.csv -r data/processed/resultados.csv

Benchmark de rendimiento

Para medir el rendimiento del programa con distintos números de hilos, se incluye un script en Bash.

Dar permisos de ejecución al script (solo la primera vez):

chmod +x benchmarks/benchmark.sh

Ejecutar el benchmark:

./benchmarks/benchmark.sh

Esto generará un archivo CSV con los resultados:

benchmarks/times.csv

Asignar automáticamente el número de hilos:

export OMP_NUM_THREADS=$(nproc)

Verificar el número de núcleos disponibles:

nproc

Ejemplo de ejecución paralela:

export OMP_NUM_THREADS=8
./dist/programa -e data/raw/estudiantes.csv -p data/raw/paes.csv -c data/raw/correctas.csv -r data/processed/resultados.csv

Créditos

Desarrollo: Sebastián Inzulza
Universidad Tecnológica Metropolitana (UTEM)

