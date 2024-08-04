# Circuit-Simulator
Simulate a circuit of resistors in series using knowledge of dynamic memory allocation and linked lists. The resistors in the circuit will be stored in memory with the use of a linked list, with one list node per resistor. Each resistor entry will contain the following information: 
1. Value of the resistance in Ohms (Ω)
2. Label of the resistor

Simulate adding/removing resistors to a circuit, printing their values, calculating the current in the circuit, and measuring the voltage across a resistor.
The simulator starts by asking the user the value of the source voltage vs in volts.
Then, the program is “menu” driven, with the user being offered a choice of the following 6 “commands”:

1. Command I. Insert a new resistor into the circuit. The program should prompt the user for the value of the resistor, which is an integer, and the label of the resistor.
2. Command R. Remove a resistor from the circuit. The program should prompt the user for the label of the resistor, the program will then find and delete the node containing that label from the circuit.
3. Command C. Calculate the current flowing through all the resistors.
4. Command P. Print the labels and values of the resistors in alphabetical order by label of the resistor.
5. Command V. Calculates the potential difference/voltage across a particular resistor.
6. Command Q. Delete all the nodes in the linked list/circuit. 
