/*
 * CWayPoint.h
 *
 *  Created on: Oct 23, 2016
 *      Author: Venkatesh
 */

#ifndef CWAYPOINT_H_
#define CWAYPOINT_H_

#include <iostream>
#include <stdlib.h>
#include <math.h>


using namespace std;

#undef SHOWADDRESS


/*
 * macros used for the latitude and longitude check
 * -90 <= latitude <= +90
 * -180 <= longitude <= +180
 */
#define LatitudeCheck(latitude) latitude >= -90 && latitude <= 90
#define LongitudeCheck(longitude) longitude >= -180 && longitude <= 180
#define CheckForCoordinates(latitude, longitude) ((LatitudeCheck(latitude)) && (LongitudeCheck(longitude)))


/*
 * macros for deciding the decimal format or the deg mm ss format
 * required for printing the latitudes and longitudes
 */
#define DEGMMSS_FORMAT 2
#define DECIMAL_FORMAT 1

/*
 * macros for the deg mm ss conversion
 */
#define MULTIPLY_FACTOR_FOR_MINS_SECS 60

/*
 * radius of earth = 6378 km
 */
#define EARTH_RADIUS 6378

/*
 * macros for calculating the distacne between two locations
 */
#define pi 3.14
#define DEGREES_TO_RADIANS(ANGLE_IN_DEGREES)	((ANGLE_IN_DEGREES * pi)/180)

#define CALCULATE_DISTANCE(LOC1,LOC2)	(acos(((sin(DEGREES_TO_RADIANS(LOC1->getLatitude()))* sin(DEGREES_TO_RADIANS(LOC2.m_latitude)))) + \
(cos(DEGREES_TO_RADIANS(LOC1->getLatitude())) * cos(DEGREES_TO_RADIANS(LOC2.m_latitude)) * \
		cos(DEGREES_TO_RADIANS(((LOC2.m_longitude)- (LOC1->getLongitude())))))))

typedef enum {
	Waypoint_e,
	Default_e
}Wp_type;
/**
 * The main class for the waypoints in a navigation system.
 * It provides the latitude, longitude and name for the waypoint.
 */
class CWayPoint
{
public:

    /**
     * The default constructor 
     */
	CWayPoint(string name = "NO_NAME", double latitude = 0, double longitude = 0);

    /**
     * The default destructor. 
     */
	~CWayPoint();

    /**
     * The API will check if the co-ordinates lies within the specified range.
     * Ranges are as defined:
     * -90 <=  latitude  <= +90
     * -180 <= longitude <= +180
     * 
     * Arguments:
     * string name :
     *  the name of the waypoint
     * double latitude : the latitude for the waypoint
     * double longitude : the longitude for the waypoint.
     * 
     * Return:
     * None. 
     */
	void set(string name, double latitude, double longitude);

    /**
     * The API returns the name of the waypoint object.
     * 
     * Arguments: 
     * None.
     * 
     * Return:
     * string: The name of the waypoint. 
     */
	string getName() const;

    /**
     * Returns the latitude of the waypint object.
     * 
     * 
     * Arguments: 
     * None.
     * 
     * Return:
     * double: The latitude of the waypoint object. 
     */
	double getLatitude() const;

    /**
     * Returns the longitude of the waypint object.
     * 
     * 
     * Arguments: 
     * None.
     * 
     * Return:
     * double: The longitude of the waypoint object.
     */
	double getLongitude() const;

    /**
     * API to get all the protected data of the class. 
     */
	void getAllDataByReference(string &name, double &latitude, double &longitude);

    /**
     * The API calculates the distance between two waypoints.
     * 
     * 
     * Arguments:
     * 
     * CWayPoint &wp[IN Parameter] : the reference of the waypoint object from where the distance needs to be calculated.
     * 
     * Return:
     * double: the distance between the two waypoints.
     */
	double calculateDistance(const CWayPoint &wp);

    /**
     * API to print the waypoints in two formats:
     * 1. Deg minutes seconds format
     * 2. Decimal format 
     */
	virtual void print(int format);

	friend ostream& operator << (ostream& os,const CWayPoint& Wp);
	Wp_type getListType();
	void setListType(Wp_type Type);



private:
	string m_name;
	double m_latitude;
	double m_longitude;
protected:

    /**
     * API to convert the longitude to Degree minutes and seconds format
     * . The conversion is done from the decimal format to the deg mm ss format.
     * 
     * Arguments:
     * 
     * deg[OUT Parameter] : reference to the degrees of location
     * mm[OUT Parameter] : reference to the minutes of the location
     * ss[OUT Parameter]: refernce to the seconds of the location.
     * 
     * Return:
     * None
     */
	void transformLongitude2Degreemmss(int &deg, double &mm, double &ss) const;

    /**
     * API to convert the latitude to Degree minutes and seconds format
     * . The conversion is done from the decimal format to the deg mm ss format.
     * 
     * Arguments:
     * 
     * deg[OUT Parameter] : reference to the degrees of location
     * mm[OUT Parameter] : reference to the minutes of the location
     * ss[OUT Parameter]: refernce to the seconds of the location.
     * 
     * Return:
     * None
     */
	void transformLatitude2Degreemmss(int &deg, double &mm, double &ss) const;

private:
	Wp_type m_WpType;

};



#endif /* CWAYPOINT_H_ */
