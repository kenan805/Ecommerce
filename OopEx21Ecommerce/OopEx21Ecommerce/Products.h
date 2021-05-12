#pragma once
#include "Exceptions.h"
using namespace ExceptionNamespace;

namespace ProductNamespace {
	class Product {
		size_t _id = 0;
		string _name = "";
		string _description = "";
		double _price = 0;
		double _discount = 0;
		double _tax = 0;
	public:
		Product() = default;
		Product(const size_t id, const string& name, const string& description, const double price, const double discount, const double tax)
		{
			setId(id);
			setName(name);
			setDescription(description);
			setPrice(price);
			setDiscount(discount);
			setTax(tax);
		}

		size_t getId()const {
			return _id;
		}
		const string& getName() const { return _name; }
		const string& getDescription() const { return _description; }
		double getPrice() const { return _price; }
		double getDiscount() const { return _discount; }
		double getTax() const { return _tax; }
		double getDiscountedPrice() const
		{
			return _price - ((_price * _discount) / 100.0);
		}

		void setId(const size_t id) {
			if (id <= 0) throw InvalidArgumentException("The id must be greater than 0.", __LINE__, __FILE__);
			_id = id;
		}
		void setName(const string& name)
		{
			if (name.empty()) throw NullException("The name is empty", __LINE__, __FILE__);
			_name = name;
		}
		void setDescription(const string& description)
		{
			if (description.empty()) throw NullException("The description is empty", __LINE__, __FILE__);
			_description = description;
		}
		void setPrice(const double& price)
		{
			if (price < 0) throw InvalidArgumentException("The price cannot be negative.", __LINE__, __FILE__);
			_price = price;
		}
		void setDiscount(const double& discount)
		{
			if (discount < 0 && discount > 100) throw InvalidArgumentException("The discount should be between 0 and 100.", __LINE__, __FILE__);
			_discount = discount;
		}
		void setTax(const double& tax)
		{
			if (tax < 0 && tax > 100) throw InvalidArgumentException("The tax should be between 0 and 100.", __LINE__, __FILE__);
			_tax = tax;

		}
		void showDetailProduct() {
			cout << "Id: " << getId() << endl;
			cout << "Name: " << getName() << endl;
			cout << "Description: " << getDescription() << endl;
			cout << "Price: " << getPrice() << " AZN" << endl;
			cout << "Discount: " << getDiscount() << " %" << endl;
			if (getDiscount() > 0) cout << "Discounted price: " << getDiscountedPrice() << " AZN" << endl;
			cout << "Tax: " << getTax() << " %" << endl;
		}
		void showProductPreview() {
			cout << "Id: " << getId() << endl;
			cout << "Name: " << getName() << endl;
			cout << "Price: " << getPrice() << " AZN" << endl;
		}


	};

	class ProductItem {
		Product* _product;
		size_t _quantity;
	public:
		ProductItem(Product*& product, const size_t quantity) {
			setProduct(product);
			setQuantity(quantity);
		}

		Product* getProduct()const {
			return _product;
		}
		size_t getQuantity()const {
			return _quantity;
		}

		void setProduct(Product* product) {
			if (product == nullptr) throw NullException("Product is empty", __LINE__, __FILE__);
			_product = product;
		}
		void setQuantity(const size_t quantity) {
			if (quantity < 0) throw InvalidArgumentException("Quantity cannot be negative.", __LINE__, __FILE__);
			_quantity = quantity;
		}

		void showProductItemDetail() {
			_product->showDetailProduct();
			cout << "Quantity: " << getQuantity();
		}
		void showProductItemPreview() {
			_product->showProductPreview();
			cout << "Quantity: " << getQuantity();
		}
		~ProductItem()
		{
			if (_product != NULL) delete _product;
		}
	};
}

