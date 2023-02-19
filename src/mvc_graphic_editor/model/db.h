#pragma once
#include <observer/observer.h>
#include <string>
#include <vector>

namespace Model {

struct Item {
    Item() = default;
    Item(std::string item_name) :
        name{std::move(item_name)} {};
    std::string name;

    bool operator==(const Item &rhs) const
    {
        if (name == rhs.name) {
            return true;
        }
        return false;
    }
};

class DB: IObserver {
public:
    DB() = default;
    void create_new_file(const std::string &filename);

    std::vector<Item> read_file(const std::string &filename);
    void write_file(const std::string &filename);

    void add_item(const Model::Item &item);
    void delete_item(const std::string &item_name);

    void subscribe(ISubscriber *) override;
    void unsubscribe(ISubscriber *) override;
    void notify() override;

    const std::vector<Item> &get_items() const;

private:
    std::vector<Item> _items;
};

} // namespace Model
