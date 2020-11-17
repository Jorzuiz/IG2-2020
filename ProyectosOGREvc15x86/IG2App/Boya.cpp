#include "Boya.h"

Boya::Boya(Ogre::SceneNode* node) : EntidadIG(node)
{
    addListener(this);
	BoyaNode_ = node;
	Ogre::Real scale = 10;
	Ogre::SceneManager* mSM = BoyaNode_->getCreator();
	// Creacion de la boya y su textura
	ent = BoyaNode_->getCreator()->createEntity("Barrel.mesh");
	ent->setMaterialName("IG2App/alas");
	BoyaNode_->attachObject(ent);
	BoyaNode_->setScale(scale, scale, scale);
	BoyaNode_->setPosition(0, 20, 0);
	//Animacion
	animation = mSM->createAnimation("animVV", 16);	// Duracion de la animación
	track = animation->createNodeTrack(0); 		// Secuencia de puntos numero 0 
	track->setAssociatedNode(BoyaNode_);		// Pegamos la animacion al node

	// POSICIONES INICIALES ANIM
	keyframePos = BoyaNode_->getPosition();
	desplazamiento = { 0.0, scale * 10, 0.0 };
	orientation = { 0.0, 0.0, 1.0 };
	Ogre::Real durPaso = 16 / 4.0;
	Ogre::TransformKeyFrame* kf;

	//kf 0
	kf = track->createNodeKeyFrame(durPaso * 0);
	kf->setTranslate(keyframePos);
	kf->setScale({ scale, scale, scale });
	//kf 1
	kf = track->createNodeKeyFrame(durPaso * 1);
	kf->setTranslate(keyframePos + desplazamiento);
	kf->setRotation(orientation.getRotationTo(Ogre::Vector3(1, 0, 1))); //45
	kf->setScale({ scale, scale, scale });
	//kf 3
	kf = track->createNodeKeyFrame(durPaso * 3);
	kf->setTranslate(keyframePos - desplazamiento);
	kf->setRotation(orientation.getRotationTo(Ogre::Vector3(-1, 0, 1)));
	kf->setScale({ scale, scale, scale });
	//kf 4
	kf = track->createNodeKeyFrame(durPaso * 4);
	kf->setTranslate(keyframePos);
	kf->setScale({ scale, scale, scale });

	// Activa la animacion y la reproduce en loop
	animationState = mSM->createAnimationState("animVV");
	animationState->setLoop(true);
	animationState->setEnabled(true);
}

void Boya::frameRendered(const Ogre::FrameEvent& evt)
{
	animationState->addTime(evt.timeSinceLastFrame);
	//BoyaNode_->yaw(Ogre::Degree(10 * evt.timeSinceLastFrame));
}
/*// FRAMES
	Ogre::Real durPaso = duration / 4.0;
	// 4 keyFrames: origen(0), abajo(1), arriba(2), origen(3)
	Ogre::TransformKeyFrame* kf;


	Ogre::Vector3 Rotaciones = {{0, 0, 1}, {1, 0, 1}, {1, 0, 1}, {0, 0, 1}}
	// Keyframe 0: origen
	for (int i = 0; i>4; i++){
		if (i == 1) i++;	// El segundo paso dura el doble 
		kf = track->createNodeKeyFrame(durPaso * i);
		kf->setRotation(orientation.getRotationTo(Rotaciones[i]));
		kf->setTranslate(keyframePos);
		kf->setScale({ scale, scale, scale });
	}
	*/