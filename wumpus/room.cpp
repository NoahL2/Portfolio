#include "room.hpp"

// TODO Room implementation (define room member functions below)

Room::Room(const Room& other){
    this->room_event = other.room_event;

}

Room& Room::operator= (const Room& other){
    if (this == &other){
        return *this;
    }

    this->room_event = other.room_event;
    return *this;
}

bool Room::room_is_empty(){
    if (this->room_event == nullptr){
        return true;
    }
    return false;
}

void Room::print()const{
    room_event->print();
}

void Room::percept()const{
    room_event->percept();
}

void Room::set_event(event* e){

    // Sets the event pointer to an event
    this->room_event = e;
}

event* Room::get_event()const{
    return this->room_event;
}

Room::~Room(){

    if (this->room_event != nullptr){
        // Deletes the event the pointer is pointing to
        delete this->room_event;
        
    }

    // sets the event pointer back to null
    this->room_event = nullptr;
}

