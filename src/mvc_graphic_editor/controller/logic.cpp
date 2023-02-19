#include "logic.h"

using namespace Controller;


Logic::Logic(std::weak_ptr<Model::DB> db, std::unique_ptr<View::UI> &ui) :
    create_new_file_btn{LogicEvent::CreateNewFile, "Create new file", *this},
    import_file_btn{LogicEvent::ImportFile, "Import file", *this},
    export_file_btn{LogicEvent::ExportFile, "Export file", *this},
    add_item_btn{LogicEvent::AddItem, "Add item", *this},
    delete_item_btn{LogicEvent::DeleteItem, "Delete item", *this},
    _db_p{std::move(db)},
    _ui_p{std::move(ui)}
{
    _ui_p->add_button(&create_new_file_btn);
    _ui_p->add_button(&import_file_btn);
    _ui_p->add_button(&export_file_btn);
    _ui_p->add_button(&add_item_btn);
    _ui_p->add_button(&delete_item_btn);

    _ui_p->update();
}

void Logic::handle_event(const Event &event)
{
    if (event.type != Event::Type::ButtonPress) {
        return; /// unhandled event
    }

    switch (event.id) {
    case LogicEvent::CreateNewFile:
        _db_p.lock()->create_new_file(event.data);
        break;

    case LogicEvent::ImportFile: {
        auto items = _db_p.lock()->read_file(event.data);
        for (auto &item : items) {
            _db_p.lock()->add_item(item);
        }
    } break;

    case LogicEvent::ExportFile:
        _db_p.lock()->write_file(event.data);
        break;

    case LogicEvent::AddItem:
        _db_p.lock()->add_item(Model::Item{event.data});
        break;

    case LogicEvent::DeleteItem:
        _db_p.lock()->delete_item(event.data);
        break;
    }
}
