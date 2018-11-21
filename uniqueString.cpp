#include "uniqueString.h"

#include <iostream>
#include <sstream>

using namespace soda;

map<string, vector<string>* > UniqueString::channels;
bool UniqueString::auto_rename;

void hello() {
    std::cout << "Hello, World!" << std::endl;
}

void UniqueString::setAutoRename(bool b) {
    auto_rename = b;
}

bool UniqueString::addChannel(string channelName) {
    if(channels.find(channelName)!=channels.end())
        return false;
    channels.emplace(channelName, new vector<string>);

}

UniqueString::UniqueString(string s, string channel) : unique_string(s) {
    channels.at(channel)->push_back(s);
}

UniqueString *UniqueString::createUnique(string s, string channel) {
    if(channels.find(channel) == channels.end())
        return nullptr;
    for(const string &s_s : *channels.at(channel)) {
        if(s.compare(s_s) == 0) {
            if(auto_rename) {
                return new UniqueString(name_with_index(s, channel), channel);
            } else {
                return nullptr;
            }
        }
    }

    return new UniqueString(s, channel);
}

string UniqueString::name_with_index(string s, string channel) {
    std::istringstream ss(s);
    size_t pos, old_suffix=0;
    for(pos=s.size();pos>0;pos--) {
        if(s[pos]=='(') break;
    }
    if(pos) {
        ss.seekg(pos+1);
        ss>>old_suffix;
    }

    long suffix = old_suffix == 0 ? 2 : old_suffix + 1;
    do{
        std::string newName;
        if(!old_suffix) {
            newName.assign(s+"("+std::to_string(suffix)+")");
        } else {
            newName.assign(string(s, 0, pos)+"("+std::to_string(suffix)+")");
        }

//        if(findObjectByName(newName) == nullptr) {
//            return newName;
//        }
        bool ac = true;
        for(const auto &s_s : *channels.at(channel)) {
            if(newName == s_s) {
                ac = false;
                break;
            }
        }
        if(ac) {
            return newName;
        }
        suffix ++;
    }while(true);
}

string UniqueString::getString() {
    return unique_string;
}
