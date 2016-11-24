MKDIR(1)                                    User Commands                                   MKDIR(1)



NNAAMMEE
       mkdir - make directories

SSYYNNOOPPSSIISS
       mmkkddiirr [_O_P_T_I_O_N]... _D_I_R_E_C_T_O_R_Y...

DDEESSCCRRIIPPTTIIOONN
       Create the DIRECTORY(ies), if they do not already exist.

       Mandatory arguments to long options are mandatory for short options too.

       --mm, ----mmooddee=_M_O_D_E
              set file mode (as in chmod), not a=rwx - umask

       --pp, ----ppaarreennttss
              no error if existing, make parent directories as needed

       --vv, ----vveerrbboossee
              print a message for each created directory

       --ZZ     set SELinux security context of each created directory to the default type

       ----ccoonntteexxtt[=_C_T_X]
              like --ZZ, or if CTX is specified then set the SELinux or SMACK security context to CTX

       ----hheellpp display this help and exit

       ----vveerrssiioonn
              output version information and exit

AAUUTTHHOORR
       Written by David MacKenzie.

RREEPPOORRTTIINNGG BBUUGGSS
       GNU coreutils online help: <http://www.gnu.org/software/coreutils/>
       Report mkdir translation bugs to <http://translationproject.org/team/>

CCOOPPYYRRIIGGHHTT
       Copyright  ©  2014 Free Software Foundation, Inc.  License GPLv3+: GNU GPL version 3 or later
       <http://gnu.org/licenses/gpl.html>.
       This is free software: you are free to change and redistribute it.  There is NO WARRANTY,  to
       the extent permitted by law.

SSEEEE AALLSSOO
       mkdir(2)

       Full documentation at: <http://www.gnu.org/software/coreutils/mkdir>
       or available locally via: info '(coreutils) mkdir invocation'



GNU coreutils 8.23                           March 2015                                     MKDIR(1)
