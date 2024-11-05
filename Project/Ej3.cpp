/*
    Implementación de funciones de estado para la ejecución de un 
    autómata finito determinista basado en la regex = ((a*|b*)c)?abcd. (gráfico visto en clases).
*/

#include <iostream>
#include <fstream>
#include <locale.h>
using namespace std;

string word = ""; // Almacenamiento de expresión válida

/* Declaración de funciones de estado */
void q1(string, int);
void q2(string, int);
void q3(string, int);
void q4(string, int);
void q5(string, int);
void q6(string, int);
void q7(string, int);
void q8(string, int);
void q9(string, int);
void q10(string, int);
void q11(string, int);
int AFD(string, int);

int main() {
	setlocale(LC_CTYPE, "Spanish"); //signos de acentuación.
    ifstream inputFile(".ej3.txt"); //Ejemplo de una cadena en .ej3.txt

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
            cout << "no es valida la cadena introducida. ";
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

    if (a == 'c') {
        word += a;
        q2(line, i + 1);
    } else if (a == 'a') {
        word += a;
        q8(line, i + 1);
    } else if (a == 'b') {
        word += a;
        q7(line, i + 1);
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
    } else {
        word = "";
        throw -1;
    }
}

void q3(string line, int i) {
    char a = line[i];

    if (a == 'b') {
        word += a;
        q4(line, i + 1);
    } else {
        word = "";
        throw -1;
    }
}

void q4(string line, int i) {
    char a = line[i];

    if (a == 'c') {
        word += a;
        q5(line, i + 1);
    } else {
        word = "";
        throw -1;
    }
}

void q5(string line, int i) {
    char a = line[i];

    if (a == 'd') {
        word += a;
        q6(line, i + 1);
    } else {
        word = "";
        throw -1;
    }
}

void q6(string line, int i) {
    throw 1; // Estado final, cadena válida
}

void q7(string line, int i) {
    char a = line[i];

    if (a == 'b') {
        word += a;
        q7(line, i + 1);
    } else if (a == 'c') {
        word += a;
        q2(line, i + 1);
    } else {
        word = "";
        throw -1;
    }
}

void q8(string line, int i) {
    char a = line[i];

    if (a == 'c') {
        word += a;
        q2(line, i + 1);
    } else if (a == 'a') {
        word += a;
        q11(line, i + 1);
    } else if (a == 'b') {
        word += a;
        q9(line, i + 1);
    } else {
        word = "";
        throw -1;
    }
}

void q9(string line, int i) {
    char a = line[i];

    if (a == 'c') {
        word += a;
        q10(line, i + 1);
    } else {
        word = "";
        throw -1;
    }
}

void q10(string line, int i) {
    char a = line[i];

    if (a == 'd') {
        word += a;
        q6(line, i + 1);
    } else {
        word = "";
        throw -1;
    }
}

void q11(string line, int i) {
    char a = line[i];

    if (a == 'a') {
        word += a;
        q11(line, i + 1);
    } else if (a == 'c') {
        word += a;
        q2(line, i + 1);
    } else {
        word = "";
        throw -1;
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

