build:
	gcc main.c bib1.c bib2.c bib3.c bib4.c bib5.c -o lanParty
run:
	./lanParty c.in d.in r.out
clean:
	rm -f lanParty