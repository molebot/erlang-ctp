{application, 'ctp', [
	{description, "Erlang NIF wrapper for ctp"},
	{vsn, "0.1.0"},
	{modules, ['ctp_md_nif','ctp_td_nif']},
	{registered, []},
	{applications, [kernel,stdlib]},
	{env, []}
]}.