# Operating systems and system programming course work - Kernel hacking

This is a collection of custom implementations of basic Unix utilities. Includes cat, grep, zip and unzip

** My-cat
My-cat is a simple program that simply prints out the contents of a file. It is given one or more
filenames as parameters. My-cat will print out the contents of each file, with nothing separating the 
files in the output. Redirecting the output to a file using the ‘>’ character works as well, for example 
“./my-cat file1 file2>output”.


** My-grep
My-grep is given a search term and zero or more files as arguments. My-grep will then search for the 
term in the contents of the files, and print out all matching lines. If multiple matches are found on 
the same line, the line gets printed out for each match. If no files are given, stdin will be searched 
instead. The output can be redirected with the ‘>’ character. Example use: “./my-grep text file1 
file2>output”.

One change I made from Linux’s grep was that I printed every match to a separate line, while 
standard grep recolors all matches in a given line. Standard grep seems to continue looking for new 
matches after the matched pattern, but if a new match begins within the matched pattern, grep 
misses it. For example, if you search for “text” in the repeating pattern “textextext” grep will match 
“<sub>text</sub>ex<sub>text</sub>”, but my-grep will match “<sub>text</sub>extext” “tex<sub>text</sub>ext” and “textex<sub>text</sub>”.

** My-zip and my-unzip
My-zip uses run-length-encoding to try and compress the information of the given files. My-zip is 
given one or more file names, which will be compressed into a binary file consisting of a 4-byte 
integer followed by a 1-byte character. When compressing multiple files, the files will be compressed 
together, with no way to separate the files again after compression. My-unzip will by default write 
its’ output to stdout, so it’s recommended to redirect the output to a file using the ‘>’ character, for 
example: “./my-zip file1 file2>zipped”.

My-unzip uncompresses a file that was previously compressed by my-zip. My-unzip takes one 
parameter, the filename of the compressed file. By default, my-unzip prints the uncompressed 
output to stdout, but you can use the redirection to write the output to a file using for example 
“./my-unzip zipped>unzipped”.

Run-length encoding can in fact increase the file size, if there are not enough of the same character 
consecutively, since an integer is added before each character. 
