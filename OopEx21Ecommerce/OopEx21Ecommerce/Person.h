#pragma once
#include "Exceptions.h"
using namespace ExceptionNamespace;

namespace PersonNamespace {
	class Person {
	protected:
		int id = 0;
		static int ID;
		Person() {
			id = ++ID;
		}
	public:
		int getId()const {

			return id;
		}

		virtual ~Person() = 0
		{

		}
	};
	int Person::ID = 0;
}

