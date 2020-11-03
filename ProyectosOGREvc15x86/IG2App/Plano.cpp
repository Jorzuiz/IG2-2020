#include "Plano.h"

Plano::Plano(SceneNode* node, std::string plano) : EntidadIG(node) {
	PlanoNode_ = node;
	Ogre::SceneManager* mSM = PlanoNode_->getCreator();
	
	MeshManager::getSingleton().createPlane(plano,
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(Vector3::UNIT_Y, 0),
		1080, 800, 100, 80, true, 1, 1.0, 1.0, Vector3::UNIT_Z);

	PlanoNode_ = mSM->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* plane = mSM->createEntity(plano);
	PlanoNode_->attachObject(plane);
};