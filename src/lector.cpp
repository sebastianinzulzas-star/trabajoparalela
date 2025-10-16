#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>

#include "utils/structs.h"
#include "utils/helpers.h"

//
// ────────────────────────────────────────────────
//   FUNCIONES DE LECTURA DE ARCHIVOS CSV
// ────────────────────────────────────────────────
//

// ────────────────────────────────────────────────
// Lectura de estudiantes.csv
// ────────────────────────────────────────────────
std::vector<Estudiante> leerEstudiantes(const std::string& rutaArchivo) {
    std::vector<Estudiante> estudiantes;
    std::ifstream archivo(rutaArchivo);

    if (!archivo.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo: " + rutaArchivo);
    }

    std::string linea;
    std::getline(archivo, linea); // Ignorar encabezado

    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue;

        std::stringstream ss(linea);
        std::string campo;
        Estudiante e;

        std::getline(ss, e.codigo, ';');
        std::getline(ss, e.genero, ';');
        std::getline(ss, e.fechaNacimiento, ';');
        std::getline(ss, e.nombres, ';');
        std::getline(ss, e.apellidos, ';');
        std::getline(ss, e.region, ';');
        std::getline(ss, campo, ';');

        // Limpieza y conversión
        e.codigo = trim(e.codigo);
        e.genero = trim(e.genero);
        e.fechaNacimiento = trim(e.fechaNacimiento);
        e.nombres = trim(e.nombres);
        e.apellidos = trim(e.apellidos);
        e.region = trim(e.region);
        campo = trim(campo);

        try {
            e.promedioNotas = std::stod(campo);
        } catch (...) {
            e.promedioNotas = 0.0;
        }

        estudiantes.push_back(e);
    }

    return estudiantes;
}

// ────────────────────────────────────────────────
// Lectura de correctas.csv
// ────────────────────────────────────────────────
std::vector<Correcta> leerCorrectas(const std::string& rutaArchivo) {
    std::vector<Correcta> correctas;
    std::ifstream archivo(rutaArchivo);

    if (!archivo.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo: " + rutaArchivo);
    }

    std::string linea;
    std::getline(archivo, linea); // Ignorar encabezado

    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue;

        std::stringstream ss(linea);
        std::string campo;
        Correcta c;

        std::getline(ss, c.prueba, ';');

        while (std::getline(ss, campo, ';')) {
            c.respuestas.push_back(trim(campo));
        }

        correctas.push_back(c);
    }

    return correctas;
}

// ────────────────────────────────────────────────
// Lectura de paes.csv (respuestas de estudiantes)
// ────────────────────────────────────────────────
std::vector<Respuesta> leerPAES(const std::string& rutaArchivo) {
    std::vector<Respuesta> paes;
    std::ifstream archivo(rutaArchivo);

    if (!archivo.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo: " + rutaArchivo);
    }

    std::string linea;
    std::getline(archivo, linea); // Ignorar encabezado

    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue;

        std::stringstream ss(linea);
        std::string campo;
        Respuesta r;

        std::getline(ss, r.estudiante, ';');
        std::getline(ss, r.prueba, ';');

        while (std::getline(ss, campo, ';')) {
            r.respuestas.push_back(trim(campo));
        }

        paes.push_back(r);
    }

    return paes;
}
