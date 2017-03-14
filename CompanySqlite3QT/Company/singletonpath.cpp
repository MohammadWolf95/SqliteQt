#include "singletonpath.h"

Singletonpath * Singletonpath::p_instance = 0;
SingletonpathDestroyer Singletonpath::destroyer;

SingletonpathDestroyer::~SingletonpathDestroyer() {
    delete p_instance;
}
void SingletonpathDestroyer::initialize( Singletonpath* p ) {
    p_instance = p;
}
Singletonpath& Singletonpath::getInstance() {
    if(!p_instance)     {
        p_instance = new Singletonpath();
        destroyer.initialize( p_instance);
    }
    return *p_instance;
}
