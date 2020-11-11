#include "AspasMolino.h"

AspasMolino::AspasMolino(Ogre::SceneNode* node, const int numAspa) : EntidadIG(node) 
{

	addListener(this);
	aspasNode = node;
	Ogre::SceneManager* mSM = aspasNode->getCreator();
	numAspas = numAspa;
	arrayAspas = new Aspa * [numAspas];	//Damos el tamaño al array de aspas dinamico
	//introduce en el array punteros de aspa, reservando espacio de tamaño aspa

	ejeNode = aspasNode->createChildSceneNode();
	Ogre::Entity* eje_ = mSM->createEntity("Barrel.mesh");
	eje_->setMaterialName("IG2App/eje");
	ejeNode->attachObject(eje_);
	ejeNode->setScale(15, 30, 15);
	ejeNode->pitch(Degree(90));

	for (int i = 0; i < numAspas; i++) {

		aspa = aspasNode->createChildSceneNode(); //crea X nodos para las aspas
		arrayAspas[i] = new Aspa(aspa); //asigna los punteros y crea las instancias

		//aspasNode->roll(Degree((360 / numAspas) * i));
		arrayAspas[i]->getAspa()->roll(Degree((360 / numAspas) * i));
		arrayAspas[i]->getAdorno()->roll(Degree(-(360 / numAspas) * i));
		//mSM->getSceneNode("adorno" + std::to_string(i))->roll(Degree(-(360 / numAspas) * i));

		/*aspasNode->createChildSceneNode("aspa_" + std::to_string(i));

		aspasNode->getChild("aspa_" + std::to_string(i))->createChild("tablero_" + std::to_string(i));
		Ogre::Entity* tabla = aspasNode->getCreator()->createEntity("cube.mesh");
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

		mSM->getSceneNode("aspa_" + std::to_string(i))->roll(Degree((360 / numAspas) * i));
		mSM->getSceneNode("adorno_" + std::to_string(i))->roll(Degree(-(360 / numAspas) * i));*/
	}
};

void AspasMolino::giro(Ogre::Real time) {
	for (int i = 0; i < numAspas; i++)
	{
		arrayAspas[i]->giro(time);
	}
}
void AspasMolino::retraEje() {
	ejeNode->translate(0, -1, 0, Ogre::Node::TS_LOCAL);
}
void AspasMolino::adornosGone() {
	for (int i = 0; i < numAspas; i++)
	{
		arrayAspas[i]->adornoGone();
	}
}

