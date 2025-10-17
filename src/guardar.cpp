#include "utils/guardar.h"
#include <fstream>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

void guardarResultadosCSV(const std::vector<Resultado>& resultados, const std::string& rutaArchivo) {
    try {
        // Crear carpeta destino si no existe
        fs::path ruta = rutaArchivo;
        fs::create_directories(ruta.parent_path());

        std::ofstream archivo(rutaArchivo, std::ios::out | std::ios::trunc);

        if (!archivo.is_open()) {
            throw std::runtime_error("No se pudo abrir el archivo de salida: " + rutaArchivo);
        }

        // Encabezado
        archivo << "CODIGO;PRUEBA;ACIERTOS;ERRORES;OMITIDAS;PUNTAJE\n";

        // Escribir cada resultado
        for (const auto& r : resultados) {
            archivo << r.estudiante << ";"
                    << r.prueba << ";"
                    << r.aciertos << ";"
                    << r.errores << ";"
                    << r.omitidas << ";"
                    << r.puntaje << "\n";
        }

        archivo.close();
        std::cout << "📁 Resultados guardados en: " << rutaArchivo << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << " Error al guardar resultados: " << e.what() << std::endl;
    }
}
