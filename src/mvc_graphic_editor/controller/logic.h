#pragma once
#include "controller_interface.h"
#include "../model/db.h"
#include "../view/ui.h"

#include <iostream>
#include <memory>
#include <observer/observer.h>

namespace Controller {

enum LogicEvent {
 CreateNewFile,
 ImportFile,
 ExportFile,
 AddItem,
 DeleteItem
};

class Logic : public IController{
 public:
  Logic(std::unique_ptr<Model::DB> &db, std::unique_ptr<View::UI> &ui);

  void handle_event(const Event &) override;

 private:
  View::Button _create_new_file_btn;
  View::Button _import_file_btn;
  View::Button _export_file_btn;
  View::Button _add_item_btn;
  View::Button _delete_item_btn;

  std::unique_ptr<Model::DB> _db_p;
  std::unique_ptr<View::UI> _ui_p;
};

} /// end of namespace Controller