// -----------------------------------------------------------------------------
//
//  Copyright (C) 2012-2018 Fons Adriaensen <fons@linuxaudio.org>
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// -----------------------------------------------------------------------------


#ifndef __MTDM_H
#define __MTDM_H


#include <unistd.h>
#include <emscripten/bind.h>


class Freq
{
public:

    int   p;
    int   f;
    float xa;
    float ya;
    float x1;
    float y1;
    float x2;
    float y2;
};


class MTDM
{
public:

    MTDM (int fsamp);
    int process (size_t len, float *inp, float *out);
    int resolve (void);
    void invert (void) { _inv ^= 1; }
    int    inv (void) const { return _inv; }
    double del (void) const { return _del; }
    double err (void) const { return _err; }

private:

    double  _del;
    double  _err;
    float   _wlp;
    int     _cnt;
    int     _inv;
    Freq    _freq [13];
};

// Binding code
EMSCRIPTEN_BINDINGS(MTDM) {
  emscripten::class_<MTDM>("MTDM")
    .constructor<int>()
    //more difficult .function("process", &MTDM::process)
    .function("resolve", &MTDM::resolve)
    .function("invert", &MTDM::invert)
    .property("inv", &MTDM::inv)
    .property("del", &MTDM::del)
    .property("err", &MTDM::err)
    ;
}

#endif

