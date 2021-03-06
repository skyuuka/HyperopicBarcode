//	(c) Copyright 2008-2009 Johann C. Rocholl
//	Portions (c) Copyright 2012 Conor Dearden & Michael LaMorte
//
//  Redistribution and use in source and binary forms, with or without modification, 
//  are permitted provided that the following conditions are met:
//
//      * Redistributions of source code must retain the above copyright notice, 
//  	  this list of conditions and the following disclaimer.
//      * Redistributions in binary form must reproduce the above copyright notice, 
//  	  this list of conditions and the following disclaimer in the documentation 
//  	  and/or other materials provided with the distribution.
//      * The name of the copyright holders may not be used to endorse or promote products
//        derived from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
//  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
//  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  
//  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,  
//  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT  
//  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR  
//  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,  
//  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)  
//  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE  
//  POSSIBILITY OF SUCH DAMAGE.
//

#include "minmax.h"


int compare_int(const void *a_ptr, const void *b_ptr)
{
	int a = *(int *) a_ptr;
	int b = *(int *) b_ptr;
	return a - b;
}


int compare_unsigned_char(const void *a_ptr, const void *b_ptr)
{
	int a = *(unsigned char *) a_ptr;
	int b = *(unsigned char *) b_ptr;
	return a - b;
}


int compare_float(const void *a_ptr, const void *b_ptr)
{
	float a = *(float *) a_ptr;
	float b = *(float *) b_ptr;
	if (a > b)
		return 1;
	if (b > a)
		return -1;
	return 0;
}
