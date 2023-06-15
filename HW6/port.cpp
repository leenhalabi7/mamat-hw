#include "port.h"


#define MAX 65535
#define MIN 0
#define STR_SIZE 2
#define DASH "-"
#define EQUAL "="
#define OUR_DELIM ","


//Port constructor 
Port::Port(String str){
	this->min = 0;
	this->max = 0;       
	this->port = str;       
}  

//port destructor 
Port::~Port(){
}

/*
	* @brief checks if the port range is legal 
*/
bool Port::set_value(String value){
	String *sub_val;
	size_t size = 0;
	//splits the min and max value of the given port rule
	value.split(DASH,&sub_val,&size);
	if (size != STR_SIZE){ 
		delete[] sub_val;
		return false;
	}
	this->min = sub_val[0].trim().to_integer(); 
	this->max = sub_val[1].trim().to_integer();
	if (this->min < MIN || this->max > MAX || this->min > this->max){
		delete[] sub_val;
		return false;
	}
	delete[] sub_val;
	return true;
}

/*
	* @brief the function is responsible for comparing a given packet with rules of the port
	* returns true if there is a match 
*/
bool Port::match(String packet){
	if(match_aux(packet)){
		int val = packet.trim().to_integer();
	    if (val < this->min || val > this->max){ //checks if packet is in the port rule range
		    return false;
	    } 
		return true;
	}

	return false;

}

/*
	* @brief checks if there is a match between the packet and the defined rules of the Port object
*/
bool Port::match_aux(String& packet){
        bool flag = false;
        String *sub_packets;
        size_t size = 0;
        packet.split(OUR_DELIM , &sub_packets,&size); //splits to sub packets 
        for (int i=0 ; i<(int)size ; i++){
                String *values;
                size_t num = 0;
                (sub_packets[i]).split(EQUAL , &values,&num); 
                (values[0])=(values[0]).trim();
                if ((this->port).equals(values[0])){
                        flag = true;
                        packet = values[1].trim();
                }
                delete[] values;
        }
        delete[] sub_packets;
        return flag;
}
