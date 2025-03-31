# Introduction to UML
## 1. General Concept

## 1.1 What is it ?
- A standard modeling language that can be applied for implementing software development process 

## 1.2 Why is it important ?

__a) Break down complex into small pieces__

- Allow visualize the complex system via diagrams
- Allow understand system's Behaviour and Structural before programming

__b) Documenting system__

- Provide standards and necessary Element to build system document include data structure, logic, work flow, interaction between objects
- Help collaborate,communicate more effectively among team members

__c) Communication__

- Provide a common language to synchronize the communication and understanding of general working system__

__d) Risk evaluation and impact verification__

- Allow to validate the impact before implementing 

## 1.3 How to implement ? 

<p align = center>
<img src = "https://github.com/user-attachments/assets/37215dc2-379c-4359-b6d6-c92d03042564" width = "600" height = "450">

## 2.Structural Diagram

### 2.1 Class Diagram

__a)  What is it ?__ 
- provide the general overview of system's structure
- Describe what are:
    + properties, method
    + relationship between them
__b) Element ?__ 

__Accessed Modifer__ 

+ Public
- Private
# Protected
~ Package Local 

<p align = center>
<img src = "https://github.com/user-attachments/assets/7c6c0c0a-48fd-455b-b6f6-5a14b3244e36" width = "600" height = "250">

__Relationship between Class and Interface__

<p align = center>
<img src = "https://github.com/user-attachments/assets/0078543e-1f5b-446d-ba5f-78de976a26bf" width = "400" height = "150">

__ASSOCIATION__

- 2 class can be used each other Interface
- 1 class can use / be used between multi class 

+ Tight coupling:
=> 1 class declare a pointer/reference to directly control other class 

<p align = center>
<img src = "https://github.com/user-attachments/assets/51858709-3721-4dd6-93c7-732931a1c3acf" width = "400" height = "150">

- 1 base class provide abtract interface that can be written by deprived classes 

__INHERITANCE__

<p align = center>
<img src = "https://github.com/user-attachments/assets/ac2468fc-3a5c-41ca-8cc9-062944c6c915" width = "400" height = "150">

__REALIZATION__

- 1 class provide interface which input parameter depends on 1 or multi class

<p align = center>
<img src = "https://github.com/user-attachments/assets/bc3ede7f-7ad3-45dc-bd29-75dd1a182be5" width = "400" height = "250">

__DEPENDENCY__

- 1 class uses object from other
- change from this class will take effect on other 

+ Loose coupling
=> 1 class can use/call interface from other  

<p align = center>
<img src = "https://github.com/user-attachments/assets/028d68bc-a675-45f9-b953-7de5696a5733" width = "400" height = "150">


__AGGREGATION__

- A general class can contain other specific classes
- All child classes does still exist even general class is deleted

<p align = center>
<img src = "https://github.com/user-attachments/assets/0a349976-8a5d-46eb-bec1-6cff7993d52c" width = "400" height = "250">

__COMPOSITION__

- strong form of aggeration if a Composite is deleted then all its parts are also deleted as well

<p align = center>
<img src = "https://github.com/user-attachments/assets/c2a7958b-959b-4a3f-9f71-94d5bc3c2ae3" width = "400" height = "250">


__c) How to implement ?__
- Indentify class and interface 
- Indentify properties and method 
- Describe relationship between class or class and interface using notation
- Draw diagram

__d) Example__ 

<p align = center>
<img src = "https://github.com/user-attachments/assets/91202a00-88d2-45f7-9cf1-fff82fa78758" width = "600" height = "350">

### 2.2 Component Diagram

__a)  What is it ?__ 
- breakdown system into various high-level functionalities 
- each component responsible for 1 duty and interact with other

<p align = center>
<img src = "https://github.com/user-attachments/assets/abd1c977-750d-47c2-ac6c-d462be0ed6ad" width = "750" height = "350">


__b) Element ?__ 

- Component: high-level functionality

 <p align = center>
<img src = "https://github.com/user-attachments/assets/f615ec32-fded-4643-bd35-bce458381d99" width = "750" height = "350">


- Interface: activities provided by one or request by other component
 
<p align = center>
<img src = "https://github.com/user-attachments/assets/df40c1f7-56ba-42f0-a95f-59a220864bc4" width = "550" height = "350">

- Port: attach to component with provided interface

<p align = center>
<img src = "https://github.com/user-attachments/assets/82677a3c-34f9-4335-92bb-138e3850abde" width = "750" height = "350">


__c) How to implement ?__



__d) Example__ 

<p align = center>
<img src = "https://github.com/user-attachments/assets/3105c5b5-e305-496d-911f-e3a750eb3b96" width = "750" height = "350">


### 2.3 Deployment Diagram

__a)  What is it ?__ 

+ Show how firmware run on hardware 

<p align = center>
<img src = "https://github.com/user-attachments/assets/291a5095-b37d-434b-bb1f-862e5edaa4d2" width =" "750" height = "350">

__b) Element ?__ 

+ Node: hardware parts like board,chip,sensor

+ Artefact: firmware installed on Node

+ Communication path: specific communication protocol between hardware node

__c) When uses it ?__

+ represent soft-hard Architecture of system with multi hardware components

__d) Example__ 

<p align = center>
<img src = "https://github.com/user-attachments/assets/6a4d52c8-e0cf-4cca-a584-c35ba50ea380" width =" "750" height = "350">



### 2.4 Object Diagram
__a)  What is it ?__ 

+ Show instance of class diagram 
+ capture snapshot of a detail state of system at specific time during running 
+ depict small part of system

<p align = center>
<img src = "https://github.com/user-attachments/assets/eb4c2c6d-58f2-4345-b4f9-0c3612c8670c"750" height = "350">

__b) Element ?__ 

+ Object: name + value

<p align = center>
<img src = "https://github.com/user-attachments/assets/2a2eb662-aa65-4a87-91c1-7f25d4c795b6" width =" "750" height = "350">

+ Link: how to connect them

__c) When uses it ?__
+ create a testcase for verification purpose
+ model behaviour and interraction between classes at current time

__d) Example__ 
### 2.5 Package Diagram

__a)  What is it ?__ 

+ Show group of class, module into a single package that serve general puprpose 

<p align = center>
<img src = "https://github.com/user-attachments/assets/69a2f149-6282-4a20-b2cc-b54b84dbde20"750" height = "350">


__c) When uses it ?__

+ Devide system into different layers : Application, middle, driver


### 2.6 Composite structure diargam


__a)  What is it ?__ 

- Show internal structure of class and how they interact to handle a specific duty of this given class

<p align = center>
<img src = "https://github.com/user-attachments/assets/4eff5b2c-8b12-4172-b25c-e6db892325a1"750" height = "350">

 
### 2.7 Profile Diagram 

## 3.Behaviour Diagram

### 3.1 Use cases Diagram

### 3.2 Activity Diagram 

### 3.3 State machine Diagram

### 3.4 Sequence Diagram

### 3.5 Communication Diagram

### 3.6 Interaction overview Diagram

### 3.7 Timing Diagram