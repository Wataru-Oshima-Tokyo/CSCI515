#ifndef GAME_ATTRIBUTE_CONSTANT_H
#define GAME_ATTRIBUTE_CONSTANT_H



#include "Constant.h"
#include "Game_object.h"
#include "error.h"

class Game_attribute_constant : public Constant {
  public:
    Game_attribute_constant(const Game_object* gop, const std::string& attribute_name)
      : Constant(gop->attribute_type(attribute_name)),
        gop(gop),
        attribute_name(attribute_name) {}

    virtual int           as_int()         const;
    virtual double        as_double()      const;
    virtual std::string   as_string()      const;

  private:
    const Game_object* gop;
    std::string attribute_name;
};



#endif 

