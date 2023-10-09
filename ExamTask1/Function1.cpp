#include <iostream>
#include <string>
#include "Function1.h"
using namespace std;

char nextChar = '\0'; // Терминатор
string line;          // Хранение строки
int currentPos = 0;   // Отслеживание текущей позиции в строке (каретка)

void NextChar() {    
    while (currentPos < line.length() && line[currentPos] == ' ') {
        currentPos++; // Пропускаем пробелы
    }

    if (currentPos < line.length()) {
        // Если строка не закончилась, берем следующий символ
        nextChar = line[currentPos];
        currentPos++;
    }
    else {
        // Если строка закончилась
        nextChar = '\0';
    }
}

int sum() {
    int result = part();
    char op;

    while (true) {
        op = nextChar; // Получаем следующий символ операции 

        switch (op) {
        case '+':
            NextChar(); 
            result += part(); // Вычисляем второй операнд 
            break;
        case '-':
            NextChar();
            result -= part(); // Вычисляем второй операнд 
            break;
        default:
            return result; // Возвращаем результат
        }
    }
}

int part() {
    int result = factor(); // Вычисляем первый операнд
    char op; 

    while (true) {
        op = nextChar; 

        switch (op) {
        case '*':
        {
            NextChar();
            result *= factor(); // Вычисляем второй операнд и умножаем на результат
            break;
        }
        case '/':
        {
            NextChar();
            int temp = factor(); // Вычисляем второй операнд
            if (temp == 0) {
                cerr << "Деление на ноль" << endl;
                return -1; 
            }
            result /= temp; // Вычисляем результат деления и обновляем результат
            break;
        }
        default:
            return result; // Возвращаем результат 
        }
    }
}

int factor() {
    char bracket = nextChar;
    int sign = 1; //По умолчанию положительный

    while (bracket == ' ') {
        NextChar();
    }

    switch (bracket) {
    case '-':
        sign = -1; // Устанавливаем знак -
        break;
    case '+':
        NextChar(); // Пропускаем символ +
        break;
    }

    while (bracket == ' ') {
        NextChar();
    }

    int result;

    if (bracket == '(') {
        NextChar(); // Пропускаем открывающую скобку
        result = sum(); // Вычисляем результат внутри скобок

        if (nextChar != ')') {
            cerr << "Неверная расстановка скобок " << endl;
            return -1;
        }
        NextChar(); // Продвигаемся на следующий символ после закрывающей скобки
    }
    else {
        result = num(); // Если это не скобка
    }

    return sign * result; // Учитываем знак и возвращаем результат
}

int num() {
    int result = 0;
    int sign = 1; //По умолчанию положительный

    if (nextChar == '-') {
        sign = -1; //Если следущий символ минус установка отрциательного
        NextChar();
    }
    else if (nextChar == '+') {
        NextChar(); //Если следущий символ плюс пропуск
    }

    while (nextChar >= '0' && nextChar <= '9') { //Если следущий символ цифра то добавляем
        result = result * 10 + (nextChar - '0'); 
        NextChar();
    }

    return sign * result; // Учитываем знак и возвращаем результат
}

int Calculate()
{
    int result;
    cout << "Введите выражение: ";
    getline(cin, line); // Считываем всю строку

    NextChar(); // Инициализация следующего символа

    result = sum(); // Вычисляем 

    cout << "Результат вычисления " << result << endl;

    return 0;
}