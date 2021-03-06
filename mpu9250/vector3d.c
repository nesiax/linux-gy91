////////////////////////////////////////////////////////////////////////////
//
//  This file is part of linux-mpu9250
//
//  Copyright (c) 2013 Pansenti, LLC
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy of 
//  this software and associated documentation files (the "Software"), to deal in 
//  the Software without restriction, including without limitation the rights to use, 
//  copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the 
//  Software, and to permit persons to whom the Software is furnished to do so, 
//  subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all 
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
//  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
//  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
//  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
//  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
//  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "vector3d.h"

void vector3DotProduct(vector3d_t a, vector3d_t b, float *d)
{
	*d = a[VEC3_X] * b[VEC3_X] + a[VEC3_Y] * b[VEC3_Y] + a[VEC3_Z] * b[VEC3_Z];  
}

void vector3CrossProduct(vector3d_t a, vector3d_t b, vector3d_t d) 
{
	d[VEC3_X] = a[VEC3_Y] * b[VEC3_Z] - a[VEC3_Z] * b[VEC3_Y];
	d[VEC3_Y] = a[VEC3_Z] * b[VEC3_X] - a[VEC3_X] * b[VEC3_Z];
	d[VEC3_Z] = a[VEC3_X] * b[VEC3_Y] - a[VEC3_Y] * b[VEC3_X];
}


/* Local Variables:  */
/* mode: c           */
/* c-basic-offset: 4 */
/* End:              */
