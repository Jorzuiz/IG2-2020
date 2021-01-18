#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <OgreCompositorManager.h>

using namespace Ogre;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
  if (evt.keysym.sym == 27)
  {
    getRoot()->queueEndRendering();
  }
  //else if (evt.keysym.sym == SDLK_???)
  if (evt.keysym.sym == SDLK_g) {
	  //Avion_->giro();
	  //Molino_->giro();//falta parametro time
	  //AspasMolino_->giro();
	  /*mSM->getSceneNode("AspasMolino")->roll(Ogre::Degree(1));
	  for (int i = 0; i < num; i++) {
		  mSM->getSceneNode("adorno" + std::to_string(i))->roll(Degree(-1));
	  }*/
	 /* mSM->getSceneNode("aspas")->roll(Ogre::Degree(1));
	  for (int i = 0; i < num; i++) {
		  mSM->getSceneNode("adorno_" + std::to_string(i))->roll(Degree(-1));
	  }*/
  }
  if (evt.keysym.sym == SDLK_j) {
	  /*mSM->getSceneNode("Tierra")->translate(-200, 0, 0, Ogre::Node::TS_LOCAL);
	  mSM->getSceneNode("Tierra")->yaw(Degree(1));
	  mSM->getSceneNode("Tierra")->translate(200, 0, 0, Ogre::Node::TS_LOCAL);

	  mSM->getSceneNode("Luna")->translate(-200, 0, 0, Ogre::Node::TS_LOCAL);
	  mSM->getSceneNode("Luna")->yaw(Degree(-2));
	  mSM->getSceneNode("Luna")->translate(200, 0, 0, Ogre::Node::TS_LOCAL);*/
	 
  }
  if (evt.keysym.sym == SDLK_c) {
	  //Avion_->retraEje();
	  //Molino_->retraEje();
	  //mSM->getSceneNode("EjeMolino")->translate(0, 0, -1);
  }
  if (evt.keysym.sym == SDLK_h) {
	  //Molino_->giroTop();		//posicionEje = molinoNode->getChild("eje")->getPosition();	//Brujería
	  /*Ogre::Vector3 posicionGiro = mSM->getSceneNode("AspasMolino")->getPosition();
	  mSM->getSceneNode("AspasMolino")->setPosition(0, 0, 0);
	  mSM->getSceneNode("AspasMolino")->yaw(Degree(1));
	  mSM->getSceneNode("AspasMolino")->translate(posicionGiro);*/

	  //GIRO SEGUNDERO
	  //mSM->getSceneNode("AgS")->translate(0,25,0, Ogre::Node::TS_LOCAL);
	  //mSM->getSceneNode("AgS")->roll(Ogre::Degree(-1));
	  //mSM->getSceneNode("AgS")->translate(0, -25, 0, Ogre::Node::TS_LOCAL);
  }
  /*if (evt.keysym.sym == SDLK_h) {
	  ClockNode_->getChild("Arrows")->roll(Ogre::Degree(-1));
  }*/
  if (evt.keysym.sym == SDLK_r) {
	  //this es tipo IG2App
	  //Molino_->keyPressed();	  
	  //Avion_->receiveEvent
	  /*PlanoNode->detachAllObjects();
	  Ogre::Entity* plane = mSM->createEntity("Plano");
	  plane->setMaterialName("IG2App/nowater");
	  PlanoNode1->attachObject(plane);*/
	  geo = !geo;
	  if(geo == true)
	  Boya_->changeMaterial(geo);
  }
  if (evt.keysym.sym == SDLK_l) {
	  BN = !BN;
	  CompositorManager::getSingleton().setCompositorEnabled(vp, "Luminance", BN);
  }
  if (evt.keysym.sym == SDLK_k) {
	  Edge = !Edge;
	  CompositorManager::getSingleton().setCompositorEnabled(vp, "EdgeEmboss", Edge);	  
  }
  return true;
}

