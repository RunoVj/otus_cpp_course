#pragma once
#include <utility>
#include <vector>
#include <string>

namespace Model {

class Item {
 public:
  Item() = default;
  Item(std::string item_name) :
  _item_name{std::move(item_name)} {};
 private:
  std::string _item_name;
};

class DB {
 public:
  DB() = default;
  void create_new_file(const std::string &filename);
  std::vector<Item> read_file(const std::string &filename);
  void write_file(const std::string &filename);

  void add_item(const Model::Item &item);
  void delete_item(const std::string& item_name);

 private:
  std::vector<Item> _items;
};

} /// end of namespace Model