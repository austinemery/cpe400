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
	#include <sys/time.h>
	#include <cassert>
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
			/**
			  *@name PacketObject
			  *
			  *@brief Constructor for the PacketObject class, takes in a message to set to message.
			  *		
			  */
			//
			PacketObject( const int& );
			/**
			  *@name ~PacketObject
			  *
			  *@brief Deconstructor for the PacketObject class, deconstructs the object.
			  *		
			  */
			//
			~PacketObject();
			/**
			  *@name getSize
			  *
			  *@brief Returns the byteSize of the object.
			  *		
			  */
			//
			int getSize();
			/**
			  *@name getMessage
			  *
			  *@brief Returns the message of the object.
			  *		
			  */
			//
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
			/**
			  *@name DroneObject
			  *
			  *@brief Constructor for the DroneObject class. Sets up the info of an individual drone.
			  *		
			  */
			//
			DroneObject( const int & = (-1) , const int & = 0 );
			/**
			  *@name ~DroneObject
			  *
			  *@brief Deconstructor for the DroneObjecct class.
			  *		
			  */
			//
			~DroneObject();
			/**
			  *@name getBattery
			  *
			  *@brief Returns the remainingBattery of the object.
			  *		
			  */
			//
			float getBattery();
			/**
			  *@name remainingPackageSpace
			  *
			  *@brief Returns 16 minus totalPackageSize so we can see how much package space is left to use.
			  *		
			  */
			//
			int remainingPackageSpace();
			/**
			  *@name getTotalPackages
			  *
			  *@brief Returns the totalPackagesSent of the object.
			  *		
			  */
			//
			int getTotalPackages();
			/**
			  *@name hasPackage
			  *
			  *@brief Checks if drone has a package to send, if it does, returns true. Returns false otherwise.
			  *		
			  */
			//
			bool hasPackage();
			/**
			  *@name getID
			  *
			  *@brief Returns the id of the object.
			  *		
			  */
			//
			int getID();
			/**
			  *@name getRank
			  *
			  *@brief Returns the rankinFleet of the object.
			  *		
			  */
			//
			int getRank();
			/**
			  *@name getLeftNeighbor
			  *
			  *@brief Returns the left neighbor of the object, which is stored in edges[0][1].
			  *		
			  */
			//
			int getLeftNeighbor();
			/**
			  *@name getRightNeighbor
			  *
			  *@brief Returns the right neighbor of the object, which is stored in edges[0][2].
			  *		
			  */
			//
			int getRightNeighbor();
			/**
			  *@name getLeftNeighborDistance
			  *
			  *@brief Returns the left neighbor's distance away from the object, which is stored in edges[1][1].
			  *		
			  */
			//
			int getLeftNeighborDistance();
			/**
			  *@name getRightNeighborDistance
			  *
			  *@brief Returns the right neighbor's distance away from the object, which is stored in edges[1][2].
			  *		
			  */
			//
			int getRightNeighborDistance();
			/**
			  *@name getCCDistance
			  *
			  *@brief Returns the Comand Center's distance away from the object, which is stored in edges[1][0].
			  *		
			  */
			//
			int getCCDistance();
			/**
			  *@name setCCDistance
			  *
			  *@brief Sets the Comand Center's distance away from the object, which is stored in edges[1][0].
			  *		
			  */
			//
			void setCCDistance(int);
			int getWeight();
			/**
			  *@name setLeftNeighborDistance
			  *
			  *@brief Sets the left neighbor's distance away from the object, which is stored in edges[1][1].
			  *		
			  */
			//
			void setLeftNeighborDistance(int);
			/**
			  *@name getRightNeighborDistance
			  *
			  *@brief Sets the right neighbor's distance away from the object, which is stored in edges[1][1].
			  *		
			  */
			//
			void setRightNeighborDistance(int);
			/**
			  *@name ableToReceivePackage
			  *
			  *@brief Uses remainingPackageSpace to determine if drone is able to recieve a package, returns bool.
			  *		
			  */
			//
			bool ableToReceivePackage( const int );
			/**
			  *@name sendPackage
			  *
			  *@brief 
			  *		
			  */
			//
			bool sendPackage( DroneObject& neighbor );
			// *
			//   *@name receivePackage
			//   *
			//   *@brief 
			//   *		
			  
			// //
			// bool receivePackage( const int** events );
			/**
			  *@name updateBattery
			  *
			  *@brief updates the battery based on a certain situation
			  *		
			  */
			//
			void updateBattery( const int& );
			/**
			  *@name updateEdgeDistance
			  *
			  *@brief updates the edge distance to a drone base on a selection and distance passed in.
			  *		
			  */
			//
			void updateEdgeDistance( const int& , const int& );
			/**
			  *@name collectPackage
			  *
			  *@brief Saves the encountered data to the package vector.
			  *		
			  */
			//
			void collectPackage(PacketObject&);


			/**
			  *@name operate= overload
			  *
			  *@brief copies all the information from one drone to another.
			  *		
			  */
			//
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
			int fleetTotal;
			int personalWeight;


		friend class CCObject;
	};

	/*
	 * COMMAND & CONTROL
	 */
	class CCObject
	{
		public:
			/**
			  *@name CCObject
			  *
			  *@brief Constructor for the CCObject class. Default amount of drones is 5.
			  *		
			  */
			//
			CCObject( const int& = 5 );
			/**
			  *@name ~CCObject
			  *
			  *@brief Deconstructor for the CCObject class.
			  *		
			  */
			//			
			~CCObject();
			/**
			  *@name printFleet
			  *
			  *@brief Prints all of the drones, with info on each drone, that are commanded by this object.
			  *		
			  */
			//
			bool printFleet();
			/**
			  *@name broadcast
			  *
			  *@brief 
			  *		
			  */
			//
			int broadcast();
			/**
			  *@name receivePackage
			  *
			  *@brief 
			  *		
			  */
			//
			bool receivePackage();
			/**
			  *@name proactiveSimulation
			  *
			  *@brief Runs the proactive simulation which has a OLSR settup. Uses a "graph" that CCObject holds
			  *		  and each drone will be able to see the graph. The graph holds the information of the 
			  *		  layout of the drones. Will be used to rout messages to the Command Center.		
			  *
			  */
			//
			void proactiveSimulation(  const int events[][2]  );
			/**
			  *@name reactiveSimulation
			  *
			  *@brief AODV
			  *		
			  */
			//
			void reactiveSimulation(  const int events[][2]  );
			/**
			  *@name droneAcceptableBatteryLife
			  *
			  *@brief Checks all of the drones for acceptable battery life. If any drone's battery is less
			  *		  than 10, then the function returns false.
			  *		
			  */
			//
			bool droneAcceptableBatteryLife();
			/**
			  *@name needToSwap
			  *
			  *@brief Checks if two drones need to swap to save battery life. (The outer drones will be using
			  *       more battery because they move a greater distance)
			  *		
			  */
			//
			bool needToSwap( DroneObject& , DroneObject& );
			/**
			  *@name swapDronePosition
			  *
			  *@brief Swaps two drones in the fleet.
			  *		
			  */
			//
			void swapDronePosition( const int& , const int& );
			/**
			  *@name getDT
			  *
			  *@brief Uses getCurrentTimeMillis to produce a delta time milliseconds and returns that value.
			  *		  Used for timing.
			  *		
			  */
			//		
			unsigned int getDT();
			/**
			  *@name getCurrentTimeMillis
			  *
			  *@brief Used by getDT, access the computers clock and returns a time in millisecs. 
			  *		
			  */
			//
			long long getCurrentTimeMillis();

			void resetSimulation();
			void incrementSimulationIndex();
			void totalSimulationSummary();
		private:
			int totalFleetSize;
			int distanceBetweenDrones;
			
			vector<DroneObject> fleet;
			long long m_currentTimeMillis;
			int** proactiveArray;


			int currentSimulationIndex;
			int proactiveTotalMessagesReceived[100];
			int reactiveTotalMessagesReceived[100];
			long long proactiveSimulationTime[100];
			long long reactiveSimulationTime[100];
		//friend class CCObject;
	};
//