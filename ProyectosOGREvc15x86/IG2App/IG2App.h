#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include "Aspa.h"
#include "AspasMolino.h"
#include "Molino.h"
#include "Avion.h"

class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener 
{
public:
  explicit IG2App() : IG2ApplicationContext("IG2App") { };  // new -> setup()  
  virtual ~IG2App() { };   // delete -> shutdown()  
 
protected:
  virtual void setup();
  virtual void shutdown();
  virtual void setupScene();

  virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
      
  Ogre::SceneManager* mSM = nullptr;
  OgreBites::TrayManager* mTrayMgr = nullptr;    
  Ogre::SceneNode* mLightNode = nullptr;
  Ogre::SceneNode* mCamNode = nullptr;
  OgreBites::CameraMan* mCamMgr = nullptr;

  //ESCENA ASPAS
  const int num = 5;
  //Ogre::SceneNode* AspasNode_ = nullptr;
  //Ogre::SceneNode* AspaNode_ = nullptr;
  //ESCENA ROMANO SINBAD

  /*Ogre::SceneNode* mSinbadNode = nullptr;
  Ogre::SceneNode* suelo = nullptr;
  Ogre::SceneNode* paredes = nullptr;
  Ogre::SceneNode* columnas = nullptr;*/

  //ESCENA RELOJ
  /*Ogre::SceneNode* ClockNode_ = nullptr; //nodo de todo el reloj
  Ogre::SceneNode* ArrowNode_ = nullptr; //nodo que agrupa las agujas
  Ogre::SceneNode* CircleNode_ = nullptr; //nodo que agrupa las esferas
  Ogre::SceneNode* HourNode_[12]; //nodos de las esferas*/
  //ESCENA MOLINO
  /*Aspa* Aspa_;
  AspasMolino* AspasMolino_;
  Molino* Molino_;*/
  //ESCENA PLANETAS
  /*Ogre::SceneNode* SunNode_ = nullptr;
  Ogre::SceneNode* TierraNode_ = nullptr;*/
  //ESCENA AVION
  Avion* Avion_;
};

#endif
