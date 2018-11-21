#ifndef UNIQUESTRING_LIBRARY_H
#define UNIQUESTRING_LIBRARY_H

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <map>
using std::map;
using std::pair;

namespace soda {

    class UniqueString {
    private:
        UniqueString(string s, string channel);
        UniqueString(const UniqueString &);

        static map<string, vector<string>* > channels;
        static bool auto_rename;
        static string name_with_index(string s, string channel);


        string unique_string;
    public:
        UniqueString() = delete;
        string getString();
        bool setString();

        static bool addChannel(string channelName);
        static void setAutoRename(bool b);
        static UniqueString* createUnique(string s, string channel);
    };

}
#endif