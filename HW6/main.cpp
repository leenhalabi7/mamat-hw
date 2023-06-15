#include "string.h"
#include "generic-field.h"
#include "ip.h"
#include "port.h"
#include "input.h" 
#include <string.h>


#define ERROR -1
#define EQUAL "="


/*
	@brief reads the stdin and the first argument of the program and prints all the mached packets to the stdout 
*/
int main(int argc, char *argv[]){

	if(check_args(argc,argv)){ //checks if the arguments are invalid
		return ERROR;
	}
	String rule = argv[1];
	String *out;
	size_t size=0;
	String original = String(rule);     
	//Split the rule into two parts based on the delimiter "=",
	//using the split function.
	rule.split(EQUAL,&out,&size); 
	//The resulting substrings are stored in the out array.
	String name = ((out)[0]).trim(); 
	String value = ((out)[1]).trim();

	if ((name.equals("dst-port"))||(name.equals("src-port"))){
		Port port_rule = Port(name);
		if(port_rule.set_value(value)){
			parse_input(port_rule);
			delete[] out;
			return 0;
		}	
	}
	if ((name.equals("dst-ip"))||(name.equals("src-ip"))){
		Ip ip_rule = Ip(name);
		if(ip_rule.set_value(value)){
			parse_input(ip_rule); 
			delete[] out;
			return 0;
		}	
	}
	delete[] out;
	return ERROR;	
}



