#pragma once
#include <string>
#include <algorithm>

// 🧹 Elimina espacios, comillas y saltos de línea
inline std::string trim(const std::string& str) {
    std::string s = str;

    // Eliminar comillas dobles
    s.erase(remove(s.begin(), s.end(), '"'), s.end());

    // Eliminar espacios al inicio
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));

    // Eliminar espacios al final
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());

    return s;
}
