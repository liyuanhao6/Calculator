#include "Controleur.h"

int main() {
    std::vector<Litterale *> lirAff;
    Controleur controleur(lirAff);
    controleur.executer();
//    lirAff.push_back(toRationnelle(1));
//    lirAff.push_back(toRationnelle(1.4));
//    lirAff.push_back(LitteraleFraction::getPointeur(LitteraleFraction(1,2)));
//    std::cout << lirAff[0]->toString() << std::endl;
//    std::cout << lirAff[1]->toString() << std::endl;
//    std::cout << lirAff[2]->toString() << std::endl;
    return 0;
}