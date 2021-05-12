#include "Database.h"
#include <string>
#include <windows.h>
using namespace DatabaseNamespace;

namespace ECommerce {
	Database* db = new Database();

	void createAdmin() {
		Admin* admin = new Admin("admin", "admin");
		db->_admins = new DbSet<Admin>();
		db->getAdmins()->add(admin);
	}

	void createGuests() {
		Guest* guest1 = new Guest("Kenan805", "+994 99 999 00 00");
		db->_guests = new DbSet<Guest>();
		db->getGuests()->add(guest1);

		Notification* notf1 = new Notification(guest1, "A new user has registered.");
		db->_notifications = new DbSet<Notification>();
		db->getNotifications()->add(notf1);

		Guest* guest2 = new Guest("Revan222", "+994 55 555 34 21");
		db->getGuests()->add(guest2);

		Notification* notf2 = new Notification(guest2, "A new user has registered.");
		db->getNotifications()->add(notf2);
	}

	void createProduct() {
		//Hazir productlar
		db->_products = new DbSet<ProductItem>();
		Product* phone = new Product(1, "Iphone 12", "256gb,Blue", 2699.99, 2, 4);
		ProductItem* product_item_phone = new ProductItem(phone, 10);
		db->getProducts()->add(product_item_phone);

		Product* computer = new Product(2, "Acer Nitro 5", "Core i5,Black", 2049.99, 8, 5);
		ProductItem* product_item_computer = new ProductItem(computer, 15);
		db->getProducts()->add(product_item_computer);

		Product* tv = new Product(3, "TV LG OLED55BXRLB", "4K UHD(3840x2160)", 2199.99, 0, 3);
		ProductItem* product_item_tv = new ProductItem(tv, 15);
		db->getProducts()->add(product_item_tv);
	}
	void updateProduct() {
		//Hazir update olunmus product
		Product* phone = new Product(3, "Iphone 13", "128gb,Black", 3699.99, 2, 4);
		ProductItem* product_item_phone = new ProductItem(phone, 20);
		db->getProducts()->updateById(3, product_item_phone);
	}


