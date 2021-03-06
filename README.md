CDKiosk
=======
by [narrowtux](http://narrowtux.com)

A Kiosk application which aims to work with the Primera Disc Publisher SE. 

However, this project is built in a way you can implement your own "Driver".

Gallery
-------
Here are some screenshots of the application to give you a rough overview of the features:

![Screenshot of the Home screen](http://i.imgur.com/vN4PD.png)

Building
--------
To build the project, you need [Qt](http://www.qt-project.org). To simply build it, follow theese 2 easy steps:

	qmake CDKiosk.pro
	make

After that, you should find an executable in the target folder (usually "../CDKiosk-[target]/").

Contributing
------------
If you want to contribute the project, the easiest way is to fork the project on [github](https://github.com/narrowtux/CDKiosk)
and push your changes to your fork. After you finished your new feature/bug fix/contribution, you can submit a pull request

Please remember to sign your commits like that:

	Commit message
	
	Signed-off-by: name<email@example.com>
	
Git will do this automatically if you add the -s parameter to the git commit call:

	git commit -s 

Copyright
---------
CDKiosk is released under the GNU Lesser General Public License Version 3 (LGPLv3).
For a copy of the license, see LICENSE.txt