void IG2App::shutdown()
{
  mShaderGenerator->removeSceneManager(mSM);  
  mSM->removeRenderQueueListener(mOverlaySystem);  
					
  mRoot->destroySceneManager(mSM);  

  delete mTrayMgr;  mTrayMgr = nullptr;
  delete mCamMgr; mCamMgr = nullptr;
  //delete Aspa_; Aspa_ = nullptr;
  //delete AspasMolino_; AspasMolino_ = nullptr;
  delete Molino_; Molino_ = nullptr;
  delete Avion_; Avion_ = nullptr;
  //delete Plano_; Plano_ = nullptr;
  delete Plano1_; Plano1_ = nullptr;
  //delete Plano2_; Plano2_ = nullptr;
  delete Simbad_; Simbad_ = nullptr;
  delete Boya_; Boya_ = nullptr;
  // do not forget to call the base 
  delete PlanoR_; PlanoR_ = nullptr;
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
  //añade sombras desde cualquier luz
  //mSM->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
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
  vp = getRenderWindow()->addViewport(cam);

  //COLOR DE FONDO
  vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));//(rojo,verde,azul)
  // Compositors y demas
  CompositorManager::getSingleton().addCompositor(vp, "Luminance");
  CompositorManager::getSingleton().addCompositor(vp, "EdgeEmboss");

  //------------------------------------------------------------------------

  // without light we would just get a black screen 

  Light* luz = mSM->createLight("Luz");
  luz->setType(Ogre::Light::LT_DIRECTIONAL);
  luz->setDiffuseColour(1, 1, 1);

  mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
  //mLightNode = mCamNode->createChildSceneNode("nLuz");
  mLightNode->attachObject(luz);

  mLightNode->setDirection(Ogre::Vector3(0, -1, -1));  //vec3.normalise();
  //lightNode->setPosition(0, 0, 1000);
 
  //------------------------------------------------------------------------

  // finally something to render

  //////////////////////
  ///ESCENA COMBINADA///
  //////////////////////

  mSM -> setSkyPlane(true, Plane(Vector3::UNIT_Z, -100),"IG2App/SpaceGLSL", 1, 1, true, 1, 10, 10);

  BoyaNode = mSM->getRootSceneNode()->createChildSceneNode();
  Boya_ = new Boya(BoyaNode);

  SimbadNode = mSM->getRootSceneNode()->createChildSceneNode();
  Simbad_ = new Simbad(SimbadNode);

  //Rio
  PlanoNodeR = mSM->getRootSceneNode()->createChildSceneNode("PlanoR");
  PlanoR_ = new Plano(PlanoNodeR, cam, mWindow.render);
  PlanoNodeR->setPosition(0, 0, 0);

  /*PlanoNode = mSM->getRootSceneNode()->createChildSceneNode("Plano");
  Plano_ = new Plano(PlanoNode, "Plano");
  //Ogre::Entity* plane = mSM->createEntity("Plano");
  //plane->setMaterialName("IG2App/water");
  //PlanoNode->attachObject(plane);
  PlanoNode->setPosition(0, 0, 0);*/

  PlanoNode1 = mSM->getRootSceneNode()->createChildSceneNode("Plano1");
  Plano1_ = new Plano(PlanoNode1, "Plano1");	//Plano del Molino
  PlanoNode1->setScale(0.25, 0.25, 0.25);
  PlanoNode1->setPosition(400, 15, -300);

  /*PlanoNode2 = mSM->getRootSceneNode()->createChildSceneNode("Plano2");
  Plano2_ = new Plano(PlanoNode2, "Plano2");	//Plano de Simbad
  //Ogre::Entity* plane2 = mSM->createEntity("Plano2");
  //plane2->setMaterialName("IG2App/rojo");
  //PlanoNode2->attachObject(plane2);
  PlanoNode2->setScale(0.25, 0.25, 0.25);
  PlanoNode2->setPosition(-400, 15, 300);*/

  caraCreepy = mSM->getRootSceneNode()->createChildSceneNode();
  Ogre::Entity* cara = mSM->createEntity("sphere.mesh");
  cara->setMaterialName("IG2App/cabeza");
  caraCreepy->attachObject(cara);
  caraCreepy->setScale(0.3, 0.3, 0.3);
  caraCreepy->setPosition(500, 30, -250);

  //////////////////
  ///ESCENA AVION///
  //////////////////

  AvionNode = mSM->getRootSceneNode()->createChildSceneNode("avion");
  Avion_ = new Avion(AvionNode, num);
  AvionNode->setScale(0.25, 0.25, 0.25);
  AvionNode->setPosition(0, 300, 0);

  /////////////////////
  ///ESCENA PLANETAS///
  /////////////////////

  /*mSM->getRootSceneNode()->createChildSceneNode("Sol");
  SunNode_ = mSM->getSceneNode("Sol");
  Ogre::Entity* EsferaS = mSM->createEntity("sphere.mesh");
  mSM->getSceneNode("Sol")->attachObject(EsferaS);
  mSM->getSceneNode("Sol")->setScale(0.5, 0.5, 0.5);
  mSM->getSceneNode("Sol")->setPosition(0, 0, 0);

  mSM->getRootSceneNode()->createChildSceneNode("Tierra");
  TierraNode_ = mSM->getSceneNode("Tierra");
  Ogre::Entity* EsferaT = mSM->createEntity("sphere.mesh");
  mSM->getSceneNode("Tierra")->attachObject(EsferaT);
  mSM->getSceneNode("Tierra")->setScale(0.2, 0.2, 0.2);
  mSM->getSceneNode("Tierra")->setPosition(0, 0, 0);
  mSM->getSceneNode("Tierra")->showBoundingBox(true);
  mSM->getSceneNode("Tierra")->translate(200, 0, 0, Ogre::Node::TS_LOCAL);

  mSM->getSceneNode("Tierra")->createChildSceneNode("Luna");
  Ogre::Entity* EsferaL = mSM->createEntity("sphere.mesh");
  mSM->getSceneNode("Luna")->attachObject(EsferaL);
  mSM->getSceneNode("Luna")->setScale(0.5, 0.5, 0.5);//hereda la escala de la tierra ojo
  mSM->getSceneNode("Luna")->showBoundingBox(true);
  mSM->getSceneNode("Luna")->translate(200, 0, 0, Ogre::Node::TS_LOCAL);//hereda la escala de la tierra ojo*/

  ///////////////////
  ///ESCENA MOLINO///
  ///////////////////

  MolinoNode = mSM->getRootSceneNode()->createChildSceneNode();
  Molino_ = new Molino(MolinoNode,num);
  MolinoNode->setScale(0.6, 0.6, 0.6);
  MolinoNode->setPosition(400, 100, -300);

  /*mSM->getRootSceneNode()->createChildSceneNode("AspasMolino");
  AspasMolino_ = new AspasMolino(mSM->getSceneNode("AspasMolino"), num);
  addInputListener(AspasMolino_);
  mSM->getSceneNode("AspasMolino")->setPosition(0, 170, 140);*/

  //////////////////
  ///ESCENA ASPAS///
  //////////////////

  /*mSM->getRootSceneNode()->createChildSceneNode("AspasMolino");
  AspasMolino_ = new AspasMolino(mSM->getSceneNode("AspasMolino"),num);
  addInputListener(AspasMolino_);
  mSM->getRootSceneNode()->createChildSceneNode("aspa");
  Aspa_ = new Aspa(mSM->getSceneNode("aspa"));
  addInputListener(Aspa_);  
  AspasNode_ = mSM->getRootSceneNode()->createChildSceneNode("aspas");
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
	 
  }
  
  AspaNode_ = mSM->getRootSceneNode()->createChildSceneNode("aspaNode");
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
  mSM->getSceneNode("adorno")->showBoundingBox(true);
  */

  //////////////////
  ///ESCENA RELOJ///
  //////////////////

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
  mSM->getSceneNode("AgM")->translate(0, 27, 0);
  AgM_->roll(Ogre::Degree(00));
  Ogre::Entity* AgujaS = mSM->createEntity("cube.mesh");
  Ogre::SceneNode* AgS_ = mSM->getSceneNode("Arrows")->createChildSceneNode("AgS");
  mSM->getSceneNode("AgS")->attachObject(AgujaS);
  mSM->getSceneNode("AgS")->setScale(0.02, 0.9, 0.02);
  mSM->getSceneNode("AgS")->setPosition(0, 0, 0);
  mSM->getSceneNode("AgS")->translate(0, -25, 0);
  //AgS_->roll(Ogre::Degree(-45));
  */

  ////////////////////////////
  ///ESCENA ROMA CON SINBAD///
  ////////////////////////////

  /*Ogre::Entity* ent = mSM->createEntity("Sinbad.mesh");

  mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
  mSinbadNode->attachObject(ent);

  mSinbadNode->setPosition(-400, 100, 300);
  mSinbadNode->setScale(20, 20, 20);
  //mSinbadNode->yaw(Ogre::Degree(-45));
  //mSinbadNode->showBoundingBox(true);
  //mSinbadNode->setVisible(false);*/

  /*Ogre::Entity* ent1 = mSM->createEntity("RomanBathLower.mesh");
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

  for (int i = 0; i < EntidadIG::appListeners.size(); i++) {
	  addInputListener(EntidadIG::appListeners.at(i));
  }

  //------------------------------------------------------------------------

  mCamMgr = new OgreBites::CameraMan(mCamNode);
  addInputListener(mCamMgr);
  mCamMgr->setStyle(OgreBites::CS_ORBIT);  
  
  //mCamMgr->setTarget(mSinbadNode);  
  //mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);

  //------------------------------------------------------------------------

}

