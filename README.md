A very small, lightweight JSON formatter for *nix systems.
It takes no command line switches, doesn't buffer data or otherwise allocate memory.
Designed to be used in long running streams.



Compiling:
    cc -o jsonf jsonf.c

Installing:

    (as root)
    
    cp jsonf /usr/bin
    
    chmod 755 /usr/bin/jsonf

Using:
    Works like most *nix command line programs.
    Can read input from a file or from stdin.
    Writes all output to stdout.

    jsonf <file>

    or

    cat <file> | jsonf

    or 
 
    jsonf < <file>

    or (as used by author to format console output from JSON bases web services...)
  
    tail -f <file> | jsonf
    
    

Author: Ben Souther
