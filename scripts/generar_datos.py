import csv
import random
import os

# 📂 Directorio de salida
OUTPUT_DIR = "data/small"
os.makedirs(OUTPUT_DIR, exist_ok=True)

# Rutas de archivo con nombres fijos (para pruebas)
estudiantes_path = os.path.join(OUTPUT_DIR, "estudiantes_small.csv")
paes_path       = os.path.join(OUTPUT_DIR, "paes_small.csv")
correctas_path  = os.path.join(OUTPUT_DIR, "correctas_small.csv")

# 1️⃣ CSV de estudiantes
with open(estudiantes_path, "w", newline="", encoding="utf-8") as f:
    writer = csv.writer(f, delimiter=';')
    writer.writerow([
        "CÓDIGO", "GÉNERO", "FECHA DE NACIMIENTO",
        "NOMBRES", "APELLIDOS", "REGION GEOGRÁFICA", "PROMEDIO DE NOTAS"
    ])
    for i in range(100):
        writer.writerow([
            f"STU{i:04d}",
            random.choice(["MASCULINO", "FEMENINO"]),
            f"200{i%10+2000}-0{(i%9)+1}-1{(i%9)}",
            f"Nombre{i}",
            f"Apellido{i}",
            random.choice(["NORTE", "CENTRO", "SUR", "ORIENTE", "PONIENTE"]),
            round(random.uniform(4.0, 7.0), 7)
        ])

# 2️⃣ CSV de respuestas correctas
with open(correctas_path, "w", newline="", encoding="utf-8") as f:
    writer = csv.writer(f, delimiter=';')
    preguntas = [f"PREGUNTA {i:03d}" for i in range(1, 101)]
    writer.writerow(["PRUEBA"] + preguntas)
    writer.writerow(["PAES"] + [random.choice(["A", "B", "C", "D"]) for _ in range(100)])

# 3️⃣ CSV de respuestas de estudiantes
with open(paes_path, "w", newline="", encoding="utf-8") as f:
    writer = csv.writer(f, delimiter=';')
    writer.writerow(["ESTUDIANTE", "PRUEBA"] + preguntas)
    for i in range(100):
        writer.writerow([f"STU{i:04d}", "PAES"] + [random.choice(["A", "B", "C", "D"]) for _ in range(100)])

print("✅ Archivos de prueba generados correctamente en:", OUTPUT_DIR)
print(" -", estudiantes_path)
print(" -", correctas_path)
print(" -", paes_path)
