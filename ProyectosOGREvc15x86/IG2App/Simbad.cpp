#include "Simbad.h"

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
