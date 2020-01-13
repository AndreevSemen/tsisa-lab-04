// Copyright 2019 AndreevSemen semen.andreev00@mail.ru

#ifndef INCLUDE_PARETO_SET_METHOD_HPP_
#define INCLUDE_PARETO_SET_METHOD_HPP_

#include <iomanip>

#include <types.hpp>

typedef std::vector<size_t> CriteriaIndexes;

Alternative ParetoMethod(MarksMatrix alternatives, CriteriaIndexes criteriaIndexes);

#endif // INCLUDE_PARETO_SET_METHOD_HPP_
