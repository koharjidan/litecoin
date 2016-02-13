Release Process
====================

<<<<<<< HEAD
* * *

=======
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771
###update (commit) version in sources

	contrib/verifysfbinaries/verify.sh
	doc/README*
	share/setup.nsi
	src/clientversion.h (change CLIENT_VERSION_IS_RELEASE to true)

###tag version in git

<<<<<<< HEAD
	git tag -s v0.8.7
=======
	git tag -s v(new version, e.g. 0.8.0)
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771

###write release notes. git shortlog helps a lot, for example:

	git shortlog --no-merges v(current version, e.g. 0.7.2)..v(new version, e.g. 0.8.0)

* * *

###update Gitian

<<<<<<< HEAD
 From a directory containing the litecoin source, gitian-builder and gitian.sigs
  
	export SIGNER=(your gitian key, ie bluematt, sipa, etc)
	export VERSION=0.8.7
	cd ./gitian-builder

 Fetch and build inputs: (first time, or when dependency versions change)

	mkdir -p inputs; cd inputs/
	wget 'http://miniupnp.free.fr/files/download.php?file=miniupnpc-1.9.20140401.tar.gz' -O miniupnpc-1.9.20140401.tar.gz'
	wget 'https://www.openssl.org/source/openssl-1.0.1k.tar.gz'
	wget 'http://download.oracle.com/berkeley-db/db-4.8.30.NC.tar.gz'
	wget 'http://zlib.net/zlib-1.2.8.tar.gz'
	wget 'ftp://ftp.simplesystems.org/pub/libpng/png/src/history/libpng16/libpng-1.6.8.tar.gz'
	wget 'http://fukuchi.org/works/qrencode/qrencode-3.4.3.tar.bz2'
	wget 'http://downloads.sourceforge.net/project/boost/boost/1.55.0/boost_1_55_0.tar.bz2'
	wget 'http://download.qt-project.org/official_releases/qt/4.8/4.8.5/qt-everywhere-opensource-src-4.8.5.tar.gz'
	cd ..
	./bin/gbuild ../litecoin/contrib/gitian-descriptors/boost-win32.yml
	mv build/out/boost-*.zip inputs/
	./bin/gbuild ../litecoin/contrib/gitian-descriptors/deps-win32.yml
	mv build/out/bitcoin*.zip inputs/
	./bin/gbuild ../litecoin/contrib/gitian-descriptors/qt-win32.yml
	mv build/out/qt*.zip inputs/

 Build litecoind and litecoin-qt on Linux32, Linux64, and Win32:
  
	./bin/gbuild --commit litecoin=v${VERSION} ../litecoin/contrib/gitian-descriptors/gitian.yml
	./bin/gsign --signer $SIGNER --release ${VERSION} --destination ../gitian.sigs/ ../litecoin/contrib/gitian-descriptors/gitian.yml
	pushd build/out
	zip -r litecoin-${VERSION}-linux.zip *
	mv litecoin-${VERSION}-linux.zip ../../
	popd
	./bin/gbuild --commit litecoin=v${VERSION} ../litecoin/contrib/gitian-descriptors/gitian-win32.yml
	./bin/gsign --signer $SIGNER --release ${VERSION}-win32 --destination ../gitian.sigs/ ../litecoin/contrib/gitian-descriptors/gitian-win32.yml
	pushd build/out
	zip -r litecoin-${VERSION}-win32.zip *
	mv litecoin-${VERSION}-win32.zip ../../
=======
 In order to take advantage of the new caching features in Gitian, be sure to update to a recent version (e9741525c or higher is recommended)

###perform Gitian builds

 From a directory containing the litecoin source, gitian-builder and gitian.sigs.ltc
  
    export SIGNER=(your Gitian key, ie wtogami, coblee, etc)
	export VERSION=(new version, e.g. 0.8.0)
	pushd ./litecoin
	git checkout v${VERSION}
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771
	popd
	pushd ./gitian-builder

###fetch and build inputs: (first time, or when dependency versions change)

