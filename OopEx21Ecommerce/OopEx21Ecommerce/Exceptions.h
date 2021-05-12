#pragma once
#include<iostream>
using namespace std;

namespace ExceptionNamespace {
	class Exception {
	protected:
		string text;
		int line;
		string file;
		string createdTime;
		Exception(const string& text, const int line, const string& file)
		{
			setText(text);
			setLine(line);
			setFile(file);
			setTime();
		}
		string getText()const {
			return text;
		}
		int getLine()const {
			return line;
		}
		string getFile()const {
			return file;
		}
		string getTime()const {
			return createdTime;
		}

		void setText(const string& text) {
			if (text.empty()) throw "Text is empty";
			this->text = text;
		}
		void setLine(const int line) {
			if (line < 0) throw "Line cannot be negative";
			this->line = line;
		}
		void setFile(const string& file) {
			if (file.empty()) throw "Source is empty";
			this->file = file;
		}
		void setTime() {
			time_t currently = time(0);
			char dt[30]{};
			ctime_s(dt, sizeof dt, &currently);
			string time = dt;

			this->createdTime = dt;
		}

	public:
		void PrintMsg()const {
			cout << endl;
			cout << "Text:" << getText() << endl;
			cout << "Line:" << getLine() << endl;
			cout << "Source:" << getFile() << endl;
			cout << "Time: " << getTime() << endl;
		}

		virtual ~Exception() = 0
		{

		}
	};

	class DatabaseException :public Exception {
	public:
		DatabaseException(const string& text, const int line, const string& source)
			:Exception(text, line, source)
		{

		}
	};

	class InvalidArgumentException :public Exception {
	public:
		InvalidArgumentException(const string& text, const int line, const string& source)
			:Exception(text, line, source)
		{

		}
	};

	class NullException :public Exception {
	public:
		NullException(const string& text, const int line, const string& source)
			:Exception(text, line, source)
		{

		}
	};
}