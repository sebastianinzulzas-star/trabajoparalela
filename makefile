# Compilar el programa
all:
	g++ src/main.cpp -o dist/hola_mundo

# Limpiar archivos compilados
clean:
	rm -rf dist/*
