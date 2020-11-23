#include "Simbad.h"

Simbad::Simbad(Ogre::SceneNode* node) : EntidadIG(node)
{
	addListener(this);
	Simbad_ = node;

	//////////////////////////
	//	Creacion de la malla//
	//////////////////////////
	
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

	////////////////////
	// ANIMATION PASEO//
	////////////////////

	SimbadAnim = mSM->createAnimation("paseo", duration);
	track = SimbadAnim->createNodeTrack(0);
	track->setAssociatedNode(Simbad_);
	// POSICIONES INICIALES ANIM
	keyframePos = Simbad_->getPosition();
	orientation = { 0.0, 0.0, 1.0 };
	desplazamiento = { 1.0, 0.0, 0.0 };

	// Creacion de Frames	
	Vector3 keyframePos(-400.0, 100.0, 300.0); Vector3 src(0, 0, 1); // posición y orientación iniciales
	TransformKeyFrame* kf; // 4 keyFrames: origen(0), abajo, arriba, origen(3)
	Ogre::Vector3 longDesplazamiento = { -400, 100, 300 };
	Ogre::Real durPaso = duration / 7.0;

	// No entiendo porque necesita que le digamos en cada keyframe las posiciones
	// que debe de tener en vez de ignorarlas
	kf = track->createNodeKeyFrame(durPaso * 0); // Keyframe 0: Plano Rojo
	kf->setTranslate(keyframePos);
	kf->setScale({ scale, scale, scale });
	kf->setRotation(src.getRotationTo(Vector3(0, 0, 1)));

	kf = track->createNodeKeyFrame(durPaso * 1); // Keyframe 1: solo gira hacia el centro
	kf->setScale({ scale, scale, scale });
	kf->setTranslate(keyframePos);
	kf->setRotation(src.getRotationTo(Vector3(1, 0, -1))); // Mira al Origen

	kf = track->createNodeKeyFrame(durPaso * 3); // Keyframe 2: Desplazarse al centro
	kf->setScale({ scale, scale, scale });
	keyframePos = Vector3{0.0, 1.0, 0.0} * longDesplazamiento;
	kf->setTranslate(keyframePos);
	kf->setRotation(src.getRotationTo(Vector3(1, 0, -1))); // Mira al Origen

	kf = track->createNodeKeyFrame(durPaso * 4); // Keyframe 3: Vuelve a mirar al Plano rojo
	kf->setScale({ scale, scale, scale });
	kf->setTranslate(keyframePos); 
	kf->setRotation(src.getRotationTo(Vector3(-1, 0, 1))); // Giro hacia el plano rojo

	kf = track->createNodeKeyFrame(durPaso * 6); // Keyframe 4: Desplaza al Plano Rojo
	kf->setScale({ scale, scale, scale });
	keyframePos = Vector3{1.0, 1.0, 1.0} * longDesplazamiento;
	kf->setTranslate(keyframePos);
	kf->setRotation(src.getRotationTo(Vector3(-1, 0, 1))); // Giro hacia el plano rojo

	kf = track->createNodeKeyFrame(durPaso * 7); // Keyframe 5: Posicion original
	kf->setTranslate(keyframePos);
	kf->setScale({ scale, scale, scale });
	kf->setRotation(src.getRotationTo(Vector3(0, 0, 1)));

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
			// RunBase y RunTop
            animationsSinbad_.at(9)->setEnabled(true);
            animationsSinbad_.at(9)->setLoop(true);
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
        
		// Cambio de mano de espadas
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
		// Idlebase e IdleTop
        animationsSinbad_.at(4)->setEnabled(true);
        animationsSinbad_.at(4)->setLoop(true);
        animationsSinbad_.at(5)->setEnabled(true);
        animationsSinbad_.at(5)->setLoop(true);
    }
	// Paseo de simbad
    if (evento.keysym.sym == SDLK_p) {

        StopAnim();
		paseo = true;
        walking->setEnabled(true);
        walking->setLoop(true);

		// RunBase y RunTop
        animationsSinbad_.at(9)->setEnabled(true);
        animationsSinbad_.at(9)->setLoop(true);
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
	if (paseo) {
		walking->addTime(evento.timeSinceLastFrame);
	}   // Animacion de caminado
	if (muerte) {
		dead->addTime(evento.timeSinceLastFrame);
	}	// Animacion de muerte
}

void Simbad::receiveEvent(EntidadIG* entidad, string mensaje)
{
	// La muerte llega desde la explosion del avion
	if (mensaje == "muere") {
		 StopAnim();
		 muerte = true;
		 keyframePos = Simbad_->getPosition();
		 aaa = Simbad_->getOrientation();
		 ////////////////////
		//ANIMACION MUERTE//
		////////////////////

		SimbadAnimM = mSM->createAnimation("muerte", 2);
		trackMuerte = SimbadAnimM->createNodeTrack(0);
		trackMuerte->setAssociatedNode(Simbad_);
		// POSICIONES INICIALES ANIM
		Ogre::TransformKeyFrame* kfm;

		// Keyframe 0: origen
		kfm = trackMuerte->createNodeKeyFrame(1);
		kfm->setTranslate(keyframePos);
		kfm->setRotation(aaa);
		kfm->setScale({ scale, scale, scale });

		// Keyframe 1: muerte
		kfm = trackMuerte->createNodeKeyFrame(2);

		kfm->setTranslate({ keyframePos.x, 20, keyframePos.z });
		kfm->setRotation(orientation.getRotationTo({aaa.x, 1, aaa.z }));
		kfm->setScale({ scale, scale, scale });

		dead = mSM->createAnimationState("muerte");
		dead->setEnabled(true);
		dead->setLoop(false);
	}
}

void Simbad::StopAnim() {   // Resetea todas las animaciones
	for (int i = 0; i < animationsSinbad_.size(); ++i)
	{
		animationsSinbad_.at(i)->setEnabled(false);
		animationsSinbad_.at(i)->setLoop(false);
	}
	walking->setEnabled(false);
	walking->setLoop(false);
	paseo = false;
	if (muerte)
	{
		dead->setEnabled(false);
		//dead->setLoop(false);
		muerte = false;
	}
}
