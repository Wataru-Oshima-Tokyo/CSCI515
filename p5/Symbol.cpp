#include "Symbol.h"
#include "Constant.h"
#include "Game_object.h"
#include "Game_attribute_constant.h"

Symbol::Symbol(const std::string& name, double* value) : 
    type_{ GPL::Type::DOUBLE }, name_{ name }, value_{ symboltype(value) }, count_{ 0 } {}

Symbol::Symbol(const std::string& name, double* value, int count) :
    type_{ GPL::Type::DOUBLE }, name_{ name }, value_{ symboltype(value) }, count_{ count } {}

Symbol::Symbol(const std::string& name, int* value) :
    type_{ GPL::Type::INT }, name_{ name }, value_{ symboltype(value)  }, count_{ 0 } {}

Symbol::Symbol(const std::string& name, int* value, int count) :
    type_{ GPL::Type::INT }, name_{ name }, value_{ symboltype(value)  }, count_{ count } {}

Symbol::Symbol(const std::string& name, std::string* value) :
    type_{ GPL::Type::STRING }, name_{ name }, value_{ symboltype(value) }, count_{ 0 } {}

Symbol::Symbol(const std::string& name, std::string* value, int count) :
    type_{ GPL::Type::STRING }, name_{ name }, value_{ symboltype(value)  }, count_{ count } {}


Symbol::Symbol(const std::string &name, Circle *game_object) :
     type_{GPL::Type::CIRCLE}, name_{name},value_{symboltype(game_object)}, count_{ 0 } {}

Symbol::Symbol(const std::string &name, Circle *game_object, int count) :
     type_{GPL::Type::CIRCLE}, name_{name},value_{symboltype(game_object)}, count_{ count } {}


Symbol::Symbol(const std::string &name, Rectangle *game_object) :
     type_{GPL::Type::RECTANGLE}, name_{name},value_{symboltype(game_object)}, count_{ 0 } {}

Symbol::Symbol(const std::string &name, Rectangle *game_object, int count) :
     type_{GPL::Type::RECTANGLE}, name_{name},value_{symboltype(game_object)}, count_{ count } {}

Symbol::Symbol(const std::string &name, Textbox *game_object) :
     type_{GPL::Type::TEXTBOX}, name_{name},value_{symboltype(game_object)}, count_{ 0 } {}

Symbol::Symbol(const std::string &name, Textbox *game_object, int count) :
     type_{GPL::Type::TEXTBOX}, name_{name},value_{symboltype(game_object)}, count_{ count } {}

Symbol::Symbol(const std::string &name, Triangle *game_object) :
     type_{GPL::Type::TRIANGLE}, name_{name},value_{symboltype(game_object)}, count_{ 0 } {}

Symbol::Symbol(const std::string &name, Triangle *game_object, int count) :
     type_{GPL::Type::TRIANGLE}, name_{name},value_{symboltype(game_object)}, count_{ count } {}

Symbol::Symbol(const std::string &name, Pixmap *game_object) :
     type_{GPL::Type::PIXMAP}, name_{name},value_{symboltype(game_object)}, count_{ 0 } {}

Symbol::Symbol(const std::string &name, Pixmap *game_object, int count) :
     type_{GPL::Type::PIXMAP}, name_{name},value_{symboltype(game_object)}, count_{ count } {}





GPL::Type Symbol::get_type() const {
    return type_;
}

std::string Symbol::get_name() const {
    return name_;
}

int Symbol::get_count() const{
    return count_;
}

Game_object* Symbol::as_game_object() {
    if (type_ == GPL::CIRCLE) {
        return value_.circle_pointer;
    } else if (type_ == GPL::RECTANGLE) {
        return value_.rectangle_pointer;
    } else if (type_ == GPL::TEXTBOX) {
        return value_.textbox_pointer;
    } else if (type_ == GPL::TRIANGLE) {
        return value_.triangle_pointer;
    } else if (type_ == GPL::PIXMAP) {
        return value_.pixmap_pointer;
    } else {
        // Throw an exception or return nullptr if the type is not a game object
        return nullptr;
    }
}

