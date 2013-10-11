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

#include <stdio.h>
#include "ulong_extras.h"

int
main(void)
{
    slong m, n, rep;
    flint_rand_t state;

    printf("add/sub/neg....");
    fflush(stdout);

    flint_randinit(state);

    for (rep = 0; rep < 500; rep++)
    {
        TEMPLATE(T, ctx_t) ctx;

        TEMPLATE(T, mat_t) A;
        TEMPLATE(T, mat_t) B;
        TEMPLATE(T, mat_t) C;

        TEMPLATE(T, ctx_randtest)(ctx, state);

        m = n_randint(state, 20);
        n = n_randint(state, 20);

        TEMPLATE(T, mat_init)(A, m, n, ctx);
        TEMPLATE(T, mat_init)(B, m, n, ctx);
        TEMPLATE(T, mat_init)(C, m, n, ctx);

        TEMPLATE(T, mat_randtest)(A, state, ctx);
        TEMPLATE(T, mat_randtest)(B, state, ctx);

        TEMPLATE(T, mat_neg)(C, A, ctx);
        TEMPLATE(T, mat_add)(A, A, B, ctx);
        TEMPLATE(T, mat_sub)(A, A, B, ctx);
        TEMPLATE(T, mat_neg)(A, A, ctx);

        if (!TEMPLATE(T, mat_equal)(A, C))
        {
            printf("FAIL: matrices not equal!\n");
            abort();
        }

        TEMPLATE(T, mat_clear)(A);
        TEMPLATE(T, mat_clear)(B);
        TEMPLATE(T, mat_clear)(C);

        TEMPLATE(T, ctx_clear)(ctx);
    }

    flint_randclear(state);
    flint_cleanup();
    printf("PASS\n");
    return 0;
}


#endif
