#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>

using namespace Ogre;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
  if (evt.keysym.sym == SDLK_ESCAPE)
  {
    getRoot()->queueEndRendering();
  }
  //else if (evt.keysym.sym == SDLK_???)
  if (evt.keysym.sym == SDLK_g) {
	  mSM->getSceneNode("aspas")->roll(Ogre::Degree(1));
	  for (int i = 0; i < num; i++) {
		  mSM->getSceneNode("adorno_" + std::to_string(i))->roll(Degree(-1));
	  }
  }
  /*if (evt.keysym.sym == SDLK_h) {
	  ClockNode_->getChild("Arrows")->roll(Ogre::Degree(-1));
  }*/
  return true;
}

void IG2App::shutdown()
{
  mShaderGenerator->removeSceneManager(mSM);  
  mSM->removeRenderQueueListener(mOverlaySystem);  
					
  mRoot->destroySceneManager(mSM);  

  delete mTrayMgr;  mTrayMgr = nullptr;
  delete mCamMgr; mCamMgr = nullptr;
  //delete Aspa_;
  delete AspasMolino_;
  // do not forget to call the base 
  IG2ApplicationContext::shutdown();
}

void IG2App::setup(void)
{
  // do not forget to call the base first
  IG2ApplicationContext::setup();

  mSM = mRoot->createSceneManager();  

  // register our scene with the RTSS
  mShaderGenerator->addSceneManager(mSM);

  mSM->addRenderQueueListener(mOverlaySystem);

  mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);  
  mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
  addInputListener(mTrayMgr);

  addInputListener(this);   
  setupScene();
}

