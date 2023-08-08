#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <cmath>
using namespace std;
using namespace std::chrono;

// Implementación del algoritmo KMP
vector<int> computeLPSArray(const string& pattern) {
    int m = pattern.length();
    vector<int> lps(m, 0);
    int length = 0;
    int i = 1;
    
    while (i < m) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    
    return lps;
}

vector<int> KMP(const string& text, const string& pattern) {
    vector<int> positions;
    int n = text.length();
    int m = pattern.length();
    
    vector<int> lps = computeLPSArray(pattern);
    
    int i = 0, j = 0;
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        
        if (j == m) {
            positions.push_back(i - j);
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    
    return positions;
}

// Implementación del algoritmo Rabin-Karp
const int base = 10;
const int prime = 13;

vector<int> RabinKarp(const string& text, const string& pattern) {
    vector<int> positions;
    int n = text.length();
    int m = pattern.length();
    int patternHash = 0, textHash = 0;
    int h = 1;
    
    for (int i = 0; i < m - 1; i++) {
        h = (h * base) % prime;
    }
    
    for (int i = 0; i < m; i++) {
        patternHash = (patternHash * base + pattern[i]) % prime;
        textHash = (textHash * base + text[i]) % prime;
    }
    
    for (int i = 0; i <= n - m; i++) {
        if (patternHash == textHash) {
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                positions.push_back(i);
            }
        }
        
        if (i < n - m) {
            textHash = (base * (textHash - text[i] * h) + text[i + m]) % prime;
            if (textHash < 0) {
                textHash += prime;
            }
        }
    }
    
    return positions;
}


int main() {
    
    //Variable para calcular el tiempo promedio de ejecución ( un vector para cada algoritmo)
    vector<int> timeKMP;
    vector<int> timeRabinKarp;
    
    //En la seccion 0 de cada vector ira el tiempo promedio de ejecucion para un texto de 10000 caracteres y un patron que cambia entre 10 , 100 y 1000 caracteres
    //En la seccion 1 de cada vector ira el tiempo promedio de ejecucion para un texto que cambia entre 10000 , 100000 y 1000000 caracteres y un patron de 10 caracteres

    // Realizar el experimento para diferentes longitudes de texto y patrón
    for (int i = 0; i < 2; i++) {
        // Realizar el experimento para diferentes longitudes de texto y patrón
        for (int j = 0; j < 3; j++) {
            // Generar el texto usando digitos aleatorios entre 0 y 9
            string text = "";
            for (int k = 0; k < 10000 * pow(10, i); k++) {
                text += to_string(rand() % 10);
            }

            // Generar el patrón usando digitos aleatorios entre 0 y 9
            string pattern = "";
            for (int k = 0; k < 10 * pow(10, j); k++) {
                pattern += to_string(rand() % 10);
            }
            
            
            // Ejecutar el algoritmo KMP
            auto start = high_resolution_clock::now();
            vector<int> positions = KMP(text, pattern);
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(end - start);
            timeKMP.push_back(duration.count());
            
            // Ejecutar el algoritmo Rabin-Karp
            start = high_resolution_clock::now();
            positions = RabinKarp(text, pattern);
            end = high_resolution_clock::now();
            duration = duration_cast<microseconds>(end - start);
            timeRabinKarp.push_back(duration.count());
        }
    }

    //Imprimir los resultados
    cout << "Tiempo promedio de ejecucion para el algoritmo KMP" << endl;
    cout << "Texto de 10000 caracteres y patron de 10 caracteres: " << timeKMP[0] << " microsegundos" << endl;
    cout << "Texto de 10000 caracteres y patron de 100 caracteres: " << timeKMP[1] << " microsegundos" << endl;
    cout << "Texto de 10000 caracteres y patron de 1000 caracteres: " << timeKMP[2] << " microsegundos" << endl;
    cout << "Texto de 10000 caracteres y patron de 10 caracteres: " << timeKMP[3] << " microsegundos" << endl;
    cout << "Texto de 100000 caracteres y patron de 10 caracteres: " << timeKMP[4] << " microsegundos" << endl;
    cout << "Texto de 1000000 caracteres y patron de 10 caracteres: " << timeKMP[5] << " microsegundos" << endl;
    cout << endl;
    cout << "Tiempo promedio de ejecucion para el algoritmo Rabin-Karp" << endl;
    cout << "Texto de 10000 caracteres y patron de 10 caracteres: " << timeRabinKarp[0] << " microsegundos" << endl;
    cout << "Texto de 10000 caracteres y patron de 100 caracteres: " << timeRabinKarp[1] << " microsegundos" << endl;
    cout << "Texto de 10000 caracteres y patron de 1000 caracteres: " << timeRabinKarp[2] << " microsegundos" << endl;
    cout << "Texto de 10000 caracteres y patron de 10 caracteres: " << timeRabinKarp[3] << " microsegundos" << endl;
    cout << "Texto de 100000 caracteres y patron de 10 caracteres: " << timeRabinKarp[4] << " microsegundos" << endl;
    cout << "Texto de 1000000 caracteres y patron de 10 caracteres: " << timeRabinKarp[5] << " microsegundos" << endl;

    return 0;
}
 