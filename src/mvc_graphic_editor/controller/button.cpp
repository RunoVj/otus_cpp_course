#include "button.h"
#include <iostream>


View::Button::Button(int btn_id, std::string_view button_name) :
  _btn_id{btn_id},
  _button_name{button_name}
{
  std::cout << "Add " << button_name << " button" << std::endl;
}

void View::Button::push(const std::string &user_input) {
  std::cout << _button_name + " pressed" << std::endl;

  Controller::Event event{};
  event.type = Controller::Event::Type::ButtonPress;
  event.id = _btn_id;
  event.data = user_input;
  logic->handle_event(event);
}

void View::Button::render() {
  std::cout << "Render " << _button_name << " button" << std::endl;
}
