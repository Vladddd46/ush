<h1>USH</h1>
<p>My own implementation of <b>unix shell</b>.</p>
<p>A <b>Unix shell</b> is a command-line interpreter or shell that provides a command line user interface for Unix-like operating systems.</p>
<p>For more details <a href="https://en.wikipedia.org/wiki/Unix_shell">Wiki</a></p>

<h2>Compilation</h2>
<ul>
    <li>Write <b>make</b> in root directory to compile project.</li>
    <li>Compilation was done only on <b>MacOS</b>. Other OS were not tested</li>
</ul>

<h2>Functional overview:</h2>
<ul>
    <li>backspace</li>
    <li>command separator `;`</li>
    <li>logic operators `||` and `&&`</li>
    <li>external binary executing: path/binary_name, ls, mkdir etc. (all binaries form standart folders /bin /etc/bin etc.)</li>
    <li>export built-in</li>
    
    <li>unset built-in</li>
    <li>export built-in</li>
    <li>exit built-in</li>
    <li>env [-i -P -u] built-in</li>
    <li>cd [-s -P -] built-in</li>
    <li>pwd [-L -P] built-in</li>
    <li>which [-a -s] built-in</li>
    
    <li>echo [-n -e -E] built-in</li>
    <li>fg [%n %str] built-in</li>
    <li>Signals handling: <b>CTRL+Z</b> <b>CTRL+D</b> <b>CTRL+C</b></li>
    <li>tilda: ~; ~/dir_name; ~username/dir_name; ~+/dir_name; ~-/dir_name</li>
    <li>variable substitution ${VARNAME}; $VARNAME</li>
    <li>command substitution  `command`; $(command)</li>
</ul>

<h2>Overview</h2>

![ezgif com-video-to-gif](https://user-images.githubusercontent.com/11888485/93004705-490e0380-f552-11ea-85b5-d259c84309d1.gif)


