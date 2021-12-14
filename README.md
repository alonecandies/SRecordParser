Hoàng Phi Long - LongHP7
Dear teachers, this is my mock project for my internship program. 
Hope it will not be error on delivery T.T

##Requirements
   Windows OS
   gcc.exe (tdm-1) 5.1.0

##Documentation
   To run this mock project, you need to compile main file and shared library files 
with gcc and run with 2 arguments which is srecord file you want to parse and 
output file you want to write in.
   Below is tutorial how to get output file with srecord input file.

   Command line:

```console
$ gcc srecord.c main.c -o <program name>
$ ./<program name> <input file> <output file>
```

   Example:

```console
$ gcc srecord.c main.c -o SrecordParserTool
$ ./SrecordParserTool input.srec output.txt
```
