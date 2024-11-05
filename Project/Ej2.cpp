/*
    Implementacion de funciones de estado para la ejecucion de un 
    automata finito deterministico para la validacion de expresiones regular segun el automata definido. (gráfico 2)
*/

#include <iostream>
#include <locale.h>
#include <fstream>
using namespace std;

string word = ""; // Almacenamiento de expresión válida

/* Declaración de funciones de estado */
void q1(string, int);
void q2(string, int);
void q3(string, int);
void q4(string, int);
void q5(string, int);
void q6(string, int);
int AFD(string, int);

int main() {
	setlocale(LC_CTYPE, "Spanish"); //signos de acentuación.
    ifstream inputFile(".ej2.txt");

    if (!inputFile.is_open()) {
        cout << "No se encontró el archivo";
        return 501;
    }

    string line = "";

    getline(inputFile, line); // Obtención de línea de entrada

    bool flag = false;

    for (int i = 0; i < line.length(); i++) {
        if (AFD(line, i) > 0) {
            cout << word << " es válido" << endl << endl;
        } else {
            flag = true;
            cout << "La cadena ingresada no es válida";
        }

        word = "";
        // Paso a la siguiente expresión separada por espacio
        while (line[i] != 32) {
            if (flag) cout << line[i];
            
            if (i >= line.length()) break;

            if (line[i + 1] == 32 && flag) {
                flag = false;
                cout << endl << endl;
            }
            i++;
        }
    }

    return 0;
}

/* Implementación de funciones de estado */
void q1(string line, int i) {
    char a = line[i];

    if (a == 'v') {
        word += a;
        q2(line, i + 1);
    } else if (a == 'b') {
        word += a;
        q3(line, i + 1);
    } else {
        word = "";
        throw -1;
    }
}

void q2(string line, int i) {
    char a = line[i];

    if (a == 'a') {
        word += a;
        q3(line, i + 1);
    } else if (a == 'b') {
        word += a;
        q5(line, i + 1);
    } else {
        word = "";
        throw -1;
    }
}

void q3(string line, int i) {
    char a = line[i];

    if (a == 'o') {
        word += a;
        q2(line, i + 1);
    } else if (a == 'v') {
        word += a;
        q4(line, i + 1);
    } else {
        word = "";
        throw -1;
    }
}

void q4(string line, int i) {
    char a = line[i];

    if (a == 'i') {
        word += a;
        q4(line, i + 1);
    } else if (a == 't') {
        word += a;
        q6(line, i + 1);
    } else {
        word = "";
        throw -1;
    }
}

void q5(string line, int i) {
    char a = line[i];

    if (a == 'i') {
        word += a;
        q4(line, i + 1);
    } else {
        throw 1; // Estado final, cadena válida
    }
}

void q6(string line, int i) {
    char a = line[i];

    if (a == 'i') {
        word += a;
        q5(line, i + 1);
    } else {
        throw 1; // Estado final, cadena válida
    }
}

int AFD(string line, int i) {
    try {
        q1(line, i);
    }
    catch (int e) {
        return e; // Retorno de estado de validación: -1 -> expresión no válida; 1 -> expresión válida
    }
    return 1;
}

