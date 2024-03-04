#ifndef toDo_hpp
#define toDo_hpp

#include <iostream>
#include <stdio.h>
#include <string>
#include <limits>
#include <assert.h>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>

struct toDo_exception
{
    std::string msg;
};

class toDo
{
public:
    toDo();
    toDo(toDo const &);
    toDo(toDo &&);
    ~toDo();

    toDo &operator=(toDo const &);
    toDo &operator=(toDo &&);

    bool is_completed() const;

    int &get_id();
    int const &get_id() const;

    std::string &get_string();
    std::string const &get_string() const;

    void set_string(std::string const &);
    void set_new_string(std::string const &);
    void set_completed();
    void clearScreen();
    void leggiFile(const std::string &filepath);
    void scriviFile(const std::string &filepath);

private:
    struct impl;
    impl *pimpl;
};

#endif
