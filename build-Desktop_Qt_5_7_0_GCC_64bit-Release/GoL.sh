#!/bin/sh

appname=`basename $0 | sed s,\.sh$,,`

dirname=`dirname $0`
tmp="${dirname#?}"

if [ "${dirname%$tmp}" != "/" ]; then
  if [ $dirname != "." ]; then
    dirname=$PWD/$dirname
  else
    dirname=$PWD
  fi
fi

libs=$dirname/lib

echo $dirname
echo $libs

LD_LIBRARY_PATH=$libs
export LD_LIBRARY_PATH

QT_QPA_PLATFORM_PLUGIN_PATH=$libs
export QT_QPA_PLATFORM_PLUGIN_PATH

$dirname/$appname "$@"

