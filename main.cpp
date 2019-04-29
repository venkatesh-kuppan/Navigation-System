// GIT-Labor
// main.h

////////////////////////////////////////////////////////////////////////////////
// Header-Dateien
#include <iostream>		// Header für die Standard-IO-Objekte (z.B. cout, cin)
#include <stdlib.h>
// TODO: Fügen Sie hier weitere benötigte Header-Dateien der
// Standard-Bibliothek ein z.B.
// #include <string>

using namespace std;	// Erspart den scope vor Objekte der
						// C++-Standard-Bibliothek zu schreiben
						// z.B. statt "std::cout" kann man "cout" schreiben

// Inkludieren Sie hier die Header-Files Ihrer Klassen, z.B.
// #include "CFraction.h"
#include "CNavigationSystem.h"
#include "CCSVManager.h"

//#define PersistantEnable

int main (void)
{
	/**
	 * create a navigation class object and run the test cases.
	 */
	CNavigationSystem NavObj;
	//NavObj.run();


	/**
	 * persistance test.
	 */
	string FileName = "Database";
	CCSVManager CSVObj;
	CSVObj.setMediaName(FileName);
	CWpDatabase WpDBObj;
	CPOIDataBase poiDBObj;
	/**
	 * add elements to WpDB
	 */

	CWayPoint Wp2("Delhi",85.20,76.12);
	WpDBObj.addWayPoint(Wp2);
	CWayPoint Wp1("Mumbai",45.20,63.12);
	WpDBObj.addWayPoint(Wp1);
	CWayPoint Wp3("Patna",34.65,78.9);
	WpDBObj.addWayPoint(Wp3);

	cout<<"in main claass size of Wp list = "<<WpDBObj.getWaypointMap().size()<<endl;
	//WpDBObj.print();
	/**
	 * add POI to POIDB
	 */
	CPOI Monument_POI(Monument_e,"Gateway Of India","Historical place",25.31,89.14);
	poiDBObj.addPOI(Monument_POI);
	CPOI KrankenHausPOI(Krankenhaus_e,"Krankenhaus","TK- Always for you",53.18,73.32);
	poiDBObj.addPOI(KrankenHausPOI);
	//CPOI HotelPOI(Restaurant_e,"Contel","Budget Hotel in Darmstadt",33.61,43.07);

	cout<<"in main claass size of poi list = "<<poiDBObj.getPOIMap().size()<<endl;
	//poiDBObj.print();

	/*for(map<string, CPOI>::iterator it = poiDBObj.getPOIList().begin(); it != poiDBObj.getPOIList().end(); ++ it)
	{
		cout <<it->second;
	}*/



	/**
	 * write data to the file
	 */


	bool WriteSuccess_bo = CSVObj.writeData(WpDBObj,poiDBObj);
	if(WriteSuccess_bo == 1)
	{
		cout<<"write completed successfully"<<endl;
	}


	bool ReadSuccess_bo = CSVObj.readData(WpDBObj,poiDBObj,CPersistentStorage::Merge_e);
	if(ReadSuccess_bo == 1) {
		cout<<"read completed successfully"<<endl;
	}

	WpDBObj.print();
	poiDBObj.print();

	return 0;
}
