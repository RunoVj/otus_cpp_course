#pragma once
#include <string>
#include <string_view>
#include <tuple>

namespace Controller {

/// weak_ptr !!! + observer pattern

struct Event {
    enum class Type {
        ButtonPress = 0
    };
    Type type;
    int id;
    std::string data;
};

class IController {
public:
    virtual void handle_event(const Event &) = 0;
};

} // namespace Controller
