#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H

#include "ingredient.h"

class Cinnamon : public Ingredient {
public:
    Cinnamon (size_t units) : Ingredient(5, units) {
        this->name = "Cinnamon";
    }

    virtual Ingredient* clone () { return new Cinnamon(*this); };
    virtual std::string get_name () { return this->name; }
};

class Chocolate : public Ingredient {
public:
    Chocolate (size_t units) : Ingredient(5, units) {
        this->name = "Chocolate";
    }

    virtual Ingredient* clone () { return new Chocolate(*this); };
    virtual std::string get_name () { return this->name; }
};

class Sugar : public Ingredient {
public:
    Sugar (size_t units) : Ingredient(1, units) {
        this->name = "Sugar";
    }

    virtual Ingredient* clone () { return new Sugar(*this); };
    virtual std::string get_name () { return this->name; }
};

class Cookie : public Ingredient {
public:
    Cookie (size_t units) : Ingredient(10, units) {
        this->name = "Cookie";
    }

    virtual Ingredient* clone () { return new Cookie(*this); };
    virtual std::string get_name () { return this->name; }
};

class Espresso : public Ingredient {
public:
    Espresso (size_t units) : Ingredient(15, units) {
        this->name = "Espresso";
    }

    virtual Ingredient* clone () { return new Espresso(*this); };
    virtual std::string get_name () { return this->name; }
};

class Milk : public Ingredient {
public:
    Milk (size_t units) : Ingredient(10, units) {
        this->name = "Milk";
    }

    virtual Ingredient* clone () { return new Milk(*this); };
    virtual std::string get_name () { return this->name; }
};

class MilkFoam : public Ingredient {
public:
    MilkFoam (size_t units) : Ingredient(5, units) {
        this->name = "MilkFoam";
    }

    virtual Ingredient* clone () { return new MilkFoam(*this); };
    virtual std::string get_name () { return this->name; }
};

class Water : public Ingredient {
public:
    Water (size_t units) : Ingredient(1, units) {
        this->name = "Water";
    }

    virtual Ingredient* clone () { return new Water(*this); };
    virtual std::string get_name () { return this->name; }
};

#endif // SUB_INGREDIENTS_H