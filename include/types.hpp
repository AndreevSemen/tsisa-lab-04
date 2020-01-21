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

struct IndexList {
    std::vector<size_t> list;

    IndexList(size_t from, size_t to) {
        for (size_t i = from; i < to; ++i) {
            list.push_back(i);
        }
    }

    bool IsConsists(size_t index) {
        return std::find(list.begin(), list.end(), index) != list.end();
    }
    void Insert(size_t index) {
        auto position = std::lower_bound(list.begin(), list.end(), index);
        list.insert(position, index);
    }
    void Remove(size_t index) {
        auto found = std::find(list.begin(), list.end(), index);
        if (found != list.end()) {
            list.erase(found);
            return;
        }
        throw std::runtime_error{
            "There is no index : " + std::to_string(index)
        };
    }
};

struct Alternative {
    std::string name;
    Marks marks;
};

typedef std::vector<Alternative> MarksMatrix;
typedef std::vector<Marks> ExpertMarks;
typedef std::vector<Marks> Matrix;

Marks GetColumn(const MarksMatrix& matrix, size_t columnIndex);
MarksMatrix InsertColumn(const MarksMatrix& matrix, const Marks& column, size_t columnIndex);

Marks NormalWeightVector(const Marks& weight);
MarksMatrix MatrixNormalization(const MarksMatrix& alternative);

#endif // INCLUDE_TYPES_HPP_
