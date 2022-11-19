#include <iostream>
#include <sstream>
#include <string>

#include <InputDevice.h>

using namespace std;

InputDevice::InputDevice(istream& istest) {

    input = &istest;

    // cout<<a.gcount();
    string line;
    while(*input) {
        cout<<"Type line now: ";
        if(std::getline(*input, line)) {
            // supposed to Parsing string into words and translate// 
            //but just reading back input for now//
            cout<<"You typed: "<<line<<endl;
        }
    }
}
