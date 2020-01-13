// Copyright 2019 AndreevSemen semen.andreev00@mail.ru

#include <pareto_set_method.hpp>

constexpr size_t MaxMark = 10;

double EuclideanDistance(const Marks& lhs, const Marks& rhs);
bool IsDominate(const Marks& lhs, const Marks& rhs);
MarksMatrix RemoveColumn(MarksMatrix& matrix, size_t columnIndex);

Alternative ParetoMethod(MarksMatrix alternatives, CriteriaIndexes criteriaIndexes) {
    std::vector<size_t> indexesToDelete;
    for (size_t i = 0; i < alternatives.back().marks.size(); ++i) {
        if (std::find(criteriaIndexes.begin(), criteriaIndexes.end(), i) ==
            criteriaIndexes.end()) {
            indexesToDelete.push_back(i);
        }
    }
    std::sort(indexesToDelete.begin(), indexesToDelete.end(), std::greater<>{});

    for (const auto& columnIndex : indexesToDelete) {
        RemoveColumn(alternatives, columnIndex);
    }
    indexesToDelete.clear();

    for (size_t i = 0; i < alternatives.size(); ++i) {
        for (size_t j = 0; j < alternatives.size(); ++j) {
            if (i == j) continue;
            if (IsDominate(alternatives[i].marks, alternatives[j].marks)) {
                if (std::find(indexesToDelete.begin(),
                              indexesToDelete.end(), j) ==
                    indexesToDelete.end()) {
                    indexesToDelete.push_back(j);
                }
            }
        }
    }
    std::sort(indexesToDelete.begin(), indexesToDelete.end(), std::greater<>{});
    for (auto index : indexesToDelete) {
        alternatives.erase(alternatives.begin() + index);
    }

    std::cout << "Pareto set : " << std::endl;
    for (const auto& [name, row] : alternatives) {
        std::cout << std::setw(20) << name << " : ";
        for (double mark : row) {
            std::cout << mark << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Utopia point : [10, 10]" << std::endl;

    Alternative withMinDistance{"dummy", {}};
    double minDistance = std::numeric_limits<double>::max();
    for (const auto& alternative : alternatives) {
        Marks utopia(alternative.marks.size(), MaxMark);
        auto distance = EuclideanDistance(alternative.marks, utopia);
        if (distance < minDistance) {
            withMinDistance = alternative;
            minDistance = distance;
        }
    }

    return withMinDistance;
}

double EuclideanDistance(const Marks& lhs, const Marks& rhs) {
    double sum = 0;
    for (size_t i = 0; i < lhs.size(); ++i) {
        sum += std::pow(lhs[i] - rhs[i], 2);
    }
    return std::sqrt(sum);
}

bool IsDominate(const Marks& lhs, const Marks& rhs) {
    for (size_t i = 0; i < lhs.size(); ++i) {
        if (lhs[i] < rhs[i]) {
            return false;
        }
    }
    return true;
}

MarksMatrix RemoveColumn(MarksMatrix& matrix, size_t columnIndex) {
    for (auto& [ _ , row] : matrix) {
        row.erase(row.begin() + columnIndex);
    }
    return matrix;
}
