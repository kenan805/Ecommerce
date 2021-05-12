#pragma once
#include "Products.h"
#include "Admin.h"
#include "Guest.h"
#include "AdminNotifications.h"
#include<string>
using namespace AdminNamespace;
using namespace GuestNamespace;
using namespace ProductNamespace;
using namespace NotificationNamespace;

namespace DatabaseNamespace {
	template<typename T>
	class DbSet {
		T** _items = nullptr;
		size_t _itemscount = 0;
	public:
		DbSet() = default;

		T** getItems()const {
			return _items;
		}
		size_t getItemscount()const {
			return _itemscount;
		}

		void add(T* item) {
			if (item == nullptr) throw DatabaseException("Item is nullptr", __LINE__, __FILE__);
			T** newItems = new T * [_itemscount + 1];

			for (size_t i = 0; i < _itemscount; i++)
			{
				newItems[i] = _items[i];
			}

			newItems[_itemscount] = item;

			delete[] _items;
			_items = newItems;
			newItems = nullptr;
			_itemscount++;
		}
		void deleteById(const int& id) {
			if (id < 0) throw InvalidArgumentException("Id cannot be negative.", __LINE__, __FILE__);

			T** newItems = new T * [_itemscount - 1];
			int index;
			for (size_t i = 0; i < _itemscount; i++)
			{
				if (getItems()[i]->getProduct()->getId() == id) {
					index = i;
					break;
				}
			}

			for (size_t j = 0, i = 0; j < index; j++, i++)
			{
				newItems[j] = _items[i];
			}
			for (size_t j = index; j < _itemscount; j++, index++)
			{
				newItems[j] = _items[index + 1];

			}
			_itemscount--;
			delete[] _items;
			_items = newItems;
			newItems = nullptr;

		}
		T* getItem(const int& id) {
			if (id < 0) throw InvalidArgumentException("Id cannot be negative.", __LINE__, __FILE__);
			for (size_t i = 0; i < _itemscount; i++)
			{
				if (_items[i]->getProduct()->getId() == id) {
					return _items[i];
				}
			}
			throw DatabaseException("Product not found !", __LINE__, __FILE__);
		}
		void updateById(const int& id, T* item) {
			if (id < 0) throw InvalidArgumentException("Id cannot be negative.", __LINE__, __FILE__);
			else if (item == nullptr) throw DatabaseException("Item is null", __LINE__, __FILE__);
			for (size_t i = 0; i < _itemscount; i++)
			{
				if (item != NULL) {
					if (_items[i]->getProduct()->getId() == id) {
						getItems()[i]->setProduct(item->getProduct());
						getItems()[i]->setQuantity(item->getQuantity());
					}
				}

			}
		}
		bool isExistsItems(const int id) {
			if (id < 0) throw InvalidArgumentException("Id cannot be negative.", __LINE__, __FILE__);
			for (size_t i = 0; i < _itemscount; i++)
			{
				if (_items[i]->getProduct()->getId() == id) return true;
			}
			return false;
		}

		bool isExistsGuests(const int id) {
			if (id < 0) throw InvalidArgumentException("Id cannot be negative.", __LINE__, __FILE__);
			for (size_t i = 0; i < _itemscount; i++)
			{
				if (_items[i]->getProduct()->getId() == id) return true;
			}
			return false;
		}

		bool isExistsItems(const string& fullname) {
			if (fullname.empty()) throw InvalidArgumentException("Fullname is empty", __LINE__, __FILE__);
			for (size_t i = 0; i < _itemscount; i++)
			{
				if (_items[i]->getFullname() == fullname) return true;
			}
			return false;
		}

		void signUp(Guest* guest) {
			if (guest == nullptr) throw DatabaseException("Guest is null", __LINE__, __FILE__);
			add(guest);
		}

		~DbSet()
		{
			for (size_t i = 0; i < _itemscount; i++)
			{
				delete _items[i];
			}
			delete[] _items;
		}
	};

	class Database {
	public:
		DbSet<ProductItem>* _products = nullptr;
		DbSet<Guest>* _guests = nullptr;
		DbSet<Admin>* _admins = nullptr;
		DbSet<Notification>* _notifications = nullptr;
		Database() = default;
		Database(DbSet<ProductItem>* products)
		{
			setProducts(products);
		}
		Database(DbSet<Admin>* admins)
		{
			setAdmins(admins);
		}
		Database(DbSet<Guest>* guests)
		{
			setGuests(guests);
		}
		Database(DbSet<Notification>* notifications)
		{
			setNotifications(notifications);
		}
		Database(DbSet<Admin>* admins, DbSet<Guest>* guests, DbSet<ProductItem>* products, DbSet<Notification>* notifications)
		{
			setAdmins(admins);
			setGuests(guests);
			setProducts(products);
			setNotifications(notifications);
		}

		DbSet<ProductItem>* getProducts()const {
			return _products;
		}
		DbSet<Admin>* getAdmins() {
			return _admins;
		}
		DbSet<Guest>* getGuests()const {
			return _guests;
		}
		DbSet<Notification>* getNotifications()const {
			return _notifications;
		}

		void setProducts(DbSet<ProductItem>* products)
		{
			if (products == nullptr)
				throw DatabaseException("Products is nullptr", __LINE__, __FILE__);

			_products = products;
		}
		void setAdmins(DbSet<Admin>* admins)
		{
			if (admins == nullptr)
				throw DatabaseException("Admins is nullptr", __LINE__, __FILE__);

			_admins = admins;
		}
		void setGuests(DbSet<Guest>* guests)
		{
			if (guests == nullptr)
				throw DatabaseException("Guests is nullptr", __LINE__, __FILE__);

			_guests = guests;
		}
		void setNotifications(DbSet<Notification>* notifications)
		{
			if (notifications == nullptr)
				throw DatabaseException("Notifications is nullptr", __LINE__, __FILE__);

			_notifications = notifications;
		}



		void showAllProductsDetail() {
			cout << "-_-_-_-_-_-_- Product detail info -_-_-_-_-_-_-" << endl;
			for (size_t i = 0; i < _products->getItemscount(); i++)
			{
				_products->getItems()[i]->showProductItemDetail();
				cout << endl;
				cout << "-----------------------------------------" << endl;
			}
		}

		void showAllProductsPreview() {
			cout << "-_-_-_-_-_-_- Product preview info -_-_-_-_-_-_-" << endl;
			for (size_t i = 0; i < _products->getItemscount(); i++)
			{
				_products->getItems()[i]->showProductItemPreview();
				cout << endl;
				cout << "-----------------------------------------" << endl;
			}
		}

		void showAllNotifications() {
			int count = 0;
			for (size_t i = 0; i < _notifications->getItemscount(); i++)
			{
				if (_notifications->getItems()[i]->getRead() == false)
				{
					++count;
				}
			}
			cout << "Oxunmamis " << count << " notification var" << endl;
			for (size_t i = 0; i < _notifications->getItemscount(); i++)
			{
				_notifications->getItems()[i]->showNotifications();
			}
		}

		void showUnReadToReadNotifications() {
			for (size_t i = 0; i < _notifications->getItemscount(); i++)
			{
				if (_notifications->getItems()[i]->getRead() == false)
				{
					_notifications->getItems()[i]->setRead(true);
				}
			}
		}

		void showUnReadNotifications() {
			for (size_t i = 0; i < _notifications->getItemscount(); i++)
			{
				if (_notifications->getItems()[i]->getRead() == false)
				{
					_notifications->getItems()[i]->showNotifications();
				}
			}
		}
	};
}