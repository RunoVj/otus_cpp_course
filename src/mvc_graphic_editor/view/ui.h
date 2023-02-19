#pragma once
#include "../controller/button.h"
#include "../model/db.h"

#include <string_view>
#include <list>
#include <memory>

#include <observer/observer.h>

namespace View {

class UI : public ISubscriber {
 public:
  UI(std::weak_ptr<Model::DB> db_p);
  virtual ~UI() = default;

  void update() override;
  void add_button(IButton* btn);

 private:
  std::list<IButton*> _btns;
  std::weak_ptr<Model::DB> _db;
};

}