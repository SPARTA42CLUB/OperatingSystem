all:
	make mtm
	make otm
	make oto

mtm:
	gcc manyToMany.c -o mtm

otm:
	gcc manyToOne.c -o mto

oto:
	gcc oneToOne.c -o oto

fclean:
	rm -f mtm mto oto
