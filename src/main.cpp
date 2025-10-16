#include <iostream>
#include <string>
#include <vector>

#include "utils/structs.h"
#include "utils/lector.h"
#include "utils/corrector.h"
#include "utils/guardar.h"

void mostrarUso(const std::string& exe) {
    std::cout << "Uso: " << exe << " [pruebas|reales]\n";
    std::cout << "  pruebas -> lee CSV de data/small/\n";
    std::cout << "  reales  -> lee CSV de data/raw/\n";
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        mostrarUso(argv[0]);
        return 1;
    }

    std::string tipo = argv[1];
    std::string rutaEstudiantes, rutaCorrectas, rutaPAES;

    if (tipo == "pruebas") {
        rutaEstudiantes = "data/small/estudiantes_small.csv";
        rutaCorrectas   = "data/small/correctas_small.csv";
        rutaPAES        = "data/small/paes_small.csv";
    } else if (tipo == "reales") {
        rutaEstudiantes = "data/raw/estudiantes.csv";
        rutaCorrectas   = "data/raw/correctas.csv";
        rutaPAES        = "data/raw/paes.csv";
    } else {
        mostrarUso(argv[0]);
        return 1;
    }

    try {
        // Leer archivos
        auto estudiantes = leerEstudiantes(rutaEstudiantes);
        auto correctas   = leerCorrectas(rutaCorrectas);
        auto paes        = leerPAES(rutaPAES);

        std::cout << "✅ Estudiantes leidos: " << estudiantes.size() << "\n";
        std::cout << "✅ Correctas leidas:   " << correctas.size() << "\n";
        std::cout << "✅ PAES leídas:        " << paes.size() << "\n";

        // Corregir secuencialmente
        auto resultados = corregirSecuencial(estudiantes, paes, correctas);
        std::cout << "✅ Correccion completada (" << resultados.size() << " resultados generados)\n";

        // 📁 Guardar resultados
        std::string rutaSalida = (tipo == "pruebas")
            ? "data/processed/resultados_small.csv"
            : "data/processed/resultados.csv";

        guardarResultadosCSV(resultados, rutaSalida);

    } catch (const std::exception& e) {
        std::cerr << "❌ Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
