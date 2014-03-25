#ifndef INTERACTABLE_H_INCLUDED
#define INTERACTABLE_H_INCLUDED
//Must define &PhysicalWorldLocation for object
//need to place one >defaultstate=?i line inside any &Interactable
#include "IComponent.h"
#include "Sigma.h"
#include "IFactory.h"
#include "ISystem.h"
#include "controllers/FPSCamera.h"
#include "composites/PhysicalWorldLocation.h"
namespace Sigma {
	class Interactable : public IFactory, public IComponent {
	public:
		DLL_EXPORT Interactable();
		DLL_EXPORT ~Interactable();
		Interactable(const id_t entityID);
		SET_COMPONENT_TYPENAME("Interactable");
		DLL_EXPORT static void Interactable::playerActionTest(const Sigma::event::BUTTON butt);
		std::map<std::string, IFactory::FactoryFunction> getFactoryFunctions();
		DLL_EXPORT IComponent* createInteractable(const id_t entityID, const std::vector<Property> &properties);
	protected:
	private:
		int validstate;         //the state the interactible would be valid for for this entity checked using 'CurrentStates[]'
		int setstate;           //the state to change to when interactable triggered by successfull playerActionTest()
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
#endif // INTERACTABLE_H_INCLUDED