Symbol::~Symbol() {
    switch (type_) {
        case GPL::Type::DOUBLE:
            if (count_ == 0) {
                delete value_.double_pointer;
            }
            else {
                delete[] value_.double_pointer;
            }
            break;
        case GPL::Type::INT:
            if (count_ == 0) {
                delete value_.int_pointer;
            }
            else {
                delete[] value_.int_pointer;
            }
            break;
        case GPL::Type::STRING:
            if (count_ == 0) {
                delete value_.string_pointer;
            }
            else {
                delete[] value_.string_pointer;
            }
            break;
        case GPL::Type::CIRCLE:
            if (count_ == 0) {
                delete value_.circle_pointer;
            }
            else {
                delete[] value_.circle_pointer;
            }
            break;
        case GPL::Type::RECTANGLE:
            if (count_ == 0) {
                delete value_.rectangle_pointer;
            }
            else {
                delete[] value_.rectangle_pointer;
            }
            break;
        case GPL::Type::TRIANGLE:
            if (count_ == 0) {
                delete value_.triangle_pointer;
            }
            else {
                delete[] value_.triangle_pointer;
            }
            break;
        case GPL::Type::PIXMAP:
            if (count_ == 0) {
                delete value_.pixmap_pointer;
            }
            else {
                delete[] value_.pixmap_pointer;
            }
            break;
        case GPL::Type::TEXTBOX:
            if (count_ == 0) {
                delete value_.textbox_pointer;
            }
            else {
                delete[] value_.textbox_pointer;
            }
            break;
       
        default:
         assert(false);
            break;
    }
}

std::ostream& operator<<(std::ostream& os, const Symbol& sym) {
    switch (sym.get_type()) {
        case GPL::Type::DOUBLE: 
            
            if (sym.count_ == 0) {
                os << "double " << sym.get_name() << " = ";
                os << *sym.value_.double_pointer;
            }
            else {
                for (int i = 0; i < sym.count_; ++i) {
                    os << "double "  << sym.get_name() << "[" << i << "]" <<" = "
                    << sym.value_.double_pointer[i];
                    if (i != sym.count_-1){
                        os <<std::endl;
                    }
                }
            }
            break;
        case GPL::Type::INT: 
            
            if (sym.count_ == 0) {
                os << "int " << sym.get_name() << " = ";
                os << *sym.value_.int_pointer;
            }
            else {

                for (int i = 0; i < sym.count_; ++i) {
                    os << "int "  << sym.get_name() << "[" << i << "]" <<" = "
                    << sym.value_.int_pointer[i];
                    if (i != sym.count_-1){
                        os <<std::endl;
                    }
                }
            }
            break;
        case GPL::Type::STRING: 
            
            if (sym.count_ == 0) {
                os << "string " << sym.get_name();
                os << " = " << "\"";
                os << *sym.value_.string_pointer << "\"";
            }
            else {
                for (int i = 0; i < sym.count_; ++i) {
                    os << "string "  << sym.get_name() << "[" << i << "]" <<" = "
                    << "\"" <<sym.value_.string_pointer[i] << "\"";
                    if (i != sym.count_-1){
                        os <<std::endl;
                    }
                }
            }
            break;

        case GPL::Type::CIRCLE: 
            
            if (sym.count_ == 0) {
                os << "circle " << sym.get_name() << *sym.value_.circle_pointer;
            }
            else {
                for (int i = 0; i < sym.count_; ++i) {
                    os << "circle "  << sym.get_name() << "[" << i << "]" << sym.value_.circle_pointer[i];
                    if (i != sym.count_-1){
                        os <<std::endl;
                    }
                }
            }
            break;

        case GPL::Type::RECTANGLE: 
            if (sym.count_ == 0) {
                os << "rectangle " << sym.get_name() << *sym.value_.rectangle_pointer;
            } else {
                for (int i = 0; i < sym.count_; ++i) {
                os << "rectangle " << sym.get_name() << "[" << i << "]" << sym.value_.rectangle_pointer[i];
                    if (i != sym.count_ - 1) {
                        os << std::endl;
                    }
                }
       
            }
         break;

        case GPL::Type::TRIANGLE: 
            if (sym.count_ == 0) {
                os << "triangle " << sym.get_name() << *sym.value_.triangle_pointer;
            } else {
                for (int i = 0; i < sym.count_; ++i) {
                os << "triangle " << sym.get_name() << "[" << i << "]" << sym.value_.triangle_pointer[i];
                    if (i != sym.count_ - 1) {
                        os << std::endl;
                    }
                }
       
            }
         break;

        case GPL::Type::PIXMAP: 
            if (sym.count_ == 0) {
                os << "pixmap " << sym.get_name() << *sym.value_.pixmap_pointer;
            } else {
                for (int i = 0; i < sym.count_; ++i) {
                os << "pixmap " << sym.get_name() << "[" << i << "]" << sym.value_.pixmap_pointer[i];
                    if (i != sym.count_ - 1) {
                        os << std::endl;
                    }
                }
       
            }
         break;

        case GPL::Type::TEXTBOX: 
            if (sym.count_ == 0) {
                os << "textbox " << sym.get_name() << *sym.value_.textbox_pointer;
            } else {
                for (int i = 0; i < sym.count_; ++i) {
                os << "textbox " << sym.get_name() << "[" << i << "]" << sym.value_.textbox_pointer[i];
                    if (i != sym.count_ - 1) {
                        os << std::endl;
                    }
                }
       
            }
         break;





    default:
        assert(false);
        break;
    }
    
    os << std::endl;
    return os;
}
const Constant* Symbol::as_constant() const {
    switch (type_) {
        case GPL::Type::INT:
            return new Integer_constant(*value_.int_pointer);
        case GPL::Type::DOUBLE:
            return new Double_constant(*value_.double_pointer);
        case GPL::Type::STRING:
            return new String_constant(*value_.string_pointer);
        default:
            throw type_;
    }
}

