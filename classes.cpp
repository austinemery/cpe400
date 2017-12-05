// Class Implementation File Information /////////////////////////////
/**
  *@file classes.cpp
  *
  *@brief contains the implementation of data memebers of Packet,
  *		Drone, and Command & Control Classes
  *
  *@details None
  *
  *@version 1.00
  *			Mercedes Anderson (21 Nov 2017)
  *			Austin Emery (21 Nov 2017)
  *			Nickolas Johnson (21 Nov 2017)
  *
  *@note 
  */
//
//
// Included Files //////////////////////////////
//

	#include "classes.h"
	using namespace std;
//
//
// Class Function Implementations //////////////
//
	/*
	 * PACKET
	 */
 	
 	/**
	  *@brief 
	  *
	  *@details 
	  *
	  *@pre 
	  *
	  *@post 
	  *
	  *@par 
	  *
	  *@exception None
	  *
	  *@return None
	  *
	  *@return None
	  *
	  *@note None
	  *
	  *@param[in] None
	  *
	  *@param[out] None
	  */
	PacketObject::PacketObject( const int& size, const int& incomingMessage )
	{
		byteSize = size;
		message = incomingMessage;
	}

	PacketObject::~PacketObject()
	{
		byteSize = 0;
		message = 0;
	}

	int PacketObject::getSize()
	{
		return byteSize;
	}

	int PacketObject::getMessage()
	{
		return message;
	}

	/*
	 * DRONE
	 */
	DroneObject::DroneObject( const int& positionInFleet , const int& totalInFleet )
	{
		id = positionInFleet + 1;
		indexOfLastPacket = -1;
		totalPackageSize = 0;
		totalPackagesSent = 0;
		remainingBattery = 100;
		rankInFleet = positionInFleet;

		if( totalInFleet == 0 )		//This drone is not connected to anyone
		{
			for( int row = 0 ; row < 2 ; row++ )
			{
				for( int col = 0 ; col < 3 ; col++ )
				{
					edges[row][col] = -1;
				}
			}
			//connection to C&C
			edges[0][0] = -10;
			edges[1][0] = -1;

		} else if( positionInFleet == ( totalInFleet - 1 ))	//This is the last drone in the brigade
		{
			//connection to C&C
			edges[0][0] = -10;
			edges[1][0] = -1;

			//drone on left
			edges[0][1] = totalInFleet - 2;
			edges[1][1] = -1; //Don't know how far. Just that it's connected.


			//NO DRONE ON RIGHT
			edges[0][2] = -1;
			edges[1][2] = -1; 

		} else if( positionInFleet == 0 ) //This is the first drone in the brigade
		{
			//connection to C&C
			edges[0][0] = -10;
			edges[1][0] = -1;

			//NO DRONE ON LEFT
			edges[0][1] = -1;
			edges[1][1] = -1; //Don't know how far. Just that it's connected. 

			//drone to the right
			edges[0][2] = 1;
			edges[1][2] = -1;

		} else
		{	
			//connection to C&C
			edges[0][0] = -10;
			edges[1][0] = -1;

			//drone on the left
			edges[0][1] = positionInFleet - 1;
			edges[1][1] = -1; //Don't know how far. Just that it's connected. 
			
			//drone on the right
			edges[0][2] = positionInFleet + 1;
			edges[1][2] = -1; //Don't know how far. Just that it's connected. 

		}	
	}
	DroneObject& DroneObject::operator=(const DroneObject& rightHandSide )
	{
		if( &rightHandSide != this )
		{
			for( int row = 0 ; row < 2 ; row++ )
			{
				for( int col = 0 ; col < 3 ; col++ )
				{
					edges[row][col] = rightHandSide.edges[row][col];
				}
			}

			package = rightHandSide.package;
			indexOfLastPacket = rightHandSide.indexOfLastPacket;		
			totalPackageSize = rightHandSide.totalPackageSize;
			totalPackagesSent = rightHandSide.totalPackagesSent;
			rankInFleet = rightHandSide.rankInFleet;
			remainingBattery = rightHandSide.remainingBattery;
			id = rightHandSide.id;
		}

		return *this;
	}
	DroneObject::~DroneObject()
	{
		id = -1;
		totalPackageSize = 0;
		totalPackagesSent = 0;
		remainingBattery = 0;
		indexOfLastPacket = -1;
		rankInFleet = -1;

		for( int row = 0 ; row < 2 ; row++ )
		{
			for( int col = 0 ; col < 3 ; col++ )
			{
				edges[row][col] = -1;
			}
		}

	}

	//Get info
	float DroneObject::getBattery()
	{
		return remainingBattery;
	}
	int DroneObject::remainingPackageSpace()
	{
		return 16 - totalPackageSize; //The packages can only be 8 bytes long
	}
	bool DroneObject::hasPackage()
	{
		if( package.empty() )
		{
			return false;
		} else
		{
			return true;
		}
	}
	int DroneObject::getID()
	{
		return id;
	}
	int DroneObject::getRank()
	{
		return rankInFleet;
	}
	int DroneObject::getTotalPackages()
	{
		return totalPackagesSent;
	}
	int DroneObject::getLeftNeighbor()
	{
		return edges[0][1];
	}
	int DroneObject::getRightNeighbor()
	{
		return edges[0][2];
	}
	int DroneObject::getLeftNeighborDistance()
	{
		return edges[1][1];
	}
	int DroneObject::getRightNeighborDistance()
	{
		return edges[1][2];
	}
	int DroneObject::getCCDistance()
	{
		return edges[1][0];
	}
	void DroneObject::setCCDistance(int distance)
	{
		edges[1][0] = distance;
	}
	void DroneObject::setLeftNeighborDistance(int distance)
	{
		edges[1][1] = distance;
	}
	void DroneObject::setRightNeighborDistance(int distance)
	{
		edges[1][2] = distance;
	}
	//Update
	void DroneObject::updateBattery( const int& situation )
	{
		switch( situation )
		{
			case 0: // 0: A cycle has gone by, account for battery life drain
					
					remainingBattery--;
						//Battery is drained by 1% for idle movement through air
					break;
			case 1: // 1: A message has been received
					
					remainingBattery -= package[indexOfLastPacket].getSize() * 0.1;
						//Every byte received takes 0.1 off the battery.
					break;
			case 2: // 2: A message has been sent. Messages should only be sent to the left
					
					if( rankInFleet == 0 ) //if we're the first drone in line, send to C&C
					{
						remainingBattery -= edges[1][0] * 0.1;
					} else
					{
						remainingBattery -= edges[1][1] * 0.1;							
					}
						//Every foot a message is sent takes 0.1 off the battery.
					break;
			case 3: // 3: Direct Message to C&C

					remainingBattery -= edges[1][0] * 0.1;
						//Every foot a message is sent takes 0.1 off the battery.
					break;
			case 4: // 4: Traded positions with counterpart

					remainingBattery -= 15;
						//Battery is drained 5% for tradiing information with counterpart on cross over
						//Battery is drained 10% for relocation
					break;				
		}
	}
	void DroneObject::updateEdgeDistance( const int& neighbor, const int& newDistance )
	{
		//0 for C&C
		//1 for left
		//2 for right
		edges[1][neighbor] = newDistance;
	}

	//Send info
	bool DroneObject::sendPackage()
	{

	}
	bool DroneObject::receivePackage()
	{

	}
	bool DroneObject::ableToReceivePackage( const int incomingSize )
	{
		if( (totalPackageSize + incomingSize) < 16 )
		{
			return true;
		} else
		{
			return false;
		}
	}
	/*
	 * COMMAND & CONTROL
	 */
	CCObject::CCObject( const int& numberOfDrones )
	{
			totalFleetSize = numberOfDrones;
			distanceBetweenDrones = 100 / numberOfDrones; 
				//Keeping this an int in order to account for errors in drone positions
			totalMessagesReceived = 0;

			for( int index = 0 ; index < numberOfDrones ; index++ )
			{
				fleet.push_back( DroneObject( index , numberOfDrones ) );				
			}

	}
	CCObject::~CCObject()
	{

	}

	bool CCObject::printFleet()
	{
		for( int index = 0 ; index < totalFleetSize ; index++ )
		{
			cout << "*********************************" << endl;
			cout << "* Rank: " << fleet[index].getRank() << "			*" << endl;
			cout << "*********************************" << endl; 
			cout << "ID: " << fleet[index].getID() << endl;
			cout << "Battery Life: " << fleet[index].getBattery() << endl;
			cout << "Total Packages Sent: " << fleet[index].getTotalPackages() << endl;
			cout << "Left Neighbor: " << fleet[index].getLeftNeighbor() << endl;
			cout << "Right Neighbor: " << fleet[index].getRightNeighbor() << endl;
			cout << endl;
		}
	}
	int CCObject::broadcast()
	{

	}
	bool CCObject::receivePackage()
	{

	}

	void CCObject::proactiveSimulation()
	{
		//swapDronePosition( 0 , totalFleetSize-1 );

		//Dynamic array that stores information on the whole graph. If the drones can see eachother, the distance will be in the index
		proactiveArray = new int*[totalFleetSize];
		for(int index = 0; index < totalFleetSize; index++)
		{
    		proactiveArray[index] = new int[totalFleetSize];
		}

		//init to 0
		for (int index = 0; index < totalFleetSize; ++index)
		{
			for (int jindex = 0; jindex < totalFleetSize; ++jindex)
			{
				proactiveArray[index][jindex] = 0;
			}
		}

		//construct "graph"
		for (int index = 0; index < totalFleetSize; index++)
		{
			//the inner drone
			if (index == 0)
			{
				proactiveArray[index][fleet[index].getRightNeighbor()] = distanceBetweenDrones;
			}
			//the outer drone
			else if(index == totalFleetSize - 1)
			{
				proactiveArray[index][fleet[index].getLeftNeighbor()] = distanceBetweenDrones;
			}
			//the rest of the drones
			else
			{
				proactiveArray[index][fleet[index].getRightNeighbor()] = distanceBetweenDrones;
				proactiveArray[index][fleet[index].getLeftNeighbor()] = distanceBetweenDrones;
			}
		}

		//Print "graph"
		cout << "START OF Proactive Array" << endl;
		for (int index = 0; index < totalFleetSize; ++index)
		{
			for (int jindex = 0; jindex < totalFleetSize; ++jindex)
			{
				cout << proactiveArray[index][jindex] << ' ';
			}
			cout << endl;
		}
		cout << "END OF Proactive Array" << endl;

    	while( droneAcceptableBatteryLife() )
    	{
			//On message get
				//can you receive a message?
					// Y/N
				//Y: send package
				//N: buffer package



			//Update drones
			for (int index = 0; index < totalFleetSize; index++)
			{
				fleet[index].updateBattery(0);
			}
    	}
	}
	void CCObject::reactiveSimulation()
	{
		//While the drones all have more than 10% of their battery.
		while( droneAcceptableBatteryLife() )
		{
			//Check to make sure drones don't need to trade places.
			for( int index = 0 ; index < totalFleetSize ; index++ )
			{

			}
			//Node requests to communicate to neighbors
				//re-establish all pathes

			//On message get
				//can you receive a message?
					// Y/N
				//Y: send package
				//N: buffer package



			//Update drones
			
		}
	}
	bool CCObject::droneAcceptableBatteryLife()
	{
		for( int index = 0 ; index < totalFleetSize ; index++ )
		{
			if( fleet[index].getBattery() < 10.0 )	//This amount is subject to change.
			{
				return false;
			}
		}

		return true;
	}
	bool CCObject::needToSwap( DroneObject& innerDrone, DroneObject& outerDrone)
	{
		if(( innerDrone.getBattery() + outerDrone.getBattery() < 100 ) && (innerDrone.getBattery() > outerDrone.getBattery()))
		{
			return true;
		} 
		else
		{
			return false;
		}
	}
	void CCObject::swapDronePosition( const int& goingRight, const int& goingLeft )
	{
		DroneObject holding;
		int holdValue = 0;


		holding = fleet[goingRight];
		fleet[goingRight] = fleet[goingLeft];
		fleet[goingLeft] = holding;


		//Update Rank
		fleet[goingRight].rankInFleet = goingRight;
		fleet[goingLeft].rankInFleet = goingLeft;

		//Update Neighbors
		for( int row = 0 ; row < 2 ; row++ )
		{
			for( int col = 0 ; col < 3 ; col++ )
			{
				holdValue = fleet[goingRight].edges[row][col];
				fleet[goingRight].edges[row][col] = fleet[goingLeft].edges[row][col];
				fleet[goingLeft].edges[row][col] = holdValue;
			}
		}

		//Update Battery
		fleet[goingRight].updateBattery(4);
		fleet[goingLeft].updateBattery(4);

	}

	unsigned int CCObject::getDT()
	{
	  long long TimeNowMillis = GetCurrentTimeMillis();
	  assert(TimeNowMillis >= m_currentTimeMillis);
	  unsigned int DeltaTimeMillis = (unsigned int)(TimeNowMillis - m_currentTimeMillis);
	  m_currentTimeMillis = TimeNowMillis;
	  return DeltaTimeMillis;
	}

	long long CCObject::GetCurrentTimeMillis()
	{
	  timeval t;
	  gettimeofday(&t, NULL);
	  long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
	  return ret;
	}
//