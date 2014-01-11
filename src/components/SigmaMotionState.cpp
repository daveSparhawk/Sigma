#include "components/SigmaMotionState.h"
#include "components/PhysicalWorldLocation.h"

namespace Sigma {
		void SigmaMotionState::setWorldTransform(const btTransform &worldTrans) {
            auto vec = worldTrans.getOrigin();
            wp->PositionWrite_x(id) = vec.x();
            wp->PositionWrite_y(id) = vec.y();
            wp->PositionWrite_z(id) = vec.z();
            float a, b, g;
            worldTrans.getBasis().getEulerZYX(a, b, g);
            (*wo)[id] = orientation_type(a, b, g);
            PhysicalWorldLocation::MarkUpdated(id);
        }

		void SigmaMotionState::getWorldTransform(btTransform &worldTrans) const {
            worldTrans.setIdentity();
            worldTrans.setOrigin(btVector3(wp->x(id), wp->y(id), wp->z(id)));
            orientation_type o = wo->at(id);
            worldTrans.getBasis().setEulerZYX(o.alpha, o.beta, o.gamma);
        };


}
