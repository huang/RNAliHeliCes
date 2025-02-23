#/bin/sh
# this is a wrapper for help2man
# it enables it to obtain help, detailed-help and version information
# directly from a given .ggo file.
#
# the first argument passed to this script must be the .ggo file which
# should be parsed, while the second argument may be one of the following
# options


case $2 in
  --help)           gengetopt --show-help --set-version=2.1.1.1 < $1;;
  --version)        echo 2.1.1.1;;
  --detailed-help)  gengetopt --show-detailed-help --set-version=2.1.1.1 < $1;;
esac
