#include "Controleur.h"

int main() {
    Controleur& controleur = Controleur::getInstance();
    controleur.executer();
    return 0;

}