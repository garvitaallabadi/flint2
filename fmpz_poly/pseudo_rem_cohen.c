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

    Copyright (C) 2010 Sebastian Pancratz

******************************************************************************/

#include <stdlib.h>
#include <mpir.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_vec.h"
#include "fmpz_poly.h"

void
_fmpz_poly_pseudo_rem_cohen(fmpz * R, const fmpz * A, long lenA, 
                            const fmpz * B, long lenB)
{
    const fmpz * leadB = B + (lenB - 1);
    long e;
    fmpz_t pow;

    if (lenB == 1)
    {
        _fmpz_vec_zero(R, lenA);
        return;
    }

    if (R != A)
        _fmpz_vec_copy(R, A, lenA);
    e = lenA - lenB + 1;

    while (lenA >= lenB)
    {
        _fmpz_vec_scalar_mul_fmpz(R, R, lenA - 1, leadB);
        _fmpz_vec_scalar_submul_fmpz(R + (lenA - lenB), B, lenB - 1, R + (lenA - 1));
        fmpz_zero(R + (lenA - 1));

        for (lenA -= 2; (lenA >= 0) && (R[lenA] == 0L); lenA--) ;
        lenA++;

        e--;
    }

    fmpz_init(pow);
    fmpz_pow_ui(pow, leadB, e);
    _fmpz_vec_scalar_mul_fmpz(R, R, lenA, pow);
    fmpz_clear(pow);
}

void
fmpz_poly_pseudo_rem_cohen(fmpz_poly_t R, fmpz_poly_t A, fmpz_poly_t B)
{
    long lenr;
    fmpz *r;
    
    if (B->length == 0)
    {
        printf("Exception: division by zero in fmpz_poly_pseudo_rem_cohen\n");
        abort();
    }
    if (A->length < B->length)
    {
        fmpz_poly_set(R, A);
        return;
    }
    
    lenr = A->length;
    if (R == B)
        r = _fmpz_vec_init(lenr);
    else
    {
        fmpz_poly_fit_length(R, lenr);
        r = R->coeffs;
    }
    
    _fmpz_poly_pseudo_rem_cohen(r, A->coeffs, A->length, B->coeffs, B->length);
    
    for (lenr = B->length - 1; r[lenr] == 0L; lenr--) ;
    lenr++;
    
    if (R == B)
    {
        _fmpz_vec_clear(R->coeffs, R->alloc);
        R->coeffs = r;
        R->alloc = A->length;
        R->length = lenr;
    }
    else
        _fmpz_poly_set_length(R, lenr);
}
