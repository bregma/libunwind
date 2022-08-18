Running The Testsuite
=====================

From the Build Directory
------------------------

The testsuite should be runnable from the build directory without modification
using the `make check` target.

The test suite should also run correctly without problems from the `make dist` target.

The testsuite can also be run standalone from the build directory:
`tests/testsuite --help` for more information.

From a Staging Directory
------------------------

If you have installed a build into a staging directory using, for example, `make
install DEST=/tmp/delete-me`, the test suite is runnable using the following
command.
```
$ /tmp/delete-me/usr/libexec/libunwind/testsuite -C /tmp/delete-me/usr/libexec/libunwind --libdir=/tmp/delete-me/usr/lib AUTOTEST_PATH=/tmp/delete-me/usr/libexec/libunwind LD_LIBRARY_PATH=/tmp/delete-me/usr/lib
```

The AUTOTEST_PATH needs to be set to tell the testsuite where to pick up the
scripts and binaries. The LD_LIBRARY_PATH needs to be set so the binaries can
find their libraries, and the --libdir is needed for the ABI check to be able to
find where the libraries are installed. The -C argument is because the testsuite
tool always looks in the current working directory to find its `atlocal` and
`atconfig` (configuration) files.
