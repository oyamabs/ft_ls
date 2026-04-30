# ft\_ls

As simple as listing the files in a directory.

## Goal 

Recreate the `ls` utility command (man ls).

## Mandatory part

list directory, the command should at least support the following flags -r -R -l -a -t

- `-l` - Gives a more detailed list of the files (for example `-rwxr-xr-x 7 user group 189 Nov 26 18:07 file`)
- `-a` - Includes every hidden files (files that starts with a dot)
- `-R` - Lists every subdirectory in the current one
- `-r` - Lists files in reverse order
- `-t` - Sorts the listed files by their last modification first

The output of ft\_ls should be as close as possible to the output of the actual ls command

> ⚠️  It is not required to list the files in columns if -l option is not passed.
> ⚠️  It is not required to handle ACL and extended attributes in the mandatory part

No particular locale management is asked

## Bonus part

- Add as many other arguments as wanted
- Add support for colors
- Add support for ACL and extended attributes
- Optimize the code as best as possible

## Allowed functions

libft is advised and recommended (as printf is forbidden)
- write
- opendir
- readdir
- closedir
- stat
- lstat
- getpwuid
- getgrgid
- listxattr
- getxattr
- time
- ctime
- readlink
- malloc
- free
- perror
- strerror
- exit

Some other functions may be allowed if they are needed during the defense (printf is not allowed because it's out of pure lazyness, tcgetattr may be allowed in certain cases)
