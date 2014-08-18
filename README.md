Call tracing using gcc's in-built function profiling tools
============================================================

<i>Language:</i> C++
<i>Usage:</i>
<pre>
	make; ./main
</pre>
<i>Interesting Features:</i> 
<ul>
	<li> Uses "__cyg_profile_func_enter" and "__cyg_profile_func_exit" to trace calls </li>
	<li> Surrounds call-tracing code within "extern C" since we're using native C functions and 
		don't want to mangle their names </li>
<ul>