const Constant* Symbol::as_constant(int index) const {
    if (index < 0 || index >= count_) {
        return nullptr;
    }
    //ToDo: I need to change for array
    switch (type_) {
        case GPL::Type::INT:
            return new Integer_constant(value_.int_pointer[index]);
        case GPL::Type::DOUBLE:
            return new Double_constant(value_.double_pointer[index]);
        case GPL::Type::STRING:
            return new String_constant(value_.string_pointer[index]);
        default:
            throw type_;
    }
}

const Constant* Symbol::as_constant(const std::string& attribute_name) const {
    switch (type_) {
        case GPL::CIRCLE:
            // Retrieve attribute from Circle object
            return new Game_attribute_constant(value_.circle_pointer, attribute_name);
        case GPL::RECTANGLE:
            // Retrieve attribute from Rectangle object
            return new Game_attribute_constant(value_.rectangle_pointer, attribute_name);
        case GPL::TEXTBOX:
            // Retrieve attribute from Textbox object
            return new Game_attribute_constant(value_.textbox_pointer, attribute_name);
        case GPL::TRIANGLE:
            // Retrieve attribute from Triangle object
            return new Game_attribute_constant(value_.triangle_pointer, attribute_name);
        case GPL::PIXMAP:
            // Retrieve attribute from Pixmap object
            return new Game_attribute_constant(value_.pixmap_pointer, attribute_name);
        default:
            throw type_;
    }
    return nullptr; // Replace with the appropriate Constant object
}

