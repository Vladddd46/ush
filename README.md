<h1>USH</h1>
<p>My own implementation of <b>unix shell</b>.</p>
<p>A <b>Unix shell</b> is a command-line interpreter or shell that provides a command line user interface for Unix-like operating systems.</p>
<p>For more details <a href="https://en.wikipedia.org/wiki/Unix_shell">Wiki</a></p>

<h2>Compilation</h2>
<ul>
    <li>Write <b>make</b> in root directory to compile project.</li>
    <li>Compilation was done only on <b>MacOS</b>. Other OS were not tested</li>
</ul>

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
