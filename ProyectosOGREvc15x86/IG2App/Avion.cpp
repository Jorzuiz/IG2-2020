#include "Avion.h"


//Movimiento basado en el de la tierra

Avion::Avion(Ogre::SceneNode* node, const int numAspas) :EntidadIG(node) {
	addListener(this);
	AvionNode = node;
	numAspas_ = numAspas;

	Ogre::SceneManager* mSM = AvionNode->getCreator();
	// Esfera del cuerpo del avion
	cuerpoNode = AvionNode->createChildSceneNode();
	Ogre::Entity* cuerpo = AvionNode->getCreator()->createEntity("sphere.mesh");
	cuerpo->setMaterialName("IG2App/rojo");
	cuerpoNode->attachObject(cuerpo);
	cuerpoNode->setScale(1, 1, 1);
	// Ala izquierda
	alaINode = AvionNode->createChildSceneNode();
	Ogre::Entity* alaI = AvionNode->getCreator()->createEntity("cube.mesh");
	alaI->setMaterialName("IG2App/alas");
	alaINode->attachObject(alaI);
	alaINode->setScale(3, 0.2, 1);
	alaINode->translate(-150, 0, 0, Ogre::Node::TS_LOCAL);
	// Ala derecha
	alaDNode = AvionNode->createChildSceneNode();
	Ogre::Entity* alaD = AvionNode->getCreator()->createEntity("cube.mesh");
	alaD->setMaterialName("IG2App/alas");
	alaDNode->attachObject(alaD);
	alaDNode->setScale(3, 0.2, 1);
	alaDNode->translate(150, 0, 0, Ogre::Node::TS_LOCAL);
	// Morro
	frenteNode = AvionNode->createChildSceneNode();
	Ogre::Entity* frente = AvionNode->getCreator()->createEntity("Barrel.mesh");
	frente->setMaterialName("IG2App/naranja");
	frenteNode->attachObject(frente);
	frenteNode->setScale(10, 10, 10);
	frenteNode->pitch(Degree(90), Ogre::Node::TS_LOCAL);
	frenteNode->translate(0, 100, 0, Ogre::Node::TS_LOCAL);
	// Piloto NINJA
	pilotoNode = AvionNode->createChildSceneNode();
	Ogre::Entity* piloto = AvionNode->getCreator()->createEntity("ninja.mesh");
	piloto->setMaterialName("IG2App/amarillo");
	pilotoNode->attachObject(piloto);
	pilotoNode->setScale(1, 1, 1);
	pilotoNode->translate(0, -50, 0, Ogre::Node::TS_LOCAL);
	pilotoNode->yaw(Degree(180), Ogre::Node::TS_LOCAL);
	// Aspa IZQ
	aspas1 = AvionNode->createChildSceneNode();
	aspasMolino1 = new AspasMolino(aspas1, numAspas_);
	aspas1->setPosition(-250, 0, 55);
	aspas1->setScale(0.3, 0.3, 0.3);
	// Aspa DER
	aspas2 = AvionNode->createChildSceneNode();
	aspasMolino2 = new AspasMolino(aspas2, numAspas_);
	aspas2->setPosition(250, 0, 55);
	aspas2->setScale(0.3, 0.3, 0.3);

	foco_ = mSM->createLight("LuzAvion");
	foco_->setType(Ogre::Light::LT_SPOTLIGHT);
	foco_->setSpotlightRange(Ogre::Degree(70), Ogre::Degree(70), 1.0);
	foco_->setDiffuseColour(0.75, 0.75, 0.75);
	foco = AvionNode->createChildSceneNode(/*"nLuz"*/);//nombre opcional
	foco->attachObject(foco_);
	foco->setDirection(Ogre::Vector3(0, -1, 0));  //vec3.normalise();
	foco->setPosition(0, -30, 0);

	AvionNode->translate(200, 0, 0, Ogre::Node::TS_LOCAL);

	// Particulas
	bbSet = mSM->createBillboardSet("bill", MaxEls);
	bbSet->setDefaultDimensions(100, 100);
	bbSet->setMaterialName("IG2App/Panel");
	AvionNode->attachObject(bbSet);
	bb = bbSet->createBillboard(Vector3(0, 0, -200));

	// Estela del avion
	pSysTrail = mSM->createParticleSystem("psSmoke", "IG2App/SmokeTrail");
	pSysTrail->setEmitting(true);
	pSysTrail->setSortingEnabled(true);
	AvionNode->attachObject(pSysTrail);

	// Explosion del avion
	pSysExplosion = mSM->createParticleSystem("psExplosion", "IG2App/Explosion");
	pSysExplosion->setEmitting(false);
	AvionNode->attachObject(pSysExplosion);
}

void Avion::frameRendered(const Ogre::FrameEvent& evt)
{
	Ogre::Real time = evt.timeSinceLastFrame;
	timeAvion = time;
	giro(10 * time);
	movimiento(time);

	if (explo)	timeExplosion += time;
	if(timeExplosion > 3)	pSysExplosion->setEmitting(false);	// Explosion
}

bool Avion::keyPressed(const OgreBites::KeyboardEvent& evt) {
	if (evt.keysym.sym == SDLK_r)
		EntidadIG::sendEvent(this, "para");
	if (evt.keysym.sym == SDLK_u) {
		EntidadIG::sendEvent(this, "explota");	// Expplosion del avion
		EntidadIG::sendEvent(this, "muere");	// Cambiar Simbad a morirse
		explo = true;
	}

	return true;
}

void Avion::receiveEvent(EntidadIG* entidad, string mensaje) {

	if (mensaje == "para") {
		parado = !parado;	//Variable de control del metodo giro
		foco_->setVisible(false);
	}

	if (mensaje == "explota") {
		parado = !parado;
		explo= true;

		bbSet->setVisible(false);
		pSysTrail->setVisible(false);		// Rastro del avión
		pSysExplosion->setEmitting(true);	// Explosion
		cuerpoNode->setVisible(false);
		alaINode->setVisible(false);
		alaDNode->setVisible(false);
		frenteNode->setVisible(false);
		pilotoNode->setVisible(false);
		aspas1->setVisible(false);
		aspas2->setVisible(false);
		foco->setVisible(false);


		
		/**cuerpoNode, *alaINode, *alaDNode, 
	*frenteNode, *pilotoNode, *aspas1, *aspas2, *foco;
	AspasMolino* aspasMolino1;
	AspasMolino* aspasMolino2;*/
	}
}

void Avion::giro(Ogre::Real time) {
	aspasMolino1->giro(time);
	aspasMolino2->giro(-time);
}

void Avion::movimiento(Ogre::Real time) {
	if (!parado) {
		AvionNode->translate(-200, 0, 0, Ogre::Node::TS_LOCAL);
		AvionNode->yaw(Degree(-50) * time);
		AvionNode->translate(200, 0, 0, Ogre::Node::TS_LOCAL);
	}
}

void Avion::retraEje() {
	aspasMolino1->retraEje();
	aspasMolino2->retraEje();
}
