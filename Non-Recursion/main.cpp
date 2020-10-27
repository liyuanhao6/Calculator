#include "computer.h"
int main() {
    Pile expAff;
    Controleur controleur(expAff);
    expAff.setMessage("Bienvenue");
    controleur.executer();
    return 0;
}