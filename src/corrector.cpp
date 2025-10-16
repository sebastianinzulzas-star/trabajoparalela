#include "utils/corrector.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>  // std::find_if, std::max
#include <cmath>      // operaciones matemáticas

std::vector<Resultado> corregirSecuencial(
    const std::vector<Estudiante>& estudiantes,
    const std::vector<Respuesta>& paes,
    const std::vector<Correcta>& correctas
) {
    std::vector<Resultado> resultados;
    resultados.reserve(estudiantes.size());

    if (correctas.empty()) {
        throw std::runtime_error("No hay respuestas correctas cargadas.");
    }

    // Tomamos la primera fila (la única en correctas.csv)
    const auto& respuestasCorrectas = correctas[0].respuestas;
    const int totalPreguntas = static_cast<int>(respuestasCorrectas.size());

    std::cout << "[DEBUG] Correccion secuencial iniciada..." << std::endl;

    // ────────────────────────────────────────────────
    //   Recorrer cada estudiante
    // ────────────────────────────────────────────────
    for (const auto& e : estudiantes) {
        // Buscar sus respuestas en PAES
        auto it = std::find_if(paes.begin(), paes.end(),
            [&](const Respuesta& r) { return r.estudiante == e.codigo; });

        Resultado r;
        r.estudiante = e.codigo;
        r.prueba = "PAES";
        r.aciertos = 0;
        r.errores = 0;
        r.omitidas = totalPreguntas;
        r.puntaje = 100.0; // Base

        // Si no hay respuestas para este estudiante
        if (it == paes.end()) {
            resultados.push_back(r);
            continue;
        }

        const auto& respEst = it->respuestas;
        int aciertos = 0, errores = 0, omitidas = 0;

        // ────────────────────────────────────────────────
        //   Comparar pregunta por pregunta
        // ────────────────────────────────────────────────
        for (int i = 0; i < totalPreguntas && i < static_cast<int>(respEst.size()); ++i) {
            std::string respuesta = respEst[i];
            std::string correcta = respuestasCorrectas[i];

            if (respuesta.empty()) {
                omitidas++;
            } else if (respuesta == correcta) {
                aciertos++;
            } else {
                errores++;
            }
        }

        // Penalización por errores y cálculo de puntaje final
        double aciertosAjustados = std::max(0.0, static_cast<double>(aciertos) - 0.25 * errores);
        double puntaje = 100.0 + (aciertosAjustados / totalPreguntas) * 900.0;

        // Registrar el resultado
        r.aciertos = aciertos;
        r.errores = errores;
        r.omitidas = omitidas;
        r.puntaje = puntaje;

        resultados.push_back(r);
    }

    std::cout << "✔️ Correccion completada (" << resultados.size() << " resultados generados)\n";
    return resultados;
}
