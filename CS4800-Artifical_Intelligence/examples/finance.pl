
/* This program implements the predicate calculus
financial advisor in Luger's AI textbook.
To use the program, load it into Prolog and
then enter: advise. */

investment(savings) :- savings_account(inadequate).
investment(stocks) :- savings_account(adequate), income(adequate).
investment(combination) :- savings_account(adequate), income(inadequate).

savings_account(adequate) :- amount_saved(X), dependents(Y), 
   minsavings(Y,Z), X > Z.
savings_account(inadequate) :- amount_saved(X), dependents(Y), 
   minsavings(Y,Z), X =< Z.

income(adequate) :- earnings(X,steady), dependents(Y),
   minincome(Y,Z), X > Z.
income(inadequate) :- earnings(X,steady), dependents(Y),
   minincome(Y,Z), X =< Z.
income(inadequate) :- earnings(X,unsteady).

minsavings(X,Y) :- Y is X * 5000.
minincome(X,Y) :- Y is 15000 + (4000 * X).

advise :- write('Enter the income: '), read(X), nl,
          write('Enter steady or unsteady: '), read(Y), nl,
          assert(earnings(X,Y)), 
          write('Enter the amount saved: '), read(Z), nl,
          assert(amount_saved(Z)), 
          write('Enter the number of dependents: '), read(W), nl,
          assert(dependents(W)), investment(A), 
          write('The recommended investment is '), write(A), nl,
          retract(earnings(X,Y)), retract(amount_saved(Z)),
          retract(dependents(W)).
   

