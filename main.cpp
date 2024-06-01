//
//  main.cpp
//  dkr1
//
//  Created by Oleksandr   on 01.06.2024.
//



#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <ctime>
using namespace std;

class Logger {
public:
    static void log(const std::string &message) {
        try {
            std::ofstream logFile("/Users/home/KPI2_2/Cpp/DKR/dkr1/log.txt", std::ios_base::app);
            if (!logFile.is_open()) {
                throw ios_base::failure("Error opening file");
            }
            logFile << currentDateTime() << " - " << message << std::endl;
        }
        catch (const std::ios_base::failure& e) {
            std::cerr << "Exception occurred: " << e.what() << std::endl;
        }
    }
    
private:
    
    static std::string currentDateTime() {
        std::time_t now = std::time(nullptr);
        char buf[80];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %X", std::localtime(&now));
        return std::string(buf);
    }
};

class ComplexNumber {
private:
    double real;
    double imag;
    
public:
    // Конструктори
    ComplexNumber() : real(0), imag(0) {}
    ComplexNumber(double r, double i) : real(r), imag(i) {}
    
    // Методи set та get
    void setReal(double r) { real = r; }
    void setImag(double i) { imag = i; }
    double getReal() const { return real; }
    double getImag() const { return imag; }
    
    // Метод toString
    std::string toString() const {
        return to_string(real) + " + " + to_string(imag) + "i";
    }
    
    // Перевантаження оператора «»
    friend ostream& operator<<(ostream &os, const ComplexNumber &cn) {
        os << cn.toString();
        return os;
    }
    
    // Метод для обчислення модуля суми двох комплексних чисел
    double modulusSum(const ComplexNumber &other) const {
        double sumReal = real + other.real;
        double sumImag = imag + other.imag;
        return sqrt(sumReal * sumReal + sumImag * sumImag);
    }
    
    // Метод для збереження даних у файл з шифруванням
    void saveToFile(const std::string &filename) const {
        ofstream file(filename, ios::binary);
        if (file.is_open()) {
            double encryptedReal = real + 10;  // Просте шифрування додаванням 10
            double encryptedImag = imag + 10;  // Просте шифрування додаванням 10
            file.write(reinterpret_cast<const char*>(&encryptedReal), sizeof(encryptedReal));
            file.write(reinterpret_cast<const char*>(&encryptedImag), sizeof(encryptedImag));
            file.close();
            Logger::log("Data saved to file with encryption");
        }
    }
};

int main() {
    ComplexNumber num1(1, 3);
    ComplexNumber num2(-1, 2);
    
    Logger::log("Complex numbers created");
    
    double modulus = num1.modulusSum(num2);
    cout << "Modulus of the sum: " << modulus << endl;
    
    Logger::log("Modulus of the sum calculated");
    
    num1.saveToFile("/Users/home/KPI2_2/Cpp/DKR/dkr1/complex1.txt");
    num2.saveToFile("/Users/home/KPI2_2/Cpp/DKR/dkr1/complex2.txt");
    
    Logger::log("Complex numbers saved to files");
    
    return 0;
}
