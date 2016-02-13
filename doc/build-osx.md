<<<<<<< HEAD
Mac OS X litecoind build instructions
=======
Mac OS X Build Instructions and Notes
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771
====================================
This guide will show you how to build litecoind(headless client) for OS X.

Notes
-----

<<<<<<< HEAD
See `doc/readme-qt.rst` for instructions on building Litecoin-Qt, the
graphical user interface.

Tested on OS X 10.5 through 10.8 on Intel processors only. PPC is not
supported because it is big-endian.
=======
* Tested on OS X 10.7 through 10.10 on 64-bit Intel processors only.
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771

* All of the commands should be executed in a Terminal application. The
built-in one is located in `/Applications/Utilities`.

Preparation
-----------

You need to install Xcode with all the options checked so that the compiler
and everything is available in /usr not just /Developer. Xcode should be
available on your OS X installation media, but if not, you can get the
current version from https://developer.apple.com/xcode/. If you install
Xcode 4.3 or later, you'll need to install its command line tools. This can
be done in `Xcode > Preferences > Downloads > Components` and generally must
be re-done or updated every time Xcode is updated.

There's also an assumption that you already have `git` installed. If
not, it's the path of least resistance to install [Github for Mac](https://mac.github.com/)
(OS X 10.7+) or
[Git for OS X](https://code.google.com/p/git-osx-installer/). It is also
available via Homebrew.

You will also need to install [Homebrew](http://brew.sh) in order to install library
dependencies.

The installation of the actual dependencies is covered in the Instructions
sections below.

<<<<<<< HEAD
Instructions: MacPorts
----------------------

### Install dependencies

Installing the dependencies using MacPorts is very straightforward.

    sudo port install boost db48@+no_java openssl miniupnpc

### Building `litecoind`

1. Clone the github tree to get the source code and go into the directory.

        git clone git@github.com:litecoin-project/litecoin.git litecoin
        cd litecoin

2.  Build litecoind:

        cd src
        make -f makefile.osx

3.  It is a good idea to build and run the unit tests, too:

        make -f makefile.osx test

Instructions: HomeBrew
=======
Instructions: Homebrew
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771
----------------------

#### Install dependencies using Homebrew

        brew install autoconf automake libtool boost miniupnpc openssl pkg-config protobuf qt

#### Installing berkeley-db4 using Homebrew

The homebrew package for berkeley-db4 has been broken for some time.  It will install without Java though.

Running this command takes you into brew's interactive mode, which allows you to configure, make, and install by hand:
```
$ brew install https://raw.github.com/mxcl/homebrew/master/Library/Formula/berkeley-db4.rb -–without-java 
```

The rest of these commands are run inside brew interactive mode:
```
/private/tmp/berkeley-db4-UGpd0O/db-4.8.30 $ cd ..
/private/tmp/berkeley-db4-UGpd0O $ db-4.8.30/dist/configure --prefix=/usr/local/Cellar/berkeley-db4/4.8.30 --mandir=/usr/local/Cellar/berkeley-db4/4.8.30/share/man --enable-cxx
/private/tmp/berkeley-db4-UGpd0O $ make
/private/tmp/berkeley-db4-UGpd0O $ make install
/private/tmp/berkeley-db4-UGpd0O $ exit
```

After exiting, you'll get a warning that the install is keg-only, which means it wasn't symlinked to `/usr/local`.  You don't need it to link it to build litecoin, but if you want to, here's how:

    $ brew link --force berkeley-db4

<<<<<<< HEAD
### Building `litecoind`
=======
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771

### Building `litecoind`

<<<<<<< HEAD
        git clone https://github.com/litecoin-project/litecoin.git
        cd litecoin
=======
1. Clone the GitHub tree to get the source code and go into the directory.
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771

        git clone https://github.com/litecoin-project/litecoin.git
        cd litecoin

2.  Build litecoind:

        ./autogen.sh
        ./configure
        make

<<<<<<< HEAD
3.  Build litecoind:
=======
3.  It is also a good idea to build and run the unit tests:
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771

        make check

4.  (Optional) You can also install litecoind to your path:

        make install

Use Qt Creator as IDE
------------------------
You can use Qt Creator as IDE, for debugging and for manipulating forms, etc.
Download Qt Creator from http://www.qt.io/download/. Download the "community edition" and only install Qt Creator (uncheck the rest during the installation process).

1. Make sure you installed everything through Homebrew mentioned above
2. Do a proper ./configure --with-gui=qt5 --enable-debug
3. In Qt Creator do "New Project" -> Import Project -> Import Existing Project
4. Enter "litecoin-qt" as project name, enter src/qt as location
5. Leave the file selection as it is
6. Confirm the "summary page"
7. In the "Projects" tab select "Manage Kits..."
8. Select the default "Desktop" kit and select "Clang (x86 64bit in /usr/bin)" as compiler
9. Select LLDB as debugger (you might need to set the path to your installtion)
10. Start debugging with Qt Creator

Creating a release build
------------------------
You can ignore this section if you are building `litecoind` for your own use.

<<<<<<< HEAD
A litecoind binary is not included in the Litecoin-Qt.app bundle. You can ignore
this section if you are building `litecoind` for your own use.

If you are building `litecond` for others, your build machine should be set up
=======
litecoind/litecoin-cli binaries are not included in the Litecoin-Qt.app bundle.

If you are building `litecoind` or `Litecoin-Qt` for others, your build machine should be set up
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771
as follows for maximum compatibility:

All dependencies should be compiled with these flags:

 -mmacosx-version-min=10.7
 -arch x86_64
 -isysroot $(xcode-select --print-path)/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.7.sdk

<<<<<<< HEAD
For MacPorts, that means editing your macports.conf and setting
`macosx_deployment_target` and `build_arch`:

    macosx_deployment_target=10.5
    build_arch=i386

... and then uninstalling and re-installing, or simply rebuilding, all ports.

As of December 2012, the `boost` port does not obey `macosx_deployment_target`.
Download `http://gavinandresen-bitcoin.s3.amazonaws.com/boost_macports_fix.zip`
for a fix. Some ports also seem to obey either `build_arch` or
`macosx_deployment_target`, but not both at the same time. For example, building
on an OS X 10.6 64-bit machine fails. Official release builds of Litecoin-Qt are
compiled on an OS X 10.6 32-bit machine to workaround that problem.

Once dependencies are compiled, creating `Litecoin-Qt.app` is easy:

    make -f Makefile.osx RELEASE=1
=======
Once dependencies are compiled, see release-process.md for how the Litecoin-Qt.app
bundle is packaged and signed to create the .dmg disk image that is distributed.
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771

Running
-------

It's now available at `./litecoind`, provided that you are still in the `src`
directory. We have to first create the RPC configuration file, though.

Run `./litecoind` to get the filename where it should be put, or just try these
commands:

    echo -e "rpcuser=litecoinrpc\nrpcpassword=$(xxd -l 16 -p /dev/urandom)" > "/Users/${USER}/Library/Application Support/Litecoin/litecoin.conf"
    chmod 600 "/Users/${USER}/Library/Application Support/Litecoin/litecoin.conf"
<<<<<<< HEAD
=======

The next time you run it, it will start downloading the blockchain, but it won't
output anything while it's doing this. This process may take several hours;
you can monitor its process by looking at the debug.log file, like this:
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771

    tail -f $HOME/Library/Application\ Support/Litecoin/debug.log

Other commands:
-------

<<<<<<< HEAD
    ./litecoind --help  # for a list of command-line options.
    ./litecoind -daemon # to start the litecoin daemon.
    ./litecoind help    # When the daemon is running, to get a list of RPC commands
=======
    ./litecoind -daemon # to start the litecoin daemon.
    ./litecoin-cli --help  # for a list of command-line options.
    ./litecoin-cli help    # When the daemon is running, to get a list of RPC commands
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771
