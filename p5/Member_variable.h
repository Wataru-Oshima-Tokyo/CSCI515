#include "Variable.h"
#include <memory>
#include <string>
class Member_variable : public Variable {
public:
    Member_variable(const std::string &name, const std::string &attribute_name);
    Member_variable(const std::string &name, const Expression *index_expression, const std::string &attribute_name);

    virtual const Constant *evaluate() const override;
    virtual std::shared_ptr<Locator> modify() const ;
    virtual GPL::Type type() const override;

private:
    std::string attribute_name_;
};