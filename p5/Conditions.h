#ifndef CONDITIONS_HPP
#define CONDITIONS_HPP

#include "Statement.h"
#include "Constant.h"
#include <iostream>

class If : public Statement {
public:
    If(const Expression *condition, Statement *if_clause, Statement *else_clause = nullptr)
        : m_condition(condition), m_if_clause(if_clause), m_else_clause(else_clause) {}

    void execute() const override {
        const Constant *result = m_condition->evaluate();
        if (result->as_int()) {
            m_if_clause->execute();
        } else if (m_else_clause) {
            m_else_clause->execute();
        }
        if (next != nullptr) {
            next->execute();
        }
    }

private:
    const Expression *m_condition;
    Statement *m_if_clause;
    Statement *m_else_clause;
};

class For : public Statement {
public:
    For(Statement *initializer, const Expression *condition, Statement *incrementor, Statement *body)
        : m_initializer(initializer), m_condition(condition), m_incrementor(incrementor), m_body(body) {}

    void execute() const override {
        if (m_initializer) {
            m_initializer->execute();
        }
        while (m_condition->evaluate()->as_int()) {
            m_body->execute();
            if (m_incrementor) {
                m_incrementor->execute();
            }
        }
        if (next != nullptr) {
            next->execute();
        }
    }

private:
    Statement *m_initializer;
    const Expression *m_condition;
    Statement *m_incrementor;
    Statement *m_body;
};

class Exit : public Statement {
public:
    Exit(int line_number, const Expression *status) : m_line_number(line_number), m_status(status) {}

    void execute() const override {
        int exit_status = m_status->evaluate()->as_int();
        std::cout << "gpl[" << m_line_number << "]: exit(" << exit_status << ")"<<std::endl;
        exit(exit_status);
        
    }

private:
    int m_line_number;
    const Expression *m_status;
};

#endif