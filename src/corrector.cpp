#include "utils/corrector.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include <cmath>

std::vector<Resultado> corregirSecuencial(
    const std::vector<Estudiante>& estudiantes,
    const std::vector<Respuesta>& paes,
    const std::vector<Correcta>& correctas
) {
    if (correctas.empty()) {
        throw std::runtime_error("No hay respuestas correctas cargadas.");
    }

    const auto& respuestasCorrectas = correctas[0].respuestas;
    const int totalPreguntas = static_cast<int>(respuestasCorrectas.size());

    std::vector<Resultado> resultados;
    resultados.reserve(estudiantes.size());

    const size_t batchSize = 10000;
    std::cout << "[DEBUG] Corrección secuencial iniciada..." << std::endl;

    for (size_t start = 0; start < estudiantes.size(); start += batchSize) {
        size_t end = std::min(start + batchSize, estudiantes.size());

        for (size_t i = start; i < end; ++i) {
            const auto& e = estudiantes[i];
            Resultado r;
            r.estudiante = e.codigo;
            r.prueba = "PAES";
            r.aciertos = 0;
            r.errores = 0;
            r.omitidas = totalPreguntas;
            r.puntaje = 100.0;

            // Buscar respuestas
            auto it = std::find_if(paes.begin(), paes.end(),
                [&](const Respuesta& rta) { return rta.estudiante == e.codigo; });

            if (it != paes.end()) {
                const auto& respEst = it->respuestas;
                int aciertos = 0, errores = 0, omitidas = 0;
                int limite = std::min((int)respEst.size(), totalPreguntas);

                for (int j = 0; j < limite; ++j) {
                    const auto& resp = respEst[j];
                    const auto& corr = respuestasCorrectas[j];
                    if (resp.empty()) omitidas++;
                    else if (resp == corr) aciertos++;
                    else errores++;
                }

                omitidas += (totalPreguntas - limite);
                double aciertosAjustados = std::max(0.0, (double)aciertos - 0.25 * errores);
                r.puntaje = 100.0 + (aciertosAjustados / totalPreguntas) * 900.0;
                r.aciertos = aciertos;
                r.errores = errores;
                r.omitidas = omitidas;
            }
            resultados.push_back(r);
        }

        double progress = 100.0 * end / estudiantes.size();
        std::cout << "\r[PROGRESO] " << std::fixed << std::setprecision(1)
                  << progress << "% completado..." << std::flush;
    }

    std::cout << "\n✔️ Corrección secuencial completada (" 
              << resultados.size() << " resultados)" << std::endl;
    return resultados;
}
