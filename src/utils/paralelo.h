#pragma once
#include <vector>
#include "structs.h"

// Corrección paralela con OpenMP (determinista y sin carreras).
std::vector<Resultado> corregirParalelo(
    const std::vector<Estudiante>& estudiantes,
    const std::vector<Respuesta>& paes,
    const std::vector<Correcta>& correctas
);
