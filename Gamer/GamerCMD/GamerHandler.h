#pragma once
#include<string>
#include<Windows.h>
using std::string;
namespace seraphim {
	class GamerHandler {
	private:
		bool pauseAtCreate{ true };
		HANDLE  hProcess;
		HANDLE hTread;
		DWORD  pid;
		DWORD  tid;
		string targetExeName;
		string  dllName;
	public:
		GamerHandler();
		int startProcess();
		int inject();
		int login(const string& uName, const string& uPasswd);
		int pause();
		int resume();
		void termindate();
		void print();
	};
};