<<<<<<< HEAD
  1. linux 32-bit and 64-bit binaries + source (litecoin-${VERSION}-linux-gitian.zip)
  2. windows 32-bit binary, installer + source (litecoin-${VERSION}-win32-gitian.zip)
  3. Gitian signatures (in gitian.sigs/${VERSION}[-win32]/(your gitian key)/
=======
	mkdir -p inputs
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771

 Register and download the Apple SDK: (see OS X Readme for details)

 https://developer.apple.com/downloads/download.action?path=Developer_Tools/xcode_6.1.1/xcode_6.1.1.dmg

<<<<<<< HEAD
	unzip litecoin-${VERSION}-linux-gitian.zip -d litecoin-${VERSION}-linux
	tar czvf litecoin-${VERSION}-linux.tar.gz litecoin-${VERSION}-linux
	rm -rf litecoin-${VERSION}-linux
=======
 Using a Mac, create a tarball for the 10.9 SDK and copy it to the inputs directory:
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771

	tar -C /Volumes/Xcode/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/ -czf MacOSX10.9.sdk.tar.gz MacOSX10.9.sdk

<<<<<<< HEAD
	unzip litecoin-${VERSION}-win32-gitian.zip -d litecoin-${VERSION}-win32
	mv litecoin-${VERSION}-win32/litecoin-*-setup.exe .
	zip -r litecoin-${VERSION}-win32.zip bitcoin-${VERSION}-win32
	rm -rf litecoin-${VERSION}-win32
=======
###Optional: Seed the Gitian sources cache
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771

  By default, Gitian will fetch source files as needed. For offline builds, they can be fetched ahead of time:

<<<<<<< HEAD
  OSX binaries are created on a dedicated 32-bit, OSX 10.6.8 machine.
  Litecoin 0.8.x is built with MacPorts.  0.9.x will be Homebrew only.

	qmake RELEASE=1 USE_UPNP=1 USE_QRCODE=1
	make
	export QTDIR=/opt/local/share/qt4  # needed to find translations/qt_*.qm files
	T=$(contrib/qt_translations.py $QTDIR/translations src/qt/locale)
	python2.7 share/qt/clean_mac_info_plist.py
	python2.7 contrib/macdeploy/macdeployqtplus Litecoin-Qt.app -add-qt-tr $T -dmg -fancy contrib/macdeploy/fancy.plist

 Build output expected: Litecoin-Qt.dmg
=======
	make -C ../litecoin/depends download SOURCES_PATH=`pwd`/cache/common

  Only missing files will be fetched, so this is safe to re-run for each build.

###Build Litecoin Core for Linux, Windows, and OS X:
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771

	./bin/gbuild --commit litecoin=v${VERSION} ../litecoin/contrib/gitian-descriptors/gitian-linux.yml
	./bin/gsign --signer $SIGNER --release ${VERSION}-linux --destination ../gitian.sigs.ltc/ ../litecoin/contrib/gitian-descriptors/gitian-linux.yml
	mv build/out/litecoin-*.tar.gz build/out/src/litecoin-*.tar.gz ../
	./bin/gbuild --commit litecoin=v${VERSION} ../litecoin/contrib/gitian-descriptors/gitian-win.yml
	./bin/gsign --signer $SIGNER --release ${VERSION}-win --destination ../gitian.sigs.ltc/ ../litecoin/contrib/gitian-descriptors/gitian-win.yml
	mv build/out/litecoin-*.zip build/out/litecoin-*.exe ../
	./bin/gbuild --commit litecoin=v${VERSION} ../litecoin/contrib/gitian-descriptors/gitian-osx.yml
	./bin/gsign --signer $SIGNER --release ${VERSION}-osx-unsigned --destination ../gitian.sigs.ltc/ ../litecoin/contrib/gitian-descriptors/gitian-osx.yml
	mv build/out/litecoin-*-unsigned.tar.gz inputs/litecoin-osx-unsigned.tar.gz
	mv build/out/litecoin-*.tar.gz build/out/litecoin-*.dmg ../
	popd
  Build output expected:

  1. source tarball (litecoin-${VERSION}.tar.gz)
  2. linux 32-bit and 64-bit binaries dist tarballs (litecoin-${VERSION}-linux[32|64].tar.gz)
  3. windows 32-bit and 64-bit installers and dist zips (litecoin-${VERSION}-win[32|64]-setup.exe, litecoin-${VERSION}-win[32|64].zip)
  4. OS X unsigned installer (litecoin-${VERSION}-osx-unsigned.dmg)
  5. Gitian signatures (in gitian.sigs/${VERSION}-<linux|win|osx-unsigned>/(your Gitian key)/

<<<<<<< HEAD
* update litecoin.org version
  make sure all OS download links go to the right versions
=======
###Next steps:

Commit your signature to gitian.sigs:

	pushd gitian.sigs
	git add ${VERSION}-linux/${SIGNER}
	git add ${VERSION}-win/${SIGNER}
	git add ${VERSION}-osx-unsigned/${SIGNER}
	git commit -a
	git push  # Assuming you can push to the gitian.sigs tree
	popd
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771

  Wait for OS X detached signature:
	Once the OS X build has 3 matching signatures, Warren/Coblee will sign it with the apple App-Store key.
	He will then upload a detached signature to be combined with the unsigned app to create a signed binary.

  Create the signed OS X binary:

<<<<<<< HEAD
Commit your signature to gitian.sigs:
=======
	pushd ./gitian-builder
	# Fetch the signature as instructed by Warren/Coblee
	cp signature.tar.gz inputs/
	./bin/gbuild -i ../litecoin/contrib/gitian-descriptors/gitian-osx-signer.yml
	./bin/gsign --signer $SIGNER --release ${VERSION}-osx-signed --destination ../gitian.sigs/ ../litecoin/contrib/gitian-descriptors/gitian-osx-signer.yml
	mv build/out/litecoin-osx-signed.dmg ../litecoin-${VERSION}-osx.dmg
	popd

Commit your signature for the signed OS X binary:
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771

	pushd gitian.sigs
	git add ${VERSION}-osx-signed/${SIGNER}
	git commit -a
	git push  # Assuming you can push to the gitian.sigs tree
	popd

<<<<<<< HEAD
=======
-------------------------------------------------------------------------

### After 3 or more people have gitian-built and their results match:

- Perform code-signing.

    - Code-sign Windows -setup.exe (in a Windows virtual machine using signtool)

  Note: only Warren/Coblee has the code-signing keys currently.

- Create `SHA256SUMS.asc` for the builds, and GPG-sign it:
```bash
sha256sum * > SHA256SUMS
gpg --digest-algo sha256 --clearsign SHA256SUMS # outputs SHA256SUMS.asc
rm SHA256SUMS
```
(the digest algorithm is forced to sha256 to avoid confusion of the `Hash:` header that GPG adds with the SHA256 used for the files)

- Update litecoin.org version

- Announce the release:

  - Release sticky on litecointalk: https://litecointalk.org/index.php?board=1.0

  - litecoin-development mailing list

  - Update title of #litecoin on Freenode IRC

  - Optionally reddit /r/litecoin, ... but this will usually sort out itself

- Add release notes for the new version to the directory `doc/release-notes` in git master

- Celebrate 
>>>>>>> d1691e599121d643db2c1f2b5f5529eb64f2a771
