/*
 * CWayPoint.cpp
 *
 *  Created on: Oct 23, 2016
 *      Author: Venkatesh
 */

#include "CWayPoint.h"



CWayPoint::CWayPoint(string name, double latitude, double longitude)
{
	//cout<<"waypoint const call"<<endl;
#ifdef SHOW_DEBUG_DATA
	cout << " CWayPoint : Constructor Block:"<<endl;
	cout << "------------------"<<endl;
#endif
	set(name, latitude, longitude);
	m_WpType = Waypoint_e;
	/**
	 * size of m_latitude = 8 bytes
	 * size of m_longitude = 8 bytes
	 */
#ifdef SHOWADDRESS
	cout<<"address of the calling object="<<this<<endl;
	cout<<"latitude = "<<this->m_latitude <<endl << "longitude="<< this->m_longitude<<endl \
			<<cout <<"name=" << this->m_name<<endl<<endl;
#endif

}


CWayPoint::~CWayPoint()
{
	// TODO Auto-generated destructor stub
}


void CWayPoint::set(string name, double latitude, double longitude)
{
	/**
	 * check for the limit of the coordinates.
	 * if it lies beyond the range, assign zero to the coordinates.
	 */
	m_name = name;
	if(CheckForCoordinates(latitude, longitude))
	{
		m_latitude = latitude;
		m_longitude = longitude;
		//m_name = name;
		//cout<<"m_name = "<<m_name<<endl;
	}
	else
	{
		m_latitude = 0;
		m_longitude = 0;
		//m_name = "NO_NAME";
	}
}

void CWayPoint::print(int format)
{
	switch(format)
	{
	case DEGMMSS_FORMAT:
		cout<<*this<<endl;
		break;
#if 0
		/**
		 * print the co ordinates in deg mm ss format
		 */
		int Degree_of_Location;
		double Mins_of_Location,SS_of_Location;
		/**
		 * transform latitude to deg mm ss
		 */
		transformLatitude2Degreemmss(Degree_of_Location,Mins_of_Location,SS_of_Location);
#ifdef SHOW_DEBUG_DATA
		cout<<"Coordinate in the deg mm ss are as follows"<<endl;
		cout<<"------------------------------------------"<<endl;
#endif
		cout<<"Coordinates for "<<getName() <<" are :"<<endl<< \
				"Latitude = "<<Degree_of_Location<<"degs  "<<Mins_of_Location <<"mins   "<<Mins_of_Location <<"secs  "<<endl;
		/**
		 * transform longitude to deg mm ss
		 */
		transformLongitude2Degreemmss(Degree_of_Location,Mins_of_Location,SS_of_Location);
		cout<<"Longitude = "<<Degree_of_Location<<"degs  "<<Mins_of_Location<<"mins   "<<SS_of_Location<<"secs  "<<endl;
		cout<<"------------------------------------------"<<endl<<endl;

		break;
#endif

	case DECIMAL_FORMAT:
		/**
		 * print the co ordinates in decimal format
		 */
#ifdef SHOW_DEBUG_DATA
		cout<<" Coordinates in the decimal format are as follows"<<endl;
		cout<< "------------------------------------------------"<<endl;
#endif
		cout<<m_name<<" on co-ordinates :"<<endl<< \
				"Latitude="<< m_latitude<<endl<< \
				"Longitude="<< m_longitude<<endl;
		cout<<"------------------------------------------"<<endl<<endl;;
		break;

	default:
		break;
	}
}

void CWayPoint::transformLatitude2Degreemmss(int& deg,double& mm,double& ss) const
{
	/**
	 * obtain the degress.
	 */
	deg = (int)(m_latitude);
	/**
	 * get the decimal part of degrees and then multiply ny 60 to convert to mins
	 */
	mm = (int)((m_latitude - deg) * MULTIPLY_FACTOR_FOR_MINS_SECS);
	/**
	 * get the decimal part of mins and then multiply by 60 to convert to seconds
	 */
	ss = (((m_latitude - deg) * MULTIPLY_FACTOR_FOR_MINS_SECS) - mm)* MULTIPLY_FACTOR_FOR_MINS_SECS;
}

void CWayPoint::transformLongitude2Degreemmss(int& deg, double& mm, double& ss) const
{
	/**
	 * obtain the degress.
	 */
	deg = (int)m_longitude;
	/**
	 * get the decimal part of degrees and then multiply by 60 to convert to mins
	 */
	mm = (int)((m_longitude - deg) * MULTIPLY_FACTOR_FOR_MINS_SECS);
	/**
	 * get the decimal part of mins and then multiply by 60 to convert to seconds
	 */
	ss = (((m_longitude - deg) * MULTIPLY_FACTOR_FOR_MINS_SECS) - mm)* MULTIPLY_FACTOR_FOR_MINS_SECS;
}


string CWayPoint::getName(void) const
{
	/**
	 * return name of the object
	 */
	return m_name;
}

double CWayPoint::getLatitude(void) const
{
	/**
	 * return Latitude of the object
	 */
	return m_latitude;
}

double CWayPoint::getLongitude(void) const
{
	/**
	 * return Longitude of the object
	 */
	return m_longitude;
}

void CWayPoint::getAllDataByReference(string& name, double& latitude, double& longitude)
{
	/**
	 * return all the data by reference
	 */
	name = m_name;
	latitude = m_latitude;
	longitude = m_longitude;
#ifdef SHOWADDRESS
	cout<< "getAllDataByReference::Address of reference variables are as follows:"<<endl;
	cout<<"-------------------------------------------"<<endl;
	cout<< "name = "<<&name<<"\t latitude = "<<&latitude<<"\t longitude = "<<&longitude<<endl;
	cout<<"-------------------------------------------"<<endl<<endl;
#endif
}


double CWayPoint::calculateDistance(const CWayPoint& wp)
{
	/**
	 * calculate the distance between two locations.
	 */
	cout<<"calling caluclate dist"<<endl;
	double Distance = EARTH_RADIUS* CALCULATE_DISTANCE(this,wp);
	return Distance;
}

ostream& operator << (ostream& os,const CWayPoint& Wp)
{

	/**
	 * print the co ordinates in deg mm ss format
	 */
	int Degree_of_Location;
	double Mins_of_Location,SS_of_Location;
	/**
	 * transform latitude to deg mm ss
	 */
	Wp.transformLatitude2Degreemmss(Degree_of_Location,Mins_of_Location,SS_of_Location);
	#ifdef SHOW_DEBUG_DATA
	cout<<"Coordinate in the deg mm ss are as follows"<<endl;
	cout<<"------------------------------------------"<<endl;
	#endif
#ifndef PersistantEnable
	os<<"Coordinates for "<<Wp.getName() <<" are :"<<endl<< \
			"Latitude = "<<Degree_of_Location<<"degs  "<<Mins_of_Location <<"mins   "<<Mins_of_Location <<"secs  "<<endl;
#else
	os<< Wp.getName() <<";" << Wp.getLatitude() <<";"<< Wp.getLongitude() <<endl;
#endif
	/**
	 * transform longitude to deg mm ss
	 */
#ifndef PersistantEnable
	Wp.transformLongitude2Degreemmss(Degree_of_Location,Mins_of_Location,SS_of_Location);
	os<<"Longitude = "<<Degree_of_Location<<"degs  "<<Mins_of_Location<<"mins   "<<SS_of_Location<<"secs  "<<endl;
	os<<"------------------------------------------"<<endl<<endl;
#endif
	return os;
}

Wp_type CWayPoint::getListType()
{
	return m_WpType;
}

void CWayPoint::setListType(Wp_type Type)
{
	m_WpType = Type;
}
