module gameobjectcomponent;

import textstatus;
import eventqueue;
import <vector>;
import <memory>;
import <algorithm>;
import <string>;

GameObject::GameObject(std::string name): name{name} {}

void GameObject::destroy(){
    destroyed=true;
}

bool GameObject::isDestroyed(){
    return destroyed;
}

int GameObject::getLifetime(){
    return lifetime;
}

void GameObject::setTextStatus(TextStatus *textStatus){
    this->textStatus = textStatus;
}

void GameObject::setEventQueue(EventQueue *eventQueue){
    this->eventQueue = eventQueue;
}

void GameObject::setLifetime(int lifetime){
    this->lifetime = lifetime;
}

void GameObject::resetLifetime(){
    this->lifetime = baseLifetime;
}

std::unique_ptr<GameObject> GameObject::clone() const{
    std::unique_ptr<GameObject> copy = std::make_unique<GameObject>(name);
    for(const auto &component : components){
        copy->addComponent(component->clone());
    }
    return copy;
}

void GameObject::print(int line, const std::string &msg){
    textStatus->setLine(line, msg);
}

void GameObject::emit(const std::string &event){
    eventQueue->pushEvent(event);
}

void GameObject::addComponent(std::unique_ptr<Component> component){
    component->gameObject = this;
    components.push_back(std::move(component));
}

void GameObject::removeComponent(Component *component){
    components.erase(std::find_if(components.begin(), components.end(), [component](const std::unique_ptr<Component> &other){return component == other.get();}));
}

void GameObject::update(){}

void Component::setActive(bool active){ this->active = active; }

bool Component::isActive(){ return active; }
