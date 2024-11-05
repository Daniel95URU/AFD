/*
    Implementacion de funciones de estado para la ejecucion de un 
    automata finito deterministico para la validacion de expresiones regular segun el automata definido. (gr�fico 2)
*/

#include <iostream>
#include <locale.h>
#include <fstream>
using namespace std;

string word = ""; // Almacenamiento de expresi�n v�lida

/* Declaraci�n de funciones de estado */
void q1(string, int);
void q2(string, int);
void q3(string, int);
void q4(string, int);
void q5(string, int);
void q6(string, int);
int AFD(string, int);

int main() {
	setlocale(LC_CTYPE, "Spanish"); //signos de acentuaci�n.
    ifstream inputFile(".ej2.txt");

    if (!inputFile.is_open()) {
        cout << "No se encontr� el archivo";
        return 501;
    }

    string line = "";

    getline(inputFile, line); // Obtenci�n de l�nea de entrada

    bool flag = false;

    for (int i = 0; i < line.length(); i++) {
        if (AFD(line, i) > 0) {
            cout << word << " es v�lido" << endl << endl;
        } else {
            flag = true;
            cout << "La cadena ingresada no es v�lida";
        }

        word = "";
        // Paso a la siguiente expresi�n separada por espacio
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

/* Implementaci�n de funciones de estado */
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
        throw 1; // Estado final, cadena v�lida
    }
}

void q6(string line, int i) {
    char a = line[i];

    if (a == 'i') {
        word += a;
        q5(line, i + 1);
    } else {
        throw 1; // Estado final, cadena v�lida
    }
}

int AFD(string line, int i) {
    try {
        q1(line, i);
    }
    catch (int e) {
        return e; // Retorno de estado de validaci�n: -1 -> expresi�n no v�lida; 1 -> expresi�n v�lida
    }
    return 1;
}

