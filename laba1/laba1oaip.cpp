/*В каждом задании по возможности ввод, вывод, сортировку оформить как отдельные функции
(применить к этим   функциям классы хранения),
функцию сортировки массива структур поместить в отдельный файл,
структурную переменную объявить как статическую,
счетчики циклов объявить как регистровые переменные,
передачу значений осуществить через внешние переменные,
осуществить динамическое распределение памяти под структуры.

7. Описать структуру с именем ZNAK, содержащую следующие поля:
фамилия, имя; знак зодиака; день рождения (массив из трех чисел).
Написать программу, выполняющую следующие действия: ввод с клавиатуры данных в массив,
состоящий из восьми элементов типа ZNAK; упорядочивать записи по датам дней рождения; 
вывод на экран информации о людях, родившихся под знаком, наименование которого введено с клавиатуры; 
если такого нет, выдать на дисплей соответствующее сообщение.*/

#include <iostream>
#include <string>
#include <algorithm>
#include <limits>
#include <stdexcept>
#include <map>
#include <vector>

using namespace std;


struct ZNAK {
    string fam;
    string name;
    string znak;
    int date[3]; 

    void input();  
    void output() const;
    static bool isValidZod(const string& zodiac); 
};


ZNAK* znaks = nullptr;
int userCount = 0; 

map<string, pair<string, vector<pair<int, pair<int, int>>>>> zodiacs = {
    {"aries", {"Овен", {{{3, {21, 31}}, {4, {1, 19}}}}}},
    {"taurus", {"Телец", {{{4, {20, 30}}, {5, {1, 20}}}}}},
    {"gemini", {"Близнецы", {{{5, {21, 31}}, {6, {1, 20}}}}}},
    {"cancer", {"Рак", {{{6, {21, 30}}, {7, {1, 22}}}}}},
    {"leo", {"Лев", {{{7, {23, 31}}, {8, {1, 22}}}}}},
    {"virgo", {"Дева", {{{8, {23, 31}}, {9, {1, 22}}}}}},
    {"libra", {"Весы", {{{9, {23, 30}}, {10, {1, 22}}}}}},
    {"scorpio", {"Скорпион", {{{10, {23, 31}}, {11, {1, 21}}}}}},
    {"sagittarius", {"Стрелец", {{{11, {22, 30}}, {12, {1, 21}}}}}},
    {"capricorn", {"Козерог", {{{12, {22, 31}}, {1, {1, 19}}}}}},
    {"aquarius", {"Водолей", {{{1, {20, 31}}, {2, {1, 18}}}}}},
    {"pisces", {"Рыбы", {{{2, {19, 28}}, {3, {1, 20}}}}}}
};


bool isStringValid(const string& str) {
    return !str.empty() && str.find_first_not_of(' ') != string::npos;
}


bool ZNAK::isValidZod(const string& zodiac) {
    const string valid_z[] = {
        "aries", "taurus", "gemini", "cancer", "leo", "virgo",
        "libra", "scorpio", "sagittarius", "capricorn", "aquarius", "pisces"
    };
    string zodiacLower = zodiac;
    transform(zodiacLower.begin(), zodiacLower.end(), zodiacLower.begin(), ::tolower);

    for (const auto& valid : valid_z) {
        if (valid == zodiacLower) {
            return true;
        }
    }
    return false;
}

void ZNAK::input() {
    auto getInput = [](const string& prompt) -> string {
        string input;
        while (true) {
            cout << prompt;
            getline(cin, input);

            if (!isStringValid(input)) {
                cerr << "Ошибка! Вы ничего не ввели или ввели только пробелы. Пожалуйста, попробуйте снова." << endl;
            } else if (input.find_first_of("0123456789") != string::npos) {
                cerr << "Ошибка! Фамилия и имя не должны содержать цифры и другие символы. Попробуйте снова." << endl;
            } else {
                break;
            }
        }
        return input;
    };

    fam = getInput("Введите фамилию: ");
    name = getInput("Введите имя: ");

    cout << "\nДоступные знаки зодиака (на английском):\n"
         << "1. Aries (Овен) - 21 марта - 19 апреля\n"
         << "2. Taurus (Телец) - 20 апреля - 20 мая\n"
         << "3. Gemini (Близнецы) - 21 мая - 20 июня\n"
         << "4. Cancer (Рак) - 21 июня - 22 июля\n"
         << "5. Leo (Лев) - 23 июля - 22 августа\n"
         << "6. Virgo (Дева) - 23 августа - 22 сентября\n"
         << "7. Libra (Весы) - 23 сентября - 22 октября\n"
         << "8. Scorpio (Скорпион) - 23 октября - 21 ноября\n"
         << "9. Sagittarius (Стрелец) - 22 ноября - 21 декабря\n"
         << "10. Capricorn (Козерог) - 22 декабря - 19 января\n"
         << "11. Aquarius (Водолей) - 20 января - 18 февраля\n"
         << "12. Pisces (Рыбы) - 19 февраля - 20 марта\n";


    while (true) {
        string zodiac = getInput("Введите знак зодиака на английском: ");
        string zodiacLower = zodiac;
        transform(zodiacLower.begin(), zodiacLower.end(), zodiacLower.begin(), ::tolower);

        if (isValidZod(zodiacLower)) {
            znak = zodiacLower;
            break;
        } else {
            cerr << "Ошибка: некорректный ввод знака зодиака. Попробуйте еще раз.\n";
        }
    }


    cout << "Для знака зодиака " << znak << " (" << zodiacs[znak].first << ") допустимые месяцы: ";
    for (const auto& d : zodiacs[znak].second) {
        cout << d.first << " ";
    }
    cout << "\nВведите месяц рождения: ";

    int month;
    while (true) {
        string input;
        getline(cin, input);

        try {
            month = stoi(input);
            bool validMonth = false;
            for (const auto& d : zodiacs[znak].second) {
                if (month == d.first) {
                    validMonth = true;
                    break;
                }
            }

            if (!validMonth) {
                throw runtime_error("Ошибка: некорректный месяц для выбранного знака зодиака.");
            }
            break;
        } catch (const exception&) {
            cerr << "Ошибка: некорректный ввод. Попробуйте еще раз.\n";
        }
    }

 
    for (const auto& d : zodiacs[znak].second) {
        if (month == d.first) {
            cout << "Для знака зодиака " << znak << " (" << zodiacs[znak].first << ") допустимые дни в " << month << " месяце: "
                 << d.second.first << "-" << d.second.second << endl;
            break;
        }
    }


    cout << "Введите день рождения: ";
    while (true) {
        string input;
        getline(cin, input);

        try {
            // Проверка, что введено только одно число
            size_t pos;
            int day = stoi(input, &pos);
            if (pos != input.size()) {
                throw runtime_error("Ошибка: введено более одного числа или некорректные символы.");
            }

            bool validDay = false;
            for (const auto& d : zodiacs[znak].second) {
                if (month == d.first && day >= d.second.first && day <= d.second.second) {
                    validDay = true;
                    break;
                }
            }

            if (!validDay) {
                throw runtime_error("Ошибка: некорректный день для выбранного знака зодиака.");
            }

            date[1] = month;
            date[0] = day;
            break;
        } catch (const exception& e) {
            cerr << e.what() << " Попробуйте еще раз.\n";
        }
    }

    // Ввод года рождения
    cout << "Введите год рождения (от 100 до 2025): ";
    while (true) {
        string input;
        getline(cin, input);

        try {
            // Проверка, что введено только одно число
            size_t pos;
            int year = stoi(input, &pos);
            if (pos != input.size()) {
                throw runtime_error("Ошибка: введено более одного числа или некорректные символы.");
            }

            if (year < 100 || year > 2025) {
                throw runtime_error("Ошибка: некорректный год. Введите число от 100 до 2025.");
            }

            date[2] = year;
            break;
        } catch (const exception& e) {
            cerr << e.what() << " Попробуйте еще раз.\n";
        }
    }
}

