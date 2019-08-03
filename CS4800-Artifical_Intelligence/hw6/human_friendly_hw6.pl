/** 
	human_friendly_hw6.pl
	
	Author: Zach Tumbleson
	
	Contains the information for my family
	as specified in assignment 6. 
	
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

%siblings
male(steven).
male(titus).
female(rachel).

%parents
male(greg).
female(andrea).

%dad's side

%grandparents
male(kendall).
female(shelby).

%aunts and uncles
male(robert).
female(susan).

%cousins
male(matthew).
female(amanda).

%mom's side

%grandparents
male(ronald).
female(judy).

%aunts and uncles
male(aaron).
female(alisa).
male(john).
female(lisa).
female(krisi).

%cousins
male(andrew).
female(sarah).
male(darron).
male(devon).
female(darcy).

%relationship predicates

%parents
father(greg, zach).
father(greg, titus).
father(greg, rachel).
father(greg, steven).

mother(andrea, zach).
mother(andrea, titus).
mother(andrea, rachel).
mother(andrea, steven).

%father's parents
father(kendall, greg).
father(kendall, susan).

mother(shelby, greg).
mother(shelby, susan).

%mother's parents

father(ronald, lisa).
father(ronald, andrea).
father(ronald, aaron).
father(ronald, krisi).

mother(judy, lisa).
mother(judy, andrea).
mother(judy, aaron).
mother(judy, krisi).

%father's side extended

father(robert, matthew).
father(robert, amanda).

mother(susan, matthew).
mother(susan, amanda).

%mother's side extended

father(aaron, darron).
father(aaron, devon).
father(aaron, darcy).

mother(alisa, darron).
mother(alisa, devon).
mother(alisa, darcy).

father(john, andrew).
father(john, sarah).

mother(lisa, andrew).
mother(lisa, sarah).