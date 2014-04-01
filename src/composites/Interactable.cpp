/*
TODO:

*/
//#include "components/Interactable.h"
#include "components/PhysicsController.h"
#include <vector>
#include <forward_list>
#include "controllers/FPSCamera.h"
#include "composites/Interactable.h"

namespace Sigma {
	//list of pointers to the interactable entities.
	//std::vector<Interactable*> Interactables;
    //This should be a map, not a vector.ID's should be used as key to pointer value in a map.
    //    Moreover this should be placed in the header file, and be a member of a "component" class (see my comment below).Here you made it global.

	//maps the Default state to the [entity ID]
    //std::map<id_t, int> CurrentStates;
    //DONE: To be put in the header file, in the class.Here you made it global.
    //DONE:    Moreover entity ID must be of type id_t, which maps to uint32_t.

	// needed ctor and dtor for external dll
	//Interactable::Interactable(){/* nothing to construct*/}
	//Interactable::~Interactable(){/* destruction of private members is handled by stl*/}
	//Interactable::Interactable(const id_t entityID) : IComponent(entityID){	/* nothing to construct*/	}
    /*These functions are called through the factory hosted by the system, not directly.*/

    //std::map<id_t, InteractableButton*> Interactables;
   // std::forward_list<Sigma::event::BUTTON>  Interactable::actionQue;// = new();

    
    //std::unordered_map<id_t, glm::vec3> InterpolatedMovement::rotationtarget_map;
    std::unordered_map<id_t, InteractableButton*> Interactable::Interactables;

    std::forward_list<Sigma::event::BUTTON> Interactable::actionQue;
}


/*
catageek:

You aim one level too high in the ECS hierarchy. Here are the details of my comments:

ECS has 3 "hierarchic" levels : System, components and low-level data.

Low-level data is the smallest atomic data that you handle and must be put in containers in "component" dir (I think Adam has renamed or will rename the folder) with the low-level code on the data. The container hosted is something like std::unordered_map, and code is merely create, read, update and delete. the low-level data are "states" that you must keep between each frame.

Components store the low-level data instance and host functional code that is organized in asynchronous batch, i.e iterating on the container elements to test something and process accordingly. It can be "iterating on all the buttons, check which buttons were clicked and update the rendering accordingly". The batch is run once at each frame. The component holds also the code to manage all the low-level data synchronously. A rule of thumb is that a component must hold only the low-level data that have the same lifecycle, otherwise it must be splitted. A component should not have other data than the low-level data containers.

Systems are responsible for coordinating components together and schedule batch operations. They also publish the Factory methods. Only the functions at the system level must be exported.

TODO:

Find a System class to host your component factory. The BulletPhysics system should be a good place to register your factory functions, that must be removed from the component itself.

Create a Interactable class that you will put in the composite folder (to be renamed too) to host your Interactables container (currently a vector that should be transformed in a map) and the playerActionTest() function. Split the playerActionTest() function in 2 parts : the synchronous function to queue the event (you need a queue container, for instance std::forward_list), and the asynchronous function to process the events.

The current Interactable class (that should be renamed InteractableButton or something like that to not be confused with the component class) will be the low-level data object definition when everything will be moved to upper level class. It should contain only CRUD (create, read, update, delete) code.


*/