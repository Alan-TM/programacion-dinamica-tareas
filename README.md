# 🎮 Tic Tac Toe (C++)

Proyecto universitario del clásico juego **Tic Tac Toe (Tres en Raya)** implementado en **C++**.  
El programa permite jugar entre **dos usuarios** o contra la **CPU (IA basada en Minimax)**.  
Incluye validación de jugadas, detección de ganador o empate, y un menú interactivo.

---

## 📘 Descripción del Proyecto

Este programa fue desarrollado como parte de una práctica universitaria para aplicar los siguientes conceptos:

- Arreglos (matrices bidimensionales) para representar el tablero.
- Funciones para modularizar el código.
- Estructuras de control (`if`, `while`, `for`, `switch`).
- Validación de entradas y control de flujo del juego.
- Detección correcta de ganadores y empates.
- Implementación opcional de inteligencia artificial con el algoritmo **Minimax**.

---

## 🧩 Funcionalidades Principales

✅ Juego entre dos jugadores (modo local).  
🤖 Modo opcional “Jugador vs CPU” con IA Minimax.  
🚫 Validación de movimientos (no se permiten jugadas inválidas).  
🏆 Detección de ganador o empate.  
🔁 Posibilidad de reiniciar el juego sin cerrar el programa.  
🧱 Menú principal interactivo.  
🧠 Código modular, legible y comentado.

---

## 🧱 Estructura del Código

El programa principal (`tictactoe.cpp`) está dividido en módulos funcionales:

| Función | Descripción |
|----------|-------------|
| `initBoard()` | Inicializa el tablero con espacios vacíos. |
| `printBoard()` | Muestra el tablero con formato legible. |
| `makeMove()` | Intenta colocar un símbolo validando que la celda esté libre. |
| `checkWinner()` | Verifica si existe un ganador, empate o si el juego continúa. |
| `playerTurn()` | Gestiona el turno de un jugador humano. |
| `gameLoopTwoPlayers()` | Controla el flujo del juego entre dos jugadores. |
| `gameLoopVsCPU()` | Controla el flujo del juego entre el jugador y la IA. |
| `minimax()` | Implementa el algoritmo Minimax para la IA. |
| `findBestMove()` | Determina la mejor jugada posible para la CPU. |
| `showMenu()` | Muestra el menú principal de opciones. |

---

## ⚙️ Requisitos del Sistema

- Compilador compatible con **C++11 o superior**.
- Sistemas operativos compatibles:
  - Windows
  - Linux
  - macOS
- Terminal o consola para ejecutar el programa.

---

## 🚀 Instrucciones de Compilación y Ejecución

### 🔧 Compilación

Usa `g++` (o cualquier compilador de C++) desde la terminal:

```bash
g++ -std=c++11 -O2 -o tictactoe tictactoe.cpp
