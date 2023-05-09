/* File : verushash.i */
%module verushash
%include <std_string.i>
%include <carrays.i>
%include <cdata.i>
%{
#include "verushash.h"
%}

%insert(cgo_comment_typedefs) %{
#cgo LDFLAGS: -L${SRCDIR}/build/lib -L${SRCDIR}/build -l:libverus_crypto.a -lsodium
#cgo CXXFLAGS: -I${SRCDIR}/build/include
%}


%include "verushash.h"
