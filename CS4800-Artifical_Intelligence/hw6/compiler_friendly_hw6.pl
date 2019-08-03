/** 
	compiler_friendly_hw6.pl
	
	Author: Zach Tumbleson
	
	Contains the same family statements
	as human_friendly_hw6.pl, but has been
	rearranged to remove compiler warnings
	
*/

%defined predicates


%grandmother - #2
grandmother(A,B) :- mother(A,C), mother(C,B), female(A).
grandmother(A,B) :- mother(A,C), father(C,B), female(A).

%sister - #3
sister(A,B) :- female(A), mother(X,A), mother(X,B), father(Y,A), father(Y,B).

%family facts

%immediate family
male(zach).
male(steven).
male(titus).
male(greg).
male(kendall).
male(robert).
male(matthew).
male(ronald).
male(aaron).
male(john).
male(andrew).
male(darron).
male(devon).

female(rachel).
female(andrea).
female(shelby).
female(susan).
female(amanda).
female(judy).
female(alisa).
female(lisa).
female(krisi).
female(sarah).
female(darcy).

father(greg, zach).
father(greg, titus).
father(greg, rachel).
father(greg, steven).
father(kendall, greg).
father(kendall, susan).
father(ronald, lisa).
father(ronald, andrea).
father(ronald, aaron).
father(ronald, krisi).
father(robert, matthew).
father(robert, amanda).
father(aaron, darron).
father(aaron, devon).
father(aaron, darcy).
father(john, andrew).
father(john, sarah).

mother(andrea, zach).
mother(andrea, titus).
mother(andrea, rachel).
mother(andrea, steven).
mother(shelby, greg).
mother(shelby, susan).
mother(judy, lisa).
mother(judy, andrea).
mother(judy, aaron).
mother(judy, krisi).
mother(susan, matthew).
mother(susan, amanda).
mother(alisa, darron).
mother(alisa, devon).
mother(alisa, darcy).
mother(lisa, andrew).
mother(lisa, sarah).