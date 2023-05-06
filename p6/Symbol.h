
#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <iostream>
#include <string>
#include "types_and_ops.h"
#include <assert.h>
#include "Locator.h"
// gameobject type
#include "Rectangle.h"
#include "Circle.h"
#include "Textbox.h"
#include "Triangle.h"
#include "Pixmap.h"
#include "Animation_code.h"
class Constant;
union symboltype{
        double *double_pointer;
        int *int_pointer;
        std::string *string_pointer;
        Circle *circle_pointer;
        Rectangle *rectangle_pointer;
        Textbox *textbox_pointer;
        Triangle *triangle_pointer;
        Pixmap *pixmap_pointer;
        Animation_code* animation_code_pointer;


        symboltype(){}
        symboltype(int* value): int_pointer(value){};
        symboltype(double* value): double_pointer(value){};
        symboltype(std::string* value): string_pointer(value){};
        symboltype(Circle *value) : circle_pointer(value) {}
        symboltype(Rectangle *value) : rectangle_pointer(value) {}
        symboltype(Textbox *value) : textbox_pointer(value) {}
        symboltype(Triangle *value) : triangle_pointer(value) {}
        symboltype(Pixmap *value) : pixmap_pointer(value) {}
        symboltype(Animation_code *value) : animation_code_pointer(value) {}
};

class Symbol {


    public:
        Symbol(const std::string& name, double* value);
        Symbol(const std::string& name, double* value, int count);
        Symbol(const std::string& name, int* value);
        Symbol(const std::string& name, int* value, int count);
        Symbol(const std::string& name, std::string* value);
        Symbol(const std::string& name, std::string* value, int count);
        // game objects
        // Constructor for individual GameObjectType1 objects
        Symbol(const std::string &name, Circle *game_object);
        Symbol(const std::string &name, Circle *game_object, int count);
        Symbol(const std::string &name, Rectangle *game_object);
        Symbol(const std::string &name, Rectangle *game_object, int count);
        Symbol(const std::string &name, Textbox *game_object);
        Symbol(const std::string &name, Textbox *game_object, int count);
        Symbol(const std::string &name, Triangle *game_object);
        Symbol(const std::string &name, Triangle *game_object, int count);
        Symbol(const std::string &name, Pixmap *game_object);
        Symbol(const std::string &name, Pixmap *game_object, int count);
        Symbol(const std::string &name, Animation_code *game_object);

        
        GPL::Type get_type() const;
        std::string get_name() const;
        Game_object*  as_game_object();
        virtual ~Symbol();
        friend std::ostream& operator<<(std::ostream& os, const Symbol& sym);
        Symbol(const Symbol&) = delete;
        Symbol& operator=(const Symbol&) = delete;
        int get_count() const;
        //↓here?
        const Constant* as_constant() const;          //Symbol value is not an array
        const Constant* as_constant(int index) const; //Symbol value is an array
        const Constant* as_constant(const std::string& attribute_name) const; // non-arrays
        const Constant* as_constant(int index, const std::string& attribute_name) const; // arrays

        //non-array: int, double, or string
        std::shared_ptr<Locator> as_lvalue() const;

        //array element: int, double, or string
        std::shared_ptr<Locator> as_lvalue(int index) const;

        // //non-array: game object
        std::shared_ptr<Locator> as_lvalue(const std::string& attribute_name) const;

        // //array element: game object
        std::shared_ptr<Locator> as_lvalue(int index, const std::string& attribute_name) const;


        

    private:
        GPL::Type type_;
        std::string name_;
        symboltype value_;
        int count_;
};

#endif