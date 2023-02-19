#include "button.h"

#include <iostream>

Button::Button(int btn_id, std::string_view button_name, Controller::IController &controller) :
    _btn_id{btn_id},
    _button_name{button_name},
    _controller{controller}
{}

void Button::push(const std::string &user_input)
{
    std::cout << _button_name + " pressed" << std::endl;

    Controller::Event event{};
    event.type = Controller::Event::Type::ButtonPress;
    event.id = _btn_id;
    event.data = user_input;
    _controller.handle_event(event);
}

void Button::render()
{
    std::cout << "Render " << _button_name << " button" << std::endl;
}
