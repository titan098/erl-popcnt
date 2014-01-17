-module(erl_util).

-compile([popcnt/1]).

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
	erlang:load_nif(filename:join(PrivDir, "erl_util"), 0).


not_loaded(Line) ->
	erlang:nif_error({not_loaded, [{module, ?MODULE}, {line, Line}]}).

nif_util_popcnt32(_B) ->
	?NOT_LOADED.
nif_util_popcnt64(_B) ->
	?NOT_LOADED.

