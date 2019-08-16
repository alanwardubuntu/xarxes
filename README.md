# "xarxes" historical network analysis project

The aim of this project is to create a network analysis system for historical 
transport networks. Basic outputs should be:

* Calculate the cost of transport from node A to node B inside the network.
* Calculate the time necessary for such transport.

Programming is done in the C language, with some parts (graphical output) in 
Python. Input files are simply in the Comma-Separated-Value (CSV) format.

All code is licensed for free distribution under the Creative-Commons 
Share-Alike No-Commercial Licence version 3.0 (CC BY-NC-SA 3.0). The full 
text of this licence may be found here: https://creativecommons.org/licenses/by-nc-sa/3.0/ 

## Program source code -- the code/ subdirectory

* xarxa.h  = Header file with general definitions
* xarxa.c  = Main program
* other .c = calculation subroutines

* Makefile = compilation directives for gnumake

* grafic.py = a program in the Python language to read in a result file 
              in CSV format, and output a graphical result figure

* xarxa_nodus.csv = a test network node definition file, in CSV
* xarxa_camins.csv = a test network edge definition file, in CSV

## Program results -- the results/ subdirectory

This subdirectory contains some test results from a network centered on Roman-era 
(1st c. BCE to 1st c. CE) Pyrenees and neighbouring regions. Contents should 
be fairly self-explanatory.


## Comments and suggestions

Any comments and (constructive) criticism are welcome by email at 
alan.ward.ubuntu at gmail.com .

