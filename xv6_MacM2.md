Updated on 1/15/2024
==========
Firstly, you need to install `gcc` on your Mac. Next is to install `QEMU`. To do this, you will need `Homebrew` and `MacPorts` installed. I ran `brew install qemu` followed by `sudo port install i386-elf-gcc`. If the installation of i386-elf-gcc has error such as
```
--->  Building i386-elf-gcc                              
Error: Failed to build i386-elf-gcc: command execution failed
Error: See /opt/local/var/macports/logs/_opt_local_var_macports_sources_rsync.macports.org_macports_release_tarballs_ports_cross_i386-elf-gcc/i386-elf-gcc/main.log for details.
Error: Follow https://guide.macports.org/#project.tickets if you believe there is a bug.
Error: Processing of port i386-elf-gcc failed
--->  Some of the ports you installed have notes:
  db48 has the following notes:
    The Java and Tcl bindings are now provided by the db48-java and
    db48-tcl subports.
```

Then try the following
```shell
sudo port -v selfupdate
brew tap nativeos/i386-elf-toolchain
brew install nativeos/i386-elf-toolchain/i386-elf-binutils
brew install nativeos/i386-elf-toolchain/i386-elf-gcc
```

After running these commands you can clone the xv6 repo
```shell
cd
mkdir -p CSCE410/Assignment1
cd CSCE410/Assignment1
git clone git@github.com:mit-pdos/xv6-public.git xv6-1
```

After cloning the repository you will need to edit the `Makefile` of `xv6` so that line 32 is uncommented and has the following TOOLPREFIX as well as commenting out lines 38-51, as shown in the following
```shell
# Cross-compiling (e.g., on Mac OS X)
TOOLPREFIX = i386-elf-

# Using native tools (e.g., on X86 Linux)
#TOOLPREFIX = 

# Try to infer the correct TOOLPREFIX if not set
# ifndef TOOLPREFIX
# TOOLPREFIX := $(shell if i386-jos-elf-objdump -i 2>&1 | grep '^elf32-i386$$' >/dev/null 2>&1; \
# 	then echo 'i386-jos-elf-'; \
# 	elif objdump -i 2>&1 | grep 'elf32-i386' >/dev/null 2>&1; \
# 	then echo ''; \
# 	else echo "***" 1>&2; \
# 	echo "*** Error: Couldn't find an i386-*-elf version of GCC/binutils." 1>&2; \
# 	echo "*** Is the directory with i386-jos-elf-gcc in your PATH?" 1>&2; \
# 	echo "*** If your i386-*-elf toolchain is installed with a command" 1>&2; \
# 	echo "*** prefix other than 'i386-jos-elf-', set your TOOLPREFIX" 1>&2; \
# 	echo "*** environment variable to that prefix and run 'make' again." 1>&2; \
# 	echo "*** To turn off this error, run 'gmake TOOLPREFIX= ...'." 1>&2; \
# 	echo "***" 1>&2; exit 1; fi)
# endif
```

You also need to remove the `-Werror` in lines 79 and 160 (or search for two places having `-Werror` in the `Makefile` of `xv6` and remove it).

Now, you should be able to run xv6 under qemu on your mac, e.g. `make qemu-nox`. If it works, then your terminal is now "transferred" to xv6's shell such as
```shell
SeaBIOS (version rel-1.16.3-0-ga6ed6b701f0a-prebuilt.qemu.org)

iPXE (http://ipxe.org) 00:03.0 CA00 PCI2.10 PnP PMM+1EFD0FC0+1EF30FC0 CA00
                                                                               
Booting from Hard Disk..xv6...
cpu0: starting 0
sb: size 1000 nblocks 941 ninodes 200 nlog 30 logstart 2 inodestart 32 bmap start 58
init: starting sh
$ 
```

Next, exit xv6 (`Ctrl-A`, then `x`) and install `gdb` by typing `brew install gdb` in your terminal. You may get the following error
```shell
The x86_64 architecture is required for this software.
Error: gdb: An unsatisfied requirement failed this build.
```

This is because my Mac is using ARM. Try to install Homebrew in Rosetta Mode as follows (i.e. Homebrew can run under Rosetta 2 to simulate an x86_64 environment for installing gdb)
```shell
softwareupdate --install-rosetta
arch -x86_64 /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
arch -x86_64 brew install gdb
arch -arm64 brew install
```

After this, you may get the error (I had it)
```shell
Error: Cannot install under Rosetta 2 in ARM default prefix (/opt/homebrew)!
To rerun under ARM use:
    arch -arm64 brew install ...
To install under x86_64, install Homebrew into /usr/local.
```

This error is because my Homebrew is still configured for ARM-based installation. We need to setup Homebrew explicitly for x86_64 by installing it in /usr/local (the default location for x86_64 Homebrew). Try again the following
```shell
arch -x86_64 brew install gdb
arch -x86_64 /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
export PATH="/usr/local/bin:$PATH"
source ~/.zshrc
arch -x86_64 brew install gdb
```
To check if gdb is installed, try `gdb --version`, which should display the version of the installed gdb.

Try to run xv6 in gdb mode.
```shell
make qemu-nox-gdb
```
Open another terminal and change directory to where you was running qemu-nox-gdb, and type `gdb`. You should place these 2 terminals next to each other so that you can see what happens on the original qemu terminal whey you are doing on the gdb terminal.