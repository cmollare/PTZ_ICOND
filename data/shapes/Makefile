all:
	for i in *.fig ; do ./fig2contour $$i `basename $$i .fig`.dat ; echo $$i; done

clean:
	rm *.dat
