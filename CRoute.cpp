/* Generated by Together */


#include "CRoute.h"




CRoute::CRoute()
{
	m_nextPOI = 0;
	m_nextWp = 0;
	m_pPOIDatabase = NULL;
	m_pWpDatabase = NULL;
	m_pRoute.clear();
}

CRoute::CRoute(CRoute const& origin)
{
	m_nextPOI = origin.m_nextPOI;
	m_nextWp = origin.m_nextWp;
	m_pPOIDatabase= new CPOIDataBase;
	m_pPOIDatabase = origin.m_pPOIDatabase;
	m_pWpDatabase = new CWpDatabase;
	m_pWpDatabase = origin.m_pWpDatabase;
	m_pRoute = origin.m_pRoute;
}

CRoute::~CRoute()
{
	//delete[] m_pWaypoint;
	//delete[] m_pPOI;
}

void CRoute::connectToPoiDatabase(CPOIDataBase* pPOIDatabase)
{
	/**
	 * Connect to the main database of POIs
	 */
	if(pPOIDatabase != NULL) {
		m_pPOIDatabase = pPOIDatabase;
	}
	else {
		cout<< "POI Database source incorrect"<<endl;
	}
}

void CRoute::connectToWpDatabase(CWpDatabase* pWpDatabase)
{
	/**
	 * Connect to the main database of POIs
	 */
	if(pWpDatabase != NULL)	{
		m_pWpDatabase = pWpDatabase;
	}
	else {
		cout<< "Wp Database source incorrect"<<endl;
	}
}

void CRoute::addWaypoint(string nameWp)
{
	if(m_pWpDatabase != NULL) {

		CWayPoint* ptrToWpDB = NULL;
		/**
		 * check if the waypoint exists in the waypoint DB
		 */
		ptrToWpDB = m_pWpDatabase->getPtrToWaypoint(nameWp);
		/**
		 * check if the return value is not equal to NULL.
		 * if NULL, then display a ERROR message.
		 */
		if(ptrToWpDB != NULL) {
			m_pRoute.push_back(ptrToWpDB);

			/*
			 * increment the variable to keep track of no. of waypoints
			 */
			m_nextWp++;
		}
		else {
			cout<<"ERROR: "<<nameWp<< "  Waypoint not found in database, Waypoint not in the POOL."<<endl;
		}
	}

	else {
		cout<<"Waypoint Database not connected."<<endl;
	}
}

void CRoute::addPoi(string namePOI, string afterWp)
{
	/**
	 * check if the database is valid, i.e. connected to the source?
	 */
	if(m_pPOIDatabase != NULL) {
		/**
		 * search if the POI exists in the POI database.
		 */
		CPOI* ptrToPOIDB = NULL;
		ptrToPOIDB = m_pPOIDatabase->getPtrToPOI(namePOI);
		/**
		 * check if the return value is not equal to NULL, i.e. if the POI is present or not in the POI DB.
		 * if NULL, then display a ERROR message.
		 */
		if(ptrToPOIDB != NULL) {
			/**
			 * if POI is found in DB, add the POI after the waypoint with name afterWp.
			 */
			CWayPointList::reverse_iterator i_rit;
			bool MatchFound = 0;
			for(i_rit = m_pRoute.rbegin(); i_rit != m_pRoute.rend() && MatchFound != 1; ++i_rit)
			{
				/**
				 * search for the waypoint after which the POI needs to be added.
				 */
				//if(((*i_rit)->getName() == afterWp) && ((*i_rit)->getListType() == Waypoint_e)) {
				if(((*i_rit)->getName() == afterWp) && ((m_pPOIDatabase->getPtrToPOI((*i_rit)->getName()) == NULL))) {
					/**
					 * increment the iterator to insert the POI after the Waypoint.
					 */
					m_pRoute.insert(i_rit.base(),ptrToPOIDB);
					MatchFound = 1;
					/**
					 * increment the variable to keep track of the no. of POIs in the route
					 */
					m_nextPOI++;
				}
			}
			if(MatchFound == 0) {
				/**
				 * The waypoint doesn't exist in the Wp DB, but the POI exists in the POI DB.
				 * Hence add the POI to the end of the list.
				 */
				cout<<" ERROR:: The afterWp "<<afterWp<<" not found in DB"<<endl;
				m_pRoute.push_back(ptrToPOIDB);
				/**
				 * increment the variable to keep track of the no. of POIs in the route
				 */
				m_nextPOI++;
			}
		}
		else {
			cout<<"ERROR: "<<namePOI<< "  POI not found in database, POI not in the POOL."<<endl;
		}
	}
	else {
		cout<<" POI Database not connected"<<endl;
	}
}

