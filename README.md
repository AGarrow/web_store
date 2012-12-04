COMP 206 FINAL ASSIGNMENT
=========================

Hanif Jetha (260205055), Alexander Garrow(enter your ID), Santiago Paiva (enter your ID)

Link to site (on Alexi's public folder):
----------------------------------------

[Human Bixie - HOME](http://cs.mcgill.ca/~agarro/home.html)

*Live Databases* (found in Alexi's `public_html/databases/`):

[Live *members.csv*](http://cs.mcgill.ca/~agarro/databases/members.csv)
[Live *log.csv*](http://cs.mcgill.ca/~agarro/databases/log.csv)
[Live *inventory.csv*](http://cs.mcgill.ca/~agarro/databases/inventory.csv)

Outline:
--------

`/pages`: contains all web pages and css

`/cgi-bin`: contains all c and python cgi scripts, and the `passweb_store` executable (essentially
a modified version of passweb from the last assignment

`/_raw_C_files`: contains uncompiled c code, so you can see what's going on behind the scenes

`/_raw_python`: contains copies of all the python stuff in the `/cgi-bin` folder, all in one place

`/databases`: contains all our CSV "databases", including: `members.csv`, `log.csv`, and `inventory.csv`

User Accounts:
--------------

(all this info is additionally available in `/databases/members.csv`

<table>
  <tr>
    <th>username</th><th>password</th><th>type</th>
  </tr>
  <tr>
    <td>agarrow</td><td>alexi</td><td>SYSTEM</td>
  </tr>
  <tr>
  <td>hjetha</td><td>hanif</td><td>SYSTEM</td>
  </tr>
 <tr>
  <td>spaiva</td><td>santiago</td><td>SYSTEM</td>
  </tr>
 <tr>
  <td>jblow</td><td>joe</td><td>USER</td>
  </tr>
 <tr>
  <td>ablow</td><td>alex</td><td>USER</td>
  </tr>
 <tr>
  <td>marcellus</td><td>wallace</td><td>USER</td>
  </tr>
</table>


Notes:
------

**Things to finish up (delete this section before handing in):**

* delete redundant web_store directory
* make sure python script to write to log works
* finish c code to display user's purchase history
* organize directory (copy all python shit to python folder, clean up useless stuff, keep everything organized)
* clone this repo in the shared folder so TAs can check out the log, possibly "unhide" the log and include it as an additional file in the main directory
* make sure everything works on alexi's cs public_html folder
* tar,zip,submit
* hope we get 100
