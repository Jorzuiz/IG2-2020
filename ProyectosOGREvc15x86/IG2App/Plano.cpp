#include "Plano.h"

Plano::Plano(SceneNode* node) :EntidadIG(node) {
	PlanoNode_ = node;
	Ogre::SceneManager* mSM = PlanoNode_->getCreator();
	
			
	PlanoNode_ = mSM->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* plane = mSM->createEntity("mPlane1080x800.mesh");
	PlanoNode_->attachObject(plane);
};