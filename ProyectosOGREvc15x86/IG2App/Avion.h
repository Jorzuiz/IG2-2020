#pragma once
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreTrays.h>
#include <OgreInput.h>
#include <OgreBillboardSet.h>
#include <OgreParticleSystem.h>
#include "AspasMolino.h"
#include "EntidadIG.h"

using namespace Ogre;
class Avion : public EntidadIG
{
public:
	Avion(Ogre::SceneNode* node, const int numAspas);
	~Avion() {}
	
	virtual void frameRendered(const Ogre::FrameEvent& evt);
	bool keyPressed(const OgreBites::KeyboardEvent& evt);;
	void receiveEvent(EntidadIG* entidad, string mensaje);
	void giro(Ogre::Real time);

	//Movimiento basado en el de la tierra
	void movimiento(Ogre::Real time);
	void retraEje();

protected:
	Ogre::SceneNode* AvionNode, *cuerpoNode, *alaINode, *alaDNode, 
	*frenteNode, *pilotoNode, *aspas1, *aspas2, *foco;
	AspasMolino* aspasMolino1;
	AspasMolino* aspasMolino2;
	int numAspas_;

	Light* foco_;

	bool parado = false;
	BillboardSet* bbSet;
	Billboard* bb;
	int MaxEls = 20;
	ParticleSystem* pSys;
};

