#include <cstdlib>
#include <iostream>
#include "filter_engine.h"

using namespace std;

int main() {

    setlocale(0, "rus");

    const double iter = 35;
    const double deltaT = 0.2;
    const double k = 15;

    string input_path_image = "C++_photo.txt";
    string output_path_image = "filtered_output_1.txt";

    string input_path_cube = "C++_cube_1.txt";
    string output_path_cube = "filtered_output_2.txt";

    //===========================================================

    cout << "Запуск Python для сохранения форматов..." << endl;

    int format = system("python Python_p1.py");

    if (format == 0) {
        cout << "Python-скрипт успешно выполнен" << endl;
    }
    else {
        cerr << "Ошибка при запуске Python-скрипта!" << endl;
    }

    //===========================================================

    cout << "Запуск фильтрации..." << endl;
    run_filter(input_path_image, output_path_image, iter, deltaT, k); //фото
    run_filter(input_path_cube, output_path_cube, iter, deltaT, k); //куб

    //===========================================================

    cout << "Фильтрация завершена. Запуск Python..." << endl;

    int result = system("python Python_p2.py");

    if (result == 0) {
        cout << "Python-скрипт успешно выполнен" << endl;
    }
    else {
        cerr << "Ошибка при запуске Python-скрипта!" << endl;
    }

    return 0;
}