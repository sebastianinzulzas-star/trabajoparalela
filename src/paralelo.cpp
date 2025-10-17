#include "utils/paralelo.h"
#include <omp.h>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <stdexcept>

std::vector<Resultado> corregirParalelo(
    const std::vector<Estudiante>& estudiantes,
    const std::vector<Respuesta>& paes,
    const std::vector<Correcta>& correctas
) {
    if (correctas.empty()) {
        throw std::runtime_error("No hay respuestas correctas cargadas.");
    }

    const auto& respuestasCorrectas = correctas[0].respuestas;
    const int totalPreguntas = static_cast<int>(respuestasCorrectas.size());

    std::unordered_map<std::string, const std::vector<std::string>*> idx;
    idx.reserve(paes.size());
    for (const auto& r : paes) {
        idx[r.estudiante] = &r.respuestas;
    }

    std::vector<Resultado> resultados(estudiantes.size());
    const int total = (int)estudiantes.size();

    std::cout << "[DEBUG] Corrección paralela iniciada con "
              << omp_get_max_threads() << " hilos...\n";

    int progreso = 0;

    #pragma omp parallel for schedule(dynamic, 512) default(none) \
        shared(estudiantes, idx, respuestasCorrectas, resultados, total, progreso) \
        firstprivate(totalPreguntas)
    for (int i = 0; i < total; ++i) {
        const auto& e = estudiantes[i];
        Resultado r;
        r.estudiante = e.codigo;
        r.prueba = "PAES";
        r.aciertos = 0;
        r.errores = 0;
        r.omitidas = totalPreguntas;
        r.puntaje = 100.0;

        auto it = idx.find(e.codigo);
        if (it != idx.end()) {
            const auto& respEst = *it->second;
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
            double aciertosAjustados = std::max(0.0, (double)aciertos - 0.25 * (double)errores);
            r.puntaje = 100.0 + (aciertosAjustados / totalPreguntas) * 900.0;
            r.aciertos = aciertos;
            r.errores = errores;
            r.omitidas = omitidas;
        }

        resultados[i] = r;

        // Actualización de progreso (solo hilo 0)
        if (omp_get_thread_num() == 0) {
            int nuevo = (i * 100) / total;
            if (nuevo > progreso) {
                progreso = nuevo;
                std::cout << "\r[PROGRESO] " << progreso << "% completado..." << std::flush;
            }
        }
    }

    std::cout << "\n✔️ Corrección paralela completada (" 
              << resultados.size() << " resultados)\n";
    return resultados;
}
