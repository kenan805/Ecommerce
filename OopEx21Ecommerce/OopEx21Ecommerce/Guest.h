#pragma once
#include "Person.h"
using namespace PersonNamespace;

namespace GuestNamespace {
	class Guest :public Person {
		string _fullname = "";
		string _phone_number = "";
		string _connected_dateTime = "";
	public:
		Guest() = default;
		Guest(const string& fullname,const string& phone_number) :Person()
		{
			setFullname(fullname);
			setPhoneNumber(phone_number);
			setDateTime();
		}

		const string& getFullname()const {
			return _fullname;
		}
		const string& getPhoneNumber()const {
			return _phone_number;
		}
		const string& getConnectedDateTime()const {
			return _connected_dateTime;
		}

		void setFullname(const string& fullname) {
			if (fullname.empty()) throw NullException("Fullname is empty", __LINE__, __FILE__);
			_fullname = fullname;
		}
		void setPhoneNumber(const string& phone_number) {
			if (phone_number.empty()) throw NullException("Phone number is empty", __LINE__, __FILE__);
			_phone_number = phone_number;
		}
		void setDateTime() {
			time_t currently = time(0);
			char dt[30]{};
			ctime_s(dt, sizeof dt, &currently);

			_connected_dateTime = dt;
		}

		void showGuest() {
			cout << "Fullname: " << getFullname() << endl;
			cout << "Phone number: " << getPhoneNumber() << endl;
			cout << "Connected datetime: " << getConnectedDateTime();
		}
	};
}
