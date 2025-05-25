#include "filter_engine.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;
using Matrix = vector<vector<double>>;

//=======================================================================================================

double congradients(double grad, double k) {
    double kappa_s = k * sqrt(2);

    if (abs(grad) <= kappa_s) {
        double term = 1 - (grad / kappa_s) * (grad / kappa_s);
        return 0.5 * term * term;
    }

    return 0;
}

Matrix read_from_file(const string& filename) {
    ifstream file(filename);
    Matrix matrix;
    string line;

    while (getline(file, line)) {
        vector<double> row;
        stringstream ss(line);
        double value;

        while (ss >> value) {
            row.push_back(value);
        }

        if (!row.empty()) {
            matrix.push_back(row);
        }
    }

    return matrix;
}

void save_to_file(const string& filename, const Matrix& mat) {

    ofstream file(filename);

    for (const auto& row : mat) {
        for (size_t i = 0; i < row.size(); i++) {
            file << fixed << setprecision(6) << row[i];
            if (i != row.size() - 1)
                file << " ";
        }
        file << "\n";
    }
}

//=======================================================================

void run_filter(const string& input_path, const string& output_path, const double iter, const double deltaT, const double k) {

    setlocale(0, "rus");

    string input_file = input_path;
    string output_file = output_path;

    Matrix input_matrix = read_from_file(input_file);

    int h = input_matrix.size();
    int w = input_matrix[0].size();

    Matrix u(h + 2, vector<double>(w + 2, 0));
    Matrix nu(h + 1, vector<double>(w + 1, 0));

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            u[i + 1][j + 1] = input_matrix[i][j];
        }
    }

    for (int m = 0; m < iter; m++) {
        for (int i = 1; i <= h; i++) {
            for (int j = 1; j <= w; j++) {

                double north = u[i - 1][j] - u[i][j];
                double south = u[i + 1][j] - u[i][j];
                double east = u[i][j + 1] - u[i][j];
                double west = u[i][j - 1] - u[i][j];

                nu[i][j] = u[i][j] + deltaT * (
                    congradients(north, k) * north +
                    congradients(south, k) * south +
                    congradients(east, k) * east +
                    congradients(west, k) * west
                    );
            }
        }

        for (int i = 1; i <= h; i++)
            for (int j = 1; j <= w; j++)
                u[i][j] = nu[i][j];
    }

    Matrix output_matrix(h, vector<double>(w));
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            output_matrix[i][j] = u[i + 1][j + 1];

    save_to_file(output_file, output_matrix);
    cout << "Сохранено в: " << output_file << endl;
}