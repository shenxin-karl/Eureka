#include "GameObject.h"
#include "Comopents/IComponent.h"
#include "Comopents/Transform.h"

namespace Eureka {

GameObject::GameObject() {
	addComponent<Transform>();
}
GameObject::~GameObject() {

}


}
