#pragma once
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreTrays.h>
#include <OgreInput.h>
#include "EntidadIG.h"
#include <iostream>
#include <string>
#include <OgreSkeletonInstance.h>
#include <OgreBone.h>
#include <SDL_keycode.h>
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>
#include <OgreAnimationState.h>
#include <OgreAnimationTrack.h>

#include <iostream>
#include <vector>
using namespace Ogre;
class Simbad : public EntidadIG
{
public:
	Simbad(Ogre::SceneNode* node) :EntidadIG(node) {
		addListener(this);
		Simbad_ = node;
		Ogre::Real scale = 20;
		ent = mSM->createEntity("Sinbad.mesh");

		Simbad_ = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
		Simbad_->attachObject(ent);

		Simbad_->setPosition(-400, 100, 300);
		Simbad_->setScale(scale, scale, scale);

		
		Ogre::AnimationStateSet* aux = ent->getAllAnimationStates();
		auto it = aux->getAnimationStateIterator().begin();

		int cont = 0;
		while (it != aux->getAnimationStateIterator().end()) {
			auto s = it->first;
			++it;
			std::cout << " Sinbad Animation " << cont << ": " << s << "\n";
			animationsSinbad_.push_back(ent->getAnimationState(s));
			++cont;
		}

		auto skeleton = ent->getSkeleton();
		auto numBones = skeleton->getNumBones();
		for (cont = 0; cont < numBones; cont++) {
			std::cout << " Sinbad Bone " << cont << ": " << skeleton->getBone(cont)->getName() << "\n";
		}
		//bailar
		//animationsSinbad_.at(0)->setEnabled(anim);
		//animationsSinbad_.at(0)->setLoop(anim);



		// ESPADAS
		// Espada 1
		sword1_ = mSM->createEntity("Sword.mesh");
		sword1Node = Simbad_->createChildSceneNode("sword1");
		
		// Espada 2
		sword2_ = mSM->createEntity("Sword.mesh");
		sword2Node = Simbad_->createChildSceneNode("sword2");		

		ent->attachObjectToBone("Sheath.L", sword1_);
		ent->attachObjectToBone("Sheath.R", sword2_);

		// ANIMATION PASEO
		animation = mSM->createAnimation("paseo", duration);
		track = animation->createNodeTrack(0);
		track->setAssociatedNode(Simbad_);
		// POSICIONES INICIALES ANIM
		keyframePos = Simbad_->getPosition();
		desplazamiento = { 1.0, 0.0, 0.0 };
		// iniciales de Simbad
		orientation = { Simbad_->getOrientation().x, Simbad_->getOrientation().y, Simbad_->getOrientation().z };

		// FRAMES
		Ogre::Real durPaso = duration / 10.0;
		Ogre::TransformKeyFrame* kf;

		// Keyframe 0: origen
		kf = track->createNodeKeyFrame(durPaso * 0);
		kf->setTranslate(keyframePos);
		kf->setScale({ scale, scale, scale });

		// Keyframe 1: giro izq
		kf = track->createNodeKeyFrame(durPaso * 1);
		desplazamiento = { 0.0, 0.0, 0.0 };
		kf->setTranslate(keyframePos + desplazamiento);
		kf->setRotation(orientation.getRotationTo(Ogre::Vector3(-1, 0, -1)));
		keyframePos += desplazamiento;
		kf->setScale({ scale, scale, scale });

		// Keyframe 2: avanza hacia boya
		kf = track->createNodeKeyFrame(durPaso * 3);
		desplazamiento = { 0.0, 0.0, 0.0 };
		kf->setTranslate(desplazamiento);
		kf->setRotation(orientation.getRotationTo(Ogre::Vector3(-1, 0, -1)));
		keyframePos = desplazamiento;
		kf->setScale({ scale, scale, scale });

		// Keyframe 3: giro derecha
		kf = track->createNodeKeyFrame(durPaso * 5);
		desplazamiento = { 0.0, 0.0, 0.0 };
		kf->setTranslate(keyframePos + desplazamiento);
		kf->setRotation(orientation.getRotationTo(Ogre::Vector3(1, 0, 1)));
		keyframePos += desplazamiento;
		kf->setScale({ scale, scale, scale });

		// Keyframe 4: avanza hacia su plano
		kf = track->createNodeKeyFrame(durPaso * 8);
		desplazamiento = { -400, 0.0, 300 };
		kf->setTranslate(keyframePos + desplazamiento);
		kf->setRotation(orientation.getRotationTo(Ogre::Vector3(1, 0, 1)));
		keyframePos += desplazamiento;
		kf->setScale({ scale, scale, scale });

		// Keyframe 5: vuelve a la pos ini
		kf = track->createNodeKeyFrame(durPaso * 10);
		desplazamiento = { 0.0, 0.0, 0.0 };
		kf->setTranslate(keyframePos + desplazamiento);
		kf->setRotation(orientation.getRotationTo(Ogre::Vector3(0, 0, 0)));
		keyframePos += desplazamiento;
		kf->setScale({ scale, scale, scale });

		// ANIMATION STATE
		walking = mSM->createAnimationState("paseo");
		
	}
	bool keyPressed(const OgreBites::KeyboardEvent& evento);
	void frameRendered(const Ogre::FrameEvent& evento);
	void receiveEvent(EntidadIG* entidad,string mensaje);

protected:
	void StopAnim();
	Ogre::SceneNode* Simbad_;
	bool anim = true;
	std::vector<AnimationState*> animationsSinbad_;
	Ogre::Entity* ent;
	Ogre::Entity* sword1_ = nullptr;
	Ogre::Entity* sword2_ = nullptr;

	Ogre::SceneNode* sword1Node = nullptr;
	Ogre::SceneNode* sword2Node = nullptr;

	// Animation 1
	Ogre::AnimationState* walking;

	Ogre::NodeAnimationTrack* track;
	Ogre::Animation* animation;
	Ogre::Vector3 keyframePos;
	Ogre::Vector3 desplazamiento;
	Ogre::Vector3 orientation;
	Ogre::Vector3 destino;
	//AnimationState* animationState;
	const Ogre::Real duration = 20;
};

	/*Dance			0
	DrawSwords
	HandsClosed
	HandsRelaxed
	IdleBase
	IdleTop			5
	JumpEnd
	JumpLoop
	JumpStart
	RunBase
	RunTop			10
	SliceHorizontal
	SliceVertical*/
