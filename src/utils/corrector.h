#pragma once
#include <vector>
#include "structs.h"

std::vector<Resultado> corregirSecuencial(
    const std::vector<Estudiante>& estudiantes,
    const std::vector<Respuesta>& paes,
    const std::vector<Correcta>& correctas
);
