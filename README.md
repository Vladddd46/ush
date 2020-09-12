<h1>USH</h1>
<p>My own implementation of unix shell.</p>
<p>A Unix shell is a command-line interpreter or shell that provides a command line user interface for Unix-like operating systems.</p>

It contains:

    - user`s input\n
      > backspace
      > logic operators || && 
      > cmd separator ;
    - external binary executing
      > path/bin_name; ls; clear; mkdir; ./bin_name ... etc.
    - 9 built-ins:
      > export
      > unset
      > exit
      > env   [-i -P -u]
      > cd    [-s -P -]
      > pwd   [-L -P]
      > which [-a -s]
      > echo  [-n -e -E]
      > fg    [%n %str]
    - signals handling
      > Ctrl+D
      > Ctrl+Z
      > Ctrl+C
    - substitutions
      > ~; ~/dir_name; ~username/dirname; ~+/dirname; ~-/dirname
      > variable substitution ${VARNAME};$VARNAME
      > command substitution  `command`; $(command)
GitHub: Vladddd46
10.02.2020
