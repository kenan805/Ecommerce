#pragma once
#include "Guest.h"
using namespace GuestNamespace;

namespace NotificationNamespace {
	class Notification {
		bool _isRead = false;
		Guest* _guest = nullptr;
		string _text = "";
		string _datetime = "";
	public:
		Notification() = default;
		Notification(Guest* guest, const string& text)
		{
			setGuest(guest);
			setText(text);
			setDatetime();
			setRead(false);
		}


		Guest* getGuest()const {
			return _guest;
		}
		string getText() const { return _text; }
		string getDatetime()const { return _datetime; }
		bool getRead()const { return _isRead; }


		void setGuest(Guest* guest) {
			if (guest == nullptr) throw DatabaseException("Guest is null", __LINE__, __FILE__);
			_guest = guest;
		}
		void setText(const string& text)
		{
			if (text.empty()) throw InvalidArgumentException("Text is empty", __LINE__, __FILE__);
			_text = text;
		}
		void setDatetime()
		{
			time_t currently = time(0);
			char dt[30]{};
			ctime_s(dt, sizeof dt, &currently);
			string time = dt;

			_datetime = dt;
		}
		void setRead(const bool& read) { _isRead = read; }

		void showNotifications() {
			cout << "                    Notification"<< endl;
			cout << "-----------------------------------------------------" << endl;
			cout << "Notification datetime: " << getDatetime();
			cout << "Notification read: ";
			if (_isRead == false)
			{
				cout << "Oxunmayib" << endl;
				cout << "Notification text: " << getText() << endl;
			}
			else cout << "Oxunub" << endl;
			_guest->showGuest();


		}

		~Notification()
		{
			delete _guest;
		}

	};
}