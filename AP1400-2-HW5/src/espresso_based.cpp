#include "espresso_based.h"

void EspressoBased::brew () {
    for (const auto& i : this->ingredients)
        std::cout << i->get_name() << std::endl;
}

std::vector<Ingredient*>& EspressoBased::get_ingredients () {
    return this->ingredients;
}

EspressoBased::~EspressoBased() {
    for (const auto& i : this->ingredients)
        delete i;
    this->ingredients.clear();
}

EspressoBased::EspressoBased () {
    this->ingredients = std::vector<Ingredient*>{};
    this->name = std::string();
}

EspressoBased::EspressoBased (const EspressoBased& esp) {
    this->ingredients = std::vector<Ingredient*>{};
    for (const auto& i : esp.ingredients)
        this->ingredients.push_back(i->clone());
    this->name = esp.name;
}

EspressoBased& EspressoBased::operator= (const EspressoBased& esp) {
    if (this != &esp) {
        this->name = esp.name;
        for (const auto& i : this->ingredients)
            delete i;
        this->ingredients = std::vector<Ingredient*>{};
        for (const auto& i : esp.ingredients)
            this->ingredients.push_back(i->clone());
    }
    return *this;
}