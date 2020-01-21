// Copyright 2019 AndreevSemen semen.andreev00@mail.ru

#include <iostream>
#include <iomanip>

#include <major_criterion_method.hpp>
#include <pareto_set_method.hpp>
#include <criteria_union_weighting_method.hpp>
#include <hierarchy_analysis_method.hpp>

int main() {
    /*
     * Criteria :
     *     distance, quality, control, infrastructure
     * */
    MarksMatrix alternatives = {
        Alternative{"motorway"    , {7, 7, 7, 6}},
        Alternative{"highway"     , {6, 4, 7, 7}},
        Alternative{"dirt road"   , {4, 3, 5, 3}},
        Alternative{"country road", {2, 1, 1, 1}},
    };
    std::cout << "Alternatives :" << std::endl;
    for (const auto& alternative : alternatives) {
        std::cout << std::setw(20) << alternative.name << " : ";
        for (const auto& mark : alternative.marks) {
            std::cout << mark << " ";
        }
        std::cout << std::endl;
    }

    Marks odds = {1, 0.1, 1.5, 0.1};
    std::cout << "Major criteria answer : "
              << MajorCriterionMethod(alternatives, odds).name << std::endl;


    auto paretoAnswer = ParetoMethod(alternatives, {0, 2});
    std::cout << "Pareto method answer  : "
              << paretoAnswer.name << std::endl;

    ExpertMarks expertMarks{
            {0  , 0.5, 1  , 1},
            {0.5, 0  , 0.5, 1},
            {0  , 0.5, 0  , 1},
            {0  , 0  , 0  , 0}
    };
    auto unionWeightingResult = CriteriaUnionWeightingMethod(alternatives, expertMarks);
    std::cout << "Criteria union and weighting method answer : "
              << paretoAnswer.name << std::endl;


    std::vector<ExpertMarks> alternativesMatrices = {
            {
                    {1, 1/3., 1/5., 1/7.},
                    {3, 1   , 1/4., 1/6.},
                    {5, 4   , 1   , 1/3.},
                    {7, 6   , 3   , 1   }
            },
            {
                    {1   , 5   , 7   , 9},
                    {1/5., 1   , 3   , 5},
                    {1/7., 1/3., 1   , 3},
                    {1/9., 1/5., 1/3., 1}
            },
            {
                    {1   , 1/2., 1/5., 1/9.},
                    {2   , 1   , 1/4., 1/6.},
                    {5   , 4   , 1   , 1/3.},
                    {9   , 6   , 3   , 1   }
            },
            {
                    {1   , 1/2., 3   , 5},
                    {2   , 1   , 5   , 7},
                    {1/3., 1/5., 1   , 3},
                    {1/5., 1/7., 1/3., 1}
            }
    };

    ExpertMarks criteriaMatrix = {
            {0  , 0.5, 1  , 1},
            {0.5, 0  , 0.5, 1},
            {0  , 0.5, 0  , 1},
            {0  , 0  , 0  , 0}
    };

    auto resultHierarchyIndex = HierarchyAnalysisMethod(alternativesMatrices, criteriaMatrix);
    std::cout << "Hierarchy analysis method answer : "
              << alternatives[resultHierarchyIndex].name << std::endl;

    return 0;
}