// Функция для вывода данных
void ZNAK::output() const {
    cout << "Фамилия: " << fam << "\nИмя: " << name
         << "\nЗнак зодиака: " << znak << " (" << zodiacs[znak].first << ")"
         << "\nДата рождения: " << date[0] << "." << date[1] << "." << date[2] << endl;
}

// Функция сортировки по дате рождения
void sortDate(ZNAK* znaks, int count) {
    sort(znaks, znaks + count, [](const ZNAK& a, const ZNAK& b) {
        if (a.date[2] != b.date[2]) return a.date[2] < b.date[2];
        if (a.date[1] != b.date[1]) return a.date[1] < b.date[1];
        return a.date[0] < b.date[0];
    });
}

// Функция для поиска и вывода людей по знаку зодиака
void outputZod(ZNAK* znaks, int count, const string& zodiac) {
    string zodiacLower = zodiac;
    transform(zodiacLower.begin(), zodiacLower.end(), zodiacLower.begin(), ::tolower);

    bool found = false;
    for (int i = 0; i < count; ++i) {
        if (znaks[i].znak == zodiacLower) {
            znaks[i].output();
            found = true;
        }
    }
    if (!found) {
        cout << "Нет людей с знаком зодиака " << zodiac << "." << endl;
    }
}

// Основное меню программы
void menu() {
    while (true) {
        cout << "\nМеню:\n"
             << "1. Добавить новых пользователей\n"
             << "2. Найти людей по знаку зодиака\n"
             << "3. Выйти\n"
             << "Выберите опцию: ";

        string input;
        getline(cin, input);

        if (!isStringValid(input)) {
            cerr << "Ошибка! Вы ничего не ввели. Пожалуйста, попробуйте снова." << endl;
            continue;
        }

        try {
            int choice = stoi(input);

            switch (choice) {
                case 1: {
                    cout << "Введите количество людей для записи: ";
                    while (true) {
                        getline(cin, input);

                        try {
                            userCount = stoi(input);
                            if (userCount <= 0) {
                                throw runtime_error("Ошибка: количество должно быть положительным числом.");
                            }
                            break;
                        } catch (const exception&) {
                            cerr << "Ошибка: некорректный ввод. Попробуйте еще раз.\n";
                        }
                    }

                    znaks = new ZNAK[userCount]; // Динамическое выделение памяти
                    for (int i = 0; i < userCount; ++i) {
                        cout << "Ввод данных для человека " << (i + 1) << ":\n";
                        znaks[i].input();
                    }

                    sortDate(znaks, userCount); // Сортировка по дате рождения
                    break;
                }
                case 2: {
                    if (znaks == nullptr) {
                        cout << "Сначала добавьте пользователей!" << endl;
                        break;
                    }

                    string zodiac;
                    cout << "Введите знак зодиака для поиска: ";
                    getline(cin, zodiac);

                    outputZod(znaks, userCount, zodiac); // Поиск и вывод по знаку зодиака
                    break;
                }
                case 3: {
                    delete[] znaks; // Освобождение памяти
                    cout << "Выход из программы." << endl;
                    return;
                }
                default: {
                    cout << "Некорректный выбор. Попробуйте снова." << endl;
                    break;
                }
            }
        } catch (const exception&) {
            cerr << "Ошибка: некорректный ввод. Попробуйте еще раз.\n";
        }
    }
}

int main() {
    menu(); // Запуск меню
    return 0;
}