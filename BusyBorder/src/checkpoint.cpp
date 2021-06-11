#include "checkpoint.h"
#include "helperFunctions.h"

Checkpoint::Checkpoint(){
    this->priorityFree = true;
    this->quarantinePerson = new Person();
    this->activePerson = new Person();
}

void Checkpoint::drawCheckpoint(int personID, Person* p){
    std::string ic =  p->state == START_CONTROL? std::to_string(p->getId()) : "#";
    std::string hc =  p->state == HEALTH_CONTROL? std::to_string(p->getId()) : "#";
    std::string id_c =  p->state == ID_CONTROL? std::to_string(p->getId()) : "#";
    char qa = quarantineIDs.size() > 0? 'P' : '#';
    mvwprintw(mainwin,1 + 3*id,1,"IC  HC  QA  ID");
    mvwprintw(mainwin,2 + 3*id,1,"");
    mvwprintw(mainwin,2 + 3*id,1,"%s  %s  %c  %s", ic.c_str(), hc.c_str(), qa, id_c.c_str());
    wrefresh(mainwin);
    refresh();
}

void Checkpoint::addToQuarantine(int id){
    quarantineIDs.push_back(id);
}

void Checkpoint::removeFromQuarantine(int id){
    int index = -1;
    for(int i = 0; i < this->quarantineIDs.size(); i++){
        if(quarantineIDs[i] == id){
            index = i;
            break;
        }
    }
    if(index != -1) 
        quarantineIDs.erase(quarantineIDs.begin() + index);
}