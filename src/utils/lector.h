#pragma once
#include <vector>
#include <string>
#include "structs.h"

std::vector<Estudiante> leerEstudiantes(const std::string& rutaArchivo);
std::vector<Correcta> leerCorrectas(const std::string& rutaArchivo);
std::vector<Respuesta> leerPAES(const std::string& rutaArchivo);
