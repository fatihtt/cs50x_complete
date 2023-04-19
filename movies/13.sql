SELECT p1.name FROM people AS p1
JOIN stars AS s1 ON s1.person_id = p1.id
JOIN movies ON movies.id = s1.movie_id
JOIN stars AS s2 ON s2.movie_id = movies.id
JOIN people AS p2 ON s2.person_id = p2.id
WHERE p2.name = "Kevin Bacon" AND p2.birth = "1958" AND NOT p1.name = "Kevin Bacon"
GROUP BY p1.name