// Class Header File Information//////////////////////////////////////////
/**
  *@file classes.h
  *
  *@brief contains the specification of the following classes: Packet,
  *		Drone, and Command & Control.
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
// Included Files /////////////////////////////////
//
	#include <iostream>
	#include <vector>
  	using namespace std;
//
//
// Class Header Specifications ////////////////////
//
	/*
	 * PACKET
	 */
	class PacketObject
	{
		public:
			//Contructors and Destructors
			PacketObject( const int& , const int& );
			~PacketObject();

			//Get info
			int getSize();
			int getMessage();

		private:
			int byteSize;
			int message;

		friend class DroneObject;
	};

	/*
	 * DRONE
	 */
	class DroneObject
	{
		public:
			//Contructors and Destructors
			DroneObject( const int & = (-1) , const int & = 0 );
			~DroneObject();

			//Get info
			float getBattery();
			int remainingPackageSpace();
			int getTotalPackages();
			bool hasPackage();
			int getID();
			int getRank();
			int getLeftNeigbor();
			int getRightNeighbor();

			//Send info
			bool sendPackage();
			bool receivePackage();

			//Update
			void updateBattery( const int& );
			void updateEdgeDistance( const int& , const int& );

			//Operators
			DroneObject& operator=(const DroneObject&);
		private:
			//create a buffer of 8
			int edges[2][3];			
							//@ most: A drone will have three edges as this is a Fire Brigade Formation
								//And all will have a connection to C&C
							//First Row: The drone it's connected to
							//Second Row: The distance between them (cost)
			vector<PacketObject> package;
			int indexOfLastPacket;		
			int totalPackageSize;
			int totalPackagesSent;
			int rankInFleet;
			float remainingBattery;
			int id;


		friend class CCObject;
	};

	/*
	 * COMMAND & CONTROL
	 */
	class CCObject
	{
		public:
			//Contructors and Destructors
			CCObject( const int& = 5 );
							//Default is five drones
			~CCObject();

			bool printFleet();

			int broadcast();
			bool receivePackage();

			bool droneAcceptableBatteryLife();
			void proactiveSimulation();	//OLSR
			void reactiveSimulation(); //AODV


			void swapDronePosition( const int& , const int& );
		private:
			int totalFleetSize;
			int distanceBetweenDrones;
			int totalMessagesReceived;
			vector<DroneObject> fleet;

		//friend class CCObject;
	};
//