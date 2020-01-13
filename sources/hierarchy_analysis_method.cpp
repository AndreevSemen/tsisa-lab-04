// Copyright 2020 AndreevSemen semen.andreev00@mail.ru

#include <hierarchy_analysis_method.hpp>

ExpertMarks InsertColumn(const ExpertMarks& matrix, const Marks& column, size_t columnIndex);
Marks Dot(const ExpertMarks& matrix, const Marks& vector);

size_t HierarchyAnalysisMethod(const std::vector<ExpertMarks>& alternativeMatrices,
                                    const ExpertMarks& criteriaMatrix) {
    ExpertMarks alternativesMatrix(alternativeMatrices.size(),
                                   Marks(alternativeMatrices.size(), 0.));
    for (size_t i = 0; i < alternativeMatrices.size(); ++i) {
        Marks column;
        for (const auto& row : alternativeMatrices[i]) {
            column.push_back(std::accumulate(row.begin(), row.end(), 0.));
        }
        column = NormalWeightVector(column);
        alternativesMatrix = InsertColumn(alternativesMatrix, column, i);
    }

    Marks criteriaVector;
    for (const auto& row : criteriaMatrix) {
        criteriaVector.push_back(std::accumulate(row.begin(), row.end(), 0.));
    }

    criteriaVector = NormalWeightVector(criteriaVector);

    auto result = Dot(alternativesMatrix, criteriaVector);
    auto withMaxValue = std::max_element(result.begin(), result.end());
    return std::distance(result.begin(), withMaxValue);
}

ExpertMarks InsertColumn(const ExpertMarks& matrix, const Marks& column, size_t columnIndex) {
    auto updatedMatrix = matrix;
    for (size_t i = 0; i < column.size(); ++i) {
        updatedMatrix[i][columnIndex] = column[i];
    }

    return updatedMatrix;
}

Marks Dot(const ExpertMarks& matrix, const Marks& vector) {
    Marks result;
    for (const auto& row : matrix) {
        double sum = 0;
        for (size_t i = 0; i < vector.size(); ++i) {
            sum += row[i]*vector[i];
        }
        result.push_back(sum);
    }

    return result;
}
