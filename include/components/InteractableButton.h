#ifndef INTERACTABLEBUTTON_H_INCLUDED
#define INTERACTABLEBUTTON_H_INCLUDED
#include "IComponent.h"
#include "Sigma.h"
/*
Low-level data is the smallest atomic data that
you handle and must be put in containers in
"component" dir (I think Adam has renamed or
will rename the folder) with the low-level code
on the data. The container hosted is something
like std::unordered_map, and code is merely
create, read, update and delete. the low-level
data are "states" that you must keep between
each frame.
(create,read,update,delete)*/
// keep in COMPONENT folder - will be the low-level data object definition 
namespace Sigma {
    struct statedetail{ int nextstate; };
    //the details for a interactable entity in the form of a button push slide etc.
    class InteractableButton : public IComponent { //REMOVED:: public IFactory  ,
    public:
        void simplecreate(id_t EntityID, float radius, int defaultstate, std::map<int, statedetail> statelist){
            this->EntityID = EntityID;
            this->radius = radius;
            ActiveState[EntityID] = defaultstate;
            this->StateList = statelist;
            LOG_ERROR << "creating an interactable button";
        }
        float GetRadius(){ return this->radius; }
        int GetState(){ return ActiveState[this->EntityID]; }
        //should only be called during an update.
        void SetToNextState(){ ActiveState[this->EntityID] = this->StateList[this->ActiveState[EntityID]].nextstate; }
        SET_COMPONENT_TYPENAME("InteractableButton"); //this :new InteractableButton(); wont work without it.
    protected:
    private:
        static std::map<id_t, int> ActiveState; //maps the Default state to the [entity ID]
        std::map<int, statedetail> StateList;  // map State ID to statedetails
        id_t EntityID;
        int validstate;         //the state the interactible would be valid for for this entity checked using 'CurrentStates[]'
        float radius;           //maximum range between the entity PhysicalWorldLocation to the player avitar.
        int selectsize;         //SIZE OF SELECT box to use when running the select pass
        //avitar actions:
        /*
        Push Button
        Turn Handle
        Pull Cable
        Pickup Item
        */
        // currently focused(like a keyboard)
        // name of animation to trigger
        // set/clear sensor state
        // set/clear bus type device state
    };
}
#endif // INTERACTABLEBUTTON_H_INCLUDED