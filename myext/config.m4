dnl $Id$
dnl config.m4 for extension myext

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(myext, for myext support,
dnl Make sure that the comment is aligned:
dnl [  --with-myext             Include myext support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(myext, whether to enable myext support,
Make sure that the comment is aligned:
[  --enable-myext           Enable myext support])

if test "$PHP_MYEXT" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-myext -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/myext.h"  # you most likely want to change this
  dnl if test -r $PHP_MYEXT/$SEARCH_FOR; then # path given as parameter
  dnl   MYEXT_DIR=$PHP_MYEXT
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for myext files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       MYEXT_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$MYEXT_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the myext distribution])
  dnl fi

  dnl # --with-myext -> add include path
  dnl PHP_ADD_INCLUDE($MYEXT_DIR/include)

  dnl # --with-myext -> check for lib and symbol presence
  dnl LIBNAME=myext # you may want to change this
  dnl LIBSYMBOL=myext # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $MYEXT_DIR/$PHP_LIBDIR, MYEXT_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_MYEXTLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong myext lib version or lib not found])
  dnl ],[
  dnl   -L$MYEXT_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(MYEXT_SHARED_LIBADD)
  PHP_REQUIRE_CXX()
 PHP_SUBST(MYEXT_SHARED_LIBADD)
PHP_ADD_LIBRARY_WITH_PATH(stdc++, "", MYEXT_SHARED_LIBADD)
PHP_ADD_LIBRARY(stdc++,EXTRA_LDFLAGS)
  PHP_NEW_EXTENSION(myext, myext.cpp, $ext_shared)
fi
