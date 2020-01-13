// Copyright 2019 semen.andreev00@mail.ru

#include  <types.hpp>

Marks GetColumn(const MarksMatrix& matrix, size_t columnIndex) {
    Marks column;
    for (const auto& row : matrix) {
        column.push_back(row.marks[columnIndex]);
    }

    return column;
}

MarksMatrix InsertColumn(const MarksMatrix& matrix, const Marks& column, size_t columnIndex) {
    auto updatedMatrix = matrix;
    for (size_t i = 0; i < column.size(); ++i) {
        updatedMatrix[i].marks[columnIndex] = column[i];
    }

    return updatedMatrix;
}

Marks NormalWeightVector(const Marks& weights) {
    auto normalized = weights;
    auto sum = std::accumulate(weights.begin(), weights.end(), 0.);
    std::transform(normalized.begin(), normalized.end(),
                   normalized.begin(),
            [sum=sum](auto& mark) {
                return mark /= sum;
            });

    return normalized;
}

MarksMatrix MatrixNormalization(const MarksMatrix& alternatives) {
    auto normalized = alternatives;
    std::transform(normalized.begin(), normalized.end(), normalized.begin(),
            [](auto& alternative) {
                return Alternative{alternative.name,
                                   NormalWeightVector(alternative.marks)
                };
            });

    return normalized;
}

