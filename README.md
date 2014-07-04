###OVERVIEW
This is a minimal demo of using libSPRITE. This demo exercies a
sping-mass-damper system.

###BUILD:
Execute 'make'

###RUN:
As root (or sudo), execute './sprite_main smd.lua' where sprite_main is the
application and demo.lua is a script that describes what and how tasks built
using libSPRITE should do, such as task execution rates, priorities, etc...
These scripts can get much more sophisticated for larger applications.

###MODIFY:
The parameters of the system can be modified in from the Lua script. Near the
top of the file are the spring constant (k), damper constant (B), and the mass.
Change these are rerun. There is not need to recompile the code. The parameters
are passed to the application through the script.
