#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

// Constantes
const char EMPTY = ' ';
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';

void initBoard(char board[3][3]);
void printBoard(const char board[3][3]);
bool makeMove(char board[3][3], int row, int col, char symbol);
bool isBoardFull(const char board[3][3]);
char checkWinner(const char board[3][3]); // retorna 'X', 'O', 'D' (empate) o ' ' (nadie aún)
void playerTurn(char board[3][3], char symbol);
void gameLoopTwoPlayers();
void gameLoopVsCPU();
int minimax(char board[3][3], bool isMaximizing);
pair<int,int> findBestMove(char board[3][3]);
void showMenu();
int getValidMenuOption(int minOpt, int maxOpt);
int getValidCellChoice();

// Inicializa el tablero con espacios vacíos
void initBoard(char board[3][3]) {
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            board[r][c] = EMPTY;
        }
    }
}

// Imprime el tablero en formato amigable
void printBoard(const char board[3][3]) {
    cout << "\n";
    cout << "     1   2   3\n";
    for (int r = 0; r < 3; ++r) {
        cout << "   -------------\n";
        cout << " " << r+1 << " |";
        for (int c = 0; c < 3; ++c) {
            cout << " " << board[r][c] << " |";
        }
        cout << "\n";
    }
    cout << "   -------------\n\n";
}

// Intenta colocar el símbolo en la celda indicada; devuelve true si fue válido
bool makeMove(char board[3][3], int row, int col, char symbol) {
    if (row < 0 || row > 2 || col < 0 || col > 2) return false;
    if (board[row][col] != EMPTY) return false; // celda ocupada
    board[row][col] = symbol; // coloca la ficha
    return true;
}

// Verifica si ya no hay espacios vacíos
bool isBoardFull(const char board[3][3]) {
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c)
            if (board[r][c] == EMPTY) return false;
    return true;
}

// Revisa filas, columnas y diagonales para determinar ganador o empate
char checkWinner(const char board[3][3]) {
    // Comprobar filas y columnas
    for (int i = 0; i < 3; ++i) {
        // Filas
        if (board[i][0] != EMPTY && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return board[i][0];
        // Columnas
        if (board[0][i] != EMPTY && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return board[0][i];
    }
    // Diagonales
    if (board[0][0] != EMPTY && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return board[0][0];
    if (board[0][2] != EMPTY && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return board[0][2];

    if (isBoardFull(board)) return 'D';

    return ' ';
}

void playerTurn(char board[3][3], char symbol) {
    while (true) {
        cout << "Turno jugador '" << symbol << "'. Ingrese fila y columna (ejemplo: 2 3): ";
        int row = getValidCellChoice();
        int col = getValidCellChoice();
        
        row -= 1;
        col -= 1;

        if (makeMove(board, row, col, symbol)) {
            break;
        } else {
            cout << "Jugada invalida. Asegurate de elegir una celda libre entre 1 y 3.\n";
        }
    }
}

void gameLoopTwoPlayers() {
    char board[3][3];
    initBoard(board);
    char current = PLAYER_X;

    while (true) {
        printBoard(board);
        playerTurn(board, current);

        char result = checkWinner(board);
        if (result == PLAYER_X || result == PLAYER_O) {
            printBoard(board);
            cout << "¡Jugador '" << result << "' ha ganado! Felicidades.\n";
            break;
        } else if (result == 'D') {
            printBoard(board);
            cout << "¡Es un empate!\n";
            break;
        }

        current = (current == PLAYER_X) ? PLAYER_O : PLAYER_X;
    }
}

int minimax(char board[3][3], bool isMaximizing) {
    char winner = checkWinner(board);
    if (winner == PLAYER_X) return +10;
    if (winner == PLAYER_O) return -10;
    if (winner == 'D') return 0;

    if (isMaximizing) {
        int bestVal = numeric_limits<int>::min();
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                if (board[r][c] == EMPTY) {
                    board[r][c] = PLAYER_X; // maximizer = X
                    int val = minimax(board, false);
                    board[r][c] = EMPTY;
                    if (val > bestVal) bestVal = val;
                }
            }
        }
        return bestVal;
    } else {
        int bestVal = numeric_limits<int>::max();
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                if (board[r][c] == EMPTY) {
                    board[r][c] = PLAYER_O; // minimizer = O (CPU)
                    int val = minimax(board, true);
                    board[r][c] = EMPTY;
                    if (val < bestVal) bestVal = val;
                }
            }
        }
        return bestVal;
    }
}

