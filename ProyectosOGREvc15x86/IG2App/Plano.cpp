#include "Plano.h"

Plano::Plano(SceneNode* node, std::string nombre) : EntidadIG(node),plano(nombre) {
	addListener(this);
    PlanoNode_ = node;
	//plano = nombre;
	Ogre::SceneManager* mSM = PlanoNode_->getCreator();
	
	MeshManager::getSingleton().createPlane(plano,
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(Vector3::UNIT_Y, 0),
		1080, 800, 100, 80, true, 1, 1.0, 1.0, Vector3::UNIT_Z);

	//PlanoNode_ = mSM->getRootSceneNode()->createChildSceneNode(plano);	//Sacamos el nodo
	plane = mSM->createEntity(plano);
	if (plano == "Plano") {
		plane->setMaterialName("IG2App/water");
	}
	else if (plano == "Plano1") {
		plane->setMaterialName("IG2App/naranja");
	}
	else if (plano == "Plano2") {
		plane->setMaterialName("IG2App/rojo");
	}
	else {
		plane->setMaterialName("IG2App/nowater");
	}
	PlanoNode_->attachObject(plane);
}
bool Plano::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_r)
		EntidadIG::sendEvent(this, "rocas");
	return true;
}

void Plano::receiveEvent(EntidadIG* entidad, string mensaje)
{
	//if (mensaje == "rocas") plane->setMaterialName("IG2App/nowater");
	if (plano == "Plano" && mensaje == "rocas") {
		plane->setMaterialName("IG2App/nowater");
	}

	//else plane->setMaterialName("IG2App/water");

}