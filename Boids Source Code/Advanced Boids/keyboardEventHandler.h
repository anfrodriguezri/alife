#ifndef KEYBOARDEVENTHANDLER_H
#define KEYBOARDEVENTHANDLER_H
#include <osgGA/GUIEventHandler>

using namespace osgGA;

class InputDeviceStateType
{
public:
	InputDeviceStateType::InputDeviceStateType() : 
	  expandWallsRequest(false), shrinkWallsRequest(false), addObstacle(false),
		  cleanObstacles(false), addPredator(false), removePredator(false),
		  addMoreBoids(false), removeBoids(false), headToCenter(false), 
		  headToRandomPos(false), randomRelocate(false), spawnFollowBoid(false), 
		  removeObstacles(false), seperationMode(false), alignmentMode(false), 
		  cohesionMode(false), predatorsHunt(false), predatorSep(false), 
		  acceleratePlayer(false), decceleratePlayer(false), playerTurnLeft(false), 
		  playerTurnRight(false) {}
	  bool expandWallsRequest;
	  bool shrinkWallsRequest;
	  bool addObstacle;
	  bool cleanObstacles;
	  bool addPredator;
	  bool removePredator;
	  bool addMoreBoids;
	  bool removeBoids;
	  bool headToCenter;
	  bool headToRandomPos;
	  bool randomRelocate;
	  bool spawnFollowBoid;
	  bool removeObstacles;
	  bool seperationMode;
	  bool alignmentMode;
	  bool cohesionMode;
	  bool predatorsHunt;
	  bool predatorSep;
	  bool acceleratePlayer;
	  bool decceleratePlayer;
	  bool playerTurnLeft;
	  bool playerTurnRight;
};

class myKeyboardEventHandler : public GUIEventHandler
{
public:
	myKeyboardEventHandler(InputDeviceStateType* tids)
	{
		InputDeviceState = tids;
	}
	virtual bool handle(const GUIEventAdapter& ea, GUIActionAdapter&);
	virtual void accept(osgGA::GUIEventHandlerVisitor& v);
protected:
	InputDeviceStateType* InputDeviceState;
};

#endif