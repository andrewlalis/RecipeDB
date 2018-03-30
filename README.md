# Recipe DB

![screenshot](http://i.imgur.com/FbltFit.png)

Recipe DB is a simple, lightweight database powered by Qt and SQLite to allow you to save, retrieve, and search through many recipes without needing to be connected to the internet. Meant as a tool for those who enjoy making recipes their own, this tool lets you edit recipes, search by ingredients or food groups, and filter out recipes that meet certain criteria. Recipe DB was created initially out of a desire to organize my many recipes in one uniform way, as simply as possible, while still making sure that retrieving any given recipe is as effortless as possible. I wanted something where I could save recipes offline, change them if I need to, convert units on-the-fly, and add a few other small utilities that would save a few precious minutes in the kitchen.

### How it works

For the user interface, a [Qt](https://www.qt.io/) Application is built, both for ease of development, and the sleek, modern visual effects for which it is popular. To save the recipes, the world-famous [SQLite](https://www.sqlite.org/) embedded database engine was used. It is simply the most obvious choice for a locally stored relational database, and has proven its worth in billions of devices and applications. The filtering, searching, and other various operations used to store and retrieve data from the database is done through the use of SQL statements constructed around user-generated parameters.

### To-Do List

* Finish User Interface
* Finish and ensure safety of SQL statements and tables in the database; ensure persistence.
* Implement Searching/Filtering
* Create an *Edit* mode in which the user can change a recipe's data.
* Create file protocol to save recipe data which is linked in the database.
	* Create a file-naming protocol.
* No save button, should save everything automatically.
* Share Options:
	* Social Media
	* Email
	* Generate PDF, Word Document
* Automatic Unit conversion for ingredients, using pre-determined conversion rates.