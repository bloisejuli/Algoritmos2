To compile this application use `$ make`  or `$ make main`

If you prefer to compile by using the command g++ the command is:
`clear && g++ *cpp -Wall -Werror -Wconversion -o main`
And then just run $ ./main

***IF YOU ADD A BUILDING IN 'UBICACIONES.TXT' MAKE SURE THE NAME/TYPE IT'S ALSO ON THE 'EDIFICIOS.TXT' FILE OR THE PROGRAM WILL THROW A SEGMENTATION ERROR***

If the map doesn't print aligned in your terminal, you can go to file **constant.h** and add or erase extra spaces on the constants icons.

There is an error in lines 80 and 81 in the file "city.cpp", for some reason every time it randomly produces steel the quantity is ALWAYS 4, maybe it has something to do with the seed, but we are not sure it has something to do with the random function.

Option "10" only makes sense if you played Age of Empires II.
