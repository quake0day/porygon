porygon
=======
![Mou icon](http://fc07.deviantart.net/fs70/f/2012/274/8/1/virtual_pokemon_by_twarda8-d5gi507.png)


## Overview
a simple virtual memory manager “virtualmem” in  C/C++ on a UNIX-based platform.
 
Due date: Nov 20 2012

## Usage
To compile the program, change to current project directory, then type command: 
	
	make
To run this program, use command: 

	./virtualmem
	
User needs to input page reference string. 
Press **Enter** to finish. The element in reference string should be separated by **blank space**.

## Options

-f **frame_size**: By default, the frame size is 5. You can set it by using this option.
-r **replacement_policy**: There are 5 available replacement algorithms. They are: 

* FIFO (First-in-first-out)
* LFU (Least-frequently-used)
* LRU-STACK (Least-recently-used stack implementation)
* LRU-CLOCK ((Least-recently-used clock implementation – second chance alg.). 
* LRU-REF8 (Least-recently-used Reference-bit Implementation, using 8 reference bits)

The default will be FIFO.
-i **input_file**: use this option, user and choose an input file contains reference string. The page number in reference string should be separated by blank space. If the file doesn't exist, user need manually input the reference string. Max length of the element in reference string is 10240.
## Member
Si Chen