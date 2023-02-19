#include "logic.h"

using namespace Controller;


Logic::Logic(std::unique_ptr<Model::DB> &db, std::unique_ptr<View::UI> &ui) :
    _create_new_file_btn{LogicEvent::CreateNewFile, "Create new file"},
    _import_file_btn{LogicEvent::ImportFile, "Import file"},
    _export_file_btn{LogicEvent::ExportFile, "Export file"},
    _add_item_btn{LogicEvent::AddItem, "Add item"},
    _delete_item_btn{LogicEvent::DeleteItem, "Delete item"},
    _db_p{std::move(db)},
    _ui_p{std::move(ui)}
{
  _ui_p->add_button(&_create_new_file_btn);
  _ui_p->add_button(&_import_file_btn);
  _ui_p->add_button(&_export_file_btn);
  _ui_p->add_button(&_add_item_btn);
  _ui_p->add_button(&_delete_item_btn);
  _ui_p->render();
}

void Logic::handle_event(const Event &event)
{
  if (event.type != Event::Type::ButtonPress) {
    return; /// unhandled event
  }

  switch (event.id) {
  case LogicEvent::CreateNewFile:
    _db_p->create_new_file(event.data);
    break;

  case LogicEvent::ImportFile: {
    auto items = _db_p->read_file(event.data);
    for (auto& item : items) {
      _db_p->add_item(item);
    }
    }
    break;

  case LogicEvent::ExportFile:
    _db_p->write_file(event.data);
    break;

  case LogicEvent::AddItem:
    _db_p->add_item(Model::Item{event.data});
    break;

  case LogicEvent::DeleteItem:
    _db_p->delete_item(event.data);
    break;
  }
}