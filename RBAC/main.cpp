#include "header.h"

int main(){
	urmap *ur = new urmap;
	prmap *pr = new prmap;
	hrmap *hr = new hrmap;

	//populate maps with given values from files
	loadURA(ur);
	loadPRA(pr);
	loadHR(hr);

	//listAll(ur, pr, hr);
	login(ur, pr, hr);

	delete ur;
	delete pr;
	delete hr;
}

void loadURA(multimap<string, string> *urmap){
	ifstream ura("URA.txt");
	string user, role;

	while(!ura.eof()){
		ura >> user;
		ura >> role;
		urmap->insert(urentry(user, role));
	}

	ura.close();
}

void loadPRA(multimap< string, pair<string, string> >* prmap){
	ifstream pra("PRA.txt");
	string role, act, obj;
	
	while(!pra.eof()){
		pra >> role;
		pra >> act;
		pra >> obj;
		prmap->insert(prentry(role, pair<string, string>(act, obj)));
	}

	pra.close();
}

void loadHR(hrmap *hr){
	ifstream hrfile("HR.txt");
	string super, role;

	while(!hrfile.eof()){
		hrfile >> super;
		hrfile >> role;
		hr->insert(hrentry(super, role));
	}

	hrfile.close();
}

void listAll(urmap *ur, prmap *pr, hrmap *hr){
	cout << "User-Role Pairs:\n";
	for(urentry entry : *ur)
		cout << entry.first << ", " << entry.second << endl;

	cout << "\nRole-Permission Pairs:\n";
	for(prentry entry : *pr)
		cout << entry.first << ": " << entry.second.first << " " << entry.second.second << endl;

	cout << "\nRole Hierarchy:\n";
	for(hrentry entry : *hr)
		cout << entry.first << " >= " << entry.second << endl;
}

void login(urmap *ur, prmap *pr, hrmap *hr){
	string user;

	cout << "Welcome! Press CTRL-Z + Enter (Windows) or CTRL-D (Linux) to exit or logout\n";
	do{
		//Take logins until successful or eof char entered
		cout << "\nlogin: ";
		getline(cin, user);

		if(cin.eof()){
			cout << "\nFinished\n";
			return;
		}

		urmap::iterator it = ur->find(user);
		if(it != ur->end()){
			cout << "User " << it->first << " is successfully logged in\n";
			eval(*it, pr, hr);
		}
		else
			cout << "User not found\n";
	}while(1);
}

void eval(urentry current, prmap *pr, hrmap *hr){
	pair<string, string> permission;
	string act, obj,
		user = current.first,
		role = current.second;

	do{
		//get permissions until eof entered, then return to login
		cout << "cmd> ";
		cin >> act;
		cin >> obj;

		if(cin.eof()){
			cout << user << "\nsigned out\n";
			cin.clear();
			return;
		}
		
		permission = pair<string, string>(act, obj);

		prmap::iterator it = pr->find(role);

		//Find permission based on role and compare it to given permission
		//Alternatively, find if role under given role in hierarchy has permission
		bool permit = it->second == permission
			|| pr->find(hr->find(role)->second)->second == permission;

		if(it != pr->end() && permit)
			cout << "Permission to " << act << " " << obj
				<< " granted to " << role << " " << user << endl;
		else if(it != pr->end() && !permit)
			cout << "Access Denied: A " << role << " cannot "
				<< act << " " << obj << endl;
		else
			cout << "Permission not found\n";
	}while(1);
}


