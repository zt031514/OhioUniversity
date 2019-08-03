/** 
	pets.pl
	
	Author: Zach Tumbleson
	
	Lists pets and the rules for choosing pets. 
	
*/

%Questions for customers

write('Do you spend most of your time indoors or outdoors?'), read(X), nl.
write('You spend most of your time '), write(X), nl.

write('')

%Rules for choosing pets

%A pet is adorable if it is cute and attention seeking
adorable(A) :- pet(A), cute(A), seeking(A)

%A pet is annoying if it looks weird and is attention seeking
annoying(A) :- pet(A), weird(A), seeking(A)

%A pet is 


%facts


%size

small(ferret).
small(rock).
small(potato).
small(rabbit).
small(hamster).
small(fish).
small(frog).
small(fish).
medium(dog).
medium(parrot).
medium(chicken).
medium(chicken).
medium(duck).
large(sheep).
large(horse).


%how much attention the pet wants from owners

seeking(dog).
seeking(parrot).
seeking(sheep).
seeking(horse).
indifferent(ferret).
indifferent(rock).
indifferent(potato).
indifferent(rabbit).
indifferent(hamster).
indifferent(fish).
indifferent(frog).
indifferent(snail).
indifferent(chicken).
indifferent(duck).
indifferent(tree).
avoidant(snake).
avoidant(spider).
avoidant(lizard).
avoidant(mouse).
avoidant(eagle).

%appearance of the pet
cute(dog).
cute(ferret).
cute(cat).
cute(rock).
cute(potato).
cute(rabbit).
cute(hamster).
cute(mouse).
weird(parrot).
weird(fish).
weird(frog).
weird(snail).
weird(chicken).
weird(sheep).
weird(duck).
cool(snake).
cool(spider).
cool(horse).
cool(tree).
cool(lizard).
cool(eagle).

%indoor vs outdoor pets (indoor, outdoor, or hybrid for both)
hybrid(dog).
indoor(ferret).
hybrid(cat).
indoor(parrot).
indoor(snake).
indoor(spider).
hybrid(rock).
hybrid(potato).
indoor(fish).
indoor(frog).
indoor(snail).
outdoor(horse).
hybrid(rabbit).
outdoor(chicken).
outdoor(tree).
hybrid(duck).
indoor(hamster).
indoor(lizard).
outdoor(sheep).
indoor(mouse).
outdoor(eagle).


%list of pets

pet(dog).
pet(ferret).
pet(cat).
pet(parrot).
pet(snake).
pet(spider).
pet(rock).
pet(potato).
pet(fish).
pet(frog).
pet(snail).
pet(horse).
pet(rabbit).
pet(chicken).
pet(tree).
pet(duck).
pet(hamster).
pet(lizard).
pet(sheep).
pet(mouse).
pet(eagle).