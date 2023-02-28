//
// Created by 12355 on 24.02.2023.
//

#ifndef CPP2_S21_CONTAINERS_0_N_DIST_H
#define CPP2_S21_CONTAINERS_0_N_DIST_H


template <typename FirstType, typename SecondType>
class Pair {
public:
    using first_type = FirstType;
    using second_type = SecondType;
    first_type first{};
    second_type second{};
    Pair() = default;
    Pair(first_type first_value, second_type second_value) : first(first_value), second(second_value) {}
}


#endif //CPP2_S21_CONTAINERS_0_N_DIST_H
