#include "ui.h"
#include <iostream>

using namespace View;

UI::UI()
{}

void UI::render() {
  std::cout << "Render UI" << std::endl;
  for (const auto& itr : _btns) {
    itr->render();
  }
}

void UI::add_button(IButton *btn) {
  _btns.push_back(btn);
}
