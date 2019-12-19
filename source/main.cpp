
#include <iostream>
#include <variant>
#include "lager/util.hpp"

// model
struct model {
    int value = 0;
};

// actions
struct action_increment {};
struct action_decrement {};
struct action_reset {
    int new_value = 0;
};
using action = std::variant<
    action_increment,
    action_decrement,
    action_reset
>;


// reducers
model update (model p_prevState, action p_newAction) {
    return std::visit(lager::visitor {
        [&](action_increment) {
            ++p_prevState.value;
            return p_prevState;
        },
        [&](action_decrement) {
            --p_prevState.value;
            return p_prevState;
        },
        [&](action_reset a) {
            p_prevState.value = a.new_value;
            return p_prevState;
        }
    }, p_newAction);
}

int main () {
    const auto old_model = model{0};
    const auto new_model = update(old_model, action_increment{});

    std::cout << old_model.value << std::endl;
    std::cout << new_model.value << std::endl;
}
