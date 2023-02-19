#pragma once
#include "controller_interface.h"

#include <string_view>
#include <string>

/// IButton - mediator pattern
class IButton {
 public:
  virtual void push(const std::string &user_input) = 0;
  virtual void render() = 0;
};

class Button : public IButton {
 public:
  explicit Button(int btn_id, std::string_view button_name, Controller::IController &controller);
  void push(const std::string &user_input) override;
  void render() override;

 private:
  int _btn_id;
  std::string _button_name;
  Controller::IController& _controller;
};
