# ft_ls

42 School `ft_ls` project — a reimplementation of the `ls` command in C.

## Features

- `-l`: use a long listing format
- `-R`: list subdirectories recursively
- `-a`: include hidden entries
- `-r`: reverse the sorting order
- `-t`: sort by modification time
- `-u`: use access time for sorting and long output
- `-f`: disable sorting and include hidden entries
- `-g`: use long format without the owner column
- `-d`: list directories themselves instead of their contents
- `-1`: display one entry per line
- Column display on terminal output
- Size-aligned long listing output
- Major and minor numbers for character and block devices

## Build

```sh
make
```

Other available rules:

- `make clean`: remove object files
- `make fclean`: remove object files, `libft.a`, and the executable
- `make re`: run `fclean` and rebuild the project

## Usage

```sh
./ft_ls
./ft_ls -la
./ft_ls -lR /etc
```

Options can be combined, for example `-laRrt`.

## Project structure

```text
ft_ls/
├── include/    # ft_ls headers
├── libft/      # local utility library and its Makefile
├── src/        # argument parsing, sorting, display, and recursion
└── Makefile
```

`src/` contains the command implementation, `libft/` provides reusable utility
functions, and `include/` contains the shared project declarations.

## Allowed functions

The project uses the system functions allowed by the subject:

```text
write, opendir, readdir, closedir, stat, lstat,
getpwuid, getgrgid, time, ctime, readlink,
malloc, free, perror, strerror, exit
```

## Notes

ACL and extended attribute indicators are not supported. They are outside the
required scope of the 42 subject.
