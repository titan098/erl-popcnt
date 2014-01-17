/* @author: David Ellefsen
 * @doc A native wrapper for GNU __builtin_popcnt or MSVC++ __popcnt.
 * If the platform is invalid, it should fall back to a built in function.
 *
 * Copyright 2014 David Ellefsen
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include "erl_nif.h"

//defines for GCC or Windows, if none can be found use built in function.
#ifdef __GNUC__
	#define POPCNT32(X)	(__builtin_popcount(X))
	#define POPCNT64(X)	(__builtin_popcountl(X))
#elif defined _MSC_VER
	#define POPCNT32(X)	(__popcnt(X))
	#define POPCNT64(X)	(__popcnt64(X))
#else
	#define POPCNT32(X)	(my_popcnt32(X))
	#define POPCNT64(X)	(my_popcnt64(X))
#endif

// See: http://graphics.stanford.edu/~seander/bithacks.html
static const int S[] = {1,2,4,8,16};
static const int B[] = {0x55555555, 0x33333333, 0x0F0F0F0F, 0x00FF00FF, 0x0000FFFF};

unsigned int my_popcnt32(unsigned int v) {
	unsigned int c = 0;
	c = v - ((v >> 1) & B[0]);
	c = ((c >> S[1]) & B[1]) + (c & B[1]);
	c = ((c >> S[2]) + c) & B[2];
	c = ((c >> S[3]) + c) & B[3];
	c = ((c >> S[4]) + c) & B[4];
	return c;
}

unsigned long my_popcnt64(unsigned long v) {
	unsigned int v1 = v & 0xffffffff;
	unsigned int v2 = (v >> 32) & 0xffffffff;

	return (unsigned long)(my_popcnt32(v1) + my_popcnt32(v2));
};

ERL_NIF_TERM util_popcnt32(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
	unsigned int in;
	unsigned int ret;

	//get the input ununsigned integer
	if (!enif_get_uint(env, argv[0], &in)) {
		return enif_make_badarg(env);
	}

	ret = POPCNT32(in);

	return enif_make_uint(env, ret);
}

ERL_NIF_TERM util_popcnt64(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
	unsigned long in;
	unsigned long ret;

	//get the input unsigned long
	if (!enif_get_ulong(env, argv[0], &in)) {
		return enif_make_badarg(env);
	}

	ret = POPCNT64(in);

	return enif_make_ulong(env, ret);
}

static ErlNifFunc nif_funcs[] = {
	{"nif_util_popcnt32",	1, util_popcnt32},
	{"nif_util_popcnt64",	1, util_popcnt64},
};

ERL_NIF_INIT(erl_popcnt, nif_funcs, NULL, NULL, NULL, NULL)

