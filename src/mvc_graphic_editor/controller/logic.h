#pragma once
#include "../model/db.h"
#include "../view/ui.h"
#include "controller_interface.h"

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

class Logic: public IController {
public:
    Logic(std::weak_ptr<Model::DB> db, std::unique_ptr<View::UI> &ui);

    void handle_event(const Event &) override;

    Button create_new_file_btn;
    Button import_file_btn;
    Button export_file_btn;
    Button add_item_btn;
    Button delete_item_btn;

private:
    std::weak_ptr<Model::DB> _db_p;
    std::unique_ptr<View::UI> _ui_p;
};

} // namespace Controller
