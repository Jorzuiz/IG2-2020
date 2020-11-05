#include "EntidadIG.h"

std::vector<EntidadIG*> EntidadIG::appListeners = std::vector<EntidadIG*>(0, nullptr);

EntidadIG::EntidadIG(Ogre::SceneNode* nodo) : mNode(nodo) {
	mSM = mNode->getCreator();
}

EntidadIG::~EntidadIG() {

}

void EntidadIG::sendEvent(EntidadIG* entidad) {
	for (EntidadIG* e : appListeners)
		e->receiveEvent(this);
}

void EntidadIG::frameRendered(const Ogre::FrameEvent& evt)
{

}

