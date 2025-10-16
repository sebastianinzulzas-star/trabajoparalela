#ifndef GUARDAR_H
#define GUARDAR_H

#include <vector>
#include <string>
#include "structs.h"

// Guarda los resultados de corrección en un archivo CSV.
// Crea la carpeta destino si no existe.
void guardarResultadosCSV(const std::vector<Resultado>& resultados, const std::string& rutaArchivo);

#endif
