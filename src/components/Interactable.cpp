#include "components/Interactable.h"
#include "components/PhysicsController.h"
#include <vector>
namespace Sigma {
	//list of pointers to the interactable entities.
	std::vector<Interactable*> Interactables;
	//maps the Default state to the [entity ID]
	std::map<unsigned int, int> CurrentStates;
	// needed ctor and dtor for external dll
	Interactable::Interactable(){/* nothing to construct*/}
	Interactable::~Interactable(){/* destruction of private members is handled by stl*/}
	Interactable::Interactable(const id_t entityID) : IComponent(entityID){	/* nothing to construct*/	}
	IComponent* Interactable::createInteractable(const id_t entityID, const std::vector<Property> &properties) 
    {
		Interactable* retvalue = new Interactable(entityID);
		for (auto propitr = properties.begin(); propitr != properties.end(); ++propitr) {
			const Property*  p = &(*propitr);
			if (p->GetName() == "radius") {
				retvalue->radius = p->Get<float>();
			}
			else if (p->GetName() == "state") {
				retvalue->validstate = p->Get<int>();
			}
			else if (p->GetName() == "defaultstate") {
				CurrentStates[entityID] = p->Get<int>();
			}
			else if (p->GetName() == "setstate") {
				retvalue->setstate = p->Get<int>();
			}
		}
		Interactables.push_back( retvalue);
		return retvalue;
	}
    void Interactable::playerActionTest(const Sigma::event::BUTTON butt)
    {
        if (butt != Sigma::event::BUTTON::LEFT){ return; };
		for (std::vector<Interactable*>::iterator pObj = Interactables.begin(); pObj != Interactables.end(); ++pObj) {
			id_t theid = (*pObj)->GetEntityID();
			std::unique_ptr<position_type> thepo = PhysicalWorldLocation::getPosition(theid);
			glm::vec3 Intpos = { thepo->x, thepo->y, thepo->z };
			glm::vec3 campos = PhysicalWorldLocation::GetTransform(1)->GetPosition();
			float range = sqrt(pow(Intpos.x - campos.x, 2) + pow(Intpos.y - campos.y, 2) + pow(Intpos.z - campos.z, 2)); 
			if (range < (*pObj)->radius){
				if ((*pObj)->validstate == CurrentStates[theid]) {
					//if selection passes {
					LOG << __FILE__ << ":" << __LINE__ << "GetEntityID: " << theid;
                    LOG << " CurrentStates: " << CurrentStates[theid];
                    std::cerr << " CurrentStates: " << CurrentStates[theid] << std::endl;
			    	CurrentStates[theid] = (*pObj)->setstate;
					break; 
					//}
				}
			}
		}
		return;
	}
    std::map<std::string, IFactory::FactoryFunction> Interactable::getFactoryFunctions()
    {
		using namespace std::placeholders;
		std::map<std::string, IFactory::FactoryFunction> retval;
		retval["Interactable"] = std::bind(&Interactable::createInteractable, this, _1, _2);
		return retval;
	}
}