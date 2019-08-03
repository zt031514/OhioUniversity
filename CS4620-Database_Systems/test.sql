select name, tshirt_size, count(tshirt_size) 
from ((runners natural join participates_in) join races on races.race_id = participates_in.race_id )
group by tshirt_size, name
order by name;

select name, sum(salary) 
from ((employees natural join works_on) join races on races.race_id = works on.race_id) 
group by races.name 
order by name;