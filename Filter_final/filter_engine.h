#ifndef FILTER_ENGINE_H
#define FILTER_ENGINE_H

#include <string>

using namespace std;

void run_filter(const string& input_path, const string& output_path, const double iter, const double deltaT, const double k);

#endif