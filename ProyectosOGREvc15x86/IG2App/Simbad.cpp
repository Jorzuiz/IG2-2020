#include "Simbad.h"

Simbad::Simbad(Ogre::SceneNode* node) : EntidadIG(node)
{
	addListener(this);
	Simbad_ = node;

	//////////////////////////
	//	Creacion de la malla//
	//////////////////////////
	Ogre::Real scale = 20;
	ent = mSM->createEntity("Sinbad.mesh");
	Simbad_ = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
	Simbad_->attachObject(ent);
	Simbad_->setPosition(-400, 100, 300);
	Simbad_->setScale(scale, scale, scale);

	// Espada 1
	sword1_ = mSM->createEntity("Sword.mesh");
	sword1Node = Simbad_->createChildSceneNode("sword1");

	// Espada 2
	sword2_ = mSM->createEntity("Sword.mesh");
	sword2Node = Simbad_->createChildSceneNode("sword2");

	// Pega las espadas a los huesos
	ent->attachObjectToBone("Sheath.L", sword1_);
	ent->attachObjectToBone("Sheath.R", sword2_);

	/////////////////////////////
	// Creacion de la animacion//
	/////////////////////////////
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

	// Obtenemos el esqueleto
	auto skeleton = ent->getSkeleton();
	auto numBones = skeleton->getNumBones();
	for (cont = 0; cont < numBones; cont++) {
		std::cout << " Sinbad Bone " << cont << ": " << skeleton->getBone(cont)->getName() << "\n";
	}

	// ANIMATION PASEO
	SimbadAnim = mSM->createAnimation("paseo", duration);
	track = SimbadAnim->createNodeTrack(0);
	track->setAssociatedNode(Simbad_);
	// POSICIONES INICIALES ANIM
	keyframePos = Simbad_->getPosition();
	orientation = { 0.0, 0.0, 1.0 };
	desplazamiento = { 1.0, 0.0, 0.0 };

	///////////////////////////
	// Creacion de los frames//
	///////////////////////////
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
	kf->setRotation(orientation.getRotationTo(Ogre::Vector3(1, 0, -1)));
	keyframePos += desplazamiento;
	kf->setScale({ scale, scale, scale });

	// Keyframe 2: avanza hacia boya
	kf = track->createNodeKeyFrame(durPaso * 3);
	desplazamiento = { 0.0, 100.0, 0.0 };
	kf->setTranslate(desplazamiento);
	keyframePos = desplazamiento;
	kf->setRotation(orientation.getRotationTo(Ogre::Vector3(1, 0, -1)));
	kf->setScale({ scale, scale, scale });

	// Keyframe 3: giro derecha
	kf = track->createNodeKeyFrame(durPaso * 5);
	desplazamiento = { 0.0, 0.0, 0.0 };
	kf->setTranslate(keyframePos + desplazamiento);
	kf->setRotation(orientation.getRotationTo(Ogre::Vector3(-1, 0, 1)));
	keyframePos += desplazamiento;
	kf->setScale({ scale, scale, scale });

	// Keyframe 4: avanza hacia su plano
	kf = track->createNodeKeyFrame(durPaso * 8);
	desplazamiento = { -400, 100.0, 300 };
	kf->setTranslate(desplazamiento);
	kf->setRotation(orientation.getRotationTo(Ogre::Vector3(-1, 0, 1)));
	keyframePos = desplazamiento;
	kf->setScale({ scale, scale, scale });

	// Keyframe 5: vuelve a la pos ini
	kf = track->createNodeKeyFrame(durPaso * 10);
	desplazamiento = { 0.0, 0.0, 0.0 };
	kf->setTranslate(keyframePos + desplazamiento);
	kf->setRotation(orientation.getRotationTo(Ogre::Vector3(0, 0, 1)));
	keyframePos += desplazamiento;
	kf->setScale({ scale, scale, scale });

	// ANIMATION STATE
	walking = mSM->createAnimationState("paseo");

}

bool Simbad::keyPressed(const OgreBites::KeyboardEvent& evento)
{
    if (evento.keysym.sym == SDLK_c) {
       
        StopAnim();     //detenemos todas las animaciones iniciales
        ent->detachObjectFromBone(sword1_);
        ent->detachObjectFromBone(sword2_);
        ent->attachObjectToBone("Sheath.L", sword1_);
        ent->attachObjectToBone("Sheath.R", sword2_);

        anim = !anim;
        if (anim) {     // Baile es la animacion base
            animationsSinbad_.at(0)->setEnabled(true);
            animationsSinbad_.at(0)->setLoop(true);
        }
        else {
            animationsSinbad_.at(9)->setEnabled(true);
            animationsSinbad_.at(9)->setLoop(true);
            // Equilibrio manos-torso
            animationsSinbad_.at(10)->setEnabled(true);
            animationsSinbad_.at(10)->setLoop(true);
        }
    }
    if (evento.keysym.sym == SDLK_e) {
        StopAnim();
        ent->detachObjectFromBone(sword1_);
        ent->detachObjectFromBone(sword2_);
        ent->attachObjectToBone("Sheath.L", sword1_);
        ent->attachObjectToBone("Sheath.R", sword2_);

        anim = !anim;
        
        if (anim) {
            ent->detachObjectFromBone(sword1_);
            ent->attachObjectToBone("Handle.L", sword1_);
            animationsSinbad_.at(1)->setEnabled(true);
        }
        else {
            ent->detachObjectFromBone(sword2_);
            ent->attachObjectToBone("Handle.R", sword2_);
            animationsSinbad_.at(1)->setEnabled(true);
        }
        animationsSinbad_.at(4)->setEnabled(true);
        animationsSinbad_.at(4)->setLoop(true);
        animationsSinbad_.at(5)->setEnabled(true);
        animationsSinbad_.at(5)->setLoop(true);
    }
    if (evento.keysym.sym == SDLK_p) {
        StopAnim();
        walking->setEnabled(true);
        walking->setLoop(true);

        animationsSinbad_.at(9)->setEnabled(true);
        animationsSinbad_.at(9)->setLoop(true);
        // Equilibrio manos-torso
        animationsSinbad_.at(10)->setEnabled(true);
        animationsSinbad_.at(10)->setLoop(true);
    }

    return false;
}

void Simbad::frameRendered(const Ogre::FrameEvent& evento)
{
    // Permite a la animacion detectar el paso del tiempo
    for (int i = 0; i < animationsSinbad_.size(); ++i)
    {
        animationsSinbad_.at(i)->addTime(evento.timeSinceLastFrame);
    }
    walking->addTime(evento.timeSinceLastFrame);    // Animacion de caminado
}

void Simbad::receiveEvent(EntidadIG* entidad, string mensaje)
{
}

void Simbad::StopAnim() {   // Resetea todas las animaciones
    for (int i = 0; i < animationsSinbad_.size(); ++i)
    {
        animationsSinbad_.at(i)->setEnabled(false);
        animationsSinbad_.at(i)->setLoop(false);
    }
    walking->setEnabled(false);
    walking->setLoop(false);
}
