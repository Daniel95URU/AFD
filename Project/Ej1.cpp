/*
    Implementacion de funciones de estado para la ejecucion de un 
    tabla de transiciones para la validacion de expresiones regular definida. (gr�fico 1)
*/
#include <iostream>
#include <fstream>
#include <locale.h>
#include "matrix.h"

using namespace std;

int main() {
	setlocale(LC_CTYPE, "Spanish"); //signos de acentuaci�n.
    ifstream inputFile(".ej1.txt");

    if (!inputFile.is_open()) {
        cout << "No se encontr� el archivo";
        return 501;
    }

    string line;
    getline(inputFile, line); // Obtenci�n de l�nea de entrada

    int validate = 0; // Estado de validaci�n: 0 -> expresi�n no v�lida; 1 -> expresi�n v�lida
    string word = "";  // Almacenamiento de la expresi�n regular
    char car = '$';    // Almacenamiento de caracter procesado
    int state = 0;     // Estado inicial (q1 en el aut�mata)

    for (int i = 0; i < line.length(); i++) {
        car = line[i];

        // Validar si el caracter es uno de los esperados: 'p', 'l', 'o', 'a', 'z'
        int charIndex;
        switch (car) {
            case 'P': charIndex = 0; break;
            case 'L': charIndex = 1; break;
            case 'O': charIndex = 2; break;
            case 'A': charIndex = 3; break;
            case 'Z': charIndex = 4; break;
            default:  // Si no es un caracter v�lido, reiniciar la palabra y continuar
                if (validate == 1) {
                    cout << "Expresi�n v�lida: " << word << endl;
                }else{
                	cout << "La expresi�n ingresada no es v�lida" << word << endl;
                	return -1;
				}
                word = "";
                state = 0;
                validate = 0;
                continue;
        }

        // Realizar la transici�n de estados PRUEBA -> ^paolazoz$
        state = matrix[state][charIndex];

        // Validar estado de error
        if (state == -1) {
            i--;  // Retrocede el �ndice si el estado es de error
            state = 0;
            word = "";
            continue;
        }

        // Verificar si se ha llegado a un estado de aceptaci�n
        validate = acceptance[state];
        word += car;
    }

    // Validar al final del procesamiento
    if (validate == 1) {
        cout << "Expresi�n v�lida: " << word << endl;
    }else{
    	 cout << "Expresi�n no v�lida: " << word << endl;
	}

    return 0;
}

