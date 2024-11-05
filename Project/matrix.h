
#include <iostream>
using namespace std;

const int NUMSTATES = 5; // 4 estados y un estado de error
const int NUMCAR = 5;    // 5 caracteres: P, l, O, A, Z

// Matriz de transiciones. Las filas representan estados y las columnas los caracteres ('p', 'l', 'o', 'a', 'z').
// Si una celda contiene -1, significa que el estado es de error para ese caracter.
int matrix[NUMSTATES][NUMCAR] = {
    // P    L    O    A    Z -> En el gr�fico salen en may�scula as� que se utilizaron letras Uppercase
    {  1,   1,  -1,  -1,  -1 }, // Estado 1 (q1): Transiciones hacia q2 con 'p' o 'l'
    { -1,  -1,   0,   1,   2 }, // Estado 2 (q2): Transici�n hacia q1 con 'o', hacia q2 con 'a', y hacia q3 con 'z'
    { -1,  -1,   2,  0,   3 }, // Estado 3 (q3): Transici�n hacia q1 con 'a', permanece en q3 con 'o', y hacia q4 con 'z'
    { -1,  -1,  -1,  -1,  -1 }  // Estado 4 (q4): Estado final (sin transiciones v�lidas, pero considerado de aceptaci�n)
};

// Array que indica si un estado es de aceptaci�n (1) o no (0 ).
int acceptance[NUMSTATES] = { 0, 0, 0, 1 };

