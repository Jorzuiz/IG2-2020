#include "Molino.h"

Molino::Molino(Ogre::SceneNode* node, const int numAspas) : EntidadIG(node)
{
	addListener(this);
	molinoNode = node;
	numAspas_ = numAspas;
	Ogre::SceneManager* mSM = molinoNode->getCreator();

	techoNode = molinoNode->createChildSceneNode();
	techo = mSM->createEntity("sphere.mesh");
	techo->setMaterialName("IG2App/amarillo");
	techoNode->attachObject(techo);
	techoNode->setScale(1.25, 1.25, 1.25);
	techoNode->setPosition(0, 170, 0);

	paredNode = molinoNode->createChildSceneNode();
	Ogre::Entity* pared = mSM->createEntity("Barrel.mesh");
	pared->setMaterialName("IG2App/muro");
	paredNode->attachObject(pared);
	paredNode->setScale(50, 60, 50);
	paredNode->setPosition(0, 0, 0);

	aspasMolino = molinoNode->createChildSceneNode();		// Esto es nodo
	aspasMolino_ = new AspasMolino(aspasMolino, numAspas_);	// Esto es creadora de clase
	aspasMolino->setScale(0.8, 0.8, 0.8);
	aspasMolino->setPosition(0, 170, 140);

};

Molino::~Molino() {
	delete aspasMolino_;
	aspasMolino_ = nullptr;
}
inline void Molino::frameRendered(const Ogre::FrameEvent& evt)
{
	Ogre::Real time = evt.timeSinceLastFrame;
	giro(time);
}
;

bool Molino::keyPressed(const OgreBites::KeyboardEvent& evt) { 
		if (evt.keysym.sym == SDLK_r)
			EntidadIG::sendEvent(this, "paraMolino");
		return true;
};

void Molino::receiveEvent(EntidadIG* entidad,string mensaje)
{
	if (mensaje == "paraMolino") {
		parado = !parado;	//Variable de control del metodo giro
		if(parado)
			techo->setMaterialName("IG2App/rojo");
		else
			techo->setMaterialName("IG2App/amarillo");
	}
	aspasMolino_->adornosGone();
}

void Molino::giro(Ogre::Real time) {
	if (!parado) aspasMolino_->giro(time);
}

void Molino::retraEje() {
	aspasMolino_->retraEje();// getEje()->translate(0, -1, 0, Ogre::Node::TS_LOCAL);
}

void Molino::giroTop() {
	aspasMolino->translate(-posicionGiro, Ogre::Node::TS_LOCAL);
	aspasMolino->yaw(Degree(1));
	aspasMolino->translate(posicionGiro, Ogre::Node::TS_LOCAL);
}