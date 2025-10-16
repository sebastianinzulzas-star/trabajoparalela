#pragma once
#include <vector>
#include "structs.h"

// Función paralela con OpenMP para corregir
std::vector<Resultado> corregirParalelo(
    const std::vector<Estudiante>& estudiantes,
    const std::vector<Correcta>& correctas,
    const std::vector<Respuesta>& respuestas,
    int numHilos
);
