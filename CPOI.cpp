/* Generated by Together */

#include "CPOI.h"




/**
 * string array for the t_poi
 */
const char* POIType_ar[] = {
		"Restaurant",
		"Krankenhaus",
		"School",
		"Monument",
		"BusStation",
		"NO POI exists",
};


void CPOI::print(int format)
{
	/**
	 * print the POI in deg mm ss format.
	 */
	cout<< "Point Of Interest===>"<<endl;
	cout<<"------------------------------------------"<<endl;
	cout << "of type "<<POIType_ar[m_type] << ": \t" << m_description<< endl;
	//CWayPoint::print(DEGMMSS_FORMAT);
	cout<<*this<<endl;
}


CPOI::CPOI(t_poi type, string name, string description, double latitude, double longitude)
{
	m_type = type;
	m_description = description;
	CWayPoint::setListType(Default_e);
	/**
	 * check for the co-ordinates and assign the name.
	 */
	CWayPoint::set(name,latitude,longitude);
	//m_latitude = latitude;
	//m_longitude = longitude;
	//m_name = name;
}

void CPOI::getAllDataByReference(double& latitude, double& longitude, string& name, t_poi& type, string& description) const
{

	/**
	 * pass all the member values.
	 */
	#if 0
	latitude = m_latitude;
	longitude = m_longitude;
	cout<<"1"<<endl;
	name = m_name;
	cout<<"2"<<endl;
	type = m_type;
	description = m_description;
#endif

	latitude = this->getLatitude();//m_latitude;
		longitude = this->getLongitude();//m_longitude;
		name = this->getName();//m_name;
		type = m_type;
		description = m_description;

}

CPOI::CPOI()
{
	m_type = DefaultPOI_e;
	m_description = "No Description Exists";
}

CPOI::~CPOI()
{

}

ostream& operator << (ostream& os,const CPOI& poi)
{
	double latitdue,longitude;
	string name,description;
	t_poi poi_type;
	/**
	 * get all the data of poi by reference.
	 */
	poi.getAllDataByReference(latitdue,longitude,name,poi_type,description);

	/**
	 * create an object of Cwaypooint wit the details extracted from the input poi.
	 */
	CWayPoint obj(name,latitdue,longitude);
	os<<obj<<endl;

	return os;
}

