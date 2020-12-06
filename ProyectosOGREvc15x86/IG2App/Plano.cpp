#include "Plano.h"
#include <OgreMaterialManager.h>
#include<OgreMaterial.h>
#include<OgrePass.h>
#include<OgreTechnique.h>

#include <OgreMovablePlane.h>
#include <OgreTextureManager.h>
#include <OgreHardwarePixelBuffer.h>//rttfref
#include <OgreViewport.h>
#include <OgreRenderTexture.h>
#include <OgreSubEntity.h>

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
	if (plano == "Plano") {s
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

Plano::Plano(Ogre::SceneNode* nodo, Camera* cam, Ogre::RenderWindow* render) : EntidadIG(nodo) {
	addListener(this);
	PlanoNode_ = nodo;
	
	// EL PLANO
	MeshManager::getSingleton().createPlane("espejo",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(Vector3::UNIT_Y, 0), 1080, 800, 100, 80,
		true, 1, 1.0, 1.0, Vector3::UNIT_Z);
	//reutilizamos la entidad
	plane = mSM->createEntity("espejo");
	plane->setMaterialName("IG2App/reflejo");
	PlanoNode_->attachObject(plane);

	// Cámara para el reflejo
	Camera* camRef = mSM->createCamera("RefCam");
	// Configuramos el fustrum igual que el de la cámara de la escena
	camRef->setNearClipDistance(cam->getNearClipDistance());
	camRef->setFarClipDistance(cam->getFarClipDistance());
	camRef->setAutoAspectRatio(cam->getAutoAspectRatio());

	// El plano está mirando arriba asique su normal es el eje Y positivo
	mpRef = new MovablePlane(Vector3::UNIT_Y, 0);	// Liberar en destructora
	PlanoNode_->attachObject(mpRef);	// Pegamos la camara al nodo del espejo
	// Configuracion de la camara para el reflejo sobre el plano
	camRef->enableReflection(mpRef);
	camRef->enableCustomNearClipPlane(mpRef);

	// Luces y Camaras diapo 6
	SceneNode* camRefNode = (SceneNode*)mSM->getRootSceneNode()->getChild("nCam");
	camRefNode->setPosition(0, 0, 1000);
	camRefNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
	camRefNode->attachObject(camRef);
	
	// Esta será la textura donde pondremos el reflejo
	TexturePtr rttRef = TextureManager::getSingleton().createManual(
		"rttReflejo", // ejemplo -> (*)
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		TEX_TYPE_2D,
		// El ancho de la camara no se actualiza si modificamos la ventana
		//(Real)cam->getViewport()->getActualWidth(), // Anchura ejemplo //mwindow,0 apuntes?
		(Real)render->getViewport(0)->getActualWidth()*1.5,
		(Real)cam->getViewport()->getActualHeight(), // Altura ejemplo
		0, PF_R8G8B8, TU_RENDERTARGET);

	// Cogemos la textura renderizada y añadimos un viewport con ella
	RenderTexture* renderTexture = rttRef->getBuffer()->getRenderTarget();
	Viewport* vpt = renderTexture->addViewport(camRef); // ocupando toda la textura
	vpt->setClearEveryFrame(true);
	vpt->setBackgroundColour(ColourValue::White);		// black/white

	// Añadimos la nueva textura al material de reflejo
	TextureUnitState* tu = plane->getSubEntity(0)->getMaterial()->
		getTechnique(0)->getPass(0)->
		createTextureUnitState("rttReflejo"); // <- (*)

	tu->setColourOperation(LBO_MODULATE); // black/white background?
	// LBO_ADD / LBO_ALPHA_BLEND / LBO_REPLACE
	
	tu->setProjectiveTexturing(true, camRef);
	// La clase Camera hereda de Frustum
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