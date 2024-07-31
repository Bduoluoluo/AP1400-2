#include "cappuccino.h"

Cappuccino::Cappuccino () {
    this->name = "Cappuccino";
    this->ingredients = std::vector<Ingredient*>{new Espresso(2), new Milk(2), new MilkFoam(1)};
    this->side_items = std::vector<Ingredient*>{};
}

Cappuccino::Cappuccino (const Cappuccino& cap) : EspressoBased(cap) {
    this->side_items = std::vector<Ingredient*>{};
    for (const auto& i : cap.side_items)
        this->side_items.push_back(i->clone());
}

Cappuccino::~Cappuccino () {
    for (const auto& i : this->side_items)
        delete i;
    this->side_items.clear();
}

Cappuccino& Cappuccino::operator= (const Cappuccino& cap) {
    if (this != &cap) {
        this->name = cap.name;
        for (const auto& i : this->ingredients)
            delete i;
        for (const auto& i : this->side_items)
            delete i;
        this->ingredients = std::vector<Ingredient*>{};
        for (const auto& i : cap.ingredients)
            this->ingredients.push_back(i->clone());
        this->side_items = std::vector<Ingredient*>{};
        for (const auto& i : cap.side_items)
            this->side_items.push_back(i->clone());        
    }
    return *this;
}

std::string Cappuccino::get_name () {
    return this->name;
}

double Cappuccino::price () {
    double p = 0;
    for (const auto& i : this->ingredients)
        p += i->price();
    for (const auto& i : this->side_items)
        p += i->price();
    return p;
}

void Cappuccino::add_side_item (Ingredient* side) {
    this->side_items.push_back(side);
}

std::vector<Ingredient*>& Cappuccino::get_side_items () {
    return this->side_items;
}