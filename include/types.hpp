// Copyright 2019 semen.andreev00@mail.ru

#ifndef INCLUDE_TYPES_HPP_
#define INCLUDE_TYPES_HPP_

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <numeric>

typedef std::vector<double> Marks;

struct Alternative {
    std::string name;
    Marks marks;
};

typedef std::vector<Alternative> MarksMatrix;
typedef std::vector<Marks> ExpertMarks;

Marks GetColumn(const MarksMatrix& matrix, size_t columnIndex);
MarksMatrix InsertColumn(const MarksMatrix& matrix, const Marks& column, size_t columnIndex);

Marks NormalWeightVector(const Marks& weight);
MarksMatrix MatrixNormalization(const MarksMatrix& alternative);

#endif // INCLUDE_TYPES_HPP_
