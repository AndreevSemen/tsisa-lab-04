// Copyright 2019 semen.andreev00@mail.ru

#include <major_criterion_method.hpp>

Alternative MajorCriterionMethod(MarksMatrix alternatives, Marks odds) {
    size_t majorCriteriaIndex = std::distance(odds.begin(),
                                              std::find(odds.begin(),
                                                        odds.end(),
                                                        1
                                              )
                                );

    Marks extremums;
    for (size_t column = 0; column < odds.size(); ++column) {
        // Matrix normalization
        auto newColumn = NormalWeightVector(GetColumn(alternatives, column));
        alternatives = InsertColumn(alternatives, newColumn, column);

        // Extremums generation
        if (column == 0 || column == 2) {
            extremums.push_back(*std::min_element(newColumn.begin(), newColumn.end()));
        } else {
            extremums.push_back(*std::max_element(newColumn.begin(), newColumn.end()));
        }

        // Odds initialization
        odds[column] *= extremums[column];
    }

    IndexList indexes(0, alternatives.size());
    for (size_t i = 0; i < alternatives.size(); ++i) {
        bool allowed = true;
        for (size_t criteria = 0; criteria < odds.size(); ++criteria) {
            if (criteria == 0 || criteria == 2) {
                if (alternatives[i].marks[criteria] > odds[criteria]) {
                    allowed = false;
                    break;
                }
            } else {
                if (alternatives[i].marks[criteria] < odds[criteria]) {
                    allowed = false;
                    break;
                }
            }
        }
        if (!allowed) {
            indexes.Remove(i);
        }
    }

    if (indexes.list.empty()) {
        return Alternative{"no any alternative", {}};
    }

    size_t withMin = indexes.list.front();
    double min = std::numeric_limits<double>::max();
    for (const auto& index : indexes.list) {
        if (alternatives[index].marks[majorCriteriaIndex] > min) {
            withMin = index;
            min = alternatives[index].marks[majorCriteriaIndex];
        }
    }

    return alternatives[withMin];
}

