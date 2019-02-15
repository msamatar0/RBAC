#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>
using namespace std;

//user-role pair: user, role
typedef pair<string, string> urentry;
typedef multimap<string, string> urmap;
//load contents of ura file into map
void loadURA(multimap<string, string> *ur);

//permission-role pair: role, permission(act on object)
typedef pair< string, pair<string, string> > prentry;
typedef multimap< string, pair<string, string> > prmap;
//load contents of pra file into map
void loadPRA(multimap< string, pair<string, string> > *pr);

//role hierarchy: super-role, role
typedef urentry hrentry;
typedef urmap hrmap;
void loadHR(hrmap *hr);

//list all pairs in both maps
void listAll(urmap *ur, prmap *pr, hrmap *hr);

//take username from input and verify it
void login(urmap *ur, prmap *pr, hrmap *hr);

//evaluate whether a given user is qualified to perform an inputted action based on their role
void eval(urentry current, prmap *pr, hrmap *hr);
