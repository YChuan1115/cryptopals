# Cryptopals

<a href="https://travis-ci.org/tanzislam/cryptopals">
  <img alt="Build Status"
       src="https://travis-ci.org/tanzislam/cryptopals.svg?branch=master"/>
</a> <a href="https://scan.coverity.com/projects/tanzislam-cryptopals">
  <img alt="Coverity Scan Build Status"
       src="https://scan.coverity.com/projects/10143/badge.svg"/>
</a> <a href="https://www.codacy.com/app/tanzislam/cryptopals">
  <img alt="Codacy"
       src=
   "https://api.codacy.com/project/badge/Grade/0eefb6418259474191b5611351e02dee"
  />
</a> <a href="https://sonarcloud.io/dashboard?id=tanzislam_cryptopals">
  <img alt="SonarCloud"
       src="https://sonarcloud.io/api/project_badges/measure?project=tanzislam_cryptopals&metric=alert_status"/>
</a> <a href="https://www.codefactor.io/repository/github/tanzislam/cryptopals">
  <img alt="CodeFactor"
       src=
   "https://www.codefactor.io/repository/github/tanzislam/cryptopals/badge"/>
</a> <a href="https://www.kiuwan.com/github/tanzislam/cryptopals">
  <img alt="Kiuwan"
       src=
   "https://www.kiuwan.com/github/tanzislam/cryptopals/badges/security.svg"/>
</a> <a href="https://lgtm.com/projects/g/tanzislam/cryptopals">
  <img alt="lgtm"
       src="https://img.shields.io/lgtm/alerts/g/tanzislam/cryptopals.svg?logo=lgtm&logoWidth=18"/>
</a> <a
  href="https://www.code-inspector.com/public/project/78/cryptopals/dashboard">
  <img alt="Code Grade"
       src="https://www.code-inspector.com/project/78/status/svg"/>
</a>

