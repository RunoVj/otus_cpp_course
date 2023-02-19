#include "ui.h"

#include <iostream>

using namespace View;

UI::UI(std::weak_ptr<Model::DB> db) :
    _db{std::move(db)}
{
    _db.lock()->subscribe(this);
    std::cout << "Render UI" << std::endl;
}

void UI::add_button(IButton *btn)
{
    std::cout << "Render UI" << std::endl;
    _btns.push_back(btn);
    btn->render();
    std::cout << std::endl;
}

void UI::update()
{
    std::cout << "Render UI" << std::endl;
    for (const auto &itr : _db.lock()->get_items()) {
        std::cout << "Render " << itr.name << std::endl;
    }
    std::cout << std::endl;
}
