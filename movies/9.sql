SELECT people.name FROM movies
JOIN stars ON stars.movie_id = movies.id
INNER JOIN people ON stars.person_id = people.id
WHERE movies.year = '2004'
GROUP BY people.id
ORDER BY people.birth ASC