pair<int,int> findBestMove(char board[3][3]) {
    int bestVal = numeric_limits<int>::max();
    pair<int,int> bestMove = {-1, -1};

    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (board[r][c] == EMPTY) {
                board[r][c] = PLAYER_O;
                int moveVal = minimax(board, true);
                board[r][c] = EMPTY;
                if (moveVal < bestVal) {
                    bestVal = moveVal;
                    bestMove = {r, c};
                }
            }
        }
    }

    if (bestMove.first == -1) {
        for (int r = 0; r < 3; ++r)
            for (int c = 0; c < 3; ++c)
                if (board[r][c] == EMPTY) return {r,c};
    }
    return bestMove;
}

void gameLoopVsCPU() {
    char board[3][3];
    initBoard(board);
    char current = PLAYER_X;

    while (true) {
        printBoard(board);
        if (current == PLAYER_X) {
            cout << "Tu turno (X).\n";
            playerTurn(board, PLAYER_X);
        } else {
            cout << "Turno CPU (O). Pensando...\n";
            pair<int,int> mv = findBestMove(board);
            if (mv.first != -1) {
                makeMove(board, mv.first, mv.second, PLAYER_O);
            } else {
                // Si no hay mejor movimiento (raro), escoger aleatorio
                bool placed = false;
                for (int r = 0; r < 3 && !placed; ++r)
                    for (int c = 0; c < 3 && !placed; ++c)
                        if (board[r][c] == EMPTY) {
                            board[r][c] = PLAYER_O;
                            placed = true;
                        }
            }
        }

        char result = checkWinner(board);
        if (result == PLAYER_X || result == PLAYER_O) {
            printBoard(board);
            if (result == PLAYER_X) cout << "¡Felicidades! ¡Ganaste!\n";
            else cout << "La CPU ha ganado. Mejor suerte la próxima.\n";
            break;
        } else if (result == 'D') {
            printBoard(board);
            cout << "¡Es un empate!\n";
            break;
        }

        current = (current == PLAYER_X) ? PLAYER_O : PLAYER_X;
    }
}

void showMenu() {
    cout << "==================== Tic Tac Toe ====================\n";
    cout << "1. Jugar 2 jugadores (local)\n";
    cout << "2. Jugar vs CPU (IA con Minimax)\n";
    cout << "3. Salir\n";
    cout << "Seleccione una opcion: ";
}

int getValidMenuOption(int minOpt, int maxOpt) {
    int opt;
    while (true) {
        if (cin >> opt) {
            if (opt >= minOpt && opt <= maxOpt) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return opt;
            }
        }
        cout << "Opcion invalida. Intente nuevamente: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int getValidCellChoice() {
    int val;
    while (true) {
        if (cin >> val) {
            if (val >= 1 && val <= 3) {
                return val;
            }
        }
        cout << "Entrada invalida. Ingrese un numero entre 1 y 3: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    while (true) {
        showMenu();
        int option = getValidMenuOption(1, 3);

        if (option == 1) {
            gameLoopTwoPlayers();
        } else if (option == 2) {
            gameLoopVsCPU();
        } else {
            cout << "Gracias por jugar. Saliendo...\n";
            break;
        }

        cout << "\nDeseas volver al menu principal? (1 = Si, 2 = No - Salir): ";
        int again = getValidMenuOption(1, 2);
        if (again == 2) {
            cout << "Saliendo del programa. ¡Hasta luego!\n";
            break;
        }
    }

    return 0;
}
