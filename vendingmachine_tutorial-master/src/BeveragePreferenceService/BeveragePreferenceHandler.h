#ifndef VENDING_MACHINE_MICROSERVICES_BEVERAGEPREFERENCEHANDLER_H
#define VENDING_MACHINE_MICROSERVICES_BEVERAGEPREFERENCEHANDLER_H

#include <iostream>
#include <string>
#include <regex>
#include <future>

#include "../../gen-cpp/BeveragePreferenceService.h"

#include "../ClientPool.h"
#include "../ThriftClient.h"
#include "../logger.h"

namespace vending_machine{

class BeveragePreferenceServiceHandler : public BeveragePreferenceServiceIf {
 public:
   BeveragePreferenceServiceHandler();
  ~BeveragePreferenceServiceHandler() override=default;
  
  void getBeverage(std::string& _return, const BeverageType::type btype);
};

// Constructor
BeveragePreferenceServiceHandler::BeveragePreferenceServiceHandler() {

}

// Remote Procedure "PlaceOrder"

void BeveragePreferenceServiceHandler::getBeverage(std::string& _return, const BeverageType::type btype) {
     // Your implementation goes here
     printf("GetBeveragePreference\n");
	
	int test = rand()%3;
    // randomly select a weather
	if( btype == BeverageType::type::COLD)
	{
		if(test == 0)
			_return = "Lemonade";
		else if(test ==1)
			_return = "Iced Tea";
		else if(test ==2)
			_return = "Soda";
	}	
	else
	{
		if(test == 0)
			_return = "Cappuccino";
		else if(test ==1)
			_return = "Latte";
		else if(test ==2)
			_return = "Espresso";
	}
	return;
}

} // namespace vending_machine


#endif //VENDING_MACHINE_MICROSERVICES_WEATHERHANDLER_H
