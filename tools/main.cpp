#include <iostream>
#include <cstdlib>

#include "toDo.hpp"
#include "toDo.cpp"


int main(int argc, const char * argv[]) {
    toDo toDos;
    char op;
    int idComplete;
    std::string descrizione;
    
    while(true) {
        clearScreen();
        std::cout<< "La tua lista delle cose da fare:"<<std::endl<<std::endl;
        
        auto it = toDos.begin_list();
        while(it) {
            std::string completo = it->is_completed() ? "fatto" : "non ancora fatto";
            int id = it->get_id();
            std::string desc = it->get_string();
            std::cout<< id << ") " << desc << ", " << completo <<std::endl<<std::endl;
            ++it;
        }
        
        if(toDos.isEmpty()) {
            std::cout<< "Non hai niente da fare per ora :)" <<std::endl;
            std::cout<<std::endl;
        }
        
        std::cout<< "Cosa vuoi fare? "<<std::endl;
        
        std::cout<< "(A)ggiungi un nuovo toDo" <<std::endl;
        std::cout<< "(C)ompleta un tuo toDo" <<std::endl;
        std::cout<< "(E)sci" <<std::endl<<std::endl;
        
        while (true) {
            std::cout << "Inserisci la tua scelta (A, C, E): ";
            std::cin >> op;

            if (std::cin.fail() || std::cin.peek() != '\n') {
                std::cout<< "Input non valido, inserisci solo un carattere" <<std::endl<<std::endl;

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                break;
            }
        }
        
        if (std::islower(op)) {
            op = std::toupper(op);
        }
        
        std::cout<<std::endl;
        if(op == 'A') {
            while(true) {
                std::cout<< "Dimmi il tuo impegno: ";
                
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, descrizione);
                
                toDo nuovo;
                nuovo.set_string(descrizione);
                
                if(!descrizione.empty()) {
                    toDos.push_back(nuovo);
                    break;
                } else {
                    std::cout<< "Input non valido, inserisci più caratteri" <<std::endl<<std::endl;
                }
            }
        } else if(op == 'C') {
            while (true) {
                if(toDos.isEmpty()) {
                    std::cout<< "Inserisci prima qualcosa da fare" <<std::endl;
                    break;
                }
                std::cout << "Dimmi l'id dell'impegno che hai completato: ";
                std::cin >> idComplete;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Inserisci un numero valido" << std::endl<<std::endl;
                } else {
                    auto iter = toDos.begin_list();
                    bool found = false;
                    while (iter && !found) {
                        if (iter->get_id() == idComplete) {
                            iter->set_completed();
                            found = true;
                        }
                        ++iter;
                    }
                    if (found) {
                        break;
                    } else {
                        std::cout << "L'id che hai inserito non esiste :( " << std::endl<<std::endl;
                    }
                }
            }
        } else if(op == 'E') {
            std::cout<< "A dopo! " <<std::endl<<std::endl;
            break;
        } else {
            std::cout<< "Inserisci un input valido ";
        }
    }
    return 0;
}
