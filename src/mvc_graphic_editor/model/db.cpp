//
// Created by RunoVj on 2/19/2023.
//
#include "db.h"

#include <algorithm>
#include <iostream>

using namespace Model;

void DB::create_new_file(const std::string &filename)
{
    std::cout << "Create new file " + filename << std::endl;
}

std::vector<Item> DB::read_file(const std::string &filename)
{
    std::cout << "Open file " + filename << std::endl;
    /// read items from file
    std::vector<Item> items;
    items.emplace_back("Item 1");
    items.emplace_back("Item 2");
    items.emplace_back("Item 3");
    return items;
}

void DB::write_file(const std::string &filename)
{
    std::cout << "Open file " + filename << std::endl;
    for (const auto &itr : _items) {
        std::cout << "Write item " + itr.name << std::endl;
    }
}

void DB::add_item(const Model::Item &item)
{
    _items.push_back(item);
    notify();
}

void DB::delete_item(const std::string &item_name)
{
    _items.erase(std::remove(_items.begin(), _items.end(), Item{item_name}), _items.end());
    notify();
}

void DB::subscribe(ISubscriber *subscriber)
{
    _subscribers.push_back(subscriber);
}

void DB::unsubscribe(ISubscriber *subscriber)
{
    _subscribers.remove(subscriber);
}

void DB::notify()
{
    for (const auto &itr : _subscribers) {
        itr->update();
    }
}

const std::vector<Item> &DB::get_items() const
{
    return _items;
}
