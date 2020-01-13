// Copyright 2019 semen.andreev00@mail.ru

#include <major_criterion_method.hpp>

Alternative MajorCriterionMethod(MarksMatrix alternatives, const Marks& odds) {
    for (size_t i = 0; i < odds.size(); ++i) {
        auto normalizedColumn = NormalWeightVector(GetColumn(alternatives, i));
        alternatives = InsertColumn(alternatives, normalizedColumn, i);
    }

    auto majorCriteriaIndex = std::distance(odds.begin(),
                                           std::find(odds.begin(), odds.end(), .0));

    Marks criteriaMaximums;
    for (size_t criteriaIndex = 0; criteriaIndex < odds.size(); ++criteriaIndex) {
        auto criteriaColumn = GetColumn(alternatives, criteriaIndex);
        criteriaMaximums.push_back(*std::max_element(criteriaColumn.begin(), criteriaColumn.end()));
    }

    Marks minimalAllowed(criteriaMaximums.size());
    auto oddsIter = odds.begin();
    std::transform(criteriaMaximums.begin(), criteriaMaximums.end(), minimalAllowed.begin(),
            [&oddsIter](auto& maximum) {
                return *(oddsIter++)*maximum;
            });

    auto satisfiedIter = std::remove_if(alternatives.begin(), alternatives.end(),
            [&odds](auto& alternative) {
                auto oddsIter = odds.begin();
                return !std::all_of(alternative.marks.begin(), alternative.marks.end(),
                        [&oddsIter](double mark) {
                            return mark >= *(oddsIter++);
                        });
            });
    alternatives.erase(satisfiedIter, alternatives.end());

    if (alternatives.empty()) {
        return Alternative{"no alternatives", Marks(odds.size(), .0)};
    }

    return *std::max_element(alternatives.begin(), alternatives.end(),
            [majorCriteriaIndex=majorCriteriaIndex](auto& lhs, auto& rhs) {
                return lhs.marks[majorCriteriaIndex] < rhs.marks[majorCriteriaIndex];
            });
}