double CRoute::getDistanceNextPoi(CWayPoint const& wp, CPOI& poi)
{
	double DistanceOfNextPOI_ar[m_pRoute.size()];
	int indexOfLeastDistPOI = 0;
	CPOI* pLeastDistPoi;
	/**
	 * check if no POIs exists in the route
	 */
	if(m_nextPOI == 0) 	{
		/*
		 * assign a default value for error handling
		 */
		DistanceOfNextPOI_ar[indexOfLeastDistPOI] = DEFAULT_VALUE_FOR_NO_POI;
		cout<< "NO POIs exist in defined route. Add new POIs and try again"<<endl;
	}
	else {
	 //pLeastDistPoi;// = NULL;
		//for (unsigned int i = 0; ((i < m_pRoute.size()) && (m_nextPOI != 0)) ; i++)
		int i = 0;
		for(CWayPointList::const_iterator ii = m_pRoute.begin(); ii != m_pRoute.end(); ++ii)
		{
			 pLeastDistPoi = dynamic_cast<CPOI*>(*ii);
			/**
			 * check if the POI is valid, if not then continue.
			 */

			if(pLeastDistPoi != NULL) {


				/**
				 * calculate the distance of next POI from the entered coordinates.
				 */
				DistanceOfNextPOI_ar[i] = (*ii)->calculateDistance(wp);
				/**
				 * find the index least element in the array of DistanceofNextPOI
				 */
				cout<<"DIst = "<<DistanceOfNextPOI_ar[i] <<endl;
				if(DistanceOfNextPOI_ar[i] < DistanceOfNextPOI_ar[indexOfLeastDistPOI]) {
					indexOfLeastDistPOI = i;
					poi = *pLeastDistPoi;

				}
			}

			/**
			 * the iterator points to the waypoint, so iterate to the next POI.
			 */
		}
		cout << "indes = "<<indexOfLeastDistPOI<<endl;
		/**
		 * Assign the poi address  of the least distance calculated
		 */

	}
	/**
	 * return the least distance found.
	 */
	return DistanceOfNextPOI_ar[indexOfLeastDistPOI];
}

void CRoute::print()
{
	cout<<"Your route contains "<<m_nextWp<<" way points and "<<m_nextPOI<<" Point of Interests"<<endl<<endl;

	/**
	 * print the waypoints in
	 *  the route
	 */
	CWayPointList::iterator it;
	for (it = m_pRoute.begin(); it != m_pRoute.end(); ++it)
	{
		//(*it)->print(DEGMMSS_FORMAT);

		CPOI* pPOI = dynamic_cast<CPOI*>(*it);
		if(pPOI != NULL)
			cout<<(*pPOI)<<endl;
		else
			cout<<(**it)<<endl;

	}
#if 0
	/**
	 * print the valid POIs in the route.
	 */
	for (unsigned int i=0; i<m_maxPOI && m_nextPOI != 0; i++)
	{
		/**
		 * check if the POI exists.
		 */
		if(m_pPOI[i] != NULL )
		{
			m_pPOI[i]->print();
		}
	}
#endif
}

CRoute& CRoute::operator = (const CRoute& Route)
{
	m_nextPOI = Route.m_nextPOI;
	m_nextWp = Route.m_nextWp;
	m_pPOIDatabase = Route.m_pPOIDatabase;
	m_pRoute = Route.m_pRoute;
	m_pWpDatabase = Route.m_pWpDatabase;
	return *this;
}

CRoute& CRoute::operator += (const string& name)
{
	/**
	 * check if the name exists as POI or a waypoint and add it to route.
	 * if the name exists in both i.e Waypoint as well as POI, then add it after the waypoint.
	 */
	addWaypoint(name);
	addPoi(name,name);
	return *this;
}

CRoute CRoute::operator + (const CRoute& RouteY)
{
	/**
	 * check if the data bases are valid
	 */
	if(RouteY.m_pPOIDatabase != NULL && RouteY.m_pWpDatabase != NULL) {
		/**
		 * check if both the routes are connected to the same database,
		 */
		if(m_pPOIDatabase == RouteY.m_pPOIDatabase && m_pWpDatabase == RouteY.m_pWpDatabase) {
			/**
			 * create a new route and assign all the concatenation of the two routes to the new routes.
			 */
			CRoute newRoute;
			newRoute.m_nextPOI = m_nextPOI + RouteY.m_nextPOI;
			newRoute.m_nextWp = m_nextWp + RouteY.m_nextWp;
			/**
			 * Add the new route to the end of the local route, i.e.newRoute
			 */
			newRoute.m_pRoute.insert(newRoute.m_pRoute.end(),RouteY.m_pRoute.begin(),RouteY.m_pRoute.end());
			newRoute.m_pRoute.insert(newRoute.m_pRoute.end(),this->m_pRoute.begin(),this->m_pRoute.end());
			/**
			 * return the newRoute.
			 */
			return newRoute;
		}
	}
	/**
	 * return an empty object.
	 */
	return CRoute();
}


/**
 * stubs provided for testing.
 */
int CRoute::getNxtWp(void)
{
	return m_nextWp;
}

const CRoute::CWayPointList& CRoute::getList()
{
	return m_pRoute;
}
