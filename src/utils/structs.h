#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>
#include <vector>

// ────────────────────────────────────────────────
// Estructura para los datos de los estudiantes
// ────────────────────────────────────────────────
struct Estudiante {
    std::string codigo;
    std::string genero;
    std::string fechaNacimiento;
    std::string nombres;
    std::string apellidos;
    std::string region;
    double promedioNotas;
};

// ────────────────────────────────────────────────
// Estructura para las respuestas correctas
// ────────────────────────────────────────────────
struct Correcta {
    std::string prueba;
    std::vector<std::string> respuestas;
};

// ────────────────────────────────────────────────
// Estructura para las respuestas de los estudiantes
// ────────────────────────────────────────────────
struct Respuesta {
    std::string estudiante;
    std::string prueba;
    std::vector<std::string> respuestas;
};

// ────────────────────────────────────────────────
// Estructura para el resultado de la corrección
// ────────────────────────────────────────────────
struct Resultado {
    std::string estudiante;
    std::string prueba;
    int aciertos = 0;
    int errores = 0;
    int omitidas = 0;
    double puntaje = 0.0;
};

#endif
