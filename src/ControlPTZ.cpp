#include "ControlPTZ.h"

ControlPTZ::ControlPTZ()
{
	//Curl configuration to work with HTTPS protocole
	handle=curl_easy_init();
	curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0L);
  	curl_easy_setopt(handle, CURLOPT_NOPROGRESS, 1L);
  	curl_easy_setopt(handle, CURLOPT_USERPWD, "opera:clm2pO");
  	curl_easy_setopt(handle, CURLOPT_USERAGENT, "curl/7.21.6 (i686-pc-linux-gnu) libcurl/7.21.6 OpenSSL/1.0.0e zlib/1.2.3.4 libidn/1.22 librtmp/2.3");
  	curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 1L);
  	curl_easy_setopt(handle, CURLOPT_MAXREDIRS, 50L);
  	curl_easy_setopt(handle, CURLOPT_HTTPAUTH, -17L);
	
}

ControlPTZ::~ControlPTZ()
{
	curl_easy_cleanup(handle);
}

void ControlPTZ::HTTPRequestPTZ(int pan, int tilt, int zoom)
{
	CURLcode response;
	ostringstream oss;

	if (pan>100)
	  pan=100;
	else if (pan<-100)
	  pan=-100;
	
	if (tilt>100)
	  tilt=100;
	else if (tilt<-100)
	  tilt=-100;

	/*if (zoom>100)
	  zoom=100;
	else if (zoom<-100)
	  zoom=-100;*/

	if (zoom>9999)
	  zoom=9999;
	else if (zoom<-9999)
	  zoom=-9999;

	oss << "https://axis-ptz2/axis-cgi/com/ptz.cgi?continuouspantiltmove=";
	oss << pan;
	oss << ",";
	oss << tilt;
	oss << "&rzoom=" << zoom;
	//oss <<"&continuouszoommove=";
	//oss << zoom;
	curl_easy_setopt(handle, CURLOPT_URL, oss.str().c_str());
	response = curl_easy_perform(handle);
	//cout << response << endl;
}

void ControlPTZ::HTTPRequestPTZPosRelative(float pan, float tilt, float zoom)
{
	CURLcode response;
	ostringstream oss;

	if (pan>360)
	  pan=360;
	else if (pan<-360)
	  pan=-360;
	
	if (tilt>360)
	  tilt=360;
	else if (tilt<-360)
	  tilt=-360;

	if (zoom>9999)
	  zoom=9999;
	else if (zoom<-9999)
	  zoom=-9999;

	oss << "https://axis-ptz2/axis-cgi/com/ptz.cgi?rpan=" << pan;
	oss << "&rtilt=" << tilt;
	oss << "&rzoom=" << zoom;

	curl_easy_setopt(handle, CURLOPT_URL, oss.str().c_str());
	response = curl_easy_perform(handle);
	//cout << response << endl;
}

void ControlPTZ::HTTPRequestPTZPosAbsolute(float pan, float tilt, float zoom)
{
	CURLcode response;
	ostringstream oss;

	if (pan>180)
	  pan=180;
	else if (pan<-180)
	  pan=-180;
	
	if (tilt>180)
	  tilt=180;
	else if (tilt<-180)
	  tilt=-180;

	if (zoom>9999)
	  zoom=9999;
	else if (zoom<-9999)
	  zoom=-9999;

	oss << "https://axis-ptz2/axis-cgi/com/ptz.cgi?pan=" << pan;
	oss << "&tilt=" << tilt;
	oss << "&zoom=" << zoom;

	curl_easy_setopt(handle, CURLOPT_URL, oss.str().c_str());
	response = curl_easy_perform(handle);
	//cout << response << endl;
}
