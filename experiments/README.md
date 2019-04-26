# Experimental Macros

These may, one day, migrate to Hedley.  Or not.  For now they live
here, partly in hope that someone will find them to be a useful, and
partly to make sure I don't lose the progress.

If you do find them useful, please let me know… if nothing else, I'm
more likely to move them over to Hedley if lots of people find them
useful.

The implementations are a bit strange in that I use `elif ... || 1`
instead of else.  This is so I can keep track of what compilers I've
tested or checked the documentation for but don't, AFAICT, support the
feature.  If you have access to a compiler not already included please
add it and send a PR.
