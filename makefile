# ==============
# Configuración
# ==============
CXX      := g++
CXXFLAGS := -std=c++17 -O3 -march=native -Wall -Wextra -fopenmp
INCLUDES := -I src/utils
SRCS     := src/main.cpp src/lector.cpp src/corrector.cpp src/paralelo.cpp src/guardar.cpp
TARGET   := dist/programa

# Windows (MSYS/MinGW) produce .exe automáticamente si TARGET termina sin extensión
# Si quieres forzarlo, descomenta:
# TARGET   := dist/programa.exe

# ==============
# Reglas
# ==============
all: $(TARGET)

$(TARGET): $(SRCS)
	@mkdir -p dist
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRCS) -o $(TARGET)

run-pruebas: $(TARGET)
	OMP_NUM_THREADS=4 ./$(TARGET) pruebas

run-reales: $(TARGET)
	OMP_NUM_THREADS=4 ./$(TARGET) reales

clean:
	rm -rf dist/*

.PHONY: all run-pruebas run-reales clean
