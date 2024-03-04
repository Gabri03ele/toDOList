#include <iostream>
#include <cstdlib>
#include <list>
#include <fstream>
#include <string>

#include "toDo.hpp"

int main(void)
{
    std::list<toDo> toDos;
    char op;
    int idComplete;
    int idModify;
    std::string descrizione;
    const std::string filepath = "/Users/gabrielearmani/ToDoList/datiSalvati.txt";

    while (true)
    {
        // system("clear");

        std::cout << "Ecco cosa devi fare: " << std::endl
                  << std::endl;

        // Se vuota non stampa nulla
        if (toDos.empty())
        {
            std::cout << "Non hai niente da fare per ora :)" << std::endl;
        }

        // Altrimenti stampa la lista
        auto it = toDos.begin();
        while (it != toDos.end())
        {
            std::string completo = it->is_completed() ? "fatto" : "da fare";
            int id = it->get_id();
            std::string desc = it->get_string();
            std::cout << id << ") " << desc << ", " << completo << std::endl
                      << std::endl;
            ++it;
        }

        std::cout << std::endl;

        std::cout << "(A)ggiungi un toDo" << std::endl;
        std::cout << "(C)ompleta un toDo" << std::endl;
        std::cout << "(M)odifica un toDo" << std::endl;
        std::cout << "(E)sci" << std::endl
                  << std::endl;

        while (true)
        {
            std::cout << "Cosa vuoi fare (A, C, M, E): ";
            std::cin >> op;

            if (std::cin.fail() || std::cin.peek() != '\n')
            {
                std::cout << "Inserisci un carattere valido" << std::endl
                          << std::endl;

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else
            {
                break;
            }
        }

        op = std::toupper(op);

        std::cout << std::endl;
        if (op == 'A')
        {
            while (true)
            {
                std::cout << "Cosa devi fare: ";

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, descrizione);

                if (!descrizione.empty())
                {
                    toDo nuovo;
                    nuovo.set_string(descrizione);
                    toDos.push_back(nuovo);
                    break;
                }
                else
                {
                    std::cout << "Inserisci 2 o più caratteri" << std::endl
                              << std::endl;
                }
            }
        }
        else if (op == 'C')
        {
            while (true)
            {
                if (toDos.empty())
                {
                    std::cout << "Inserisci prima qualcosa da fare" << std::endl;
                    break;
                }
                std::cout << "Inserisci l'id del ToDo da completare: ";
                std::cin >> idComplete;

                if (std::cin.fail())
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Inserisci un numero valido" << std::endl
                              << std::endl;
                }
                else
                {
                    auto iter = toDos.begin();
                    bool found = false;
                    while (iter != toDos.end() && !found)
                    {
                        if (iter->get_id() == idComplete)
                        {
                            iter->set_completed();
                            found = true;
                        }
                        ++iter;
                    }
                    if (found)
                    {
                        break;
                    }
                    else
                    {
                        std::cout << "L'id che hai inserito non esiste :( " << std::endl
                                  << std::endl;
                    }
                }
            }
        }
        else if (op == 'M')
        {
            while (true)
            {
                if (toDos.empty())
                {
                    std::cout << "Inserisci prima qualcosa da fare" << std::endl;
                    break;
                }

                std::cout << "Inserisci l'id del ToDo da modificare: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin >> idModify;

                if (std::cin.fail())
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Inserisci un numero valido" << std::endl
                              << std::endl;
                }
                else
                {
                    auto iter = toDos.begin();
                    bool found = false;
                    while (!found && iter != toDos.end())
                    {
                        if (iter->get_id() == idModify)
                        {
                            while (true)
                            {
                                std::string newDesc = "";
                                std::cout << "Inserisci la nuova descrizione: ";

                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                std::getline(std::cin, newDesc);

                                iter->set_new_string(newDesc);

                                if (!newDesc.empty())
                                {
                                    break;
                                }
                                else
                                {
                                    std::cout << "Inserisci 2 o più caratteri" << std::endl;
                                }
                            }
                            found = true;
                        }
                        ++iter;
                    }

                    if (found)
                    {
                        break;
                    }
                    else
                    {
                        std::cout << "L'id che hai inserito non esiste :( " << std::endl
                                  << std::endl;
                    }
                }
            }
        }
        else if (op == 'E')
        {
            std::cout << "A dopo! " << std::endl
                      << std::endl;
            break;
        }
        else
        {
            std::cout << "Inserisci un input valido ";
        }
    }
    return 0;
}
