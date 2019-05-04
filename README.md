# TextSearch
Text Search program

 

TextSearch, the program in the image above takes input for the filename that its user wants to analyse and search through. The file being searched through must be in the parent folder/directory of the program.

 
 
	While searching for a pattern or a word using this program, the user will be asked if the search should be case sensitive, if his choice should be remembered in the next search (If the case should be locked) and if he wishes to view the search matches.

 
 
 
The case can be unlocked from being reused in future searches by using the ‘&menu’ command and selecting the second option on the menu. This menu also gives the user the power to change the selected file without restarting the program.

 
 
 

There are 3 wildcards that can be used (*,?, #). The wildcard ‘*’ matches anything, the wildcard ‘?’ matches just one character while the ‘#’ wildcard searches for the frequency of words instead of the words themselves. The syntax of these wildcards is displayed in the images above.




# How it works (Brief Description)

The program makes use of a customized binary search tree. The tree is like the standard binary search tree except it keeps count of  the instances of each word. 
Words extracted from text files being searched through are stored in a list of strings (a vector) and they are sorted alphabetically. The middle word of the list is taken as the root node and words are added to the tree from the start of the list, skipping the root node. This allows the binary to take a form in which the two branches can be searched through asynchronously on different threads to enable the program to search through files with thousands of words.
	
