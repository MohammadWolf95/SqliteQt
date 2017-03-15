# QTProjects
These projects are written using QT

This project uses the library sqlite3 and does payroll staff. The description of this task is located in CompanySqlite3QT / task.txt.

How to build a project?<br>
for Windows msvc:<br>
First specify in the .pro file the path to include files sqlite3 (I also poured the library sqlite3, it is in the folder sqlite3).
Then you connect the library files in the .pro file (depending on which compiler, for example: if you select a project under x86 and you have a debug program, then connect the library sqlite3 \ lib \ x86 \ sqlite3libd.lib). Finally, you must specify the path to sqlite3.exe in environment variables
