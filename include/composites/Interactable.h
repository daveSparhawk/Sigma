#ifndef INTERACTABLE_H_INCLUDED
#define INTERACTABLE_H_INCLUDED
//Must define &PhysicalWorldLocation for the object with a InteractableButton
#include "Sigma.h"
#include "controllers/FPSCamera.h"
#include "composites/PhysicalWorldLocation.h"
#include "components/InteractableButton.h"
#include <forward_list>
// COMPOSITE folder
namespace Sigma {
    /* Create a Interactable class that you will
        put in the composite folder (to be renamed
        too) to host your Interactables container
        (currently a vector that should be 
        transformed in a map) and the 
        playerActionUpdate() 
        playerActionTest()*/
    // Holds all the functions to look after InteractableButton and other Interactables
    class Interactable {
        Interactable(); 
        ~Interactable();
    public:
       static void AddEntity(const id_t id, InteractableButton* intbt) { Interactables.emplace(id,intbt); };
        //a synchronous function to queue the event, 
        static void Interactable::playerActionTest(const Sigma::event::BUTTON butt) { actionQue.push_front(butt); return; }
        //an asynchronous function to unqueue 
        //all the events and process them.The 
        //asynchronous function must be called
        //from the Update() function of the 
        //system on which this component is depending.
        static void Interactable::playerActionUpdate()
        {
            for (std::forward_list<Sigma::event::BUTTON>::iterator itt = actionQue.begin(); itt != actionQue.end(); ++itt) {
                if (actionQue.front() == Sigma::event::BUTTON::LEFT){
                    for (std::unordered_map<id_t, InteractableButton*>::iterator pObj = Interactables.begin(); pObj != Interactables.end(); ++pObj) {
                        id_t theid = pObj->first;
                        assert(theid != 0);
                        std::unique_ptr<position_type> thepo = PhysicalWorldLocation::getPosition(theid);
                        glm::vec3 Intpos = { thepo->x, thepo->y, thepo->z };
                        glm::vec3 campos = PhysicalWorldLocation::GetTransform(1)->GetPosition();
                        float range = sqrt(pow(Intpos.x - campos.x, 2) + pow(Intpos.y - campos.y, 2) + pow(Intpos.z - campos.z, 2));
                        /*The algorithm to search objects in a specific area should use the collision detection algorithm that Bullet provides, using a collision box.Someone has worked on the collision detection API 2 months ago, but I can't remember who.*/
                        if (range <  pObj->second->GetRadius()){
                            LOG_ERROR << __FILE__ << ":" << __LINE__ << "GetEntityID: " << theid;
                            LOG_ERROR << " switch State: " << pObj->second->GetState();
                            pObj->second->SetToNextState();
                            break;}
                    }
                };
            }
            actionQue.clear();
            return;
        }
    private:
        static std::forward_list<Sigma::event::BUTTON> actionQue;
        //Interactables container 
        static std::unordered_map<id_t, InteractableButton*> Interactables;
    };
}
#endif // INTERACTABLE_H_INCLUDED