/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2013 Mike Hansen

******************************************************************************/


#ifdef T

#include "templates.h"

void
TEMPLATE(T, mat_solve_tril_recursive)(TEMPLATE(T, mat_t) X,
                                      const TEMPLATE(T, mat_t) L,
                                      const TEMPLATE(T, mat_t) B,
                                      int unit,
                                      const TEMPLATE(T, ctx_t) ctx)
{
    TEMPLATE(T, mat_t) LA, LC, LD, XX, XY, BX, BY;
    slong r, n, m;

    n = L->r;
    m = B->c;
    r = n / 2;

    if (n == 0 || m == 0)
        return;

    /*
    Denoting inv(M) by M^, we have:

    [A 0]^ [X]  ==  [A^          0 ] [X]  ==  [A^ X]
    [C D]  [Y]  ==  [-D^ C A^    D^] [Y]  ==  [D^ (Y - C A^ X)]
    */

    TEMPLATE(T, mat_window_init)(LA, L, 0, 0, r, r);
    TEMPLATE(T, mat_window_init)(LC, L, r, 0, n, r);
    TEMPLATE(T, mat_window_init)(LD, L, r, r, n, n);
    TEMPLATE(T, mat_window_init)(BX, B, 0, 0, r, m);
    TEMPLATE(T, mat_window_init)(BY, B, r, 0, n, m);
    TEMPLATE(T, mat_window_init)(XX, X, 0, 0, r, m);
    TEMPLATE(T, mat_window_init)(XY, X, r, 0, n, m);

    TEMPLATE(T, mat_solve_tril)(XX, LA, BX, unit, ctx);
    TEMPLATE(T, mat_submul)(XY, BY, LC, XX, ctx);
    TEMPLATE(T, mat_solve_tril)(XY, LD, XY, unit, ctx);

    TEMPLATE(T, mat_window_clear)(LA);
    TEMPLATE(T, mat_window_clear)(LC);
    TEMPLATE(T, mat_window_clear)(LD);
    TEMPLATE(T, mat_window_clear)(BX);
    TEMPLATE(T, mat_window_clear)(BY);
    TEMPLATE(T, mat_window_clear)(XX);
    TEMPLATE(T, mat_window_clear)(XY);
}


#endif
