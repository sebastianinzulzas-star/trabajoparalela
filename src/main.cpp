#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <filesystem>
#include <clocale>

#include "utils/structs.h"
#include "utils/lector.h"
#include "utils/corrector.h"
#include "utils/paralelo.h"
#include "utils/guardar.h"

using namespace std;
using namespace std::chrono;
namespace fs = std::filesystem;

void mostrarUso(const string& exe) {
    cout << "Uso: " << exe << " -e <estudiantes.csv> -p <paes.csv> -c <correctas.csv> -r <resultados.csv>\n";
    cout << "Ejemplo:\n  " << exe << " -e data/raw/estudiantes.csv -p data/raw/paes.csv -c data/raw/correctas.csv -r data/processed/resultados.csv\n";
}

void mostrarCabecera() {
    cout << "=== Trabajo Computacion Paralela ./dist/programa GRUPO 0 ===\n";
    cout << "Integrante A: Sebastian Inzulza\n";
    cout << "===============================================\n\n";
}

void detectarDataset(const string& rutaEstudiantes) {
    try {
        auto size = fs::file_size(rutaEstudiantes);
        if (size < 50'000) {
            cout << "[INFO] Usando dataset de PRUEBAS (" << size << " bytes)\n";
        } else {
            cout << "[INFO] Usando dataset REAL (" << size << " bytes)\n";
        }
    } catch (...) {
        cout << "[WARN] No se pudo determinar el tamaño del dataset.\n";
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    std::setlocale(LC_ALL, "C");

    mostrarCabecera();

    if (argc != 9) {
        mostrarUso(argv[0]);
        return 1;
    }

    string rutaEstudiantes, rutaPAES, rutaCorrectas, rutaSalida;

    for (int i = 1; i < argc; i += 2) {
        string flag = argv[i];
        string valor = argv[i + 1];

        if (flag == "-e") rutaEstudiantes = valor;
        else if (flag == "-p") rutaPAES = valor;
        else if (flag == "-c") rutaCorrectas = valor;
        else if (flag == "-r") rutaSalida = valor;
        else {
            cerr << "[ERROR] Opcion no reconocida: " << flag << "\n";
            mostrarUso(argv[0]);
            return 1;
        }
    }

    try {
        detectarDataset(rutaEstudiantes);

        auto estudiantes = leerEstudiantes(rutaEstudiantes);
        auto correctas   = leerCorrectas(rutaCorrectas);
        auto paes        = leerPAES(rutaPAES);

        cout << "Estudiantes leidos: " << estudiantes.size() << "\n";
        cout << "Correctas leidas:   " << correctas.size() << "\n";
        cout << "PAES leidas:        " << paes.size() << "\n\n";

        auto t1 = high_resolution_clock::now();
        auto resultados = corregirSecuencial(estudiantes, paes, correctas);
        auto t2 = high_resolution_clock::now();
        auto tiempoSec = duration_cast<milliseconds>(t2 - t1).count();

        guardarResultadosCSV(resultados, rutaSalida);
        cout << "[TIME] Secuencial: " << tiempoSec << " ms\n\n";

        auto t3 = high_resolution_clock::now();
        auto resultadosParalelo = corregirParalelo(estudiantes, paes, correctas);
        auto t4 = high_resolution_clock::now();
        auto tiempoPar = duration_cast<milliseconds>(t4 - t3).count();

        string rutaParalelo = rutaSalida.substr(0, rutaSalida.find_last_of('.')) + "_paralelo.csv";
        guardarResultadosCSV(resultadosParalelo, rutaParalelo);
        cout << "[TIME] Paralelo:   " << tiempoPar << " ms\n\n";

        cout << "[OK] Ejecucion completada correctamente.\n";
        return 0;
    }
    catch (const exception& e) {
        cerr << "[FATAL] Error: " << e.what() << "\n";
        return 1;
    }
}
