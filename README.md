<<<<<<< HEAD
Litecoin integration/staging tree
================================

http://www.litecoin.org

Copyright (c) 2009-2014 Bitcoin Developers
Copyright (c) 2011-2014 Litecoin Developers

What is Litecoin?
----------------

Litecoin is a lite version of Bitcoin using scrypt as a proof-of-work algorithm.
 - 2.5 minute block targets
 - subsidy halves in 840k blocks (~4 years)
 - ~84 million total coins

The rest is the same as Bitcoin.
 - 50 coins per block
 - 2016 blocks to retarget difficulty

For more information, as well as an immediately useable, binary version of
the Litecoin client sofware, see http://www.litecoin.org.
=======
Litecoin Core integration/staging tree
=====================================

https://litecoin.org

What is Litecoin?
----------------

Litecoin is an experimental new digital currency that enables instant payments to
anyone, anywhere in the world. Litecoin uses peer-to-peer technology to operate
with no central authority: managing transactions and issuing money are carried
out collectively by the network. Litecoin Core is the name of open source
software which enables the use of this currency.

For more information, as well as an immediately useable, binary version of
the Litecoin Core software, see https://litecoin.org
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771

License
-------

<<<<<<< HEAD
Litecoin is released under the terms of the MIT license. See `COPYING` for more
=======
Litecoin Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771
information or see http://opensource.org/licenses/MIT.

Development process
-------------------

Developers work in their own trees, then submit pull requests when they think
their feature or bug fix is ready.

If it is a simple/trivial/non-controversial change, then one of the Litecoin
development team members simply pulls it.

If it is a *more complicated or potentially controversial* change, then the patch
<<<<<<< HEAD
submitter will be asked to start a discussion with the devs and community.
=======
submitter will be asked to start a discussion (if they haven't already) on the
[mailing list](https://groups.google.com/forum/#!forum/litecoin-dev).
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771

The patch will be accepted if there is broad consensus that it is a good thing.
Developers should expect to rework and resubmit patches if the code doesn't
match the project's coding conventions (see [doc/coding.md](doc/coding.md)) or are
controversial.

<<<<<<< HEAD
The `master` branch is regularly built and tested, but is not guaranteed to be
=======
The `master-0.10` branch is regularly built and tested, but is not guaranteed to be
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771
completely stable. [Tags](https://github.com/litecoin-project/litecoin/tags) are created
regularly to indicate new official, stable release versions of Litecoin.

Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test on short notice. Please be patient and help out by testing
other people's pull requests, and remember this is a security-critical project where any mistake might cost people
lots of money.

### Manual Quality Assurance (QA) Testing

Large changes should have a test plan, and should be tested by somebody other
than the developer who wrote the code.
Creating a thread in the [Litecoin discussion forum](https://litecointalk.org/index.php?board=2.0) will allow the Litecoin
development team members to review your proposal and to provide assistance with creating a test plan. 


Translations
------------

**Important**: We do not accept translation changes as GitHub pull requests because the next
pull from Transifex would automatically overwrite them again.

We only accept translation fixes that are submitted through [Bitcoin Core's Transifex page](https://www.transifex.com/projects/p/bitcoin/).
Translations are converted to Litecoin periodically.

<<<<<<< HEAD
    qmake BITCOIN_QT_TEST=1 -o Makefile.test bitcoin-qt.pro
    make -f Makefile.test
    ./litecoin-qt_test

=======
Development tips and tricks
---------------------------

**compiling for debugging**

Run configure with the --enable-debug option, then make. Or run configure with
CXXFLAGS="-g -ggdb -O0" or whatever debug flags you need.

**debug.log**

If the code is behaving strangely, take a look in the debug.log file in the data directory;
error and debugging messages are written there.

The -debug=... command-line option controls debugging; running with just -debug will turn
on all categories (and give you a very large debug.log file).

The Qt code routes qDebug() output to debug.log under category "qt": run with -debug=qt
to see it.

**testnet and regtest modes**

Run with the -testnet option to run with "play litecoins" on the test network, if you
are testing multi-machine code that needs to operate across the internet.

If you are testing something that can run on one machine, run with the -regtest option.
In regression test mode, blocks can be created on-demand; see qa/rpc-tests/ for tests
that run in -regtest mode.

**DEBUG_LOCKORDER**

Litecoin Core is a multithreaded application, and deadlocks or other multithreading bugs
can be very difficult to track down. Compiling with -DDEBUG_LOCKORDER (configure
CXXFLAGS="-DDEBUG_LOCKORDER -g") inserts run-time checks to keep track of which locks
are held, and adds warnings to the debug.log file if inconsistencies are detected.
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771
