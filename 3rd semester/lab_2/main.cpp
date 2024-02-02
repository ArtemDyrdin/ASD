#include <iostream>
#include <vector>
#include <string>

std::vector<double> numbers; // стек чисел
std::vector<char> operators; // стек операций

// запись оконченного числа в стек чисел
void put_full_number(std::string& number) {
    if (!number.empty())
        numbers.push_back(stoi(number));
    number = "";
}

int main() {
    std::string expression; // заданное выражение
    getline(std::cin, expression);

    std::string number;
    bool after_operator = false; // флажок если предыдущий элемент был оператор
    int brackets = 0; // счетчик-баланс скобочек
    int is_open_bracket = 0; // флажок о наличии открывающей скобки
    bool is_close_bracket = false; // флажок о наличии закрывающей скобки

    try {
        for (char c: expression) {
            if (isdigit(c)) {
                number += c;
                after_operator = false;

            } else if (c == '(') {
                is_open_bracket++;
                brackets++;
                put_full_number(number); // c - оператор -> число закончилось
                operators.push_back(c);
//                after_operator = true;

            } else if (c == ')') { // если c - закрывающая скобка, то вычисляем выражение в скобках
                if (is_open_bracket == 0) {
                    std::cerr << "Brackets didn't put correctly!" << std::endl;
                    return 0;
                }
                is_close_bracket = true;
                is_open_bracket--;
                brackets--;
                put_full_number(number); // c - оператор -> число закончилось
                while (!operators.empty() &&
                       operators.back() != '(') { // пока стек операторов не пуст и не дошли до открывающей скобки
                    // выбираем два последних числа из стека чисел и последнюю операцию из стека операций
                    double b = numbers.back();
                    numbers.pop_back();
                    double a = numbers.back();
                    numbers.pop_back();
                    char op = operators.back();
                    operators.pop_back();

                    // вместо двух последних чисел вставляем их выражение в соответствие с операцией
                    if (op == '+')
                        numbers.push_back(a + b);
                    else if (op == '-')
                        numbers.push_back(a - b);
                    else if (op == '*')
                        numbers.push_back(a * b);
                    else if (op == '/') {
                        if (b == 0) {
                            std::cerr << "Zero division!" << std::endl;
                            return 0;
                        }
                        numbers.push_back(a / b);
                    }
                }
                operators.pop_back(); // удаляем открывающую скобку
//                after_operator = true;

            } else if (c == '+' || c == '-' || c == '*' || c == '/') { // если c - оператор
                if (after_operator) {
                    std::cerr << "Nearby operators!" << std::endl;
                    return 0;
                }
                put_full_number(number); // c - оператор -> число закончилось
                while (!operators.empty() && (operators.back() == '*' || operators.back() ==
                                                                         '/')) { // пока стек операторов не пуст и последний оператор равен * или /
                    // выбираем два последних числа из стека чисел и последнюю операцию из стека операций
                    double b = numbers.back();
                    numbers.pop_back();
                    double a = numbers.back();
                    numbers.pop_back();
                    char op = operators.back();
                    operators.pop_back();

                    // вместо двух последних чисел вставляем их выражение в соответствие с * или /
                    if (op == '*')
                        numbers.push_back(a * b);
                    else if (op == '/') {
                        if (b == 0) {
                            std::cerr << "Zero division!" << std::endl;
                            return 0;
                        }
                        numbers.push_back(a / b);
                    }
                }
                operators.push_back(c); // добавляем операцию в стек операций
                after_operator = true;

            } else if (c == '=') { // если выражение окончилось
                if (after_operator) {
                    std::cerr << "Nearby operators!" << std::endl;
                    return 0;
                }
                if (brackets != 0) {
                    std::cerr << "Brackets didn't put correctly!" << std::endl;
                    return 0;
                }

                put_full_number(number); // c - оператор -> число закончилось
                while (!operators.empty()) { // пока стек не пуст заменяем по два последних элемента их выражениями в соответствие с операциями
                    double b = numbers.back();
                    numbers.pop_back();
                    double a = numbers.back();
                    numbers.pop_back();
                    char op = operators.back();
                    operators.pop_back();

                    if (op == '+')
                        numbers.push_back(a + b);
                    else if (op == '-')
                        numbers.push_back(a - b);
                    else if (op == '*')
                        numbers.push_back(a * b);
                    else if (op == '/') {
                        if (b == 0) {
                            std::cerr << "Zero division!" << std::endl;
                            return 0;
                        }
                        numbers.push_back(a / b);
                    }
                }

                std::cout << numbers.back() << std::endl;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    return 0;
}

/*
3+2*(1*3-2)+2*(1+2*(1*1*1+2*2)+2)+1=
*/