#include "toDo.hpp"
#include <cstdlib>

struct Cella
{
    toDo info;
    Cella *next;
    Cella *prev;
};
typedef Cella *PCella;

struct toDo::impl
{
    std::string str;
    int id;
    bool completed;
};

void toDo::clearScreen()
{
    std::system("clear");
}

toDo::toDo()
{
    pimpl = new impl;

    pimpl->str = "";
    pimpl->id = 0;
    pimpl->completed = false;
}

toDo::toDo(toDo const &val) : toDo()
{
    pimpl->str = val.pimpl->str;
    pimpl->id = val.pimpl->id;
    pimpl->completed = val.pimpl->completed;
}

toDo::toDo(toDo &&val) : toDo()
{
    pimpl->str = val.pimpl->str;
    pimpl->id = val.pimpl->id;
    pimpl->completed = val.pimpl->completed;
}

toDo::~toDo()
{
    delete pimpl;
}

toDo &toDo::operator=(toDo const &val)
{
    if (this != &val)
    {
        pimpl->id = val.pimpl->id;
        pimpl->str = val.pimpl->str;
        pimpl->completed = val.pimpl->completed;
    }
    return *this;
}

toDo &toDo::operator=(toDo &&val)
{
    if (this != &val)
    {
        pimpl->id = val.pimpl->id;
        pimpl->str = val.pimpl->str;
        pimpl->completed = val.pimpl->completed;
    }
    return *this;
}

bool toDo::is_completed() const
{
    return pimpl->completed;
}

int &toDo::get_id()
{
    return pimpl->id;
}

int const &toDo::get_id() const
{
    return pimpl->id;
}

std::string &toDo::get_string()
{
    return pimpl->str;
}

std::string const &toDo::get_string() const
{
    return pimpl->str;
}

void toDo::set_string(std::string const &str)
{
    static int uniqueID = 0;
    pimpl->id = ++uniqueID;

    pimpl->str = str;
    pimpl->completed = false;
}

void toDo::set_new_string(std::string const &str)
{
    pimpl->str = str;
    pimpl->completed = false;
}

void toDo::set_completed()
{
    if (pimpl->completed == false)
    {
        pimpl->completed = true;
    }
    else
    {
        pimpl->completed = false;
    }
}

void toDo::leggiFile(const std::string &filepath)
{
    std::ifstream file(filepath);

    if (!file.is_open())
    {
        std::cerr << "Errore durante l'apertura per la lettura: " << filepath << std::endl;
        return;
    }

    std::string line;
    std::cout << "La tua lista:" << std::endl;

    while (std::getline(file, line))
    {
        std::cout << line << std::endl;
    }

    file.close();
}

void toDo::scriviFile(const std::string &filepath)
{
    std::ofstream myfile(filepath, std::ios::app);

    if (!myfile.is_open())
    {
        std::cerr << "Errore durante l'apertura per la scrittura" << std::endl;
        return;
    }

    std::string input;
    std::cout << "Inserisci il testo (chiudi con una riga vuota): " << std::endl;

    while (true)
    {
        std::getline(std::cin, input);

        if (input.empty())
            break;

        myfile << input << std::endl;
    }

    myfile.close();
}