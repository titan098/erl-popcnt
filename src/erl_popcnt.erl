%% @author: David Ellefsen
%% @doc A wrapper for a native population count function (popcnt).
%% 	The number of set bits in an integer will be returned.
%%	32 and 64-bit unsigned integers are supported. It should be
%%	supported on any machine that supports GCC/Clang
%%
%%   Copyright 2014 David Ellefsen
%%
%%   Licensed under the Apache License, Version 2.0 (the "License");
%%   you may not use this file except in compliance with the License.
%%   You may obtain a copy of the License at
%%
%%       http://www.apache.org/licenses/LICENSE-2.0
%%
%%   Unless required by applicable law or agreed to in writing, software
%%   distributed under the License is distributed on an "AS IS" BASIS,
%%   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
%%   See the License for the specific language governing permissions and
%%   limitations under the License.
%%
-module(erl_popcnt).

-export([popcnt/1]).

-define(NOT_LOADED, not_loaded(?LINE)).

-on_load(init/0).

popcnt(X) when X < 0 ->
	{error, use_unsigned_values};
popcnt(X) when X =< 16#ffffffff ->
	nif_util_popcnt32(X);
popcnt(X) when X =< 16#ffffffffffffffff ->
	nif_util_popcnt64(X);
popcnt(_X) ->
	{error, arg_to_large}.

init() ->
	PrivDir = case code:priv_dir(?MODULE) of
		{error, _} ->
			EbinDir = filename:dirname(code:which(?MODULE)),
			AppPath = filename:dirname(EbinDir),
			filename:join(AppPath, "priv");
		Path ->
			Path
	end,
	erlang:load_nif(filename:join(PrivDir, "erl_popcnt"), 0).


not_loaded(Line) ->
	erlang:nif_error({not_loaded, [{module, ?MODULE}, {line, Line}]}).

nif_util_popcnt32(_B) ->
	?NOT_LOADED.
nif_util_popcnt64(_B) ->
	?NOT_LOADED.