void IG2App::setupScene(void)
{
  // create the camera
  Camera* cam = mSM->createCamera("Cam");
  cam->setNearClipDistance(1); 
  cam->setFarClipDistance(10000);
  cam->setAutoAspectRatio(true);
  //cam->setPolygonMode(Ogre::PM_WIREFRAME); 

  mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
  mCamNode->attachObject(cam);

  mCamNode->setPosition(0, 0, 1000);
  mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
  //mCamNode->setDirection(Ogre::Vector3(0, 0, -1));  
  
  // and tell it to render into the main window
  Viewport* vp = getRenderWindow()->addViewport(cam);

  //COLOR DE FONDO
  vp->setBackgroundColour(Ogre::ColourValue(0.1, 0.7, 0.6));//(rojo,verde,azul)

  //------------------------------------------------------------------------

  // without light we would just get a black screen 

  Light* luz = mSM->createLight("Luz");
  luz->setType(Ogre::Light::LT_DIRECTIONAL);
  luz->setDiffuseColour(0.75, 0.75, 0.75);

  mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
  //mLightNode = mCamNode->createChildSceneNode("nLuz");
  mLightNode->attachObject(luz);

  mLightNode->setDirection(Ogre::Vector3(0, 0, -1));  //vec3.normalise();
  //lightNode->setPosition(0, 0, 1000);
 
  //------------------------------------------------------------------------

  // finally something to render

  //ESCENA ASPAS
  mSM->getRootSceneNode()->createChildSceneNode("AspasMolino");
  AspasMolino_ = new AspasMolino(mSM->getSceneNode("AspasMolino"),12);
  addInputListener(AspasMolino_);


  //mSM->getRootSceneNode()->createChildSceneNode("aspa");
  //Aspa_ = new Aspa(mSM->getSceneNode("aspa"));
  //addInputListener(Aspa_);
  
  /*AspasNode_ = mSM->getRootSceneNode()->createChildSceneNode("aspas");
  for (int i = 0; i < num; i++) {
	 mSM->getSceneNode("aspas")->createChildSceneNode("aspa_" + std::to_string(i));

	 mSM->getSceneNode("aspa_" + std::to_string(i))->createChildSceneNode("tablero_" + std::to_string(i));
	 Ogre::Entity* tabla = mSM->createEntity("cube.mesh");
	 mSM->getSceneNode("tablero_" + std::to_string(i))->attachObject(tabla);
	 mSM->getSceneNode("tablero_" + std::to_string(i))->setScale(3.5, 0.7, 0.1);
	 mSM->getSceneNode("tablero_" + std::to_string(i))->setPosition(0, 0, 0);
	 mSM->getSceneNode("tablero_" + std::to_string(i))->translate(200, 0, 0);

	 mSM->getSceneNode("aspa_" + std::to_string(i))->createChildSceneNode("adorno_" + std::to_string(i));
	 Ogre::Entity* cilindro = mSM->createEntity("Barrel.mesh");
	 mSM->getSceneNode("adorno_" + std::to_string(i))->attachObject(cilindro);
	 mSM->getSceneNode("adorno_" + std::to_string(i))->setScale(5, 10, 5);
	 mSM->getSceneNode("adorno_" + std::to_string(i))->setPosition(0, 0, 0);
	 mSM->getSceneNode("adorno_" + std::to_string(i))->translate(340, 0, 20);

	 mSM->getSceneNode("aspa_" + std::to_string(i))->roll(Degree((360 / 12) * i));
	 mSM->getSceneNode("adorno_" + std::to_string(i))->roll(Degree(-(360 / 12) * i));
	 
  }*/

  /*AspaNode_ = mSM->getRootSceneNode()->createChildSceneNode("aspaNode");
  Ogre::SceneNode* tableroNode_ = mSM->getSceneNode("aspaNode")->createChildSceneNode("tablero");
  Ogre::Entity* tabla = mSM->createEntity("cube.mesh");
  mSM->getSceneNode("tablero")->attachObject(tabla);
  mSM->getSceneNode("tablero")->setScale(5, 1, 0.1);
  mSM->getSceneNode("tablero")->setPosition(0, 0, 0);
  mSM->getSceneNode("tablero")->translate(2.5, 0, 0);
  mSM->getSceneNode("tablero")->showBoundingBox(true);

  Ogre::SceneNode* cilindroNode_ = mSM->getSceneNode("aspaNode")->createChildSceneNode("adorno");
  Ogre::Entity* cilindro = mSM->createEntity("Barrel.mesh");
  mSM->getSceneNode("adorno")->attachObject(cilindro);
  mSM->getSceneNode("adorno")->setScale(5, 10, 5);
  mSM->getSceneNode("adorno")->setPosition(0, 0, 0);
  mSM->getSceneNode("adorno")->translate(200, 0, 20);
  mSM->getSceneNode("adorno")->showBoundingBox(true);*/

  //ESCENA RELOJ
  /*ClockNode_ = mSM->getRootSceneNode()->createChildSceneNode("Clock");		// crea un nodo general
  Ogre::SceneNode* CircleNode_ = ClockNode_->createChildSceneNode("Balls");
  Ogre::SceneNode* ArrowNode_ = ClockNode_->createChildSceneNode("Arrows");
  Ogre::SceneNode* HourNode_[12] = { nullptr };
  //mSM->getSceneNode("Balls");
  
  for(int i = 0; i < 12; i++){
    Ogre::Entity* Esfera = mSM->createEntity("sphere.mesh"); //genera la entidad esfera
	HourNode_[i] = mSM->getSceneNode("Balls")->createChildSceneNode("Hora " + std::to_string(i)); // genera nombres para los nodos
	mSM->getSceneNode("Hora " + std::to_string(i))->attachObject(Esfera);
	if (i % 2 == 0) {
		mSM->getSceneNode("Hora " + std::to_string(i))->setScale(0.1, 0.1, 0.1);
	}
	else {
		mSM->getSceneNode("Hora " + std::to_string(i))->setScale(0.15, 0.15, 0.15);
	}
	//mSM->getSceneNode("Hora " + std::to_string(i))->setScale(0.15, 0.15, 0.15);
	// posibilidad de acceso directo a nombre
	mSM->getSceneNode("Hora " + std::to_string(i))->setVisible(true);
	mSM->getSceneNode("Hora " + std::to_string(i))->showBoundingBox(true);
	mSM->getSceneNode("Hora " + std::to_string(i))->setPosition(100 * Ogre::Math::Cos(Ogre::Degree((360 / 12)*i)), 100 * Ogre::Math::Sin(Ogre::Degree((360 / 12)*i)), 0);
  }

  Ogre::Entity* AgujaH = mSM->createEntity("cube.mesh");
  Ogre::SceneNode* AgH_ = mSM->getSceneNode("Arrows")->createChildSceneNode("AgH");	
  mSM->getSceneNode("AgH")->attachObject(AgujaH);
  mSM->getSceneNode("AgH")->setScale(0.05, 0.4, 0.05);
  mSM->getSceneNode("AgH")->setPosition(0, 0, 0);
  mSM->getSceneNode("AgH")->translate(18, 0, 0);
  AgH_->roll(Ogre::Degree(90));
  Ogre::Entity* AgujaM = mSM->createEntity("cube.mesh");
  Ogre::SceneNode* AgM_ = mSM->getSceneNode("Arrows")->createChildSceneNode("AgM");
  mSM->getSceneNode("AgM")->attachObject(AgujaM);
  mSM->getSceneNode("AgM")->setScale(0.05, 0.6, 0.05);
  mSM->getSceneNode("AgM")->setPosition(0, 0, 0);
  mSM->getSceneNode("AgM")->setPosition(0, 0, 0);
  mSM->getSceneNode("AgM")->setPosition(0, 27, 0);
  AgM_->roll(Ogre::Degree(00));
  Ogre::Entity* AgujaS = mSM->createEntity("cube.mesh");
  Ogre::SceneNode* AgS_ = mSM->getSceneNode("Arrows")->createChildSceneNode("AgS");
  mSM->getSceneNode("AgS")->attachObject(AgujaS);
  mSM->getSceneNode("AgS")->setScale(0.02, 0.9, 0.02);
  mSM->getSceneNode("AgS")->setPosition(0, 0, 0);
  mSM->getSceneNode("AgS")->setPosition(-25, -25, 0);
  AgS_->roll(Ogre::Degree(-45));
  
  
  //ESCENA ROMA CON SINBAD 
  
  Ogre::Entity* ent = mSM->createEntity("Sinbad.mesh");

  mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
  mSinbadNode->attachObject(ent);

  //mSinbadNode->setPosition(400, 100, -300);
  mSinbadNode->setScale(20, 20, 20);
  //mSinbadNode->yaw(Ogre::Degree(-45));
  //mSinbadNode->showBoundingBox(true);
  //mSinbadNode->setVisible(false);


  Ogre::Entity* ent1 = mSM->createEntity("RomanBathLower.mesh");
  suelo = mSM->getRootSceneNode()->createChildSceneNode("suelo");
  suelo->attachObject(ent1);
  suelo->setScale(1.5, 1.5, 1.5);
  Ogre::Entity* ent2 = mSM->createEntity("RomanBathUpper.mesh");
  suelo = mSM->getRootSceneNode()->createChildSceneNode("paredes");
  suelo->attachObject(ent2);
  suelo->setScale(1.5, 1.5, 1.5);
  Ogre::Entity* ent3 = mSM->createEntity("Columns.mesh");
  suelo = mSM->getRootSceneNode()->createChildSceneNode("columnas");
  suelo->attachObject(ent3);
  suelo->setScale(1.5, 1.5, 1.5);*/

  
  //------------------------------------------------------------------------

  mCamMgr = new OgreBites::CameraMan(mCamNode);
  addInputListener(mCamMgr);
  mCamMgr->setStyle(OgreBites::CS_ORBIT);  
  
  //mCamMgr->setTarget(mSinbadNode);  
  //mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);

  //------------------------------------------------------------------------

}

