// Copyright 2019 AndreevSemen semen.andreev00@mail.ru

#include <pareto_set_method.hpp>

constexpr size_t MaxMark = 10;

double EuclideanDistance(const Marks& lhs, const Marks& rhs, const CriteriaIndexes& indexes);
bool IsDominate(const Marks& lhs, const Marks& rhs, const CriteriaIndexes& indexes);
MarksMatrix RemoveColumn(MarksMatrix& matrix, size_t columnIndex);

Alternative ParetoMethod(MarksMatrix alternatives, CriteriaIndexes criteriaIndexes) {
    Alternative utopia{"point of utopia"};
    for (size_t i = 0; i < alternatives.front().marks.size(); ++i) {
        if (i == 0 || i == 2) {
            utopia.marks.push_back(0);
        } else {
            utopia.marks.push_back(10);
        }
    }

    IndexList indexes(0, alternatives.size());
    for (size_t i = 0; i < alternatives.size(); ++i) {
        for (size_t j = 0; j < alternatives.size(); ++j) {
            if (i == j) continue;
            if (IsDominate(alternatives[i].marks, alternatives[j].marks, criteriaIndexes)) {
                if (!indexes.IsConsists(j)) {
                    indexes.Remove(j);
                }
            }
        }
    }

    size_t withMinDistance = 0;
    double minDistance = std::numeric_limits<double>::max();
    for (const auto& index : indexes.list) {
        auto distance = EuclideanDistance(alternatives[index].marks, utopia.marks, criteriaIndexes);
        if (distance < minDistance) {
            minDistance = distance;
            withMinDistance = index;
        }
    }

    return alternatives[withMinDistance];
}

double EuclideanDistance(const Marks& lhs, const Marks& rhs, const CriteriaIndexes& indexes) {
    double sum = 0;
    for (size_t i = 0; i < lhs.size(); ++i) {
        if (std::find(indexes.begin(), indexes.end(), i) == indexes.end()) {
            continue;
        }
        sum += std::pow(lhs[i] - rhs[i], 2);
    }
    return std::sqrt(sum);
}

bool IsDominate(const Marks& lhs, const Marks& rhs, const CriteriaIndexes& indexes) {
    for (size_t i = 0; i < lhs.size(); ++i) {
        if (std::find(indexes.begin(), indexes.end(), i) == indexes.end()) {
            continue;
        }
        if (i == 0 || i == 2) {
            if (lhs[i] > rhs[i]) {
                return false;
            }
        } else {
            if (lhs[i] < rhs[i]) {
                return false;
            }
        }
    }
    return true;
}
