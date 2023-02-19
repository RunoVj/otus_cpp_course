#pragma once
#include "../controller/button.h"
#include "../model/db.h"

#include <string_view>
#include <list>

#include <observer/observer.h>

namespace View {

class UI  {
 public:
  UI();
  virtual ~UI() = default;

  void render();
  void add_button(IButton* btn);
 private:
  std::list<IButton*> _btns;
};

}