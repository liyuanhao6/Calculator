#include "Controleur.h"

int main() {
    try {
        Controleur& controleur = Controleur::getInstance();
        controleur.executer();
    } catch (...) {

    }
    return 0;

}