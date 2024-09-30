# Finance-management-Cpp-File-handling
This C++ project helps users manage their money by allowing them to register, log in, and track their income and expenses. Users can add funds and record transactions, with all data saved in files for easy access.


How To Run:
 * Execute Code and register your account(if not registered)
 * After Successfull registration, Login to your account
 * After login your current balance will shown to you.
 * Now, User have options to add amount, add expences and and Logging out your account
 * You can add funds and expences to your account and details of each transaction(Time, Description and Amount) will be save in user transaction file and balance 
   will be updated in User Balance File after each transaction.


Sample of Each Functionality:
  * Register:

Welcome to Finance Management System
1. Login
2. Register
Enter your choice: 2
---- Create your account to handle and track your Finance ----

Enter your details:
User Name: mujtaba
Pass Key: 123
Email: mujtaba@gmail.com
Register Successful!
Your UUID is: 1142 (Don't forget your UUID!)


  * Login:

Welcome to Finance Management System
1. Login
2. Register
Enter your choice: 1

---- Login to your Finance Account ----
User Name: mujtaba
Pass Key: 123
Email: mujtaba@gmail.com
UUID: 1142
Login Successful!


  * Add amount:
  
-----Transaction Menu-----
1. Add Amount
2. Add Expense
3. Logout
Enter your choice: 1

Enter Amount To Add: 56000
Amount Added: 56000
Updated Balance: 56000

---Details of Transaction---
Amount: 56000
Description: Funds Added
Time: Mon Sep 30 13:44:56 2024


  * Add Expence

-----Transaction Menu-----
1. Add Amount
2. Add Expense
3. Logout
Enter your choice: 2

Expense Amount: 3500
Expense Description: Gym Fee
Expense Added: 3500
Updated Balance: 52500

---Details of Transaction---
Amount: 3500
Description: Gym Fee
Time: Mon Sep 30 13:46:55 2024


  * LogOut:

-----Transaction Menu-----
1. Add Amount
2. Add Expense
3. Logout
Enter your choice: 3
Logging Out...



Data Stored In File:

  * User File:

mujtaba 123 mujtaba@gmail.com 1142


  * User Balance File:

52500


  * User Transaction File:

---Details of Transaction---
Amount: 56000
Description: Funds Added
Time: Mon Sep 30 13:44:56 2024
--------------------------

---Details of Transaction---
Amount: 3500
Description: Gym Fee
Time: Mon Sep 30 13:46:55 2024
--------------------------


This are functionalities of my simple code that i have done to boost my Concepts of c++ language and to prepare myself for furtur improvement.










