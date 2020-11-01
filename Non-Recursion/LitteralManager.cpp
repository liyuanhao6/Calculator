//
// Created by 黎袁昊 on 2020/10/28.
//

#include "LitteralManager.h"

LitteraleManager *LitteraleManager::instance = nullptr;

LitteraleManager &LitteraleManager::getInstance() {
    if (instance == nullptr) instance = new LitteraleManager;
    return *instance;
}

void LitteraleManager::destroyInstance() {
    delete instance;
    instance = nullptr;
}

Litterale *LitteraleManager::addLitterale(Litterale *l) {
    litterales.push_back(l);
    return l;
}

void LitteraleManager::removeLitterale(Litterale *l) {
    auto it = find(this->litterales.begin(), this->litterales.end(), l);
    if (it == this->litterales.end()) {
        throw ComputerException("L'élément à supprimer n'exisite pas!");
    } else {
        this->litterales.erase(it);
    }
}