These are my solutions to the interesting challenges at [the cryptopals crypto
challenges](https://cryptopals.com). All solutions are coded in C++11 and Boost.

## Requirements

To build these solutions you will need:
 - [GNU Compiler Collection (GCC)](https://gcc.gnu.org/). I used v8.2.0 in
   [MSYS2](https://www.msys2.org/) on Windows 7. On macOS Sierra I used the
   default [Clang](http://clang.llvm.org/) v8.0.0 (build `clang-800.0.42.1`)
   which is compatible with GCC. On macOS Tiger (on a PowerPC G3 iBook) I used
   GCC v7.4.0 (invoked as `g++-mp-7`) from [MacPorts](https://www.macports.org).

 - [GNU Make](https://www.gnu.org/software/make/). I used v4.2.1 in MinGW-w64 in
   Windows 7 (invoked as `mingw32-make`). On macOS Sierra and Tiger I installed
   v4.2.1 (invoked as `gmake` to distinguish from the system default v3.8.1)
   using [Homebrew](https://brew.sh) and MacPorts, respectively. On Ubuntu I had
   to upgrade to Cosmic (18.10) to get v4.2.1.

 - [Git](https://git-scm.com/). On Windows 7 and 10 I used the Git for Windows
   download. On macOS Sierra and Tiger I installed the latest version using
   Homebrew and MacPorts, respectively.

 - [Boost C++ Libraries](http://www.boost.org/). I used the "master" branch from
   [modular Boost](https://github.com/boostorg/boost/).
   - You will need to build the libraries as described for your platform in the
     [Getting Started guide](
     https://github.com/boostorg/boost/wiki/Getting-Started%3A-Overview). Only
     specific libraries are needed (as indicated by the `BOOST_LIBS` line in
     each solution's `GNUmakefile`), so you can speed up the build by appending
     the `--with-<library_name>` option below.
   - On Windows:
     `b2 --layout=system toolset=gcc variant=release address-model=64`.
   - On macOS and Linux: `./b2 --layout=system variant=release`.

 - [Google Test](https://github.com/google/googletest/).
   - You will need to build Google Test as described in the Generic Build
     Instructions. To do this on Windows you will need a UNIX-like set of
     utilities (see below).
   - On Windows / MinGW-w64 I had to specify a Makefile override:
     `cd googletest/make; mingw32-make AR=gcc-ar RANLIB=gcc-ranlib`.

 - [Hunspell](https://hunspell.github.io/).
   - On Windows 7 / MinGW-w64 I had to first install the `autoconf`, `automake`
     and `mingw-w64-x86_64-libtool` packages in the MSYS2 shell, and then I
     could build it with the following commands in a MinGW 64-bit Shell:

         autoreconf -vfi
         ./configure --disable-dependency-tracking
         mingw32-make

   - On macOS Sierra / Homebrew I had to first obtain the GNU Autotools
     packages: `automake`, `libtool`, and `gettext`. I also had to export the
     `LDFLAGS` and `CPPFLAGS` environment variables to what `brew` specified
     when installing `gettext`. After that I could run the standard steps.
   - On macOS Tiger / MacPorts I only had to install the `automake` and
     `libtool` packages, and they pulled in the other ones as dependencies.
   - You will also need an English dictionary for Hunspell -- specifically the
     `.dic` and `.aff` files. Get one from [SCOWL](http://wordlist.aspell.net/).

 - [Crypto++](http://www.cryptopp.com/).
   - You will need to build Crypto++ as a static library using the included
     `GNUmakefile`. To do this on Windows you will need a UNIX-like shell and
     set of utilities (see below).
   - On Windows / MinGW-w64 I had to specify a Makefile override:
     `mingw32-make AR=gcc-ar RANLIB=gcc-ranlib`.

UNIX-like utilities on Windows are provided by any of the following:
 - [MSYS2](http://msys2.github.io/), or originally [MSYS](http://www.mingw.org/)
 - [Cygwin](https://www.cygwin.com/)
 - Interix / [Windows Services for Unix](
   https://technet.microsoft.com/en-gb/library/bb463212.aspx) / [Subsystem for
   Unix-based Applications (SUA)](
   https://msdn.microsoft.com/en-us/library/cc772343(v=ws.11).aspx) --
   available as an optional Windows feature up to Windows 8 / Server 2012
 - [Windows Services for Linux (WSL)](
   https://msdn.microsoft.com/commandline/wsl/) -- available as an optional
   Windows feature on Windows 10 (Anniversary Update onwards)
 - [GnuWin](http://gnuwin32.sourceforge.net/), [UnxUtils](
   http://unxutils.sourceforge.net/) or [win-bash](
   http://win-bash.sourceforge.net/)

You may need to install additional packages beyond the ones bundled with the
default installation. Check the respective documentation for guidance on how to
locate and install packages.

Once the packages are installed, the "from source" dependency libraries can be
downloaded and built using the `prepare_deps` script, especially in CI jobs. You
will need [GNU Bash](https://www.gnu.org/software/bash/) (at least v3.1),
[Wget](https://www.gnu.org/software/wget/) and `unzip` for it. (When installing
Wget in MacPorts I ran into [this issue](https://trac.macports.org/ticket/47085)
but the suggested fix worked fine -- so run `sudo port -v configure libffi`,
then patch the files, then run `sudo port build libffi && sudo make install`.)

Although my development environment is in Windows (primarily [Notepad++](
https://notepad-plus-plus.org/) enhanced with some humble [NppExec](
https://sourceforge.net/projects/npp-plugins/files/NppExec/) scripts), I tried
to make no assumptions about the environment and instead stuck by whatever is
guaranteed by the language standard and library documentation. The solutions
should build in a UNIX environment just fine. Check out the [Wiki](
https://github.com/tanzislam/cryptopals/wiki) for guides to using additional
development tools.

## Building

The solutions are organized in two directory levels: the first level for the Set
and the second level for the Challenge (as in the Cryptopals website). Each
inner directory has a `GNUmakefile` that expects these variables:
 - `BOOST_DIR` -- the top-level directory of your Boost installation
 - `GTEST_DIR` -- the top-level directory of your Google Test installation
 - `HUNSPELL_DIR` -- the top-level directory of your Hunspell repository clone
 - `CRYPTOPP_DIR` -- the top-level directory of your Crypto++ repository clone

To build any solution, ensure that the above are set in the environment, then
`cd` to that directory and run `make` (or `gmake`, `mingw32-make`, etc.). This
will produce the executable, along with other intermediary build products. The
executable name will begin with `test_`, so should be easy to locate.

Alternatively, you can use the top-level `GNUmakefile` by running `make` (or its
equivalent for your platform) in the repository root directory. This will
produce the combined test program called `test`.

**NOTES:**
 - None of the above variables may have spaces in them. So, on Windows you can't
   use `C:\Program Files\...`, but `C:\Users\UsernameWithoutSpace\Documents\etc`
   is good. You can work around this restriction by creating directory symlinks.
 - The above variables do not have to be **environment variables**, but can
   instead be specified in the GNU Make command line as [overrides](
   https://www.gnu.org/software/make/manual/make.html#Overriding).
 - The above variables may be either relative paths or absolute paths.
 - By default the makefiles will compile the code with maximum optimizations and
   no debugging information. To put the code under a debugger, you need to do a
   debug build instead by overriding `"CPP_OPTIMIZATIONS=-g -Og"` on the command
   line.

You can even do an out-of-source build. `cd` into an unrelated directory (it can
be outside the repo or an uncommitted subdirectory inside the repo) and then run
`make -f path/to/GNUmakefile`. The build system will adjust VPATH by itself, so
you do not need to specify it yourself. (The `clean` target may leak some files
in this case, but you can `rm -rf` the entire build directory yourself anyway.)

Some solutions will require the location of a Hunspell dictionary to be provided
in the `HUNSPELL_AFFIX_PATH` and `HUNSPELL_DICT_PATH` environment variables.

## Deciphering the Code

The main translation unit of each solution is full of test cases written with
the Google Test framework. The `main()` inside Google Test is used, so you will
not find a `main()` function in here.

Unlike most solutions, these solutions aim to be scalable to very large inputs
with constant memory requirements. They are therefore designed to work with C++
IOStreams for input and output, instead of in-memory `std::string` objects. They
never read in _all_ the contents of the input streams into memory, but do read
in small chunks at a time for code-conversion, frequency analysis, etc. They
also work on the assumption that the input and output streams are slow devices,
and therefore try to minimize the number of times they are read or written to
(ideally only one pass).

The test drivers (i.e. the source files with names beginning with `test_`) are
_not_ considered part of the solutions, so you will find them constructing
in-memory streams containing the input and output data.

Because of the above design constraints, these solutions have become somewhat of
an adventure in IOStreams programming, using some of its more advanced details
and techniques:
 - custom manipulators with arguments
 - checking and setting `std::ios_base::io_state` flags
 - custom stream buffers as input/output filters

### Why not Boost.Iostreams?

I could have started out with the [Boost.Iostreams](
http://www.boost.org/doc/libs/release/libs/iostreams/) framework for all this,
instead of trying to make ends meet with the Standard IOStreams library. While
the Boost framework is impressively designed for ease of use, my intention here
was to primarily explore the C++ Standard Library thoroughly and identify its
shortcomings, followed by a gradual feature-comparison with the Boost libraries.
