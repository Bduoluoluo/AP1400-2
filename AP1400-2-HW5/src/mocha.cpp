#include "mocha.h"

Mocha::Mocha () {
    this->name = "Mocha";
    this->ingredients = std::vector<Ingredient*>{new Espresso(2), new Milk(2), new MilkFoam(1), new Chocolate(1)};
    this->side_items = std::vector<Ingredient*>{};
}

Mocha::Mocha (const Mocha& cap) : EspressoBased(cap) {
    this->side_items = std::vector<Ingredient*>{};
    for (const auto& i : cap.side_items)
        this->side_items.push_back(i->clone());
}

Mocha::~Mocha () {
    for (const auto& i : this->side_items)
        delete i;
    this->side_items.clear();
}

Mocha& Mocha::operator= (const Mocha& cap) {
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

std::string Mocha::get_name () {
    return this->name;
}

double Mocha::price () {
    double p = 0;
    for (const auto& i : this->ingredients)
        p += i->price();
    for (const auto& i : this->side_items)
        p += i->price();
    return p;
}

void Mocha::add_side_item (Ingredient* side) {
    this->side_items.push_back(side);
}

std::vector<Ingredient*>& Mocha::get_side_items () {
    return this->side_items;
}