	void start() {
		try
		{
			createAdmin();
			createGuests();
			createProduct();
			while (true)
			{
				system("cls");
				cout << "> > > > > Electro Shop E-Bazar-App < < < < <\n";
				cout << "(1) - Admin\n";
				cout << "(2) - Guest\n";
				cout << "(3) - Exit\n";
				int option;
				cout << "Make your choice: ";
				cin >> option;
				if (option == 1) {
					while (true)
					{
						//Admin hisse
						system("cls");
						string adminUsername;
						string adminpassword;
						cout << "Enter admin username: ";
						cin >> adminUsername;
						cout << "Enter admin password: ";
						cin >> adminpassword;
						for (size_t i = 0; i < db->getAdmins()->getItemscount(); i++)
						{
							if (adminUsername == db->getAdmins()->getItems()[i]->getUsername()) {
								if (adminpassword == db->getAdmins()->getItems()[i]->getPassword()) {
									cout << "You are logged in as an administrator!" << endl;
									Sleep(1000);
									system("cls");
									string adminOption;
									while (1)
									{
										system("cls");
										cout << "> > > > > Admin operations < < < < <" << endl;
										cout << "(1) - Show all products\n";
										cout << "(2) - Add product\n";
										cout << "(3) - Delete product\n";
										cout << "(4) - Update product\n";
										cout << "(5) - Notificatons\n";
										cout << "(6) - Go back\n";
										cout << "Make your choice: ";
										cin >> adminOption;
										if (adminOption == "1") {
											system("cls");
											db->showAllProductsDetail();
											string clickBack;
											cout << "\nClick any to back: ";
											cin >> clickBack;
											continue;
										}
										else if (adminOption == "2") {
											system("cls");
											cout << "Enter the product information." << endl;
											string name, description;
											size_t id, quantity;
											double price, discount, tax;
											id = db->getProducts()->getItemscount() + 1;
											cout << "Enter name: ";
											cin.ignore();
											getline(cin, name);
											cout << "Enter description: ";
											getline(cin, description);
											cout << "Enter price: ";
											cin >> price;
											cout << "Enter discount: ";
											cin >> discount;
											cout << "Enter tax: ";
											cin >> tax;
											cout << "Enter quantity: ";
											cin >> quantity;
											Product* newProduct = new Product(id, name, description, price, discount, tax);
											ProductItem* newProductItem = new ProductItem(newProduct, quantity);
											db->getProducts()->add(newProductItem);
											cout << "The product is added .";
											for (size_t i = 0; i < 2; i++)
											{
												Sleep(1000);
												cout << ".";
											}
											cout << "\nThe product was successfully added!" << endl;
											Sleep(2000);
											continue;
										}
										else if (adminOption == "3") {
											system("cls");
											db->showAllProductsDetail();
											int idChoiseDelete;
											cout << "Select the id of the product you want to delete: ";
											cin >> idChoiseDelete;
											if (db->getProducts()->isExistsItems(idChoiseDelete)) {
												db->getProducts()->deleteById(idChoiseDelete);
												cout << "The product is deleted from the database.";
												for (size_t i = 0; i < 2; i++)
												{
													Sleep(1000);
													cout << ".";
												}
												cout << "\nThe product has been successfully deleted from the database!" << endl;
												Sleep(2000);
											}
											else {
												cout << "Product not found !" << endl;
												Sleep(1000);
												continue;
											}
										}
										else if (adminOption == "4") {
											system("cls");
											db->showAllProductsDetail();
											int idChoiseUpdate;
											cout << "Select the id of the product you want to update: ";
											cin >> idChoiseUpdate;
											if (db->getProducts()->isExistsItems(idChoiseUpdate) == true) {
												system("cls");
												string name, description;
												size_t id, quantity;
												double price, discount, tax;
												db->getProducts()->getItems()[idChoiseUpdate - 1]->showProductItemDetail();
												cout << "\nUpdate the selected product information." << endl;
												cout << "\n(1) To change all the details of the product. \n(2) To change certain parts.\nMake your choice: ";
												int updateFormChoise;
												cin >> updateFormChoise;
												if (updateFormChoise == 1)
												{
													id = db->getProducts()->getItems()[idChoiseUpdate - 1]->getProduct()->getId();
													cout << "Enter update name: ";
													cin.ignore();
													getline(cin, name);
													cout << "Enter update description: ";
													getline(cin, description);
													cout << "Enter update price: ";
													cin >> price;
													cout << "Enter update discount: ";
													cin >> discount;
													cout << "Enter update tax: ";
													cin >> tax;
													cout << "Enter update quantity: ";
													cin >> quantity;
													Product* updateProduct = new Product(id, name, description, price, discount, tax);
													ProductItem* updateProductItem = new ProductItem(updateProduct, quantity);
													db->getProducts()->updateById(idChoiseUpdate, updateProductItem);
												}
												else if (updateFormChoise == 2) {
													int somePartUpdateChoise;
													while (true)
													{
														system("cls");
														db->getProducts()->getItems()[idChoiseUpdate - 1]->showProductItemDetail();
														cout << "\n\n(1) Name\n(2) Description\n(3) Price\n(4) Discount\n(5) Tax\n(6) Quantity\n(7) Send to update" << endl;
														cout << "Make your choice: ";
														cin >> somePartUpdateChoise;
														id = db->getProducts()->getItems()[idChoiseUpdate - 1]->getProduct()->getId();
														db->getProducts()->getItems()[idChoiseUpdate - 1]->getProduct()->setId(id);
														if (somePartUpdateChoise == 1) {
															cout << "Enter update name: ";
															cin.ignore();
															getline(cin, name);
															db->getProducts()->getItems()[idChoiseUpdate - 1]->getProduct()->setName(name);
															continue;
														}
														else if (somePartUpdateChoise == 2) {
															cout << "Enter update description: ";
															cin.ignore();
															getline(cin, description);
															db->getProducts()->getItems()[i]->getProduct()->setDescription(description);
															continue;
														}
														else if (somePartUpdateChoise == 3) {
															cout << "Enter update price: ";
															cin >> price;
															db->getProducts()->getItems()[i]->getProduct()->setPrice(price);
															continue;
														}
														else if (somePartUpdateChoise == 4) {
															cout << "Enter update discount: ";
															cin >> discount;
															db->getProducts()->getItems()[i]->getProduct()->setDiscount(discount);
															continue;
														}
														else if (somePartUpdateChoise == 5) {
															cout << "Enter update tax: ";
															cin >> tax;
															db->getProducts()->getItems()[i]->getProduct()->setTax(tax);
															continue;
														}
														else if (somePartUpdateChoise == 6) {
															cout << "Enter update quantity: ";
															cin >> quantity;
															db->getProducts()->getItems()[i]->setQuantity(quantity);
															continue;
														}
														else if (somePartUpdateChoise == 7) break;
														else {
															cout << "The choice is wrong !" << endl;
															Sleep(1000);
															db->getProducts()->getItems()[idChoiseUpdate - 1]->showProductItemDetail();
															continue;
														}
													}
												}
												else {
													cout << "The choice is wrong !" << endl;
													Sleep(1000);
													continue;
												}

												cout << "The product is updated .";
												for (size_t i = 0; i < 2; i++)
												{
													Sleep(1000);
													cout << ".";
												}
												cout << "\nThe product has been successfully updated !" << endl;
												Sleep(2000);
												continue;
											}
											else {
												cout << "Product not found !" << endl;
												Sleep(1000);
												continue;
											}
										}
										else if (adminOption == "5") {
											cout << "(1) All notifications\n(2) Unread notifications" << endl;
											string notifChoise;
											cout << "Make your choice: ";
											cin >> notifChoise;
											if (notifChoise == "1") {
												system("cls");
												db->showAllNotifications();
												db->showUnReadToReadNotifications();
												string clickBack;
												cout << "\nClick any to back: ";
												cin >> clickBack;
												continue;
											}
											else if (notifChoise == "2") {
												system("cls");
												db->showUnReadNotifications();
												db->showUnReadToReadNotifications();
												cout << "There is no unread notification." << endl;
												string clickBack;
												cout << "\nClick any to back: ";
												cin >> clickBack;
												continue;
											}
											else {
												cout << "Secim yanlisdir, yeniden yoxlayin !" << endl;
												Sleep(700);
												continue;
											}
										}
										else if (adminOption == "6") start();
										else {
											cout << "The choice is wrong, check again !" << endl;
											Sleep(700);
											continue;
										}
									}
								}
								else {
									cout << "Password incorrect !" << endl;
									Sleep(1000);
									continue;
								}
							}
							else {
								cout << "Username incorrect !" << endl;
								Sleep(1000);
								continue;
							}
						}
					}
				}
				else if (option == 2) {
					//Guest hisse
					while (true)
					{
						system("cls");
						cout << "(1) - Guest sign in\n";
						cout << "(2) - Guest sign up\n";
						cout << "(3) - Go back\n";
						string optionGuest;
						cout << "Make your choice: ";
						cin >> optionGuest;
						if (optionGuest == "1")
						{
							string fullname;
							cout << "Enter fullname: ";
							cin.ignore();
							getline(cin, fullname);
							if (db->getGuests()->isExistsItems(fullname)) {
								while (true)
								{
									system("cls");
									db->showAllProductsPreview();
									cout << "_____________________________\n";
									cout << "(1) - Buy" << endl;
									cout << "(2) - Show detail" << endl;
									cout << "(3) - Go back" << endl;
									string optionGuest2;
									cout << "Make your choice: ";
									cin >> optionGuest2;
									if (optionGuest2 == "1") {
										int id;
										size_t quantity;
										cout << "Enter id: ";
										cin >> id;
										if (db->getProducts()->isExistsGuests(id))
										{
											cout << "Enter quantity: ";
											cin >> quantity;
											if (quantity == 0) continue;
											else if (db->getProducts()->getItems()[id - 1]->getQuantity() < quantity) {
												cout << "There aren't as many products in stock as you choose." << endl;
												Sleep(2000);
												continue;
											}
											else {
												string yes_or_no;
												cout << "Are you sure to buy with " << quantity << " amounts?(y/n): ";
												cin >> yes_or_no;
												if (yes_or_no == "y" || yes_or_no == "Y") {
													if (db->getProducts()->getItems()[id - 1]->getQuantity() > quantity) {
														db->getProducts()->getItems()[id - 1]->setQuantity(db->getProducts()->getItems()[id - 1]->getQuantity() - quantity);
														cout << "You buy " << quantity << " of the selected products." << endl;
														Sleep(2000);
														continue;
													}
													else if (db->getProducts()->getItems()[id - 1]->getQuantity() == quantity)
													{
														cout << "You buy " << quantity << " of the selected products." << endl;
														Sleep(2000);
														db->getProducts()->deleteById(id);
														continue;
													}
													else {
														cout << "There aren't as many products in stock as you choose." << endl;
														Sleep(2000);
														continue;
													}
												}
												else if (yes_or_no == "n" || yes_or_no == "N") continue;
											}
										}
										else {
											cout << "Product not found !" << endl;
											Sleep(1000);
											continue;
										}
									}
									else if (optionGuest2 == "2") {
										size_t id;
										cout << "Enter id: ";
										cin >> id;
										if (db->getProducts()->isExistsGuests(id))
										{
											system("cls");
											db->getProducts()->getItems()[id - 1]->showProductItemDetail();
											string click;
											cout << "\n\nClick any to back: ";
											cin >> click;
											system("cls");
											continue;
										}
										else {
											cout << "Product not found !" << endl;
											Sleep(1000);
											continue;
										}
									}
									else if (optionGuest2 == "3") break;
									else {
										cout << "The choice is wrong, check again !" << endl;
										Sleep(700);
										continue;
									}
								}
							}
							else {
								cout << "Login to account failed ..." << endl;
								Sleep(700);
								continue;
							}
						}
						else if (optionGuest == "2") {
							//size_t id;
							string fullname, phone_number;
							/*cout << "Enter id: ";
							cin >> id;*/
							cout << "Enter fullname: ";
							cin.ignore();
							getline(cin, fullname);
							cout << "Enter phone number: ";
							getline(cin, phone_number);
							Guest* newGuest = new Guest(/*id, */fullname, phone_number);
							db->getGuests()->signUp(newGuest);
							Notification* newNotf = new Notification(newGuest, "A new user has registered.");
							db->getNotifications()->add(newNotf);
							cout << "Registration ended successfully." << endl;
							Sleep(1500);
						}
						else if (optionGuest == "3") break;
						else {
							cout << "The choice is wrong, check again !" << endl;
							Sleep(700);
							continue;
						}
					}
				}
				else if (option == 3) exit(0);
				else {
					cout << "The choice is wrong, check again !" << endl;
					Sleep(700);
					continue;
				}
			}
		}
		catch (Exception& ex)
		{
			cout << "\nException occured !";
			ex.PrintMsg();
		}
	}
}

int main() {
	ECommerce::start();
	return 0;
}