const Constant* Symbol::as_constant(int index, const std::string& attribute_name) const {
    if (index < 0 || index >= count_) {
        return nullptr;
    }
    //ToDo: I need to change for array
    switch (type_) {
        case GPL::CIRCLE:
            // Retrieve attribute from Circle object
            return new Game_attribute_constant(&value_.circle_pointer[index], attribute_name);
        case GPL::RECTANGLE:
            // Retrieve attribute from Rectangle object
            return new Game_attribute_constant(&value_.rectangle_pointer[index], attribute_name);
        case GPL::TEXTBOX:
            // Retrieve attribute from Textbox object
            return new Game_attribute_constant(&value_.textbox_pointer[index], attribute_name);
        case GPL::TRIANGLE:
            // Retrieve attribute from Triangle object
            return new Game_attribute_constant(&value_.triangle_pointer[index], attribute_name);
        case GPL::PIXMAP:
            // Retrieve attribute from Pixmap object
            return new Game_attribute_constant(&value_.pixmap_pointer[index], attribute_name);
        default:
            throw type_;
    }
    return nullptr; // Replace with the appropriate Constant object
}

// Non-array: int, double, or string
std::shared_ptr<Locator> Symbol::as_lvalue() const {
    switch (type_) {
        case GPL::INT:
            return std::make_shared<Integer_locator>(*value_.int_pointer);
        case GPL::DOUBLE:
            return std::make_shared<Double_locator>(*value_.double_pointer);
        case GPL::STRING:
            return std::make_shared<String_locator>(*value_.string_pointer);
        default:
            throw type_;       
    }
    return nullptr;
}

// Array element: int, double, or string
std::shared_ptr<Locator> Symbol::as_lvalue(int index) const {
    if (index < 0 || index >= count_) {
        return nullptr;
    }
    switch (type_) {
        case GPL::INT:
            return std::make_shared<Integer_locator>(value_.int_pointer[index]);
        case GPL::DOUBLE:
            return std::make_shared<Double_locator>(value_.double_pointer[index]);
        case GPL::STRING:
            return std::make_shared<String_locator>(value_.string_pointer[index]);
        default:
            throw type_;  
            
    }
    return nullptr;
}


// Non-array: game object
std::shared_ptr<Locator> Symbol::as_lvalue(const std::string& attribute_name) const {

    switch (type_) {
        case GPL::CIRCLE:
            // Retrieve attribute from Circle object
            return std::make_shared<Game_attribute_locator>(value_.circle_pointer, attribute_name);
        case GPL::RECTANGLE:
            // Retrieve attribute from Rectangle object
            return std::make_shared<Game_attribute_locator>(value_.rectangle_pointer, attribute_name);
        case GPL::TEXTBOX:
            // Retrieve attribute from Textbox object
            return std::make_shared<Game_attribute_locator>(value_.textbox_pointer, attribute_name);
        case GPL::TRIANGLE:
            // Retrieve attribute from Triangle object
            return std::make_shared<Game_attribute_locator>(value_.triangle_pointer, attribute_name);
        case GPL::PIXMAP:
            // Retrieve attribute from Pixmap object
            return std::make_shared<Game_attribute_locator>(value_.pixmap_pointer, attribute_name);
        default:
            throw type_;
    }
    return nullptr; // Replace with the appropriate Constant object
}

// Array element: game object
std::shared_ptr<Locator> Symbol::as_lvalue(int index, const std::string& attribute_name) const {
    if (index < 0 || index >= count_) {
        return nullptr;
    }
    //ToDo: I need to change for array
    switch (type_) {
        case GPL::CIRCLE:
            // Retrieve attribute from Circle object
            return std::make_shared<Game_attribute_locator>(&value_.circle_pointer[index], attribute_name);
        case GPL::RECTANGLE:
            // Retrieve attribute from Rectangle object
            return std::make_shared<Game_attribute_locator>(&value_.rectangle_pointer[index], attribute_name);
        case GPL::TEXTBOX:
            // Retrieve attribute from Textbox object
            return std::make_shared<Game_attribute_locator>(&value_.textbox_pointer[index], attribute_name);
        case GPL::TRIANGLE:
            // Retrieve attribute from Triangle object
            return std::make_shared<Game_attribute_locator>(&value_.triangle_pointer[index], attribute_name);
        case GPL::PIXMAP:
            // Retrieve attribute from Pixmap object
            return std::make_shared<Game_attribute_locator>(&value_.pixmap_pointer[index], attribute_name);
        default:
            throw type_;
    }
    return nullptr; // Replace with the appropriate Constant object
}