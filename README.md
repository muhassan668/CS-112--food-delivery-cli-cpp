# CS-112 Food Delivery CLI System

A terminal-based **Digital Food Ordering System** developed in C++ as a CS-112 Object-Oriented Programming semester project.

The project simulates a simple food delivery platform where customers can view restaurants, add menu items to cart, place orders, make payments, and where admins can manage order-related operations. The system uses file handling to store and load data such as users, restaurants, menu items, orders, and delivery agents.

---

## Features

* Customer registration and login
* Admin login
* View available restaurants
* View menu items
* Add items to cart
* Place food orders
* Payment handling
* Delivery agent assignment
* Delivery agent availability management
* Order status updates
* File-based data storage

---

## Object-Oriented Programming Concepts Used

This project demonstrates several core OOP concepts:

* **Classes and Objects**
* **Encapsulation**
* **Inheritance**
* **Composition**
* **Aggregation**
* **File Handling**
* **Dynamic Program Structure**
* **Modular Programming using Header and Source Files**

---

## Project Structure

```text
CS-112--food-delivery-cli-cpp
│
├── main.cpp
├── Enums.h
│
├── User.h
├── User.cpp
│
├── Customer.h
├── Customer.cpp
│
├── Admin.h
├── Admin.cpp
│
├── DeliveryAgent.h
├── DeliveryAgent.cpp
│
├── MenuItem.h
├── MenuItem.cpp
│
├── Restaurant.h
├── Restaurant.cpp
│
├── Cart.h
├── Cart.cpp
│
├── Order.h
├── Order.cpp
│
├── Payment.h
├── Payment.cpp
│
├── FileManager.h
├── FileManager.cpp
│
├── CommandHandler.h
├── CommandHandler.cpp
│
├── users.txt
├── restaurants.txt
├── menu_items.txt
├── orders.txt
├── delivery_agents.txt
│
├── .gitignore
└── README.md
```

---

## Technologies Used

* C++
* Object-Oriented Programming
* File Handling
* Command Line Interface
* Git and GitHub

---

## Data Files

The project uses text files for storing and loading data:

* `users.txt`
* `restaurants.txt`
* `menu_items.txt`
* `orders.txt`
* `delivery_agents.txt`

Make sure these files are present in the same folder as the source code before running the program.

---

## Team Members

* Muhammad Hassan
* Muhammad Salman Saeed

---

## Course Information

* **Course:** CS-112 Object-Oriented Programming and Design
* **Project Type:** Semester Project
* **Language:** C++

---

## Notes

This project was created for academic learning purposes. It focuses on applying object-oriented programming concepts in a practical command-line application.
