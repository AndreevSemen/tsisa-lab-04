// Copyright 2020 AndreevSemen semen.andreev00@mail.ru

#include <criteria_union_weighting_method.hpp>

Marks Dot(const MarksMatrix& matrix, const Marks& vector);

Alternative CriteriaUnionWeightingMethod(MarksMatrix alternatives, const ExpertMarks& expertMarks) {
    for (size_t i = 0; i < alternatives.front().marks.size(); ++i) {
        auto normalizedColumn = NormalWeightVector(GetColumn(alternatives, i));
        alternatives = InsertColumn(alternatives, normalizedColumn, i);
    }

    Marks weightVector(expertMarks.size());
    auto expertMarksIter = expertMarks.begin();
    std::transform(weightVector.begin(), weightVector.end(), weightVector.begin(),
            [&expertMarksIter](auto& item) {
                auto remind = std::accumulate(expertMarksIter->begin(),
                                              expertMarksIter->end(),
                                              0.);
                ++expertMarksIter;
                return remind;
            });

    weightVector = NormalWeightVector(weightVector);

    auto result = Dot(alternatives, weightVector);

    auto withMaxValue = std::max_element(result.begin(), result.end());
    return alternatives[std::distance(result.begin(), withMaxValue)];
}

Marks Dot(const MarksMatrix& matrix, const Marks& vector) {
    Marks result;
    for (const auto& [ _ , row] : matrix) {
        double sum = 0;
        for (size_t i = 0; i < vector.size(); ++i) {
            sum += row[i]*vector[i];
        }
        result.push_back(sum);
    }

    return result;
}
