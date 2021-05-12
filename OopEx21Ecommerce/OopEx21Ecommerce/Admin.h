#pragma once
#include "Person.h"
using namespace PersonNamespace;

namespace AdminNamespace {
	class Admin :public Person {
		string _username = "";
		string _password = "";

	public:
		Admin() = default;
		Admin(const string& username, const string& password) :Person()
		{
			setUsername(username);
			setPassword(password);
		}

		const string& getUsername()const {
			return _username;
		}
		const string& getPassword()const {
			return _password;
		}

		void setUsername(const string& username) {
			if (username.empty()) throw NullException("Username is empty", __LINE__, __FILE__);
			_username = username;
		}
		void setPassword(const string& password) {
			if (password.empty()) throw NullException("Password is empty", __LINE__, __FILE__);
			_password = password;
		}

		void showAdmin() {
			cout << "~ ~ ~ ~ A D M I N S ~ ~ ~ ~" << endl;
			cout << "Id: " << getId() << endl;
			cout << "Username: " << getUsername() << endl;
			string passwordSecret(getPassword().size(), '*');
			cout << "Password: " << passwordSecret << endl;
		}
	};
}