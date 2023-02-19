#include "mvc_graphic_editor/model/db.h"
#include "mvc_graphic_editor/view/ui.h"
#include "mvc_graphic_editor/controller/logic.h"

#include <iostream>
#include <filesystem>

int main([[maybe_unused]] int argc, [[maybe_unused]] char const *argv[])
{
  auto db_p = std::make_shared<Model::DB>(); /// db keeps somewhere else
  auto ui_p = std::make_unique<View::UI>(std::weak_ptr<Model::DB>(db_p));

  Controller::Logic logic{std::weak_ptr<Model::DB>(db_p), ui_p};

  std::cout << std::endl;
  logic.create_new_file_btn.push("Untitled");
  logic.import_file_btn.push(std::filesystem::path{"./in"}.string());
  logic.export_file_btn.push(std::filesystem::path{"./out"}.string());
  logic.add_item_btn.push("New random item");
  logic.delete_item_btn.push("New random item");
  return 0;
}